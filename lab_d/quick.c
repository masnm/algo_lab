#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int* arr;
	int size;
} st ;

void swap ( int* a, int* b )
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition ( int A[], int lb, int ub,
		bool (*coma) ( int, int ), bool (*comb) ( int, int) )
{
	int pivot = A[lb], start = lb, end = ub;
	while ( start < end ) {
		while ( start < ub && coma ( A[start], pivot ) )
			++start;
		while ( comb ( A[end], pivot ) )
			--end;
		if ( start < end )
			swap ( &A[start], &A[end] );
	}
	swap ( &A[lb], &A[end] );
	return end;
}

void quick_sort ( int A[], int lb, int ub,
		bool (*coma) ( int, int ), bool (*comb) ( int, int) )
{
	if ( lb < ub ) {
		int loc = partition ( A, lb, ub, coma, comb );
		quick_sort ( A, lb, loc - 1, coma, comb );
		quick_sort ( A, loc + 1, ub, coma, comb );
	}
}

bool les ( int a, int b ) { return a < b; }
bool les_equ ( int a, int b ) { return a <= b; }
bool gra ( int a, int b ) { return a > b; }
bool gra_equ ( int a, int b ) { return a >= b; }

st input_array ( )
{
	int* ar;
	int n;
	printf ( "Enter size of the int list : " );
	scanf ( "%d", &n );
	ar = (int*) malloc ( sizeof ( int ) * n );
	printf ( "Enter %d integers : ", n );
	for ( int i = 0 ; i < n ; ++i ) {
		scanf ( "%d", &ar[i] );
	}
	puts ( "" );
	return (st) { ar, n };
}

void print_array ( st array, char* msg )
{
	printf ( "The %s sorted integers list is :\n", msg );
	for ( int i = 0 ; i < array.size ; ++i ) {
		printf ( " %d", array.arr[i] );
	}
	puts("\n");
}

int main ()
{
	st inp = input_array ( );

	quick_sort ( inp.arr, 0, inp.size - 1 , les_equ, gra );
	print_array ( inp, "increasing" );

	quick_sort ( inp.arr, 0, inp.size - 1, gra_equ, les );
	print_array ( inp, "decreasing" );

	free ( inp.arr );


	return 0;
}
