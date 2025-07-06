![](/skins/bj2008/images/fire.gif) [lazarus + free pascal](https://www.cnblogs.com/apeishuai/articles/18810966 "发布于 2025-04-06 17:33")

https://wiki.freepascal.org/Basic_Pascal_Tutorial/Contents/zh_CN  
https://www.freepascal.org/docs.var  
https://wiki.freepascal.org/Lazarus_Tutorial/zh_CN

PROGRAM ProgramName (FileList);

CONST  
(\* 常量说明 _)  
TYPE  
(_ 类型说明 _)  
VAR  
(_ 变量说明 _)  
(_ 子程序定义 _)  
BEGIN  
(_ 执行语句 \*)  
END.

Pascal是不区分大小写的！

const  
Identifier1 = value;  
Identifier2 = value;  
Identifier3 = value;

var  
IdentifierList1 : DataType1 = defaultValue;  
IdentifierList2 : DataType2 = defaultValue;  
IdentifierList3 : DataType3 = defaultValue;  
...

Free Pascal支持Delphi中的PChar类型。PChar被定义为Char类型的指针，但它还具有一些额外的特性。对PChar类型最好的理解就是将其等价于C风格空结尾字符串，也就是说，PChar类型的变量实际上是一个指向Char数组的指针，并且这个数组以空字符（#0）结尾。Free Pascal支持PChar型常量的初始化和直接赋值。例如，下面的两段代码是等效的：

variable_name := expression; //赋值

writeln ('Number of integers = ', NumberOfIntegers);

write 和 writeln 的区别在于：write语句是输出项输出后，不换行，光标停留在最后一项后，writeln 语句按项输出后，自动换行，光标则停留在下一行的开始位置。  
writeln 语句允许不含有输出项，即仅writeln;表示换行。

for count := 1 to 100 do  
sum := sum + count;

read  
readln

file：xx

repeat  
语句1;  
语句  
until 逻辑表达式;

function Name (参数列表) : 返回类型;

type  
MonthType = (January, February, March, April,  
May, June, July, August, September,  
October, November, December);

好文要顶 关注我 收藏该文 微信分享

[![](https://pic.cnblogs.com/face/3531360/20250403195920.png)](https://home.cnblogs.com/u/apeishuai/)

[Pomr](https://home.cnblogs.com/u/apeishuai/)  
[粉丝 - 0](https://home.cnblogs.com/u/apeishuai/followers/) [关注 - 2](https://home.cnblogs.com/u/apeishuai/followees/)  

0

0

[升级成为会员](https://cnblogs.vip/)

[«](https://www.cnblogs.com/apeishuai/articles/18811308) 上一篇： [公差 互换性](https://www.cnblogs.com/apeishuai/articles/18811308 "发布于 2025-04-06 17:03")  
[»](https://www.cnblogs.com/apeishuai/articles/18811403) 下一篇： [《工程思维》](https://www.cnblogs.com/apeishuai/articles/18811403 "发布于 2025-04-06 18:28")

posted on 2025-04-06 17:33  [Pomr](https://www.cnblogs.com/apeishuai)  阅读(6)  评论(0)  [MD](https://www.cnblogs.com/apeishuai/articles/18810966.md)  [编辑](https://i.cnblogs.com/EditArticles.aspx?postid=18810966)  收藏  举报