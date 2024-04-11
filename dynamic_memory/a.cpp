#include <bits/stdc++.h>
using namespace std;
#define int long long

// ns - в каких n замеряем время
const vector<int> ns = {10,   100,  1000, 2000, 3000, 4000,
                        5000, 6000, 7000, 8000, 9000, 10000};
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
  vector<vector<int>> dp(3, vector<int>(ns.size(), 0));
  for (int i = 0; i < ns.size(); ++i) {
    int n = ns[i];
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
  ofstream f1;
  f1.open("01.txt");
  for (int j = 0; j < ns.size(); ++j) {
    f1 << dp[0][j] / k;
    if (j != ns.size() - 1) f1 << ", ";
  }
  f1.close();
  f1.open("02.txt");
  for (int j = 0; j < ns.size(); ++j) {
    f1 << dp[1][j] / k;
    if (j != ns.size() - 1) f1 << ", ";
  }
  f1.close();
  f1.open("03.txt");
  for (int j = 0; j < ns.size(); ++j) {
    f1 << dp[2][j] / k;
    if (j != ns.size() - 1) f1 << ", ";
  }
  f1.close();
}