# http服务
nohup  //no hang up , 单独使用时进程在前台运行\
&  //将进程放进后台运行,

```c
nohup your_command &
```
job -l 查看当前会话后台任务

pkill -f "your_program"  # 按名称终止\
kill -9 <PID>  # 强制终止指定PID
