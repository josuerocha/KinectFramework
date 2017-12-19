#include "Registering.h"

using namespace std;
using namespace pcl;

template <class T>
Registering<T>::Registering(){
    //ctor
}

template <class T>
Registering<T>::~Registering(){
    //dtor
}

template <class T>
bool Registering<T>::registerICP(class PointCloud<T>::Ptr source_cloud,class PointCloud<T>::Ptr target_cloud,class PointCloud<T>::Ptr final_cloud,int iterations,double distanceThresh){

    //TransformationEstimation estimation;

	this->icp.setInputSource(source_cloud);
	this->icp.setInputTarget(target_cloud);
    this->icp.setMaximumIterations (iterations);
    //this->icp.setTransformationEstimation();
	//this->icp.setMaxCorrespondenceDistance(distanceThresh);
	this->icp.align(*final_cloud);
	if (!icp.hasConverged()){
        cout<<"*WARNING* ICP Registration has not converged"<<endl;
	}
    return icp.hasConverged();
}

template <class T>
bool Registering<T>::registerICPNonLinear(class PointCloud<T>::Ptr source_cloud,class PointCloud<T>::Ptr target_cloud,class PointCloud<T>::Ptr final_cloud,int iterations,double distanceThresh){

    //TransformationEstimation estimation;
    this->icpNl.setTransformationEpsilon (1e-6);
	this->icpNl.setInputSource(source_cloud);
	this->icpNl.setInputTarget(target_cloud);
    this->icpNl.setMaximumIterations (iterations);
    //this->icp.setTransformationEstimation();
	//this->icpNl.setMaxCorrespondenceDistance(distanceThresh);
	this->icpNl.align(*final_cloud);
	if (!icpNl.hasConverged()){
        cout<<"*WARNING* ICP Registration has not converged"<<endl;
	}
    return icpNl.hasConverged();
}

template <class T>
void Registering<T>::registerFBR(class PointCloud<T>::Ptr source_cloud,class PointCloud<T>::Ptr target_cloud,class PointCloud<T>::Ptr final_cloud){



}
