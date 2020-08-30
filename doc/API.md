# Introduction

Software implementation of our project has been divided into c++ classes with the aim of encapsulating different functionalities in a logical way
and making everything more modular. API documentation will reflect this and therefore consist mostly of class descriptions.
Further explanations into the Zephyr's API reference can be found from: https://docs.zephyrproject.org/latest/boards/arm/nrf52840dk_nrf52840/doc/index.html
Despite it's name this document does not attempt to be a sterile API reference nor is it written by an expert on the topic. Instead, it is designed to explain
itself as well as possible from a subjective point of view in an attempt to help beginners to Zephyr avoid potential pitfalls.

Also it is imperative that a developer learns about Zephyr's inner workings from Zephyr's own tutorials. For example:
https://docs.zephyrproject.org/latest/guides/dts/intro.html#devicetree-intro <- which is a link to Zephyr project's device tree introduction in case the link dies.
Coming from personal experience, relying too heavily in deducting Zephyr's functionality from it's own code samples is not the most efficient method of
understanding it.

## DebugBlinker
DebugBlinker is a lightweight class that other classes can use for debugging. The final prototype will most likely have no use for LEDs as they will not be visible to
the end user. User of this class can create as many DebugBlinker objects as they want: they do not imply any sort of exclusive ownership of a led. However,
DebugBlinker's functionality currently is not thread-safe. LED4 is reserved for declaring an exeption: If LED4 is lit then some part of the program has called
declareException() function.

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

## DebugPrinter

DebugPrinter is another lightweight class that can be used for debugging. It was used in conjunction with Segger's J-Link SWOWiever tool for debug output.
Zephyr does also provide a function called printk for serial output but as it didn't work immediately for unknown reasons and although SWOViewer was a clumsy-ish
compromise it did eventually satisfy all of the group's needs for debugging and as such not much research was put into the problem which probably
would have been proven out to be very solvable. For further development using printk is still most likely a more preferable solution as it is being used in examples.

DebugPrinter has << operator overloading and it can be used as if it were std::cout with the exception that it is not a static class and should be instead
interacted through DebugPrinter objects. The first instance of DebugPrinter initializes SWO and SWOViewer and can be configured to work only after that.
Therefore it is recommended to create one DeubgPrinter Object right in the beginning of main(): another example of why printk would have indeed been more preferable.

Member functions:

### PrintString(char* string)
Prints a null-terminated-string to the SWO terminal. Can also be used with << operator
### PrintChar(char c)
Prints a single char to the SWO terminal. Can also be used with << operator
### PrintInt(int number)
Prints a number to the SWO terminal. Can also be used with << operator

## MotorController

This class is responsible for emulating the control signal of the desk's physical button presses. It determines which control signals should be listened to at what
times as a finite state machine. Currently it has two states: BUTTON and BLUETOOTH. However, additional states could be defined for additional states. BLUETOOTH state
might actually be a bit misrepresenting as it isn't actually directly responsible for listening to bluetooth signals. It just steers the table towards a target height
automatically based on steerRequest() function calls.

Currently, unfortunately, creating multiple objects of this class causes undefined behaviour!

### enum ButtonState
The electric desk's control button has four logical states it can be in. Our microcontroller tries to emulate them so that when a user presses the button
our controller functions as if it wouldn't be there at all catching the signal.

### enum ControlState
The MotorController internally functions as a finite state machine. Currently it has two states: BLUETOOTH and BUTTON. Every state has it's respective member
function responsible for sending the appropriate control signals to the motor and transitioning between states.

Member functions:

### void steerRequest(int newTargetHeight)

Tells MotorController to steer itself autonomously to a set target height. newTargetHeight represents reverse-engineered encoder steps which we spy and as such 
the distance traversed isn't strictly bound to any physical unit of height. Theoretically one encoder step does represent a certain constant distance but where
the table actually sets in within these boundaries could vary. The resolution of the table's encoder steps between the most upwards position and down position
is between 0 and somewhere around 400. Requests that differ from this range are currently not being ignored or cropped to physical limits by the function.

### ControlState getState()

Returns in which control state MotorController is in right now.

### run()

a forever blocking function which keeps running the internal state machine logic to steer the table according to their respective user inputs.

### EncoderAnalyzer

This class analyzes the data which the desk's encoder provides with the help of an ADC pin. It is used by MotorController class internally and provides no useful
functionality outside of that.

## BluetoothModule.hpp

This is a more of a c-style interface responsible for implementing bluetooth functionality. It mostly has asynchronous functions and callback functions that describe
what is supposed to happen after event x happening. The c-style approach is because from our experience asynchronous functions combined with c++-style objects
do not really fit together well. It defines a custom bluetooth GATT service that has a 128-bit UUID of 6495c7ad-e0cc-4c2c-87c8-e8ad2f964b03 and advertises said service this UUID should be able to be changed with just one line of code. Naturally though the code of your BLE clients should be updated as well.
