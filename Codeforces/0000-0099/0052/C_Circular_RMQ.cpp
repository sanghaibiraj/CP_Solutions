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

void buildTree(vl& segTree, vl& v, ll l, ll r, ll i){
    if(l==r){
        segTree[i] = v[l];
        return;
    }
    ll mid = l+(r-l)/2;
    buildTree(segTree, v, l, mid, i*2+1);
    buildTree(segTree, v, mid+1, r, i*2+2);
    segTree[i] = min(segTree[2*i+1], segTree[2*i+2]);
}

ll query(vl& segTree, vl& lazy, ll l, ll r, ll i, ll a, ll b){
    if(lazy[i]){
        segTree[i] += lazy[i];
        if(l!=r){
            lazy[2*i+1] += lazy[i];
            lazy[2*i+2] += lazy[i];
        }
        lazy[i]=0;
    }
    if(b<l || a>r) return LLONG_MAX;
    if(l>=a && r<=b) return segTree[i];
    ll mid = l+(r-l)/2;
    return min(query(segTree, lazy, l, mid, i*2+1, a, b), query(segTree, lazy, mid+1, r, i*2+2, a, b));
}

void update(vl& segTree, vl& lazy, ll l, ll r, ll i, ll a, ll b, ll c){
    if(lazy[i]){
        segTree[i] += lazy[i];
        if(l!=r){
            lazy[2*i+1] += lazy[i];
            lazy[2*i+2] += lazy[i];
        }
        lazy[i]=0;
    }
    if(b<l || a>r) return;
    if(l>=a && r<=b){
        // cout(segTree[i]);
        segTree[i] += c;
        if(l!=r){
            lazy[2*i+1] += c;
            lazy[2*i+2] += c;
        }
        return;
    }
    ll mid = l + (r-l)/2;
    update(segTree, lazy, l, mid, i*2+1, a, b, c);
    update(segTree, lazy, mid+1, r, i*2+2, a, b, c);
    segTree[i] = min(segTree[2*i+1], segTree[2*i+2]);
}

void solve(){
    ll n;
    cin >> n;
    vl v(n);
    ain(i,v,n);
    vl segTree(4*n);
    vl lazy(4*n, 0);
    buildTree(segTree, v, 0, n-1, 0);    
    ll q;
    cin >> q;
    while(q--){
        ll a,b,c;
        if (cin.peek() == '\n') cin.ignore();
        string line;
        getline(cin, line);
        stringstream ss(line);
        vl vals;
        ll v;
        while (ss >> v) vals.push_back(v);
        a=vals[0];
        b=vals[1];
        if (vals.size() == 2) {
            if(b>=a) cout(query(segTree, lazy, 0, n-1, 0, a, b));
            else{
                ll q1 = query(segTree, lazy, 0, n-1, 0, a, n-1);
                ll q2 = query(segTree, lazy, 0, n-1, 0, 0, b);
                cout(min(q1, q2));
            }
        } 
        else {
            c=vals[2];
            if(b>=a) update(segTree, lazy, 0, n-1, 0, a, b, c);
            else{
                update(segTree, lazy, 0, n-1, 0, a, n-1, c);
                update(segTree, lazy, 0, n-1, 0, 0, b, c);
            }
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