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

namespace idcoli {

void IDColiMove::setShapeParms(float parm0, float parm1) {
    m_shapeParms[0] = parm0;
    m_shapeParms[1] = parm1;
}

void IDColiMove::setFloor(float floor) { m_floor = floor; }

void IDColiMove::setAccuracy(bool accuracy) { m_accuracy = accuracy; }

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
