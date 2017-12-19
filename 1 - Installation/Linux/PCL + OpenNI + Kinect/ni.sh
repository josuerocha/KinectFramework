#INSTALLING OPENNI

if [ ! -d "kinect" ] 
then
	mkdir kinect
fi

cd kinect
git clone https://github.com/OpenNI/OpenNI.git
cd OpenNI
git checkout unstable
cp ../../files/XnUSBLinux.cpp Source/OpenNI/Linux
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

