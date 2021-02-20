#ifndef _CELLS_FIELD_H
#define _CELLS_FIELD_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem> 
#include <stdint.h>
#include <cell.h>

class cells_field: public QGraphicsView{
	private:
		uint8_t cells_w;
		uint8_t cells_h;
		QGraphicsScene *local_scene;
		uint32_t border_offset_left;
		uint32_t border_offset_up;
		uint32_t cell_width;
		uint32_t cell_height;
	public:
		cells_field(
				uint8_t cells_count_width, uint8_t cells_count_height, QGraphicsPixmapItem *start_border, 
				QGraphicsPixmapItem *left_border, QGraphicsPixmapItem *up_border		
		);
		cell get_cell(uint8_t w, uint8_t h);
		void set_cell(cell c, uint8_t w, uint8_t h);
};

#endif
