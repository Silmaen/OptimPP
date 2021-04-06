//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#pragma once

#include "MeshElement.h"

namespace optim::mesh {

/**
 * @brief Base class for mesh management
 */
class MeshManager {
public:
    // definitions
    using NodeIterator = vector<shared_ptr<MeshNode>>::iterator;                 ///< iterator on nodes
    using NodeConstIterator = vector<shared_ptr<MeshNode>>::const_iterator;      ///< constant iterator on nodes
    using ElementIterator = vector<shared_ptr<MeshElement>>::iterator;           ///< iterator on elements
    using ElementConstIterator = vector<shared_ptr<MeshElement>>::const_iterator;///< constant iterator on elements

    /**
     * @brief clear the mesh
     */
    void clear() noexcept {
        nodes.clear();
        elements.clear();
    }

    // comparison
    /**
     * @brief comparison operator
     * @param other the other mesh to compare
     * @return true if the mesh contains the same elements
     */
    bool operator==(const MeshManager& other)const noexcept;

    /**
     * @brief Comparison operator
     * @param other the other mesh to compare
     * @return true if the mesh contains different data
     */
    bool operator!=(const MeshManager& other)const noexcept;

    // access
    /**
     * @brief retrieve node by its ID
     * @param[in] id the node Id to find
     * @return pointer to the node nullptr if not found
     */
    [[nodiscard]] shared_ptr<MeshNode> getNodeByID(u64 id) const noexcept;

    /**
     * @brief retrieve element by its ID
     * @param[in] id the element Id to find
     * @return pointer to the element nullptr if not found
     */
    [[nodiscard]] shared_ptr<MeshElement> getElementByID(u64 id) const noexcept;

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
     * @brief get the beginning of the element's list
     * @return iterator to the beginning of the element's list
     */
    [[nodiscard]] ElementIterator getElementBegin() noexcept { return elements.begin(); }
    /**
     * @brief get the beginning of the element's list
     * @return const iterator to the beginning of the element's list
     */
    [[nodiscard]] ElementConstIterator getElementBegin() const noexcept { return elements.begin(); }

    /**
     * @brief get the ending of the element's list
     * @return iterator to the ending of the element's list
     */
    [[nodiscard]] ElementIterator getElementEnd() noexcept { return elements.end(); }

    /**
     * @brief get the ending of the element's list
     * @return const iterator to the ending of the element's list
     */
    [[nodiscard]] ElementConstIterator getElementEnd() const noexcept { return elements.end(); }

    /**
     * @brief create a node in the mesh
     * @param[in] Id the node ID
     * @param[in] x first coordinate of the node
     * @param[in] y second coordinate of the node
     * @param[in] z third coordinate of the node
     * @return a reference to the pointer to the created node
     */
    shared_ptr<MeshNode> &createNode(u64 Id, double x, double y, double z);

    /**
     * @brief create a node in the mesh
     * @param[in] Id the node ID
     * @param[in] v coordinates of the node
     * @return a reference to the pointer to the created node
     */
    shared_ptr<MeshNode> &createNode(u64 Id, const base::Vector3 &v);

    /**
     * @brief create a element in the mesh
     * @param[in] Id the element ID
     * @param[in] element_form type of the element
     * @param[in] element_order order of the element
     * @param[in] nodeIDList list of the element's node
     * @return a reference to the pointer to the created element
     */
    shared_ptr<MeshElement> &createElement(
            u64 Id,
            const ElementForm &element_form,
            const ElementOrder &element_order,
            const vector<u64> &nodeIDList);

    /**
     * @brief get the number of nodes in the mesh
     * @return the number of nodes
     */
    [[nodiscard]] u64 getNbNodes()const noexcept { return nodes.size(); }

    /**
     * @brief get the number of elements in the mesh
     * @return the number of elements
     */
    [[nodiscard]] u64 getNbElements()const noexcept { return elements.size(); }

    /**
     * @brief sort all item by their ID
     */
    void sortMeshItems();

private:
    vector<shared_ptr<MeshNode>> nodes;      ///< the list of nodes
    vector<shared_ptr<MeshElement>> elements;///< the list of elements
};

}// namespace optim::mesh
