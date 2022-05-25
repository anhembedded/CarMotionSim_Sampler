//
// Created by hoang on 11/28/2021.
//

#include "UHAL_ADC.hpp"

/**
  * @brief  Enable the selected ADC instance.
  * @note   On this STM32 series, after ADC enable, a delay for 
  *         ADC internal analog stabilization is required before performing a
  *         ADC conversion start.
  *         Refer to device datasheet, parameter tSTAB.
**/

void UHAL_ADC::enable() {
   LL_ADC_Enable(thisInstance);
    waitUntil(LL_ADC_IsEnabled(ADC1));
}

void UHAL_ADC::disable() {
    LL_ADC_Disable(thisInstance);
}

void UHAL_ADC::enableInterrupt() {

	flag_IT::EOC::enableInterrupt();
	flag_IT::OVR::enableInterrupt();
    NVIC_SetPriority(ADC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
    NVIC_EnableIRQ(ADC_IRQn);
}


void UHAL_ADC::enableGPIOClock() {
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
}

void UHAL_ADC::disableGPIOClock() {
      // todo not implement yet
}

void UHAL_ADC::enablePerihClock() {
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);
}

void UHAL_ADC::disablePerihClock() {
    // todo not implement yet
}

void UHAL_ADC::on() {
    LL_ADC_Enable(thisInstance);
}

void UHAL_ADC::off() {
    LL_ADC_Disable(thisInstance);
}


void UHAL_ADC::startConversion() {
    LL_ADC_REG_StartConversionSWStart(thisInstance);
}



void UHAL_ADC::recoverAdcFormOverrun(uintptr_t addressBuffer, uintptr_t addressPeripherals, uint16_t numberOfDataTransfer) {

	flag_IT::OVR::clear();
    DMAReInitForRecover();
    UHAL_DMA2::DMA_ADC1::setBufferAddress(addressBuffer);
    UHAL_DMA2::DMA_ADC1::setPeripheralADDress(addressPeripherals);
    UHAL_DMA2::DMA_ADC1::setNumberOfDataTransfer(numberOfDataTransfer);
    startConversion();

}

UHAL_ADC::thisADC_T UHAL_ADC::readAdcConversionRegister() {
    return LL_ADC_REG_ReadConversionData12(thisInstance);
}
void UHAL_ADC::initialize2()
{

	  /* USER CODE BEGIN ADC1_Init 0 */

	  /* USER CODE END ADC1_Init 0 */

	  LL_ADC_InitTypeDef ADC_InitStruct = {0};
	  LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = {0};
	  LL_ADC_CommonInitTypeDef ADC_CommonInitStruct = {0};

	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* Peripheral clock enable */
	  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);

	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	  /**ADC1 GPIO Configuration
	  PA2   ------> ADC1_IN2
	  PA3   ------> ADC1_IN3
	  */
	  GPIO_InitStruct.Pin = LL_GPIO_PIN_2|LL_GPIO_PIN_3;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /* ADC1 DMA Init */

	  /* ADC1 Init */
	  LL_DMA_SetChannelSelection(DMA2, LL_DMA_STREAM_0, LL_DMA_CHANNEL_0);

	  LL_DMA_SetDataTransferDirection(DMA2, LL_DMA_STREAM_0, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

	  LL_DMA_SetStreamPriorityLevel(DMA2, LL_DMA_STREAM_0, LL_DMA_PRIORITY_VERYHIGH);

	  LL_DMA_SetMode(DMA2, LL_DMA_STREAM_0, LL_DMA_MODE_CIRCULAR);

	  LL_DMA_SetPeriphIncMode(DMA2, LL_DMA_STREAM_0, LL_DMA_PERIPH_NOINCREMENT);

	  LL_DMA_SetMemoryIncMode(DMA2, LL_DMA_STREAM_0, LL_DMA_MEMORY_INCREMENT);

	  LL_DMA_SetPeriphSize(DMA2, LL_DMA_STREAM_0, LL_DMA_PDATAALIGN_HALFWORD);

	  LL_DMA_SetMemorySize(DMA2, LL_DMA_STREAM_0, LL_DMA_MDATAALIGN_HALFWORD);

	  LL_DMA_EnableFifoMode(DMA2, LL_DMA_STREAM_0);

	  LL_DMA_SetFIFOThreshold(DMA2, LL_DMA_STREAM_0, LL_DMA_FIFOTHRESHOLD_1_4);

	  LL_DMA_SetMemoryBurstxfer(DMA2, LL_DMA_STREAM_0, LL_DMA_MBURST_SINGLE);

	 LL_DMA_SetPeriphBurstxfer(DMA2, LL_DMA_STREAM_0, LL_DMA_PBURST_SINGLE);

	  /* ADC1 interrupt Init */
	//  NVIC_SetPriority(ADC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1, 1));
	 // NVIC_EnableIRQ(ADC_IRQn);

	  /* USER CODE BEGIN ADC1_Init 1 */

	  /* USER CODE END ADC1_Init 1 */
	  /** Common config
	  */
	  ADC_InitStruct.Resolution = LL_ADC_RESOLUTION_12B;
	  ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
	  ADC_InitStruct.SequencersScanMode = LL_ADC_SEQ_SCAN_ENABLE;
	  LL_ADC_Init(ADC1, &ADC_InitStruct);
	  ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
	  ADC_REG_InitStruct.SequencerLength = LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS;
	  ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
	  ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_CONTINUOUS;
	  ADC_REG_InitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_UNLIMITED;
	  LL_ADC_REG_Init(ADC1, &ADC_REG_InitStruct);
	  LL_ADC_REG_SetFlagEndOfConversion(ADC1, LL_ADC_REG_FLAG_EOC_SEQUENCE_CONV);
	  ADC_CommonInitStruct.CommonClock = LL_ADC_CLOCK_SYNC_PCLK_DIV2;
	  ADC_CommonInitStruct.Multimode = LL_ADC_MULTI_INDEPENDENT;
	  LL_ADC_CommonInit(__LL_ADC_COMMON_INSTANCE(ADC1), &ADC_CommonInitStruct);
	  /** Configure Regular Channel
	  */
	  LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_2);
	  LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_2, LL_ADC_SAMPLINGTIME_3CYCLES);
	  /** Configure Regular Channel
	  */
	  LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_2, LL_ADC_CHANNEL_3);
	  LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_3, LL_ADC_SAMPLINGTIME_3CYCLES);
	  /* USER CODE BEGIN ADC1_Init 2 */

	  /* USER CODE END ADC1_Init 2 */
}
void UHAL_ADC::initialize() {


  LL_ADC_InitTypeDef ADC_InitStruct = {0};
  LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = {0};
  LL_ADC_CommonInitTypeDef ADC_CommonInitStruct = {0};
  
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  /**ADC1 GPIO Configuration
  PA2   ------> ADC1_IN2
  PA3   ------> ADC1_IN3
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_2|LL_GPIO_PIN_3;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* ADC1 interrupt Init */


  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
   /** Common config
  */
  ADC_InitStruct.Resolution = LL_ADC_RESOLUTION_12B;
  ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
  ADC_InitStruct.SequencersScanMode = LL_ADC_SEQ_SCAN_ENABLE;
  LL_ADC_Init(ADC1, &ADC_InitStruct);
  ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
  ADC_REG_InitStruct.SequencerLength = LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS;
  ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
  ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_CONTINUOUS;
  ADC_REG_InitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_LIMITED;
  LL_ADC_REG_Init(ADC1, &ADC_REG_InitStruct);
  LL_ADC_REG_SetFlagEndOfConversion(ADC1, LL_ADC_REG_FLAG_EOC_UNITARY_CONV);
  ADC_CommonInitStruct.CommonClock = LL_ADC_CLOCK_SYNC_PCLK_DIV2;
  ADC_CommonInitStruct.Multimode = LL_ADC_MULTI_INDEPENDENT;
  LL_ADC_CommonInit(__LL_ADC_COMMON_INSTANCE(ADC1), &ADC_CommonInitStruct);
  /** Configure Regular Channel
  */
  LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_2);
  LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_2, LL_ADC_SAMPLINGTIME_3CYCLES);
  /** Configure Regular Channel
  */
  LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_2, LL_ADC_CHANNEL_3);
  LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_3, LL_ADC_SAMPLINGTIME_3CYCLES);
  /* USER CODE BEGIN ADC1_Init 2 */
    /*FOR THE DMA */
 //   UHAL_DMA2::DMA_ADC1::initialize();
  /* USER CODE END ADC1_Init 2 */
	flag_IT::EOC::enableInterrupt();
	flag_IT::OVR::enableInterrupt();
  NVIC_SetPriority(ADC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(ADC_IRQn);
}

void UHAL_ADC::disableInterrupt() {
    NVIC_DisableIRQ(thisIRQn);
}

UHAL_ADC::thisADC_T UHAL_ADC::fristTest(uintptr_t addressBuffer)
{
    initialize();
    UHAL_DMA2::DMA_ADC1::setBufferAddress(addressBuffer);
    disableInterrupt();
    on();
    startConversion();
    waitUntil(flag_IT::EOC::isSet());
    return readAdcConversionRegister();
}

void UHAL_ADC::DMAReInitForRecover() {
    
    
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
    LL_DMA_DisableStream(UHAL_DMA2::DMA_ADC1::thisInstance, UHAL_DMA2::DMA_ADC1::thisStream);
    waitUntil(!LL_DMA_IsEnabledStream(UHAL_DMA2::DMA_ADC1::thisInstance, UHAL_DMA2::DMA_ADC1::thisStream));
   

	  LL_DMA_SetChannelSelection(DMA2, LL_DMA_STREAM_0, LL_DMA_CHANNEL_0);

	  LL_DMA_SetDataTransferDirection(DMA2, LL_DMA_STREAM_0, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

	  LL_DMA_SetStreamPriorityLevel(DMA2, LL_DMA_STREAM_0, LL_DMA_PRIORITY_VERYHIGH);

	  LL_DMA_SetMode(DMA2, LL_DMA_STREAM_0, LL_DMA_MODE_CIRCULAR);

	  LL_DMA_SetPeriphIncMode(DMA2, LL_DMA_STREAM_0, LL_DMA_PERIPH_NOINCREMENT);

	  LL_DMA_SetMemoryIncMode(DMA2, LL_DMA_STREAM_0, LL_DMA_MEMORY_INCREMENT);

	  LL_DMA_SetPeriphSize(DMA2, LL_DMA_STREAM_0, LL_DMA_PDATAALIGN_HALFWORD);

	  LL_DMA_SetMemorySize(DMA2, LL_DMA_STREAM_0, LL_DMA_MDATAALIGN_HALFWORD);

	  LL_DMA_EnableFifoMode(DMA2, LL_DMA_STREAM_0);

	  LL_DMA_SetFIFOThreshold(DMA2, LL_DMA_STREAM_0, LL_DMA_FIFOTHRESHOLD_1_4);

	  LL_DMA_SetMemoryBurstxfer(DMA2, LL_DMA_STREAM_0, LL_DMA_MBURST_SINGLE);

	 LL_DMA_SetPeriphBurstxfer(DMA2, LL_DMA_STREAM_0, LL_DMA_PBURST_SINGLE);



}


