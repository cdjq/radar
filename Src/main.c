/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "acc_detector_distance_peak.h"
#include "acc_hal_definitions.h"
#include "acc_rss.h"

#include "radar.h"
#include "global.h"
#include "rtu.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
bool dataParse(uint8_t *buf, uint8_t len)
{
	bool ret = 1;
	if (((buf[0] != config.addr) && buf[0]) || len > 256) {
		ret = 0;
	} else {
		if (buf[1] == 0x10) {
			if (len != (sizeof(sRtuHead_t) + 1 + buf[sizeof(sRtuHead_t)] + 2)) {
				ret = 0;
				goto out;
			}
	    } else if (len != (sizeof(sRtuHead_t) + 2)) {
			ret = 0;
			goto out;
		} else {
			uint8_t crchi,crclo;
			crchi = (crcCheck(buf, len-2) & 0xff00) >> 8;
			crclo = crcCheck(buf, len-2) & 0x00ff;
			if ((buf[len - 2] != crclo) || (buf[len - 1] != crchi)) {
				ret = 0;
			}
		}
	}

out:
	return ret;
}
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
const uint16_t  reflection_count_max = 5;
acc_detector_distance_peak_reflection_t reflections[5];
acc_detector_distance_peak_result_info_t result_info;
acc_detector_distance_peak_handle_t handle;
acc_detector_distance_peak_configuration_t distance_configuration;
acc_service_configuration_t envelope_configuration;
uint8_t configUart = 0;
/**
  * @brief  The application entry point.
  * @retval int
  */

void initConfig()
{}
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */
  /*
   * 这一处判断是检查配置是否写入到内存中，如果0x8032800地址是0102030401020304，则表示写入成功，那么就把配置读取出来，否则用默认配置
   */
  if (*(uint64_t *)0x8032800 == 0x0102030401020304) {
 	  restoreConfig();
  } else {
	  storeConfig();
  }

  /* Initialize all configured peripherals */
  MX_GPIO_Init();                    //初始化引脚
  MX_SPI2_Init();                    //初始化spi，用于和雷达通信
  MX_USART1_UART_Init();             //初始化串口
  MX_TIM2_Init();                    //初始化tim2，用于判断数据是否满足modbus rtu协议
   MX_TIM15_Init();                  //初始化tim15，用于每0.1s雷达自动测量，和按键重启时指示灯闪烁
   MX_TIM16_Init();                  //初始化tim16，用于检测按键重启
  /* USER CODE BEGIN 2 */
  //__HAL_RCC_PWR_CLK_ENABLE();
  //HAL_PWR_Init();

  HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);
  /* USER CODE END 2 */

  POWER_ON                         //雷达上电
   HAL_Delay(1000);
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  /*
       * 下面这两行要放在每次启动雷达和激活雷达前，因为雷达配置和激活时会通过串口向外发送数据，这两行关闭串口发送
   */
   CLEAR_BIT(huart1.Instance->CR1, USART_CR1_TE);
  (&huart1)->gState = HAL_UART_STATE_BUSY;

  acc_hal_t hal = acc_hal_integration_get_implementation();
  if (!acc_rss_activate(&hal)) {
  	return false;
  }
  while (1)
  {
	  radarInit();                                  //主要用于配置雷达参数
	  /*
	   * 开启串口发送
	   */
	  SET_BIT(huart1.Instance->CR1, USART_CR1_TE);
	  huart1.gState = HAL_UART_STATE_READY;
      /*
       * 如果发现要重启uart，重启uart，开启接受中断
       */
	  if (configUart) {
		configUart = 0;
		uartConfig();
		HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);
	}
	  /*
	   * 如果测量模式是0.1s自动测量，开启tim15
	   */
	 if (config.measureMode == 1) {
		  __HAL_TIM_SET_COUNTER(&htim15, 0);
		  HAL_TIM_Base_Start_IT(&htim15);
	  }
	  while (1) {

		  /*
		   *当以很快的速率（用sscom低于50ms速率发送一帧）发送数据时，当发送到几千帧的时候，总是会出错，串口接收不到数据，然后发现是
		* huart->RxState 本该是 HAL_UART_STATE_BUSY_RX，但是不知道什么原因导致它是 HAL_UART_STATE_READY，导致串口中断没开，
		* 如果这样，就打开串口中断
		   */
		  if (huart1.RxState == HAL_UART_STATE_READY) {
			  while(HAL_UART_Receive_IT(&huart1, (uint8_t *)aRxBuffer, 1) != HAL_OK)
				  ;
		  }
          /*
           * 如果是自动测量模式，并且tim15告知时间到了0.1s，则经行一次测量
           */
		  if ((config.measureMode == 1) && (doDet == 1)) {
            /*低功耗模式下，在每次测量前用acc_detector_distance_peak_activate(handle)激活雷达
             *            ，激活前要关串口发送，激活后打开串口发送。发送前才激活，发送后取消激活的设计，可以降低15ma左右的电流
             * 但是测量数据没有保持激活稳定。目前各模式电流消耗：保持激活45ma，发送前才激活测量30ma，关闭雷达（不激活不测量）15ma。
             *
			  CLEAR_BIT(huart1.Instance->CR1, USART_CR1_TE);
			  (&huart1)->gState = HAL_UART_STATE_BUSY;
			  acc_detector_distance_peak_activate(handle);
			  SET_BIT(huart1.Instance->CR1, USART_CR1_TE);
			  huart1.gState = HAL_UART_STATE_READY;
*/
				execDetOnce(handle, reflections, reflection_count_max, &result_info);
/*
				CLEAR_BIT(huart1.Instance->CR1, USART_CR1_TE);
				(&huart1)->gState = HAL_UART_STATE_BUSY;
				acc_detector_distance_peak_deactivate(handle);
				SET_BIT(huart1.Instance->CR1, USART_CR1_TE);
				huart1.gState = HAL_UART_STATE_READY;
*/
			  doDet = 0;

			  /*
			   * 自动模式下，控制指示灯亮灭
			   */
			  if (config.distance1 <= config.compareLength) {
				  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
			  } else {
				  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
			  }
			  //HAL_UART_Transmit_IT(&huart1, &tim16Count, 1);
		  }

		  /*
		   * 如果tim2，检测到一帧数据都发完了，并不是错误帧，则进行数据分析
		   */

		  if (dataAna && !dataErr) {
			  dataAna = 0;
			  uint8_t aa = dataParse(USART_RX_BUF, USART_RX_POS);   //先进性数据长度的判断，和crc判断
			  //HAL_UART_Transmit_IT(&huart1, &USART_RX_BUF, USART_RX_POS);
			  if (aa) {
				  uint8_t ret;
				  ret = rtuParse(USART_RX_BUF, USART_RX_POS); //ret = 0成功//ret = 1需要更改配置，重新设置雷达
				  while (huart1.gState != HAL_UART_STATE_READY);       //这句话是等待数据发送完毕，保证数据发送完毕，再把串口发送关了
				  if (ret == 1) {
					  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);      //关指示灯
					  HAL_TIM_Base_Stop_IT(&htim15);                             //关tim15
					  CLEAR_BIT(huart1.Instance->CR1, USART_CR1_TE);             //关串口发送
					  (&huart1)->gState = HAL_UART_STATE_BUSY;

					  /*
					   * 这几行关雷达，并回收资源
					   */
					  acc_detector_distance_peak_deactivate(handle);
					  acc_detector_distance_peak_destroy(&handle);
					  acc_detector_distance_peak_configuration_destroy(&distance_configuration);
				  	  break;
				  }
			  }

		  }

	  }

  }

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 20;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure the main internal regulator output voltage 
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
