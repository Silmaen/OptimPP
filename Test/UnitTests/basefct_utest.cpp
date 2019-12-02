#include <gtest/gtest.h>
#include <base/type.h>

using namespace optim;

TEST(optimbase, clamp)
{
    EXPECT_EQ(clamp(0, -1, 1), 0);
    EXPECT_EQ(clamp(-4, -1, 1), -1);
    EXPECT_EQ(clamp(4, -1, 1), 1);
    EXPECT_FLOAT_EQ(clamp((float)0.0, (float)-1.0, (float)1.0), (float)0.0);
    EXPECT_FLOAT_EQ(clamp((float)-4.0, (float)-1.0, (float)1.0), (float)-1.0);
    EXPECT_FLOAT_EQ(clamp((float)4.0, (float)-1.0, (float)1.0), (float)1.0);
    EXPECT_DOUBLE_EQ(clamp((double)0.0, (double)-1.0, (double)1.0), 0.0);
    EXPECT_DOUBLE_EQ(clamp((double)-4.0, (double)-1.0, (double)1.0), -1.0);
    EXPECT_DOUBLE_EQ(clamp((double)4.0, (double)-1.0, (double)1.0), 1.0);
}

TEST(optimbase, sign)
{
    EXPECT_EQ(sign(0), 0);
    EXPECT_EQ(sign(-1), -1);
    EXPECT_EQ(sign(1), 1);
    EXPECT_FLOAT_EQ(sign((float)0.0), (float)0.0);
    EXPECT_FLOAT_EQ(sign((float)-1.0), (float)-1.0);
    EXPECT_FLOAT_EQ(sign((float)1.0), (float)1.0);
    EXPECT_DOUBLE_EQ(sign((double)0.0), 0.0);
    EXPECT_DOUBLE_EQ(sign((double)-1.0), -1.0);
    EXPECT_DOUBLE_EQ(sign((double)1.0), 1.0);
}

TEST(optimbase, min)
{
    EXPECT_EQ(min((u8)0, (u8)1), 0u);
    EXPECT_EQ(min((u8)1, (u8)0), 0u);
    EXPECT_EQ(min((u16)0, (u16)1), 0u);
    EXPECT_EQ(min((u16)1, (u16)0), 0u);
    EXPECT_EQ(min((u32)0, (u32)1), 0u);
    EXPECT_EQ(min((u32)1, (u32)0), 0u);
    EXPECT_EQ(min((s32)-1, (s32)1), -1);
    EXPECT_EQ(min((s32)1, (s32)-1), -1);
    EXPECT_FLOAT_EQ(min((float)-1.0, (float)1.0), -1.0);
    EXPECT_FLOAT_EQ(min((float)1.0, (float)-1.0), -1.0);
    EXPECT_DOUBLE_EQ(min((double)-1.0, (double)1.0), -1.0);
    EXPECT_DOUBLE_EQ(min((double)1.0, (double)-1.0), -1.0);
}

TEST(optimbase, max)
{
    EXPECT_EQ(max((u8)0, (u8)1), 1u);
    EXPECT_EQ(max((u8)1, (u8)0), 1u);
    EXPECT_EQ(max((u16)0, (u16)1), 1u);
    EXPECT_EQ(max((u16)1, (u16)0), 1u);
    EXPECT_EQ(max((u32)0, (u32)1), 1u);
    EXPECT_EQ(max((u32)1, (u32)0), 1u);
    EXPECT_EQ(max((s32)-1, (s32)1), 1);
    EXPECT_EQ(max((s32)1, (s32)-1), 1);
    EXPECT_FLOAT_EQ(max((float)-1.0, (float)1.0), (float)1.0);
    EXPECT_FLOAT_EQ(max((float)1.0, (float)-1.0), (float)1.0);
    EXPECT_DOUBLE_EQ((double)max((double)-1.0, (double)1.0), 1.0);
    EXPECT_DOUBLE_EQ((double)max((double)1.0, (double)-1.0), 1.0);
}

#include <array>
TEST(optimbase, BitOperations)
{
    std::array<bool, 8>bb = { true,false,false,false,true,false,false,true };
    u8 field = 145;
    bitSet(field, 3); bb[3] = true;
    bitClear(field, 7); bb[7] = false;
    bitToggle(field, 4); bb[4] = false;
    bitToggle(field, 5); bb[5] = true;
    bitDefine(field, 1, true); bb[1] = true;
    for(u8 i = 0; i < 8; ++i)
        EXPECT_EQ(bitGet(field, i), bb[i]);
    std::array<bool, 64>bb64 = { true,false,false,false,true,false,false,true,false,false,false,false,false,false,false,false,
    false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,
    false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,
    false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false };
    u64 field64 = 145;
    bitSet(field64, 43); bb64[43] = true;
    bitClear(field64, 7); bb64[7] = false;
    bitToggle(field64, 4); bb64[4] = false;
    bitToggle(field64, 55); bb64[55] = true;
    bitDefine(field64, 61, true); bb64[61] = true;
    for(u8 i = 0; i < 64; ++i)
        EXPECT_EQ(bitGet(field64, i), bb64[i]);
}

