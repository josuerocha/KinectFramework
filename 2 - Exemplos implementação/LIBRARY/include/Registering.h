#ifndef REGISTRATION_H
#define REGISTRATION_H

//PCL INCLUDES
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/point_representation.h>
#include <pcl/registration/icp.h>
#include <pcl/registration/icp_nl.h>

template <class T>
class Registering{
    private:
        pcl::IterativeClosestPoint<T,T> icp;
        pcl::IterativeClosestPointNonLinear<T, T> icpNl;

    protected:

    public:
        Registering();
        ~Registering();

        bool registerICP(class pcl::PointCloud<T>::Ptr source_cloud,class pcl::PointCloud<T>::Ptr target_cloud,class pcl::PointCloud<T>::Ptr final_cloud,int iterations,double distanceThresh);
        bool registerICPNonLinear(class pcl::PointCloud<T>::Ptr source_cloud,class pcl::PointCloud<T>::Ptr target_cloud,class pcl::PointCloud<T>::Ptr final_cloud,int iterations,double distanceThresh);

        void registerFBR(class pcl::PointCloud<T>::Ptr source_cloud,class pcl::PointCloud<T>::Ptr target_cloud,class pcl::PointCloud<T>::Ptr final_cloud);
};

template class Registering <pcl::PointXYZ>;
template class Registering <pcl::PointXYZRGB>;
template class Registering <pcl::PointXYZRGBA>;

#endif // REGISTRATION_H
