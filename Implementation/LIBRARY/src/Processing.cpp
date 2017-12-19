#include "Processing.h"

using namespace std;
using namespace pcl;

template <class T>
Processing<T>::Processing(){


}

template <class T>
Processing<T>::~Processing(){
    //dtor
}

template <class T>
void Processing<T>::simpleConcatenate(class PointCloud<T>::Ptr cloudA,class PointCloud<T>::Ptr cloudB,class PointCloud<T>::Ptr output){
    *output = (*cloudA) + (*cloudB);
}

template <class T>
void Processing<T>::fieldConcatenate(class PointCloud<T>::Ptr cloudA,PointCloud<Normal>::Ptr cloudB,PointCloud<PointNormal>::Ptr output){
    //concatenateFields(*cloudA, *cloudB, *output);
}

template <class T>
void Processing<T>::toXYZ(class PointCloud<T>::Ptr source,PointCloud<PointXYZ>::Ptr output){
    output->points.resize(source->points.size());
    for (size_t i = 0; i < source->points.size(); ++i){
        output->points[i].x = source->points[i].x;
        output->points[i].y = source->points[i].y;
        output->points[i].z = source->points[i].z;
    }
}

template <class T>
void Processing<T>::addPoint( PointCloud<PXYZRGBA>::Ptr input_cloud,Coord3D coord){
            PXYZRGBA point;
            point.x = coord.x;
            point.y = coord.y;
            point.z = coord.z;
            point.r = coord.r;
            point.g = coord.g;
            point.b = coord.b;
            point.a = coord.a;
            input_cloud->points.push_back(point);
}

template <class T>
void Processing<T>::addPoint( PointCloud<PXYZRGB>::Ptr input_cloud,Coord3D coord){
            PXYZRGB point;
            point.x = coord.x;
            point.y = coord.y;
            point.z = coord.z;
            point.r = coord.r;
            point.g = coord.g;
            point.b = coord.b;

            input_cloud->points.push_back(point);
}

template <class T>
void Processing<T>::addPoint( PointCloud<PXYZ>::Ptr input_cloud,Coord3D coord){
            PXYZ point;
            point.x = coord.x;
            point.y = coord.y;
            point.z = coord.z;

            input_cloud->points.push_back(point);
}
