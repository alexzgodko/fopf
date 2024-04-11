#include <bits/stdc++.h>
using namespace std;
#define int long long

const int t = 10;  // количество точек на графике
const int k = 5;  // количество замеров времени для одной точки

// пытаемся добавить элементы 0 ... n в массив a,
// динамически изменяя его размер тремя способами

void solve1(int n) {
  vector<int> a;
  for (int i = 0; i < n; ++i) {
    vector<int> b(a.size() + 1);
    for (int j = 0; j < a.size(); ++j) b[j] = a[j];
    swap(a, b);
    a[i] = i;
  }
}

const int m = 100;  // на сколько элементов увеличиваем размер массива
void solve2(int n) {
  vector<int> a;
  for (int i = 0; i < n; ++i) {
    if (i == a.size()) {
      vector<int> b(a.size() + m);
      for (int j = 0; j < a.size(); ++j) b[j] = a[j];
      swap(a, b);
    }
    a[i] = i;
  }
}

void solve3(int n) {
  vector<int> a;
  for (int i = 0; i < n; ++i) {
    if (i == a.size()) {
      vector<int> b(max(1LL, (int)(a.size() * 2)));
      for (int j = 0; j < a.size(); ++j) b[j] = a[j];
      swap(a, b);
    }
    a[i] = i;
  }
}

signed main() {
  vector<vector<int>> dp(3, vector<int>(t, 0));
  for (int i = 0; i < t; ++i) {
    int n = (i + 1) * 1000;
    for (int j = 0; j < k; ++j) {  // solve1
      auto begin = std::chrono::steady_clock::now();
      solve1(n);
      auto end = std::chrono::steady_clock::now();
      auto time_span =
          std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
      dp[0][i] += time_span.count();
    }
    for (int j = 0; j < k; ++j) {  // solve2
      auto begin = std::chrono::steady_clock::now();
      solve2(n);
      auto end = std::chrono::steady_clock::now();
      auto time_span =
          std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
      dp[1][i] += time_span.count();
    }
    for (int j = 0; j < k; ++j) {  // solve3
      auto begin = std::chrono::steady_clock::now();
      solve3(n);
      auto end = std::chrono::steady_clock::now();
      auto time_span =
          std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
      dp[2][i] += time_span.count();
    }
  }
  for (int i = 0; i < 3; ++i) {
    cout << "Solve" << i + 1 << " results:" << endl;
    for (int j = 0; j < t; ++j) cout << dp[i][j] / k << endl;
    cout << endl;
  }
}