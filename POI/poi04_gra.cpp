#include <bits/stdc++.h>

#define mk make_pair
#define lp(i,a,b ) for(int i = a ; i < b ; i++ )
#define ll long long
#define sz(x) (int)x.size()
#define pb push_back
#define all(x) x.begin(),x.end()
#define pii pair<int,int>

const int MAX =1e6+10 ;

using namespace std ;

map<int,int> mp ;

int main(){
	ios_base::sync_with_stdio(false) ;
	cin.tie(0) ;

	int N ,  M ;
	cin >> M >> N ;

	vector<int> arr(N) ;

	for(auto &e : arr ) cin >> e ;

	sort(all(arr)) ;

	int last = M+1 ;
	int x_sum = 0 ;
	int g = 0 ;

	vector<int> vec[2] ;

	for(int i = sz(arr)-1 , j ; i >= 0 ; i = j){
		j = i-1 ;
		while(j >= 0 && arr[j] == arr[j+1]-1 ) j-- ;

		int diff = last-arr[i]-1 ;

		g += diff ;
		last = arr[j+1] ;

		//cout << j+1 << " " << i << " " << g << endl ;

		vec[g&1].pb(g);
		mp[g] = i-j ;

		if(g&1) x_sum ^= (i-j) ;
		if(g == 1){
			cout << (i-j) << "\n" ;
			return 0 ;
		}
	}

	if(x_sum == 0 ){
		cout << "0\n" ;
		return 0 ;
	}

	int ans = 0 ;

	for(auto e : vec[1] ){
		int x = mp[e] ;
		for(int i = 0 ; i < x ; i++ )
			if(((x_sum^x)^i) == 0 ) ans++ ;
	}
	for(auto e : vec[0] ) {
		int cur = mp[e] ;
		int nxt = mp[e-1] ;
		if(e-1 == 1 ) continue ; 
		for(int i = 1 ; i <= cur ; i++ )
			if( ( (x_sum^nxt)^(nxt+i) ) == 0 ) ans++ ;
	}

	cout << ans << "\n" ;
}
