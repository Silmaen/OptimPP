//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once
#include <cinttypes>

namespace optim
{

constexpr double DefaultTolerance = 1.e-7;

// base int types
// SIGNED INTEGERS
typedef int64_t  s64;  // -170 141 183 460 469 231 731 687 303 715 884 105 728 to 170 141 183 460 469 231 731 687 303 715 884 105 727
typedef int32_t  s32;  // -2 147 483 648 to 2 147 483 647
typedef int16_t  s16;  // -32 768 to 32 767
typedef int8_t   s8;   // -128 to 127
// UNSIGNED INTEGERS
typedef uint64_t u64;  // 0 to 340 282 366 920 938 463 463 374 607 431 768 211 455
typedef uint32_t u32;  // 0 to 4 294 967 295
typedef uint16_t u16;  // 0 to 65 535
typedef uint8_t  u8;   // 0 to 255

// ------------------------------------------ BASE FCT ------------------------------------------
// CLAMP
[[nodiscard]] inline s32 clamp(const s32& x, const s32& a, const s32& b) { return((x < a) ? a : ((x > b) ? b : x)); }
[[nodiscard]] inline float clamp(const float& x, const float& a, const float& b) { return((x < a) ? a : ((x > b) ? b : x)); }
[[nodiscard]] inline double clamp(const double& x, const double& a, const double& b) { return((x < a) ? a : ((x > b) ? b : x)); }
// SIGN
[[nodiscard]] inline s32 sign(const s32&x) { return(x < 0 ? -1 : ((x > 0) ? 1 : 0)); }
[[nodiscard]] inline float sign(const float&x) { return(x < 0 ? -1.0f : ((x > 0) ? 1.0f : 0.0f)); }
[[nodiscard]] inline double sign(const double&x) { return(x < 0 ? -1.0 : ((x > 0) ? 1.0 : 0.0)); }
// ABS
[[nodiscard]] inline s32 abs(const s32&x) { return(x < 0 ? -x : x); }
[[nodiscard]] inline float abs(const float& x) { return(x < 0 ? -x : x); }
[[nodiscard]] inline double abs(const double& x) { return(x < 0 ? -x : x); }
//MIN
[[nodiscard]] inline u8 min(const u8& a, const u8& b) { return((a > b) ? b : a); }
[[nodiscard]] inline u16 min(const u16& a, const u16& b) { return((a > b) ? b : a); }
[[nodiscard]] inline u32 min(const u32& a, const u32& b) { return((a > b) ? b : a); }
[[nodiscard]] inline u64 min(const u64& a, const u64& b) { return((a > b) ? b : a); }
[[nodiscard]] inline s32 min(const s32& a, const s32& b) { return((a > b) ? b : a); }
[[nodiscard]] inline s64 min(const s64& a, const s64& b) { return((a > b) ? b : a); }
[[nodiscard]] inline float min(const float& a, const  float& b) { return((a > b) ? b : a); }
[[nodiscard]] inline double min(const double& a, const  double& b) { return((a > b) ? b : a); }
//MAX
[[nodiscard]] inline u8 max(const u8& a, const u8& b) { return((a > b) ? a : b); }
[[nodiscard]] inline u16 max(const u16& a, const u16& b) { return((a > b) ? a : b); }
[[nodiscard]] inline u32 max(const u32& a, const u32& b) { return((a > b) ? a : b); }
[[nodiscard]] inline u64 max(const u64& a, const u64& b) { return((a > b) ? a : b); }
[[nodiscard]] inline s32 max(const s32& a, const s32& b) { return((a > b) ? a : b); }
[[nodiscard]] inline s64 max(const s64& a, const s64& b) { return((a > b) ? a : b); }
[[nodiscard]] inline float max(const float& a, const  float& b) { return((a > b) ? a : b); }
[[nodiscard]] inline double max(const double& a, const  double& b) { return((a > b) ? a : b); }
// Bits operations
inline void bitSet(u8& number, const u8& bit) { number |= 1ul << bit; }
inline void bitDefine(u8& number, const u8& bit, const bool& value) { number = (number&~(1UL << bit)) | (value << bit); }
inline void bitClear(u8& number, const u8& bit) { number &= ~(1ul << bit); }
inline void bitToggle(u8& number, const u8& bit) { number ^= 1ul << bit; }
[[nodiscard]] inline bool bitGet(const u8& number, const u8& bit) { return((number >> bit) & 1u); }
inline void bitSet(u64& number, const u8& bit) { number |= 1ull << bit; }
inline void bitDefine(u64& number, const u8& bit, const bool& value) { number = (number&~(1ull << bit)) | ((u64)value << bit); }
inline void bitClear(u64& number, const u8& bit) { number &= ~(1ull << bit); }
inline void bitToggle(u64& number, const u8& bit) { number ^= 1ull << bit; }
[[nodiscard]] inline bool bitGet(const u64& number, const u8& bit) { return((number >> bit) & 1ull); }

// float Equality
[[nodiscard]] inline bool isfNull(const float& a, const double& tolerance = DefaultTolerance) { return(abs(a) < tolerance); }
[[nodiscard]] inline bool isfNull(const double& a, const double& tolerance = DefaultTolerance) { return(abs(a) < tolerance); }
[[nodiscard]] inline bool isfEqual(const float& a, const float& b, const double& tolerance = DefaultTolerance) { return(abs(a - b) < tolerance); }
[[nodiscard]] inline bool isfEqual(const double& a, const double& b, const double& tolerance = DefaultTolerance) { return(abs(a - b) < tolerance); }

}