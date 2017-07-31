//Standard includes
#include <iostream>
#include <string>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/point_representation.h>
#include <pcl/visualization/pcl_visualizer.h>


//Custom includes
#include "IO.h"
#include "Processing.h"
#include "Viewer.h"
#include "KinectControl.h"
#include "Filtering.h"

using namespace std;
using namespace pcl;

XYZRGBACloud_ptr cloud;
IO<PXYZRGBA> io_interface;

int main(){
    cloud = XYZRGBACloud_ptr(new XYZRGBACloud);


    io_interface.setSensorSequencialGrabbing(true);
    cloud = io_interface.getCloud_ptr();

    Viewer<PXYZRGBA> viewer;
    viewer.addCloud(cloud);

    KinectControl kinect;
    kinect.Move(10);
    while(true){
        io_interface.grabSequencialFrameSensor();
        Filtering<PXYZRGBA>::filterArea(cloud,cloud,0.5,1.0,"z");
        viewer.showExternalCloud(cloud);

    }

    return 0;
}
