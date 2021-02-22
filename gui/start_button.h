#ifndef CUSTOM_BUTTON
#define CUSTOM_BUTTON

#include <QEvent>
#include <QGridLayout>
#include <QMouseEvent>
#include <QPushButton>
#include <Qt>
#include <cell.h>
#include <cells_field.h>
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
	uint16_t latency;
	void (*update_grid_fnc)(void* grid, uint8_t *cells_array);
};
#endif

void write_cells(void *cf, uint8_t *cells_arr);

class start_button: public QPushButton{
	private:
		void block_buttons();
		void unblock_buttons();
		cells_field *local_cells_field;
		edit_cell_button **buttons_arr;
		uint32_t buttons_count;
		uint32_t is_active;
		HANDLE render_thread;
		void *thread_data;
		uint16_t latency;

	public:
		start_button(const QIcon &icon, cells_field *cf, edit_cell_button **buttons, uint32_t buttons_count, uint16_t latency);
		~start_button();

	protected:
		bool event(QEvent *e) override;
};

#endif
