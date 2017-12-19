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

    vector<float> coefficients;
    coefficients.push_back(0);
    coefficients.push_back(0);
    coefficients.push_back(1);
    coefficients.push_back(0);

    while(true){
        io_interface.grabSequencialFrameSensor();
        ///PROJECTING SCENE OVER X-Y PLANE
        Filtering<PXYZRGBA>::parametricProjection(cloud,filtered_cloud,SACMODEL_PLANE,coefficients);

        viewer1.showExternalCloud(cloud);
        viewer2.showExternalCloud(filtered_cloud);
    }

    return 0;
}
