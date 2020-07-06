#ifndef __RADAR_INIT_H_
#define __RADAR_INIT_H_

#include <stdbool.h>
#include "acc_detector_distance_peak.h"
#include "acc_base_configuration.h"
#include "acc_hal_integration.h"
#include "acc_hal_definitions.h"
#include "acc_service_envelope.h"
#include "acc_rss.h"
#include "acc_version.h"

#include "global.h"
/**
 * @brief Detector distance peak example
 *
 * @return Returns true if successful, otherwise false
 */
int radarInit(void);
bool execDetOnce(acc_detector_distance_peak_handle_t handle, \
		acc_detector_distance_peak_reflection_t *reflections, \
		uint16_t  reflection_count_max,
		acc_detector_distance_peak_result_info_t *result_info);

#endif


