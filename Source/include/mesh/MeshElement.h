//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once

#include "MeshNode.h"

namespace optim::mesh {

class MeshManager;

/**
 * @brief list of element Type
 */
enum class ElementForm {
    // OD element
    VOID,///< Void element, e.g. the void
    // 1D element
    BAR,///< Bar element meaning a bar
    // 2D elements
    TRIANGLE,  ///< 2D triangle element
    QUADRANGLE,///< 2D quadrangle element
    HEXAGON,   ///< 2D hexagon element
    // 3D elements
    TETRAHEDRON,///< 3D tetrahedron element
    PYRAMID,    ///< 3D pyramid element (pentahedron with 4 triangles faces and 1 quadrangle face)
    PRISM,      ///< 3D prism element (pentahedron with 2 triangles faces and 3 quadrangles faces)
    HEXAHEDRON, ///< 3D hexahedron element
};

/**
 * @brief list of supported ElementOrder
 */
enum class ElementOrder {
    NONE,     ///< Order 0 element (special elements)
    LINEAR,   ///< order 1 element
    QUADRATIC,///< order 2 elements
};

/**
 * @brief determine the number of nodes of an element base on type and order
 * @param[in] element_form the type of element
 * @param[in] element_order the order of element
 * @return the number of node for the element (negative number means
 * no theoretical value (special elements)
 */
[[nodiscard]] s8 getTheoreticalElementNodeNumber(
        const ElementForm &element_form,
        const ElementOrder &element_order) noexcept;

/**
 * @brief base class handling Element in mesh
 */
class MeshElement : public InequalityComparable<MeshElement> {
public:
    // definitions
    using NodeIterator = vector<shared_ptr<MeshNode>>::iterator;           ///< iterator on nodes
    using NodeConstIterator = vector<shared_ptr<MeshNode>>::const_iterator;///< constant iterator on nodes
    // constructors
    /**
     * @brief base default constructor
     * @param[in] manager pointer to the parent manager
     */
    explicit MeshElement(
            MeshManager *manager = nullptr) : meshManager{manager} {}
    /**
     * @brief parametric constructor
     * @param[in] manager pointer to the parent manager, exception is raised if nullptr
     * @param[in] element_id the Id of the element
     * @param[in] element_form the element type
     * @param[in] element_order the element order
     * @param[in] nodeIDList list of the node ID of this element, exception raised if the size mismatch theoretical one
     */
    MeshElement(
            MeshManager *manager,
            u64 element_id,
            const ElementForm &element_form,
            const ElementOrder &element_order,
            const vector<u64> &nodeIDList);
    // comparison
    /**
     * @brief Key function of comparison
     * @param[in] other the other element to compare
     * @return Tuple object containing the id of the element
     *
     * first sort by Id, then dimension, then number of nodes, then nodes ID
     */
    [[nodiscard]] constexpr bool operator<(const MeshElement &other) const noexcept {
        if (Id == other.Id) {
            if (getDimension() == other.getDimension()) {
                if (nodes.size() == other.nodes.size()) {
                    for (vector_index i = 0; i < nodes.size(); ++i) {
                        if (*(nodes[i]) != *(other.nodes[i]))
                            return *(nodes[i]) < *(other.nodes[i]);
                    }
                } else {
                    return nodes.size() < other.nodes.size();
                }
            } else {
                return getDimension() < other.getDimension();
            }
        } else {
            return Id < other.Id;
        }
        return false;
    }
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
     * @param AllThrow if true(default) will throw an exception(OK) in case of valid element
     *                 else, the method will throw exception only if validity issue.
     *
     * throw exceptions when error are founds
     */
    void checkValidity(bool AllThrow = true) const;
    /**
    * @brief determine the number of nodes of this element
    * @return the number of node for the element (negative number means no theoretical value (special elements)
    */
    [[nodiscard]] s8 getSupposedElementNodeNumber() const noexcept {
        return getTheoreticalElementNodeNumber(eType, eOrder);
    }
    /**
     * @brief get the actual number of nodes of this element
     * @return the number of nodes
     */
    [[nodiscard]] s8 getElementNodeNumber() const noexcept {
        return clamp8(static_cast<s64>(nodes.size()));
    }
    /**
     * @brief return the ID of the node
     * @return the ID of the node
     */
    [[nodiscard]] const u64 &getID() const noexcept { return Id; }
    /**
     * @brief affect the mesh to a manager (only if not already affected)
     * @param[in] newMeshManager the new mesh manager
     */
    void attachToMesh(MeshManager *newMeshManager) noexcept {
        if (meshManager == nullptr && newMeshManager != nullptr)
            meshManager = newMeshManager;
    }
    /**
     * @brief retrieve the element type
     * @return the element type
     */
    [[nodiscard]] const ElementForm &getType() const noexcept { return eType; }
    /**
     * @brief retrieve the element type
     * @return the element type
     */
    [[nodiscard]] ElementForm &getType() noexcept { return eType; }
    /**
     * @brief retrieve the element order
     * @return the element order
     */
    [[nodiscard]] const ElementOrder &getOrder() const noexcept { return eOrder; }
    /**
     * @brief retrieve the element order
     * @return the element order
     */
    [[nodiscard]] ElementOrder &getOrder() noexcept { return eOrder; }

    /**
     * @brief get the element dimension
     * @return the element dimension
     */
    [[nodiscard]] u8 getDimension()const noexcept{
        switch(eType){
            case ElementForm::VOID:
                return 0;
            case ElementForm::BAR:
                return 1;
            case ElementForm::TRIANGLE:
            case ElementForm::QUADRANGLE:
            case ElementForm::HEXAGON:
                return 2;
            case ElementForm::TETRAHEDRON:
            case ElementForm::PYRAMID:
            case ElementForm::PRISM:
            case ElementForm::HEXAHEDRON:
                return 3;
        }
        return 0;
    }
    /**
     * @brief get the beginning of the node's list
     * @return iterator to the beginning of the node's list
     */
    [[nodiscard]] NodeIterator getNodeBegin() noexcept { return nodes.begin(); }
    /**
     * @brief get the beginning of the node's list
     * @return const iterator to the beginning of the node's list
     */
    [[nodiscard]] NodeConstIterator getNodeBegin() const noexcept { return nodes.begin(); }
    /**
     * @brief get the ending of the node's list
     * @return iterator to the ending of the node's list
     */
    [[nodiscard]] NodeIterator getNodeEnd() noexcept { return nodes.end(); }
    /**
     * @brief get the ending of the node's list
     * @return const iterator to the ending of the node's list
     */
    [[nodiscard]] NodeConstIterator getNodeEnd() const noexcept { return nodes.end(); }

    /**
     * @brief return the list of node IDs
     * @return the list of node IDs
     */
    [[nodiscard]] vector<u64> getNodeIdList() const noexcept {
        vector<u64> result;
        for (const auto &node : nodes)
            result.emplace_back(node->getID());
        return result;
    }

private:
    MeshManager *meshManager;               ///< pointer to the parent manager
    u64 Id{0};                              ///< the element unique ID
    ElementForm eType{ElementForm::VOID};   ///< type of the element
    ElementOrder eOrder{ElementOrder::NONE};///< order of the element
    vector<shared_ptr<MeshNode>> nodes;     ///< list of the element's nodes
};

}// namespace optim::mesh
