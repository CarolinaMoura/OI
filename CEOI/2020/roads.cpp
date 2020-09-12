#include <bits/stdc++.h>

#define pb push_back
#define ll long long
#define pii pair<int,int>
#define mk make_pair
#define all(x) x.begin(),x.end()
#define ff first
#define ss second
#define debug printf

const int MAXN = 1e5+100 ;
const ll inf = 1e8 ;

using namespace std ;

struct Point
{
    ll x , y ;

    Point( ll x = 0LL , ll y = 0LL  ) : x(x) , y(y) {}

    void read() { scanf("%lld %lld", &x, &y) ; }
    bool operator < ( Point other ) const { return mk(x,y) < mk(other.x, other.y) ; }
    ll operator % ( Point other ) const { return x*other.y - y*other.x ; }
    Point operator - ( Point other ) const { return Point(x-other.x, y-other.y) ; }

};


int N ;
double slope[MAXN] , linear[MAXN] ;
Point leftEndpoint[MAXN] , rightEndpoint[MAXN] ;
Point rightMost[MAXN] ;
ll curX ;
vector< pair<Point,int> > sweep ;

bool cmp(int i, int j)
{

    double yI , yJ ;

    if( rightEndpoint[i].x == leftEndpoint[i].x ) yI = leftEndpoint[i].y ;
    else yI = slope[i] * (double)curX + linear[i] ;

    if( rightEndpoint[j].x == leftEndpoint[j].x ) yJ = leftEndpoint[j].y ;
    else yJ = slope[j] * (double)curX + linear[j] ;

    return yI < yJ ;

}

set<int, bool(*)(int,int)> mySet(cmp) ;

int main()
{
    scanf("%d", &N ) ;
    for(int i = 1 ; i <= N ; i++ )
    {
        leftEndpoint[i].read() ;
        rightEndpoint[i].read() ;

        if( rightEndpoint[i] < leftEndpoint[i] )
            swap( rightEndpoint[i] , leftEndpoint[i] ) ;

        sweep.pb( mk( leftEndpoint[i] , i ) ) ;
        sweep.pb( mk( rightEndpoint[i] , -i ) ) ;
    }

    sort( all(sweep) ) ;

    leftEndpoint[N+1] = Point( -inf , -inf ) ;
    rightEndpoint[N+1] = Point(inf, -inf ) ;

    mySet.insert( N+1 ) ;
    curX = -inf ;

    for(int i = 1 ; i<= N+1 ; i++ )
    {
        rightMost[i] = leftEndpoint[i] ;

        if( rightEndpoint[i].x == leftEndpoint[i].x ) continue ;

        slope[i] = (double)( rightEndpoint[i].y - leftEndpoint[i].y  ) /( rightEndpoint[i].x - leftEndpoint[i].x ) ;
        linear[i] = (double)leftEndpoint[i].y - slope[i] * leftEndpoint[i].x ;
    }

    for(auto e : sweep )
    {
        Point p = e.ff ;
        int i = e.ss ;

        curX = p.x ;

        if( i > 0 )
        {

            //This is a left endpoint
            mySet.insert( i ) ;

            auto it = mySet.find( i ) ;
            it-- ;

            if( rightMost[*it].x != -inf )
                printf("%lld %lld %lld %lld\n", p.x , p.y , rightMost[*it].x, rightMost[*it].y ) ;

            rightMost[*it] = leftEndpoint[i] ;

        }
        else
        {
            i = -i ;

            auto it = mySet.find(i) ;
            it-- ;

            rightMost[*it] = rightEndpoint[i] ;

            it++ ;
            mySet.erase(it) ;

        }

    }

}
