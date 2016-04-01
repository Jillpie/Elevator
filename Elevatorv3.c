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
Todo:

	Needs to have an "act" function where the program acually excutes the movement rather than just changeing what it'll do 
		- for instance if the elevator "just got to" floor 1 and it's on its wait timer and all buttons are pressed it'll 
		- change the Univesal event value to the correct value but continue its timer and latter "act" accordering to waht
		- the universal event value is euqal to...

		Resolve: This is acually not a problem just its not called "act" its just useing the "act" I currently have as motorPosition
			- to as the "act" 


	Funcion motorPosition needs to be fixed so it dosn't have a loop in it that will halt program

		Almost Resolve: Perhaps it is not nessassary to do this, once motorPosition is completed meaning the elevator
			-is on the correct floor then the LED will turn on normally the only case where this'll be a problem is if 
			-I'd want to do something during the elevator moving to a floor i.e change an LED.. or if I press a button...

		Posible Resolve: If I made a muilty treading I can capture both button inputs and set motor values... the main program will create a
			-new tread running the motor and when completed it'll remove the tread, in between the code will allow the button inputs to be read

		Resolve: For now I think I'll just re rid of the while(true) though it'll have a wait(.01) to complete some of it's task	


	Incorperate and test if statusts are able to be used for this program


	Make Fucntion that can navagate though an array


	It'd be cool to add a debuger in witch if a function ever sends or revices a wrong calue it'll report it


	Make sure to add that if a process is going on then dont count safetypro
		- in other words...

		[Temp] Resolve: Added, in safter pro,  if change in encoder values occurs it'll reset the sateryprotimmer
			-Acually it'll reqire a array... I'd rather not relly on that to work yet...

		[Fake] Resolve: Added if UE is at a floor then the saty pro takes effect

		Improvemnts: if UE is somehow global I"ll be able to declar the UE into the saftypro and not just 
			-in the task main () witch is messy 

		Resole: I realized it has to be a global varible explination is not exist


	Button clicks, in witch if a button is held down what'll happen? it should 
		1. not do the saeftyPro() (check)
		2. it should register the click and not half the program

		Therory Resolve: make a function that only allows a button value to be changed when button is pressed "and" relessed completely

		Resolve:


	Always be solving Q&A

		Imposible Resolve: Can't be resolved ;D

Q&A:
	Q: Is SensorType[] nessassary? and what are all the SensorType[] inputs that go into [] i.e sensorTouch for touch sensor
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


	Q:Do arrays work and how could I use them?
	A:


	Q:SensorValue is it SensorValue() or SensorValue[] is S cap or not?
	A:


	Q:If I declar a global varible and I asign a value in a local scope dose it change the golbal vaible
		-value or dose it chnage a local verson of the gloabal varlibe
	A:


	Q:
	A:

*/


//Initialization of some values: 
	//Sensors:
		//Touch sensors

		//SensorType[button1] = sensorTouch;
		//SensorType[button2] = sensorTouch;
		//SensorType[button3] = sensorTouch;
		//SensorType[limitSwitch1] = sensorTouch;
		//SensorType[limitSwitch2] = sensorTouch;
		//SensorType[limitSwitch3] = sensorTouch;


//Global Varibles:
	//Constants:

	//Encoder values for different floors 1, 2, and 3
	int POSITION1 = 20;
	int POSITION2 = 1040;
	int POSITION3 = 1660;

	//Motor Power Maxuim and Minimum (the lowest it'll go, not stall or zero) Absolutly
	int HIGHESTMOTORPOWER = 127;
	int LOWESTMOTORPOWER = 21;

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
		wait(.1);					
		turnLEDOff(lED1);
		turnLEDOff(lED2);
		turnLEDOff(lED3);
		wait(.1);					
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

	// is this nessasary here? Q&A3 positionChange = goalPosition - currentPositionEncoder 

	startMotor(elevatorMotor,advancedMotorPower(positionChange));
	wait(.05);
	
}

void motorLEDInterp(int motorLEDInput){   
	if(motorLEDInput == 10 || motorLEDInput == 11){			//rework this..
		motorPosition(1);
	}else if(motorLEDInput == 20 || motorLEDInput == 22){
		motorPosition(2);
	}else if(motorLEDInput == 33){
		motorPosition(3);
	}else{
		lEDSpam();
	}
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

void safetyPro(){
	if(eButton1 == 0 && eButton2 == 0 && eButton3 == 0 && time1(T1) >= SAFETYPROTIME && (UniversalEvent == 3000 || UniversalEvent == 5000)){
		motorPosition(1);
	}else if(eButton1 != 0 && eButton2 != 0 && eButton3 != 0 ){	
		clearTimer(T1);
	}else if(UniversalEvent == 1000){
		clearTimer(T1);
	}
}

task main(){

	int trigger = 0;
	while(trigger == 1){
		safetyPro();	

	
	}
}