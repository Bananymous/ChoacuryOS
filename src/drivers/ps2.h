#pragma once

#include "ps2_keyboard.h"

#define PS2_TYPE_NONE		0
#define PS2_TYPE_KEYBOARD	1

#define PS2_COMMAND_QUEUE_SIZE 32
#define PS2_BYTE_BUFFER_SIZE 32
#define PS2_EVENT_QUEUE_SIZE 32

typedef struct ps2_device_t {
    u8 type;

    u8 byte_buffer_len;
    u8 byte_buffer[PS2_BYTE_BUFFER_SIZE];

    /* TODO: Add other types of events to this union */
    u8 event_queue_len;
    union {
        struct {
            ps2_key_event_t keyboard_event_queue[PS2_EVENT_QUEUE_SIZE];
            ps2_keyboard_info keyboard_info;
        };
    };
} ps2_device_t;

void ps2_init();
void ps2_device_append_command_queue(ps2_device_t* device, u8 command, u8 response_size);
void ps2_device_append_command_queue_with_data(ps2_device_t* device, u8 command, u8 data, u8 response_size);
ps2_device_t* ps2_get_device(u8 index);
