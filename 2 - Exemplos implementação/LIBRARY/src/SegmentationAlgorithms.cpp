#include "SegmentationAlgorithms.h"

using namespace std;
using namespace pcl;

SegmentationAlgorithms::SegmentationAlgorithms(){
    //ctor
}

SegmentationAlgorithms::~SegmentationAlgorithms(){
    //dtor
}

void SegmentationAlgorithms::regionGrowingXYZ(XYZCloud_ptr input_cloud,XYZRGBCloud_ptr output_cloud, NormalCloud_ptr normals,SearchXYZ_ptr tree, int minClusterSize,int maxClusterSize, unsigned int neighborNo, float smoothness, float curvature,
                                              vector< Object<PXYZRGB> > &objects){
    cout<<"Executing region growing segmentation"<<endl;

    pcl::RegionGrowing<pcl::PointXYZ, pcl::Normal> reg;

    reg.setMinClusterSize (minClusterSize);
    reg.setMaxClusterSize (maxClusterSize);
    reg.setSearchMethod (tree);
    reg.setNumberOfNeighbours (neighborNo);
    reg.setInputCloud (input_cloud);
    //reg.setIndices (indices);
    reg.setInputNormals (normals);
    reg.setSmoothnessThreshold (smoothness); //Threshold value for the angle between normals
    reg.setCurvatureThreshold (curvature); //

    std::vector <pcl::PointIndices> clusters;
    reg.extract(clusters);

    if(clusters.size() > 0){
        copyPointCloud(*reg.getColoredCloud(), *output_cloud);
        transformVectToObj(clusters,objects);
    }
    else{
        cout<<"No clusters detected"<<endl;
    }

}

void SegmentationAlgorithms::regionGrowingRGB(XYZRGBACloud_ptr input_cloud,XYZRGBCloud_ptr output_cloud, NormalCloud_ptr normals,SearchXYZRGBA_ptr tree,
                                              int minClusterSize,int maxClusterSize,unsigned int neighborNo, float smoothness, float curvature, float distance,
                                              float color, float regionColor,vector< Object<PXYZRGB> > &objects){
    vector<PointIndices> clusters;

    cout<<"Executing region growing segmentation"<<endl;

    pcl::RegionGrowingRGB<pcl::PointXYZRGBA, pcl::Normal> reg;

    reg.setMinClusterSize (minClusterSize);
    reg.setMaxClusterSize (maxClusterSize);
    reg.setSearchMethod(tree);
    reg.setInputCloud (input_cloud);
    reg.setDistanceThreshold(distance);
    reg.setPointColorThreshold (color);
    reg.setRegionColorThreshold (regionColor);

    //reg.setIndices (indices);
    reg.setInputNormals (normals);
    reg.setSmoothnessThreshold (smoothness); //Threshold value for the angle between normals
    reg.setCurvatureThreshold (curvature); //

    reg.setNormalTestFlag(true);
    reg.setCurvatureTestFlag(true);

    reg.extract(clusters);

    if(clusters.size() > 0){
        copyPointCloud(*reg.getColoredCloud(), *output_cloud);
        transformVectToObj(clusters,objects);
    }else{
        cout<<"No clusters detected"<<endl;
    }
}

void SegmentationAlgorithms::ransac(XYZRGBACloud_ptr input_cloud, float distanceThreshold,SacModel modelType,Object<PXYZRGBA> &object){
    PointIndices cluster;
    ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);
    SACSegmentation<PXYZRGBA> seg;
    seg.setOptimizeCoefficients (true);
    seg.setModelType(modelType);
    seg.setMethodType(SAC_RANSAC);
    seg.setDistanceThreshold (distanceThreshold);
    seg.setInputCloud(input_cloud);
    seg.segment (cluster, *coefficients);

    object.pointIndices = cluster;
}

void SegmentationAlgorithms::ransac(XYZRGBACloud_ptr input_cloud, float distanceThreshold,SacModel modelType,float maxRadius,NormalCloud_ptr normals,Object<PXYZRGBA> &object){
    PointIndices cluster;
    ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);
    pcl::SACSegmentationFromNormals<PXYZRGBA, pcl::Normal> seg;
    seg.setOptimizeCoefficients (true);
    seg.setModelType(modelType);
    seg.setMethodType(SAC_RANSAC);
    seg.setDistanceThreshold (distanceThreshold);
    seg.setInputCloud(input_cloud);
    seg.setRadiusLimits (0, maxRadius);
    seg.setInputNormals (normals);

    seg.segment (cluster, *coefficients);

    object.pointIndices = cluster;
}

void SegmentationAlgorithms::euclidean(XYZRGBACloud_ptr input_cloud,SearchXYZRGBA_ptr tree, int minClusterSize,int maxClusterSize,float clusterTolerance,vector< Object<PXYZRGBA> > &objects){
    PIndicesVector clusters;
    tree->setInputCloud (input_cloud);

    EuclideanClusterExtraction<pcl::PointXYZRGBA> ec;
    ec.setClusterTolerance (clusterTolerance);
    ec.setMinClusterSize (minClusterSize);
    ec.setMaxClusterSize (maxClusterSize);
    ec.setSearchMethod (tree);
    ec.setInputCloud (input_cloud);
    ec.extract (clusters);

    if(clusters.size() > 0){
        transformVectToObj(clusters,objects);
    }else{
        cout<<"No clusters detected"<<endl;
    }
}

void SegmentationAlgorithms::minCut(XYZCloud_ptr input_cloud,XYZRGBCloud_ptr output_cloud ,Coord3D objCenter, float radius,float sigma,int neighborNo,float sourceWeight,vector< Object<PXYZRGB> > &objects){
    MinCutSegmentation<PointXYZ> seg;
    seg.setInputCloud (input_cloud);

    PointCloud<PointXYZ>::Ptr foreground_points(new PointCloud<PointXYZ> ());
    pcl::PointXYZ point;
    point.x = objCenter.x;
    point.y = objCenter.y;
    point.z = objCenter.z;
    foreground_points->points.push_back(point);
    seg.setForegroundPoints (foreground_points);

    seg.setSigma (sigma);
    seg.setRadius (radius);
    seg.setNumberOfNeighbours (neighborNo);
    seg.setSourceWeight (sourceWeight);

    vector <pcl::PointIndices> clusters;
    seg.extract (clusters);

    if(clusters.size() > 0){

        cout<<"NUMBER OF CLUSTERS: " << clusters.size() << endl;
        copyPointCloud(*seg.getColoredCloud(), *output_cloud);
        transformVectToObj(clusters,objects);
    }
    else{

    }
}

void SegmentationAlgorithms::transformVectToObj(PIndicesVector &clusters, vector< Object<PXYZRGB> > &objects){
        objects.clear();

        Object<PXYZRGB> object;
        for(unsigned int i=0; i<clusters.size(); i++){
            object.pointIndices = clusters[i];
            objects.push_back(object);
        }
}

void SegmentationAlgorithms::transformVectToObj(PIndicesVector &clusters, vector< Object<PXYZRGBA> > &objects){
        objects.clear();

        Object<PXYZRGBA> object;
        for(unsigned int i=0; i<clusters.size(); i++){
            object.pointIndices = clusters[i];
            objects.push_back(object);
        }
}

