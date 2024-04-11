import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import math


x = np.array([1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000])
y1 = np.array([2744, 10331, 22896, 40281, 62538,
              89780, 121670, 178895, 220120, 246900])
y2 = np.array([28, 105, 236, 407, 687, 901, 1313, 1895, 2110, 2604])
y3 = np.array([11, 21, 37, 39, 109, 105, 99, 109, 184, 216])

coefficients1 = np.polyfit(x, y1, 1)
polynomial1 = np.poly1d(coefficients1)

coefficients2 = np.polyfit(x, y2, 1)
polynomial2 = np.poly1d(coefficients2)

coefficients3 = np.polyfit(x, y3, 1)
polynomial3 = np.poly1d(coefficients3)

# plt.figure(figsize=[13, 7])
plt.suptitle("Time(N)", fontweight='bold')
plt.subplots_adjust(wspace=0.4, hspace=0.4)

plt.subplot(1, 3, 1)
plt.scatter(x, y1)
plt.plot(x, polynomial1(x), 'r')
plt.grid()
plt.title("Добавляем строго по одному элементу", fontsize=10)

plt.subplot(1, 3, 2)
plt.scatter(x, y2)
plt.plot(x, polynomial2(x), 'r')
plt.grid()
plt.title("Добавляем 100 элементов", fontsize=10)

plt.subplot(1, 3, 3)
plt.scatter(x, y3)
plt.plot(x, polynomial3(x), 'r')
plt.grid()
plt.title("Увеличиваем размер в 2 раза", fontsize=10)

plt.show()
