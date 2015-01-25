#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
int main()
{
    double joy_x;            // will hold the X value of the analog stick
    double joy_y;            // will hold the Y value of the analog stick
    int threshold = 4;   // helps to eliminate 'noise' from a joystick that is not perfectly at (0,0)
    int leftMotor;
    int rightMotor;
    cin>>joy_x>>joy_y;
    leftMotor = joy_x;   // Initializes joy_x to joystick.joy1_x1
    rightMotor = joy_y;   // Initializes joy_y to joystick.joy1_y1

    // Turning in place: (abs(X) is above the threshold, abs(Y) is below the threshold)
    if((abs(joy_x) > threshold) && (abs(joy_y) < threshold))
    {
        leftMotor  = joy_x;
        rightMotor = (-1 * joy_x);
    }
    // Moving straight and moving back (abs(X) is below the threshold, abs(Y) is above the threshold)
    else if ((abs(joy_x) < threshold) && (abs(joy_y) > threshold))
    {
        leftMotor = joy_y;
        rightMotor = joy_y;
    }
    // Swing turns: (both abs(X) and abs(Y) are above the threshold, and Y is POSITIVE)
    else if((abs(joy_x) > threshold) && (abs(joy_y) > threshold) && (joy_y > 0))
    {
        leftMotor  = (joy_y + joy_x)/2;
        rightMotor = (joy_y - joy_x)/2;
    }
    // Swing turns: (both abs(X) and abs(Y) are above the threshold, and Y is NEGATIVE)
    else if((abs(joy_x) > threshold) && (abs(joy_y) > threshold) && (joy_y < 0))
    {
        leftMotor  = (joy_y - joy_x)/2;
        rightMotor = (joy_y + joy_x)/2;
    }
    // Standing still: (both abs(X) and abs(Y) are below the threshold)
    else
    {
        leftMotor  = 0;
        rightMotor = 0;
    }
    cout<<"Left Motor = "<<leftMotor<<" Right Motor = "<<rightMotor<<endl;
}
