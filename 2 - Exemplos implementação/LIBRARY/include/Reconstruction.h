#ifndef RECONSTRUCTION_H
#define RECONSTRUCTION_H

//STANDARD INCLUDES
#include <iostream>
#include <string>
#include <vector>

//PCL INCLUDES
#include <pcl/point_types.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <pcl/surface/mls.h>

//CUSTOM INCLUDES
#include "CustomStructures.h"
#include "Calculations.h"
#include "Processing.h"

template <class T>
class Reconstruction{
    private:

    public:
        Reconstruction();
        ~Reconstruction();

        static void triangulate(pcl::PointCloud<PXYZ>::Ptr input_cloud,pcl::PolygonMesh::Ptr triangles);
        static void movingLeastSquaresUpsampling(class pcl::PointCloud<T>::Ptr input_cloud,class pcl::PointCloud<T>::Ptr output_cloud,float searchRadius,float upSamplingRadius, float upSamplingStep);
        static void movingLeastSquaresSmoothing(class pcl::PointCloud<T>::Ptr input_cloud,class pcl::PointCloud<T>::Ptr output_cloud,float searchRadius);
};

template class Reconstruction <pcl::PointXYZ>;
template class Reconstruction <pcl::PointXYZRGB>;
template class Reconstruction <pcl::PointXYZRGBA>;

#endif // RECONSTRUCTION_H
