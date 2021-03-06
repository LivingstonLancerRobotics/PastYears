#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     IR_LEFT,        sensorHiTechnicIRSeeker1200)
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
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "hitechnic-gyro.h"
#include "Dump.c"
#include "moveFunctions.c"
#include "infraredSensor.c"
#include "gyrofunctions.c"

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

task servoInit() {
	while(true)
		servo[dump] = 94 + PI;
}

task main()
{
		waitForStart();
//		startTask(servoInit);
		servo[dump] = 85+PI;
		coastTo(24);
		wait1Msec(500);
		encRot(-88);
		wait1Msec(500);
		coastTo(50); //move to center goal
		wait1Msec(500);
		coastTo(-20);
		wait1Msec(1000);
		encRot(-50);
		wait1Msec(1000);
		coastTo(30);
		coastTo(-30);
		wait1Msec(500);
		encRot(-145);
		wait1Msec(500);
		coastTo(30);
		encRot(-88);
		coastFor(-20);
		//Neccessary do not touch
		wait1Msec(500000);
}
//note to user: coastTo and coastFor have been resolved to  P

/*

Move out of parking zone/ramp and scan for IR (in front of ramp) facing forward still
Then scan for IR
Move to location, mantaining no strafe
Release kickstand
Align with center structure
Move under center goal, raise lift and score

*/
