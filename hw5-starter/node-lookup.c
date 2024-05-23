#include "node.h"
#include <string.h>

Node *node_lookup(Node *front, const char *id) {
	// Step through the chain pointed to by front
	// if found return a pointer to the node, else return NULL
	while (front != NULL) {
		if ( strcmp(front->id, id) == 0 ) {
			return front;
		}
		front = front->next;
	}
	return NULL; 
}
