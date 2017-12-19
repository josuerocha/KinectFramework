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
#include <pcl/visualization/pcl_visualizer.h>

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

///GLOBALS
PolygonMesh::Ptr reconstructed (new PolygonMesh);
IO<PXYZ> io_interface;

///FUNCTION PROTOTYPES
void keyboardEventOccurred (const pcl::visualization::KeyboardEvent &event, void* viewer_void);

int main (int argc, char** argv){

    XYZCloud_ptr cloud (new XYZCloud);
    XYZCloud_ptr filtered_cloud (new XYZCloud);
    XYZCloud_ptr filtered_cloud_xyz (new XYZCloud);

    io_interface.setSensorSequencialGrabbing(true);
    io_interface.grabSequencialFrameSensor();
    cloud = io_interface.getCloud_ptr();

    Viewer<PXYZ> viewer("Downsampled");
    viewer.addCloud(filtered_cloud);
    viewer.setViewerText("Visualizing live cloud.",Coord2D(30.0,10.0),30.0,Color(1.0f,0.0f,0.0f,1.0f),"text1");
    viewer.viewer->registerKeyboardCallback(keyboardEventOccurred,(void*)viewer.viewer.get ());

    Viewer<PXYZRGBA> viewer2("Reconstructed");
    //viewer2.addMesh(reconstructed);
    viewer2.setViewerText("Visualizing live cloud.",Coord2D(30.0,10.0),30.0,Color(1.0f,0.0f,0.0f,1.0f),"text1");

    io_interface.readFromPCD("bunny.pcd",cloud);
    Filtering<PXYZ>::voxelize(cloud,cloud,Dimension3D(0.01f,0.01f,0.01f));

    cout<<"TAMANHO " << cloud->size() << endl;
    while(true){
        //io_interface.grabSequencialFrameSensor();



        //Filtering<PXYZ>::filterArea(cloud,filtered_cloud,0.5,1.5,"z");

        //Filtering<PXYZ>::statisticalOutlierFilter(filtered_cloud,filtered_cloud,10,5.0f);

        Reconstruction<PXYZ>::triangulate(cloud,reconstructed);

        viewer.showExternalCloud(cloud);
        viewer2.showExternalMesh(reconstructed);

    }

    return (0);
}

void keyboardEventOccurred (const pcl::visualization::KeyboardEvent &event, void* viewer_void){
  if (event.getKeySym () == "space" && event.keyDown ()){
    cout<<"SAVING" << endl;
    io_interface.writeToPLY("reconstruction.ply",reconstructed);
    system("pwd");
  }
}

