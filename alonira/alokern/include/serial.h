// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#ifndef ALO_SERIAL_H
#define ALO_SERIAL_H

#include <alocom.h>
#include "kio.h"

typedef enum __packed {
    ALO_SERIAL_COM1 = 0x3F8,
    ALO_SERIAL_COM2 = 0x2F8,
    ALO_SERIAL_COM3 = 0x3E8,
    ALO_SERIAL_COM4 = 0x2E8,
    ALO_SERIAL_COM5 = 0x5F8,
    ALO_SERIAL_COM6 = 0x4F8,
    ALO_SERIAL_COM7 = 0x5E8,
    ALO_SERIAL_COM8 = 0x4E8 
} alo_serial_com_port_t;

#define ALO_SERIAL_PORT_REGISTER_DATA 0
#define ALO_SERIAL_PORT_REGISTER_INTERRUPT_ENABLE 1
#define ALO_SERIAL_PORT_REGISTER_BAUD_DIVISOR_LSB 0
#define ALO_SERIAL_PORT_REGISTER_BAUD_DIVISOR_MSB 1
#define ALO_SERIAL_PORT_REGISTER_INTERRUPT_ID 2
#define ALO_SERIAL_PORT_REGISTER_LINE_CONTROL 3
#define ALO_SERIAL_PORT_REGISTER_MODEM_CONTROL 4
#define ALO_SERIAL_PORT_REGISTER_LINE_STATUS 5
#define ALO_SERIAL_PORT_REGISTER_MODEM_STATUS 6
#define ALO_SERIAL_PORT_REGISTER_SCRATCH 7

typedef enum {
    ALO_SERIAL_DATA_WIDTH_5,
    ALO_SERIAL_DATA_WIDTH_6,
    ALO_SERIAL_DATA_WIDTH_7,
    ALO_SERIAL_DATA_WIDTH_8
} alo_serial_data_width_t;

typedef enum {
    ALO_SERIAL_STOP_BIT_1,
    ALO_SERIAL_STOP_BIT_1_5,
    ALO_SERIAL_STOP_BIT_2
} alo_serial_stop_bit_width_t;

typedef enum {
    ALO_SERIAL_PARITY_NONE,
    ALO_SERIAL_PARITY_ODD,
    ALO_SERIAL_PARITY_EVEN,
    ALO_SERIAL_PARITY_MARK,
    ALO_SERIAL_PARITY_SPACE
} alo_serial_parity_mode_t;

enum {
    ALO_SERIAL_INTERRUPT_NONE = 0,
    ALO_SERIAL_INTERRUPT_DATA_NOTIFY = 1 << 0,
    ALO_SERIAL_INTERRUPT_SEND_COMPLETE = 1 << 1,
    ALO_SERIAL_INTERRUPT_ERROR = 1 << 2,
    ALO_SERIAL_INTERRUPT_STATUS_NOTIFY = 1 << 3
};

typedef uint8_t alo_serial_interrupt_mode_t;

ALO_DIAGNOSTIC_REGION_BEGIN
#pragma clang diagnostic ignored "-Wgnu-binary-literal"

static __forceinline __nodiscard alo_error_t alo_serial_set(const alo_serial_com_port_t com_port, const uint16_t baud, const alo_serial_data_width_t data_width, const alo_serial_stop_bit_width_t stop_bit_width, const alo_serial_parity_mode_t parity_mode, const alo_serial_interrupt_mode_t interrupt_mode) {
    ALO_FRAME_BEGIN(alo_serial_set);

    const uint16_t baud_divisor = (uint16_t) 115200 / baud;
    alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL, 0b10000000 | alo_port_in_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL));
    alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_BAUD_DIVISOR_LSB, (uint8_t) ((baud_divisor << 8) >> 8));
    alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_BAUD_DIVISOR_MSB, (uint8_t) (baud_divisor >> 8));
    alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL, ~0b10000000 & alo_port_in_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL));

    switch(data_width) {
        case ALO_SERIAL_DATA_WIDTH_5: {
            alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL, ~0b00000011 & alo_port_in_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL));
            break;
        }
        case ALO_SERIAL_DATA_WIDTH_6: {
            alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL, 0b00000001 | alo_port_in_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL));
            alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL, ~0b00000010 & alo_port_in_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL));
            break;
        }
        case ALO_SERIAL_DATA_WIDTH_7: {
            alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL, ~0b00000001 & alo_port_in_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL));
            alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL, 0b00000010 | alo_port_in_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL));
            break;
        }
        case ALO_SERIAL_DATA_WIDTH_8: {
            alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL, 0b00000011 | alo_port_in_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL));
            break;
        }
    }

    switch(stop_bit_width) {
        case ALO_SERIAL_STOP_BIT_1: {
            alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL, ~0b00000100 & alo_port_in_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL));
            break;
        }
        case ALO_SERIAL_STOP_BIT_1_5:
        case ALO_SERIAL_STOP_BIT_2: {
            alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL, 0b00000100 | alo_port_in_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL));
            break;
        }
    }

    switch(parity_mode) {
        case ALO_SERIAL_PARITY_NONE: {
            alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL, ~0b00011100 & alo_port_in_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL));
            break;
        }
        case ALO_SERIAL_PARITY_ODD: {
            alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL, ~0b00110000 & alo_port_in_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL));
            alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL, 0b00001000 | alo_port_in_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL));
            break;
        }
        case ALO_SERIAL_PARITY_EVEN: {
            alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL, ~0b00100000 & alo_port_in_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL));
            alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL, 0b00011000 | alo_port_in_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL));
            break;
        }
        case ALO_SERIAL_PARITY_MARK: {
            alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL, ~0b00010000 & alo_port_in_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL));
            alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL, 0b00101000 | alo_port_in_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL));
            break;
        }
        case ALO_SERIAL_PARITY_SPACE: {
            alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL, 0b00111000 | alo_port_in_byte(com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL));
            break;
        }
    }

    alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_INTERRUPT_ENABLE, ~0b00001111 & alo_port_in_byte(com_port + ALO_SERIAL_PORT_REGISTER_INTERRUPT_ENABLE));
    alo_port_out_byte(com_port + ALO_SERIAL_PORT_REGISTER_INTERRUPT_ENABLE, interrupt_mode | alo_port_in_byte(com_port + ALO_SERIAL_PORT_REGISTER_INTERRUPT_ENABLE));

    ALO_ALL_OK;
}
ALO_DIAGNOSTIC_REGION_END

#endif
