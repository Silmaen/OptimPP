//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once

namespace optim
{
/**
 * @brief base template class for comparable item
 *
 * @tparam T the base object to make comparable
 *
 * this class rely on the existence of a member function 'CompareTo' in the template class T
 * this function should return negative value if 'other' is greater that 'this'
 * this function should return positive value if 'other' is lesser that 'this'
 * this function should return 0 value if 'other' is equal 'this'
 */
template<class T>
struct Comparable
{
    /**
     * @brief return this class as its templated base class
     * @return this as the template Type
     */
    constexpr T const& Underlying() const { return static_cast<const T&>(*this); }
    Comparable() = default; ///< default constructor
    ~Comparable<T>() = default; ///< default destructor
    Comparable<T>(const Comparable<T>&) = default; ///< default copy constructor
    Comparable<T>(Comparable<T>&&)noexcept = default; ///< default move constructor
    Comparable<T>& operator=(const Comparable<T>&) = default; ///< default copy affectation
    Comparable<T>& operator=(Comparable<T>&&)noexcept = default; ///< default move affectation
    /**
     * @brief equality operator
     * @param[in] other the other object to compare
     * @return true if the objects are the same
     */
    [[nodiscard]] constexpr bool operator==(const T& other) const noexcept { return(Underlying().CompareTo(other) == 0); }
    /**
     * @brief inequality operator
     * @param[in] other the other object to compare
     * @return true if the objects are not the same
     */
    [[nodiscard]] constexpr bool operator!=(const T& other) const noexcept { return(Underlying().CompareTo(other) != 0); }
    /**
     * @brief greater operator
     * @param[in] other the other object to compare
     * @return true if the object is greater than this one
     */
    [[nodiscard]] constexpr bool operator<(const T& other) const noexcept { return(Underlying().CompareTo(other) < 0); }
    /**
     * @brief lesser operator
     * @param[in] other the other object to compare
     * @return true if the object lesser than this one
     */
    [[nodiscard]] constexpr bool operator>(const T& other) const noexcept { return(Underlying().CompareTo(other) > 0); }
    /**
     * @brief greater or equal operator
     * @param[in] other the other object to compare
     * @return true if the object greater or equal than this one
     */
    [[nodiscard]] constexpr bool operator>=(const T& other) const noexcept { return(Underlying().CompareTo(other) >= 0); }
    /**
     * @brief lesser or equal operator
     * @param[in] other the other object to compare
     * @return true if the object lesser or equal than this one
     */
    [[nodiscard]] constexpr bool operator<=(const T& other) const noexcept { return(Underlying().CompareTo(other) <= 0); }
};

}
