![](/skins/bj2008/images/fire.gif) [Docker](https://www.cnblogs.com/apeishuai/articles/18741696 "发布于 2025-02-27 18:40")

```objectivec
sudo docker export id|name > name.zip  //导出容器
sudo docker save id|name > xx.zip  //导出镜像
```

docker run -d ubuntu bash -c "tail -f /dev/null"，程序后台运行

# busybox image 解析

# docker-compose.yml

depends_on 指令用于指定一个服务必须在其他服务启动之后才能启动。  
depends_on 只能确保服务的启动顺序，但不能保证服务已经完全准备好。如果需要更精细的控制，可以结合 healthcheck 指令使用。healthcheck 可以定义服务的健康检查逻辑，确保服务在启动后处于健康状态。