//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once

namespace optim::ExitCode
{
enum struct Value
{
    OK,
    OutOfBounds,
    ArithmeticError,

    GeneralError = 255,
};

static constexpr Value ExitCodes[] = {
    Value::OK,
    Value::OutOfBounds,
    Value::ArithmeticError,
    Value::GeneralError,
};

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
        default:
            return "Unknown error";
    }
}

}