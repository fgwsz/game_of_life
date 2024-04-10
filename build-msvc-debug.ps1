$project_name=Split-Path -Leaf (Get-Location)
$build_path="./build/msvc/debug"
if(!(Test-Path -Path $build_path)){
    mkdir $build_path
}
cd $build_path
cmake -G "Visual Studio 17 2022" ../../..
cmake --build .
cd ../../..
cp "$build_path/Debug/$project_name.exe" "./$project_name-msvc-debug.exe"
$sdl_dll_path="./vendored/sdl/lib/x64/SDL2.dll"
cp $sdl_dll_path ./SDL2.dll
& "./$project_name-msvc-debug.exe"
