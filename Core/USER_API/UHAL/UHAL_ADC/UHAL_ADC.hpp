/**
  ******************************************************************************
  * @file    UHAL_ADC.hpp
  * @author  Trần Hoàng Anh
  * @brief   Header file of ADC User Hardware Layer ADC1
  ******************************************************************************
  * @attention  More information, might be updated late
  * @warning    This User Hardware Layer just support for only regular channel
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CARMOTIONSIM_SAMPLER_UHAL_ADC_HPP
#define CARMOTIONSIM_SAMPLER_UHAL_ADC_HPP

#include "main_cpp.hpp"
#include "../UHAL_DMA/UHAL_DMA.hpp"
#include "stm32f4xx_ll_adc.h"


namespace UHAL_ADC /// @brief this namespace for the Hardware abstract layer of ADC peripheral
{

    //* GENERAL PERIPHERAL METHOD *//

    /*!< This namespace Instance */
    const decltype(ADC1) thisInstance = ADC1;
    /*!< GPIO port for the PWM output pin */
    const decltype(GPIOA) thisInstanceGPIO = GPIOA;
    /*!< Timer Interrupt line's number */
    const auto thisIRQn = ADC_IRQn;
    /*!< Timer "counting register Type" */
    typedef uint_least16_t thisADC_T;


    //* METHODS FOR POS ASSERT *//
    /**
     * @brief  METHODS FOR POS ASSERT
     * @brief Check if the peripheral's clock be enabled or not
     * @return 1 if clock is enabled, otherwise 0
     */
    __SFI auto isPeripheralClKEnabled() {
        return LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM5);
    }
    /**
     * @brief METHODS FOR POS ASSERT
     * @brief check of the GPIO's clock of "this" output peripheral be enabled or not
     * @return 1 if clock is enabled, otherwise 0
     */
    __SFI auto isGPIOClKEnabled() {
        return LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    }


    /**
     * @brief   Initiation for the ADC1 to use
     * @param   None
     * @retval  Void
     * @note    Will be initial several primary step for make ADC can be use
     *          and setup features to make specific of the project, 
     *          the features be setup include:
     *          Clock prescaler.
     *          Resolution.
     *          Data Alignment.
     *          Scan conversion mode.
     *          Continuous conversion mode.
     *          End of conversion selection.
     *          Number of the conversion in the conversion group.
     *          Rank of a channel in a conversion group.
     *          Sampling time.
     * @note    Enable Peripherals clock. Enable peripheral's GPIO clock.
     *          Setup alternative function for the associate GPIO.
     * @author Trần Hoàng Anh        
     *          
     */
    void initialize();
    void initialize2();

/**
  * @brief  Enable the selected ADC instance.
  * @note   On this STM32 series, after ADC enable, a delay for 
  *         ADC internal analog stabilization is required before performing a
  *         ADC conversion start.
  *         Refer to device datasheet, parameter tSTAB.
**/
     void enable();
    /**
  * @brief  Disable the selected ADC instance.
   **/
     void disable(); ///@note implement this

    void enableInterrupt();

    // todo: Examination flag for Interrupts
    void disableInterrupt();

    void enableGPIOClock();

    void disableGPIOClock();

    void enablePerihClock();

    void disablePerihClock();

    // All Methods below here are the specific method of ADC peripherals.
    // this base on the technical document those have been examined
    void on();

    void off();

    /**
  * @brief  Start ADC group regular conversion.
  * @note   On this STM32 series, this function is relevant only for
  *         internal trigger (SW start), not for external trigger:
  *         - If ADC trigger has been set to software start, ADC conversion
  *           starts immediately.
  */
    void startConversion(); /// Regular channel
    [[deprecated("No software stop")]] auto stopConversion();  /// Regular channel
    [[deprecated("The initialize function handle it")]] auto channelSelection(); /// initialize method has handled it.
    [[deprecated("The initialize function handle it")]] auto enableScanMode();  /// @brief
    [[deprecated("The initialize function handle it")]]auto disableScanMode(); /// @brief
    /**
    * @brief   To recover the ADC from OVR state when the DMA is used
    * @param   None
    * @retval  Void
    * @note     Follow the steps below: (according to reference manual)
     *          1.Reinitialize the DMA (adjust destination address and NDTR counter)
     *          2.Clear the ADC OVR bit in ADC_SR register.
     *          3.Trigger the ADC to start the conversion.
    * @author Trần Hoàng Anh
    */
    void recoverAdcFormOverrun(uintptr_t addressBuffer, uintptr_t addressPeripherals, uint16_t numberOfDataTransfer);
    /**
   * @brief   get ADC result directly from register
   * @param   None
   * @retval  thisADC_T The last ADC's result conversion
   * @retval    Value between Min_Data=0x000 and Max_Data=0xFFF
   * @note     Just the last ADC's result conversion
   * @author Trần Hoàng Anh
   */
    thisADC_T readAdcConversionRegister();

    namespace flag_IT /// @brief flag and interrupt's relevant
    {
    	/*This bit is set by hardware at the end of the conversion of a regular group of channels. It is
    cleared by software or by reading the ADC_DR register.*/
        namespace EOC   /// @brief End of conversion of regular group
        {
            __SFI auto isSet() {
              return  LL_ADC_IsActiveFlag_EOCS(thisInstance);
            }

            __SFI auto clear() {
                LL_ADC_ClearFlag_EOCS(thisInstance);
            }

            __SFI auto enableInterrupt() {
                LL_ADC_EnableIT_EOCS(thisInstance);
            }
            // OVRIE
            __SFI auto isEnableInterrupt() {
               return LL_ADC_IsEnabledIT_EOCS(thisInstance);
            }

            [[deprecated("this flag no pending")]] __SFI auto clearPendingBit();
        }
        namespace OVR   /// @brief Overrun error
        {
            __SFI auto isSet() {
               return LL_ADC_IsActiveFlag_OVR(thisInstance);
            }

            __SFI auto clear() {
                LL_ADC_ClearFlag_OVR(thisInstance);
            }

            __SFI auto enableInterrupt() {
                LL_ADC_EnableIT_OVR(thisInstance);
            }
            // OVRIE
            __SFI auto isEnableInterrupt() {
              return  LL_ADC_IsEnabledIT_OVR(thisInstance);
            }

           [[deprecated("this flag no pending")]] __SFI auto clearPendingBit();
        }
    }

    void DMAReInitForRecover();
    thisADC_T fristTest(uintptr_t addressBuffer);

}

#endif // CARMOTIONSIM_SAMPLER_UHAL_ADC_HPP
