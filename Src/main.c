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

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI2_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_TIM15_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);
  /* USER CODE END 2 */
  if (*(uint64_t *)0x8032800 == 0x0102030401020304) {
  	  restoreConfig();
  } else {
	  storeConfig();
  }

  POWER_ON
   HAL_Delay(1000);
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	  CLEAR_BIT(huart1.Instance->CR1, USART_CR1_TE);
  	  (&huart1)->gState = HAL_UART_STATE_BUSY;
  acc_hal_t hal = acc_hal_integration_get_implementation();
  if (!acc_rss_activate(&hal)) {
  	return false;
  }
  //printf("config.measuaremode = %d\n", config.measureMode);
  while (1)
  {
    /* USER CODE END WHILE */
	  radarInit();
	  SET_BIT(huart1.Instance->CR1, USART_CR1_TE);
	  huart1.gState = HAL_UART_STATE_READY;

	  if (configUart) {
		configUart = 0;
		uartConfig();
		HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);
	}
	 if (config.measureMode == 1) {
		  __HAL_TIM_SET_COUNTER(&htim15, 0);
		  HAL_TIM_Base_Start_IT(&htim15);
	  }

	  while (1) {

		  if (huart1.RxState == HAL_UART_STATE_READY) {
			  while(HAL_UART_Receive_IT(&huart1, (uint8_t *)aRxBuffer, 1) != HAL_OK)
				  ;
		  }
		  if ((config.measureMode == 1) && (doDet == 1)) {
			  execDetOnce(handle, reflections, reflection_count_max, &result_info);
			  //int status = huart1.RxState;
			  //HAL_UART_Transmit_IT(&huart1, (uint8_t *)&status, 4);
			  doDet = 0;
			  if (!config.compareSwitch) {
				  if (config.distance1 <= config.compareLength) {
					  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
				  } else {
					  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
				  }
			  }
		  }
		  if (dataAna && !dataErr) {
			  dataAna = 0;
			  uint8_t aa = dataParse(USART_RX_BUF, USART_RX_POS);
			  if (aa) {
				  uint8_t ret;
				  ret = rtuParse(USART_RX_BUF, USART_RX_POS); //ret = 0成功//ret = 1更改配置重启
				  while(huart1.gState != HAL_UART_STATE_READY);
				  if (ret == 1) {
					  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
					  HAL_TIM_Base_Stop_IT(&htim15);
					  CLEAR_BIT(huart1.Instance->CR1, USART_CR1_TE);
					  (&huart1)->gState = HAL_UART_STATE_BUSY;
					  acc_detector_distance_peak_deactivate(handle);
					  acc_detector_distance_peak_destroy(&handle);
					  acc_detector_distance_peak_configuration_destroy(&distance_configuration);
				  	  break;
				  }
			  }

		  }


	  }

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
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
