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

void solve() {
    ll n,m,x,y;
    cin >> n >> m;
    vector<vector<char>> v(n, vector<char>(m));
    fi(i,0,n) fi(j,0,m) {
        cin >> v[i][j];
        if(v[i][j] == 'S') x=i, y=j;
    }

    ll dis[n][m][4][4];
    fi(i,0,n) fi(j,0,m) fi(d,0,4) fi(c,0,4) dis[i][j][d][c] = LLONG_MAX;

    using State = array<ll,5>; // {dist, x, y, dir, cnt}
    priority_queue<State, vector<State>, greater<State>> pq;

    vector<pair<int,int>> dir = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    fi(d,0,4) {
        dis[x][y][d][0] = 0;
        pq.push({0,x,y,d,0});
    }

    ll ans = LLONG_MAX;
    while(!pq.empty()){
        auto [d, cx, cy, cd, cnt] = pq.top();
        pq.pop();
        if(d != dis[cx][cy][cd][cnt]) continue;
        if(v[cx][cy] == 'T'){ ans = d; break; }

        fi(i,0,4){
            ll nx = cx + dir[i].first;
            ll ny = cy + dir[i].second;
            if(nx<0 || ny<0 || nx>=n || ny>=m || v[nx][ny]=='#') continue;

            ll nd, ncnt;
            if(i == cd){
                if(cnt == 3) nd = d+3, ncnt = 2;
                else nd = d+1, ncnt = cnt+1;
            } else nd = d+1, ncnt = 1;

            if(nd < dis[nx][ny][i][ncnt]){
                dis[nx][ny][i][ncnt] = nd;
                pq.push({nd,nx,ny,i,ncnt});
            }
        }
    }

    cout << (ans==LLONG_MAX ? -1 : ans);
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