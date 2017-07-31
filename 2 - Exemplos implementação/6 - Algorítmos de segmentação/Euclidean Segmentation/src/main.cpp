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
#include "Viewer.h"
#include "Object.h"

using namespace std;
using namespace pcl;

float smoothness = M_PI / 45;
float curvature = 1.0;

int main (int argc, char** argv){

    XYZRGBACloud_ptr cloud (new XYZRGBACloud);
    XYZRGBACloud_ptr filtered_cloud (new XYZRGBACloud);

    IO<PXYZRGBA> io;
    io.setSensorSequencialGrabbing(true);
    io.grabSequencialFrameSensor();
    cloud = io.getCloud_ptr();

    Viewer<PXYZRGBA> viewer;
    viewer.addCloud(filtered_cloud);
    viewer.setViewerText("Visualizing live cloud.",Coord2D(30.0,10.0),30.0,Color(1.0f,0.0f,0.0f,1.0f),"text1");

    while(true){
        io.grabSequencialFrameSensor();

        cout<< cloud->points.size() << endl;

        Filtering<PXYZRGBA>::filterArea(cloud,filtered_cloud,0.5,1.5,"z");
        Filtering<PXYZRGBA>::voxelize(filtered_cloud,filtered_cloud,Dimension3D(0.04f,0.04f,0.04f));
        Filtering<PXYZRGBA>::statisticalOutlierFilter(filtered_cloud,filtered_cloud,10,5.0f);

        SearchXYZRGBA_ptr tree = boost::shared_ptr<search::Search<PointXYZRGBA> > (new search::KdTree<PointXYZRGBA>);

        vector < Object<PXYZRGBA> > objects;

        clock_t tStart = clock();

        Object<PXYZRGBA> groundPlane;
        SegmentationAlgorithms::ransac(filtered_cloud,0.01,SACMODEL_PLANE, groundPlane);
        //groundPlane.extractIndices(true,filtered_cloud,filtered_cloud);

        SegmentationAlgorithms::euclidean(filtered_cloud,tree,2,1000,0.07f,objects);

        float minHeight = 30;
        int o = 0;
        cout<<"Number of objects: " << objects.size() << endl;
        for(unsigned int i=0 ; i<objects.size(); i++){
            objects[i].highLightClusterHeight(filtered_cloud);
            if(objects[i].getHeight() < minHeight){
                minHeight = objects[i].getHeight();
                o = i;
            }
        }

        viewer.addArrow(objects[o].getCentroid(),Coord3D(0,0,0),Color(255,0,0,255));

        cout<<"END . Time taken " << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
        cout<<"________________________________________________"<<endl;

        viewer.showExternalCloud(filtered_cloud);

    }

    return (0);
}



