// Copyright (c) Acconeer AB, 2019
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
#include "acc_service_sparse.h"

#include "acc_version.h"


/**
 * @brief Example that shows how to use the sparse service
 *
 * This is an example on how the sparse service can be used.
 * The example executes as follows:
 *   - Activate Radar System Software (RSS)
 *   - Create a sparse service configuration
 *   - Create a sparse service using the previously created configuration
 *   - Activate the sparse service
 *   - Get the result and print it 5 times
 *   - Deactivate and destroy the sparse service
 *   - Destroy the sparse service configuration
 *   - Deactivate Radar System Software (RSS)
 */


static bool execute_sparse(acc_service_configuration_t sparse_configuration);


bool acc_example_service_sparse(void)
{
	printf("Acconeer software version %s\n", acc_version_get());

	acc_hal_t hal = acc_hal_integration_get_implementation();

	if (!acc_rss_activate(&hal))
	{
		fprintf(stderr, "acc_rss_activate() failed\n");
		return false;
	}

	acc_service_configuration_t sparse_configuration = acc_service_sparse_configuration_create();

	if (sparse_configuration == NULL)
	{
		printf("acc_service_sparse_configuration_create() failed\n");
		acc_rss_deactivate();
		return false;
	}

	uint16_t sweeps_per_frame = 16;

	acc_service_sparse_configuration_sweeps_per_frame_set(sparse_configuration, sweeps_per_frame);

	acc_base_configuration_t base_configuration = acc_service_get_base_configuration(sparse_configuration);

	float start_m  = 0.18f;
	float length_m = 0.36f;

	acc_base_configuration_requested_start_set(base_configuration, start_m);
	acc_base_configuration_requested_length_set(base_configuration, length_m);

	if (!execute_sparse(sparse_configuration))
	{
		acc_service_sparse_configuration_destroy(&sparse_configuration);
		acc_rss_deactivate();
		return false;
	}

	acc_service_sparse_configuration_destroy(&sparse_configuration);

	acc_rss_deactivate();

	return true;
}


bool execute_sparse(acc_service_configuration_t sparse_configuration)
{
	acc_service_handle_t handle = acc_service_create(sparse_configuration);

	if (handle == NULL)
	{
		fprintf(stderr, "acc_service_create() failed\n");
		return false;
	}

	acc_service_sparse_metadata_t sparse_metadata;
	acc_service_sparse_get_metadata(handle, &sparse_metadata);

	printf("Start: %d mm\n", (int)(sparse_metadata.start_m * 1000.0f));
	printf("Length: %u mm\n", (unsigned int)(sparse_metadata.length_m * 1000.0f));
	printf("Data length: %u\n", (unsigned int)(sparse_metadata.data_length));

	uint16_t sweeps_per_frame = acc_service_sparse_configuration_sweeps_per_frame_get(sparse_configuration);
	uint16_t sweep_length     = sparse_metadata.data_length / sweeps_per_frame;

	printf("Sweeps per frame: %u\n", (unsigned int)sweeps_per_frame);
	printf("Sweep length: %u\n", (unsigned int)sweep_length);

	uint16_t                         data[sparse_metadata.data_length];
	acc_service_sparse_result_info_t result_info;

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
		success = acc_service_sparse_get_next(handle, data, sparse_metadata.data_length, &result_info);

		if (!success)
		{
			fprintf(stderr, "acc_service_sparse_get_next() failed\n");
			break;
		}

		printf("Sparse data:\n");

		for (uint16_t sweep = 0; sweep < sweeps_per_frame; sweep++)
		{
			printf("Sweep %u:\t", (unsigned int)(sweep + 1));

			for (uint16_t sweep_idx = 0; sweep_idx < sweep_length; sweep_idx++)
			{
				printf("%6u", (unsigned int)data[(sweep * sweep_length) + sweep_idx]);
			}

			printf("\n");
		}

		printf("\n");
	}

	bool deactivated = acc_service_deactivate(handle);

	acc_service_destroy(&handle);

	return deactivated && success;
}
