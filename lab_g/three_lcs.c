#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
	size_t size;
	char* data;
} string ;

string str_get ( int num )
{
	static char inp[1005];
	printf ( "Enter String %d : ", num );
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
	stop_here,
	layer_up_left_up,
	one_layer_up,
	this_layer_left,
	this_layer_up
} direction ;

typedef struct {
	int value;
	direction d;
} tuple ;

tuple max ( tuple a, tuple b, tuple c )
{
	tuple ret;
	if ( a.value >= b.value && a.value >= c.value ) {
		ret.value = a.value;
		ret.d = one_layer_up;
	} else if ( b.value >= a.value && b.value >= c.value ) {
		ret.value = b.value;
		ret.d = this_layer_up;
	} else {
		ret.value = c.value;
		ret.d = this_layer_left;
	}
	return ret;
}

string lcs ( string first, string second, string third )
{
	tuple dp[first.size][second.size][third.size];
	for ( int i = 0 ; i < first.size ; ++i ) {
		for ( int j = 0 ; j < second.size ; ++j ) {
			for ( int k = 0 ; k < third.size ; ++k ) {
				if ( i == 0 || j == 0 || k == 0 ) {
					dp[i][j][k].value = 0;
					dp[i][j][k].d = stop_here;
				} else if ( first.data[i-1] == second.data[j-1] &&
						first.data[i-1] == third.data[k-1] ) {
					dp[i][j][k].value = 1 + dp[i-1][j-1][k-1].value;
					dp[i][j][k].d = layer_up_left_up;
				} else {
					dp[i][j][k] = max ( dp[i-1][j][k], dp[i][j-1][k],
							dp[i][j][k-1] );
				}
			}
		}
	}
	char str[first.size+5];
	int index = 0, i = first.size-1, j = second.size-1, k = third.size-1;
	while ( true ) {
		direction d = dp[i][j][k].d;
		if ( d == stop_here ) break;
		if ( d == layer_up_left_up ) {
			str[index++] = first.data[i-1];
			--i; --j; --k;
		} else if ( d == this_layer_left ) --k;
		else if ( d == this_layer_up ) --j;
		else if ( d == one_layer_up ) --i;
	}
	string s = {
		.size = index+1,
		.data = (char*) malloc( sizeof(char)*(index+1) )
	};
	s.data[index] = '\0';
	for ( i = 0 ; i < index ; ++i )
		s.data[i] = str[index - i - 1];
	return s;
	printf ( "%s\n", s.data );
	free ( s.data );
}

int main ()
{
	string first, second, third;
	first = str_get( 1 );
	second = str_get( 2 );
	third = str_get( 3 );

	string ans = lcs(first, second, third );
	printf ( "Length of the LCS is : %ld\n", ans.size-1 );
	printf ( "The LCS is : %s\n", ans.data );

	str_destroy ( &ans );
	str_destroy ( &first );
	str_destroy ( &second );
	str_destroy ( &third );

	return 0;
}

