#include <bits/stdc++.h>
#define fi(i,s,e) for(int i=s;i<e;i++)
#define nl cout << endl
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long double> s(n);
    fi(i,0,n) {
        long double x; 
        cin >> x;
        s[i] = x;
    }
    vector<long double> P(n, 0.0L);
    long double kn = (long double)k / (long double)n;

    fi(L,0,n) {
        long double ratio = 0.0L;
        if (k == 1) {
            ratio = 1.0L; 
        } else if (n - 1 - L >= k - 1) {
            long double r = 1.0L;
            for (int t = 0; t < k - 1; ++t) {
                r *= (long double)(n - 1 - L - t) / (long double)(n - 1 - t);
            }
            ratio = r;
        } else {
            ratio = 0.0L;
        }
        P[L] = kn * ratio;
    }
    vector<long double> ans(n, 0.0L);
    for (int i = 0; i < n; ++i) {
        long double sum = 0.0L;
        for (int j = 0; j < n; ++j) {
            int L = i - j;
            if (L < 0) L += n; 
            sum += s[j] * P[L];
        }
        ans[i] = sum;
    }
    cout << setprecision(10);
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        long double v = ans[i];
        if (v < 0 && v > -1e-12L) v = 0; 
        cout << (long double)v;
    }
    nl;
    return 0;
}