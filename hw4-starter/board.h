#ifndef _BOARD_H
#define _BOARD_H
#include "cse30life.h"
#include <stdint.h>

// we can change the board type to different sizes to see how this affects the speed.
// DO NOT CHANGE - libcse30life library assumes uint8_t
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

extern Board *create_board(const char *filename);
extern void delete_board(Board **board);
extern void clear_board(Board *board);
extern void swap_buffers(Board *board);
extern void sim_step(Board *board, unsigned int steps);
extern void set_sim(Board *board, void (*sim)(Board *board, unsigned int steps));
extern size_t get_index(size_t ncols,
	size_t row,
	size_t col); // get index of (row,col) in 1D buffer

#endif // _BOARD_H
