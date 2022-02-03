#include <bits/stdc++.h>
 
const int MAX = 710 ;
const int inf = 1e9+10 ;
 
using namespace std ;
 
int N , M, lastGroup = -1 , Node = 0 ;
int dx[4] = {0,0,1,-1} , dy[4] = {1,-1,0,0} ;
int horGroup[MAX][MAX] , vertGroup[MAX][MAX] , distGroups[MAX*MAX*2] ;
char grid[MAX][MAX] ;
 
bool valid(int x, int y) {return 0 <= min(x,y) && x < N && y < M ; }
 
void bfsViking( pair<int,int> S ){
	vector< vector<int> > dist( N , vector<int>(M, inf ) ) ;
	dist[ S.first ][ S.second ] = 0 ;
 
	queue< pair<int,int> > fila ;
	fila.push( S ) ;
 
	while(!fila.empty() ){
		
		int x = fila.front().first ;
		int y = fila.front().second ;
 
		fila.pop() ;
 
 		for(int i = 0 , nx , ny ;  i < 4 ; i++ ){
 			nx = x + dx[i] ;
 			ny =y + dy[i] ;
 
 			if(!valid(nx,ny) || grid[nx][ny] == 'I' || dist[nx][ny] <= dist[x][y]+1 ) continue ;
 			
 			dist[nx][ny] = dist[x][y]+1 ;
 			fila.push( make_pair(nx,ny) ) ;
 		}
 
	}
 
	for(int i = 0 ; i < N ; i++ )
		for(int j = 0 ; j < M ; j++ ){
			distGroups[ horGroup[i][j] ] = min(distGroups[ horGroup[i][j] ], dist[i][j] ) ;
			distGroups[ vertGroup[i][j] ] = min( distGroups[ vertGroup[i][j] ] , dist[i][j] ) ;
		}
 
}
 
bool bfsYou(pair<int,int> S, pair<int,int> T ){
 
	auto getMin = [&](int a, int b){
		return min(distGroups[ horGroup[a][b] ], distGroups[ vertGroup[a][b] ] ) ;
	} ;
 
	vector< vector<int> > dist( N, vector<int>(M, inf) ) ;
 
	dist[S.first][S.second] = 0 ;
	queue<pair<int,int> > fila ;
 
	fila.push(S) ;
 
	while(!fila.empty() ){
		int x = fila.front().first;
		int y = fila.front().second ;
 
		fila.pop() ;
 
		if( x == T.first && y == T.second ) return true ;
 
		for(int i = 0 , nx , ny ; i < 4 ; i++ ){
			nx = x + dx[i] ;
			ny = y + dy[i] ;
 
			if(!valid(nx,ny) || grid[nx][ny] == 'I' || dist[nx][ny] <= dist[x][y]+1 ) continue ;	
			if( getMin(nx,ny) <= dist[x][y]+1 ) continue ;
 
			dist[nx][ny] = dist[x][y]+1 ;
			fila.push( make_pair(nx,ny) ) ;
 
		}
 
	}
 
	return false ;
 
}
 
void debug(){
	cout << "Componentes horizontais: \n" ;
	for(int i = 0 ; i < N ; i++ , cout << endl )
		for(int j = 0 ; j < M ; j++ ) cout << horGroup[i][j] <<" " ;
	cout << endl ;
 
	cout << "Componentes verticais: \n" ;
	for(int i = 0 ; i < N ; i++ , cout << endl )
		for(int j = 0 ; j < M ; j++ ) cout << vertGroup[i][j] <<" " ;
	cout << endl ;
 
	cout << "Distancias: \n" ;
	for(int i = 1 ; i <= Node ; i++ ) cout << distGroups[i] <<" " ;
	cout << endl ;
}
 
int main(){
	ios_base::sync_with_stdio(false) ;
	cin.tie(0) ;
 
	cin >> N >> M ;
	for(int i = 0 ; i < N ; i++ )
		for(int j = 0 ; j <M ; j++ ) cin >> grid[i][j] ;
 
	for(int i = 0 ; i <N ; i++ ){
		lastGroup = -1 ;
		for(int j = 0 ; j <M ; j++ ){
			if( grid[i][j] == 'I' ) lastGroup = -1 ;
			else {
				if( lastGroup == -1 ) lastGroup = ++Node ;
				horGroup[i][j] = lastGroup ;
			}
		}
	}
 
	for(int i = 0 ; i < M ; i++ ){
		lastGroup = -1 ;
		for(int j = 0 ; j < N ; j++ ){
			if(grid[j][i] == 'I' ) lastGroup = -1 ;
			else {
				if( lastGroup == -1 ) lastGroup = ++Node ;
				vertGroup[j][i] = lastGroup ;
			}
		}
	}
 
	for(int i = 1 ; i <= Node ; i++ ) distGroups[i] = inf ;
 
	pair<int,int> S , T , V ;
	for(int i = 0 ; i < N ; i++ )
		for(int j= 0 ; j < M ; j++ ){
			if( grid[i][j] == 'Y' ) S = make_pair(i,j) ;
			if( grid[i][j] == 'T' ) T = make_pair(i,j) ;
			if( grid[i][j] == 'V' ) V = make_pair(i,j) ;
		}
 
	bfsViking(V) ;
	cout << ( bfsYou(S,T) ? "YES" : "NO" ) << "\n" ;
 
//	debug() ;
}
