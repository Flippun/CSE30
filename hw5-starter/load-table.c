#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 100
#define FILE_OPEN_ERR_MSG "error in load_table while opening file %s\n"
#define DUPLICATE_ID_MSG "load_table duplicate entry: %s\n"
#define INSERTION_ERROR_MSG "load_table could not create node for %s\n"

bool load_table(Node **htable, size_t table_size, const char *filename) {
	FILE *fp = NULL;
	// pen the file and check that it was successful
	if ((fp = fopen(filename, "r")) == NULL) {
		fprintf(stderr, FILE_OPEN_ERR_MSG, filename);
		return 0;
	}

	// Loop through the file and read one line at a time using fgets
	char buf[MAX_LINE_LEN + 1]; // input buffer for fgets
	while (fgets(buf, MAX_LINE_LEN + 1, fp) == buf) {
		// For each line, use strtok to break it into columns
		char *id = strtok(buf, ",");
		char *purchased_item = strtok(NULL, ",");
		double cost = atof(strtok(NULL, ","));
		
		// Get the corresponding chain for this entry
		unsigned long bucket = hash(id) % table_size;

		// Check that the node doesn't already exist in table
		if (node_lookup(htable[bucket], id) != NULL) {
			fprintf(stderr, DUPLICATE_ID_MSG, id);
			continue;
		}

		// Add non-duplicate node to the front of its chain
		Node *node = make_node(*htable, id, purchased_item, cost); 
		if (node == NULL) {
			fprintf(stderr, INSERTION_ERROR_MSG, id);
			return 0;
		}	
		node->next = htable[bucket];
		htable[bucket] = node;

	}
	fclose(fp);
	return 1;
}
