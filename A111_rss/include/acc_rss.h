// Copyright (c) Acconeer AB, 2018-2019
// All rights reserved

#ifndef ACC_RSS_H_
#define ACC_RSS_H_

#include <stdbool.h>

#include "acc_definitions.h"
#include "acc_hal_definitions.h"


/**
 * @defgroup RSS Radar System Software, RSS
 *
 * @brief Acconeer Radar System Software, RSS
 *
 * @{
 */


/**
 * @brief Activate the Acconeer Radar System Software, RSS
 *
 * A HAL struct containing integration functions (such as 'wait_for_interrupt', 'mem_alloc' and 'log')
 * needed by RSS must first be populated and then sent in. See 'acc_definitions.h' for a full list
 * of functions needed.
 *
 * This function must be called before any other RSS function. If it is not, or it failed,
 * calling any other RSS function is undefined behaviour.
 *
 * @param[in] hal Reference to a HAL struct containing integration functions that is needed by RSS
 * @return True if RSS activated successfully
 */
bool acc_rss_activate(acc_hal_t *hal);


/**
 * @brief Deactivate the Acconeer Radar System Software, RSS
 */
void acc_rss_deactivate(void);


/**
 * @brief Get the sensor calibration context
 *
 * Must be called after RSS has been activated.
 * A calibration will be done for the specific sensor.
 * A successful call to this function will also trigger context reset.
 *
 * @param[in] sensor_id The sensor to get the context for
 * @param[out] calibration_context Reference to struct where the context will be stored
 * @return True if successful, false otherwise
 */
bool acc_rss_calibration_context_get(acc_sensor_id_t sensor_id, acc_calibration_context_t *calibration_context);


/**
 * @brief Set a previously saved sensor calibration context and verify that the sensor calibration context is valid
 *
 * Must be called after RSS has been activated.
 * No active service is allowed on the sensor when setting the context.
 * If this function is successfully called, a new sensor calibration will not be done during service creation step.
 *
 * @param[in] sensor_id The sensor to set the context on
 * @param[in] calibration_context The calibration context to set
 *
 * @return True if successful, false otherwise
 */
bool acc_rss_calibration_context_set(acc_sensor_id_t sensor_id, acc_calibration_context_t *calibration_context);



/**
 * @brief Set a previously saved sensor calibration context, ignore the result from calibration context validation
 *
 * Must be called after RSS has been activated. Must only be used with a fresh calibration context
 * immediately after a successfull call to acc_rss_calibration_context_get.
 * No active service is allowed on the sensor when setting the context.
 * If this function is successfully called, a new sensor calibration will not be done during service creation step.
 *
 * @param[in] sensor_id The sensor to set the context on
 * @param[in] calibration_context The calibration context to set
 *
 * @return True if successful, false otherwise
 */
bool acc_rss_calibration_context_forced_set(acc_sensor_id_t sensor_id, acc_calibration_context_t *calibration_context);


/**
 * @brief Reset a calibration done on the specific sensor (or remove a previously set calibration context)
 *
 * No active service is allowed on the sensor when resetting the calibration
 * If this function is successfully called, a new sensor calibration will be done during service creation step.
 *
 * @param[in] sensor_id The sensor to reset the calibration on
 *
 * @return True if successful, false otherwise
 */
bool acc_rss_calibration_reset(acc_sensor_id_t sensor_id);


/**
 * @}
 */

#endif
