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
$architecture=Get-WmiObject -Class Win32_Processor|Select-Object AddressWidth
if($architecture.AddressWidth -eq 64){
    $system_info="x64"
}else{
    $system_info="x86"
}
$sdl_dll_path="./vendor/SDL2/lib/$system_info/SDL2.dll"
cp $sdl_dll_path "./bin/SDL2.dll"
$bin_res_path="./bin/res"
if(!(Test-Path -Path $bin_res_path)){
    mkdir $bin_res_path
}
cp ./res/* $bin_res_path
& "./bin/$project_name-mingw-debug.exe"
