#include <bits/stdc++.h>

#define pb push_back
#define lp(i,a,b) for(int i = a ;i < b ; i++)
#define sz(x) (int)(x.size())
#define all(x) x.begin(),x.end()

const int MAXN = 10010 ;

using namespace std;

int N ; 
vector<int> adj[MAXN]; 

int DFS(int x, int pai , int &curMax, int tam ){
	
	vector<int> vec , par ;
	
	for(auto e : adj[x] ) 
		if(e != pai) vec.push_back( DFS(e, x, curMax,tam)+1 ) ;
		
	if( (sz(adj[x])&1) ) vec.push_back(0) ;
	
	sort(all(vec)) ;
	par.resize( sz(vec) ) ;
	
	if(pai == -1 ){
		
		for(int i = 0 , j = sz(vec)-1 ; i < j ; i++ , j-- ){
			curMax = max(curMax, vec[i]+vec[j]) ;
		}		
		return 0 ;
		
	}
	
	multiset<int> s ;
	
	for(int i = 1 , j = sz(vec)-1 ; i < j ; i++ ,j-- ){
		s.insert( vec[i]+vec[j] ) ;
		par[i] = j ;
		par[j] = i ;
	}
		
	if(s.empty() || *prev(s.end()) <= tam ) return vec[0] ;
				
	for(int i = 1 ; i < sz(vec); i++ ){
		
		s.erase( s.find(vec[i]+vec[par[i]]) ) ;
		par[i-1] = par[i] ;
		par[par[i]] = i-1 ;
		s.insert(vec[i-1]+vec[par[i]]) ;
		
		if(*prev(s.end()) <= tam ) return vec[i] ;
	}
	
	curMax = tam+10 ;
	
	return 0 ;
}

bool test(int x){
	
	int mx =  -1 ;
	
	DFS(1,-1,mx, x) ;
	
	return mx <= x ;
}

int main(){
	ios_base::sync_with_stdio(false) ;
	cin.tie(0) ;
	
	cin >> N ;
	for(int i = 0 , a , b ; i < N-1 ; i++ ){
		cin >> a >> b ;
		adj[a].push_back(b) ;
		adj[b].push_back(a) ;
	}
	
	int ans = 0 ;
	lp(i,1,N+1)
		ans += ( (adj[i].size()&1) ) ;
	ans >>= 1 ;
	
	int l = 1 , r = N , mid ;
	
	while(l < r){
		
		mid = (l+r)>>1 ;
		
		if(test(mid)) r = mid ;
		else l = mid+1 ;
		
	} 
	
	cout << ans << " " << l << "\n" ;
	
}
