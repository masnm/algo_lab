#include<stdio.h>
#include<assert.h>
#include<stdbool.h>
#include<stdlib.h>

int fib ( int n )
{
	if ( n == 0 || n == 1 ) return n;
	else if ( n > 1 ) return fib ( n - 2 ) + fib ( n - 1 );

	// making sure the program is executing properly
	// going to show runtime error if something bad happens
	assert ( false );
}

int main ()
{
	int n;
	printf ( "Enter until which term you want to see the series : " );
	scanf ( "%d", &n );

	// making sure the input is not negative or zero
	// going to show runtime error
	assert ( n > 0 );

	if ( n > 40 ) {
		printf ( "This algorithm is not efficient enough" );
		printf ( " to calculate more than 40 terms." );
		puts("\n");
		fflush ( stdout );

		// exiting the program with runtime error
		assert ( false );
	}

	printf ( "The fibonacci series upto %d term is :\n", n );
	for ( int i = 0 ; i < n ; ++i ) {
		printf ( "%d ", fib ( i ) );
	}
	puts("\n");

	return 0;
}
