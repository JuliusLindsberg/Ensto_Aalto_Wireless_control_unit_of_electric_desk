#include "BluetoothModule.hpp"

#include <zephyr/types.h>
#include <stddef.h>
#include <sys/printk.h>
#include <sys/util.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include "DebugBlinker.hpp"


//#define DEVICE_NAME "CONFIG_BT_DEVICE_NAME"
//#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

static const struct bt_data ad[] = {
	/*BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_NO_BREDR),
	BT_DATA_BYTES(BT_DATA_UUID16_ALL, 0xaa, 0xfe),
	BT_DATA_BYTES(BT_DATA_SVC_DATA16,
		      0xaa, 0xfe, // Eddystone UUID
		      0x10, // Eddystone-URL frame type
		      0x00, // Calibrated Tx power at 0m
		      0x00, // URL Scheme Prefix http://www.
		      'z', 'e', 'p', 'h', 'y', 'r',
		      'p', 'r', 'o', 'j', 'e', 'c', 't',
		      0x08) // .org */
};

static const struct bt_data sd[] = {
	//BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};



bool initialized = false;


BluetoothModule::BluetoothModule()
{
    if(!initialized)
    {
        int err = 0;
        initialized = true;
        //err = bt_le_adv_start(BT_LE_ADV_NCONN, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
        if (err) {
            declareException();
	    }

    }
}