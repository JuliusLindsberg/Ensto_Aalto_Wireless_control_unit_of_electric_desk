#include <zephyr.h>
#include "DebugBlinker.hpp"
#include "EncoderAnalyzer.hpp"
#include "MotorController.hpp"
#include <string.h>
#define ONE_SECOND 1000
#include <stdio.h>
//for usb debug console messages
#include <sys/printk.h>
#include <sys/util.h>

void main(void)
{
	//This is a working example demonstration of DebugBlinky class features.
	DebugBlinker ledOne(1);
	DebugBlinker ledTwo(2);
	DebugBlinker ledThree(3);
	ledThree.ledOff();
	ledOne.ledOff();
	ledTwo.ledOff();
	EncoderAnalyzer analyzer;
	MotorController motorController;
	//ledOne.ledOn();
	//k_msleep(3000);
	int counter = 0;
	while(1){
		motorController.setButtonInputVoltageState(1);
		ledOne.ledOn();
		k_msleep(1000);
		motorController.setButtonInputVoltageState(0);
		ledOne.ledOff();
		k_msleep(1000);
	}
	return;
	while(true)
	{
		//short* sample = analyzer.getSample();
		//analyzer.debugPrintSample(sample);
		if(motorController.readButtonState())
		{
			ledOne.ledOn();
			DebugPrint("got a pin read of ");
    		DebugPrint(motorController.readButtonState());
    		DebugPrint("\n");
		}
		else{
			ledOne.ledOff();
		}
		k_msleep(1000);
		//motorController.setButtonInputVoltageState(counter%2);
		counter++;
	}
}
