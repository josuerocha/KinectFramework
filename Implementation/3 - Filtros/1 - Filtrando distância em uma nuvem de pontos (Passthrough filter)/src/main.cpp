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
#include "CustomStructures.h"
#include "Processing.h"
#include "Viewer.h"
#include "KinectControl.h"
#include "Filtering.h"

using namespace std;
using namespace pcl;

XYZRGBACloud_ptr cloud;
XYZRGBACloud_ptr filtered_cloud;
IO<PXYZRGBA> io_interface;

int main(){
    cloud = io_interface.getCloud_ptr();
    filtered_cloud = XYZRGBACloud_ptr(new XYZRGBACloud);

    io_interface.setSensorSequencialGrabbing(true);


    Viewer<PXYZRGBA> viewer1("Original cloud");
    viewer1.addCloud(cloud);

    Viewer<PXYZRGBA> viewer2("Filtered cloud");
    viewer2.addCloud(filtered_cloud);

    while(true){
        io_interface.grabSequencialFrameSensor();
        Filtering<PXYZRGBA>::filterArea(cloud,filtered_cloud,0.5, 1.5, "z");

        viewer1.showExternalCloud(cloud);
        viewer2.showExternalCloud(filtered_cloud);
    }

    return 0;
}
