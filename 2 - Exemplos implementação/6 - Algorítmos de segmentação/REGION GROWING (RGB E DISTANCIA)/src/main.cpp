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

float smoothness = 3.99 * (M_PI / 180); //SMOOTHNESS SET TO 3.99 DEGREES
float curvature = 1.0;

int main (int argc, char** argv)
{
    XYZRGBACloud_ptr cloud (new XYZRGBACloud);
    XYZRGBACloud_ptr filtered_cloud (new XYZRGBACloud);
    XYZRGBCloud_ptr colored_cloud(new PointCloud <PointXYZRGB>);

    IO<PXYZRGBA> io;
    io.setSensorSequencialGrabbing(true);
    io.grabSequencialFrameSensor();
    cloud = io.getCloud_ptr();

    Viewer<PXYZRGB> viewer;
    viewer.addCloud(colored_cloud);
    viewer.setViewerText("Visualizing segmented cloud.",Coord2D(30.0,10.0),30.0,Color(1.0f,0.0f,0.0f,1.0f),"text1");

    Viewer<PXYZRGBA> viewer2;
    viewer2.addCloud(filtered_cloud);
    viewer2.setViewerText("Visualizing live cloud.",Coord2D(30.0,10.0),30.0,Color(1.0f,0.0f,0.0f,1.0f),"text1");

    KinectControl kinect;
    kinect.Move(30);
    kinect.Move(-30);
    kinect.Move(15);
    //io.ReadFromPCD("test49.pcd");
    while(true){
        clock_t tStart = clock();

        io.grabSequencialFrameSensor();

        Filtering<PXYZRGBA>::filterArea(cloud,filtered_cloud,0.5,1.5,"z");
        Filtering<PXYZRGBA>::voxelize(filtered_cloud,filtered_cloud,Dimension3D(0.04f,0.04f,0.04f));
        Filtering<PXYZRGBA>::statisticalOutlierFilter(filtered_cloud,filtered_cloud,10,5.0);

        NormalCloud_ptr normals(new NormalCloud);
        SearchXYZRGBA_ptr tree = boost::shared_ptr<search::Search<PointXYZRGBA> > (new search::KdTree<PointXYZRGBA>);

        Calculations<PXYZRGBA>::estimateNormals(filtered_cloud, normals, 50);

        Object<PXYZRGBA> groundPlane;
        SegmentationAlgorithms::ransac(filtered_cloud,0.005,SACMODEL_PLANE, groundPlane);
        //groundPlane.extractIndices(true,filtered_cloud,filtered_cloud);

        vector < Object<PXYZRGB> > objects;
        SegmentationAlgorithms::regionGrowingRGB(filtered_cloud,colored_cloud,normals,tree,5,100000000,50,smoothness,curvature,0.08f,255,255,objects);

        float minHeight = 30;
        int o = 0;
        cout<<"Number of objects: " << objects.size() << endl;
        /*for(unsigned int i=0 ; i<objects.size(); i++){
            objects[i].highLightClusterHeight(colored_cloud);
            if(objects[i].getHeight() < minHeight){
                minHeight = objects[i].getHeight();
                o = i;
            }
        }*/

        //viewer.addArrow(objects[o].getCentroid(),Coord3D(0,0,0),Color(255,0,0,255));

        cout<<"END . Time taken " << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
        cout<<"________________________________________________"<<endl;

        viewer.showExternalCloud(colored_cloud);
        viewer2.showExternalCloud(filtered_cloud);

    }

    return (0);
}



