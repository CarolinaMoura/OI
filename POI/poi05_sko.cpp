#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define lp(i,a,b) for(int i = a ;i < b ; i++)
#define sz(x) (int)(x.size())
#define all(x) x.begin(),x.end()
#define mk make_pair

const int MAX = 110 ;

using namespace std;

int N ;
ll X[MAX] , Y[MAX] ;

void gcdExtended(ll a , ll b , ll &x, ll &y ){

	if(a == 0) return (void)(x = 0 , y = 1);

	gcdExtended(b%a , a , x , y ) ;

	y -= (b/a)*x ;
	swap(x,y );

}

void solve( ll &ax, ll &ay, ll &bx, ll &by ){

	ll m = __gcd(ay, by) ;
	ll k = ay/m ;
	ll l = by/m ;
	ll p , q ;

	/*cout << "ax: " << ax <<" " << "ay: " << ay << endl ;
	cout << "bx: " << bx <<" " << "by: " << by << endl ;
	cout << "k: " << k << " l: " << l << endl ;  */
	
	gcdExtended( min(ay,by) , max(ay,by) , p , q  ) ;

	if(ay > by) swap(p,q); 

	//cout << m << " = " << p << "*" << ay << " + " << q << "*" << by << endl ;

	ll cx = l*ax-k*bx ;
	ll dx = p*ax + q*bx ;
	ll dy = m ;

	ax = cx ; ay = 0 ;
	bx = dx ;
	by= dy ;
}

int main(){
	ios_base::sync_with_stdio(false) ;
	cin.tie(0) ;
	
	cin >> N ;
	for(int i = 1 ; i <= N ; i++ ){
		cin >> X[i] >> Y[i] ;
	}

	ll x = 10001 ;

	for(int i = 1 ; i < N ; i++ ){
		if(Y[i+1] == 0){
			swap(X[i] , X[i+1]) ;
			swap(Y[i] , Y[i+1]) ;
		}
		if(Y[i] == 0 ){
			X[i] = abs(X[i]) ;
			continue ;
		}

		solve(X[i] , Y[i] , X[i+1] , Y[i+1]) ;

		if( X[i] < 0 ) X[i] = -X[i] ;
		if(X[i+1] < 0){
			X[i+1] = -X[i+1] ;
			Y[i+1] = -Y[i+1] ;
		}

		X[i] %= x ;
		X[i+1] %= x ;

		if(X[i]) x = X[i] ;
	}

	cout << X[N] << " " << Y[N] << "\n" ;

	ll g = 0 ;
	for(int i = 1 ; i < N ; i++ )
		if(X[i] != 0){
			if(g) g = __gcd(g,X[i]) ;
			else g = X[i] ;
		}

	cout << g << " 0\n" ;

}
