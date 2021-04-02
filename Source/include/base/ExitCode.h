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

        // operations
        OutOfBounds,       ///< Code for handling out of bounds exceptions
        ArithmeticError,   ///< Code for handling Arithmetic error exceptions
        NullPointerError,   ///< Code for handling Arithmetic error exceptions

        // elements invalidity
        NoMeshManager,   ///< code for not existence of the MeshManager
        WrongNodeNumber, ///< the element has the wrong number of points
        WrongNodeId, ///< the element refers to an invalid node Id

        // file Io invalidity
        EmptyFileName, ///< the given file name is empty
        FileDoesNotExists, ///< the file does not exists for reading
        OpenFileFailed, ///< the opening of the file failed

        GeneralError ///< Default Error Code (unknown error)
    };

    /**
     * @brief the list of error codes
     */
    static constexpr Value ExitCodes[] = {
        Value::OK,
        Value::OutOfBounds,
        Value::ArithmeticError,
        Value::NullPointerError,
        Value::NoMeshManager,
        Value::WrongNodeNumber,
        Value::WrongNodeId,
        Value::EmptyFileName,
        Value::FileDoesNotExists,
        Value::OpenFileFailed,
        Value::GeneralError,
    };

    /**
     * @brief convert Exit Code into string
     * @param[in] iErrorCode the ExitCode to convert
     * @return the string corresponding to the given ExitCode
     */
    inline const char* ToString(Value iErrorCode)
    {
        switch (iErrorCode) {
        case Value::OK:
            return "OK";
        // ------------------------------------------
        // operations
        case Value::OutOfBounds:
            return "Out Of Bounds";
        case Value::ArithmeticError:
            return "Arithmetic Error";
        case Value::NullPointerError:
            return "Null pointer Error";
        // ------------------------------------------
        // elements invalidity
            case Value::NoMeshManager:
            return "No Mesh Manager Defined";
        case Value::WrongNodeNumber:
            return "Wrong Node Number";
        case Value::WrongNodeId:
            return "Wrong Node Id";
        // ------------------------------------------
        // file Io invalidity
        case Value::EmptyFileName:
            return "File name is Empty";
        case Value::FileDoesNotExists:
            return "File does not exists";
        case Value::OpenFileFailed:
            return "Failed to open file";
        // ------------------------------------------
        // general
        case Value::GeneralError:
            return "General Error";
        }
        return "Unknown error";
    }

}

