[领域及阅读列表](https://dxr54gq30qo.feishu.cn/wiki/UQnJw306eivn4vk3OwtcD5NUndb?from=from_copylink)

- [ ] 电气设计规范
- [x] 接地
- [ ] solidworks基本操作
- [ ] 机加工方法
- [ ] 大模型(可加快学习速度)


# draw
[download opengl](https://opengl.gpuinfo.org/download.php)



# node.js
# Linux
[linux学习路线](https://www.bilibili.com/opus/498161531410328699)
# docker
# c++
# qt
- qt version history \<trace\> \
[qt history](https://wiki.qt.io/Qt_History)\
[qt version history](https://wiki.qt.io/Qt_version_history)\
[release information](https://wiki.qt.io/Template:Release_Information)\
[qt4 version](https://wiki.qt.io/Qt_4_versions)\
[ABI symbols qt](https://abi-laboratory.pro/index.php?view=timeline&l=qt)


# git

[What makes Git so hard to use? | HighFlux](https://www.highflux.io/blog/what-makes-git-hard-to-use)\
/Entered on/ [2023-01-06 周五 12:45]

```
git config --global user.name "apeishuai"
git config --global user.email "whswhswhs66@gmail.com"
```
```
git submodule \\列出所有子模块信息\
git submodule status \\查看子模块状态

git submodule add <path> <url> \\添加submodule子模块

git submodule set-url <path> <new-repository-url> 

.gitmodule\
[submodule "Shell"]\
    path = Shell\
    url = <正确的URL>

git submodule init \\根据.gitmodules文件中的配置初始化和更新子模块。\
git submodule update \\同步子模块URL：如果你修改了.gitmodules文件中的URL，使用git submodule sync命令将新的URL更新到.git/config文件中：\
git submodule sync \\确保.git/config文件中的子模块配置与.gitmodules文件保持一致。\
git rm --cached Shell \\从Git的索引中移除子模块，但保留在工作目录中

vim .gitignore
```

# Appendix A shortcut
功能： Prettier是一款非常流行的代码格式化工具，支持多种语言，包括JSON。它可以自动格式化JSON代码，使其符合特定的代码风格规范。\
安装： 在VSCode的扩展商店中搜索“Prettier - Code formatter”并安装。\
使用方法：\
打开JSON文件。\
使用快捷键Ctrl + Shift + P（Windows）或Cmd + Shift + P（Mac）打开命令面板。\
输入Format Document并选择该命令，或者直接使用快捷键Shift + Alt + F。


# Appendix B lib
[nlohmann json](https://github.com/nlohmann/json) : nlohmann 是一个用于解析 JSON 的开源 C++ 库，口碑一流，使用非常方便直观，是很多 C++ 程序员的首选

# Appendix C C++ standrand lib
![](/img/64ca262e0cfa29d1e134e3582bd4c637.png)


```
// setw example
#include <iostream>     // std::cout, std::endl
#include <iomanip>      // std::setw

int main () {
  std::cout << std::setw(20);
  std::cout << 77 << std::endl;
  return 0;
}
```
