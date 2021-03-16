//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#include "base/vector3.h"
#include "base/Exception.h"

namespace optim::base{

std::ostream & Vector3::dump(std::ostream & os) const noexcept{
    os << m_data[0] << " " << m_data[1] << " " << m_data[2];
    return os;
}

double & Vector3::at(u8 i){
    if(i > 2)
        throw Exception(ExitCode::Value::OutOfBounds);
    return m_data[i];
}

const double & Vector3::at(u8 i)const{
    if(i > 2)
        throw Exception(ExitCode::Value::OutOfBounds);
    return m_data[i];
}

void Vector3::set(u8 i,double value){
    if(i > 2)
        throw Exception(ExitCode::Value::OutOfBounds);
    m_data[i] = value;
}

Vector3& Vector3::operator/=(const double& o){
    if(isfNull(o))
        throw Exception(ExitCode::Value::ArithmeticError);
    m_data[0] /= o; m_data[1] /= o; m_data[2] /= o; return *this;
}

Vector3 Vector3::operator/(const double& o)const{
    Vector3 t(*this); t /= o; return t;
}

std::ostream& operator<<(std::ostream& os, const Vector3& v){
    return v.dump(os);
}

}

