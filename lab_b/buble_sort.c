#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap ( int* a, int* b )
{
	int t = *a;
	*a = *b;
	*b = t;
}

int less ( const void* a, const void* b )
{
	return *((int*)a) - *((int*)b);
}

int more ( const void* a, const void* b )
{
	return *((int*)b) - *((int*)a);
}

void buble_sort ( int ar[], int n, int (*comp) ( const void*, const void* ) )
{
	for ( int i = 0 ; i < n ; ++i ) {
		bool swapped = false;
		for ( int j = 0 ; j < n - i - 1 ; ++j ) {
			// if ( ar[j] > ar[j+1] ) {
			if ( comp ( &ar[j], &ar[j+1] ) > 0 ) {
				swap ( &ar[j], &ar[j+1] );
				swapped = true;
			}
		}
		if ( !swapped ) break;
	}
}

void buble_sort_class ( int ar[], int n )
{
	for ( int i = 0 ; i < n ; ++i ) {
		for ( int j = 0 ; j < n - i - 1 ; ++j ) {
			if ( ar[j] > ar[j+1] ) {
				swap ( &ar[j], &ar[j+1] );
			}
		}
	}
}

void print_array ( int ar[], int n )
{
	printf ( "The sorted int list is : " );
	for ( int i = 0 ; i < n ; ++i ) {
		printf ( "%d ", ar[i] );
	}
	puts("");
}

int main ()
{
	int n, ar[1005];

	printf ( "Enter size of the int list : " );
	scanf ( "%d", &n );
	printf ( "Enter %d elements : ", n );
	for ( int i = 0 ; i < n ; ++i ) {
		scanf ( "%d", &ar[i] );
	}

	buble_sort ( ar, n, less );
	print_array ( ar, n );

	buble_sort ( ar, n, more );
	print_array ( ar, n );

	// buble_sort_class ( ar, n );
	qsort ( ar, n, sizeof(int), less );
	print_array ( ar, n );

	qsort ( ar, n, sizeof(int), more );
	print_array ( ar, n );

	puts ( "\n" );


	return 0;
}
