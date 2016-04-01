#pragma config(Sensor, dgtl1,  limitSwitch1,   sensorTouch)
#pragma config(Sensor, dgtl2,  limitSwitch2,   sensorTouch)
#pragma config(Sensor, dgtl3,  encoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  limitSwitch3,    sensorTouch)
#pragma config(Sensor, dgtl6,  button3,        sensorTouch)
#pragma config(Sensor, dgtl7,  button2,        sensorTouch)
#pragma config(Sensor, dgtl8,  button1,        sensorTouch)
#pragma config(Sensor, dgtl11, lED3,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl10, lED2,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl9, lED1,           sensorLEDtoVCC)
#pragma config(Motor,  port2, elevatorMotor,         tmotorVex393_MC29, openLoop)

task main(){
 //add code for wait timer going to first floor
 //turn led1 on because its on the first floor
while(1==1)
 turnLEDoff(lED1)
 turnLEDoff(lED2)
 turnLEDoff(lED3)

{//when button is pressed and elevator is on first floor
 if(sensorValue(sensorQuadEncoder<8)==1) 
 {
  if(sensorValue(button2)==1)  //if button 2 is pressed
   startMotor(elevator,60);
   untilSonarGreaterThan(9,sonar) && untilSonarLessThan(16,sonar);
   stopMotor(elevator);
   turnLEDOn(lED2);
  }
  else
  {
   if(sensorValue(button3)==1)
   startMotor(elevator,60);
   untilSonarGreaterThan(16,sonar);
   stopMotor(elevator);
   turnLEDOn(lED3);
  }
}

{//when button is pressed and elevator is on second floor
 if(sensorValue(sensorQuadEncoder<16)==1) && (sensorValue(sensorQuadEncoder<8)==1)
 {
  if(sensorValue(button1)==1)
   startMotor(elevator,60);
   untilSonarLessThan(8,sonar);
   stopMotor(elevator);
   turnLEDOn(lED1);
  }
  else
  {
   if(sensorValue(button3)==1)
   startMotor(elevator,60);
   untilSonarGreaterThan(16,sonar);
   stopMotor(elevator);
   turnLEDOn(lED3);
  }
}
{//when button is pressed and elevator is on third floor
 if(sensorValue(sensorQuadEncoder<16)==1)
 {
  if(sensorValue(button2)==1)
   startMotor(elevator,60);
   untilSonarGreaterThan(9,sonar) && untilSonarLessThan(16,sonar);
   stopMotor(elevator);
   turnLEDOn(lED2);
  }
  else
  {
   if(sensorValue(button1)==1)
   startMotor(elevator,60);
   untilSonarLessThan(8,sonar);
   stopMotor(elevator);
   turnLEDOn(lED1);
  }

{//when limitswitch is pressed and elevator is on first floor
 if(sensorValue(sensorQuadEncoder<8)==1) 
 {
  if(sensorValue(limitSwitch2)==1)  //if limitswitch 2 is pressed
   startMotor(elevator,60);
   untilSonarGreaterThan(9,sonar) && untilSonarLessThan(16,sonar);
   stopMotor(elevator);
   turnLEDOn(lED2);
  }
  else
  {
   if(sensorValue(limitSwitch3)==1)  //if limitswitch 3 is pressed
   startMotor(elevator,60);
   untilSonarGreaterThan(16,sonar);
   stopMotor(elevator);
   turnLEDOn(lED3);
  }
}

{//when limitswitch is pressed and elevator is on second floor
 if(sensorValue(sensorQuadEncoder<16)==1) && (sensorValue(sensorQuadEncoder<8)==1)
 {
  if(sensorValue(limitSwitch1)==1)  //if limitswitch 1 is pressed
   startMotor(elevator,60);
   untilSonarLessThan(8,sonar);
   stopMotor(elevator);
   turnLEDOn(lED1);
  }
  else
  {
   if(sensorValue(limitSwitch3)==1)  //if limitswitch 3 is pressed
   startMotor(elevator,60);
   untilSonarGreaterThan(16,sonar);
   stopMotor(elevator);
   turnLEDOn(lED3);
  }
}
{//when limitswitch is pressed and elevator is on third floor
 if(sensorValue(sensorQuadEncoder<16)==1)
 {
  if(sensorValue(limitSwitch2)==1)  //if limitswitch 2 is pressed
   startMotor(elevator,60);
   untilSonarGreaterThan(9,sonar) && untilSonarLessThan(16,sonar);
   stopMotor(elevator);
   turnLEDOn(lED2);
  }
  else
  {
   if(sensorValue(limitSwitch1)==1)  //if limitswitch 1 is pressed
   startMotor(elevator,60);
   untilSonarLessThan(8,sonar);
   stopMotor(elevator);
   turnLEDOn(lED1);
  }

}
}
}