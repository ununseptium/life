#include <render.h>

void get_neighbors_cells(
		uint8_t *cells_array, uint32_t cell_index, struct neighbors_cells *nc,
		uint8_t cells_count_width, uint8_t cells_count_height
){
	uint8_t cell_row = cell_index / cells_count_width;
	uint8_t cell_column = cell_index % cells_count_width;

	if (cell_row == 0 || cell_column == 0)
		nc->neigh0 = 0;
	else
		nc->neigh0 = cells_array[cell_index - cells_count_width - 1];

	if (cell_row == 0)
		nc->neigh1 = 0;
	else
		nc->neigh1 = cells_array[cell_index - cells_count_width];

	if (cell_row == 0 || cell_column == cells_count_width - 1)
		nc->neigh2 = 0;
	else
		nc->neigh2 = cells_array[cell_index - cells_count_width + 1];

	if (cell_column == cells_count_width - 1)
		nc->neigh3 = 0;
	else
		nc->neigh3 = cells_array[cell_index + 1];

	if (cell_row == cells_count_height - 1 || cell_column == cells_count_width - 1)
		nc->neigh4 = 0;
	else
		nc->neigh4 = cells_array[cell_index + cells_count_width + 1];

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

uint32_t get_fill_neighbors_cells_count(struct neighbors_cells nc){
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

void calc_next_cells_array(uint8_t *cur_cells, uint8_t *next_cells, uint8_t cells_count_width, uint8_t cells_count_height){
	uint32_t cells_count = cells_count_width * cells_count_height;
	struct neighbors_cells cur_cell_neighbors;
	for (uint32_t cell_index = 0; cell_index < cells_count; cell_index++){
		get_neighbors_cells(
				cur_cells, cell_index, &cur_cell_neighbors, 
				cells_count_width, cells_count_height
		);

		if (get_fill_neighbors_cells_count(cur_cell_neighbors) == 3 && cur_cells[cell_index] == 0)
			next_cells[cell_index] = 1;
		else if(get_fill_neighbors_cells_count(cur_cell_neighbors) != 3 && cur_cells[cell_index] == 0)
			next_cells[cell_index] = 0;
		else if (
					(
							get_fill_neighbors_cells_count(cur_cell_neighbors) < 2 || 
							get_fill_neighbors_cells_count(cur_cell_neighbors) > 3
					) && 
					cur_cells[cell_index] == 1
		)
			next_cells[cell_index] = 0;
		else
			next_cells[cell_index] = 1;
	}
}

DWORD render_cycle(struct render_info* ri){
	uint32_t cells_count = ri->cells_count_width * ri->cells_count_height;
	uint8_t current_cells_arr[cells_count];
	memcpy(current_cells_arr, ri->cells_array, cells_count);
	uint8_t next_cells_arr[cells_count];

	while(1){
		calc_next_cells_array(current_cells_arr, next_cells_arr, ri->cells_count_width, ri->cells_count_height);
		memcpy(current_cells_arr, next_cells_arr, cells_count);
		ri->update_grid_fnc(ri->grid, current_cells_arr);
		Sleep(ri->latency);
	}
	return 0;
}
