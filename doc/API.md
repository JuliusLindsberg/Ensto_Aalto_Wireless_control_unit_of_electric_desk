# Introduction

Software implementation of our project has been divided into c++ classes with the aim to encapsulate different functionalities in a logical way
and make everything more modular. API documentation will reflect this and therefore consist mostly of class descriptions.
This API aims to be agnostic of as many functions and definitions that originate from Zephyr RTOS and their behaviour will (hopefully!) also be adequetly explained by comments within sourcecode or the Zephyr API reference: https://docs.zephyrproject.org/latest/boards/arm/nrf52840dk_nrf52840/doc/index.html

## DebugBlinker
DebugBlinker is a lightweight class that other classes can use for debugging. The final prototype will most likely have no use for LEDs as they will not be visible to the end user. User of this class can create as many DebugBlinker objects as they want: they do not imply any sort of exclusive ownership of a led. However, DebugBlinker's functionality currently is not thread-safe. LED4 is reserved for declaring an exeption: If LED4 is lit then some part of the program has called declareException() function.

Non-Member functions:

### void declareException()

Lights up LED4 as a signal of exceptional circumstances faced somewhere during the execution of the program. It is supposed to replace a hole left by c++ standard library's exception handling as unfortunately Zephyr currently does not support it.


Member functions:

### DebugBlinker(int led_)

constructor for the DebugBlinker object. Supports leds 1, 2 and 3.
This is the only way to create an object of this class currently that is supported by the API.

### void ledOn()

Will light up a led. Supports leds 1, 2 and 3.

### void ledOff(int led)

Will power off a led. Supports leds 1, 2 and 3.

## MotorController

This class is responsible for emulating the control signal of the desk's physical button presses. It also is supposed to enforce safety limits on maximum up and down positions and determining on which control signal should be listened to and at what times as a finite state machine. 

Currently, unfortunately, creating multiple objects of this class causes undefined behaviour!

###enum ButtonState
The electric desk's control button has four logical states it can be in. Our microcontroller tries to emulate them so that when a user presses the button
our controller functions as if it wouldn't be there at all catching the signal.

###enum ControlState
The MotorController interlanny functions as a finite state machine. Currently it has two states: BLUETOOTH and BUTTON. Every state has it's respective member
function responsible for sending the appropriate control signals to the motor and transitioning between states.

Member functions:

### void steerRequest(int newTargetHeight)

Tells MotorController to steer itself autonomously to a set target height. The maximum range of table right now is from 0 to three or four hundred.
The value represents encoder steps which we spy on and is therefore not strictly bound to any physical unit of height.

### ControlState getState()

Returns in which control state MotorController is in right now.

### run()

a forever blocking function that keeps running the internal state machine to steer the table according to user inputs.

### EncoderAnalyzer

This class analyzes the data which the desk's encoder provides with the help of an ADC pin. It is used by MotorController class internally and provides no useful
functionality outside of that.

