![](/skins/bj2008/images/fire.gif) [C++ 类 对象模型 类构造及生命周期](https://www.cnblogs.com/apeishuai/articles/18733868 "发布于 2025-02-24 13:57")

class对象的生命周期：
class{
	function
	member
}
构造、析构、拷贝、赋值     (内存变化)

# 对象模型

(2种)class data member: static nonstatic  
(3种)class member functions: static nonstatic virtual

![](https://img2024.cnblogs.com/blog/3531360/202504/3531360-20250430082042257-932181455.png)

1.  数据成员（Data Members）

| 类型  | 存储位置 | 生命周期 | 访问方式 | 示例  |
| --- | --- | --- | --- | --- |
| static | 全局数据区（独立于对象） | 程序运行期间 | `类名::成员名` 或 `对象.成员` | `static int count;` |
| non-static | 对象内存中 | 随对象创建/销毁 | `对象.成员名` | `int value;` |

2.  成员函数（Member Functions）

| 类型  | 是否依赖对象实例 | 能否访问非静态成员 | 能否被重写（override） | 示例  |
| --- | --- | --- | --- | --- |
| static | ❌ 不依赖 | ❌ 不能 | ❌ 不能 | `static void print();` |
| non-static | ✅ 依赖 | ✅ 能 | ❌ 不能（除非是虚函数） | `void show();` |
| virtual | ✅ 依赖 | ✅ 能 | ✅ 能（支持多态） | `virtual void draw();` |

| 类的组成部分 | 存储位置 | 说明  |
| --- | --- | --- |
| 成员函数（非虚） | 代码段（.text 区） | 所有对象共享同一份函数代码，编译后固定在可执行文件中。 |
| 虚函数（virtual） | 虚函数表（vtable） | 存储在只读数据段（.rodata 或 .data），供所有对象共享。 |
| 静态成员变量 | 全局/静态数据区（.data/.bss） | 独立于对象存在，程序启动时初始化。 |
| RTTI（运行时类型信息） | 只读数据段 | 用于 typeid 和 dynamic_cast（如果有虚函数）。 |

# 初始化，

## default construct

(from C++ Standard)  
当类没有任何用户声明的构造函数时，编译器确实会隐式声明一个默认构造函数。这个隐式声明的默认构造函数是inline public的。  
对于Class X，如果没有任何user-declared constructor，那么会有一个default constrcutor被implicitly声明，一个被implicitly声明的default constructor将是一个trivial construcor

### nontrivial default constructor

如果该类型在构造时可能分配内存、加锁、调用外部API等，那它几乎肯定是非平凡的。  
如果它只是简单聚合数据（如POD类型），则可能是平凡的

如果class没有任何constructor，但是内含一个member object，而后者是default constructor，这个class的implicit default constructor就是"nontrivial"，编译器需要为此class合成一个default constructor，不过合成操作只有再constructpr真正需要被调用的时候才会发生。

编译器为避免合成出多个default constructor，解决方法是把合成的deafult constructor、copy constructor、destructor、assignment copy operator都以inline的方式完成，一个inline函数有静态链接，不会被档案以外者看到，如果函数太复杂，会合成一个explicit non-line static实体

被合成的default constructor只满足编译器的需要，而不是程序的需要

### user constrcutor

user所提供的constructors存在，所以不会合成新的default constructor。如果同时存在着"带有default constructors"的member class objects，那些default constructors也会被调用

### have virtual function

class 继承或声明一个 virtual function  
class 派生自一个继承串链，其中有一个或者更多的virtual base classes

由于缺乏user声明的constructor，编译器会详细记录合成一个default constructor的必要信息：  
virtual function table ： 内放class的virtual function地址  
每一个class object种，一个额外的pointer member被编译，内含相关的class vtbl地址  
virtual invocation会被重写

对于那些未声明的任何constructors的class，编译器会为它们合成一个default constructor，以便正确的初始化每一个class object的vptr

### have virtual base class

虚基类的构造函数由最派生类直接调用  
中间类（如A）对虚基类的构造调用可能被覆盖  
成员变量（如j）的初始化与普通类一致，不受虚继承影响

virtual base class的实现法在不同的编译器之间有极大的差异，共同点在于必须使virtual base class在其每一个derived class object中的位置，能够在执行期间准备妥当

```cpp
class X {public: int i;};
class A : public virtual X {public: int j;};
class B : public virtual X {public: double d;};
class C : public A, public B {public: int k;};

void foo(const A* pa){pa->i = 1024}

void foo(const A* pa) {pa->__vbcX->i = 1024;}
```

## copy constructor

1 Class X {...} ; 对一个object做明确的初始化工作  
X x;  
X xx = x

2 object被当作参数  
extern void foo(X x)

3 object被当作返回值  
X  
foo_bar{  
X xx;  
//...  
return xx;  
}

X::X(const X& x);  
当一个class object以另一个同类实体作为初值时，上述的constructor会被调用。这可能会导致一个暂时性的class object的产生或优化代码

### deafult memberwise initalizator

当class object以"相同class的另一个object"作为初值时，其内部是以所谓的default memberwise initializatior完成的  
拷贝其内建的member_occurs，然后再于String member object_word身上递归实施memberwise initialization  
c++ standard 把copy constructor区分为trivial和nontrivial两种，只有nontrivial的实体才会被合成于程序中，决定一个copy constructor是否为trivial的标准在于class是否展现“Bitwise Copy Semantics”  
  

一个class不展现出"bitwise copy semantics":  
1 class内含mamber object，而后者的class声明有一个copy constructor

```csharp
class A {
public:
    int* ptr;
    A(const A& other) {  // 自定义拷贝构造
        ptr = new int(*other.ptr);  // 深拷贝
    }
};
```

2 class继承自一个base class，而后者存在一个copy constructor  
3 class声明了一个或多个virtual functions  
4 class派生自一个继承串链，其中有一个或者多个virtual base classes

#### virtual functions

  
  
  
  

#### virtual base class subobject

一个class object如果以另一个object作为初值，而后者有一个virtual base class subobject，那么也会使"bitwise copy semantics"失效  
为了正确处理"以一个class object"作为另一个class object的初值，必须合成出一个copy constructor

### explicit initialization

必要的程序转化分两段：  
1 重写每一个定义，其中的初始化操作会被剥除  
2 class的copy constructor调用操作会被安插进去

### 参数初始化

策略1：\__temp object  
以class X的copy constructor正确设置初值，然后再以biewise方式拷贝到局部实体，形式参数从原来的class X object转换为class X reference；class X声明一个destructor，

策略2： 拷贝构建  
该位置视函数活动范围的不同记录于程序堆栈中

### 返回值初始化

1 加额外参数，类型是class object的一个reference  
2 return指令前安插一个copy constructor

分类: [all](https://www.cnblogs.com/apeishuai/category/2452653.html)

标签: [c++](https://www.cnblogs.com/apeishuai/tag/c%2B%2B/)

好文要顶 关注我 收藏该文 微信分享

[![](https://pic.cnblogs.com/face/3531360/20250403195920.png)](https://home.cnblogs.com/u/apeishuai/)

[Pomr](https://home.cnblogs.com/u/apeishuai/)  
[粉丝 - 0](https://home.cnblogs.com/u/apeishuai/followers/) [关注 - 2](https://home.cnblogs.com/u/apeishuai/followees/)  

0

0

[升级成为会员](https://cnblogs.vip/)

[«](https://www.cnblogs.com/apeishuai/articles/18732015) 上一篇： [windows](https://www.cnblogs.com/apeishuai/articles/18732015 "发布于 2025-02-24 13:28")  
[»](https://www.cnblogs.com/apeishuai/articles/18736065) 下一篇： [C++ 函数 指针](https://www.cnblogs.com/apeishuai/articles/18736065 "发布于 2025-02-25 13:44")

posted on 2025-02-24 13:57  [Pomr](https://www.cnblogs.com/apeishuai)  阅读(2)  评论(0)  [MD](https://www.cnblogs.com/apeishuai/articles/18733868.md)  [编辑](https://i.cnblogs.com/EditArticles.aspx?postid=18733868)  收藏  举报