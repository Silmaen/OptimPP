//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once

#include "mesh/MeshManager.h"
#include <filesystem>
#include <utility>

/**
 * @namespace optim::IO
 * @brief namespace gathering the file IO stuffs
 */
namespace optim::IO {

/**
 * @brief base class for Mesh IO support
 */
class baseMeshIO {
public:
    /**
     * @brief constructor
     */
    baseMeshIO(
            std::shared_ptr<mesh::MeshManager> mesh,
            std::filesystem::path  filename
            ): _mesh{std::move(mesh)}, _filename{std::move(filename)} {}

    /**
     * @brief read the file
     */
    virtual void readMeshFile()=0;
    /**
     * @brief write the file
     */
    virtual void writeMeshFile()=0;
    /**
     * @brief check the file validity
     * @return true if the file is valid
     */
    virtual bool isFileValid();

    /**
     * @brief acces to the mesh element
     * @return the mesh component
     */
    shared_ptr<mesh::MeshManager> getMesh(){return _mesh;}

    /**
     * @brief access to the file name
     * @return the filename
     */
    std::filesystem::path getFilename(){return _filename;}
private:
    shared_ptr<mesh::MeshManager> _mesh; ///< pointer to the mesh
    std::filesystem::path _filename; ///< the file path
};

} // namespace optim::IO
