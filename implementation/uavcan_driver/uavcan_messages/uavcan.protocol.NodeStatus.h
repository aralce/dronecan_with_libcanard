#pragma once
#include <stdbool.h>
#include <stdint.h>
// #include "canard.h"
#include "../canard.h"

#ifdef __cplusplus
extern "C"
{
#endif

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
bool uavcan_protocol_NodeStatus_decode(const CanardRxTransfer* transfer, struct uavcan_protocol_NodeStatus* msg);

#if defined(CANARD_DSDLC_INTERNAL)
static inline void _uavcan_protocol_NodeStatus_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_NodeStatus* msg, bool tao);
static inline void _uavcan_protocol_NodeStatus_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_NodeStatus* msg, bool tao);
void _uavcan_protocol_NodeStatus_encode(uint8_t* buffer, uint32_t* bit_ofs, struct uavcan_protocol_NodeStatus* msg, bool tao) {
    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;

    canardEncodeScalar(buffer, *bit_ofs, 32, &msg->uptime_sec);
    *bit_ofs += 32;
    canardEncodeScalar(buffer, *bit_ofs, 2, &msg->health);
    *bit_ofs += 2;
    canardEncodeScalar(buffer, *bit_ofs, 3, &msg->mode);
    *bit_ofs += 3;
    canardEncodeScalar(buffer, *bit_ofs, 3, &msg->sub_mode);
    *bit_ofs += 3;
    canardEncodeScalar(buffer, *bit_ofs, 16, &msg->vendor_specific_status_code);
    *bit_ofs += 16;
}

void _uavcan_protocol_NodeStatus_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct uavcan_protocol_NodeStatus* msg, bool tao) {
    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;

    canardDecodeScalar(transfer, *bit_ofs, 32, false, &msg->uptime_sec);
    *bit_ofs += 32;

    canardDecodeScalar(transfer, *bit_ofs, 2, false, &msg->health);
    *bit_ofs += 2;

    canardDecodeScalar(transfer, *bit_ofs, 3, false, &msg->mode);
    *bit_ofs += 3;

    canardDecodeScalar(transfer, *bit_ofs, 3, false, &msg->sub_mode);
    *bit_ofs += 3;

    canardDecodeScalar(transfer, *bit_ofs, 16, false, &msg->vendor_specific_status_code);
    *bit_ofs += 16;

}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct uavcan_protocol_NodeStatus sample_uavcan_protocol_NodeStatus_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"
#endif
