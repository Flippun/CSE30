#include "node.h"
#include <limits.h>
#include <stdio.h>

#define TABLESIZE_MSG "Table size: %zu\n"
#define TOTAL_ENTRIES_MSG "Total entries: %lu\n"
#define LONGEST_MSG "Longest chain: %lu\n"
#define SHORTEST_MSG "Shortest chain: %lu\n"
#define THRESHOLD_MSG "Reached threshold: %lu\n"
#define EMPTY_MSG "Empty buckets: %lu\n"

void print_info(Node **htable, size_t table_size, unsigned long threshold) {
	// Walk down the indices of the htable
	// iterate through each chain and update statistics
	// print out statistics at end
	unsigned long total_entries = 0;
	unsigned long curr_chain = 0;
	unsigned long longest_chain = 0;
	unsigned long shortest_chain = ULONG_MAX;
	unsigned long reached_threshold = 0;
	unsigned long empty_buckets = 0;
	Node *curr = NULL;

	for (size_t i = 0; i < table_size; i++) {
		curr_chain = 0;
		curr = htable[i];
		while(curr != NULL)	{
			curr_chain++;
			curr = curr->next;
		}

		if (curr_chain == 0) {
			empty_buckets++;
			shortest_chain = 0;
			continue;
		}
	
		total_entries = total_entries + curr_chain;
		if (curr_chain > longest_chain) {
			longest_chain = curr_chain;
		}
		if (curr_chain < shortest_chain) {
			shortest_chain = curr_chain;
		}
		if (curr_chain >= threshold) {
			reached_threshold++;
		}
	}

	printf(TABLESIZE_MSG, table_size);
	printf(TOTAL_ENTRIES_MSG, total_entries);
	printf(LONGEST_MSG, longest_chain);
	printf(SHORTEST_MSG, shortest_chain);
	printf(THRESHOLD_MSG, reached_threshold);
	printf(EMPTY_MSG, empty_buckets);
}
