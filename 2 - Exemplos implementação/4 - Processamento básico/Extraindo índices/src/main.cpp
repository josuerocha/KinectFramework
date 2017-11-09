/** JOSUÈ ROCHA LIMA - CLUSTER EXTRACTION DEMO
This code extracts a segmented cluster from the original PointCloud grabbed from a Kinect Sensor
**/
///STANDARD INCLUDES
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <time.h>

///PCL INCLUDES
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/point_representation.h>
#include <pcl/search/search.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d.h>

///CUSTOM INCLUDES
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

float smoothness = M_PI / 45;
float curvature = 1.0;

int main (int argc, char** argv){
    XYZRGBACloud_ptr cloud (new XYZRGBACloud);
    XYZRGBACloud_ptr filtered_cloud (new XYZRGBACloud);

    IO<PXYZRGBA> io;
    io.setSensorSequencialGrabbing(true);
    cloud = io.getCloud_ptr();

    Viewer<PXYZRGBA> viewer;
    viewer.setViewerText("Visualizing filtered cloud.",Coord2D(30.0,10.0),30.0,Color(1.0f,0.0f,0.0f,1.0f),"text1");
    viewer.addCloud(filtered_cloud);

    Viewer<PXYZRGBA> viewer2;
    viewer2.setViewerText("Visualizing live cloud.",Coord2D(30.0,10.0),30.0,Color(1.0f,0.0f,0.0f,1.0f),"text1");
    viewer2.addCloud(cloud);

    KinectControl kinect;
    kinect.Move(31);
    kinect.Move(0);

    while(true){
        io.grabSequencialFrameSensor();

        Filtering<PXYZRGBA>::filterArea(cloud,filtered_cloud,0.5,1.25,"z");
        Filtering<PXYZRGBA>::voxelize(filtered_cloud,filtered_cloud,Dimension3D(0.03f,0.03f,0.03f));
        Filtering<PXYZRGBA>::statisticalOutlierFilter(filtered_cloud,filtered_cloud,10,5.0);

        SearchXYZRGBA_ptr tree = boost::shared_ptr<search::Search<PointXYZRGBA> > (new search::KdTree<PointXYZRGBA>);
        Object<PXYZRGBA> object;

        clock_t tStart = clock();
        NormalCloud_ptr normals(new NormalCloud);
        Calculations<PXYZRGBA>::estimateNormalsParallel(filtered_cloud, normals, 50);
        SegmentationAlgorithms::ransac(filtered_cloud, 0.1,SACMODEL_CYLINDER,0.7,normals,object);

        viewer2.showExternalCloud(filtered_cloud);

        object.extractIndices(true,filtered_cloud,filtered_cloud);

        viewer.showExternalCloud(filtered_cloud);


        cout<<"END . Time taken " << (double)(clock() - tStart)/CLOCKS_PER_SEC << " seconds" << endl;
        cout<<"________________________________________________"<<endl;
    }

    return 0;
}



