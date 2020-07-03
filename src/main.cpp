#include <zephyr.h>

#include "DebugBlinker.hpp"
#define ONE_SECOND 1000

void main(void)
{
	//This is a working example demonstration of DebugBlinky class features.
	DebugBlinker ledone(1);
	DebugBlinker ledtwo(2);
	DebugBlinker ledthree(3);
	ledone.ledOff();
	ledtwo.ledOn();
	ledthree.ledOn();
	while(1)
	{
		k_msleep(ONE_SECOND);
		ledone.ledOn();
		ledtwo.ledOff();
		k_msleep(ONE_SECOND);
		ledone.ledOff();
		declareException();
		ledthree.virtualLedToggle();
		if(ledthree.virtualLedState())
		{
			ledthree.ledOn();
		}
		else
		{
			ledthree.ledOff();
		}
	}
}
