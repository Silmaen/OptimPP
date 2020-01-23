//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------


#include "mesh/MeshManager.h"
#include <algorithm>
#include "base/Exception.h"
#include <iostream>

namespace optim::mesh
{

shared_ptr<MeshNode> MeshManager::getNodeByID(const u64 id) const noexcept
{
	auto node = std::find_if(nodes.begin(), nodes.end(), [&id] (auto& anode) {return anode->getID() == id; });
	if(node == nodes.end())
		return nullptr;
	return *node;
}

shared_ptr<MeshElement> MeshManager::getElementByID(const u64 id)const noexcept
{
	auto element = std::find_if(elements.begin(), elements.end(), [&id] (auto& aelement) {return aelement->getID() == id; });
	if(element == elements.end())
		return nullptr;
	return *element;
}

shared_ptr<MeshNode>& MeshManager::createNode(const u64 Id, const double x, const  double y, const double z)
{
	return nodes.emplace_back(std::make_shared<MeshNode>(this, Id, x, y, z));
}

shared_ptr<MeshNode>& MeshManager::createNode(const u64 Id, const base::Vector3& v)
{
	return nodes.emplace_back(std::make_shared<MeshNode>(this, Id, v));
}

shared_ptr<MeshElement>& MeshManager::createElement(const u64 Id, const ElementType ety, const ElementOrder eo, const vector<u64>& nodeIDList)
{
	return elements.emplace_back(std::make_shared<MeshElement>(this, Id, ety, eo, nodeIDList));
}

void MeshManager::sortMeshItems()
{
	std::sort(nodes.begin(),nodes.end());
	std::sort(elements.begin(),elements.end());
}

}
