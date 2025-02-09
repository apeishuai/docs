# tmux教程
tmux是一个终端复用器

## 会话管理
```bash
tmux new -s <session-name>
tmux detach
tmux ls
tmux attach -t <session-name>
tmux kill-session -t <session-name>

tmux switch -t <session-name>
tmux rename-session -t 0 <new-name>


快捷键：
ctrl+b d: 分离当前会话
ctrl+b s: 列出所有会话
ctrl+b $: 重命名当前会话

```
## 窗格操作
```bash
tmux split-window
tmux split-window -h

tmux select-pane -U -D -L -R
tmux swap-pane -U -D
```
## 窗口管理
```bash
tmux new-window
tmux new-window -n <window-name>

tmux select-window -t <window-number>
tmux select-window -t <window-name>
tmux rename-window <new-name>
```
## 其他命令
```bash
tmux list-keys
tmux list-commands
tmux ifo
tmux source-file ~/.tmux.conf
```

## 结对编程

# 配置
常用操作：开一个pane、三个bash、每个bash按需切割窗口，免得一直切换，很方便


```bash
2024/03/22
set-window-option -g mode-keys vi
#set-window-option -g utf8 on
#set-option -g status-utf8 on

set-option -g prefix C-a
#unbind-key C-b

# window
bind-key C-w kill-window
bind-key c new-window -c "#{pane_current_path}"
bind-key '"' split-window -c "#{pane_current_path}"
bind-key % split-window -h -c "#{pane_current_path}"

# pane
bind-key C-x confirm-before -p "Do you really want to kill this pane?" kill-pane
#bind-key C-a last-window
#bind-key C-w last-pane
bind-key '(' command-prompt -p "Name pane:" "select-pane -T '%%'"
bind-key ')' command-prompt -p "Name window:" "rename-window '%%'"

# conf
bind-key rc source-file ~/.tmux.conf \; display-message "tmux.conf reloaded"



bind -n C-Left select-pane -L
bind -n C-Right select-pane -R
bind -n C-Up select-pane -U
bind -n C-Down select-pane -D

#enable mount
set-option -g mouse on
```
# ref
[ruanyifeng tmux tiutorial](https://www.ruanyifeng.com/blog/2019/10/tmux.html)
[louizhai tmux tutorial](https://louiszhai.github.io/2017/09/30/tmux/#%E7%BB%93%E5%AF%B9%E7%BC%96%E7%A8%8B)
