//
// Created by hoang on 11/29/2021.
//

#ifndef CARMOTIONSIM_SAMPLER_UHAL_DMA_HPP
#define CARMOTIONSIM_SAMPLER_UHAL_DMA_HPP
#include "stm32f4xx_ll_dma.h"
#include "main_cpp.hpp"



namespace UHAL_DMA2 /// @brief for ADC1
{

   namespace DMA_ADC1
    {
       const decltype(DMA2) thisInstance = DMA2;
       constexpr auto  thisStream = LL_DMA_STREAM_0;
       constexpr auto thisChannel = LL_DMA_CHANNEL_0;
       constexpr auto thisIRQn = DMA2_Stream0_IRQn;
      
         void setBufferAddress(uintptr_t bufferAddress);
         void setPeripheralADDress(const uintptr_t address);
         void enable();
         void setNumberOfDataTransfer(uint16_t numb);
       void initialize();
       void initialize2();
       void enableInterrupt();
       void disableInterrupt();
       void enablePerihClock();
       void enableInterrupt();
       namespace flag_IT
       {
          namespace HTIF // Half-transfer reached
          {
            __SFI auto isSet() 
            {
               return LL_DMA_IsActiveFlag_HT0(thisInstance);
            }
            __SFI auto clear()
            {
               LL_DMA_ClearFlag_HT0(thisInstance);
            }         
            __SFI auto enableInterrupt()
            {
               LL_DMA_EnableIT_HT(thisInstance, thisStream);
            }
            __SFI auto isEnableInterrupt() ;
             [[deprecated("this flag no pending")]] __SFI auto clearPendingBit();
          }
            namespace TCIF // Transfer complete
          {
            __SFI auto isSet()
            {
               return LL_DMA_IsActiveFlag_TC0(thisInstance);
            }
            __SFI auto clear()  
            {
                LL_DMA_ClearFlag_TC0(thisInstance);
            }       
            __SFI auto enableInterrupt()
            {
                LL_DMA_EnableIT_TC(thisInstance, thisStream);
            }
            __SFI auto isEnableInterrupt() ;
             [[deprecated("this flag no pending")]] __SFI auto clearPendingBit();
          }
            namespace TEIF // Transfer error
          {
            __SFI auto isSet()
            {
               return LL_DMA_IsActiveFlag_TE0(thisInstance);
            }
            __SFI auto clear()  
            {
                LL_DMA_ClearFlag_TE0(thisInstance);
            }       
            __SFI auto enableInterrupt()
            {
                LL_DMA_EnableIT_TE(thisInstance, thisStream);
            }
            __SFI auto isEnableInterrupt() ;
             [[deprecated("this flag no pending")]] __SFI auto clearPendingBit();
          }
            namespace FEIF // FIFO overrun/underrun
          {
           __SFI auto isSet()
            {
               return LL_DMA_IsActiveFlag_FE0(thisInstance);
            }
            __SFI auto clear()  
            {
                LL_DMA_ClearFlag_FE0(thisInstance);
            }       
            __SFI auto enableInterrupt()
            {
                LL_DMA_EnableIT_FE(thisInstance, thisStream);
            }
            __SFI auto isEnableInterrupt() ;
             [[deprecated("this flag no pending")]] __SFI auto clearPendingBit();
          }
          namespace DMEIF // Direct mode error
          {
           
            __SFI auto isSet()
            {
               return LL_DMA_IsActiveFlag_DME0(thisInstance);
            }
            __SFI auto clear()  
            {
                LL_DMA_ClearFlag_DME0(thisInstance);
            }       
            __SFI auto enableInterrupt()
            {
                LL_DMA_EnableIT_DME(thisInstance, thisStream);
            }
            __SFI auto isEnableInterrupt() ;
             [[deprecated("this flag no pending")]] __SFI auto clearPendingBit();
          }
          
       }
      void firstRun();

    }
    namespace DMA_USART6
    {
       const decltype(DMA2) thisInstance = DMA2;
       constexpr auto  thisStream = LL_DMA_STREAM_1;
       constexpr auto thisChannel = LL_DMA_CHANNEL_5;
         constexpr auto thisIRQn = DMA2_Stream1_IRQn;
         
         void setBufferAddress(uintptr_t bufferAddress);
         void setPeripheralADDress(const uintptr_t address);
         void enable();
         void setNumberOfDataTransfer(uint16_t numb);
       void initialize();
       void initialize2();
       void enableInterrupt();
       void disableInterrupt();
       void enablePerihClock();
       void enableInterrupt();
       namespace flag_IT
       {
          namespace HTIF // Half-transfer reached
          {
            __SFI auto isSet() 
            {
               return LL_DMA_IsActiveFlag_HT0(thisInstance);
            }
            __SFI auto clear()
            {
               LL_DMA_ClearFlag_HT0(thisInstance);
            }         
            __SFI auto enableInterrupt()
            {
               LL_DMA_IsEnabledIT_HT(thisInstance, thisStream);
            }
            __SFI auto isEnableInterrupt() ;
             [[deprecated("this flag no pending")]] __SFI auto clearPendingBit();
          }
            namespace TCIF // Transfer complete
          {
            __SFI auto isSet()
            {
               return LL_DMA_IsActiveFlag_TC0(thisInstance);
            }
            __SFI auto clear()  
            {
                LL_DMA_ClearFlag_TC0(thisInstance);
            }       
            __SFI auto enableInterrupt()
            {
                LL_DMA_IsEnabledIT_TC(thisInstance, thisStream);
            }
            __SFI auto isEnableInterrupt() ;
             [[deprecated("this flag no pending")]] __SFI auto clearPendingBit();
          }
            namespace TEIF // Transfer error
          {
            __SFI auto isSet()
            {
               return LL_DMA_IsActiveFlag_TE0(thisInstance);
            }
            __SFI auto clear()  
            {
                LL_DMA_ClearFlag_TE0(thisInstance);
            }       
            __SFI auto enableInterrupt()
            {
                LL_DMA_IsEnabledIT_TE(thisInstance, thisStream);
            }
            __SFI auto isEnableInterrupt() ;
             [[deprecated("this flag no pending")]] __SFI auto clearPendingBit();
          }
            namespace FEIF // FIFO overrun/underrun
          {
           __SFI auto isSet()
            {
               return LL_DMA_IsActiveFlag_FE0(thisInstance);
            }
            __SFI auto clear()  
            {
                LL_DMA_ClearFlag_FE0(thisInstance);
            }       
            __SFI auto enableInterrupt()
            {
                LL_DMA_IsEnabledIT_FE(thisInstance, thisStream);
            }
            __SFI auto isEnableInterrupt() ;
             [[deprecated("this flag no pending")]] __SFI auto clearPendingBit();
          }
          namespace DMEIF // Direct mode error
          {
           
            __SFI auto isSet()
            {
               return LL_DMA_IsActiveFlag_DME0(thisInstance);
            }
            __SFI auto clear()  
            {
                LL_DMA_ClearFlag_DME0(thisInstance);
            }       
            __SFI auto enableInterrupt()
            {
                LL_DMA_IsEnabledIT_DME(thisInstance, thisStream);
            }
            __SFI auto isEnableInterrupt() ;
             [[deprecated("this flag no pending")]] __SFI auto clearPendingBit();
          }
          
       }
   
      void firstRun();
    }

}




#endif //CARMOTIONSIM_SAMPLER_UHAL_DMA_HPP
