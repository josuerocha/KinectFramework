#include "Reconstruction.h"

using namespace std;
using namespace pcl;

template <class T>
Reconstruction<T>::Reconstruction(){
    //ctor
}

template <class T>
Reconstruction<T>::~Reconstruction(){
    //dtor
}

template <class T>
void Reconstruction<T>::triangulate(PointCloud<PXYZ>::Ptr input_cloud,PolygonMesh::Ptr triangles){

    cout<<"TAMANHO2 " << input_cloud->size() << endl;
    PointCloud<Normal>::Ptr normals(new PointCloud<Normal>);
    Calculations<PXYZ>::estimateNormals(input_cloud,normals,50);



    PointCloud<PointNormal>::Ptr pointNormals (new PointCloud<PointNormal>);
    concatenateFields (*input_cloud, *normals, *pointNormals);

    search::KdTree<PointNormal>::Ptr tree (new search::KdTree<PointNormal>);
    tree->setInputCloud (pointNormals);

    // Initialize objects
    pcl::GreedyProjectionTriangulation<PointNormal> gp;


    // Set the maximum distance between connected points (maximum edge length)
    gp.setSearchRadius (0.06);

    // Set typical values for the parameters
    gp.setMu (2.5);
    gp.setMaximumNearestNeighbors (100);
    gp.setMaximumSurfaceAngle(M_PI/4); // 45 degrees
    gp.setMinimumAngle(M_PI/18); // 10 degrees
    gp.setMaximumAngle(2*M_PI/3); // 120 degrees
    gp.setNormalConsistency(false);

    // Get result
    gp.setInputCloud (pointNormals);
    gp.setSearchMethod (tree);
    gp.reconstruct (*triangles);

}

template <class T>
void Reconstruction<T>::movingLeastSquaresUpsampling(class PointCloud<T>::Ptr input_cloud,class PointCloud<T>::Ptr output_cloud,float searchRadius,float upSamplingRadius, float upSamplingStep){

 // Filtering object.
	MovingLeastSquares<T, T> filter;
	filter.setInputCloud(input_cloud);
	// Object for searching.
	class search::KdTree<T>::Ptr kdtree;
	filter.setSearchMethod(kdtree);
	// Use all neighbors in a radius of 3cm.
	filter.setSearchRadius(searchRadius);
	// Upsampling method. Other possibilites are DISTINCT_CLOUD, RANDOM_UNIFORM_DENSITY
	// and VOXEL_GRID_DILATION. NONE disables upsampling. Check the API for details.
	filter.setUpsamplingMethod(MovingLeastSquares<T, T>::SAMPLE_LOCAL_PLANE);
	// Radius around each point, where the local plane will be sampled.
	filter.setUpsamplingRadius(upSamplingRadius);
	// Sampling step size. Bigger values will yield less (if any) new points.
	filter.setUpsamplingStepSize(upSamplingStep);

	filter.process(*output_cloud);

}

template <class T>
void Reconstruction<T>::movingLeastSquaresSmoothing(class PointCloud<T>::Ptr input_cloud,class PointCloud<T>::Ptr output_cloud,float searchRadius){
    // Smoothing object (we choose what point types we want as input and output).
	MovingLeastSquares<T, PointNormal> filter;
	filter.setInputCloud(input_cloud);
	// Use all neighbors in a radius of 3cm.
	filter.setSearchRadius(searchRadius);
	// If true, the surface and normal are approximated using a polynomial estimation
	// (if false, only a tangent one).
	filter.setPolynomialFit(true);
	// We can tell the algorithm to also compute smoothed normals (optional).
	filter.setComputeNormals(false);
	// kd-tree object for performing searches.
	class search::KdTree<T>::Ptr kdtree;
	filter.setSearchMethod(kdtree);

//	filter.process(*output_cloud);


}


