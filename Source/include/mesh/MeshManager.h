//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once

#include "MeshElement.h"

namespace optim::mesh
{

/**
 * @brief Base class for mesh management
 */
class MeshManager
{
public:
	// definitions
	using NodeIterator = vector< shared_ptr<MeshNode>>::iterator; ///< iterator on nodes
	using NodeConstIterator = vector< shared_ptr<MeshNode>>::const_iterator; ///< constant iterator on nodes
	using ElementIterator = vector< shared_ptr<MeshElement>>::iterator; ///< iterator on elements
	using ElementConstIterator = vector< shared_ptr<MeshElement>>::const_iterator; ///< constant iterator on elements

	// rule of fives
	MeshManager(const MeshManager&) = default; ///< Default copy constructor
	MeshManager(MeshManager&&)noexcept = default; ///< Default move constructor
	/**
	 * @brief default copy affectation
	 * @return this object
	 */
	MeshManager& operator=(const MeshManager&) = default;
	/**
	 * @brief default move affectation
	 * @return this object
	 */
	MeshManager& operator=(MeshManager&&)noexcept = default;
	~MeshManager() = default; ///< Default destructor
	/**
	 * @brief default constructor
	 */
	MeshManager() {}
	// access
	/**
	 * @brief retrieve node by its ID
	 * @param[in] id the node Id to find
	 * @return pointer to the node nullptr if not found
	 */
	[[nodiscard]] shared_ptr<MeshNode> getNodeByID(const u64 id)const noexcept;
	/**
	 * @brief retrieve element by its ID
	 * @param[in] id the element Id to find
	 * @return pointer to the element nullptr if not found
	 */
	[[nodiscard]] shared_ptr<MeshElement> getElementByID(const u64 id)const noexcept;
	/**
	 * @brief get the beginning of the node's list
	 * @return iterator to the beginning of the node's list
	 */
	[[nodiscard]] NodeIterator getNodeBegin()noexcept { return nodes.begin(); }
	/**
	 * @brief get the beginning of the node's list
	 * @return const iterator to the beginning of the node's list
	 */
	[[nodiscard]] NodeConstIterator getNodeBegin()const noexcept { return nodes.begin(); }
	/**
	 * @brief get the ending of the node's list
	 * @return iterator to the ending of the node's list
	 */
	[[nodiscard]] NodeIterator getNodeEnd()noexcept { return nodes.end(); }
	/**
	 * @brief get the ending of the node's list
	 * @return const iterator to the ending of the node's list
	 */
	[[nodiscard]] NodeConstIterator getNodeEnd()const noexcept { return nodes.end(); }
	/**
	 * @brief get the beginning of the element's list
	 * @return iterator to the beginning of the element's list
	 */
	[[nodiscard]] ElementIterator getElementBegin()noexcept { return elements.begin(); }
	/**
	 * @brief get the beginning of the element's list
	 * @return const iterator to the beginning of the element's list
	 */
	[[nodiscard]] ElementConstIterator getElementBegin()const noexcept { return elements.begin(); }
	/**
	 * @brief get the ending of the element's list
	 * @return iterator to the ending of the element's list
	 */
	[[nodiscard]] ElementIterator getElementEnd()noexcept { return elements.end(); }
	/**
	 * @brief get the ending of the element's list
	 * @return const iterator to the ending of the element's list
	 */
	[[nodiscard]] ElementConstIterator getElementEnd()const noexcept { return elements.end(); }
	/**
	 * @brief create a node in the mesh
	 * @param[in] Id the node ID
	 * @param[in] x first coordinate of the node
	 * @param[in] y second coordinate of the node
	 * @param[in] z third coordinate of the node
	 * @return a reference to the pointer to the created node
	 */
	shared_ptr<MeshNode>& createNode(const u64 Id, const double x, const  double y, const double z);
	/**
	 * @brief create a node in the mesh
	 * @param[in] Id the node ID
	 * @param[in] v coordinates of the node
	 * @return a reference to the pointer to the created node
	 */
	shared_ptr<MeshNode>& createNode(const u64 Id, const base::Vector3& v);
	/**
	 * @brief create a element in the mesh
	 * @param[in] Id the element ID
	 * @param[in] ety type of the element
	 * @param[in] eo order of the element
	 * @param[in] nodeIDList list of the element's node
	 * @return a reference to the pointer to the created element
	 */
	shared_ptr<MeshElement>& createElement(const u64 Id, const ElementType ety, const ElementOrder eo, const vector<u64>& nodeIDList);
	/**
	 * @brief get the number of nodes in the mesh
	 * @return the number of nodes
	 */
	u64 getNbNodes() { return nodes.size(); }
	/**
	 * @brief get the number of elements in the mesh
	 * @return the number of elements
	 */
	u64 getNbElements() { return elements.size(); }
	/**
	 * @brief sort all item by their ID
	 */
	void sortMeshItems();
private:
	vector<shared_ptr<MeshNode>> nodes; ///< the list of nodes
	vector<shared_ptr<MeshElement>> elements; ///< the list of elements
};

}
