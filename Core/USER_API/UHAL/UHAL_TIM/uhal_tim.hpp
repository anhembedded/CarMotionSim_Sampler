/**
  ******************************************************************************
  * @file    uhal_tim.hpp
  * @author  Trần Hoàng Anh
  * @brief   Header file for User hardware abstract layer for the timer
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]
    The LL CORTEX driver contains a set of generic APIs that can be
    used by user:
      (+) SYSTICK configuration used by LL_mDelay and LL_Init1msTick
          functions
      (+) Low power mode configuration (SCB register of Cortex-MCU)
      (+) MPU API to configure and enable regions
          (MPU services provided only on some devices)
      (+) API to access to MCU info (CPUID register)
      (+) API to enable fault handler (SHCSR accesses)

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */



#ifndef CARMOTIONSIM_SAMPLER_UHAL_TIM_HPP
#define CARMOTIONSIM_SAMPLER_UHAL_TIM_HPP
#include "main_cpp.hpp"


/**
 * @namespace UHAL_TIM5_PWM
 * @brief This namespace for Hardware Abstract Layer for 2 change PWM of a timer
 */
namespace UHAL_TIM5_PWM /// @brief User hardware abstraction layer for timer 5 with PWM
{

    /*!< This namespace Instance */
    const decltype(TIM5) thisInstance = TIM5;
    /*!< GPIO port for the PWM output pin */
    const decltype(GPIOA) thisInstanceGPIO = GPIOA;
    /*!< Timer Interrupt line's number */
    const auto thisIRQn = TIM5_IRQn;
    /*!< Timer "counting register Type" */
    typedef uint32_t thisTimerType_T;
    /*!< Timer "prescaler Type" */
    typedef uint16_t thisTimerPrescaler_T;

    /**
     * @brief Check if the peripheral's clock be enabled or not
     * @return 1 if clock is enabled, otherwise 0
     */
    __SFI auto isPeripheralClKEnabled()
    {
        return LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM5);
    }
    /**
     * \brief check of the GPIO's clock of "this" output peripheral be enabled or not
     * \return 1 if clock is enabled, otherwise 0
     */
    __SFI auto isGPIOClKEnabled()
    {
        return LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    }

    void initialize();

    __SFI auto enable(); ///@note No implement
    __SFI auto disable();	///@note No implement

    void startCounter();

    void stopCounter();

    void upCountingDirection();     /// init
    void downCountingDirection();   /// init
    void selectTimerClock();        /// External or anything's else. init
    void channelPwmModeSelection(); /// init
    void enablePreloadForChannel(); /// init

    void holdOnUpdateEvent();

    void releaseUpdateEvent();

    void updateEventGenerating();

    /// @brief selecting polarity for channel x
    [[deprecated("this flag no pending")]] void OCxPolarity();  // not important

    void setPrescaler(thisTimerPrescaler_T prescalerVar); // 1 - 16bit
    void setAutoReload(thisTimerType_T autoReloadVar);

    void setCaptureCompareCH1(thisTimerType_T captureCompareVar); /// @note must be smaller than autoReloadVar
    void setCaptureCompareCH2(thisTimerType_T captureCompareVar); /// @note must be smaller than autoReloadVar
    //todo: Examination flag for Interrupts
    void enableInterrupt();
    //todo: Examination flag for Interrupts
    void disableInterrupt();

     auto enableGPIOClock();

     auto disableGPIOClock();

     auto enablePerihClock();

     auto disablePerihClock();

    namespace flag_IT::flagX
    {

        __SFI auto isSet();

        __SFI auto clear();

        __SFI auto enableInterrupt();

        __SFI auto clearPendingBit();
    }
    namespace developing
    {
        void firstRun();

    }
}

#endif // CARMOTIONSIM_SAMPLER_UHAL_TIM_HPP
