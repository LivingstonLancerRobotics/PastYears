#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          flag1,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          flag2,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          flag3,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     lift,          tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C1_2,     hang,          tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C2_1,     rightFront,    tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C2_2,     rightBack,     tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C3_1,     hang2,         tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
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
#define JOYSTICK_UPDATE_TIME 10

const int HIGH_PASS = 15; //Take out possible electric noise below <HIGH_PASS>.
const int flag = 100; //Power for flag
const int SLOW=20; //slow drive for dpad

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

		if(joy1Btn(6))
			servo[open]=255;
		if(joy1Btn(8))
			servo[open]=145;

		if(joy1Btn(5))
		{
			motor[flag1]=100;
			motor[flag2]=100;
			motor[flag3]=100;
		}
		else if(joy1Btn(7))
		{
			motor[flag1]=-100;
			motor[flag2]=-100;
			motor[flag3]=-100;
		}
		else
		{
			motor[flag1]=0;
			motor[flag2]=0;
			motor[flag3]=0;
		}


	}
}
