#include <bits/stdc++.h>
 
const int MAXN = 1e5+10 ;
 
using namespace std ;
 
int N , M ;
 
// ----- SEGMENT TREE -----
 
int mx[MAXN*4] , lz[MAXN*4] ;
 
int m(int l, int r) { return (l+r)>>1 ;}
 
void refresh(int pos, int l, int r){
	mx[pos] += lz[pos] ;
	if( l == r) return (void)(lz[pos] = 0 ) ;
	lz[pos<<1] += lz[pos] ;
	lz[pos<<1|1] += lz[pos] ;
	lz[pos] = 0 ;
}
 
void upd(int pos, int l, int r, int beg, int en , int val ){
 
	refresh(pos,l,r) ;
 
	if( l > en || r < beg ) return ;
	if( l >= beg && r <= en ){
		lz[pos] += val ;
		refresh(pos,l,r) ;
		return ;
	}
 
	upd(pos<<1 , l , m(l,r) , beg, en, val ) ;
	upd(pos<<1|1, m(l,r)+1 , r, beg, en, val ) ;
 
	mx[pos] = max( mx[pos<<1 ] , mx[pos<<1|1] ) ;
 
}
 
int qry1(int pos, int l, int r, int H ) {
 
	refresh(pos,l,r) ;
 
	if( mx[pos] < H ) return N+1 ;
	if( l == r ) return l ;
 
	int ans_left = qry1(pos<<1 , l , m(l,r) , H ) ;
 
	if(ans_left != N+1 ) return ans_left ;
 
	return qry1(pos<<1|1, m(l,r)+1, r , H) ;
}
 
int qry2(int pos, int l, int r, int x){
	
	refresh(pos,l,r) ;
 
	if( l == r ) return mx[pos] ;
 
	if( x <= m(l,r) ) return qry2(pos<<1 , l , m(l,r) , x ) ;
	return qry2(pos<<1|1, m(l,r)+1, r , x ) ;
 
}
 
// ------------------------
 
void F(int x, int y){
 
	int L = qry1(1,1,N, y) ;		
	
	x = min( x , N-L+1 ) ;
 
	if(x <= 0 ) return ;
 
	int R = L+x-1 ;
	int hr = qry2(1,1,N, R) ;
 
	int aux = qry1(1,1,N, hr) ;
	int qtd = R-aux+1 ;
	int aux2 = qry1(1,1,N, hr+1) ;
 
	if( L <= aux-1 ) upd(1,1,N, L, aux-1, 1) ;
	upd(1,1,N, aux2-qtd , aux2-1 , 1) ; 
 
}
 
void C(int L, int R){
	int S = qry1( 1 , 1 , N , R+1 )-qry1(1,1,N, L ) ;
	cout << S << "\n" ;
}
 
int main(){
	ios_base::sync_with_stdio(false) ;
	cin.tie(0) ;
 
	cin >> N >> M ;
	
	vector<int> arr(N) ;
	for(int i = 0 ; i< N ; i++ ) cin >> arr[i] ;
 
	sort(arr.begin() , arr.end() ) ;
 
	for(int i = 0 ; i < N ; i++ ) upd( 1 , 1 , N , i+1, i+1, arr[i] ) ;
 
	for(int i = 0 ; i < M ; i++ ){
		char c ;
		int a , b ;
		cin >> c >> a >> b ;
 
		if( c == 'F' ) F(a,b) ;
		else C(a,b) ;
 
	}
}
