// Copyright (c) Acconeer AB, 2018-2019
// All rights reserved

#ifndef ACC_DEFINITIONS_H_
#define ACC_DEFINITIONS_H_

#include <inttypes.h>
#include <stdint.h>


/**
 * @brief Type representing a sensor ID
 */
typedef uint32_t acc_sensor_id_t;

/**
 * @brief Macro for printing sensor id
 */
#define PRIsensor_id PRIu32


/**
 * @brief Data type for interger-based representation of complex numbers
 */
typedef struct
{
	int16_t real;
	int16_t imag;
} acc_int16_complex_t;


/**
 * Type used when retrieving and setting a sensor calibration context
 */
typedef struct
{
	uint8_t data[64];
} acc_calibration_context_t;


#endif
