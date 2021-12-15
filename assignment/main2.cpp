#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 5;
map<int,int> mp;
map<int,int> mpr;
int N = -1;
int ins;

vector<pair<int,int>> bfs ( vector<vector<int>>& g, int root )
{
	vector<pair<int,int>> vp ( g.size(), { INF, -1 } );++ins;
	vector<bool> v ( g.size(), false );++ins;
	v[root] = true;++ins;
	vp[root] = { 0, root };++ins;
	queue<int> q;++ins;
	q.push ( root );++ins;
	while ( !q.empty() && ++ins) {
		int cp = q.front();++ins; q.pop();++ins;
		for ( int x : g[cp] ) {
			++ins;
			if ( !v[x] && ++ins ) {
				v[x] = true;++ins;
				q.push(x);++ins;
				vp[x] = { vp[cp].first + 1, cp };++ins;
			}
		}
	}
	return vp;
}

vector<pair<int,int>> dfs ( vector<vector<int>>& g, int root )
{
	vector<pair<int,int>> vp ( g.size(), { INF, -1 } );++ins;
	vector<bool> v ( g.size(), false );++ins;
	v[root] = true;++ins;
	vp[root] = { 0, root };++ins;
	stack<int> s;++ins;
	s.push ( root );++ins;
	while ( !s.empty() && ++ins) {
		int cp = s.top();++ins; s.pop();++ins;
		for ( int x : g[cp] ) {
			++ins;
			if ( !v[x] && ++ins ) {
				v[x] = true;++ins;
				s.push(x);++ins;
				vp[x] = { vp[cp].first + 1, cp };++ins;
			}
		}
	}
	return vp;
}

void run_print ( vector<vector<int>>& g, int root,
		vector<pair<int,int>> (*func) ( vector<vector<int>>&, int ),
		string algo )
{
	ins = 0;
	vector<pair<int,int>> sol = func ( g, root );
	cout << "Output for " << algo << " algorithm." << endl;
	cout << algo << " executed : " << ins << " instructions." << endl;
	cout << "The reachable nodes are : " << endl;
	for ( int i = 0 ; i < (int)sol.size() ; ++i )
		if ( sol[i].first != INF )
			cout << mpr[i] << " ";
	cout << endl;
	for ( int i = 0 ; i < (int)sol.size() ; ++i ) {
		if ( sol[i].first == INF ) continue;
		cout << "Distance from " << mpr[root] << " to " << mpr[i]
			<< " is : " << sol[i].first << ". ";
		cout << "Path is : ";
		vector<int> v;
		int bas = i;
		while ( sol[bas].second != bas ) {
			v.push_back(bas);
			bas = sol[bas].second;
		}
		v.push_back(root);
		reverse ( v.begin(), v.end() );
		for ( int x : v ) cout << mpr[x] << ' ';
		cout << endl;
	}
	cout << endl;
}

int main ()
{
	int n, e;
	cout << "Enter the number of nodes : ";
	cin >> n;
	cout << "Enter the number of edges : ";
	cin >> e;
	vector<vector<int>> g ( n, vector<int>() );
	cout << "Enter " << e << " edges : " << endl;
	for ( int i = 0 ; i < e ; ++i ) {
		int l, r;
		cin >> l >> r;
		auto search = mp.find ( l );
		if ( search == mp.end() ) mp[l]=++N,mpr[N]=l,l=N;
		else l = search->second;
		search = mp.find ( r );
		if ( search == mp.end() ) mp[r]=++N,mpr[N]=r,r=N;
		else r = search->second;
		g[l].push_back(r);
	}
	int root;
	cout << "Enter the Starting Node : ";
	cin >> root;
	root = mp.find(root)->second;
	run_print ( g, root, bfs, "BFS" );
	run_print ( g, root, dfs, "DFS" );

	return 0;
}
