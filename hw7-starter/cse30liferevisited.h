#ifndef CSE30LIFE_H
#define CSE30LIFE_H

#include <stddef.h>
#include <stdint.h>

typedef uint8_t Cell;

typedef struct {
	Cell *buf1; /* pointer to first life board buffer */
	Cell *buf2; /* pointer to ansecond life board buffer */
	size_t nrows; /* number of rows in the life board */
	size_t ncols; /* number of cols in the life board */
	Cell *buffer; /* pointer to the current life board's buffer */
	Cell *next_buffer; /* pointer to the next iteration's board buffer */
	unsigned int gen; /* generation number */
} Board;

void clear_board(Board *board);
void swap_buffers(Board *board);
size_t get_index(size_t ncols, size_t row, size_t col);

size_t mod(int x, size_t N);

Board *create_board(const char *filename);
void sim_loop(Board *board, unsigned int steps);
void do_row(Cell *dest, Cell *src, size_t row, size_t rows, size_t cols);

#endif
