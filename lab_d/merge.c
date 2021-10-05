#include <stdio.h>
#include <stdbool.h>

const int nax = 100;

void merge ( int A[], int lb, int mid, int ub, bool (*comp) ( int, int ) )
{
	static int B[100];
	int i = lb, j = mid + 1, k = lb;
	while ( i <= mid && j <= ub ) {
		if ( comp ( A[i], A[j] ) ) {
			B[k] = A[i];
			++i;
		} else {
			B[k] = A[j];
			++j;
		}
		++k;
	}
	while ( i <= mid ) {
		B[k] = A[i];
		++i;
		++k;
	}
	while ( j <= ub ) {
		B[k] = A[j];
		++j;
		++k;
	}
	for ( int ii = lb ; ii <= ub ; ++ii )
		A[ii] = B[ii];
}

void merge_sort ( int ar[], int lb, int ub, bool (*comp) ( int, int ) )
{
	if ( lb < ub ) {
		int mid = ( lb + ub ) / 2; // int division
		merge_sort ( ar, lb, mid, comp );
		merge_sort ( ar, mid + 1, ub, comp );
		merge ( ar, lb, mid, ub, comp );
	}
}

bool inc ( int a, int b ) { return a <= b; }
bool dec ( int a, int b ) { return a >= b; }

int main ()
{
	int ar[] = { 1, 9, 8, 2, 5, 3, 7, 0, 5 };
	merge_sort ( ar, 0, 8, inc );
	for ( int i = 0 ; i < 8 ; ++i ) {
		printf ( "%d ", ar[i] );
	}
	puts("\n");


	return 0;
}
