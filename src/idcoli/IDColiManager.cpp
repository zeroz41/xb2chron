#define MM_LIB_FROM_IDCOLI
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/idcoli/IDColiObj.h"
#include "classes/idcoli/IDColiObjBase.h"
#include "idcoli/IDColiObjData.h"
#include "idcoli/ColiLinkList.h"
#include "classes/idcoli/IDColiMemHandleAllocator.h"
#include "classes/idcoli/IDColiManager.h"
#include "classes/idcoli/IDColiObjGrand.h"
#include "classes/idcoli/IDColiObjPhantom.h"
#include "idcoli/IDColiAccMan.h"
#include "idcoli/IDColiGrandObj.h"
#include "idcoli/IDColiMove.h"
#include "idcoli/IDColiParms.h"
#include "idcoli/IDColiPrimitive.h"
#include "idcoli/IDColiTreeTop.h"
#include "classes/idcoli/IDColiObjChar.h"
#include "classes/idcoli/IDColiObjCharCheck.h"
#include "classes/idcoli/IDColiObjPhantomCheck.h"
#include "classes/idcoli/IDColiObjGrdChar.h"
#include <string.h>
#include "classes/idcoli/IDColiManager.h"
#include "classes/idcoli/IDColiMemHandleAllocator.h"
#include "classes/idcoli/IDColiObj.h"
#include "classes/idcoli/IDColiObjBase.h"
#include "classes/idcoli/IDColiObjChar.h"
#include "classes/idcoli/IDColiObjCharCheck.h"
#include "classes/idcoli/IDColiObjGrand.h"
#include "classes/idcoli/IDColiObjGrdChar.h"
#include "classes/idcoli/IDColiObjPhantom.h"
#include "classes/idcoli/IDColiObjPhantomCheck.h"
#include "idcoli/ColiLinkList.h"
#include "idcoli/IDColiAccMan.h"
#include "idcoli/IDColiGrandObj.h"
#include "idcoli/IDColiMove.h"
#include "idcoli/IDColiObjData.h"
#include "idcoli/IDColiParms.h"
#include "idcoli/IDColiTreeTop.h"
#include "mm/Mat44.h"
#include "ml/CriticalSection.h"
#include "mm/Vec3.h"
#include "mtl/MemManager.h"
#include "idcoli/IDColiDef.h"
#include "idcoli/IDColiPhantom.h"
#include "idcoli/IDColiCheckObj.h"
#include "idcoli/IDColiInput.h"
#include "idcoli/IDColiInputUtil.h"
#include "classes/fw/ColiCheckCallback.h"

namespace idcoli {

IDColiDef::IDColiDef() {
    pad_0 = false;
    m_radiusSq = 0.0f;
    pad_1 = true;
    pad_2 = true;
    m_callback = nullptr;
}

void IDColiMove::setShapeParms(float parm0, float parm1) {
    m_shapeParms[0] = parm0;
    m_shapeParms[1] = parm1;
}

void IDColiMove::setFloor(float floor) { m_floor = floor; }

void IDColiMove::setAccuracy(bool accuracy) { m_accuracy = accuracy; }

bool IDColiMove::moveColi(IDColiObj* obj, const mm::Vec3& move) {
    if (obj->m_state & (1 << 2)) {
        m_result = move;
        return true;
    }
    mm::Vec3 hitPos[32];
    mm::Vec3 hitNormal[32];
    unsigned int hitBits[3];
    m_coliResult.m_tblPos = hitPos;
    m_coliResult.m_type = 2;
    m_coliResult.m_tblMax = 32;
    m_coliResult.m_tblNormal = hitNormal;
    m_baseObj = obj;
    m_coliResult.pad_d8 = hitBits;
    m_coliResult.m_skipObj = obj;
    setupParms(move);
    IDColiObjData* data = static_cast<IDColiObjData*>(obj);
    m_coliResult.m_ignoreMaterial = data->m_offMaterialBit;
    m_adsorption = data->m_adsorption;
    calcCheckParams(m_move);
    pad_1f5 = false;
    if ((obj->m_state & (1 << 3)) && !(obj->m_attr & 1)) {
        pad_1f5 = true;
    }
    if (obj->m_flags & 0x100) {
        return moveDataColi();
    }
    IDColiPrimitive::s_CallBasePos[data->m_baseType](m_basePos, m_baseOffset, m_baseFlag, m_shapeParms[0],
                                                     m_shapeParms[1], data->m_base);
    return moveDefColi();
}

bool IDColiMove::calcWallHitChkVec(const mm::Vec3& normal, const mm::Vec3& pos, wrlResTempVec* temp) {
    if (!(m_move.y <= 0.0f)) return false;
    float x = pos.x - m_pos.x;
    float z = pos.z - m_pos.z;
    float length = ::sqrtf(x * x + z * z);
    if (!(length >= 0.01f)) {
        if (pad_1f1) return false;
        if (m_wallCount != 0) return true;
        pad_1f0 = true;
        return false;
    }
    if (pad_1f0) return true;
    float scale = 1.0f / length;
    x = x * scale;
    z = z * scale;
    if (normal.y > 0.01f) pad_1f2 = true;
    if (pad_1f2 && m_wallCount != 0) {
        for (int i = 0; i < m_wallCount; i++) {
            if (x * temp->m_dir[i].x + z * temp->m_dir[i].z < -0.8660254f) return true;
        }
        if (m_wallCount >= 2) {
            float angle = ::atan2f(x, z);
            float cos0 = ::cosf(2.0943952f - angle);
            float sin0 = ::sinf(2.0943952f - angle);
            float cos1 = ::cosf(-2.0943952f - angle);
            float sin1 = ::sinf(-2.0943952f - angle);
            unsigned int sides = 0;
            for (int i = 0; i < m_wallCount; i++) {
                if (!(sides & 1) && -sin0 * temp->m_dir[i].x + cos0 * temp->m_dir[i].z >= 0.49999997f) {
                    sides |= 1;
                    if (sides == 3) return true;
                }
                if (!(sides & 2) && -sin1 * temp->m_dir[i].x + cos1 * temp->m_dir[i].z >= 0.49999997f) {
                    sides |= 2;
                    if (sides == 3) return true;
                }
            }
        }
    }
    if (m_wallCount < 32) {
        temp->m_dir[m_wallCount].x = x;
        temp->m_dir[m_wallCount].z = z;
        m_wallCount++;
    }
    return false;
}

IDColiPhantom::IDColiPhantom() {
    pad_0 = false;
    m_radiusSq = 0.0f;
    pad_1 = true;
    pad_2 = true;
    m_callback = nullptr;
}

IDColiCheckObj::IDColiCheckObj() {
    pad_0 = false;
    m_radiusSq = 0.0f;
    pad_1 = true;
    pad_2 = true;
    m_callback = nullptr;
}

bool IDColiCheckObj::testLine(const IDColiObj* obj, const mm::Vec3& start, const mm::Vec3& end) {
    IDColiInput input;
    m_result.m_nearLength = 100000.0f;
    m_result.m_secNearLength = -100000.0f;
    m_result.m_tblNum = 0;
    m_result.m_nearHit = false;
    m_result.m_secNearHit = false;
    m_result.m_near.m_vector = mm::Vec3(0.0f, 0.0f, 0.0f);
    m_result.m_secNear.m_vector = mm::Vec3(0.0f, 0.0f, 0.0f);
    m_result.pad_f8 = nullptr;
    m_result.m_callback = m_callback;
    IDColiInputUtil::getLine(input, start, end, true);
    input.m_instSizeMin = m_radiusSq;
    m_result.pad_f8 = obj;
    m_result.m_obj = obj->m_userData;
    switch (obj->m_type) {
    case 1: {
        IDColiObjCharCheck* chr = static_cast<IDColiObjCharCheck*>(const_cast<IDColiObj*>(obj));
        if (m_result.m_type != 0) {
            if (!chr->testResultLine(m_result, input)) return false;
        } else {
            if (!chr->testCheckLine(m_result, input)) return false;
        }
        break;
    }
    case 2: {
        IDColiObjPhantomCheck* phantom = static_cast<IDColiObjPhantomCheck*>(const_cast<IDColiObj*>(obj));
        if (m_result.m_type != 0) {
            if (!phantom->testResultLine(m_result, input)) return false;
        } else {
            if (!phantom->testCheckLine(m_result, input)) return false;
        }
        break;
    }
    case 3: {
        if (obj->m_flags & 0x80) return false;
        // the grand test's IDColiGrandObj sits above the input on the stack: an inlined helper's local
        bool hit = [&]() {
            IDColiGrandObj grand(&static_cast<IDColiObjGrand*>(const_cast<IDColiObj*>(obj))->m_work);
            return grand.testLine(m_result, input);
        }();
        if (!hit) return false;
        break;
    }
    default:
        return false;
    }
    if (m_result.m_type == 1 && m_callback != nullptr) {
        m_callback->coli_param_callback(m_result.m_nearObj, m_result.m_near);
    }
    return true;
}

bool IDColiCheckObj::testSphere(const IDColiObj* obj, const mm::Vec3& pos, float radius) {
    IDColiInput input;
    m_result.m_nearLength = 100000.0f;
    m_result.m_secNearLength = -100000.0f;
    m_result.m_tblNum = 0;
    m_result.m_nearHit = false;
    m_result.m_secNearHit = false;
    m_result.m_near.m_vector = mm::Vec3(0.0f, 0.0f, 0.0f);
    m_result.m_secNear.m_vector = mm::Vec3(0.0f, 0.0f, 0.0f);
    m_result.pad_f8 = nullptr;
    m_result.m_callback = m_callback;
    IDColiInputUtil::getSphere(input, pos, radius, true);
    input.m_instSizeMin = m_radiusSq;
    m_result.pad_f8 = obj;
    m_result.m_obj = obj->m_userData;
    switch (obj->m_type) {
    case 1: {
        IDColiObjCharCheck* chr = static_cast<IDColiObjCharCheck*>(const_cast<IDColiObj*>(obj));
        if (m_result.m_type != 0) {
            if (!chr->testResultSphere(m_result, input)) return false;
        } else {
            if (!chr->testCheckSphere(m_result, input)) return false;
        }
        break;
    }
    case 2: {
        IDColiObjPhantomCheck* phantom = static_cast<IDColiObjPhantomCheck*>(const_cast<IDColiObj*>(obj));
        if (m_result.m_type != 0) {
            if (!phantom->testResultSphere(m_result, input)) return false;
        } else {
            if (!phantom->testCheckSphere(m_result, input)) return false;
        }
        break;
    }
    case 3: {
        if (obj->m_flags & 0x80) return false;
        // the grand test's IDColiGrandObj sits above the input on the stack: an inlined helper's local
        bool hit = [&]() {
            IDColiGrandObj grand(&static_cast<IDColiObjGrand*>(const_cast<IDColiObj*>(obj))->m_work);
            return grand.testSphere(m_result, input, false);
        }();
        if (!hit) return false;
        break;
    }
    default:
        return false;
    }
    if (m_result.m_type == 1 && m_callback != nullptr) {
        m_callback->coli_param_callback(m_result.m_nearObj, m_result.m_near);
    }
    return true;
}

void* IDColiMemHandleAllocator::allocate(unsigned long size, unsigned long alignment) {
    return mtl::MemManager::allocate(m_allocHandle, size, alignment, false, "no name", 0);
}

void IDColiMemHandleAllocator::deallocate(void* memory) {
    if (memory != nullptr) {
        mtl::MemManager::deallocate(memory, 0, false);
    }
}

IDColiManager::~IDColiManager() {
    release();
    if (m_gblIdBits != nullptr) {
        mtl::MemManager::deallocate(m_gblIdBits, 0, false);
        m_gblIdBits = nullptr;
    }
    if (m_charTree != nullptr) {
        delete m_charTree;
        m_charTree = nullptr;
    }
    if (m_phantomTree != nullptr) {
        delete m_phantomTree;
        m_phantomTree = nullptr;
    }
    if (m_allocHandle.m_handle != 0) {
        mtl::MemManager::erase(m_allocHandle);
        m_allocHandle.m_handle = 0;
    }
}

void IDColiManager::release() {
    for (int i = 0; i < 2; i++) {
        for (int kind = 0; kind < KIND_NUM; kind++) {
            ColiLinkList<IDColiObj>& list = m_addList[kind][i];
            for (IDColiObj* obj = list.m_head; obj != nullptr;) {
                IDColiObj* next = obj->m_next;
                delete obj;
                obj = next;
            }
            list.m_head = nullptr;
            list.m_tail = nullptr;
        }
    }
    for (int kind = 0; kind < KIND_NUM; kind++) {
        ColiLinkList<IDColiObj>& list = m_objList[kind];
        for (IDColiObj* obj = list.m_head; obj != nullptr;) {
            IDColiObj* next = obj->m_next;
            delete obj;
            obj = next;
        }
        list.m_head = nullptr;
        list.m_tail = nullptr;
    }
}

void IDColiManager::update() {
    addDelUpdate();
    for (int kind = 0; kind < KIND_NUM; kind++) {
        for (IDColiObj* obj = m_objList[kind].m_head; obj != nullptr; obj = obj->m_next) {
            obj->update();
        }
    }
}

void IDColiManager::consistentUpdate() {
    m_charTree->begin();
    m_phantomTree->begin();
    updateConsistentList(m_objList[KIND_CHARACTER]);
    updateConsistentList(m_objList[KIND_PHANTOM]);
    m_charTree->end();
    m_phantomTree->end();
}

void IDColiManager::tail() {
    int debIdx = s_nDebIdx;
    s_nDebIdx = debIdx == 0;
    s_nStkIdx = debIdx != 0;
}

// the lock the createColi* functions share: one static, one guard. Proposed name, not the original's: the symbols
// leave it unnamed (lbl_71015E9C40, its guard lbl_71015E9C68); the function holding it is inline everywhere
static ml::CriticalSection& getCreateCS() {
    static ml::CriticalSection s_createCS;
    return s_createCS;
}

IDColiObj* IDColiManager::createColiGrand(const void* data) {
    ml::CS lock(getCreateCS());
    IDColiObjGrand* obj = new (m_allocHandle, nullptr, 0, 4, false) IDColiObjGrand();
    obj->createGrand(m_allocHandle, data);
    m_addList[KIND_GRAND][s_nStkIdx].pushBack(obj);
    return obj;
}

IDColiObj* IDColiManager::createColiCharacter() {
    ml::CS lock(getCreateCS());
    IDColiObjCharCheck* obj = new (m_allocHandle, nullptr, 0, 4, false) IDColiObjCharCheck(m_charTree);
    m_addList[KIND_CHARACTER][s_nStkIdx].pushBack(obj);
    return obj;
}

IDColiObj* IDColiManager::createColiPhantom() {
    ml::CS lock(getCreateCS());
    IDColiObjPhantomCheck* obj = new (m_allocHandle, nullptr, 0, 4, false) IDColiObjPhantomCheck(m_phantomTree);
    m_addList[KIND_PHANTOM][s_nStkIdx].pushBack(obj);
    return obj;
}

IDColiObj* IDColiManager::createColiGrdChar() {
    ml::CS lock(getCreateCS());
    IDColiObjGrdChar* obj = new (m_allocHandle, nullptr, 0, 4, false) IDColiObjGrdChar();
    m_addList[KIND_GRDCHAR][s_nStkIdx].pushBack(obj);
    return obj;
}

inline IDColiObj* IDColiManager::getSweepTop(ColiLinkList<IDColiObj>& list) {
    for (IDColiObj* obj = list.m_head; obj != nullptr; obj = obj->m_next) {
        if (!(obj->m_flags & (1 << s_nDebIdx)) && !(obj->m_state & 4) && !(obj->m_flags & 0x80)) {
            return obj;
        }
    }
    return nullptr;
}

void IDColiManager::addList(ColiLinkList<IDColiObj>& list, ColiLinkList<IDColiObj>& add, bool sweep) {
    for (IDColiObj* obj = add.m_head; obj != nullptr;) {
        IDColiObj* next = obj->m_next;
        add.remove(obj);
        if (sweep) {
            static_cast<IDColiObjBase*>(obj)->sweepPush(static_cast<IDColiObjBase*>(getSweepTop(list)));
        }
        list.pushBack(obj);
        obj = next;
    }
    add = ColiLinkList<IDColiObj>();
}

unsigned int IDColiManager::isGblId(unsigned int id) { return m_gblIdBits[id >> 5] & (1 << (id & 0x1F)); }

void IDColiManager::setGblId(unsigned int id, bool clear) {
    unsigned int bit = 1 << (id & 0x1F);
    if (clear) {
        m_gblIdBits[id >> 5] &= ~bit;
    } else {
        m_gblIdBits[id >> 5] |= bit;
    }
}

IDColiObj::IDColiObj()
    : m_prev(nullptr), m_next(nullptr), m_state(3), m_flags(0), m_attr(9), pad_28(0), m_materialBit(0),
      pad_30(nullptr), pad_38(nullptr), pad_40(0), m_userData(nullptr) {}

void IDColiObj::release() {
    m_userData = nullptr;
    setDeleteCall();
}

void IDColiObj::setDeleteCall() { m_flags |= 1 << IDColiManager::s_nStkIdx; }

void IDColiParmsBase::setPriority(int priority) { m_obj->m_priority = priority; }

int IDColiParmsBase::getPriority() const { return m_obj->m_priority; }

void IDColiParmsBase::setUserData(void* userData) { m_obj->m_userData = userData; }

bool IDColiParmsBase::isAttr(ColiAtrr attr) const { return (m_obj->m_attr & (1 << attr)) != 0; }

bool IDColiParmsBase::isState(ColiState state) const { return (m_obj->m_state & (1 << state)) != 0; }

void IDColiParmsBase::setState(ColiState state) {
    IDColiObjBase* obj = m_obj;
    obj->m_state |= 1 << state;
}

void IDColiParmsBase::clearState(ColiState state) {
    IDColiObjBase* obj = m_obj;
    obj->m_state &= ~(1 << state);
}

void IDColiParmsBase::setMaterialBit(unsigned int bit) { m_obj->m_materialBit = bit; }

void IDColiParmsBase::setOffMaterialBit(unsigned int bit) { m_obj->m_offMaterialBit = bit; }

unsigned int IDColiParmsBase::getOffMaterialBit() const { return m_obj->m_offMaterialBit; }

void IDColiParmsBase::setMatrix(const mm::Mat44& matrix) {
    m_obj->m_matrix = matrix;
    m_obj->m_flags |= 8 << IDColiManager::s_nStkIdx;
}

const mm::Vec3& IDColiParmsBase::getMax() const { return m_obj->m_max; }

const mm::Vec3& IDColiParmsBase::getMin() const { return m_obj->m_min; }

void IDColiParmsBase::setInstantlyMatrix(const mm::Mat44& matrix) {
    setMatrix(matrix);
    m_obj->sizeUpdate();
}

IDColiParmsCharacter::IDColiParmsCharacter(IDColiObj* obj)
    : IDColiParmsBase(obj), m_data(static_cast<IDColiObjData*>(obj)) {}

void IDColiParmsCharacter::createSphere(float radius) {
    m_data->m_size = mm::Vec3(radius, radius, radius);
    m_data->m_shapeType = 0;
    m_data->m_flags |= 0x20;
}

void IDColiParmsCharacter::createCapsule(float height, float radius, bool flag) {
    m_data->m_size = mm::Vec3(radius, height, radius);
    if (flag) {
        m_data->m_shapeType = 7;
        m_data->m_flags |= 0x400;
    } else {
        m_data->m_shapeType = 2;
        m_data->m_flags &= ~0x400;
    }
    m_data->m_flags |= 0x20;
}

void IDColiParmsCharacter::createBox(const mm::Vec3& size, bool flag) {
    m_data->m_size = size;
    if (flag) {
        m_data->m_shapeType = 6;
        m_data->m_flags |= 0x400;
    } else {
        m_data->m_shapeType = 1;
        m_data->m_flags &= ~0x400;
    }
    m_data->m_flags |= 0x20;
}

void IDColiParmsCharacter::createCharacter(float height, float radius) {
    m_data->m_size = mm::Vec3(radius, height, radius);
    m_data->m_shapeType = 3;
    m_data->m_flags |= 0x20;
}

void IDColiParmsCharacter::createData(const void* data) { m_data->createBinary(data); }

void IDColiParmsCharacter::setAdsorption(float adsorption) { m_data->m_adsorption = adsorption; }

float IDColiParmsCharacter::getAdsorption() const { return m_data->m_adsorption; }

IDColiParmsBone::IDColiParmsBone(IDColiObj* obj) : m_data(static_cast<IDColiObjData*>(obj)) {}

int IDColiParmsBone::getBoneMax() const { return m_data->m_boneNum; }

const char* IDColiParmsBone::getBoneName(int index) const { return m_data->getBoneName(index); }

void IDColiParmsBone::setBoneMatrix(int index, const mm::Mat44& matrix) { m_data->setBoneMatrix(index, matrix); }

IDColiParmsPhantom::IDColiParmsPhantom(IDColiObj* obj)
    : IDColiParmsBase(obj), m_phantom(static_cast<IDColiObjPhantom*>(obj)) {}

void IDColiParmsPhantom::createSphere(float radius) {
    m_phantom->m_size = mm::Vec3(radius, radius, radius);
    m_phantom->m_shapeType = 0;
    m_phantom->m_flags |= 0x20;
}

void IDColiParmsPhantom::createCapsule(float height, float radius) {
    m_phantom->m_size = mm::Vec3(radius, height, radius);
    m_phantom->m_shapeType = 2;
    m_phantom->m_flags |= 0x20;
}

void IDColiParmsPhantom::createBox(const mm::Vec3& size) {
    m_phantom->m_size = size;
    m_phantom->m_shapeType = 1;
    m_phantom->m_flags |= 0x20;
}

void IDColiParmsPhantom::createCharacter(float height, float radius) {
    m_phantom->m_size = mm::Vec3(radius, height, radius);
    m_phantom->m_shapeType = 3;
    m_phantom->m_flags |= 0x20;
}

void IDColiPartsMoveGrand::setMatrix(const mm::Mat44& matrix) { m_obj->setMat(matrix); }

void IDColiPartsMoveGrand::setUserData(void* userData) { m_obj->m_userData = userData; }

IDColiParmsGrand::IDColiParmsGrand(IDColiObj* obj) : m_grand(&static_cast<IDColiObjGrand*>(obj)->m_work) {}

IDColiPartsMoveGrand IDColiParmsGrand::getMoveObj(unsigned int index) {
    return IDColiPartsMoveGrand(&m_grand->m_moveObjs[index]);
}

int IDColiParmsGrand::getMoveObjIdx(const char* name) {
    int num = m_grand->m_moveObjNum;
    for (int i = 0; i < num; i++) {
        if (strcmp(m_grand->m_moveObjs[i].m_name, name) == 0) {
            return i;
        }
    }
    return -1;
}

IDColiAccMan::IDColiAccMan() {}

IDColiObj* IDColiAccMan::createColiGrand(const void* data) { return IDColiManager::get()->createColiGrand(data); }

IDColiObj* IDColiAccMan::createColiCharacter() { return IDColiManager::get()->createColiCharacter(); }

IDColiObj* IDColiAccMan::createColiPhantom() { return IDColiManager::get()->createColiPhantom(); }

bool IDColiAccMan::getGrandAABB(mm::Vec3& max, mm::Vec3& min) const {
    IDColiManager* manager = IDColiManager::get();
    max = mm::Vec3(-10000.0f, -10000.0f, -10000.0f);
    min = mm::Vec3(10000.0f, 10000.0f, 10000.0f);
    bool found = false;
    for (IDColiObj* obj = manager->m_objList[IDColiManager::KIND_GRAND].m_head; obj != nullptr; obj = obj->m_next) {
        static_cast<IDColiObjGrand*>(obj)->getGrandAABB(max, min);
        found = true;
    }
    if (!found) {
        max = mm::Vec3(100.0f, 100.0f, 100.0f);
        min = mm::Vec3(-100.0f, -100.0f, -100.0f);
    }
    return found;
}

void IDColiAccMan::setSubNum(unsigned int num) { IDColiManager::get()->m_subNum = num; }

}  // namespace idcoli
