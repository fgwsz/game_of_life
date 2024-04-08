# Game Of Life
# Install
This project does not publish binary files (.exe) due to differences in the user's system environment.
You need to install the environment dependency and build the binary file (.exe).
Required environment dependent:  
`CMake>=3.0`  
`Visual Studio>=2017`  
or  
`MinGW-W64>=7.0.0`  
(Note: Make sure MinGW-W64 comes with CMake version >=3.0)
## Visual Studio build
Install `CMake` and `Visual Studio`, after the installation is complete,
Left mouse button double-click `build-msvc*.ps1` to generate `game_of_life-msvc*.exe` and run.
## MinGW-W64 build
Install `MinGW-W64`, after installation is complete,
Left mouse button double click `build-mingw*.ps1` generate `game_of_life-mingw*.exe` and run.
## Use
Rename the build-generated binary file (.exe) to `game_of_life.exe`,
Double-click the left mouse button to run.
Since `game_of_life.exe` itself is a console application,
Therefore, it can be called and run in the terminal through terminal commands/scripts.
# 生命游戏
# 安装
因用户系统环境可能存在差异，本项目不发布二进制文件(.exe)，
需用户安装环境依赖，自行构建二进制文件(.exe)。
所需环境依赖：  
`CMake>=3.0`  
`Visual Studio>=2017`  
or  
`MinGW-W64>=7.0.0`  
（注意：需确保MinGW-W64自带的CMake版本>=3.0）
## Visual Studio 构建
安装`CMake`和`Visual Studio`，安装完成之后，
鼠标左键双击`build-msvc*.ps1`生成`game_of_life-msvc*.exe`并运行。
## MinGW-W64 构建
安装`MinGW-W64`，安装完成之后，
鼠标左键双击`build-mingw*.ps1`生成`game_of_life-mingw*.exe`并运行。
## 使用
将构建生成的二进制文件(.exe)重命名为`game_of_life.exe`，
鼠标左键双击即可运行。
由于`game_of_life.exe`本身是控制台应用，
因此能在终端中通过终端命令/脚本等方式调用运行。
