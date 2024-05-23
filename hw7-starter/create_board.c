#include "cse30liferevisited.h"
#include <stdlib.h>
#include <stdio.h>

Board* create_board(const char* filename) {
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
		//	delete_board(&bptr);
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
