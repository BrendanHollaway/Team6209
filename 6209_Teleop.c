#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     LightSensor,    sensorLightActive)
#pragma config(Sensor, S4,     irSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     motorFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorFL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motorBL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     motorManipulatorLift, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorFlagSpinner, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_1,     motorPickUp,   tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_2,     motorPullUp,   tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    servoStopper,         tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    doubleLift,           tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Retrieve data from the controller.
#include "JoystickDriver.c"

// Initialize the Robot.
void initializeRobot(){
	servo[servoStopper] = 180;
	return;
	}

//========================= Drive control functions ========================================================================================================

//All features are mapped to Controller 1.
//Left Joystick (1)  - Controls the left wheels of the tank drive.
//Right Joystick (2) - Controls the right wheels of the tank drive.

//================ Drive control functions- Task driveControl ==============================================================================================

//Task driveControl() controls the tank driving system by reading the y value given off by
//the left and right joystick on the first controller. Task driveControl() then assigns
//power to their corresponding motors.
//There are four different motors used in this task.
//The Left Joystick controls MotorFL and MotorFR.
//--- MotorFL = The motor that controls the Front Left Wheel.
//--- MotorFR = The motor that controls the Front Right Wheel.
//The Right Joystick controls MotorBL and MotorBR.
//--- MotorBL = The motor that controls the Back Left Wheel.
//--- MotorBR = The motor that controls the Back Right Wheel.
task driveControl(){

	//Create a variable named threshold that will prevent the motors from recieving power
	//due to erroneous Jostick readings that are greater than 0.
	int threshold = 7;

	//Create a variable named negThreshold that will prevent the motors from recieving power
	//due to erroneous Jostick readings that are less than 0.
	int negThreshold = -7;

	//Create a variable named powerScaling that is used to scale the power that is distributed to the motors.
	float powerScaling = 0.8;

	//Create a variable named turnPowerScaling that isused to scale
	//the power that is distributed to the motors while turning.
	float turnPowerScaling = 0.6;

	//Continuously obtain the joystick settings and set them equal to their respective motor's power.
	while(true){

		//Obtain the values given by the joysticks.
		getJoystickSettings(joystick);

		//If only the left joystick is manipulated, distribute power to the two left motors.
		if(abs(joystick.joy1_y1) > threshold && abs(joystick.joy1_y2) < threshold ){
			motor [motorFL] = (joystick.joy1_y1 * powerScaling);
			motor [motorBL] = (joystick.joy1_y1 * powerScaling);
		}

		//If only the right joystick is manipulated, distribute power to the two right motors.
		else if(abs(joystick.joy1_y2) > threshold && abs(joystick.joy1_y1) < threshold ){
			motor [motorFR] = (joystick.joy1_y2 * powerScaling);
			motor [motorBR] = (joystick.joy1_y2 * powerScaling);
		}

		//If both joysticks are pressed in the same direction, distribute power to all four motors.
		else if(joystick.joy1_y2 > threshold && joystick.joy1_y1 > threshold || joystick.joy1_y2 < threshold && joystick.joy1_y1 < threshold ){
			motor [motorFR] = (joystick.joy1_y1 * powerScaling);
			motor [motorBR] = (joystick.joy1_y1 * powerScaling);
			motor [motorFL] = (joystick.joy1_y2 * powerScaling);
			motor [motorBL] = (joystick.joy1_y2 * powerScaling);
		}

		//If both joysticks are pressed in opposite directions, give power to all four motors, used to turn the robot.
		else if(((joystick.joy1_y1 > threshold) && (joystick.joy1_y2 < negThreshold)) || ((joystick.joy1_y2 > threshold) && (joystick.joy1_y1 < negThreshold))) {
			motor [motorFL] = (joystick.joy1_y1 * turnPowerScaling);
			motor [motorBL] = (joystick.joy1_y1 * turnPowerScaling);
			motor [motorFR] = (joystick.joy1_y2 * turnPowerScaling);
			motor [motorBR] = (joystick.joy1_y2 * turnPowerScaling);
		}

		//If the joysticks are not being manipulated, set all the motors to 0 power.
		else {
			motor [motorFL] = (0);
			motor [motorBL] = (0);
			motor [motorFR] = (0);
			motor [motorBR] = (0);
		}

		// Add a wait of 7 Milliseconds to the code in order to reduce latency.
		wait1Msec(10);

	  } //End of while loop.

	} //End of task driveControl().
//================================================ Task Arm Control =========================================================================================
//Task Arm Control controls the raising of the block manipulator
//by reading the values of the left joystick on controller two.
//===========================================================================================================================================================
task armControl(){

	//Create a variable named threshold that will prevent the motors from recieving power
	//due to erroneous Jostick readings that are less than 7.
	int threshold = 7;

	//Create a variable named threshold that will prevent the motors from recieving power
	//due to erroneous Jostick readings that are greater than -7.
  //int negThreshold = -7;


	//Create a variable named powerScaling that is used to scale the power that is distributed to the motors.
	float powerScaling = 0.85;



	//Sets the motor Lift to the value of 1, so that we know when it is at the bottom.

	//Continously obtain the joystick settings and set them equal to their respective motor's power.
	while(true){

		getJoystickSettings(joystick);

		//When the right joystick on the second controller is manipulated, set the
		//motor on the block manipulator lift to the value of the right joystick.
					if(abs(joystick.joy2_y1) > threshold){
						motor[motorManipulatorLift] = (joystick.joy2_y1);
				} // End of if(joystick > threshold)

				else{
					motor[motorManipulatorLift] = 0;
				}

		//else if(joystick.joy2_y1 < negThreshold){
				//motor[motorManipulatorLift] = (joystick.joy2_y1);
		//} // End of else if(joystick < negThreshold)

		//Sets the motor to 0 if nothing is pressed

		//If button 6 is pressed, set motorArm to full power
		if(joy1Btn(6)==true){
			motor [motorPickUp] = 100;
		} //End of if(joy1Btn(7))

		//If button 5 is pressed, set the motorArm to full reverse
		else if(joy1Btn(5)==true){
			motor [motorPickUp] = -100;
		} //End of else if(joy1Btn(8))

		else{
			motor[motorPickUp] = 0;
		}

		if(joy2Btn(1) == true){
			servo[servoStopper] = 180;
		}
		else if(joy2Btn(3) == true){
			servo[servoStopper] = 0;
		}

		// Add a wait of 10 Milliseconds to the code in order to reduce latency.
		wait1Msec(10);

		}//End of while loop.

}// End of task Arm Control.


//================\============= Task Flag Control ===========================================================================================================
//Task Flag Control controls the raising of the flagSpinner
//by reading the press of button 1 on controller 2.
//Task Flag Control controls the spinning of the flagSpinner
//by reading the press of button 2 on controller 2.
//Task Flag Control controls motorFlagLift and motorFlagSpinner
//---motorFlagLift= The motor that raises the elevator, which raises the flagSpinner
//---motorFLagSpinner= The motor that spins the flagSpinner, which raises the flag to its maximum height.
//===========================================================================================================================================================
task trainingwheels(){

	//Create a variable named threshold that will prevent the motors from recieving power
	//due to erroneous Jostick readings that are less than 7.
	int threshold = 7;

	//Create a variable named threshold that will prevent the motors from recieving power
	//due to erroneous Jostick readings that are greater than -7.
  //int negThreshold = -7;


	//Create a variable named powerScaling that is used to scale the power that is distributed to the motors.
	float powerScaling = 0.85;



	//Sets the motor Lift to the value of 1, so that we know when it is at the bottom.

	//Continously obtain the joystick settings and set them equal to their respective motor's power.
	while(true){

		getJoystickSettings(joystick);

				if(joystick.joy2_y1 > threshold && nMotorEncoder[motorManipulatorLift] < 6000){
						motor[motorManipulatorLift] = (joystick.joy2_y1);
				} // End of if(joystick > threshold)

				else if(joystick.joy2_y1 <  -threshold && nMotorEncoder[motorManipulatorLift] > 750){
						motor[motorManipulatorLift] = (joystick.joy2_y1);
				} // End of else if(joystick < negThreshold)

				//Sets the motor to 0 if nothing is pressed
				else{
					motor[motorManipulatorLift] = 0;
				}

		//else if(joystick.joy2_y1 < negThreshold){
				//motor[motorManipulatorLift] = (joystick.joy2_y1);
		//} // End of else if(joystick < negThreshold)

		//Sets the motor to 0 if nothing is pressed

		//If button 6 is pressed, set motorArm to full power
		if(joy1Btn(6)==true){
			motor [motorPickUp] = 100;
		} //End of if(joy1Btn(7))

		//If button 5 is pressed, set the motorArm to full reverse
		else if(joy1Btn(5)==true){
			motor [motorPickUp] = -100;
		} //End of else if(joy1Btn(8))

		else{
			motor[motorPickUp] = 0;
		}

		if(joy2Btn(1) == true){
			servo[servoStopper] = 180;
		}
		else if(joy2Btn(3) == true){
			servo[servoStopper] = 0;
		}

		if(joy1Btn(7)==true){
				servo [doubleLift] = 255;
		} //End of if(joy1Btn(7))

			//Close the Double Lift
		else if(joy1Btn(8)==true){
				servo [doubleLift] = 0;
		} //End of else if(joy1Btn(8))

		else{
				servo[doubleLift] = 127;
		}
		// Add a wait of 10 Milliseconds to the code in order to reduce latency.
		wait1Msec(10);

		}//End of while loop.

}  //End of task training wheels

task chooser(){

	int choose = 0;

	while(true){
		if(joy2Btn(7) == true){
			choose = 1;
			wait10Msec(50);
		}

		else if(joy2Btn(8) == true){
			choose = 0;
			wait10Msec(50);
		}

		if(choose == 1){
			StartTask(armControl);
			StopTask(trainingwheels);
		}

		else{
			StartTask(trainingwheels);
			StopTask(armControl);
		}

	 }

 }


task flagControl(){

	//Boolean which determines whether
	bool spinning = false;

	//Integer variable used to set the Limit for the motor encoder.
	int EncoderLimit = 0;

	int turning = 1;

	//Sets the motor encoder to zero at the beginning of the task.
	nMotorEncoder[motorFlagSpinner] = 0;

	//Continuously obtain the joystick settings and set them equal to their respective motor's power.
	while(true){

		getJoystickSettings(joystick);

		//When the A button on the second controller is pressed,
		//spin the flagSpinner until the flag is raised to max height.
	if(joy2Btn(2) == true){
		motor[motorFlagSpinner] = 60;
	} // End of if(joy2Btn(2) == true)

	if(joy2Btn(4) == true){
		motor[motorFlagSpinner] = 100;
		} // End of if(joy2Btn(1) == true)

	else {
		motor[motorFlagSpinner] = 0;
	} // End of else

	// Add a wait of 7 Milliseconds to the code in order to reduce latency.
	wait1Msec(10);

	}//End of while loop while(true)

}//End of task flagControl()

//=============================== Pull Up Control ===========================================================================================================
//
//===========================================================================================================================================================
task pullControl(){

	//Continuously obtain the joystick settings and set them equal to their respective motor's power.
	while(true){

		getJoystickSettings(joystick);

		//If button 7 is pressed, set pushes the arm up in full power
		if(joy2Btn(5)==true){
			motor [motorPullUp] = 100;
		} //End of if(joy1Btn(7))

		//If button 6 is pressed, set the pulls the arm down in full reverse
		else if(joy2Btn(6)==true){
			motor [motorPullUp] = -100;
		} //End of else if(joy1Btn(8))

		else{
			motor[motorPullUp] = 0;
		}

	// Add a wait of 7 Milliseconds to the code in order to reduce latency.
	wait1Msec(10);

	}//End of while loop while(true)

}//End of task flagControl()


//================================ Main Task ===============================================================================================================

//The main task, which is used to initialize the start of the robot,
//the driveControl task, and an infinite loop to keep the code running.
//Task main also prevents the robot from moving during competition until
//the match begins .
task main(){

	//Start the Robot.
	initializeRobot();

	// Wait for start.
	waitForStart();

//===================== Initizlaize Driver Controls (In Main Task) =====================

	//Initialize the Drive Control method.
	StartTask(driveControl);

	//Initialize the Flag Control method.
	StartTask(flagControl);

	//Initialize the Arm Control method.
	StartTask(chooser);

	// Initialize the Pull Up Method.
	StartTask(pullControl);

	//Initialize infinite loop to keep the code running.
	while(true){

 		}//End of while loop.

}  //End task main
