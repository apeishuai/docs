# 调试思路



# OllyDbg
![](/skins/bj2008/images/fire.gif) [Ollydbg](https://www.cnblogs.com/apeishuai/articles/18773546 "发布于 2025-03-15 13:20")

![](https://img2024.cnblogs.com/blog/3531360/202503/3531360-20250315132637406-1447564149.png)

# IDA

ctrl + 1 ;quick view  
\--> Strings; HexDump

Alt+f3 close window  
ctrl + . focus on command line  
f6 ;next window  
shift + window ;previous window

alt+M ;mark position  
ctrl+M ;jump to mark position

# Windbg

[PEB](https://learn.microsoft.com/zh-cn/windows/win32/api/winternl/ns-winternl-peb)

```css
typedef struct _PEB {
  BYTE                          Reserved1[2];
  BYTE                          BeingDebugged;
  BYTE                          Reserved2[1];
  PVOID                         Reserved3[2];
  PPEB_LDR_DATA                 Ldr;
  PRTL_USER_PROCESS_PARAMETERS  ProcessParameters;
  PVOID                         Reserved4[3];
  PVOID                         AtlThunkSListPtr;
  PVOID                         Reserved5;
  ULONG                         Reserved6;
  PVOID                         Reserved7;
  ULONG                         Reserved8;
  ULONG                         AtlThunkSListPtr32;
  PVOID                         Reserved9[45];
  BYTE                          Reserved10[96];
  PPS_POST_PROCESS_INIT_ROUTINE PostProcessInitRoutine;
  BYTE                          Reserved11[128];
  PVOID                         Reserved12[1];
  ULONG                         SessionId;
} PEB, *PPEB;
```

g //continue

u . //反汇编当前指令附近代码  
u @rip L10 //显示从当前RIP开始的16条指令

uf. //反汇编当前所在的整个函数  
uf 140001000 //反汇编指定地址的函数

lm //列出所有已加载模块  
lm m _ssl_ //查找包含ssl的模块

x /v /d libssl-1_1-x64!\* //列出模块所有符号  
!address -f:IMAGE 140001000 //查看模块内存范围

bp 140001000 //在代码段设置普通断点  
ba e1 140001000 //设置硬件执行断点

windbg 动态调试  
windbg转储

监控 CPU 使用率并生成转储  
procdump -c 90 -n 3 -ma notepad.exe C:\\dumps

.hh  
.hh 

s \\内存搜索 -u unicode  
r \\display or modifies registers, floating-point registers, flags, pseudo-registers, and fixed-name aliases  
e \\\* commands enter into memory the values that you specify  
e ea eb ed eD ef ep eq eu ew eza  
d \\The d\* commands display the contents of memory in the given range.  
d da db dc dd dD df dp dq du

!error \\The !error extension decodes and displays information about an error value.  
.writemem

kb \\调用过程  
kp \\

# \[Pattern\] \[Address \[ L Size \]\]

!tp  
!cpuid  
!address \\The !address extension displays information about the memory that the target process or target computer uses

.restart  
g  
t //断点，命中后开始单步

run  
breakpoint  
memory  
反汇编  
modules  
type information、symbols

进程入手 ：  
PEB：包含进程信息

!peb  
dt \_PEB 0000006567277000 ImageBaseAddress //显示给定地址处PEB结构的详细信息  
!dh 0x00007ff74afe0000 -a //查看PE头中的入口点

.logopen > log.txt  
op xx  
.logclose  
grep "entry point"

u address //一段一段读汇编指令

breakpoint //断点跳跃  
t //回溯函数调用栈

.frame //查看当前函数的调用栈

k //显示当前函数调用栈  
~0s \\stack trace for thread 0  
~1s \\stack trace for thread 1  
!heap 堆列表  
.cls //清屏

// process and module  
lm //列出所有加载的模块  
lm m notepad  
!dlls \\display list of modules with loader-specific information  
!dlls -c kernel32 \\  
!imgreloc \\display relocation information  
!dh kernel32 \\display the header for kernel32  
dt ntdll!\* \\display all variables in ntdll

//symbols  
.sympath  
.sympath SRV_D:\\softwares\\msys64\\home\\whens\\bin\\conf\\Symbols_https://msdl.microsoft.com/download/symbols  
!sym noisy \\显示执行.reload时的详细信息  
!sym quiet  
symchk /r %windir%\\system32 /s SRV\*d:\\symbols\*http://msdl.microsoft.com/download/symbols

//threads information  
~  
~0  
~.  
~\*  
~\* k

### windbg check sheet

https://blog.lamarranet.com/wp-content/uploads/2021/09/WinDbg-Cheat-Sheet.pdf  
theartofdev.com/windbg-cheat-sheet/  
https://vancir.github.io/blog/2022/windbg-cheatsheet/  
https://exploit-notes.hdks.org/exploit/reverse-engineering/cheatsheet/windbg-cheatsheet/