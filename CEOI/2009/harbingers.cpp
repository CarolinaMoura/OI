#include <bits/stdc++.h>

#define ll long long

const ll inf = 1e18+10LL;
const int MAXN = 1e5+10;

using namespace std;

struct Ponto{
	ll x, a, b;

	Ponto(ll x = 0, ll a = 0, ll b = 0):
		a(a), b(b), x(x) {}
} ds[MAXN];

struct Antigo{
	Ponto ant;
	int r;

	Antigo(Ponto ant = Ponto(0,0,0), int r = 0):
		ant(ant), r(r) {}

} v[MAXN];

int N;
int l = 1, r = 0;
ll pref[MAXN], dp[MAXN];
vector<pair<int,int> > adj[MAXN];
ll S[MAXN], V[MAXN];

ll teto(ll num, ll den){
	assert(den > 0);
	return (num+den-1)/den;
}

Antigo insere(ll a, ll b){
	int lo = 0, hi = r, mid;
	Antigo ret;

	while(lo < hi){
		mid = (lo+hi+1)>>1;
		ll x = ds[mid].x;

		if(a*x + b <= ds[mid].a*x + ds[mid].b){
			hi = mid-1;
		}
		else lo = mid;
	}

	if(lo == 0){
		ret = Antigo(ds[1], r);
		l = r = 1;
		ds[1] = Ponto(0,a,b);
	}
	else{
		ret = Antigo(ds[++lo], r);
		r = lo;
		ll x = teto(b-ds[r-1].b, ds[r-1].a-a);
		ds[r] = Ponto(x, a,b);
	}

	return ret;
}

ll getAnswer(ll x){
	if(r == 0) return inf;

	int lo = l, hi = r, mid;
	
	while(lo < hi){
		mid = (lo+hi+1)>>1;

		if(ds[mid].x <= x){
			lo = mid;
		}
		else hi = mid-1;
	}

	return ds[lo].a * x + ds[lo].b;
}

void dfs(int x, int par){

	if(x != 1){
		dp[x] = min(0LL,getAnswer(V[x]))+V[x]*pref[x]+S[x];
		v[x] = insere(-pref[x], dp[x]);
	}

	for(auto &e: adj[x]){
		if(e.first == par)
			continue;

		pref[e.first] = pref[x]+e.second;

		dfs(e.first, x);
	}

	ds[r] = v[x].ant;
	r = v[x].r;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;

	for(int i = 0, a, b, c; i < N-1; i++){
		cin >> a >> b >> c;

		adj[a].push_back(make_pair(b,c));
		adj[b].push_back(make_pair(a,c));
	}

	for(int i = 2; i <= N; i++){
		cin >> S[i] >> V[i];
	}

	dfs(1,-1);

	for(int i = 2; i <= N; i++)
		cout << dp[i] << " ";

	cout << "\n";
}
