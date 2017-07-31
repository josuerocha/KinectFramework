#include "KinectControl.h"

//STANDARD INCLUDES
#include <iostream>
using namespace std;
KinectControl::KinectControl(){
    m_bOpened = false;
    flag_Moving = false;
    if( Create() == XN_STATUS_OK ){
        cout<<"***Motor and LED connection succesfully created***" << endl;
    }
    else{
        cout<<"*** ERROR creating Motor and LED connection***" <<endl;
        exit(1);
    }
}

KinectControl::~KinectControl(){
    Release();
}


XnStatus KinectControl::Create(){
    const XnUSBConnectionString *paths;
    XnUInt32 count;
    XnStatus res;

    // Init OpenNI USB
    res = xnUSBInit();
    if( res != XN_STATUS_OK && res != 131142 /** USB already initialized **/ )
        return res;

    // list all "Kinect motor" USB devices
    res = xnUSBEnumerateDevices( 0x045E, 0x02B0, &paths, &count );
    if( res != XN_STATUS_OK )
        return res;

    const XnChar* pUSBtoUse = paths[0];

    if( count > 0 )
    {
        res = xnUSBOpenDeviceByPath( pUSBtoUse, &m_xDevice );
        if( res != XN_STATUS_OK )
            return res;

        // Init motors
        XnUChar buf;
        res = xnUSBSendControl( m_xDevice, (XnUSBControlType) 0xc0, 0x10, 0x00, 0x00, &buf, sizeof(buf), 0 );
        if( res != XN_STATUS_OK )
        {
            Release();
            return res;
        }

        res = xnUSBSendControl( m_xDevice, XN_USB_CONTROL_TYPE_VENDOR, 0x06, 0x01, 0x00, NULL, 0, 0);
        if( res != XN_STATUS_OK )
        {
            Release();
            return res;
        }

        m_bOpened = true;
        return XN_STATUS_OK;
    }

    return XN_STATUS_OS_FILE_OPEN_FAILED;
}

void KinectControl::Release(){
    if( m_bOpened )
    {
        SetLED( LED_BLINK_GREEN );
        xnUSBCloseDevice( m_xDevice );
        m_bOpened = false;
    }
}

bool KinectControl::SetLED( LED_STATUS eStatus ){
    if( !m_bOpened )
        return false;

    XnStatus res = xnUSBSendControl( m_xDevice, XN_USB_CONTROL_TYPE_VENDOR, 0x06, eStatus, 0x00, NULL, 0, 0 );
    if( res != XN_STATUS_OK ){
        return false;
    }

    return true;
}

bool KinectControl::Move(int angle){

        if (!(angle < -31 || angle > 31)){
                    if( !m_bOpened )
            return XN_STATUS_OS_EVENT_OPEN_FAILED;

            XnStatus res = xnUSBSendControl( m_xDevice, XN_USB_CONTROL_TYPE_VENDOR, 0x31, 2 * angle, 0x00, NULL, 0, 0 );

            if( res != XN_STATUS_OK ){
                return false;
            }

            sleep(0.3);
            while(GetMotorStatus() == MOTOR_MOVING){
                ///WAIT TILL MOVING FINISHES
            }

            return true;
        }
        else{
            return false;
        }
}

int KinectControl::GetAngle() const
{
    int iA;
    MOTOR_STATUS eStatus;
    XnVector3D vVec;
    GetInformation( iA, eStatus, vVec );
    return iA;
}

XnVector3D KinectControl::GetAccelerometer() const
{
    int iA;
    MOTOR_STATUS eStatus;
    XnVector3D vVec;
    GetInformation( iA, eStatus, vVec );
    return vVec;
}

/**
 * Get all information
 */
XnStatus KinectControl::GetInformation( int& rAngle, MOTOR_STATUS& rMotorStatus, XnVector3D& rVec ) const
{
    XnUChar aData[10];
    XnUInt32 uSize;
    XnStatus res = xnUSBReceiveControl( m_xDevice, XN_USB_CONTROL_TYPE_VENDOR, 0x32, 0x00, 0x00, aData, 10, &uSize, 0 );
    if( res == XN_STATUS_OK )
    {
        rAngle = aData[8];
        if( rAngle > 128 )
            rAngle = -0.5 * ( 255 - rAngle );
        else
            rAngle /= 2;

        if( aData[9] == 0x00 )
            rMotorStatus = MOTOR_STOPPED;
        else if( aData[9] == 0x01 )
            rMotorStatus = MOTOR_LIMIT;
        else if( aData[9] == 0x04 )
            rMotorStatus = MOTOR_MOVING;
        else
            rMotorStatus = MOTOR_UNKNOWN;

        rVec.X = (float)( ((XnUInt16)aData[2] << 8) | aData[3] );
        rVec.Y = (float)( ((XnUInt16)aData[4] << 8) | aData[5] );
        rVec.Z = (float)( ((XnUInt16)aData[6] << 8) | aData[7] );
    }
    return res;
}

MOTOR_STATUS KinectControl::GetMotorStatus() const{
    int iA;
    MOTOR_STATUS eStatus;
    XnVector3D vVec;
    GetInformation( iA, eStatus, vVec );
    return eStatus;
}
