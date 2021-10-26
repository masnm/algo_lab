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
	arr[rt_s] = (int*) realloc ( arr[rt_s], sizeof(int) * (siz[rt_s]+siz[rt_e]) );
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
	scanf ( "%d", &n );
	tuple_array ta = {
		.size = n,
		.data = (tuple*) malloc ( sizeof(tuple) * n )
	};
	int s, e, c;
	for ( int i = 0 ; i < n ; ++i ) {
		scanf ( "%d%d%d", &s, &e, &c );
		ta.data[i].start = s;
		ta.data[i].end = e;
		ta.data[i].cost = c;
	}
	return ta;
}

int main ()
{
	tuple_array tp_arr = get_input ();
	qsort ( tp_arr.data, tp_arr.size, sizeof (tuple), comp );


	dsu_prepare ();

	int cost = 0;
	for ( int i = 0 ; i < tp_arr.size ; ++i ) {
		if ( dsu_add ( tp_arr.data[i].start, tp_arr.data[i].end ) ) {
			cost += tp_arr.data[i].cost;
			printf ( "%d %d %d\n", tp_arr.data[i].start, tp_arr.data[i].end, tp_arr.data[i].cost );
		}
	}
	printf ( "Cost : %d\n", cost );

	dsu_destroy ();

	for ( int i = 0 ; i < tp_arr.size ; ++i ) {
		printf ( "%d %d %d\n", tp_arr.data[i].start, tp_arr.data[i].end, tp_arr.data[i].cost );
	}

	free ( tp_arr.data );

	return 0;
}

