#include <bits/stdc++.h>
using namespace std;
#define int long long

const int INF = LONG_LONG_MAX;

int n;
vector<int> a;
vector<vector<int>> dp;

/* dp[l, r] - ответ на [l, r)
мы можем разделить последовательность на две части для каждой возможной позиции
*/

inline int solve(int l, int r) {  // [l, r)
  if (dp[l][r] == -1) {
    if (r - l < 3) {
      dp[l][r] = 0;
    } else {
      dp[l][r] = INF;
      for (int i = l + 1; i < r - 1; ++i)
        dp[l][r] = min(dp[l][r],
                       a[l] * a[i] * a[r - 1] + solve(l, i + 1) + solve(i, r));
    }
  }
  return dp[l][r];
}

signed main() {
  cin >> n;
  a.assign(n, 0);
  for (auto& i : a) cin >> i;
  dp.assign(n, vector<int>(n + 1, -1));
  cout << solve(0, n) << endl;
}