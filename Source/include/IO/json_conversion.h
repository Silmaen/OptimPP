//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once
#include "base/Exception.h"
#include "mesh/MeshManager.h"

#include <json_safe_include.h>


namespace optim::IO::json {

using json = nlohmann::ordered_json;

/**
 * @brief generate the json for the given mesh
 * @param i_mesh the mesh to convert
 * @return a json file representing the MeshManager
 */
json toJSON(const mesh::MeshManager &i_mesh);

/**
 * @brief generate the json for the given mesh
 * @overload
 *
 * Will throw an null pointer Exception if the given node is null
 * @param mesh the mesh to convert
 * @return a json file representing the MeshManager
 */
inline json toJSON(const shared_ptr<mesh::MeshManager> &mesh) {
    if (!mesh)
        throw Exception(ExitCode::Value::NullPointerError);
    return toJSON(*mesh);
}

/**
 * @brief read a mesh from a json entity
 * @param j_str the json entity
 * @param i_mesh the mesh to populate (any content will be erased)
 */
void fromJSON(const json& j_str, mesh::MeshManager &i_mesh);


/**
 * @brief read a mesh from a json entity
 * @overload
 *
 * Will throw an null pointer Exception if the given node is null
 * @param j_str the json entity
 * @param mesh the mesh to populate (any content will be erased)
 */
inline void fromJSON(const json& j_str, shared_ptr<mesh::MeshManager> &mesh) {
    if (!mesh)
        throw Exception(ExitCode::Value::NullPointerError);
    return fromJSON(j_str, *mesh);
}

/**
 * @brief generate the json for the given node
 * @param node the node to convert
 * @return a json file representing the MeshNode
 */
inline json toJSON(const mesh::MeshNode &node) {
    return json{node.getID(), node.getCoords().getX(), node.getCoords().getY(), node.getCoords().getZ()};
}

/**
 * @brief generate the json for the given node
 * @overload
 *
 * Will throw an null pointer Exception if the given node is null
 * @param node the node to convert
 * @return a json file representing the MeshNode
 */
inline json toJSON(const shared_ptr<mesh::MeshNode> &node) {
    if (!node)
        throw Exception(ExitCode::Value::NullPointerError);
    return toJSON(*node);
}

/**
 * @brief generate the json for the given element
 * @param element the element to convert
 * @return a json file representing the MeshElement
 */
inline json toJSON(const mesh::MeshElement &element) {
    return json{element.getID(), element.getType(), element.getOrder(), element.getNodeIdList()};
}

/**
 * @brief generate the json for the given element
 * @overload
 *
 * Will throw an null pointer Exception if the given element is null
 * @param element the element to convert
 * @return a json file representing the MeshElement
 */
inline json toJSON(const shared_ptr<mesh::MeshElement> &element) {
    if (!element)
        throw Exception(ExitCode::Value::NullPointerError);
    return toJSON(*element);
}


}// namespace optim::IO::json
