# DroneCAN with libcanard
--------------------------
## Table of contents
1. Introduction
2. API reference
------------------------------  
# 1. Introduction  
The library is in charge of managing the DroneCAN messages to have a DroneCAN node. The intention is to have a simple library to manage messages without too much effort.  
  
This library needs the implementation of a simple CAN driver. The [CAN_bus_adaptor.h](https://github.com/aralce/DroneCAN_service_API/blob/develop/CAN_bus_adaptor.h) contains the prototype of the interface.  
Read and send frames are the only two functions required.
  
# 2. API reference  
The library has 3 files to have in mind:  
- DroneCAN_service_api.h: Contains the interface for use in the library.  
- DroneCAN_service_configuration.h: Contains important configurations as the desired pins to use for CAN bus and CAN bus baud rate.   
- CAN_bus_adaptor.h: Interface for the CAN bus driver. It is required to implement read and send frame functions. 

### DroneCAN_service_api.h  
#### Initialization  
The way to use the API is creating an instance of DroneCAN_service class:  
```
DroneCAN_service droneCAN_service
```  
  
You can instantiate the droneCAN_service with an NODE_ID defined:  
```  
const uint8_t NODE_ID = 42;
DroneCAN_service droneCAN_service(NODE_ID);
```  
if the node is not defined on instantiation, then the NODE_ID assignated to the device will be the DEFAULT_NODE_ID located on Drone_CAN_service_configuration.h  
  
You have the option of instantiate the DroneCAN_service with an error handle function:  
```  
void handle_droneCAN_error(DroneCAN_error error){
  /** Feel free to complete with you code **/
}
  
DroneCAN_service droneCAN_service(handle_droneCAN_error);
```  
Each time the droneCAN_service detects an error, this function will be called as a callback function. The DroneCAN_error enum class argument contains the type of the error triggered.  

#### Running the pending tasks  
As the library doesn't have a RTOS as its framework (it can be used in baremetal or with an RTOS) it needs to call a function to run the neccesary task on background.
This function is called: `run_pending_tasks`  
```  
void loop() {
  unsigned long actual_time = millis();
  droneCAN_service.run_pending_tasks(actual_time);
}
```
***`run_pending_tasks` returns the ms necessary for the next call to the function. Since DroneCAN msg have a great tolerance, the next time to call the function can vary in at least 100ms*** 

#### Register a message to publish  
The library can register a message to be published on intervals of time defined by the user. By the moment, the library only supports batteryInfo messages. To register a battery message you need to provide a function to get the battery info:  
```  
CAN_bus_adaptor can_driver;
DroneCAN_service droneCAN_service(can_driver);  
  
uavcan_equipment_power_BatteryInfo msg_to_send; //Complete the struct with the values you want to send
  
void setup()
{  
  const int MILLISECONDS_BETWEEN_BATTERY_MESSAGE_PUBLISH = 500;  
  droneCAN_service.publish_regularly(get_battery_info, MILLISECONDS_BETWEEN_BATTERY_MESSAGE_PUBLISH);
}  
  
void loop()
{
  unsigned long actual_time = millis();
  droneCAN_service.run_pending_tasks(actual_time);

  if (need_to_change_param_in_msg_to_send)
  {
    msg_to_send.param = new_value;
  }
}  
```

### Apendix
+ [How to compile DSDL for DroneCAN](https://github.com/aralce/dronecan_with_libcanard/blob/master/docs/compile_DSDL_for_DroneCAN.md)
+ [How to run the Unit Tests](https://github.com/aralce/dronecan_with_libcanard/blob/develop/tests/README.md)
