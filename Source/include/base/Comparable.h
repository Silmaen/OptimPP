//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once

namespace optim
{
template<class T>
struct Comparable
{
    constexpr T const& Underlying() const { return static_cast<const T&>(*this); }
    Comparable() = default;
    ~Comparable<T>() = default;
    Comparable<T>(const Comparable<T>&) = default;
    Comparable<T>(Comparable<T>&&)noexcept = default;
    Comparable<T>& operator=(const Comparable<T>&) = default;
    Comparable<T>& operator=(Comparable<T>&&)noexcept = default;
    [[nodiscard]] constexpr bool operator==(const T& other) const noexcept { return(Underlying().CompareTo(other) == 0); }
    [[nodiscard]] constexpr bool operator!=(const T& other) const noexcept { return(Underlying().CompareTo(other) != 0); }
    [[nodiscard]] constexpr bool operator<(const T& other) const noexcept { return(Underlying().CompareTo(other) < 0); }
    [[nodiscard]] constexpr bool operator>(const T& other) const noexcept { return(Underlying().CompareTo(other) > 0); }
    [[nodiscard]] constexpr bool operator>=(const T& other) const noexcept { return(Underlying().CompareTo(other) >= 0); }
    [[nodiscard]] constexpr bool operator<=(const T& other) const noexcept { return(Underlying().CompareTo(other) <= 0); }
};
}