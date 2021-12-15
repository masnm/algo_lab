#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct {
	int no_of_nodes;
	bool **edges;
} graph ;

void destroy_graph ( graph* g );

graph* create_graph ( int node_count )
{
	graph* g = (graph*) malloc ( sizeof ( graph ) );
	if ( g == NULL ) return NULL;
	g -> no_of_nodes = node_count;
	g -> edges = calloc ( sizeof ( bool* ), node_count );
	if ( g -> edges == NULL ) {
		destroy_graph ( g );
		return NULL;
	}
	for ( int i = 0 ; i < node_count ; ++i ) {
		g -> edges[i] = calloc ( sizeof ( bool ), node_count );
		if ( g -> edges[i] == NULL ) {
			destroy_graph ( g );
			return NULL;
		}
	}
	return g;
}

void destroy_graph ( graph* g )
{
	for ( int i = 0 ; i < g -> no_of_nodes ; ++i ) {
		if ( g -> edges[i] != NULL ) {
			free ( g -> edges[i] );
		}
	}
	if ( g -> edges != NULL ) {
		free ( g -> edges );
	}
	if ( g != NULL ) {
		free ( g );
	}
}
bool add_edge ( graph* g, int start, int end )
{
	assert ( g != NULL );
	assert ( start < g -> no_of_nodes );
	assert ( end < g -> no_of_nodes );
	if ( g -> edges [ start ] [ end ] == true ) {
		return false;
	}
	return g -> edges [ start ] [ end ] = true;
}

bool have_edge ( graph* g, int start, int end )
{
	assert ( g != NULL );
	assert ( start < g -> no_of_nodes );
	assert ( end < g -> no_of_nodes );
	return g -> edges [ start ] [ end ];
}

void print_graph ( graph* g )
{
	printf ( "Edges {\n" );
	for ( int i = 0 ; i < g -> no_of_nodes ; ++i ) {
		for ( int j = 0 ; j < g -> no_of_nodes ; ++j ) {
			if ( have_edge ( g, i, j ) ) {
				printf ( "%d -> %d\n", i, j );
			}
		}
	}
	printf ( "}\n" );
}

graph* input_graph ()
{
	int nodes = -1, edges = -1;
	printf ( "Enter the number of node : " );
	scanf ( "%d", &nodes );
	printf ( "Enter the number of edges : " );
	scanf ( "%d", &edges );

	assert ( nodes > 0 && nodes < 3005 );
	assert ( edges > -1 && edges < 9000005 );

	graph* g = create_graph ( nodes );
	if ( g != NULL ) {
		// undirected
		int start = -1, end = -1;
		for ( int i = 0 ; i < edges ; ++i ) {
			scanf ( "%d%d", &start, &end );
			add_edge ( g, start, end );
			add_edge ( g, end, start );
		}
	} else {
		exit ( 1 );
	}
	return g;
}

typedef struct stack {
	int size;
	int* data;
} stack ;

stack stack_create ()
{
	stack s = {
		.size = 0,
		.data = NULL
	};
	return s;
}

void stack_push ( stack* st, int val )
{
	++ st->size;
	st->data = (int*) realloc ( st->data, sizeof(stack) * st->size );
	st->data [ st->size - 1 ] = val;
}

void stack_pop ( stack* st )
{
	assert ( st->size > 0 );
	-- st->size;
	st->data = (int*) realloc ( st->data, sizeof(stack) * st->size );
}

int stack_top ( stack* st )
{
	assert ( st->size > 0 );
	return st->data [ st->size - 1 ];
}

bool stack_empty ( stack* st )
{
	return st->size == 0;
}

void stack_destroy ( stack* st )
{
	st->size = 0;
	free ( st->data );
	st->data = NULL;
}

typedef struct tuple {
	bool visited;
	int parent;
	int distance;
} tuple ;

typedef struct tuple_array {
	int size;
	tuple* data;
} tuple_array ;

tuple_array tuple_array_create ( int n )
{
	tuple_array tpar = {
		.size = n,
		.data = (tuple*) malloc ( sizeof(tuple) * n )
	};
	for ( int i = 0 ; i < n ; ++i ) {
		tpar.data [ i ] . visited = false;
		tpar.data [ i ] . parent = -1;
		tpar.data [ i ] . distance = -1;
	}
	return tpar;
}

void tuple_array_destroy ( tuple_array* tp )
{
	free ( tp->data );
	tp -> size = 0;
	tp -> data = NULL;
}

tuple_array dfs ( graph* g, int root )
{
	stack stk_int = stack_create ();
	tuple_array tpar = tuple_array_create ( g->no_of_nodes );
	tpar.data [ root ] . parent = -1;
	tpar.data [ root ] . distance = 0;
	stack_push ( &stk_int, root );
	while ( !stack_empty ( &stk_int ) ) {
		int cp = stack_top ( &stk_int );
		stack_pop ( &stk_int );
		if ( tpar.data[cp].visited == true ) continue;
		tpar.data[cp].visited = true;
		for ( int i = 0 ; i < g -> no_of_nodes ; ++i ) {
			if ( !tpar.data[i].visited && g -> edges [ cp ] [ i ] ) {
				tpar.data[i].parent = cp;
				tpar.data[i].distance = tpar.data[cp].distance + 1;
				stack_push ( &stk_int, i );
			}
		}
	}
	stack_destroy ( &stk_int );
	return tpar;
}

void print_reachable_node ( tuple_array bfar )
{
	printf ( "The reachable nodes are : " );
	for ( int i = 0 ; i < bfar.size ; ++i )
		if ( bfar.data[i].distance != -1 )
			printf ( "%d ", i );
	puts ( "\n" );
}

void print_path ( tuple_array bfar, int root, int target )
{
	int* ar = (int*) malloc ( sizeof(int) * bfar.size );
	for ( int i = 0 ; i < bfar.size ; ++i ) ar[i] = -1;
	int cr = target, ind = 0;
	ar[ind++] = target;
	while ( bfar.data [cr] . parent != -1 ) {
		ar [ ind++ ] = bfar.data [cr] . parent;
		cr = bfar.data [cr] . parent;
	}
	if ( ar[ind-1] != 0 ) {
		printf ( "Can't reach %d from %d.", target, root );
		puts ( "" );
	} else {
		printf ( "Distance from %d to %d is : %d. ",
				root, target, bfar.data[target].distance );
		printf ( "Path is : " );
		for ( int i = ind - 1 ; i > -1 ; --i ) {
			printf ( " %d ", ar[i] );
		}
		puts ( "" );
	}
	free ( ar );
}

int main ()
{
	graph* g = input_graph ();
//	print_graph ( g );

	int root;
	printf ( "Enter the Starting Node : " );
	scanf ( "%d", &root );

	tuple_array bfar = dfs ( g, root );

	puts ( "\n" );
	print_reachable_node ( bfar );
	for ( int i = 0 ; i < bfar.size ; ++i ) {
		print_path ( bfar, root, i );
	}

	tuple_array_destroy ( &bfar );
	destroy_graph ( g );

	return 0;
}
