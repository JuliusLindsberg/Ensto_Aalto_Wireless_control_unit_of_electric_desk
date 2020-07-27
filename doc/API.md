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

Member functions:

### void steerMotor(ButtonState directive)

Tells motorcountroller that it should act as if a button was pressed. This function should be changed to private eventually.

### ButtonState readButtonState()

Returns the current state of the physical direction button.

### EncoderAnalyzer

This class analyzes the data which the desk's encoder provides with the help of an ADC pin.
