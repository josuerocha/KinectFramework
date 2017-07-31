#ifndef CALCULATIONS_H
#define CALCULATIONS_H

//STANDARD INCLUDES
#include <iostream>
#include <string>
#include <vector>

//PCL INCLUDES
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/point_representation.h>
#include <pcl/search/search.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/common/centroid.h>

//CUSTOM INCLUDES
#include "CustomStructures.h"

template <class T>
class Calculations
{
    private:

    public:
        Calculations();
        ~Calculations();

        static void estimateNormals(class pcl::PointCloud<T>::Ptr input_cloud,NormalCloud_ptr normals, int kSearch);
        static void estimateNormalsParallel(class pcl::PointCloud<T>::Ptr input_cloud,NormalCloud_ptr normals, int kSearch);
        static Coord3D calculateCentroid(class pcl::PointCloud<T>::Ptr input_cloud);
        static Coord3D calculateObjCentroid(class pcl::PointCloud<T>::Ptr input_cloud, pcl::PointIndices indices);
};

template class Calculations <pcl::PointXYZ>;
template class Calculations <pcl::PointXYZRGB>;
template class Calculations <pcl::PointXYZRGBA>;

#endif // CALCULATIONS_H
