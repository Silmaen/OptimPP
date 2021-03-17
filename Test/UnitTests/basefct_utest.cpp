#include <gtest/gtest.h>
#include <base/type.h>

using namespace optim;

TEST(optimbase, clamp)
{
    EXPECT_EQ(clamp(0ll, -1ll, 1ll), 0ll);
    EXPECT_EQ(clamp(-4ll, -1ll, 1ll), -1ll);
    EXPECT_EQ(clamp(4ll, -1ll, 1ll), 1ll);
    EXPECT_FLOAT_EQ(clamp(0.0f, -1.0f, 1.0f), 0.0f);
    EXPECT_FLOAT_EQ(clamp(-4.0f, -1.0f, 1.0f),-1.0f);
    EXPECT_FLOAT_EQ(clamp(4.0f, -1.0f, 1.0f), 1.0f);
    EXPECT_DOUBLE_EQ(clamp(0.0, -1.0, 1.0), 0.0);
    EXPECT_DOUBLE_EQ(clamp(-4.0, -1.0, 1.0), -1.0);
    EXPECT_DOUBLE_EQ(clamp(4.0, -1.0, 1.0), 1.0);

	EXPECT_EQ(clamp8(4), 4);
	EXPECT_EQ(clamp8(-400), -128);
	EXPECT_EQ(clamp8(400), 127);
}

TEST(optimbase, sign)
{
    EXPECT_EQ(sign(0ll), 0ll);
    EXPECT_EQ(sign(-1ll), -1ll);
    EXPECT_EQ(sign(1ll), 1ll);
    EXPECT_FLOAT_EQ(sign(0.0f), 0.0f);
    EXPECT_FLOAT_EQ(sign(-1.0f), -1.0f);
    EXPECT_FLOAT_EQ(sign(1.0f), 1.0f);
    EXPECT_DOUBLE_EQ(sign(0.0), 0.0);
    EXPECT_DOUBLE_EQ(sign(-1.0), -1.0);
    EXPECT_DOUBLE_EQ(sign(1.0), 1.0);
}

TEST(optimbase, abs)
{
    EXPECT_EQ(optim::abs(-1ll), 1ll);
    EXPECT_EQ(optim::abs(1ll), 1ll);
    EXPECT_FLOAT_EQ(optim::abs(-1.0f), 1.0f);
    EXPECT_FLOAT_EQ(optim::abs(1.0f), 1.0f);
    EXPECT_DOUBLE_EQ(optim::abs(-1.0), 1.0);
    EXPECT_DOUBLE_EQ(optim::abs(1.0), 1.0);
}

TEST(optimbase, min)
{
    EXPECT_EQ(min(static_cast<u8>(0), static_cast<u8>(1)), 0u);
    EXPECT_EQ(min(static_cast<u8>(1), static_cast<u8>(0)), 0u);
    EXPECT_EQ(min(static_cast<u16>(0), static_cast<u16>(1)), 0u);
    EXPECT_EQ(min(static_cast<u16>(1), static_cast<u16>(0)), 0u);
    EXPECT_EQ(min(static_cast<u32>(0), static_cast<u32>(1)), 0u);
    EXPECT_EQ(min(static_cast<u32>(1), static_cast<u32>(0)), 0u);
    EXPECT_EQ(min(static_cast<u64>(0), static_cast<u64>(1)), 0u);
    EXPECT_EQ(min(static_cast<u64>(1), static_cast<u64>(0)), 0u);
    EXPECT_EQ(min(static_cast<s32>(-1), static_cast<s32>(1)), -1);
    EXPECT_EQ(min(static_cast<s32>(1), static_cast<s32>(-1)), -1);
    EXPECT_EQ(min(static_cast<s64>(-1), static_cast<s64>(1)), -1);
    EXPECT_EQ(min(static_cast<s64>(1), static_cast<s64>(-1)), -1);
    EXPECT_FLOAT_EQ(min(-1.0f, 1.0f), -1.0f);
    EXPECT_FLOAT_EQ(min(1.0f, -1.0f), -1.0f);
    EXPECT_DOUBLE_EQ(min(-1.0, 1.0), -1.0);
    EXPECT_DOUBLE_EQ(min(1.0, -1.0), -1.0);
}

TEST(optimbase, max)
{
    EXPECT_EQ(max(static_cast<u8>(0), static_cast<u8>(1)), 1u);
    EXPECT_EQ(max(static_cast<u8>(1), static_cast<u8>(0)), 1u);
    EXPECT_EQ(max(static_cast<u16>(0), static_cast<u16>(1)), 1u);
    EXPECT_EQ(max(static_cast<u16>(1), static_cast<u16>(0)), 1u);
    EXPECT_EQ(max(static_cast<u32>(0), static_cast<u32>(1)), 1u);
    EXPECT_EQ(max(static_cast<u32>(1), static_cast<u32>(0)), 1u);
    EXPECT_EQ(max(static_cast<u64>(0), static_cast<u64>(1)), 1u);
    EXPECT_EQ(max(static_cast<u64>(1), static_cast<u64>(0)), 1u);
    EXPECT_EQ(max(static_cast<s32>(-1), static_cast<s32>(1)), 1);
    EXPECT_EQ(max(static_cast<s32>(1), static_cast<s32>(-1)), 1);
    EXPECT_EQ(max(static_cast<s64>(-1), static_cast<s64>(1)), 1);
    EXPECT_EQ(max(static_cast<s64>(1), static_cast<s64>(-1)), 1);
    EXPECT_FLOAT_EQ(max(-1.0f, 1.0f), 1.0f);
    EXPECT_FLOAT_EQ(max(1.0f, -1.0f), 1.0f);
    EXPECT_DOUBLE_EQ(max(-1.0, 1.0), 1.0);
    EXPECT_DOUBLE_EQ(max(1.0, -1.0), 1.0);
}

TEST(optimbase, isfNull)
{
    EXPECT_TRUE(isfNull(0.0f));
    EXPECT_TRUE(isfNull(0.00000001f));
    EXPECT_FALSE(isfNull(1.0f));
    EXPECT_FALSE(isfNull(-1.0f));
    EXPECT_TRUE(isfNull(0.0));
    EXPECT_TRUE(isfNull(0.00000001));
    EXPECT_FALSE(isfNull(1.0));
    EXPECT_FALSE(isfNull(-1.0));

    EXPECT_TRUE(isfEqual(1.0f,1.0f));
    EXPECT_TRUE(isfEqual(0.1f,0.10000001f));
    EXPECT_FALSE(isfEqual(1.0f,0.01f));
    EXPECT_FALSE(isfEqual(-1.0f,0.01f));
    EXPECT_TRUE(isfEqual(1.0,1.0));
    EXPECT_TRUE(isfEqual(0.1,0.100000001));
    EXPECT_FALSE(isfEqual(1.0,0.01));
    EXPECT_FALSE(isfEqual(-1.0,0.01));
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

