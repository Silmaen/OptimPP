//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#include "base/MathOperators.h"
#include "base/Exception.h"
#include <cmath>

namespace optim
{

[[nodiscard]] u8 sqrt(const u8& x)noexcept
{
    return static_cast<u8>(std::sqrt(x));
}

[[nodiscard]] u16 sqrt(const u16& x)noexcept
{
    return static_cast<u16>(std::sqrt(x));
}

[[nodiscard]] u32 sqrt(const u32& x)noexcept
{
    return static_cast<u32>(std::sqrt(x));
}

[[nodiscard]] u64 sqrt(const u64& x)noexcept
{
    return static_cast<u64>(std::sqrt(x));
}

[[nodiscard]] s8 sqrt(const s8& x)
{
    if(x < 0)
        throw Exception(ExitCode::Value::ArithmeticError);
    return static_cast<s8>(std::sqrt(x));
}

[[nodiscard]] s16 sqrt(const s16& x)
{
    if(x < 0)
        throw Exception(ExitCode::Value::ArithmeticError);
    return static_cast<s16>(std::sqrt(x));
}

[[nodiscard]] s32 sqrt(const s32& x)
{
    if(x < 0)
        throw Exception(ExitCode::Value::ArithmeticError);
    return static_cast<s32>(std::sqrt(x));
}

[[nodiscard]] s64 sqrt(const s64& x)
{
    if(x < 0)
        throw Exception(ExitCode::Value::ArithmeticError);
    return static_cast<s64>(std::sqrt(x));
}

[[nodiscard]] float sqrt(const float& x)
{
    if(x < 0)
        throw Exception(ExitCode::Value::ArithmeticError);
    return std::sqrt(x);
}

[[nodiscard]] double sqrt(const double& x)
{
    if(x < 0)
        throw Exception(ExitCode::Value::ArithmeticError);
    return std::sqrt(x);
}



// log2
#ifdef _MSC_VER
#include <intrin.h>
#endif
[[nodiscard]] u32 log2i(const u32& x)
{
#ifdef _MSC_VER
    unsigned long result;
    _BitScanReverse(&result, static_cast<u32>(x));
    return(result);
#else
    return(31u - static_cast<u32>(__builtin_clz(x)));
#endif
}

[[nodiscard]] float cos(const float& x) { return std::cos(x); }
[[nodiscard]] double cos(const double& x) { return std::cos(x); }
[[nodiscard]] float cosdeg(const float& x) { return std::cos(x*Deg2Radf); }
[[nodiscard]] double cosdeg(const double& x) { return std::cos(x*Deg2Rad); }
[[nodiscard]] float sin(const float& x) { return std::sin(x); }
[[nodiscard]] double sin(const double& x) { return std::sin(x); }
[[nodiscard]] float sindeg(const float& x) { return std::sin(x*Deg2Radf); }
[[nodiscard]] double sindeg(const double& x) { return std::sin(x*Deg2Rad); }

}

