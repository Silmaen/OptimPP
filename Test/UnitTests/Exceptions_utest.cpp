#include <gtest/gtest.h>
#include "base/type.h"
#include "base/Exception.h"

using namespace optim;
#include <iterator>
TEST(Exceptions,baseCreation)
{
    for (u32 i = 0; i < std::size(ExitCode::ExitCodes); ++i) {
        Exception a(ExitCode::ExitCodes[i]);
        EXPECT_EQ(a.GetCode(), ExitCode::ExitCodes[i]);
        EXPECT_STREQ(a.what().c_str(), ExitCode::ToString(ExitCode::ExitCodes[i]).c_str());
    }
    
    Exception b(ExitCode::Value(-1));
    EXPECT_STREQ(b.what().c_str(), "Unknown error");
}

