![](/skins/bj2008/images/fire.gif) [c++ 类 基础](https://www.cnblogs.com/apeishuai/articles/18736073 "发布于 2025-02-25 13:48")

chapter 10、11、12

不要将函数定义或者变量声明放到头文件  
例如，如果在头文件包含一个函数定义，然后再其他两个文佳佳你(属于同一个程序)中包含该头文件，则同一个程序中将包含同一个函数的两个定义

# 对象和类

### 类的使用

![](https://img2024.cnblogs.com/blog/3531360/202503/3531360-20250311131702615-112195734.png)

要创建类对象，可以声明类变量，也可以使用new为类对象分配存储空间  
可以将对象作为返回值，也可以把一个赋值给另一个

* 类方法可以访问类的private组件
* 使用作用域解析操作符(::)标识函数所属的类

### 类的构造和析构

因为类的数据对象私有的，c++提供了特殊的成员函数：类构造函数，专门用于构造新对象，  
程序声明对象时，将自动调用构造函数  
构造函数的参数表示的不是类成员，而是赋予类成员的值。因此，参数名不能与类成员相同，通常做法是在数据成员名中使用m_前缀

stick food = stock("world cabage",250,1.25) //显示构造  
stock garment("furry Mason",50,2.5) //隐式构造

c++标准允许编译器使用两种方式执行显式构造，一种是创建一个名为Stock的对象，并将其数据成员初始化为指定的值；另一种方法是允许构造函数创建一个临时对象，，然后将该临时对象复制到stock2中，并丢弃它，如果使用第二种方式，则将为临时对象调用析构函数

Stock \*pstock = new Stock("Electroshock Games",18,19.0) //对象指针  
（无法使用对象来调用构造函数，在构造函数构造出对象前，对象是不存在的）

默认构造函数可能如下：  
STock::stock(){}，当且没有定义任何构造函数时，编译器才会提供默认构造函数。

与构造函数不同的是，析构函数没有参数，因此Stock析构函数的原型必须是：  
~Stock():  
通常不应该在代码中显式的调用析构函数（例外情形，参阅12章 new操作符），由于类对象过期时析构函数将会被自动调用，因此必须有一个析构函数。如果程序员没有提供析构函数，编译器将声明一个默认析构函数，并在发现导致对象被删除的代码后，提供默认析构函数的定义

explict：  
explicit关键字只需用于类内的单参数构造函数前面。由于无参数的构造函数和多参数的构造函数总是显示调用，这种情况在构造函数前加explicit无意义。  
effective c++中说：被声明为explicit的构造函数通常比其non-explicit兄弟更受欢迎。因为它们禁止编译器执行非预期（往往也不被期望）的类型转换。除非我有一个好理由允许构造函数被用于隐式类型转换，否则我会把它声明为explicit，鼓励大家遵循相同的政策

### 对象复制

stock2=stock1  
默认情况下，给类对象赋值时，将把一个对象成员复制给另一个

### const成员函数

class const的对象，函数承诺不改变私有变量属性  
void show() const; // promise not to change invoking object  
void stock::show() const //promise not to change invoking object

### this 指针

this指针指向用来调用成员函数的对象(this被作为隐藏参数传递给方法)  
每个成员函数（包括构造函数和析构函数）都有一个this指针，this指针指向调用对象，如果方法需要引用整个调用对象，可以使用_this  
this是对象的地址，而对象本身，是_this，返回类型引用意味着返回的是调用对象本身，而不是其拷贝

### 对象数组

### 接口

修改类的私有部分和实现文件属于实现变更；修改类的公有部分属于接口变更。  
Stock::Stock(const char \* co,int n, double pr)

{company = co;}  
{  
std::strncpy(company,co,29);  
company\[29\]='\\0';  
}

### 类作用域

使用类成员名时，必须根据上下文使用直接操作符(.)、间接成员操作符(->)或者作用域解析操作符(:😃  
static： 为整个对象作用域创建常量  

```cpp
class String {
private:
    static int num_strings;  // 静态数据成员
    char* str;
    int len;
public:
    // 静态成员函数
    static int HowMany() { return num_strings; } 
    // 可以访问num_strings，但不能访问str和len
};

int String::num_strings = 0;  // 静态成员初始化

// 使用方式
int count = String::HowMany();  // 正确调用方式
```

```kotlin
静态成员函数的核心特性
调用方式：
不能通过对象实例调用
使用类名加作用域解析运算符直接调用（如 String::HowMany()）

this指针限制：
静态成员函数没有隐含的 this 指针
因此不能访问类的非静态成员（实例变量和方法）

访问权限：只能访问类的其他静态成员（静态变量和静态方法）
```

enum {len=30}，也可以创建常量

### ADT

### 运算符重载

operator op(argument-list)

重载操作符限制：  
1 重载后的操作符必须至少有一个操作数是用户定义的类型  
2 使用操作符时不嫩那个违反原来的语法规则  
3 不能定义新的操作符  
4 不能重载下面的操作符  
  
  
可以重载如下操作符  

### 友元函数

运算符重载，有参数顺序问题，可以建立非成员操作符重载函数  
friend Time operator\* (double m, const Time & t); // goes in class declaration  
1 不是成员函数，不能使用成员操作符  
2 虽然不是成员函数，但与成员函数的访问权限相同

应将友元函数看作类的扩展接口的组成部分

常用的友元：

### 类型转换

c++不自动转换不兼容的类型  
可以将类定义成与基本类型或另一个类相关，使得从一种类型转换为另一种类型是有意义的

构造函数作为自动类型转换函数(隐式转换)，构造函数创建一个临时对象，采用逐成员赋值的方式将该临时对象的内容复制到xx中  
explicit 关键字关闭这种自动特性

函数原型化提供的参数匹配过程，允许使用构造函数来转换其他数值类型，但是，当且仅当转换不存在二义性时，才会进行这种二步转换

要进行相反的转换，需要用到转换函数，转换函数是用户定义的强制类型转换，可以像使用强制类型转换那样使用  
stonewt wells(20,3)  
double star = wells

operator typeName();

# 类和动态内存分配

不能在类声明中初始化静态成员变量，这是因为声明描述了如何分配内存，但并不分配内存

隐式成员函数：

* 默认构造函数，如果没有定义构造函数
* 复制构造函数，如果没有定义
* 赋值操作符，如果没有定义
* 默认析构函数，如果没有定义
* 地址操作符，如果没有定义

### 类复制构造

类复制构造原型：  
class_name(const Class_name &)

新建一个对象并将其初始化为同类现有对象时，复制构造函数将被调用  
StringBad ditto(motto)  
StringBad metoo = motoo  
StringBad also = StringBad(motoo)  
StringBad \* pStringBad = new StringBad(motoo)

浅复制：  
默认的复制构造函数诸葛复制非静态成员，复制的是成员的值  
深复制：  
将字符串内容也复制给新创建变量

Class_name & Class_name::operator=(const Class_name &)，接收并返回一个指向类对象的引用  
StringBad & StringBad::operator=(const StringBad &)

# 类继承

### 多态公有继承

* 在派生类中重新定义基类的方法
* 使用虚方法

纯虚函数：如果希望派生类能够重新定义方法，应在基类中将方法定义为虚拟的，这样可以启动动态联编  

ABC：接口规则

# c++代码重用

# 输入、输出和文件

## 访问权限总结表

| 访问修饰符 | 类内部 | 派生类 | 类外部 |
| --- | --- | --- | --- |
| `public` | ✅ 可访问 | ✅ 可访问 | ✅ 可访问 |
| `protected` | ✅ 可访问 | ✅ 可访问 | ❌ 不可访问 |
| `private` | ✅ 可访问 | ❌ 不可访问 | ❌ 不可访问 |

* * *

## 关键点

* **`public`**  
    → 开放接口，任何地方都能访问。  
    → 通常用于类的外部接口方法或需要公开的数据。
    
* **`private`**  
    → 隐藏实现细节，仅限类内部使用。  
    → 确保数据安全性，防止外部直接修改。
    
* **`protected`**  
    → 介于 `public` 和 `private` 之间，允许派生类访问，但对外隐藏。  
    → 主要用于继承体系，方便子类扩展功能。
    

## 应用类类型
类类型	主要用途	典型示例
接口类	定义行为规范	Runnable, Comparable
数据类	存储数据	UserDTO, Product
抽象类	提供部分实现	AbstractList
服务类	封装业务逻辑	UserService
工具类	提供静态辅助方法	StringUtils
控制器类	处理用户输入/HTTP 请求	UserController
工厂类	创建对象	CarFactory
单例类	全局唯一实例	DatabaseConnection
装饰器类	动态扩展功能	BufferedInputStream
观察者类	事件监听	MouseListener
