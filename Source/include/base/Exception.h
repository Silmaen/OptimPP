//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once

#include "ExitCode.h"

namespace optim
{

 /**
  * @brief class for handling exceptions
  */
class Exception
{
public:
    /**
     * @brief Constructor by ExitCode
     * @param[in] iErrCode the error code to initialize
     *
     * the message is deduce from the ExitCode
     */
//    inline Exception(ExitCode::Value iErrCode) : m_ErrorCode{ iErrCode }, m_Message(ToString(iErrCode)) {}
    inline Exception(ExitCode::Value iErrCode) : m_ErrorCode{ iErrCode } {}

    /**
     * @brief retrieve the ExitCode
     * @return the ExitCode
     */
    inline ExitCode::Value GetCode()const noexcept { return m_ErrorCode; }
    /**
     * @brief retrieve the message
     * @return the message associated with Exception
     */
    inline string what()const noexcept { return ExitCode::ToString(m_ErrorCode); }
private:
    ExitCode::Value m_ErrorCode; ///< the exit/error code 
};

}

