//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------
#include "base/Exception.h"
#include <gtest/gtest.h>

using namespace optim;
TEST(Exceptions, baseCreation) {
    for (auto ExitCode : ExitCode::ExitCodes) {
        Exception a(ExitCode);
        EXPECT_EQ(a.GetCode(), ExitCode);
        EXPECT_STREQ(a.what(), ExitCode::ToString(ExitCode));
    }

    Exception b(ExitCode::Value(-1));
    EXPECT_STREQ(b.what(), "Unknown error");
}
