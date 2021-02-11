#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
int n, logn;
int q;
const int MaxN = 1e5 + 1;
const int MaxLogN = 17;
vector<vi> lista(MaxN);
vi edad(MaxN);
int dp[MaxN][MaxLogN];
vector<vector<int>> fiesta(MaxN);
vector<int> invitado(MaxN);


struct Ft{
        vector<int> ft;
        Ft(int l){
                ft.assign(l+1, 0);
        }
        ll sum(int b){
                ll s = 0;
                while(b > 0){
                        s += ft[b];
                        b -= b & -b;
                }
                return s;
        }
	ll rmq(int a, int b){
		if(a - 1 >=0) return sum(b) - sum(a-1);
		return sum(b);
	}
        void upd(int k, int v){
                while(k < (int)ft.size()){
                        ft[k] += v;
                        k += k & -k;
                }
        }
};

Ft fe(MaxN);
void dfs(int u, int p){
	dp[u][0] = p;
	for(int i=1; i<logn; i++){
		dp[u][i] = dp[ dp[u][i-1] ][i-1];
	}
	for(int i=0; i<(int)lista[u].size(); i++){
		int v = lista[u][i];
		if(v == p) continue;
		dfs(v,u);
	}
}

void cont(int u, int p){
	for(int i=0; i<(int)fiesta[u].size(); i++){
		int ed_minima = fiesta[u][i];
		fe.upd(ed_minima, 1);
	}
	invitado[u] += fe.rmq(1,edad[u]);
	for(int i=0; i<(int)lista[u].size(); i++){
		int v = lista[u][i];
		if(v == p) continue;
		cont(v,u);
	}
	for(int i=0; i<(int)fiesta[u].size(); i++){
		int ed_minima = fiesta[u][i];
		fe.upd(ed_minima, -1);
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int e,p;
	cin >> n >> q;
	logn = ceil(log2(n));
	for(int i=1; i<=n; i++){
		cin >> e >> p;
		edad[i] = e;
		lista[i].push_back(p);
		lista[p].push_back(i);
	}
	dfs(1,1);
	int l,r;
	for(int i=1; i<=q; i++){
		cin >> p >> l >> r;
		for(int i=logn - 1; i>=0 ; --i){
			if(edad[dp[p][i]] <= r){
				p = dp[p][i];
			}
		}
		fiesta[p].push_back(l);
	}
	cont(1,1);
	for(int i=1; i<=n; i++){
		cout << invitado[i] << " ";
	}
	cout << "\n";
	return 0;
}

