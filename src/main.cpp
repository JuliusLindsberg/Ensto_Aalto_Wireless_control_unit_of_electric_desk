//there might be useless includes
#include <stdio.h>
#include <zephyr.h>
#include <arch/cpu.h>
#include <sys/printk.h>

#include "DebugBlinker.hpp"

#define SLEEPYTIME 1000

void main(void)
{
	DebugBlinker led0(0);
	DebugBlinker led1(1);
	DebugBlinker led2(2);
	DebugBlinker led3(3);
	led0.ledOn();
	led1.ledOff();
	led2.ledOff();
	led3.ledOn();

	while(true)
	{
		k_msleep(SLEEPYTIME);
		led3.virtualLedToggle();
		if(led3.virtualLedState())
		{
			led3.ledOn();
		}
		else
		{
			led3.ledOff();
		}
	}
}
