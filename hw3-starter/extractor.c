#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_LEN 1024 // including null terminator
#define USAGE_FORMAT_STR "ERR: expected usage is %s -c <in_cols> [-d delimiter] [-s] col1 ...\n"


int main(int argc, char **argv) {		
	int in_cols = 0; // number of columns in input
	int out_cols = 0; // number of columns to output

	bool c_flag = false; // keep track of whether or not we received the required c flag
	bool stats_flag = false; // keep track of whether -s flag is passed in or not

	char delim = ','; // keep track of the delimiter, by default it is a comma

	// local variables to store the statistics
	unsigned int lines = 0; // number of lines in input
	size_t max_len = 0; // longest field in input
	size_t output_size = 0; // total output printed in characters

	int c;
	while ( (c = getopt(argc, argv, "c:sd:")) != -1 ) {
		switch (c) {
			case 'c':
				c_flag = 1;
				in_cols = atoi(optarg);
				break;
			
			case 'd':
				delim = *optarg;
				break;

			case 's':
				stats_flag = 1;
				break;
						
			default:
				fprintf(stderr, USAGE_FORMAT_STR, *argv);
				return EXIT_FAILURE;
		}
	}

	if (c_flag != 1 || in_cols == 0) {
		// we did not receive the required c option, print usage and terminate
		fprintf(stderr, USAGE_FORMAT_STR, *argv);
		return EXIT_FAILURE;
	}
	
	/* pointers to arrays which will be allocated dynamically by you */
	char **colptrs = NULL; /* pointer to array of pointers to the start of
	                         each field in input buffer */
	int *target_cols = NULL; /* pointer to array of output indices */
	
	// allocate arrays dynamically
	colptrs = malloc(sizeof(*colptrs) * (in_cols)); 
	if (colptrs == NULL) {
		return EXIT_FAILURE;
	}

	out_cols = (argc - optind);
	target_cols = malloc(sizeof(*target_cols) * out_cols);
	if (target_cols == NULL) { 
		free(colptrs);
		return EXIT_FAILURE;
	}
 
	for (int i = 0; i < out_cols; i++) {
		*(target_cols + i) = atoi(*(argv + optind + i));
	}

	char line[MAX_LINE_LEN]; // read buffer for processing lines in input
	
	// Loop over input stream from stdin
	while ( (*colptrs = fgets(line, 1024, stdin)) != NULL ) {
		char *reset = *colptrs;
		int column = 1;
		int i = 0;	
		
		// Parse line, change delim to '\0', set colptrs
		while (1) {
			char *curr = *colptrs + i;
			if (*curr == delim) {
				*curr = '\0';
				*(colptrs + column) = curr + 1;
				*colptrs = curr + 1;
				column++;
				i = 0;
				continue;
			}
			else if (*curr == '\n') {
				*curr = '\0';
				*colptrs = reset;
				break;
			}
			i++;
		}

		// If incorrect in_cols
		if (in_cols != column) {
			printf("ERR: line %s has incorrect number of columns, expected %d, received %d.\nDropping line...\n", *colptrs, in_cols, column);
			continue;
		}
	
		// Parse colptrs & print target_cols columns
		for (int i = 0; i < out_cols; i++) {	
			char *output = *(colptrs + *(target_cols + i) - 1);	
			if (i != out_cols - 1) {
				printf("%s%c", output, delim);
			}
			else {	
				printf("%s\n", output);

			}

			// Calculate output_size
			if (stats_flag) {	
				for (int j = 0; *(output + j) != '\0'; j++) {
					output_size++;
				}
				output_size++;
			}
		}

		// Calculate max_len and lines	
		if (stats_flag) {
			for (int i = 0; i < in_cols; i++) {
				size_t field_size = 0;	
				char *curr = *(colptrs + i);
				while (1) {
					if (*curr == '\0') {
						break;
					}	
					field_size++;
					curr++;
				}	
				if ( field_size > max_len ) {
					max_len = field_size;
				}
			}
			lines++;
		}
	}

	// Print stats
	if (stats_flag) {
		printf(
			"Number of lines: %d\nLongest field: %zu characters\nOutput size: %zu characters\n", lines, max_len, output_size
		);
	}

	// free the memory for arrays allocated with malloc
	free(colptrs);
	free(target_cols);

	return EXIT_SUCCESS;
}	
