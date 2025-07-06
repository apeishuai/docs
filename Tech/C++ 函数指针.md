![](/skins/bj2008/images/fire.gif) [C++ 函数 指针](https://www.cnblogs.com/apeishuai/articles/18736065 "发布于 2025-02-25 13:44")

ref &lt;c++ primer plus&gt;

# quick use

void func(int,int){
}

void func(&a,&b){
}

void func(_a,_b){
}

# 函数

（函数原型、函数调用）  
原型描述了函数到编译器的接口  
函数圆形不需要提供变量名，有类型列表就够了 。圆形中的变量名相当于占位符，所以不必与函数定义中的变量名相同。  
void cheers(int);

### 按值传递

（函数参数、按值传递）  
将数值参数传递给函数，后者将其赋给一个新的变量

### 初始化 auto

## 数组

（函数和指针，const，）  
C++将数组名解释为其第一个元素地址  
![](https://img2024.cnblogs.com/blog/3531360/202502/3531360-20250225082459242-325944387.png)  
![](https://img2024.cnblogs.com/blog/3531360/202502/3531360-20250225082722046-26653563.png)  
![](https://img2024.cnblogs.com/blog/3531360/202502/3531360-20250225082816667-1224668632.png)

void show_array(const double ar\[\], int n)  
void show_array(double ar\[\], int n)  
//接收数组名的函数将使用原始数据，需加const进行保护  
//需要修改则不保护

arr\[20\] etc

禁止将 const 的地址赋给非 const 指针，这意味着可以修改const指向的值

const + pointer  
涉及一级间接关系，将非const指针赋值给const指针可以  

使用const的好处：  
1 可以避免无意间的数据修改导致的编程错误  
2 const使得函数能处理const和非const实参

int \* const ptr = &a //无法修改指针的值  
const int \* ptr = &a //无法修改ptr指向的值  
void show_array(const double arr\[\],int n){} //无法修改传入的参数

### 二维数组

data\[3\]\[4\]，下面是两种函数参数传递方式：  
int sum(int(\*ar2)\[\]\[4\])  
int sum(int ar2\[\]\[4\],int size)

## 字符串

字符串形式：  
1 char数组  
2 引号括起的字符串常量  
3 被设置为字符串地址的char指针

C-风格字符串 vs 常规char数组：字符串有内置结束字符

## 结构

按值传递、按地址传递、按引用传递  
引用 底层来看是 const ptr；使用来看是地址别名

```cpp
int* ptr = &a;  // 普通指针
*ptr = 30;      // 通过指针修改 a 的值
```

## 递归

结构递归 和 生成递归

## 指针

使用函数名(后面不跟参数)，就能获取函数的地址  

函数指针：声明的函数指针要像函数原型一样指出有关函数的信息  
声明应指定函数的返回类型以及函数的特征标(参数列表)。  
  
使用：使用(\*pf)时，只要将其看成函数名即可

## 内联函数

内联函数：编译器使用相应的函数代码替换函数调用，能提高运行效率，但整体来看，作用不大  
inline 函数&lt;声明&gt;和&lt;定义&gt;前加 inline  
内联函数不能递归  
内联函数和常规函数一样，也是按值传递参数，如果参数为表达式，内联函数将传递表达式的值

C define宏通过文本替换实现

## 变量引用

引用变量主要用途是用作函数的形参  
记住：必须在声明引用时进行初始化  
引用更接近const指针，必须在创建时初始化，一旦与某个变量关联，就将一致效忠于它//引用不能修改指针的值，但能修改值  
int \* const pr = &rats;  

```cpp
int rats;
cint & rodents = rata //int &是指向int的引用
cout << &rodents << endl  //&是地址操作符，表示rondents引用变量的地址
```
  
当数据量比较大时，引用参数将很有用  

如果实参与引用参数不匹配，c++将生成临时变量  
临时变量只在函数调用期存在，  
如果声明将引用指定为const，c++将在必要的时候生成临时变量  
如果引用参数是const，则编译器将在下面两种情况下生成临时变量：  
1 实参类型正确，但不是左值  
2 实参类型不正确，转换成正确的类型

派生类继承了基类的方法  
基类可以指向派生类对象，而无需进行强制类型转换。这种特征的一个实际结果是，可以定义一个接收基类引用作为参数的函数

## 默认参数

必须通过函数原型设置默认值  
仅当函数基本上执行相同的任务，但使用不同形式的数据时，才应该采用函数重载

## 函数重载

特征标，而不是函数类型使得可以对函数进行重载  
如果函数需要不同类型的参数时，默认参数就不管用了，这时候应该使用函数重载

## 函数模板

模板允许以通用类型的方式编写程序，这种类型是用参数表示对额，因此模板特性有时被称为参数化类型(parameterized types)

template

具体化机制：  
如果有多个原型，编译器在选择原型时，非模板版本将优先显式具体化和模板版本；显式具体化将优先于使用模板生成的版本

实例化：  
模板并非函数定义，但是使用int的模板实例是函数定义，这叫隐式实例化

隐式实例化、显式实例化和显式具体化统称为具体化，表示都i是使用具体类型的函数定义

template <> swap(int &, int &); //显式具体化

编译器选择函数版本策略：  
1 创建候选函数列表  
2 使用候选函数列表创建可行函数列表  
3 确定是否有最佳可行函数

分类: [all](https://www.cnblogs.com/apeishuai/category/2452653.html)

标签: [c++](https://www.cnblogs.com/apeishuai/tag/c%2B%2B/)

好文要顶 关注我 收藏该文 微信分享

[![](https://pic.cnblogs.com/face/3531360/20250403195920.png)](https://home.cnblogs.com/u/apeishuai/)

[Pomr](https://home.cnblogs.com/u/apeishuai/)  
[粉丝 - 0](https://home.cnblogs.com/u/apeishuai/followers/) [关注 - 2](https://home.cnblogs.com/u/apeishuai/followees/)  

0

0

[升级成为会员](https://cnblogs.vip/)

[«](https://www.cnblogs.com/apeishuai/articles/18733868) 上一篇： [C++ 类 对象模型 类构造及生命周期](https://www.cnblogs.com/apeishuai/articles/18733868 "发布于 2025-02-24 13:57")  
[»](https://www.cnblogs.com/apeishuai/articles/18736073) 下一篇： [c++ 类 基础](https://www.cnblogs.com/apeishuai/articles/18736073 "发布于 2025-02-25 13:48")

posted on 2025-02-25 13:44  [Pomr](https://www.cnblogs.com/apeishuai)  阅读(4)  评论(0)  [MD](https://www.cnblogs.com/apeishuai/articles/18736065.md)  [编辑](https://i.cnblogs.com/EditArticles.aspx?postid=18736065)  收藏  举报