#include <zephyr.h>
#include "DebugBlinker.hpp"
#include "MotorController.hpp"

#include "DebugPrinter.hpp"
#include "BluetoothModule.hpp"
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
	DebugPrinter printer;
	printer << "asd\n";
	k_msleep(10000);
	printer << "starting bt now\n";
	ledThree.ledOff();
	ledOne.ledOff();
	ledTwo.ledOff();
	startBluetooth();
}
