#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  HTServo,  none,     none)
#pragma config(Sensor, S3,     HTSPB,          sensorI2CCustom9V)
#pragma config(Sensor, S4,     SMUX,           sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     frontRight,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     backRight,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorLift1,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorLift2,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     frontLeft,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     backLeft,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     collector,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     collector2,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    dump,                 tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_1,    rollingGoalLeft,      tServoStandard)
#pragma config(Servo,  srvo_S2_C2_2,    rollingGoalRight,     tServoStandard)
#pragma config(Servo,  srvo_S2_C2_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_6,    servo12,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard		!!*//


#include "hitechnic-gyro.h"
#include "Collector.c"
#include "RollingGoal.c"
#include "Dump.c"
#include "encoderFunctions.c"
#include "moveFunctions.c"
#include "infraredSensor.c"
#include "gyrofunctions.c"


void rotateTrue(int relativeAngle, int direction, int power)
{
	int finalHeading = currHeading + direction*relativeAngle;

	if (finalHeading > 360) finalHeading -= 360;
	else if(finalHeading < 0) finalHeading += 360;

	while(abs(finalHeading - currHeading) != 0)
	{
		int x = 0;
		int y = 0;
		int z = power*direction*128/100;

		motorTrigger(frontRight,x,-y,-z);
		motorTrigger(backRight,-x,-y,-z);
		motorTrigger(frontLeft,x,y,-z);
		motorTrigger(backLeft,-x,y,-z);
	}
	motorTrigger(frontRight,0,0,0);
	motorTrigger(backRight,0,0,0);
	motorTrigger(frontLeft,0,0,0);
	motorTrigger(backLeft,0,0,0);

	wait1Msec(100);
}

/*
SMUX
1 - Gyro
2 - Accel
3 - IR right
4 - IR left
*/

task display()
{
	while (true){
		eraseDisplay();
		nxtDisplayTextLine(0,"Act:%d",nMotorEncoder[frontLeft]);
		//nxtDisplayCenteredTextLine(0, "Heading: %d", currHeading);
		//nxtDisplayCenteredTextLine(2, "Sonar: %d", sonarValue);
		wait1Msec(20);
	}
}

void initializeRobot()
{
	initial = 0;
	for(int i = 0; i < 100; i++){//Sensor
		initial += SensorValue[S4];
		wait10Msec(1);
	}
	initial = initial / 100;//Sensor
	return;
}

void raiseLift() {

	motor[motorlift2]=-90;
	motor[motorlift1]=-90;
	//raise lift

	nMotorEncoder[motorlift2] = 0;
	wait1Msec(50);
	while(abs(nMotorEncoder[motorlift2])<(1440*2.7))//2.5 rotations
	{
		//until its at the top
	}

	motor[motorlift2]=0;
	motor[motorlift1]=0;
	//then stop
}

void lowerLift() {
	motor[motorLift2]=90;
	motor[motorLift1]=90;
	wait1Msec(50);
	while(abs(nMotorEncoder[motorLift2])<(1440*2.4)) {}
	stopEncodedMotors();
	nMotorEncoder[motorLift2] = 0;
}

void dumpAll() {
	servo[dump] = 170;
	wait1Msec(5000);
	servo[dump] = 94+PI;
}

task servoInit() {
	while(true)
		servo[dump] = 94 + PI;
}

task main()
{
	waitForStart();
		startTask(servoInit);
		servo[dump] = 94+PI;
			rotate(-40);
		coast(-77); //move to center goal
		advBrake();
	//Neccessary do not touch
	while(true)
	{
		wait1Msec(10000);
		//playSound(soundBeepBeep);
	}
}

/*

Move out of parking zone/ramp and scan for IR (in front of ramp) facing forward still
Then scan for IR
Move to location, mantaining no strafe
Release kickstand
Align with center structure
Move under center goal, raise lift and score

*/
