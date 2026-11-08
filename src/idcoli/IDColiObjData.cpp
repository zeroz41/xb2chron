#include "classes/idcoli/IDColiObjBase.h"
#include "idcoli/IDColiObjData.h"
#include "classes/idcoli/IDColiObjCharCheck.h"
#include "classes/idcoli/IDColiObjPhantom.h"
#include "classes/idcoli/IDColiObjPhantomCheck.h"
#include "idcoli/IDColiTreeTop.h"
#include "idcoli/IDColiResult.h"
#include "idcoli/IDColiPrimitive.h"
#include "idcoli/IDColiUtilColi.h"
#include "idcoli/IDColiShapeWork.h"
#include "classes/idcoli/IDColiObjBase.h"
#include "idcoli/IDColiObjData.h"
#include "classes/idcoli/IDColiObjChar.h"
#include "classes/idcoli/IDColiObjCharCheck.h"
#include "classes/idcoli/IDColiObjPhantom.h"
#include "classes/idcoli/IDColiObjPhantomCheck.h"
#include "idcoli/IDColiTreeTop.h"
#include "idcoli/IDColiResult.h"
#include "idcoli/IDColiPrimitive.h"
#include "idcoli/IDColiUtilColi.h"

namespace idcoli {

void IDColiObjBase::sweepPush(IDColiObjBase* next) {
    if (next != nullptr) {
        for (int i = 0; i < 2; i++) {
            m_sweepNext[i] = next;
            IDColiObjBase* prev = next->m_sweepPrev[i];
            if (prev != nullptr) {
                prev->m_sweepNext[i] = this;
            }
            m_sweepPrev[i] = prev;
            next->m_sweepPrev[i] = this;
        }
    } else {
        m_sweepNext[0] = nullptr;
        m_sweepNext[1] = nullptr;
        m_sweepPrev[0] = nullptr;
        m_sweepPrev[1] = nullptr;
    }
    m_sweepMax[0] = 0.0f;
    m_sweepMax[1] = 0.0f;
}

void IDColiObjBase::sweepPop() {
    for (int i = 0; i < 2; i++) {
        IDColiObjBase* next = m_sweepNext[i];
        IDColiObjBase* prev = m_sweepPrev[i];
        if (prev != nullptr) {
            prev->m_sweepNext[i] = next;
        }
        if (next != nullptr) {
            next->m_sweepPrev[i] = prev;
        }
        m_sweepNext[i] = nullptr;
        m_sweepPrev[i] = nullptr;
    }
}

void IDColiObjBase::sweepTreeMax(IdSweepAxisType axis, IdVectorAxisType component) {
    if (m_flags & 0x80) {
        IDColiObjBase* next = m_sweepNext[axis];
        if (next != nullptr) {
            m_sweepMax[axis] = next->m_sweepMax[axis];
        }
    } else {
        m_sweepMax[axis] = (&m_max.x)[component];
        IDColiObjBase* next = m_sweepNext[axis];
        if (next != nullptr && (&m_max.x)[component] < next->m_sweepMax[axis]) {
            m_sweepMax[axis] = next->m_sweepMax[axis];
        }
    }
}


IDColiObjCharCheck::IDColiObjCharCheck(IDColiTreeTop* tree) : IDColiObjChar(tree) {}

bool IDColiObjCharCheck::testResultLine(IDColiResult& result, const IDColiInput& input) {
    const void* base = m_base;
    if ((result.m_ignoreMaterial & m_materialBit) == 0 && (m_state & 2) && !(m_flags & 3)) {
        if (!(m_flags & 0x100)) {
            return IDColiUtilColiResult::s_CallLine[m_baseType](result, input, base);
        }
        bool hit = false;
        const CHCLInfo* info = getInfo();
        const unsigned short* index = getPrimIndices(info);
        for (int i = 0; i < info->m_primIndexNum; i++, index++) {
            PrimWork& work = m_primWork[*index];
            hit |= IDColiUtilColiResult::s_CallLine[work.m_baseType](result, input, work.m_base);
        }
        return hit;
    }
    return false;
}

bool IDColiObjCharCheck::testResultRay(IDColiResult& result, const IDColiInput& input) {
    const void* base = m_base;
    if ((result.m_ignoreMaterial & m_materialBit) == 0 && (m_state & 2) && !(m_flags & 3)) {
        if (!(m_flags & 0x100)) {
            return IDColiUtilColiResult::s_CallRay[m_baseType](result, input, base);
        }
        bool hit = false;
        const CHCLInfo* info = getInfo();
        const unsigned short* index = getPrimIndices(info);
        for (int i = 0; i < info->m_primIndexNum; i++, index++) {
            PrimWork& work = m_primWork[*index];
            hit |= IDColiUtilColiResult::s_CallRay[work.m_baseType](result, input, work.m_base);
        }
        return hit;
    }
    return false;
}

bool IDColiObjCharCheck::testResultSphere(IDColiResult& result, const IDColiInput& input) {
    const void* base = m_base;
    if ((result.m_ignoreMaterial & m_materialBit) == 0 && (m_state & 2) && !(m_flags & 3)) {
        if (!(m_flags & 0x100)) {
            return IDColiUtilColiResult::s_CallSphere[m_baseType](result, input, base);
        }
        bool hit = false;
        const CHCLInfo* info = getInfo();
        const unsigned short* index = getPrimIndices(info);
        for (int i = 0; i < info->m_primIndexNum; i++, index++) {
            PrimWork& work = m_primWork[*index];
            hit |= IDColiUtilColiResult::s_CallSphere[work.m_baseType](result, input, work.m_base);
        }
        return hit;
    }
    return false;
}

bool IDColiObjCharCheck::testResultCapsule(IDColiResult& result, const IDColiInput& input) {
    const void* base = m_base;
    if ((result.m_ignoreMaterial & m_materialBit) == 0 && (m_state & 2) && !(m_flags & 3)) {
        if (!(m_flags & 0x100)) {
            return IDColiUtilColiResult::s_CallCapsule[m_baseType](result, input, base);
        }
        bool hit = false;
        const CHCLInfo* info = getInfo();
        const unsigned short* index = getPrimIndices(info);
        for (int i = 0; i < info->m_primIndexNum; i++, index++) {
            PrimWork& work = m_primWork[*index];
            hit |= IDColiUtilColiResult::s_CallCapsule[work.m_baseType](result, input, work.m_base);
        }
        return hit;
    }
    return false;
}

bool IDColiObjCharCheck::testCheckBox(IDColiResult& result, const IDColiInput& input) {
    const void* base = m_base;
    if ((result.m_ignoreMaterial & m_materialBit) == 0 && (m_state & 2) && !(m_flags & 3)) {
        return IDColiUtilColiSimple::s_CallBox[m_baseType](result, input, base);
    }
    return false;
}

bool IDColiObjCharCheck::testTypeLine(IDColiResult& result, const IDColiInput& input, ColiCheckType type) {
    const void* base = m_base;
    if ((result.m_ignoreMaterial & m_materialBit) == 0 && (m_state & 2) && !(m_flags & 3)) {
        if (!(m_flags & 0x100)) {
            if (type == 1) {
                if (!(m_flags & 0x400)) {
                    return false;
                }
            } else if (type == 2) {
                if (m_flags & 0x400) {
                    return false;
                }
            }
            return IDColiUtilColiResult::s_CallLine[m_baseType](result, input, base);
        }
        bool hit = false;
        const CHCLHeader* binary = m_binary;
        const CHCLInfo* info = getInfo();
        if (type == 1) {
            const unsigned short* index = binary->getIndices(info->m_type1IndexOffset);
            for (int i = 0; i < info->m_type1IndexNum; i++, index++) {
                PrimWork& work = m_primWork[*index];
                hit |= IDColiUtilColiResult::s_CallLine[work.m_baseType](result, input, work.m_base);
            }
        } else if (type == 2) {
            const unsigned short* index = binary->getIndices(info->m_type2IndexOffset);
            for (int i = 0; i < info->m_type2IndexNum; i++, index++) {
                PrimWork& work = m_primWork[*index];
                hit |= IDColiUtilColiResult::s_CallLine[work.m_baseType](result, input, work.m_base);
            }
        } else {
            const unsigned short* index = binary->getIndices(info->m_primIndexOffset);
            for (int i = 0; i < info->m_primIndexNum; i++, index++) {
                PrimWork& work = m_primWork[*index];
                hit |= IDColiUtilColiResult::s_CallLine[work.m_baseType](result, input, work.m_base);
            }
        }
        return hit;
    }
    return false;
}

bool IDColiObjCharCheck::testTypeSphere(IDColiResult& result, const IDColiInput& input, ColiCheckType type) {
    const void* base = m_base;
    if ((result.m_ignoreMaterial & m_materialBit) == 0 && (m_state & 2) && !(m_flags & 3)) {
        if (!(m_flags & 0x100)) {
            if (type == 1) {
                if (!(m_flags & 0x400)) {
                    return false;
                }
            } else if (type == 2) {
                if (m_flags & 0x400) {
                    return false;
                }
            }
            return IDColiUtilColiResult::s_CallSphere[m_baseType](result, input, base);
        }
        bool hit = false;
        const CHCLHeader* binary = m_binary;
        const CHCLInfo* info = getInfo();
        if (type == 2) {
            {
                const unsigned short* index = binary->getIndices(info->m_type1IndexOffset);
                for (int i = 0; i < info->m_type1IndexNum; i++, index++) {
                    PrimWork& work = m_primWork[*index];
                    hit |= IDColiUtilColiResult::s_CallSphere[work.m_baseType](result, input, work.m_base);
                }
            }
            {
                const unsigned short* index = binary->getIndices(info->m_type2IndexOffset);
                for (int i = 0; i < info->m_type2IndexNum; i++, index++) {
                    PrimWork& work = m_primWork[*index];
                    hit |= IDColiUtilColiResult::s_CallSphere[work.m_baseType](result, input, work.m_base);
                }
            }
        } else if (type == 1) {
            return false;
        } else {
            const unsigned short* index = binary->getIndices(info->m_primIndexOffset);
            for (int i = 0; i < info->m_primIndexNum; i++, index++) {
                PrimWork& work = m_primWork[*index];
                hit |= IDColiUtilColiResult::s_CallSphere[work.m_baseType](result, input, work.m_base);
            }
        }
        return hit;
    }
    return false;
}

bool IDColiObjCharCheck::testTypeCapsule(IDColiResult& result, const IDColiInput& input, ColiCheckType type) {
    const void* base = m_base;
    if ((result.m_ignoreMaterial & m_materialBit) == 0 && (m_state & 2) && !(m_flags & 3)) {
        if (!(m_flags & 0x100)) {
            if (type == 1) {
                if (!(m_flags & 0x400)) {
                    return false;
                }
            } else if (type == 2) {
                if (m_flags & 0x400) {
                    return false;
                }
            }
            return IDColiUtilColiResult::s_CallCapsule[m_baseType](result, input, base);
        }
        bool hit = false;
        const CHCLHeader* binary = m_binary;
        const CHCLInfo* info = getInfo();
        if (type == 2) {
            {
                const unsigned short* index = binary->getIndices(info->m_type2IndexOffset);
                for (int i = 0; i < info->m_type2IndexNum; i++, index++) {
                    PrimWork& work = m_primWork[*index];
                    hit |= IDColiUtilColiResult::s_CallCapsule[work.m_baseType](result, input, work.m_base);
                }
            }
            {
                const unsigned short* index = binary->getIndices(info->m_type1IndexOffset);
                for (int i = 0; i < info->m_type1IndexNum; i++, index++) {
                    PrimWork& work = m_primWork[*index];
                    hit |= IDColiUtilColiResult::s_CallCapsule[work.m_baseType](result, input, work.m_base);
                }
            }
        } else if (type == 1) {
            return false;
        } else {
            const unsigned short* index = binary->getIndices(info->m_primIndexOffset);
            for (int i = 0; i < info->m_primIndexNum; i++, index++) {
                PrimWork& work = m_primWork[*index];
                hit |= IDColiUtilColiResult::s_CallCapsule[work.m_baseType](result, input, work.m_base);
            }
        }
        return hit;
    }
    return false;
}

const char* IDColiObjData::getBoneName(int index) const {
    return reinterpret_cast<const char*>(m_binary) + m_boneInfo[index].m_nameOffset;
}

void IDColiObjData::setBoneMatrix(int index, const mm::Mat44& matrix) {
    m_boneMatrix[index] = matrix;
}

void IDColiObjData::primset_sphere(void* base, IDColiBaseType& type, const CHCLBaseData* data, const CHCLBaseInfo* info) {
    mm::Mat44 matrix;
    calcNodeMatrix(matrix, m_matrix, data, info);
    CLSphereWork* sphere = static_cast<CLSphereWork*>(base);
    mm::Vec3 axis(matrix.m[0][0] + matrix.m[1][0] + matrix.m[2][0], matrix.m[0][1] + matrix.m[1][1] + matrix.m[2][1],
                  matrix.m[0][2] + matrix.m[1][2] + matrix.m[2][2]);
    float radius = axis.length() * IDColiObj::OBJ_CALC_RADIUS;
    sphere->m_radius = data->m_size.x * radius;
    sphere->m_center = matrix.getTrans();
    type = IDCOLI_BASE_SPHERE;
}

void IDColiObjData::primset_capsule(void* base, IDColiBaseType& type, const CHCLBaseData* data, const CHCLBaseInfo* info) {
    mm::Mat44 matrix;
    calcNodeMatrix(matrix, m_matrix, data, info);
    IDColiPrimitive::createBaseCapsule(base, type, matrix, data->m_size);
}

void IDColiObjData::primset_bone_capsule(void* base, IDColiBaseType& type, const CHCLBaseData* data,
                                         const CHCLBaseInfo* info) {
    mm::Mat44 matrix;
    calcNodeMatrix(matrix, m_matrix, data, info);
    mm::Mat44 link;
    calcLinkNodeMatrix(link, info);
    CLCapsuleWork* capsule = static_cast<CLCapsuleWork*>(base);
    capsule->m_pos = matrix.getTrans();
    capsule->m_end = link.getTrans();
    mm::Vec3 axis(matrix.m[0][0] + matrix.m[1][0] + matrix.m[2][0], matrix.m[0][1] + matrix.m[1][1] + matrix.m[2][1],
                  matrix.m[0][2] + matrix.m[1][2] + matrix.m[2][2]);
    float radius = axis.length() * IDColiObj::OBJ_CALC_RADIUS;
    float dx = capsule->m_pos.x - capsule->m_end.x;
    float dy = capsule->m_pos.y - capsule->m_end.y;
    float dz = capsule->m_pos.z - capsule->m_end.z;
    if (dx * dx + dy * dy + dz * dz <= 0.001f) {
        // both ends at one point: a sphere
        CLSphereWork* sphere = static_cast<CLSphereWork*>(base);
        sphere->m_radius = radius * data->m_size.x;
        sphere->m_center = matrix.getTrans();
        type = IDCOLI_BASE_SPHERE;
    } else {
        capsule->m_radius = radius * data->m_size.x;
        IDColiPrimitive::calcCapsuleSetup(capsule);
        type = IDCOLI_BASE_CAPSULE;
    }
}

void IDColiObjData::primset_box(void* base, IDColiBaseType& type, const CHCLBaseData* data, const CHCLBaseInfo* info) {
    mm::Mat44 matrix;
    calcNodeMatrix(matrix, m_matrix, data, info);
    IDColiPrimitive::createBaseBox(base, type, matrix, data->m_size);
}

void IDColiObjData::primset_base(void* base, IDColiBaseType& type, const CHCLBaseData* data, const CHCLBaseInfo* info) {
    mm::Mat44 matrix;
    calcNodeMatrix(matrix, m_matrix, data, info);
    IDColiPrimitive::createBaseCharacter(base, type, matrix, data->m_size);
}

void IDColiObjData::primset_poli(void* base, IDColiBaseType& type, const CHCLBaseData* data, const CHCLBaseInfo* info) {
    mm::Mat44 matrix;
    calcNodeMatrix(matrix, m_matrix, data, info);
    IDColiPrimitive::createBasePoli(base, type, matrix, data->m_size);
}

void IDColiObjData::primset_subbase(void* base, IDColiBaseType& type, const CHCLBaseData* data, const CHCLBaseInfo* info) {
    mm::Mat44 matrix;
    calcNodeMatrix(matrix, m_matrix, data, info);
    IDColiPrimitive::createSubBaseCharacter(base, type, matrix, data->m_size, !(m_flags & 0x800));
}

IDColiObjChar::~IDColiObjChar() {
    releaseSubObj();
    releaseWork();
}

void IDColiObjChar::release() {
    m_userData = nullptr;
    setDeleteCall();
    releaseSubObj();
}

void IDColiObjChar::update() {
    if (!(m_flags & 0x80)) {
        pad_210 = 0;
        pad_214 = 0.0f;
        pad_218 = 0.0f;
        sizeUpdate();
    }
}

bool IDColiObjChar::SweepAndPruneUpdate() {
    bool moved = false;
    if (m_flags & 0x80) {
        return moved;
    }
    // moves this object along the axis's list past the objects whose m_min component is above its own
    auto sort = [this](int axis, int component) -> bool {
        IDColiObjBase* next = m_sweepNext[axis];
        if (next == nullptr) {
            return false;
        }
        IDColiObjBase* target = nullptr;
        for (IDColiObjBase* it = next; it != nullptr; it = it->m_sweepNext[axis]) {
            if ((&m_min.x)[component] >= (&it->m_min.x)[component]) {
                break;
            }
            target = it;
        }
        if (target == nullptr) {
            return false;
        }
        IDColiObjBase* prev = m_sweepPrev[axis];
        if (prev != nullptr) {
            prev->m_sweepNext[axis] = m_sweepNext[axis];
        }
        m_sweepNext[axis]->m_sweepPrev[axis] = prev;
        IDColiObjBase* after = target->m_sweepNext[axis];
        if (after != nullptr) {
            after->m_sweepPrev[axis] = this;
        }
        m_sweepNext[axis] = after;
        m_sweepPrev[axis] = target;
        target->m_sweepNext[axis] = this;
        return true;
    };
    moved = sort(0, 0);
    moved |= sort(1, 2);
    m_flags |= 0x1000;
    return moved;
}

void IDColiObjChar::consistentUpdate() {
    m_treeIndex = -1;
    if (!(m_flags & 0x80)) {
        m_treeIndex = m_tree->setupTreeList(&m_treeObj, m_max, m_min);
    }
}

IDColiObjPhantomCheck::IDColiObjPhantomCheck(IDColiTreeTop* tree) : IDColiObjPhantom(tree) {}

bool IDColiObjPhantomCheck::testResultLine(IDColiResult& result, const IDColiInput& input) {
    const void* base = m_base;
    if ((result.m_ignoreMaterial & m_materialBit) != 0 || (m_flags & 3) != 0) {
        return false;
    }
    return IDColiUtilColiResult::s_CallLine[m_baseType](result, input, base);
}

bool IDColiObjPhantomCheck::testResultSphere(IDColiResult& result, const IDColiInput& input) {
    const void* base = m_base;
    if ((result.m_ignoreMaterial & m_materialBit) != 0 || (m_flags & 3) != 0) {
        return false;
    }
    return IDColiUtilColiResult::s_CallSphere[m_baseType](result, input, base);
}

bool IDColiObjPhantomCheck::testResultCapsule(IDColiResult& result, const IDColiInput& input) {
    const void* base = m_base;
    if ((result.m_ignoreMaterial & m_materialBit) != 0 || (m_flags & 3) != 0) {
        return false;
    }
    return IDColiUtilColiResult::s_CallCapsule[m_baseType](result, input, base);
}

bool IDColiObjPhantomCheck::testCheckLine(IDColiResult& result, const IDColiInput& input) {
    const void* base = m_base;
    if ((result.m_ignoreMaterial & m_materialBit) != 0 || (m_flags & 3) != 0) {
        return false;
    }
    return IDColiUtilColiSimple::s_CallLine[m_baseType](result, input, base);
}

bool IDColiObjPhantomCheck::testCheckSphere(IDColiResult& result, const IDColiInput& input) {
    const void* base = m_base;
    if ((result.m_ignoreMaterial & m_materialBit) != 0 || (m_flags & 3) != 0) {
        return false;
    }
    return IDColiUtilColiSimple::s_CallSphere[m_baseType](result, input, base);
}

bool IDColiObjPhantomCheck::testCheckCapsule(IDColiResult& result, const IDColiInput& input) {
    const void* base = m_base;
    if ((result.m_ignoreMaterial & m_materialBit) != 0 || (m_flags & 3) != 0) {
        return false;
    }
    return IDColiUtilColiSimple::s_CallCapsule[m_baseType](result, input, base);
}

void IDColiObjPhantom::sizeUpdate() {
    if (!(m_flags & 0x80)) {
        IDColiPrimitive::s_CallPrimSet[m_shapeType](m_base, m_baseType, m_matrix, m_size);
        m_max = mm::Vec3(-100000.0f, -100000.0f, -100000.0f);
        m_min = mm::Vec3(100000.0f, 100000.0f, 100000.0f);
        IDColiPrimitive::s_CallAaBb[m_baseType](m_max, m_min, m_base);
    }
}

void IDColiObjPhantom::update() {
    sizeUpdate();
}

bool IDColiObjPhantom::SweepAndPruneUpdate() {
    bool moved = false;
    if (m_flags & 0x80) {
        return moved;
    }
    // moves this object along the axis's list past the objects whose m_min component is above its own
    auto sort = [this](int axis, int component) -> bool {
        IDColiObjBase* next = m_sweepNext[axis];
        if (next == nullptr) {
            return false;
        }
        IDColiObjBase* target = nullptr;
        for (IDColiObjBase* it = next; it != nullptr; it = it->m_sweepNext[axis]) {
            if ((&m_min.x)[component] >= (&it->m_min.x)[component]) {
                break;
            }
            target = it;
        }
        if (target == nullptr) {
            return false;
        }
        IDColiObjBase* prev = m_sweepPrev[axis];
        if (prev != nullptr) {
            prev->m_sweepNext[axis] = m_sweepNext[axis];
        }
        m_sweepNext[axis]->m_sweepPrev[axis] = prev;
        IDColiObjBase* after = target->m_sweepNext[axis];
        if (after != nullptr) {
            after->m_sweepPrev[axis] = this;
        }
        m_sweepNext[axis] = after;
        m_sweepPrev[axis] = target;
        target->m_sweepNext[axis] = this;
        return true;
    };
    moved = sort(0, 0);
    moved |= sort(1, 2);
    m_flags |= 0x1000;
    return moved;
}

void IDColiObjPhantom::consistentUpdate() {
    m_treeIndex = -1;
    if (!(m_flags & 0x80)) {
        m_treeIndex = m_tree->setupTreeList(&m_treeObj, m_max, m_min);
    }
}

IDColiTreeTop::~IDColiTreeTop() {}

ColiLinkList<IDColiTreeObj>* IDColiTreeTop::getObjList(int x, int z, int level) {
    unsigned int index = COLI_TBL_INDEX[level] + x + COLI_TBL_GRID[level] * z;
    return &m_objList[index];
}

void IDColiTreeTop::begin() {
    m_prevMax = m_max;
    m_prevMin = m_min;
    updateTree();
    m_max = mm::Vec3(-1000000.0f, -1000000.0f, -1000000.0f);
    m_min = mm::Vec3(1000000.0f, 1000000.0f, 1000000.0f);
    m_flags &= ~1;
}

}  // namespace idcoli
