#ifndef KINECTCONTROL_H
#define KINECTCONTROL_H

/** CLASS TO CONTROL KINECT SERVOMOTORS **/

//STANDARD INCLUDES
#include <vector>

//BOOST INCLUDES
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

//OpenNI INCLUDES
#include <XnUSB.h>
#include <XnTypes.h>

//CUSTOM INCLUDES

//CONTROL DATA STRUCTURES
enum LED_STATUS{LED_OFF	= 0, LED_GREEN = 1,LED_RED = 2,LED_YELLOW = 3, LED_BLINK_YELLOW	= 4, LED_BLINK_GREEN = 5, LED_BLINK_RED_YELLOW	= 6};
enum MOTOR_STATUS{MOTOR_STOPPED = 0x00, MOTOR_LIMIT = 0x01, MOTOR_MOVING = 0x04, MOTOR_UNKNOWN	= 0x08};

class KinectControl{

    private:
        bool				m_bOpened;
        XN_USB_DEV_HANDLE	m_xDevice;
        bool flag_Moving;

        std::vector <int> moveQueue;
        boost::thread t;

        XnStatus Create();
        void Release();

    public:

        //CTOR AND DTOR
        KinectControl();
        ~KinectControl();

        //SETTERS
        bool SetLED( LED_STATUS eStatus );
        bool Move( int angle );

        //* GETTERS
        int GetAngle() const;
        MOTOR_STATUS GetMotorStatus() const;
        XnVector3D GetAccelerometer() const; //* Get the vector from the accelerometer
        XnStatus GetInformation( int& rAngle, MOTOR_STATUS& rMotorStatus, XnVector3D& rVec ) const; //Get all information
};

#endif // KINECTMOTOR_H
