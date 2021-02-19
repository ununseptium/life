#ifndef CELL_H
#define CELL_H

#include <QEvent>
#include <QGraphicsPixmapItem>
#include <QGridLayout>
#include <QGridLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPixmap>
#include <Qt>
#include <edit_cell_button.h>
#include <stdint.h>

enum cell_state {space_state, fill_state};

class cell: public QGraphicsPixmapItem{
	private:
		edit_cell_button *fill_button;
		edit_cell_button *clear_button;
		uint32_t scale_value;
		enum cell_state state;
	public:
		cell(enum cell_state cs, uint32_t scale_value);
		void set_fill_button(edit_cell_button *fill_button);
		void set_clear_button(edit_cell_button *clear_button);
		enum cell_state get_state();
		void set_state(enum cell_state cs);
	
	protected:
};

#endif
