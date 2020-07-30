#ifndef MOTOR_CONTROLLER_HPP
#define MOTOR_CONTROLLER_HPP

#include "EncoderAnalyzer.hpp"

typedef enum ButtonState {
    NOT_PRESSED,
    UP,
    DOWN,
    BOTH,
} ButtonState;

//MotorController essentially functions as a finite state machine with two states: BUTTON and BLUETOOTH which may transition from one to another
typedef enum ControlState {
    BUTTON,
    BLUETOOTH
} ControlState;

typedef enum TargetDirection
{
    NONE,
    UP_DIRECTION,
    DOWN_DIRECTION
};

class MotorController {
    EncoderAnalyzer analyzer;
    //DO NOT CHANGE THE VALUE OF THIS DIRECTLY! USE GETTERS AND SETTERS there might be a need for getters or setters later on
    ControlState controlState;
    int targetHeight;
    //-1 means down, 1 means up, 0 means no direction
    TargetDirection targetDirection;
    ButtonState readButtonState();
    void steerMotor(ButtonState directive);
    //returns true if target has been reached, false if not
    bool steerTowardsTarget(int tableHeight);
    ControlState controlStateButton(int tableHeight, ButtonState buttonState);
    ControlState controlStateBluetooth(int tableHeight, ButtonState buttonState);
    void setState(ControlState newState);
    public:
    ControlState getState();
    MotorController();
    void bluetoothSteerRequest(int newTargetHeight);
    //a forever blocking function that should either have it's own seperate thread or be the program's main-loop
    void run();
};

#endif