#include "classes/gf/GfChainAttack.h"
#include "classes/gf/GfMenuManager.h"
#include "gf/GfObjFactory.h"
#include "gf/GfPlayFactory.h"
#include "classes/gf/GfGameObj.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfInitParamDriver.h"
#include "classes/gf/GfMountManager.h"
#include "classes/gf/GfAllocator.h"

namespace gf {

GfChainAttack::~GfChainAttack() {}

void GfChainAttack::createPartyDriver() {
    for (unsigned int i = 0; i < 3; i++) {
        unsigned int id = GfGameParty::getDriverBdatId(i, static_cast<PTPOS>(0));
        if (id != 0) {
            GfInitParamDriver param;
            param.m_createType = 7;
            param.m_objId = id;
            param.pad_24 = 1;
            param.pad_40 = 10;
            param.pad_81 = false;
            param.pad_82 = 0;
            param.pad_50 = 0.0f;
            GF_OBJ_HANDLE* handle = GfObjFactory::createDriver(param);
            if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                m_drivers[i] = handle;
            }
        }
    }
}

void GfChainAttack::startSetup() {
    m_state = 1;
    m_update.set(this, &GfChainAttack::updateForSetup);
    GfMenuManager::openBtlModelView();
    createPartyDriver();
}

void GfChainAttack::updateForSetup(const fw::UpdateInfo&) {
    if (!GfMenuManager::isOpenBtlModelView()) {
        return;
    }
    for (int i = 0; i < 3; i++) {
        if (m_drivers[i] != reinterpret_cast<GF_OBJ_HANDLE*>(-1) && !GfGameObj::isValidGameObj(m_drivers[i], true, nullptr)) {
            return;
        }
    }
    m_state = 2;
    m_update.set(this, &GfChainAttack::updateForPlay);
}

void GfChainAttack::updateForPlay(const fw::UpdateInfo&) {}

void GfChainAttack::update(const fw::UpdateInfo& info) {
    if (m_update.isValid()) {
        m_update(info);
    }
}

GfChainAttack* GfChainAttack::create() {
    if (!GfPlayFactory::createChainAttack()) {
        return nullptr;
    }
    GfChainAttack* attack = get();
    if (attack == nullptr) {
#line 128
        attack = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfChainAttack();
    }
    return attack;
}

void GfChainAttack::destroy() {
    GfChainAttack* attack = get();
    if (attack != nullptr) {
        for (int i = 0; i < 3; i++) {
            if (attack->m_drivers[i] != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                GfGameObj::destroyGameObj(attack->m_drivers[i], 0.0f);
                attack->m_drivers[i] = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
            }
        }
        GfMenuManager::closeBtlModelView();
        attack->m_update = mm::mtl::Delegate<void(const fw::UpdateInfo&)>();
        attack->m_state = 0;
        delete attack;
    }
}

int GfChainAttack::getState() const {
    return m_state;
}

GF_OBJ_HANDLE* GfChainAttack::getDriverByPartyId(unsigned int id) const {
    if (m_state != 2) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    return m_drivers[id];
}

GfWeapon* GfChainAttack::getWeaponByPartyId(unsigned int id) const {
    return GfMountManager::getGfWeapon(getDriverByPartyId(id), GFATTACH(0));
}

}  // namespace gf
