#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define lp(i,a,b) for(int i = a ;i < b ; i++)
#define sz(x) (int)(x.size())
#define all(x) x.begin(),x.end()
#define mk make_pair

const int MAX = 5e5+10 ;

using namespace std;

int N , mx = 0 ;
int idx[MAX] ;
int lcp[MAX] , val[MAX], lef[MAX] , rig[MAX] ;
bool vis[MAX] ;
string str ;

void add(int id){
	vis[id] = true ;

	if(id+1 < N){
		if(vis[id+1]){
			rig[id] = rig[id+1] ;
		}
	}
	if(id-1 > 0 ){
		if(vis[id-1])
			lef[id] = lef[id-1] ;
	}

	mx = max(mx, rig[id]-lef[id]+1) ;
	lef[ rig[id] ] = lef[id] ;
	rig[ lef[id] ] = rig[id] ;
}

int main(){
	ios_base::sync_with_stdio(false) ;
	cin.tie(0) ;
	cin >> str ;

	N = sz(str) ;

	for(int i = 0 ; i < N; i++ ){

		int k = i-1 ;
		while( k >= 0 && str[i] != str[lcp[k]] ){
			k = lcp[k]-1 ;
		}
		if(k >= 0 ) lcp[i] = lcp[k]+1 ;

	}

	for(int i = 1 , ptr = 0 ; i < N ; ){


		while(ptr < N && str[i+ptr] == str[ptr]){
			ptr++ ;
		}

		val[i] = ptr ;

		for(int j = i+1 ; ptr && j < i+ptr-lcp[ptr-1] ; j++ ){
			val[j] = val[j-i] ;
		}

		if(ptr)
			i = i+ptr-lcp[ptr-1] ;
		else i++ ;
		
		if(ptr) ptr = lcp[ptr-1] ;
		else ptr = 0 ;

	}

	iota(idx, idx+N-1 , 1 ) ;
	iota(lef+1, lef+N, 1 ) ;
	iota(rig+1, rig+N,1) ;
	sort(idx, idx+N-1, [&](int a, int b){ return val[a] < val[b] ; }) ;

	int ptr = 0 ;
	for(int i = 1 ; i <= N ; i++ ){

		while( ptr < N-1 && val[idx[ptr]] == i-1 ){
			add(idx[ptr]) ;
			ptr++ ;
		}

		if( mx < i ){
			cout << i << "\n" ;
			return 0 ;
		}

	}

}
