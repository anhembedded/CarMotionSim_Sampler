#ifndef __UFL_USART_H__
#define __UFL_USART_H__

#include "main_cpp.hpp"
#include "../UHAL_DMA/UHAL_DMA.hpp"
#include "string"

namespace UHAL_USART6
{

	const decltype(USART6) thisInstance = USART6;
	const auto thisIRQn = USART6_IRQn;
	typedef uint8_t data_T;

	void initialize(uint32_t baudRate = 115200);

	 void enable();
	 void disable();


	 void enableTransmitter();
	 void enableReceiver();

	 void transmitData(const data_T data);
	 data_T receivedData();

	 void enableGPIOClock();
	 void enablePerihClock();

	 void  enableInterruptHandle(const uint8_t PreemptPriority = 0,
									 const uint8_t SubPriority = 0);

	

	void interruptTransInit();
	void interruptReceiveInit();

	void send(uint8_t *str);
	void send(const uint8_t data);
	void send(const char *str);
	void send(const std::string &str);
	data_T get();

	__SFI auto isPeripheralClKEnabled()
	{
		return LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_USART6);
	}
	/// Flag and Interrupt packets
	inline namespace flag_IT
	{
		/*Note flag_IT Abstraction layer include 4 routines
		 isSet, clear, enableIT, clearPendingBit.
		 */
		namespace TC /// Transmission Complete Flag
		{
			__SFI auto isSet();
			__SFI auto clear();
			__SFI auto enableIT();
			[[deprecated("this flag no pending")]] __SFI auto clearPendingBit();
		}
		namespace TXE /// Transmit Data Register Empty
		{
			__SFI auto isSet();
			__SFI auto clear();
			__SFI auto enableIT();
			[[deprecated("this flag no pending")]] __SFI auto clearPendingBit();
		}
		namespace IDLE /// Idle Line Detected
		{
			__SFI auto isSet()
			{
				return LL_USART_IsActiveFlag_IDLE(thisInstance);
			}
			__SFI auto clear()
			{
				if constexpr (systemDebug == debug_T::debugOn)
				{
					auto posAssert = isSet();
					assert_param(posAssert);
				}
				LL_USART_ClearFlag_IDLE(thisInstance);
			}
			__SFI auto enableIT()
			{
				LL_USART_EnableIT_IDLE(thisInstance);
			}
			[[deprecated("this flag no pending")]] __SFI auto clearPendingBit()
			{
			}
		}
		namespace RXNE /// Received data ready to be read
		{
			__SFI auto isSet()
			{
				return LL_USART_IsActiveFlag_RXNE(thisInstance);
			}
			__SFI auto clear()
			{
				if constexpr (systemDebug == debug_T::debugOn)
				{
					auto posAssert = isSet();
					assert_param(posAssert);
				}
				LL_USART_ClearFlag_RXNE(thisInstance);
			}
			__SFI auto enableIT()
			{
				LL_USART_EnableIT_RXNE(thisInstance);
			}
			[[deprecated("this flag no pending")]] __SFI auto clearPendingBit()
			{
			}
		}
		namespace PE /// Parity error detected
		{
			__SFI auto isSet()
			{
				return LL_USART_IsActiveFlag_PE(thisInstance);
			}
			__SFI auto clear()
			{
				if constexpr (systemDebug == debug_T::debugOn)
				{
					auto posAssert = isSet();
					assert_param(posAssert);
				}
				LL_USART_ClearFlag_PE(thisInstance);
			}
			__SFI auto enableIT()
			{
				LL_USART_EnableIT_PE(thisInstance);
			}
			[[deprecated("this flag no pending")]] __SFI auto clearPendingBit()
			{
			}
		}
		namespace NF /// Noise flag
		{
			__SFI auto isSet()
			{
				return LL_USART_IsActiveFlag_NE(thisInstance);
			}
			__SFI auto clear()
			{
				if constexpr (systemDebug == debug_T::debugOn)
				{
					auto posAssert = isSet();
					assert_param(posAssert);
				}
				LL_USART_ClearFlag_NE(thisInstance);
			}
			__SFI auto enableIT()
			{
				LL_USART_EnableIT_ERROR(thisInstance);
			}
			[[deprecated("this flag no pending")]] __SFI auto clearPendingBit()
			{
			}
		}
		namespace FE /// Framing error
		{
			__SFI auto isSet()
			{
				return LL_USART_IsActiveFlag_FE(thisInstance);
			}
			__SFI auto clear()
			{
				if constexpr (systemDebug == debug_T::debugOn)
				{
					auto posAssert = isSet();
					assert_param(posAssert);
				}
				LL_USART_ClearFlag_FE(thisInstance);
			}
			__SFI auto enableIT()
			{
				LL_USART_EnableIT_ERROR(thisInstance);
			}
			[[deprecated("this flag no pending")]] __SFI auto clearPendingBit()
			{
			}
		}
		namespace ORE /// Overrun error detected
		{
			__SFI auto isSet()
			{
				return LL_USART_IsActiveFlag_ORE(thisInstance);
			}
			__SFI auto clear()
			{
				if constexpr (systemDebug == debug_T::debugOn)
				{
					auto posAssert = isSet();
					assert_param(posAssert);
				}
				LL_USART_ClearFlag_ORE(thisInstance);
			}
			__SFI auto enableIT()
			{
				LL_USART_EnableIT_RXNE(thisInstance);
			}
			[[deprecated("this flag no pending")]] __SFI auto clearPendingBit()
			{
			}
		}
	}


	namespace developing
	{
		void fristRun(uintptr_t addressBuffer, uint16_t numberOfData);
	}
}







__STATIC_FORCEINLINE auto UHAL_USART6::flag_IT::TC::isSet()
{
	return LL_USART_IsActiveFlag_TC(thisInstance);
}

__SFI auto UHAL_USART6::flag_IT::TC::clear()
{
	if constexpr (systemDebug == debug_T::debugOn)
	{
		auto posAssert = isSet();
		assert_param(posAssert);
	}
	LL_USART_ClearFlag_TC(thisInstance);
}

__SFI auto UHAL_USART6::flag_IT::TC::enableIT()
{
	LL_USART_EnableIT_TC(thisInstance);
}

__SFI auto UHAL_USART6::flag_IT::TC::clearPendingBit()
{
	return UHAL_ERROR::DEPRECATED;
}
auto UHAL_USART6::flag_IT::TXE::isSet()
{
	return LL_USART_IsActiveFlag_TXE(thisInstance);
}

auto UHAL_USART6::flag_IT::TXE::enableIT()
{
	LL_USART_EnableIT_TXE(thisInstance);
}

auto UHAL_USART6::flag_IT::TXE::clearPendingBit()
{
	return UHAL_ERROR::DEPRECATED;
}

auto UHAL_USART6::flag_IT::TXE::clear()
{
	return UHAL_ERROR::DEPRECATED;
}


#endif // __UFL_USART_H__
