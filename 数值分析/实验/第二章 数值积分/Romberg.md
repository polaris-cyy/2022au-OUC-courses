```python
import numpy as np
import math as m
```


```python
def Calculate_func(X, *, functype):
    """

    :param X: 样本点
    :param func: 函数类型
    :return: 函数值
    """
    if functype == "Exp":
        return np.exp(X)
    elif functype == "Frac":
        return 1 / X
    elif functype == "Real":
        return m.sqrt(1-((972.5/7782.5)*np.sin(X))**2)
    else:
        print(f"Invalid function {functype}")
        exit(1)
```


```python
def Trapezoidal_next(ans, func, left, right, n, *, functype):
    sum = 0
    h = (right - left) * 2 ** (-n)
    ans = ans / 2
    point = left + h / 2
    n = 2 ** n
    for i in range(n):
        sum += Calculate_func(point + i * h, functype=func)
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
    ans = ans * h / 2
    for i in range(n):
        ans, h = Trapezoidal_next(ans, func, left, right, i, functype=func)
        
    return ans

def Trapezoidal_precision(left, right, theory, *, functype, precision):
    epsilon = 10 ** (-precision) / 2
    n = 0
    h = right - left
    trap = Trapezoidal(left, right, 0, func=functype)
    func = functype
    while abs(trap - theory) > epsilon:
        trap, h = Trapezoidal_next(trap, func, left, right, n, functype=func)
        n = n + 1
        
    
    print("Trapezoidal method")
    print(f"Theory value: {theory}")
    print(f"Predicted value: {round(trap, precision)}")
    print(f"Intervals: {2 ** n}")
```


```python
def Simpson(left, right, n, *, func="Exp"):

    """

    :param left: 左边界
    :param right: 右边界
    :param n: 区间个数为2 ** (n + 1)
    :param func: 函数类型
    :return: 前项为积分值，后项用于递推
    """
    trap1 = Trapezoidal(left, right, n, func=func)
    trap2 = Trapezoidal_next(trap1, func, left, right, n, functype=func)[0]
    return [(trap2 * 4 - trap1) / 3, trap2]

def Simpson_next(simp, left, right, n, *, func):
    trap_next = Trapezoidal_next(simp[1], func, left, right, n + 1, functype=func)[0]
    return [(trap_next * 4 - simp[1]) / 3, trap_next]

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
    print(f"Intervals: {2 ** (n + 1)}\n")
```


```python
def Cotes(left, right, n, *, func="Exp"):
    """

    :param left: 左边界
    :param right: 右边界
    :param n: 区间个数为2 ** (n + 2)
    :param func: 函数类型
    :return: 积分值
    """
    simp1, trap2 = Simpson(left, right, n, func=func)
    trap3 = Trapezoidal_next(trap2, func, left, right, n+1, functype=func)[0]
    simp2 = trap3 * 4 / 3 - trap2 / 3
    cotes1 = simp2 * 16 / 15 - simp1 / 15
    return [cotes1, simp2, trap3]

def Cotes_next(cotes, left, right, n, *, func):
    simp_next, trap_next = Simpson_next([cotes[1], cotes[2]], left, right, n+1, func=func)
    return [simp_next * 16 / 15 - cotes[1] / 15, simp_next, trap_next]

def Cotes_precision(left, right, theory, *, functype, precision):
    epsilon = 10 ** (-precision) / 2
    n = 0
    cotes = Cotes(left, right, 0, func=functype)
    while abs(cotes[0] - theory) > epsilon:
        cotes = Cotes_next(cotes, left, right, n, func=functype)
        n = n + 1
    
    print("Cotes method")
    print(f"Theory value: {theory}")
    print(f"Predicted value: {round(cotes[0], precision)}")
    print(f"Intervals: {2 ** (n + 2)}\n")
```


```python
def Romberg(left, right, n, *, functype="Exp"):
    """

    :param left: 左边界
    :param right: 右边界
    :param n: 区间个数为2 ** (n + 3)
    :param functype: 函数类型
    :return: 积分值
    """

    cotes1, simp2, trap3 = Cotes(left, right, n, func=functype)
    trap4 = Trapezoidal_next(trap3, functype, left, right, n + 2, functype=functype)[0]
    simp3 = trap4 * 4 / 3 - trap3 / 3
    cotes2 = simp3 * 16 / 15 - simp2 / 15
    return [cotes2 * 64 / 63 - cotes1 / 63, cotes2, simp3, trap4]

def Romberg_next(left, right, n, rom, *, functype):
    trap5 = Trapezoidal_next(rom[3], functype, left, right, n + 3, functype=functype)[0]
    simp4 = trap5 * 4 / 3 - rom[3] / 3
    cotes3 = simp4 * 16 / 15 - rom[2] / 15
    return [cotes3 * 64 / 63 - rom[1] / 63, cotes3, simp4, trap5]

def Romberg_precision(left, right, theory, *, functype, precision):
    epsilon = 10 ** (-precision) / 2
    n = 0
    rom = Romberg(left, right, 0, functype=functype)
    while abs(rom[0] - theory) > epsilon:
        rom = Romberg_next(left, right, n, rom, functype=functype)
        n = n + 1
    
    print("Romberg method")
    print(f"Theory value: {theory}")
    print(f"Predicted value: {round(rom[0], precision)}")
    print(f"Intervals: {2 ** (n + 3)}\n")
```


```python
def precision_test(left, right, theory, n, *, func):
    Romberg_precision(left, right, theory, functype=func, precision=n)
    Cotes_precision(left, right, theory, functype=func, precision=n)
    Simpson_precision(left, right, theory, functype=func, precision=n)
    Trapezoidal_precision(left, right, theory, functype=func, precision=n)
```


```python
precision_test(1, 3, m.e ** 3 - m.e, 12, func="Exp")
```

    Romberg method
    Theory value: 17.36725509472862
    Predicted value: 17.367255094729
    Intervals: 64
    
    Cotes method
    Theory value: 17.36725509472862
    Predicted value: 17.367255094729
    Intervals: 256
    
    Simpson method
    Theory value: 17.36725509472862
    Predicted value: 17.367255094729
    Intervals: 2048
    
    Trapezoidal method
    Theory value: 17.36725509472862
    Predicted value: 17.367255094729
    Intervals: 4194304
    


```python
precision_test(1, 5, np.log(5), 12, func="Frac")
```

    Romberg method
    Theory value: 1.6094379124341003
    Predicted value: 1.609437912434
    Intervals: 256
    
    Cotes method
    Theory value: 1.6094379124341003
    Predicted value: 1.609437912434
    Intervals: 512
    
    Simpson method
    Theory value: 1.6094379124341003
    Predicted value: 1.609437912435
    Intervals: 2048
    
    Trapezoidal method
    Theory value: 1.6094379124341003
    Predicted value: 1.609437912434
    Intervals: 2097152
    


```python
def simpson(left, right, *, func):
    return Simpson(left, right, 1, func=func)[0]

def asr(left, right, simp, *, epsilon, func):
    mid = (left + right) / 2
    l = simpson(left, mid, func=func)
    r = simpson(mid, right, func=func)
    if abs(l + r - simp) <= 15 * epsilon:
        return l + r + (l + r - simp) / 15
    else:
        return asr(left, mid, l, epsilon=epsilon/2, func=func) + asr(mid, right, r, epsilon=epsilon/2, func=func)
```


```python
def asr_test(left, right, func, epsilon, theory):
    answer = asr(left, right, simpson(left, right, func=func), epsilon=epsilon, func=func)
    print("Adaptive Simpson method")
    print(f"Theory value: {theory}")
    print(f"Predicted value: {answer}")
```


```python
asr_test(1, 5, "Frac", 10 ** (-12), np.log(5))
```

    Adaptive Simpson method
    Theory value: 1.6094379124341003
    Predicted value: 1.6094379124341003
    


```python
asr_test(1, 3, "Exp", 10 ** (-12), m.e ** 3 - m.e)
```

    Adaptive Simpson method
    Theory value: 17.36725509472862
    Predicted value: 17.367255094728623
    


```python
4 * 7782.5 * asr(0, m.pi/2, simpson(0, m.pi/2, func="Real"), epsilon=10**(-12), func="Real")
```




    48707.43851187989




```python

```


```python

```


```python

```


```python

```


```python

```


```python

```


```python

```


```python

```


```python

```


```python

```


```python

```
