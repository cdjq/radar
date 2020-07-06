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
#include "acc_service_envelope.h"

#include "acc_version.h"


/**
 * @brief Example that shows how to use the envelope service
 *
 * This is an example on how the envelope service can be used.
 * The example executes as follows:
 *   - Activate Radar System Software (RSS)
 *   - Create an envelope service configuration
 *   - Create an envelope service using the previously created configuration
 *   - Activate the envelope service
 *   - Get the result and print it 5 times
 *   - Deactivate and destroy the envelope service
 *   - Destroy the envelope service configuration
 *   - Deactivate Radar System Software (RSS)
 */


static bool execute_envelope(acc_service_configuration_t envelope_configuration);

uint8_t context_flag=0;
acc_calibration_context_t context_t;


bool acc_example_service_envelope(void)
{
	printf("Acconeer software version %s\n", acc_version_get());

	acc_hal_t hal = acc_hal_integration_get_implementation();

	if (!acc_rss_activate(&hal))
	{
		fprintf(stderr, "acc_rss_activate() failed\n");
		return false;
	}

	if(context_flag!=1)
	{
	  bool flag=acc_rss_calibration_context_get(1,&context_t);
	  if(flag==1)
	  {
		  context_flag=1;
	  }
	}
	else
	{
		context_flag=1;
		acc_rss_calibration_context_set(1,&context_t);
	}


	acc_service_configuration_t envelope_configuration = acc_service_envelope_configuration_create();

	if (envelope_configuration == NULL)
	{
		fprintf(stderr, "acc_service_envelope_configuration_create() failed\n");
		acc_rss_deactivate();
		return false;
	}

	acc_base_configuration_t base_configuration = acc_service_get_base_configuration(envelope_configuration);

	float start_m  = 0.2f;
	float length_m = 0.5f;

	acc_base_configuration_requested_start_set(base_configuration, start_m);
	acc_base_configuration_requested_length_set(base_configuration, length_m);

	if (!execute_envelope(envelope_configuration))
	{
		acc_service_envelope_configuration_destroy(&envelope_configuration);
		acc_rss_deactivate();
		return false;
	}

	acc_service_envelope_configuration_destroy(&envelope_configuration);

	acc_rss_deactivate();

	return true;
}


bool execute_envelope(acc_service_configuration_t envelope_configuration)
{

	uint16_t tickstart1=0;
	uint16_t tickstart2=0;
	tickstart1=HAL_GetTick();

	acc_service_handle_t handle = acc_service_create(envelope_configuration);

	tickstart2=HAL_GetTick();
	printf("\r\nCreate Time=%d\r\n\r\n",tickstart2-tickstart1);

	if (handle == NULL)
	{
		fprintf(stderr, "acc_service_create() failed\n");
		return false;
	}

	acc_service_envelope_metadata_t envelope_metadata;
	acc_service_envelope_get_metadata(handle, &envelope_metadata);

	printf("Start: %d mm\n", (int)(envelope_metadata.start_m * 1000.0f));
	printf("Length: %u mm\n", (unsigned int)(envelope_metadata.length_m * 1000.0f));
	printf("Data length: %u\n", (unsigned int)(envelope_metadata.data_length));

	uint16_t data[envelope_metadata.data_length];

	acc_service_envelope_result_info_t result_info;

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
		success = acc_service_envelope_get_next(handle, data, envelope_metadata.data_length, &result_info);

		if (!success)
		{
			fprintf(stderr, "acc_service_envelope_get_next() failed\n");
			break;
		}

		printf("Envelope data:\n");

		for (uint16_t j = 0; j < envelope_metadata.data_length; j++)
		{
			if ((j > 0) && ((j % 8) == 0))
			{
				printf("\n");
			}

			printf("%6u", (unsigned int)(data[j]));
		}

		printf("\n");
	}

	bool deactivated = acc_service_deactivate(handle);

	acc_service_destroy(&handle);

	return deactivated && success;
}
