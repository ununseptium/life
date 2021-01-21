#include <cell.h>

cell::cell(enum cell_state cs, uint32_t scale_value): QLabel() {
	this->scale_value = scale_value;
	set_state(cs);
}

void cell::set_fill_button(edit_cell_button *fill_button){
	this->fill_button = fill_button;
}

void cell::set_clear_button(edit_cell_button *clear_button){
	this->clear_button = clear_button;
}

bool cell::event(QEvent *e){
	if (e->type() == QEvent::MouseButtonPress){
		QMouseEvent *me = dynamic_cast<QMouseEvent*>(e);
		if (me != NULL && me->button() == Qt::LeftButton){
			if (fill_button->isChecked() && get_state() != fill_state){
				set_state(fill_state);
			} else if (clear_button->isChecked() && get_state() != space_state){
				set_state(space_state);
			}
		}
	}
	return QLabel::event(e);
}

enum cell_state cell::get_state(){
	return state;
}

void cell::set_state(enum cell_state cs){
	QPixmap pixmap;
	if (cs == fill_state){
		pixmap = QPixmap("resources\\fill_cell.svg");
	} else{
		pixmap = QPixmap("resources\\space_cell.svg");
	}
	pixmap = pixmap.scaled(9 * scale_value, 9 * scale_value);
	setPixmap(pixmap);
	state = cs;
}
