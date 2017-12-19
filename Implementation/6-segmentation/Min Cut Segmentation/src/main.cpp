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

using namespace std;
using namespace pcl;

float smoothness = M_PI / 2;
float curvature = 1.0;

int main (int argc, char** argv)
{
    XYZCloud_ptr cloud (new XYZCloud);
    XYZCloud_ptr filtered_cloud (new XYZCloud);
    XYZRGBCloud_ptr colored_cloud(new XYZRGBCloud);

    IO<PXYZ> io;
    io.setSensorSequencialGrabbing(true);
    io.grabSequencialFrameSensor();
    cloud = io.getCloud_ptr();

    Viewer<PXYZRGB> viewer;
    viewer.addCloud(colored_cloud);
    viewer.setViewerText("Visualizing live cloud.",Coord2D(30.0,10.0),30.0,Color(1.0f,0.0f,0.0f,1.0f),"text1");

    KinectControl kinect;
    kinect.Move(30);
    kinect.Move(-30);
    kinect.Move(0);


    //io.readFromPCD("min_cut_segmentation_tutorial.pcd",cloud);
    while(true){
        clock_t tStart = clock();
        io.grabSequencialFrameSensor();

        Filtering<PXYZ>::filterArea(cloud,filtered_cloud,0.5,1.5,"z");
        Filtering<PXYZ>::voxelize(filtered_cloud,filtered_cloud,Dimension3D(0.04f,0.04f,0.04f));
        Filtering<PXYZ>::statisticalOutlierFilter(filtered_cloud,filtered_cloud,10,5.0);

        vector < Object<PXYZRGB> > objects;

        SegmentationAlgorithms::minCut(filtered_cloud,colored_cloud,Coord3D(0,0,1.0),2.5,0.05,14,0.8,objects);
        /*
        float minHeight = 30;

        int o = -1;
        for(unsigned int i=0 ; i<objects.size(); i++){
            objects[i].highLightClusterHeight(colored_cloud);
            if(objects[i].getHeight() < minHeight){
                minHeight = objects[i].getHeight();
                o = i;
            }
        }

        if(o != -1){
            viewer.addArrow(objects[o].getCentroid(),Coord3D(0,0,0),Color(255,0,0,255));
        }
        */
        cout<<"Finished region growing execution. Displaying now." << endl;
        cout<<"END . Time taken " << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;

        viewer.showExternalCloud(colored_cloud);
        cout<<"________________________________________________"<<endl;
    }

    return (0);
}



