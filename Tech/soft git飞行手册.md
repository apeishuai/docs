![](/skins/bj2008/images/fire.gif) [git飞行手册](https://www.cnblogs.com/apeishuai/articles/18778288 "发布于 2025-03-18 09:40")


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
https://vikingz.me/git-pro/  
https://github.com/k88hudson/git-flight-rules/blob/master/README_zh-CN.md


git 逆顺序reset：  
https://www.conventionalcommits.org/zh-hans/v1.0.0/ //git commit 规范  
git rev-list --count HEAD //查看commit次数  
git reset --hard HEAD~n //回退到前n次提交之前

git commit --amend --no-edit //  
git push origin master --force

git reflog //

curl -v https://github.com --proxy socks5://127.0.0.1:7897  //测试连通性
git -c http.proxy=socks5://127.0.0.1:7897 pull origin master
git clone -c http.proxy=socks5://127.0.0.1:7897 repository

git config --global http.proxy socks5://127.0.0.1:7897
git config --global https.proxy socks5://127.0.0.1:7897
git config --global --unset http.proxy
git config --global --unset https.prox

# git notes
a common use of git notes is tacking metadata onto commits

git notes add -m 'Acked-by <tyler@tylerxxx.com>'

and then it shows up in 'git log': xxx

for discuss
```
commit 00f09d0e4b1826ee0519ea64e919515032966450
Author: <redacted>
Date:   Thu Jan 28 02:05:55 2010 +0100

    bash: support 'git notes' and its subcommands
    ...

Notes (amlog):
    Message-Id: <1264640755-22447-1-git-send-email-szeder@ira.uka.de>
```
for review
```
commit d1d17908d2a97f057887a4afbd99f6c40be56849
Author: User <user@example.com>
Date:   Sun Mar 27 18:10:51 2022 +0200

    Change the thing

Notes (review):
    Verified+1: SonarQube Bot
    Verified+2: jenkins-bot
    Code-Review+2: Reviewer Human <reviewerhuman@wikimedia.org>
    Submitted-by: jenkins-bot
    Submitted-at: Tue, 14 Jun 2022 21:59:58 +0000
    Reviewed-on: https://gerrit.wikimedia.org/r/c/mediawiki/core/+/774005
    Project: mediawiki/core
    Branch: refs/heads/master
```



## git
2023-07-09T11:53:48+08:00
常用操作
```bash
ssh-keygen -t rsa -C "your_email@example.com" //生成密钥
git -T ssh@github.com //测试是否连通
```

git工作流程
+ 新建github账号
+ 新建repository
+ 执行ssh-keygen，生成key，将public key的值填入SSH and GPG keys
  - [ ] ssh原理
+ git clone xx (拉取远程仓库的.git文件夹)
+ 本地新建目录
  + 执行git init (生成.git文件夹（如果通过clone得到.git文件夹就不用执行此步骤）)
  + git remote add repo-name xx (关联远程仓库)
+ 推送至本地仓库 (注：stage为暂存区)
![文件状态周期img/文件状态周期_2023-07-09_15-23-53.png)
  + git add .
	+ git status (查看文件状态)
	+ git rm --cache xx.txt (从暂存区移除文件)
	+ git mv(修改文件名称= mv + rm + add)
	+ git reset HEAD xx.txt(取消已经暂存的文件)
	+ git checkout -- xx.txt(取消对文件的修改)
	+ git diff --cached (查看已暂存的将要添加到下次提交的内容)
	+ git diff  (查看尚未暂存的改动)
  + git commit -m "first post"
	+ git commit -m "xx"
	+ git add forgetten_files(修正第一个的提交内容)
	+ git commit --amend (修改最后一次提交)
+ 推送至远程仓库
  + git push origin master
	+ git fetch (将远程仓库有但是当前仓库没有的信息拉取然后存储在本地数据库)
	+ git pull (=fetch + merge)

+ 历史版本回退
![commit历史img/commit历史_2023-07-09_16-18-22.png)
	- [ ] commit格式规定：
   + git log (查看提交历史)
	 + git log -p -2 (-p展开显示每次提交的内容差异，-2显示最近的两次更新)
	 + git log --stat (显示简要的增改行数统计)
	 + git log --pretty=oneline(short|full|fuller) (指定使用完全不同于默认格式的方式展示提交历史)
	 + git log --pretty=format:"%h - %an, %ar : %s" (见表格)
	 + git log --since=2.weeks | after
	 + git log --until | --before | --author | --committer
![commit状态img/commit状态_2023-07-09_16-27-15.png)
   + git reset(书本内搜索git reset，第23个索引起做了很详细的解释)
	 + git reset --soft HEAD~
	 + git reset --mixed HEAD~
	 + git reset --hard HEAD~
   + git reflog (本地操作历史记录)

git协作
+ git branch（创建新分支）
  + git branch new-branch
  + git branch --no-merged
  + git branch --merged
  + git branch -d new-branch(删除分支，未合并分支无法删除)
  + git branch -D new-branch(强制删除分支)
  + git branch -v(检查各个分支最后一次commit信息)
+ git checkout new-branch
  + git fetch origin
  + git checkout -b serverfix origin/serverfix (在远程分支的基础上分化新分支)
  + git checkout --track origin/xx (设定跟踪分支(从远程分支检出的本地分支))
  + git push origin :xx (删除远程分支，在这里提取空白然后将其变成[远程分支])

**合并和变基**\
变基是将一系列提交按照原有次序依次应用到另一分支上，最终效果和合并一样，但是其提交历史更整洁
+ git merge
+ git rebase master experiment
  + git checkout experiment
  + git rebase --onto master server client(原理是回到两个分支的共同祖先，提取你所在分支每次提交产生时的差异，把差异保存到临时文件里，然后从当前分支转换到你需衍合入的分支，依序施用每一个差异补丁文件)

问题：合并冲突\
如果你在两个不同的分支中，对同一个文件的同一个部分进行了不同的修改，Git 就没法干净的合并它们。但是在merge过程中会显示冲突文件，可以使用git status看哪些文件处于unstage阶段，做修改

基础
git有三类对象：blob、tree、commit，blob为文档内容+哈希值，tree对应unix中的目录，commit指向先前的commit及顶层tree对象。三类对象保存在.git/objects目录下

需要一个文件用简单的名字记录这些哈希值，这样就可以用指针而不是原来的哈希值去检索了，ref。ref也能帮助记录新分支的对象哈希值；HEAD文件是一个指向你当前所在分支的引用标识符，当你执行git commit命令，就是创建了一个commit对象，把这个commit对象的父级设置为HEAD指向的引用的哈希值。

tag对象指向commit，是一个永远不会发生变化的分支。

remote ref，可以把本地的master分支推送到远程服务器，remote分支是不能被check out的

向项目贡献
参考“向一个项目贡献小节”
![](img/私有团队流程_2023-07-09_17-13-10.png)

向开源项目贡献
+ fork项目副本
+ 从master分支中创建一个新分支
+ 将分支推送到github
+ 创建一个合并请求
  + push到fork的副本后，会出现一个绿色按钮，检查改动并给源项目创建合并请求
+ 讨论，根据实际情况继续修改
+ 项目拥有者合并或关闭合并请求

+ 用git format-patch命令生成mbox格式的文件然后作为附件发送
  + git format-patch -M origin/master
	+ -/.gitconfig文件中配置imap项
	+ git send-email *.patch

合并产生冲突怎么办？
+ 将源版本库添加为一个远端，并命名为"upstream"
+ 从远端抓取最新内容
+ 将主分支的内容合并到你的分支
+ 修复产生的冲突
+ 再推送回同一个分支 

- [ ] 维护项目
(能力达不到主导开源项目，这部分暂时pending)

[PROGIT 第二版](https://progit.cn)
