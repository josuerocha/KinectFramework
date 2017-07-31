#include "Object.h"

using namespace std;
using namespace pcl;

template <class T>
Object<T>::Object(){
    //ctor
}

template <class T>
Object<T>::~Object(){
    //dtor
}

template <class T>
void Object<T>::highLightClusterHeight(class PointCloud<T>::Ptr input_cloud){
        Color color;

        vector<PointIndices>::iterator c;
        vector<int>::iterator p;

        int startingPosition = *pointIndices.indices.begin();

        this->highestPoint = Coord3D(input_cloud->points[startingPosition].x,
                input_cloud->points[startingPosition].y,
                input_cloud->points[startingPosition].z);

        this->lowestPoint =  Coord3D(input_cloud->points[startingPosition].x,
                input_cloud->points[startingPosition].y,
                input_cloud->points[startingPosition].z);

        this->lowestIndex = *pointIndices.indices.begin();
        this->highestIndex = *pointIndices.indices.begin();



        for (p = pointIndices.indices.begin(); p != pointIndices.indices.end (); p++){
            int index;
            index = *p;

            if(input_cloud->points[index].y < this->highestPoint.y){
                this->highestPoint = Coord3D(input_cloud->points[index].x,input_cloud->points[index].y,input_cloud->points[index].z);
                this->highestIndex = index;
            }
            else if(input_cloud->points[index].y > this->lowestPoint.y){
                this->lowestPoint = Coord3D(input_cloud->points[index].x,input_cloud->points[index].y,input_cloud->points[index].z);
                this->lowestIndex = index;
            }

        }

        this->height = abs( this->lowestPoint.y - this->highestPoint.y);
        cout<< endl << "HIGHEST POINT " << this->highestPoint.y << " m" <<endl;
        cout<< "LOWEST POINT " << this->lowestPoint.y << " m" << endl;
        cout<<"HEIGHT " << this->height << " m" << endl << endl;

        if(height > 0.25){
            color = Color(255,255,255,255);
        }
        else if(height > 0.16){
            color = Color(0,255,0,255);
        }
        else if(height >= 0){
            color = Color(0,0,255,255);
        }

        paintCluster(input_cloud,color);

        input_cloud->points[highestIndex].r = 255;
        input_cloud->points[highestIndex].g = 0;
        input_cloud->points[highestIndex].b = 0;

        input_cloud->points[lowestIndex].r = 204;
        input_cloud->points[lowestIndex].g = 150;
        input_cloud->points[lowestIndex].b = 198;

        if(pointIndices.indices.size() > 0){
            centroid = Calculations<T>::calculateObjCentroid(input_cloud,pointIndices);
        }
}

template <class T>
void Object<T>::paintCluster(class PointCloud<T>::Ptr input_cloud,Color color){

    for (vector<int>::iterator p = pointIndices.indices.begin(); p != pointIndices.indices.end(); p++){
            int index;
            index = *p;
            input_cloud->points[index].r = color.r;
            input_cloud->points[index].g = color.g;
            input_cloud->points[index].b = color.b;

    }
}

template <class T>
float Object<T>::getHeight(){
    return height;
}

template <class T>
Coord3D Object<T>::getHighestPoint(){
    return highestPoint;
}

template <class T>
Coord3D Object<T>::getLowestPoint(){
    return lowestPoint;
}

template <class T>
Coord3D Object<T>::getCentroid(){
    return centroid;
}

template <class T>
void Object<T>::extractIndices(bool negativeExtraction,class PointCloud<T>::Ptr input_cloud,class PointCloud<T>::Ptr output_cloud){
/** NEGATIVE EXTRACTION IF SET TRUE WILL EXTRACT POINTS NOT CONTAINED IN INDICES **/

    PointIndices::Ptr indices_ptr (new PointIndices(this->pointIndices));

	pcl::ExtractIndices < T > extract;
	extract.setInputCloud(input_cloud);
	extract.setIndices(indices_ptr);
	extract.setNegative(negativeExtraction);
	extract.filter(*output_cloud);
}
