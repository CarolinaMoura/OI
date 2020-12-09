#include <bits/stdc++.h>
 
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
 
#define mkt make_tuple
#define debug printf
#define all(x) x.begin(),x.end()
#define lp(i,a,b) for(int i = a ; i< b ; i++)
#define ss second
#define ff first
#define ll long long
#define int ll
#define pb push_back
#define pii pair<int,int>
#define mk make_pair
 
using namespace std ;
 
int N , X , Y , M = -1 ;
map< pii , bool > mp ;
string s ;
 
bool valid(int x, int y) { return 1 <= min(x,y) && max(x,y) <= N ; }
 
bool test(int x, int y)
{
    if(!valid(x,y) ) return false;
 
    if( mp.find( mk(x,y) ) != mp.end() ) return mp[ mk(x,y) ] ;
 
    cout << "examine "<< x << " " << y << endl ;
    cin >> s ;
 
    mp[ mk(x,y) ] = ( s == "true" ) ;
 
    return s == "true" ;
}
 
int32_t main()
{
 
    ios_base::sync_with_stdio(false) ;
    cin.tie(NULL) ;
 
    cin >> N >> X >> Y ;
 
    mp[ mk(X,Y) ] = true ;
 
    int l = Y , r = N , mid , best_up = l ;
    while(l<=r)
    {
        mid = (l+r)>>1 ;
 
        if( test(X,mid) ) { best_up = mid ; l = mid + 1; }
        else r = mid - 1 ;
 
    }
 
    r = Y , l = 1 , mid ;
    int best_low = r ;
 
    while(l<=r)
    {
        mid = (l+r)>>1;
 
        if( test(X,mid) ) { best_low = mid ; r = mid - 1 ; }
        else l = mid + 1 ;
 
    }
 
    //I know interval [best_low, best_up] is great
    //But how many squares are there?
 
    //Testing 3 squares
    if( (best_up-best_low+1) % 5 == 0 )
    {
        M = ( best_up - best_low + 1 )/5 ;
 
        if( !test( X , best_up - M + 1 ) || test(X,best_up-M) || test( X , best_up - 2*M + 1 ) || !test(X, best_up - 2*M ) || !test(X, best_up - 3*M + 1) || test(X, best_up - 3*M) || test(X, best_up - 4*M + 1) || !test(X, best_up - 4*M) )
            M = -1 ;
 
    }
 
    //Testing 2 squares
    if( M == -1 && (best_up - best_low + 1) % 3 == 0 )
    {
        M = ( best_up - best_low + 1 )/3 ;
 
        if( !test( X , best_up - M + 1 ) || test(X,best_up-M) || test( X , best_up - 2*M + 1 ) || !test(X, best_up - 2*M ) )
            M = -1 ;
 
    }
 
    //Testing only one square
    if( M == -1 ) M = best_up - best_low + 1 ;
 
 
    //Find the center of any square
    Y = best_up - ( (M-1)/2) ;
 
    l = X , r = min(N , l + M) ;
    int best_right ;
 
    while( l <= r )
    {
        mid = (l+r)>>1 ;
        if( test(mid , Y) ) { best_right = mid ; l = mid + 1 ; }
        else r = mid - 1 ;
    }
 
    l = max(1LL, X - M ), r = X ;
    int best_left ;
 
    while( l <= r )
    {
        mid = (l+r)>>1 ;
        if( test(mid, Y) ) { best_left = mid ; r = mid - 1 ; }
        else l = mid + 1 ;
    }
 
    X = ( best_right + best_left )/2 ;
 
    while( test(X , Y + 2*M) ) Y += 2*M ;
    while( test(X-2*M , Y) ) X -= 2*M ;
 
    if( test(X - M , Y + M ) ) X += M , Y -= M ;
    else X += 2*M , Y -= 2*M ;
 
    cout << "solution " << X << " " << Y << endl ;
 
    return 0 ;
 
}
