mkdir build/linux/debug
cd build/linux/debug
cmake -DCMAKE_BUILD_TYPE=Debug ../../..
make
cp ./game_of_life ../../../game_of_life-linux-debug
cd ../../..
./game_of_life-linux-debug