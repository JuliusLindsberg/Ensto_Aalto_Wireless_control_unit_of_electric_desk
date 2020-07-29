#ifndef BLUETOOTH_HPP
#define BLUETOOTH_HPP

//maximum amount of paired devices supported by bluetooth
#define CONFIG_BT_MAX_PAIRED 1
//maximum amount of connections supported by bluetooth
#define CONFIG_BT_MAX_CONN 1

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)


class BluetoothModule
{
    public:
    BluetoothModule();
    void startScanning();
    void startAdvertising();
};

#endif