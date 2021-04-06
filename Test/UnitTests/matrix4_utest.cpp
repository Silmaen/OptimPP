//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#include <base/Exception.h>
#include <base/matrix4.h>
#include <gtest/gtest.h>

using namespace optim::base;

Matrix4 matinit_Throw();
Matrix4 matequal_Throw(Matrix4 AA);
void f1(Matrix4 &T1);
void f2(Matrix4 &T1);
void f3(Matrix4 &T1);
double f4(const Matrix4 &A);
double f5(const Matrix4 &A);
double f6(const Matrix4 &A);
void fs1(Matrix4 &I1);
void fs2(Matrix4 &I1);
void fs3(Matrix4 &I1);


TEST(Matrix4, baseFunctions) {
    Matrix4 I0;
    EXPECT_TRUE(I0.isNull());
    double toto = 1;
    auto I1 = Matrix4(toto);
    EXPECT_FALSE(I1.isNull());
    Matrix4 I = Matrix4::makeIdentity();
    EXPECT_TRUE(I.isDiagonal());
    EXPECT_TRUE(I.isIdentity());
    EXPECT_FALSE(I1.isDiagonal());
    EXPECT_FALSE(I1.isIdentity());
    EXPECT_TRUE(I0.isDiagonal());
    EXPECT_FALSE(I0.isIdentity());
    //
    EXPECT_DOUBLE_EQ(I1[5], I1(1, 1));
    const Matrix4 A(I1);
    EXPECT_DOUBLE_EQ(A[5], A(1, 1));
    EXPECT_THROW(matinit_Throw(), optim::Exception);
    EXPECT_THROW(matequal_Throw(I0), optim::Exception);
    Matrix4 T1{1, 2, 3, 4,
               5, 6, 7, 8,
               9, 1, 2, 3,
               4, 5, 6, 7};
    EXPECT_DOUBLE_EQ(T1(2, 3), 3.0);
    EXPECT_THROW(f1(T1), optim::Exception);
    EXPECT_THROW(f2(T1), optim::Exception);
    EXPECT_THROW(f3(T1), optim::Exception);
    EXPECT_THROW(f4(A), optim::Exception);
    EXPECT_THROW(f5(A), optim::Exception);
    EXPECT_THROW(f6(A), optim::Exception);

    I1 = {11, 22, 33, 44,
          15, 26, 37, 48,
          19, 21, 32, 43,
          14, 25, 36, 47};
    EXPECT_DOUBLE_EQ(I1(2, 3), 43.0);
    EXPECT_THROW(fs1(I1), optim::Exception);
    EXPECT_THROW(fs2(I1), optim::Exception);
    EXPECT_THROW(fs3(I1), optim::Exception);
    I1.set(3, 5.0);
    I1.set(3, 1, -25.0);
    EXPECT_DOUBLE_EQ(I1(3, 1) + I1(0, 3), -20.0);
}

Matrix4 matinit_Throw() {
    Matrix4 AA{1.0, 2.0, 3.0};
    return AA;
}
Matrix4 matequal_Throw(Matrix4 AA) {
    AA = {1.0, 2.0, 3.0};
    return AA;
}
void f1(Matrix4 &T1) { T1(1, 4) = 3.0; }
void f2(Matrix4 &T1) { T1(4, 1) = 3.0; }
void f3(Matrix4 &T1) { T1[16] = 3.0; }
void fs1(Matrix4 &I1) { I1.set(18, 12.0); }
void fs2(Matrix4 &I1) { I1.set(4, 4, 12.0); }
void fs3(Matrix4 &I1) { I1.set(1, 4, 12.0); }
double f4(const Matrix4 &A) { return A(1, 4); }
double f5(const Matrix4 &A) { return A(4, 1); }
double f6(const Matrix4 &A) { return A[16]; }


TEST(Matrix4, baseOperations) {
    Matrix4 I0;
    Matrix4 I1 = Matrix4(1);
    const Matrix4 A(I1);
    //double toto = 4;
    I0 -= A;
    EXPECT_EQ(I0, -A);
    I1 += A;
    EXPECT_EQ(I1[8], 2.0 * A[8]);
    EXPECT_EQ(6.25 * I1, I1 * 6.25);
    I1 = {11, 22, 33, 5,
          15, 26, 37, 48,
          19, 21, 32, 43,
          14, -25, 36, 47};
    EXPECT_THROW(I1 /= 0, optim::Exception);
    EXPECT_THROW(I0 = I1 / 0, optim::Exception);
    Matrix4 D = A / 10;
    EXPECT_DOUBLE_EQ(D[6], 0.1);
    const Matrix4 B(I1);
    I1 = I1 + I1 - I1;
    EXPECT_EQ(B, I1);
    I1 = A * A;
    EXPECT_EQ(4 * A, I1);
}

#include <sstream>
TEST(Matrix4, Stream) {
    Matrix4 A(10);
    std::stringstream oss;
    oss << A;
    EXPECT_STREQ(oss.str().c_str(), "[ [10 10 10 10] [10 10 10 10] [10 10 10 10] [10 10 10 10] ]");
}

TEST(Matrix4, Transposition) {
    Matrix4 I1 = {1, 2, 3, 4,
                  5, 6, 7, 8,
                  9, 10, 11, 12,
                  13, 14, 15, 16};
    Matrix4 T1 = {1, 5, 9, 13,
                  2, 6, 10, 14,
                  3, 7, 11, 15,
                  4, 8, 12, 16};
    EXPECT_EQ(I1.Transposed(), T1);
}

TEST(Matrix4, Rotations) {
    Matrix4 R1 = Matrix4::makeRotationMatrixDeg(Vector3(90, 0, 0));
    EXPECT_EQ(R1.TransformVector(Vector3(1.0, 0.0, 0.0)), Vector3(1.0, 0.0, 0.0));
    Matrix4 R2 = Matrix4::makeRotationMatrix(Vector3(1.5707963267948, 0, 0));
    EXPECT_EQ(R2.TransformPoint(Vector3(1.0, 0.0, 0.0)), Vector3(1.0, 0.0, 0.0));
    R2.set(15, 0.0);
    EXPECT_EQ(R2.TransformPoint(Vector3(1.0, 0.0, 0.0)), Vector3(1.0, 0.0, 0.0));
}
