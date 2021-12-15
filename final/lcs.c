#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
	size_t size;
	char* data;
} string ;

string str_get ( char* name )
{
	static char inp[1005];
	printf ( "Enter String %s : ", name );
	scanf ( "%s", inp );
	int len = 1 + strlen( inp );
	string s = {
		.size = len,
		.data = (char*) malloc( sizeof(char) * len )
	};
	for ( int i = 0 ; i < len ; ++i )
		s.data[i] = inp[i];
	return s;
}

void str_destroy ( string* s )
{
	s->size = 0;
	free ( s->data );
	s->data = NULL;
}

typedef enum {
	go_up,
	go_left,
	go_up_left,
	stop_here
} direction ;

typedef struct {
	int value;
	direction dir;
} tuple ;

tuple max ( tuple a, tuple b )
{
	tuple ret;
	if ( a.value >= b.value ) {
		ret.value = a.value;
		ret.dir = go_left;
	} else {
		ret.value = b.value;
		ret.dir = go_up;
	}
	return ret;
}

string lcs ( string first, string second )
{
	tuple dp[first.size][second.size];
	for ( int i = 0 ; i < first.size ; i++ ) {
		for ( int j = 0 ; j < second.size ; j++ ) {
			if ( i == 0 || j == 0 ) {
				dp[i][j].value = 0;
				dp[i][j].dir = stop_here;
			} else if ( first.data[i - 1] == second.data[j - 1] ) {
				dp[i][j].value = 1 + dp[i-1][j-1].value;
				dp[i][j].dir = go_up_left;
			} else {
				dp[i][j] = max ( dp[i-1][j], dp[i][j-1] );
			}
		}
	}
	char str[first.size+5];
	int index = 0, i = first.size-1, j = second.size-1;
	while ( true ) {
		direction d = dp[i][j].dir;
		if ( d == stop_here ) break;
		if ( d == go_up_left ) {
			str[index++] = first.data[i-1];
			--i; --j;
		} else if ( d == go_up ) --j;
		else if ( d == go_left ) --i;
	}
	string s = {
		.size = index+1,
		.data = (char*) malloc( sizeof(char)*(index+1) )
	};
	s.data[index] = '\0';
	for ( i = 0 ; i < index ; ++i )
		s.data[i] = str[index - i - 1];
	return s;
}

void string_print ( string s, char* name )
{
	printf ( "String %s is [ %zu, %s ]\n", name, s.size-1, s.data );
}

int main ()
{
	string STR1, STR2, STR3, STR4;
	STR1 = str_get ( "STR1" );
	STR2 = str_get ( "STR2" );
	STR3 = str_get ( "STR3" );
	STR4 = str_get ( "STR4" );

	string L1 = lcs ( STR1, STR2 );
	string L2 = lcs ( STR3, STR4 );

	puts( "\n" );
	string_print ( L1, "L1" );
	string_print ( L2, "L2" );

	if ( L1.size > L2.size ) {
		printf ( "\nLargest String is : L1\n" );
		string_print ( L1, "L1" );
	} else {
		printf ( "\nLargest String is : L2\n" );
		string_print ( L2, "L2" );
	}


	str_destroy ( &STR1 );
	str_destroy ( &STR2 );
	str_destroy ( &STR3 );
	str_destroy ( &STR4 );
	str_destroy ( &L1 );
	str_destroy ( &L2 );

	return 0;
}
