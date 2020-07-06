// Copyright (c) Acconeer AB, 2019
// All rights reserved

#include "main.h"

#include "acc_app_integration.h"

void acc_app_integration_sleep_us(uint32_t time_usec)
{
	uint32_t time_ms = time_usec / 1000;

	HAL_Delay(time_ms ? time_ms : 1);
}
