#include <bits/stdc++.h>

const int MAXN = 110;
const int8_t inf = 105;

using namespace std;

int N, A;
int X[MAXN], Y[MAXN];
vector<int> x, y;
vector<int> freqx[MAXN];
uint8_t dp[MAXN][MAXN][MAXN];

int getMax(int l){
	return freqx[l].empty() ?
				-1 : freqx[l].back();
}

int makeCalculation(int l, int r){
	int base = max(x[--r]-x[--l],1);
	int h = A/base;

	return upper_bound(y.begin(),y.end(), h)-y.begin();
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	/*freopen("photo.in", "r", stdin);
	freopen("photo.out", "w", stdout); */

	cin >> N >> A;
	for(int i = 1; i <= N; i++){
		cin >> X[i] >> Y[i];

		x.push_back(X[i]);
		y.push_back(Y[i]);
	}

	sort(x.begin(),x.end());
	sort(y.begin(),y.end());

	x.erase(unique(x.begin(),x.end()), x.end());
	y.erase(unique(y.begin(),y.end()), y.end());

	for(int i = 1; i <= N; i++){
		X[i] = lower_bound(x.begin(),x.end(), X[i])-x.begin()+1;
		Y[i] = lower_bound(y.begin(),y.end(), Y[i])-y.begin()+1;
		freqx[X[i]].push_back(Y[i]);
	}

	for(int i = 1; i <= x.size(); i++) 
		sort(freqx[i].begin(), freqx[i].end());

	for(int i = y.size(); i > 0; i--){
		for(int diff = 0; 1+diff <= x.size(); diff++)
			for(int l = 1, r = 1+diff; r <= x.size(); l++, r++){
				dp[i][l][r] = inf;


				if(getMax(l) < i){
					dp[i][l][r] = dp[i][l+1][r];
					continue;
				}
				if(getMax(r) < i){
					dp[i][l][r] = dp[i][l][r-1];
					continue;
				}

				int stops = makeCalculation(l,r);

				if(stops+1 > i)
					dp[i][l][r] = dp[stops+1][l][r]+1;

				for(int corte = l; corte+1 <= r; corte++){
					uint8_t res = dp[i][l][corte];
					res += dp[i][corte+1][r];

					dp[i][l][r] = min(dp[i][l][r], res );
				}
			}
		}

	int ans = dp[1][1][x.size()];

	cout << ans << "\n"; 
}
