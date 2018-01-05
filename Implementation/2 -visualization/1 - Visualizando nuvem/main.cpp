//Standard includes
#include <iostream>
#include <string>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/point_representation.h>
#include <pcl/visualization/pcl_visualizer.h>


//Custom includes
#include "CustomStructures.h"
#include "Filtering.h"
#include "IO.h"
#include "KinectControl.h"
#include "Processing.h"
#include "Viewer.h"

using namespace std;
using namespace pcl;

XYZRGBACloud_ptr cloud;
IO<PXYZRGBA> io_interface;

int main(){
    cloud = XYZRGBACloud_ptr(new XYZRGBACloud);

    //io_interface.readFromPCD("milk.pcd",cloud);
    //io_interface.readFromPCD("scene.")
    io_interface.setSensorSequentialGrabbing(true);
    cloud = io_interface.getCloud_ptr();

    Viewer<PXYZRGBA> viewer;
    viewer.addCloud(cloud);

    KinectControl kinect;
    kinect.Move(30);
    kinect.Move(-30);
    while(true){
        cout<< "GRABBING" << endl;

        io_interface.grabSequentialFrameSensor();

        cout<< "GRABBED" << endl;

        viewer.showExternalCloud(cloud);

        cout << "SHOWED" << endl;
    }

    return 0;
}
