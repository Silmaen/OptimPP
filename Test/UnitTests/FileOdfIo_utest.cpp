//
// Created by damien.lachouette on 26/03/2021.
//

#include <gtest/gtest.h>
#include <IO/FileOdfIo.h>
#include <base/Exception.h>

TEST(FileOdfIo, BaseChecks){
    std::shared_ptr<optim::mesh::MeshManager> mesh;
    optim::IO::FileOdfIo fileIo(mesh, std::filesystem::path());
    EXPECT_FALSE(fileIo.isFileValid());
    EXPECT_THROW(fileIo.readMeshFile(),optim::Exception);
    EXPECT_THROW(fileIo.writeMeshFile(),optim::Exception);

    optim::IO::FileOdfIo fileIo2(mesh, std::filesystem::path("toto.odf"));
    EXPECT_THROW(fileIo2.readMeshFile(),optim::Exception);

    mesh->createNode(1, 0., 0., 0.);
    mesh->createNode(3, 1., 0., 0.);
    mesh->createNode(2, 0., 1., 0.);
    mesh->createNode(4, 0., 0., 1.);
    mesh->createNode(7, { 0., 0., -1. });
    mesh->createElement(2, optim::mesh::ElementForm::TETRAHEDRON, optim::mesh::ElementOrder::LINEAR, { 1,2,3,4 });
    mesh->createElement(1, optim::mesh::ElementForm::TETRAHEDRON, optim::mesh::ElementOrder::LINEAR, { 1,2,3,7 });
    fileIo.writeMeshFile();
}
