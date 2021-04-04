//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once
#include <cinttypes>
#include <memory>
#include <string>
#include <vector>

/**
 * @brief namespace of the whole project
 */
namespace optim {

constexpr double DefaultTolerance = 1.e-7;                    ///< default tolerance for double comparison
constexpr float DefaultfTolerance = static_cast<float>(1.e-7);///< default tolerance for float comparison

// base int types
// SIGNED INTEGERS
/// @brief signed 64bit integer
using s64 = int64_t;// -170 141 183 460 469 231 731 687 303 715 884 105 728 to 170 141 183 460 469 231 731 687 303 715 884 105 727
/// @brief signed 32bit integer
using s32 = int32_t;// -2 147 483 648 to 2 147 483 647
/// @brief signed 16bit integer
using s16 = int16_t;// -32 768 to 32 767
/// @brief signed 8bit integer
using s8 = int8_t;// -128 to 127
// UNSIGNED INTEGERS
/// @brief unsigned 64bit integer
using u64 = uint64_t;// 0 to 340 282 366 920 938 463 463 374 607 431 768 211 455
/// @brief unsigned 32bit integer
using u32 = uint32_t;// 0 to 4 294 967 295
/// @brief unsigned 16bit integer
using u16 = uint16_t;// 0 to 65 535
/// @brief unsigned 8bit integer
using u8 = uint8_t;// 0 to 255
/// @brief base string type
using string = std::string;

// shortcut for std structures
using std::shared_ptr;
using std::vector;

// ------------------------------------------ BASE FCT ------------------------------------------
// CLAMP
/**
 * @brief compute the value of x clamped between [a,b]
 * @param[in] x the value to clamp
 * @param[in] a the lower value of the clamp interval
 * @param[in] b the upper value of the clamp interval
 * @return a if x lesser than a, b if x greater than b else x
 */
[[nodiscard]] inline s64 clamp(const s64 &x, const s64 &a, const s64 &b) { return ((x < a) ? a : ((x > b) ? b : x)); }
/**
 * @brief clamp a value int the s8 range
 * @param[in] x the value to clamp
 * @return the s8 value in the range [-128, 127]
 */
[[nodiscard]] inline s8 clamp8(const s64 &x) { return static_cast<s8>(clamp(x, -128, 127)); }
/**
 * @overload
 * @param[in] x the value to clamp
 * @param[in] a the lower value of the clamp interval
 * @param[in] b the upper value of the clamp interval
 * @return a if x lesser than a, b if x greater than b else x
 */
[[nodiscard]] inline float clamp(const float &x, const float &a, const float &b) { return ((x < a) ? a : ((x > b) ? b : x)); }
/**
 * @overload
 * @param[in] x the value to clamp
 * @param[in] a the lower value of the clamp interval
 * @param[in] b the upper value of the clamp interval
 * @return a if x lesser than a, b if x greater than b else x
 */
[[nodiscard]] inline double clamp(const double &x, const double &a, const double &b) { return ((x < a) ? a : ((x > b) ? b : x)); }
// SIGN
/**
 * @brief compute the sign of x
 * @param[in] x the value to sign
 * @return -1 if x lesser than 0, 1 if x greater than 0 else 0
 */
[[nodiscard]] inline s64 sign(const s64 &x) { return (x < 0 ? -1 : ((x > 0) ? 1 : 0)); }
/**
 * @overload
 * @param[in] x the value to sign
 * @return -1 if x lesser than 0, 1 if x greater than 0 else 0
 */
[[nodiscard]] inline float sign(const float &x) { return (x < 0 ? -1.0F : ((x > 0) ? 1.0F : 0.0F)); }
/**
 * @overload
 * @param[in] x the value to sign
 * @return -1 if x lesser than 0, 1 if x greater than 0 else 0
 */
[[nodiscard]] inline double sign(const double &x) { return (x < 0 ? -1.0 : ((x > 0) ? 1.0 : 0.0)); }
// ABS
/**
 * @brief compute the absolute value of x
 * @param[in] x the value to abs
 * @return -x if x lesser than 0, else x
 */
[[nodiscard]] inline s64 abs(const s64 &x) { return (x < 0 ? -x : x); }
/**
 * @overload
 * @param[in] x the value to abs
 * @return -x if x lesser than 0, else x
 */
[[nodiscard]] inline float abs(const float &x) { return (x < 0 ? -x : x); }
/**
 * @overload
 * @param[in] x the value to abs
 * @return -x if x lesser than 0, else x
 */
[[nodiscard]] inline double abs(const double &x) { return (x < 0 ? -x : x); }
//MIN
/**
 * @brief get the lesser of two numbers
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a lesser than b else b
 */
[[nodiscard]] inline u8 min(const u8 &a, const u8 &b) { return ((a > b) ? b : a); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a lesser than b else b
 */
[[nodiscard]] inline u16 min(const u16 &a, const u16 &b) { return ((a > b) ? b : a); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a lesser than b else b
 */
[[nodiscard]] inline u32 min(const u32 &a, const u32 &b) { return ((a > b) ? b : a); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a lesser than b else b
 */
[[nodiscard]] inline u64 min(const u64 &a, const u64 &b) { return ((a > b) ? b : a); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a lesser than b else b
 */
[[nodiscard]] inline s32 min(const s32 &a, const s32 &b) { return ((a > b) ? b : a); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a lesser than  else b
 */
[[nodiscard]] inline s64 min(const s64 &a, const s64 &b) { return ((a > b) ? b : a); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a lesser than b else b
 */
[[nodiscard]] inline float min(const float &a, const float &b) { return ((a > b) ? b : a); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a lesser than b else b
 */
[[nodiscard]] inline double min(const double &a, const double &b) { return ((a > b) ? b : a); }
//MAX
/**
 * @brief get the greater of two numbers
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a greater than b else b
 */
[[nodiscard]] inline u8 max(const u8 &a, const u8 &b) { return ((a > b) ? a : b); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a greater than b else b
 */
[[nodiscard]] inline u16 max(const u16 &a, const u16 &b) { return ((a > b) ? a : b); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a greater than b else b
 */
[[nodiscard]] inline u32 max(const u32 &a, const u32 &b) { return ((a > b) ? a : b); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a greater than b else b
 */
[[nodiscard]] inline u64 max(const u64 &a, const u64 &b) { return ((a > b) ? a : b); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a greater than b else b
 */
[[nodiscard]] inline s32 max(const s32 &a, const s32 &b) { return ((a > b) ? a : b); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a greater than b else b
 */
[[nodiscard]] inline s64 max(const s64 &a, const s64 &b) { return ((a > b) ? a : b); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a greater than b else b
 */
[[nodiscard]] inline float max(const float &a, const float &b) { return ((a > b) ? a : b); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a greater than b else b
 */
[[nodiscard]] inline double max(const double &a, const double &b) { return ((a > b) ? a : b); }
// Bits operations
/**
 * @brief set a bit in number
 * @param[in,out] number the number where to set the bit
 * @param[in] bit the index of the bit to set
 */
inline void bitSet(u8 &number, const u8 &bit) { number |= 1UL << bit; }
/**
 * @brief define the value of a bit in number
 * @param[in,out] number the number where to set the bit
 * @param[in] bit the index of the bit to set
 * @param[in] value the value of the bit to set
 */
inline void bitDefine(u8 &number, const u8 &bit, const bool &value) { number = static_cast<u8>((number & ~(static_cast<u8>(1U) << bit)) | (static_cast<u8>(value) << bit)); }
/**
 * @brief clear a bit in number
 * @param[in,out] number the number where to clear the bit
 * @param[in] bit the index of the bit to clear
 */
inline void bitClear(u8 &number, const u8 &bit) { number &= ~(1UL << bit); }
/**
 * @brief toggle a bit in number
 * @param[in,out] number the number where to toggle the bit
 * @param[in] bit the index of the bit to toggle
 */
inline void bitToggle(u8 &number, const u8 &bit) { number ^= 1UL << bit; }
/**
 * @brief get a bit in number
 * @param[in,out] number the number where to get the bit
 * @param[in] bit the index of the bit to get
 * @return the value of the bit
 */
[[nodiscard]] inline bool bitGet(const u8 &number, const u8 &bit) { return ((number >> bit) & 1U) != 0U; }
/**
 * @overload
 * @param[in,out] number the number where to set the bit
 * @param[in] bit the index of the bit to set
 */
inline void bitSet(u64 &number, const u8 &bit) { number |= 1ULL << bit; }
/**
 * @overload
 * @param[in,out] number the number where to set the bit
 * @param[in] bit the index of the bit to set
 * @param[in] value the value of the bit to set
 */
inline void bitDefine(u64 &number, const u8 &bit, const bool &value) { number = (number & ~(1ULL << bit)) | (static_cast<u64>(value) << bit); }
/**
 * @overload
 * @param[in,out] number the number where to clear the bit
 * @param[in] bit the index of the bit to clear
 */
inline void bitClear(u64 &number, const u8 &bit) { number &= ~(1ULL << bit); }
/**
 * @overload
 * @param[in,out] number the number where to toggle the bit
 * @param[in] bit the index of the bit to toggle
 */
inline void bitToggle(u64 &number, const u8 &bit) { number ^= 1ULL << bit; }
/**
 * @overload
 * @param[in,out] number the number where to get the bit
 * @param[in] bit the index of the bit to get
 * @return the value of the bit
 */
[[nodiscard]] inline bool bitGet(const u64 &number, const u8 &bit) { return ((number >> bit) & 1ULL) != 0U; }

// float Equality
/**
 * @brief test if the given real number is null (with the given tolerance)
 * @param[in] a the real number to test
 * @param[in] tolerance the absolute value of tolerance for comparison
 * @return true if a is closer to 0 than tolerance
 */
[[nodiscard]] inline bool isfNull(const float &a, const float &tolerance = DefaultfTolerance) { return (abs(a) < tolerance); }
/**
 * @overload
 * @param[in] a the real number to test
 * @param[in] tolerance the absolute value of tolerance for comparison
 * @return true if a is closer to 0 than tolerance
 */
[[nodiscard]] inline bool isfNull(const double &a, const double &tolerance = DefaultTolerance) { return (abs(a) < tolerance); }
/**
 * @brief test if the given real numbers are equal (closer than the given tolerance)
 * @param[in] a the first real number to test
 * @param[in] b the second real number to test
 * @param[in] tolerance the absolute value of tolerance for comparison
 * @return true if a is closer to b than tolerance
 */
[[nodiscard]] inline bool isfEqual(const float &a, const float &b, const float &tolerance = DefaultfTolerance) { return (abs(a - b) < tolerance); }
/**
 * @overload
 * @param[in] a the first real number to test
 * @param[in] b the second real number to test
 * @param[in] tolerance the absolute value of tolerance for comparison
 * @return true if a is closer to b than tolerance
 */
[[nodiscard]] inline bool isfEqual(const double &a, const double &b, const double &tolerance = DefaultTolerance) { return (abs(a - b) < tolerance); }

}// namespace optim
