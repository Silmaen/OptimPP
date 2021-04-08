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
     * @brief Constructor
     * @param mesh the reference mesh
     * @param filename the file name
     */
    baseMeshIO(
            std::shared_ptr<mesh::MeshManager> mesh,
            std::filesystem::path  filename
            ): _mesh{std::move(mesh)}, _filename{std::move(filename)} {}

    /**
     * @brief virtual dtor
     */
    virtual ~baseMeshIO() = default;
    /**
     * @brief copy ctor
     */
    baseMeshIO(const baseMeshIO&) = default;
    /**
     * @brief move ctor
     */
    baseMeshIO(baseMeshIO&&) = default;
    /**
     * @brief copy assignment
     * @return this instance
     */
    baseMeshIO& operator=(const baseMeshIO&) = default;
    /**
     * @brief move assignment
     * @return this instance
     */
    baseMeshIO& operator=(baseMeshIO&&) = default;

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
     * @brief access to the mesh element
     * @return the mesh component
     */
    shared_ptr<mesh::MeshManager>& getMesh(){return _mesh;}

    /**
     * @brief access to the file name
     * @return the filename
     */
    std::filesystem::path& getFilename(){return _filename;}
private:
    /**
     * @brief default constructor as private
     */
    baseMeshIO() = default;
    shared_ptr<mesh::MeshManager> _mesh; ///< pointer to the mesh
    std::filesystem::path _filename; ///< the file path
};

} // namespace optim::IO
