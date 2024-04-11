#include <bits/stdc++.h>
using namespace std;
#define int long long

const int INF = 1000000000;

/* dp[i] - число, на которое оканчивается возрастающая подпоследовательность
длины i; p[i] - на элементе с каким индексом оканчивается оптимальная
подпоследовательность длины i; prev[i] - индекс элемента, который должен стоять
перед a[i] */

signed main() {
  int n;
  cin >> n;
  vector<int> a(n), dp(n + 1, INF), p(n + 1, -1), prev(n, -1);
  for (auto& i : a) cin >> i;
  dp[0] = -INF;
  for (int i = 0; i < n; ++i) {
    // j - наибольший номер ячейки, которую может обновить a[i]
    int j = upper_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
    if (dp[j - 1] < a[i] && a[i] < dp[j]) {
      dp[j] = a[i];
      p[j] = i;
      prev[i] = p[j - 1];
    }
  }
  int res = 0;
  while (res + 1 <= n && dp[res + 1] != INF) ++res;
  vector<int> path;
  int cur = p[res];
  while (cur != -1) {
    path.push_back(a[cur]);
    cur = prev[cur];
  }
  for (auto& i : path) cout << i << ' ';
  cout << res << endl;
}