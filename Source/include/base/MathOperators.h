//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once

#include "type.h"

namespace optim
{
// SQRT 
[[nodiscard]] u8 sqrt(const u8&)noexcept;
[[nodiscard]] u16 sqrt(const u16&)noexcept;
[[nodiscard]] u32 sqrt(const u32&)noexcept;
[[nodiscard]] u64 sqrt(const u64&)noexcept;
[[nodiscard]] s8 sqrt(const s8&);
[[nodiscard]] s16 sqrt(const s16&);
[[nodiscard]] s32 sqrt(const s32&);
[[nodiscard]] s64 sqrt(const s64&);
[[nodiscard]] float sqrt(const float&);
[[nodiscard]] double sqrt(const double&);

// log2
[[nodiscard]] u32 log2i(const u32& x);

}

