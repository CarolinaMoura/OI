#include <bits/stdc++.h>

#define sz(x) (int)(x.size())
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define mk make_pair
#define all(x) x.begin(),x.end()
#define pii pair<int,int:
#define debug  

const int MAXN = 2010 ;
const int MAXC = 10010 ;
const ll inf = 1e9+2 ;

using namespace std ;

struct Point
{

	ll x , y ;

	Point(ll x=0, ll y=0):x(x), y(y) {}

	bool operator == (Point other) const { return x == other.x && y == other.y ; }
	Point operator - (Point other) const { return Point(x-other.x, y-other.y) ; } 
	double operator % (Point other) const 
	{
		double ax = (double)x ;
		double ay = (double)y ;
		double bx = (double)other.x ;
		double by = (double)other.y ;

		ax /= 1000000000.0 ;
		ay /= 1000000000.0 ;
		bx /= 1000000000.0 ;
		by /= 1000000000.0 ;

		return ax*by - ay*bx ;
	}
	ll operator *(Point other) const { return x*other.x + y*other.y ; }
	void print() { printf("%lld %lld\n" , x , y) ; }

} ;

//Toma cuidado quando os pontos têm a mesma coordenada x

int W , H , N , C ;
Point G ;
Point camp[MAXC] ;
Point tree[MAXN] ;
bool iLost[MAXC] ;
vector<Point> myPoints[MAXN] ;

int quad(Point p )
{
	//Nao tem como ser zero, entao nao vou me importar
	//Soh nao cai no caso (0,0)
	//Fine by me

	if( p.x > 0 && p.y >= 0 ) return 0 ;
	if( p.x <= 0 && p.y > 0 ) return 1 ;
	if( p.x < 0 && p.y <= 0 ) return 2 ;
	if( p.x >= 0 && p.y < 0 ) return 3 ;
}


int main()
{
	scanf("%d%d", &W, &H);
	scanf("%lld %lld", &G.x, &G.y ) ;
	scanf("%d", &C ) ;
	for(int i = 1 ; i <= C ; i++ ) scanf("%lld %lld", &camp[i].x, &camp[i].y ) ;
	scanf("%d", &N ) ;
	for(int i = 1 ; i <= N ; i++ ) scanf("%lld %lld", &tree[i].x, &tree[i].y ) ;

	for(int i = 1 ; i <= N ; i++ )
	{
		for(int j = 1 ; j <= N ; j++ )
		{
			if(i == j) continue ;

			if( tree[i].x == tree[j].x )
			{
				if( tree[i].y > tree[j].y )
					myPoints[i].push_back( Point(tree[i].x , inf ) ) ;
				else myPoints[i].push_back( Point(tree[i].x, -inf ) ) ;
			}
			else if( tree[i].x < tree[j].x )
			{

				ll x = (-tree[j].x)/(tree[j].x-tree[i].x) ;
				x-- ;

				x = tree[j].x + (tree[j].x-tree[i].x)*x ;

				ll dir = (x-tree[i].x)/(tree[j].x-tree[i].x) ;
				dir *= tree[j].y - tree[i].y ;

				ll y = dir + tree[i].y ;

				myPoints[i].push_back(Point(x,y))  ;

			}
			else if( tree[i].x > tree[j].x )
			{
				ll x = (inf-tree[j].x)/(tree[j].x-tree[i].x) ;
				x-- ;

				x = tree[j].x + x*(tree[j].x-tree[i].x) ;

				ll dir = (x-tree[i].x)/(tree[j].x-tree[i].x) ;
				dir *= tree[j].y - tree[i].y ;

				ll y = dir + tree[i].y ;

				myPoints[i].push_back(Point(x,y)) ;

			}

		}

		myPoints[i].push_back(G) ;

		sort(all(myPoints[i]) , [&](Point p1, Point p2 )
		{
			Point aux1 = p1 - tree[i] ;
			Point aux2 = p2 - tree[i] ;
			
			if( quad(aux1) != quad(aux2) ) return quad(aux1) < quad(aux2) ;

			//aux1.x * aux2.y > aux1.y * aux2.x 
			//aux1.x/aux1.y> aux2.x/aux2.y

			return aux1 % aux2 > 0.0 ;

		}) ;
	}	

	for(int i = 1 ; i <= N ; i++ )
	{
		int L = 0 , R = 0 ;

		for(int j = 0 ; j < sz(myPoints[i]) ; j++ )
			if( myPoints[i][j] == G )
			{
				L = j-1 ;
				if(L < 0) L = sz(myPoints[i])-1 ;

				R = j+1 ;
				if( R >= sz(myPoints[i]) ) R = 0 ;
				break ;
			}

		Point p1 = myPoints[i][L] - tree[i] ;
		Point p2 = myPoints[i][R] - tree[i] ;

		for(int j = 1 ; j <= C ; j++ )
		{
			Point p = camp[j] - tree[i] ;

			if( p1 % p2 > 0.0 )
			{
				if( p1 % p >= 0.0 && p%p2 >= 0.0 ) continue ;
				else iLost[j] = true ;
			}
			else 
			{
				if( p2%p > 0.0 && p%p1 > 0.0) iLost[j] = true ;
				else continue ;
			}

		}

	}

	vector<int> ans ;
	for(int i = 1 ; i <= C ; i++ )
		if(!iLost[i]) ans.push_back(i) ;

	printf("%d\n" , sz(ans )) ;
	for(auto e : ans ) printf("%d " , e ) ;
	printf("\n") ;

}
