//
// Created by hoang on 11/30/2021.
//

#ifndef CARMOTIONSIM_SAMPLER_UAPP_SIMTOOL_HPP
#define CARMOTIONSIM_SAMPLER_UAPP_SIMTOOL_HPP
#include "string"
#include "array"
#include "algorithm"
#include "main_cpp.hpp"

namespace UAPP_SIMTOOL
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

    void streamManipulator(std::array<uint8_t, 10> &data, uint8_t &surge, uint8_t &sway, uint8_t &traction);
}
using serialData_T = UAPP_SIMTOOL::SIMTOOL_SERIAL_DATA_Type_T;




#endif //CARMOTIONSIM_SAMPLER_UAPP_SIMTOOL_HPP
