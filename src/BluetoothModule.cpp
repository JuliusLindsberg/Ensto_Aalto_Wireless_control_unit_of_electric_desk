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
#include <bluetooth/services/hrs.h>

const struct bt_uuid_16 tableControlUUID16 =
{
	.uuid = {BT_UUID_TYPE_16},
	.val = (TABLE_CONTROL_SERVICE_UUID)
};

//this is the actual data struct being sent through bluetooth low-energy. The size of this is hard-capped to 512 bytes defined by the bluetooth low-energy standard
typedef struct TableSteeringData
{
	//the new target height the user wants to reach
	int tableTargetHeight;
	//an integer which the service can use to differentiate between different users.
	//Currently there is no any sort of service in place that provides a fail-safe guarantee of uniqueness though
	int userIdentifier;
} TableSteeringData;

static TableSteeringData steeringData = {0, 0};
//callback functions associated with the GATT bluetooth low-energy layer

//this gets called when a GATT attribute has been received(?)
static ssize_t received(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf, uint16_t len, uint16_t offset)
{
	DebugPrinter printer;
	printer << "SteeringData received\n";
	return 0;
}
//this gets called when a GATT attribute has been written to(?)
static ssize_t written(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf, uint16_t len, uint16_t offset, uint8_t flags)
{
	DebugPrinter printer;
	printer << "SteeringData written\n";
	return 0;
}

//GATT attribute that carries with it the data payload required to steer the table
static struct bt_gatt_attr tableSteerRequest = 
{
	//WARNING: THE FOLLOWING LINE IS SHADY
	.uuid = (bt_uuid*)&tableControlUUID16,
	.read = received,
	.write = written,
	.user_data = &steeringData,
	.perm = (BT_GATT_PERM_READ | BT_GATT_PERM_WRITE)
};
static struct bt_gatt_service tableControlService =
{
	//we should be needing only one attribute here
	.attrs = &tableSteerRequest,
	.attr_count = 1
	//sys_snode_t node <- no idea what this is. Who knows if it's important
};

//the board keeps repeating sending this data to the air repeatedly (and then waits for potential connections?)
static const struct bt_data advertisingData[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_NO_BREDR),
	BT_DATA_BYTES(BT_DATA_UUID16_ALL, 0xaa, 0xfe),
	BT_DATA_BYTES(BT_DATA_SVC_DATA16,
		      0xaa, 0xfe, // Eddystone UUID
		      0x10, // Eddystone-URL frame type 
		      0x00, // Calibrated Tx power at 0m 
		      0x00, // URL Scheme Prefix http://www.
		      'z', 'e', 'p', 'h', 'y', 'r',
		      'p', 'r', 'o', 'j', 'e', 'c', 't',
		      0x08) // .org 
};

static const struct bt_data scanResponseData[] = {
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

//callback functions associated with the GATT bluetooth low-energy layer
namespace GAPCallbacks
{
	static void connected(struct bt_conn *connection, uint8_t error)
	{
		DebugPrinter printer;
		char address[BT_ADDR_LE_STR_LEN];

		bt_addr_le_to_str(bt_conn_get_dst(connection), address, sizeof(address));

		if (error) {
			declareException();
			return;
		}

		printer << "connected to: " << address << "\n";
	}

	static void disconnected(struct bt_conn *connection, uint8_t reason)
	{
		DebugPrinter printer;
		char address[BT_ADDR_LE_STR_LEN];

		bt_addr_le_to_str(bt_conn_get_dst(connection), address, sizeof(address));

		printer << "Disconnected from " << address << ". Reason: " << reason << "\n";
	}
};


struct bt_conn_cb connectionCallbacks
{
	.connected = GAPCallbacks::connected,
	.disconnected = GAPCallbacks::disconnected,
};


//this struct defines how the board sends advertisements
static struct bt_le_adv_param advertisingParameters =
{
	.id = BT_ID_DEFAULT,
	.sid = 0,
	.secondary_max_skip = 0,
	.options = (BT_LE_ADV_OPT_CONNECTABLE | BT_LE_ADV_OPT_SCANNABLE),
	.interval_min = BT_GAP_ADV_SLOW_INT_MIN,
	.interval_max = BT_GAP_ADV_SLOW_INT_MAX,
	.peer = NULL,
};

//callback when bluetooth is enabled
void bluetoothReady(int error)
{
	if (error) {
		declareException();
		return;
	}
	//the bluetooth module is ready for use: therefore we should begin advertising
	error = bt_le_adv_start(&advertisingParameters, advertisingData, ARRAY_SIZE(advertisingData),
			      scanResponseData, ARRAY_SIZE(scanResponseData));
	if (error) {
		declareException();
		return;
	}
	error = bt_register_gatt_service(&tableControlService);
	if(error)
	{
		declareException();
	}
}

void startBluetooth()
{
	bt_conn_cb_register(&connectionCallbacks);
	int error = bt_enable(bluetoothReady);
	if(error)
	{
		declareException();
	}
}