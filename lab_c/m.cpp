#include "bits/stdc++.h"
using namespace std;

using ll = long long int;

int ar[] = { 9, 3, 2, 5, 1, 6, 3, 8, 1, 0 };

void interchange ( int a[], int i, int j )
{
	int p = a[i];
	a[i] = a[j];
	a[j] = p;
}

int partition ( int a[], int m, int p )
{
	int v = a[m], i = m, j = p;
	do {
		do {
			i = i + 1;
		} while ( i < p && a[i] >= v );
		do {
			j = j - 1;
		} while ( j > 0 && a[j] <= v );
		if ( i < j ) interchange ( a, i, j );
	} while ( i <= j );
	a[m] = a[j];
	a[j] = v;
	return j;
}

void qs ( int p, int q )
{
	if ( p < q ) {
		int j = partition ( ar, p, q+1 );
		qs ( p, j-1 );
		qs ( j+1, q );
	}
}

int main ()
{
	int n = 5;
	qs ( 0, n );
	for ( int i = 0 ; i < n ; ++i ) printf ( "%d ", ar[i] );
	puts ("");

	return 0;
}
