#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

int main ()
{
	for ( int i = 0 ; i < 10 ; ++i ) {
		for ( int j = 0 ; j < 10 ; ++j ) {
			if ( (i == 0 && j == 1) || (i == 1 && j == 0) ) printf("%d ",1);
			else if ( (i == 1 && j == 2) || (i == 2 && j == 1) ) printf("%d ",1);
			else if ( (i == 1 && j == 4) || (i == 4 && j == 1) ) printf("%d ",1);
			else if ( (i == 4 && j == 0) || (i == 0 && j == 4) ) printf("%d ",1);
			else if ( (i == 3 && j == 1) || (i == 1 && j == 3) ) printf("%d ",1);
			else if ( (i == 3 && j == 2) || (i == 2 && j == 3) ) printf("%d ",1);
			//else if ( (i == 4 && j == 9) || (i == 9 && j == 4) ) printf("%d ",1);
			//else if ( (i == 4 && j == 6) || (i == 6 && j == 4) ) printf("%d ",1);
			else if ( (i == 5 && j == 8) || (i == 8 && j == 5) ) printf("%d ",1);
			else if ( (i == 6 && j == 8) || (i == 8 && j == 6) ) printf("%d ",1);
			else if ( (i == 9 && j == 5) || (i == 5 && j == 9) ) printf("%d ",1);
			else if ( (i == 7 && j == 6) || (i == 6 && j == 7) ) printf("%d ",1);
			else printf("%d ",0);
		}
		puts("");
	}
	puts("");

	return 0;
}

