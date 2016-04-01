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

	//Varibles:

	int UniversalEvent;

	int eButton1 = SensorValue[button1] + SensorValue[limitSwitch1];
	int eButton2 = SensorValue[button2] + SensorValue[limitSwitch2];
	int eButton3 = SensorValue[button3] + SensorValue[limitSwitch3];

	//Arrays:
	int sArray[48][4] = {
		{1,1000,1000,00},
		{2,1100,1000,00},
		{3,1200,2200,00},
		{4,1300,2300,00},
		//{,,,},
		{5,2100,1000,11},
		{6,2200,3000,22},
		{7,2300,3300,20},
		//{,,,},
		{8,3000,3000,00},
		{9,3100,2100,00},
		{10,3200,3000,00},
		{11,3300,4300,00},
		//{,,,},
		{12,4100,3100,20},
		{13,4200,3000,22},
		{14,4300,5000,33},
		//{,,,},
		{15,5000,5000,00},
		{16,5100,4100,00},
		{17,5200,4200,00},
		{18,5300,5000,00},
		//{,,,},
		//{,,,},
		{19,1230,2230,00},
		{20,1320,2230,00},
		//{,,,},
		{21,2120,1200,11},
		{22,2130,1300,11},
		{23,2210,3100,22},
		{24,2230,3300,22},
		{25,2310,3310,20},
		{26,2320,3300,22},
		//{,,,},
		{27,3130,2130,00},
		{28,3310,4310,00},
		//{,,,},
		{29,4120,3100,22},
		{30,4130,3130,20},
		{31,4210,3100,22},
		{32,4230,3300,22},
		{33,4310,5100,33},
		{34,4320,5200,33},
		//{,,,},
		{35,5120,4210,00},
		{36,5210,4210,00},
		//{,,,},
		//{,,,},
		{37,2123,1230,11},
		{38,2132,1320,11},
		{39,2213,3130,22},
		{40,2231,3310,22},
		{41,2312,3310,22},
		{42,2321,3310,22},
		//{,,,},
		{43,4123,3130,22},
		{44,4132,3130,22},
		{45,4213,3130,22},
		{46,4231,3310,22},
		{47,4312,5120,33},
		{48,4321,5210,33}
	};

	//If ^that up tehre dosent work use this:
	/*
		sArray[1][1] = 1;	sArray[1][2] = 1000;	sArray[1][3] = 1000;	sArray[1][4] = 00;
		sArray[2][1] = 2;	sArray[2][2] = 1100;	sArray[2][3] = 1000;	sArray[2][4] = 00;
		sArray[3][1] = 3;	sArray[3][2] = 1200;	sArray[3][3] = 2200;	sArray[3][4] = 00;
		sArray[4][1] = 4;	sArray[4][2] = 1300;	sArray[4][3] = 2300;	sArray[4][4] = 00;
		sArray[5][1] = 5;	sArray[5][2] = 2100;	sArray[5][3] = 1000;	sArray[5][4] = 11;
		sArray[6][1] = 6;	sArray[6][2] = 2200;	sArray[6][3] = 3000;	sArray[6][4] = 22;
		sArray[7][1] = 7;	sArray[7][2] = 2300;	sArray[7][3] = 3300;	sArray[7][4] = 20;
		sArray[8][1] = 8;	sArray[8][2] = 3000;	sArray[8][3] = 3000;	sArray[8][4] = 00;
		sArray[9][1] = 9;	sArray[9][2] = 3100;	sArray[9][3] = 2100;	sArray[9][4] = 00;
		sArray[10][1] = 10;	sArray[10][2] = 3200;	sArray[10][3] = 3000;	sArray[10][4] = 00;
		sArray[11][1] = 11;	sArray[11][2] = 3300;	sArray[11][3] = 4300;	sArray[11][4] = 00;
		sArray[12][1] = 12;	sArray[12][2] = 4100;	sArray[12][3] = 3100;	sArray[12][4] = 20;
		sArray[13][1] = 13;	sArray[13][2] = 4200;	sArray[13][3] = 3000;	sArray[13][4] = 22;
		sArray[14][1] = 14;	sArray[14][2] = 4300;	sArray[14][3] = 5000;	sArray[14][4] = 33;
		sArray[15][1] = 15;	sArray[15][2] = 5000;	sArray[15][3] = 5000;	sArray[15][4] = 00;
		sArray[16][1] = 16;	sArray[16][2] = 5100;	sArray[16][3] = 4100;	sArray[16][4] = 00;
		sArray[17][1] = 17;	sArray[17][2] = 5200;	sArray[17][3] = 4200;	sArray[17][4] = 00;
		sArray[18][1] = 18;	sArray[18][2] = 5300;	sArray[18][3] = 5000;	sArray[18][4] = 00;
		sArray[19][1] = 19;	sArray[19][2] = 1230;	sArray[19][3] = 2230;	sArray[19][4] = 00;
		sArray[20][1] = 20;	sArray[20][2] = 1320;	sArray[20][3] = 2230;	sArray[20][4] = 00;
		sArray[21][1] = 21;	sArray[21][2] = 2120;	sArray[21][3] = 1200;	sArray[21][4] = 11;
		sArray[22][1] = 22;	sArray[22][2] = 2130;	sArray[22][3] = 1300;	sArray[22][4] = 11;
		sArray[23][1] = 23;	sArray[23][2] = 2210;	sArray[23][3] = 3100;	sArray[23][4] = 22;
		sArray[24][1] = 24;	sArray[24][2] = 2230;	sArray[24][3] = 3300;	sArray[24][4] = 22;
		sArray[25][1] = 25;	sArray[25][2] = 2310;	sArray[25][3] = 3310;	sArray[25][4] = 20;
		sArray[26][1] = 26;	sArray[26][2] = 2320;	sArray[26][3] = 3300;	sArray[26][4] = 22;
		sArray[27][1] = 27;	sArray[27][2] = 3130;	sArray[27][3] = 2130;	sArray[27][4] = 00;
		sArray[28][1] = 28;	sArray[28][2] = 3310;	sArray[28][3] = 4310;	sArray[28][4] = 00;
		sArray[29][1] = 29;	sArray[29][2] = 4120;	sArray[29][3] = 3100;	sArray[29][4] = 22;
		sArray[30][1] = 30;	sArray[30][2] = 4130;	sArray[30][3] = 3130;	sArray[30][4] = 20;
		sArray[31][1] = 31;	sArray[31][2] = 4210;	sArray[31][3] = 3100;	sArray[31][4] = 22;
		sArray[32][1] = 32;	sArray[32][2] = 4230;	sArray[32][3] = 3300;	sArray[32][4] = 22;
		sArray[33][1] = 33;	sArray[33][2] = 4310;	sArray[33][3] = 5100;	sArray[33][4] = 33;
		sArray[34][1] = 34;	sArray[34][2] = 4320;	sArray[34][3] = 5200;	sArray[34][4] = 33;
		sArray[35][1] = 35;	sArray[35][2] = 5120;	sArray[35][3] = 4210;	sArray[35][4] = 00;
		sArray[36][1] = 36;	sArray[36][2] = 5210;	sArray[36][3] = 4210;	sArray[36][4] = 00;
		sArray[37][1] = 37;	sArray[37][2] = 2123;	sArray[37][3] = 1230;	sArray[37][4] = 11;
		sArray[38][1] = 38;	sArray[38][2] = 2132;	sArray[38][3] = 1320;	sArray[38][4] = 11;
		sArray[39][1] = 39;	sArray[39][2] = 2213;	sArray[39][3] = 3130;	sArray[39][4] = 22;
		sArray[40][1] = 40;	sArray[40][2] = 2231;	sArray[40][3] = 3310;	sArray[40][4] = 22;
		sArray[41][1] = 41;	sArray[41][2] = 2312;	sArray[41][3] = 3310;	sArray[41][4] = 22;
		sArray[42][1] = 42;	sArray[42][2] = 2321;	sArray[42][3] = 3310;	sArray[42][4] = 22;
		sArray[43][1] = 43;	sArray[43][2] = 4123;	sArray[43][3] = 3130;	sArray[43][4] = 22;
		sArray[44][1] = 44;	sArray[44][2] = 4132;	sArray[44][3] = 3130;	sArray[44][4] = 22;
		sArray[45][1] = 45;	sArray[45][2] = 4213;	sArray[45][3] = 3130;	sArray[45][4] = 22;
		sArray[46][1] = 46;	sArray[46][2] = 4231;	sArray[46][3] = 3310;	sArray[46][4] = 22;
		sArray[47][1] = 47;	sArray[47][2] = 4312;	sArray[47][3] = 5120;	sArray[47][4] = 33;
		sArray[48][1] = 48;	sArray[48][2] = 4321;	sArray[48][3] = 5210;	sArray[48][4] = 33;
	*/
	/*
	Useage of sArray:

	int sArray[48][4] = {
		{row number, name, where it's going, What it's doing},
		{1, 1000,1000,00}... [Meainging that it's on floor 1 going to name 1000 (itself) without changeing LED or Motor]
	};

	*/

	/*
	int arrayExample[4][4] = {
		{0,1,2,3},
		{0,1,2,3},
		{0,1,2,3},
		{0,1,2,3}
	};
*/

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

//Array Navagation Set

int sArrayFind(){

}

int sArrayExtract(){

}

task main(){
	while(true){
		safetyPro();	

	
	}
}