sudo apt-get install build-essential cmake pkg-config
sudo apt-get install libusb-1.0-0-dev
sudo apt-get install libturbojpeg libjpeg-turbo8-dev
sudo apt-get install libglfw3-dev

git clone https://github.com/OpenKinect/libfreenect2.git
cd libfreenect2
cd depends
./download_debs_trusty.sh

cd ..
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=usr/local/freenect2
make
make install
