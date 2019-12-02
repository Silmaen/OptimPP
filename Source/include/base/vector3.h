//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once

#include "type.h"
#include "Comparable.h"
#include <ostream>

namespace optim::base
{

class Vector3 : public Comparable<Vector3>
{
public:
    // rule of fives
    Vector3(const Vector3&) = default;
    Vector3(Vector3&&)noexcept = default;
    Vector3& operator=(const Vector3&) = default;
    Vector3& operator=(Vector3&&)noexcept = default;
    ~Vector3() = default;
    // constructors
    Vector3(double a = 0) :m_data { a, a, a } {}
    Vector3(double x, double y, double z) :m_data { x, y, z } {}
    // out stream
    std::ostream& dump(std::ostream&)const noexcept;
    // comparison
    [[nodiscard]] s8 CompareTo(const Vector3&)const noexcept;
    // access
    [[nodiscard]] double& operator[](const u8 i) { return at(i); }
    [[nodiscard]] const double& operator[](const u8 i)const { return at(i); }
    [[nodiscard]] double& getX() { return at(0); }
    [[nodiscard]] const double& getX()const { return at(0); }
    [[nodiscard]] double& getY() { return at(1); }
    [[nodiscard]] const double& getY()const { return at(1); }
    [[nodiscard]] double& getZ() { return at(2); }
    [[nodiscard]] const double& getZ()const { return at(2); }
    [[nodiscard]] double& at(const u8 i);
    [[nodiscard]] const double& at(const u8 i)const;
    void set(const u8 i, double value);
    // base operations
    Vector3& operator+=(const Vector3& o)noexcept { m_data[0] += o.m_data[0]; m_data[1] += o.m_data[1]; m_data[2] += o.m_data[2]; return *this; }
    Vector3& operator-=(const Vector3& o)noexcept { m_data[0] -= o.m_data[0]; m_data[1] -= o.m_data[1]; m_data[2] -= o.m_data[2]; return *this; }
    Vector3& operator*=(const double& o)noexcept { m_data[0] *= o; m_data[1] *= o; m_data[2] *= o; return *this; }
    Vector3& operator/=(const double& o);
    [[nodiscard]] Vector3 operator+(const Vector3& o)const noexcept { Vector3 t(*this); t += o; return t; }
    [[nodiscard]] Vector3 operator-(const Vector3& o)const noexcept { Vector3 t(*this); t -= o; return t; }
    [[nodiscard]] Vector3 operator*(const double& o)const noexcept { Vector3 t(*this); t *= o; return t; }
    [[nodiscard]] Vector3 operator/(const double&)const;
    [[nodiscard]] friend Vector3 operator*(const double& o, const Vector3& v) noexcept { Vector3 t(v); t *= o; return t; }
    [[nodiscard]] Vector3 CrossProduct(const Vector3& o)const noexcept { return Vector3(m_data[1] * o.m_data[2] - m_data[2] * o.m_data[1], m_data[2] * o.m_data[0] - m_data[0] * o.m_data[2], m_data[0] * o.m_data[1] - m_data[1] * o.m_data[0]); }
    [[nodiscard]] double DotProduct(const Vector3& o)const noexcept { return m_data[0] * o.m_data[0] + m_data[1] * o.m_data[1] + m_data[2] * o.m_data[2]; }
    // properties
    [[nodiscard]] bool isNull()const noexcept { return (isfNull(m_data[0]) && isfNull(m_data[1]) && isfNull(m_data[2])); };
    [[nodiscard]] bool isPerpandicular(const Vector3& o)const noexcept { return isfNull(DotProduct(o)); };
    [[nodiscard]] bool isColinear(const Vector3& o)const noexcept { return CrossProduct(o).isNull(); };
    [[nodiscard]] double LengthSQ()const noexcept { return DotProduct(*this); }
    [[nodiscard]] double Length() const { return sqrt(LengthSQ()); }
    [[nodiscard]] double DistanceSQ(const Vector3& o)const noexcept { return (*this-o).LengthSQ(); }
    [[nodiscard]] double Distance(const Vector3& o) const { return sqrt(DistanceSQ(o)); }
private:
    double m_data[3];
};

std::ostream& operator<<(std::ostream& os, const Vector3& v);

}