#include <common_to_all_tests.h>
#include <Canard_wrapper.h>
#include <support/Canard_spy.h>
#include <DroneCAN_service_configuration.h>
#include <CAN_BUS_adaptor/CAN_bus_adaptor.h>

#include <typeinfo>

TEST_GROUP(Canard_wrapper)
{
    CanardCANFrame_comparator CanardCANFrame_t;
    void setup()
    {
        mock().installComparator("CanardCANFrame", CanardCANFrame_t);
    }
    
    void teardown()
    {
        mock().checkExpectations();
        mock().clear();
        mock().removeAllComparatorsAndCopiers();
    }
};

Canard get_canard_instance()
{
    Canard canard;
    return canard;
}

TEST(Canard_wrapper, init)
{
    Canard canard = get_canard_instance();
    size_t buffer_size = LIBCANARD_ALLOCATION_BUFFER_IN_BYTES;
    mock().expectOneCall("canardInit")
          .withUnsignedLongLongIntParameter("mem_arena_size", buffer_size);
    CHECK_TRUE(typeid(buffer_size) == typeid(size_t));
    
    canard.init();
}

TEST(Canard_wrapper, set_node_ID)
{
    Canard canard = get_canard_instance();
    const uint8_t CANARD_NODE_ID = 40;
    
    canard.set_node_ID(CANARD_NODE_ID);

    Canard_spy spy(canard);
    uint8_t node_id = spy.get_node_id();

    CHECK_EQUAL(CANARD_NODE_ID, node_id);
}

    canard_message_type_info_t message_type_info = {.signature = 4,
                                                    .id = 99,
                                                    .priority = CANARD_TRANSFER_PRIORITY_MEDIUM};
    uint8_t data[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    canard_message_data_t message_data = {.ptr = data, .length = 8};
    const uint16_t RETURN_VALUE = 16;
TEST(Canard_wrapper, broadCast)
{
    Canard canard = get_canard_instance();
    
    mock().expectOneCall("canardBroadcast")
          .withUnsignedLongLongIntParameter("data_type_signature", message_type_info.signature)
          .withUnsignedIntParameter("data_type_id", message_type_info.id)
          .withUnsignedIntParameter("priority", message_type_info.priority)
          .withPointerParameter("payload", message_data.ptr)
          .withUnsignedIntParameter("payload_len", message_data.length)
          .andReturnValue(RETURN_VALUE);

    CHECK_EQUAL(RETURN_VALUE, canard.broadcast(message_type_info, message_data));
}

TEST(Canard_wrapper, send_response)
{
    Canard canard = get_canard_instance();

    uint8_t DESTINATION_NODE_ID = 40;
    mock().expectOneCall("canardRequestOrRespond")
          .withUnsignedIntParameter("destination_node_id", DESTINATION_NODE_ID)
          .withUnsignedLongLongIntParameter("data_type_signature", message_type_info.signature)
          .withUnsignedIntParameter("data_type_id", message_type_info.id)
          .withUnsignedIntParameter("priority", message_type_info.priority)
          .withPointerParameter("payload", (void*)message_data.ptr)
          .withUnsignedIntParameter("payload_len", message_data.length)
          .andReturnValue(RETURN_VALUE);
    
    canard.send_response(DESTINATION_NODE_ID, message_type_info, message_data);
}

TEST(Canard_wrapper, peekTxQueue)
{
    Canard canard = get_canard_instance();

    CanardCANFrame can_frame{};
    mock().expectOneCall("canardPeekTxQueue")
          .andReturnValue((void*)&can_frame);

    CHECK_EQUAL(&can_frame, canard.peekTxQueue());
}

TEST(Canard_wrapper, popTxQueue)
{
    Canard canard = get_canard_instance();

    mock().expectOneCall("canardPopTxQueue");
    canard.popTxQueue();
}

TEST(Canard_wrapper, is_txQueue_empty_return_the_queue_has_data)
{
    Canard canard = get_canard_instance();

    CanardCANFrame can_frame{};
    mock().expectOneCall("canardPeekTxQueue")
          .andReturnValue((void*)&can_frame);
    
    CHECK_FALSE(canard.is_txQueue_empty());
}

TEST(Canard_wrapper, is_txQueue_empty_returns_the_queue_is_empty)
{
    Canard canard = get_canard_instance();

    mock().expectOneCall("canardPeekTxQueue")
          .andReturnValue((void*)NULL);

    CHECK_TRUE(canard.is_txQueue_empty());
}

TEST(Canard_wrapper, handle_rx_frame)
{
    Canard canard = get_canard_instance();

    CanardCANFrame canard_frame{.id = 67, .data = {1,2,3,4}, .data_len = 4};
    uint64_t TIMESTAMP_MICROSECONDS = 10000;
    int16_t ERROR_CODE = -99;

    canard_frame.id = 67 | CANARD_CAN_FRAME_EFF; // The wrapper should apply this flag.
    mock().expectOneCall("canardHandleRxFrame")
          .withParameterOfType("CanardCANFrame","frame", (void*)&canard_frame)
          .withUnsignedLongLongIntParameter("timestamp_usec", TIMESTAMP_MICROSECONDS)
          .andReturnValue(ERROR_CODE);

    int16_t returned_value = canard.handle_rx_frame(canard_frame, TIMESTAMP_MICROSECONDS);
    CHECK_EQUAL(ERROR_CODE, returned_value);
}

TEST(Canard_wrapper, release_rx_memory)
{
    Canard canard = get_canard_instance();

    CanardRxTransfer rx_transfer{};

    mock().expectOneCall("canardReleaseRxTransferPayload")
          .withPointerParameter("transfer", (void*)&rx_transfer);

    canard.release_rx_memory(&rx_transfer);
}