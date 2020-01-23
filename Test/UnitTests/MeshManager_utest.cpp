#include <gtest/gtest.h>
#include <mesh/MeshManager.h>
#include <base/Exception.h>

using namespace optim::mesh;

TEST(MeshElement, TheoreticalNodeNumber)
{
	// special
	EXPECT_EQ(getTheoreticalElementNodeNumber(ElementType::VOID, ElementOrder::NONE), -1); // free node number
	EXPECT_EQ(getTheoreticalElementNodeNumber(ElementType::VOID, static_cast<ElementOrder>(666)), -1); // out of bounds
	EXPECT_EQ(getTheoreticalElementNodeNumber(static_cast<ElementType>(666), ElementOrder::LINEAR), -1); // out of bounds
	EXPECT_EQ(getTheoreticalElementNodeNumber(static_cast<ElementType>(666), ElementOrder::QUADRATIC), -1); // out of bounds
	// void
	EXPECT_EQ(getTheoreticalElementNodeNumber(ElementType::VOID, ElementOrder::LINEAR), 0); // Void has no node
	EXPECT_EQ(getTheoreticalElementNodeNumber(ElementType::VOID, ElementOrder::QUADRATIC), 0); // Void has no node
	// 1D
	EXPECT_EQ(getTheoreticalElementNodeNumber(ElementType::BAR, ElementOrder::LINEAR), 2); // 1D bar has 2 nodes
	EXPECT_EQ(getTheoreticalElementNodeNumber(ElementType::BAR, ElementOrder::QUADRATIC), 3); // 1D quad bar has 3 nodes
	// 2D
	EXPECT_EQ(getTheoreticalElementNodeNumber(ElementType::TRIANGLE, ElementOrder::LINEAR), 3); // 2D triangle has 3 nodes
	EXPECT_EQ(getTheoreticalElementNodeNumber(ElementType::TRIANGLE, ElementOrder::QUADRATIC), 6); // 2D quad triangle has 6 nodes
	EXPECT_EQ(getTheoreticalElementNodeNumber(ElementType::QUADRANGLE, ElementOrder::LINEAR), 4); // 2D quadrangle has 4 nodes
	EXPECT_EQ(getTheoreticalElementNodeNumber(ElementType::QUADRANGLE, ElementOrder::QUADRATIC), 8); // 2D quad quadrangle has 8 nodes
	EXPECT_EQ(getTheoreticalElementNodeNumber(ElementType::HEXAGON, ElementOrder::LINEAR), 6); // 2D hexagon has 6 nodes
	EXPECT_EQ(getTheoreticalElementNodeNumber(ElementType::HEXAGON, ElementOrder::QUADRATIC), 12); // 2D quad hexagon has 12 nodes
	// 3D
	EXPECT_EQ(getTheoreticalElementNodeNumber(ElementType::TETRAHEDRON, ElementOrder::LINEAR), 4); // 3D tetrahedron has 4 nodes
	EXPECT_EQ(getTheoreticalElementNodeNumber(ElementType::TETRAHEDRON, ElementOrder::QUADRATIC), 9); // 3D quad tetrahedron has 9 nodes
	EXPECT_EQ(getTheoreticalElementNodeNumber(ElementType::PYRAMID, ElementOrder::LINEAR), 5); // 3D pyramid has 5 nodes
	EXPECT_EQ(getTheoreticalElementNodeNumber(ElementType::PYRAMID, ElementOrder::QUADRATIC), 13); // 3D quad pyramid has 13 nodes
	EXPECT_EQ(getTheoreticalElementNodeNumber(ElementType::PRISM, ElementOrder::LINEAR), 6); // 3D prism has 4 nodes
	EXPECT_EQ(getTheoreticalElementNodeNumber(ElementType::PRISM, ElementOrder::QUADRATIC), 15); // 3D quad prism has 15 nodes
	EXPECT_EQ(getTheoreticalElementNodeNumber(ElementType::HEXAHEDRON, ElementOrder::LINEAR), 8); // 3D hexahedron has 4 nodes
	EXPECT_EQ(getTheoreticalElementNodeNumber(ElementType::HEXAHEDRON, ElementOrder::QUADRATIC), 20); // 3D quad hexahedron has 20 nodes
}

TEST(MeshElement, Nodescheck)
{
	MeshElement el = MeshElement();
	el.getOrder() = ElementOrder::QUADRATIC;
	el.getType() = ElementType::BAR;
	el.attachToMesh(nullptr);
	EXPECT_TRUE(el.isNotValid());
	MeshManager mm;
	el.attachToMesh(&mm);
	el.getType() = ElementType::VOID;
	EXPECT_TRUE(el.isValid());
	el.attachToMesh(nullptr); // should do nothing!
	EXPECT_TRUE(el.isValid());

	mm.createNode(1, 0., 0., 0.);
	mm.createNode(3, 1., 0., 0.);
	mm.createNode(2, 0., 1., 0.);
	mm.createNode(4, 0., 0., 1.);
	mm.createElement(1, ElementType::TETRAHEDRON, ElementOrder::LINEAR, { 1,2,3,4 });
	for(auto it = mm.getElementBegin(); it != mm.getElementEnd(); ++it)
	{
		for(auto itn = (*it)->getNodeBegin(); itn != (*it)->getNodeEnd(); ++itn)
		{
			EXPECT_TRUE((*itn)->isValid());
		}
	}
}

TEST(MeshManager, MeshCreation)
{
	MeshManager mm;
	EXPECT_EQ(mm.getNbNodes(), 0ull);
	mm.createNode(1, 0., 0., 0.);
	mm.createNode(3, 1., 0., 0.);
	mm.createNode(2, 0., 1., 0.);
	mm.createNode(4, 0., 0., 1.);
	mm.createNode(7, { 0., 0., -1. });
	EXPECT_EQ(mm.getNbNodes(), 5ull);
	mm.sortMeshItems();
	//try to find non existing nodeId
	EXPECT_EQ(mm.getNodeByID(5), nullptr);

	mm.createElement(2, ElementType::TETRAHEDRON, ElementOrder::LINEAR, { 1,2,3,4 });
	mm.createElement(1, ElementType::TETRAHEDRON, ElementOrder::LINEAR, { 1,2,3,7 });
	EXPECT_EQ(mm.getNbElements(), 2ull);
	mm.sortMeshItems();
	//try to find non existing ElementId
	EXPECT_EQ(mm.getElementByID(3), nullptr);
	EXPECT_EQ(mm.getElementByID(1)->getID(), 1);

	for(auto it = mm.getNodeBegin(); it != mm.getNodeEnd(); ++it)
	{
		EXPECT_TRUE((*it)->isValid());
		EXPECT_FALSE((*it)->isNotValid());
	}
	for(auto it = mm.getElementBegin(); it != mm.getElementEnd(); ++it)
	{
		EXPECT_TRUE((*it)->isValid());
		EXPECT_FALSE((*it)->isNotValid());
	}

	// invalidity of node without mesh manager
	EXPECT_FALSE(MeshNode().isValid());
	// invalidity of element without mesh manager
	EXPECT_FALSE(MeshElement().isValid());

	// invalid element creation
	EXPECT_THROW(new MeshElement(nullptr, 25, ElementType::TETRAHEDRON, ElementOrder::LINEAR, { 1,2,3,4 }), optim::Exception);
	EXPECT_THROW(new MeshElement(&mm, 25, ElementType::TETRAHEDRON, ElementOrder::LINEAR, { 1,2,3 }), optim::Exception);
	EXPECT_THROW(new MeshElement(&mm, 25, ElementType::TETRAHEDRON, ElementOrder::LINEAR, { 1,2,3,18 }), optim::Exception);

	// element validity
	MeshElement el = MeshElement();
	el.attachToMesh(&mm);
	EXPECT_TRUE(el.isValid());
	el.getOrder() = ElementOrder::LINEAR;
	EXPECT_EQ(el.getOrder(), ElementOrder::LINEAR);
	EXPECT_EQ(el.getType(), ElementType::VOID);
	EXPECT_TRUE(el.isValid()); // void with no node is OK
	el.getOrder() = ElementOrder::QUADRATIC;
	el.getType() = ElementType::BAR;
	EXPECT_TRUE(el.isNotValid()); // Bar with no node is KO
}

