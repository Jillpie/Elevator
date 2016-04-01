#pragma config(Sensor, dgtl1,  limitSwitch1,         sensorTouch)
#pragma config(Sensor, dgtl2,  limitSwitch2,         sensorTouch)
#pragma config(Sensor, dgtl3,  limitSwitchFloor2,    sensorTouch)
#pragma config(Sensor, dgtl4,  limitSwitchFloor3,    sensorTouch)
#pragma config(Sensor, dgtl5,  limitSwitch3,         sensorTouch)
#pragma config(Sensor, dgtl6,  button3,              sensorTouch)
#pragma config(Sensor, dgtl7,  button2,              sensorTouch)
#pragma config(Sensor, dgtl8,  button1,              sensorTouch)
#pragma config(Sensor, dgtl9,  lED3,   				 sensorLEDtoVCC)
#pragma config(Sensor, dgtl10, lED2,                 sensorLEDtoVCC)
#pragma config(Sensor, dgtl11, lED1,                 sensorLEDtoVCC)
#pragma config(Sensor, dgtl12, limitSwitchFloor1,    sensorTouch)
#pragma config(Motor,  port2, elevatorMotor,         tmotorVex393_MC29, openLoop)


/* 
ABSTRACT:
	Elevatorv8c.c is the simple and 3 major attempt useing limit siwtches not encoders and has configureation is most complete of all versions so far and is also commented:
		Go to a floor when button press: YES
		Pause on floor: YES
		Hold button values i.e press all buttons: YES
		Safety: YES
		LED Indecators: YES
BACKGROUND:
	Purpose for the CONFIGURATION is to set up global varlibes for all functions, good pratice
	Purpose for Background is to shorten comments but make them have same content
	The Author of this code would like you to know this code was made over more than 25 hours... and it was fun 
	if a comment is ** it most likely is relavent to one of the requirements
	if a comment has one * then it is very imporant and "more" cool than all the cool code 
	There'll be no comments on the major topics or sections i.e. BACKGROUND
	if there is a - it means its coninuining from the end of the last line of comments for less scolling

	Q&A if you're wondering why I did what I did:
		Q: Why is there only one while statment
			A: the fuctions will be held up by the other while statments and not let the code proceed
				-this is very important because lets say you ahve a fuction or a part of your coe that checks
				-for if a utton is press, if your code is looping a motor to move to a correct spot then
				-the moveing motor means if you press a button during that time your code would not do anything with your button press

	B1: Constant, Configureation type 1 = true, 0 = false.
	B2: Runs code with higher chance of failure but is better
	B3: For the Next set of the same things.
	B4: This comment is for the code()

	Elaborate Explainations:
		Laches: 
			Problem: if you press all buttons only one button value will be saved, elevator gose to that floor
				-then once its done it dosent go to the other floors
			Soulution: Useing laches a button triggered whenever & wherever will trigger and prime the "lach" called 
				-eButton, eButton will stay in the primed position until reset; ulimatly when the elevator reaches a story it'll
				-reset the lach or "eButton" for that floor it reached
			Real-life Connection: In elevators if you pres a button it lights up, in the elevator 
				-if that light is the lach then it knows where its going to go, all the lights lit up
				-when pressed show where its going, and every time it reaches a floor the light turns off
				-when the light turns off then it resets the light back to off, the only way the reset happens is if 
				-it reaches the floor to insure every sotry lit up gets reached...

	*/ 

//CONFIGUREATION:
	//safetyPro 								//short for Safety Protocal
		int elabSPP;							//short for Elaborate Safety Protocal Power
		int ELABORATESAFETYPRO = 1;				//B1 & B2
		int ELABORATESAFETYPROPOWER = 1;		//B1 & B2

	//CONSTANTS:
		//Motor Specifics
			int DIRECTION = 1;					//Changes Spin of motor if incorect, though should be correct as is
			int NORMALMOTORPOWER = 63;			//The default speed everyhting in the program wil lthe the motor value to Unless its running non-elaborate mode.

		//SafetyPro constants 
			int SAFETYPROTIME = 20000;			//**Is the User defined period of nonuse (in milisecounds?)

		//ElevatorPosition
			int eButton1;						//B3, initlizing global ints explained latter...
			int eButton2;
			int eButton3;
			int elevatorPositionPower;			//B3, initlizing global ints explained latter...	
			int goTo;
			int currentDir;
			int ELEVATORSTAYTIME = 5000;		//*Defines the amount of time the Elevator stays on a floor (in miliseounds?)
			int ELEVATORLIFTOFFTIME = 500;		//Defines the time it takes for the elevator to stop triggering a limitswitchfloor limitsiwtch

		//FailSafePro
			int ENABLEFAILSAFEPRO = 1;			//B1, If for some reason elevator is between values undefined (i.e. between 1st and 2ed story) then this will bring it back to the next lower story (i.e 1-2 -> 1, 2-3 -> 2)
			int FAILTIMER = 15000;				//How long it takes for FAILSAFE to activate (in miliseounds?)
			int FAILSAFESAFE = 0;				//B1, safer failsafe, uses a more primitive version of failsafe incase elaborate failsafe fails to safe

//FUNCTIONS:
	void elevatorPosition(){							//The Main Input Logic Output for contolling Elevator

		//Latches (forgot the proper term)		//**Sets up the laches "eButton" Explaind in background 
			if(SensorValue(button1) == 1 || SensorValue(limitSwitch1) == 1){	//B3, if call button or floor button is pressed then lach is set 
				eButton1 = 1;
			}
			if(SensorValue(button2) == 1 || SensorValue(limitSwitch2) == 1){
				eButton2 = 1;
			}
			if(SensorValue(button3) == 1 || SensorValue(limitSwitch3) == 1){
				eButton3 = 1;
			}
			if(SensorValue(limitSwitchFloor1) == 1){
				eButton1 = 0;
			}
			if(SensorValue(limitSwitchFloor2) == 1){
				eButton2 = 0;
			}
			if(SensorValue(limitSwitchFloor3) == 1){
				eButton3 = 0;
			}

		//currentDir 							//*Accounts for diffnert directions, allows i.e if you are going to 3rd from 1st and press 2 before reached 2ed sotry then it'll stop at 2ed story before thrid 
			if(SensorValue(limitSwitchFloor1) == 1){		//assigns currentDir = 1 if elevator is on first story 
				currentDir = 1;
			}else if(SensorValue(limitSwitchFloor2) == 1){	
				currentDir = 2;
			}else if(SensorValue(limitSwitchFloor3) == 1){	//if it wasnt on 1st or 2st it checks thrid
				currentDir = 3;
			}else if(goTo == 3){							//if its not on any stry it know and only care if its going some place either 1 -> 3 or 3 -> 1 
				currentDir = 8;
			}else if(goTo == 1){							//Like above, if its going to floor 1 it can be 2->1 or 3-> 1 and such we can asume it could be between 1-2 or 2-3 such that this dir is useful for us
				currentDir = 9;
			}												//dosent need an else to reset currentDir to 0 because if it reaches a floor (its goal is to reach a floor) then it sets it to a floor value

		//Interpertaion of button pressess		//**Main routing and computing of inputs to fromulat an output
			if(SensorValue(limitSwitchFloor1) == 1){		//B3 Generally First it checks if its on a floor 1,2,3
				if(eButton2 == 1){							//Lets say it on floor one, Next it checks for a ebutton2 or 3 withc means if button 2 or 3 was pressed 
					goTo = 12;								//if button 2 was pressd it sets goTo to 12 witch means elevator go to sotry 2 from sotry 1	
				}											//thechially both ebutton2 and 3 could have been triggered in that case this part of the fuction is useless (its explained latter)
				if(eButton3 == 1){
					goTo = 3;
				}
			}
			if(SensorValue(limitSwitchFloor2) == 1){
				if(eButton1 == 1){
					goTo = 1;
				}
				if(eButton3 == 1){
					goTo = 3;
				}
			}
			if(SensorValue(limitSwitchFloor3) == 1){
				if(eButton2 == 1){
					goTo = 32;								//32 just means from story 3 goign to 2 
				}
				if(eButton1 == 1){
					goTo = 1;
				}
			}
			if(currentDir == 8 && eButton2 == 1 && SensorValue(limitSwitchFloor2) == 1){	//**(this is explained latter): so this says if elevator is going from 1 -> 3,meaning button 3 was pressed, and then button 2 was pressed it'll make sure to stop at floor 2 if its between 1->2 before geting to 3
				goTo = 12;
			}
			if(currentDir == 9 && eButton2 == 1 && SensorValue(limitSwitchFloor2) == 1){	//same concept expect going down, so you're thinking maybe "oh how dose it know to stil lgo to three once it stops at 2?" well using ebutton laches the lach hasnt reset due to it not reaching the floor yet so its all fail safe.
				goTo = 32;																	//It's miss leading if you think about it it says from 3 go to 2 and you might think the quesion one line above this line 
			}

		//Asignments to motor vectors			//**Main Routing of computing inputs to now setting outputs
			if(goTo == 1){														//**B3 Interpertaion of Button PRessess gave us goTo values, now we'll be useing them to decide the outputs
				elevatorPositionPower = (-1 * DIRECTION * NORMALMOTORPOWER);	//if goto == 1 that means go to floor 1 (from either 2 or 3 )so that menas we're goign down in such we havea negitive direction at the power of NORMALPOWER

				if(SensorValue(limitSwitchFloor1) == 1){						//goto was also a lach... this is the reset for the goto lach, once it reaches its goal of floor one it'll hit a swich on floor one indecating the goto is no longer nessary 
					goTo = 0;
				}
			}
			if(goTo == 12){
				elevatorPositionPower = (DIRECTION * NORMALMOTORPOWER);

				if(SensorValue(limitSwitchFloor2) == 1){
					goTo = 0;
				}
			}
			if(goTo == 32){
				elevatorPositionPower = (-1 * DIRECTION * NORMALMOTORPOWER);

				if(SensorValue(limitSwitchFloor2) == 1){
					goTo = 0;
				}
			}
			if(goTo == 3){
				elevatorPositionPower = (DIRECTION * NORMALMOTORPOWER);

				if(SensorValue(limitSwitchFloor3) == 1){
					goTo = 0;
				}
			}
			if(goTo == 0){										//if a goto got reset this makes the "resset" value of a goto to be no movement on the motor...
				elevatorPositionPower = 0;
			}

		//Pauseing at a floor 					//**Without this the elevator will go to a floor and leave to go to the next one...
		//	if((SensorValue(limitSwitchFloor1)  == 1 || SensorValue(limitSwitchFloor1)  == 1 || SensorValue(limitSwitchFloor1)  == 1) && time1(T3) >= ELEVATORSTAYTIME){
		//		clearTimer(T3);					//**B4(Above), Says if the elevator is on any floor and the time the elevator gets to stay on a floor is over then clear the clocks
		//		clearTimer(T4);
		//	}else{
		//		elevatorPositionPower = 0;
		//	}

		//Acually run the motor
			
	}

	void lEDIndicator(){
		if(SensorValue(limitSwitchFloor1) == 1){
			turnLEDOn(lED1);
		}else{
			turnLEDOff(lED1);
		}
		if(SensorValue(limitSwitchFloor2) == 1){
			turnLEDOn(lED2);
		}else{
			turnLEDOff(lED2);
		}
		if(SensorValue(limitSwitchFloor3) == 1){
			turnLEDOn(lED3);
		}else{
			turnLEDOff(lED3);
		}
	}

	void safetyPro(){
		if((SensorValue(button1) == 0 || SensorValue(button2) == 0 || SensorValue(button3) == 0 || SensorValue(limitSwitch2) == 0 || SensorValue(limitSwitch3) == 0 || SensorValue(limitSwitch1) == 0) && SensorValue(limitSwitchFloor1) == 0 ){
			if(time1(T1) >= SAFETYPROTIME){
				if(ELABORATESAFETYPROPOWER == 1){
					elabSPP = (-1 * DIRECTION * NORMALMOTORPOWER);
					startMotor(elevatorMotor,elabSPP);
				}else{
					startMotor(elevatorMotor,-63);
				}
			}
		}else{
			clearTimer(T1);
		}
	}

	void failSafePro(){
		if(SensorValue(limitSwitchFloor1) == 0 && SensorValue(limitSwitchFloor2) == 0 && SensorValue(limitSwitchFloor3) == 0 && time1(T2) >= FAILTIMER){
			if(FAILSAFESAFE == 1){
				startMotor(elevatorMotor, -63);
			}else{
				startMotor(elevatorMotor,(-DIRECTION * NORMALMOTORPOWER));
			}
		}else{
			clearTimer(T2);
		}
	}


//MAIN:
	task main(){
		while(true){
			lEDIndicator();
			//safetyPro();
			failSafePro();

			elevatorPosition();

			startMotor(elevatorMotor,elevatorPositionPower);
		}
	}