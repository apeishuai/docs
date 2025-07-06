![](/skins/bj2008/images/fire.gif) [Bash脚本](https://www.cnblogs.com/apeishuai/articles/18742496 "发布于 2025-02-28 06:59")

bash shell 会将所有的命令行参数都指派给称作位置参数（positional parameter）的特殊变量。这也包括 shell 脚本名称。位置变量①的名称都是标准数字：对应脚本名，对应脚本名，0对应脚本名，1 对应第一个命令行参数，对应第二个命令行参数，以此类推，直到对应第二个命令行参数，以此类推，直到2对应第二个命令行参数，以此类推，直到9。

xargs用来将参数 xxx

# skill

使用 和和@和\* 获取所有参数

```makefile
$@ 和 $* 都可以用来获取所有传递给脚本的参数，但它们在双引号中的行为略有不同。
$@ 在双引号中会将每个参数视为独立的引用字符串。
$* 在双引号中会将所有参数视为一个整体字符串。
```

# !/bin/bash

echo "使用 遍历参数：遍历参数：@遍历参数："forargin"@"; do  
echo "参数: $arg"  
done

echo "使用 遍历参数：遍历参数：∗遍历参数："forargin"\*"; do  
echo "参数: $arg"  
done

使用 遍历参数：参数参数参数使用遍历参数：参数参数参数使用@遍历参数：参数:Hello参数:World参数:Thisisatest使用\* 遍历参数：  
参数: Hello World This is a test\*\*\*\*

分类: [all](https://www.cnblogs.com/apeishuai/category/2452653.html)

好文要顶 关注我 收藏该文 微信分享

[![](https://pic.cnblogs.com/face/3531360/20250403195920.png)](https://home.cnblogs.com/u/apeishuai/)

[Pomr](https://home.cnblogs.com/u/apeishuai/)  
[粉丝 - 0](https://home.cnblogs.com/u/apeishuai/followers/) [关注 - 2](https://home.cnblogs.com/u/apeishuai/followees/)  

0

0

[升级成为会员](https://cnblogs.vip/)

[«](https://www.cnblogs.com/apeishuai/articles/18741696) 上一篇： [Docker](https://www.cnblogs.com/apeishuai/articles/18741696 "发布于 2025-02-27 18:40")  
[»](https://www.cnblogs.com/apeishuai/articles/18758930) 下一篇： [eplan插件开发](https://www.cnblogs.com/apeishuai/articles/18758930 "发布于 2025-03-08 09:20")

posted on 2025-02-28 06:59  [Pomr](https://www.cnblogs.com/apeishuai)  阅读(1)  评论(0)  [MD](https://www.cnblogs.com/apeishuai/articles/18742496.md)  [编辑](https://i.cnblogs.com/EditArticles.aspx?postid=18742496)  收藏  举报