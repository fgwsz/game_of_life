$project_name=Split-Path -Leaf (Get-Location)
$build_path="./build/msvc/debug"
if(!(Test-Path -Path $build_path)){
    mkdir $build_path
}
cd $build_path
cmake -G "Visual Studio 17 2022" ../../..
cmake --build .
cd ../../..
cp "$build_path/Debug/$project_name.exe" "./bin/$project_name-msvc-debug.exe"
$sdl_dll_path="./vendor/sdl/lib/x64/SDL2.dll"
cp $sdl_dll_path "./bin/SDL2.dll"
& "./bin/$project_name-msvc-debug.exe"
