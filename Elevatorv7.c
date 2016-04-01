#pragma config(Sensor, dgtl1,  limitSwitch1,         sensorTouch)
#pragma config(Sensor, dgtl2,  limitSwitch2,         sensorTouch)
//#pragma config(Sensor, dgtl3,  encoder,            sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  limitSwitchFloor2,    sensorQuadEncoder)
#pragma config(Sensor, dgtl4,  limitSwitchFloor3,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  limitSwitch3,         sensorTouch)
#pragma config(Sensor, dgtl6,  button3,              sensorTouch)
#pragma config(Sensor, dgtl7,  button2,              sensorTouch)
#pragma config(Sensor, dgtl8,  button1,              sensorTouch)
#pragma config(Sensor, dgtl9,  limitSwitchFloor1,    sensorTouch)
#pragma config(Sensor, dgtl10, lED3,                 sensorLEDtoVCC)
#pragma config(Sensor, dgtl11, lED2,                 sensorLEDtoVCC)
#pragma config(Sensor, dgtl12, lED1,                 sensorLEDtoVCC)
#pragma config(Motor,  port2, elevatorMotor,         tmotorVex393_MC29, openLoop)


//CONFIGUREATION:
	//CONSTANTS:
		//Motor Specifics
		int HIGHESTMOTORPOWER = 127;
		int NORMALMOTORPOWER = 63;
		int LOWESTMOTORPOWER = 21;

		//SafetyPro constants 
		int SAFETYPROTIME = 20000;
		int FLOORDURATIONTIME = 5000;


//FUNCTIONS:

	elevatorPosition(int floor){

	}

	lEDIndicator(){
		if(SensorValue(limitSwitchFloor1) == 1){
			turnLEDOn(led1);
		}else{
			turnLEDOff(led1);
		}
		if(SensorValue(limitSwitchFloor2) == 1){
			turnLEDOn(led2);
		}else{
			turnLEDOff(led2);
		}
		if(SensorValue(limitSwitchFloor3) == 1){
			turnLEDOn(led3);
		}else{
			turnLEDOff(led3);
		}
	}

	safetyPro(){
		
	}


task main(){
	int eButton1;
	int eButton2;
	int eButton3;


	while(true){
		eButton1 = (SensorValue(button1) + SensorValue(limitSwitch1));
		eButton2 = (SensorValue(button2) + SensorValue(limitSwitch2));
		eButton3 = (SensorValue(button3) + SensorValue(limitSwitch3));

		lEDIndicator();

	}
}