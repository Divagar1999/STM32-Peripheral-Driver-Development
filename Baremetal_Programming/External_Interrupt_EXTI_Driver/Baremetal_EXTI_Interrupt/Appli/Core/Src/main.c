/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

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

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void SystemIsolation_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static void GPIO_Init(void);
static void External_IT_Init(void);

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/
  HAL_Init();

  /* USER CODE BEGIN Init */
  GPIO_Init();

  External_IT_Init();

  /* USER CODE END Init */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  SystemIsolation_Config();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief RIF Initialization Function
  * @param None
  * @retval None
  */
  static void SystemIsolation_Config(void)
{

  /* USER CODE BEGIN RIF_Init 0 */

  /* USER CODE END RIF_Init 0 */

  /* set all required IPs as secure privileged */
  __HAL_RCC_RIFSC_CLK_ENABLE();

  /*RIMC configuration*/
  RIMC_MasterConfig_t RIMC_master = {0};
  RIMC_master.MasterCID = RIF_CID_1;
  RIMC_master.SecPriv = RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_NPRIV;
  HAL_RIF_RIMC_ConfigMasterAttributes(RIF_MASTER_INDEX_ETH1, &RIMC_master);

  /* USER CODE BEGIN RIF_Init 1 */

  /* USER CODE END RIF_Init 1 */
  /* USER CODE BEGIN RIF_Init 2 */

  /* USER CODE END RIF_Init 2 */

}

/* USER CODE BEGIN 4 */

 static void GPIO_Init()
  {
  	// Clock enable for Port G and Port C
  	RCC ->AHB4ENR |= (0x1 << 6 );
  	RCC ->AHB4ENR |= (0x1 << 2 );

  	//Input pin 13, Port C
  	GPIOC ->MODER &= ~(0X3 << 26); // RESET THE PIN 13

  	//Output pin 8, Port G
  	GPIOG ->MODER &= ~(0x3 << 16);
  	GPIOG ->MODER |= (0x1 << 16);

  	//Pull-Down Resistor for button pin 13, port c

  	GPIOC ->PUPDR &= ~(0x3 << 26);
  	GPIOC ->PUPDR |= (0x2 << 26);

  //	//Pull up for LED ( PIN 8, PORT G) to keep the led high during boot
  //
  //	GPIOG ->PUPDR &= ~(0x3 << 16);
  //	GPIOG ->PUPDR |= (0x1 << 16);

  	GPIOG ->BSRR |= (0x1 << 8);  // HIGH as default; LED is off by default

  }

 static void External_IT_Init()
 {
	 //

	 EXTI ->EXTICR[3] &= ~(0xFF << 8 ); // Connecting the PC13 pin to EXTI line 13
	 EXTI ->EXTICR[3] |= (0x02 << 8);	// Connecting the PC13 pin to EXTI line 13

	 EXTI ->IMR1 |= 0x1 << 13;   // Enabling the EXTI line 13 to generate interrupt request

	 EXTI ->FTSR1 |= 0x1 <<13;   // Enabling the falling trigger
	 EXTI ->RTSR1 |= 0x1 <<13;	// Enabling the Rising trigger


	 NVIC_SetPriority(EXTI13_IRQn, 0);
	 NVIC_EnableIRQ(EXTI13_IRQn);


 }

void EXTI13_IRQHandler()
{
	if(EXTI ->RPR1 & 0x01 << 13 )
	{
		EXTI ->RPR1 &= (0x01 << 13); // Resetting the bit

		GPIOG ->BSRR |= (0x1 << (8+16) ); // set
	}
	else if(EXTI ->FPR1 & 0x01 << 13 )
	{
		EXTI ->FPR1 &= (0x01 << 13); // Resetting the bit

		GPIOG ->BSRR |= (0x1 << 8 );  // reset

	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
