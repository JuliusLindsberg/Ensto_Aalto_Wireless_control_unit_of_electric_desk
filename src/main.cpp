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
	while(true)
	{
		analyzer.debugPrintSample(analyzer.getSample());
		k_msleep(200);
	}
}
