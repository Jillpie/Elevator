#pragma config(Sensor, dgtl1,  limitSwitch1,   sensorTouch)
#pragma config(Sensor, dgtl2,  limitSwitch2,   sensorTouch)
#pragma config(Sensor, dgtl3,  encoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  limitSwitch3,    sensorTouch)
#pragma config(Sensor, dgtl6,  button3,        sensorTouch)
#pragma config(Sensor, dgtl7,  button2,        sensorTouch)
#pragma config(Sensor, dgtl8,  button1,        sensorTouch)
#pragma config(Sensor, dgtl10, lED3,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl11, lED2,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl12, lED1,           sensorLEDtoVCC)
#pragma config(Motor,  port2, elevatorMotor,         tmotorVex393_MC29, openLoop)

/*
Test:
	Reconfigure limit switches and buttons i.e button1 = floor one button
	check:

*/

//Global Varibles [CONFIGURATION]:

	//CONFIGUREATION:

		int placeHolderInt;

	//Constants:

		//Encoder values for different floors 1, 2, and 3
		int POSITION1 = 20;
		int POSITION2 = 1040;
		int POSITION3 = 1660;

		//Motor Power Maxuim and Minimum (the lowest it'll go, not stall or zero) Absolutly
		int HIGHESTMOTORPOWER = 127;
		int LOWESTMOTORPOWER = 25;

		//Speical
		int SAFETYPROTIME = 20000; //value millisecouns of the safety pro timeout time, how long untill elevator dose saftey pro
		int FLOORDURATIONTIME = 5000;	//value in millisoneoucns = 5sec

	//Varibles:

		int UniversalEvent;

		int eButton1 = SensorValue[button1] + SensorValue[limitSwitch1];
		int eButton2 = SensorValue[button2] + SensorValue[limitSwitch2];
		int eButton3 = SensorValue[button3] + SensorValue[limitSwitch3];

//Functions:
void lEDSpam(){
	stopMotor(elevatorMotor);
	while(true){
		turnLEDOn(lED1);
		turnLEDOn(lED2);
		turnLEDOn(lED3);
		wait(.5);
		turnLEDOff(lED1);
		turnLEDOff(lED2);
		turnLEDOff(lED3);
		wait(.5);
	}
}

void lEDGroup(int lED1Group, int lED2Group, int lED3Group){
	if(lED1Group == 1){
		turnLEDOn(lED1);
	}else if(lED1Group == 0){
		turnLEDOff(lED1);
	}else {
		lEDSpam();
	}

	if(lED2Group == 1){
		turnLEDOn(lED2);
	}else if(lED2Group == 0){
		turnLEDOff(lED2);
	}else {
		lEDSpam();
	}

	if(lED3Group == 1){
		turnLEDOn(lED3);
	}else if(lED3Group == 0){
		turnLEDOff(lED3);
	}else {
		lEDSpam();
	}
}

/*
float advancedMotorPower(float aMPInput){
	float aMPOutput;
	float slope = (.0635);
		if(abs(aMPInput) <= 20){
		aMPOutput = LOWESTMOTORPOWER * (aMPInput/abs(aMPInput));
		}else{
			aMPOutput = (aMPInput * slope);
		//aMPOutput = (HIGHESTMOTORPOWER/12) * (pow(aMPInput,1/3));
		}
		int powerBug = pow(aMPInput,1/3);
		int highestPower = (127/12);
	return aMPOutput;
}
*/

void motorPosition(int floor){
	int currentPositionEncoder = SensorValue(encoder);
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

	positionChange = goalPosition - currentPositionEncoder;
	int advancedPowerFunc = (positionChange * .0635);
	startMotor(elevatorMotor,advancedPowerFunc);
	
}

void lEDIndicator(){
	int currentPositionEncoder = SensorValue(encoder);
	int LEDPOSRANGE = 30;

	if(currentPositionEncoder <= (POSITION1 + LEDPOSRANGE) && currentPositionEncoder >= (POSITION1 - LEDPOSRANGE)){
		lEDGroup(1,0,0);
	}else if(currentPositionEncoder <= (POSITION2 + LEDPOSRANGE) && currentPositionEncoder >= (POSITION2 - LEDPOSRANGE)){
		lEDGroup(0,1,0);
	}else if(currentPositionEncoder <= (POSITION3 + LEDPOSRANGE) && currentPositionEncoder >= (POSITION3 - LEDPOSRANGE)){
		lEDGroup(0,0,1);
	}else{
		lEDGroup(0,0,0);
	}
}

/*
void safetyPro(){
	if(eButton1 == 0 && eButton2 == 0 && eButton3 == 0 && time1(T1) >= SAFETYPROTIME && (UniversalEvent == 3000 || UniversalEvent == 5000)){
		motorPosition(1);
	}else if(eButton1 != 0 && eButton2 != 0 && eButton3 != 0 ){
		clearTimer(T1);
	}else if(UniversalEvent == 1000){
		clearTimer(T1);
	}
}
*/

task main(){

	int trigger = 0;
	int timer1;
	int timer2;
	int timer3;
	int timer4;
	int myBug = 1233;

	while(true){

		eButton1 = SensorValue[button1] + SensorValue[limitSwitch1];
		eButton2 = SensorValue[button2] + SensorValue[limitSwitch2];
		eButton3 = SensorValue[button3] + SensorValue[limitSwitch3];


		if(eButton1 != 0 && eButton2 != 0){
			myBug = 10;
		}

		lEDIndicator();


		if((trigger == 0) && (eButton1 != 0 || eButton2 != 0 || eButton3 != 0)){
			trigger = 1;
			clearTimer(T2);
			clearTimer(T3);
		}
		if(trigger == 1){

			motorPosition(2);

		}
	}
}


