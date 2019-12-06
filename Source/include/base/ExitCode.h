//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once

#include "type.h"

/**
 * @namespace optim::ExitCode
 * @brief namespace gathering the ExitCodes management
 */
namespace optim::ExitCode
{
    /**
     * @brief the definition of Exit codes
     */
    enum struct Value
    {
        OK = 0,                ///< Code for a good execution
        OutOfBounds,       ///< Code for handling out of bounds exceptions
        ArithmeticError,   ///< Code for handling Aritmetic error exceptions

        GeneralError ///< Default Error Code (unknown error)
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
    inline const string ToString(Value iErrorCode)
    {
        string a;
        switch (iErrorCode) {
        case Value::OK:
            a = "OK";
            break;
        case Value::OutOfBounds:
            a = "Out Of Bounds";
            break;
        case Value::ArithmeticError:
            a = "Arithmetic Error";
            break;
        case Value::GeneralError:
            a = "General Error";
            break;
        }
        a = "Unknown error";
        return a;
    }

}

