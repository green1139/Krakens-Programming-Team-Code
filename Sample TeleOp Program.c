#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    ,                     tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    ,                     tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of tele-op mode, you may want to perform some initialization on your robot
// and the variables within your program.
//
// In most cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  servo[servo1] = 255;  // Gripper opened
  servo[servo2] = 127;  // Arm raised

  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the tele-op robot operation. Customize as appropriate for
// your specific robot.
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot. Most tele-op programs will follow the following
// logic:
//   1. Loop forever repeating the following actions:
//   2. Get the latest game controller / joystick settings that have been received from the PC.
//   3. Perform appropriate actions based on the joystick + buttons settings. This is usually a
//      simple action:
//      *  Joystick values are usually directly translated into power levels for a motor or
//         position of a servo.
//      *  Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//         position.
//   4. Repeat the loop.
//
// Your program needs to continuously loop because you need to continuously respond to changes in
// the game controller settings.
//
// At the end of the tele-op period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
  initializeRobot();

  int mThreshold = 15;      // Sets dead zones to avoid unnecessary movement
  int aThreshold = 30;
  int xVal, yVal;           //Stores left analog stick values
  float scaleFactor = 40.0 / 127;           //Sets max. average motor power and maps range of analog stick to desired range of power
  float aPosition = ServoValue[servo2];     //Stores the current position of the arm servo

  waitForStart();   // wait for start of tele-op phase

  while (true)
  {
    getJoystickSettings(joystick); // Retrieves data from the joystick

    xVal = joystick.joy1_x1;
    yVal = joystick.joy1_y1;

    //Checks if analog stick values are within the dead zone

    if (abs(xVal) < mThreshold)
    {
      xVal = 0;
    }
    if (abs(yVal) < mThreshold)
    {
      yVal = 0;
    }

    motor[motorD] = ((yVal) + (xVal)) * scaleFactor;      //Sets left motor power
    motor[motorE] = ((yVal) - (xVal)) * scaleFactor;      //Sets right motor power

    //Controls arm servo position

    if((joystick.joy1_y2 > aThreshold) && (aPosition > 0))
    {
      aPosition -= 0.15;
    }
    else if((joystick.joy1_y2 < (aThreshold * -1)) && (aPosition < 255))
    {
      aPosition += 0.15;
    }
    servo[servo2] = aPosition;      //Moves the arm servo

    if(joy1Btn(5))            // Open Gripper
    {
      servo[servo1] = 255;
    }
    else if(joy1Btn(6))       // Close Gripper
    {
      servo[servo1] = 0;
    }
  }
}
