mkdir build/linux/release
cd build/linux/release
cmake -DCMAKE_BUILD_TYPE=Release ../../..
make
cp ./game_of_life ../../../game_of_life-linux-release
cd ../../..
./game_of_life-linux-release
