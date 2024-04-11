$project_name=Split-Path -Leaf (Get-Location)
$build_path="./build/msvc/release"
if(!(Test-Path -Path $build_path)){
    mkdir $build_path
}
cd $build_path
cmake -G "Visual Studio 17 2022" ../../..
cmake --build . --config Release
cd ../../..
cp "$build_path/Release/$project_name.exe" "./bin/$project_name-msvc-release.exe"
$architecture=Get-WmiObject -Class Win32_Processor|Select-Object AddressWidth
if($architecture.AddressWidth -eq 64){
    $system_info="x64"
}else{
    $system_info="x86"
}
$sdl_dll_path="./vendor/SDL2/lib/$system_info/SDL2.dll"
cp $sdl_dll_path "./bin/SDL2.dll"
& "./bin/$project_name-msvc-release.exe"
