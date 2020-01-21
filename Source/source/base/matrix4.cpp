//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#include "base/matrix4.h"
#include "base/Exception.h"
#include <utility>

namespace optim::base
{

Matrix4 Matrix4::makeRotationMatrix(const double& roll, const double& pitch, const double& yaw) noexcept
{
	double sr = sin(roll), cr = cos(roll);
	double sp = sin(pitch), cp = cos(pitch);
	double sy = sin(yaw), cy = cos(yaw);
	Matrix4 T;
	T.m_data[15] = 1.0;
	T.m_data[0] = cy * cp;
	T.m_data[1] = cy * sp * sr - sy * cr;
	T.m_data[2] = cy * sp * cr + sy * sr;
	T.m_data[4] = sy * cp;
	T.m_data[5] = sy * sp * sr + cy * cr;
	T.m_data[6] = sy * sp * cr - cy * sr;
	T.m_data[8] = -sp;
	T.m_data[9] = cp * sr;
	T.m_data[10] = cp * cr;
	return T;
}

Matrix4 Matrix4::makeRotationMatrixDeg(const double& roll, const double& pitch, const double& yaw) noexcept
{
	return makeRotationMatrix(roll * Deg2Rad, pitch * Deg2Rad, yaw * Deg2Rad);
}

Matrix4::Matrix4(std::initializer_list<double> l)
{
	if(l.size() != 16)
		throw Exception(ExitCode::Value::OutOfBounds);
	u8 i = 0;
	for(auto it = l.begin(); it != l.end(); ++it, ++i)
	{
		m_data[i] = *it;
	}
}

Matrix4& Matrix4::operator=(std::initializer_list<double> l)
{
	if(l.size() != 16)
		throw Exception(ExitCode::Value::OutOfBounds);
	u8 i = 0;
	for(auto it = l.begin(); it != l.end(); ++it, ++i)
	{
		m_data[i] = *it;
	}
	return *this;
}

std::ostream& Matrix4::dump(std::ostream& os)const noexcept
{
	os << "[ ";
	for(u8 i = 0; i < 4; ++i)
	{
		os << "[" << m_data[4 * i] << " " << m_data[4 * i + 1] << " " << m_data[4 * i + 2] << " " << m_data[4 * i + 3] << "] ";
	}
	os << "]";
	return os;
}

s8 Matrix4::CompareTo(const Matrix4& other)const noexcept
{
	for(u8 i = 0; i < 16; ++i)
	{
		if(at(i) < other.at(i)) return -1;
		if(at(i) > other.at(i)) return 1;
	}
	return 0;
}

[[nodiscard]] double& Matrix4::at(const u8 i)
{
	if(i > 15) throw Exception(ExitCode::Value::OutOfBounds);
	return m_data[i];
}
[[nodiscard]] const double& Matrix4::at(const u8 i)const
{
	if(i > 15) throw Exception(ExitCode::Value::OutOfBounds);
	return m_data[i];
}
[[nodiscard]] double& Matrix4::at(const u8 i, const u8 j)
{
	if(i > 3) throw Exception(ExitCode::Value::OutOfBounds);
	if(j > 3) throw Exception(ExitCode::Value::OutOfBounds);
	return m_data[i * 4 + j];
}
[[nodiscard]] const double& Matrix4::at(const u8 i, const u8 j)const
{
	if(i > 3) throw Exception(ExitCode::Value::OutOfBounds);
	if(j > 3) throw Exception(ExitCode::Value::OutOfBounds);
	return m_data[i * 4 + j];
}

void Matrix4::set(const u8 i, const double value)
{
	if(i > 15) throw Exception(ExitCode::Value::OutOfBounds);
	m_data[i] = value;

}
void Matrix4::set(const u8 i, const u8 j, const double value)
{
	if(i > 3) throw Exception(ExitCode::Value::OutOfBounds);
	if(j > 3) throw Exception(ExitCode::Value::OutOfBounds);
	m_data[i * 4 + j] = value;
}

Matrix4& Matrix4::operator/=(const double& o)
{
	if(isfNull(o))
		throw Exception(ExitCode::Value::ArithmeticError);
	for(u8 i = 0; i < 16; ++i)
	{
		m_data[i] /= o;
	}
	return *this;
}

[[nodiscard]] Matrix4 Matrix4::operator/(const double& o)const
{
	Matrix4 T(*this);
	T /= o;
	return T;
}

std::ostream& operator<<(std::ostream& os, const Matrix4 m)
{
	m.dump(os);
	return os;
}

void Matrix4::Transpose() noexcept
{
	for(u8 i = 0; i < 3; ++i)
		for(u8 j = i + 1; j < 4; ++j)
			std::swap(m_data[4 * i + j ], m_data[4 * j + i]);
}

[[nodiscard]] Matrix4 Matrix4::Transposed()const noexcept
{
	Matrix4 T(*this);
	T.Transpose();
	return T;
}

[[nodiscard]] Vector3 Matrix4::TransformVector(const Vector3& x) const noexcept
{
	Vector3 R;
	R.getX() = m_data[0] * x.getX() + m_data[1] * x.getY() + m_data[2] * x.getZ();
	R.getY() = m_data[4] * x.getX() + m_data[5] * x.getY() + m_data[6] * x.getZ();
	R.getZ() = m_data[8] * x.getX() + m_data[9] * x.getY() + m_data[10] * x.getZ();
	return R;
}

[[nodiscard]] Vector3 Matrix4::TransformPoint(const Vector3& x) const noexcept
{
	Vector3 R;
	R.getX() = m_data[0] * x.getX() + m_data[1] * x.getY() + m_data[2] * x.getZ() + m_data[3];
	R.getY() = m_data[4] * x.getX() + m_data[5] * x.getY() + m_data[6] * x.getZ() + m_data[7];
	R.getZ() = m_data[8] * x.getX() + m_data[9] * x.getY() + m_data[10] * x.getZ() + m_data[11];
	double w = m_data[12] * x.getX() + m_data[13] * x.getY() + m_data[14] * x.getZ() + m_data[15];
	if(!isfNull(w)) R /= w;
	return R;
}

}
