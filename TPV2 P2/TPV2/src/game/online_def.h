#pragma once
#include "ecs_def.h"

// Mensajes para enviar a través de internet

struct online_message {
	enum _msg_id : unsigned char {
		msg_PLACEHOLDER,

		// Do not erase pls
		msg_INVALID
	};

	_msg_id id;

	struct {
		uint8_t dataUint;
		char dataChar;
		int dataInt;
		ecs::cmpId dataCmpId;
		float dataFloat;
	} data_placeholder;
};
