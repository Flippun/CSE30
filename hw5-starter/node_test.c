#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "node.h"

int main(int argc, char **argv) {
	Node node1, node2, node3, node4;

	node1.id = "A1";
	node1.purchased_item = "AXE";
	node1.cost = 50;
	node1.next = &node2;

	node2.id = "A2";
	node2.purchased_item = "SWORD";
	node2.cost = 25;
	node2.next = &node3;

	node3.id = "A3";
	node3.purchased_item = "BOW";
	node3.cost = 100;
	node3.next = &node4;

	node4.id = "A4";
	node4.purchased_item = "HAMMER";
	node4.cost = 200;
	node4.next = NULL;

	Node *node0 = make_node(&node1, "A0", "Rock", 0);
   	Node *node10 = make_node(node0, "A10", "Bean", 1000);	

	Node *n = node_lookup(node10, "A0");
	printf("Id: %s\nItem: %s\nCost: %f\n", n->id, n->purchased_item, n->cost);

	return 0;
}
