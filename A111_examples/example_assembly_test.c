// Copyright (c) Acconeer AB, 2019
// All rights reserved

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "acc_hal_integration.h"
#include "acc_hal_definitions.h"
#include "acc_rss.h"
#include "acc_rss_assembly_test.h"
#include "acc_version.h"


/**
 * @brief Example that shows how to use the assembly test
 *
 * This is an example on how the assembly test can be used.
 * The example executes as follows:
 *   - Activate Radar System Software (RSS)
 *   - Create an assembly test configuration and configure it
 *   - Run the assembly test
 *   - Print the assembly test results
 *   - Destroy the assembly test configuration
 *   - Deactivate Radar System Software (RSS)
 */


#define DEFAULT_SENSOR_ID 1




bool acc_example_assembly_test(void)
{
	printf("Acconeer software version %s\n", acc_version_get());

	acc_rss_assembly_test_result_t test_results[ACC_RSS_ASSEMBLY_TEST_MAX_NUMBER_OF_TESTS];
	uint16_t                       nr_of_test_results = ACC_RSS_ASSEMBLY_TEST_MAX_NUMBER_OF_TESTS;
	bool                           success;

	acc_hal_t hal = acc_hal_integration_get_implementation();

	if (!acc_rss_activate(&hal))
	{
		return false;
	}

	acc_rss_assembly_test_configuration_t configuration = acc_rss_assembly_test_configuration_create();

	acc_rss_assembly_test_configuration_sensor_set(configuration, DEFAULT_SENSOR_ID);

	success = acc_rss_assembly_test(configuration, test_results, &nr_of_test_results);

	if (success)
	{
		bool all_passed = true;

		for (uint16_t i = 0; i < nr_of_test_results; i++)
		{
			const bool test_passed = test_results[i].test_passed;
			printf("Name: %s, result: %s\n", test_results[i].test_name, test_passed ? "Pass" : "Fail");
			all_passed = test_passed ? all_passed : false;
		}

		if (all_passed)
		{
			printf("Assembly test: All tests passed\n");
		}
		else
		{
			fprintf(stderr, "Assembly test: There are failed tests\n");
			success = false;
		}
	}
	else
	{
		fprintf(stderr, "Assembly test: Failed to complete\n");
	}

	acc_rss_assembly_test_configuration_destroy(&configuration);

	acc_rss_deactivate();

	return success;
}
