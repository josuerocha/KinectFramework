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
#include "Reconstruction.h"

using namespace std;
using namespace pcl;

float smoothness = M_PI / 45;
float curvature = 1.0;

int main (int argc, char** argv){

    XYZRGBACloud_ptr cloud (new XYZRGBACloud);
    XYZRGBACloud_ptr filtered_cloud (new XYZRGBACloud);
    XYZRGBACloud_ptr reconstructed_cloud (new XYZRGBACloud);

    IO<PXYZRGBA> io;
    io.setSensorSequencialGrabbing(true);
    io.grabSequencialFrameSensor();
    cloud = io.getCloud_ptr();

    Viewer<PXYZRGBA> viewer("Downsampled");
    viewer.addCloud(filtered_cloud);
    viewer.setViewerText("Visualizing live cloud.",Coord2D(30.0,10.0),30.0,Color(1.0f,0.0f,0.0f,1.0f),"text1");

    Viewer<PXYZRGBA> viewer2("Reconstructed");
    viewer2.addCloud(reconstructed_cloud);
    viewer2.setViewerText("Visualizing live cloud.",Coord2D(30.0,10.0),30.0,Color(1.0f,0.0f,0.0f,1.0f),"text1");

    while(true){
        io.grabSequencialFrameSensor();



        Filtering<PXYZRGBA>::filterArea(cloud,filtered_cloud,0.5,1.5,"z");
        Filtering<PXYZRGBA>::voxelize(filtered_cloud,filtered_cloud,Dimension3D(0.04f,0.04f,0.04f));
        Filtering<PXYZRGBA>::statisticalOutlierFilter(filtered_cloud,filtered_cloud,10,5.0f);

        Reconstruction<PXYZRGBA>::movingLeastSquaresSmoothing(filtered_cloud,reconstructed_cloud,0.1f);

        viewer.showExternalCloud(filtered_cloud);
        viewer2.showExternalCloud(reconstructed_cloud);

    }

    return (0);
}



