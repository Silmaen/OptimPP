//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#include <base/Exception.h>
#include <base/MathOperators.h>
#include <gtest/gtest.h>

using namespace optim;

TEST(MathOperators, sqrtnoexcept) {
    EXPECT_EQ(sqrt(static_cast<u8>(4)), 2U);
    EXPECT_EQ(sqrt(static_cast<u16>(4)), 2U);
    EXPECT_EQ(sqrt(static_cast<u32>(4)), 2U);
    EXPECT_EQ(sqrt(static_cast<u64>(4)), 2U);
    EXPECT_EQ(sqrt(static_cast<s8>(4)), 2);
    EXPECT_EQ(sqrt(static_cast<s16>(4)), 2);
    EXPECT_EQ(sqrt(static_cast<s32>(4)), 2);
    EXPECT_EQ(sqrt(static_cast<s64>(4)), 2);
    EXPECT_FLOAT_EQ(optim::sqrt(4.0F), 2.0F);
    EXPECT_DOUBLE_EQ(optim::sqrt(4.0), 2.0);
}

TEST(MathOperators, sqrtexcept) {
    bool a = false;
    EXPECT_THROW({ a = sqrt(static_cast<s8>(-4)) == 2; }, Exception);
    EXPECT_THROW({ a = sqrt(static_cast<s16>(-4)) == 2; }, Exception);
    EXPECT_THROW({ a = sqrt(static_cast<s32>(-4)) == 2; }, Exception);
    EXPECT_THROW({ a = sqrt(static_cast<s64>(-4)) == 2; }, Exception);
    EXPECT_THROW({ a = isfEqual(optim::sqrt(-4.0F), 2); }, Exception);
    EXPECT_THROW({ a = isfEqual(optim::sqrt(-4.0), 2); }, Exception);
    if (a) return;
}

TEST(MathOperators, log2i) {
    EXPECT_EQ(log2i(static_cast<u32>(4)), 2U);
    EXPECT_EQ(log2i(static_cast<u32>(1U << 16)), 16U);
    EXPECT_EQ(log2i(static_cast<u32>(1U << 30)), 30U);
}

TEST(MathOperators, sincos) {
    float pi2f = 3.141592F / 2.F;
    double pi2 = 3.141592653589793 / 2.0;
    EXPECT_FLOAT_EQ(optim::sin(pi2f), 1.0F);
    EXPECT_DOUBLE_EQ(optim::sin(pi2), 1.0);
    EXPECT_NEAR(optim::cos(pi2f), 0.0F, 1e-6);
    EXPECT_NEAR(optim::cos(pi2), 0.0, 1e-15);
    EXPECT_FLOAT_EQ(sindeg(90.0F), 1.0F);
    EXPECT_DOUBLE_EQ(sindeg(90.0), 1.0);
    EXPECT_NEAR(cosdeg(90.0F), 0.0F, 1e-6);
    EXPECT_NEAR(cosdeg(90.0), 0.0, 1e-15);
}
