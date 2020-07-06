// Copyright (c) Acconeer AB, 2015-2019
// All rights reserved

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "acc_base_configuration.h"
#include "acc_hal_integration.h"
#include "acc_hal_definitions.h"
#include "acc_rss.h"
#include "acc_service.h"
#include "acc_service_power_bins.h"

#include "acc_version.h"


/**
 * @brief Example that shows how to use the Power Bins service
 *
 * This is an example on how the Power Bins service can be used.
 * The example executes as follows:
 *   - Activate Radar System Software (RSS)
 *   - Create a Power Bins service configuration
 *   - Create a Power Bins service using the previously created configuration
 *   - Activate the Power Bins service
 *   - Get the result and print it 5 times
 *   - Deactivate and destroy the Power Bins service
 *   - Destroy the Power Bins service configuration
 *   - Deactivate Radar System Software (RSS)
 */


static bool execute_power_bins(acc_service_configuration_t power_bins_configuration);


bool acc_example_service_power_bins(void)
{
	printf("Acconeer software version %s\n", acc_version_get());

	acc_hal_t hal = acc_hal_integration_get_implementation();

	if (!acc_rss_activate(&hal))
	{
		fprintf(stderr, "acc_rss_activate() failed\n");
		return false;
	}

	acc_service_configuration_t power_bins_configuration = acc_service_power_bins_configuration_create();

	if (power_bins_configuration == NULL)
	{
		fprintf(stderr, "acc_service_power_bins_configuration_create() failed\n");
		acc_rss_deactivate();
		return false;
	}

	acc_base_configuration_t base_configuration = acc_service_get_base_configuration(power_bins_configuration);

	float start_m  = 0.2f;
	float length_m = 0.5f;

	acc_base_configuration_requested_start_set(base_configuration, start_m);
	acc_base_configuration_requested_length_set(base_configuration, length_m);

	if (!execute_power_bins(power_bins_configuration))
	{
		acc_service_power_bins_configuration_destroy(&power_bins_configuration);
		acc_rss_deactivate();
		return false;
	}

	acc_service_power_bins_configuration_destroy(&power_bins_configuration);

	acc_rss_deactivate();

	return true;
}


bool execute_power_bins(acc_service_configuration_t power_bins_configuration)
{
	acc_service_handle_t handle = acc_service_create(power_bins_configuration);

	if (handle == NULL)
	{
		fprintf(stderr, "acc_service_create() failed\n");
		return false;
	}

	acc_service_power_bins_metadata_t power_bins_metadata;
	acc_service_power_bins_get_metadata(handle, &power_bins_metadata);

	printf("Start: %d mm\n", (int)(power_bins_metadata.start_m * 1000.0f));
	printf("Length: %u mm\n", (unsigned int)(power_bins_metadata.length_m * 1000.0f));
	printf("Bin count: %u\n", (unsigned int)(power_bins_metadata.bin_count));

	uint16_t data[power_bins_metadata.bin_count];

	acc_service_power_bins_result_info_t result_info;

	if (!acc_service_activate(handle))
	{
		printf("acc_service_activate() failed\n");
		acc_service_destroy(&handle);
		return false;
	}

	bool      success    = true;
	const int iterations = 5;

	for (int i = 0; i < iterations; i++)
	{
		success = acc_service_power_bins_get_next(handle, data, power_bins_metadata.bin_count, &result_info);

		if (!success)
		{
			fprintf(stderr, "acc_service_power_bins_get_next() failed\n");
			break;
		}

		printf("Power Bins data:\n");

		for (uint16_t j = 0; j < power_bins_metadata.bin_count; j++)
		{
			printf("%u\t", (unsigned int)(data[j]));
		}

		printf("\n");
	}

	bool deactivated = acc_service_deactivate(handle);

	acc_service_destroy(&handle);

	return deactivated && success;
}
