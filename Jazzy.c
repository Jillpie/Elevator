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

task main(){
	while(1==1){
//Elevator on Floor 3//
		while(SensorValue(limit)==1){
			untilTouch(floor1);
			startMotor(elevator,-60);
			untilSonarLessThan(8,sonar);
			stopMotor(elevator);
		}
		while(SensorValue(sonar)>18){
			untilTouch(floor2);
			startMotor(elevator,-60);
			untilSonarLessThan(16,sonar);
			stopMotor(elevator);
		}
		//Elevator on Floor 1//
		while(SensorValue(quad)<299){
			untilTouch(floor3);
			startMotor(elevator,127);
			untilTouch(limit);
			stopMotor(elevator);
		}
		while(SensorValue(sonar)<12){
			untilTouch(floor2);
			startMotor(elevator,127);
			untilSonarGreaterThan(12,sonar);
			stopMotor(elevator);
		}
	}
}
