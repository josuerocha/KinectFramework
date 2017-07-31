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
sudo apt-get --yes --force-yes install libeigen3-dev

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

#INSTALLING OPENNI

if [ ! -d "kinect" ] 
then
	mkdir kinect
fi

cd kinect
git clone https://github.com/OpenNI/OpenNI.git
cd OpenNI
git checkout unstable
cp ../../../files/XnUSBLinux.cpp Source/OpenNI/Linux
cd Platform/Linux/CreateRedist
chmod +x RedistMaker
./RedistMaker
cd ../Redist/OpenNI-Bin-Dev-Linux-x64-v1.5.8.5/
sudo ./install.sh
cd ../../../../../..

#INSTALLING PRIMESENSE DRIVERS

cd kinect
git clone https://github.com/ph4m/SensorKinect.git
cd SensorKinect
git checkout unstable
cd Platform/Linux/CreateRedist/
chmod +x RedistMaker
./RedistMaker
cd ../Redist/Sensor-Bin-Linux-x64-v5.1.2.1/
sudo chmod +x install.sh
sudo ./install.sh
cd ../../../../../..

#cd ..

#PCL Installation
echo "\033[1;35m **************** \033[0;31m DOWNLOADING PCL \033[1;35m ****************\033[0m"
wget https://github.com/PointCloudLibrary/pcl/archive/pcl-1.8.0.zip

echo "\033[1;35m **************** \033[0;31m INSTALLING PCL \033[1;35m **************** \033[0m"
unzip pcl-1.8.0.zip
cd pcl-pcl-1.8.0 && mkdir build && cd build
cmake ..
make -j $coreNo
sudo make -j $coreNo install
cd ../../..
sudo cp -R pcl-temp /usr/local
echo "\033[1;35m **************** \033[0;31m REINICIANDO SISTEMA \033[1;35m ****************\033[0m"
sudo reboot
