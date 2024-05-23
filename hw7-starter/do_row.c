#include "cse30liferevisited.h"


void do_row(Cell *dest, Cell *src, size_t row, size_t rows, size_t cols) {
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
