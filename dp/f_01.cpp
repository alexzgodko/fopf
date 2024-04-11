#include <bits/stdc++.h>
using namespace std;
#define int long long

/*дан ряд чисел; выбираем тройку рядом стоящих чисел; прибавляем
их произведение к ответу; удаляем центральное число; числа сдвигаются,
заполняя пропуск; нужно минимизировать ответ*/

vector<int> solve(vector<int> a) {
  int n = a.size();
  if (n == 3) {
    return {a[0] * a[1] * a[2], a[0], a[1], a[2]};
  }
  int mn = 1000000000;
  int ans = 0;
  vector<int> vec_ans;
  for (int i = 1; i < a.size() - 1; ++i) {
    int x = a[i];
    a.erase(a.begin() + i);
    vector<int> vec = solve(a);
    a.insert(a.begin() + i, x);
    int sol = vec[0];
    int cur = a[i - 1] * a[i] * a[i + 1] + sol;
    if (cur < mn) {
      ans = i;
      vec_ans = vec;
      mn = cur;
    }
  }
  vec_ans[0] = mn;
  vec_ans.push_back(a[ans - 1]);
  vec_ans.push_back(a[ans]);
  vec_ans.push_back(a[ans + 1]);
  return vec_ans;
}

signed main() {
  //   int n;
  //   cin >> n;
  //   vector<int> a(n);
  //   for (auto& i : a) cin >> i;
  vector<int> a = {12, 340, 39, 123, 76, 44, 86, 865, 75, 40};
  vector<int> res = solve(a);
  cout << res[0] << endl;
  for (int i = 1; i < res.size(); i += 3) {
    cout << res[i] << ' ' << res[i + 1] << ' ' << res[i + 2] << endl;
  }
}