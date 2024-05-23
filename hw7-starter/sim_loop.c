#include "cse30liferevisited.h"

void sim_loop(Board* board, unsigned int steps) {
	while(steps) {
		for (size_t i = 0; i < board->nrows; i++) {
			do_row(board->next_buffer, board->buffer, i, board->nrows, board->ncols);	
		}
	
		swap_buffers(board);
		board->gen++;
		steps--;
	}
}
