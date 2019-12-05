//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once

#include <string>
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
    inline Exception(ExitCode::Value iErrCode) :  m_ErrorCode(iErrCode), m_Message(ToString(iErrCode)) {}
    /**
     * @brief Constructor by message
     * @param[in] iMessage the message
     *
     * the ExitCode is then defaulted to 'GeneralError'
     */
    inline Exception(const std::string& iMessage) : m_ErrorCode(ExitCode::Value::GeneralError), m_Message(iMessage) {}

    /**
     * @brief retrieve the ExitCode
     * @return the ExitCode
     */
    inline ExitCode::Value GetCode()const { return m_ErrorCode; }
    /**
     * @brief retrieve the message
     * @return the message associated with Exception
     */
    inline const std::string& what()const { return m_Message; }
private:
    ExitCode::Value m_ErrorCode; ///< the exit/error code 
    std::string m_Message; ///< the associated message
};

}

