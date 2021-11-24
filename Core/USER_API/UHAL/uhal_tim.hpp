
/**
* @file
* @brief For the hardware abstract layer for timer7
*/

#ifndef CARMOTIONSIM_SAMPLER_UHAL_TIM_HPP
#define CARMOTIONSIM_SAMPLER_UHAL_TIM_HPP

#include "main_cpp.hpp"
#include "ufl_clk.hpp"

typedef uint16_t TIM7_T;


/**
* \namespace UFL_TIM7
* \brief This is the hardware abstract layer for timer2
*/namespace UFL_TIM7
{
    
    constexpr auto  thisTimerClk = clk::APB1Timer;
    constexpr auto timerMaxValue = UINT16_MAX;
    // thisInstance = TIM7;
    constexpr auto thisPeripheralClk = LL_APB1_GRP1_PERIPH_TIM7;
    constexpr auto interruptNumber = TIM7_IRQn;

    __SFI auto initialize(TIM7_T Prescaler, TIM7_T AutoReload);
    __SFI auto setPrescaler(TIM7_T Prescaler);
    __SFI auto setAutoReload(TIM7_T AutoReload);
    __SFI auto enableClk();
    __SFI auto enableCounterClk();
    __SFI auto disableClk();
    __SFI auto enableCounting();
    __SFI auto disableUpdateEvent();
    __SFI auto updateEvent();
    
    namespace flag_interrupt
    {
        __SFI auto enableUpdateInterrupt();
        namespace UIF
        {
            __SFI auto isSet();
            __SFI auto clear();
        }
    }

}

namespace UFL_TIMx
{

}

// definition

__SFI auto UFL_TIM7::initialize(uint16_t Prescaler = 500, uint16_t Autoreload = 65535)
{

    LL_TIM_InitTypeDef TIM_InitStruct = {0};
    TIM_InitStruct.Prescaler = Prescaler;
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload = Autoreload;
    LL_TIM_Init(TIM7, &TIM_InitStruct);
    LL_TIM_DisableARRPreload(TIM7);
    LL_TIM_SetTriggerOutput(TIM7, LL_TIM_TRGO_RESET);
    LL_TIM_DisableMasterSlaveMode(TIM7);

}

__SFI auto UFL_TIM7::enableClk()
{
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7);
}
__SFI auto UFL_TIM7::disableClk()
{
    LL_APB1_GRP1_DisableClock(thisPeripheralClk);
}
__SFI auto UFL_TIM7::enableCounterClk()
{  
    SET_BIT(TIM7->CR1, TIM_CR1_CEN);
}


#endif //CARMOTIONSIM_SAMPLER_UHAL_TIM_HPP
