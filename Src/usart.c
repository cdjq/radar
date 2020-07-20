/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
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
#include "usart.h"
#include "global.h"

/* USER CODE BEGIN 0 */
uint8_t USART_RX_BUF[256] = {0};        //定义接受数据的缓存buf，modbus协议一帧数据不会超过256字节，雷达应用定义的寄存器少，实际不会用到100字节
uint8_t USART_RX_POS = 0;
uint8_t aRxBuffer[1];
uint8_t dataErr = 0;
/* USER CODE END 0 */

UART_HandleTypeDef huart1;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
	uint32_t baud[8] = {2400, 4800, 9600, 14400, 19200, 38400, 57600, 115200};
	if (config.baudrate && (config.baudrate < 9)) {
		huart1.Init.BaudRate = baud[config.baudrate - 1];
	} else {
		huart1.Init.BaudRate = 9600;
	}
	if (config.parity == 0 || config.parity > 2) {
		huart1.Init.WordLength = UART_WORDLENGTH_8B;
		 huart1.Init.Parity = UART_PARITY_NONE;
	} else if(config.parity == 1) {
		huart1.Init.WordLength = UART_WORDLENGTH_9B;
		huart1.Init.Parity = UART_PARITY_EVEN;
	} else if(config.parity == 2) {
		huart1.Init.WordLength = UART_WORDLENGTH_9B;
		huart1.Init.Parity = UART_PARITY_ODD;
	}
	if (config.stopBit == 1 || config.stopBit >3) {
		huart1.Init.StopBits = UART_STOPBITS_1;
	} else if (!config.stopBit) {
		huart1.Init.StopBits = UART_STOPBITS_0_5;
	} else if (config.stopBit == 2) {
		huart1.Init.StopBits = UART_STOPBITS_1_5;
	} else {
		huart1.Init.StopBits = UART_STOPBITS_2;
	}
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
     Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 8, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
/**
  * ��������: �ض���c�⺯��printf��huart3
  * �������?: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
/*
#ifdef __GNUC__

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)

PUTCHAR_PROTOTYPE
{
  // ע�������һ��������?&huart3����Ϊcubemx�����˴���3�Զ����ɵ�
  HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
  return ch;
}
#endif
/*
 * 定义write调用中断发送
 */
int _write(int file, char *ptr, int len)
{
	/*
	if (huart1.gState == HAL_UART_STATE_BUSY) {
		return 0;
	}*/
	return HAL_UART_Transmit_IT(&huart1, (uint8_t*)ptr, len);
}
/* USER CODE END 1 */

extern volatile uint8_t dataFrameComp;
extern volatile uint8_t dataFrameErr;
extern volatile uint8_t timInCount;
extern volatile uint8_t dataAna;
extern TIM_HandleTypeDef htim2;

/*
 * 接受中断最终会调用这个回调函数
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if( huart->Instance==USART1) {
		timInCount = 0;                 //每次让tim2中断里操作的变量timInCount清零
		if (dataFrameComp) {            //如果上一帧已经完，说明这次是本帧的第一个字节产生的中断
			dataFrameComp = 0;
			dataFrameErr = 0;
			dataErr = 0;
			dataAna = 0;
			USART_RX_BUF[0] = aRxBuffer[0];            //给缓存buf的第一字节赋值
			USART_RX_POS = 1;                          //让缓存buf的计数器从第二字节开始
		}
		/*
		 * 不是帧的第一个字节产生的中断
		 */
		else {
			USART_RX_BUF[USART_RX_POS] = aRxBuffer[0];          //给缓存buf相应位置赋值
			USART_RX_POS++;                                    //计数器加一
			if (USART_RX_POS == 256) {                         //计数器不能超范围
				USART_RX_POS = 0;
			}
			HAL_TIM_Base_Stop_IT(&htim2);                       //关tim2，为了让tim2计数器清零
			if (dataFrameErr) {
				dataErr = 1;
			}
		}
		__HAL_TIM_SET_COUNTER(&htim2, 0);                  //tim2计数器清零
		HAL_TIM_Base_Start_IT(&htim2);                      //重启
	}
}

void USART1_IRQHandler(void)
{
	uint32_t timeout=0;
	uint32_t maxDelay=0x1FFFF;

	uint32_t isrflags   = READ_REG(huart1.Instance->ISR);
	uint32_t cr1its     = READ_REG(huart1.Instance->CR1);
	uint32_t cr3its     = READ_REG(huart1.Instance->CR3);
	uint32_t errorflags = (isrflags & (uint32_t)(USART_ISR_PE | USART_ISR_FE | USART_ISR_ORE | USART_ISR_NE));
	/*
	 * 如果是接受中断，或者错误中断，进第一个分支
	 */
	if ( (((errorflags == RESET) && (isrflags & USART_ISR_RXNE) != RESET) && ((cr1its & USART_CR1_RXNEIE) != RESET)) ||
			((errorflags != RESET)&& (((cr3its & USART_CR3_EIE) != RESET)
	          || ((cr1its & (USART_CR1_RXNEIE | USART_CR1_PEIE)) != RESET)))) {
		HAL_UART_IRQHandler(&huart1);

		timeout=0;
		while (huart1.RxState != HAL_UART_STATE_READY)
		{
			timeout++;
			if(timeout>maxDelay) break;
		}
		timeout=0;
		while(HAL_UART_Receive_IT(&huart1, (uint8_t *)aRxBuffer, 1) != HAL_OK)  //HAL库函数HAL_UART_IRQHandler会关串口接受中断，需要重新开启
		{
			timeout++;
			if(timeout>maxDelay) break;
		}
	} else {                                 //如果是发送中断
		HAL_UART_IRQHandler(&huart1);
	}
}

void uartConfig()
{
	uint32_t baud[8] = {2400, 4800, 9600, 14400, 19200, 38400, 57600, 115200};
	HAL_UART_DeInit(&huart1);

	if (config.baudrate && (config.baudrate < 9)) {
		huart1.Init.BaudRate = baud[config.baudrate - 1];
	} else {
		huart1.Init.BaudRate = 9600;
	}
	if (config.parity == 0 || config.parity > 2) {
		huart1.Init.WordLength = UART_WORDLENGTH_8B;
		 huart1.Init.Parity = UART_PARITY_NONE;
	} else if(config.parity == 1) {
		huart1.Init.WordLength = UART_WORDLENGTH_9B;
		huart1.Init.Parity = UART_PARITY_EVEN;
	} else if(config.parity == 2) {
		huart1.Init.WordLength = UART_WORDLENGTH_9B;
		huart1.Init.Parity = UART_PARITY_ODD;
	}
	if (config.stopBit == 1 || config.stopBit >3) {
		huart1.Init.StopBits = UART_STOPBITS_1;
	} else if (!config.stopBit) {
		huart1.Init.StopBits = UART_STOPBITS_0_5;
	} else if (config.stopBit == 2) {
		huart1.Init.StopBits = UART_STOPBITS_1_5;
	} else {
		huart1.Init.StopBits = UART_STOPBITS_2;
	}
	HAL_UART_Init(&huart1);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
