![](/skins/bj2008/images/fire.gif) [c++ 基础](https://www.cnblogs.com/apeishuai/articles/18828886 "发布于 2025-04-16 16:01")

# initize and 作用域 and 生命周期

不同的C++存储方式是通过存储持续性、作用域和链接性来描述的。

### 存储持续性

自动存储：函数定义中声明的变量(包括函数参数)的存储持续性为自动的。它们在程序开始执行其所属的函数或者代码块时被创建，执行完函数或者代码块，它们使用的内存被释放。（2种）

初始化：可以使用任何在声明时其值为已知的表达式来初始化自动变量  
auto 或者默认，堆栈中分配、register 寄存器分配

静态存储：函数定义外定义的变量，或者使用static关键字定义的变量存储周期都为静态，它们在程序的整个运行过程中都存在（3种）

初始化：  
静态变量的数目在程序运行期间不变，编译器将分配固定的内存块来存储所有静态变量，如果没有显式的初始化静态变量，编译器将其设置为0；静态存储区的变量地址在编译期确定，只能用

```csharp
// file.c
int global = 1000; // static duration, external linkage
static int one = 50; // static duration, internal linkage

void func(){
  static int count = 0; //static duration, no linkage  该变量虽然只在代码块中使用，代码块非活动状态也能存在
}
```

动态存储：new操作符分配的内存将一直存在，直到使用delete操作符将其释放或程序结束为止

```csharp
#include <new>
struct chaff{
  char dross[20];
  int slag;
};
char buffer1[50];
char buffer2[500]
int main(){
  chaff *p1,*p2;
  int *p3,*p4;
  p1 = new chaff; //place structure in heap
  p3 = new int[20]; //place int array in heap
  p2 = new (buffer1) chaff; //place structure in buffer1
  p4 = new (buffer2) int[20]; //place int array in buffer2
}
```

### 作用域：描述名称在文件多大范围可见：

函数定义变量：该函数中使用  
文件函数外定义变量：整个文件的函数可用

作用域为局部：的变量只能在定义它的代码块中使用，{}  
作用域为全局(文件作用域)：的变量在定义位置到文件结尾之间都可用

自动变量作用域为局部  
静态变量的作用域是全局还是局部取决于它是如何被定义的  
函数原型(声明)作用域中使用的名称只在包含参数列表的括号内可用，(定义)名称在整个函数可用  
类中声明的成员的作用域为整个类  
名称空间声明的变量作用域为整个名称空间  
c++函数的作用域可以是整个类或整个名称空间

### 链接性：外部的名称可以在文件之间共享

链接性为外：的名称可以在文件间共享，  
链接性为内：的名称只能由一个文件中的函数共享，  
自动变量：的名称没有链接性，因为它们不能共享

链接性为外部的变量通常简称为外部变量,它们的存储持续性为静态,作用域为整个文件

double warming = 0.3: 称为定义声明(defining declaration)或简称为定义(definition)。它给该变量分配存储空间  
extern double warming: 称为引用声明 (referencing declaration),或简称为声明(declaration)。它不给变量分配存储空间,因为它引用己有的变量，只能在引用其他地方(或函数)定义的变量的声明中使用关键字  
extern double warming = 0.5: // INVALID  
仅当声明将为变量分配存储空间时(即定义声明),才能在声明中初始化变量。毕竟,初始化指的是在分配内存单元时给它赋值。  
表明,定义与全局变量同名的局部变量后,局部变量将隐藏全局变量。C++比C语言进了一步——它提供了作用域解析操作符()。当放在变量名称前面时,该操作符表示使用变量的全局版本。

const全局变量链接性为内部  
如果出于某种原因,程序员希望某个常量的链接性为外部的,则可以使用 extern 关键字来覆盖默认的内部链接性  
extern const int states = 50: // external linkage  
在函数或代码块中声明 const 时,其作用域为代码块

C++修改了常量类型的规则,让程序员更轻松。例如,假设将一组常量放在头文件中,并在同一个程  
序的多个文件中使用该头文件。那么,预处理器将头文件的内容包含到每个源文件中后,所有的源文件都  
将包含类似下面这样的定义:  
const int fingers = 10:  
const charr \* warning - "Wak! ";

单定义规则：对每个非内联函数，程序中只能包含一个定义  
内联函数：允许其定义放在头文件中。c++要求同一个函数的所有内联定义必须相等

数据共享：  
外部链接性  
名称空间提供了另外一种共享数据的方法,C++标准指出,使用 static 来创建内部链接性的方法将逐步被淘汰

const：内存初始化后，程序便不能再进行修改  
//colatile：即使程序代码没有对内存单元进行修改，其值也可能发生变化  
//mutable：即使结构(或类)的变量为const，其某个成员也可以被修改

### 名称空间

using声明使一个名称可用，using编译指令使所有名称可用

```cpp
namespace Jill{
  double bucket(double n) {...};
  double fetch;
  struct Hill {...};
}
char fetch;
int main(){
  using namespace Jill;
  Hill Thrill;
  double water = bucket(2)'
  double fetch; //not an error: hides Jill:fetch
  cin >> fetch; //read a value into the local fetch
  cin >> ::fetch; //read a value int global fetch
  cin >> Jill::fetch; //read a value into Jill::fetch
  ...
}
```

名称空间类似于无限层级的标签，  
未命名的名称空间：  
namespace{  
int ice;  
int bandycoot; //作用域：声明点到该声明的末尾区域。不能再未命名名称空间所属文件之外的其他文件使用该变量，这种方法可以替代链接性为内部的静态变量。  
//c++标准不赞成在名称空间和全局作用域使用static  
}

# 关键字

Specifiers：The following keywords are storage class specifiers ﻿:

auto (until C++11)  
register (until C++17)  
static  
thread_local (since C++11)  
extern  
mutable  
inline ： 编译器行为优化

Static storage duration：  
A variable satisfying all following conditions has static storage duration ﻿:  
It belongs to a namespace scope or are first declared with static or extern.  
It does not have thread storage duration. (since C++11)  
The storage for these entities lasts for the duration of the program. //维持在整个程序的生命周期
