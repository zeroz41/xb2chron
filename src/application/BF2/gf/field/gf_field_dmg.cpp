#include <string.h>
#include "classes/gf/GfFieldDmg.h"
#include "classes/gf/GfFieldDmgManager.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/GfGameUtil.h"
#include "gf/MapjumpCallbackInfo.h"
#include "fw/ColiDamage.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfObj.h"
#include "gf/GfObjAcc.h"
#include "gf/MsgObjectDamage.h"
#include "plugin/Bdat.h"

namespace gf {

GfFieldDmg::GfFieldDmg(const CreateInfo* info)
    : m_applyDamage(true), m_active(false), m_bdatInfo(nullptr), m_damageId(-1), m_time(0.0f), m_hit(false) {
    if (info != nullptr) {
        create(*info);
    }
}

void GfFieldDmg::create(const CreateInfo& info) {
    dispose();
    m_applyDamage = info.m_applyDamage;
    m_active = true;
}

void GfFieldDmg::dispose() {
    m_hit = false;
    m_damageId = fw::COLI_INVALID_DAMAGE_ID;
    m_time = 0.0f;
    m_bdatInfo = nullptr;
    m_applyDamage = true;
    m_active = false;
}

void GfFieldDmg::update(const UpdateInfo& info) {
    m_hit = false;
    if (!m_active) {
        return;
    }
    if (info.m_damageId != m_damageId) {
        if (info.m_damageId < 0) {
            m_bdatInfo = nullptr;
        } else {
            m_bdatInfo = GfFieldDmgManager::get()->findBdatInfo(info.m_damageId);
        }
        m_damageId = info.m_damageId;
        m_time = 0.0f;
    }
    if (m_bdatInfo == nullptr) {
        return;
    }
    GfGameUtil::requestFieldDamage(info.m_handle);
    m_time += info.m_deltaTime;
    if (m_bdatInfo->m_interval <= m_time) {
        m_hit = true;
        m_time = 0.0f;
        if (m_applyDamage) {
            applyDamage(info.m_handle, m_bdatInfo->m_enemyDamage);
        }
    }
}

const GfFieldDmgManager::BdatInfo* GfFieldDmgManager::findBdatInfo(unsigned short id) const {
    if (m_bdatInfos.size() != 0) {
        const BdatInfo* it = m_bdatInfos.begin();
        const BdatInfo* end = m_bdatInfos.end();
        for (; it != end; ++it) {
            if (it->m_id == id) {
                return it;
            }
        }
    }
    return nullptr;
}

bool GfFieldDmg::applyDamage(GF_OBJ_HANDLE* handle, unsigned char percent) {
    GfObjAcc acc(handle);
    GfObj* obj = acc.getObj();
    if (obj == nullptr) {
        return false;
    }
    DataParamAcc param(handle);
    unsigned int damage = calculateDamage(param.getHpMax(false), percent, 0.0f);
    unsigned int hp = param.getHp() - 1;
    damage = damage < hp ? damage : hp;
    if (damage != 0) {
        MsgObjectDamage msg(damage, 2);
        obj->sendMessage(obj, msg);
    }
    return true;
}

unsigned int GfFieldDmg::calculateDamage(unsigned int hp, unsigned char percent, float ratio) {
    unsigned int damage = (unsigned int)((float)(percent * hp) * 0.01f);
    return damage - (unsigned int)((float)damage * ratio);
}

void GfFieldDmgManager::create(const GfSetupParam& param) {
    dispose();
    unsigned char* fp = GfDataBdat::getFP(0x6D);
    int count = Bdat::getIdCount(fp);
    m_bdatInfos.setAllocator(getAllocator(ALLOCATOR(0)));
    m_bdatInfos.reserve(count);
    m_bdatInfos.resize(count);
}

GfFieldDmgManager::~GfFieldDmgManager() {
    dispose();
    GfEvent::removeEventCallback(this);
}

void GfFieldDmgManager::gevMapjump(GEV gev, const MapjumpCallbackInfo& info) {
    if (gev == GEV(5)) {
        m_bdatInfos.clear();
        CBdatWrapper bdat(GfDataBdat::getFP(0x6D));
        int count = Bdat::getIdCount(bdat.m_fp);
        for (int i = 0; i < count; i++) {
            int id = Bdat::getIdTop(bdat.m_fp) + i;
            if ((unsigned short)(unsigned long)Bdat::getValCheck(bdat.m_fp, "MAPID", id, 2) == info.m_mapId) {
                m_bdatInfos.push_back(BdatInfo());
                m_bdatInfos.back().create(bdat, id);
            }
        }
    }
}

void GfFieldDmgManager::build(const GfSetupParam& param) {
#line 275
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfFieldDmgManager(&param);
}

void GfFieldDmgManager::destroy() {
    delete get();
}

}  // namespace gf
