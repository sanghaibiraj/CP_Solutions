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

int calc(vector<int>& v, vector<vector<int>>& dp, int idx, int pre){
    if(idx==v.size()) return 0;
    if(dp[idx][pre] != -1) return dp[idx][pre];
    int gym = calc(v, dp, idx+1, 1);
    int con = calc(v, dp, idx+1, 2);
    int rest = 1+calc(v, dp, idx+1, 0);
    if(pre==0){
        if(v[idx]==1) rest = min(rest, con);
        else if(v[idx]==2) rest=min(rest,gym);
        else if(v[idx]==3) rest = min(rest, min(gym,con));
    }
    else if(pre==1){
        if(v[idx]==1 || v[idx]==3) rest = min(rest, con);
    }
    else{
        if(v[idx]==2 || v[idx]==3) rest = min(rest, gym);
    }
    return dp[idx][pre] = rest;
}

void solve(){
  ll n;
  cin >> n;
  vector<int> v(n);
  ain(i,v,n);
  vector<vector<int>> dp(n, vector<int>(3,-1));
  int ans = calc(v, dp, 0, 0);
  cout(ans);
}

// v - 0 - no gym no contest
// 1 - no gym, yes contest
// 2 - gym open, no contest
// 3 - gym open, yes contest

// pre - 0 - rest
// 1 - gym
// 2 - contest

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t=1;
//   cin >> t;
  while(t--){
    solve();
  }
}