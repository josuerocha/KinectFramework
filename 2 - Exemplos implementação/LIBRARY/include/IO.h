///*Framework de IO para operação com arquivos

#ifndef IO_H
#define IO_H

///STANDARD INCLUDES
#include <string>

///PCL INCLUDES
#include <pcl/io/openni_grabber.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/obj_io.h>
#include <pcl/console/parse.h>
#include <pcl/point_cloud.h>


///CUSTOM INCLUDES
#include "CustomStructures.h"

template <class T>
class IO
{
    private:
        ///GRABBER
        pcl::Grabber* openniGrabber;

        ///INTERNAL CLOUD
        class pcl::PointCloud<T>::Ptr cloud_ptr;

        ///CONTROL FLAGS
        bool flag_getFromSensor;
        bool flag_sequencialGrabbing;

        ///INITIALIZATION
        void initializeGrabber();

        ///GRABBER CALLBACK
        void grabberCallback(const class pcl::PointCloud<T>::ConstPtr &temp_cloud);


    public:
        IO();
        ~IO();

        ///READ AND WRITE PCD
        void readFromPCD(std::string filename,class pcl::PointCloud<T>::Ptr cloud);
        void writeToPCD(std::string filename, class pcl::PointCloud<T>::Ptr cloud);

        void writeToPLY(std::string filename,pcl::PolygonMesh::Ptr mesh);

        ///GRABBER CONFIG
        void setSensorSequencialGrabbing(bool sequencialGrabbing);

        ///SINGLE FRAME GRABBERS
        void grabSequencialFrameSensor();
        void grabSingleFrameSensor();

        ///GETTER
        class pcl::PointCloud<T>::Ptr getCloud_ptr();

};

template class IO <pcl::PointXYZ>;
template class IO <pcl::PointXYZRGB>;
template class IO <pcl::PointXYZRGBA>;

#endif // IO_H
