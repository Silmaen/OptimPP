//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once

#include "type.h"

namespace optim
{
// SQRT 
/**
 * @brief compute the square root
 * @param[in] x the value to compute the square root
 * @return the square root
 */
[[nodiscard]] u8 sqrt(const u8& x)noexcept;
/**
 * @overload
 * @param[in] x the value to compute the square root
 * @return the square root
 */
[[nodiscard]] u16 sqrt(const u16& x)noexcept;
/**
 * @overload
 * @param[in] x the value to compute the square root
 * @return the square root
 */
[[nodiscard]] u32 sqrt(const u32& x)noexcept;
/**
 * @overload
 * @param[in] x the value to compute the square root
 * @return the square root
 */
[[nodiscard]] u64 sqrt(const u64& x)noexcept;
/**
 * @overload
 * @param[in] x the value to compute the square root
 * @return the square root
 */
[[nodiscard]] s8 sqrt(const s8& x);
/**
 * @overload
 * @param[in] x the value to compute the square root
 * @return the square root
 */
[[nodiscard]] s16 sqrt(const s16& x);
/**
 * @overload
 * @param[in] x the value to compute the square root
 * @return the square root
 */
[[nodiscard]] s32 sqrt(const s32& x);
/**
 * @overload
 * @param[in] x the value to compute the square root
 * @return the square root
 */
[[nodiscard]] s64 sqrt(const s64& x);
/**
 * @overload
 * @param[in] x the value to compute the square root
 * @return the square root
 */
[[nodiscard]] float sqrt(const float& x);
/**
 * @overload
 * @param[in] x the value to compute the square root
 * @return the square root
 */
[[nodiscard]] double sqrt(const double& x);

// log2
/**
 * @brief compute the logarithm base 2 of the given number
 * @param[in] x the value to compute the log2
 * @return the logarithm base 2
 */
[[nodiscard]] u32 log2i(const u32& x);

//-----------------------------------------------------------------------------
// trigonometry
//-----------------------------------------------------------------------------

constexpr double Pi = 3.141592653589793; ///< constant Pi as double
constexpr float Pif = 3.141592f;  ///< constant Pi as float
[[maybe_unused]] constexpr double Rad2Deg = 180.0 / Pi;  ///< Conversion radian to degree as double
[[maybe_unused]] constexpr float Rad2Degf = 180.0f / Pif;///< Conversion radian to degree as float
constexpr double Deg2Rad = Pi / 180.0; ///< Conversion degree to radian as double
constexpr float Deg2Radf = Pif / 180.0f; ///< Conversion degree to radian as float

/**
 * @brief the cosine of a radian angle
 * @param[in] x the angle in radian
 * @return the value of the cosine
 */
[[nodiscard]] float cos(const float& x);
/**
 * @overload
 * @param[in] x the angle in radian
 * @return the value of the cosine
 */
[[nodiscard]] double cos(const double& x);/**
 * @brief the cosine of a radian angle
 * @param[in] x the angle in degree
 * @return the value of the cosine
 */
[[nodiscard]] float cosdeg(const float& x);
/**
 * @overload
 * @param[in] x the angle in degree
 * @return the value of the cosine
 */
[[nodiscard]] double cosdeg(const double& x);
/**
 * @brief the sine of a radian angle
 * @param[in] x the angle in radian
 * @return the value of the sine
 */
[[nodiscard]] float sin(const float& x);
/**
 * @overload
 * @param[in] x the angle in radian
 * @return the value of the sine
 */
[[nodiscard]] double sin(const double& x);
/**
 * @brief the sine of a radian angle
 * @param[in] x the angle in degree
 * @return the value of the sine
 */
[[nodiscard]] float sindeg(const float& x);
/**
 * @overload
 * @param[in] x the angle in degree
 * @return the value of the sine
 */
[[nodiscard]] double sindeg(const double& x);

}

