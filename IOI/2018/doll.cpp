#include "doll.h"
#include <bits/stdc++.h>
 
#define printPii(p) printf("%d %d\n" ,p.ff , p.ss)
#define debug printf
#define lp(i,a,b) for(int i=a;i<b;i++)
#define pii pair<int,int>
#define ll long long
#define ff first
#define ss second
#define pb push_back
#define mk make_pair
 
const int inf=1e9+10 ;
const int MAXN = 2e5+10;
 
using namespace std ;
 
int n , m , qtd ;
int triggers[MAXN*2] ;
vector<pii> folha ;
 
// -------------------------
 
struct node
{
 
  int id , l , r , gate ;
  bool exist ;
 
} ;
 
node v[MAXN*4] ;
 
int mid(int l , int r ) { return (l+r)/2 ; }
 
 
void createTree(int pos, int l , int r )
{
 
  v[pos].id = -pos ;
 
  if(l==r) return ;
 
 
  createTree( pos*2, l , mid(l,r) ) ;
  createTree(pos*2+1, mid(l,r)+1 , r ) ;
 
  v[pos].gate = 0 ;
  v[pos].exist = false ;
 
}
 
void simulate( int pos , int l , int r , int cnt )
{
 
  if( l == r )
  {
 
    folha.pb(mk( pos , cnt )) ;
 
    if( ++cnt <= qtd )  simulate(1 , 1 , qtd , cnt) ;
 
    return ;
 
  }
 
  int idx = pos*2 ;
  pii p = mk( l , mid(l,r) ) ;
 
  if( v[pos].gate == 1 )
  {
    idx ++ ;
    p = mk( mid(l,r)+1 , r ) ;
  }
 
  v[pos].gate = !v[pos].gate ;
 
  simulate( idx , p.ff , p.ss , cnt ) ;
 
}
 
pii helpful[MAXN*4] ;
 
void finalize(int pos, int l, int r )
{
 
  if( l ==  r) return ;
 
  finalize( pos*2 , l , mid(l,r) ) ;
  finalize(pos*2+1, mid(l,r)+1, r) ;
 
  if( !v[pos*2].exist && !v[pos*2+1].exist )
  {
    v[pos].exist = false ;
    return ;
  }
 
  v[pos].exist = true ;
}
 
int cnt = 1 ;
 
void lastProcessing( int pos , int l , int r )
{
 
  if(l==r) return ;
 
  if( v[pos].exist ) v[pos].id = - cnt ;
  else { v[pos].id = -1 ; return ; }
 
  cnt ++ ;
 
  lastProcessing( pos*2 , l , mid(l,r) ) ;
  lastProcessing(pos*2+1, mid(l,r)+1 , r ) ; 
 
  v[pos].l = ( v[pos*2].exist ? v[pos*2].id : -1 ) ;
  v[pos].r = ( v[pos*2+1].exist ? v[pos*2+1].id : -1 ) ;
 
  int idx = -v[pos].id ;
 
  helpful[idx] = mk( v[pos].l , v[pos].r ) ;
 
}
 
void print(int pos,  int l , int r )
{
  printf("%d (%d %d) -> %d %d %d\n" , pos , l , r , v[pos].id , v[pos].l , v[pos].r ) ;
  printf("%d!\n" , v[pos].exist ) ;
  if(l==r) return ;
  print(pos*2 , l,  mid(l,r)) ;
  print(pos*2+1, mid(l,r)+1, r) ;
}
 
void create_circuit(int M, vector<int> A) 
{
  m = M ;
  n = A.size() ;
  lp(i,1,n+1) triggers[i] = A[i-1] ;
  triggers[++n] = 0 ;
 
  vector<int> c(m+1) ;
  lp(i,0,m+1) c[i] = -1 ;
 
 
 
  for(int i = 0 ; i <= 21 ; i++ )
    if( (1<<i) >= n )
      { qtd = (1<<i) ; break ; }
 
 
  createTree( 1 , 1 , qtd );
  simulate(1,1,qtd , 1) ;
 
  sort( folha.begin() , folha.end() ) ;    //ordena por id na arvore
  reverse(folha.begin() , folha.end() ) ;
  lp(i,0,n) swap( folha[i].ff  ,folha[i].ss ) ;
  sort( folha.begin() , folha.begin() + n ) ; //ordena os n ultimos por oderm de processamento
  lp(i,0,n) 
  {
    int idx = folha[i].ss ;
 
    v[ idx ].id = triggers[i+1] ;
    v[idx].exist = true ;
  }
 
  finalize(1,1,qtd) ;
  lastProcessing(1,1,qtd) ;
 // print(1,1,qtd);
 
  vector<int> x(cnt-1) , y(cnt-1) ;
 
  lp(i,0,cnt-1) 
  {
    x[i] = helpful[i+1].ff ;
    y[i] = helpful[i+1].ss ;
  }
 
  answer(c,x,y) ;
 
}
