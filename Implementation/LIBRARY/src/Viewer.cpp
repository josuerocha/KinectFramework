#include "Viewer.h"

using namespace std;
using namespace pcl;

template <class T>
Viewer<T>::Viewer(){
    viewer.reset(new pcl::visualization::PCLVisualizer ("Default", false));
	viewer->addCoordinateSystem(1);
    viewer->createInteractor();
	//viewer->registerKeyboardCallback(&Viewer::keyboardCallback, *this);
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5,"cloud");
	viewer->initCameraParameters();
    viewer->setCameraPosition	(0,0,-2,0,-1,0,0);
/*
    flag_fullScreen = false;
    flag_updating = false;
    flag_spinning = false;
*/
     //m_thread = boost::thread(&Viewer::keepSpinning, this);
}

template <class T>
Viewer<T>::Viewer(string name){
    viewer.reset(new pcl::visualization::PCLVisualizer (name, false));
	viewer->addCoordinateSystem(1);
    viewer->createInteractor();

	//viewer->registerKeyboardCallback(&Viewer::keyboardCallback, *this);
/*
    flag_fullScreen = false;
    flag_updating = false;
    flag_spinning = false;
*/
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5,"cloud");
	viewer->initCameraParameters();

    viewer->setCameraPosition	(0,0,-2,0,-1,0,0);

    //m_thread = boost::thread(&Viewer::keepSpinning, this);
}

template <class T>
Viewer<T>::~Viewer(){
    //dtor
}

template <class T>
void Viewer<T>::addArrow(Coord3D coord1,Coord3D coord2,Color color){
    T point1 , point2;

    point1.x = coord1.x;
    point1.y = coord1.y;
    point1.z = coord1.z;

    point2.x = coord2.x;
    point2.y = coord2.y;
    point2.z = coord2.z;

    removeShape("arrow");
    viewer->addArrow (point1,point2,color.r, color.g, color.b,true);

}

template <class T>
void Viewer<T>::addCloud(class PointCloud<T>::Ptr cloud){
    viewer->addPointCloud(cloud,"cloud");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5,"cloud");
}

template <class T>
void Viewer<T>::addCloud(class PointCloud<T>::Ptr cloud,NormalCloud_ptr normalCloud){
    addCloud(cloud);
    viewer->addPointCloudNormals<T, Normal> (cloud, normalCloud, 1, 0.05, "normals");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5,"normals");
}

template <class T>
void Viewer<T>::addMesh(PolygonMesh::Ptr mesh){
    viewer->addPolygonMesh(*mesh,"mesh",0);
}

template <class T>
void Viewer<T>::Spin(){
    if(viewer->wasStopped()){
        exit(1);
    }
    viewer->spinOnce (50);
}

template <class T>
void Viewer<T>::showExternalCloud(class PointCloud<T>::Ptr cloud){

    viewer->updatePointCloud(cloud,"cloud");
    Spin();
}


template <class T>
void Viewer<T>::showExternalCloud(class PointCloud<T>::Ptr cloud,NormalCloud_ptr normalCloud){
    removeShape("normals");
    removeShape("cloud");
    addCloud(cloud,normalCloud);
    Spin();
}

template <class T>
void Viewer<T>::showExternalMesh(PolygonMesh::Ptr mesh){
    removeShape("mesh");
    viewer->addPolygonMesh(*mesh,"mesh",0);
}

template <class T>
void Viewer<T>::setViewerText(string text,Coord2D coord, float textSize , Color color, string id){
    viewer->addText(text, coord.x, coord.y, textSize, color.r,color.g,color.b, id);
}

template <class T>
void Viewer<T>::removeShape(string id){
    viewer->removeShape (id);
}
/*
template <class T>
void Viewer<T>::keepSpinning(){
    while(true){
        if(!flag_updating){
            flag_spinning = true;
            Spin();
            flag_spinning = false;
        }
        sleep(0.25);
    }
}


/*
// For detecting when SPACE is pressed.
template <class T>
void Viewer<T>::keyboardCallback(const visualization::KeyboardEvent& event, void* nothing){

    if(event.keyDown()){
        if(event.getKeySym() == "esc"){
            exit(0);
        }
        else if(event.getKeySym() == "f"){
            if(flag_fullScreen){
                viewer->setFullScreen(false);
                flag_fullScreen = false;
            }
            else{
                viewer->setFullScreen(true);
                flag_fullScreen = true;
            }

        }
    }
}
*/

