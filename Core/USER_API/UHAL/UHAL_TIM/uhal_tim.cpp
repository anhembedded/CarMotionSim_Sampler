//
// Created by hoang on 11/25/2021.
//

#include "uhal_tim.hpp"


void UHAL_TIM5_PWM::initialize() {
    /* USER CODE BEGIN TIM5_Init 0 */

    /* USER CODE END TIM5_Init 0 */

    LL_TIM_InitTypeDef TIM_InitStruct = {0};
    LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};

    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM5);

    /* TIM5 DMA Init */

    /* TIM5_CH1 Init */


    /* TIM5 interrupt Init */
  //  NVIC_SetPriority(TIM5_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
   // NVIC_EnableIRQ(TIM5_IRQn);

    /* USER CODE BEGIN TIM5_Init 1 */

    /* USER CODE END TIM5_Init 1 */
    TIM_InitStruct.Prescaler = 01211;
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload = 255;
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    LL_TIM_Init(TIM5, &TIM_InitStruct);


    LL_TIM_EnableARRPreload(TIM5);


    LL_TIM_OC_EnablePreload(TIM5, LL_TIM_CHANNEL_CH1);
    TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
    TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_ENABLE; // enable Signal
    TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.CompareValue = 255;
    TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
    LL_TIM_OC_Init(TIM5, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);
    LL_TIM_OC_DisableFast(TIM5, LL_TIM_CHANNEL_CH1);

    LL_TIM_OC_EnablePreload(TIM5, LL_TIM_CHANNEL_CH2);
    TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
    LL_TIM_OC_Init(TIM5, LL_TIM_CHANNEL_CH2, &TIM_OC_InitStruct);
    LL_TIM_OC_DisableFast(TIM5, LL_TIM_CHANNEL_CH2);
    LL_TIM_SetTriggerOutput(TIM5, LL_TIM_TRGO_ENABLE);


    LL_TIM_DisableMasterSlaveMode(TIM5);
    /* USER CODE BEGIN TIM5_Init 2 */

    /* USER CODE END TIM5_Init 2 */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    /**TIM5 GPIO Configuration
    PA0-WKUP     ------> TIM5_CH1
    PA1     ------> TIM5_CH2
    */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_0 | LL_GPIO_PIN_1;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_2;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void UHAL_TIM5_PWM::holdOnUpdateEvent() {
    LL_TIM_DisableUpdateEvent(thisInstance);
}

void UHAL_TIM5_PWM::releaseUpdateEvent() {
    LL_TIM_EnableUpdateEvent(thisInstance);
}

void UHAL_TIM5_PWM::updateEventGenerating() {

    if constexpr(systemDebug == debug_T::debugOn)
    {
        assert_param(isPeripheralClKEnabled());
    }
    LL_TIM_GenerateEvent_UPDATE(thisInstance);
}


/**
* \brief Set prescaler
* \note This not intimidate set, otherwise it's waiting for update event
*/
void UHAL_TIM5_PWM::setPrescaler(UHAL_TIM5_PWM::thisTimerPrescaler_T prescalerVar)
{
    if constexpr(systemDebug == debug_T::debugOn)
    {
        assert_param(isPeripheralClKEnabled());
    }
    LL_TIM_SetPrescaler(thisInstance, prescalerVar);
}

void UHAL_TIM5_PWM::setAutoReload(UHAL_TIM5_PWM::thisTimerType_T autoReloadVar) {

    if constexpr(systemDebug == debug_T::debugOn)
    {
        assert_param(isPeripheralClKEnabled());
    }

    LL_TIM_SetAutoReload(thisInstance, autoReloadVar);


}

void UHAL_TIM5_PWM::setCaptureCompareCH1(UHAL_TIM5_PWM::thisTimerType_T captureCompareVar) {

    if constexpr(systemDebug == debug_T::debugOn)
    {
        assert_param(isPeripheralClKEnabled());
    }
    LL_TIM_OC_SetCompareCH1(thisInstance, captureCompareVar);

}

void UHAL_TIM5_PWM::setCaptureCompareCH2(UHAL_TIM5_PWM::thisTimerType_T captureCompareVar) {

    if constexpr(systemDebug == debug_T::debugOn)
    {
        assert_param(isPeripheralClKEnabled());
    }
    LL_TIM_OC_SetCompareCH2(thisInstance, captureCompareVar);
}

auto UHAL_TIM5_PWM::enableGPIOClock() {
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
}

auto UHAL_TIM5_PWM::disableGPIOClock() {
    LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
}

auto UHAL_TIM5_PWM::enablePerihClock() {
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM5);
}

auto UHAL_TIM5_PWM::disablePerihClock() {
    LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM5);
}

void UHAL_TIM5_PWM::enableInterrupt() {
    NVIC_SetPriority(thisIRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(thisIRQn);
}

void UHAL_TIM5_PWM::disableInterrupt() {
    NVIC_DisableIRQ(thisIRQn);
}

void UHAL_TIM5_PWM::startCounter() {

    if constexpr(systemDebug == debug_T::debugOn)
    {
        assert_param(isPeripheralClKEnabled());
    }
    LL_TIM_EnableCounter(thisInstance);
}

void UHAL_TIM5_PWM::stopCounter() {
    if constexpr(systemDebug == debug_T::debugOn)
    {
        assert_param(isPeripheralClKEnabled());
    }
    LL_TIM_DisableCounter(thisInstance);
}


void UHAL_TIM5_PWM::developing::firstRun() {

    /*!< Pos assert */
	initialize();
    if constexpr(systemDebug == debug_T::debugOn)
    {
        assert_param(isPeripheralClKEnabled());
        assert_param(isGPIOClKEnabled());
    }


    setCaptureCompareCH1(100);
    setCaptureCompareCH2(200);

    startCounter();


   
}
