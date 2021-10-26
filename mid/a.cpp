#include <bits/stdc++.h>
using namespace std;

int A ( int m, int n )
{
	int ans = 0;
	if ( m == 0 ) {
		ans = n + 1;
	}
	if ( m > 0 && n == 0 ) {
		ans = A ( m - 1, 1 );
	}
	if ( m > 0 && n > 0 ) {
		int right = A ( m, n -1 );
		ans = A ( m - 1, right );
	}
	return ans;
}

int main ()
{
	cout << "Enter the value of m and n" << endl;
	int m, n;
	cin >> m >> n;

	long ans = A ( m, n );
	cout << "A("<<m<<","<<n<<")="<<ans<<endl;

	return 0;
}

