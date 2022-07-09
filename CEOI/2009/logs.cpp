#include <bits/stdc++.h>

#define ll long long

const int MAXN = 15010;
const int MAXM = 1505;
const int sq = 63;

using namespace std;

int N, M, ans;
int grid[MAXM];
int ini[MAXN], fim[MAXN];
int bucket[MAXN];
int freq[MAXN];
ll ligados[MAXN];

void makeBuckets(){
	for(int i = 0, b = sq, k = 0; i <= N; i++, b++){
		if(b == sq){
			b = 0;
			ini[++k] = i;
		}

		bucket[i] = k;
		fim[k] = i;
	}
}

int getPos(int val){
	return val-ini[bucket[val]];
}

void op(int pos, int val){
	if(freq[pos]){
		ligados[bucket[pos]] ^= 1LL<<getPos(pos);
	}

	freq[pos] += val;
	
	if(freq[pos]){
		ligados[bucket[pos]] |= 1LL<<getPos(pos);
	}
}

int calc(){
	int tempAns = 0;
	int s = 0;

	for(int i = bucket[N]; i > 0; i--){
		ll aux = ligados[i];

		while(aux){
			int cur = 63-__builtin_clzll(aux);
			aux ^= (1LL<<cur);

			cur += ini[i];
			s += freq[cur];

			tempAns = max(tempAns, s * cur );
		}
	}

	return tempAns;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> M;

	makeBuckets();

	for(int i = 1; i <= M; i++)
		op(0,1);

	for(int i = 1; i <= N; i++){
		string str;
		cin >> str;

		for(int j = 1; j <= M; j++){
			op(grid[j], -1);
			
			if(str[j-1] == '0'){
				grid[j] = 0;
			}
			else grid[j]++;

			op(grid[j],1);
		}

		ans = max(ans, calc());
	}

	cout << ans << "\n";
}
