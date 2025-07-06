![](/skins/bj2008/images/fire.gif) [c++多线程](https://www.cnblogs.com/apeishuai/articles/18909541 "发布于 2025-06-04 09:43")

# 并发编程模型
1 Reactor + Thread Pool  //IO密集型
2 per thread one loop + event loop + 任务队列
	event loop模型没有标准实现，如果自己写代码，尽可能按所用Reactor的推荐方式来编程	
3 Proactor + 异步IO
4 数据并行模式

message passing  //消息传递\
shared memory   //共享内存

基本线程原语选用：
Thread、mutex、Condition
<thread> <Boost.Thread> //使用这两个库

任务队列执行模式： //队列是调度机制，执行方式取决于消费者设计
串行执行、并行执行、混合模式

串行方案：QObject+信号槽
并行方案：QtConcurrent

![](/img/Capturer_2025-07-03_084955_187.png)


## IO模型
阻塞IO
非阻塞IO
select/poll
epoll/kequeue
信号驱动IO
异步IO     //高性能服务器
Reactor    //事件驱动
Proactor


Reactor模式：

  ┌─────────────┐     ┌─────────────┐
  │   Reactor   │←───→│ Event Demux │
  └─────────────┘     └─────────────┘
        ↑
        │ 分发
        ↓
  ┌─────────────┐
  │ Event Handler│
  └─────────────┘

Reactor：事件循环核心，负责调度
Event Demultiplexer：系统级I/O多路复用(select/poll/epoll)
Event Handler：具体事件处理接口
Concrete Event Handler：实际事件处理实现


## 任务调度与协调
任务队列+线程池
BlockingQueue 生产者消费者队列

阻抗匹配：
密集计算所占时间比重P(0<P<=1)，系统共有C个CPU，为了让这C个CPU跑满而又不过载。线程池大小公式：T=C/P

P<0.2，这个公式就不适用，T可以取一个固定值，比如5*C。


# shared memory
race condition

死锁：

```scss
void func1()                    
{                       
    LOCK(&mutex_a);                      
    LOCK(&mutex_b);//线程1停滞在此         
    counter++;                       
    UNLOCK(&mutex_b);                     
    UNLOCK(&mutex_a);                    
}                       
void func2()
{
    LOCK(&mutex_b);
    LOCK(&mutex_a);//线程2停滞在此
    counter++;
    UNLOCK(&mutex_a);
    UNLOCK(&mutex_b);
}
```

# 多线程
线程管控\
	基本管控\
	向线程函数传递参数\
	移交线程归属权\
	运行时选择线程数量\
	识别线程\
线程间共享数据\
并发操作同步\
c++内存模型和原子操作\
设计基于锁的并发数据结构\
设计无锁数据结构\
设计并发代码\
	线程间切分任务的方法\
		先切分数据，再开始处理\
		递归方式划分数据\
		依据工作类别划分任务（分离关注点、）\
			问题点：线程间有大量共享数据(说明划分不对)\
		线程间按流程划分任务\	
	影响并发代码性能的因素\
		处理器数量\
		数据竞争和缓存乒乓\
		数据的紧凑程度\
		过度任务切换和线程过饱和\
	设计数据结构提升多线程性能\	
		针对复杂操作的数据划分(数组操作)\

		其他数据类型：（缓存一致性协议（MESI）的强制同步；锁和数据再同一缓存行会破坏A的数据独占，造成性能损失）
		
高级线程管理\
并行算法函数\
多线程应用的测试和除错