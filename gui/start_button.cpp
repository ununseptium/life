#include <start_button.h>

static void read_cells(QGridLayout* cells_field, uint8_t* cells_arr){
	uint32_t border_offset = 1;
	uint32_t cells_row_count = cells_field->rowCount() - border_offset;
	uint32_t cells_column_count = cells_field->columnCount() - border_offset;

	for (int cell_row_index = 0; cell_row_index < cells_row_count; cell_row_index++){
		for (int cell_column_index = 0; cell_column_index < cells_column_count; cell_column_index++){
			cell* cur_cell = (cell*)(
					cells_field->
					itemAtPosition(cell_row_index + border_offset, cell_column_index + border_offset)->
					widget()
			);
			if (cur_cell->get_state() == fill_state){
				cells_arr[cells_row_count * cell_row_index + cell_column_index] = 1;
			}else{
				cells_arr[cells_row_count * cell_row_index + cell_column_index] = 0;
			}
		}
	}
}

void write_cells(void *grid, uint8_t *cells_arr){
	QGridLayout *cells_field = (QGridLayout*)grid;
	uint32_t border_offset = 1;
	uint32_t cells_row_count = cells_field->rowCount() - border_offset;
	uint32_t cells_column_count = cells_field->columnCount() - border_offset;

	for (int cell_row_index = 0; cell_row_index < cells_row_count; cell_row_index++){
		for (int cell_column_index = 0; cell_column_index < cells_column_count; cell_column_index++){
			cell* cur_cell = (cell*)(
					cells_field->
					itemAtPosition(cell_row_index + border_offset, cell_column_index + border_offset)->
					widget()
			);
			if (cells_arr[cell_row_index * cells_row_count + cell_column_index] == 1){
				cur_cell->set_state(fill_state);
			}else{
				cur_cell->set_state(space_state);
			}
		}
	}
}

start_button::start_button(const QIcon &icon, QGridLayout *grid_layout, edit_cell_button **buttons, uint32_t buttons_count, uint16_t latency): 
		QPushButton(icon, NULL, NULL){
	local_cells_field = grid_layout;
	buttons_arr = (edit_cell_button**)malloc(buttons_count * sizeof(edit_cell_button));
	for (uint32_t button_index = 0; button_index < buttons_count; button_index++){
		buttons_arr[button_index] = buttons[button_index];
	}

	this->buttons_count = buttons_count;
	is_active = 0;
	render_thread = NULL;
	this->latency = latency;
}

start_button::~start_button(){
	free(buttons_arr);
}

bool start_button::event(QEvent *e){
	if (e->type() == QEvent::MouseButtonPress){
		QMouseEvent *me = dynamic_cast<QMouseEvent*>(e);
		if (me != NULL && me->button() == Qt::LeftButton){
			if (!is_active){
				is_active = 1;
				block_buttons();
				uint16_t cells_count = (local_cells_field->rowCount() - 1) * (local_cells_field->columnCount() - 1);
				uint8_t *cells_arr = (uint8_t*)malloc(cells_count);
				read_cells(local_cells_field, cells_arr);
				struct render_info *ri = (struct render_info*)malloc(sizeof(struct render_info));
				ri->grid = local_cells_field;
				ri->cells_count_width = local_cells_field->columnCount() - 1;
				ri->cells_count_height = local_cells_field->rowCount() - 1;
				ri->cells_array = cells_arr;
				ri->latency = latency;
				ri->update_grid_fnc = write_cells;
				render_thread = CreateThread(NULL, 0, render_cycle, ri, 0, NULL);
				thread_data = ri;
			}else{
				is_active = 0;
				unblock_buttons();
				DWORD ex_code;
				GetExitCodeThread(render_thread, &ex_code);
				TerminateThread(render_thread, ex_code);
				free(((struct render_info*)thread_data)->cells_array);
				free(thread_data);
			}
		}
	}
	return QPushButton::event(e);
}

void start_button::block_buttons(){
	for (uint32_t button_index = 0; button_index < buttons_count; button_index++){
		buttons_arr[button_index]->set_checked(false);
		buttons_arr[button_index]->set_checkable(0);
	}
}

void start_button::unblock_buttons(){
	for (uint32_t button_index = 0; button_index < buttons_count; button_index++){
		buttons_arr[button_index]->set_checkable(1);
	}
}
