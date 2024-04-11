#include <bits/stdc++.h>
using namespace std;
#define int long long

// задача о наибольшей общей подпоследовательности

signed main() {
  string s1, s2;
  cin >> s1 >> s2;
  int n = s1.size(), m = s2.size();
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (s1[i - 1] == s2[j - 1])
        dp[i][j] = dp[i - 1][j - 1] + 1;
      else
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    }
  }
  cout << fixed << setprecision(10) << 100 * dp[n][m] / min(n, m) << endl;
}