#include <zephyr.h>
#include "DebugBlinker.hpp"
#include "EncoderAnalyzer.hpp"
#include "MotorController.hpp"
<<<<<<< HEAD
#include "BluetoothModule.hpp"
=======
#include "DebugPrinter.hpp"
>>>>>>> master
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
<<<<<<< HEAD
	BluetoothModule bluetooth;
	while(true)
	{
		
=======
	EncoderAnalyzer analyzer;
	MotorController motorController;
	DebugPrinter printer;
	int counter = 0;

	while(true)
	{
		int pos = analyzer.updateAndGetDeskPosition();
		k_msleep(4);
		printer << "Desk position: " << pos << "\n";
>>>>>>> master
	}

}
