// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 Emily "TTG" Banerjee <prs.ttg+alonira@pm.me>

#include "include/serial.h"

#include "include/kio.h"

#include <gencommon.h>
#include <genstring.h>

// TODO: Exclusive access to each serial port - mutex

gen_error_t* alo_serial_set(const alo_serial_com_port_t com_port, const uint16_t baud, const alo_serial_data_width_t data_width, const alo_serial_stop_bit_width_t stop_bit_width, const alo_serial_parity_mode_t parity_mode, const alo_serial_interrupt_mode_t interrupt_mode) {
	GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_serial_set, GEN_FILE_NAME);
	if(error) return error;

    // TODO: De-magic this - move out port bitfields into structs

	const uint16_t baud_divisor = (uint16_t) 115200 / baud;
	alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL), 0b10000000 | alo_port_in_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL)));
	alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_BAUD_DIVISOR_LSB), (uint8_t) ((baud_divisor << 8) >> 8));
	alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_BAUD_DIVISOR_MSB), (uint8_t) (baud_divisor >> 8));
	alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL), ~0b10000000 & alo_port_in_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL)));

	switch(data_width) {
		case ALO_SERIAL_DATA_WIDTH_5: {
			alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL), ~0b00000011 & alo_port_in_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL)));
			break;
		}
		case ALO_SERIAL_DATA_WIDTH_6: {
			alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL), 0b00000001 | alo_port_in_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL)));
			alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL), ~0b00000010 & alo_port_in_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL)));
			break;
		}
		case ALO_SERIAL_DATA_WIDTH_7: {
			alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL), ~0b00000001 & alo_port_in_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL)));
			alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL), 0b00000010 | alo_port_in_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL)));
			break;
		}
		case ALO_SERIAL_DATA_WIDTH_8: {
			alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL), 0b00000011 | alo_port_in_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL)));
			break;
		}
	}

	switch(stop_bit_width) {
		case ALO_SERIAL_STOP_BIT_1: {
			alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL), ~0b00000100 & alo_port_in_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL)));
			break;
		}
		case ALO_SERIAL_STOP_BIT_1_5:
		case ALO_SERIAL_STOP_BIT_2: {
			alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL), 0b00000100 | alo_port_in_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL)));
			break;
		}
	}

	switch(parity_mode) {
		case ALO_SERIAL_PARITY_NONE: {
			alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL), ~0b00011100 & alo_port_in_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL)));
			break;
		}
		case ALO_SERIAL_PARITY_ODD: {
			alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL), ~0b00110000 & alo_port_in_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL)));
			alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL), 0b00001000 | alo_port_in_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL)));
			break;
		}
		case ALO_SERIAL_PARITY_EVEN: {
			alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL), ~0b00100000 & alo_port_in_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL)));
			alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL), 0b00011000 | alo_port_in_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL)));
			break;
		}
		case ALO_SERIAL_PARITY_MARK: {
			alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL), ~0b00010000 & alo_port_in_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL)));
			alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL), 0b00101000 | alo_port_in_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL)));
			break;
		}
		case ALO_SERIAL_PARITY_SPACE: {
			alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL), 0b00111000 | alo_port_in_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_CONTROL)));
			break;
		}
	}

	alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_INTERRUPT_ENABLE), ~0b00001111 & alo_port_in_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_INTERRUPT_ENABLE)));
	alo_port_out_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_INTERRUPT_ENABLE), (uint8_t) interrupt_mode | alo_port_in_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_INTERRUPT_ENABLE)));

	return NULL;
}

gen_error_t* alo_serial_send(const alo_serial_com_port_t com_port, const char data) {
	GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_serial_send, GEN_FILE_NAME);
	if(error) return error;

	while((alo_port_in_byte((uint16_t) (com_port + ALO_SERIAL_PORT_REGISTER_LINE_STATUS)) & 0b00100000) == 0)
		;

	alo_port_out_byte((uint16_t) (com_port), (uint8_t) data);

	return NULL;
}

gen_error_t* alo_serial_send_string(const alo_serial_com_port_t com_port, const char* const restrict data) {
	GEN_TOOLING_AUTO gen_error_t* error = gen_tooling_push(GEN_FUNCTION_NAME, (void*) alo_serial_send_string, GEN_FILE_NAME);
	if(error) return error;

	if(!data) return gen_error_attach_backtrace(GEN_ERROR_INVALID_PARAMETER, GEN_LINE_NUMBER, "`data` was `NULL`");

	size_t length = 0;
	error = gen_string_length(data, GEN_STRING_NO_BOUNDS, GEN_STRING_NO_BOUNDS, &length);
	if(error) return error;

	for(size_t i = 0; i < length; ++i) {
		error = alo_serial_send(com_port, data[i]);
		if(error) return error;
	}

	return NULL;
}
