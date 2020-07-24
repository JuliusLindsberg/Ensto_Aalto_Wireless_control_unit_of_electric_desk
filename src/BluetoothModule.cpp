#include "BluetoothModule.hpp"
#include "DebugBlinker.hpp"
#include "DebugPrinter.hpp"

#include <zephyr/types.h>
#include <stddef.h>
#include <sys/printk.h>
#include <sys/util.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
#include <sys/byteorder.h>

bool initialized = false;

static struct bt_conn *defaultConnection = NULL;
static void deviceFound(const bt_addr_le_t *address, int8_t rssi, uint8_t type,
			 struct net_buf_simple *ad);

//as opposed to C code the configurations of some functionalities in zephyr's c++ are required to be done by using these kind of structs instead of
//some helper macros and then passed on as a reference to function calls. This is a severely undocumented phenomenom by zephyr's documentation.
//If using a helper macro claims "taking address of temporary array" that means one should refrain from using said marco and configure as a struct
// that the macro is defining instead.
static struct bt_le_scan_param blueToothScanConfig =
{
	.type = BT_LE_SCAN_TYPE_ACTIVE,
	.options = BT_LE_SCAN_OPT_FILTER_DUPLICATE,
	.interval = BT_GAP_SCAN_FAST_INTERVAL,
	.window = BT_GAP_SCAN_FAST_WINDOW,
	.timeout = 0,
	.interval_coded = 0,
	.window_coded = 0
};

static struct bt_conn_le_create_param createConnectionParameters = {
	.options = BT_CONN_LE_OPT_NONE,
	.interval = BT_GAP_SCAN_FAST_INTERVAL,
	.window = BT_GAP_SCAN_FAST_INTERVAL
};
//default connection parameters.
static struct bt_le_conn_param defaultConnectionParameters = {
	.interval_min = BT_GAP_INIT_CONN_INT_MIN,
	.interval_max = BT_GAP_INIT_CONN_INT_MAX,
	.latency = 0,
	.timeout = 400
};


//this has be a static function, as it might be used as a callback function
static void startBluetoothScan()
{
	int error;
	error = bt_le_scan_start(&blueToothScanConfig, deviceFound);
	if (error) {
		declareException();
	}
}



//a callback function
static void deviceFound(const bt_addr_le_t *address, int8_t rssi, uint8_t type,
			 struct net_buf_simple *ad)
{
	DebugBlinker ledOne(1);
	ledOne.ledOn();
	DebugPrinter printer;
	printer<<"\nRSSI: "<<rssi;

	char addressString[BT_ADDR_LE_STR_LEN];
	int error;

	/*if (defaultConnection) {
		return;
	}*/

	//We're only interested in connectable events
	if (type != BT_GAP_ADV_TYPE_ADV_IND &&
	    type != BT_GAP_ADV_TYPE_ADV_DIRECT_IND) {
		return;
	}

	bt_addr_le_to_str(address, addressString, sizeof(addressString));

	printer<<"\nAdderss: "<<addressString;
	// connect only to devices in close proximity
	if (rssi < -70) {
		return;
	}

	if (bt_le_scan_stop()) {
		return;
	}

	error = bt_conn_le_create(address, &createConnectionParameters,
				&defaultConnectionParameters, &defaultConnection);
	DebugBlinker ledThree(3);
	ledThree.ledOn();
	if (error) {
		startBluetoothScan();
		DebugBlinker ledTwo(2);
		ledTwo.ledOn();
	}
}


//a callback function
static void bluetoothConnected(struct bt_conn *connection, uint8_t error)
{
	char address[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(connection), address, sizeof(address));

	if (error) {

		bt_conn_unref(defaultConnection);
		defaultConnection = NULL;

		startBluetoothScan();
		return;
	}

	if (connection != defaultConnection) {
		return;
	}

	bt_conn_disconnect(connection, BT_HCI_ERR_REMOTE_USER_TERM_CONN);
}
//a callback function
static void bluetoothDisconnected(struct bt_conn *connection, uint8_t reason)
{
		char address[BT_ADDR_LE_STR_LEN];

	if (connection != defaultConnection) {
		return;
	}

	bt_addr_le_to_str(bt_conn_get_dst(connection), address, sizeof(address));

	bt_conn_unref(defaultConnection);
	defaultConnection = NULL;

	startBluetoothScan();
}

static struct bt_conn_cb connectionCallbacks = {
		.connected = bluetoothConnected,
		.disconnected = bluetoothDisconnected,
};


BluetoothModule::BluetoothModule()
{
    if(!initialized)
    {
        int error = 0;
        initialized = true;
        error = bt_enable(NULL);
		bt_conn_cb_register(&connectionCallbacks);
        if (error) {
            declareException();
	    }
    }
}

void BluetoothModule::startScanning()
{
	startBluetoothScan();
}

void BluetoothModule::startAdvertising()
{
	
}