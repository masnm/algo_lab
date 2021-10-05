#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

char c[20];

typedef struct node node;

struct node {
	int me;
	int bal;
	node* left;
	node* right;
};

node* array_to_heap ( int ar[], int me, int len )
{
	if ( me >= len ) {
		return NULL;
	}
	node* tn = (node*) malloc ( sizeof ( node ) );
	tn -> me = ar[me];
	tn -> left = NULL;
	tn -> right = array_to_heap ( ar, me + 1, len );
	// tn -> left = array_to_heap ( ar, 2 * me + 1, len );
	// tn -> right = array_to_heap ( ar, 2 * me + 2, len );
	return tn;
}

int init_balance ( node* root )
{
	if ( root == NULL ) return 0;
	int lbal = init_balance ( root -> left );
	int rbal = init_balance ( root -> right );
	root -> bal = ( lbal > rbal ? lbal - rbal : rbal - lbal );
	return 1 + ( lbal > rbal ? lbal : rbal );
}

void print_heap ( node* root )
{
	if ( root == NULL ) return;
	printf ( "%d %d\n", root -> me, root -> bal );
	print_heap ( root -> left );
	print_heap ( root -> right );
}

void cleanup_memory ( node* root )
{
	if ( root == NULL ) return;
	cleanup_memory ( root -> left );
	cleanup_memory ( root -> right );
	free ( root );
}

int main ()
{
	int len = 10;
	int ar[] = { 0, 1, 9, 2, 8, 3, 7, 4, 6, 5 };

	node* root = array_to_heap ( ar, 0, len );

	init_balance ( root );
	print_heap ( root );

	cleanup_memory ( root );

	return 0;
}
