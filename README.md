# 生命游戏(Game Of Life)
# 安装(Windows/Linux/MacOS)
需用户安装环境依赖，自行构建可执行文件。  
Windows所需环境依赖：  
`CMake>=3.0`  
`Visual Studio>=2017`  
or  
`MinGW-W64>=7.0.0`  
（注意：需确保MinGW-W64自带的CMake版本>=3.0）  
Linux/MacOS所需环境依赖：  
`CMake>=3.0`  
`GCC>=8.0`  
or  
`CMake>=3.0`  
`Clang>=10.0`  
## Windows操作系统构建
### Visual Studio构建
执行`build-msvc*.ps1`生成`game_of_life-msvc*.exe`并运行。
### MinGW-W64构建
执行`build-mingw*.ps1`生成`game_of_life-mingw*.exe`并运行。
## Linux操作系统构建
执行`build-linux*.sh`生成`game_of_life-linux*`并运行。
## MacOS操作系统构建
执行`build-linux*.sh`生成`game_of_life-macos*`并运行。
