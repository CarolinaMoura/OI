#include "brperm.h"
#include <bits/stdc++.h>

#define all(x) (x.begin(),x.end())
#define ll long long

const ll PRIME = 37LL;
const ll MOD = 1e9+7;
const int LOG = 25;
const int MAXN = 5e5+10;

using namespace std;

ll dp[LOG][MAXN];
ll invPot[LOG][MAXN], sv[LOG][MAXN], pot2[LOG][MAXN];
int token;
int N;

void init(int n, const char s[]) {

  N = n;

  token = 0;
  while((1<<token) <= n)
    token++;

  token--;

  pot2[0][0] = PRIME;
  for(int j = 1; j <= N; j++)
    pot2[0][j] = (pot2[0][j-1] * PRIME) % MOD;

  for(int i = 1; i <= token; i++){
    pot2[i][0] = (pot2[i-1][0]*pot2[i-1][0])%MOD;
    for(int j = 1; j <= N; j++)
      pot2[i][j] = (pot2[i][j-1] * pot2[i][0] ) % MOD;
  }

  for(int i = 0; i <= token; i++){
    for(int j= n-1; j >= 0; j--){
      sv[i][j] = (sv[i][j+1]*pot2[i][0])%MOD;
      sv[i][j] += s[j]-'a'+1;
      if(sv[i][j] >= MOD)
        sv[i][j] -= MOD;
    }
  }

  for(int i = 0; i < n; i++)
    dp[0][i] = s[i]-'a'+1;  

  for(int i = 1; i <= token; i++)
    for(int j= 0; j+(1<<i)-1 < N; j++){
      dp[i][j] = dp[i-1][j];
      ll toSum = (dp[i-1][j+(1<<(i-1))]*pot2[token-i][0]) % MOD;
      dp[i][j] += toSum;
      if(dp[i][j] >= MOD)
        dp[i][j] -= MOD;
    }
}

int query(int i, int k) {
    
    int l = i, r = (1<<k)+l-1;

    if(r >= N){
      return 0;
    }

    ll hashSeq = sv[token-k][l]-((sv[token-k][r+1]*pot2[token-k][r-l])%MOD);
    hashSeq %= MOD;
    hashSeq += MOD;
    hashSeq %= MOD;

    return hashSeq == dp[k][l];
}
