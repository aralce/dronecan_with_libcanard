#pragma once

#define CAN_BUS_BAUDRATE 10
#define CAN_BUS_RX_PIN 0
#define CAN_BUS_TX_PIN 1


#define LIBCANARD_ALLOCATION_BUFFER_IN_BYTES 2000  //minimun 1000 bytes

#define UAVCAN_MAX_BYTES_ON_MESSAGE 500 //UAVCAN_v1 up to 255 bytes

#define DEFAULT_NODE_ID 42
#define MILLISECONDS_BETWEEN_NODE_STATUS_PUBLISHES 500  //MIN: 2 - MAX: 1000
#define NODE_STATUS_VENDOR_SPECIFIC_STATUS_CODE 500