#include <bits/stdc++.h>
using namespace std;
#define int long long

// метод отжига

int n;
const int k = 20000;  // количество итераций
vector<int> a;

inline int f(const vector<int> &p) {  // ответ для порядка обхода p - O(n^2)
  int res = 0;
  vector<int> a2 = a;
  for (auto &i : p) {
    int left = i - 1, right = i + 1;
    while (a2[left] == -1) --left;
    while (a2[right] == -1) ++right;
    res += a2[left] * a2[right] * a2[i];
    a2[i] = -1;
  }
  return res;
}

double rnd() { return double(rand()) / RAND_MAX; }

signed main() {
  cin >> n;
  a.assign(n, 0);
  for (auto &i : a) cin >> i;
  vector<int> v(n - 2);
  iota(v.begin(), v.end(), 1);
  shuffle(v.begin(), v.end(), std::mt19937{std::random_device{}()});
  int res = f(v);

  double t = 1;
  for (int i = 0; i < k; ++i) {
    t *= 0.99;
    vector<int> u = v;
    swap(u[rand() % (n - 2)], u[rand() % (n - 2)]);
    swap(u[rand() % (n - 2)], u[rand() % (n - 2)]);
    int val = f(u);
    if (val < res || rnd() < exp((res - val) / t)) {
      v = u;
      res = val;
    }
  }
  cout << res << endl;
}