//STANDARD INCLUDES
#include <iostream>

//PCL INCLUDES

//CUSTOM INCLUDES
#include "KinectControl.h"

using namespace std;

int main (int argc, char** argv){

    KinectControl kinect;

    while(true){
        int time = 5;
        kinect.SetLED(LED_BLINK_GREEN);
        sleep(time);

        kinect.SetLED(LED_BLINK_RED_YELLOW);
        sleep(time);

        kinect.SetLED(LED_BLINK_YELLOW);
        sleep(time);

        kinect.SetLED(LED_GREEN);
        sleep(time);

        kinect.SetLED(LED_OFF);
        sleep(time);

        kinect.SetLED(LED_YELLOW);
        sleep(time);
    }
    return 0;
}



