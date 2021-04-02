//
// Created by damien.lachouette on 26/03/2021.
//

#include "IO/FileOdfIo.h"
#include "base/Exception.h"
#include <fstream>
#include "IO/json_conversion.h"

using json = nlohmann::json;

namespace optim::IO {

    bool baseMeshIO::isFileValid(){
        return !_filename.empty();
    }


    void FileOdfIo::readMeshFile() {
        if (_filename.empty())
            throw Exception(ExitCode::Value::EmptyFileName);
        if (!std::filesystem::exists(_filename))
            throw Exception(ExitCode::Value::FileDoesNotExists);
        std::ofstream file_stream;
        file_stream.open(_filename, std::ios::in);
        if (!file_stream.is_open())
            throw Exception(ExitCode::Value::OpenFileFailed);



        // close the file
        file_stream.close();
    }

    void FileOdfIo::writeMeshFile() {
        if (_filename.empty())
            throw Exception(ExitCode::Value::EmptyFileName);
        std::ofstream file_stream;

        // convert to json
        json::json j_file;
        j_file["general"]["nb_nodes"] = _mesh->getNbNodes();
        j_file["general"]["nb_elements"] = _mesh->getNbElements();

        for(auto node=_mesh->getNodeBegin(); node != _mesh->getNodeEnd(); ++node){
            j_file["nodes"].emplace_back((*node));
        }
        for(auto element=_mesh->getElementBegin(); element!=_mesh->getElementEnd(); ++element){
            j_file["elements"].emplace_back((*element)->toJSON());
        }

        file_stream.open(_filename, std::ios::out);
        if (!file_stream.is_open())
            throw Exception(ExitCode::Value::OpenFileFailed);

        for(auto element=_mesh->getElementBegin(); element!=_mesh->getElementEnd(); ++element){
            file_stream << element->get()->getID() << " " << element->get() << std::endl;
        }
        // close the file
        file_stream.close();
    }

}
