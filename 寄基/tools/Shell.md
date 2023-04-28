## Shell

---

- [常用指令](#order)
- [常用格式](#form)
- [感觉不常用的指令](#_order)

---

<span id = "order">常用指令</span>

- cd /\<address\>

> change directionary
>
> 有几个默认地址
>
> ​	. 代表当前文件夹
>
> ​	..代表上级文件夹
>
> ​	~代表home
>
> ​	-代表之前所在的文件夹
>
> ​	sys是一个很核心的文件夹，应该用不到

- clear

> 清屏 

- ls

> 显示当前文件夹下的所有文件
>
> 常用 **ls** 或 **ls -l**

- mv <old path\> <new path\>

> rename file
>
> 就是这样

- cp <source path\> <dest path\>

> copy

- sudo ...

> 记住就好了，一般下东西的时候会用
>
> 或者sudo su，获得管理员权限

- rm <path\>

> remove
>
> 删除文件

- xdg-open <filename\>

> 打开filename，系统会自动选择合适的软件打开filename

---

<span id = "form">常用格式</span>

- -l

> long listing form
>
> ​	ls -l, 试试就懂了

- |

> <order_1\> | <order_2>
>
> 以 | 左边为输入，右边为输出？

- \> <file\>

> 向file输入内容(清除并输入, 如果想append则用>>)
>
> 如cat > test.txt
>
> tail -1 > test.txt

- < <file\>

> 从file提取内容
>
> 如cat < test.txt
>
> cat < test1.txt > test2.txt

---

<span id = "_order">感觉不是很常用的指令</span>

- echo

> print something
>
> ​	echo $path, echo <string\> echo <file\>

- pwd

> print working directionary

- man

> manual page
>
> man ls可以使用一个比较好看的界面

- tail

> tail -<number\>输出最后number条信息
>
> ls -l | tail -3 输出ls -l 的最后三条信息

- cat <file\>

> 输出file内容

- rmdir <dir\>

> 删除文件夹

- mkdir <name>

> make dir