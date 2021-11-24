#ifndef __UFL_CLK_H__
#define __UFL_CLK_H__
#include "main_cpp.hpp"


namespace clk
{
    constexpr   auto megaHZ = 1000000 ;
    constexpr   auto SYSCLK = 168 * megaHZ;
    constexpr   auto HCLK   = 168 * megaHZ;
    constexpr   auto APB1   = 42 * megaHZ;
    constexpr   auto APB1Timer  = 84 * megaHZ;
    constexpr   auto APB2       = 84 * megaHZ;
    constexpr   auto APB2Timer  = 168*megaHZ;

}


#endif // __UFL_CLK_H__
