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
    Vector3 a(1, 2, 3), b1(1,2,4), b2(1, 2, 2), c1(1, 3, 3), c2(1, 1, 3), d1(2), d2(0, 2, 3) ;
    EXPECT_TRUE(a == a);
    EXPECT_TRUE(a != b1);
    // comparison
    EXPECT_TRUE(a <= a);
    EXPECT_TRUE(a <= b1);
    EXPECT_FALSE(a <= b2);
    EXPECT_TRUE(a <= c1);
    EXPECT_FALSE(a <= c2);
    EXPECT_TRUE(a <= d1);
    EXPECT_FALSE(a <= d2);
    EXPECT_FALSE(a < a);
    EXPECT_TRUE(a < b1);
    EXPECT_FALSE(a < b2);
    EXPECT_TRUE(a < c1);
    EXPECT_FALSE(a < c2);
    EXPECT_TRUE(a < d1);
    EXPECT_FALSE(a < d2);
    EXPECT_TRUE(a >= a);
    EXPECT_FALSE(a >= b1);
    EXPECT_TRUE(a >= b2);
    EXPECT_FALSE(a >= c1);
    EXPECT_TRUE(a >= c2);
    EXPECT_FALSE(a >= d1);
    EXPECT_TRUE(a >= d2);
    EXPECT_FALSE(a > a);
    EXPECT_FALSE(a > b1);
    EXPECT_TRUE(a > b2);
    EXPECT_FALSE(a > c1);
    EXPECT_TRUE(a > c2);
    EXPECT_FALSE(a > d1);
    EXPECT_TRUE(a > d2);
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
    // set values
    V.set(0, -666);
    V[1] *= 2;
    EXPECT_EQ(V, Vector3(-666, 1332, 666666));
    EXPECT_THROW(V.set(3,8), optim::Exception);
}

TEST(Vector3, baseOperations) {
    Vector3 V(-1, 666, 666666);
    EXPECT_EQ(V * 2, 2 * V);
    Vector3 V2(V);
    V /= 2;
    EXPECT_EQ(V2 / 2, V);
    EXPECT_THROW(V=V2/0, optim::Exception);
    EXPECT_THROW(V2 /= 0, optim::Exception);
    EXPECT_EQ(V + V2, V2 + V);
    EXPECT_EQ(V2 - V, V2 / 2);
    V[0] = 3; V[1] = 2; V[2] = 1;
    V2[0] = 1; V2[1] = 2; V2[2] = 3;
    EXPECT_DOUBLE_EQ(V.DotProduct(V2), V2.DotProduct(V));
    EXPECT_DOUBLE_EQ(V.DotProduct(V2), 10.0);
    EXPECT_EQ(V.CrossProduct(V2), -1.0 * V2.CrossProduct(V));
    EXPECT_EQ(V.CrossProduct(V2), Vector3(4,-8,4));
}

TEST(Vector3, AngleTest) {
    Vector3 V(-1, 666, 666666);
    Vector3 V2(2*V);
    EXPECT_TRUE(V.isColinear(V2));
    EXPECT_FALSE(V.isPerpandicular(V2));
}

TEST(Vector3, LengthDistance) {
    Vector3 V(-1, 666, 666666);
    Vector3 V2(2 * V);
    EXPECT_DOUBLE_EQ(V.LengthSQ(),V2.LengthSQ()/4.0);
    EXPECT_DOUBLE_EQ(V.Length(), V2.Length() / 2.0);
    EXPECT_DOUBLE_EQ(V.Distance(V2), V.Length());
    EXPECT_DOUBLE_EQ(V.DistanceSQ(V2), V.LengthSQ());
}
