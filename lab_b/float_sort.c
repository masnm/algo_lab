#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int limit;
float ar[1001];

bool increase ( const float a, const float b )
{
	return a > b;
}

bool decrease ( const float a, const float b )
{
	return a < b;
}

void insertion_sort ( bool (*comp) ( const float, const float ) )
{
	int hp; // hole position
	float vti; // value to insert
	for ( int i = 0 ; i < limit ; ++i ) {
		vti = ar[i];
		hp = i;
		while ( ( hp > 0 ) && ( comp ( ar[hp-1], vti ) == true ) ) {
			ar[hp] = ar[hp-1];
			hp = hp - 1;
		}
		ar[hp] = vti;
	}
}

void input_array ( )
{
	printf ( "Enter size of the floats list : " );
	scanf ( "%d", &limit );
	printf ( "Enter %d floats : ", limit );
	for ( int i = 0 ; i < limit ; ++i ) {
		scanf ( "%f", &ar[i] );
	}
	puts ( "" );
}

void print_array ( char* msg )
{
	printf ( "The %s sorted floats list is :\n", msg );
	for ( int i = 0 ; i < limit ; ++i ) {
		printf ( " %.2f", ar[i] );
	}
	puts("\n");
}

int main ()
{
	input_array ( );

	insertion_sort ( increase );
	print_array ( "Increasingly" );

	insertion_sort ( decrease );
	print_array ( "Decreasingly" );


	return 0;
}
