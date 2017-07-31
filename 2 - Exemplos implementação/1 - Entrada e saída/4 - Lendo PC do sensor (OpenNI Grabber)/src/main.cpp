///Standard includes
#include <iostream>
#include <string>
#include <pcl/io/pcd_io.h>

///Custom includes
#include "IO.h"
#include "Processing.h"
#include "Viewer.h"

using namespace std;
using namespace pcl;

typedef pcl::PointXYZRGBA PointT;

int main(){
    PointCloud<PointT>::Ptr cloudA(new PointT);
    IO<PXYZRGBA> io;
    string path;

    cout<<"Informe o caminho para o arquivo PCD 1:" << endl;
    cin>>path;
    io.readFromPCD(path,cloudA);

    io.grabSingleFrameSensor();
    PointCloud<PointT>::Ptr cloudB = io.getCloud_ptr();

    pcl::PointCloud<PointT>::Ptr cloud1 (new pcl::PointCloud<PointT>);
    pcl::PointCloud<PointT>::Ptr cloud2 (new pcl::PointCloud<PointT>);

    PointCloud<PointT>::Ptr cloudC(new PointCloud<PointT>);
    *cloudC = *cloudA + *cloudB;
    //Processing<PXYZRGBA>::simpleConcatenate(cloudA,cloudB,cloudC);

    string newPath = "FinalCloud.pcd";
    io.writeToPCD(newPath,cloudC);

    Viewer<PXYZRGBA> viewer;
    viewer.addCloud(cloudC);
    viewer.showExternalCloud(cloudC);

    while(true){
        viewer.Spin();
    }

    return 0;
}
