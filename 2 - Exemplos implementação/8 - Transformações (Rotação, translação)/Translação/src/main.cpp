/** JOSUÈ ROCHA LIMA - ROTATION DEMO
This code rotates a cloud grabbed from kinect sensor about the X axis over
the iterations
**/
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
#include "Transformations.h"
#include "Viewer.h"

using namespace std;
using namespace pcl;

int main (int argc, char** argv){

    XYZRGBACloud_ptr cloud (new XYZRGBACloud);
    XYZRGBACloud_ptr filtered_cloud (new XYZRGBACloud);

    IO<PXYZRGBA> io;
    io.setSensorSequencialGrabbing(true);
    cloud = io.getCloud_ptr();

    Viewer<PXYZRGBA> viewer;
    viewer.setViewerText("Visualizing live cloud.",Coord2D(30.0,10.0),30.0,Color(1.0f,0.0f,0.0f,1.0f),"text1");
    viewer.addCloud(filtered_cloud);

    KinectControl kinect;
    kinect.Move(31);
    kinect.Move(-5);

    float translation_index = 0;
    bool increment = true;

    while(true){
        io.grabSequencialFrameSensor();

        Filtering<PXYZRGBA>::filterArea(cloud,filtered_cloud,0.0,1.25,"z");
        Filtering<PXYZRGBA>::voxelize(filtered_cloud,filtered_cloud,Dimension3D(0.04f,0.04f,0.04f));
        Filtering<PXYZRGBA>::statisticalOutlierFilter(filtered_cloud,filtered_cloud,10,5.0);

        Transformations<PXYZRGBA>::translateCloud(translation_index,0,0,filtered_cloud,filtered_cloud);

        int tStart= clock();

        viewer.showExternalCloud(filtered_cloud);

        if(translation_index >= 2) {increment = false;}
        else if(translation_index <=-2 ){increment = true;}

        if(increment){translation_index += 0.1;}
        else{translation_index -= 0.1;}

        cout<<"END . Time taken " << (double)(clock() - tStart)/CLOCKS_PER_SEC << " seconds" << endl;
        cout<<"________________________________________________"<<endl;

    }

    return 0;
}



