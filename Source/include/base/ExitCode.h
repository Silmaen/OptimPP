//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once

/**
 * @brief namespace gathering the ExitCodes management
 */
namespace optim::ExitCode
{
/**
 * @brief the definition of Exit codes
 */
enum struct Value
{
    OK,                ///< Code for a good execution
    OutOfBounds,       ///< Code for handling out of bounds exceptions
    ArithmeticError,   ///< Code for handling Aritmetic error exceptions

    GeneralError = 255, ///< Default Error Code (unknown error)
};

/**
 * @brief the list of error codes
 */
static constexpr Value ExitCodes[] = {
    Value::OK,
    Value::OutOfBounds,
    Value::ArithmeticError,
    Value::GeneralError,
};

/**
 * @brief convert Exit Code into string
 * @param[in] iErrorCode the ExitCode to convert
 * @return the string corresponding to the given ExitCode
 */
constexpr inline const char* ToString(Value iErrorCode)
{
    switch(iErrorCode)
    {
        case Value::OK:
            return "Ok";
        case Value::OutOfBounds:
            return "Out of Bounds";
        case Value::ArithmeticError:
            return "Arithmetic Error";
        case Value::GeneralError:
            return "General failure";
    }
    return "Unknown error";
}

}

