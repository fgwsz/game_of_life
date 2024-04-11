mkdir build/linux/release
cd build/linux/release
cmake -DCMAKE_BUILD_TYPE=Release ../../..
make
cp ./game_of_life ../../../bin/game_of_life-linux-release
cd ../../..
./bin/game_of_life-linux-release
