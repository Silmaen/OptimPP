//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#include "IO/json_conversion.h"

namespace optim::IO::json {

json toJSON(const mesh::MeshManager &i_mesh) {
    json j;
    j["general"] = {
            {"nb nodes", i_mesh.getNbNodes()},
            {"nb elements", i_mesh.getNbElements()},
    };
    for (auto node = i_mesh.getNodeBegin(); node != i_mesh.getNodeEnd(); ++node) {
        j["nodes"].push_back(toJSON(*node));
    }
    for (auto element = i_mesh.getElementBegin(); element != i_mesh.getElementEnd(); ++element) {
        j["elements"].push_back(toJSON(*element));
    }
    return j;
}

void fromJSON(const json& j_str, mesh::MeshManager &i_mesh){
    i_mesh.clear();
    for(auto  i_a:j_str.at("nodes"))
        i_mesh.createNode(i_a[0],i_a[1],i_a[2],i_a[3]);
    for(auto  i_a:j_str.at("elements"))
        i_mesh.createElement(i_a[0], i_a[1], i_a[2], i_a[3]);
}

}// namespace optim::IO::json
