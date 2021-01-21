#include <life_gui.h>

void find_max_avalible_free_space(uint16_t *width, uint16_t *height){
	RECT rect;
	SystemParametersInfoA(SPI_GETWORKAREA, 0, &rect, 0);
	uint16_t os_space_width = abs(rect.left - rect.right);
	uint16_t os_space_height = abs(rect.top - rect.bottom);

	uint16_t frame_width = GetSystemMetrics(SM_CYSIZEFRAME);
	uint16_t frame_height = GetSystemMetrics(SM_CXSIZEFRAME) + GetSystemMetrics(SM_CYCAPTION);

	*width = os_space_width - frame_width;
	*height = os_space_height - frame_height;
}

uint32_t find_scale_value(uint16_t usage_width, uint16_t usage_height, uint8_t cells_w, uint8_t cells_h){
	uint32_t scale_value = 1;
	while (
			usage_width > (cells_w * CELL_WI + 1) * (scale_value + 1) && 
			usage_height > (cells_h * CELL_HE + 1) * (scale_value + 1)
	){
		scale_value += 1;
	}

	return scale_value;
}

event_loop init_event_loop(char *argv[]){
	int arg = 1;
	return new QApplication(arg, argv);
}

void create_gui(uint8_t cells_count_wi, uint8_t cells_count_he, uint16_t ms_delay){
	uint16_t resolution_w;
	uint16_t resolution_h;
	find_max_avalible_free_space(&resolution_w, &resolution_h);
	resolution_h -= MANAGE_BUTTONS_HE;

	QIcon white_cell_icon = QIcon("resources\\white_cell.svg");
	edit_cell_button *white_cell_button = new edit_cell_button(NULL, white_cell_icon);
	white_cell_button->setFixedHeight(MANAGE_BUTTONS_HE);

	QIcon black_cell_icon = QIcon("resources\\black_cell.svg");
	edit_cell_button *black_cell_button = new edit_cell_button(NULL, black_cell_icon);
	black_cell_button->setFixedHeight(MANAGE_BUTTONS_HE);

	white_cell_button->add_button(black_cell_button);
	black_cell_button->add_button(white_cell_button);
	
	QGridLayout *cells_field = new QGridLayout();
	cells_field->setContentsMargins(0, 0, 0, 0);
	cells_field->setSpacing(0);
	uint32_t scale_val = find_scale_value(resolution_w, resolution_h, cells_count_wi, cells_count_he);
	for (uint8_t row_index = 0; row_index < cells_count_he + 1; row_index++){
		for (uint8_t column_index = 0; column_index < cells_count_wi + 1; column_index++){
			uint32_t is_border = row_index == 0 || column_index == 0;
			if (is_border){
				QLabel *label = new QLabel();
				QPixmap pixmap;
				if (row_index == 0 && column_index == 0){
					pixmap = QPixmap("resources\\start_border.svg");
					pixmap = pixmap.scaled(START_BORDER_WI, START_BORDER_HE);
				} else if (row_index == 0){
					pixmap = QPixmap("resources\\up_border.svg");
					pixmap = pixmap.scaled(UP_BORDER_WI, UP_BORDER_HE);
				}else {
					pixmap = QPixmap("resources\\left_border.svg");
					pixmap = pixmap.scaled(LEFT_BORDER_WI, LEFT_BORDER_HE);
				}

				pixmap = pixmap.scaled(pixmap.width() * scale_val, pixmap.height() * scale_val);
				label->setPixmap(pixmap);
				cells_field->addWidget(label, row_index, column_index, (Qt::Alignment)0);
			}else{
				cell *cur_cell = new cell(space_state, scale_val);
				cur_cell->set_fill_button(black_cell_button);
				cur_cell->set_clear_button(white_cell_button);
				cells_field->addWidget(cur_cell, row_index, column_index, (Qt::Alignment)0);
			}
		}
	}

	edit_cell_button *edit_buttons[] = {white_cell_button, black_cell_button};
	QIcon start_icon = QIcon("resources\\start_button.svg");
	start_button *sb = new start_button(start_icon, cells_field, edit_buttons, 2);
	sb->setFixedHeight(MANAGE_BUTTONS_HE);

	QHBoxLayout *horizontal_layout = new QHBoxLayout();
	horizontal_layout->setContentsMargins(0, 0, 0, 0);
	horizontal_layout->setSpacing(0);
	horizontal_layout->addWidget(sb, 1, (Qt::Alignment)0);
	horizontal_layout->addWidget(white_cell_button, 1, (Qt::Alignment)0);
	horizontal_layout->addWidget(black_cell_button, 1, (Qt::Alignment)0);

	QVBoxLayout *vertical_layout = new QVBoxLayout();
	vertical_layout->setSpacing(0);
	vertical_layout->setContentsMargins(0, 0, 0, 0);
	vertical_layout->addLayout(horizontal_layout);
	vertical_layout->addLayout(cells_field);

	QWidget *window = new QWidget();
	window->setLayout(vertical_layout);
	window->show();
}

void start_event_loop(event_loop el){
	el->exec();
}
