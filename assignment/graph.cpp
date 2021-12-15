#include<bits/stdc++.h>
using namespace std;

const int nax = 1e5 + 5;
const int inf = 1e9 + 5;

int n, e, l, r, root, ins, cp;
vector<int> par ( nax ), dis ( nax ), g [ nax ], pp;
vector<bool> v ( nax ), in ( nax );

void reset ()
{
	for ( int i = 0 ; i < nax ; ++i )
		par [i] = -inf;
	for ( int i = 0 ; i < nax ; ++i )
		dis [i] = inf;
	for ( int i = 0 ; i < nax ; ++i )
		v [i] = in [i] = false;
	for ( int i = 0 ; i < nax ; ++i )
		g [i].clear ();
}

void bfs ()
{
	ins = 0;
	v[root] = true; ++ins;
	par[root] = root; ++ins;
	dis[root] = 0; ++ins;
	queue<int> q; ++ins;
	q.push ( root ); ++ins;
	while ( !q.empty() && ++ins ) {
		cp = q.front(); ++ins;
		q.pop(); ++ins;
		for ( int x : g[cp] ) {
			++ins;
			if ( !v[x] && ++ins ) {
				v[x] = true; ++ins;
				q.push ( x ); ++ins;
				par[x] = cp; ++ins;
				dis[x] = dis[cp] + 1; ++ins;
			}
		}
	}
	cout << "Output for BFS." << endl;
	cout << "Reachable nodes are : ";
	for ( int i = 0 ; i < nax ; ++i ) {
		if ( in[i] && (dis[i] != inf ) ) {
			cout << i << " ";
		}
	}
	cout << endl;
	cout << "Instructions : " << ins << endl;
	cout << "Paths are:" << endl;
	for ( int i = 0 ; i < nax ; ++i ) {
		if ( in[i] && (dis[i] != inf ) ) {
			cout << "Path from "<<root<<" to " <<i<< " is : ";
			int bas = i;
			pp.clear();
			while ( par[bas] != bas ) {
				pp.push_back(bas);
				bas = par[bas];
			}
			pp.push_back(root);
			reverse ( pp.begin(), pp.end() );
			for ( int xx : pp ) cout << xx << " ";
			cout << endl;
		}
	}
	cout << endl;
}

void dfs ()
{
	for ( int i = 0 ; i < nax ; ++i )
		par [i] = -inf;
	for ( int i = 0 ; i < nax ; ++i )
		dis [i] = inf;
	for ( int i = 0 ; i < nax ; ++i )
		v [i] = false;
	ins = 0; ++ins;
	v[root] = true; ++ins;
	par[root] = root; ++ins;
	dis[root] = 0; ++ins;
	stack<int> s; ++ins;
	s.push ( root ); ++ins;
	while ( !s.empty() && ++ins ) {
		cp = s.top(); ++ins;
		s.pop(); ++ins;
		for ( int x : g[cp] ) {
			++ins;
			if ( !v[x] && ++ins ) {
				v[x] = true; ++ins;
				s.push ( x ); ++ins;
				par[x] = cp; ++ins;
				dis[x] = dis[cp] + 1; ++ins;
			}
		}
	}
	cout << "Output for DFS." << endl;
	cout << "Reachable nodes are : ";
	for ( int i = 0 ; i < nax ; ++i ) {
		if ( in[i] && (dis[i] != inf ) ) {
			cout << i << " ";
		}
	}
	cout << endl;
	cout << "Instructions : " << ins << endl;
	cout << "Paths are:" << endl;
	for ( int i = 0 ; i < nax ; ++i ) {
		if ( in[i] && (dis[i] != inf ) ) {
			cout << "Path from "<<root<<" to " <<i<< " is : ";
			int bas = i;
			pp.clear();
			while ( par[bas] != bas ) {
				pp.push_back(bas);
				bas = par[bas];
			}
			pp.push_back(root);
			reverse ( pp.begin(), pp.end() );
			for ( int xx : pp ) cout << xx << " ";
			cout << endl;
		}
	}
	cout << endl;
}

int main ()
{
	reset ();
	cout << "Enter the number of nodes : ";
	cin >> n;
	cout << "Enter the number of edges : ";
	cin >> e;
	cout << "Enter " << e << " edges : " << endl;
	for ( int i = 0 ; i < e ; ++i ) {
		cin >> l >> r;
		in [l] = in [r] = true;
		g[l].push_back(r);
	}
	cout << "Enter the Starting Node : ";
	cin >> root;

	bfs ();
	dfs ();


	return 0;
}
