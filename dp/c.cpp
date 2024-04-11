#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 105;

map<int, int> mp = {{1, 1},  {2, 5},  {3, 8},  {4, 9},  {5, 10},
                    {6, 17}, {7, 17}, {8, 20}, {9, 24}, {10, 30}};

/*восстановление ответа для задачи B:
храним дополнительный массив предков p
p[i] - длина последнего отрезанного куска*/

signed main() {
  int n;
  cin >> n;
  vector<int> dp(MAXN, 0), p(MAXN, 0);
  for (int i = 1; i <= 10; ++i) dp[i] = mp[i], p[i] = i;
  for (int i = 2; i <= n; ++i) {
    for (auto [key, val] : mp)
      // проверяем, что удалось улучить ответ для длины i
      if (i - key >= 0 && dp[i - key] + val > dp[i]) {
        dp[i] = dp[i - key] + val;
        p[i] = key;  // в это состояние мы пришли, добавив кусок длины key
      }
  }

  // восстановление ответа
  vector<int> res;
  while (n > 0) {
    res.push_back(p[n]);
    n -= p[n];
  }
  sort(res.begin(), res.end());
  for (auto& i : res) cout << i << ' ';
  cout << endl;
}