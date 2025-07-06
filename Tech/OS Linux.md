![](/skins/bj2008/images/fire.gif) [OS Linux](https://www.cnblogs.com/apeishuai/articles/18737515 "发布于 2025-02-25 23:20")

进程：
线程  
堆
esp寄存器

```cpp
https://github.com/ningmoon/ray2v\
$ sudo apt install ray2 ray2\
$ sudo systemctl start ray2.service

20250227 校验通过
```

* 配置ubuntu  
    [linux config bash脚本](https://github.com/apeishuai/bash/tree/master/linux)

chattr +i ~/.ssh //使得文件夹变得不可修改  
chattr -i ~/.ssh //恢复文件夹可修改状态

# 备忘

忘记密码  
进入recovery模式，root--> $ passwd username

# 网络

# 浏览器安装

```bash
wget https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
sudo apt-get install ./google-chrome-stable_current_amd64.deb
```

# 服务

## dns解析

```bash
nslookup xxx

暴力修改dns，直接奏效
/etc/network/interfaces
service networking restart

/etc/resolvconf/resolv.conf.d/base
/etc/resolvconf/resolv.conf.d/tailbase
service resolvconf restart

vim /etc/resolv.conf
ln /etc/resolv.conf 发现是一条软链接

rm -rf /etc/resolv.conf
echo -e "nameserver 1.1.1.1" > /etc/resolv.conf //会导致系统不能使用网卡通过dhcp得到dns

resolvconf是一个ubuntu上管理配置本机dns地址的工具，不提供dns解析
resolvconf -a /run/resolvocnf/interface/systemd-resolved //软链接
resolvconf -u //更新/etc/resolv.conf文件内容

/etc/systemd/resolved.conf
/usr/lib/systemd/resolv.conf
/run/systemd/resolve/stub-resolv.conf
/run/systemd/resolve/resolv.conf
system-resolv --status
app-->linux api-->system-resolved-->globa dns, /etc/resolv.conf

终极大法
systemctl stop systemd-resolved.service
systemctl disable systemd-resolved.service
```

## 后台任务

```dart
& //加载一个命令最后，可以把这个命令放后台执行
ctrl+z //将一个前台的命令放到后台执行，并处于暂停状态
jobs //查看有多少正在运行的指令
fg %num //将后台中的命令调至前台运行
bg %num //将一个在后台暂停的命令，变成在后台继续执行
kill %num //终止进程
nohup //在退出账户、关闭终端之后继续运行相应的进程
```

## 定时任务 cron

```bash
cron [-u user] {-l | -r | -e}
cron [-u user] file

crontab -l //列出所登录账户下所有cron任务
grep -v "#" //过滤所有注释

crontab -e //创建定时任务
crontab -r //删除crontab文件

sudo grep cron /var/log/syslog | tail //查看cron执行日志


分 时 日 月 星期 要运行的命令

* * * * * myCommand //每1min执行一次指令
3,15 * * * * myCommand //每小时的第3和15min执行
3,15 8-11 * * * myCommand
3,15 8-11 */2  *  * myCommand //每隔2天的上午8点到11点的第三和第15min执行
3,15 8-11 * * 1 myCommand
30 21 * * * /etc/init.d/smb restart
```

## 环境信息

who  
env  
which  
lastlog\\

## 用户与管理

```相关文件
/etc/passwdS\
root:x:0:0::/root:/bin/bash\
name: :user id:gid:directory:bash\
(gid:一登陆就会自动获得，初始群组)

/etc/shadow\
root:xxxxx:13025:5:60:7:2:13125:\
name:pass:最近密码更新日期:密码不可被更改天数:密码需要重新变更天数:密码需要变更期限前警告:密码过期恕限时间:账号失效日期:保留\

/etc/group\
root:x:0:root\
gname:pass:gid:support account

/etc/gshadow\
root:::root\
user:pass(!xx表示无法登入):group account:群组所属账号

/home/username
```

```操作命令
groupadd\
groupmod\
groupdel\
gpasswd\

newgrp users: 切换有效群组(决定新创建文件归属)\
exit: 离开新的有效群组

groups:查看账号属于的群组(第一个为有效群组)
```

```指令执行后相关文件改动
useradd:(相关文件改动)\
ref: \
/etc/default/useradd\
/etc/login.defs\
/etc/skel/*

passwd:
/etc/login.defs\
/etc/pam.d/passwd\

usermod:

userdel:\
/etc/passwd\
/etc/shadow\
/home/username\

sudo \
/etc/sudoer

PAM模块：\
/etc/nologin, /etc/securetty\
/etc/pam.d\
```

当前信息查看

```bash
awk -F: '{print $1}' /etc/passwd
```

```练习

```

## 档案权限与文件目录

```bash
因为 Linux 的开发者实在太多了，如果每个人都发展出属于自己的目录配置方法， 那么将可能会造成很多管理上的困扰。您能想象，您进入一个企业之后，所接触到的 Linux 目录配置方法竟然跟您以前学的完全不同吗？！很难想象吧～所以，后来就有所谓的 Filesystem Hierarchy Standard (FHS) 标准的出炉了(link. <鸟哥的linux私房菜>)


/ 根目录

/bin 二进制文件
	/usr/bin
	/usr/local/bin

/boot 启动linux时使用的一些核心文件
/data 
/dev 设备文件
/etc 存放系统管理所需的配置文件和子目录
	/etc/init.d/
	/etc/xinetd.d/
	/etc/X11
/home 用户的主目录
/lib 存放系统最基本的动态链接共享库和内核模块
	/usr/lib
	/usr/loval/lib
/lib32
/lib64
/libx32
/lost+found
/media
/mnt
/opt 存放第三方应用程序的可选软件包
/proc 虚拟文件系统，包含运行中的内核和进程信息
/root
/run 存储系统启动以来的信息，如当前登录的用户和运行中的守护进程的PID文件
/sbin
/srv
/swapfile
/sys
/tmp
/usr
/var 针对系统执行过程中，常态性变动的档案放置目录
	/var/cache
	/var/lib
	/var/log
	/var/lock
	/var/run
	/var/spool
```

# softwares

## perf

perf is powerful: it can instrument CPU performance counters, tracepoints, kprobes, and uprobes (dynamic tracing). It is capable of lightweight profiling. It is also included in the Linux kernel, under tools/perf, and is frequently updated and enhanced.

基于ubuntu x86_64 v20.04安装perf

```bash
apt install linux-tools-common
apt install linux-tools-5.13.0-40-generic
apt install linux-cloud-tools-5.13.0-40-generic
```

```bash
perf -v
```

# linux性能

top  
ps  
vimstat  
pidstat  
execsnoop

* [ ]  内核  
    内核能执行的任务：  
    进程调度：  
    内存管理：  
    创建与终止进程：

分类: [all](https://www.cnblogs.com/apeishuai/category/2452653.html)

好文要顶 关注我 收藏该文 微信分享

[![](https://pic.cnblogs.com/face/3531360/20250403195920.png)](https://home.cnblogs.com/u/apeishuai/)

[Pomr](https://home.cnblogs.com/u/apeishuai/)  
[粉丝 - 0](https://home.cnblogs.com/u/apeishuai/followers/) [关注 - 2](https://home.cnblogs.com/u/apeishuai/followees/)  

0

0

[升级成为会员](https://cnblogs.vip/)

[«](https://www.cnblogs.com/apeishuai/articles/18737433) 上一篇： [qt QML QUICK](https://www.cnblogs.com/apeishuai/articles/18737433 "发布于 2025-02-25 22:23")  
[»](https://www.cnblogs.com/apeishuai/articles/18737558) 下一篇： [OS Windows](https://www.cnblogs.com/apeishuai/articles/18737558 "发布于 2025-02-25 23:53")

posted on 2025-02-25 23:20  [Pomr](https://www.cnblogs.com/apeishuai)  阅读(0)  评论(0)  [MD](https://www.cnblogs.com/apeishuai/articles/18737515.md)  [编辑](https://i.cnblogs.com/EditArticles.aspx?postid=18737515)  收藏  举报