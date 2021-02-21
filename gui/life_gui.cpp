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

	uint32_t scale_val = find_scale_value(resolution_w, resolution_h, cells_count_wi, cells_count_he);

	QPixmap start_border_pixmap = QPixmap("resources\\start_border.svg");
	start_border_pixmap = start_border_pixmap.scaled(START_BORDER_WI * scale_val, START_BORDER_HE * scale_val);
	QGraphicsPixmapItem start_border_pixmap_item = QGraphicsPixmapItem(start_border_pixmap, NULL);

	QPixmap up_border_pixmap = QPixmap("resources\\up_border.svg");
	up_border_pixmap = up_border_pixmap.scaled(UP_BORDER_WI * scale_val, UP_BORDER_HE * scale_val);
	QGraphicsPixmapItem up_border_pixmap_item = QGraphicsPixmapItem(up_border_pixmap, NULL);

	QPixmap left_border_pixmap = QPixmap("resources\\left_border.svg");
	left_border_pixmap = left_border_pixmap.scaled(LEFT_BORDER_WI * scale_val, LEFT_BORDER_HE * scale_val);
	QGraphicsPixmapItem left_border_pixmap_item = QGraphicsPixmapItem(left_border_pixmap, NULL);

	cells_field *cf = new cells_field(
			cells_count_wi, cells_count_he, &start_border_pixmap_item, &left_border_pixmap_item, &up_border_pixmap_item
	);

	for (uint8_t row_index = 0; row_index < cells_count_he; row_index++){
		for (uint8_t column_index = 0; column_index < cells_count_wi; column_index++){
			cell *cur_cell = new cell(space_state, scale_val);
			cur_cell->set_fill_button(black_cell_button);
			cur_cell->set_clear_button(white_cell_button);
			cf->set_cell(cur_cell, column_index, row_index);
		}
	}

	edit_cell_button *edit_buttons[] = {white_cell_button, black_cell_button};
	QIcon start_icon = QIcon("resources\\start_button.svg");
	start_button *sb = new start_button(start_icon, cf, edit_buttons, 2, ms_delay);
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
	vertical_layout->addWidget(cf);

	QWidget *window = new QWidget();
	window->setLayout(vertical_layout);
	window->show();
}

void start_event_loop(event_loop el){
	el->exec();
}
