#include "MotorController.hpp"

#include "DebugBlinker.hpp"
#include <zephyr.h>
//#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <dt-bindings/gpio/gpio.h>

#define BUTTON_VOLTAGE_PIN 3
#define BUTTON_INPUT_PIN 1


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
        //init input pin
        gpio_pin_configure(pinDevice, BUTTON_VOLTAGE_PIN, GPIO_OUTPUT_HIGH);
        //init output pin
        //gpio_pin_configure(pinDevice, BUTTON_INPUT_PIN, GPIO_INPUT);
        gpio_pin_set_raw(pinDevice, BUTTON_VOLTAGE_PIN, 1);
    }
}

bool MotorController::readButtonState()
{
    int ret = gpio_pin_get_raw(pinDevice, BUTTON_INPUT_PIN);
    if( ret == 0)
    {
        return false; 
    }
    else if(ret == 1)
    {
        return true;
    }
    else
    {
        declareException();
        return false;
    }
}

void MotorController::setButtonInputVoltageState(bool state)
{
    DebugPrint("pin set to ");
    DebugPrint(state);
    DebugPrint("\n");
    gpio_pin_set_raw(pinDevice, BUTTON_VOLTAGE_PIN, state);
}