#ifndef FILTERING_H
#define FILTERING_H

///PCL INCLUDES
#include <pcl/filters/passthrough.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/filters/uniform_sampling.h>
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/filters/project_inliers.h>

///CUSTOM INCLUDES
#include "CustomStructures.h"
#include "Calculations.h"

template <class T>
class Filtering{

    private:

    public:
        Filtering();
        ~Filtering();

        ///DOWNSAMPLING
        static void filterArea(class pcl::PointCloud<T>::Ptr input,class pcl::PointCloud<T>::Ptr output ,float minDistance, float maxDistance, std::string axis);
        static void voxelize(class pcl::PointCloud<T>::Ptr input,class pcl::PointCloud<T>::Ptr output, Dimension3D leafSize);
        static void uniformSampling(class pcl::PointCloud<T>::Ptr input, class pcl::PointCloud<T>::Ptr output, float radius);

        ///OUTLIER REMOVAL
        static void statisticalOutlierFilter(class pcl::PointCloud<T>::Ptr input, class pcl::PointCloud<T>::Ptr output,int mean, float stdDev);
        static void radiusOutlierFilter(class pcl::PointCloud<T>::Ptr input, class pcl::PointCloud<T>::Ptr output, float radius, unsigned int minNeighbors);

        ///PROJECTION
        static void parametricProjection(class pcl::PointCloud<T>::Ptr input, class pcl::PointCloud<T>::Ptr output, pcl::SacModel model, std::vector<float> &coefficientsVect);
};

template class Filtering <pcl::PointXYZ>;
template class Filtering <pcl::PointXYZRGB>;
template class Filtering <pcl::PointXYZRGBA>;

#endif // FILTERING_H
