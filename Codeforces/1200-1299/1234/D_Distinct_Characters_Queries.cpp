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

void buildTree(vector<vector<int>>& segTree, string& s, int l, int r, int i){
    if(l==r){
        segTree[i][s[l]-'a']=1;
        return;
    }
    int mid = l + (r-l)/2;
    buildTree(segTree, s, l, mid, i*2+1);
    buildTree(segTree, s, mid+1, r, i*2+2);
    for(int j=0;j<26;j++){
        segTree[i][j] = segTree[2*i+1][j] + segTree[2*i+2][j];
    }
}

void update(vector<vector<int>>& segTree, int pos, char ch, int l, int r, int i){
    if(l==r){
        fi(j,0,26){
            if(j==(ch-'a')) segTree[i][j]=1;
            else segTree[i][j]=0;
        }
        return;
    }
    int mid = l+(r-l)/2;
    if(pos<=mid) update(segTree, pos, ch, l, mid, i*2+1);
    else update(segTree, pos, ch, mid+1, r, 2*i+2);
    fi(j,0,26){
        segTree[i][j] = segTree[2*i+1][j] + segTree[2*i+2][j];
    }
}

vector<int> query(vector<vector<int>>& segTree, int start, int end, int l, int r, int i){
    if(end<l || start>r) return vector<int>(26, 0);
    if(l>=start && r<=end){
        return segTree[i];
    }
    int mid = l+(r-l)/2;
    vector<int> lft = query(segTree, start, end, l, mid, i*2+1);
    vector<int> rt = query(segTree, start, end, mid+1, r, 2*i+2);
    for(int j=0;j<26;j++) lft[j] += rt[j];
    return lft;  
}

void solve(){
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<int>> segTree(4*n, vector<int>(26, 0));
    buildTree(segTree, s, 0, n-1, 0);
    int q;
    cin >> q;
    while(q--){
        int x;
        cin >> x;
        if(x==1){
            int pos; char ch;
            cin >> pos >> ch;
            pos--;
            update(segTree, pos, ch, 0, n-1, 0);
        }
        else{
            int l,r,c=0;
            cin >> l >> r;
            l--; r--;
            vector<int> tmp = query(segTree, l, r, 0, n-1, 0);
            fi(j,0,26) if(tmp[j]) c++;
            cout(c);
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