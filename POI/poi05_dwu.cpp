#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define lp(i,a,b) for(int i = a ;i < b ; i++)
#define sz(x) (int)(x.size())
#define all(x) x.begin(),x.end()
#define mk make_pair

const int MAX = 50010 ;

using namespace std;

int N ;
int dsu[MAX*2],qtd[MAX*2] ;
int a1[MAX*2] , a2[MAX*2] ;

int find(int x) { return dsu[x] = (dsu[x] == x) ? x : find(dsu[x]) ; }
bool join(int x, int y){

	x = find(x) ;
	y = find(y) ;

	if(x == y) return false ;

	if(rand() % 2) swap(x,y) ;

	dsu[x] = y ;
	qtd[y] += qtd[x] ;

	return true ;
}

int neg(int x){ return x > N ? (x-N) : (x+N) ; }

void createEdge(int a, int b){
	join(a,b) ;
	join(neg(a) , neg(b) ) ;
}

int main(){
	ios_base::sync_with_stdio(false) ;
	cin.tie(0) ;
	
	cin >> N ;
	for(int i = 0 ; i < 2 ; i++ )
		for(int j = 1 , x ; j <= N ; j++ ){
			cin >> x ;
			swap(a1[x] , a2[x]) ;
			a1[x] = j+i*N ;
		}
	
	iota(dsu+1, dsu+1+2*N , 1 ) ;
	for(int i = 1 ; i <= N ; i++)qtd[i]++ ;

	for(int i = 1 ; i <= 100000 ; i++ ){
		if(a2[i] == 0 ) continue ;
		if( (a1[i] <= N) == (a2[i] <= N) ){
			int p = (a1[i] > N) ? (-N) : 0 ;
			createEdge(a1[i]+p , neg(a2[i]+p) ) ;
		}
		else{

			if(a1[i] > a2[i]) swap(a1[i] , a2[i]) ;
			createEdge(a1[i] , a2[i]-N)  ;

		}
	}

	int ans = 0 ;

	for(int i = 1 ; i <= 2*N ; i++ ) 
		if(find(i) == i){

			if( qtd[i] < qtd[find(neg(i))] ){
				ans += qtd[i ];
			}
			else if(qtd[i] == qtd[find(neg(i))] && i < find(neg(i) ) ) ans += qtd[i] ;

		}

	cout << ans << "\n" ;
}
