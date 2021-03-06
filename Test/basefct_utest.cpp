//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------
#include <base/type.h>
#include <gtest/gtest.h>

using namespace optim;

TEST(optimbase, clamp) {
    EXPECT_EQ(clamp(static_cast<s64>(0), static_cast<s64>(-1), static_cast<s64>(1)), 0);
    EXPECT_EQ(clamp(static_cast<s64>(-4), static_cast<s64>(-1), static_cast<s64>(1)), -1);
    EXPECT_EQ(clamp(static_cast<s64>(4), static_cast<s64>(-1), static_cast<s64>(1)), 1);
    EXPECT_FLOAT_EQ(clamp(0.0F, -1.0F, 1.0F), 0.0F);
    EXPECT_FLOAT_EQ(clamp(-4.0F, -1.0F, 1.0F), -1.0F);
    EXPECT_FLOAT_EQ(clamp(4.0F, -1.0F, 1.0F), 1.0F);
    EXPECT_DOUBLE_EQ(clamp(0.0, -1.0, 1.0), 0.0);
    EXPECT_DOUBLE_EQ(clamp(-4.0, -1.0, 1.0), -1.0);
    EXPECT_DOUBLE_EQ(clamp(4.0, -1.0, 1.0), 1.0);

    EXPECT_EQ(clamp8(4), 4);
    EXPECT_EQ(clamp8(-400), -128);
    EXPECT_EQ(clamp8(400), 127);
}

TEST(optimbase, sign) {
    EXPECT_EQ(sign(static_cast<s64>(0)), 0);
    EXPECT_EQ(sign(static_cast<s64>(-1)), -1);
    EXPECT_EQ(sign(static_cast<s64>(1L)), 1);
    EXPECT_FLOAT_EQ(sign(0.0F), 0.0F);
    EXPECT_FLOAT_EQ(sign(-1.0F), -1.0F);
    EXPECT_FLOAT_EQ(sign(1.0F), 1.0F);
    EXPECT_DOUBLE_EQ(sign(0.0), 0.0);
    EXPECT_DOUBLE_EQ(sign(-1.0), -1.0);
    EXPECT_DOUBLE_EQ(sign(1.0), 1.0);
}

TEST(optimbase, abs) {
    EXPECT_EQ(optim::abs(static_cast<s64>(-1)), 1);
    EXPECT_EQ(optim::abs(static_cast<s64>(1)), 1);
    EXPECT_FLOAT_EQ(optim::abs(-1.0F), 1.0F);
    EXPECT_FLOAT_EQ(optim::abs(1.0F), 1.0F);
    EXPECT_DOUBLE_EQ(optim::abs(-1.0), 1.0);
    EXPECT_DOUBLE_EQ(optim::abs(1.0), 1.0);
}

TEST(optimbase, min) {
    EXPECT_EQ(min(static_cast<u8>(0), static_cast<u8>(1)), 0U);
    EXPECT_EQ(min(static_cast<u8>(1), static_cast<u8>(0)), 0U);
    EXPECT_EQ(min(static_cast<u16>(0), static_cast<u16>(1)), 0U);
    EXPECT_EQ(min(static_cast<u16>(1), static_cast<u16>(0)), 0U);
    EXPECT_EQ(min(static_cast<u32>(0), static_cast<u32>(1)), 0U);
    EXPECT_EQ(min(static_cast<u32>(1), static_cast<u32>(0)), 0U);
    EXPECT_EQ(min(static_cast<u64>(0), static_cast<u64>(1)), 0U);
    EXPECT_EQ(min(static_cast<u64>(1), static_cast<u64>(0)), 0U);
    EXPECT_EQ(min(static_cast<s32>(-1), static_cast<s32>(1)), -1);
    EXPECT_EQ(min(static_cast<s32>(1), static_cast<s32>(-1)), -1);
    EXPECT_EQ(min(static_cast<s64>(-1), static_cast<s64>(1)), -1);
    EXPECT_EQ(min(static_cast<s64>(1), static_cast<s64>(-1)), -1);
    EXPECT_FLOAT_EQ(min(-1.0F, 1.0F), -1.0F);
    EXPECT_FLOAT_EQ(min(1.0F, -1.0F), -1.0F);
    EXPECT_DOUBLE_EQ(min(-1.0, 1.0), -1.0);
    EXPECT_DOUBLE_EQ(min(1.0, -1.0), -1.0);
}

TEST(optimbase, max) {
    EXPECT_EQ(max(static_cast<u8>(0), static_cast<u8>(1)), 1U);
    EXPECT_EQ(max(static_cast<u8>(1), static_cast<u8>(0)), 1U);
    EXPECT_EQ(max(static_cast<u16>(0), static_cast<u16>(1)), 1U);
    EXPECT_EQ(max(static_cast<u16>(1), static_cast<u16>(0)), 1U);
    EXPECT_EQ(max(static_cast<u32>(0), static_cast<u32>(1)), 1U);
    EXPECT_EQ(max(static_cast<u32>(1), static_cast<u32>(0)), 1U);
    EXPECT_EQ(max(static_cast<u64>(0), static_cast<u64>(1)), 1U);
    EXPECT_EQ(max(static_cast<u64>(1), static_cast<u64>(0)), 1U);
    EXPECT_EQ(max(static_cast<s32>(-1), static_cast<s32>(1)), 1);
    EXPECT_EQ(max(static_cast<s32>(1), static_cast<s32>(-1)), 1);
    EXPECT_EQ(max(static_cast<s64>(-1), static_cast<s64>(1)), 1);
    EXPECT_EQ(max(static_cast<s64>(1), static_cast<s64>(-1)), 1);
    EXPECT_FLOAT_EQ(max(-1.0F, 1.0F), 1.0F);
    EXPECT_FLOAT_EQ(max(1.0F, -1.0F), 1.0F);
    EXPECT_DOUBLE_EQ(max(-1.0, 1.0), 1.0);
    EXPECT_DOUBLE_EQ(max(1.0, -1.0), 1.0);
}

TEST(optimbase, isfNull) {
    EXPECT_TRUE(isfNull(0.0F));
    EXPECT_TRUE(isfNull(0.00000001F));
    EXPECT_FALSE(isfNull(1.0F));
    EXPECT_FALSE(isfNull(-1.0F));
    EXPECT_TRUE(isfNull(0.0));
    EXPECT_TRUE(isfNull(0.00000001));
    EXPECT_FALSE(isfNull(1.0));
    EXPECT_FALSE(isfNull(-1.0));

    EXPECT_TRUE(isfEqual(1.0F, 1.0F));
    EXPECT_TRUE(isfEqual(0.1F, 0.10000001F));
    EXPECT_FALSE(isfEqual(1.0F, 0.01F));
    EXPECT_FALSE(isfEqual(-1.0F, 0.01F));
    EXPECT_TRUE(isfEqual(1.0, 1.0));
    EXPECT_TRUE(isfEqual(0.1, 0.100000001));
    EXPECT_FALSE(isfEqual(1.0, 0.01));
    EXPECT_FALSE(isfEqual(-1.0, 0.01));
}

#include <array>
TEST(optimbase, BitOperations) {
    std::array<bool, 8> bb = {true, false, false, false, true, false, false, true};
    u8 field = 145;
    bitSet(field, 3);
    bb[3] = true;
    bitClear(field, 7);
    bb[7] = false;
    bitToggle(field, 4);
    bb[4] = false;
    bitToggle(field, 5);
    bb[5] = true;
    bitDefine(field, 1, true);
    bb[1] = true;
    for (u8 i = 0; i < 8; ++i)
        EXPECT_EQ(bitGet(field, i), bb[i]);
    std::array<bool, 64> bb64 = {true, false, false, false, true, false, false, true, false, false, false, false, false, false, false, false,
                                 false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
                                 false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
                                 false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
    u64 field64 = 145;
    bitSet(field64, 43);
    bb64[43] = true;
    bitClear(field64, 7);
    bb64[7] = false;
    bitToggle(field64, 4);
    bb64[4] = false;
    bitToggle(field64, 55);
    bb64[55] = true;
    bitDefine(field64, 61, true);
    bb64[61] = true;
    for (u8 i = 0; i < 64; ++i)
        EXPECT_EQ(bitGet(field64, i), bb64[i]);
}
