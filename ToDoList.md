Programming To-Do List

Top Level Scripts for Driving System Behavior

-Launch Day Script
	-Compilation of expected launch day behavior; this sketch is the primary sketch that is uploaded
	to the Arduino
	-Thrust Vector On/Off Toggle - Multiple Reference Trajectory Options should be toggleable before launch
	-Launch triggers and abort from ground computers via radio commands
	-In-Flight Controls Abort handling
		-Centers and Locks Gimbals
		-Deploys parachute post burnout - triggered via timer
	-Output all data in a FIFO queue to be transmitted via radio to ground computers

-Unit Test Scripts
	-Scripts for ground tests with various components, hardware in the loop tests


Supporting Library Functions

-setup()
	-Runs pin initialization
	-Initialization of IMU, radio, and servos
	-This is written in a separate sketch from the Top Level Scripts in order to have a common setup function
	that can be reused for all Top Level Scripts

-Adafruit IMU interface
	-IMUread()
		-Reads raw IMU data
		-Outputs to FIFO queue

-Controls
	-controller()
		-reads saved IMU values
		-Calculates physical state and error
		-Outputs physical state to FIFO queue to be transmitted to ground
		-Implements PID control
			-One call to controller() each time you go through control loop
		-Outputs desired gimbal x-y deflection in degrees

-Servos
	-gimbal()
		-Takes in x-y deflection angles
		-Calculates proper servo positions using calculated transfer function
		-Drives servos to proper positions
	-gimbalCenter()
		-Centers gimbal mount to zero values
		-Used for initialization, vector off mode, and in flight aborts
		-Actual zero angles used may need to be found through hand calibration

-Parachute - Finished
	-deploy()
		-Sends current to detonate black powder ejection charge

-Radio/Serial
	-broadcast()
		-Sends top items off of FIFO queues to radio to be broadcast to ground
	-receive()
		-Receives abort, launch hold, and launch ignition commands from ground
	-Radio and Serial are two almost identical sketches; each one contains broadcast and receive functions
	-Radio will be loaded on launch day and during radio based tests
	-Serial will be loaded on hardware in the loop tests when the microcontroller will be hooked up to a
	computer through USB/Serial
