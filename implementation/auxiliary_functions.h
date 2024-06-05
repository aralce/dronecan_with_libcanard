#ifndef AUXILIARY_FUNCTIONS_H_
#define AUXILIARY_FUNCTIONS_H_
#include <cstring>
#include "uavcan_driver/uavcan_messages/uavcan.protocol.param.Value.h"
// #include <uavcan.protocol.param.NumericValue.h>
#include "uavcan_driver/uavcan_messages/uavcan.protocol.param.NumericValue.h"

#define UAVCAN_PARAM_VALUE_MAX_NAME_LENGTH 128

uavcan_protocol_param_Value package_uavcan_param_value(int32_t value_to_package);
uavcan_protocol_param_Value package_uavcan_param_value(int64_t value_to_package);
uavcan_protocol_param_Value package_uavcan_param_value(float value_to_package);
uavcan_protocol_param_Value package_uavcan_param_value(bool value_to_package);

uavcan_protocol_param_Value package_uavcan_param_value(const uint8_t* value_to_package);
uavcan_protocol_param_Value package_uavcan_param_value(const char* value_to_package);

uavcan_protocol_param_Value package_uavcan_param_value_empty();

uavcan_protocol_param_NumericValue package_uavcan_param_numeric_value(int32_t value_to_package);
uavcan_protocol_param_NumericValue package_uavcan_param_numeric_value(float value_to_package);

uavcan_protocol_param_NumericValue package_uavcan_param_numeric_value_empty();

#endif // AUXILIARY_FUNCTIONS_H_