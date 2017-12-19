#include "IO.h"

using namespace std;
using namespace pcl;

template <class T>
IO<T>::IO(){
    cloud_ptr = typename PointCloud<T>::Ptr(new PointCloud<T>);
    flag_getFromSensor = false;
    flag_sequencialGrabbing = false;
    initializeGrabber();
}

template <class T>
IO<T>::~IO(){
    //dtor
}

template <class T>
void IO<T>::readFromPCD(string filename,class PointCloud<T>::Ptr cloud){
    try{
        if(io::loadPCDFile<T>(filename.c_str(), *cloud) == -1){
            cout<<"ERROR READING PCD FILE"<<endl;
        }
        else{
        cout<<"File read" << endl;
        }
    }
    catch (PCLException e){
        cout<<"ERROR READING PCD FILE"<<endl;
        exit(1);
    }
}

template <class T>
void IO<T>::writeToPCD(string filename,class PointCloud<T>::Ptr cloud){
        try{
            io::savePCDFileASCII(filename.c_str(), *cloud);
            cout<<"File saved" << endl;
        }
        catch(PCLException e1){
            cout<<"ERROR saving PCD file" << endl;
        }
    }

template <class T>
void IO<T>::writeToPLY(string filename,PolygonMesh::Ptr mesh){
        try{
            io::saveOBJFile (filename,*mesh);
            cout<<"File saved" << endl;
        }
        catch(PCLException e1){
            cout<<"ERROR saving PCD file" << endl;
        }
    }


template <class T>
class PointCloud<T>::Ptr IO<T>::getCloud_ptr(){
    return this->cloud_ptr;
}

template <class T>
void IO<T>::setSensorSequencialGrabbing(bool sequencialGrabbing){
    if(sequencialGrabbing && !flag_sequencialGrabbing){
        flag_sequencialGrabbing = true;
        openniGrabber->start();
        cout<<"STARTING"<<endl;
    }
    else if(!sequencialGrabbing && flag_sequencialGrabbing){
        flag_sequencialGrabbing = false;
        openniGrabber->stop();
    }

}

template <class T>
void IO<T>::grabSingleFrameSensor(){
    flag_getFromSensor = true;
    openniGrabber->start();

    while(flag_getFromSensor){
        cout<<""; //Sem esse cout o loop nao executa XD
    }

    openniGrabber->stop();
}

template <class T>
void IO<T>::grabSequencialFrameSensor(){
    flag_getFromSensor = true;

    while(flag_getFromSensor){
        cout<<""; //Sem esse cout o loop nao executa XD
    }
}

template <class T>
void IO<T>::grabberCallback(const class PointCloud<T>::ConstPtr &temp_cloud){

	if (flag_getFromSensor){

        *cloud_ptr = *temp_cloud;
		flag_getFromSensor = false;
	}
}

template <class T>
void IO<T>::initializeGrabber(){

    openniGrabber = new OpenNIGrabber();
    if (openniGrabber == 0){
     cout<<"*ERROR on grabber*" << endl;
     exit(1);
    }

    boost::function<void (const class PointCloud<T>::ConstPtr&)> f = boost::bind (&IO<T>::grabberCallback, this, _1);
    openniGrabber->registerCallback(f);
}

