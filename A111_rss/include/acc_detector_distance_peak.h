// Copyright (c) Acconeer AB, 2018-2019
// All rights reserved

#ifndef ACC_DETECTOR_DISTANCE_PEAK_H_
#define ACC_DETECTOR_DISTANCE_PEAK_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "acc_service.h"
#include "acc_base_configuration.h"

/**
 * @defgroup Detectors Detectors
 *
 * @brief Radar services provided by Acconeer
 *
 */


/**
 * @defgroup Distance_Peak Distance Peak Detector
 * @ingroup Detectors
 *
 * @brief Distance peak detector API description
 *
 * @{
 */


/**
 * @brief Distance detector configuration
 */
struct acc_detector_distance_peak_configuration;

typedef struct acc_detector_distance_peak_configuration *acc_detector_distance_peak_configuration_t;


/**
 * @brief Distance detector handle
 */
struct acc_detector_distance_peak_handle;

typedef struct acc_detector_distance_peak_handle *acc_detector_distance_peak_handle_t;


/**
 * @brief Reflection struct for the distance detector reflections
 */
typedef struct
{
	float    distance;
	uint16_t amplitude;
} acc_detector_distance_peak_reflection_t;

/**
 * @brief Metadata for the distance detector
 */
typedef struct
{
	float start_m;
	float length_m;
} acc_detector_distance_peak_metadata_t;


/**
 * @brief Metadata for each result provided by the distance detector
 */
typedef struct
{
	bool missed_data;
	bool data_saturated;
} acc_detector_distance_peak_result_info_t;


/**
 * @brief A callback for retrieving the service data buffer that the detector is based on
 *
 * @param[in] data A pointer to the buffer with envelope data
 * @param[in] data_length Size of the data buffer
 */
typedef void (*acc_detector_distance_peak_service_data_callback_t)(const uint16_t *data, uint16_t data_length);


/**
 * @brief Create a configuration for a distance detector
 *
 * @return A reference to the distance detector configuration, NULL if creation was not possible
 */
acc_detector_distance_peak_configuration_t acc_detector_distance_peak_configuration_create(void);


/**
 * @brief Destroy a distance detector configuration
 *
 * Destroy a distance detector configuration that is no longer needed, may be done even if a
 * detector has been created with the specific configuration and has not yet been destroyed.
 * The detector configuration reference is set to NULL after destruction.
 *
 * @param[in] configuration The configuration to destroy, set to NULL
 */
void acc_detector_distance_peak_configuration_destroy(acc_detector_distance_peak_configuration_t *configuration);


/**
 * @brief Create a distance detector
 *
 * @param[in] configuration The distance detector configuration
 *
 * @return A reference to the distance detector handle. NULL in case of failure
 */
acc_detector_distance_peak_handle_t acc_detector_distance_peak_create(acc_detector_distance_peak_configuration_t configuration);


/**
 * @brief Destroy a distance detector
 *
 * @param[in] handle The distance detector handle
 */
void acc_detector_distance_peak_destroy(acc_detector_distance_peak_handle_t *handle);


/**
 * @brief Activate a distance detector
 *
 * @param[in] handle The distance detector handle to activate
 *
 * @return True if successful, false otherwise
 */
bool acc_detector_distance_peak_activate(acc_detector_distance_peak_handle_t handle);


/**
 * @brief Deactivate a distance detector
 *
 * @param[in] handle The distance detector handle
 *
 * @return True if successful, false otherwise
 */
bool acc_detector_distance_peak_deactivate(acc_detector_distance_peak_handle_t handle);


/**
 * @brief Retrieve the distance detector base configuration
 *
 * @param[in] configuration The distance detector configuration
 *
 * @return A reference to the base configuration, or NULL if an error occurs
 */
acc_base_configuration_t acc_detector_distance_peak_get_base_configuration(acc_detector_distance_peak_configuration_t configuration);


/**
 * @brief Get the current service profile used by the detector
 *
 * See @ref acc_service_profile_enum_t for details
 *
 * @param[in] configuration The configuration to get a profile from
 * @return The current profile, 0 if configuration is invalid
 */
acc_service_profile_t acc_detector_distance_peak_service_profile_get(acc_detector_distance_peak_configuration_t configuration);


/**
 * @brief Set a service profile to be used by the detector
 *
 * See @ref acc_service_profile_enum_t for details
 *
 * @param[in] configuration   The configuration to set a profile for
 * @param[in] service_profile The profile to set
 */
void acc_detector_distance_peak_service_profile_set(acc_detector_distance_peak_configuration_t configuration,
                                                    acc_service_profile_t                      service_profile);


/**
 * @brief Get running average factor
 *
 * The running average factor is the factor of which the most recent sweep is weighed against previous sweeps.
 * Valid range is between 0.0 and 1.0 where 0.0 means that no history is weighed in, i.e filtering is effectively disabled.
 * A factor of 1.0 means that the most recent sweep has no effect on the result,
 * which will result in that the first sweep is forever received as the result.
 * The filtering is coherent and is done on complex valued IQ data before conversion to envelope data.
 *
 * @param[in] configuration The configuration to get the running average factor for
 * @return Running average factor
 */
float acc_detector_distance_peak_running_average_factor_get(acc_detector_distance_peak_configuration_t configuration);


/**
 * @brief Set running average factor
 *
 * The running average factor is the factor of which the most recent sweep is weighed against previous sweeps.
 * Valid range is between 0.0 and 1.0 where 0.0 means that no history is weighed in, i.e filtering is effectively disabled.
 * A factor of 1.0 means that the most recent sweep has no effect on the result,
 * which will result in that the first sweep is forever received as the result.
 * The filtering is coherent and is done on complex valued IQ data before conversion to envelope data.
 *
 * @param[in] configuration The configuration to set the running average factor for
 * @param[in] factor The running average factor to set
 */
void acc_detector_distance_peak_running_average_factor_set(acc_detector_distance_peak_configuration_t configuration, float factor);


/**
 * @brief Get the sensor downsampling factor
 *
 * Gets the downsampling factor - the number of steps taken between each data point. A downsampling factor of 1 samples
 * every possible point in the range. A downsampling_factor of 2 samples every other point, and so on.
 *
 * The base step length is ~0.5mm. Thus, for example setting downsampling_factor to 4 makes the distance
 * between two points in the measured range ~2mm.
 *
 * @param[in] configuration The configuration to get downsampling factor from
 * @return The downsampling factor
 */
uint16_t acc_detector_distance_peak_downsampling_factor_get(acc_detector_distance_peak_configuration_t configuration);


/**
 * @brief Set the sensor downsampling factor
 *
 * Sets the downsampling factor - the number of steps taken between each data point. A downsampling factor of 1 samples
 * every possible point in the range. A downsampling factor of 2 samples every other point, and so on.
 *
 * The base step length is ~0.5mm. Thus, for example setting downsampling_factor to 4 makes the distance
 * between two points in the measured range ~2mm.
 *
 * The distance peak detector supports a downsampling factor of 1, 2, or 4.
 *
 * @param[in] configuration The configuration to set downsampling factor in
 * @param[in] downsampling_factor The downsampling factor
 */
void acc_detector_distance_peak_downsampling_factor_set(acc_detector_distance_peak_configuration_t configuration, uint16_t downsampling_factor);


/**
 * @brief Retrieve the next result from the distance detector
 *
 * May only be called after the distance detector has been activated to retrieve the next result, blocks
 * the application until a result is ready.
 *
 * @param[in] handle The distance detector handle
 * @param[out] reflections Reflection results
 * @param[in,out] reflection_count The maximum number reflections as input and the actual number of reflections as output
 * @param[out] result_info Detection results metadata
 *
 * @return True if successful, false otherwise
 */
bool acc_detector_distance_peak_get_next(acc_detector_distance_peak_handle_t      handle,
                                         acc_detector_distance_peak_reflection_t  *reflections,
                                         uint16_t                                 *reflection_count,
                                         acc_detector_distance_peak_result_info_t *result_info);


/**
 * @brief Get the distance detector metadata
 *
 * May only be called after a distance detector has been created.
 *
 * @param[in] handle The detector handle
 * @param[out] metadata Metadata results are provided in this parameter
 */
void acc_detector_distance_peak_get_metadata(acc_detector_distance_peak_handle_t   handle,
                                             acc_detector_distance_peak_metadata_t *metadata);


/**
 * @brief Set the threshold mode to fixed
 *
 * @param[in] configuration The distance detector configuration previously created
 * @param[in] fix_threshold_value Threshold value
 *
 * @return True if successful, false otherwise
 */
bool acc_detector_distance_peak_set_threshold_mode_fixed(
	acc_detector_distance_peak_configuration_t configuration,
	uint16_t                                   fix_threshold_value);


/**
 * @brief Set the threshold value to the provided one
 *
 * @param[in] configuration The distance detector configuration previously created
 * @param[in] threshold_context_size The size of the threshold_context_data
 * @param[in] threshold_context_data A reference to a context from a previous threshold estimation
 *
 * @return True if successful, false otherwise
 */
bool acc_detector_distance_peak_set_threshold_mode_provided(
	acc_detector_distance_peak_configuration_t configuration,
	size_t                                     threshold_context_size,
	void                                       *threshold_context_data);


/**
 * @brief Set the threshold mode to estimation i.e. the distance detector estimates and creates threshold to be used
 *
 * @param[in] configuration The distance detector configuration previously created
 *
 * @return True if successful, false otherwise
 */
bool acc_detector_distance_peak_set_threshold_mode_estimation(
	acc_detector_distance_peak_configuration_t configuration);


/**
 * @brief Threshold estimation update.
 *
 * Starts or updates an already ongoing threshold estimation.
 * It is recommended to use at least 50 updates. The threshold estimation must be called before activating the detector
 *
 * @param[in] configuration The distance detector configuration previously created
 * @param[in] updates_count The number of updates for the threshold estimation
 * @param[in] distance_start_m The distance of the first data point[m]
 * @param[in] distance_end_m The distance of the last data point[m]
 *
 * @return True if successful, false otherwise
 */
bool acc_detector_distance_peak_threshold_estimation_update(
	acc_detector_distance_peak_configuration_t configuration,
	uint16_t                                   updates_count,
	float                                      distance_start_m,
	float                                      distance_end_m);


/**
 * @brief Set if distance detector should operate on absolute amplitude (otherwise delta amplitude compared to threshold, which is the default behaviour)
 *
 * @param[in] configuration The distance detector configuration previously created
 * @param[in] set_absolute True if absolute amplitude should be used instead of difference (compared to threshold), false otherwise
 * @return True if successful, false otherwise
 */
bool acc_detector_distance_peak_set_absolute_amplitude(acc_detector_distance_peak_configuration_t configuration,
                                                       bool                                       set_absolute);


/**
 * @brief Threshold estimation reset.
 *
 * Resets contents of any ongoing threshold estimation.
 *
 * @param[in] configuration The distance detector configuration previously created
 *
 * @return True if successful, false otherwise
 */
bool acc_detector_distance_peak_threshold_estimation_reset(
	acc_detector_distance_peak_configuration_t configuration);


/**
 * @brief Get the size of threshold estimation data.
 *
 * Retrieves the size of threshold estimation data to use when retrieving the data.
 *
 * @param[in] configuration The distance detector configuration previously created
 * @param[out] threshold_data_size The threshold estimation data size is stored in this parameter
 *
 * @return True if successful, false otherwise
 */
bool acc_detector_distance_peak_threshold_estimation_get_size(
	acc_detector_distance_peak_configuration_t configuration,
	size_t                                     *threshold_data_size);


/**
 * @brief Get the result of a threshold estimation.
 *
 * Retrieves the result of a threshold estimation which is possible to save to a file and use when recreating the distance detector.
 *
 * @param[in] configuration The distance detector configuration previously created
 * @param[in] threshold_data_size The size of memory referenced by threshold_data, must be of at least the size provided in acc_detector_distance_peak_threshold_estimation_get_size
 * @param[out] threshold_data The threshold data is stored in this parameter, must be of at least the size provided in acc_detector_distance_peak_threshold_estimation_get_size
 *
 * @return True if successful, false otherwise
 */
bool acc_detector_distance_peak_threshold_estimation_get_data(
	acc_detector_distance_peak_configuration_t configuration,
	size_t                                     threshold_data_size,
	uint8_t                                    *threshold_data);


/**
 * @brief Set sensitivity factor for false detection rate, 0.0 for lowest sensitivity and 1.0 for highest sensitivity
 *
 * This function is optional but, if used, must be called before acc_detector_distance_peak_detect().
 *
 * @param[in] configuration The distance detector configuration previously created
 * @param[in] sensitivity Sensitivity factor to be set
 *
 * @return True if successful, false otherwise
 */
bool acc_detector_distance_peak_set_sensitivity(acc_detector_distance_peak_configuration_t configuration,
                                                float                                      sensitivity);


/**
 * @brief Set sort reflection by amplitude
 *
 * This function is optional but, if used, must be called before acc_detector_distance_peak_create().
 *
 * @param[in] configuration The distance detector configuration previously created
 * @param[in] sort_by_amplitude True if reflections should be sorted by amplitude, largest amplitude first
 *
 * @return True if successful, false otherwise
 */

bool acc_detector_distance_peak_set_sort_by_amplitude(acc_detector_distance_peak_configuration_t configuration,
                                                      bool                                       sort_by_amplitude);


/**
 * @brief Set a callback function to get the service data
 *
 * A callback can be used to get the envelope service buffer. The data is the unprocessed envelope data that is fed into the distance peak algorithm
 *
 * @param[in] configuration The configuration to set the service data callback for
 * @param[in] service_data_callback The callback to get service data
 */
void acc_detector_distance_peak_set_service_data_callback(acc_detector_distance_peak_configuration_t         configuration,
                                                          acc_detector_distance_peak_service_data_callback_t service_data_callback);


/**
 * @}
 */


#endif
