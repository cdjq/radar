// Copyright (c) Acconeer AB, 2018-2019
// All rights reserved

#include <complex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "acc_base_configuration.h"
#include "acc_hal_integration.h"
#include "acc_hal_definitions.h"
#include "acc_rss.h"
#include "acc_service.h"
#include "acc_service_iq.h"

#include "acc_version.h"


/**
 * @brief Example that shows how to use the IQ service
 *
 * This is an example on how the IQ service can be used.
 * The example executes as follows:
 *   - Activate Radar System Software (RSS)
 *   - Create an IQ service configuration
 *   - Create an IQ service using the previously created configuration
 *   - Activate the IQ service
 *   - Get the result and print it 5 times
 *   - Deactivate and destroy the IQ service
 *   - Destroy the IQ service configuration
 *   - Deactivate Radar System Software (RSS)
 */


static bool execute_iq(acc_service_configuration_t iq_configuration);


bool acc_example_service_iq(void)
{
	printf("Acconeer software version %s\n", acc_version_get());

	acc_hal_t hal = acc_hal_integration_get_implementation();

	if (!acc_rss_activate(&hal))
	{
		fprintf(stderr, "acc_rss_activate() failed\n");
		return false;
	}

	acc_service_configuration_t iq_configuration = acc_service_iq_configuration_create();

	if (iq_configuration == NULL)
	{
		fprintf(stderr, "acc_service_iq_configuration_create() failed\n");
		acc_rss_deactivate();
		return false;
	}

	acc_service_iq_output_format_set(iq_configuration, ACC_SERVICE_IQ_OUTPUT_FORMAT_FLOAT_COMPLEX);
	acc_base_configuration_t base_configuration = acc_service_get_base_configuration(iq_configuration);

	float start_m  = 0.2f;
	float length_m = 0.5f;

	acc_base_configuration_requested_start_set(base_configuration, start_m);
	acc_base_configuration_requested_length_set(base_configuration, length_m);

	if (!execute_iq(iq_configuration))
	{
		acc_service_iq_configuration_destroy(&iq_configuration);
		acc_rss_deactivate();
		return false;
	}

	acc_service_iq_configuration_destroy(&iq_configuration);

	acc_rss_deactivate();

	return true;
}


bool execute_iq(acc_service_configuration_t iq_configuration)
{
	acc_service_handle_t handle = acc_service_create(iq_configuration);

	if (handle == NULL)
	{
		fprintf(stderr, "acc_service_create() failed\n");
		return false;
	}

	acc_service_iq_metadata_t iq_metadata;
	acc_service_iq_get_metadata(handle, &iq_metadata);

	printf("Start: %d mm\n", (int)(iq_metadata.start_m * 1000.0f));
	printf("Length: %u mm\n", (unsigned int)(iq_metadata.length_m * 1000.0f));
	printf("Data length: %u\n", (unsigned int)(iq_metadata.data_length));

	float complex                data[iq_metadata.data_length];
	acc_service_iq_result_info_t result_info;

	if (!acc_service_activate(handle))
	{
		fprintf(stderr, "acc_service_activate() failed\n");
		acc_service_destroy(&handle);
		return false;
	}

	bool      success    = true;
	const int iterations = 5;

	for (int i = 0; i < iterations; i++)
	{
		success = acc_service_iq_get_next(handle, data, iq_metadata.data_length, &result_info);

		if (!success)
		{
			fprintf(stderr, "acc_service_iq_get_next() failed\n");
			break;
		}

		printf("IQ data in polar coordinates (r, phi) (multiplied by 1000):\n");

		for (uint16_t j = 0; j < iq_metadata.data_length; j++)
		{
			if ((j > 0) && ((j % 8) == 0))
			{
				printf("\n");
			}

			printf("(%d, %d)\t", (int)(cabsf(data[j]) * 1000), (int)(cargf(data[j]) * 1000));
		}

		printf("\n");
	}

	bool deactivated = acc_service_deactivate(handle);

	acc_service_destroy(&handle);

	return deactivated && success;
}
