//---------------------------------------------------------------------------------------------
// this file is the property of Damien Lachouette every copy is strictly forbidden
//---------------------------------------------------------------------------------------------

#include "mesh/MeshElement.h"
#include "base/Exception.h"
#include "mesh/MeshManager.h"

namespace optim::mesh {

MeshElement::MeshElement(
        MeshManager *manager,
        u64 element_id,
        const ElementForm &element_form,
        const ElementOrder &element_order,
        const vector<u64> &nodeIDList) : meshManager{manager}, Id{element_id}, eType{element_form}, eOrder{element_order} {
    if (meshManager == nullptr)
        throw Exception(ExitCode::Value::NoMeshManager);
    s8 sNodeNum = getSupposedElementNodeNumber();
    if (sNodeNum >= 0 && static_cast<u8>(sNodeNum) != nodeIDList.size())
        throw Exception(ExitCode::Value::WrongNodeNumber);
    nodes.clear();
    nodes.reserve(nodeIDList.size());
    for (auto nid : nodeIDList) {
        auto n = meshManager->getNodeByID(nid);
        if (n == nullptr)
            throw Exception(ExitCode::Value::WrongNodeId);
        n->checkValidity(false);// false: throw only if error
        nodes.push_back(n);
    }
}

bool MeshElement::isValid() const noexcept {
    try {
        checkValidity(true);
    } catch (Exception &e) {
        if (e.GetCode() == ExitCode::Value::OK)
            return true;
    }
    return false;
}

void MeshElement::checkValidity(bool AllThrow) const {
    if (meshManager == nullptr)
        throw Exception(ExitCode::Value::NoMeshManager);
    if (getSupposedElementNodeNumber() >= 0 && getSupposedElementNodeNumber() != getElementNodeNumber())
        throw Exception(ExitCode::Value::WrongNodeNumber);
    for (const auto &node : nodes)
        node->checkValidity(false);// false: throw only if error
    if (AllThrow) throw Exception(ExitCode::Value::OK);
}

s8 getTheoreticalElementNodeNumber(
        const ElementForm &element_form,
        const ElementOrder &element_order) noexcept {
    switch (element_order) {
        case ElementOrder::NONE:
            return -1;
        case ElementOrder::LINEAR:
            switch (element_form) {
                case ElementForm::VOID:
                    return 0;
                case ElementForm::BAR:
                    return 2;
                case ElementForm::TRIANGLE:
                    return 3;
                case ElementForm::QUADRANGLE:
                    return 4;
                case ElementForm::HEXAGON:
                    return 6;
                case ElementForm::TETRAHEDRON:
                    return 4;
                case ElementForm::PYRAMID:
                    return 5;
                case ElementForm::PRISM:
                    return 6;
                case ElementForm::HEXAHEDRON:
                    return 8;
            }
            break;
        case ElementOrder::QUADRATIC:
            switch (element_form) {
                case ElementForm::VOID:
                    return 0;
                case ElementForm::BAR:
                    return 3;
                case ElementForm::TRIANGLE:
                    return 6;
                case ElementForm::QUADRANGLE:
                    return 8;
                case ElementForm::HEXAGON:
                    return 12;
                case ElementForm::TETRAHEDRON:
                    return 9;
                case ElementForm::PYRAMID:
                    return 13;
                case ElementForm::PRISM:
                    return 15;
                case ElementForm::HEXAHEDRON:
                    return 20;
            }
            break;
    }
    return -1;
}

}// namespace optim::mesh
