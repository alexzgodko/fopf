#include <bits/stdc++.h>
using namespace std;
#define int long long

/* dp[i] - длина наибольшей возрастающей подпоследовательности,
оканчивающейся в элементе с индексом i; dp[i] = max(1, max(dp[j] + 1)), j = [0,
i - 1]: a[j] < a[i];
t[a[i]] = dp[i] => нужно найти max на префиксе t[0 ... a[i] - 1] */

inline pair<int, int> max_pair(const pair<int, int> &a,
                               const pair<int, int> &b) {
  if (a.first > b.first || (a.first == b.first && a.second < b.second))
    return a;
  return b;
}

struct segtree {
  int size = 1;
  vector<pair<int, int>> t;  // t[i] = {a[i], i}
  void init(int n) {
    while (size < n) size <<= 1;
    t.assign(2 * size - 1, {0, -1});
  }
  void build(const vector<int> &a) {
    init(a.size());
    for (int i = size - 1; i < 2 * size - 1; ++i)
      t[i] = {a[i - size + 1], i - size + 1};
    for (int i = size - 2; i >= 0; --i) {
      t[i] = max_pair(t[2 * i + 1], t[2 * i + 1]);
    }
  }
  pair<int, int> Max(int v, int tl, int tr, int l, int r) {
    if (l > r) return {0, -1};
    if (l == tl && r == tr) return t[v];
    int tm = (tl + tr) / 2;
    return max_pair(Max(2 * v + 1, tl, tm, l, min(r, tm)),
                    Max(2 * v + 2, tm + 1, tr, max(l, tm + 1), r));
  }
  pair<int, int> Max(int l, int r) { return Max(0, 0, size - 1, l, r); }
  void update(int v, int tl, int tr, int pos, int val, int ind) {
    if (tl == tr) {
      t[v] = {val, ind};
      return;
    }
    int tm = (tl + tr) / 2;
    if (pos <= tm)
      update(2 * v + 1, tl, tm, pos, val, ind);
    else
      update(2 * v + 2, tm + 1, tr, pos, val, ind);
    t[v] = max_pair(t[2 * v + 1], t[2 * v + 2]);
  }
  void update(int pos, int val, int ind) {
    update(0, 0, size - 1, pos, val, ind);
  }
};

signed main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (auto &i : a) cin >> i;

  /* сжатие координат: перенумеруем элементы а в порядке возрастания; теперь
   вместо a[i] используем его номер mp[a[i]] */
  set<int> set_a(a.begin(), a.end());
  map<int, int> mp;
  int m = 0;
  for (auto &i : set_a) mp[i] = m++;

  /* dp[i] = {длина наибольшей возрастающей подпоследовательности,
  оканчивающейся на позиции i; предыдущее число} */
  vector<pair<int, int>> dp(n, {1, -1});
  segtree st;
  st.init(m);

  for (int i = 0; i < n; ++i) {
    auto [dp_j, pred] = st.Max(0, mp[a[i]] - 1);
    dp[i] = {dp_j + 1, pred};
    st.update(mp[a[i]], dp[i].first, i);
  }

  int ans_ind = 0;
  for (int i = 1; i < n; ++i)
    if (dp[i].first > dp[ans_ind].first) ans_ind = i;

  int res = dp[ans_ind].first;
  while (ans_ind != -1) {
    cout << a[ans_ind] << ' ';
    ans_ind = dp[ans_ind].second;
  }
  cout << res << endl;
}