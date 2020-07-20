#include "radar.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "global.h"

eMode_t MODE = 1;
#define THRESHOLD (100)

extern acc_detector_distance_peak_configuration_t distance_configuration;
extern acc_service_configuration_t envelope_configuration;
extern acc_detector_distance_peak_handle_t handle;
/*
 * 雷达的初始设置
 */
int radarInit()
{

	distance_configuration = acc_detector_distance_peak_configuration_create();  //创建configuration
		if (distance_configuration == NULL)
		{
			//fprintf(stderr, "acc_detector_distance_peak_configuration_create() failed\n");
			acc_rss_deactivate();
			return false;
		}
		acc_detector_distance_peak_service_profile_set(distance_configuration, config.profile + 1);  //设置profile参数
		/*
		 * 由于内存限制，不同的测量起始和结束地址占用内存大小不一样，为了防止需要内存超过ram大小，
		 * 根据测量起始结束地址分配采样精度。
		 * acc_detector_distance_peak_downsampling_factor_set的第2个参数1：表示每0.5mm采样，2：每1mm采样，4：每2mm采样
		 */
		if (config.stop - config.start <= 1900) {  //测量范围小于等于1900mm，每隔0.5mm进行一次采样
			acc_detector_distance_peak_downsampling_factor_set(distance_configuration,1);
		} else if (config.stop - config.start <= 4100) {
			acc_detector_distance_peak_downsampling_factor_set(distance_configuration,2);
		} else {
			acc_detector_distance_peak_downsampling_factor_set(distance_configuration,4);
		}
		/*
		 * 采用绝对振幅表示，就是振幅的实际值（相对振幅表示振幅超过阈值的大小）
		 */
		acc_detector_distance_peak_set_absolute_amplitude(distance_configuration, true);
		/*
		 * 根据配置，决定数据排序的方式
		 */
		if (!config.sort) {
			acc_detector_distance_peak_set_sort_by_amplitude(distance_configuration, false);  //由距离排序
		} else {
			acc_detector_distance_peak_set_sort_by_amplitude(distance_configuration, true);   //由振幅大小排序
		}
        /*
         * 设置前面的测量对本次测量影响的大小，
         */
		acc_detector_distance_peak_running_average_factor_set(distance_configuration, ((float)config.relate) / 100);

		acc_sensor_id_t sensor_id = 1;              //只有一个雷达，id = 1
		float           start_m   = (float)config.start / 1000;                     //计算起始距离
		float           length_m  = (float)(config.stop - config.start) / 1000;

		acc_base_configuration_t base_configuration = acc_detector_distance_peak_get_base_configuration(distance_configuration);
		acc_base_configuration_sensor_set(base_configuration, sensor_id);
		acc_base_configuration_requested_start_set(base_configuration, start_m);
		acc_base_configuration_requested_length_set(base_configuration, length_m);
		acc_detector_distance_peak_metadata_t   metadata;
		handle = acc_detector_distance_peak_create(distance_configuration);
		//acc_detector_distance_peak_get_metadata(handle, &metadata);
		//printf("Start: %u mm\n", (unsigned int)(metadata.start_m * 1000.0f));
		//printf("Length: %u mm\n", (unsigned int)(metadata.length_m * 1000.0f));
		//printf("\n");

		/*
			if (!config.thresholdMode) {
				acc_detector_distance_peak_set_threshold_mode_fixed(distance_configuration, config.threshold);
			} else {
				acc_detector_distance_peak_set_threshold_mode_estimation(distance_configuration);
				acc_detector_distance_peak_threshold_estimation_reset(distance_configuration);
				acc_detector_distance_peak_threshold_estimation_update(distance_configuration,100, metadata.start_m, metadata.start_m+metadata.length_m);
				acc_detector_distance_peak_set_sensitivity(distance_configuration, 0.5);
			}
		*/
		acc_detector_distance_peak_set_threshold_mode_fixed(distance_configuration, config.threshold);        //设置阈值
		acc_base_configuration_hw_accelerated_average_samples_set(base_configuration, config.average);        //设置每一个采样点的测量次数，取平均值
		acc_base_configuration_repetition_mode_on_demand_set(base_configuration);              //雷达用ondemand模式，即应用程序需要才测量

		//acc_service_envelope_noise_level_normalization_set(envelope_configuration, 0);
		//bool a = acc_service_envelope_noise_level_normalization_get(envelope_configuration);
		//printf("normalizetion is %d\n", a);

		//acc_base_configuration_receiver_gain_set(base_configuration,0.8);
		//acc_sweep_configuration_receiver_gain_set(sweep_configuration, 0.8);
	    //float gain=acc_base_configuration_receiver_gain_get(base_configuration);
	    //printf("gain = %d\n", (uint8_t)(gain*100));

	    acc_base_configuration_power_save_mode_set(base_configuration, config.powerSaveMode);  //设置省电模式
	  //  if (config.measureMode == 1) {
			if (!acc_detector_distance_peak_activate(handle)) {            //激活雷达（如果为了降低功耗，也可以先不激活雷达，需要使用时再激活）
				acc_detector_distance_peak_destroy(&handle);
			}
	 //   }
	 //   */

}

bool execDetOnce(acc_detector_distance_peak_handle_t handle, \
		acc_detector_distance_peak_reflection_t *reflections, \
		uint16_t reflection_count_max,
		acc_detector_distance_peak_result_info_t *result_info)
{
	bool success = true;
	uint16_t reflection_count = reflection_count_max;             //设置返回数据个数的最大值
	success = acc_detector_distance_peak_get_next(handle, reflections, &reflection_count, result_info);
	if (!success) {
		//printf("acc_detector_distance_peak_get_next() failed\n");
		return success;
	}
	config.number = reflection_count;                            //得到数据的实际个数

	/*
	 * 对于超过阈值的数据，把距离和振幅写入相应变量，由于共有5对距离振幅寄存器，如果填不满，剩下的距离用oxffff填充，振幅用0填充
	 */
	for (uint8_t i = 0; i < reflection_count; i++) {
		*(&config.distance1 + i*2) = (unsigned int)((reflections[i].distance * 1000.0f) + 0.5f);
		*(&config.distance1 + i*2 + 1) = (unsigned int)(reflections[i].amplitude);
	}
	for (uint8_t j = reflection_count; j < 5; j++) {
		*(&config.distance1 + j*2) = 0xffff;
		*(&config.distance1 + j*2 + 1) = 0;
	}
	//printf("Peak %d, Distance: %3u mm, Amplitude: %u\n", 0, config.distance1, config.amplitude1);

	return success;
}

