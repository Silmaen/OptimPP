//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#include "mesh/MeshNode.h"
#include "base/Exception.h"

namespace optim::mesh {

bool MeshNode::isValid() const noexcept{
    try{
        checkValidity();
    }    catch(Exception & e){
        if(e.GetCode() == ExitCode::Value::OK)
            return true;
    }
    return false;
}

void MeshNode::checkValidity(bool AllThrow) const{
    if(meshManager == nullptr)
        throw Exception(ExitCode::Value::NoMeshManager);
    if (AllThrow)throw Exception(ExitCode::Value::OK);
}

}
