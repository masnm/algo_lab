#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

const int INF = 1e5 + 5;
const int NIL = -1 * 1e5 + 5;

#define nax 130
int mp[nax], N;

typedef struct {
	int no_of_nodes;
	int **edges;
} graph ;

void destroy_graph ( graph* g );

graph* create_graph ( int node_count )
{
	graph* g = (graph*) malloc ( sizeof ( graph ) );
	if ( g == NULL ) return NULL;
	g -> no_of_nodes = node_count;
	g -> edges = calloc ( sizeof ( int* ), node_count );
	if ( g -> edges == NULL ) {
		destroy_graph ( g );
		return NULL;
	}
	for ( int i = 0 ; i < node_count ; ++i ) {
		g -> edges[i] = calloc ( sizeof ( int ), node_count );
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

bool add_edge ( graph* g, int start, int end, int coast )
{
	assert ( g != NULL );
	assert ( start < g -> no_of_nodes );
	assert ( end < g -> no_of_nodes );
	g -> edges [ start ] [ end ] = coast;
	return true;
}

bool have_edge ( graph* g, int start, int end )
{
	assert ( g != NULL );
	assert ( start < g -> no_of_nodes );
	assert ( end < g -> no_of_nodes );
	return g -> edges [ start ] [ end ] != 0;
}

int get_coast ( graph* g, int start, int end )
{
	assert ( g != NULL );
	assert ( start < g -> no_of_nodes );
	assert ( end < g -> no_of_nodes );
	return g -> edges [ start ] [ end ];
}

void print_prims_graph ( graph* g )
{
	printf ( "\nThe edges list ont the MST are in the form of\n" );
	printf ( "node - node -> coast\n" );
	printf ( "Edges {\n" );
	int sum = 0;
	for ( int i = 0 ; i < g -> no_of_nodes ; ++i ) {
		for ( int j = 0 ; j < g -> no_of_nodes ; ++j ) {
			if ( have_edge ( g, i, j ) ) {
				char ll, rr;
				for ( int ii = 0 ; ii < nax ; ++ii ) {
					if ( mp[ii] == i ) ll = ii;
					if ( mp[ii] == j ) rr = ii;
				}
				printf ( "%c - %c -> %d\n", ll, rr, g->edges[i][j] );
				sum += g->edges[i][j];
			}
		}
	}
	printf ( "}\n\n" );
	printf ( "The Total coast of the spanning tree is : %d", sum );
	puts ( "\n" );
}

graph* input_graph ()
{
	int nodes = -1, edges = -1;
	printf ( "Enter the number of node : " );
	scanf ( "%d", &nodes );
	printf ( "Enter the number of edges : " );
	scanf ( "%d", &edges );

	// virtual nodes & edge limits
	assert ( nodes > 0 && nodes < 3005 );
	assert ( edges > -1 && edges < 9000005 );

	printf ( "Enter the edges details in the form :\n" );
	printf ( "node - node - coast\n" );

	N = 0;
	for ( int i = 0 ; i < nax ; ++i ) mp[i] = -1;
	graph* g = create_graph ( nodes );
	if ( g != NULL ) {
		// undirected
		char start[3], end[3];
		int coast, ll, rr;
		for ( int i = 0 ; i < edges ; ++i ) {
			scanf ( "%s%s%d", start, end, &coast );
			if ( mp[(int)start[0]] == -1 ) {
				mp[(int)start[0]] = N++;
				ll = mp[(int)start[0]];
			} else ll = mp[(int)start[0]];
			if ( mp[(int)end[0]] == -1 ) {
				mp[(int)end[0]] = N++;
				rr = mp[(int)end[0]];
			} else rr = mp[(int)end[0]];
			add_edge ( g, ll, rr, coast );
			add_edge ( g, rr, ll, coast );
		}
	} else {
		exit ( 1 );
	}
	return g;
}

typedef struct st {
	int node_no;
	int parent;
	int key;
} st ;
typedef struct priority_queue {
	int size;
	st* data;
} priority_queue ;

priority_queue pq_create ()
{
	priority_queue pq = {
		.size = 0,
		.data = NULL
	};
	return pq;
}

void pq_insert ( priority_queue* pq, st u )
{
	int ins_idx = 0;
	for ( int i = 0 ; i < pq -> size ; ++i ) {
		if ( pq -> data[i].key > u.key )
			break;
		ins_idx = i;
	}
	++ pq -> size;
	pq -> data = (st*) realloc ( pq -> data, sizeof(st) * pq -> size );
	for ( int i = pq -> size - 1 ; i > ins_idx ; --i ) {
		pq -> data [i] = pq -> data [i - 1];
	}
	pq -> data [ ins_idx ] = u;
}

st pq_erase ( priority_queue* pq, int n_n )
{
	int nindx = -1;
	for ( int i = 0 ; i < pq -> size ; ++i ) {
		if ( pq -> data [i].node_no == n_n ) {
			nindx = i;
			break;
		}
	}
	if ( nindx != -1 ) {
		st s = pq -> data [nindx];
		for ( int i = nindx ; i < pq -> size - 1 ; ++i ) {
			pq -> data [i] = pq -> data [i + 1];
		}
		-- pq -> size;
		pq -> data = (st*) realloc ( pq -> data, sizeof(st) * pq -> size );
		return s;
	}
	st s = { .node_no = 0, .parent = NIL, .key = INF };
	return s;
}

void decrease_key ( priority_queue* pq, int n_n, int kval )
{
	st s = pq_erase ( pq, n_n );
	s.key = kval;
	pq_insert ( pq, s );
}

st extract_min ( priority_queue* pq )
{
	st s;
	int cmin = INF + INF, ind;
	for ( int i = 0 ; i < pq->size ; ++i ) {
		if ( pq->data[i].key < cmin ) {
			cmin = pq->data[i].key;
			s = pq->data[i];
			ind = i;
		}
	}
	for ( int i = ind ; i < pq -> size - 1 ; ++i ) {
		pq -> data[i] = pq -> data[i + 1];
	}
	-- pq -> size;
	pq -> data = (st*) realloc ( pq -> data, sizeof(st) * pq -> size );
	return s;
}

bool pq_empty ( priority_queue* pq )
{
	return pq->size == 0;
}

bool pq_exists ( priority_queue* pq, int n_n )
{
	for ( int i = 0 ; i < pq -> size ; ++i )
		if ( pq -> data [i].node_no == n_n )
			return true;
	return false;
}

int pq_get_key ( priority_queue* pq, int n_n )
{
	for ( int i = 0 ; i < pq -> size ; ++i )
		if ( pq -> data[i].node_no == n_n )
			return pq -> data[i].key;
	return -INF;
}

void pq_parent_update ( priority_queue* pq, int n_n, int prnt )
{
	for ( int i = 0 ; i < pq -> size ; ++i ) {
		if ( pq -> data[i].node_no == n_n ) {
			pq -> data[i].parent = prnt;
		}
	}
}

void pq_print ( priority_queue* pq )
{
	puts ( "Start" );
	for ( int i = 0 ; i < pq -> size ; ++i ) {
		printf ( "%d %d %d\n", pq->data[i].node_no, pq->data[i].key, pq->data[i].parent );
	}
	puts ( "" );
}

void pq_destroy ( priority_queue* pq )
{
	free  ( pq -> data );
}

graph* prims_mst ( graph* g, void* w, int r )
{
	priority_queue pq = pq_create ();
	for ( int i = 0 ; i < g -> no_of_nodes ; ++i ) {
		st u = {
			.node_no = i,
			.parent = NIL,
			.key = INF
		};
		pq_insert ( &pq, u );
	}
	graph* pri = create_graph ( g -> no_of_nodes );
	decrease_key ( &pq, r, 0 );
	while ( ! pq_empty ( &pq ) ) {
		st s = extract_min ( &pq );
		if ( s.parent != NIL )
			add_edge ( pri, s.parent, s.node_no, s.key );
		for ( int i = 0 ; i < g->no_of_nodes ; ++i ) {
			if ( pq_exists ( &pq, i ) && have_edge ( g, i, s.node_no )
				&& get_coast ( g, i, s.node_no ) < pq_get_key ( &pq, i ) ) {
				pq_parent_update ( &pq, i, s.node_no );
				decrease_key ( &pq, i, get_coast ( g, i, s.node_no ) );
			}
		}
	}
	return pri;
}

int main ()
{
	graph* g = input_graph ();

	graph* prim = prims_mst ( g, NULL, 0 );
	print_prims_graph ( prim );

	destroy_graph ( g );
	destroy_graph ( prim );

	return 0;
}

