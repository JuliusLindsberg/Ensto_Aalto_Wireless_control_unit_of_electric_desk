#include <device.h>
#include <devicetree.h>
#include <zephyr.h>
#include <drivers/gpio.h>
#include "DebugBlinker.hpp"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "DebugSwo.h"

//there might be redundant FLAGS here but lets get this working first
#define LED0_NODE DT_ALIAS(led0)
#define LED0 DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN0 DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS0 DT_GPIO_FLAGS(LED0_NODE, gpios)

#define LED1_NODE DT_ALIAS(led1)
#define LED1 DT_GPIO_LABEL(LED1_NODE, gpios)
#define PIN1 DT_GPIO_PIN(LED1_NODE, gpios)
#define FLAGS1 DT_GPIO_FLAGS(LED1_NODE, gpios)

#define LED2_NODE DT_ALIAS(led2)
#define LED2 DT_GPIO_LABEL(LED2_NODE, gpios)
#define PIN2 DT_GPIO_PIN(LED2_NODE, gpios)
#define FLAGS2 DT_GPIO_FLAGS(LED2_NODE, gpios)

#define LED3_NODE DT_ALIAS(led3)
#define LED3 DT_GPIO_LABEL(LED3_NODE, gpios)
#define PIN3 DT_GPIO_PIN(LED3_NODE, gpios)
#define FLAGS3 DT_GPIO_FLAGS(LED3_NODE, gpios)

//no static variables in Zephyr confirmed. This was learned the hard way... I suggest static variables that are shared by instances of a class could be
//implemented like this: as global variables inside a class specific cpp file as they then won't be included any place else. Or put into a namespace
//Or the concept could be ditched entirely and just code everything with local variables.
struct device* leds[USABLE_LED_COUNT];
uint8_t pins[USABLE_LED_COUNT];
bool DB_initialized = false;
bool virtualLeds[USABLE_LED_COUNT];
bool DB_exceptionIsDeclared = false;
bool debugSwoInitilized = false;


void declareException()
{
    if(!exceptionIsDeclared())
    {
    struct device* exceptionLed = device_get_binding("GPIO_0");
    gpio_pin_configure(exceptionLed, PIN3, GPIO_OUTPUT_ACTIVE | FLAGS3);
    gpio_pin_set(exceptionLed, PIN3, 1);
    }
}

bool exceptionIsDeclared()
{
    if(DB_exceptionIsDeclared)
    {
        return true;
    }
    return false;
}


DebugBlinker::DebugBlinker(int led_)
{
    //gets initialized automatically the first time a DebugBlinker object is constructed and never afterwards
    if( !(led_ < 1 || led_ > USABLE_LED_COUNT) )
    {
        led = led_-1;
        if(!DB_initialized)
        {
            DB_initialized = true;
            leds[0] = device_get_binding(LED0);
            leds[1] = device_get_binding(LED1);
            leds[2] = device_get_binding(LED2);
            pins[0] = PIN0;
            pins[1] = PIN1;
            pins[2] = PIN2;
            gpio_pin_configure(leds[0], PIN0, GPIO_OUTPUT_ACTIVE | FLAGS0);
            gpio_pin_configure(leds[1], PIN1, GPIO_OUTPUT_ACTIVE | FLAGS1);
            gpio_pin_configure(leds[2], PIN2, GPIO_OUTPUT_ACTIVE | FLAGS2);
        }
    }
    else
    {
        declareException();
        //lets see if exeptions work in Zephyr
        //throw std::out_of_range("Error: DebugBlinky only supports leds indexed as 1, 2 or 3");
        //Unfortunately no c++-style exception handling in Zephyr confirmed. Looking for alternatives...
    }
}

void DebugBlinker::ledOn()
{
    //led = PIN.
    gpio_pin_set(leds[led], pins[led], 1);
}

void DebugBlinker::ledOff()
{
    gpio_pin_set(leds[led], pins[led], 0);
}

void DebugBlinker::ledToggle()
{
    //not implemented. This function might be stupid.
}

void DebugBlinker::virtualLedOn()
{
    virtualLeds[led] = true;
}

void DebugBlinker::virtualLedOff()
{
    virtualLeds[led] = false;
}

void DebugBlinker::virtualLedToggle()
{
    virtualLeds[led] = !virtualLeds[led];
}


bool DebugBlinker::virtualLedState()
{
    return virtualLeds[led];
}

void numberToBlinks(int number)
{
    DebugBlinker ledOne(1);
    DebugBlinker ledTwo(2);
    DebugBlinker ledThree(3);
    ledOne.ledOn();
    ledTwo.ledOn();
    ledThree.ledOn();
    k_msleep(2000);
    ledOne.ledOff();
    ledTwo.ledOff();
    ledThree.ledOff();
    k_msleep(500);
    char buffer[20] = {0};
    sprintf(buffer, "%d", number);
    for(char* c = buffer; *c != 0; c++)
    {
        ledTwo.ledOn();
        k_msleep(2000);
        ledTwo.ledOff();
        k_msleep(2000);
        ledOne.ledOff();
        if(*c == '-')
        {
            ledThree.ledOn();
            continue;
        }
        for(unsigned char k = (*c)-48; k > 0; k--)
        {
            k_msleep(1000);
            ledOne.ledOn();
            k_msleep(500);
            ledOne.ledOff();
        }
    }
    k_msleep(500);
    ledOne.ledOn();
    ledTwo.ledOn();
    ledThree.ledOn();
    k_msleep(500);
    ledOne.ledOff();
    ledTwo.ledOff();
    ledThree.ledOff();
}

void DebugPrint(char* string)
{
    SWO_PrintString(string);
}

void DebugPrint(char c)
{
    SWO_PrintChar(c);
}