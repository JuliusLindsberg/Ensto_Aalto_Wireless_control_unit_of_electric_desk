#include <zephyr.h>
#include "DebugBlinker.hpp"
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
	DebugPrinter printer;
	ledThree.ledOff();
	ledOne.ledOff();
	ledTwo.ledOff();
	k_msleep(10000);
	MotorController controller;
	//BluetoothModule bluetooth;
	controller.run();
}
