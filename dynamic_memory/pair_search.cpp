#include <chrono>
#include <iostream>
#include <random>

#define N 100000

void func(int (&arr)[N], int meaning, int (&counter)[N]) {
  for (int j = 0; j != N; ++j) {
    if (arr[j] == meaning) {
      if (j > 0) {
        counter[j]++;
        for (int k = j - 1; k >= 0; --k) {
          if (counter[k] < counter[k + 1]) {
            int x = arr[k];
            arr[k] = arr[k + 1];
            arr[k + 1] = x;
            counter[k]++;
            counter[k + 1]--;
          } else
            break;
        }
        break;
      } else {
        counter[j]++;
        break;
      }
    }
  }
}

int main() {
  int arr[N] = {0};
  unsigned seed = N;
  std::default_random_engine rng(seed);
  std::uniform_int_distribution<unsigned> dstr(0, N - 1);
  for (int j = 0; j < 5; ++j) {
    for (int i = 0; i < N; ++i) arr[i] = dstr(rng);
    int counter[N] = {0};
    auto begin = std::chrono::steady_clock::now();
    for (int i = 0; i != 100000; ++i) func(arr, arr[dstr(rng)], counter);
    auto end = std::chrono::steady_clock::now();
    auto time_span =
        std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << std::endl << time_span.count() << std::endl;
  }
  return 0;
}