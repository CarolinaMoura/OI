#include <bits/stdc++.h>

using namespace std ;

int N ;
int freq[3] ;

int main()
{
	scanf("%d", &N) ;

	vector<int> color(N) , nxt(N) , prev(N) ;

	for(int i = 0 ; i < N ; i++ )
	{
		char c ;
		scanf(" %c", &c ) ; 

		color[i] = c-'1' ;
		freq[ color[i] ]++ ;

		nxt[i] = (i == N-1) ? 0 : (i+1) ;
		prev[ nxt[i] ] = i ;
	}

	for(int i = 0 ; i < 3 ; i++ )
		if(freq[i] > N-2 || (N-2-freq[i])&1 )
		{
			printf("NE\n") ;
			return 0 ;
		}
	
	printf("DA\n") ;

	vector< tuple<int,int,int> > ans ;

	int cur = 1 ;

	while(N > 3 )
	{
		int mostFrequent = (freq[0] > freq[1] ) ? 0 : 1 ;
		mostFrequent = (freq[mostFrequent] > freq[2] ) ? mostFrequent : 2 ;

		if( color[cur] != color[ nxt[cur] ] && (color[cur] == mostFrequent || color[nxt[cur] ] == mostFrequent) )
		{
//			printf("%d %d %d %d %d\n", cur, nxt[cur], nxt[nxt[cur] ] , color[cur] , color[nxt[cur] ] ) ;

			freq[ color[cur] ]-- ;
			freq[ color[nxt[cur] ] ]-- ;

			color[cur] = 3 - color[cur] - color[ nxt[cur] ] ;
			nxt[cur] = nxt[ nxt[cur] ] ;
			prev[ nxt[cur] ] = cur ;

			ans.push_back( make_tuple(cur, nxt[cur] , color[cur] ) ) ;

			freq[color[cur] ]++ ;
			cur = prev[cur] ;
			N-- ;
		}
		else cur = nxt[cur] ;

	}

	for(auto e : ans ) printf("%d %d %d\n", get<0>(e)+1 , get<1>(e)+1, get<2>(e)+1 ) ;

}
