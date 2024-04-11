# 生命游戏 Game Of Life (Windows)
## 直接下载 Release 版
下载网址:<https://github.com/fgwsz/game_of_life/releases>
## 自主构建
### 安装项目构建工具
`CMake>=3.5`  
`Visual Studio>=2017`  
or  
`MinGW-W64>=7.0.0`  
（注意：需确保MinGW-W64自带的CMake版本>=3.5）  
### 导入第三方库`SDL2`
下载`SDL2`:<https://github.com/libsdl-org/SDL/releases>  
（注意：下载`SDL2-devel-2.x.y.zip`版本）  
将下载好的安装包解压，解压后的根目录一般名为`SDL2-2.x.y`，
将其重命名为`SDL2`，拷贝这个文件夹到本项目的`vendor/`目录中，
检查一下`SDL2/`目录下的`cmake/`文件夹的位置是否符合如下路径：  
`vendor/SDL2/cmake`  
若符合，则导入第三方库`SDL2`成功。
### 生成可执行文件
1. `Visual Studio` 生成  
左键双击执行`build-msvc*.ps1`，
会在`bin/`目录下生成`game_of_life-msvc*.exe`并运行。
2. `MinGW-W64` 生成  
左键双击执行`build-msvc*.ps1`，
会在`bin/`目录下生成`game_of_life-mingw*.exe`并运行。
