#include <edit_cell_button.h>

edit_cell_button::edit_cell_button(QWidget *parent, const QIcon &icon): QToolButton(parent) {
	ecb_count = 0;
	setIcon(icon);
	setCheckable(true);
	ecb_set = (edit_cell_button**)malloc(sizeof(edit_cell_button*));
	is_checkable = 1;
}

edit_cell_button::~edit_cell_button(){
	free(ecb_set);
}

void edit_cell_button::add_button(edit_cell_button *button){
	ecb_set[ecb_count] = button;
	ecb_count++;
}

bool edit_cell_button::event(QEvent *e){
	if (!is_checkable) return QToolButton::event(e);

	if (e->type() == QEvent::MouseButtonPress){
		QMouseEvent *me = dynamic_cast<QMouseEvent*>(e);
		if (me != NULL && me->button() == Qt::LeftButton){
			onChangeCheckable(!isChecked());
		}
	}
	return QToolButton::event(e);
}

void edit_cell_button::set_checked(bool check){
	QToolButton::setChecked(check);
	onChangeCheckable(check);
}

void edit_cell_button::onChangeCheckable(bool checked){
	if (checked){
		for (int button_index = 0; button_index < ecb_count; button_index++){
			ecb_set[button_index]->setChecked(false);
		}
	}
}

void edit_cell_button::set_checkable(int checkable){
	is_checkable = checkable;
	setCheckable((bool)checkable);
}
