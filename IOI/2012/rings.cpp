#include <bits/stdc++.h>
 
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size())
 
const int MAXN = 1e6+10 ;
 
using namespace std ;
 
int N ;
vector<pair<int,int> > edg ;
int dsu[5][MAXN] , qtd[5][MAXN] , deg[5][MAXN] , qtdCycle[5] , sz_cycle[5] ;
int bigDegree[5] , guy[5] ;
 
int find(int x, int idx){
  return dsu[idx][x] = ( x == dsu[idx][x]) ? x : find(dsu[idx][x],idx) ;
}
 
int isCycle(int x, int y, int idx ){
  x = find(x,idx) ;
  y = find(y,idx) ;
 
  if(x == y  )return true ;
 
  if(rand() % 2) swap(x,y) ;
 
  dsu[idx][x] = y ;
  qtd[idx][y] += qtd[idx][x] ;
 
  return false ;
}
 
void addEdge(int A, int B, int idx){
 
  if(A == guy[idx] || B == guy[idx]) return ;
 
  bigDegree[idx] = max(bigDegree[idx],++deg[idx][A]) ;
  bigDegree[idx] = max(bigDegree[idx],++deg[idx][B]) ;
 
  if(isCycle(A,B,idx)){
    qtdCycle[idx]++ ;
    sz_cycle[idx] = qtd[idx][find(A,idx)] ;
  }
 
}
 
void Init(int N_) {
  N = N_;
  guy[0] = -1 ;
  sz_cycle[0] = N ;
  for(int i= 0 ; i < 5 ; i++ )
    for(int j = 0 ; j < N ; j++ ){
      qtd[i][j] = 1 ;
      dsu[i][j] = j ;
    }
}
 
void Link(int A, int B) {
  
  edg.push_back(make_pair(A,B)) ;
  bool spoiled = (bigDegree[0] >= 3) ;
 
  addEdge(A,B,0) ;
  if(spoiled)
    for(int i = 1 ; i < 5 ; i++ ) addEdge(A,B,i) ;
 
  if(deg[0][A] < deg[0][B]) swap(A,B) ;
  if(bigDegree[0] < 3 || spoiled ) return ;
 
  guy[1] = A ;
  int id = 1 ;
  for(auto &e : edg ){
    if(e.first == A ) swap(e.first, e.second );
    if(e.second == A) guy[++id] = e.first ;
  }
 
  for(auto &e : edg )
    for(int i = 1 ;i  < 5 ; i++ )
      addEdge(e.first, e.second , i ) ;
}
 
int CountCritical() {
 
  int ans = 0 ;
  if(bigDegree[0] < 3 && qtdCycle[0] <= 1){
    ans += sz_cycle[0] ;
  }
 
  if(bigDegree[0] >= 3 ){
    for(int i = 1 ; i < 5 ; i++ ) 
      ans += (bigDegree[i] < 3 && qtdCycle[i] == 0 ) ;
  }
 
  return ans ;
 
}
