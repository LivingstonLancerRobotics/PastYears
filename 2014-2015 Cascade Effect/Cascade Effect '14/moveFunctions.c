#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  HTServo,  none,     none)
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
#pragma config(Servo,  srvo_S2_C1_2,    rollingGoalLeft,      tServoNone)
#pragma config(Servo,  srvo_S2_C1_3,    rollingGoalRight,     tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_1,    servo7,               tServoStandard)
#pragma config(Servo,  srvo_S2_C2_2,    servo8,               tServoStandard)
#pragma config(Servo,  srvo_S2_C2_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_6,    servo12,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "hitechnic-sensormux.h"
#include "hitechnic-gyro.h"
#include "gyroFunctions.c"

float ticks = 0; int theta;
bool braked;

void motorTrigger(tMotor motorCall,int x,int y,int z)
{
	motor[motorCall]= (y+x+z);
}



void moveEncodedMotor(int target)
{
	nMotorEncoder[motorLift2] = 0;
	//	nMotorEncoder[lift2] = 0; has no encoder

	nMotorEncoderTarget[motorlift2] = target;  //times spun 2.5 rotations = 900
	//	nMotorEncoderTarget[lift2] = target; //times spun

	motor[motorlift1] = 50;
	motor[motorlift2] = 50;

	wait1Msec(8000);
}


void moveTime(int angle, int power, int time)
{

	int x = power*128/100*cosDegrees(angle);
	int y = power*128/100*sinDegrees(angle);
	int z = 0;

	//	int accelValue = SensorValue(Accel); //set accelerometer value to accelValue
	//	int gyroValue = HTGYROReadRot(Gyro); //set gyroscope value to gyroValue

	//nxtDisplayCenteredBigTextLine(5,"%d",gyroValue); //display gyroValue to NXT
	//nxtDisplayCenteredBigTextLine(5,"%d",accelValue); //display accelValue to NXT

	//	int trueX = (cosDegrees(currHeading+calibrate)*x)-(sinDegrees(currHeading+calibrate)*y); //sets trueX to rotated x value
	//	int trueY = (sinDegrees(currHeading+calibrate)*x)+(cosDegrees(currHeading+calibrate)*y); //sets trueY to rotated y value
	//
	//	x = trueX;
	//	y = trueY;

	motorTrigger(frontRight,x,-y,-z);
	motorTrigger(backRight,-x,-y,-z);
	motorTrigger(frontLeft,x,y,-z);
	motorTrigger(backLeft,-x,y,-z);

	wait1Msec(time);

	motorTrigger(frontRight,0,0,0);
	motorTrigger(backRight,0,0,0);
	motorTrigger(frontLeft,0,0,0);
	motorTrigger(backLeft,0,0,0);

	wait1Msec(100);

}



void resetEncoders() {
	nMotorEncoder[frontLeft] = 0;
	nMotorEncoder[frontRight] = 0;
	nMotorEncoder[backLeft] = 0;
	nMotorEncoder[backRight] = 0;
}


void moveAll(float fl, float fr, float bl, float br){
	motor[frontLeft] = fl;
	motor[frontRight] = fr;
	motor[backLeft] = bl;
	motor[backRight] = br;
}

void moveAll(float left, float right){
	moveAll(left,right,left,right);
}

void moveAll(float all){
	moveAll(all,all);
}
void setAll(float fl, float fr, float bl, float br){
	nMotorEncoderTarget[frontleft]=fl;
	nMotorEncoderTarget[frontright]=fr;
	nMotorEncoderTarget[backleft]=bl;
	nMotorEncoderTarget[backright]=br;
	moveAll(75, -75);
	while(nMotorRunState[frontleft] != runStateIdle) { }
	moveAll(0);
}


void setAll(float left, float right){
	nMotorEncoder[frontLeft] = 0;
	nMotorEncoder[frontright] = 0;
	nMotorEncoder[backLeft] = 0;
	nMotorEncoder[backright] = 0;
	nMotorEncoderTarget[frontleft]=left;
	nMotorEncoderTarget[frontright]=right;
	nMotorEncoderTarget[backleft]=left;
	nMotorEncoderTarget[backright]=right;
	motor[frontleft] = 75; motor[backleft] = 75;
	motor[frontright] = -75; motor[backright] = -75;
	while(nMotorRunState[frontleft] != runStateIdle) { //playSound(soundBeepBeep);
	}
	playSound(soundBeepBeep);
	moveAll(0);
}

void setAllPos(float left, float right){
	nMotorEncoder[frontLeft] = 0;
	nMotorEncoder[frontright] = 0;
	nMotorEncoder[backLeft] = 0;
	nMotorEncoder[backright] = 0;
	nMotorEncoderTarget[frontleft]=-left;
	nMotorEncoderTarget[frontright]=-right;
	nMotorEncoderTarget[backleft]=-left;
	nMotorEncoderTarget[backright]=-right;
	motor[frontleft] = -75; motor[backleft] = -75;
	motor[frontright] = 75; motor[backright] = 75;
	while(nMotorRunState[frontleft] != runStateIdle) { //playSound(soundBeepBeep);
	}
	//	playSound(soundBeepBeep);
	moveAll(0);
	//this sets everything to brakestop
}


void setAll(float all){
	nMotorEncoder[frontLeft] = 0;
	nMotorEncoder[frontright] = 0;
	nMotorEncoder[backLeft] = 0;
	nMotorEncoder[backright] = 0;
	nMotorEncoderTarget[frontleft]=all;
	nMotorEncoderTarget[frontright]=all;
	nMotorEncoderTarget[backleft]=all;
	nMotorEncoderTarget[backright]=all;
	motor[frontleft] = 75; motor[backleft] = 75;
	motor[frontright] = 75; motor[backright] = 75;
	while(nMotorRunState[frontleft] != runStateIdle) { //playSound(soundBeepBeep);
	}
	//	playSound(soundBeepBeep);
	moveAll(0);
}

void encodedMove(float dist){
	float encoderValue = (dist/8)*1120.0;
	setAll(encoderValue,-encoderValue);
}

void encodedMovePos(float dist){
	float encoderValue = (dist/8)*1120.0;
	setAllPos(encoderValue,-encoderValue);
}

void stopMotors()
{
	motor[frontleft]=0;
	motor[frontright]=0;
	motor[backleft]=0;
	motor[backright]=0;
}

/*void rotate(float degreesRelative)
{
float dist = degreesRelative*((PI/360)*15.56)+1.5;
float encoderValue = (dist/(4.0*PI))*1120.0;
resetEncoders();
setAll(encoderValue);
resetEncoders();
playSound(soundBeepBeep);
}*/

void rotatePos(float degreesRelative)
{
	float dist = degreesRelative*((PI/360)*15.56)+1.5;
	float encoderValue = (dist/8)*1120.0;
	resetEncoders();
	setAll(-encoderValue);
	resetEncoders();
	playSound(soundBeepBeep);
}

void rotate(float relativeAngle, int direction)
{
	float finalHeading = currHeading + direction*relativeAngle;

	if (finalHeading > 360) finalHeading -= 360;
	else if(finalHeading < 0) finalHeading += 360;
	//clearDebugStream();
	//writeDebugStreamLine("%d", finalHeading);
	float z=0;
	int startHeading = currHeading;
	float theta = abs(currHeading-startHeading);
	while(abs(finalHeading - currHeading) >= 2){
		z = -direction*(39*cos(pi*theta/relativeAngle)+39);
		motor[frontLeft] = z;
		motor[frontRight] = z;
		motor[backLeft] = z;
		motor[backRight] = z;
		theta = abs(currHeading-startHeading);
	}
	//int z = -70*direction;
	/*theta = abs(relativeAngle/2.0);
	while(abs(finalHeading - currHeading) > theta)
	{
	z-=direction;
	motor[frontLeft] = z;
	motor[frontRight] = z;
	motor[backLeft] = z;
	motor[backRight] = z;
	}
	playSound(soundBeepBeep);
	while(abs(finalHeading - currHeading) < theta && abs(finalHeading - currHeading) > 0)
	{
	z+=direction;
	motor[frontLeft] = z;
	motor[frontRight] = z;
	motor[backLeft] = z;
	motor[backRight] = z;
	}
	playSound(soundBeepBeep);
	*/
	z = 0;
	motor[frontLeft] = z;
	motor[frontRight] = z;
	motor[backLeft] = z;
	motor[backRight] = z;
	playSound(soundBeepBeep);
	wait1Msec(100);
}

void rotateCoast(float relativeAngle, int direction){
	float finalHeading = currHeading + direction*relativeAngle;

	if (finalHeading > 360) finalHeading -= 360;
	else if(finalHeading < 0) finalHeading += 360;
	//clearDebugStream();
	//writeDebugStreamLine("%d", finalHeading);
	float z=0;
	float startHeading = currHeading;
	float theta = abs(currHeading-startHeading);
	while(abs(finalHeading - currHeading) >= 0.5){
		z = -direction*(20*cos(pi*theta/relativeAngle)+75);
		motor[frontLeft] = z;
		motor[frontRight] = z;
		motor[backLeft] = z;
		motor[backRight] = z;
		theta = abs(currHeading-startHeading);
	}
	z = 0;
	motor[frontLeft] = z;
	motor[frontRight] = z;
	motor[backLeft] = z;
	motor[backRight] = z;
	playSound(soundBeepBeep);
	wait1Msec(100);
}

/*
task calibrateDrive()//needs work, doing some wack stuff
{
calibrate = 360 - currHeading;
PlaySound(soundUpwardTones);
wait1Msec(500);
/*
initializeRobot();
HTGYROstartCal(Gyro);
delTime = 0;//calibration
prevHeading = 0;
curRate = 0;
wait1Msec(500);
*/
//}un




void encodedMoveForward(float dist){ //accuracy is inversely proportional to distance
	float encoderValue = (dist/(4.0*PI))*1120.0;
	nMotorEncoder[frontLeft] = 0;
	nMotorEncoder[frontRight] = 0;
	nMotorEncoder[backLeft] = 0;
	nMotorEncoder[backRight] = 0;
	if(encoderValue < 0){
		while(abs(nMotorEncoder[backLeft]) < abs(encoderValue)){
			motor[frontLeft] = -70;
			motor[backLeft] = -70;
			motor[frontRight] = 70;
			motor[backRight] = 70;
		}
		}	else{
		while(nMotorEncoder[backLeft] < encoderValue){
			motor[frontLeft] = 70;
			motor[backLeft] = 70;
			motor[frontRight] = -70;
			motor[backRight] = -70;
		}
	}
	motor[frontLeft] = 0;
	motor[backLeft] = 0;
	motor[frontRight] = 0;
	motor[backRight] = 0;

	/*
	motor[frontLeft] = 70;
	motor[backLeft] = 70;
	motor[frontRight] = -70;
	motor[backRight] = -70;
	bl = true; br=true;fr=true;fl=true;
	while(true){
	if(nMotorEncoder[frontLeft] > encoderValue && !fl)
	{motor[frontLeft]=0;fl=true; playSound(soundDownwardTones);}
	if(nMotorEncoder[frontRight] < -encoderValue && !fr)
	{motor[frontRight]=0;fr=true; playSound(soundDownwardTones);}
	if(nMotorEncoder[backLeft] > encoderValue && !bl)
	{motor[backLeft]=0;bl=true; playSound(soundDownwardTones);}
	if(nMotorEncoder[backRight] < -encoderValue && !br)
	{motor[backRight]=0;br=true; playSound(soundDownwardTones);}
	if(br&&bl&&fl&&fr)
	break;
	}*/
}

void encodedMoveRight(float dist){ //not really accurate bc it's mecanum
	float encoderValue = (dist/(4.0*PI))*1120.0;
	nMotorEncoder[frontLeft] = 0;
	nMotorEncoder[frontRight] = 0;
	nMotorEncoder[backLeft] = 0;
	nMotorEncoder[backRight] = 0;
	if(encoderValue < 0){
		while(abs(nMotorEncoder[backLeft]) < abs(encoderValue)){
			motor[frontLeft] = 70;
			motor[backLeft] = -70;
			motor[frontRight] = -70;
			motor[backRight] = 70;
		}
		}	else{
		while(nMotorEncoder[backLeft] < encoderValue){
			motor[frontLeft] = -70;
			motor[backLeft] = 70;
			motor[frontRight] = 70;
			motor[backRight] = -70;
		}
	}
	motor[frontLeft] = 0;
	motor[backLeft] = 0;
	motor[frontRight] = 0;
	motor[backRight] = 0;

	/*
	motor[frontLeft] = 70;
	motor[backLeft] = 70;
	motor[frontRight] = -70;
	motor[backRight] = -70;
	bl = true; br=true;fr=true;fl=true;
	while(true){
	if(nMotorEncoder[frontLeft] > encoderValue && !fl)
	{motor[frontLeft]=0;fl=true; playSound(soundDownwardTones);}
	if(nMotorEncoder[frontRight] < -encoderValue && !fr)
	{motor[frontRight]=0;fr=true; playSound(soundDownwardTones);}
	if(nMotorEncoder[backLeft] > encoderValue && !bl)
	{motor[backLeft]=0;bl=true; playSound(soundDownwardTones);}
	if(nMotorEncoder[backRight] < -encoderValue && !br)
	{motor[backRight]=0;br=true; playSound(soundDownwardTones);}
	if(br&&bl&&fl&&fr)
	break;
	}*/
}
void target(float left, float right){
	nMotorEncoderTarget[frontleft] = left;
	nMotorEncoderTarget[frontright] = right;
	nMotorEncoderTarget[backleft] = left;
	nMotorEncoderTarget[backright] = right;
}

void freezeEncoders() {
	nMotorEncoder[frontleft] = 0;
	nMotorEncoder[frontright] = 0;
	nMotorEncoder[backleft] = 0;
	nMotorEncoder[backright] = 0;
	playSound(soundBeepBeep);
}

float checkMotorEnc() {
	return nMotorEncoder[frontleft];
}

void setPwr(int pwr) {
	/*
	if(!isPos){
	if(pwr>78)pwr=78;
	if(pwr<0)pwr=1;
	}
	else {
	if(pwr<-78)pwr=-78;
	if(pwr>0)pwr=-1;
	}
	*/
	motor[frontleft] = pwr;
	motor[backleft] = pwr;
	motor[backright] = -1*pwr;
	motor[frontright] = -1*pwr;
}

void setPwrRot(int pwr) {
	motor[frontleft] = pwr;
	motor[backleft] = pwr;
	motor[backright] = pwr;
	motor[frontright] = pwr;
}

void setPwrPos(int pwr) {
	if(pwr<-78)
		pwr=-78;
	if(pwr>0)
		pwr=-1;
	motor[frontleft] = -pwr;
	motor[backleft] = -pwr;
	motor[backright] = pwr;
	motor[frontright] = pwr;
}

void rotPwr(int pwr) {
	if(pwr>78)pwr = 78;
	if(pwr<0) pwr = 1;
	motor[frontleft] = pwr;
	motor[backleft] = pwr;
	motor[backright] = pwr;
	motor[frontright] = pwr;
}

void brake()
{
	motor[frontleft] = 0;
	motor[frontright] = 0;
	motor[backright] = 0;
	motor[backleft] = 0;
}

void advBrake() {
	motor[frontleft] = -1;
	motor[frontRight] = -1;
	motor[backLeft] = -1;
	motor[backright] = -1;
	wait1Msec(100);
	motor[frontleft] = 0;
	motor[frontright] = 0;
	motor[backLeft] = 0;
	motor[backright] = 0;
}

void advBrakeNeg() {
	motor[motorLift1] = -5;
	motor[motorLift2] = -5;
}

void advCoast(float dist){
	bool positiveSign;
	if(dist > 0)positiveSign = true;
	else positiveSign = false;
	float encval = dist/(16.0*PI)*1120; //converts dist to inches
	freezeEncoders();
	int motorVal = 0;
	while(abs(checkMotorEnc()) < abs(encVal/2))
	{
		if(dist > 0) {motorVal -=1;}
		else {motorVal+=1;}
		//setPwr(motorVal, positiveSign);
	}
	while(abs(checkMotorEnc()) > abs(encVal/2))
	{
		if(dist > 0) motorVal +=1;
		else motorVal-=1;
		//	setPwr(motorVal, positiveSign);
		if(abs(checkMotorEnc()) > abs(encVal)) break;
	}
	brake();
	playSound(soundBeepBeep);
}

void coastTicks(int dist)
{
	float encval = dist;
	freezeEncoders();
	int motorVal = 0;
	while(abs(checkMotorEnc()) < abs(encVal/2))
	{
		motorVal-=1;
		setPwrPos(motorVal);
	}
	while(abs(checkMotorEnc()) > abs(encVal/2) && abs(checkMotorEnc()) < abs(encVal))
	{
		motorVal+=1;
		setPwrPos(motorVal);
	}
	brake();
}

task checkIfBraked(){
	wait1Msec(4000);
	braked = true;
}

void coastTo(float dist){
	float encval = dist/(7.25*PI)*1120;
	freezeEncoders();
	int motorVal;
	startTask(checkIfBraked);
	while(abs(checkMotorEnc()) < abs(encVal)){
		//if(abs(encVal)-abs(checkMotorEnc()) > 600)
		//	motorVal = -dist/abs(dist)*78;
		//else
		motorVal = -dist/abs(dist)*(25*cos(pi*checkMotorEnc()/encval)+50);
		motor[frontleft] = -motorVal;
		motor[frontright] = motorVal;
		motor[backright] = motorVal;
		motor[backleft] = -motorVal;
		if(braked)
		{
			braked = false;
			break;
		}
	}
	stopTask(checkIfBraked);
	motor[frontleft] = 0;
	motor[frontright] = 0;
	motor[backright] = 0;
	motor[backleft] = 0;
	wait1Msec(500);
}

void coastRaw(int dist){
	float encval = dist;
	freezeEncoders();
	int motorVal;
	startTask(checkIfBraked);
	while(abs(checkMotorEnc()) < abs(encVal)){
		//if(abs(encVal)-abs(checkMotorEnc()) > 600)
		//	motorVal = -dist/abs(dist)*78;
		//else
		motorVal = -dist/abs(dist)*(25*cos(pi*checkMotorEnc()/encval)+50);
		motor[frontleft] = -motorVal;
		motor[frontright] = motorVal;
		motor[backright] = motorVal;
		motor[backleft] = -motorVal;
		if(braked){
			braked = false;
			break;
		}
	}
	stopTask(checkIfBraked);
	motor[frontleft] = 0;
	motor[frontright] = 0;
	motor[backright] = 0;
	motor[backleft] = 0;
	wait1Msec(500);
}


/*
float encoderValue = dist;
freezeEncoders();
float motorVal = 0;
int multiplier = 1;
int adder = 5;
if(dist < 0)multiplier = -1;
while(abs(checkMotorEnc()) < abs(encoderValue))
{
int temp = checkMotorEnc();
motorVal = (checkMotorEnc()*pi/encoderValue);
//setPwr(-((motorVal*motorVal)-5)+78);\
setPwr(abs(sin(degreesToRadians(motorVal))*50+adder)*multiplier); // sets power to rounded shape
//wait1Msec(10);
if(checkMotorEnc()==temp)adder++;
else if(abs(checkMotorEnc()- temp) < 5) adder = 5;// needs to be changed to range
}
brake();

}*/

void coastFor(int dist)
{
	float encoderValue = dist/(16.0*PI)*1120;
	freezeEncoders();
	float motorVal = 0;
	int multiplier = 1;
	int adder = 5;
	if(dist < 0)multiplier = -1;
	while(abs(checkMotorEnc()) < abs(encoderValue))
	{
		int temp = checkMotorEnc();
		motorVal = (checkMotorEnc()/2*pi);
		//setPwr(-((motorVal*motorVal)-5)+78);\
		setPwr(abs(sin(degreesToRadians(motorVal))*50+adder)*multiplier); // sets power to rounded shape
		//wait1Msec(10);
		if(checkMotorEnc()==temp)adder++;
		else if(abs(checkMotorEnc()- temp) < 5) adder = 5;// needs to be changed to range
	}
	brake();
}

void coast(float dist){
	float encval = dist/(16.0*PI)*1120;
	freezeEncoders();
	int motorVal = 0;
	while(abs(checkMotorEnc()) < abs(encVal/2))
	{
		motorVal-=5;
		setPwrPos(motorVal);
	}
	while(abs(checkMotorEnc()) > abs(encVal/2) && abs(checkMotorEnc()) < abs(encVal))
	{
		motorVal+=5;
		setPwrPos(motorVal);
	}
	brake();
}

void moveReading(){
	motor[frontleft] = 78;
	motor[frontright] = -78;
	motor[backLeft] = 78;
	motor[backRight] = -78;
	while(true)
		ticks = checkMotorEnc();
}

void encRot(float dist){
	if(dist<0)
	{
		float encval = dist/(16.0*PI)*1120/180*114.5;
		freezeEncoders();
		int motorVal = 0;
		while(abs(checkMotorEnc())<abs(encVal/2))
		{
			motorVal++;
			rotPwr(motorVal);
		}
		while(abs(checkMotorEnc()) > abs(encVal/2)
			&&	abs(checkMotorEnc()) < abs(encVal))
		{
			motorVal--;
			rotPwr(motorVal);
		}
		playSound(soundDownwardTones);
		brake();
		playSound(soundBeepBeep);
	}
	else
	{
		float encval = dist/(16.0*PI)*1120/8.0/30*45;
		freezeEncoders();
		int motorVal = 0;
		while(abs(checkMotorEnc())<abs(encVal/2))
		{
			motorVal++;
			rotPwr(-motorVal);
		}
		while(abs(checkMotorEnc()) > abs(encVal/2))
		{
			motorVal--;
			rotPwr(-motorVal);
		}
		brake();
	}
}

void lowerLift() {
	motor[motorlift2]=90;
	motor[motorlift1]=90;
	nMotorEncoder[motorlift2] = 0;
	wait1Msec(50);
	while(abs(nMotorEncoder[motorlift2])<abs(1440*3.2)) { /*until its at the top*/ }
	playSound(soundBeepBeep);
	motor[motorlift2]=0;
	motor[motorlift1]=0;
}

 void lowerLift2() {
	motor[motorlift2]=90;
	motor[motorlift1]=90;
	nMotorEncoder[motorlift2] = 0;
	wait1Msec(50);
	while(abs(nMotorEncoder[motorlift2])<abs(1440*1.8)) { /*until its at the top*/ }
	playSound(soundBeepBeep);
	motor[motorlift2]=0;
	motor[motorlift1]=0;
}


void dumpAll() {
	//wait1Msec(2000);
	//encodedMove(-3);
	wait1Msec(500);
	servo[dump] = 180;
	wait1Msec(1500);
	servo[dump] = 70;
	//lowerLift();
}

void dumpAll2() {
	servo[dump] = 170;
	wait1Msec(2000);
	servo[dump] = 66;
	//lowerLift();
}


void raiseLift() {


	motor[motorlift2]=-90;
	motor[motorlift1]=-90;
	//raise lift

	nMotorEncoder[motorlift2] = 0;
	wait1Msec(50);
	while(abs(nMotorEncoder[motorlift2])<(1440*3.5))//2.5 rotations
	{
		//until its at the top
	}
	playSound(soundBeepBeep);
	motor[motorlift2]=0;
	motor[motorlift1]=0;
	//then stop
	//	stopTask(servoInit);
}


void raiseLift2() {


	motor[motorlift2]=-90;
	motor[motorlift1]=-90;
	//raise lift

	nMotorEncoder[motorlift2] = 0;
	wait1Msec(50);
	while(abs(nMotorEncoder[motorlift2])<(1440*2))//2.5 rotations
	{
		//until its at the top
	}
	playSound(soundBeepBeep);
	motor[motorlift2]=0;
	motor[motorlift1]=0;
	//then stop
	//	stopTask(servoInit);
}


void startCollector(){
	motor[collector] = 65;
	motor[collector2] = -65;
}

void stopCollector(){
	motor[collector] = 0;
	motor[collector2] = 0;
}

void moveSlow(int dir){
	moveAll(dir*20,dir*-32);
	//use dir to indicate direction
}