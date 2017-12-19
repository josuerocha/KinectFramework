#ifndef OBJECT_H
#define OBJECT_H

///STANDARD INCLUDES
#include <vector>
#include <typeinfo>
#include <math.h>

///PCL INCLUDES
#include <pcl/filters/extract_indices.h>
#include <pcl/features/normal_3d.h>

///CUSTOM INCLUDES
#include "CustomStructures.h"
#include "Calculations.h"

template <class T>
class Object{

    private:
        int lowestIndex;
        int highestIndex;
        Coord3D highestPoint;
        Coord3D lowestPoint;
        Coord3D centroid;
        float height;
    protected:

    public:

        pcl::PointIndices pointIndices; ///Vector of indices to store points of object

        Object();
        ~Object();

        void paintCluster(class pcl::PointCloud<T>::Ptr input_cloud, Color color);
        void highLightClusterHeight(class pcl::PointCloud<T>::Ptr input_cloud);
        void extractIndices(bool negativeExtraction,class pcl::PointCloud<T>::Ptr input_cloud,class pcl::PointCloud<T>::Ptr output_cloud);

        float getHeight();
        Coord3D getHighestPoint();
        Coord3D getLowestPoint();
        Coord3D getCentroid();
};

//template class Object <pcl::PointXYZ>;
template class Object <pcl::PointXYZRGB>;
template class Object <pcl::PointXYZRGBA>;

#endif // OBJECT_H
