#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char **argv) {

	int x = atoi(argv[1]);
	int N = atoi(argv[2]);

	printf("%d\n", (x + x / N * N) % N);


	return 0;
}
