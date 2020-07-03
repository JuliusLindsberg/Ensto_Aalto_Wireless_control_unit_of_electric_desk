# Introduction

Software implementation of our project has been divided into c++ classes with the aim to encapsulate different functionalities in a logical way
and make everything more modular. API documentation will reflect this and therefore consist mostly of class descriptions.
This API is also agnostic of any functions and definitions that originate from Zephyr RTOS and their behaviour will (hopefully!) be adequetly explained by comments within sourcecode or the Zephyr API reference located in https://docs.zephyrproject.org/latest/boards/arm/nrf52840dk_nrf52840/doc/index.html

##DebugBlinker
DebugBlinker is a lightweight static class that other classes can use for gathering debug data. The final prototype will most likely have no use for LEDs as they will not be visible to the end user. It also supports 3 'virtual leds' that are simple boolean values which switch on or off based on function calls. This might come handy later on for debugging code. There is no function for checking a physical led's status. This is intentional: physical leds are only for debugging visually. Use the virtual leds instead to debug something logically, if tempted. If they turn out to be practical enough they will have mutexes to make them thread friendly. Currently though, not. LED4 is reserved for declaring an exeption: If LED4 is lit then some part of the program has called declareException() function.
Member functions:

###DebugBlinker(int led_)

constructor for the DebugBlinker object. Supports leds 1, 2 and 3.
This is the only way to create an object of this class currently that is supported by the API.

###void ledOn();

Will light up a led. Supports leds 1, 2 and 3.

###void ledOff(int led);

Will power off a led. Supports leds 1, 2 and 3.

###void virtualLedOn();

Will switch virtual led on. Supports leds 1, 2 and 3.

###void virtualLedOff();

Will switch virtual led off. Supports leds 1, 2 and 3.

###void virtualLedToggle();

Will toggle a led's status to the opposite. Supports leds 1, 2 and 3.

###bool virtualLedStatus();

Returns a virtual led's status as boolean value. Supports leds 1, 2 and 3.

###void declareException();

Lights up LED4 as a signal of exceptional circumstances faced somewhere in the code. It is supposed to replace a hole left by c++ standard library's stdexcept as unfortunately Zephyr currently does not support c++-style exception handling.

##Regular Classes
Your regular OOP experience...
###MotorController
TODO

###EncoderAnalyzer
TODO
