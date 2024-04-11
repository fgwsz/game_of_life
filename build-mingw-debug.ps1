$project_name=Split-Path -Leaf (Get-Location)
$build_path="./build/mingw/debug"
if(!(Test-Path -Path $build_path)){
    mkdir $build_path
}
cd $build_path
cmake -G "MinGW Makefiles" ../../..
cmake --build .
cd ../../..
cp "$build_path/$project_name.exe" "./bin/$project_name-mingw-debug.exe"
$sdl_dll_path="./vendor/sdl/lib/x64/SDL2.dll"
cp $sdl_dll_path "./bin/SDL2.dll"
& "./bin/$project_name-mingw-debug.exe"
