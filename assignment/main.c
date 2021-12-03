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

bool is_node ( graph* g, int me )
{
	assert ( g != NULL );
	assert ( me < g -> no_of_nodes );
	for ( int i = 0 ; i < g->no_of_nodes ; ++i ) {
		if ( have_edge ( g, me, i ) || have_edge ( g, i, me ) )
			return true;
	}
	return false;
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
	printf ( "Enter %d edges in form [Start_node End_node] each line.\n", edges );
	if ( g != NULL ) {
		// undirected
		int start = -1, end = -1;
		for ( int i = 0 ; i < edges ; ++i ) {
			scanf ( "%d%d", &start, &end );
			add_edge ( g, start, end );
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

typedef struct queue {
	int size;
	int* data;
} queue ;

queue queue_create ()
{
	queue q = {
		.size = 0,
		.data = NULL
	};
	return q;
}

void queue_enqueue ( queue* q, int val )
{
	++(*q).size;
	(*q).data = (int*) realloc ( q->data, (q->size)*sizeof(int) );
	(*q).data [q->size - 1] = val;
}

int queue_front ( queue* q )
{
	assert ( q->size > 0 );
	return q->data[0];
}

void queue_dequeue ( queue* q )
{
	assert ( q->size > 0 );
	for ( int i = 0 ; i < q->size - 1 ; ++i )
		(*q).data [i] = (*q).data [ i + 1 ];
	-- (*q).size;
	(*q).data = (int*) realloc ( q->data, (q->size)*sizeof(int) );
}

bool queue_empty ( queue* q )
{
	return q->size == 0;
}

void queue_destroy ( queue* q )
{
	(*q).size = 0;
	free ( (*q).data );
	(*q).data = NULL;
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

int statement_count;
void reset_count () { statement_count = 0; }
void incc () { ++statement_count; }
int get_count () { return statement_count; }

tuple_array bfs ( graph* g, int root )
{
	queue que_int = queue_create (); incc();
	tuple_array tpar = tuple_array_create ( g->no_of_nodes ); incc();
	tpar.data [ root ] . visited = true; incc();
	tpar.data [ root ] . parent = -1; incc();
	tpar.data [ root ] . distance = 0; incc();
	queue_enqueue ( &que_int, root ); incc();
	while ( !queue_empty ( &que_int ) ) {
		incc (); // for the while loop
		int cp = queue_front ( &que_int ); incc();
		queue_dequeue ( &que_int ); incc();
		for ( int i = 0 ; i < g -> no_of_nodes ; ++i, incc() ) {
			incc(); // for the next if
			if ( !tpar.data[i].visited && g -> edges [ cp ] [ i ] ) {
				tpar.data[i].visited = true; incc();
				tpar.data[i].parent = cp; incc();
				tpar.data[i].distance = tpar.data[cp].distance + 1; incc();
				queue_enqueue ( &que_int, i ); incc();
			}
		}
	}
	queue_destroy ( &que_int ); incc();
	return tpar;
}

tuple_array dfs ( graph* g, int root )
{
	stack stk_int = stack_create (); incc();
	tuple_array tpar = tuple_array_create ( g->no_of_nodes ); incc();
	tpar.data [ root ] . parent = -1; incc();
	tpar.data [ root ] . distance = 0; incc();
	stack_push ( &stk_int, root ); incc();
	while ( !stack_empty ( &stk_int ) ) {
		incc (); // for the while loop
		int cp = stack_top ( &stk_int ); incc();
		stack_pop ( &stk_int ); incc();
		incc(); // for the next if
		if ( tpar.data[cp].visited == true ) continue;
		tpar.data[cp].visited = true; incc();
		for ( int i = 0 ; i < g -> no_of_nodes ; ++i ) {
			incc(); // for the next if
			if ( !tpar.data[i].visited && g -> edges [ cp ] [ i ] ) {
				tpar.data[i].parent = cp; incc();
				tpar.data[i].distance = tpar.data[cp].distance + 1; incc();
				stack_push ( &stk_int, i ); incc();
			}
		}
	}
	stack_destroy ( &stk_int ); incc();
	return tpar;
}

void dfs_recur ( graph* g, tuple_array tpar, int me, int distance )
{
	for ( int i = 0 ; i < g -> no_of_nodes ; ++i, incc() ) {
		incc(); // for the next if
		if ( !tpar.data[i].visited && g->edges[me][i] ) {
			tpar.data[i].visited = true; incc();
			tpar.data[i].parent = me; incc();
			tpar.data[i].distance = distance; incc();
			dfs_recur ( g, tpar, i, distance + 1 ); incc();
		}
	}
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
	if ( ar[ind-1] == root ) {
		printf ( "Distance from %d to %d is : %d. ", root, target, bfar.data[target].distance );
		printf ( "Path is : " );
		for ( int i = ind - 1 ; i > -1 ; --i ) {
			printf ( " %d ", ar[i] );
		}
		puts ( "" );
	}
	free ( ar );
}

void bfs_and_print_path ( graph* g, int root )
{
	reset_count ();
	tuple_array bfar = bfs ( g, root );
	printf ( "Here is the finding using BFS algorithm.\n" );
	printf ( "The reachable nodes form the source are :\n" );
	for ( int i = 0 ; i < bfar.size ; ++i ) {
		if ( bfar.data[i].distance != -1 )
			printf ( " %d", i );
	}
	printf ( "\n\nBFS executed %d instructions.\n\n", get_count() );
	printf ( "Paths for the reachable nodes are\n" );
	for ( int i = 0 ; i < bfar.size ; ++i ) {
		if ( is_node ( g, i ) )
			print_path ( bfar, root, i );
	}
	printf ( "\n" );
	tuple_array_destroy ( &bfar );
}

void dfs_and_print_path ( graph* g, int root )
{
	reset_count ();
	tuple_array bfar = dfs ( g, root );
	printf ( "Here is the finding using DFS algorithm.\n" );
	printf ( "The reachable nodes form the source are :\n" );
	for ( int i = 0 ; i < bfar.size ; ++i ) {
		if ( bfar.data[i].distance != -1 )
			printf ( " %d", i );
	}
	printf ( "\n\nDFS executed %d instructions.\n\n", get_count() );
	printf ( "Paths for the reachable nodes are\n" );
	for ( int i = 0 ; i < bfar.size ; ++i ) {
		if ( is_node ( g, i ) )
			print_path ( bfar, root, i );
	}
	printf ( "\n" );
	tuple_array_destroy ( &bfar );
}

void recur_dfs_and_print_path ( graph* g, int root )
{
	reset_count ();
	tuple_array tpar = tuple_array_create ( g->no_of_nodes ); incc();
	tpar.data [ root ] . parent = -1; incc();
	tpar.data [ root ] . distance = 0; incc();
	tpar.data [ root ] . visited = true; incc();
	dfs_recur ( g, tpar, root, 1 ); incc();
	printf ( "Here is the finding using Recursive DFS algorithm.\n" );
	printf ( "The reachable nodes form the source are :\n" );
	for ( int i = 0 ; i < tpar.size ; ++i ) {
		if ( tpar.data[i].distance != -1 )
			printf ( " %d", i );
	}
	printf ( "\n\nRecursive DFS executed %d instructions.\n\n", get_count() );
	printf ( "Paths for the reachable nodes are\n" );
	for ( int i = 0 ; i < tpar.size ; ++i ) {
		if ( is_node ( g, i ) )
			print_path ( tpar, root, i );
	}
	printf ( "\n" );
	tuple_array_destroy ( &tpar );
}

int main ()
{
	graph* g = input_graph ();
//	print_graph ( g );

	int root;
	printf ( "Enter the Starting Node : " );
	scanf ( "%d", &root );

	bfs_and_print_path ( g, root );
	dfs_and_print_path ( g, root );
	recur_dfs_and_print_path ( g, root );

	destroy_graph ( g );

	return 0;
}
