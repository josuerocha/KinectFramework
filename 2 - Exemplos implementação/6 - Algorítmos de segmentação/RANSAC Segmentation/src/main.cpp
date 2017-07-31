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
    kinect.Move(-25);

    while(true){
        io.grabSequencialFrameSensor();
        ///cout<< "Size " << cloud->points.size() << endl;

        Filtering<PXYZRGBA>::filterArea(cloud,filtered_cloud,0.5,2.0,"z");
        Filtering<PXYZRGBA>::voxelize(filtered_cloud,filtered_cloud,Dimension3D(0.04f,0.04f,0.04f));
        Filtering<PXYZRGBA>::statisticalOutlierFilter(filtered_cloud,filtered_cloud,10,5.0);

        vector <PointIndices> clusters;
        PointIndices cluster;
        clusters.push_back(cluster);

        clock_t tStart = clock();
        Object<PXYZRGBA> object;
        SegmentationAlgorithms::ransac(filtered_cloud, 0.02,SACMODEL_PLANE,object);

        object.paintCluster(filtered_cloud,Color(255,0,0,0));

        viewer.showExternalCloud(filtered_cloud);

        cout<<"END . Time taken " << (double)(clock() - tStart)/CLOCKS_PER_SEC << " seconds" << endl;
        cout<<"________________________________________________"<<endl;
    }

    return 0;
}



