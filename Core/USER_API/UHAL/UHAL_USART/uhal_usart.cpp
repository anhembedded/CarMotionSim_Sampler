//
// Created by hoang on 11/23/2021.
//

#include "uhal_usart.hpp"
#include "cstring"


void UHAL_USART1::initialize(uint32_t baudRate) {


    // DMA clock


    /* USER CODE BEGIN USART1_Init 0 */

    /* USER CODE END USART1_Init 0 */

    LL_USART_InitTypeDef USART_InitStruct = {0};

    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* Peripheral clock enable */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
    /**USART1 GPIO Configuration
    PB6   ------> USART1_TX
    PB7   ------> USART1_RX
    */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_6 | LL_GPIO_PIN_7;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);




    LL_DMA_SetChannelSelection(DMA2, LL_DMA_STREAM_5, LL_DMA_CHANNEL_4);

    LL_DMA_SetDataTransferDirection(DMA2, LL_DMA_STREAM_5, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

    LL_DMA_SetStreamPriorityLevel(DMA2, LL_DMA_STREAM_5, LL_DMA_PRIORITY_VERYHIGH);

    LL_DMA_SetMode(DMA2, LL_DMA_STREAM_5, LL_DMA_MODE_NORMAL);

    LL_DMA_SetPeriphIncMode(DMA2, LL_DMA_STREAM_5, LL_DMA_PERIPH_NOINCREMENT);

    LL_DMA_SetMemoryIncMode(DMA2, LL_DMA_STREAM_5, LL_DMA_MEMORY_INCREMENT);

    LL_DMA_SetPeriphSize(DMA2, LL_DMA_STREAM_5, LL_DMA_PDATAALIGN_BYTE);

    LL_DMA_SetMemorySize(DMA2, LL_DMA_STREAM_5, LL_DMA_MDATAALIGN_BYTE);

    LL_DMA_EnableFifoMode(DMA2, LL_DMA_STREAM_5);

    LL_DMA_SetFIFOThreshold(DMA2, LL_DMA_STREAM_5, LL_DMA_FIFOTHRESHOLD_1_4);

   LL_DMA_SetMemoryBurstxfer(DMA2, LL_DMA_STREAM_5, LL_DMA_MBURST_SINGLE);

    LL_DMA_SetPeriphBurstxfer(DMA2, LL_DMA_STREAM_5, LL_DMA_PBURST_SINGLE);

    LL_USART_EnableDMAReq_RX(thisInstance);

    NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
    NVIC_EnableIRQ(USART1_IRQn);

    UHAL_DMA2::DMA_USART1::flag_IT::FEIF::enableInterrupt();
    UHAL_DMA2::DMA_USART1::flag_IT::DMEIF::enableInterrupt();
    UHAL_DMA2::DMA_USART1::flag_IT::HTIF::enableInterrupt();
    UHAL_DMA2::DMA_USART1::flag_IT::TCIF::enableInterrupt();
    UHAL_DMA2::DMA_USART1::flag_IT::TEIF::enableInterrupt();



    USART_InitStruct.BaudRate = baudRate;
    USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_9B;
    USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
    USART_InitStruct.Parity = LL_USART_PARITY_EVEN;
    USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
    USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
    LL_USART_Init(thisInstance, &USART_InitStruct);
    LL_USART_ConfigAsyncMode(thisInstance);

    UHAL_DMA2::DMA_USART1::initialize();
 //   LL_USART_Enable(USART6);

}


void UHAL_USART1::send(const UHAL_USART1::data_T data) {
    using namespace UHAL_USART1::flag_IT;
    enable();
    enableTransmitter();
            waitUntil(TXE::isSet());
    transmitData(data);
            waitUntil(TC::isSet());

}


void UHAL_USART1::send(uint8_t *str) {
    using namespace UHAL_USART1::flag_IT;
    enable();
    enableTransmitter();
            waitUntil(TXE::isSet());

}


void UHAL_USART1::send(const std::string &str) {
    using namespace UHAL_USART1::flag_IT;
    enable();
    enableTransmitter();
            waitUntil(TXE::isSet());
    for (decltype(static_cast<std::string>(str))::value_type eachCharOfStr: str) {
        transmitData(eachCharOfStr);
                waitUntil(TC::isSet());
    }

}


void UHAL_USART1::send(const char *str) {
    using namespace UHAL_USART1::flag_IT;
    enable();
    enableTransmitter();
            waitUntil(TXE::isSet());
    auto strLength = strlen(str);
    for (auto i = 0; i < strLength; i++) {
        transmitData(str[i]);
                waitUntil(TC::isSet());
    }

}


void UHAL_USART1::interruptTransInit() {
    using namespace UHAL_USART1::flag_IT;
    TXE::enableIT();
    enable();
    enableTransmitter();
    enableInterruptHandle();
}

void UHAL_USART1::interruptReceiveInit() {

    if constexpr(systemDebug == debug_T::debugOn) {
        auto posAssert = isPeripheralClKEnabled();
        assert_param(posAssert);
    }
    using namespace UHAL_USART1::flag_IT;
    FE::enableIT();
    ORE::enableIT();
    PE::enableIT();
    IDLE::enableIT();
    NF::enableIT();
    enableReceiver();
    enableInterruptHandle(0,0);
}

void UHAL_USART1::developing::fristRun(uintptr_t addressBuffer, uint16_t numberOfData) {

    initialize(115200);
    enableTransmitter();
   enableReceiver();
   UHAL_DMA2::DMA_USART1::setPeripheralADDress(reinterpret_cast<uintptr_t>(&thisInstance->DR));
   UHAL_DMA2::DMA_USART1::setBufferAddress(addressBuffer);
    UHAL_DMA2::DMA_USART1::setNumberOfDataTransfer(numberOfData);
   UHAL_DMA2::DMA_USART1::enable();
    interruptReceiveInit();
    enable();
}

void UHAL_USART1::enableGPIOClock() {
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
}

void UHAL_USART1::enablePerihClock() {
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART6);
}


void UHAL_USART1::enable() {

    if constexpr (systemDebug == debug_T::debugOn) {
        auto posAssert = LL_APB2_GRP1_IsEnabledClock(
                LL_APB2_GRP1_PERIPH_USART6);
        assert_param(posAssert);
    }
    LL_USART_Enable(thisInstance);
}

void UHAL_USART1::enableTransmitter() {
    LL_USART_EnableDirectionTx(thisInstance);
}

void UHAL_USART1::transmitData(const data_T data) {
    LL_USART_TransmitData8(thisInstance, data);
}

void UHAL_USART1::disable() {
    LL_USART_Disable(thisInstance);
}

void UHAL_USART1::enableInterruptHandle(const uint8_t PreemptPriority,
                                        const uint8_t SubPriority) {
    NVIC_SetPriority(USART1_IRQn,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(), PreemptPriority,
                                         SubPriority));
    NVIC_EnableIRQ(USART1_IRQn);
}

void UHAL_USART1::enableReceiver()
{
    LL_USART_EnableDirectionRx(thisInstance);
}

UHAL_USART1::data_T UHAL_USART1::receivedData()
{
    return LL_USART_ReceiveData9(thisInstance);
}
