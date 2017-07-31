#include "Transformations.h"

using namespace std;
using namespace pcl;

template <class T>
Transformations<T>::Transformations()
{
    //ctor
}

template <class T>
Transformations<T>::~Transformations()
{
    //dtor
}

template <class T>
void Transformations<T>::translateCloud(float x, float y, float z, class PointCloud<T>::Ptr source, class PointCloud<T>::Ptr output){

    Eigen::Affine3f transform_2 = Eigen::Affine3f::Identity();

    transform_2.translation() << x, y, z;

    transformPointCloud (*source, *source, transform_2);

}

template <class T>
void Transformations<T>::rotateCloud(float angle, char axis,class PointCloud<T>::Ptr source,class PointCloud<T>::Ptr output){

    Eigen::Affine3f transform_2 = Eigen::Affine3f::Identity();

    switch(axis){
        case 'x':
            transform_2.rotate (Eigen::AngleAxisf (angle, Eigen::Vector3f::UnitX()));
            break;
        case 'y':
            transform_2.rotate (Eigen::AngleAxisf (angle, Eigen::Vector3f::UnitY()));
            break;
        case 'z':
            transform_2.rotate (Eigen::AngleAxisf (angle, Eigen::Vector3f::UnitZ()));
            break;
    }

    transformPointCloud (*source, *output, transform_2);

}
