#include <bits/stdc++.h>

#define debug printf
#define all(x) x.begin(),x.end()
#define ll long long
#define sz(x) (int)(x.size())

const ll MOD = 1e9+7 ;

using namespace std ;

int n , m , globalAnswer ;
int index1, index2 ;
string str1, str2 ;
vector<int> realIndex ;

void solve()
{

	//cout << "New solve iteration" << endl ;
	//cout << str1 << endl << str2 << endl ;

	//I'll try just a simple hash at first

	vector< ll > pref1(n,0LL) , pref2(m,0LL) ;
	vector<ll> firstPot(max(n,m),1LL );
	ll firstPrime = 37 ;

	for(int i = 1 ; i < max(n,m) ; i++ )
		firstPot[i] = (firstPot[i-1] * firstPrime) % MOD ;

	for(int i = 0 ; i < n ; i++ )
	{
		if(i) pref1[i] = pref1[i-1] ;
		
		ll toAdd = (int)( str1[i] - 'a' ) * firstPot[i] ;

		( pref1[i] += toAdd%MOD ) %= MOD ;

	}

	for(int i = 0 ; i < m ; i++ )
	{
		if(i) pref2[i] = pref2[i-1] ;

		ll toAdd = (int)(str2[i] - 'a') * firstPot[i] ;

		( pref2[i] += toAdd%MOD ) %= MOD ;

	}

	vector<int> vec( n, m-1 ) ;

	auto isEqual = [&](int l1, int r1, int l2, int r2 )
	{
		ll valor1 = pref1[r1] - ( ( l1 == 0 ) ? 0LL : pref1[l1-1] ) ;
		ll valor2 = pref2[r2] - ( (l2 == 0) ? 0LL : pref2[l2-1] ) ;

		if( l1 > l2 ) (valor2 *= firstPot[ l1-l2 ] ) %= MOD ;
		else (valor1 *= firstPot[l2-l1] ) %= MOD ;

		if(valor1 < 0 ) valor1 += MOD ;
		if(valor2 < 0 ) valor2 += MOD ;

		return (valor1 == valor2 ) ;

	};

	for(int i = m-1 ; i >= 0 ; i-- )
		for(int j = 0 ; j < n ; j++ )
		{

			if( str1[j] != str2[i] ) continue ;
			//calcula nossa interseccao

			int l = 1 , r = min(i, j)+1 , mid, best=1;

			while( l <= r )
			{
				mid = (l+r)>>1 ;

				if( isEqual(j-mid+1, j,i-mid+1, i) )
				{
					best = mid ;
					l = mid+1 ;
				}
				else r = mid-1 ;

			}

			//cout << "To indices " << j << " " << i << " " << best << endl ;

			if(best > globalAnswer)
			{
				globalAnswer = best ;

				index1 = j-best+1 ;
				index2 = min(realIndex[i-best+1 ] , realIndex[i] ) ;
			}

			int beg = j-best ;

			while( vec[beg] > i  )
			{
				int intendedSize = vec[beg] - i ;
				
				if( isEqual(beg-intendedSize+1, beg, i+1, vec[beg]) ) break ;
				
				vec[beg]-- ;

			}

			if(best+vec[beg]-i > globalAnswer)
			{
				globalAnswer=best+vec[beg]-i ;

				index1 = beg-(vec[beg]-i)+1 ;
				index2 = min(realIndex[i-best+1 ] , realIndex[vec[beg]] ) ;
			} 

		}

}

int main()
{

	ios_base::sync_with_stdio(false);
	cin.tie(NULL) ;

	cin >> str1 >> str2 ;

	n = sz(str1) ;
	m = sz(str2) ;

	realIndex.resize(m) ; iota(all(realIndex),0) ;

	solve() ;

	reverse(all(str2)) ;
	reverse(all(realIndex)) ;

	solve() ;

	printf("%d\n%d %d\n" , globalAnswer , index1, index2 ); 

}
