//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once

#include "MathOperators.h"
#include "Comparable.h"
#include <ostream>

/**
 * @brief namespace for all base structures
 */
namespace optim::base
{

/**
 * @brief Default base structure for 3D vector
 */
class Vector3 : public Comparable<Vector3>
{
public:
    // rule of fives
    Vector3(const Vector3&) = default; ///< Default copy constructor
    Vector3(Vector3&&)noexcept = default; ///< Default move constructor
    Vector3& operator=(const Vector3&) = default; ///< Default copy affectation
    Vector3& operator=(Vector3&&)noexcept = default; ///< Default move affectation
    ~Vector3() = default; ///< Default destructor
    // constructors
    /**
     * @brief One Constant constructor
     * @param[in] a the value to affect to all components
     */
    Vector3(double a = 0) :m_data { a, a, a } {}
    /**
     * @brief One Constant constructor
     * @param[in] x the value of the first component
     * @param[in] y the value of the second component
     * @param[in] z the value of the third component
     */
    Vector3(double x, double y, double z) :m_data { x, y, z } {}
    // out stream
    /**
     * @brief dump the value of vector into a basic stream
     * @param[inout] os the stream where to dump
     * @return reference to the input stream
     */
    std::ostream& dump(std::ostream&)const noexcept;
    // comparison
    /**
     * @brief Key function of comparison
     * @param[in] other the other vector to compare
     * @return negative value if this vector is lesser than other, positive value if greater, 0 if equal
     *
     * note that it will first compare the first component, if equal: the second , if equal the third
     */
    [[nodiscard]] s8 CompareTo(const Vector3&)const noexcept;
    // access

    /**
     * @brief Get the i-st vector component
     * @param[in] i the index of the component
     * @return the i-st component
     */
    [[nodiscard]] double& operator[](const u8 i) { return at(i); }
    /**
     * @brief Get the i-st vector component
     * @param[in] i the index of the component
     * @return the i-st component
     */
    [[nodiscard]] const double& operator[](const u8 i)const { return at(i); }
    /**
     * @brief Get the first vector component
     * @return the first component
     */
    [[nodiscard]] double& getX() { return at(0); }
    /**
     * @brief Get the first vector component
     * @return the first component
     */
    [[nodiscard]] const double& getX()const { return at(0); }
    /**
     * @brief Get the second vector component
     * @return the second component
     */
    [[nodiscard]] double& getY() { return at(1); }
    /**
     * @brief Get the second vector component
     * @return the second component
     */
    [[nodiscard]] const double& getY()const { return at(1); }
    /**
     * @brief Get the third vector component
     * @return the third component
     */
    [[nodiscard]] double& getZ() { return at(2); }
    /**
     * @brief Get the third vector component
     * @return the third component
     */
    [[nodiscard]] const double& getZ()const { return at(2); }
    /**
     * @brief Get the i-st vector component
     * @param[in] i the index of the component
     * @return the i-st component
     */
    [[nodiscard]] double& at(const u8 i);
    /**
     * @brief Get the i-st vector component
     * @param[in] i the index of the component
     * @return the i-st component
     */
    [[nodiscard]] const double& at(const u8 i)const;
    /**
     * @brief Get the i-st vector component
     * @param[in] i the index of the component
     * @param[in] value the value to set
     */
    void set(const u8 i, double value);
    // base operations
    /**
     * @brief add the other vector to this one
     * @param[in] o the other vector to add
     * @return this vector updated
     */
    Vector3& operator+=(const Vector3& o)noexcept { m_data[0] += o.m_data[0]; m_data[1] += o.m_data[1]; m_data[2] += o.m_data[2]; return *this; }
    /**
     * @brief substract the other vector to this one
     * @param[in] o the other vector to substract
     * @return this vector updated
     */
    Vector3& operator-=(const Vector3& o)noexcept { m_data[0] -= o.m_data[0]; m_data[1] -= o.m_data[1]; m_data[2] -= o.m_data[2]; return *this; }
    /**
     * @brief multiply this vector to a constant
     * @param[in] o the constant to multiply
     * @return this vector updated
     */
    Vector3& operator*=(const double& o)noexcept { m_data[0] *= o; m_data[1] *= o; m_data[2] *= o; return *this; }
    /**
     * @brief divide this vector to a constant
     * @param[in] o the constant to divide
     * @return this vector updated
     */
    Vector3& operator/=(const double& o);
    /**
     * @brief add the other vector to this one
     * @param[in] o the other vector to add
     * @return the sum of the two vectors
     */
    [[nodiscard]] Vector3 operator+(const Vector3& o)const noexcept { Vector3 t(*this); t += o; return t; }
    /**
     * @brief substract the other vector to this one
     * @param[in] o the other vector to substract
     * @return the difference of the two vectors
     */
    [[nodiscard]] Vector3 operator-(const Vector3& o)const noexcept { Vector3 t(*this); t -= o; return t; }
    /**
     * @brief change the sign of the vector
     * @return an inverted vector
     */
    [[nodiscard]] Vector3 operator-()const noexcept { return (*this * -1.0 ); }
    /**
     * @brief multiply this vector to a constant
     * @param[in] o the constant to multiply
     * @return the resultant vector
     */
    [[nodiscard]] Vector3 operator*(const double& o)const noexcept { Vector3 t(*this); t *= o; return t; }
    /**
     * @brief divide this vector to a constant
     * @param[in] o the constant to divide
     * @return the resultant vector
     */
    [[nodiscard]] Vector3 operator/(const double&)const;
    /**
     * @brief multiply a vector to a constant
     * @param[in] o the constant to multiply
     * @param[in] v the vector to multiply
     * @return the resultant vector
     */
    [[nodiscard]] friend Vector3 operator*(const double& o, const Vector3& v) noexcept { Vector3 t(v); t *= o; return t; }
    /**
     * @brief compute the cross product of this vector and the given one
     * @param[in] o the other vector to multiply
     * @return the cross product between the two vectors
     */
    [[nodiscard]] Vector3 CrossProduct(const Vector3& o)const noexcept { return Vector3(m_data[1] * o.m_data[2] - m_data[2] * o.m_data[1], m_data[2] * o.m_data[0] - m_data[0] * o.m_data[2], m_data[0] * o.m_data[1] - m_data[1] * o.m_data[0]); }
    /**
     * @brief compute the dot product of this vector and the given one
     * @param[in] o the other vector to multiply
     * @return the dot product between the two vectors
     */
    [[nodiscard]] double DotProduct(const Vector3& o)const noexcept { return m_data[0] * o.m_data[0] + m_data[1] * o.m_data[1] + m_data[2] * o.m_data[2]; }
    // properties
    /**
     * @brief is this vector null
     * @return true if all the component are closer to 0 than the default tolerance
     */
    [[nodiscard]] bool isNull()const noexcept { return (isfNull(m_data[0]) && isfNull(m_data[1]) && isfNull(m_data[2])); }
    /**
     * @brief check if two vectors are perpandicular
     * @param[in] o the other vector to compare
     * @return true if all the two vectors are perpandicular (whitin the default tolerance)
     */
    [[nodiscard]] bool isPerpandicular(const Vector3& o)const noexcept { return isfNull(DotProduct(o)); }
    /**
     * @brief check if two vectors are colinear
     * @param[in] o the other vector to compare
     * @return true if all the two vectors are colinear (whitin the default tolerance)
     */
    [[nodiscard]] bool isColinear(const Vector3& o)const noexcept { return CrossProduct(o).isNull(); }
    /**
     * @brief compute the square length of the vector
     * @return the square norm of the vector
     */
    [[nodiscard]] double LengthSQ()const noexcept { return DotProduct(*this); }
    /**
     * @brief compute the length of the vector
     * @return the norm of the vector
     */
    [[nodiscard]] double Length() const { return sqrt(LengthSQ()); }
    /**
     * @brief compute the square length of the vector from this to the given one
     * @param[in] o the other point to compute the distance
     * @return the square distance to the other point
     */
    [[nodiscard]] double DistanceSQ(const Vector3& o)const noexcept { return (*this-o).LengthSQ(); }
    /**
     * @brief compute the length of the vector from this to the given one
     * @param[in] o the other point to compute the distance
     * @return the distance to the other point
     */
    [[nodiscard]] double Distance(const Vector3& o) const { return sqrt(DistanceSQ(o)); }
private:
    double m_data[3]; ///< the data of the
};

/**
 * @brief stream operator apply to vector
 * @param[in] os the stream where to write the data
 * @param[in] v the vector to stream
 * @return the output stream
 */
std::ostream& operator<<(std::ostream& os, const Vector3& v);

}

