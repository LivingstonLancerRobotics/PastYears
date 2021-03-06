#pragma config(Sensor, S4,     IR_LEFT,        sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "hitechnic-sensormux.h"
#include "Robotics (PROGRAMENG)/hitechnic-irseeker-v2.h"

//const tMUXSensor IR_LEFT = msensor_S4_2;

/*
Edited again on 3/2, if it has stopped working revert to the edit from 2/21
--


*/


int irChannel, rightStrength, rightChannel, leftChannel, leftStrength, irStrength;
int irPosition = -1;
int vertValue = 40;
//const tMUXSensor IR = msensor_S1_1;
/*
task getIR()
{
	while(true){
		if(HTIRS2readEnhanced(IR_RIGHT,rightChannel,rightStrength)){
			if(HTIRS2readEnhanced(IR_LEFT,leftChannel,leftStrength)){
				if((rightChannel==7 && leftChannel ==3) && (abs(rightStrength-leftStrength)<50)){
					irChannel = 1; irStrength = ((float)rightStrength+(float)leftStrength)/2;}
				else if((rightChannel==7 && leftChannel ==1) && (abs(rightStrength-leftStrength)<50)){
					irChannel = 2; irStrength = ((float)rightStrength+(float)leftStrength)/2;}
				else {irChannel = 0; irStrength = ((float)rightStrength+(float)leftStrength)/2;;}
			}
		}
		nxtDisplayTextLine(0,"Right: %d",rightChannel);
		nxtDisplayTextLine(1,"Left: %d",leftChannel);
		nxtDisplayTextLine(2,"Total: %d",irChannel);
		nxtDisplayTextLine(3,"Str: %d", irStrength);
	}
}
*/
task readPosition()
{

	//startTask(getIR);
	wait1Msec(2000);
	while(true){
			if(nNxtButtonPressed == 2) vertValue--;
	if(nNxtButtonPressed == 1) vertValue++;
		if(HTIRS2readEnhanced(IR_LEFT,leftChannel,leftStrength))
		{
			if((leftChannel == 9 || leftChannel == 8) && leftStrength > vertValue) irPosition = 0;
			else if((leftChannel == 7 || leftChannel == 8) && leftStrength >30) irPosition = 1;
			else irPosition = 2;
		}
		nxtDisplayTextLine(0,"Channel: %d", leftChannel);
		nxtDisplayTextLine(2,"Strength: %d", leftStrength);
		nxtDisplayTextLine(4,"CutOff Value: %d", vertValue);
		nxtDisplayTextLine(6,"Position: %d", irPosition);
	}
}
