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