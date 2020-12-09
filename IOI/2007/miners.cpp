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
#define pb push_back
#define pii pair<int,int>
#define mk make_pair
 
const int MAXN = 1e5+10 ;
 
using namespace std ;
 
int N ;
bool freq[4] ;
int dp[MAXN][4][4][4][4] ;
char str[MAXN] ;
 
int get(char c)
{
    if( c == 'B' ) return 1 ;
    return c == 'F' ? 2 : 3 ;
}
 
int _count()
{
    int cnt = 0 ;
    lp(i,1,4) cnt += freq[i] ;
    return cnt ;
}
 
int main()
{
    scanf("%d %s", &N , str ) ;
 
    for(int i = N-1 ; i >= 0 ; i-- )
        for(int j1 = 0 ; j1 < 4 ; j1 ++ )
            for(int j2 = 0 ; j2 < 4 ; j2 ++ )
                for(int g1 = 0 ; g1 < 4 ; g1 ++ )
                    for(int g2 = 0 ; g2 < 4 ; g2 ++ )
                    {
                        int &ptr = dp[i][j1][j2][g1][g2] ;
                        int x = get(str[i]) ;
 
                        freq[x] = true ;
 
                        //Decidi dar pro primeiro
                        freq[j1] = freq[j2] = true ;
                        ptr = max(ptr, _count() + dp[i+1][j2][x][g1][g2] ) ;
                        freq[j1] = freq[j2] = false ;
 
                        freq[x] = true ;
 
                        //Decidi dar pro segundo
                        freq[g1] = freq[g2] = true ;
                        ptr = max(ptr, _count() + dp[i+1][j1][j2][g2][x]) ;
                        freq[g1] = freq[g2] = false ;
 
                        freq[x] = false ;
 
                    }
 
    printf("%d\n" , dp[0][0][0][0][0] ) ;
 
}
