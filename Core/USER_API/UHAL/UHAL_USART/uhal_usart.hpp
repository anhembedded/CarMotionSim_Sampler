#ifndef __UFL_USART_H__
#define __UFL_USART_H__

#include "main_cpp.hpp"
#include "string"

namespace UHAL_USART6
{

	const decltype(USART6) thisInstance = USART6;
	const auto thisIRQn = USART6_IRQn;
	typedef uint8_t data_T;

	__SFI auto initialize();
	__SFI auto enable();
	__SFI auto disable();
	__SFI auto enableGPIOClock();
	__SFI auto enableTransmitter();
	__SFI auto enableReceiver();
	__SFI auto transmitData(const data_T data);
	__SFI data_T receivedData();
	__SFI auto enablePerihClock();
	__SFI auto enableInterruptHandle(const uint8_t PreemptPriority = 0,
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
}

__SFI auto UHAL_USART6::enableGPIOClock()
{
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
}

__SFI auto UHAL_USART6::enablePerihClock()
{
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART6);
}

__SFI auto UHAL_USART6::initialize()
{
	LL_USART_InitTypeDef USART_InitStruct = {0};
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* Peripheral clock enable */
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART6);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
	/**USART6 GPIO Configuration
	 PC6   ------> USART6_TX
	 PC7   ------> USART6_RX
	 */
	GPIO_InitStruct.Pin = LL_GPIO_PIN_6 | LL_GPIO_PIN_7;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_8;
	LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	USART_InitStruct.BaudRate = 115200;
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_9B;
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	USART_InitStruct.Parity = LL_USART_PARITY_EVEN;
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
	LL_USART_Init(USART6, &USART_InitStruct);
	LL_USART_ConfigAsyncMode(USART6);
}

__SFI auto UHAL_USART6::enable()
{

	if constexpr (systemDebug == debug_T::debugOn)
	{
		auto posAssert = LL_APB2_GRP1_IsEnabledClock(
			LL_APB2_GRP1_PERIPH_USART6);
		assert_param(posAssert);
	}
	LL_USART_Enable(thisInstance);
}

auto UHAL_USART6::enableTransmitter()
{
	LL_USART_EnableDirectionTx(thisInstance);
}

auto UHAL_USART6::transmitData(const data_T data)
{
	LL_USART_TransmitData8(thisInstance, data);
}

auto UHAL_USART6::disable()
{
	LL_USART_Disable(thisInstance);
}

auto UHAL_USART6::enableInterruptHandle(const uint8_t PreemptPriority,
										const uint8_t SubPriority)
{
	NVIC_SetPriority(USART6_IRQn,
					 NVIC_EncodePriority(NVIC_GetPriorityGrouping(), PreemptPriority,
										 SubPriority));
	NVIC_EnableIRQ(USART6_IRQn);
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

auto UHAL_USART6::enableReceiver()
{
	LL_USART_EnableDirectionRx(thisInstance);
}

UHAL_USART6::data_T UHAL_USART6::receivedData()
{
	return LL_USART_ReceiveData9(thisInstance);
}

#endif // __UFL_USART_H__
