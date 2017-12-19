//Standard includes
#include <iostream>
#include <string>
#include <pcl/io/pcd_io.h>

//Custom includes
#include "IO.h"
#include "Processing.h"
#include "Viewer.h"

using namespace std;
using namespace pcl;

typedef pcl::PointXYZRGBA PointT;

int main(){
    PointCloud<PointT>::Ptr cloudA(new PointCloud<PointT>);
    PointCloud<PointT>::Ptr cloudB(new PointCloud<PointT>);
    PointCloud<PointT>::Ptr finalCloud(new PointCloud<PointT>);

    IO<PointT> io;
    string path;

    cout<<"Informe o caminho para o arquivo PCD 1:" << endl;
    cin>>path;
    io.readFromPCD(path,cloudA);

    cout<<"Informe o caminho para o arquivo PCD 2:" << endl;
    cin>>path;
    io.readFromPCD(path,cloudB);


    Processing<PointT>::SimpleConcatenate(cloudA,cloudB,finalCloud);

    string newPath = "FinalCloud.pcd";
    io.writeToPCD(newPath,finalCloud);

    Viewer<PointT> viewer;
    viewer.addCloud(finalCloud);
    while(true){
        viewer.Spin();
    }

    return 0;
}
