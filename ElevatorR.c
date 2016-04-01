/*
Todo:


Q/A:
Q: Is SensorType[] nessassary?
A:

Q:Dose lEDspam() work being called before and inside of the fuction it calls itself 
A:

Q:If I declare varible x = a + b and I change a or b would x change as well?
	In other words could x be valued as "a + b" or is it what ever "a + b" was when declared?
	
	int a = 1;
	int b = 2;
	int x = a + b;
	print(x);
	a = 2;
	print(x);

A:

Q:

*/



//Global Varibles:
	//Constants:

	//Encoder values for different floors 1, 2, and 3
	int POSITION1 = 20;
	int POSITION2 = 1040;
	int POSITION3 = 1660;

	//Motor Power Maxuim and Minimum (the lowest it'll go, not stall or zero) Absolutly
	int HIGHESTMOTORPOWER = 127;
	int LOWESTMOTORPOWER = 21;

	//Varibles:

//Initialization of some values: 
	//Sensors:
	SensorType[button1] = sensorTouch;
	SensorType[button2] = sensorTouch;
	SensorType[button3] = sensorTouch;



//Functions:
void lEDConfiguration(int lED1pos, int lED2pos, int lED3pos){
	if(lED1pos == 1){
			turnLEDOn(lED1);
		}else if(lED1pos == 0){
			turnLEDOff(lED1);
		}else {
			lEDSpam();
		}

		if(lED2pos == 1){
			turnLEDOn(lED2);
		}else if(lED2pos == 0){
			turnLEDOff(lED2);
		}else {
			lEDSpam();
		}

		if(lED3pos == 1){
			turnLEDOn(lED3);
		}else if(lED3pos == 0){
			turnLEDOff(lED3);
		}else {
			lEDSpam();
		}
}

void lEDSpam(){
	stopMotor(motor);
	while(true){
		lEDConfiguration(1,1,1);
		wait(.1);					
		lEDConfiguration(0,0,0);
		wait(.1);					
	}
}

float advancedMotorPower(int aMPInput){	//*should be float but may have to be int (depening on what StartMotor()takes as an input type)
	float aMPOutput;
		if(abs(aMPInput) >= 20){			//*May need to be changed to abs(-2) = 2...
		aMPOutput = LOWESTMOTORPOWER * (aMPInput/abs(aMPInput));
		}else{
		aMPOutput = (HIGHESTMOTORPOWER/12) * (pow(aMPInput,1/3)); //*Formula needs to be changed for vex robotics
		}
	return aMPOutput;					//*most likely needs differnt api...
}

void motorPosition(int floor){
	int currentPositionEncoder = SensorValue[encoder];
	int goalPosition;
	int positionChange = goalPosition - currentPositionEncoder;

	if(floor == 1){
		goalPosition = POSITION1;
	}else if(floor == 2){
		goalPosition = POSITION2;
	}else if(floor == 3){
		goalPosition = POSITION3;
	}else{
		lEDSpam();
	}

	// is this nessasary here? QA3 positionChange = goalPosition - currentPositionEncoder 

	while(abs(positionChange) < 20){
		startMotor(advancedMotorPower(positionChange));
		wait(.01);
	}
}

void motorLEDInterp(int motorLEDinput){
	if(motorLEDinput == 10){
		motorPosition(1);
	}else if(motorLEDinput == 11){
		motorPosition(1);
		lEDConfiguration(1,0,0);
	}else if(motorLEDinput == 20){
		motorPosition(2);
		lEDConfiguration(0,0,0);
	}else if(motorLEDinput == 22){
		motorPosition(2);
		lEDConfiguration(0,1,0);
	}else if(motorLEDinput == 33){
		motorPosition(3);
		lEDConfiguration(0,0,1);
	}else{
		lEDSpam();
	}
}
task main(){



}

/*
int arrayExample[4][4] = {
	{0,1,2,3},
	{0,1,2,3},
	{0,1,2,3},
	{0,1,2,3}
};
*/