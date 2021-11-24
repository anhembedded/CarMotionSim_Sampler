#ifndef __SIMTOOLS_H__
#define __SIMTOOLS_H__

#include "main.h"

namespace simTools
{
    typedef  uint8_t SIMTOOL_SERIAL_DATA_Type_T;
    enum serialBaudRate
    {
        _9600 = 9600,
        _14400 = 14400,
        _19200 = 19200,
        _28800 = 28800,
        _31250 = 31250,
        _38400 = 38400,
        _57600 = 57600,
        _115200 = 115200,
        _230400 = 230400,
        _250000 = 250000,
        _460800 = 460800,
        _500000 = 500000,
        _921600 = 921600
    };
};

using serialData_T = simTools::SIMTOOL_SERIAL_DATA_Type_T;

#endif // __SIMTOOLS_H__