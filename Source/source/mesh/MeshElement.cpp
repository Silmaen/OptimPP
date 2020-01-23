//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#include "mesh/MeshElement.h"
#include "mesh/MeshManager.h"
#include "base/Exception.h"

namespace optim::mesh
{
MeshElement::MeshElement(MeshManager* manager, const u64 ElementID, const ElementType ety, const ElementOrder eo, const vector<u64>& nodeIDList) :meshManager { manager }, Id { ElementID }, eType { ety }, eOrder { eo }
{
	if(meshManager == nullptr)
		throw Exception(ExitCode::Value::NoMeshManager);
	s8 sNodeNum = getSupposedElementNodeNumber();
	if(sNodeNum >= 0 && static_cast<u8>(sNodeNum) != nodeIDList.size())
		throw Exception(ExitCode::Value::WrongNodeNumber);
	nodes.clear();
	nodes.reserve(nodeIDList.size());
	for(auto nid : nodeIDList)
	{
		auto n = meshManager->getNodeByID(nid);
		if(n == nullptr)
			throw Exception(ExitCode::Value::WrongNodeId);
		n->checkValidity(false); // false: throw only if error
		nodes.push_back(n);
	}
}

bool MeshElement::isValid() const noexcept
{
	try
	{
		checkValidity(true);
	}
	catch(Exception & e)
	{
		if(e.GetCode() == ExitCode::Value::OK)
			return true;
	}
	return false;
}

void MeshElement::checkValidity(bool AllThrow) const
{
	if(meshManager == nullptr)
		throw Exception(ExitCode::Value::NoMeshManager);
	if(getSupposedElementNodeNumber() >= 0 && getSupposedElementNodeNumber() != getElementNodeNumber())
		throw Exception(ExitCode::Value::WrongNodeNumber);
	for(auto node : nodes)
		node->checkValidity(false); // false: throw only if error
	if (AllThrow)throw Exception(ExitCode::Value::OK);
}

s8 getTheoreticalElementNodeNumber(const ElementType& ety, const ElementOrder& eord)noexcept
{
	switch(eord)
	{
		case ElementOrder::NONE:
			return -1;
		case ElementOrder::LINEAR:
			switch(ety)
			{
				case ElementType::VOID:
					return 0;
				case ElementType::BAR:
					return 2;
				case ElementType::TRIANGLE:
					return 3;
				case ElementType::QUADRANGLE:
					return 4;
				case ElementType::HEXAGON:
					return 6;
				case ElementType::TETRAHEDRON:
					return 4;
				case ElementType::PYRAMID:
					return 5;
				case ElementType::PRISM:
					return 6;
				case ElementType::HEXAHEDRON:
					return 8;
			}
			break;
		case ElementOrder::QUADRATIC:
			switch(ety)
			{
				case ElementType::VOID:
					return 0;
				case ElementType::BAR:
					return 3;
				case ElementType::TRIANGLE:
					return 6;
				case ElementType::QUADRANGLE:
					return 8;
				case ElementType::HEXAGON:
					return 12;
				case ElementType::TETRAHEDRON:
					return 9;
				case ElementType::PYRAMID:
					return 13;
				case ElementType::PRISM:
					return 15;
				case ElementType::HEXAHEDRON:
					return 20;
			}
			break;
	}
	return -1;
}

}