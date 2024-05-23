#include "node.h"
#include <stdlib.h>

void delete_table(Node **htable, size_t table_size) {
	// Walk through the chains in table
	for (size_t i = 0; i < table_size; i++) {
		// Free all the memory associated to each node in each chain
		Node *curr = htable[i];
		while(curr != NULL) {
			Node *temp = curr->next;
			free (curr->id);
			free (curr->purchased_item);
			free (curr);
			curr = temp;	
		}
	}

	// Free the entire table
	free(htable);
}
