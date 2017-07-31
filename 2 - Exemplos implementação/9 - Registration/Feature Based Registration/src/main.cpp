//STANDARD INCLUDES
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <time.h>

//PCL INCLUDES
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/point_representation.h>
#include <pcl/search/search.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d.h>

//CUSTOM INCLUDES
#include "IO.h"
#include "Processing.h"
#include "Filtering.h"
#include "CustomStructures.h"
#include "SegmentationAlgorithms.h"
#include "Calculations.h"
#include "KinectControl.h"
#include "Viewer.h"
#include "Registering.h"

using namespace std;
using namespace pcl;

int main (int argc, char** argv){
    XYZRGBACloud_ptr cloud (new XYZRGBACloud);
    XYZRGBACloud_ptr filtered_cloud (new XYZRGBACloud);
    XYZRGBACloud_ptr main_cloud(new XYZRGBACloud);

    IO<PXYZRGBA> io;
    io.setSensorSequencialGrabbing(true);
    io.grabSequencialFrameSensor();
    cloud = io.getCloud_ptr();
    io.grabSequencialFrameSensor();

    Filtering<PXYZRGBA>::filterArea(cloud,filtered_cloud,0.5,1.5,"z");
    Filtering<PXYZRGBA>::voxelize(filtered_cloud,filtered_cloud,Dimension3D(0.03f,0.03f,0.03f));
    Filtering<PXYZRGBA>::removeOutliers(filtered_cloud,filtered_cloud,10,5.0);
    copyPointCloud(*filtered_cloud, *main_cloud);

    Viewer<PXYZRGBA> viewer;
    viewer.addCloud(main_cloud);
    viewer.setViewerText("Visualizing live cloud.",Coord2D(30.0,10.0),30.0,Color(1.0f,0.0f,0.0f,1.0f),"text1");

    KinectControl kinect;
    kinect.Move(30);
    kinect.Move(-30);
    kinect.Move(0);

    clock_t tStart;

    while(true){
        tStart = clock();

        io.grabSequencialFrameSensor();

        Filtering<PXYZRGBA>::filterArea(cloud,filtered_cloud,0.5,3.5,"z");
        Filtering<PXYZRGBA>::voxelize(filtered_cloud,filtered_cloud,Dimension3D(0.03f,0.03f,0.03f));
        Filtering<PXYZRGBA>::removeOutliers(filtered_cloud,filtered_cloud,10,5.0);


        cout<<"ABOUT TO REGISTER"<<endl;
        Registering<PXYZRGBA>::registerFBR(filtered_cloud,main_cloud,filtered_cloud);
        cout<<"FINISHED REGISTERING"<<endl;
        *main_cloud = *main_cloud + *filtered_cloud;
        viewer.showExternalCloud(main_cloud);
        cout<<"AFF"<<endl;
    }

    return 0;
}



