#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

// mapping between Character to int
int map[128] = {};
char rmap[128] = {};

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

	printf ( "Enter %d edges in form\n", edges );
	printf ( "<starting node>  <ending node>\n" );

	graph* g = create_graph ( nodes );
	if ( g != NULL ) {
		char start[5], end[5];
		for ( int i = 0 ; i < edges ; ++i ) {
			scanf ( "%s%s", start, end );
			add_edge ( g, map[(int)start[0]], map[(int)end[0]] );
		}
	} else {
		exit ( 1 );
	}
	return g;
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

tuple_array bfs ( graph* g, int root )
{
	queue que_int = queue_create ();
	tuple_array tpar = tuple_array_create ( g->no_of_nodes );
	tpar.data [ root ] . visited = true;
	tpar.data [ root ] . parent = -1;
	tpar.data [ root ] . distance = 0;
	queue_enqueue ( &que_int, root );
	while ( !queue_empty ( &que_int ) ) {
		int cp = queue_front ( &que_int );
		queue_dequeue ( &que_int );
		for ( int i = 0 ; i < g -> no_of_nodes ; ++i ) {
			if ( !tpar.data[i].visited && g -> edges [ cp ] [ i ] ) {
				tpar.data[i].visited = true;
				tpar.data[i].parent = cp;
				tpar.data[i].distance = tpar.data[cp].distance + 1;
				queue_enqueue ( &que_int, i );
			}
		}
	}
	queue_destroy ( &que_int );
	return tpar;
}

void print_reachable_node ( tuple_array bfar )
{
	printf ( "The reachable nodes are : " );
	for ( int i = 0 ; i < bfar.size ; ++i )
		if ( bfar.data[i].distance != -1 )
			printf ( "%c ", rmap[i] );
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
		printf ( "Can't reach %c from %c.", rmap[target], rmap[root] );
		puts ( "" );
	} else {
		printf ( "Distance from %c to %c is : %d. ",
				rmap[root], rmap[target], bfar.data[target].distance );
		printf ( "Path is : " );
		for ( int i = ind - 1 ; i > -1 ; --i ) {
			printf ( " %c ", rmap[ar[i]] );
		}
		puts ( "" );
	}
	free ( ar );
}

int main ()
{
	int msi = 0;
	char msc = 'A';
	for ( char s = msc ; s <= 'Z' ; ++s ) {
		map[(int)s] = msi++;
		rmap[msi-1] = s;
	}

	graph* g = input_graph ();
//	print_graph ( g );

	char rs[5];
	int root;
	printf ( "Enter the Starting Node : " );
	scanf ( "%s", rs );
	root = map[(int)rs[0]];

	tuple_array bfar = bfs ( g, root );

	puts ( "\n" );
	print_reachable_node ( bfar );
	for ( int i = 0 ; i < bfar.size ; ++i ) {
		print_path ( bfar, root, i );
	}

	tuple_array_destroy ( &bfar );
	destroy_graph ( g );

	return 0;
}
