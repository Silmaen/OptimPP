//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once
#include <cinttypes>

/**
 * @brief namesapce of the whole project
 */
namespace optim
{

constexpr double DefaultTolerance = 1.e-7; ///< default tolerence for double comparison
constexpr float DefaultfTolerance = static_cast<float>(1.e-7); ///< default tolerence for float comparison

// base int types
// SIGNED INTEGERS
/// @brief signed 64bit integer 
typedef int64_t  s64;  // -170 141 183 460 469 231 731 687 303 715 884 105 728 to 170 141 183 460 469 231 731 687 303 715 884 105 727
/// @brief signed 32bit integer 
typedef int32_t  s32;  // -2 147 483 648 to 2 147 483 647
/// @brief signed 16bit integer 
typedef int16_t  s16;  // -32 768 to 32 767
/// @brief signed 8bit integer 
typedef int8_t   s8;   // -128 to 127
// UNSIGNED INTEGERS
/// @brief unsigned 64bit integer 
typedef uint64_t u64;  // 0 to 340 282 366 920 938 463 463 374 607 431 768 211 455
/// @brief unsigned 32bit integer 
typedef uint32_t u32;  // 0 to 4 294 967 295
/// @brief unsigned 16bit integer 
typedef uint16_t u16;  // 0 to 65 535
/// @brief unsigned 8bit integer 
typedef uint8_t  u8;   // 0 to 255

// ------------------------------------------ BASE FCT ------------------------------------------
// CLAMP
/**
 * @brief compute the value of x clamped between [a,b]
 * @param[in] x the value to clamp
 * @param[in] a the lower value of the clamp interval
 * @param[in] b the upper value of the clamp interval
 * @return a if x<a, b if x>b else x
 */
[[nodiscard]] inline s32 clamp(const s32& x, const s32& a, const s32& b) { return((x < a) ? a : ((x > b) ? b : x)); }
/**
 * @overload
 * @param[in] x the value to clamp
 * @param[in] a the lower value of the clamp interval
 * @param[in] b the upper value of the clamp interval
 * @return a if x<a, b if x>b else x
 */
[[nodiscard]] inline float clamp(const float& x, const float& a, const float& b) { return((x < a) ? a : ((x > b) ? b : x)); }
/**
 * @overload
 * @param[in] x the value to clamp
 * @param[in] a the lower value of the clamp interval
 * @param[in] b the upper value of the clamp interval
 * @return a if x<a, b if x>b else x
 */
[[nodiscard]] inline double clamp(const double& x, const double& a, const double& b) { return((x < a) ? a : ((x > b) ? b : x)); }
// SIGN
/**
 * @brief compute the sign of x
 * @param[in] x the value to sign
 * @return -1 if x<0, 1 if x>0 else 0
 */
[[nodiscard]] inline s32 sign(const s32&x) { return(x < 0 ? -1 : ((x > 0) ? 1 : 0)); }
/**
 * @overload
 * @param[in] x the value to sign
 * @return -1 if x<0, 1 if x>0 else 0
 */
[[nodiscard]] inline float sign(const float&x) { return(x < 0 ? -1.0f : ((x > 0) ? 1.0f : 0.0f)); }
/**
 * @overload
 * @param[in] x the value to sign
 * @return -1 if x<0, 1 if x>0 else 0
 */
[[nodiscard]] inline double sign(const double&x) { return(x < 0 ? -1.0 : ((x > 0) ? 1.0 : 0.0)); }
// ABS
/**
 * @brief compute the absolute value of x
 * @param[in] x the value to abs
 * @return -x if x<0, else x
 */
[[nodiscard]] inline s32 abs(const s32&x) { return(x < 0 ? -x : x); }
/**
 * @overload
 * @param[in] x the value to abs
 * @return -x if x<0, else x
 */
[[nodiscard]] inline float abs(const float& x) { return(x < 0 ? -x : x); }
/**
 * @overload
 * @param[in] x the value to abs
 * @return -x if x<0, else x
 */
[[nodiscard]] inline double abs(const double& x) { return(x < 0 ? -x : x); }
//MIN
/**
 * @brief get the lesser of two nuimbers
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a<b else b
 */
[[nodiscard]] inline u8 min(const u8& a, const u8& b) { return((a > b) ? b : a); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a<b else b
 */
[[nodiscard]] inline u16 min(const u16& a, const u16& b) { return((a > b) ? b : a); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a<b else b
 */
[[nodiscard]] inline u32 min(const u32& a, const u32& b) { return((a > b) ? b : a); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a<b else b
 */
[[nodiscard]] inline u64 min(const u64& a, const u64& b) { return((a > b) ? b : a); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a<b else b
 */
[[nodiscard]] inline s32 min(const s32& a, const s32& b) { return((a > b) ? b : a); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a<b else b
 */
[[nodiscard]] inline s64 min(const s64& a, const s64& b) { return((a > b) ? b : a); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a<b else b
 */
[[nodiscard]] inline float min(const float& a, const  float& b) { return((a > b) ? b : a); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a<b else b
 */
[[nodiscard]] inline double min(const double& a, const  double& b) { return((a > b) ? b : a); } 
//MAX
/**
 * @brief get the greater of two nuimbers
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a>b else b
 */
[[nodiscard]] inline u8 max(const u8& a, const u8& b) { return((a > b) ? a : b); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a>b else b
 */
[[nodiscard]] inline u16 max(const u16& a, const u16& b) { return((a > b) ? a : b); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a>b else b
 */
[[nodiscard]] inline u32 max(const u32& a, const u32& b) { return((a > b) ? a : b); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a>b else b
 */
[[nodiscard]] inline u64 max(const u64& a, const u64& b) { return((a > b) ? a : b); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a>b else b
 */
[[nodiscard]] inline s32 max(const s32& a, const s32& b) { return((a > b) ? a : b); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a>b else b
 */
[[nodiscard]] inline s64 max(const s64& a, const s64& b) { return((a > b) ? a : b); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a>b else b
 */
[[nodiscard]] inline float max(const float& a, const  float& b) { return((a > b) ? a : b); }
/**
 * @overload
 * @param[in] a the first number to test
 * @param[in] b the second number to test
 * @return a if a>b else b
 */
[[nodiscard]] inline double max(const double& a, const  double& b) { return((a > b) ? a : b); }
// Bits operations
/**
 * @brief set a bit in number
 * @param[inout] number the number where to set the bit
 * @param[in] bit the index of the bit to set
 */
inline void bitSet(u8& number, const u8& bit) { number |= 1ul << bit; }
/**
 * @brief define the value of a bit in number
 * @param[inout] number the number where to set the bit
 * @param[in] bit the index of the bit to set
 * @param[in] value the value of the bit to set
 */
inline void bitDefine(u8& number, const u8& bit, const bool& value) { number = static_cast<u8>((number&~(static_cast<u8>(1U) << bit)) | (static_cast<u8>(value) << bit)); }
/**
 * @brief clear a bit in number
 * @param[inout] number the number where to clear the bit
 * @param[in] bit the index of the bit to clear
 */
inline void bitClear(u8& number, const u8& bit) { number &= ~(1ul << bit); }
/**
 * @brief toggle a bit in number
 * @param[inout] number the number where to toggle the bit
 * @param[in] bit the index of the bit to toggle
 */
inline void bitToggle(u8& number, const u8& bit) { number ^= 1ul << bit; }
/**
 * @brief get a bit in number
 * @param[inout] number the number where to get the bit
 * @param[in] bit the index of the bit to get
 * @return the value of the bit
 */
[[nodiscard]] inline bool bitGet(const u8& number, const u8& bit) { return((number >> bit) & 1u); }
/**
 * @overload
 * @param[inout] number the number where to set the bit
 * @param[in] bit the index of the bit to set
 */
inline void bitSet(u64& number, const u8& bit) { number |= 1ull << bit; }
/**
 * @overload
 * @param[inout] number the number where to set the bit
 * @param[in] bit the index of the bit to set
 * @param[in] value the value of the bit to set
 */
inline void bitDefine(u64& number, const u8& bit, const bool& value) { number = (number&~(1ull << bit)) | (static_cast<u64>(value) << bit); }
/**
 * @overload
 * @param[inout] number the number where to clear the bit
 * @param[in] bit the index of the bit to clear
 */
inline void bitClear(u64& number, const u8& bit) { number &= ~(1ull << bit); }
/**
 * @overload
 * @param[inout] number the number where to toggle the bit
 * @param[in] bit the index of the bit to toggle
 */
inline void bitToggle(u64& number, const u8& bit) { number ^= 1ull << bit; }
/**
 * @overload
 * @param[inout] number the number where to get the bit
 * @param[in] bit the index of the bit to get
 * @return the value of the bit
 */
[[nodiscard]] inline bool bitGet(const u64& number, const u8& bit) { return((number >> bit) & 1ull); }

// float Equality
/**
 * @brief test if the given real number is null (with the given tolerence)
 * @param[in] a the real number to test
 * @param[in] tolerance the asolute value of tolerance for comparison
 * @return true if a is closer to 0 than tolerance
 */
[[nodiscard]] inline bool isfNull(const float& a, const float& tolerance = DefaultfTolerance) { return(abs(a) < tolerance); }
/**
 * @overload
 * @param[in] a the real number to test
 * @param[in] tolerance the asolute value of tolerance for comparison
 * @return true if a is closer to 0 than tolerance
 */
[[nodiscard]] inline bool isfNull(const double& a, const double& tolerance = DefaultTolerance) { return(abs(a) < tolerance); }
/**
 * @brief test if the given real numbers are equal (closer than the given tolerence)
 * @param[in] a the first real number to test
 * @param[in] b the second real number to test
 * @param[in] tolerance the asolute value of tolerance for comparison
 * @return true if a is closer to b than tolerance
 */
[[nodiscard]] inline bool isfEqual(const float& a, const float& b, const float& tolerance = DefaultfTolerance) { return(abs(a - b) < tolerance); }
/**
 * @overload
 * @param[in] a the first real number to test
 * @param[in] b the second real number to test
 * @param[in] tolerance the asolute value of tolerance for comparison
 * @return true if a is closer to b than tolerance
 */
[[nodiscard]] inline bool isfEqual(const double& a, const double& b, const double& tolerance = DefaultTolerance) { return(abs(a - b) < tolerance); }

}

