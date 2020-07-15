#include "MotorController.hpp"

#include "DebugBlinker.hpp"
#include <zephyr.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <dt-bindings/gpio/gpio.h>

//Button up input pin 1 of device GPIO_1 is (ARDUINO D0, p1.01) in nrf52840dk
#define BUTTON_UP_INPUT 1
//p1.02
#define BUTTON_DOWN_INPUT 2
//p1.04
#define BUTTON_DOWN_OUTPUT 4
//p1.03
#define BUTTON_UP_OUTPUT 3


struct device* pinDevice;
bool MCInitialized = false;

MotorController::MotorController()
{
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
    int retDOWN = gpio_pin_get_raw(pinDevice, BUTTON_UP_OUTPUT);

    if( retUP == 1 && retDOWN == 0)
    {
        return ButtonState::UP;
    }
    else if(retUP == 0 && retDOWN == 1)
    {
        return ButtonState::DOWN;
    }
    else if(retUP == 1 && retDOWN == 1)
    {
        return ButtonState::BOTH;
    }
    else if(retUP == 0 && retDOWN == 0)
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