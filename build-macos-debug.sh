mkdir build/macos/debug
cd build/macos/debug
cmake -DCMAKE_BUILD_TYPE=Debug ../../..
make
cp ./game_of_life ../../../game_of_life-macos-debug
cd ../../..
./game_of_life-macos-debug
