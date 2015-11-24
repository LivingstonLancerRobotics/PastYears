#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  HTServo,  none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     lift,          tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C1_2,     hang,          tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C2_1,     rightFront,    tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C2_2,     rightBack,     tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C3_1,     hang2,         tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C3_2,     flag,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     leftBack,      tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C4_2,     leftFront,     tmotorTetrix, PIDControl)
#pragma config(Servo,  srvo_S2_C1_1,    autonomous,           tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_3,    hangrelease,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    collector,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_5,    tilt,                 tServoStandard)
#pragma config(Servo,  srvo_S2_C1_6,    clamp,                tServoStandard)
#pragma config(Servo,  srvo_S2_C2_1,    open,                 tServoStandard)
#pragma config(Servo,  srvo_S2_C2_2,    servo8,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_6,    servo12,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment\Sample Programs\NXT\3rd Party Sensor Drivers\drivers\hitechnic-sensormux.h"

#define JOYSTICK_UPDATE_TIME 10



const int HIGH_PASS = 15; //Take out possible electric noise below <HIGH_PASS>.
const int FLAG = 100; //Power for flag
const int SLOW = 20; //slow drive for dpad

const int cJoyDead = 8;         // joystick range in which movement is considered accidental
const int cMotorMin = 15;       // minimum drive motor power
const float cDriveExp = 1.4;    // exponent for drive power calculations  (1 = linear, 2 = squared)

void initializeRobot()
{
	// Place code here to initialize servos to starting positions.
	// Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

	servo[autonomous]=100;
	servo[hangrelease]=0;
	servo[clamp]=120;
	servo[tilt]=0;
	servo[collector]=231;
	servo[open]=255;
	return;
}
/*

int expDrive (int joyVal, float driveExp, int joyDead, int motorMin)
{
int joyMax = 128 - joyDead;
int joySign = sgn(joyVal);
int joyLive = abs(joyVal) - joyDead;
return joySign * (motorMin + ((100 - motorMin) * pow(joyLive, driveExp) / pow(joyMax, driveExp)));
}*/

task main()
{
	initializeRobot();

	waitForStart();   // wait for start of tele-op phase
	getJoystickSettings(joystick);

	while (true)
	{

		//int powerL = expDrive(joystick.joy1_y1, cDriveExp, cJoyDead, cMotorMin);
		//int powerR = expDrive(joystick.joy1_y2, cDriveExp, cJoyDead, cMotorMin);

		int powerL = joystick.joy1_y1;
		int powerR = joystick.joy1_y2;

		if(abs(powerL) > HIGH_PASS || abs(powerR) > HIGH_PASS)
		{
			motor[leftBack] = powerL;
			motor[leftFront] = powerL;

			motor[rightBack] = -powerR;
			motor[rightFront] = -powerR;
		}
		else if(joystick.joy1_TopHat==0)
		{
			motor[leftBack] = SLOW;
			motor[leftFront] = SLOW;

			motor[rightBack] = -SLOW;
			motor[rightFront] = -SLOW;
		}
		else if(joystick.joy1_TopHat==4)
		{
			motor[leftBack] = -SLOW;
			motor[leftFront] = -SLOW;

			motor[rightBack] = SLOW;
			motor[rightFront] = SLOW;
		}
		else if(joystick.joy1_TopHat==6)
		{
			motor[leftBack] = -SLOW;
			motor[leftFront] = -SLOW;

			motor[rightBack] = -SLOW;
			motor[rightFront] = -SLOW;
		}
		else if(joystick.joy1_TopHat==2)
		{
			motor[leftBack] = SLOW;
			motor[leftFront] = SLOW;

			motor[rightBack] = SLOW;
			motor[rightFront] = SLOW;
		}
		else
		{
			motor[leftBack] = 0;
			motor[leftFront] = 0;

			motor[rightBack] = 0;
			motor[rightFront] = 0;
		}


		if(abs(joystick.joy2_y2)>15)
			motor[lift]=-joystick.joy2_y2;
		else
			motor[lift]=0;

		if(joy2Btn(4))
			servo[autonomous]=253;
		//autonomous arm inside bot
//		if(joy1Btn(2))
	//		servo[autonomous]=100;
		//autonomous arm upright
		if(joy2Btn(3))
			servo[autonomous]=0;
	//autonomous arm completely flipped over

		if(joy1Btn(4))
		{
			motor[hang]=100; //expands hang motor
			motor[hang2]=-100;
		}
		else if(joy1Btn(3))
		{
			motor[hang]=-100; //contracts hang motor
			motor[hang2]=100;
		}
		else
		{
			motor[hang]=0;
			motor[hang2]=0;
		}


		if(joy1Btn(2))
			servo[hangrelease]=255;//hook on to bar
		if(joy1Btn(1))
			servo[hangrelease]=210;//rubberband release
		if(joy1Btn(10))
			servo[hangrelease]=0; //hook flips all the way back

		if(joystick.joy2_TopHat==0)
		{
			motor[flag]=FLAG;
		}
		else if(joystick.joy2_TopHat==4)
		{
			motor[flag]=-FLAG;
		}
		else
		{
			motor[flag]=0;
		}

		if(joystick.joy2_TopHat==6)
			servo[open]=255;
		//close
		if(joystick.joy2_TopHat==2)
			servo[open]=145;
		//open


		if(joy2Btn(8))
			servo[collector]=10;
		//collector down
		if(joy2Btn(6))
		{
			servo[collector]=231;
			//collector up
			servo[clamp]=120;
			//close
			servo[tilt]=0;
			//collect
		}



		if(joy2Btn(1) || joy1Btn(8))
			servo[clamp]=120;
		//close
		if(joy2Btn(2) || joy1Btn(6))
			servo[clamp]=90;
		//open

		if(joy2Btn(7))
			servo[tilt]=0;
		//collect
		if(joy2Btn(5))
			servo[tilt]=90;
		//dump
	}
}