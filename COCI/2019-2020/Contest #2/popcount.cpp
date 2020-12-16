#include <bits/stdc++.h>

#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size() )

const int MAX = 510 ;

using namespace std ;

struct Bignum
{

	vector<int> a ;

	Bignum operator + (Bignum other) const 
	{

		Bignum aux ;

		for(int i = 0, carry = 0 ; i < max(sz(other.a), sz(a) ) || carry ; i++ )
		{
			int myContribution = ( i >= sz(a) ) ? 0 : a[i] ;
			int otherContribution = ( i >= sz(other.a) ) ? 0 : other.a[i] ;

			aux.a.push_back( myContribution + otherContribution + carry ) ;

			if( aux.a.back() > 9 )
			{
				carry = 1 ;
				aux.a.back() -= 10 ;
			}
			else carry = 0 ;

		}

		return aux ;

	}

	void print()
	{
		for(int i = sz(a)-1 ; i >= 0 ; i-- ) printf("%d", a[i] ) ;
	}

} ;

int N , K ;
Bignum pot[MAX] ;

int main()
{
	scanf("%d %d", &N , &K ) ;

	pot[0].a.push_back(1) ;
	for(int i = 1 ; i < N ; i++ ) pot[i] = pot[i-1] + pot[i-1] ;

	int cnt = 0 ;
	for(int qtd = N ; qtd > 1 ; qtd = (qtd+1)>>1 ) { cnt++ ; } 

	printf("%d\n", cnt ) ;

	for(int qtd = N , i = 1 ; qtd > 1 ; qtd = (qtd+1)>>1 , i<<=1 )
	{
		Bignum num ;	

		for(int j = 0 ; j < N ; j += i<<1 )
		{
			for(int g = 0 ; g < i && j+g < N ; g++  )
				num = num + pot[ g+j ] ;

		} 

		printf("A=((A&") ; num.print() ;
		printf(")+((A>>%d)&" , i) ; num.print() ;
		printf("))\n") ;

	} 
}
