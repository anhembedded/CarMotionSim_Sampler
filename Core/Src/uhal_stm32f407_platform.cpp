/*
 * uhal_stm32f407_platform.cpp
 *
 *  Created on: Nov 6, 2021
 *      Author: Tran Hoang Anh
 */

#include "../USER_API/UHAL/uhal_stm32f407_platform.hpp"



void uhal_stm32f407_platform::pinMode(uint16_t pin, uint16_t mode) {
    // GPIO pin configuring will be taken by another function.
    // do not need to implement this method
    __NOP(); // ASM, No operation - do not thing
}

void uhal_stm32f407_platform::digitalWrite(uint16_t pin, uint16_t val) {

    if(val == HIGH)
    {
        LL_GPIO_SetOutputPin(this->arduino_port, pin);
    } else
    {
        LL_GPIO_ResetOutputPin(this->arduino_port, pin);
    }
}

[[deprecated("because I not implement")]] int uhal_stm32f407_platform::digitalRead(uint16_t pin) {
    return 0;
}

[[deprecated("because I not implement")]] unsigned long uhal_stm32f407_platform::millis() {

    return 0;
}

[[deprecated("because I not implement")]] unsigned long uhal_stm32f407_platform::micros() {
    return 0;
}

void uhal_stm32f407_platform::delay(unsigned long ms) {
    LL_mDelay(ms);
}

void uhal_stm32f407_platform::delayMicroseconds(unsigned int  us) {

	__NOP();
}

