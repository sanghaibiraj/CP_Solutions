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

ll ncr(ll n, ll r){
    if(r<0) return 0;
    ll numerator=1, denominator=1;
    for(ll i=0;i<r;i++){
        numerator = (numerator * ((n - i + mod) %mod))%mod;
        denominator = (denominator * ((i + 1 + mod) %mod))%mod;
    }
    return (numerator * mod_inv(denominator))%mod;
}

void rec(ll n, ll a, ll b, vpll &fac, ll &ans, ll idx, ll curr_a, ll curr_b){
    if(idx==fac.size()){
        ans = (ans+curr_b)%mod;
        return;
    }
    ll p = fac[idx].ff, e=fac[idx].ss;
    ll pow = 1;
    vl tmp(e+1), tmp2(e+1);
    fi(i,0,e+1){
        tmp[i] = ncr(n+i-1, i);
        tmp2[i] = ncr(n+e-i-1, e-i);
    }
    fi(i,0,e+1){
        bool flag=0;
        if(pow>0 && curr_a>0 && pow>LLONG_MAX/curr_a) flag=1;
        if(flag || curr_a*pow > a) break;
        ll new_a = curr_a*pow;
        ll new_b = (curr_b * ((tmp[i]*tmp2[i])%mod) )%mod;
        rec(n, a, b, fac, ans, idx+1, new_a, new_b);
        if(i<e){
            if(pow>LLONG_MAX/p) break;
            pow = pow * p;
        }
    }
}

void solve(){
    ll n,a,b;
    cin >> n >> a >> b;
    ll i=2;
    vpll fac;
    while(i*i<=b){
        if(b%i==0){
            ll c=0;
            while(b%i==0){
                c++;
                b/=i;
            }
            fac.pb({i,c});
        }
        i++;
    }
    if(b>1) fac.pb({b,1});
    ll ans=0;
    rec(n,a,b,fac,ans,0,1,1);
    cout(ans);
}
int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t=1;
  cin >> t;
  for(int i=1;i<=t;i++){
    cout << "Case #" << i << ": ";
    solve();
  }
}