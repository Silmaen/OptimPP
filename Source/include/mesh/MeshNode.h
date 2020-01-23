//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once

#include "base/vector3.h"

/**
 * @namespace optim::mesh
 * @brief namespace gathering the mesh elements
 */
namespace optim::mesh
{

class MeshManager;

/**
 * @brief class for handing the node of a mesh
 */
class MeshNode : public Comparable<MeshNode>
{
public:
	// rule of fives
	MeshNode(const MeshNode&) = default; ///< Default copy constructor
	MeshNode(MeshNode&&)noexcept = default; ///< Default move constructor
	/**
	 * @brief default copy affectation
	 * @return this object
	 */
	MeshNode& operator=(const MeshNode&) = default;
	/**
	 * @brief default move affectation
	 * @return this object
	 */
	MeshNode& operator=(MeshNode&&)noexcept = default;
	~MeshNode() = default; ///< Default destructor
	// constructors
	/**
	 * @brief base default constructor
	 * @param[in] manager the parent MeshManager
	 * @param[in] NodeID the Id of the node
	 */
	MeshNode(MeshManager* manager = nullptr, const u64 NodeID = 0) :meshManager { manager }, Id { NodeID }, coords {}{}
	/**
	 * @brief constructor with coordinates
	 * @param[in] manager the parent MeshManager
	 * @param[in] NodeID the Id of the node
	 * @param[in] v the coordinates to initialize
	 */
	MeshNode(MeshManager* manager, const u64 NodeID, const base::Vector3& v) :meshManager { manager }, Id { NodeID }, coords { v } {}
	/**
	 * @brief constructor with coordinates
	 * @param[in] manager the parent MeshManager
	 * @param[in] NodeID the Id of the node
	 * @param[in] x the first coordinate
	 * @param[in] y the first coordinate
	 * @param[in] z the first coordinate
	 */
	MeshNode(MeshManager* manager, const u64 NodeID, const double& x, const double& y, const double& z) :meshManager { manager }, Id { NodeID }, coords { x,y,z } {}
	// comparison
	/**
	 * @brief Key function of comparison
	 * @param[in] other the other vector to compare
	 * @return negative value if this vector is lesser than other, positive value if greater, 0 if equal
	 *
	 * note that it will first compare the first component, if equal: the second , if equal the third
	 */
	[[nodiscard]] s8 CompareTo(const MeshNode& other)const noexcept { return clamp8(Id - other.Id); };	
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
	 * @param[in] AllThrow if true (default), will throw Exitcode::OK if valid, else, it only throw if errors
	 */
	void checkValidity(bool AllThrow=true)const;
	// Access
	/**
	 * @brief return the ID of the node
	 * @return the ID of the node
	 */
	[[nodiscard]] const u64& getID()const noexcept { return Id; }
	/**
	 * @brief get access to the node coordinates
	 * @return the node coordinates
	 */
	[[nodiscard]] base::Vector3& getCoords()noexcept { return coords; }
	/**
	 * @brief get access to the node coordinates
	 * @return the node coordinates
	 */
	[[nodiscard]] const base::Vector3& getCoords()const noexcept { return coords; }
	/**
	 * @brief set the node coordinates
	 * @param[in] v the new coordinates
	 */
	void setCoords(const base::Vector3& v) noexcept { coords = v; }
	/**
	 * @brief set the node coordinates
	 * @param[in] x the first coordinate
	 * @param[in] y the first coordinate
	 * @param[in] z the first coordinate
	 */
	void setCoords(const double& x, const double& y, const double& z) noexcept { setCoords(base::Vector3 { x,y,z }); }
private:
	MeshManager* meshManager; ///< pointer to the parent manager
	u64 Id { 0 }; ///< the Id of the node
	base::Vector3 coords; ///< the coordinates of the node
};



}
