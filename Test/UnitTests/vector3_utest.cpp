#include <gtest/gtest.h>
#include <base/vector3.h>
#include <base/Exception.h>

using namespace optim::base;

TEST(Vector3,baseFunctions){
    // is NULL
    EXPECT_TRUE(Vector3(0, 0, 0).isNull());
    EXPECT_FALSE(Vector3(0, 0, 1).isNull());
    EXPECT_FALSE(Vector3(0, 1, 0).isNull());
    EXPECT_FALSE(Vector3(1, 0, 0).isNull());
    // equality
    EXPECT_TRUE(Vector3(1, 2, 3) == Vector3(1, 2, 3));
    EXPECT_TRUE(Vector3(1, 2, 3) != Vector3(1, 2, 4));
    // comparison
    EXPECT_TRUE(Vector3(1, 2, 3) <= Vector3(1, 2, 4));
    EXPECT_TRUE(Vector3(1, 2, 3) < Vector3(1, 2, 4));
    EXPECT_TRUE(Vector3(1, 2, 3) <= Vector3(1, 3, 2));
    EXPECT_TRUE(Vector3(1, 2, 3) < Vector3(1, 3, 2));
    EXPECT_TRUE(Vector3(1, 2, 3) <= Vector3(2, 1, 2));
    EXPECT_TRUE(Vector3(1, 2, 3) < Vector3(2, 1, 2));
    EXPECT_FALSE(Vector3(1, 2, 3) >= Vector3(1, 2, 4));
    EXPECT_FALSE(Vector3(1, 2, 3) > Vector3(1, 2, 4));
    EXPECT_FALSE(Vector3(1, 2, 3) >= Vector3(1, 3, 2));
    EXPECT_FALSE(Vector3(1, 2, 3) > Vector3(1, 3, 2));
    EXPECT_FALSE(Vector3(1, 2, 3) >= Vector3(2, 1, 2));
    EXPECT_FALSE(Vector3(1, 2, 3) > Vector3(2, 1, 2));
    // access
    Vector3 V(-1,666,666666);
    EXPECT_NEAR(V.at(0),-1,0.0001);
    EXPECT_NEAR(V.at(1), 666, 0.0001);
    EXPECT_NEAR(V.at(2), 666666, 0.0001);
    EXPECT_NEAR(V[0], -1, 0.0001);
    EXPECT_NEAR(V[1], 666, 0.0001);
    EXPECT_NEAR(V[2], 666666, 0.0001);
    EXPECT_NEAR(V.getX(), -1, 0.0001);
    EXPECT_NEAR(V.getY(), 666, 0.0001);
    EXPECT_NEAR(V.getZ(), 666666, 0.0001);
    const Vector3 Vc(-1, 666, 666666);
    EXPECT_NEAR(Vc.at(0), -1, 0.0001);
    EXPECT_NEAR(Vc.at(1), 666, 0.0001);
    EXPECT_NEAR(Vc.at(2), 666666, 0.0001);
    EXPECT_NEAR(Vc[0], -1, 0.0001);
    EXPECT_NEAR(Vc[1], 666, 0.0001);
    EXPECT_NEAR(Vc[2], 666666, 0.0001);
    EXPECT_NEAR(Vc.getX(), -1, 0.0001);
    EXPECT_NEAR(Vc.getY(), 666, 0.0001);
    EXPECT_NEAR(Vc.getZ(), 666666, 0.0001);
    // bad access
    EXPECT_THROW(V[0] = V.at(55), optim::Exception);
    EXPECT_THROW(V[0] = Vc.at(55), optim::Exception);
}