# 动态内存管理
生命周期管理最佳实践

优先使用栈对象和智能指针
对于资源管理类，遵循RAII原则
明确所有权语义：
  独占所有权：unique_ptr
  共享所有权：shared_ptr
  无所有权：原始指针或引用
在多线程环境中特别注意共享对象的生命周期
使用移动语义优化资源转移
避免从构造函数中泄漏资源
考虑使用工厂函数返回智能指针


# 内存管理

1 优先使用栈对象
2 为必须使用new的情况编写RAII包装器


对象创建时机：	
	堆 & 栈
		栈：适用于生命周期明确，作用域内使用
		堆：适用于需要动态生命周期管理的对象
	线程安全创建对象
	单例模式与工厂模式
	初始化与延迟初始化
	异常安全与资源管理（RAII 智能指针shared_ptr weak_ptr）
		初始化、销毁
	Qt父子机制
		QObject  //继承自QObject的类，建议用父子关系管理内存
		结合QThread使用

//栈分配
void MyClass::showMessage() {
    QMessageBox msgBox;  // 栈上创建，自动释放
    msgBox.setText("Hello");
    msgBox.exec();
}
//堆分配+指定parent
// 在类成员中
MainWindow::MainWindow(QWidget *parent) 
    : QMainWindow(parent) 
{
    m_button = new QPushButton("Save", this); // this 作为 parent
    m_label = new QLabel("Status", this);
}
//智能指针组合
// 使用 QSharedPointer 管理无 parent 的对象
QSharedPointer<QFile> file = QSharedPointer<QFile>::create("data.txt");
// 或者使用 std::unique_ptr
std::unique_ptr<QTimer> timer(new QTimer());


C++ 里可能出现的内存问题大致有这么几个方面：
1. 缓冲区溢出（buffer overrun）。
2. 空悬指针/野指针。
3. 重复释放（double delete）。
4. 内存泄漏（memory leak）。
5. 不配对的 new[]/delete。
6. 内存碎片（memory fragmentation）。


1. 缓冲区溢出：用 std::vector<char>/std::string 或自己编写 Buffer class 来
管理缓冲区，自动记住用缓冲区的长度，并通过成员函数而不是裸指针来修改
缓冲区。
2. 空悬指针/野指针：用 shared_ptr/weak_ptr，这正是本章的主题。
3. 重复释放：用 scoped_ptr，只在对象析构的时候释放一次。
4. 内存泄漏：用 scoped_ptr，对象析构的时候自动释放内存。
5. 不配对的 new[]/delete：把 new[] 统统替换为 std::vector/scoped_array(unique_ptr)。
6. 内存碎片：暂时不需要处理

# 指针
```
shared_ptr  //共享所有权 ，引入计数
    使用场景：
        普通对象分配
        对象共享所有权
        作为类成员

make_shared  //宏，不需要new，用一个控制块连接shared_ptr

1 直接使用new + shared_ptr构造函数
  std::shared_ptr<MyClass> ptr(new MyClass());  // 这里确实调用了new；；控制块和对象内存一起分配，共有两次分配；会有内存泄漏问题(如果shared_ptr初始化失败，之前new的内存将不会被释放)
  VS xx = new class(); shared_ptr(xx)     //和上一种写法比，多了双重释放风险
2 使用std::make_shared
  auto ptr = std::make_shared<MyClass>();  
3 从已有的shared_ptr创建
auto ptr2 = ptr  //auto 自动类型推导
auto ptr3(ptr)
4 从weak_ptr升级
std::weak_ptr<MyClass> weak = ptr;
auto ptr4 = weak.lock

一个类多个实例
多个指针共享一个对象所有权
管理动态数组

结论：
优先使用make_shared；只有在需要自定义删除器或者特殊内存时才直接用new；避免混合使用new和shared_ptr的裸指针构造函数
  自定义删除：文件句柄需要特殊关闭方式；数组需要delete[]
  需要自定义内存分配方式：aligned_alloc分配对齐内存
  需要延迟初始化
  需要共享同一个对象的多个不同指针
  需要避免make_shared的内存捆绑

make_shared 会将对象和控制块分配在连续内存中，这意味着即使所有 shared_ptr 都释放了，如果还有 weak_ptr 存在，对象占用的内存可能不会立即释放（因为控制块需要保留）
make_shared 不支持自定义删除器，如果需要自定义删除器，必须直接使用 shared_ptr 构造函数
weak_ptr 不能直接解引用，必须先用 lock() 方法转换为 shared_ptr
    

unique_ptr  //独占所有权
weak_ptr  //观察而不拥有
scope_ptr  //作用域结束时自动释放所管理的对象

```

# RAII vs 智能指针
特性	自定义 RAII 类	智能指针\
资源释放逻辑	完全自定义	固定为 delete/deleter\
多资源管理	单类管理多个资源	每个指针管理一个资源\
移动语义支持	可自定义	自动提供\
线程安全性	自行实现	内置支持(shared_ptr)\
开发效率	需要更多代码	快速简单\
性能开销	可优化到最小	有引用计数开销\
适用场景	复杂资源管理	简单内存管理