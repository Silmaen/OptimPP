//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once

#include "vector3.h"

namespace optim::base
{

/**
 * @brief Basic class for handling transformation matrices
 */
class Matrix4 : public TieComparable<Matrix4>
{
public:
    // rule of fives
    Matrix4(const Matrix4&) = default; ///< basic copy constructor
    Matrix4(Matrix4&&)noexcept = default; ///< basic move constructor
    /**
     * default copy affectation
     * @return this object
     */
    Matrix4& operator=(const Matrix4&) = default;
    /**
     * default move affectation
     * @return this object
     */
    Matrix4& operator=(Matrix4&&)noexcept = default;
    ~Matrix4() = default;  ///< basic destructor
    /**
     * @brief constructor by a constant
     * @param[in] c the constant to apply to all components
     */
    explicit Matrix4(const double& c = 0) :m_data { c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c } {}
    /**
     * @brief constructor by initializer_list
     * @param[in] l the list of components
     */
    Matrix4(std::initializer_list<double> l);
    /**
     * @brief affectation by initializer_list
     * @param[in] l the list of components
     * @return this object
     */
    Matrix4& operator=(std::initializer_list<double> l);
    /**
     * @brief static method for creating a identity matrix
     * @return identity matrix
     */
    static Matrix4 makeIdentity()  noexcept { Matrix4 t; t[0] = 1.0; t[5] = 1.0; t[10] = 1.0; t[15] = 1.0; return t; }
    /**
     * @brief construct a rotation matrix base on rotation components
     * @param[in] roll the rotation in radian around X axis
     * @param[in] pitch the rotation in radian around Y axis
     * @param[in] yaw the rotation in radian around Z axis
     * @return a rotation matrix
     */
    static Matrix4 makeRotationMatrix(const double& roll, const double& pitch, const double& yaw) noexcept;
    /**
     * @overload
     * @param[in] rotationVector the tree component of the rotation
     * @return a rotation matrix
     */
    static Matrix4 makeRotationMatrix(const Vector3& rotationVector) noexcept{ return makeRotationMatrix(rotationVector.getX(), rotationVector.getY(), rotationVector.getZ());}
    /**
     * @brief construct a rotation matrix base on rotation components
     * @param[in] roll the rotation in degree around X axis
     * @param[in] pitch the rotation in degree around Y axis
     * @param[in] yaw the rotation in degree around Z axis
     * @return a rotation matrix
     */
    static Matrix4 makeRotationMatrixDeg(const double& roll, const double& pitch, const double& yaw) noexcept;
    /**
     * @overload
     * @param[in] rotationVector the tree component of the rotation
     * @return a rotation matrix
     */
    static Matrix4 makeRotationMatrixDeg(const Vector3& rotationVector) noexcept { return makeRotationMatrixDeg(rotationVector.getX(), rotationVector.getY(), rotationVector.getZ()); }
    // out stream
    /**
     * @brief dump data into a stream
     * @param[in] os stream where to dump data
     * @return reference to the input stream
     */
    std::ostream& dump(std::ostream& os)const noexcept;
    // comparison
    /**
     * @brief Key function of comparison
     */
    [[nodiscard]] auto Tie()const noexcept{
        return std::tie(m_data[0],m_data[1],m_data[2],m_data[3],m_data[4],m_data[5],m_data[6],m_data[7],m_data[8],m_data[9],m_data[10],m_data[11],m_data[12],m_data[13],m_data[14],m_data[15]);
    }
    // access
    /**
     * @brief Get the i-st matrix component in linear order
     * @param[in] i the index of the component
     * @return the i-st component
     */
    [[nodiscard]] double& operator[](const u8 i) { return at(i); }
    /**
     * @brief Get the i-st matrix component in linear order
     * @param[in] i the index of the component
     * @return the i-st component
     */
    [[nodiscard]] const double& operator[](const u8 i)const { return at(i); }
    /**
     * @brief Get the (i,j)-st matrix component
     * @param[in] i the index of the component's row
     * @param[in] j the index of the component's column
     * @return the (i,j)-st component
     */
    [[nodiscard]] double& operator()(const u8 i, const u8 j) { return at(i, j); }
    /**
     * @brief Get the (i,j)-st matrix component
     * @param[in] i the index of the component's row
     * @param[in] j the index of the component's column
     * @return the (i,j)-st component
     */
    [[nodiscard]] const double& operator()(const u8 i, const u8 j)const { return at(i, j); }
    /**
     * @brief Get the i-st matrix component in linear order
     * @param[in] i the index of the component
     * @return the i-st component
     */
    [[nodiscard]] double& at(u8 i);
    /**
     * @brief Get the i-st matrix component in linear order
     * @param[in] i the index of the component
     * @return the i-st component
     */
    [[nodiscard]] const double& at(u8 i)const;
    /**
     * @brief Get the i-st matrix component in linear order
     * @param[in] i the index of the component's row
     * @param[in] j the index of the component's column
     * @return the (i,j)-st component
     */
    [[nodiscard]] double& at(u8 i, u8 j);
    /**
     * @brief Get the (i,j)-st matrix component
     * @param[in] i the index of the component's row
     * @param[in] j the index of the component's column
     * @return the (i,j)-st component
     */
    [[nodiscard]] const double& at(u8 i, u8 j)const;
    /**
     * @brief Set the i-st matrix component in linear order
     * @param[in] i the index of the component
     * @param[in] value the value to set
     */
    void set(u8 i, double value);
    /**
     * @brief Set the (i,j)-st matrix component
     * @param[in] i the index of the component's row
     * @param[in] j the index of the component's column
     * @param[in] value the value to set
     */
    void set(u8 i, u8 j, double value);

    // base operations
    /**
     * @brief add the other matrix to this one
     * @param[in] o the other matrix to add
     * @return this matrix updated
     */
    Matrix4& operator+=(const Matrix4& o)noexcept { for(u8 i = 0; i < 16; ++i) { m_data[i] += o.m_data[i]; } return *this; }
    /**
     * @brief subtract the other matrix to this one
     * @param[in] o the other matrix to subtract
     * @return this matrix updated
     */
    Matrix4& operator-=(const Matrix4& o)noexcept { for(u8 i = 0; i < 16; ++i) { m_data[i] -= o.m_data[i]; } return *this; }
    /**
     * @brief multiply this matrix to a constant
     * @param[in] o the constant to multiply
     * @return this matrix updated
     */
    Matrix4& operator*=(const double& o)noexcept { for(double & i : m_data) { i *= o; } return *this; }
    /**
     * @brief divide this matrix to a constant
     * @param[in] o the constant to divide
     * @return this matrix updated
     */
    Matrix4& operator/=(const double& o);
    /**
     * @brief add the other vector to this one
     * @param[in] o the other vector to add
     * @return the sum of the two matrices
     */
    [[nodiscard]] Matrix4 operator+(const Matrix4& o)const noexcept { Matrix4 t(*this); t += o; return t; }
    /**
     * @brief subtract the other matrix to this one
     * @param[in] o the other vector to subtract
     * @return the difference of the two matrices
     */
    [[nodiscard]] Matrix4 operator-(const Matrix4& o)const noexcept { Matrix4 t(*this); t -= o; return t; }
    /**
     * @brief change the sign of the matrix
     * @return an inverted matrix
     */
    [[nodiscard]] Matrix4 operator-()const noexcept { return (*this * -1.0); }
    /**
     * @brief multiply this matrix to a constant
     * @param[in] o the constant to multiply
     * @return the resultant matrix
     */
    [[nodiscard]] Matrix4 operator*(const double& o)const noexcept { Matrix4 t(*this); t *= o; return t; }
    /**
     * @brief multiply this matrix to another matrix
     * @param[in] o the matrix to multiply
     * @return the resultant matrix
     */
    [[nodiscard]] Matrix4 operator*(const Matrix4& o)const noexcept { Matrix4 t; for(u8 i = 0; i < 4; ++i)for(u8 j = 0; j < 4; ++j)for(u8 k = 0; k < 4; ++k) { t(i, j) += at(i, k)*o.at(k, j); }  return t; }
    /**
     * @brief divide this matrix to a constant
     * @param[in] o the constant to divide
     * @return the resultant matrix
     */
    [[nodiscard]] Matrix4 operator/(const double& o)const;
    /**
     * @brief multiply a matrix to a constant
     * @param[in] o the constant to multiply
     * @param[in] v the matrix to multiply
     * @return the resultant matrix
     */
    [[nodiscard]] friend Matrix4 operator*(const double& o, const Matrix4& v) noexcept { Matrix4 t(v); t *= o; return t; }
    /**
     * @brief check if the matrix is an identity matrix.
     * @return true if the matrix is only constituted by 1 on the diagonal
     */
    [[nodiscard]] bool isIdentity()const noexcept { bool r = true; for(u8 i = 0; i < 15; ++i) { if((i == 0)||(i == 5)||(i == 10))r&=isfEqual(m_data[i], 1.); r &= isfNull(m_data[i]); } return r; }
    /**
     * @brief check if the matrix is Null
     * @return true if the matrix is only constituted by 0 (within tolerance)
     */
    [[nodiscard]] bool isNull()const noexcept { bool r = true; for(double i : m_data) { r &= isfNull(i); } return r; }
    /**
     * @brief check if the matrix is diagonal
     * @return true if the matrix is diagonal
     */
    [[nodiscard]] bool isDiagonal()const noexcept { bool r = true; for(u8 i = 1; i < 15; ++i) { if(i == 5)continue; if(i == 10)continue; r &= isfNull(m_data[i]); } return r; }
    /**
     * @brief Transpose tis matrix
     */
    void Transpose() noexcept;
    /**
     * @brief get a transposed version of this matrix
     * @return a copy of this matrix transposed
     */
    [[nodiscard]] Matrix4 Transposed()const noexcept;
    /**
     * @brief determine if this rotation matrix is a rotation matrix
     * @return true if the matrix is a rotation matrix
     */
    [[nodiscard]] bool isRotationMatrix()const noexcept {return (*this * Transposed()).isIdentity();}
    /**
     * @brief transform the given vector in the vector space
     * @param[in] x the vector to transform
     * @return the transformed vector
     */
    [[nodiscard]] Vector3 TransformVector(const Vector3& x) const noexcept;
    /**
     * @brief transform the given vector in the affine space
     * @param[in] x the vector to transform
     * @return the transformed vector
     */
    [[nodiscard]] Vector3 TransformPoint(const Vector3& x) const noexcept;
private:
    double m_data[16];///< the matrix data
};

/**
 * @brief streaming operator for matrix
 * @param[in,out] os input stream
 * @param[in] m the matrix to stream
 * @return the stream
 */
std::ostream& operator<<(std::ostream& os, const Matrix4& m);

}
