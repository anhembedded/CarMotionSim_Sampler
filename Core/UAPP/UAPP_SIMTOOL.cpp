//
// Created by hoang on 11/30/2021.
//

#include "UAPP_SIMTOOL.hpp"

void UAPP_SIMTOOL::streamManipulator(std::array<uint8_t, 10> &data, uint8_t &surge, uint8_t &sway, uint8_t &traction)
{

    if constexpr(systemDebug == debug_T::debugOn)
    {
        std::string simtoolSteam = "[A<surge>[B<sway>[C<traction>";
    }
    constexpr auto nextByte = 1;
    constexpr auto startByte = '[';

    auto A_iter = std::find(data.begin(), data.end(), 'A');
    auto B_iter = std::find(data.begin(), data.end(), 'B');
    auto C_iter = std::find(data.begin(), data.end(), 'C');

    auto exam = [data](decltype(A_iter) praIter)
    {
        if ((praIter != data.end()) && (praIter != data.begin()))
        {
            return 1;
        }
        return 0;
    };

    if (exam(A_iter))
    {
        if (*(A_iter - nextByte) == startByte)
        {
            surge = *(A_iter + nextByte);
        }
    }
    if (exam(B_iter))
    {
        if (*(B_iter - nextByte) == startByte)
        {
            sway = *(B_iter + nextByte);
        }
    }
    if (exam(C_iter))
    {
        if (*(C_iter - nextByte) == startByte)
        {
            traction = *(C_iter + nextByte);
        }
    }
}
