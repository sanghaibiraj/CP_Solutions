#include <bits/stdc++.h>
#define ll long long int
#define cout(a) cout << (a) << endl
#define nl cout << endl
#define fi(i,s,e) for(int i=s;i<e;i++)
#define ain(i,arr,n); for(int i=0;i<n;i++){ cin >> arr[i];}
#define vl vector<ll>
#define vi vector<int>
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vpll vector<pair<ll, ll>>
#define si set<int>
#define sc set<char>
#define pb push_back
#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

using namespace std;

const ll mod = 1e9+7;
/*dfs */
// void dfs(int vertex){
//     //Take action on vertex after entering the vertex
//     vis[vertex]=1;
//     for(int child :g[vertex]){
//         //Take action on child before entering the child node
//         if(vis[child])continue;
//         dfs(child);
//         // Take action on child after exiting the child node
//     }
//     // Take action on vertex before exiting the vertex
// }
const int dsu_N = 1e4;
int dsu_parent[dsu_N];
int dsu_Size[dsu_N];
void make(int v){
  dsu_parent[v]=v;
  dsu_Size[v]=1;
}
int find(int v){
  if(v == dsu_parent[v]) return v;
  return dsu_parent[v]=find(dsu_parent[v]);
}
void Union(int a, int b){
  a=find(a);
  b=find(b);
  if(a!=b){
    if(dsu_Size[a]<dsu_Size[b]) swap(a,b);
    dsu_parent[b] = a;
    dsu_Size[a]+=dsu_Size[b];
  }
}
bool prime(ll n){
  if (n < 2) return false;
  if (n <= 3) return true;
  if (n % 2 == 0 || n % 3 == 0) return false;
  for (int i=5; i * i <= n; i += 6)
    if (n % i == 0 || n % (i+2) == 0)
      return false;
  return true;
}
ll power(ll a, ll b){
  ll res =1;
  while(b>0){
    if(b%2==1)
      res = ((res%mod) * (a%mod))%mod;
    a = ((a%mod)*(a%mod))%mod;
    b /= 2;
  }
  return res%mod;
}
ll mod_inv(ll a) {
    return power(a, mod - 2);
}

void dfs(ll u, ll par, ll xr, ll tar, set<ll>& s, vector<vpll>& gr){
    if(u==tar) return;
    s.insert(xr);
    for(auto i: gr[u]){
        if(i.first == par) continue;
        dfs(i.first, u, xr^i.second, tar, s, gr);
    }
}

bool dfs2(ll u, ll par, ll xr, set<ll>& s, ll tar, vector<vpll>& gr){
    if(u!=tar && s.find(xr)!=s.end()) return 1;
    for(auto i: gr[u]){
        if(i.first==par) continue;
        if(dfs2(i.first, u, xr^i.second, s, tar, gr)) return 1;
    }
    return 0;
}

void solve(){
  ll n, a, b;
  cin >> n >> a >> b;
  vector<vpll> gr(n+1);
  fi(i,0,n-1){
    ll u,v,w;
    cin >> u >> v >> w;
    gr[u].pb({v,w});
    gr[v].pb({u,w});
  }
  set<ll> s;
  dfs(a, -1, 0, b, s, gr);
  if(dfs2(b, -1, 0, s, b, gr)) cout("YES");
  else cout("NO");
}
int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t=1;
  cin >> t;
  while(t--){
    solve();
  }
}