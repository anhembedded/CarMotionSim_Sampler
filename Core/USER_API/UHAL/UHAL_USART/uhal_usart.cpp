//
// Created by hoang on 11/23/2021.
//

#include "uhal_usart.hpp"
#include "cstring"




void  UHAL_USART6::send(const UHAL_USART6::data_T data)
{
    using namespace UHAL_USART6::flag_IT;
    enable();
    enableTransmitter();
    waitUntil(TXE::isSet());
    transmitData(data);
    waitUntil(TC::isSet());

}


void UHAL_USART6::send (uint8_t * str)
{
	 using namespace UHAL_USART6::flag_IT;
	  enable();
	  enableTransmitter();
	  waitUntil(TXE::isSet());

}


void UHAL_USART6::send(const std::string& str)
{
  using namespace UHAL_USART6::flag_IT;
  enable();
  enableTransmitter();
  waitUntil(TXE::isSet());
    for (decltype(static_cast<std::string>(str))::value_type  eachCharOfStr : str)
  {
    transmitData(eachCharOfStr);
    waitUntil(TC::isSet());
  }

}


void UHAL_USART6::send(const char* str)
{
    using namespace UHAL_USART6::flag_IT;
    enable();
    enableTransmitter();
    waitUntil(TXE::isSet());
    auto strLength = strlen(str);
    for(auto i = 0; i<strLength; i ++ )
    {
        transmitData(str[i]);
        waitUntil(TC::isSet());
    }

}


 void  UHAL_USART6::interruptTransInit()
{
    using namespace UHAL_USART6::flag_IT;
    TXE::enableIT();
    enable();
    enableTransmitter();
    enableInterruptHandle();
}

void UHAL_USART6::interruptReceiveInit()
{

    if constexpr(systemDebug == debug_T::debugOn)
    {
        auto posAssert =  isPeripheralClKEnabled();
        assert_param(posAssert);
    }
    using namespace UHAL_USART6::flag_IT;
    RXNE::enableIT();
   // PE::enableIT();
    enable();
    enableReceiver();
    enableInterruptHandle();

}
