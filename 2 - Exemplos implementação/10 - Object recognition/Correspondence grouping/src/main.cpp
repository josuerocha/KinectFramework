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

///BOOST INCLUDES
#include <boost/thread.hpp>

///CUSTOM INCLUDES
#include "IO.h"
#include "CustomStructures.h"
#include "KinectControl.h"
#include "Viewer.h"
#include "Registering.h"
#include "Recognition.h"
#include "Filtering.h"

using namespace std;
using namespace pcl;

///FUNCTION PROTOTYPES
void updateViewer();
void areaPickingCallback (const pcl::visualization::AreaPickingEvent &event, void* cloudStruct);

///WRAPPER STRUCT
struct CloudandIndices{
        pcl::PointCloud<PointXYZRGBA>::Ptr cloud_ptr;

        pcl::PointIndices::Ptr point_indicies;

};


XYZRGBACloud_ptr cloud (new XYZRGBACloud);
XYZRGBACloud_ptr output (new XYZRGBACloud);
XYZRGBACloud_ptr filtered_cloud (new XYZRGBACloud);
XYZRGBACloud_ptr model (new XYZRGBACloud);

Viewer<PXYZRGBA> viewer1("Scene");

bool outputReady;

boost::thread    m_thread;

int main (int argc, char** argv){

    outputReady = false;
    m_thread = boost::thread(updateViewer);

    IO<PXYZRGBA> io;
    io.readFromPCD("models/milk.pcd",model);
    io.readFromPCD("models/scene.pcd",cloud);

    //io.setSensorSequencialGrabbing(true);
    //io.grabSequencialFrameSensor();
    //cloud = io.getCloud_ptr();

    viewer1.addCloud(model);
    viewer1.setViewerText("Visualizing MODEL cloud.",Coord2D(30.0,10.0),30.0,Color(1.0f,0.0f,0.0f,1.0f),"text1");
    ///REGISTERING AREA PICKING CALLBACK
    PointCloud<PXYZRGBA>::Ptr point_cloud_ptr(new PointCloud<PXYZRGBA>);
    PointIndices::Ptr point_indicies (new pcl::PointIndices());
    struct CloudandIndices pointSelectors;
    pointSelectors.cloud_ptr = point_cloud_ptr;
    pointSelectors.point_indicies = point_indicies;
    CloudandIndices *pointSelectorsPtr = &pointSelectors;
    viewer1.viewer->registerAreaPickingCallback (areaPickingCallback, (void*)pointSelectorsPtr);

    //KinectControl kinect;

    //kinect.Move(5);

    clock_t tStart;


    viewer1.setViewerText("Visualizing LIVE cloud.",Coord2D(30.0,10.0),30.0,Color(1.0f,0.0f,0.0f,1.0f),"text1");
    while(true){
         tStart = clock();

        //io.grabSequencialFrameSensor();
        Filtering<PXYZRGBA>::filterArea(cloud,cloud,0.5,1.5,"z");
        Recognition<PXYZRGBA>::run(model,cloud, output);
        outputReady = true;


    }

    return 0;
}

void updateViewer(){
    while(true){
        if(outputReady){
            viewer1.showExternalCloud(output);
            outputReady = false;
        } else{
            viewer1.Spin();
        }
    }
}

void areaPickingCallback (const pcl::visualization::AreaPickingEvent &event, void* cloudStruct){

        struct CloudandIndices *cloudInfoStruct = (struct CloudandIndices*) cloudStruct;

        PointCloud<PointXYZRGBA>::Ptr tempCloud = cloudInfoStruct->cloud_ptr;

        PointIndices::Ptr point_indices_ = cloudInfoStruct->point_indicies;



        if (event.getPointsIndices (point_indices_->indices))
        {
                std::cout <<"Picked "<< point_indices_->indices.size() << " points." << endl;
                int point_indices_size = point_indices_->indices.size();
                for (unsigned int i = 0; i < point_indices_->indices.size(); i++){
                        cout<< "OBA" << endl;

                        unsigned int index = point_indices_->indices[i];

                        cout << "X: "<< tempCloud->points[index].x ;
                        cout << "   Y: "<< tempCloud->points[index].y ;
                        cout << "   Z: "<< tempCloud->points[index].z << endl;

                }

        }
        else
                cout<<"No valid points selected!"<< endl;
}

