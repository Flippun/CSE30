#include "sim.h"

/**
 * gets x mod N (works for negative numbers as well! Use this instead of %)
 */
size_t mod(int x, size_t N) { return (x + x / N * N) % N; }

/**
 * process one row of the board
 */
static void do_row(Cell *dest, Cell *src, size_t row, size_t rows, size_t cols) {
	for (size_t col = 0; col < cols; col++) {
		size_t neighbors = 0;
		size_t index = get_index(cols, row, col);

		for (size_t j = 0; j < 3; j++) {
			size_t cmp_row = mod(row + rows + j - 1, rows);
			for (size_t k = 0; k < 3; k++) {
				size_t cmp_col = mod(col + cols + k - 1, cols);
				size_t cmp_index = get_index(cols, cmp_row, cmp_col);

				if (row == cmp_row && col == cmp_col) { continue; }
				if (src[cmp_index]) { neighbors++; }		
			}
		}	

		if (src[index]) {
			if (neighbors == 2 || neighbors == 3) {
				dest[index] = 1;
			}
			else { 
				dest[index] = 0;
			}
		}
		else {
			if (neighbors == 3 || neighbors == 6) { 
				dest[index] = 1;
			}	
			else {
				dest[index] = 0;
			}
		}	
	}
}

/**
 * perform a simulation for "steps" generations
 *
 * for steps
 *   calculate the next board
 *   swap current and next
 */
void sim_loop(Board *board, unsigned int steps) {
	while(steps) {
		for (size_t i = 0; i < board->nrows; i++) {
			do_row(board->next_buffer, board->buffer, i, board->nrows, board->ncols);
		}
		swap_buffers(board);
		board->gen++;
		steps--;
	}
}
