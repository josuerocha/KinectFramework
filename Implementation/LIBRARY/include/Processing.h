#ifndef PROCESSING_H
#define PROCESSING_H

///STANDARD INCLUDES


///PCL INCLUDES
#include <pcl/io/pcd_io.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/features/normal_3d.h>

///CUSTOM INCLUDES
#include "CustomStructures.h"

template <class T>
class Processing
{   private:

    public:
        Processing();
        ~Processing();
        static void simpleConcatenate(class pcl::PointCloud<T>::Ptr cloudA, class pcl::PointCloud<T>::Ptr cloudB,class pcl::PointCloud<T>::Ptr output);
        static void fieldConcatenate(class pcl::PointCloud<T>::Ptr cloudA, pcl::PointCloud<pcl::Normal>::Ptr cloudB, pcl::PointCloud<pcl::PointNormal>::Ptr output);
        static void toXYZ( class pcl::PointCloud<T>::Ptr source, pcl::PointCloud<PXYZ>::Ptr output);

        static void addPoint( pcl::PointCloud<PXYZ>::Ptr input_cloud,Coord3D coord);
        static void addPoint( pcl::PointCloud<PXYZRGB>::Ptr input_cloud,Coord3D coord);
        static void addPoint( pcl::PointCloud<PXYZRGBA>::Ptr input_cloud,Coord3D coord);
};

template class Processing <pcl::PointXYZ>;
template class Processing <pcl::PointXYZRGB>;
template class Processing <pcl::PointXYZRGBA>;

#endif // PROCESSING_H
