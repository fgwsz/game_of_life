$project_name=Split-Path -Leaf (Get-Location)
$build_path="./build/mingw/release"
if(!(Test-Path -Path $build_path)){
    mkdir $build_path
}
cd $build_path
cmake -G "MinGW Makefiles" ../../..
cmake --build . --config Release
cd ../../..
cp "$build_path/$project_name.exe" "./$project_name-mingw-release.exe"
$sdl_dll_path="./vendored/sdl/lib/x64/SDL2.dll"
cp $sdl_dll_path ./SDL2.dll
& "./$project_name-mingw-release.exe"
