//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#include "base/MathOperators.h"
#include "base/Exception.h"
#include <cmath>
#include <intrin.h>

namespace optim
{

[[nodiscard]] u8 sqrt(const u8& x)noexcept { return std::sqrt(x); }
[[nodiscard]] u16 sqrt(const u16& x)noexcept { return std::sqrt(x); }
[[nodiscard]] u32 sqrt(const u32& x)noexcept { return std::sqrt(x); }
[[nodiscard]] u64 sqrt(const u64& x)noexcept { return std::sqrt(x); }
[[nodiscard]] s8 sqrt(const s8& x) { if(x < 0)throw Exception(ExitCode::Value::ArithmeticError); return std::sqrt(x); }
[[nodiscard]] s16 sqrt(const s16& x) { if(x < 0)throw Exception(ExitCode::Value::ArithmeticError); return std::sqrt(x); }
[[nodiscard]] s32 sqrt(const s32& x) { if(x < 0)throw Exception(ExitCode::Value::ArithmeticError); return std::sqrt(x); }
[[nodiscard]] s64 sqrt(const s64& x) { if(x < 0)throw Exception(ExitCode::Value::ArithmeticError); return std::sqrt(x); }
[[nodiscard]] float sqrt(const float& x) { if(x < 0)throw Exception(ExitCode::Value::ArithmeticError); return std::sqrt(x); }
[[nodiscard]] double sqrt(const double& x) { if(x < 0)throw Exception(ExitCode::Value::ArithmeticError); return std::sqrt(x); }



// log2
[[nodiscard]] u32 log2i(const u32& x)
{
#ifdef _MSC_VER
    unsigned long result;
    _BitScanReverse(&result, static_cast<u32>(x));
    return(result);
#else
    return(32 - __builtin_clz(x));
#endif
}
}