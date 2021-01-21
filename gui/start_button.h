#ifndef CUSTOM_BUTTON
#define CUSTOM_BUTTON

#include <QEvent>
#include <QGridLayout>
#include <QMouseEvent>
#include <QPushButton>
#include <Qt>
#include <cell.h>
#include <edit_cell_button.h>
#include <stdint.h>

class start_button: public QPushButton{
	private:
		void block_buttons();
		void unblock_buttons();
		QGridLayout *cells_field;
		edit_cell_button **buttons_arr;
		uint32_t buttons_count;
		uint32_t is_active;

	public:
		start_button(const QIcon &icon, QGridLayout *grid_layout, edit_cell_button **buttons, uint32_t buttons_count);
		~start_button();

	protected:
		bool event(QEvent *e) override;
};

#endif
