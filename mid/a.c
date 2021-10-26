#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

long A ( int m, int n )
{
	if ( m == 0 ) {
		return n + 1;
	} else if ( m > 0 && n == 0 ) {
		return A ( m - 1, 1 );
	} else if ( m > 0 && n > 0 ) {
		return A ( m - 1, A ( m, n - 1 ) );
	}

	// making sure not reaching the end
	// of non void retrning function
	assert(false);
}

int main ()
{
	printf ( "Enter the value of m and n : " );
	int m, n;
	scanf ( "%d%d", &m, &n );

	long ans = A ( m, n );
	printf ( "\nA ( %d, %d ) = %ld\n", m, n, ans );

	puts("");

	return 0;
}

