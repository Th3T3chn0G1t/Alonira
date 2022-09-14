// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#ifndef ALO_SERIAL_H
#define ALO_SERIAL_H

#include <gencommon.h>

#define ALO_ANSI_COLOR_BLACK "30"
#define ALO_ANSI_COLOR_RED "31"
#define ALO_ANSI_COLOR_GREEN "32"
#define ALO_ANSI_COLOR_YELLOW "33"
#define ALO_ANSI_COLOR_BLUE "34"
#define ALO_ANSI_COLOR_MAGENTA "35"
#define ALO_ANSI_COLOR_CYAN "36"
#define ALO_ANSI_COLOR_WHITE "37"
#define ALO_ANSI_BOLD "1"
#define ALO_ANSI_CLEAR "0"
#define ALO_INTERNAL_ANSI_SEQUENCE_PREFIX "\033["
#define ALO_INTERNAL_ANSI_SEQUENCE_SUFFIX "m"
#define ALO_INTERNAL_ANSI_COLOR_DARK_PREFIX "0;"
#define ALO_INTERNAL_ANSI_COLOR_LIGHT_PREFIX "1;"
#define ALO_ANSI_SEQUENCE(code) ALO_INTERNAL_ANSI_SEQUENCE_PREFIX code ALO_INTERNAL_ANSI_SEQUENCE_SUFFIX
#define ALO_ANSI_COLOR_DARK(color) ALO_ANSI_SEQUENCE(ALO_INTERNAL_ANSI_COLOR_DARK_PREFIX color)
#define ALO_ANSI_COLOR_LIGHT(color) ALO_ANSI_SEQUENCE(ALO_INTERNAL_ANSI_COLOR_LIGHT_PREFIX color)


typedef enum ALO_PACKED {
    ALO_SERIAL_COM1 = 0x3F8,
    ALO_SERIAL_COM2 = 0x2F8,
    ALO_SERIAL_COM3 = 0x3E8,
    ALO_SERIAL_COM4 = 0x2E8,
    ALO_SERIAL_COM5 = 0x5F8,
    ALO_SERIAL_COM6 = 0x4F8,
    ALO_SERIAL_COM7 = 0x5E8,
    ALO_SERIAL_COM8 = 0x4E8 
} alo_serial_com_port_t;

typedef enum {
    ALO_SERIAL_PORT_REGISTER_DATA = 0,
    ALO_SERIAL_PORT_REGISTER_INTERRUPT_ENABLE = 1,
    ALO_SERIAL_PORT_REGISTER_BAUD_DIVISOR_LSB = 0,
    ALO_SERIAL_PORT_REGISTER_BAUD_DIVISOR_MSB = 1,
    ALO_SERIAL_PORT_REGISTER_INTERRUPT_ID = 2,
    ALO_SERIAL_PORT_REGISTER_LINE_CONTROL = 3,
    ALO_SERIAL_PORT_REGISTER_MODEM_CONTROL = 4,
    ALO_SERIAL_PORT_REGISTER_LINE_STATUS = 5,
    ALO_SERIAL_PORT_REGISTER_MODEM_STATUS = 6,
    ALO_SERIAL_PORT_REGISTER_SCRATCH = 7
} alo_serial_port_register_t;

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

typedef enum ALO_FLAG_ENUM {
    ALO_SERIAL_INTERRUPT_NONE,
    ALO_SERIAL_INTERRUPT_DATA_NOTIFY = 1 << 0,
    ALO_SERIAL_INTERRUPT_SEND_COMPLETE = 1 << 1,
    ALO_SERIAL_INTERRUPT_ERROR = 1 << 2,
    ALO_SERIAL_INTERRUPT_STATUS_NOTIFY = 1 << 3
} alo_serial_interrupt_mode_t;

extern gen_error_t* alo_serial_set(const alo_serial_com_port_t com_port, const uint16_t baud, const alo_serial_data_width_t data_width, const alo_serial_stop_bit_width_t stop_bit_width, const alo_serial_parity_mode_t parity_mode, const alo_serial_interrupt_mode_t interrupt_mode);
extern gen_error_t* alo_serial_send(const alo_serial_com_port_t com_port, const char data);
extern gen_error_t* alo_serial_send_string(const alo_serial_com_port_t com_port, const char* const restrict data);

#endif
