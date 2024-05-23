#include <stdio.h>
#include <stdlib.h>
#include "fib.h"

// function declaration
int read_int(char *arg);

int main(int argc, char **argv) {
	// checking the number of arguments
	if (argc != 2) {
		fprintf(stderr, "ERR: expected 1 argument, received %d\n", argc - 1);
		return EXIT_FAILURE;
	}

	// reading in input
	int n = read_int(argv[1]);
	if (n < 0) {
		return EXIT_FAILURE;
	}
	printf("n = %d\n", n);

	// call your implementation of get_nth_fib & print the result
	int nth_fib = get_nth_fib(n);
	printf("The nth fibonacci number for n = %d is %d\n", n, nth_fib);

	return EXIT_SUCCESS;
}

/*
 * ------ Note: Do not change anything below this line! ------
 *
 * Helper function which reads in an integer and handles boundary checking.
 * You may not understand parts of this function right now but you should 
 * learn enough to understand it in a couple weeks. You may just black box
 * the function for now and just assume it works.
 *
 * On success, the function returns the integer read in.
 * On failure, the success returns -1
 */
int read_int(char *input) {
	char *p;
	long int n = strtol(input, &p, 10);
	if (n < 0 || n > 45 || *p != '\0') {
		fprintf(stderr, "ERR: argument must be an integer in the range [0,45]\n");
		return -1;
	}
	return (int) n;
}
