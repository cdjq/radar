// Copyright (c) Acconeer AB, 2018-2019
// All rights reserved

#ifndef ACC_HAL_DEFINITIONS_H_
#define ACC_HAL_DEFINITIONS_H_

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "acc_definitions.h"


/**
 * @brief Defines the largest allowed value of a sensor ID
 */
#define ACC_SENSOR_ID_MAX 32

/**
 * @brief Specifies the minimal size in bytes that SPI transfers must be able to handle
 */
#define ACC_SPI_TRANSFER_SIZE_REQUIRED 16


/**
 * @defgroup OS OS Integration
 * @ingroup Integration
 *
 * @brief Integration OS primitives
 *
 * @{
 */


/**
 * @brief Definition of a memory allocation function
 *
 * Must be implemented by integration. Returning NULL is seen as failure.
 */
typedef void *(*acc_os_mem_alloc_function_t)(size_t);


/**
 * @brief Definition of a memory free function
 *
 * Must be implemented by integration.
 */
typedef void (*acc_os_mem_free_function_t)(void *);


/**
 * @brief Definition of a time retrival function
 *
 * The time returned must be in milliseconds.
 *
 * Must be implemented by integration.
 */
typedef uint32_t (*acc_os_get_time_function_t)(void);


/**
 * @brief Struct that contains the implementation of os integration primitives
 */
typedef struct
{
	acc_os_mem_alloc_function_t mem_alloc;
	acc_os_mem_free_function_t  mem_free;
	acc_os_get_time_function_t  gettime;
} acc_integration_os_primitives_t;

/**
 * @}
 */


/**
 * @defgroup HAL Hardware Integration
 * @ingroup Integration
 *
 * @brief Integration of Hardware Abstraction Layer for the radar sensor
 *
 * @{
 */


/**
 * @brief Definition of a sensor power function
 *
 * In the case of the power_on function:
 * Any pending sensor interrupts should be cleared before returning from function.
 */
typedef void (*acc_hal_sensor_power_function_t)(acc_sensor_id_t sensor_id);


/**
 * @brief Definition of a hal get frequency function
 */
typedef float (*acc_hal_get_frequency_function_t)(void);


/**
 * @brief Definition of a wait for sensor interrupt function
 *
 * This function shall wait at most timeout_ms for the interrupt to become active and
 * then return true. It may return true immediately if an interrupt have
 * occurred since last call to this function.
 *
 * If waited more than timeout_ms for the interrupt to become active it shall
 * return false.
 *
 * Note that this function can be called with a timeout_ms = 0.
 *
 */
typedef bool (*acc_hal_sensor_wait_for_interrupt_function_t)(acc_sensor_id_t sensor_id, uint32_t timeout_ms);


/**
 * @brief Definition of a sensor transfer function
 */
typedef void (*acc_hal_sensor_transfer_function_t)(acc_sensor_id_t sensor_id, uint8_t *buffer, size_t buffer_size);


/**
 * @brief This struct contains function pointers that point to
 *        functions needed for communication with the radar sensor.
 */
typedef struct
{
	acc_hal_sensor_power_function_t              power_on;
	acc_hal_sensor_power_function_t              power_off;
	acc_hal_sensor_wait_for_interrupt_function_t wait_for_interrupt;
	acc_hal_sensor_transfer_function_t           transfer;
	acc_hal_get_frequency_function_t             get_reference_frequency;
} acc_integration_sensor_device_t;

/**
 * @}
 */


/**
 * @defgroup Properties Integration Properties
 * @ingroup Integration
 *
 * @brief Driver and board specific properties
 *
 * @{
 */


/**
 * @brief This struct contains information about board properties that
 *        are needed by RSS.
 *
 * @ref sensor_count is the maximal sensor ID that the integration layer supports.
 * This value must not exceed @ref ACC_SENSOR_ID_MAX.
 *
 * @ref max_spi_transfer_size is zero or the maximal buffer size that is supported
 * by the implementation of @ref acc_hal_sensor_transfer_function_t. Use a zero value
 * to indicate that there is no restriction. Otherwise, this value must not be smaller
 * than @ref ACC_SPI_TRANSFER_SIZE_REQUIRED.
 */
typedef struct
{
	uint32_t sensor_count;
	size_t   max_spi_transfer_size;
} acc_integration_properties_t;

/**
 * @}
 */


/**
 * @defgroup Log Log Integration
 * @ingroup Integration
 *
 * @brief Integration for log functionality
 *
 * @{
 */


/**
 * @brief This enum represents the different log levels for RSS
 */
typedef enum
{
	ACC_LOG_LEVEL_ERROR,
	ACC_LOG_LEVEL_WARNING,
	ACC_LOG_LEVEL_INFO,
	ACC_LOG_LEVEL_VERBOSE,
	ACC_LOG_LEVEL_DEBUG
} acc_log_level_enum_t;
typedef uint32_t acc_log_level_t;


/**
 * @brief Definition of a log function
 */
typedef void (*acc_log_function_t)(acc_log_level_t level, const char *module, const char *buffer);


/**
 * @brief This struct contains information about log properties and functions
 *        needed by RSS
 */
typedef struct
{
	acc_log_level_t    log_level;
	acc_log_function_t log;
} acc_integration_log_t;


/**
 * @}
 */


/**
 * @defgroup Integration Integration
 * @brief Driver and OS Integration
 *
 * @{
 */


/**
 * @brief This struct contains the information about the sensor
 *        integration that RSS needs.
 */

typedef struct
{
	acc_integration_properties_t    properties;
	acc_integration_os_primitives_t os;
	acc_integration_sensor_device_t sensor_device;
	acc_integration_log_t           log;
} acc_hal_t;

/**
 * @}
 */


#endif
