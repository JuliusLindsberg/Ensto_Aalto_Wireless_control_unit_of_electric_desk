#include "MotorController.hpp"

#include "DebugBlinker.hpp"
#include <zephyr.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <dt-bindings/gpio/gpio.h>
#include "DebugPrinter.hpp"
//Button up input pin 1 of device GPIO_1 is (ARDUINO D0, p1.01) in nrf52840dk
#define BUTTON_UP_INPUT 1
//p1.02
#define BUTTON_DOWN_INPUT 2
//p1.03
#define BUTTON_UP_OUTPUT 4
//p1.04
#define BUTTON_DOWN_OUTPUT 5


struct device* pinDevice;
bool MCInitialized = false;

MotorController::MotorController()
{
    setState(ControlState::BUTTON);
    targetHeight = -1;
    if(!MCInitialized)
    {
        MCInitialized = true;
        pinDevice = device_get_binding("GPIO_1");
        
        if(pinDevice == NULL)
        {
            declareException();
        }
        //init digital input pins
        gpio_pin_configure(pinDevice, BUTTON_UP_INPUT, GPIO_INPUT);
        gpio_pin_configure(pinDevice, BUTTON_DOWN_INPUT, GPIO_INPUT);
        //init digital output pins
        gpio_pin_configure(pinDevice, BUTTON_DOWN_OUTPUT, GPIO_OUTPUT_LOW);
        gpio_pin_configure(pinDevice, BUTTON_UP_OUTPUT, GPIO_OUTPUT_LOW);
    }
}

ButtonState MotorController::readButtonState()
{
    int retUP = gpio_pin_get_raw(pinDevice, BUTTON_UP_INPUT);
    int retDOWN = gpio_pin_get_raw(pinDevice, BUTTON_DOWN_INPUT);

    if( retUP == 1 && retDOWN == 0)
    {
        return ButtonState::DOWN;
    }
    else if(retUP == 0 && retDOWN == 1)
    {
        return ButtonState::UP;
    }
    else if(retUP == 0 && retDOWN == 0)
    {
        return ButtonState::BOTH;
    }
    else if(retUP == 1 && retDOWN == 1)
    {
        return ButtonState::NOT_PRESSED;
    }
    else
    {
        //in case of an unknown state the safest signal to send is ButtonState::NOT_PRESSED as then it won't move the desk due to potential error states
        declareException();
        return ButtonState::NOT_PRESSED;
    }
}

void MotorController::steerMotor(ButtonState directive)
{
    DebugPrinter printer;
    if(directive == ButtonState::UP)
    {
        gpio_pin_set_raw(pinDevice, BUTTON_UP_OUTPUT, 1);
        gpio_pin_set_raw(pinDevice, BUTTON_DOWN_OUTPUT, 0);
        printer << "UP\n";
    }
    else if(directive == ButtonState::DOWN)
    {
        gpio_pin_set_raw(pinDevice, BUTTON_UP_OUTPUT, 0);
        gpio_pin_set_raw(pinDevice, BUTTON_DOWN_OUTPUT, 1);
        printer << "DOWN\n";
    }
    else if(directive == ButtonState::BOTH)
    {
        gpio_pin_set_raw(pinDevice, BUTTON_UP_OUTPUT, 1);
        gpio_pin_set_raw(pinDevice, BUTTON_DOWN_OUTPUT, 1);
        printer << "BOTH\n";
    }
    else
    {
        printer << "NOTPRESSED\n";
        gpio_pin_set_raw(pinDevice, BUTTON_UP_OUTPUT, 0);
        gpio_pin_set_raw(pinDevice, BUTTON_DOWN_OUTPUT, 0);
    }
}

bool MotorController::steerTowardsTarget(int tableHeight)
{
    if(targetHeight < 0)
    {
        return true;
    }
    if(analyzer.getTargetDirection() == TargetDirection::DOWN_DIRECTION)
    {
        //goal reached
        if(tableHeight <= targetHeight)
        {
            return true;
        }
        //keep steering
        else
        {
            steerMotor(ButtonState::DOWN);
        }
    }
    else if(analyzer.getTargetDirection() == TargetDirection::UP_DIRECTION)
    {
        //goal reached
        if(tableHeight >= targetHeight)
        {
            return true;
        }
        //keep steering
        else
        {
            steerMotor(ButtonState::UP);
        }
    }
    else
    {
        //this shouldnt happen. If we get here there's a bug in code.
        declareException();
        return true;
    }
    //goal has not been reached
    return false;
}

ControlState MotorController::controlStateButton(int tableHeight, ButtonState buttonState)
{
    if(buttonState == ButtonState::NOT_PRESSED)
    {
        steerMotor(ButtonState::NOT_PRESSED);
    }
    else if(buttonState == ButtonState::DOWN)
    {
        //user wants to steer downwards via button press
        steerMotor(ButtonState::DOWN);
    }
    else if(buttonState == ButtonState::UP)
    {
        //user wants to steer upwards via button press
        steerMotor(ButtonState::UP);
    }
    else if(buttonState == ButtonState::BOTH)
    {
        //no idea what is supposed to happen
        steerMotor(ButtonState::BOTH);
    }
    return ControlState::BUTTON;
}
ControlState MotorController::controlStateBluetooth(int tableHeight, ButtonState buttonState)
{
    if(buttonState != ButtonState::NOT_PRESSED)
    {
        return ControlState::BUTTON;
    }
    //target achieved
    if(steerTowardsTarget(tableHeight))
    {
        analyzer.setTargetDirection(TargetDirection::NONE);
        targetHeight = -1;
        return ControlState::BUTTON;
    }
    return ControlState::BLUETOOTH;
}

void MotorController::run()
{
    DebugPrinter printer;
    //DEBUGGING REMOVE THIS
    bluetoothSteerRequest(120);
    //REMOVE THIS END
    while(1)
    {
        k_msleep(1);
        //these steps are the same for every state
        int tableHeight = analyzer.updateAndGetDeskPosition();
        ButtonState buttonState = readButtonState();
        //finite state machine spesific states
        printer << "STATE: " << getState() << "\n" << " tableHeight: " << tableHeight << "\n";
        switch (getState())
        {
        case ControlState::BUTTON:
            setState(controlStateButton(tableHeight, buttonState));
            break;
        case ControlState::BLUETOOTH:
            setState(controlStateBluetooth(tableHeight, buttonState));
            break;
        default:
            //currently this should be logically impossible. There is no designated error state
            declareException();
            break;
        }
    }
};

ControlState MotorController::getState()
{
    return controlState;
}

void MotorController::setState(ControlState newState)
{
    controlState = newState;
}

void MotorController::bluetoothSteerRequest(int newTargetHeight)
{
    //this has to be reworked when bluetooth branch gets more progressed
    setState(ControlState::BLUETOOTH);
    targetHeight = newTargetHeight;
    if( analyzer.lastDeskPosition() < newTargetHeight )
    {
        analyzer.setTargetDirection(TargetDirection::UP_DIRECTION);
    }
    else if( analyzer.lastDeskPosition() > newTargetHeight )
    {
        analyzer.setTargetDirection(TargetDirection::DOWN_DIRECTION);
    }
    else
    {
        analyzer.setTargetDirection(TargetDirection::NONE);
        targetHeight = -1;
        declareException();
    }
}