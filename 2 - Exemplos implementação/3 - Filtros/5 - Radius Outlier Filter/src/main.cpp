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

XYZCloud_ptr cloud;
XYZCloud_ptr filtered_cloud;
IO<PXYZ> io_interface;

int main(){
    cloud = XYZCloud_ptr(new XYZCloud);
    filtered_cloud = XYZCloud_ptr(new XYZCloud);

    io_interface.readFromPCD("table_scene.pcd", cloud);
    Filtering<PXYZ>::radiusOutlierFilter(cloud,filtered_cloud,0.02f,10); ///2 neighbors will be analyzed for each
        ///seed point and any point that doesnt have at least 2 points withinthe radius will be removed

    Viewer<PXYZ> viewer1("Original cloud");
    viewer1.addCloud(cloud);
    viewer1.showExternalCloud(cloud);
    viewer1.Spin();

    Viewer<PXYZ> viewer2("Filtered cloud");
    viewer2.addCloud(filtered_cloud);
    viewer2.showExternalCloud(filtered_cloud);

    while(true){
        viewer2.Spin();
        viewer1.Spin();
    }

    return 0;
}
