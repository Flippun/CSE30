#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
	int opt;
	bool scramble = true;

	while ((opt = getopt(argc, argv, "us")) != -1) {
		switch (opt) {
		case 's':
			scramble = true;
			break;
		case 'u':
			scramble = false;
			break;
		case '?':
			fprintf(stderr, "unknown option: %c\n", opt);
			return 1;
		default:
			fprintf(stderr, "unexpcted option: %c\n", opt);
			abort();
		}
	}

	if (argc != 4) {
		fprintf(stderr, "usage: %s <s|-u> <input-file> <key>\n", argv[0]);
		return EXIT_FAILURE;
	}

	// file is now in argv[2] and key is in argv[3]
	FILE *fin = fopen(argv[2], "r");
	if (fin == NULL) {
		return 1;
	}

	int in_index = 0;
	int out_index = 0;
	int key_index = 0;
	int i = 0;
	int key_length = strlen(argv[3]);

	if (scramble) {
		while (1) {
			in_index = toupper( fgetc(fin) );
			if (in_index == EOF) {				// End Condition
				break;
			}	
			if (in_index < 'A' || in_index > 'Z') {  // If non-alphabet, skip
				continue;
			}

			if (i == key_length) {			// Wraps Key
				i = 0;
			}
			key_index = argv[3][i++];		
			
			out_index = ( (in_index + key_index) % 26 );	// Vignere
			printf("%c", out_index + 'A');	
		}
	}

	else {
		while (1) {
			in_index = toupper( fgetc(fin) );
			if (in_index == EOF) {				// End condition
				break;
			}	
			if (in_index < 'A' || in_index > 'Z') {  // If non-alphabet, skip
				continue;
			}

			if (i == key_length) {			// Wraps Key
				i = 0;
			}
			key_index = argv[3][i++];		
			
			out_index = ( (in_index -  key_index + 26) % 26 );  // Vignere
			printf("%c", out_index + 'A');	
		}
	}

	printf("\n");
		
	// close the file
	fclose(fin);
	return 0;
}
