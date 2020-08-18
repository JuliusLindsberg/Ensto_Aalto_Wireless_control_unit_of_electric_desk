#ifndef BLUETOOTH_HPP
#define BLUETOOTH_HPP
//NRF52840 in this prototype is supposed to work in bluetooth low energy peripheral role.
//This module is implemented without a class. classes seem to make callback handling just more difficult and zephy's bluetooth library works mostly on them
//maximum amount of paired devices supported by bluetooth
#include "MotorController.hpp"
#define CONFIG_BT_MAX_PAIRED 1
//maximum amount of connections supported by bluetooth
#define CONFIG_BT_MAX_CONN 1

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

void bluetoothReadyCallback(int err);
void startBluetooth();
//sets the controller object which the bluetooth functionality sends it's data to
void setController(MotorController* controller);


#endif