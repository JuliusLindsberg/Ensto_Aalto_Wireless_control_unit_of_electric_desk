#ifndef DEBUGBLINKER_HPP
#define DEBUGBLINKER_HPP
//Basically the more c++ version of #define LEDCOUNT 4. These are c++11 standard: thse can be replaced with #defines if c++11 is not supported.
constexpr int LEDCOUNT = 4;

class DebugBlinker
{
    //inside a class static members are not part of any object. Just like in c,
    //they are created at the start of a program and will stay in stack until the very end.
    int led;
    //every element after public: is free to use by anyone outside this class. This is opposed to a private variable.
    //the technical difference between struct and class in c++ is that struct has it's members declared public by default and
    //class has them as private.
    public:

    DebugBlinker(int led_);

    void ledOn();
    void ledOff();
    void ledToggle();
    void virtualLedOn();
    void virtualLedOff();
    void virtualLedToggle();
    bool virtualLedState();
};


#endif