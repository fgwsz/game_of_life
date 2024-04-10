$project_name=Split-Path -Leaf (Get-Location)
$build_path="./build/msvc/release"
if(!(Test-Path -Path $build_path)){
    mkdir $build_path
}
cd $build_path
cmake -G "Visual Studio 17 2022" ../../..
cmake --build . --config Release
cd ../../..
cp "$build_path/Release/$project_name.exe" "./$project_name-msvc-release.exe"
$sdl_dll_path="./vendored/sdl/lib/x64/SDL2.dll"
cp $sdl_dll_path ./SDL2.dll
& "./$project_name-msvc-release.exe"
