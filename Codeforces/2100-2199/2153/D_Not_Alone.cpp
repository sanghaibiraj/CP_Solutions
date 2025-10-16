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

vl dp;
vl cur;

ll dprec(ll i){
    ll n = cur.size();
    if(i>=n) return 0;
    if(i==n-1) return 1e18;
    if(dp[i]!=-1) return dp[i];
    ll ans = 1e18;
    if(i+1<n){
        ans = min(ans, abs(cur[i]-cur[i+1])+dprec(i+2));
    }
    if(i+2<n){
        ll mx = max({cur[i], cur[i+1], cur[i+2]});
        ll mn = min({cur[i], cur[i+1], cur[i+2]});
        ans = min(ans, mx-mn+dprec(i+3));
    }
    return dp[i]=ans;
}

ll dpsolve(vl& v){
    cur = v;
    dp.assign(v.size(), -1);
    return dprec(0);
}

void solve(){
  ll n;
  cin >> n;
  vl v(n);
  ain(i,v,n);
  ll ans = LLONG_MAX;
  ans = min(ans, dpsolve(v));
  if(n>=2){
    vl tmp(v.begin() + 1, v.begin() + n - 1);
    ans = min(ans, abs(v[n-1]-v[0])+dpsolve(tmp));
  }
  if(n>=3){
    vl tmp(v.begin() + 1, v.begin() + n - 2);
    ll mx = max({v[0], v[n-2], v[n-1]});
    ll mn = min({v[0], v[n-2], v[n-1]});
    ans = min(ans, mx-mn+dpsolve(tmp));

    vl tmp2(v.begin() + 2, v.begin() + n - 1);
    ll mx2 = max({v[0], v[1], v[n-1]});
    ll mn2 = min({v[0], v[1], v[n-1]});
    ans = min(ans, mx2-mn2+dpsolve(tmp2));
  }
  cout(ans);
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