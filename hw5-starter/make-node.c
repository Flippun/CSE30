#include "node.h"
#include <stdlib.h>
#include <string.h>

Node *make_node(Node *front, char *id, char *purchased_item, double cost) {
	// Create a node, copy in the parameter fields
	Node *node = malloc(sizeof(Node));
	if (node == NULL) { return NULL; }

	char *nid, *nitem;

	int len1 = strlen(id);
	nid = malloc(sizeof(char) * (len1+1));
	if (nid == NULL) { return NULL; }
	strcpy(nid, id);
	nid[len1] = '\0';

	int len2 = strlen(purchased_item);
	nitem = malloc(sizeof(char) * (len2+1));	
	if (nitem == NULL) { return NULL; }
	strcpy(nitem, purchased_item);
	nitem[len2] = '\0';

	node->id = nid;
	node->purchased_item = nitem;
	node->cost = cost;

	// Link the new node into the chain
	node->next = front;

	// Return the new head of the chain if the function succeeded
	return node;
}
