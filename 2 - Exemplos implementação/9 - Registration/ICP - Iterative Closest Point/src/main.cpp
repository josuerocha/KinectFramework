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

XYZRGBACloud_ptr cloud (new XYZRGBACloud);
XYZRGBACloud_ptr filtered_cloud (new XYZRGBACloud);
XYZRGBACloud_ptr previous_cloud(new XYZRGBACloud);
XYZRGBACloud_ptr main_cloud(new XYZRGBACloud);

IO<PXYZRGBA> io_interface;

Viewer<PXYZRGBA> viewer;

Registering<PXYZRGBA> registering;

void keyboardEventOccurred (const pcl::visualization::KeyboardEvent &event, void* viewer_void){
  if (event.getKeySym () == "space" && event.keyDown ()){
        io_interface.grabSequencialFrameSensor();

        Filtering<PXYZRGBA>::filterArea(cloud,filtered_cloud,0.5,1.5,"z");
        Filtering<PXYZRGBA>::voxelize(filtered_cloud,filtered_cloud,Dimension3D(0.06f,0.06f,0.06f));
        Filtering<PXYZRGBA>::statisticalOutlierFilter(filtered_cloud,filtered_cloud,10,5.0);

        bool converged = false;


        while(!converged){
            cout<<"ABOUT TO REGISTER"<<endl;
            converged = registering.registerICP(filtered_cloud,previous_cloud,filtered_cloud,200,0.01f);
        }

        *main_cloud = *main_cloud + *filtered_cloud;
        Filtering<PXYZRGBA>::voxelize(main_cloud,main_cloud,Dimension3D(0.03f,0.03f,0.03f));
        copyPointCloud(*filtered_cloud, *previous_cloud);
        viewer.showExternalCloud(main_cloud);
        cout<<"FINISHED"<<endl;
  }
}

int main (int argc, char** argv){

    io_interface.setSensorSequencialGrabbing(true);
    io_interface.grabSequencialFrameSensor();
    cloud = io_interface.getCloud_ptr();
    io_interface.grabSequencialFrameSensor();

    Filtering<PXYZRGBA>::filterArea(cloud,filtered_cloud,0.5,1.5,"z");
    Filtering<PXYZRGBA>::voxelize(filtered_cloud,filtered_cloud,Dimension3D(0.03f,0.03f,0.03f));
    Filtering<PXYZRGBA>::statisticalOutlierFilter(filtered_cloud,filtered_cloud,10,5.0);
    copyPointCloud(*filtered_cloud, *main_cloud);
    copyPointCloud(*filtered_cloud, *previous_cloud);

    viewer.addCloud(main_cloud);
    viewer.setViewerText("Visualizing live cloud.",Coord2D(30.0,10.0),30.0,Color(1.0f,0.0f,0.0f,1.0f),"text1");
    viewer.viewer->registerKeyboardCallback(keyboardEventOccurred,(void*)viewer.viewer.get ());

    KinectControl kinect;
    kinect.Move(10);

    cout<<"ENTERED LOOP"<<endl;
    while(true){
        viewer.Spin();
    }

    return 0;
}



