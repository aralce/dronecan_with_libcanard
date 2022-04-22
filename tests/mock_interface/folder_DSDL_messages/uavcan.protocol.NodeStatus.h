#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>
#include <common_to_all_mocks.h>

#define UAVCAN_PROTOCOL_NODESTATUS_MAX_SIZE 7
#define UAVCAN_PROTOCOL_NODESTATUS_SIGNATURE (0xF0868D0C1A7C6F1ULL)
#define UAVCAN_PROTOCOL_NODESTATUS_ID 341

#define UAVCAN_PROTOCOL_NODESTATUS_MAX_BROADCASTING_PERIOD_MS 1000
#define UAVCAN_PROTOCOL_NODESTATUS_MIN_BROADCASTING_PERIOD_MS 2
#define UAVCAN_PROTOCOL_NODESTATUS_OFFLINE_TIMEOUT_MS 3000
#define UAVCAN_PROTOCOL_NODESTATUS_HEALTH_OK 0
#define UAVCAN_PROTOCOL_NODESTATUS_HEALTH_WARNING 1
#define UAVCAN_PROTOCOL_NODESTATUS_HEALTH_ERROR 2
#define UAVCAN_PROTOCOL_NODESTATUS_HEALTH_CRITICAL 3
#define UAVCAN_PROTOCOL_NODESTATUS_MODE_OPERATIONAL 0
#define UAVCAN_PROTOCOL_NODESTATUS_MODE_INITIALIZATION 1
#define UAVCAN_PROTOCOL_NODESTATUS_MODE_MAINTENANCE 2
#define UAVCAN_PROTOCOL_NODESTATUS_MODE_SOFTWARE_UPDATE 3
#define UAVCAN_PROTOCOL_NODESTATUS_MODE_OFFLINE 7

struct uavcan_protocol_NodeStatus {
    uint32_t uptime_sec;
    uint8_t health;
    uint8_t mode;
    uint8_t sub_mode;
    uint16_t vendor_specific_status_code;
};

uint32_t uavcan_protocol_NodeStatus_encode(struct uavcan_protocol_NodeStatus* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);

class Uavcan_protocol_NodeStatus_comparator : public MockNamedValueComparator
{
public:
    virtual bool isEqual(const void* object1, const void* object2)
    {
        uavcan_protocol_NodeStatus* msg_1 = (uavcan_protocol_NodeStatus*)object1;
        uavcan_protocol_NodeStatus* msg_2 = (uavcan_protocol_NodeStatus*)object2;

        if (msg_1->health != msg_2->health)
            return false;
        if (msg_1->mode != msg_2->mode)
            return false;
        if (msg_1->sub_mode != msg_2->sub_mode)
            return false;
        if (msg_1->uptime_sec != msg_2->uptime_sec)
            return false;
        if (msg_1->vendor_specific_status_code != msg_2->vendor_specific_status_code)
            return false;
        return true;
    }

    virtual SimpleString valueToString(const void* type_info)
    {
        return StringFrom(type_info);
    }
};