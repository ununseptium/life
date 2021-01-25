#include <render.h>

void get_neighbors_cells(
		uint8_t *cells_array, uint32_t cell_index, struct neighbors_cells *nc,
		uint8_t cell_count_width, uint8_t cells_count_height
){
	uint8_t cell_row = cell_index / cell_count_width;
	uint8_t cell_column = cell_index % cell_count_width;

	if (cell_row == 0 || cell_column == 0)
		nc->neigh0 = 0;
	else
		nc->neigh0 = cells_array[cell_index - cells_count_width - 1];

	if (cell_row == 0)
		nc->neigh1 = 0;
	else
		nc->neigh1 = cells_array[cell_index - cell_count_width];

	if (cell_row == 0 || cell_column == cells_count_width - 1)
		nc->neigh2 = 0;
	else
		nc->neigh2 = cells_array[cell_index - cells_count_width + 1];

	if (cell_column == cell_count_width - 1)
		nc->neigh3 = 0;
	else
		nc->neigh3 = cells_array[cell_index + 1];

	if (cell_row == cells_count_height - 1 || cell_column == cells_count_width - 1)
		nc->neigh4 = 0;
	else
		nc->neigh4 = cells_array[cell_index + cell_count_width + 1];

	if (cell_row == cells_count_height - 1)
		nc->neigh5 = 0;
	else
		nc->neigh5 = cells_array[cell_index + cells_count_width];

	if (cell_row == cells_count_width - 1 || cell_column == 0)
		nc->neigh6 = 0;
	else
		nc->neigh6 = cells_array[cell_index + cells_count_width - 1];

	if (cell_column == 0)
		nc->neigh7 = 0;
	else
		nc->neigh7 = cells_array[cell_index - 1];
}

uint32_t get_fill_neighbors_count(struct neighbors_cells nc){
	uint32_t fill_neighbors_cells = 0;

	if (nc.neigh0 == 1)
		fill_neighbors_cells++;
	if (nc.neigh1 == 1)
		fill_neighbors_cells++;
	if (nc.neigh2 == 1)
		fill_neighbors_cells++;
	if (nc.neigh3 == 1)
		fill_neighbors_cells++;
	if (nc.neigh4 == 1)
		fill_neighbors_cells++;
	if (nc.neigh5 == 1)
		fill_neighbors_cells++;
	if (nc.neigh6 == 1)
		fill_neighbors_cells++;
	if (nc.neigh7 == 1)
		fill_neighbors_cells++;
	
	return fill_neighbors_cells;
}

DWORD render_cycle(struct render_info* ri){
	while(1){

	}
	return 0;
}
