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

void solve(){
  ll n,m,k;
  cin >> n >> m >> k;
  vector<vl> v(n, vl(m));
  fi(i,0,n){
    fi(j,0,m) cin >> v[i][j];
  }
  vector<string> s(n);
  fi(i,0,n) cin >> s[i];
  ll h1=0, h0=0;
  fi(i,0,n){
    fi(j,0,m){
        if(s[i][j] == '0') h0 += v[i][j];
        else h1 += v[i][j];
    }
  }
  if(h0 == h1){
    cout("YES");
    return;
  }
  ll h = abs(h0-h1);
  vector<vl> cnt(n, vl(m,0));
  fi(i,0,n){
    fi(j,0,m){
        if(s[i][j]=='1') cnt[i][j]++;
        if(i>0) cnt[i][j] += cnt[i-1][j];
        if(j>0) cnt[i][j] += cnt[i][j-1];
        if(i>0 && j>0) cnt[i][j] -= cnt[i-1][j-1];
    }
  }
  ll g=0;
  fi(i,k-1,n){
    fi(j,k-1,m){
        ll x = cnt[i][j];
        if(i-k>=0) x-=cnt[i-k][j];
        if(j-k>=0) x-=cnt[i][j-k];
        if(i-k>=0 && j-k>=0) x+=cnt[i-k][j-k];
        x = abs(k*k-2*x);
        g = __gcd(g,x);
    }
  }
  if(g==0 || h%g!=0) cout("NO");
  else cout("YES");
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