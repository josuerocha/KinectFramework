#include "Filtering.h"
using namespace std;
using namespace pcl;

template <class T>
Filtering<T>::Filtering(){
    //ctor
}

template <class T>
Filtering<T>::~Filtering(){
    //dtor
}

template <class T>
void Filtering<T>::filterArea(class PointCloud<T>::Ptr input,class PointCloud<T>::Ptr output ,float minDistance, float maxDistance, string axis){
    //cout<<"Executing index filter"<<endl;
    //IndicesPtr indices (new vector <int>);
    PassThrough<T> pass;
    pass.setInputCloud (input);
    pass.setFilterFieldName (axis); //dimension to be filtered
    pass.setFilterLimits (minDistance , maxDistance); //distance to be considered on image filtering
    pass.filter (*output);
}

template <class T>
void Filtering<T>::voxelize(class PointCloud<T>::Ptr input, class PointCloud<T>::Ptr output, Dimension3D leafSize){
    //cout<<"Executing voxelization grid filter (Downsampling)" << endl;
    VoxelGrid<T> grid;
    grid.setInputCloud (input);
    grid.setLeafSize(leafSize.width,leafSize.height, leafSize.depth); //Registering leaf dimensions for eliminating points
    grid.filter(*output);
}

template <class T>
void Filtering<T>::uniformSampling(class PointCloud<T>::Ptr input, class PointCloud<T>::Ptr output, float radius){
    UniformSampling<T> uniform_sampling;
    uniform_sampling.setInputCloud (input);
    uniform_sampling.setRadiusSearch (radius);
    uniform_sampling.filter (*output);
}

template <class T>
void Filtering<T>::statisticalOutlierFilter(class PointCloud<T>::Ptr input, class PointCloud<T>::Ptr output,int mean, float stdDev){
    pcl::StatisticalOutlierRemoval<T> sor;
    sor.setInputCloud (input);
    sor.setMeanK(mean);
    sor.setStddevMulThresh (stdDev);
    sor.filter (*output);
}

template <class T>
void Filtering<T>::radiusOutlierFilter(class PointCloud<T>::Ptr input, class PointCloud<T>::Ptr output, float radius, unsigned int minNeighbors){
    RadiusOutlierRemoval<T> filter;// build the filter
    filter.setInputCloud(input);
    filter.setRadiusSearch(radius);
    filter.setMinNeighborsInRadius (minNeighbors);
    filter.filter (*output);
}

template <class T>
void Filtering<T>::parametricProjection(class PointCloud<T>::Ptr input, class PointCloud<T>::Ptr output, SacModel model, vector<float> &coefficientsVect){
    ModelCoefficients::Ptr coefficients (new ModelCoefficients ());
    coefficients->values.resize (coefficientsVect.size());
    for(unsigned int i=0; i<coefficientsVect.size() ; i++){
        coefficients->values[i] = coefficientsVect[i];
    }

    ProjectInliers<T> proj;
    proj.setModelType (model);
    proj.setInputCloud (input);
    proj.setModelCoefficients (coefficients);
    proj.filter (*output);
}

