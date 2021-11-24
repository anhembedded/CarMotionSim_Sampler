/*
 * uhal_stm32f407_platform.h
 *
 *  Created on: Nov 6, 2021
 *      Author: hoang
 */

#ifndef INC_UFL_STM32F407_PLATFORM_HPP_
#define INC_UFL_STM32F407_PLATFORM_HPP_

#include "Arduino.hpp"
#include "main_cpp.hpp"



class uhal_stm32f407_platform: public Arduino
        {
private:
    const decltype(GPIOC)  arduino_port = GPIOC;
public:
     void pinMode(uint16_t pin, uint16_t mode) final;

     void digitalWrite(uint16_t pin, uint16_t val) final;

     int digitalRead(uint16_t pin) final;

     unsigned long millis() final;

     unsigned long micros() final;

     void delay(unsigned long ms) final;

     void delayMicroseconds(unsigned int us) final;

};



#endif /* INC_UFL_STM32F407_PLATFORM_HPP_ */
