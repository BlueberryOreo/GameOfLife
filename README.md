# GameOfLife
DataStructruesCourse-practice1

## 数据结构实践1

### 文件结构

* GameOfLife
  * utility.h
  * Life.h ```Life类的定义```
  * DoubleBuffer.h
  * Life.cpp
  * DoubleBuffer.cpp
  * GameOfLife.cpp  ```主程序```
  * GameOfLife.vcxproj
  * GameOfLife.vcxproj.filters
* .gitattributes
* .gitignore
* GameOfLife.sln
* README.md

## 一个手动输入的样例

### *滑翔机生成器输入：

```
n
1
50
50
y
33
0
0
0
0
0
0
0
0
0
0
1
25
2
23 25
6
13 14 21 22 35 36
6
12 16 21 22 35 36
6
1 2 11 17 21 22
8
1 2 11 15 17 18 23 25
3
11 17 25
2
12 16
2
13 14
-1
```

## 文件输入样例：

文件中死细胞用空格' '表示，活细胞请用ASCII码除空格以外的可见字符表示；一行全部死亡请用一个空格表示，行数不得超过51，列数不得超过88。如下：

```
test.txt:
 xxxxx xx 
xx xx x  x
xx xx   x 
x xx  xx x
 
       xxx
  x xxx  x
xx  xx x  
 xxx  x xx
xxxxxx    
xx  x xx x
```

读入结果：

```
□■■■■■□■■□
■■□■■□■□□■
■■□■■□□□■□
■□■■□□■■□■
□□□□□□□□□□
□□□□□□□■■■
□□■□■■■□□■
■■□□■■□■□□
□■■■□□■□■■
■■■■■■□□□□
■■□□■□■■□■
```
