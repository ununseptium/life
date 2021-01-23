#include <stdio.h>
#include <windows.h>

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

DWORD test_thread_fnc(void* param);
