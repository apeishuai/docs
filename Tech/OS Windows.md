![](/skins/bj2008/images/fire.gif) [OS Windows](https://www.cnblogs.com/apeishuai/articles/18737558 "发布于 2025-02-25 23:53")

# 虚拟机
qemu
https://qemu.weilnetz.de/w64/


# 进程

[vmmap](https://www.cnblogs.com/studyskill/p/8301870.html)  
[rammap+ vm map](https://www.cnblogs.com/gered/p/13905687.html)  
[procdump](https://www.cnblogs.com/yilang/p/12432509.html)


《深入解析Windows操作系统第四版.pdf》

![](https://img2024.cnblogs.com/blog/3531360/202503/3531360-20250331094121359-1550398671.png)

分类：  
固定系统支持进程  
服务进程  
用户应用程序  
开发环境支持

内核：windows executive、kernel、device driver、HAL(hardware abstraction layer)、windows and graphic system  
![](https://img2024.cnblogs.com/blog/3531360/202503/3531360-20250331095119100-1771757750.png)

# 进程

进程指一个容器，其中包含了当执行一个程序特定实例时用到的各种资源

* 私有的虚拟地址空间
* 可执行程序
* 已经打开句柄的列表，句柄指向各种资源
* 访问令牌的安全环境
* 进程ID的唯一标识符
* 至少一个执行线程

$tasklist

## 如何查看进程元信息
process exp \
process hacker \
process monitor \
win+r , resmon \
apimonitor \
VMMap 查看某个进程的内存使用状态（以及虚拟内存）  



# 系统安装
https://msdn.itellyou.cn/

# 软件包管理

scoop、msys2

# normal

sc query &lt;service.name&gt; \\查询服务名称

sc query Dhcp \\自动获取ip  
sc query Schedule \\执行计划任务  
sc query EventLog \\记录系统和应用程序事件  
sc query wuauserv \\检查、下载和安装windows更新

# 内存管理
phsycal : 

在一个进程的虚拟地址空间，物理上留驻在内存中的那一部分子集被称为工作集(working set)
当内存被过度提交时，系统会将内存中的有些内容转移到磁盘上

进程：私有地址空间

X86虚拟地址空间布局结构
![](/img/Capturer_2025-06-27_163740_145.png)
系统空间
![](/img/Capturer_2025-06-27_163925_012.png)

x64地址空间布局结构
![](/img/Capturer_2025-06-27_164226_359.png)
![](/img/Capturer_2025-06-27_164646_383.png)

页面帧状态
![](/img/Capturer_2025-06-27_165339_892.png)

用户模式内存分配
```
0x0000000000000000  ┌───────────────────────────────────────┐
                    │              **保留区**               │
                    │  (空指针访问拦截/未使用)               │
0x0000000000400000  ├───────────────────────────────────────┤
                    │              **代码段**               │
                    │  .text (程序指令, 只读)                │
0x0000000001000000  ├───────────────────────────────────────┤
                    │              **数据段**               │
                    │  .data (初始化全局变量)                │
                    │  .bss  (未初始化全局变量, 零页初始化)  │
0x0000000020000000  ├───────────────────────────────────────┤
                    │               **堆 Heap**             │
                    │  (动态内存分配: malloc/new → 向高地址增长)│
                    │                                       │
0x00007F0000000000  ├───────────────────────────────────────┤
                    │         **内存映射区域 (mmap)**        │
                    │  - 共享库 (libc.so, chrome.dll)       │
                    │  - 文件映射 (大文件/缓存)             │
                    │  - 匿名映射 (大块内存)                │
0x00007FFFFFFE0000  ├───────────────────────────────────────┤
                    │           **线程栈 (Stack)**          │
                    │  (每个线程独立, 默认1~8MB, 向低地址增长)│
                    │  e.g., 主线程栈 ≈ 0x00007FFFFFFF0000   │
0x00007FFFFFFFF000  └───────────────────────────────────────┘
                    │              **Guard Page**           │
                    │  (防止栈溢出/堆越界的保护页)           │
0x0000800000000000  ────────────────────────────────────────
                    │              **内核空间**              │
                    │  (用户进程不可访问: 0xFFFF800000000000+)│
```


hwmonitor

虚拟内存、物理内存

etw: 
wpr
wpa
perfview
UIforETW

# 性能分析
amduprof
vtune


# 网络问题排查

硬件、驱动器

win+r: inetcpl.cpl hosts文件 代理  
win+r: sysdm.cpl \\系统属性窗口，环境变量  
win+r: ncpa.cpl \\网络连接

特定端口占用:  
netstat -ano | findstr 8888 \\查找特定端口及其pid  
tasklist | findstr "PID" \\查找特定进程

ipconfig  
ping  
nslookup  
vim C:\\Windows\\System32\\drivers\\etc\\hosts

arp  
\-a 显示arp缓存表

tracert

route  
print 打印本地路由表

netstat  
\-ano 显示所有活动的tcp连接和正在监听的tcp、udp端口;端口用数字表示，包含连接的进程号  
\-p tcp 显示指定的tcp协议

# 杂

* 打开了很多窗口，任务栏一个都不显示  
    ctrl+alt+. 任务管理器 资源管理器-结束任务  
    ctrl+shift+esc 文件-->运行新任务 explorer
    
* 文件夹删不掉  
    ctrl+shift+esc，  
    资源管理器里找文件夹对应进程，停掉服务，删除文件夹即可