//
// Created by damien.lachouette on 26/03/2021.
//

#pragma once
#include "BaseIo.h"

namespace optim::IO {
    /**
     * @brief class to handle ODF files
     *
     * OMF stand for Optim++ Data File
     */
    class FileOdfIo: public baseMeshIO {
    public:
        /**
         * @brief Constructor
         */
        FileOdfIo(shared_ptr<mesh::MeshManager> mesh,
                  const std::filesystem::path& filename
        ):baseMeshIO(mesh, filename){}

        /**
         * @brief read the file
         */
        void readMeshFile() override;
        /**
         * @brief write the file
         */
        void writeMeshFile() override;
    };
}
