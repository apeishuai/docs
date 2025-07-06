# 多线程模型分析
长生命周期：
短生命周期：

# 在Qt中实现线程安全的主要方法包括
使用QThread和moveToThread()管理线程
	线程对象的生命周期：
	默认情况，使用exec()事件循环；线程不会自动结束，除非显式调用quit()或exit()
	重写run方法，线程结束后自动退出；如果run方法中有exec()，则不会自动结束
	
通过信号与槽实现线程间通信。

使用QMutex和QReadWriteLock保护共享资源。
使用QAtomicInt等进行无锁操作。

使用QSemaphore和QWaitCondition进行复杂同步。
使用QtConcurrent避免手动线程管理。
最推荐的方式是结合信号与槽和事件循环，因为它们利用了Qt的核心优势，简单且安全。对于性能敏感场景，可考虑QAtomicInt或QReadWriteLock；复杂同步需求则使用QSemaphore或QWaitCondition。

# qt thread

1 qthread子类化  
简单的独立任务  
不需要事件循环的纯计算  
已有基于run()的遗留代码  
2 movetothread  
需要事件循环  
有多个任务在同一线程执行  
需要频繁与主线程通信  
使用qt的网络、数据库等模块  
3 QThreadPool and QRunnable  
大量短期任务（几十到几百个）（毫秒到秒级）  
无阻塞的纯计算任务  
可并行处理的独立任务  
不需要复杂通信的任务  
4 concurrent  
异步执行  
map-reduce计算  
数据并行处理

# QThread
begin executing in run(), by default, run() starts the event loop by calling exec() and runs a Qt event loop inside the thread. 

run()
    不重写run()，
        线程会启动自己的事件循环
        主线程的事件循环不受影响
    重写run()但不调用exec()
        线程执行完run()后代码会退出
        主线程的事件循环不受影响
    重写run()并调用exec()
        线程会运行自己的事件循环
        主线程的事件循环仍然独立运行
start()
wait()

# MoveToThread
创建QObject派生类，
在槽函数中实现
通过信号槽控制 //线程亲和性
自动拥有事件循环


To move an object to the main thread, use QApplication::instance() to retrieve a pointer to the current application, and then use QApplication::thread() to retrieve the thread in which the application lives. For example:
```
myObject->moveToThread(QApplication::instance()->thread());
```

# QRunnable + QThreadPool





# QConcurrent  //非阻塞式
## basic mode
### Running a Function in a Separate Thread
```
extern void aFunction();
QFuture<void> future = QtConcurrent::run(aFunction);
```

```
extern void aFunction();
QThreadPool pool;
QFuture<void> future = QtConcurrent::run(&pool, aFunction);
```
### Passing arguments to the Function
```
extern void aFunctionWithArguments(int arg1, double arg2, const QString &string);

int integer = ...;
double floatingPoint = ...;
QString string = ...;

QFuture<void> future = QtConcurrent::run(aFunctionWithArguments, integer, floatingPoint, string);
```

call the overload function through lambda:
```
QFuture<void> future = QtConcurrent::run([] { foo(42); });
```
tell the compiler which overload to choose by using a static_cast
```
QFuture<void> future = QtConcurrent::run(static_cast<void(*)(int)>(foo), 42);
```
```
QFuture<void> future = QtConcurrent::run(qOverload<int>(foo), 42);
```
### Return Values from the function
```
extern QString functionReturningAString();
QFuture<QString> future = QtConcurrent::run(functionReturningAString);
...
QString result = future.result();
```
```
extern QString someFunction(const QByteArray &input);

QByteArray bytearray = ...;

QFuture<QString> future = QtConcurrent::run(someFunction, bytearray);
...
QString result = future.result();
```

