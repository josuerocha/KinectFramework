//STANDARD INCLUDES
#include <iostream>

//PCL INCLUDES

//CUSTOM INCLUDES
#include "KinectControl.h"

using namespace std;

int main (int argc, char** argv){

    KinectControl kinect;

    while(true){
        kinect.Move(-31); //Moving to max position
        kinect.Move(31); //Moving to max position
    }
    return 0;
}



