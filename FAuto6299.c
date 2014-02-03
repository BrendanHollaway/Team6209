#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     irSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     motorFR,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorBR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorFL,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorManipulatorLift, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorFlagSpinner, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S2_C1_1,     motorArm,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    servoManip,           tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servoL,               tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Start the robot
void initializeRobot(){
	return;
	}

void setWheels(int fl, int bl, int fr, int br){
	motor[motorFL] = fl;
	motor[motorBL] = bl;
	motor[motorFR] = fr;
	motor[motorBR] = br;
}

// Retrieve the joystick values from the joystick
#include "JoystickDriver.c"

void wheelStop(){
	setWheels(0,0,0,0);
	wait10Msec(25);
	return;
}

void wheelStop(int t){
	setWheels(0,0,0,0);
	wait10Msec(t);
	return;
}


// Takes two parameters: int m, which is the value which the motorEncoder is supposed to run until, and float turn,
// which determines whether the robot is turning right, left, or not turning(going forward or backwards)
void wheelEncoder(int m, float turn){
	if(turn == 0){
		if(m > 0){
			while(nMotorEncoder[motorFL] < m){
				setWheels(-40,-40,-40,-40);
				}
			}
		else{
			while(nMotorEncoder[motorFL] > m){
				setWheels(40,40,40,40);
				}
			}
		} // end of turn==0

	else if(turn == .5){
		while(nMotorEncoder[motorFL] > -m){
			setWheels(-45,-45,45,45);
			}
		}
	else if(turn == -.5){
		while(nMotorEncoder[motorFL] < m){
			setWheels(45,45,-45,-45);
			}
		}
	return;
}

void wheelEncoder(int m, float turn, int turnSpeed){
	if(turn == 0){
		if(m > 0){
			while(nMotorEncoder[motorFL] < m){
				setWheels(-turnSpeed,-turnSpeed,-turnSpeed,-turnSpeed);
				}
			}
		else{
			while(nMotorEncoder[motorFL] > m){
				setWheels(turnSpeed,turnSpeed,turnSpeed,turnSpeed);
				}
			}
		} // end of turn==0

	else if(turn == .5){
		while(nMotorEncoder[motorFL] > -m){
			setWheels(-turnSpeed,-turnSpeed,turnSpeed,turnSpeed);
			}
		}
	else if(turn == -.5){
		while(nMotorEncoder[motorFL] < m){
			setWheels(turnSpeed,turnSpeed,-turnSpeed,-turnSpeed);
			}
		}
	return;
}

//==================Task Main=====================================================
// Move the robot to the basket above the IR beacon
// and then score into that basket.
// Then move onto the ramp
task main()
{
	initializeRobot();
	//waitForStart();

	bool lift = false;
	nMotorEncoder[motorManipulatorLift] = 0;

	while ((nMotorEncoder[motorManipulatorLift] < 5200)){
		motor[motorManipulatorLift] = 100;
	}

	motor[motorManipulatorLift] = 0;
	//wait10Msec(400);
	nMotorEncoder[motorFL] = 0;

	wheelEncoder(1390, 0);

	nMotorEncoder[motorFL] = 0;
	wheelStop(45);

	wheelEncoder(690, -.5); // ADJUST THIS

	wheelStop(45);

	nMotorEncoder[motorFL] = 0;

	while(SensorValue[irSeeker]!=5){
		setWheels(-40,-40,-40,-40);
	}

	wheelStop(45);
	int back = 0;
	if (nMotorEncoder[motorFL] < 1000 && nMotorEncoder[motorFL] > 90)
		back = nMotorEncoder[motorFL] + 900;
	else
		back = nMotorEncoder[motorFL] + 370;

	wheelEncoder(back, 0);

	wheelStop(45);
	lift = true;

	wait10Msec(25);
	servo[servoManip] = 0;

	wheelStop(45);
	wait10Msec(50);

	wheelEncoder(0, 0); // go back to first basket

	nMotorEncoder[motorFL] = 0;
	wheelStop();



	wheelEncoder(-1050, 0, 100); //Go back

	nMotorEncoder[motorFL] = 0;
	wheelStop();
	while((nMotorEncoder[motorManipulatorLift] > 110)){
		motor[motorManipulatorLift] = -100;
	}
		motor[motorManipulatorLift] = 0;
	wait10Msec(50);
	wheelEncoder(1850, .5, 100);  //TURN TWO

	nMotorEncoder[motorFL] = 0;
	wheelStop();

	wheelEncoder(2550, 0, 100);

	nMotorEncoder[motorFL] = 0;
	wheelStop();

	wheelEncoder(750, -.5, 100);

	nMotorEncoder[motorFL] = 0;
	wheelStop();

	wheelEncoder(1850, 0, 100); //GOES FORWARD

	nMotorEncoder[motorFL] = 0;
	//wheelStop();


	wheelEncoder(1250, -.5, 100); //turn
	nMotorEncoder[motorFL] = 0;
	//wheelStop();

	wheelEncoder(4800, 0, 100); //GOES FORWARD

	nMotorEncoder[motorFL] = 0;
	//wheelStop();

	servo[servoManip] = 180;
	wait10Msec(50);
}
