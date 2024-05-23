#include "board.h"
#include "cse30life.h"

/**
 * create a new board - STUDENT
 *
 * - malloc a boards structure
 * - set the generation to 0
 * - open the file (if it doesn't exist, return a NULL pointer
 * - read the first line which the number of rows
 * - read the second line which is the number of cols
 * - set the # of rows and # of cols in the boards structure
 * - malloc buf1 and buf2
 * - clear both board buffers
 * - read the file until done.  each row contains a row and a columns separted by
 *   white space
 *     for each line, setCell in the next buffer
 * - swap the buffers
 * - close the file
 * - return the boards pointer
 */
Board *create_board(const char *filename) {
	Board *bptr = malloc(sizeof(Board)); 
	if (bptr == NULL) {
		return NULL;
	}	

	FILE *fp;
	if ((fp = fopen(filename, "r")) == NULL) {
		return NULL;
	}
	
	size_t rows;	
	fscanf(fp, "%zu", &rows);
	bptr->nrows = rows;

	size_t cols;
	fscanf(fp, "%zu", &cols);
	bptr->ncols = cols;

	bptr->buf1 = malloc(rows * cols);
	if (bptr->buf1 == NULL) {
		return NULL;
	}

	bptr->buf2 = malloc(rows * cols);
	if (bptr->buf2 == NULL) {
		return NULL;
	}

	bptr->buffer = bptr->buf1;
	bptr->next_buffer = bptr->buf2;
	clear_board(bptr);

	size_t row;
	size_t col;
	while ( fscanf(fp, "%zu %zu", &row, &col) > 0 ) {
		if (row >= rows || col >= cols) {
			fprintf(stderr, "Invalid index %zu %zu\n", row, col);
			delete_board(&bptr);
			fclose(fp);
			return NULL;
		}
		size_t index = get_index(cols, row, col);
		bptr->next_buffer[index] = 1;
	}
	swap_buffers(bptr);

	if (fclose(fp) == EOF) {
		fprintf(stderr, "File did not close properly!");
		return NULL;
	}

	bptr->gen = 0;
	return bptr;
}

/**
 * delete a board
 *
 * note: this is a deep delete - STUDENT
 * the pointer to the boards structure should be set to NULL
 * after the memory is freed.
 */
void delete_board(Board **bpp) {
	free((*bpp)->buf1);
	free((*bpp)->buf2);
	free(*bpp);
	*bpp = NULL;
}

/**
 * set all the Cells to 0 - STUDENT
 */
void clear_board(Board *board) {
	for (size_t i = 0; i < board->nrows; i++) {
		for (size_t j = 0; j < board->ncols; j++) {
			size_t index = get_index(board->ncols, i, j);
			board->buf1[index] = 0;
			board->buf2[index] = 0;
		}
	}
}

/**
 * swap the current and next buffers
 */
void swap_buffers(Board *board) {
	Cell *temp_buffer = board->buffer;
	board->buffer = board->next_buffer;
	board->next_buffer = temp_buffer;	
}

/**
 * get a cell index
 */
size_t get_index(size_t ncols, size_t row, size_t col) {
	return row * ncols + col;
}
