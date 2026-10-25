#include "classes/idcoli/IDColiObjBase.h"
#include "idcoli/IDColiObjData.h"
#include "classes/idcoli/IDColiObjCharCheck.h"
#include "classes/idcoli/IDColiObjPhantom.h"
#include "classes/idcoli/IDColiObjPhantomCheck.h"
#include "idcoli/IDColiTreeTop.h"
#include "idcoli/IDColiResult.h"
#include "idcoli/IDColiPrimitive.h"
#include "idcoli/IDColiUtilColi.h"
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

bool IDColiObjCharCheck::testCheckBox(IDColiResult& result, const IDColiInput& input) {
    const void* base = m_base;
    if ((result.m_ignoreMaterial & m_materialBit) == 0 && (m_state & 2) && !(m_flags & 3)) {
        return IDColiUtilColiSimple::s_CallBox[m_baseType](result, input, base);
    }
    return false;
}

const char* IDColiObjData::getBoneName(int index) const {
    return reinterpret_cast<const char*>(m_binary) + m_boneInfo[index].m_nameOffset;
}

void IDColiObjData::setBoneMatrix(int index, const mm::Mat44& matrix) {
    m_boneMatrix[index] = matrix;
}

void IDColiObjData::primset_capsule(void* base, IDColiBaseType& type, const CHCLBaseData* data, const CHCLBaseInfo* info) {
    mm::Mat44 matrix;
    calcNodeMatrix(matrix, m_matrix, data, info);
    IDColiPrimitive::createBaseCapsule(base, type, matrix, data->m_size);
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

void IDColiObjChar::consistentUpdate() {
    m_treeIndex = -1;
    if (!(m_flags & 0x80)) {
        m_treeIndex = m_tree->setupTreeList(&m_treeObj, m_max, m_min);
    }
}

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

void IDColiObjPhantom::update() {
    sizeUpdate();
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

}  // namespace idcoli
