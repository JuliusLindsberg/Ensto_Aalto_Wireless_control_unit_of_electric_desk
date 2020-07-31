#ifndef DEBUGBLINKER_HPP
#define DEBUGBLINKER_HPP
//Basically the more c++ version of #define LEDCOUNT 4. These are c++11 standard: can be replaced with a plain #define macro if c++11 is covered.
constexpr int USABLE_LED_COUNT = 3;

//LED 4 is reserved for exceptions only as exception handling is not supported. Once an exception has been declared, it cannot lit off.
void declareException();
bool exceptionIsDeclared();
//this is the most ineffective method of relaying information but
//in some simple situations it might be beneficial to debug something just by counting blinks...
//this function is blocking and intentionally takse a long time to execute.
void numberToBlinks(int number);

class DebugBlinker
{
    int led;
    //every element after public: is free to use by anything outside this class. This is opposed to a private variable which is only for
    //classes internal usage. There is also protected, but we probably won't be using inheritance in this project
    //the technical difference between struct and class in c++ is that struct has it's members declared public by default and
    //class has them as private.
    public:
    //note that led number is reflective of the physical markings in the board. LED1 is led index 1 as opposed to led 0 like it's treated as in Zephyr.
    //this policy is an effort order to avoid confusion. Time will tell if it backfires...
    DebugBlinker(int led_);

    void ledOn();
    void ledOff();
    void ledToggle();
};


#endif