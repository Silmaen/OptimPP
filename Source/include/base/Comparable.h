//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once

namespace optim {
/**
 * @brief base template class for comparable item
 *
 * @tparam T the base object to make comparable
 *
 * this class rely on the existence of a member function 'Tie' that use the std::Tie
 */
template<class T>
class TieComparable {
private:
    /**
     * @brief return this class as its templated base class
     * @return this as the template Type
     */
    constexpr T const &Underlying() const { return static_cast<const T &>(*this); }
    TieComparable() = default;                               ///< default constructor
    ~TieComparable<T>() = default;                           ///< default destructor
    TieComparable<T>(const TieComparable<T> &) = default;    ///< default copy constructor
    TieComparable<T>(TieComparable<T> &&) noexcept = default;///< default move constructor

    /**
     * default copy affectation
     * @return this object
     */
    TieComparable<T> &operator=(const TieComparable<T> &) = default;
    /**
     * default move affectation
     * @return this object
     */
    TieComparable<T> &operator=(TieComparable<T> &&) noexcept = default;
    friend T;///< allow access to template
public:
    /**
     * @brief equality operator
     * @param[in] other the other object to compare
     * @return true if the objects are the same
     */
    [[nodiscard]] constexpr bool operator==(const T &other) const noexcept { return (Underlying().Tie() == other.Tie()); }
    /**
     * @brief inequality operator
     * @param[in] other the other object to compare
     * @return true if the objects are not the same
     */
    [[nodiscard]] constexpr bool operator!=(const T &other) const noexcept { return (Underlying().Tie() != other.Tie()); }
    /**
     * @brief greater operator
     * @param[in] other the other object to compare
     * @return true if the object is greater than this one
     */
    [[nodiscard]] constexpr bool operator<(const T &other) const noexcept { return (Underlying().Tie() < other.Tie()); }
    /**
     * @brief lesser operator
     * @param[in] other the other object to compare
     * @return true if the object lesser than this one
     */
    [[nodiscard]] constexpr bool operator>(const T &other) const noexcept { return (Underlying().Tie() > other.Tie()); }
    /**
     * @brief greater or equal operator
     * @param[in] other the other object to compare
     * @return true if the object greater or equal than this one
     */
    [[nodiscard]] constexpr bool operator>=(const T &other) const noexcept { return (Underlying().Tie() >= other.Tie()); }
    /**
     * @brief lesser or equal operator
     * @param[in] other the other object to compare
     * @return true if the object lesser or equal than this one
     */
    [[nodiscard]] constexpr bool operator<=(const T &other) const noexcept { return (Underlying().Tie() <= other.Tie()); }
};
/**
 * @brief base template class for comparable item
 *
 * @tparam T the base object to make comparable
 *
 * This class rely on the existence of a member operator<.
 *
 * This implementation is similar to @ref TieComparable but is easier to implement
 * especially for complex objects. The draw back is that this implementation is
 * slower for == and != (about 2 times slower).
 */
template<class T>
class [[maybe_unused]] InequalityComparable {
private:
    /**
   * @brief return this class as its templated base class
   * @return this as the template Type
   */
    constexpr T const &Underlying() const { return static_cast<const T &>(*this); }
    InequalityComparable() = default;                                ///< default constructor
    ~InequalityComparable<T>() = default;                            ///< default destructor
    InequalityComparable<T>(const InequalityComparable<T> &) = default;    ///< default copy constructor
    InequalityComparable<T>(InequalityComparable<T> &&) noexcept = default;///< default move constructor

    /**
   * default copy affectation
   * @return this object
   */
    InequalityComparable<T> &operator=(const InequalityComparable<T> &) = default;
    /**
   * default move affectation
   * @return this object
   */
    InequalityComparable<T> &operator=(InequalityComparable<T> &&) noexcept = default;
    friend T;///< allow access to template
public:
    /**
   * @brief equality operator
   * @param[in] other the other object to compare
   * @return true if the objects are the same
   */
    [[nodiscard]] constexpr bool operator==(const T &other) const noexcept { return Underlying() >= other && other >= Underlying(); }
    /**
   * @brief inequality operator
   * @param[in] other the other object to compare
   * @return true if the objects are not the same
   */
    [[nodiscard]] constexpr bool operator!=(const T &other) const noexcept { return (Underlying() < other) || (other < Underlying()); }
    /**
   * @brief lesser operator
   * @param[in] other the other object to compare
   * @return true if the object lesser than this one
   */
    [[nodiscard]] constexpr bool operator>(const T &other) const noexcept { return other < Underlying(); }
    /**
   * @brief greater or equal operator
   * @param[in] other the other object to compare
   * @return true if the object greater or equal than this one
   */
    [[nodiscard]] constexpr bool operator>=(const T &other) const noexcept { return Underlying() >= other; }
    /**
   * @brief lesser or equal operator
   * @param[in] other the other object to compare
   * @return true if the object lesser or equal than this one
   */
    [[nodiscard]] constexpr bool operator<=(const T &other) const noexcept { return other >= Underlying(); }
};
}// namespace optim
