//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once

#include <string>
#include "ExitCode.h"

namespace optim
{

class Exception
{
public:
    inline Exception(ExitCode::Value iErrCode) : m_Message(ToString(iErrCode)),m_ErrorCode(iErrCode) {}
    inline Exception(const std::string& iMessage) : m_Message(iMessage), m_ErrorCode(ExitCode::Value::GeneralError) {}

    inline ExitCode::Value GetCode()const { return m_ErrorCode; }
    inline const std::string& what()const { return m_Message; }
private:
    std::string m_Message;
    ExitCode::Value m_ErrorCode;
};

}

