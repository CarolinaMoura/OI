#include <bits/stdc++.h>

#define ll long long

const int MAXN = 3e5+10;
const int LOG = 25;

using namespace std;

int N, T;
ll arr[MAXN], v[MAXN];
ll diffArray[MAXN];
ll dp[MAXN];
int binLift[LOG][MAXN];

int calcDp(int i, int j){
	if(binLift[i][j] != -1)
		return binLift[i][j];
	if(j == 0) 
		return 0;

	int id = calcDp(i-1,j)-1;


	if(id <= 0){
		return binLift[i][j] = 0;
	}

	if(v[j] == 0 || v[id] == 0)
		return binLift[i][j] = 0;

	if((v[id] < 0) != (v[j] < 0))
		return binLift[i][j] = 0;

	ll curNum = v[j]*(1LL<<(i-1));
	ll jump = curNum/v[id];
	
	if(v[id] * jump != curNum)
		return binLift[i][j] = 0;

	if(__builtin_popcountll(jump) != 1)
		return binLift[i][j] = 0;

	int qtd = 63-__builtin_clzll(jump);

	if(qtd >= LOG)
		return binLift[i][j] = 0;

	return binLift[i][j] = calcDp(qtd,id);
}

void solveTestCase(){
	cin >> N;
	for(int i = 1; i <= N; i++)
		cin >> arr[i];
	for(int i = 1; i < N; i++)
		diffArray[i] = arr[i+1]-arr[i];

	int ptr = 0;
	for(int i = 1; i < N; i++){
		if(ptr && v[ptr] == 0 && diffArray[i] == 0){
			continue;
		}

		v[++ptr] = diffArray[i];
	}

	N = ptr;

	for(int i = 0; i < LOG; i++)
		for(int j= 1; j <= N; j++)
			binLift[i][j] = -1;

	for(int i = 1; i <= N; i++)
		binLift[0][i] = i;

	dp[0] = 0;
	dp[1] = 1;
	for(int i = 2; i <= N; i++){
		dp[i] = 1+dp[i-1];
		for(int j = 0; j < LOG; j++){
			if(calcDp(j,i) == 0)
				break;
		//	cout << j << " " << i << " " << binLift[j][i] << endl;
			dp[i] = min(dp[i], dp[binLift[j][i]-1]+1);
		}
	}

	cout << dp[N]+1 << "\n";
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> T;
	while(T--){
		solveTestCase();
	}
}
