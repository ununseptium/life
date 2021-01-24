#include <stdio.h>
#include <windows.h>

#ifndef _RENDER_INFO
#define _RENDER_INFO
struct render_info{
	uint8_t cells_count_width;
	uint8_t cells_count_height;
	uint8_t *cells_array;
	void *grid;
	uint16_t latency;
	void (*update_grid_fnc)(void* grid, uint8_t *cells_array);
}
#endif

#ifndef _NEIGHBORS_CELLS
#define _NEIGHBORS_CELLS
struct neighbors_cells{
	// start from top-left neighbor's cell; clockwise
	uint8_t neigh0;
	uint8_t neigh1;
	uint8_t neigh2;
	uint8_t neigh3;
	uint8_t neigh4;
	uint8_t neigh5;
	uint8_t neigh6;
	uint8_t neigh7;
}
#endif

DWORD render_cycle(struct render_info* ri);
