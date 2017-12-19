#include "Calculations.h"

using namespace std;
using namespace pcl;

template <class T>
Calculations<T>::Calculations(){
    //ctor
}

template <class T>
Calculations<T>::~Calculations(){
    //dtor
}

template <class T>
void Calculations<T>::estimateNormals(class PointCloud<T>::Ptr input_cloud,NormalCloud_ptr normals, int kSearch){

    //CREATING TREE FOR SEARCH
    class search::Search<T>::Ptr tree = boost::shared_ptr<search::Search<T> > (new search::KdTree<T>);
    //CREATING NORMAL ESTIMATION OBJECT
    class NormalEstimation<T, Normal> normal_estimator;
    normal_estimator.setSearchMethod (tree);
    normal_estimator.setInputCloud (input_cloud);
    normal_estimator.setKSearch (kSearch);
    normal_estimator.compute (*normals);
}

template <class T>
void Calculations<T>::estimateNormalsParallel(class PointCloud<T>::Ptr input_cloud,NormalCloud_ptr normals, int kSearch){
    NormalEstimationOMP<T, Normal> norm_est;
    norm_est.setKSearch (kSearch);
    norm_est.setInputCloud (input_cloud);
    norm_est.compute (*normals);
}

template <class T>
Coord3D Calculations<T>::calculateCentroid(class PointCloud<T>::Ptr input_cloud){
    Eigen::Vector4f centroid;
    compute3DCentroid(*input_cloud, centroid);
    return Coord3D(centroid[0],centroid[1],centroid[2]);
}

template <class T>
Coord3D Calculations<T>::calculateObjCentroid(class PointCloud<T>::Ptr input_cloud, PointIndices indices){
    Eigen::Vector4f centroid;
    compute3DCentroid(*input_cloud,indices.indices, centroid);
    return Coord3D(centroid[0],centroid[1],centroid[2]);
}
