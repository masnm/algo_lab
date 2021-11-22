#include <stdio.h>

int a[20][20], q[20], visited[20];
int parent[20], distance[20];
int n, i, j, f = 0, r = -1;

void bfs ( int v, int dis, int par ) {
	printf ( "%d %d %d\n", v, dis, par );
		printf ( "%d - %d\n", q[f], f );
	parent[v] = par;
	distance[v] = dis;
	for ( i = 0 ; i < n ; i++ )
		if ( a[v][i] && !visited [ i ] )
			q [ ++r ] = i;
	if ( f <= r ) {
		visited [ q [ f ] ] = 1;
		bfs ( q [ f++ ], dis + 1, v );
	}
}

int main() {
	int v;
	printf("\nEnter the number of vertices: ");
	scanf("%d",&n);
	for ( i = 0 ; i < n ; i++ ) {
		q [ i ] = 0;
		visited [ i ] = 0;
	}
	printf("\nEnter graph data in matrix form:\n");
	for ( i = 0 ; i < n ; i++ )
		for ( j = 0 ; j < n ; j++ )
			scanf ( "%d", &a[i][j] );
	printf("\nEnter the starting vertex: ");
	scanf("%d",&v);
	visited[v] = 1;
	bfs(v, 0, -1);
	printf("\nThe node which are reachable are:\n");
	for ( i = 0 ; i < n ; i++ )
		if ( visited [ i ] != 0 )
			printf ( " %d\t", i );
	printf("\nThe node which are not reachable are:\n");
	for ( i = 0 ; i < n ; i++ )
		if ( visited [ i ]  == 0 )
			printf ( " %d\t", i );

	puts ( "" );
	for ( i = 0 ; i < n ; ++i ) {
		printf ( "%d %d %d %d\n", i, distance[i], parent[i], q[i] );
	}
	return 0;
}
