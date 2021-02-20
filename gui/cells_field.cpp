#include <cells_field.h>

cells_field::cells_field(
		uint8_t cells_count_width, uint8_t cells_count_height, QGraphicsPixmapItem *start_border, 
		QGraphicsPixmapItem *left_border, QGraphicsPixmapItem *up_border
){
	local_scene = new QGraphicsScene();
	this->setScene(local_scene);

	border_offset_up = up_border->pixmap().height();
	border_offset_left = left_border->pixmap().width();
	cells_w = cells_count_width;
	cells_h = cells_count_height;
	cell_width = up_border->pixmap().width();
	cell_height = left_border->pixmap().height();

	QGraphicsPixmapItem *local_start_border = new QGraphicsPixmapItem(start_border->pixmap());
	local_start_border->setOffset((qreal)0, (qreal)0);
	local_scene->addItem(local_start_border);

	QGraphicsPixmapItem *local_up_border;
	for (uint8_t up_border_index = 0; up_border_index < cells_w; up_border_index++){
		local_up_border = new QGraphicsPixmapItem(up_border->pixmap());
		local_up_border->setOffset(
				(qreal)(border_offset_left + up_border->pixmap().width() * up_border_index),
				(qreal)0
		);
		local_scene->addItem(local_up_border);
	}

	QGraphicsPixmapItem *local_left_border;
	for (uint8_t left_border_index = 0; left_border_index < cells_h; left_border_index++){
		local_left_border = new QGraphicsPixmapItem(left_border->pixmap());
		local_left_border->setOffset(
				(qreal)0,
				(qreal)(border_offset_up + up_border->pixmap().height() * left_border_index)
		);
		local_scene->addItem(local_left_border);
	}
}
