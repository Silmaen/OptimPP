//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#include <base/Exception.h>
#include <gtest/gtest.h>
#include <mesh/MeshManager.h>

using namespace optim::mesh;

TEST(MeshElement, TheoreticalNodeNumber) {
    // special
    EXPECT_EQ(getTheoreticalElementNodeNumber(ElementForm::VOID, ElementOrder::NONE), -1);                 // free node number
    EXPECT_EQ(getTheoreticalElementNodeNumber(ElementForm::VOID, static_cast<ElementOrder>(666)), -1);     // out of bounds
    EXPECT_EQ(getTheoreticalElementNodeNumber(static_cast<ElementForm>(666), ElementOrder::LINEAR), -1);   // out of bounds
    EXPECT_EQ(getTheoreticalElementNodeNumber(static_cast<ElementForm>(666), ElementOrder::QUADRATIC), -1);// out of bounds
    // void
    EXPECT_EQ(getTheoreticalElementNodeNumber(ElementForm::VOID, ElementOrder::LINEAR), 0);   // Void has no node
    EXPECT_EQ(getTheoreticalElementNodeNumber(ElementForm::VOID, ElementOrder::QUADRATIC), 0);// Void has no node
    // 1D
    EXPECT_EQ(getTheoreticalElementNodeNumber(ElementForm::BAR, ElementOrder::LINEAR), 2);   // 1D bar has 2 nodes
    EXPECT_EQ(getTheoreticalElementNodeNumber(ElementForm::BAR, ElementOrder::QUADRATIC), 3);// 1D quad bar has 3 nodes
    // 2D
    EXPECT_EQ(getTheoreticalElementNodeNumber(ElementForm::TRIANGLE, ElementOrder::LINEAR), 3);     // 2D triangle has 3 nodes
    EXPECT_EQ(getTheoreticalElementNodeNumber(ElementForm::TRIANGLE, ElementOrder::QUADRATIC), 6);  // 2D quad triangle has 6 nodes
    EXPECT_EQ(getTheoreticalElementNodeNumber(ElementForm::QUADRANGLE, ElementOrder::LINEAR), 4);   // 2D quadrangle has 4 nodes
    EXPECT_EQ(getTheoreticalElementNodeNumber(ElementForm::QUADRANGLE, ElementOrder::QUADRATIC), 8);// 2D quad quadrangle has 8 nodes
    EXPECT_EQ(getTheoreticalElementNodeNumber(ElementForm::HEXAGON, ElementOrder::LINEAR), 6);      // 2D hexagon has 6 nodes
    EXPECT_EQ(getTheoreticalElementNodeNumber(ElementForm::HEXAGON, ElementOrder::QUADRATIC), 12);  // 2D quad hexagon has 12 nodes
    // 3D
    EXPECT_EQ(getTheoreticalElementNodeNumber(ElementForm::TETRAHEDRON, ElementOrder::LINEAR), 4);   // 3D tetrahedron has 4 nodes
    EXPECT_EQ(getTheoreticalElementNodeNumber(ElementForm::TETRAHEDRON, ElementOrder::QUADRATIC), 9);// 3D quad tetrahedron has 9 nodes
    EXPECT_EQ(getTheoreticalElementNodeNumber(ElementForm::PYRAMID, ElementOrder::LINEAR), 5);       // 3D pyramid has 5 nodes
    EXPECT_EQ(getTheoreticalElementNodeNumber(ElementForm::PYRAMID, ElementOrder::QUADRATIC), 13);   // 3D quad pyramid has 13 nodes
    EXPECT_EQ(getTheoreticalElementNodeNumber(ElementForm::PRISM, ElementOrder::LINEAR), 6);         // 3D prism has 4 nodes
    EXPECT_EQ(getTheoreticalElementNodeNumber(ElementForm::PRISM, ElementOrder::QUADRATIC), 15);     // 3D quad prism has 15 nodes
    EXPECT_EQ(getTheoreticalElementNodeNumber(ElementForm::HEXAHEDRON, ElementOrder::LINEAR), 8);    // 3D hexahedron has 4 nodes
    EXPECT_EQ(getTheoreticalElementNodeNumber(ElementForm::HEXAHEDRON, ElementOrder::QUADRATIC), 20);// 3D quad hexahedron has 20 nodes
}

TEST(MeshElement, DimentsionCheck){

    MeshElement el = MeshElement();
    el.getType() = static_cast<ElementForm>(666);
    EXPECT_TRUE(el.getDimension() == 0);
    el.getType() = ElementForm::VOID;
    EXPECT_TRUE(el.getDimension() == 0);
    el.getType() = ElementForm::BAR;
    EXPECT_TRUE(el.getDimension() == 1);
    el.getType() = ElementForm::TRIANGLE;
    EXPECT_TRUE(el.getDimension() == 2);
    el.getType() = ElementForm::QUADRANGLE;
    EXPECT_TRUE(el.getDimension() == 2);
    el.getType() = ElementForm::HEXAGON;
    EXPECT_TRUE(el.getDimension() == 2);
    el.getType() = ElementForm::TETRAHEDRON;
    EXPECT_TRUE(el.getDimension() == 3);
    el.getType() = ElementForm::PYRAMID;
    EXPECT_TRUE(el.getDimension() == 3);
    el.getType() = ElementForm::PRISM;
    EXPECT_TRUE(el.getDimension() == 3);
    el.getType() = ElementForm::HEXAHEDRON;
    EXPECT_TRUE(el.getDimension() == 3);
}

TEST(MeshElement, Nodescheck) {
    MeshElement el = MeshElement();
    el.getOrder() = ElementOrder::QUADRATIC;
    el.getType() = ElementForm::BAR;
    el.attachToMesh(nullptr);
    EXPECT_TRUE(el.isNotValid());
    MeshManager mm;
    el.attachToMesh(&mm);
    el.getType() = ElementForm::VOID;
    EXPECT_TRUE(el.isValid());
    el.attachToMesh(nullptr);// should do nothing!
    EXPECT_TRUE(el.isValid());

    mm.createNode(1, 0., 0., 0.);
    mm.createNode(3, 1., 0., 0.);
    mm.createNode(2, 0., 1., 0.);
    mm.createNode(4, 0., 0., 1.);
    mm.createElement(1, ElementForm::TETRAHEDRON, ElementOrder::LINEAR, {1, 2, 3, 4});
    for (auto it = mm.getElementBegin(); it != mm.getElementEnd(); ++it) {
        for (auto itn = (*it)->getNodeBegin(); itn != (*it)->getNodeEnd(); ++itn) {
            EXPECT_TRUE((*itn)->isValid());
        }
    }
}

TEST(MeshElement,Comparisons){
    MeshManager mm;
    mm.createNode(1, 0., 0., 0.);
    mm.createNode(3, 1., 0., 0.);
    mm.createNode(2, 0., 1., 0.);
    mm.createNode(4, 0., 0., 1.);
    mm.createNode(5, 0., 1., 1.);
    std::shared_ptr<MeshElement> elem1 = mm.createElement(1, ElementForm::TETRAHEDRON, ElementOrder::LINEAR, {1, 2, 3, 4});
    std::shared_ptr<MeshElement> elem2 = mm.createElement(1, ElementForm::PYRAMID, ElementOrder::LINEAR, {1, 2, 3, 4, 5});
    std::shared_ptr<MeshElement> elem3 = mm.createElement(1, ElementForm::QUADRANGLE, ElementOrder::LINEAR, {1, 2, 3, 4});

    EXPECT_TRUE((*elem1) < (*elem2)); // elem2 has more nodes
    EXPECT_TRUE((*elem3) < (*elem1)); // elem3's dimension is lower
}

TEST(MeshManager, MeshCreation) {
    MeshManager mm;
    EXPECT_EQ(mm.getNbNodes(), 0ULL);
    mm.createNode(1, 0., 0., 0.);
    mm.createNode(3, 1., 0., 0.);
    mm.createNode(2, 0., 1., 0.);
    mm.createNode(4, 0., 0., 1.);
    mm.createNode(7, {0., 0., -1.});
    EXPECT_EQ(mm.getNbNodes(), 5ULL);
    mm.sortMeshItems();
    //try to find non existing nodeId
    EXPECT_EQ(mm.getNodeByID(5), nullptr);

    mm.createElement(2, ElementForm::TETRAHEDRON, ElementOrder::LINEAR, {1, 2, 3, 4});
    mm.createElement(1, ElementForm::TETRAHEDRON, ElementOrder::LINEAR, {1, 2, 3, 7});
    EXPECT_EQ(mm.getNbElements(), 2ULL);
    mm.sortMeshItems();
    //try to find non existing ElementId
    EXPECT_EQ(mm.getElementByID(3), nullptr);
    EXPECT_EQ(mm.getElementByID(1)->getID(), 1);

    for (auto it = mm.getNodeBegin(); it != mm.getNodeEnd(); ++it) {
        EXPECT_TRUE((*it)->isValid());
        EXPECT_FALSE((*it)->isNotValid());
    }
    for (auto it = mm.getElementBegin(); it != mm.getElementEnd(); ++it) {
        EXPECT_TRUE((*it)->isValid());
        EXPECT_FALSE((*it)->isNotValid());
    }

    // invalidity of node without mesh manager
    EXPECT_FALSE(MeshNode().isValid());
    // invalidity of element without mesh manager
    EXPECT_FALSE(MeshElement().isValid());

    // invalid element creation
    EXPECT_THROW(new MeshElement(nullptr, 25, ElementForm::TETRAHEDRON, ElementOrder::LINEAR, {1, 2, 3, 4}), optim::Exception);
    EXPECT_THROW(new MeshElement(&mm, 25, ElementForm::TETRAHEDRON, ElementOrder::LINEAR, {1, 2, 3}), optim::Exception);
    EXPECT_THROW(new MeshElement(&mm, 25, ElementForm::TETRAHEDRON, ElementOrder::LINEAR, {1, 2, 3, 18}), optim::Exception);

    // element validity
    MeshElement el = MeshElement();
    el.attachToMesh(&mm);
    EXPECT_TRUE(el.isValid());
    el.getOrder() = ElementOrder::LINEAR;
    EXPECT_EQ(el.getOrder(), ElementOrder::LINEAR);
    EXPECT_EQ(el.getType(), ElementForm::VOID);
    EXPECT_TRUE(el.isValid());// void with no node is OK
    el.getOrder() = ElementOrder::QUADRATIC;
    el.getType() = ElementForm::BAR;
    EXPECT_TRUE(el.isNotValid());// Bar with no node is KO
}

TEST(MeshManager, MeshComparison) {
    MeshManager mesh1;
    MeshManager mesh2;
    mesh1.createNode(1, 0., 0., 0.);
    mesh1.createNode(3, 1., 0., 0.);
    mesh1.createNode(2, 0., 1., 0.);
    mesh1.createNode(4, 0., 0., 1.);
    mesh1.createNode(7, {0., 0., -1.});
    mesh1.createElement(2, ElementForm::TETRAHEDRON, ElementOrder::LINEAR, {1, 2, 3, 4});
    mesh1.createElement(1, ElementForm::TETRAHEDRON, ElementOrder::LINEAR, {1, 2, 3, 7});
    // dummy test
    EXPECT_TRUE(mesh1 == mesh1);
    EXPECT_FALSE(mesh1 != mesh1);
    mesh2 = mesh1;
    EXPECT_TRUE(mesh1 == mesh2);
    EXPECT_FALSE(mesh1 != mesh2);
    mesh2.createNode(66, 0., 0., 0.);
    // test different node number
    EXPECT_FALSE(mesh1 == mesh2);
    EXPECT_TRUE(mesh1 != mesh2);
    mesh2.clear();
    mesh2.createNode(1, 0., 0., 0.);
    mesh2.createNode(3, 1., 0., 0.);
    mesh2.createNode(2, 0., 1., 0.);
    mesh2.createNode(4, 0., 0., 1.);
    mesh2.createNode(7, {0., 0., -1.});
    // test different element number
    EXPECT_FALSE(mesh1 == mesh2);
    EXPECT_TRUE(mesh1 != mesh2);
    mesh2.createElement(2, ElementForm::TETRAHEDRON, ElementOrder::LINEAR, {1, 2, 3, 4});
    mesh2.createElement(1, ElementForm::TETRAHEDRON, ElementOrder::LINEAR, {1, 2, 4, 7});
    // test same number but different elements
    EXPECT_FALSE(mesh1 == mesh2);
    EXPECT_TRUE(mesh1 != mesh2);
    mesh2.clear();
    mesh2.createNode(1, 0., 0., 0.);
    mesh2.createNode(3, 1., 0., 0.);
    mesh2.createNode(2, 0., 1., 0.);
    mesh2.createNode(4, 0., 0., 1.);
    mesh2.createNode(7, {0., 0., 1.});
    mesh2.createElement(2, ElementForm::TETRAHEDRON, ElementOrder::LINEAR, {1, 2, 3, 4});
    mesh2.createElement(1, ElementForm::TETRAHEDRON, ElementOrder::LINEAR, {1, 2, 3, 7});
    // test same number but different node
    EXPECT_FALSE(mesh1 == mesh2);
    EXPECT_TRUE(mesh1 != mesh2);
    mesh2.clear();
    mesh2.createNode(1, 0., 0., 0.);
    mesh2.createNode(3, 1., 0., 0.);
    mesh2.createNode(4, 0., 0., 1.);
    mesh2.createNode(2, 0., 1., 0.);
    mesh2.createNode(7, {0., 0., -1.});
    mesh2.createElement(2, ElementForm::TETRAHEDRON, ElementOrder::LINEAR, {1, 2, 3, 4});
    mesh2.createElement(1, ElementForm::TETRAHEDRON, ElementOrder::LINEAR, {1, 2, 3, 7});
    // test identical but node in different order
    EXPECT_TRUE(mesh1 == mesh2);
    EXPECT_FALSE(mesh1 != mesh2);
    mesh2.clear();
    mesh2.createNode(1, 0., 0., 0.);
    mesh2.createNode(3, 1., 0., 0.);
    mesh2.createNode(2, 0., 1., 0.);
    mesh2.createNode(4, 0., 0., 1.);
    mesh2.createNode(7, {0., 0., -1.});
    mesh2.createElement(1, ElementForm::TETRAHEDRON, ElementOrder::LINEAR, {1, 2, 3, 7});
    mesh2.createElement(2, ElementForm::TETRAHEDRON, ElementOrder::LINEAR, {1, 2, 3, 4});
    // test identical but elements in different order
    EXPECT_TRUE(mesh1 == mesh2);
    EXPECT_FALSE(mesh1 != mesh2);
}
