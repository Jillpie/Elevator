#pragma config(Sensor, dgtl1,  limitSwitch1,   sensorTouch)
#pragma config(Sensor, dgtl2,  limitSwitch2,   sensorTouch)
#pragma config(Sensor, dgtl5,  limitSwitch3,    sensorTouch)
#pragma config(Sensor, dgtl6,  button3,        sensorTouch)
#pragma config(Sensor, dgtl7,  button2,        sensorTouch)
#pragma config(Sensor, dgtl8,  button1,        sensorTouch)
#pragma config(Sensor, dgtl11, red,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl10, yellow,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl9, green,           sensorLEDtoVCC)
#pragma config(Servo,  srvo_S1_C2_1,    rightServo,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_1,    leftServo,               tServoStandard)

task main()
{
 ClearTimer(T1);

while(1==1)
{
 if(time10[T1] == 1000)                 //if the timer hits 10 seconds
{ turnLEDOff(green);
 turnLEDOff(red);
 turnLEDOff(yellow);            //reset the leds
 setServo(rightServo, 60);  
 setServo(leftServo, -60);            //bottom position
 turnLEDOn(green);                     //turn on green led

}

if(SensorValue(limitSwitch1)==1)  //if limitswitch one pressed
 {
 ClearTimer(T1);                  //set timer to 0
 turnLEDOff(green);
 turnLEDOff(red);
 turnLEDOff(yellow);        //reset leds
 setServo(rightServo, 60);  
 setServo(leftServo, -60);         // set to bottom position
 turnLEDOn(green);                  //turn on green led

}
if(SensorValue(button1)==1)
 {
 ClearTimer(T1);                  //set timer to 0
 turnLEDOff(green);
 turnLEDOff(red);
 turnLEDOff(yellow);        //reset leds
 setServo(rightServo, 60);  
 setServo(leftServo, -60);         // set to bottom position
 turnLEDOn(green);                  //turn on green led

}
if(SensorValue(limitSwitch2)==1)
 {
 ClearTimer(T1);                  //set timer to 0
 turnLEDOff(green);
 turnLEDOff(red);
 turnLEDOff(yellow);        //reset leds
 setServo(rightServo, 0);     //set position to middle
 setServo(leftServo, 0);
turnLEDOn(yellow);                       //turn on yellow led
}
if(SensorValue(button2)==1)
 {
 ClearTimer(T1);                  //set timer to 0
 turnLEDOff(green);
 turnLEDOff(red);
 turnLEDOff(yellow);        //reset leds
 setServo(rightServo, 0);     //set position to middle
 setServo(leftServo, 0);
turnLEDOn(yellow);                        //turn on yellow led
}
if(SensorValue(limitSwitch3)==1)
 {
 ClearTimer(T1);                  //set timer to 0
 turnLEDOff(green);
 turnLEDOff(red);
 turnLEDOff(yellow);        //reset leds
 setServo(rightServo, -60);    //set to top position
 setServo(leftServo, 60);
turnLEDOn(red);                            //turn on red led
}
if(SensorValue(button3)==1)
  {
 ClearTimer(T1);                  //set timer to 0
 turnLEDOff(green);
 turnLEDOff(red);
 turnLEDOff(yellow);        //reset leds
 setServo(rightServo, -60);    //set to top position
 setServo(leftServo, 60);
turnLEDOn(red);                             //turn on red led

}

}
}