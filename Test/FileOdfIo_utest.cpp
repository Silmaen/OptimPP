//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <IO/FileOdfIo.h>
#include <base/Exception.h>
#include <IO/json_conversion.h>

using namespace optim::IO;
using namespace optim::mesh;

TEST(FileOdfIo, JSONGeneratorError) {
    std::shared_ptr<optim::mesh::MeshManager> mesh = nullptr;
    EXPECT_THROW(json::toJSON(mesh), optim::Exception);
    std::shared_ptr<optim::mesh::MeshElement> element = nullptr;
    EXPECT_THROW(json::toJSON(element), optim::Exception);
    std::shared_ptr<optim::mesh::MeshNode> node = nullptr;
    EXPECT_THROW(json::toJSON(node), optim::Exception);
}

TEST(FileOdfIo, ErrorChecks) {
    std::shared_ptr<optim::mesh::MeshManager> mesh = std::make_shared<optim::mesh::MeshManager>();
    optim::IO::FileOdfIo fileIo(mesh, std::filesystem::path());
    EXPECT_FALSE(fileIo.isFileValid());
    EXPECT_THROW(fileIo.readMeshFile(), optim::Exception);
    EXPECT_THROW(fileIo.writeMeshFile(), optim::Exception);

    optim::IO::FileOdfIo fileIo2(mesh, std::filesystem::path("toto.odf"));
    EXPECT_THROW(fileIo2.readMeshFile(), optim::Exception);
}

TEST(FileOdfIo, baseJSONChecks){
    std::shared_ptr<optim::mesh::MeshManager> mesh = std::make_shared<optim::mesh::MeshManager>();
    mesh->createNode(1, 0., 0., 0.);
    mesh->createNode(3, 1., 0., 0.);
    mesh->createNode(2, 0., 1., 0.);
    mesh->createNode(4, 0., 0., 1.);
    mesh->createNode(7, { 0., 0., -1. });
    mesh->createElement(2, optim::mesh::ElementForm::TETRAHEDRON, optim::mesh::ElementOrder::LINEAR, { 1,2,3,4 });
    mesh->createElement(1, optim::mesh::ElementForm::TETRAHEDRON, optim::mesh::ElementOrder::LINEAR, { 1,2,3,7 });

    auto j_node = optim::IO::json::toJSON(mesh->getNodeByID(2));
    EXPECT_STREQ(j_node.dump().c_str(), "[2,0.0,1.0,0.0]");
    auto j_element = optim::IO::json::toJSON(mesh->getElementByID(2));
    EXPECT_STREQ(j_element.dump().c_str(), "[2,5,1,[1,2,3,4]]");

    auto j_mesh = optim::IO::json::toJSON(mesh);
    EXPECT_STREQ(j_mesh.dump().c_str(), "{\"general\":{\"nb nodes\":5,\"nb elements\":2},\"nodes\":[[1,0.0,0.0,0.0],[3,1.0,0.0,0.0],[2,0.0,1.0,0.0],[4,0.0,0.0,1.0],[7,0.0,0.0,-1.0]],\"elements\":[[2,5,1,[1,2,3,4]],[1,5,1,[1,2,3,7]]]}");
}

TEST(FileOdfIo, FileIOChecks){
    std::shared_ptr<optim::mesh::MeshManager> mesh = std::make_shared<optim::mesh::MeshManager>();
    mesh->createNode(1, 0., 0., 0.);
    mesh->createNode(3, 1., 0., 0.);
    mesh->createNode(2, 0., 1., 0.);
    mesh->createNode(4, 0., 0., 1.);
    mesh->createNode(7, { 0., 0., -1. });
    mesh->createElement(2, optim::mesh::ElementForm::TETRAHEDRON, optim::mesh::ElementOrder::LINEAR, { 1,2,3,4 });
    mesh->createElement(1, optim::mesh::ElementForm::TETRAHEDRON, optim::mesh::ElementOrder::LINEAR, { 1,2,3,7 });
    optim::IO::FileOdfIo fileIo(mesh, std::filesystem::path("toto.odf"));

    fileIo.writeMeshFile();
    std::shared_ptr<optim::mesh::MeshManager> mesh2 = std::make_shared<optim::mesh::MeshManager>();
    optim::IO::FileOdfIo fileIo2(mesh2, std::filesystem::path("toto.odf"));
    fileIo2.readMeshFile();
    EXPECT_EQ(*mesh, *mesh2);
    // destroy utest file
    std::filesystem::remove(std::filesystem::path("toto.odf"));
}
