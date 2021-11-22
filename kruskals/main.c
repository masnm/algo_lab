#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct tuple {
	int start;
	int end;
	int cost;
} tuple ;

typedef struct tuple_array {
	int size;
	tuple* data;
} tuple_array ;

int comp ( const void* a, const void* b )
{
	return (*(tuple*)a).cost - (*(tuple*)b).cost;
}

#define nax 105
int siz[nax];
int root[nax];
int* arr[nax];

void dsu_prepare ()
{
	for ( int i = 0 ; i < nax ; ++i ) {
		root[i] = i;
		siz[i] = 1;
		free ( arr[i] );
		arr[i] = (int*) malloc ( sizeof(int) * siz[i] );
		arr[i][0] = i;
	}
}

void swap ( int* a, int* b )
{
	int t = *a;
	*a = *b;
	*b = t;
}

bool dsu_add ( int s, int e )
{
	assert ( s < nax && e < nax );
	if ( root[s] == root[e] )
		return false;
	int rt_s = root[s], rt_e = root[e];
	if ( siz[rt_e] < siz[rt_s] )
		swap ( &rt_s, &rt_e );
	arr[rt_s] = (int*) realloc ( arr[rt_s],
			sizeof(int) * (siz[rt_s]+siz[rt_e]) );
	for ( int i = 0 ; i < siz[rt_e] ; ++i ) {
		int node = arr[rt_e][i];
		root[node] = rt_s;
		arr[rt_s][siz[rt_s]+i] = node;
	}
	siz[rt_s] += siz[rt_e];
	siz[rt_e] = 0;
	free ( arr[rt_e] );
	arr[rt_e] = NULL;
	return true;
}

void dsu_destroy ()
{
	for ( int i = 0 ; i < nax ; ++i ) {
		root[i] = i;
		siz[i] = 0;
		if ( arr[i] != NULL )
			free ( arr[i] );
	}
}

tuple_array get_input ()
{
	int n;
	printf ( "Enter the number of Edges : " );
	scanf ( "%d", &n );
	tuple_array ta = {
		.size = n,
		.data = (tuple*) malloc ( sizeof(tuple) * n )
	};
	printf ( "Enter %d edges in the form,\n", n );
	printf ( "Start_Node End_node Cost\n" );
	int s, e, c;
	for ( int i = 0 ; i < n ; ++i ) {
		scanf ( "%d%d%d", &s, &e, &c );
		ta.data[i].start = s;
		ta.data[i].end = e;
		ta.data[i].cost = c;
	}
	return ta;
}

void add_element ( tuple_array *span, tuple tpl )
{
	++(*span).size;
	(*span).data = (tuple*) realloc
		( (*span).data, sizeof(tuple) * (*span).size );
	(*span).data[(*span).size-1].start = tpl.start;
	(*span).data[(*span).size-1].end = tpl.end;
	(*span).data[(*span).size-1].cost = tpl.cost;
}

tuple_array kruskals ( tuple_array edge_list )
{
	qsort ( edge_list.data, edge_list.size, sizeof (tuple), comp );

	dsu_prepare ();

	tuple_array span_arr = {
		.size = 0,
		.data = NULL
	};

	for ( int i = 0 ; i < edge_list.size ; ++i ) {
		if ( dsu_add ( edge_list.data[i].start,
				edge_list.data[i].end ) ) {
			add_element ( &span_arr, edge_list.data[i] );
		}
	}

	dsu_destroy ();

	return span_arr;
}

int main ()
{
	tuple_array tp_arr = get_input ();

	tuple_array span_arr = kruskals ( tp_arr );

	printf ( "\nThe Edges in the Minimum Spanning Tree are\n" );
	printf ( "Start_Node End_node Cost\n" );
	int cost = 0;
	for ( int i = 0 ; i < span_arr.size ; ++i ) {
		printf ( "%d  %d  %d\n",
				span_arr.data[i].start,
				span_arr.data[i].end,
				span_arr.data[i].cost
			);
		cost += span_arr.data[i].cost;
	}
	printf ( "Cost of the tree is : %d \n", cost );

	free ( tp_arr.data );
	free ( span_arr.data );

	return 0;
}
