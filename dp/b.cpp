#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 505;

map<int, int> mp = {{1, 1},  {2, 5},  {3, 8},  {4, 9},  {5, 10},
                    {6, 17}, {7, 17}, {8, 20}, {9, 24}, {10, 30}};

/*ИДЕЯ: для каждой длины ищем максимальную стоимость,
пытаясь прийти в это состояние из доступных предыдущих*/

signed main() {
  int n;
  cin >> n;
  vector<int> dp(MAXN, 0);
  for (int i = 1; i <= 10; ++i) dp[i] = mp[i];
  for (int i = 2; i <= n; ++i) {
    for (auto [key, val] : mp)
      if (i - key >= 0) dp[i] = max(dp[i], dp[i - key] + val);
  }
  cout << dp[n] << endl;
}