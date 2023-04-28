import numpy as np
import math as m

def Calculate_func(X, *, functype):
    """

    :param X: 样本点
    :param func: 函数类型
    :return: 函数值
    """
    if functype == "Exp":
        return np.exp(X)
    elif functype == "Frac":
        return 1/X
    else:
        print(f"Invalid function {functype}")
        exit(1)


def Trapezoidal_next(ans, h, func, left, right, n, *, functype):
    sum = 0
    ans = ans / 2
    point = h / 2 + left
    while point < right:
        sum += Calculate_func(point, functype=func)
        point += h
    h = h / 2
    ans += sum * h

    return [ans, h]


def Trapezoidal(left, right, n, *, func="Exp"):
    """

    :param left: 左边界
    :param right: 右边界
    :param n: 区间个数为2 ** n
    :param func: 函数类型
    :return: 积分值
    """

    h = right - left
    ans = Calculate_func(left, functype=func) + Calculate_func(right, functype=func)
    ans /= 2
    for i in range(n):
        ans, h = Trapezoidal_next(ans, h, func, left, right, n, functype=func)

    return ans


def Trapezoidal_precision(left, right, theory, *, functype, precision):
    epsilon = 10 ** (-precision) / 2
    n = 0
    h = right - left
    trap = Trapezoidal(left, right, 0, func=functype)
    func = functype
    while abs(trap - theory) > epsilon:
        trap, h = Trapezoidal_next(trap, h, func, left, right, n, functype=func)
        n = n + 1

    print("Trapezoidal method")
    print(f"Theory value: {theory}")
    print(f"Predicted value: {round(trap, precision)}")
    print(f"Intervals: {2 ** n}")


def Simpson(left, right, n, *, func="Exp"):
    """

    :param left: 左边界
    :param right: 右边界
    :param n: 函数类型
    :param func: 积分值
    :return: 前项为积分值，后项用于递推
    """
    trap1 = Trapezoidal(left, right, n, func=func)
    trap2 = Trapezoidal_next(trap1, (right - left) * 2 ** (-n), func, left, right, n, functype=func)[0]
    return [trap2 * 4 / 3 - trap1 / 3, trap2]


def Simpson_next(simp, left, right, n, *, func):
    trap_next = Trapezoidal_next(simp[1], (right - left) * 2 ** (-n - 1), func, left, right, n, functype=func)[0]
    return [trap_next * 4 / 3 - simp[1] / 3, trap_next]


def Simpson_precision(left, right, theory, *, functype, precision):
    epsilon = 10 ** (-precision) / 2
    n = 0
    h = right - left
    simp = Simpson(left, right, 0, func=functype)
    func = functype
    while abs(simp[0] - theory) > epsilon:
        simp = Simpson_next(simp, left, right, n, func=func)
        n = n + 1

    print("Simpson method")
    print(f"Theory value: {theory}")
    print(f"Predicted value: {round(simp[0], precision)}")
    print(f"Intervals: {2 ** n}\n")


def Cotes(left, right, n, *, func="Exp"):
    """

    :param left: 左边界
    :param right: 右边界
    :param n: 区间个数
    :param func: 函数类型
    :return: 积分值
    """
    simp1, trap2 = Simpson(left, right, n, func=func)
    trap3 = Trapezoidal_next(trap2, (right - left) * 2 ** (- n - 1), func, left, right, n, functype=func)[0]
    simp2 = trap3 * 4 / 3 - trap2 / 3
    return [simp2 * 16 / 15 - simp1 / 15, simp2, trap3]


def Cotes_next(cotes, left, right, n, *, func):
    simp = [cotes[1], cotes[2]]
    simp_next, trap_next = Simpson_next([cotes[1], cotes[2]], left, right, n + 1, func=func)
    return [simp_next * 16 / 15 - cotes[0] / 15, simp_next, trap_next]


def Cotes_precision(left, right, theory, *, functype, precision):
    epsilon = 10 ** (-precision) / 2
    n = 0
    cotes = Cotes(left, right, 0, func=functype)
    while abs(cotes[0] - theory) > epsilon:
        n = n + 1
        cotes = Cotes_next(cotes, left, right, n, func=functype)

    print("Cotes method")
    print(f"Theory value: {theory}")
    print(f"Predicted value: {round(cotes[0], precision)}")
    print(f"Intervals: {2 ** n}\n")


def Romberg(left, right, n, *, functype="Exp"):
    """

    :param left: 左边界
    :param right: 右边界
    :param n: 区间个数
    :param functype: 函数类型
    :return: 积分值
    """

    cotes1, simp2, trap3 = Cotes(left, right, n, func=functype)
    trap4 = Trapezoidal_next(trap3, (right - left) * 2 ** (-n - 2), functype, left, right, n, functype=functype)[0]
    simp3 = trap4 * 4 / 3 - trap3 / 3
    cotes2 = simp3 * 16 / 15 - simp2 / 15
    return [cotes2 * 64 / 63 - cotes1 / 63, cotes2, simp3, trap4]


def Romberg_next(left, right, n, rom, *, functype):
    trap5 = Trapezoidal_next(rom[3], (right - left) * 2 ** (-n - 3), functype, left, right, n, functype=functype)[0]
    simp4 = trap5 * 4 / 3 - rom[3] / 3
    cotes3 = simp4 * 16 / 15 - rom[2] / 15
    return [cotes3 * 64 / 63 - rom[1] / 63, cotes3, simp4, trap5]


def Romberg_precision(left, right, theory, *, functype, precision):
    epsilon = 10 ** (-precision) / 2
    n = 0
    rom = Romberg(left, right, 0, functype=functype)
    while abs(rom[0] - theory) > epsilon:
        n = n + 1
        rom = Romberg_next(left, right, n, rom, functype=functype)

    print("Romberg method")
    print(f"Theory value: {theory}")
    print(f"Predicted value: {round(rom[0], precision)}")
    print(f"Intervals: {2 ** n}\n")

print(Trapezoidal(0, 1, 2))
print(Simpson(0, 1, 4))
print(Cotes(0, 1, 2))
print(Romberg(0, 1, 1))

print(Trapezoidal(1, 5, 4, func="Frac"))
print(Simpson(1, 5, 3, func="Frac"))
print(Cotes(1, 5, 2, func="Frac"))
print(Romberg(1, 5, 1, functype="Frac"))

n=5
Romberg_precision(1, 5, np.log(5), functype="Frac", precision=n)
Cotes_precision(1, 5, np.log(5), functype="Frac", precision=n)
Simpson_precision(1, 5, np.log(5), functype="Frac", precision=n)
Trapezoidal_precision(1, 5, np.log(5), functype="Frac", precision=n)

n=6
theory = m.e ** 3 - m.e ** 1
Romberg_precision(1, 3, theory, functype="Exp", precision=n)
Cotes_precision(1, 3, theory, functype="Exp", precision=n)
Simpson_precision(1, 3, theory, functype="Exp", precision=n)
Trapezoidal_precision(1, 3, theory, functype="Exp", precision=n)