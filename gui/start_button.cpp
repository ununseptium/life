#include <start_button.h>

static void read_cells(cells_field* cf, uint8_t* cells_arr){
	uint32_t cells_row_count = cf->vertical_cells_count();
	uint32_t cells_column_count = cf->horizontal_cells_count();

	for (int cell_row_index = 0; cell_row_index < cells_row_count; cell_row_index++){
		for (int cell_column_index = 0; cell_column_index < cells_column_count; cell_column_index++){
			cell* cur_cell = cf->get_cell(cell_column_index, cell_row_index);
			if (cur_cell->get_state() == fill_state){
				cells_arr[cells_row_count * cell_row_index + cell_column_index] = 1;
			}else{
				cells_arr[cells_row_count * cell_row_index + cell_column_index] = 0;
			}
		}
	}
}

void write_cells(void *cf, uint8_t *cells_arr){
	uint32_t cells_row_count = ((cells_field*)cf)->vertical_cells_count();
	uint32_t cells_column_count = ((cells_field*)cf)->horizontal_cells_count();

	for (int cell_row_index = 0; cell_row_index < cells_row_count; cell_row_index++){
		for (int cell_column_index = 0; cell_column_index < cells_column_count; cell_column_index++){
			cell* cur_cell = ((cells_field*)cf)->get_cell(cell_column_index, cell_row_index);
			if (cells_arr[cell_row_index * cells_row_count + cell_column_index] == 1){
				cur_cell->set_state(fill_state);
			}else{
				cur_cell->set_state(space_state);
			}
		}
	}
}

start_button::start_button(const QIcon &icon, cells_field *cf, edit_cell_button **buttons, uint32_t buttons_count, uint16_t latency): 
		QPushButton(icon, NULL, NULL){
	local_cells_field = cf;
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
				uint16_t cells_count = (local_cells_field->vertical_cells_count()) * (local_cells_field->horizontal_cells_count());
				uint8_t *cells_arr = (uint8_t*)malloc(cells_count);
				read_cells(local_cells_field, cells_arr);
				struct render_info *ri = (struct render_info*)malloc(sizeof(struct render_info));
				ri->grid = local_cells_field;
				ri->cells_count_width = local_cells_field->horizontal_cells_count();
				ri->cells_count_height = local_cells_field->vertical_cells_count();
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
