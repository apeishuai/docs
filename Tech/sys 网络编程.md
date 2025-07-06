POSIX规范，
sin_family sin_addr sin_port，三个字段

sin_family AF_xxx







![](/img/Capturer_2025-06-30_112534_841.png)
![](/img/Capturer_2025-06-30_112642_735.png)
```
int socket(int family,int type, int protocol)  //指定期望的通信协议类型，返回套接字描述符
```
```
bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen);//成功则为0，出错则为-1
```
服务器绑定端口，客户端动态分配
```
connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen) //成功返回1
```
```
listen(int sockfd, int backlog);//成功则为0
```
```
accept(int sockfd, struct sockaddr *cliaddr,sock_t *addrlen); //成功则为非负描述符，出错则为-1
```



![](/skins/bj2008/images/fire.gif) [网络编程 socket](https://www.cnblogs.com/apeishuai/articles/18861366 "发布于 2025-05-06 13:48")

![](https://img2024.cnblogs.com/blog/3531360/202505/3531360-20250506131339818-2011532923.png)  
建立新连接，SYN +1,数据字段，ISN(Initial Sequence Number)，Seq sequence number  
ACK：确认序号有效  
URG：紧急指针有效  
PSH: 接收方应尽快将这个报文交给应用层  
RST：重建连接  
SYN：同步需要用来发起一个链接  
FIN：发端完成发送任务

一个TCP连接是全双工，关闭必须是单向关闭

![](https://img2024.cnblogs.com/blog/3531360/202505/3531360-20250506105358319-2055545250.png)  
![](https://img2024.cnblogs.com/blog/3531360/202505/3531360-20250506144522768-1217298739.png)

# 压力测试

https://www.cnblogs.com/goldsunshine/p/16607820.html  
locust

# TCP优化

带宽/吞吐量测试：  
ntttcp -s -m 4,_,127.0.0.1 -t 120  
ntttcp -r -m 4,_,127.0.0.1 -t 120

rtt测试：  
ping