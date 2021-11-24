//
// Created by hoang on 11/6/2021.
//

#ifndef LCD_ARDUINO_HPP
#define LCD_ARDUINO_HPP

#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdint>

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3



#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

#define lowByte(w) ((uint16_t) ((w) & 0xff))
#define highByte(w) ((uint16_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitToggle(value, bit) ((value) ^= (1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? bitSet(value, bit) : bitClear(value, bit))

typedef unsigned int word;

#define bit(b) (1UL << (b))

typedef bool boolean;
typedef uint16_t byte;




class Arduino
        {
public:
    virtual void pinMode(uint16_t pin, uint16_t mode) = 0;

    virtual void digitalWrite(uint16_t pin, uint16_t val) = 0;

    virtual int digitalRead(uint16_t pin)= 0;

    virtual unsigned long millis()= 0;

    virtual unsigned long micros()=0;

    virtual void delay(unsigned long ms)=0;

    virtual void delayMicroseconds(unsigned int us)=0;

};


#endif //LCD_ARDUINO_HPP
