# Introduction

Software implementation of our project has been divided into c++ classes with the aim to encapsulate different functionalities in a logical way
and make everything more modular. API documentation will reflect this and therefore consist mostly of class descriptions.
This API is also agnostic of any functions and definitions that originate from Zephyr RTOS and their behaviour will (hopefully!) be adequetly explained by comments within sourcecode or the Zephyr API reference located in https://docs.zephyrproject.org/latest/boards/arm/nrf52840dk_nrf52840/doc/index.html

#Static Classes
Static classes are classes that cannot be made into objects. Their function is to provide a global while at the same time encapsulating their internal logic as invisible for clarity's sake.
##DebugBlinker (static)
DebugBlinker is a lightweight static class interface that other classes will be using during the development for gathering debug data. The final prototype will most likely have no use for LEDs as they will not be visible to the user. It also supports 4 'virtual leds' that are simple boolean values which switch on or off based on function calls. This might come handy later on for debugging code. There is no function for checking a physical led's status. This is intentional: physical leds are only for debugging visually. Use the virtual leds instead to debug something logically, if tempted. If they turn out to be practical enough they will have mutexes to make them thread friendly. Currently though, not.

###void ledOn(int led);

Will light up a led. Supports leds 0, 1, 2 and 3. Giving any value outside this range will do nothing and be ignored.

###void ledOff(int led);

Will power off a led. Supports leds 0, 1, 2 and 3. Giving any value outside this range will do nothing and be ignored.

###void toggleLed(int led);

Will toggle a led's status to the opposite. Supports leds 0, 1, 2 and 3. Giving any value outside this range will do nothing and be ignored.

###void virtualLedOn(int led);

Will switch virtual led on. Supports leds 0, 1, 2 and 3. Giving any value outside this range will do nothing and be ignored.

###void virtualLedOff(int led);

Will switch virtual led off. Supports leds 0, 1, 2 and 3. Giving any value outside this range will do nothing and be ignored.

###void virtualLedToggle(int led);

Will toggle a led's status to the opposite. Supports leds 0, 1, 2 and 3. Giving any value outside this range will do nothing and be ignored.

###bool virtualLedStatus(int led);

Returns a virtual led's status as boolean value. Supports leds 0, 1, 2 and 3. Giving any value outside this range will return false.

##Regular Classes
Your regular OOP experience...
###MotorController
TODO

###EncoderAnalyzer
TODO