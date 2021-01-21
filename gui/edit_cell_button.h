#ifndef EDIT_CELL_BUTTON_H
#define EDIT_CELL_BUTTON_H

#include <QToolButton>
#include <stdlib.h>
#include <QToolButton>
#include <QEvent>
#include <QMouseEvent>
#include <Qt>

class edit_cell_button: public QToolButton{
	private:
		edit_cell_button **ecb_set;
		int ecb_count;
		int is_checkable;
	public:
		edit_cell_button(QWidget *parent, const QIcon &icon);
		~edit_cell_button();
		void add_button(edit_cell_button *button);
		void set_checkable(int checkable);
		void set_checked(bool check);
	private:
		bool event(QEvent *e) override;
		void onChangeCheckable(bool checked);
};

#endif
