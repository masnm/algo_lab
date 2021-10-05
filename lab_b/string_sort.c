#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int limit;
char ar[105][25];

int min ( int a, int b ) { return ( a < b ? a : b ); }
int mabs ( int a, int b ) { int c = a - b; return ( c < 0 ? -c : c ); }

void swap ( const void* a, const void* b )
{
	char t = *(char*)a;
	*(char*)a = *(char*)b;
	*(char*)b = t;
}

int string_len ( const void* a )
{
	for ( int i = 0 ;  ; ++i ) {
		if ( *( (char*)a + i ) == '\0' )
			return i + 1;
		// cheaking for invalid string
		assert ( i < 100 );
	}
}

void str_swap ( const void* a, const void* b )
{
	int len_a = string_len ( (char*)a );
	int len_b = string_len ( (char*)b );
	for ( int i = 0 ; i < min ( len_a, len_b ) ; ++i ) {
		swap ( (char*)a + i, (char*)b + i );
	}
	if ( len_a > len_b ) {
		int mn = min ( len_a, len_b );
		int ab = mabs ( len_a, len_b );
		for ( int i = mn ; i < mn + ab ; ++i ) {
			*( (char*)b + i ) = *( (char*)a + i );
		}
		*( (char*)a + len_b ) = '\0';
		*( (char*)b + len_a ) = '\0';
	} else if ( len_a < len_b ) {
		int mn = min ( len_a, len_b );
		int ab = mabs ( len_a, len_b );
		for ( int i = mn ; i < mn + ab ; ++i ) {
			*( (char*)a + i ) = *( (char*)b + i );
		}
		*( (char*)a + len_b ) = '\0';
		*( (char*)b + len_a ) = '\0';
	}
}

int increase ( const void* a, const void* b )
{
	int len_a = string_len ( (char*)a );
	int len_b = string_len ( (char*)b );
	for ( int i = 0 ; i < min ( len_a, len_b ) ; ++i ) {
		if ( *( (char*)a + i ) > *( (char*)b + i ) ) {
			return 1;
		} else if ( *( (char*)a + i ) < *( (char*)b + i ) ) {
			return -1;
		}
	}
	if ( len_a != len_b ) return ( len_a > len_b ? 1 : -1 );
	return 0;
}

int decrease ( const void* a, const void* b )
{
	int len_a = string_len ( (char*)a );
	int len_b = string_len ( (char*)b );
	for ( int i = 0 ; i < min ( len_a, len_b ) ; ++i ) {
		if ( *( (char*)a + i ) > *( (char*)b + i ) ) {
			return -1;
		} else if ( *( (char*)a + i ) < *( (char*)b + i ) ) {
			return 1;
		}
	}
	if ( len_a != len_b ) return ( len_a > len_b ? 1 : -1 );
	return 0;
}

void buble_sort ( int (*comp) ( const void*, const void* ) )
{
	for ( int i = 0 ; i < limit ; ++i ) {
		bool swapped = false;
		for ( int j = 0 ; j < limit - i - 1 ; ++j ) {
			if ( comp ( &ar[j], &ar[j+1] ) > 0 ) {
				str_swap ( &ar[j], &ar[j+1] );
				swapped = true;
			}
		}
		if ( !swapped ) break;
	}
}

void input_array ( )
{
	printf ( "Enter size of the stirngs list : " );
	scanf ( "%d", &limit );
	printf ( "Enter %d strings : ", limit );
	for ( int i = 0 ; i < limit ; ++i ) {
		scanf ( "%s", ar[i] );
	}
	puts ( "" );
}

void print_array ( char* msg )
{
	printf ( "The %s sorted strings list is :\n", msg );
	for ( int i = 0 ; i < limit ; ++i ) {
		printf ( " %s", ar[i] );
	}
	puts("\n");
}

int main ()
{
	input_array ( );

	buble_sort ( increase );
	print_array ( "Increasingly" );

	buble_sort ( decrease );
	print_array ( "Decreasingly" );

	return 0;
}
