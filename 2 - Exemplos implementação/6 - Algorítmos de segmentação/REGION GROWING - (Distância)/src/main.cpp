//Standard includes
#include <iostream>
#include <string>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/point_representation.h>
#include <vector>
#include <pcl/search/search.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d.h>
#include <time.h>

//Custom includes
#include "IO.h"
#include "Filtering.h"
#include "CustomStructures.h"
#include "SegmentationAlgorithms.h"
#include "Calculations.h"
#include "Object.h"
#include "Viewer.h"

using namespace std;
using namespace pcl;

typedef PointXYZ PXYZ;
typedef PointCloud<PXYZ>::Ptr CloudXYZ_ptr;

float smoothness = M_PI / 40;
float curvature = 1.0;

int main (int argc, char** argv){

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

    while(true)
    {
        clock_t tStart = clock();

        io.grabSequencialFrameSensor();

        Filtering<PXYZ>::filterArea(cloud,filtered_cloud,0.5,2.0,"z");
        Filtering<PXYZ>::voxelize(filtered_cloud,filtered_cloud,Dimension3D(0.04f,0.04f,0.04f));
        Filtering<PXYZ>::statisticalOutlierFilter(filtered_cloud,filtered_cloud,10,5.0);

        NormalCloud_ptr normals(new NormalCloud);
        SearchXYZ_ptr tree = boost::shared_ptr<search::Search<PointXYZ> > (new search::KdTree<PointXYZ>);
        Calculations<PXYZ>::EstimateNormals(filtered_cloud, normals, 50);

        vector < Object<PXYZRGB> > objects;
        SegmentationAlgorithms::regionGrowingXYZ(filtered_cloud,colored_cloud,normals,tree,5,1000,10,smoothness,curvature,objects);

        float minHeight = 30;
        int o = 0;
        cout<<"Number of objects: " << objects.size() << endl;
        for(unsigned int i=0 ; i<objects.size(); i++){
            objects[i].highLightClusterHeight(colored_cloud);
            if(objects[i].getHeight() < minHeight){
                minHeight = objects[i].getHeight();
                o = i;
            }
        }

        viewer.addArrow(objects[o].getCentroid(),Coord3D(0,0,0),Color(255,0,0,255));

        cout<<"END . Time taken " << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
        cout<<"________________________________________________"<<endl;

        viewer.showExternalCloud(colored_cloud);
    }

    return (0);
}



