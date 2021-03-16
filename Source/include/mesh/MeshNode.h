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
class MeshNode : public base::Vector3
{
public:
    // rule of fives
    MeshNode(const MeshNode&) = default; ///< Default copy constructor
    MeshNode(MeshNode&&)noexcept = default; ///< Default move constructor
    ~MeshNode() = default; ///< Default destructor
    // constructors
    /**
     * @brief base default constructor
     * @param[in] manager the parent MeshManager
     * @param[in] NodeID the Id of the node
     */
    explicit MeshNode(
        MeshManager* manager = nullptr,
        const u64 NodeID = 0
        ) :base::Vector3{},
            meshManager { manager },
            Id { NodeID }
    {}
    /**
     * @brief constructor with coordinates
     * @param[in] manager the parent MeshManager
     * @param[in] NodeID the Id of the node
     * @param[in] v the coordinates to initialize
     */
    MeshNode(
        MeshManager* manager,
        const u64 NodeID,
        const base::Vector3& v
        ) :base::Vector3{v},
            meshManager { manager },
            Id { NodeID }
    {}
    /**
     * @brief constructor with coordinates
     * @param[in] manager the parent MeshManager
     * @param[in] NodeID the Id of the node
     * @param[in] x the first coordinate
     * @param[in] y the first coordinate
     * @param[in] z the first coordinate
     */
    MeshNode(
        MeshManager* manager,
        const u64 NodeID,
        const double& x,
        const double& y,
        const double& z
        ) :base::Vector3{x,y,z},
            meshManager { manager },
            Id { NodeID } {}
    // comparison
    /**
     * @brief Key function of comparison
     * @param[in] other the other vector to compare
     * @return negative value if this vector is lesser than other, positive value if greater, 0 if equal
     *
     * note that it will first compare the first component, if equal: the second , if equal the third
     */
    [[nodiscard]] s8 CompareTo(const MeshNode& other)const noexcept {
        return clamp8(static_cast<s64>(Id) - static_cast<s64>(other.Id));
    }
    /**
     * @brief check if the element information are valid
     * @return true if the element is valid
     */
    [[nodiscard]] bool isValid()const noexcept;
    /**
     * @brief check if the element information are not valid
     * @return true if the element is not valid
     */
    [[nodiscard]] bool isNotValid()const noexcept { return !isValid(); }
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
private:
    MeshManager* meshManager; ///< pointer to the parent manager
    u64 Id { 0 }; ///< the Id of the node
};



}
