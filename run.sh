cat packages.txt | xargs sudo apt install -y
mkdir build
cd build
cmake ..
make
./Raycasting-in-Maze