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

}

