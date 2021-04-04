//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once

#include "base/vector3.h"
#include <json.hpp>
using json = nlohmann::json;

/**
 * @namespace optim::mesh
 * @brief namespace gathering the mesh elements
 */
namespace optim::mesh {

class MeshManager;

/**
 * @brief class for handing the node of a mesh
 */
class MeshNode : public TieComparable<MeshNode> {
public:
    // constructors
    /**
     * @brief base default constructor
     * @param[in] manager the parent MeshManager
     * @param[in] NodeID the Id of the node
     */
    explicit MeshNode(
            MeshManager *manager = nullptr,
            const u64 NodeID = 0) : meshManager{manager},
                                    Id{NodeID},
                                    coords{} {}
    /**
     * @brief constructor with coordinates
     * @param[in] manager the parent MeshManager
     * @param[in] NodeID the Id of the node
     * @param[in] v the coordinates to initialize
     */
    MeshNode(
            MeshManager *manager,
            const u64 NodeID,
            const base::Vector3 &v) : meshManager{manager},
                                      Id{NodeID},
                                      coords{v} {}
    /**
     * @brief constructor with coordinates
     * @param[in] manager the parent MeshManager
     * @param[in] NodeID the Id of the node
     * @param[in] x the first coordinate
     * @param[in] y the first coordinate
     * @param[in] z the first coordinate
     */
    MeshNode(
            MeshManager *manager,
            const u64 NodeID,
            const double &x,
            const double &y,
            const double &z) : meshManager{manager},
                               Id{NodeID},
                               coords{x, y, z} {}
    // comparison

    /**
     * @brief check if the element information are valid
     * @return true if the element is valid
     */
    [[nodiscard]] bool isValid() const noexcept;
    /**
     * @brief check if the element information are not valid
     * @return true if the element is not valid
     */
    [[nodiscard]] bool isNotValid() const noexcept { return !isValid(); }
    /**
     * @brief validity checker
     *
     * throw exceptions when error are founds
     * @param[in] AllThrow if true (default), will throw Exitcode::OK if valid, else, it only throw if errors
     */
    void checkValidity(bool AllThrow = true) const;
    // Access
    /**
     * @brief return the ID of the node
     * @return the ID of the node
     */
    [[nodiscard]] const u64 &getID() const noexcept { return Id; }

    /**
     * @brief get acdess to the coordinates
     * @return the cooardinates
     */
    [[nodiscard]] const base::Vector3& getCoords() const noexcept { return coords; }

    // comparison
    /**
    * @brief Key function of comparison
    * @return Tuple object containing the components
    */
    [[nodiscard]] auto Tie() const noexcept {
        return std::tie(Id, coords.getX(), coords.getY(), coords.getZ());
    }
private:
    MeshManager *meshManager;///< pointer to the parent manager
    u64 Id{0};               ///< the Id of the node
    base::Vector3 coords;    ///< coordinates of the node
};


}// namespace optim::mesh
