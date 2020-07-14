#include <zephyr.h>
#include "DebugBlinker.hpp"
#include "EncoderAnalyzer.hpp"
#include "MotorController.hpp"
#include "DebugPrinter.hpp"
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
	DebugPrinter printer;
	k_msleep(10000);
	int sampleSize = 500;
	short buffer[sampleSize];
	ledOne.ledOn();
	for(unsigned i = 0; i < sampleSize; i++)
	{
		buffer[i] = analyzer.getSample();
	}
	ledTwo.ledOn();
	k_msleep(1000);
	for(unsigned i = 0; i < sampleSize; i++)
	{
		printer << buffer[i];
		printer << " ";
		if(i%20 == 0)
		{
			printer<<"\n";
		}
	}
	while(true)
	{
		k_msleep(ONE_SECOND);
	}
}
