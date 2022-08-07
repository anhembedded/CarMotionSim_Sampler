//
// Created by hoang on 11/29/2021.
//

#include "UHAL_DMA.hpp"


// DMA2 ADC1
void UHAL_DMA2::DMA_ADC1::enablePerihClock() {
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
}
void UHAL_DMA2::DMA_ADC1::setBufferAddress(uintptr_t bufferAddress) {
    LL_DMA_SetMemoryAddress(thisInstance, thisStream, bufferAddress);
}

void UHAL_DMA2::DMA_ADC1::initialize2()
{
	
	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);

	  NVIC_SetPriority(thisIRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1, 1));
	  NVIC_EnableIRQ(thisIRQn);
	
}

void UHAL_DMA2::DMA_ADC1::enable() {
    LL_DMA_EnableStream(thisInstance, thisStream);
}

void UHAL_DMA2::DMA_ADC1::setNumberOfDataTransfer(uint16_t numb) {
    LL_DMA_SetDataLength(thisInstance, thisStream, numb);
}

void UHAL_DMA2::DMA_ADC1::setPeripheralADDress(const uintptr_t address) {
    LL_DMA_SetPeriphAddress(thisInstance, thisStream, address);
}

void UHAL_DMA2::DMA_ADC1::enableInterrupt()
{
    flag_IT::DMEIF::enableInterrupt();
    flag_IT::FEIF::enableInterrupt();
    flag_IT::HTIF::enableInterrupt();
    flag_IT::TCIF::enableInterrupt();
    flag_IT::TEIF::enableInterrupt();
}

void UHAL_DMA2::DMA_ADC1::initialize() {
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);

    NVIC_SetPriority(thisIRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
    NVIC_EnableIRQ(thisIRQn);
}




// DMA2 USART6

void UHAL_DMA2::DMA_USART1::enablePerihClock() {
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
}
void UHAL_DMA2::DMA_USART1::setBufferAddress(uintptr_t bufferAddress) {
    LL_DMA_SetMemoryAddress(thisInstance, thisStream, bufferAddress);
}

void UHAL_DMA2::DMA_USART1::initialize2()
{
	
	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);

	  NVIC_SetPriority(thisIRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
	  NVIC_EnableIRQ(thisIRQn);
	
}


void UHAL_DMA2::DMA_USART1::enable() {
    LL_DMA_EnableStream(thisInstance, thisStream);
}

void UHAL_DMA2::DMA_USART1::setNumberOfDataTransfer(uint16_t numb) {
    LL_DMA_SetDataLength(thisInstance, thisStream, numb);
}

void UHAL_DMA2::DMA_USART1::setPeripheralADDress(const uintptr_t address) {
    LL_DMA_SetPeriphAddress(thisInstance, thisStream, address);
}

void UHAL_DMA2::DMA_USART1::enableInterrupt()
{
    flag_IT::DMEIF::enableInterrupt();
    flag_IT::FEIF::enableInterrupt();
    flag_IT::HTIF::enableInterrupt();
    flag_IT::TCIF::enableInterrupt();
    flag_IT::TEIF::enableInterrupt();
}

void UHAL_DMA2::DMA_USART1::initialize() {
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
    NVIC_SetPriority(thisIRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
    NVIC_EnableIRQ(thisIRQn);
}

void UHAL_DMA2::DMA_USART1::disable() {
    LL_DMA_DisableStream(thisInstance, thisStream);
}

uint8_t UHAL_DMA2::DMA_USART1::isDisabled()
{
	return !LL_DMA_IsEnabledStream(thisInstance, thisStream);
}


