// DO NOT EDIT
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

/*
 * function protoype for your assembly routine
 */
extern uint32_t fpconvert(uint32_t);

typedef union {
	uint32_t i;
	float f;
} uf;

int main(int argc, char* argv[]) {
	uf cnvrt_num;
	FILE* infile;

	if (argc != 2) {
		fprintf(stderr, "Useage: convertfp file\n");
		return EXIT_FAILURE;
	}

	/*
	 * open the data file
	 */
	if ((infile = fopen(argv[1], "r")) == NULL) {
		perror("convertftp fopen()");
		return EXIT_FAILURE;
	}
	printf("15-bit Pattern\tIEEE Bit Pattern\tIEEE Base-10\n");
	/*
	 * read until EOF, calling your assembly function to convert
	 */
    unsigned int uint;
    while(fscanf(infile, "%x%*[^\n]", &uint) > 0){
		uint32_t fp = (uint32_t) uint;
		cnvrt_num.i = fpconvert(fp);
		printf("%04x\t\t", fp);
		printf("%08x\t\t", cnvrt_num.i);
		printf("%16.10g\n", cnvrt_num.f);
	}

	fclose(infile);
	return EXIT_SUCCESS;
}
