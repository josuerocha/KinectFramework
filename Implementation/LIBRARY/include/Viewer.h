#ifndef VIEWER_H
#define VIEWER_H

///STANDARD INCLUDES
#include <string>
#include <boost/thread.hpp>

///PCL INCLUDES
#include <pcl/visualization/pcl_visualizer.h>

///CUSTOM INCLUDES
#include "CustomStructures.h"

template <class T>
class Viewer
{

    private:

        /*
        boost::thread    m_thread;
        bool flag_updating;
        bool flag_spinning;
        bool flag_fullScreen;
*/

    protected:

    public:

        boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer; ///PCLVIsualizer

        Viewer(std::string windowName);
        Viewer();
        ~Viewer();

        //CHANGE VIEWER TEXT
        void setViewerText(std::string text,Coord2D coord,float textSize, Color color, std::string id);
        void removeShape(std::string id);
        void addArrow(Coord3D coord1,Coord3D coord2,Color color);

        //SHOWING
        void showExternalCloud(class pcl::PointCloud<T>::Ptr cloud);
        void showExternalCloud(class pcl::PointCloud<T>::Ptr cloud,NormalCloud_ptr normalCloud);
        void showExternalMesh(pcl::PolygonMesh::Ptr mesh);
        void addCloud(class pcl::PointCloud<T>::Ptr cloud);
        void addCloud(class pcl::PointCloud<T>::Ptr cloud,NormalCloud_ptr normalCloud);
        void addMesh(pcl::PolygonMesh::Ptr mesh);

        void registerKeyboardCallback(boost::function<void (const pcl::visualization::KeyboardEvent&)> cb);

        void Spin();
};

template class Viewer <pcl::PointXYZ>;
template class Viewer <pcl::PointXYZRGB>;
template class Viewer <pcl::PointXYZRGBA>;
//template class Viewer <pcl::PointNormal>;

#endif // VIEWER_H
