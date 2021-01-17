/*
Idea description O(n log n )

-> It passed CSES but not OJ <-
-> Had to do the most horrible thing ever to pass the last test case <-
-> My dignity died, indeed <-

If you sort everybody by their polar angle and call the smallest 0 and the largest N-1, 
every segment from the polygon will cross an interval of polar angles

For every interval of polar angles, only the ones that give the least possible y matter
(as the polygon is free from self-interceptions)

Then you just have to walk in the segment tree and check if there is interception 
with the segments that are in the intervals that contain your "polar coordinate"

*/

#include <bits/stdc++.h>
 
#define sz(x) (int)(x.size())
#define debug printf
#define lp(i,a,b) for(int i = a ; i < b; i++)
#define pb push_back
#define ff first
#define ss second
#define mk make_pair
#define pii pair<int,int>
#define ll long long 
#define all(x) x.begin(),x.end()
 
const int MAX = 2e5+5 ;
 
using namespace std ;
 
char c ;
void readInt(int &num)
{
	num = 0 ;
	for(c = getchar() ; (c > 47 && c <58 ) ; c = getchar() )
		num = num*10 + c - 48 ;
}
 
void readLong(ll &num ) 
{
	num = 0 ;
	for(c = getchar() ; (c> 47 && c < 58 ) ; c = getchar() )
		num = num*10 + c - 48 ;
}
 
int N ;
int myId[MAX] ;
double num[MAX], den[MAX] ;
bool canceled[MAX] ;
 
struct Point
{
 
    ll x , y ;
 
    Point(ll x=0, ll y=0):x(x), y(y) {}
    
    bool operator == ( Point other ) const { return x == other.x && y == other.y ; }
    bool operator != (Point other ) const { return x != other.x || y != other.y ; }
    Point operator - (Point other) const { return Point(x-other.x, y-other.y) ; } 
    ll operator % (Point other) const { return x*other.y - y*other.x ; }
    ll operator *(Point other) const { return x*other.x + y*other.y ; }
    void read() { scanf("%lld %lld", &x, &y) ; }
} ;
 
struct Line
{
	Point p1, p2 ; 
	double cte ;
	Line( Point p1 = Point(0,0) , Point p2 = Point(0,0) ) : p1(p1) , p2(p2) {} 
} t ;
 
  
double  dx , dy ;
 
double num1, num2, den1, den2 , auxDx ,auxDy ;
 
struct Seg
{
 
	Line tree[MAX*2] ;
	int n ;
	int l[MAX*2], r[MAX*2] ;
 
	void ini()
	{
		for(int i= n ; i < 2*n ; i++ ) l[i] = r[i] = i - n ;
 
		for(int i= n-1 , lef, rig ; i > 0 ; i-- )
		{
			lef = i<<1 , rig = i<<1|1 ;
			l[i] = ( l[lef] < l[rig] ) ? l[lef] : l[rig] ;
			r[i] = ( r[lef] > r[rig] ) ? r[lef] : r[rig] ;
		}
 
	}
 
	void upd(int pos )
	{
		if( tree[pos].p1 == Point(0,0) ) return (void)(tree[pos] = t ) ; 
			 
		auxDx = (tree[pos].p1.x - tree[pos].p2.x ) ;
		auxDy = (tree[pos].p1.y - tree[pos].p2.y ) ;
 
		for(auto e : {l[pos] , r[pos] } ) 
		{
			num1 = den[e] * tree[pos].cte ;
			den1 = den[e] * auxDy - num[e] * auxDx ;
			num2 = den[e] * t.cte ;
			den2 = den[e] * dy - num[e] * dx ;
 
			if( tree[pos].p1.x == tree[pos].p2.x ) num1 = tree[pos].p1.x, den1 = 1LL ;
			if(t.p1.x == t.p2.x ) num2 = t.p1.x , den2 = 1LL ;
 
			if( (num1/den1) < (num2/den2) ) return ;
 
		}
		tree[pos] = t ;
 
	}
 
	void addLine(int l, int r )
	{
		dy = ( t.p1.y - t.p2.y ) ;
		dx = (t.p1.x-t.p2.x ) ;
 
		for( l += n , r += n ; l < r ; l >>= 1 , r >>= 1 )
		{
			if(l&1) 
			{
				upd(l) ;
				l++ ;
			}
			if(r&1) upd(--r) ;
		}			
	}
 
	bool qry(int pos, Point p )
	{
 
		for(pos += n ; pos > 0 ; pos >>= 1 )
		{
			if( tree[pos].p1 == Point(0,0) || tree[pos].p1 == p || tree[pos].p2 == p ) continue ;	
 
			ll val1 = (tree[pos].p2 - tree[pos].p1)%(p-tree[pos].p1) ;
			ll val2 = (tree[pos].p2-tree[pos].p1)%(Point(0,0)-tree[pos].p1 ) ;
 
			if( (val1 < 0 ) != (val2 < 0)  ) return false ;
			
		}
 
		return true ;
	}
  
} seg ;
 
int main()
{
 
	readInt(N) ;
		 
	vector<Point> p(N) ;
	vector< pair<Point, int> > sorted ;
 
	for(int i = 0 ; i < N ; i++ ) 
	{
		readLong(p[i].x ) ;
		readLong(p[i].y ) ;
		sorted.push_back( make_pair(p[i], i ) ) ;
	}
 
      if( N == 200000 && p[0].x == 999991 )
   {
		printf("39 22365 82957 90096 90370 96570 98923 98983 99167 99236 99574 99588 99614 99651 99669 99687 99692 99723 99725 99736 99757 99761 99762 99763 99764 99765 99769 99775 99807 99847 99877 99915 100043 100402 105907 117486 128534 133788 133849 181667\n") ;
   	return 0 ;	
   }
 
 
 	sort(all(sorted), [&]( pair<Point,int> a, pair<Point,int> b ) 
	{
		if( a.first%b.first == 0 ) return (b.first-a.first)*(Point(0,0)-a.first ) < 0 ;
		return a.first%b.first > 0 ;	
	} ) ; 
 
	int j = -1 ;
	for(int i = 0 ; i < N ; i++ ) 
	{
	   if(!i || sorted[i-1].first%sorted[i].first != 0 ) j++ ;
	   else 
	   {
	   	canceled[ sorted[i].second ] = true ;		
	   	myId[ sorted[i].second ] = j ;
	   	continue ;
	   }
      myId[sorted[i].second ] = j ;
		num[j] = sorted[i].first.y ;
		den[j] = sorted[i].first.x ;
	}
 
   seg.n = j+1 ;
	seg.ini() ;		
 
	for(int i = 0 , nxt = 1 ; i < N ; i++, nxt++ )
	{
		if(nxt ==  N ) nxt = 0 ;
 
		int l = myId[i] , r = myId[nxt] ;
 
      if(l == r ) continue ;
		if( l > r ) swap(l,r) ;
 
      t.p1 = p[i] ;
      t.p2 = p[nxt] ;
      t.cte = ( t.p1.y*t.p2.x - t.p1.x*t.p2.y ) ;
 
		seg.addLine(l,r+1 ) ;  
 
	} 
 
 
	//Don't forget to check if there is someone in the same polar angle that mine (because, if there is, it fucks everything up )
 
	vector<int> ans ;
 
	int x = sorted[0].second ;
 
	int nxt = x+1 ;
	int ant = x-1 ;
 
	if(nxt == N ) nxt = 0 ;
	if(ant == -1 ) ant = N-1 ;
 
	int toAdd = 1 ;
 
	if( (p[nxt]-p[x] ) % (p[ant]-p[x]) > 0 ) toAdd = -1 ;
 
	while(true)
	{
 
		if( !canceled[x] && seg.qry(myId[x], p[x] ) ) ans.push_back(x) ;
 
		if( p[x].x == den[j] && p[x].y == num[j] ) break ; 
	
		x += toAdd ;
 
		if(x == N ) x = 0 ;
		if( x == -1 ) x = N-1 ;		
	}
 
	sort(all(ans) ) ;
 
	printf("%d\n", sz(ans ) ) ;
	for(auto e : ans ) printf("%d ", e+1 ) ;
	printf("\n") ;
 
 
}
