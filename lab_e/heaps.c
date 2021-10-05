#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct array {
	int array_size;
	int heap_size;
	int* data;
} array ;

void swap ( int* a, int* b )
{
	int t = *a;
	*a = *b;
	*b = t;
}

array create_input_array ()
{
	array a;
	printf ( "Enter the size of int Array : " );
	scanf ( "%d", &a.array_size );
	// virtual limit from ' 1 - 1000 '
	assert ( a.array_size > 0 && a.array_size < 1005 );
	a.data = (int*) malloc ( sizeof ( int ) * a.array_size );
	printf ( "Print %d integer numbers :\n", a.array_size );
	for ( int i = 0 ; i < a.array_size ; ++i )
		scanf ( "%d", &a.data[i] );
	a.heap_size = a.array_size - 1;
	return a;
}

void max_heapify ( array* A, int ind )
{
	int l = ind * 2 + 1;
	int r = ind * 2 + 2;
	int lar;
	if ( l < A->heap_size && A->data[l] > A->data[ind] )
		lar = l;
	else
		lar = ind;
	if ( r < A->heap_size && A->data[r] > A->data[lar] )
		lar = r;
	if ( lar != ind ) {
		swap ( &A->data[ind], &A->data[lar] );
		max_heapify ( A, lar );
	}
}

void build_max_heap ( array* A )
{
	for ( int i = A->array_size / 2 ; i > 0 ; --i ) {
		max_heapify ( A, i );
	}
}

void print_array ( array* A )
{
	printf ( "The array is : " );
	for ( int i = 0 ; i < A->array_size ; ++i ) {
		printf ( "%d ", A->data[i] );
	}
	puts ( "" );
}

void heap_sort ( array* A )
{
	build_max_heap ( A );
	for ( int i = A->array_size - 1 ; i > 0 ; --i ) {
		swap ( &A->data[0], &A->data[i] );
		if ( A->heap_size > 1 )
			-- A->heap_size;
		max_heapify ( A, 0 );
	}
}

int main ()
{
	array A = create_input_array ();
	heap_sort ( &A );
	print_array ( &A );
	free ( A.data );

	return 0;
}

