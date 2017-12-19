#!/bin/bash
#Script para a instalação da Point Cloud Library (PCL) no Linux - by Josué Rocha Lima #josuerocha@me.com josuerocha.com.br

#Reading number of CPU cores to be used
echo -n "Enter the number of CPU cores to be used in the compilation process: "
read coreNo
echo "Compiling with $coreNo cores."

#CREATING TEMP FOLDER
echo "\033[1;35m **************** \033[0;31m CREATING TEMP FOLDER \033[1;35m ****************\033[0m"

if [ ! -d "pcl-temp" ] 
then
	mkdir pcl-temp
fi

sudo cp kinect.sh pcl/temp
cd pcl-temp
sudo chmod +x kinect.sh

#REMOVING OLD INSTALLATION FILES
echo "\033[1;35m **************** \033[0;31m REMOVING OLD INSTALLATION FILES \033[1;35m ****************\033[0m"
#OPENNI
if [ -f "OpenNI-Linux-x64-2.2.0.33.tar.bz2" ] 
then
	rm OpenNI-Linux-x64-2.2.0.33.tar.bz2
fi

if [ -d "OpenNI-Linux-x64-2.2" ] 
then
	rm -R OpenNI-Linux-x64-2.2
fi

#PCL
if [ -f "pcl-1.8.0.zip" ] 
then
	rm pcl-1.8.0.zip
fi

if [ -d "pcl-pcl-1.8.0" ]; 
then
	rm -R pcl-pcl-1.8.0
fi


#VTK
if [ -f "VTK-7.1.0.zip" ] 
then
	rm VTK-7.1.0.zip
fi

if [ -d "VTK-7.1.0" ]; 
then
	rm -R VTK-7.1.0
fi


#Dependencies installation
#GIT
echo "\033[1;35m **************** \033[0;31m INSTALLING GIT \033[1;35m ****************\033[0m"
sudo apt-get --yes --force-yes install git

#CMAKE 
echo "\033[1;35m **************** \033[0;31m INSTALLING CMAKE \033[1;35m ****************\033[0m"
sudo apt-get --yes --force-yes install cmake

#FREEGLUT AND OPENGL
echo "\033[1;35m **************** \033[0;31m INSTALLING OPENGL \033[1;35m ****************\033[0m"
sudo apt-get --yes --force-yes install freeglut3-dev

#LIB BOOST
echo "\033[1;35m **************** \033[0;31m INSTALLING LIBBOOST \033[1;35m ****************\033[0m"
sudo apt-get --yes --force-yes install libboost-all-dev

#LIB UDEV
sudo apt-get --yes --force-yes install libudev-dev

#JAVA
sudo apt-get --yes --force-yes install default-jre
sudo apt-get --yes --force-yes install default-jdk

#PKG-CONFIG
sudo apt-get --yes --force-yes install pkg-config 

#BUILD ESSENTIAL
sudo apt-get --yes --force-yes install build-essential

#LIBXMU
sudo apt-get --yes --force-yes install libxmu-dev

#LIBXI-DEV
sudo apt-get --yes --force-yes install libxi-dev 

#GRAPHVIZ
sudo apt-get --yes --force-yes install graphviz

#MONO
sudo apt-get --yes --force-yes install mono-complete

#LIB USB
echo "\033[1;35m **************** \033[0;31m INSTALLING LIB USB \033[1;35m ****************\033[0m"
sudo apt-get --yes --force-yes install libusb-1.0-0-dev

#Doxygen
echo "\033[1;35m **************** \033[0;31m INSTALLING DOXYGEN \033[1;35m ****************\033[0m"
sudo apt-get --yes --force-yes install doxygen

#Eigen
echo "\033[1;35m **************** \033[0;31m INSTALLING EIGEN \033[1;35m ****************\033[0m"
wget http://launchpadlibrarian.net/209530212/libeigen3-dev_3.2.5-4_all.deb
sudo dpkg -i libeigen3-dev_3.2.5-4_all.deb
#sudo apt-get --yes --force-yes install libeigen3-dev

#LIB FLANN
echo "\033[1;35m **************** \033[0;31m INSTALLING FLANN \033[1;35m ****************\033[0m"
sudo apt-get --yes --force-yes install libflann-dev

#VTK
echo "\033[1;35m **************** \033[0;31m DOWNLOADING VTK \033[1;35m ****************\033[0m"
wget http://www.vtk.org/files/release/7.1/VTK-7.1.0.zip
echo "\033[1;35m **************** \033[0;31m INSTALLING VTK \033[1;35m ****************\033[0m"
unzip VTK-7.1.0.zip
cd VTK-7.1.0
mkdir build
cd build
cmake ..
make -j $coreNo install #Substituir pelo numero de CPUs disponíveis
cd ../..

#installing KINECT SUPPORT

if [ ! -d "kinect" ] 
then
	mkdir kinect
fi

cd kinect

#INSTALLING FREENECT DRIVERS

sudo git clone https://github.com/OpenKinect/libfreenect
cd libfreenect
sudo mkdir build
cd build
sudo cmake .. -DBUILD_OPENNI2_DRIVER=ON
sudo make -j $coreNo
sudo make -j $coreNo install
sudo ldconfig /usr/local/lib64/
sudo freenect-glview

SCRIPT=$(readlink -f "$0")
SCRIPTPATH=$(dirname "$SCRIPT")
SCRIPTPATH=$SCRIPTPATH'/lib'
echo $SCRIPTPATH

export LD_LIBRARY_PATH=export LD_LIBRARY_PATH=$SCRIPTPATH

sudo cp lib/OpenNI2-FreenectDriver/libFreenectDriver.so ../..
cd ../../
sudo cp libFreenectDriver.so /usr/lib/OpenNI2/Drivers


#INSTALLING OPENNI2
#sudo apt-get install libopenni2-dev
git clone https://github.com/occipital/openni2
cd openni2
make -j $coreNo
cd Packaging 
python ReleaseVersion.py x64
cd Final
tar jxf OpenNI-Linux-x64-2.2.tar.bz2
cd OpenNI-Linux-x64-2.2
sudo ./install.sh
cd ../../..

sudo cp ../libFreenectDriver.so Packaging/Final/OpenNI-Linux-x64-2.2/Redist/OpenNI2/Drivers
sudo cp ../libFreenectDriver.so Packaging/Final/OpenNI-Linux-x64-2.2/Tools/OpenNI2/Drivers
sudo cp ../libFreenectDriver.so Packaging/Final/OpenNI-Linux-x64-2.2/Samples/Bin/OpenNI2/Drivers
sudo cp ../libFreenectDriver.so Bin/x64-Release/OpenNI2/Drivers

cd ..

sudo mv openni2 /usr/local

#export OPENNI2_INCLUDE=/home/jr/Desktop/kinect/openni2/Packaging/Final/OpenNI-Linux-x64-2.2/Include
#export OPENNI2_LIBRARY=/home/jr/Desktop/kinect/openni2/Packaging/Final/OpenNI-Linux-x64-2.2/Redist

#export OPENNI2_INCLUDE=/usr/local/include
#export OPENNI2_LIBRARY=/usr/local/lib/Redist

#sudo cp -R openni2/Packaging/Final/OpenNI-Linux-x64-2.2/Redist /usr/local/lib

#PCL Installation
echo "\033[1;35m **************** \033[0;31m DOWNLOADING PCL \033[1;35m ****************\033[0m"
#wget https://github.com/PointCloudLibrary/pcl/archive/pcl-1.8.0.zip

echo "\033[1;35m **************** \033[0;31m INSTALLING PCL \033[1;35m **************** \033[0m"
unzip pcl-1.8.0.zip
cd pcl-pcl-1.8.0 && mkdir build && cd build

cmake .. -DOPENNI2_LIBRARY=/usr/local/openni2/Packaging/Final/OpenNI-Linux-x64-2.2/Redist/libOpenNI2.so -DOPENNI2_INCLUDE_DIRS=/usr/local/openni2/Packaging/Final/OpenNI-Linux-x64-2.2/Include
make -j $coreNo #Substituir pelo numero de CPUs disponíveis
sudo make -j $coreNo install
