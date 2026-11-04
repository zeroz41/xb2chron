#include "classes/gf/GfTrinityAttack.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfGameObj.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMountManager.h"
#include "classes/gf/GfWeapon.h"
#include "gf/GfDataDriver.h"
#include "gf/GfObjUtil.h"
#include "gf/GfObjFactory.h"
#include "classes/gf/GfInitParamBlade.h"
#include "classes/gf/GfAllocator.h"

namespace gf {

GfTrinityAttack::~GfTrinityAttack() {}

// the partner blade of the leader's (driver 1) engaged blade engaged, when it is engagedId and the partner is set
// (inline: the name is not the original's)
static inline unsigned int findPartnerBlade(unsigned int engagedId, unsigned int partnerId) {
    if (GfGameParty::getDriverBdatId(0, static_cast<PTPOS>(0)) == 1) {
        int engaged = GfDataDriver::getBladeSet(1);
        if (GfGameParty::getBladeBdatId(0, engaged) == engagedId) {
            int count = GfDataDriver::getMaxSetBladeNum(1);
            for (int slot = 0; slot < count; slot++) {
                if (slot != engaged && GfGameParty::getBladeBdatId(0, slot) == partnerId) {
                    return partnerId;
                }
            }
        }
    }
    return 0;
}

unsigned int GfTrinityAttack::getBladeId() const {
    unsigned int id = findPartnerBlade(1001, 1011);
    if (id != 0) {
        return id;
    }
    return findPartnerBlade(1011, 1001);
}

bool GfTrinityAttack::isLoading() const {
    if (!GfGameObj::isValidGameObj(m_blade, true, nullptr)) {
        return true;
    }
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_blade, GFATTACH(3));
    if (weapon != nullptr) {
        for (int i = 0; i < 10; i++) {
            GF_OBJ_HANDLE* handle = weapon->getObjHandles()[i];
            if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) && !GfGameObj::isValidGameObj(handle, true, nullptr)) {
                return true;
            }
        }
    }
    return false;
}

void GfTrinityAttack::startAttack() {
    m_state = 1;
    m_update.set(this, &GfTrinityAttack::updateForSetup);
    unsigned int bladeId = getBladeId();
    GfInitParamBlade param;
    unsigned int partyId = GfGameParty::getPartyId(GfGameManager::getPartyLeaderDriver());
    param.m_createType = 8;
    param.m_objId = bladeId;
    param.pad_40 = 4;
    param.pad_81 = false;
    param.pad_20 = partyId;
    param.pad_a0 = 3;
    param.pad_50 = 0.0f;
    param.pad_38 = GfGameManager::getPartyLeaderDriver();
    m_blade = GfObjFactory::createBlade(param);
    GF_OBJ_HANDLE* driver = GfGameManager::getPartyLeaderDriver();
    GF_MOUNT_HANDLE* mount = GfObjUtil::getMountHandle(m_blade, GFATTACH(3));
    if (mount != reinterpret_cast<GF_MOUNT_HANDLE*>(-1)) {
        GfMountManager::removeMountHandle(driver, GFATTACH(3));
        GfMountManager::addMountHandle(mount, driver);
    }
}

void GfTrinityAttack::updateForSetup(const fw::UpdateInfo&) {
    if (!isLoading()) {
        m_state = 2;
        m_update.set(this, &GfTrinityAttack::updateForPlay);
    }
}

void GfTrinityAttack::endAttack() {
    GF_OBJ_HANDLE* driver = GfGameManager::getPartyLeaderDriver();
    if (GfObjUtil::getMountHandle(driver, GFATTACH(3)) != reinterpret_cast<GF_MOUNT_HANDLE*>(-1)) {
        GfMountManager::removeMountHandle(driver, GFATTACH(3));
    }
    GfObjUtil::destroy(m_blade);
    m_blade = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    m_update = mm::mtl::Delegate<void(const fw::UpdateInfo&)>();
    m_state = 0;
}

void GfTrinityAttack::updateForPlay(const fw::UpdateInfo&) {}

void GfTrinityAttack::update(const fw::UpdateInfo& info) {
    if (m_update.isValid()) {
        m_update(info);
    }
}

GfTrinityAttack* GfTrinityAttack::create() {
    GfTrinityAttack* attack = get();
    if (attack == nullptr) {
#line 189
        attack = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfTrinityAttack();
    }
    return attack;
}

void GfTrinityAttack::destroy() {
    GfTrinityAttack* attack = get();
    if (attack != nullptr) {
        if (attack->m_blade != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            GfGameObj::destroyGameObj(attack->m_blade, 0.0f);
            attack->m_blade = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
        }
        attack->m_update = mm::mtl::Delegate<void(const fw::UpdateInfo&)>();
        attack->m_state = 0;
        delete attack;
    }
}

int GfTrinityAttack::getState() const {
    return m_state;
}

GF_OBJ_HANDLE* GfTrinityAttack::getBlade() const {
    return m_blade;
}

GfWeapon* GfTrinityAttack::getWeapon() const {
    return GfMountManager::getGfWeapon(m_blade, GFATTACH(3));
}

}  // namespace gf
