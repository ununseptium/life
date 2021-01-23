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
#include <render.h>

#ifndef _RENDER_INFO
#define _RENDER_INFO
struct render_info{
	uint8_t cells_count_width;
	uint8_t cells_count_height;
	uint8_t *cells_array;
	void *grid;
	void (*update_grid_fnc)(void* grid, uint8_t *cells_array);
}
#endif

class start_button: public QPushButton{
	private:
		void block_buttons();
		void unblock_buttons();
		QGridLayout *cells_field;
		edit_cell_button **buttons_arr;
		uint32_t buttons_count;
		uint32_t is_active;
		HANDLE render_thread;

	public:
		start_button(const QIcon &icon, QGridLayout *grid_layout, edit_cell_button **buttons, uint32_t buttons_count);
		~start_button();

	protected:
		bool event(QEvent *e) override;
};

#endif
