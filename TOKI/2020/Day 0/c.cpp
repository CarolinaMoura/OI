#include <bits/stdc++.h>

using namespace std ;

int k , n ;

int resto(int i, int j) 
{
	int r = (j-i)%(n+1) ;
	if(r < 0) r += n+1 ;
	return r ;
}

int main()
{
	ios_base::sync_with_stdio(false) ;
	cin.tie(NULL) ;

	cin >> k >> n ;
	vector<int> a(2,0) ;
	for(int i = 0 ; i < k ; i++ ) cin >> a[i] ;

	while(true)
	{
		int pilha = -1 ;
		int qtd = -1 ;

		//Testa se consigo tirar da primeira
		if( ( n+1-resto(a[0],a[1]) ) <= a[0]) 
		{
			int toTake = n+1 - resto(a[0],a[1]) ;
			cout << "1 " << toTake << endl ;
			a[0] -= toTake ;
		}
		else cout << "2 " << resto(a[0],a[1]) << endl , a[1] -= resto(a[0],a[1]) ;

		cin >> pilha >> qtd ;
		if(pilha == -1) break ;

		a[pilha-1] -= qtd ;

	}

}
