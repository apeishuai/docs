# On macOS and Linux.
curl -LsSf https://astral.sh/uv/install.sh | sh

# On Windows.
powershell -ExecutionPolicy ByPass -c "irm https://astral.sh/uv/install.ps1 | iex"

# With pip.
pip install uv

$ uv help

usage:
1 create folder
2 
$ uv init <project dir>
//uv init后，自动将项目使用git管理
pyproject.toml //项目信息

3 
$ uv sync
uv.lock
4 
$ uv run .\hello.py
  
$ uv add pandas  //uv.lock会多出一些内容
$ uv remove pandas

$ uv add --group dev pandas
$ uv add --group production requests

- 构建和发布python包到PyPi
- 创建虚拟环境 
$ uv venv my-name 3.11
$ uv venv //使用虚拟环境
$ uv pip install ruff
$ .venv\Scripts\activate
$ uv pip install --system 
如果没有--system标志，uv会忽略任何不在虚拟环境中的解释器，反之，提供了--system，uv会忽略所有在虚拟环境中的解释器


当运行会改变环境的命令（如 uv pip sync 或 uv pip install）时，uv 会按以下顺序搜索虚拟环境：
基于 VIRTUAL_ENV 环境变量的已激活虚拟环境。
基于 CONDA_PREFIX 环境变量的已激活 Conda 环境。
当前目录中的 .venv 虚拟环境，或者最近的父目录中的虚拟环境。
如果未找到虚拟环境，uv 会提示用户在当前目录中通过 uv venv 创建一个。