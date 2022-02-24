// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2022 TTG <prs.ttg+alonira@pm.me>

#include "include/alocom.h"

const char* alo_error_name(const alo_error_t error) {
	switch(error) {
		case ALO_OK: return "ALO_OK";
		case ALO_UNKNOWN: return "ALO_UNKNOWN";
		case ALO_PERMISSION: return "ALO_PERMISSION";
		case ALO_INVALID_PARAMETER: return "ALO_INVALID_PARAMETER";
		case ALO_IO: return "ALO_IO";
		case ALO_TOO_LONG: return "ALO_TOO_LONG";
		case ALO_NO_SUCH_OBJECT: return "ALO_NO_SUCH_OBJECT";
		case ALO_OUT_OF_MEMORY: return "ALO_OUT_OF_MEMORY";
		case ALO_WRONG_OBJECT_TYPE: return "ALO_WRONG_OBJECT_TYPE";
		case ALO_ALREADY_EXISTS: return "ALO_ALREADY_EXISTS";
		case ALO_OUT_OF_SPACE: return "ALO_OUT_OF_SPACE";
		case ALO_OUT_OF_HANDLES: return "ALO_OUT_OF_HANDLES";
		case ALO_TOO_SHORT: return "ALO_TOO_SHORT";
		case ALO_BAD_CONTENT: return "ALO_BAD_CONTENT";
		case ALO_BAD_OPERATION: return "ALO_BAD_OPERATION";
		case ALO_IN_USE: return "ALO_IN_USE";
		case ALO_NOT_IMPLEMENTED: return "ALO_NOT_IMPLEMENTED";
		case ALO_OUT_OF_BOUNDS: return "ALO_OUT_OF_BOUNDS";
		case ALO_INVALID_CONTROL: return "ALO_INVALID_CONTROL";
		case ALO_BAD_ALIGNMENT: return "ALO_BAD_ALIGNMENT";
	}
}

const char* alo_error_description(const alo_error_t error) {
	switch(error) {
		case ALO_OK: return "No error occurred";
		case ALO_UNKNOWN: return "An unknown error occurred";
		case ALO_PERMISSION: return "A permission error occurred";
		case ALO_INVALID_PARAMETER: return "The provided parameter was invalid";
		case ALO_IO: return "An IO error occurred";
		case ALO_TOO_LONG: return "The provided argument is too long";
		case ALO_NO_SUCH_OBJECT: return "A nonexistent object was referenced";
		case ALO_OUT_OF_MEMORY: return "Program ran out of usable memory";
		case ALO_WRONG_OBJECT_TYPE: return "An object of the wrong type was provided";
		case ALO_ALREADY_EXISTS: return "An object already exists by the provided identifier";
		case ALO_OUT_OF_SPACE: return "The specified destination is out of space";
		case ALO_OUT_OF_HANDLES: return "Too many platform handles are open";
		case ALO_TOO_SHORT: return "The provided argument is too short";
		case ALO_BAD_CONTENT: return "The provided argument contains bad or invalid content";
		case ALO_BAD_OPERATION: return "A bad or invalid operation was requested";
		case ALO_IN_USE: return "The specified target is in use elsewhere";
		case ALO_NOT_IMPLEMENTED: return "An unimplemented feature was used";
		case ALO_OUT_OF_BOUNDS: return "The specified value is out of bounds";
		case ALO_INVALID_CONTROL: return "The program reached an invalid control path";
		case ALO_BAD_ALIGNMENT: return "The provided data was misaligned";
	}
}
