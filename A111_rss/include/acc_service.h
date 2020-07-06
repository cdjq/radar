// Copyright (c) Acconeer AB, 2018-2019
// All rights reserved

#ifndef ACC_SERVICE_H_
#define ACC_SERVICE_H_

#include <stdbool.h>

#include "acc_base_configuration.h"

/**
 * @defgroup Services Services
 *
 * @brief Radar services provided by Acconeer
 *
 * @details Experimental
 *
 *          In our code you might encounter features tagge dxperimental.
 *          This means that the feature in question is an early version that has a
 *          limited test scope, and the API and/or functionality might change in
 *          upcoming releases.
 *
 *          The intention is to let users try these features out and we appreciate
 *          feedback.
 * @defgroup Generic Generic Service API
 * @ingroup Services
 *
 * @brief Generic service API description
 *
 * @{
 */


/**
 * @brief Generic service configuration container
 */
struct acc_service_configuration;
typedef struct acc_service_configuration *acc_service_configuration_t;


/**
 * @brief Generic service handle
 */
struct acc_service_handle;
typedef struct acc_service_handle *acc_service_handle_t;


/**
 * @brief Service profile
 *
 * Each profile consists of a number of settings for the sensor that configures
 * the RX and TX paths. Profile 1 maximizes on the depth resolution and
 * profile 5 maximizes on radar loop gain with a sliding scale in between.
 */
typedef enum
{
	ACC_SERVICE_PROFILE_1 = 1,
	ACC_SERVICE_PROFILE_2,
	ACC_SERVICE_PROFILE_3,
	ACC_SERVICE_PROFILE_4,
	ACC_SERVICE_PROFILE_5,
} acc_service_profile_enum_t;
typedef uint32_t acc_service_profile_t;


/**
 * @brief Create a service with the provided configuration
 *
 * Only one service may exist for a specific sensor at any given time and
 * invalid configurations will not allow for service creation.
 *
 * @param[in] configuration The service configuration to create a service with
 * @return Service handle, NULL if service was not possible to create
 */
acc_service_handle_t acc_service_create(acc_service_configuration_t configuration);


/**
 * @brief Activate the service associated with the provided handle
 *
 * When activated, the application can get data from the service with the
 * associated handle.
 *
 * @param[in] service_handle The service handle for the service to activate
 * @return True if successful, false otherwise
 */
bool acc_service_activate(acc_service_handle_t service_handle);


/**
 * @brief Deactivate the service associated with the provided handle
 *
 * @param[in] service_handle The service handle for the service to deactivate
 * @return True if successful, false otherwise
 */
bool acc_service_deactivate(acc_service_handle_t service_handle);


/**
 * @brief Destroy a service identified with the provided service handle
 *
 * Destroy the context of a service allowing another service to be created using the
 * same resources. The service handle reference is set to NULL after destruction.
 *
 * @param[in] service_handle A reference to the service handle to destroy
 */
void acc_service_destroy(acc_service_handle_t *service_handle);


/**
 * @brief Retrieve a base configuration from a service configuration
 *
 * The base configuration can be used to configure the service for different use cases.
 * See @ref acc_base_configuration.h for configuration parameters.
 *
 * @param[in] service_configuration The service configuration to get a base configuration from
 * @return Base configuration, NULL if the service configuration does not contain a base configuration
 */
acc_base_configuration_t acc_service_get_base_configuration(acc_service_configuration_t service_configuration);


/**
 * @brief Get the currently used service profile
 *
 * See @ref acc_service_profile_enum_t for details
 *
 * @param[in] service_configuration The configuration to get a profile for
 * @return The current profile, 0 if configuration is invalid
 */
acc_service_profile_t acc_service_profile_get(acc_service_configuration_t service_configuration);


/**
 * @brief Set a service profile
 *
 * See @ref acc_service_profile_enum_t for details
 *
 * @param[in] service_configuration The configuration to set a profile for
 * @param[in] profile                The profile to set
 */
void acc_service_profile_set(acc_service_configuration_t service_configuration,
                             acc_service_profile_t       profile);


/**
 * @brief Get Maximize signal attenuation mode
 *
 * Will be true if Maximize signal attenuation mode is enabled, false otherwise
 *
 * @param[in] service_configuration The configuration to get Maximize signal attenuation mode for
 * @return Maximize signal attenuation mode
 */
bool acc_service_maximize_signal_attenuation_get(acc_service_configuration_t service_configuration);


/**
 * @brief Set Maximize signal attenuation mode
 *
 * Enable or disable Maximize signal attenuation mode to measure the direct leakage
 *
 * @param[in] service_configuration        The configuration to set Maximize signal attenuation mode in
 * @param[in] maximize_signal_attenuation  Maximize signal attenuation mode, true or false
 */
void acc_service_maximize_signal_attenuation_set(acc_service_configuration_t service_configuration,
                                                 bool                        maximize_signal_attenuation);


/**
 * @}
 */

#endif
