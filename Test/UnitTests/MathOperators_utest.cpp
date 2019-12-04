#include <gtest/gtest.h>
#include <base/MathOperators.h>
#include <base/Exception.h>

using namespace optim;

TEST(MathOperators, sqrtnoexcept)
{
    EXPECT_EQ(sqrt(static_cast<u8>(4)), 2u);
    EXPECT_EQ(sqrt(static_cast<u16>(4)), 2u);
    EXPECT_EQ(sqrt(static_cast<u32>(4)), 2u);
    EXPECT_EQ(sqrt(static_cast<u64>(4)), 2u);
    EXPECT_EQ(sqrt(static_cast<s8>(4)), 2);
    EXPECT_EQ(sqrt(static_cast<s16>(4)), 2);
    EXPECT_EQ(sqrt(static_cast<s32>(4)), 2);
    EXPECT_EQ(sqrt(static_cast<s64>(4)), 2);
    EXPECT_EQ(sqrt(4.0f), 2.0f);
    EXPECT_EQ(sqrt(4.0), 2.0);
}

TEST(MathOperators, sqrtexcept)
{
    bool a=false;
    EXPECT_THROW({ a = sqrt(static_cast<s8>(-4)) == 2; }, Exception);
    EXPECT_THROW({ a = sqrt(static_cast<s16>(-4)) == 2; }, Exception);
    EXPECT_THROW({ a = sqrt(static_cast<s32>(-4)) == 2; }, Exception);
    EXPECT_THROW({ a = sqrt(static_cast<s64>(-4)) == 2; }, Exception);
    EXPECT_THROW({ a = isfEqual(sqrt(-4.0f), 2); }, Exception);
    EXPECT_THROW({ a = isfEqual(sqrt(-4.0), 2); }, Exception);
    if (a) return;
}

TEST(MathOperators, log2i)
{
    EXPECT_EQ(log2i(static_cast<u32>(4)), 3u);
}
