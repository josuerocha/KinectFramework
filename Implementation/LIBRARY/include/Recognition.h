#ifndef RECOGNITION_H
#define RECOGNITION_H

///PCL INCLUDES
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/point_cloud.h>
#include <pcl/correspondence.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/features/shot_omp.h>
#include <pcl/features/board.h>
#include <pcl/filters/uniform_sampling.h>
#include <pcl/recognition/cg/hough_3d.h>
#include <pcl/recognition/cg/geometric_consistency.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/kdtree/impl/kdtree_flann.hpp>
#include <pcl/common/transforms.h>
#include <pcl/console/parse.h>

///CUSTOM INCLUDES
#include "Viewer.h"

template <class T>
class Recognition
{
    private:


    protected:

    public:
        Recognition();
        virtual ~Recognition();

        static double computeCloudResolution (const class pcl::PointCloud<T>::ConstPtr &cloud);
        static void run (class pcl::PointCloud<T>::Ptr model,class pcl::PointCloud<T>::Ptr scene,class pcl::PointCloud<T>::Ptr output);
};

//template class Recognition <pcl::PointXYZ>;
template class Recognition <pcl::PointXYZRGB>;
template class Recognition <pcl::PointXYZRGBA>;

#endif // RECOGNITION_H
