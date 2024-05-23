#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_QUERY_LEN 100
#define MIN_TABLE_SIZE 3
#define DEFAULT_TABLE_SIZE 1873
#define QUERY_SUCCESS_FORMAT "found sale id=%s, purchased_item=%s, cost=%.5f\n"
#define QUERY_FAILURE_FORMAT "could not find sale with id=%s\n"
#define USAGE_STRING "%s [-s threshold] [-t table_size] <filename>\n"

int main(int argc, char **argv) {
	int s_flag = 0;
	size_t table_size = DEFAULT_TABLE_SIZE;
	size_t threshold = 0;

	// Parse opts with getopt and initialize these variables,
	// handle any bad inputs (missing filename or invalid option flag
	// by printing out the USAGE_STRING to stderr and exiting with failure.
	int c;
	while ( (c = getopt(argc, argv, "s:t:")) != -1 ) {
		switch (c) {
			case 's':
				s_flag = 1;
				threshold = strtoul(optarg, NULL, 0);
				break;

			case 't':
				table_size = strtoul(optarg, NULL, 0);
				if (table_size < MIN_TABLE_SIZE) {
					table_size = MIN_TABLE_SIZE;
				}
				break;

			default:
				fprintf(stderr, USAGE_STRING, argv[0]);
				return EXIT_FAILURE;
		}
	}

	if (optind != argc - 1) {
		fprintf(stderr, USAGE_STRING, argv[0]);
		return EXIT_FAILURE;
	}

	// Initialze htable
	// using calloc so all buckets are initialized to NULL
	Node **htable = calloc( table_size, sizeof(Node) );
	if (htable == NULL) {
		return EXIT_FAILURE;
	}

	// Get filename and call load_table;
	char *filename = argv[optind];


	if ( load_table(htable, table_size, filename) == 0) {
		fprintf(stderr, "error in load_table\n");
		return EXIT_FAILURE;
	}

	char query[MAX_QUERY_LEN + 1];
	char *end;
	int succ_queries = 0;
	// read one line at a time from stdin, do a lookup for that id
	while (fgets(query, MAX_QUERY_LEN + 1, stdin) == query) {
		// replace the \n, if it exists (for hashing)
		if ((end = strchr(query, '\n'))) *end = '\0'; // don't change this line

		unsigned long bucket = hash(query) % table_size; 
		Node *curr = node_lookup(htable[bucket], query);
	
		if (curr == NULL) {
		   	printf(QUERY_FAILURE_FORMAT, query);
		}
		else {
			printf(QUERY_SUCCESS_FORMAT, 
					query, curr->purchased_item, curr->cost);
			succ_queries++;
		}
	}

	printf("%d successful queries\n", succ_queries);

	// if -s called then print stats
	if (s_flag) {
		print_info(htable, table_size, threshold);
	}

	// Free all allocated memory associated with the table
	delete_table(htable, table_size);
	return EXIT_SUCCESS;
}
