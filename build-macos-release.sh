mkdir build/macos/release
cd build/macos/release
cmake -DCMAKE_BUILD_TYPE=Release ../../..
make
cp ./game_of_life ../../../game_of_life-macos-release
cd ../../..
./game_of_life-macos-release
