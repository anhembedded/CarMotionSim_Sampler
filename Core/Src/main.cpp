/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"
#include "main_cpp.hpp"
#include "LiquidCrystal.h"
#include "../USER_API/UHAL/UHAL_USART/uhal_usart.hpp"
#include <string>
#include <algorithm>
#include <array>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
uint8_t _surge;
uint8_t _sway;
uint8_t _traction;


volatile uint8_t _uartBuffer = 0;
std::array<uint8_t, 10>  _arrayBuffer;
uint8_t _index = 0;

uint8_t Axis1a {};
uint8_t Axis2a {};
uint8_t Axis3a {};

struct simtool
{
    uint8_t sway;
    uint8_t heave;
    uint8_t traction;
};
simtool thisData;

simtool getData(std::array<uint8_t,12> data)
{
    simtool temp {};
    return temp;
}


void  getData(std::array<uint8_t,10> &data,uint8_t &surge, uint8_t &sway, uint8_t &traction)
{
    constexpr auto nextByte = 1;
    constexpr auto startByte = '[';

    auto A_iter = std::find(data.begin(),  data.end(),'A');
    auto B_iter = std::find(data.begin(), data.end(), 'B');
    auto C_iter = std::find(data.begin(), data.end(), 'C');


    auto exam = [data](decltype(A_iter) praIter)
    {
        if((praIter != data.end()) && (praIter != data.begin()))
        {
            return 1;
        }
        return 0;
    };

    if(exam(A_iter))
    {
       if(*(A_iter-nextByte) == startByte)
       {
    	   surge = *(A_iter+nextByte);
       }
    }
    if(exam(B_iter))
    {
        if(*(B_iter-nextByte) == startByte)
        {
        	sway = *(B_iter+nextByte);
        }
    }
    if(exam(C_iter))
    {
        if(*(C_iter-nextByte) == startByte)
        {
            traction = *(C_iter+nextByte);
        }
    }

}


#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config();


/**
  * @brief  The application entry point.
  * @retval int
  */
const char *myName = "TranHoangAnh";
int main()
{
  
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_0);

  SystemClock_Config();  
  MX_GPIO_Init();

  
  UHAL_USART6::initialize();
  UHAL_USART6::interruptReceiveInit();
  
  while (true)
  {
    
  }
  
}


extern "C"
{
void USART6_IRQHandler(void)
{
    using namespace UHAL_USART6;
    using namespace UHAL_USART6::flag_IT;

//    if(TXE::isSet())
//    {
//        transmitData(_uartBuffer);
//        TXE::clear();
//    }


    if(RXNE::isSet())
    {
    	if(_index <10)
    	{
    		_index++;

    	}else
    	{
    		getData(_arrayBuffer, _surge,_sway,_traction);
    		_index = 0;

    	}
      _arrayBuffer[_index] = receivedData();


    }
    NVIC_ClearPendingIRQ(UHAL_USART6::thisIRQn);
}

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_5)
  {
  }
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  LL_RCC_HSE_EnableBypass();
  LL_RCC_HSE_Enable();

   /* Wait till HSE is ready */
  while(LL_RCC_HSE_IsReady() != 1)
  {

  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_4, 168, LL_RCC_PLLP_DIV_2);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_Init1msTick(168000000);
  LL_SetSystemCoreClock(168000000);
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
  __disable_irq();
  while (1)
  {
  }
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
//	void *str = file;
	std::string _file = reinterpret_cast<const char*>(file);
	std::string _line = std::to_string(line);
	std::string msg =_line + _file + '\n';
	UHAL_USART6::send(msg);

}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

#pragma clang diagnostic pop
