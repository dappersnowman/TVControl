Blink Script Test Results
-Meant to test out ability to read digital pin output with multimeter using a continuity test.
	-Results
		-Blink test was successful, but counterintuitive.
		-When pin is not activated, no sound is heard from multimeter.
		-When pin is activated but set to LOW, beeping is heard from multimeter.
		-When pin is activated and HIGH, no beeping is heard.
		-Positive probe was applied to test pin, and negative probe was applied to digital ground.
		-Pin 13, which was connected to the on board LED, also was able to be read from the multimeter.
		-Five volts of resistance were measured off of HIGH pins.

Parachute Deploy Test Results
-Triggered and tested results of deployment function
	-Results
		-Charge was delivered when commanded via serial.

Queue Test Results
-Tested the new queue library by filling and emptying the queue over and over again
	-Results
		-Queue library from Github took up lots of memory and couldn't offload on demand
		-Had to roll own version of queue library
		-Rolled own version using global array variables.
		-New version actually worked
		-New version used less memory
		-New version is less flexible and requires more typing.
			-Eh, at least it works.

Multidimensional Queue Test Results
-Redid original queue test with storing instances of arrays in the queue
	-Results
		-Worked like a beauty.
		-Reworded some of the original functions to better support flexible array sizes.

Sensors Test
-Collected sensor data and spit it out to the serial port.
	-Results
		-Previous sensors unit test code was not present in the Github repo; had to start from scratch
		-Modeled test code on test code supplied by Adafruit
		-Accurate data can be taken, but Arduino stops after a handful of iterations
		-It is possible that the Arduino is not deleting every data point, leading to a memory leak
		-Must fix memory issues.
		-Also, cannot run other trials after running barometer trial. Not a big problem, but should be looked at.
		-Once memory issues are fixed, should record extended data in console and plot the noise in the idle signal.

Sensors Test 8/24
	-Results
		-As unit tests get more involved, I split off unit testing into a new branch in order to clean up repo history.
		-Changed event object to global object, fixing the runaway memory leak.
		-Well, maybe not a memory leak, more like a memory flood.
		-Anyway, the Arduino can now spit out as much data as it needs. The limited storage on the Arduino may be an issue during flight. Not sure until I test out radios.
		-Sometimes, there is a bug where I cannot run two trials in a row one after the other. I'm sure this is a bug with the unit test code and may not be present on the flight.