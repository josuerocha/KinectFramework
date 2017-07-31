#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

//STANDARD INCLUDES
#include <pcl/common/transforms.h>

//CUSTOM INCLUDES
#include "CustomStructures.h"

template <class T>
class Transformations
{
    private:

    public:
        Transformations();
        virtual ~Transformations();

        static void rotateCloud(float angle, char axis, class pcl::PointCloud<T>::Ptr source, class pcl::PointCloud<T>::Ptr output);
        static void translateCloud(float x,float y,float z, class pcl::PointCloud<T>::Ptr source, class pcl::PointCloud<T>::Ptr output);


};

template class Transformations <pcl::PointXYZ>;
template class Transformations <pcl::PointXYZRGB>;
template class Transformations <pcl::PointXYZRGBA>;


#endif // TRANSFORMATIONS_H
