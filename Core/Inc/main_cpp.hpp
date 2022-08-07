/**
 * @file Serial examinating.ino
 *
 * @brief The frist program for examinating Serial protocol.
 *          
 * @author Tran Hoang Anh
 * Contact: Zalo or phones, 0965062996
 *
 */

#ifndef __MAIN_CPP_H__
#define __MAIN_CPP_H__
#include "main.h"
#include "cstddef"
#include "uhal_systemConfig.hpp"

enum class debug_T
{
    failed = 0,
    ok = 1,
    debugOn,
    debugOff

};


#define DEBUG_MODE 1
constexpr auto systemDebug = debug_T::debugOff;


#define __SFI __STATIC_FORCEINLINE
#define UN_WAIT_UNTIL(condition) while (!(condition))
#define READ_BIT_MASK(data, pos, mask) ((data >> pos) & (mask))
#define waitUntil UN_WAIT_UNTIL
#define MASK(x) (0b01 << (x))

/**
* \class UHAL_ERROR
* \brief For user hardware abstract layer asserting

*/enum class UHAL_ERROR
{
    ERROR,
    DEPRECATED,
    UHAL_OK

};


#endif // __MAIN_CPP_H__
