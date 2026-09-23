// An algorithm that passes a number through multiple transformation stages.
// These stages are the program's hot code.

#include "algorithm.hpp"

#include <bit>
#include <cstdint>

// Defines one stage of the algorithm as a separate function that can be
// positioned independently in the binary.
//
// ID identifies its position in the sequence and gives the stage a unique
// calculation.
#define DEFINE_STAGE(ID)                                                   \
    [[gnu::noinline, gnu::aligned(64), gnu::section(".text.layout." #ID)]] \
    std::uint64_t stage_##ID(std::uint64_t value)                          \
    {                                                                      \
        return std::rotl(value ^ 0x##ID, 1) + 0x##ID;                      \
    }

extern "C" {
DEFINE_STAGE(00)
DEFINE_STAGE(01)
DEFINE_STAGE(02)
DEFINE_STAGE(03)
DEFINE_STAGE(04)
DEFINE_STAGE(05)
DEFINE_STAGE(06)
DEFINE_STAGE(07)
DEFINE_STAGE(08)
DEFINE_STAGE(09)
DEFINE_STAGE(10)
DEFINE_STAGE(11)
DEFINE_STAGE(12)
DEFINE_STAGE(13)
DEFINE_STAGE(14)
DEFINE_STAGE(15)
DEFINE_STAGE(16)
DEFINE_STAGE(17)
DEFINE_STAGE(18)
DEFINE_STAGE(19)
DEFINE_STAGE(20)
DEFINE_STAGE(21)
DEFINE_STAGE(22)
DEFINE_STAGE(23)
DEFINE_STAGE(24)
DEFINE_STAGE(25)
DEFINE_STAGE(26)
DEFINE_STAGE(27)
DEFINE_STAGE(28)
DEFINE_STAGE(29)
DEFINE_STAGE(30)
DEFINE_STAGE(31)
}

std::uint64_t run_algorithm(std::uint64_t iterations)
{
    std::uint64_t state = 0x1234;

    while (iterations-- != 0) {
        state = stage_00(state);
        state = stage_01(state);
        state = stage_02(state);
        state = stage_03(state);
        state = stage_04(state);
        state = stage_05(state);
        state = stage_06(state);
        state = stage_07(state);
        state = stage_08(state);
        state = stage_09(state);
        state = stage_10(state);
        state = stage_11(state);
        state = stage_12(state);
        state = stage_13(state);
        state = stage_14(state);
        state = stage_15(state);
        state = stage_16(state);
        state = stage_17(state);
        state = stage_18(state);
        state = stage_19(state);
        state = stage_20(state);
        state = stage_21(state);
        state = stage_22(state);
        state = stage_23(state);
        state = stage_24(state);
        state = stage_25(state);
        state = stage_26(state);
        state = stage_27(state);
        state = stage_28(state);
        state = stage_29(state);
        state = stage_30(state);
        state = stage_31(state);
    }
    return state;
}
