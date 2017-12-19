#include "Recognition.h"



using namespace std;
using namespace pcl;

template <class T>
Recognition<T>::Recognition(){

}

template <class T>
Recognition<T>::~Recognition(){

}

template <class T>
double Recognition<T>::computeCloudResolution (const class PointCloud<T>::ConstPtr &cloud){
  double resolution = 0.0;
  int n_points = 0;
  int nres;
  std::vector<int> indices (2);
  std::vector<float> sqr_distances (2);
  pcl::search::KdTree<T> tree;
  tree.setInputCloud (cloud);

  for (size_t i = 0; i < cloud->size (); ++i){

    if (! pcl_isfinite ((*cloud)[i].x)){
      continue;
    }
    //Considering the second neighbor since the first is the point itself.
    nres = tree.nearestKSearch (i, 2, indices, sqr_distances);
    if (nres == 2){
      resolution += sqrt (sqr_distances[1]);
      ++n_points;
    }
  }
  if (n_points != 0){
    resolution /= n_points;
  }
  return resolution;
}

template <class T>
void Recognition<T>::run (class PointCloud<T>::Ptr model,class PointCloud<T>::Ptr scene,class PointCloud<T>::Ptr output){
    cout<<"STARTED FINISHED"<<endl;

    class pcl::PointCloud<T>::Ptr model_keypoints (new pcl::PointCloud<T> ());
    class pcl::PointCloud<T>::Ptr scene_keypoints (new pcl::PointCloud<T> ());
    pcl::PointCloud<Normal>::Ptr model_normals (new pcl::PointCloud<Normal> ());
    pcl::PointCloud<Normal>::Ptr scene_normals (new pcl::PointCloud<Normal> ());
    pcl::PointCloud<SHOT352>::Ptr model_descriptors (new pcl::PointCloud<SHOT352> ());
    pcl::PointCloud<SHOT352>::Ptr scene_descriptors (new pcl::PointCloud<SHOT352> ());

    //Algorithm params
    bool use_cloud_resolution_ (false);
    bool use_hough_ (true);
    float model_ss_ (0.03f);
    float scene_ss_ (0.03f);
    float rf_rad_ (0.03f);
    float descr_rad_ (0.03f);
    float cg_size_ (0.03f);
    float cg_thresh_ (1.0f);

  //
  //  Set up resolution invariance
  //
  if (use_cloud_resolution_)
  {
    float resolution = static_cast<float> (computeCloudResolution (model));
    if (resolution != 0.0f){
      model_ss_   *= resolution;
      scene_ss_   *= resolution;
      rf_rad_     *= resolution;
      descr_rad_  *= resolution;
      cg_size_    *= resolution;
    }

    std::cout << "Model resolution:       " << resolution << std::endl;
    std::cout << "Model sampling size:    " << model_ss_ << std::endl;
    std::cout << "Scene sampling size:    " << scene_ss_ << std::endl;
    std::cout << "LRF support radius:     " << rf_rad_ << std::endl;
    std::cout << "SHOT descriptor radius: " << descr_rad_ << std::endl;
    std::cout << "Clustering bin size:    " << cg_size_ << std::endl << std::endl;
  }

  //
  //  Compute Normals
  //
  pcl::NormalEstimationOMP<T, Normal> norm_est;
  norm_est.setKSearch (10);
  norm_est.setInputCloud (model);
  norm_est.compute (*model_normals);

  norm_est.setInputCloud (scene);
  norm_est.compute (*scene_normals);

  //
  //  Downsample Clouds to Extract keypoints
  //

  pcl::UniformSampling<T> uniform_sampling;
  uniform_sampling.setInputCloud (model);
  uniform_sampling.setRadiusSearch (model_ss_);
  uniform_sampling.filter (*model_keypoints);
  std::cout << "Model total points: " << model->size () << "; Selected Keypoints: " << model_keypoints->size () << std::endl;

  uniform_sampling.setInputCloud (scene);
  uniform_sampling.setRadiusSearch (scene_ss_);
  uniform_sampling.filter (*scene_keypoints);
  std::cout << "Scene total points: " << scene->size () << "; Selected Keypoints: " << scene_keypoints->size () << std::endl;


  //
  //  Compute Descriptor for keypoints
  //
  pcl::SHOTEstimationOMP<T, Normal, SHOT352> descr_est;
  descr_est.setRadiusSearch (descr_rad_);

  descr_est.setInputCloud (model_keypoints);
  descr_est.setInputNormals (model_normals);
  descr_est.setSearchSurface (model);
  descr_est.compute (*model_descriptors);

  descr_est.setInputCloud (scene_keypoints);
  descr_est.setInputNormals (scene_normals);
  descr_est.setSearchSurface (scene);
  descr_est.compute (*scene_descriptors);

  //
  //  Find Model-Scene Correspondences with KdTree
  //
  pcl::CorrespondencesPtr model_scene_corrs (new pcl::Correspondences ());

  pcl::KdTreeFLANN<SHOT352> match_search;
  match_search.setInputCloud (model_descriptors);

  //  For each scene keypoint descriptor, find nearest neighbor into the model keypoints descriptor cloud and add it to the correspondences vector.
  for (size_t i = 0; i < scene_descriptors->size (); ++i)
  {
    std::vector<int> neigh_indices (1);
    std::vector<float> neigh_sqr_dists (1);
    if (!pcl_isfinite (scene_descriptors->at (i).descriptor[0])) //skipping NaNs
    {
      continue;
    }
    int found_neighs = match_search.nearestKSearch (scene_descriptors->at (i), 1, neigh_indices, neigh_sqr_dists);
    if(found_neighs == 1 && neigh_sqr_dists[0] < 0.25f) //  add match only if the squared descriptor distance is less than 0.25 (SHOT descriptor distances are between 0 and 1 by design)
    {
      pcl::Correspondence corr (neigh_indices[0], static_cast<int> (i), neigh_sqr_dists[0]);
      model_scene_corrs->push_back (corr);
    }
  }
  cout << "Correspondences found: " << model_scene_corrs->size () << std::endl;

  vector<Eigen::Matrix4f, Eigen::aligned_allocator<Eigen::Matrix4f> > rototranslations;
  vector<pcl::Correspondences> clustered_corrs;

  //  Using Hough3D
  if (use_hough_)
  {
    //
    //  Compute (Keypoints) Reference Frames only for Hough
    //
    pcl::PointCloud<ReferenceFrame>::Ptr model_rf (new pcl::PointCloud<ReferenceFrame> ());
    pcl::PointCloud<ReferenceFrame>::Ptr scene_rf (new pcl::PointCloud<ReferenceFrame> ());

    pcl::BOARDLocalReferenceFrameEstimation<T, Normal, ReferenceFrame> rf_est;
    rf_est.setFindHoles (true);
    rf_est.setRadiusSearch (rf_rad_);

    rf_est.setInputCloud (model_keypoints);
    rf_est.setInputNormals (model_normals);
    rf_est.setSearchSurface (model);
    rf_est.compute (*model_rf);

    rf_est.setInputCloud (scene_keypoints);
    rf_est.setInputNormals (scene_normals);
    rf_est.setSearchSurface (scene);
    rf_est.compute (*scene_rf);

    //  Clustering
    pcl::Hough3DGrouping<T, T, ReferenceFrame, ReferenceFrame> clusterer;
    clusterer.setHoughBinSize (cg_size_);
    clusterer.setHoughThreshold (cg_thresh_);
    clusterer.setUseInterpolation (true);
    clusterer.setUseDistanceWeight (false);

    clusterer.setInputCloud (model_keypoints);
    clusterer.setInputRf (model_rf);
    clusterer.setSceneCloud (scene_keypoints);
    clusterer.setSceneRf (scene_rf);
    clusterer.setModelSceneCorrespondences (model_scene_corrs);

    //clusterer.cluster (clustered_corrs);
    clusterer.recognize (rototranslations, clustered_corrs);
  }
  else // Using GeometricConsistency
  {
    pcl::GeometricConsistencyGrouping<T, T> gc_clusterer;
    gc_clusterer.setGCSize (cg_size_);
    gc_clusterer.setGCThreshold (cg_thresh_);

    gc_clusterer.setInputCloud (model_keypoints);
    gc_clusterer.setSceneCloud (scene_keypoints);
    gc_clusterer.setModelSceneCorrespondences (model_scene_corrs);

    //gc_clusterer.cluster (clustered_corrs);
    gc_clusterer.recognize (rototranslations, clustered_corrs);
  }

  //
  //  Output results
  //
  std::cout << "Model instances found: " << rototranslations.size () << std::endl;
  for (size_t i = 0; i < rototranslations.size (); ++i)
  {
    std::cout << "\n    Instance " << i + 1 << ":" << std::endl;
    std::cout << "        Correspondences belonging to this instance: " << clustered_corrs[i].size () << std::endl;

    // Print the rotation matrix and translation vector
    Eigen::Matrix3f rotation = rototranslations[i].block<3,3>(0, 0);
    Eigen::Vector3f translation = rototranslations[i].block<3,1>(0, 3);

    printf ("\n");
    printf ("            | %6.3f %6.3f %6.3f | \n", rotation (0,0), rotation (0,1), rotation (0,2));
    printf ("        R = | %6.3f %6.3f %6.3f | \n", rotation (1,0), rotation (1,1), rotation (1,2));
    printf ("            | %6.3f %6.3f %6.3f | \n", rotation (2,0), rotation (2,1), rotation (2,2));
    printf ("\n");
    printf ("        t = < %0.3f, %0.3f, %0.3f >\n", translation (0), translation (1), translation (2));
  }

  copyPointCloud(*scene,*output);

  for (size_t i = 0; i < rototranslations.size (); ++i)
  {
    class PointCloud<T>::Ptr rotated_model (new PointCloud<T> ());
    transformPointCloud (*model, *rotated_model, rototranslations[i]);

    for(unsigned int i=0; i != rotated_model->points.size(); i++){
        rotated_model->points[i].r = 255;
        rotated_model->points[i].g = 0;
        rotated_model->points[i].b = 0;
    }

    *output = *output + *rotated_model;
  }

}
