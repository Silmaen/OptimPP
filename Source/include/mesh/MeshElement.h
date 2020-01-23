//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once

#include "MeshNode.h"

namespace optim::mesh
{

class MeshManager;

/**
 * @brief list of element Type
 */
enum class ElementType
{
	// OD element
	VOID, ///< Void element, e.g. the void
	// 1D element
	BAR, ///< Bar element meaning a bar
	// 2D elements
	TRIANGLE, ///< 2D triangle element
	QUADRANGLE, ///< 2D quadrangle element
	HEXAGON, ///< 2D hexagon element
	// 3D elements
	TETRAHEDRON, ///< 3D tetrahedron element
	PYRAMID, ///< 3D pyramid element (pentahedron with 4 triangles faces and 1 quadrangle face)
	PRISM, ///< 3D prism element (pentahedron with 2 triangles faces and 3 quadrangles faces)
	HEXAHEDRON, ///< 3D hexahedron element
};

/**
 * @brief list of supported ElementOrder
 */
enum class ElementOrder
{
	NONE, ///< Order 0 element (special elements)
	LINEAR, ///< order 1 element 
	QUADRATIC, ///< order 2 elements
};

/**
* @brief determine the number of nodes of an element base on type and order
* @param[in] ety the type of element
* @param[in] eord the order of element
* @return the number of node for the element (negative number means no theoretical value (special elements)
*/
[[nodiscard]] s8 getTheoreticalElementNodeNumber(const ElementType& ety, const ElementOrder& eord)noexcept;

/**
 * @brief base class handling Element in mesh
 */
class MeshElement : Comparable<MeshElement>
{
public:
	// definitions
	using NodeIterator = vector< shared_ptr<MeshNode>>::iterator; ///< iterator on nodes
	using NodeConstIterator = vector< shared_ptr<MeshNode>>::const_iterator; ///< constant iterator on nodes
	// rule of fives
	MeshElement(const MeshElement&) = default; ///< Default copy constructor
	MeshElement(MeshElement&&)noexcept = default; ///< Default move constructor
	/**
	 * @brief default copy affectation
	 * @return this object
	 */
	MeshElement& operator=(const MeshElement&) = default;
	/**
	 * @brief default move affectation
	 * @return this object
	 */
	MeshElement& operator=(MeshElement&&)noexcept = default;
	~MeshElement() = default; ///< Default destructor
	// constructors
	/**
	 * @brief base default constructor
	 * @param[in] manager pointer to the parent manager
	 */
	MeshElement(MeshManager* manager = nullptr) :meshManager { manager }, Id { 0 }, eType { ElementType::VOID }, eOrder { ElementOrder::NONE } {}
	/**
	 * @brief parametric constructor
	 * @param[in] manager pointer to the parent manager, exception is raised if nullptr
	 * @param[in] ElementID the Id of the element
	 * @param[in] ety the element type
	 * @param[in] eo the element order
	 * @param[in] nodeIDList list of the node ID of this element, exception raised if the size missmatch theoretical one
	 */
	MeshElement(MeshManager* manager, const u64 ElementID, const ElementType ety, const ElementOrder eo, const vector<u64>& nodeIDList);
	// comparison
	/**
	 * @brief Key function of comparison
	 * @param[in] other the other vector to compare
	 * @return negative value if this vector is lesser than other, positive value if greater, 0 if equal
	 *
	 * note that it will first compare the first component, if equal: the second , if equal the third
	 */
	[[nodiscard]] s8 CompareTo(const MeshElement& other)const noexcept { return clamp8(Id - other.Id); };
	/**
	 * @brief check if the element informations are valid
	 * @return true if the element is valid
	 */
	[[nodiscard]] bool isValid()const noexcept;
	/**
	 * @brief check if the element informations are not valid
	 * @return true if the element is not valid
	 */
	[[nodiscard]] bool isNotValid()const noexcept { return !isValid(); };
	/**
	 * @brief validity checker
	 *
	 * throw exceptions when error are founds
	 */
	void checkValidity(bool AllThrow = true)const;
	/**
	* @brief determine the number of nodes of this element
	* @return the number of node for the element (negative number means no theoretical value (special elements)
	*/
	[[nodiscard]] s8 getSupposedElementNodeNumber()const noexcept { return getTheoreticalElementNodeNumber(eType, eOrder); }
	/**
	 * @brief get the actual number of nodes of this element
	 * @return the number of nodes
	 */
	[[nodiscard]] s8 getElementNodeNumber()const noexcept { return clamp8(nodes.size()); }
	/**
	 * @brief return the ID of the node
	 * @return the ID of the node
	 */
	[[nodiscard]] const u64& getID()const noexcept { return Id; }
	/**
	 * @brief affect the mesh to a manager (only if not already affected)
	 * @param[in] newMeshManager the new mesh manager
	 */
	void attachToMesh(MeshManager* newMeshManager)noexcept { if(meshManager==nullptr && newMeshManager != nullptr) meshManager = newMeshManager; }
	/**
	 * @brief retrieve the element type
	 * @return the element type
	 */
	[[nodiscard]] const ElementType& getType()const noexcept { return eType; }
	/**
	 * @brief retrieve the element type
	 * @return the element type
	 */
	[[nodiscard]] ElementType& getType()noexcept { return eType; }
	/**
	 * @brief retrieve the element order
	 * @return the element order
	 */
	[[nodiscard]] const ElementOrder& getOrder()const noexcept { return eOrder; }
	/**
	 * @brief retrieve the element order
	 * @return the element order
	 */
	[[nodiscard]] ElementOrder& getOrder()noexcept { return eOrder; }
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
private:
	MeshManager* meshManager; ///< pointer to the parent manager
	u64 Id; ///< the element unique ID
	ElementType eType; ///< type of the element
	ElementOrder eOrder; ///< order of the element
	vector<shared_ptr<MeshNode>> nodes; ///< list of the element's nodes
};

}