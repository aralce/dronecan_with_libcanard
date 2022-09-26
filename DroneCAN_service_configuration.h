#pragma once

#define DRONECAN_NODE_NAME "Upgrade Energy Tech -- Smart Battery"

#define CAN_BUS_BAUDRATE 1000000

#if defined (ESP32)  || defined (IS_RUNNING_TESTS)
    #define CAN_BUS_CRX_PIN 26
    #define CAN_BUS_CTX_PIN 25
#elif defined TARGET_RP2040
    #define CAN_BUS_CRX_PIN 0
    #define CAN_BUS_CTX_PIN 1
#endif

#define LIBCANARD_ALLOCATION_BUFFER_IN_BYTES 5000//minimun 1000 bytes

#define UAVCAN_MAX_BYTES_ON_MESSAGE 255 //UAVCAN_v1 up to 255 bytes

#define DEFAULT_NODE_ID 42
#define MICROSECONDS_BETWEEN_NODE_STATUS_PUBLISHES 500e3  //MIN: 2.000 - MAX: 1.000.000
#define NODE_STATUS_VENDOR_SPECIFIC_STATUS_CODE 500

#define MAX_NUMBER_OF_PARAMETERS 25

#define NAME_FOR_INVALID_PARAMETER "INVALID"

#define MS_TO_CONSIDER_CAN_BUS_INACTIVE  10e3 
