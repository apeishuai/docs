![](/skins/bj2008/images/fire.gif) [c++ qt](https://www.cnblogs.com/apeishuai/articles/18801515 "发布于 2025-03-31 08:58")

qapplication  
![](https://img2024.cnblogs.com/blog/3531360/202504/3531360-20250415065404922-164547254.png)  
![](https://img2024.cnblogs.com/blog/3531360/202504/3531360-20250415065459756-1186424140.png)  
![](https://img2024.cnblogs.com/blog/3531360/202504/3531360-20250415065534761-1776692729.png)  
![](https://img2024.cnblogs.com/blog/3531360/202504/3531360-20250423145838516-644006726.png)  
![](https://img2024.cnblogs.com/blog/3531360/202504/3531360-20250423150258663-1226200155.png)  
![](https://img2024.cnblogs.com/blog/3531360/202504/3531360-20250423150934317-746191574.png)  
![](https://img2024.cnblogs.com/blog/3531360/202504/3531360-20250423151434760-2100714304.png)

































# qt version

[qt version history](https://wiki.qt.io/Qt_version_history)  
[qt releasing](https://wiki.qt.io/QtReleasing)

qt版本确认：
Qt一共有几百个版本，关于如何选择Qt版本的问题，我一般保留四个版本，为了兼容Qt4用4.8.7，最后的支持XP的版本5.7.0，最新的长期支持版本比如5.15，最高的新版本比如5.15.2。强烈不建议使用4.7以前和5.0到5.3之间的版本（Qt6.0到Qt6.2之间、不含6.2的版本也不建议，很多模块还没有集成），太多bug和坑，稳定性和兼容性相比于之后的版本相当差，能换就换，不能换睡服领导也要换。如果没有历史包袱建议用5.15.2，目前新推出的6.0版本也强烈不建议使用，官方还在整合当中，好多类和模块暂时没有整合，需要等到6.2.2版本再用。考虑到qss性能以及自带mysql驱动的因素，最终Qt5选用5.12.3，Qt4选用4.8.7，Qt6选用6.5.x。


# qt tools

qt maintenance tools: 维护工具

# 基础

## 内存安全

qsharedpointer  //引用计数
qweakpointer //配套qsharedpointer，避免循环计数
qscopedpointer //作用域指针
qpointer  //专为QObject设计的弱指针

## MOC meta object compliar

## 信号与槽

信号发生器：

只有 QObject 及其派生类才能使用信号和槽机制，且在类之中还需要使用 Q_OBJECT 宏。  
信号由 moc 自动生成，不得在 .cpp 文件中实现。  

信号创建规则：  
信号使用 signals 关键字声明，在其后面有一个冒号“:”，在其前面不能有 public、private、protected 访问控制符，信号默认是 public 的。  
信号只需像函数那样声明即可，其中可以有参数，参数的主要作用是用于和槽的通信，这就像普通函数的参数传递规则一样。信号虽然像函数，但是对他的调用方式不一样，信号需要使用 emit 关键字发射。  
信号只需声明，不能对其进行定义，信号是由 moc 自动生成的。  
信号的返回值只能是 void 类型的。

槽创建规则：  
声明槽需要使用 slots 关键字，在其后面有一个冒号“:”，且槽需使用 public、private、protected 访问控制符之一。  
槽就是一个普通的函数，可以像使用普通函数一样进行使用，槽与普通函数的主要区别是，槽可以与信号关联。

发射信号规则：  
发射信号需要使用 emit 关键字，注意，在 emit 后面不需要冒号。  
emit 发射的信号使用的语法与调用普通函数相同，比如有一个信号为 void f(int)，则发送的语法为：emit f(3);  
当信号被发射时，与其相关联的槽函数会被调用(注意：信号和槽需要使用  
QObject::connect 函数进行关联之后，发射信号后才会调用相关联的槽函数)。  
因为信号位于类之中，因此发射信号的位置需要位于该类的成员函数中或该  
类能见到信号的标识符的位置。

信号和槽的关系：  
槽的参数的类型需要与信号参数的类型相对应，  
槽的参数不能多余信号的参数，因为若槽的参数更多，则多余的参数不能接收到信号传递过来的值，若在槽中使用了这些多余的无值的参数，就会产生错误。  
若信号的参数多余槽的参数，则多余的参数将被忽略。  
一个信号可以与多个槽关联，多个信号也可以与同一个槽关联，信号也可以关联到另一个信号上。  
若一个信号关联到多个槽时，则发射信号时，槽函数按照关联的顺序依次执行。  
若信号连接到另一个信号，则当第一个信号发射时，会立即发射第二个信号。

高级用法
1. 自动管理对象生命周期
cpp
// 使用智能指针管理对象
class ClassManager : public QObject
{
    Q_OBJECT
public:
    explicit ClassManager(QObject *parent = nullptr);
    
    void setupConnections(QSharedPointer<ClassA> a, 
                         QSharedPointer<ClassB> b);

private:
    QSharedPointer<ClassA> m_classA;
    QSharedPointer<ClassB> m_classB;
};
2. 支持动态添加/移除连接
cpp
class ClassManager : public QObject
{
    // ... 其他代码 ...
    
public slots:
    void addConnection(ClassA* a, ClassB* b);
    void removeConnection(ClassA* a, ClassB* b);
};
3. 使用信号转发中心
cpp
class ClassManager : public QObject
{
    Q_OBJECT
public:
    // ... 其他代码 ...
    
signals:
    void forwardedSignalA(DataType data);
    void forwardedSignalB(DataType data);
    
private slots:
    void forwardSignalA(DataType data) { emit forwardedSignalA(data); }
    void forwardSignalB(DataType data) { emit forwardedSignalB(data); }
};


# 绘图

[QObject Class](https://doc.qt.io/qt-6/qobject.html#details)  
[QQuickItem Class](https://doc.qt.io/qt-6/qquickitem.html#QQuickItem)

[Qt Qml Tooling](https://doc.qt.io/qt-6/qtqml-tooling.html)  
[QPen Class](https://doc.qt.io/qt-6/qpen.html#QPen)

[QQuickPaintedItem Class](https://doc.qt.io/qt-6/qquickpainteditem.html#public-types)  

QPainter class

# [layout items using the concept of anchors](https://doc.qt.io/qt-6/qtquick-positioning-anchors.html)

# qml type registration

## QRect QPoint QColor

```php
QColor::QColor(Qt::GlobalColor color)
  ![](https://img2024.cnblogs.com/blog/3531360/202502/3531360-20250225144537373-846225590.png)

QPoint(int xpos, int ypos)

QRect::QRect(const QPoint &topLeft, const QPoint &bottomRight)
QRect::QRect(const QPoint &topLeft, const QSize &size)

QBrush::QBrush(const QColor &color, Qt::BrushStyle style = Qt::SolidPattern)
```

分类: [all](https://www.cnblogs.com/apeishuai/category/2452653.html)

好文要顶 关注我 收藏该文 微信分享

[![](https://pic.cnblogs.com/face/3531360/20250403195920.png)](https://home.cnblogs.com/u/apeishuai/)

[Pomr](https://home.cnblogs.com/u/apeishuai/)  
[粉丝 - 0](https://home.cnblogs.com/u/apeishuai/followers/) [关注 - 2](https://home.cnblogs.com/u/apeishuai/followees/)  

0

0

[升级成为会员](https://cnblogs.vip/)

[«](https://www.cnblogs.com/apeishuai/articles/18801472) 上一篇： [电机选型](https://www.cnblogs.com/apeishuai/articles/18801472 "发布于 2025-03-31 08:21")  
[»](https://www.cnblogs.com/apeishuai/articles/18805455) 下一篇： [模拟电路](https://www.cnblogs.com/apeishuai/articles/18805455 "发布于 2025-04-02 10:06")

posted on 2025-03-31 08:58  [Pomr](https://www.cnblogs.com/apeishuai)  阅读(2)  评论(0)  [MD](https://www.cnblogs.com/apeishuai/articles/18801515.md)  [编辑](https://i.cnblogs.com/EditArticles.aspx?postid=18801515)  收藏  举报