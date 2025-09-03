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

void buildTree(vl& segTreeMax, vl& segTreeSum, vl& v, ll l, ll r, ll i){
    if(l==r){
        segTreeMax[i] = v[l];
        segTreeSum[i] = v[l];
        return;
    }
    ll mid = l+(r-l)/2;
    buildTree(segTreeMax, segTreeSum, v, l, mid, i*2+1);
    buildTree(segTreeMax, segTreeSum, v, mid+1, r, i*2+2);
    segTreeMax[i] = max(segTreeMax[2*i+1], segTreeMax[2*i+2]);
    segTreeSum[i] = segTreeSum[2*i+1] + segTreeSum[2*i+2];

}

void countFactors(vl& factors){
    for(int i=2;i<=1e6;i++){
        for(int j=i;j<=1e6;j+=i){
            factors[j]++;
        }
    }
}

void replace(vl& segTreeMax, vl& segTreeSum, vl& factors, ll l, ll r, ll a, ll b, ll i){
    if(b<l || a>r) return;
    if(segTreeMax[i] < 3) return;
    if(l==r){
        segTreeMax[i] = factors[segTreeMax[i]];
        segTreeSum[i] = factors[segTreeSum[i]];
        return;
    }
    ll mid = l+(r-l)/2;
    replace(segTreeMax, segTreeSum, factors, l, mid, a, b, i*2+1);
    replace(segTreeMax, segTreeSum, factors, mid+1, r, a, b, i*2+2);
    segTreeMax[i] = max(segTreeMax[2*i+1], segTreeMax[2*i+2]);
    segTreeSum[i] = segTreeSum[2*i+1] + segTreeSum[2*i+2];
}

ll query(vl& segTreeSum, ll a, ll b, ll l, ll r, ll i){
    if(b<l || a>r) return 0;
    if(l>=a && r<=b) return segTreeSum[i];
    ll mid = l+(r-l)/2;
    return query(segTreeSum, a, b, l, mid, i*2+1) + query(segTreeSum, a, b, mid+1, r, i*2+2);
}

void solve(){
    ll n,m;
    cin >> n >> m;
    vl v(n);
    ain(i,v,n);
    vl segTreeMax(4*n);
    vl segTreeSum(4*n);
    buildTree(segTreeMax, segTreeSum, v, 0, n-1, 0);
    vl factors(1e6+2, 1);
    countFactors(factors);
    fi(i,0,m){
        ll x,a,b;
        cin >> x >> a >> b;
        a--; b--;
        if(x==1){
            replace(segTreeMax, segTreeSum, factors, 0, n-1, a, b, 0);
        }
        else{
            ll ans = query(segTreeSum, a, b, 0, n-1, 0);
            cout(ans);
        }
    }
}
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