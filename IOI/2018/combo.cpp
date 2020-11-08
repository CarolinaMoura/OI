#include <bits/stdc++.h>
#include "combo.h"
 
#define debug 
#define lp(i,a,b) for(int i=a;i<b;i++)
#define pii pair<int,int>
#define ll long long
#define ff first
#define ss second
#define pb push_back
#define mk make_pair
 
const int MAXN = 2e3+10 ;
 
using namespace std ;
 
int n ;
 
string guess_sequence(int n)
{
 
  string p ;
  int firstLetter ;
  char c[4] = {'A' , 'B' , 'X' , 'Y'} ;
 
  p.resize( n ) ;
 
  //Find first letter
  string p1 = "AB" , p2 = "XY" ;
  if( press(p1) != 0 )
  {
    firstLetter = 0 ;
    p1 = "B" ;
    if( press(p1) != 0 ) firstLetter = 1 ;
  }
  else
  {
    firstLetter = 2 ;
    p2 = "Y" ;
    if( press(p2) != 0 )  firstLetter = 3 ;
  }
  p = c[firstLetter] ;
  swap( c[firstLetter] , c[0] ) ;
 
  if( n == 1 ) return p ;
 
  lp(i,2,n)
  {
 
    string aux = p + c[2] ;
 
    lp(j,1,4) aux = aux +  p + c[1] + c[j] ;
 
    int newVal = press(aux) ;
 
    if(newVal == i) p += c[2] ;
    else if( newVal == i+1 ) p += c[1] ;
    else p += c[3] ;
 
  }
 
  string aux = p + c[1] ;
 
  if( press(aux) == n ) return aux ;
 
  aux = p + c[2] ;
 
  if(press(aux) == n) return aux ;
 
  p += c[3] ;
 
  return p ;
 
}
