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

void bfs ( graph* g, int root )
{
	printf ( "BFS traversal : " );
	int qu[1001], qs = 0, qe = 0;
	bool v[1001] = { };
	v[root] = true;
	qu[qe++] = root;
	while ( qs != qe ) {
		int cp = qu[qs];
		printf ( "%d ", cp );
		++qs; if ( qs >= 1000 ) qs = 0;
		for ( int i = 0 ; i < g -> no_of_nodes ; ++i ) {
			if ( !v[i] && g -> edges [ cp ] [ i ] ) {
				v[i] = true;
				qu[qe++] = i;
				if ( qe >= 1000 ) qe = 0;
			}
		}
	}
	puts ( "" );
}

void dfs ( graph* g, int root )
{
	printf ( "DFS traversal : " );
	int st[1001], ss = 0, se = 0;
	bool v[1001] = { };
	// v[root] = true;
	st[se++] = root;
	while ( ss != se ) {
		int cp = st[--se];
		if ( v[cp] ) continue;
		v[cp] = true;
		printf ( "%d ", cp );
		for ( int i = 0 ; i < g -> no_of_nodes ; ++i ) {
			if ( !v[i] && g -> edges [ cp ] [ i ] ) {
				st[se++] = i;
			}
		}
	}
	puts ( "" );
}

int main ()
{

	graph* g = input_graph ();
	print_graph ( g );

	bfs ( g, 0 );
	dfs ( g, 0 );

	destroy_graph ( g );

	return 0;
}
