/**
  ******************************************************************************
  * File Name          : TIM.c
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2020 STMicroelectronics
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

/* Includes ------------------------------------------------------------------*/
#include "tim.h"
#include "main.h"
#include "global.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim15;
TIM_HandleTypeDef htim16;

/* TIM2 init function */
void MX_TIM2_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 955-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}
/* TIM15 init function */
void MX_TIM15_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim15.Instance = TIM15;
  htim15.Init.Prescaler = 8000-1;
  htim15.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim15.Init.Period = 1000-1;
  htim15.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim15.Init.RepetitionCounter = 0;
  htim15.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim15) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim15, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim15, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

void MX_TIM16_Init(void)
{
	  htim16.Instance = TIM16;
	  htim16.Init.Prescaler = 10000-1;
	  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
	  htim16.Init.Period = 8000-1;
	  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	  htim16.Init.RepetitionCounter = 0;
	  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  __HAL_TIM_CLEAR_IT(&htim16, TIM_IT_UPDATE);

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspInit 0 */

  /* USER CODE END TIM2_MspInit 0 */
    /* TIM2 clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();

    /* TIM2 interrupt Init */
    HAL_NVIC_SetPriority(TIM2_IRQn, 8, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspInit 1 */

  /* USER CODE END TIM2_MspInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM15)
  {
  /* USER CODE BEGIN TIM15_MspInit 0 */

  /* USER CODE END TIM15_MspInit 0 */
    /* TIM15 clock enable */
    __HAL_RCC_TIM15_CLK_ENABLE();

    /* TIM15 interrupt Init */
    HAL_NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 8, 0);
    HAL_NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn);
  /* USER CODE BEGIN TIM15_MspInit 1 */

  /* USER CODE END TIM15_MspInit 1 */
  } else if (tim_baseHandle->Instance==TIM16) {
	  __HAL_RCC_TIM16_CLK_ENABLE();
	  HAL_NVIC_SetPriority(TIM1_UP_TIM16_IRQn, 8, 0);
	  HAL_NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspDeInit 0 */

  /* USER CODE END TIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();

    /* TIM2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspDeInit 1 */

  /* USER CODE END TIM2_MspDeInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM15)
  {
  /* USER CODE BEGIN TIM15_MspDeInit 0 */

  /* USER CODE END TIM15_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM15_CLK_DISABLE();

    /* TIM15 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM1_BRK_TIM15_IRQn);
  /* USER CODE BEGIN TIM15_MspDeInit 1 */

  /* USER CODE END TIM15_MspDeInit 1 */
  } else if(tim_baseHandle->Instance==TIM16)
  {
  /* USER CODE BEGIN TIM15_MspDeInit 0 */

  /* USER CODE END TIM15_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM16_CLK_DISABLE();

    /* TIM15 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM1_UP_TIM16_IRQn);
  /* USER CODE BEGIN TIM15_MspDeInit 1 */

  /* USER CODE END TIM15_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

volatile uint8_t dataFrameComp = 1;           //浼犺緭甯х粨鏉熸寚�??�??
volatile uint8_t dataFrameErr = 0;            //涓�甯у唴鐩搁偦�?�楄妭闂撮殧瓒呰�??1.5瀛楃锛�??
                                          //璁や负杩欏抚鏈夎锛岃涓㈠�??
volatile uint16_t timInCount = 0;       //鐢ㄦ潵璁板綍杩涘叆�?�氭椂鍣ㄤ腑鏂鏁�??
volatile uint8_t dataAna = 0;
volatile uint8_t tim16Count = 0;
volatile uint8_t doDet = 0;
extern UART_HandleTypeDef huart1;
volatile uint8_t reboot = 0;
volatile uint8_t rebootCount = 0;

void TIM2_IRQHandler(void)
{
	if (__HAL_TIM_GET_FLAG(&htim2, TIM_FLAG_UPDATE) != RESET) {
		HAL_TIM_IRQHandler(&htim2);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *timer)
{
	if (timer->Instance == htim2.Instance) {
		timInCount++;
		//printf("1");
		if (timInCount == 5 * (115200/huart1.Init.BaudRate)) {
			dataFrameErr = 1;
		}
		if (timInCount == 9 * (115200/huart1.Init.BaudRate)) {
			//printf("\n timecallback end\n");
			dataFrameComp = 1;
			dataAna = 1;
			HAL_TIM_Base_Stop_IT(&htim2);
		}
	} else if (timer->Instance == htim15.Instance) {
		if(!reboot) {
			doDet = 1;
		} else {
			doDet = 0;
			HAL_UART_DeInit(&huart1);
			rebootCount++;
			if (! (rebootCount%2)) {
				HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
			}
			if (rebootCount == 60) {
				storeConfig();
				__set_FAULTMASK(1);//关闭所有中断
				NVIC_SystemReset();
			}
		}
	} else if (timer->Instance == htim16.Instance) {
		tim16Count++;
		if (tim16Count == 2) {
			reboot = 1;
			tim16Count = 0;
			setConfig();
			//config = {.pid=0x0002, .vid=0x0010, .addr=0x0C, .baudrate=0x03, .parity=0, .stopBit=0x01, .number=0,
			//		0xffff, 0, 0xffff, 0, 0xffff, 0, 0xffff, 0, 0xffff, 0,
				//	.sort = 0, .start=0x00C8, .stop = 0x19C0, 0x0190, 0x0A, 0x46, 0x02, 0x01, 0x012C, 0, 0x03};

		//	storeConfig();
		//	__set_FAULTMASK(1);//关闭所有中断
		//	NVIC_SystemReset();
		}
	}
}

void setConfig()
{
	config.pid = 0x0002;
	config.vid = 0x0010;
	config.addr = 0x0c;
	config.baudrate = 0x03;
	config.parity = 0;
	config.stopBit = 0x01;
	config.number = 0;
	config.distance1 = 0xffff;
	config.amplitude1 = 0;
	config.distance2 = 0xffff;
	config.amplitude2 = 0;
	config.distance3 = 0xffff;
	config.amplitude3 = 0;
	config.distance4 = 0xffff;
	config.amplitude4 = 0;
	config.distance5 = 0xffff;
	config.amplitude5 = 0;
	config.sort = 0;
	config.start = 0x00c8;
	config.stop = 0x19c0;
	config.threshold = 0x0190;
	config.average = 0x0a;
	config.relate = 0x46;
	config.profile = 0x02;
	config.compareLength = 0x12c;
	config.powerSaveMode = 0x0003;
}

/* USER CODE END 1 */
void TIM15_IRQHandler(void)
{
	if (__HAL_TIM_GET_FLAG(&htim15, TIM_FLAG_UPDATE) != RESET) {
		HAL_TIM_IRQHandler(&htim15);
	}
}

void TIM1_UP_TIM16_IRQHandler(void)
{
	if (__HAL_TIM_GET_FLAG(&htim16, TIM_FLAG_UPDATE) != RESET) {
		HAL_TIM_IRQHandler(&htim16);
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
