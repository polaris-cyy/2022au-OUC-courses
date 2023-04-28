import numpy as np
import matplotlib.pyplot as plt

X = input("x的值: ").split(' ')
Y = input("y的值: ").split(' ')
x = input("预测点: ").split(' ')
print("\n")

if len(X)  != len(Y):
    print("非法输入，程序终止。")
    exit(1)

X = np.array(X).astype(np.float64)
Y = np.array(Y).astype(np.float64)
x = np.array(x).astype(np.float64)

n = len(X)


def Frac(x, i, X):
    """

    :param x: 插值点
    :param i: 第i个基函数
    :param X: 给定点的集合
    :return: 基函数的分子或分母
    """
    num = 1
    for val in X:
        if X[i] == val:
            continue
        num = num * (x - val)
    return num


def P(i, x, X, Y):
    """

    :param i: 计算第i个点
    :param x: 插值点
    :param X: 给定点的集合
    :param Y: 给定点的纵坐标的集合
    :return: 第i个点的基函数*Y[i]
    """
    P_i = Frac(x, i, X)/Frac(X[i], i, X) * Y[i]
    return P_i


def L(x, X, Y):
    """

    :param x: 插值点
    :param X: 给定点的集合
    :param Y: 给定点的纵坐标集合
    :return: f(x)
    """
    result = 0
    for i in range(n):
        result = result + P(i, x, X, Y)
    return result


y = L(x, X, Y)

print("结果: " + str(y) + '\n')

X_n = np.linspace(X[0]-3, X[n-1]+3, 1000) #略微延伸
Y_n = L(X_n, X, Y)

plt.grid(visible=True)
l1, = plt.plot(X_n, Y_n, label='prediction', linestyle='-')

plt.show()