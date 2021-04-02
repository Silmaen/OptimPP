//
// Created by damien.lachouette on 02/04/2021.
//

#pragma once
#include <json.hpp>
#include "mesh/MeshManager.h"
#include "base/Exception.h"

namespace optim::IO::json {

    using json = nlohmann::json;

    /**
     * @brief generate the json for the given mesh
     * @param mesh the mesh to convert
     * @return a json file representing the MeshManager
     */
    json toJSON(const mesh::MeshManager& mesh);

    /**
     * @brief generate the json for the given mesh
     * @overload
     *
     * Will throw an null pointer Exception if the given node is null
     * @param mesh the mesh to convert
     * @return a json file representing the MeshManager
     */
    json toJSON(const shared_ptr<mesh::MeshManager>& mesh){
        if (!mesh)
            throw Exception(ExitCode::Value::NullPointerError);
        return toJSON(*mesh);
    }

    /**
     * @brief generate the json for the given node
     * @param node the node to convert
     * @return a json file representing the MeshNode
     */
    json toJSON(const mesh::MeshNode& node){
        return json{{node.getID(), node.getX(), node.getY(), node.getZ()}};
    }

    /**
     * @brief generate the json for the given node
     * @overload
     *
     * Will throw an null pointer Exception if the given node is null
     * @param node the node to convert
     * @return a json file representing the MeshNode
     */
    json toJSON(const shared_ptr<mesh::MeshNode>& node){
        if (!node)
            throw Exception(ExitCode::Value::NullPointerError);
        return toJSON(*node);
    }

}
//%%% STOP %%%