#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 50;

signed main() {
    int n;
    cin >> n;
    vector<int> dp(MAXN, 0);
    dp[0] = dp[1] = 1;
    dp[2] = 4;
    for(int i = 3; i <= n; ++i) dp[i] = 2 * dp[i - 1] + 2 * dp[i - 2] - dp[i - 3];
    cout << dp[n] << endl;
}