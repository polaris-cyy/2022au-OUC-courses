import numpy as np
import matplotlib.pyplot as plt

X = input("x的值: ").split(' ')
Y = input("y的值: ").split(' ')
x = input("预测点集: ").split(" ")
print("\n")

if len(X) != len(Y):
    print("非法输入，程序终止")
    exit(1)

X = np.array(X).astype(np.float64)
Y = np.array(Y).astype(np.float64)
x = np.array(x).astype(np.float64)

n = len(X)

def Dif(X, Y, x):
    """

    :param X: 给定的横坐标
    :param Y: f(X)
    :param x: 插值点的横坐标
    :return: 差商
    """

    dif = Y
    for i in range(1, len(X)):
        for j in range(len(X)-1, i-1, -1):
            dif[j] = (dif[j] - dif[j-1])/(X[j] - X[j-i])
    return dif


dif = Dif(X, Y, x)      # 求出差商，避免重复计算


def Newton(X, Y, x, dif):
    """

    :param X: 给定点的横坐标
    :param Y: f(X)
    :param x: 插值点的横坐标
    :param dif: 差商
    :return: f(x)
    """

    ans = 0
    mult = 1
    for i in range(0, len(dif)):
        ans += dif[i] * mult
        mult *= (x-X[i])
    return ans


a = Newton(X, Y, x, dif)
print(f"结果是: {a}\n")

X_n = np.linspace(X[0]-3, X[n-1]+3, 1000)
Y_n = Newton(X, Y, X_n, dif)

plt.grid(visible=True)
l1, = plt.plot(X_n, Y_n, label='prediction', linestyle='-')

plt.show()