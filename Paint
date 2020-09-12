/*
  APIO 2020 - Painting Walls (Paint)
*/

#include <bits/stdc++.h>
#include "paint.h"

#define debug printf
#define sz(x) (int)(x.size())
#define all(x) x.begin(),x.end()
#define pb push_back

const int MAXN = 1e5+5 ;
const int MAXM = 5e4+10 ;

using namespace std ;

int N , M , qtdOk ;
int C[MAXN] , qtd[MAXM] ;
vector<int> color[MAXN] ;
bool isOk[MAXN] ;

void solve(int idx, int type )
{
    int meuMod = idx % M ;

    for(int j : color[ C[idx] ] )
    {
        int toFill = j - meuMod ;
        if(toFill < 0) toFill += M ;

        if( qtd[ toFill ] == M && qtd[toFill] + type != M ) qtdOk-- ;
        if( qtd[toFill] != M && qtd[toFill] + type == M ) qtdOk++ ;

        qtd[toFill] += type ;

    }

}

int minimumInstructions(int n , int m , int K , vector<int> c , vector<int> A , vector< vector<int> > B )
{
    N = n ;
    M = m ;

    for(int i = 0 ; i < N ; i++ ) C[i] = c[i] ;

    for(int i = 0 ; i < M ; i++ )
        for(int j = 0 ; j < A[i] ; j++ )
            color[ B[i][j] ].push_back(i) ;

    for(int i = 0 ; i < M ; i++ ) solve(i,1) ;

    if( qtdOk ) isOk[0] = true ;

    for(int i = 1 ; i + M - 1 <= N ; i++ )
    {
        if(C[i-1] != C[i+M-1])
        {
            solve(i-1, -1 ) ;
            solve(i+M-1,1) ;
        }
        isOk[i] = (qtdOk > 0) ;


    }


    int last = -MAXN ;
    int lastOperated = -MAXN ;
    int cnt = 0 ;

    for(int i = 0 ; i < N ; i++ )
    {
        if( isOk[i] ) last = i + M - 1 ;

        if( i > lastOperated )
        {
            if( last < i ) return -1 ;

            lastOperated = last ;
            cnt++ ;
        }

    }

    return cnt ;

}
/*
int main()
{
    int n , m , k  ;
    scanf("%d%d%d", &n , &m, &k ) ;

    vector<int> c(n) , a(m) ;
    vector< vector<int> > b(m) ;

    for(int i = 0  ; i < n ; i++ ) scanf("%d", &c[i]) ;
    for(int i = 0 ; i < m ; i++ )
    {
        scanf("%d", &a[i]) ;
        for(int j = 0 ,x ; j < a[i] ; j++ )
        {
            scanf("%d", &x ) ;
            b[i].push_back(x) ;
        }
    }

    printf("%d\n", minimumInstructions(n,m,k,c,a,b) ) ;

}
*/

