//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#include "IO/FileOdfIo.h"
#include "IO/json_conversion.h"
#include "base/Exception.h"
#include <fstream>


namespace optim::IO {

bool baseMeshIO::isFileValid() {
    return !_filename.empty();
}


void FileOdfIo::readMeshFile() {
    if (getFilename().empty())
        throw Exception(ExitCode::Value::EmptyFileName);
    if (!std::filesystem::exists(getFilename()))
        throw Exception(ExitCode::Value::FileDoesNotExists);
    std::ifstream file_stream(getFilename(), std::ios::binary);
    if (!file_stream.is_open())
        throw Exception(ExitCode::Value::OpenFileFailed);
    vector<u8> v_bson;
    u8 read_byte = 0;
    while(file_stream.read(reinterpret_cast<char *>(&read_byte), 1))
        v_bson.push_back(read_byte);
    file_stream.close();
    json::fromJSON(nlohmann::json::from_bson(v_bson), *getMesh());

}

void FileOdfIo::writeMeshFile() {
    if (getFilename().empty())
        throw Exception(ExitCode::Value::EmptyFileName);
    std::ofstream file_stream(getFilename(), std::ios::out | std::ios::binary );
    if (!file_stream.is_open())
        throw Exception(ExitCode::Value::OpenFileFailed);
    vector<u8> v_bson = nlohmann::json::to_bson(json::toJSON(getMesh()));
    file_stream.write(reinterpret_cast<char*>(v_bson.data()), static_cast<std::streamsize>(v_bson.size()));
    // close the file
    file_stream.close();
}

}// namespace optim::IO
