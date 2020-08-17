#ifndef BLUETOOTH_HPP
#define BLUETOOTH_HPP
//NRF52840 in this prototype is supposed to work in bluetooth low energy peripheral role.
//This module is implemented without a class. classes seem to make callback handling just more difficult and zephy's bluetooth library works mostly on them
//maximum amount of paired devices supported by bluetooth
#define CONFIG_BT_MAX_PAIRED 1
//maximum amount of connections supported by bluetooth
#define CONFIG_BT_MAX_CONN 1

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

//this UUID is associated with the custom table control GATT bluetooth low-energy service
#define TABLE_CONTROL_SERVICE_UUID 1000

void bluetoothReadyCallback(int err);
void startBluetooth();



#endif