#ifndef SEGMENTATIONALGORITHMS_H
#define SEGMENTATIONALGORITHMS_H

//STANDARD INCLUDES
#include <vector>

//PCL INCLUDES
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/point_representation.h>
#include <pcl/segmentation/region_growing.h>
#include <pcl/segmentation/region_growing_rgb.h>
#include <pcl/search/search.h>
#include <pcl/search/kdtree.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/segmentation/min_cut_segmentation.h>

//CUSTOM INCLUDES
#include "CustomStructures.h"
#include "Object.h"

class SegmentationAlgorithms
{   private:
        static void transformVectToObj(PIndicesVector &clusters, std::vector< Object<PXYZRGB> > &objects);
        static void transformVectToObj(PIndicesVector &clusters, std::vector< Object<PXYZRGBA> > &objects);

    public:
        SegmentationAlgorithms();
        ~SegmentationAlgorithms();

        static void regionGrowingXYZ(XYZCloud_ptr input_cloud,XYZRGBCloud_ptr output_cloud, NormalCloud_ptr normals,SearchXYZ_ptr tree, int minClusterSize,int maxClusterSize,
                                     unsigned int neighborNo, float smoothness, float curvature,std::vector<Object <PXYZRGB> > &objects);

        static void regionGrowingRGB(XYZRGBACloud_ptr input_cloud,XYZRGBCloud_ptr output_cloud, NormalCloud_ptr normals,SearchXYZRGBA_ptr tree, int minClusterSize,int maxClusterSize, unsigned int neighborNo,
                                    float smoothness, float curvature, float distance,
                                     float color, float regionColor,std::vector<Object <PXYZRGB> > &objects);
        static void ransac(XYZRGBACloud_ptr input_cloud, float distanceThreshold,pcl::SacModel, Object<PXYZRGBA> &object);

        static void ransac(XYZRGBACloud_ptr input_cloud, float distanceThreshold,pcl::SacModel, float maxRadius, NormalCloud_ptr normals, Object<PXYZRGBA> &object);

        static void euclidean(XYZRGBACloud_ptr input_cloud,SearchXYZRGBA_ptr tree, int minClusterSize,int maxClusterSize,float clusterTolerance,std::vector< Object<PXYZRGBA> > &objects);

        static void minCut(XYZCloud_ptr input_cloud,XYZRGBCloud_ptr output_cloud ,Coord3D objCenter, float radius,float sigma,int neighborNo,float sourceWeight,std::vector< Object<PXYZRGB> > &objects);
};

#endif // SEGMENTATIONALGORITHMS_H
