![](/skins/bj2008/images/fire.gif) [c语言](https://www.cnblogs.com/apeishuai/articles/18758967 "发布于 2025-03-08 09:52")

# c语言历史

![](https://img2024.cnblogs.com/blog/3531360/202504/3531360-20250404084424321-1911334526.png)  
![](https://img2024.cnblogs.com/blog/3531360/202504/3531360-20250404084610940-380266242.png)  
早期c语言某些特性是为编译器设置的

* 预处理器：字符串替换、头文件包含、宏
* K&R C &lt;THE C PROGRAMMING LANGUAGE·&gt;
* ANSI C

标准问题：语义不清晰，产生误解(语法、语义分析)

编程语言缺陷分析：  
该做的没做好、不该做的做了、该做的没做

# Storage duration

Every object has a property called storage duration, which limits the object lifetime. There are four kinds of storage duration in C:

automatic storage duration. The storage is allocated when the block in which the object was declared is entered and deallocated when it is exited by any means (goto, return, reaching the end). One exception is the VLAs; their storage is allocated when the declaration is executed, not on block entry, and deallocated when the declaration goes out of scope, not when the block is exited(since C99). If the block is entered recursively, a new allocation is performed for every recursion level. All function parameters and non-static block-scope objects have this storage duration, as well as compound literals used at block scope(until C23)  
当block结束，变量被释放；VLA(变长数组)是例外，在声明时分配内存，声明的作用域结束时候释放内存

static storage duration. The storage duration is the entire execution of the program, and the value stored in the object is initialized only once, prior to main function. All objects declared static and all objects with either internal or external linkage that aren't declared \_Thread_local(until C23)thread_local(since C23)(since C11) have this storage duration.  
static storage存在程序执行的整个周期，只初始化一次，static声明和具有内外部链接的变量have this storage duration

thread storage duration. The storage duration is the entire execution of the thread in which it was created, and the value stored in the object is initialized when the thread is started. Each thread has its own, distinct, object. If the thread that executes the expression that accesses this object is not the thread that executed its initialization, the behavior is implementation-defined. All objects declared \_Thread_local(until C23)thread_local(since C23) have this storage duration.  
(since C11)

allocated storage duration. The storage is allocated and deallocated on request, using dynamic memory allocation functions.

# Linkage

Linkage refers to the ability of an identifier (variable or function) to be referred to in other scopes. If a variable or function with the same identifier is declared in several scopes, but cannot be referred to from all of them, then several instances of the variable are generated. The following linkages are recognized:

no linkage. The variable or function can be referred to only from the scope it is in (block scope). All block scope variables that are not declared extern have this linkage, as well as all function parameters and all identifiers that aren't functions or variables.

internal linkage. The variable or function can be referred to from all scopes in the current translation unit. All file scope variables which are declared static or constexpr(since C23) have this linkage, and all file scope functions declared static (static function declarations are only allowed at file scope).

external linkage. The variable or function can be referred to from any other translation units in the entire program. All file scope variables which are not declared static or constexpr(since C23) have this linkage, all file scope function declarations which are not declared static, all block scope function declarations, and, additionally, all variables or functions declared extern have this linkage unless a prior declaration with internal linkage is visible at that point.

If the same identifier appears with both internal and external linkage in the same translation unit, the behavior is undefined. This is possible when tentative definitions are used.

# scope

Each identifier that appears in a C program is visible (that is, may be used) only in some possibly discontiguous portion of the source code called its scope.  
Within a scope, an identifier may designate more than one entity only if the entities are in different name spaces.  
C has four kinds of scopes:

block scope:  
file scope  
function scope  
function prototype scope

# 声明

变量 函数： 声明、定义

函数声明默认extern，头文件有展开作用，如果不用头文件，直接在.c文件里extern声明也可以  
变量声明必须用extern xxx

```cpp
extern int a; // 声明一个全局变量 a
int a; // 定义一个全局变量 a
extern int a =0 ; // 定义一个全局变量 a 并给初值。
int a =0;    // 定义一个全局变量 a, 并给初值，
```

# 基础

echo | gcc -dM -E - | grep "**STDC_VERSION**" //查看gcc默认c标准  
gcc -print-search-dirs //打印索引路径

# 基础操作

## 关键字

static const //file scope，变量一直存在，inter link；block scope，变量一直存在，inter link  
  
extern //不用包含头文件，extern声明后，直接使用外部的函数和变量，但是编译的时候要添加文件  
restrict  
parama  
enum

## 函数

## 文件读取

C把文件看作是一系列连续的字节，每个字节都能被单独读取。  
C提供两种文件模式：文本模式和二进制模式。

用二进制编码的字符（例如， ASCII或Unicode）表示文本（就像C字符串那样），该文件就是文本文件  
如果文件中的二进制值代表机器语言代码或数值数据

### 字符串

分类: [all](https://www.cnblogs.com/apeishuai/category/2452653.html)

标签: [c](https://www.cnblogs.com/apeishuai/tag/c/)

好文要顶 关注我 收藏该文 微信分享

[![](https://pic.cnblogs.com/face/3531360/20250403195920.png)](https://home.cnblogs.com/u/apeishuai/)

[Pomr](https://home.cnblogs.com/u/apeishuai/)  
[粉丝 - 0](https://home.cnblogs.com/u/apeishuai/followers/) [关注 - 2](https://home.cnblogs.com/u/apeishuai/followees/)  

0

0

[升级成为会员](https://cnblogs.vip/)

[«](https://www.cnblogs.com/apeishuai/articles/18758930) 上一篇： [eplan插件开发](https://www.cnblogs.com/apeishuai/articles/18758930 "发布于 2025-03-08 09:20")  
[»](https://www.cnblogs.com/apeishuai/articles/18759183) 下一篇： [编译器](https://www.cnblogs.com/apeishuai/articles/18759183 "发布于 2025-03-08 13:25")

posted on 2025-03-08 09:52  [Pomr](https://www.cnblogs.com/apeishuai)  阅读(4)  评论(0)  [MD](https://www.cnblogs.com/apeishuai/articles/18758967.md)  [编辑](https://i.cnblogs.com/EditArticles.aspx?postid=18758967)  收藏  举报