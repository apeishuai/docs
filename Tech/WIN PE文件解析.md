![](/skins/bj2008/images/fire.gif) [WIN PE文件解析](https://www.cnblogs.com/apeishuai/articles/18740524 "发布于 2025-02-27 11:00")

# PE文件格式

![](https://img2024.cnblogs.com/blog/3531360/202502/3531360-20250227102158192-1446994950.png)

![](https://img2024.cnblogs.com/blog/3531360/202505/3531360-20250508090953778-172836032.png)  
![](https://img2024.cnblogs.com/blog/3531360/202505/3531360-20250508091020818-436100441.png)  
![](https://img2024.cnblogs.com/blog/3531360/202505/3531360-20250508091037097-298252346.png)

.rdata : Read-only initialized data \
.pdata : exception information \
.text : executable code \
.data : initinal data \
.idata : 导入表，包含程序运行时需要从其他动态链接库导w入的函数信息 \
.bss : 存储未初始化的全局变量和静态变量

# ref

《windows PE权威指南》