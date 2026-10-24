#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfBdatUniqueMotion.h"
#include "classes/gf/GfGamePlayerUniqueScheduler.h"
#include "gf/MsgPcFieldSetUniqueMotion.h"
#include "gf/MsgPcFieldTestEnableUniqueMotion.h"
#include "algorithm"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjSetup.h"
#include "fw/UpdateInfo.h"
#include "gf/GfObjUtil.h"
#include "gf/GfSetupParam.h"
#include "ml/MTRand.h"

namespace gf {

void GfGamePlayerUniqueScheduler::build(const GfSetupParam& param) {
#line 31
    GfGamePlayerUniqueScheduler* scheduler = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGamePlayerUniqueScheduler();
    scheduler->setup();
}

void GfGamePlayerUniqueScheduler::destroy() {
    GfGamePlayerUniqueScheduler* scheduler = get();
    scheduler->cleanup();
    delete scheduler;
}

void GfGamePlayerUniqueScheduler::update(const fw::UpdateInfo& info) {
    GfGamePlayerUniqueScheduler* scheduler = get();
    if (scheduler != nullptr && !GfGameManager::fn_71002AC70C()) {
        scheduler->executeRequest(info);
        scheduler->judge(info);
    }
}

inline GfGamePlayerUniqueScheduler::Member* GfGamePlayerUniqueScheduler::findMember(unsigned short charaId) {
    for (Member& member : m_members) {
        if (member.m_charaId == charaId) {
            return &member;
        }
    }
    return nullptr;
}

inline void GfGamePlayerUniqueScheduler::executeRequest(const fw::UpdateInfo& info) {
    for (int i = 0; i < 9; i++) {
        Member& member = m_members[i];
        if (member.m_state == 3) {
            member.m_wait -= info.m_deltaTime;
            if (member.m_wait < 0.0f) {
                MsgPcFieldSetUniqueMotion msg(member.m_motion < 3 ? member.m_motion : 0);
                if (GfObj* obj = GfObjUtil::getObj(member.m_handle)) {
                    static_cast<fw::MessageObject*>(obj)->recieveMessage(this, msg);
                }
                member.m_state = 1;
            }
        }
    }
}

void GfGamePlayerUniqueScheduler::judge(const fw::UpdateInfo& info) {
    const Param* param = getParam();
    m_timer += info.m_deltaTime;
    if (m_timer > param->m_interval) {
        for (Member& member : m_members) {
            if (member.m_state == 1) {
                MsgPcFieldTestEnableUniqueMotion msg;
                if (GfObj* obj = GfObjUtil::getObj(member.m_handle)) {
                    static_cast<fw::MessageObject*>(obj)->recieveMessage(this, msg);
                    if (msg.m_result) {
                        member.m_state = 2;
                    }
                }
            }
        }
        if (ml::mtRandf1() * 100.0f < param->m_probability) {
            // the ready members' characters
            GfBdatUniqueMotion::PresetKey key(
                static_cast<unsigned short>(m_members[0].m_state == 2 ? m_members[0].m_charaId : 0),
                static_cast<unsigned short>(m_members[1].m_state == 2 ? m_members[1].m_charaId : 0),
                static_cast<unsigned short>(m_members[2].m_state == 2 ? m_members[2].m_charaId : 0),
                static_cast<unsigned short>(m_members[3].m_state == 2 ? m_members[3].m_charaId : 0),
                static_cast<unsigned short>(m_members[4].m_state == 2 ? m_members[4].m_charaId : 0),
                static_cast<unsigned short>(m_members[5].m_state == 2 ? m_members[5].m_charaId : 0));
            std::sort(key.m_ids, key.m_ids + 6);
            if (!m_presets.empty()) {
                int total = 0;
                for (const GfBdatUniqueMotion::PresetInfo* info : m_presets) {
                    if (info->m_key.isContain(key)) {
                        total += info->m_weight;
                    }
                }
                if (total > 0) {
                    int pick = ml::mtRand(1, total);
                    const GfBdatUniqueMotion::PresetInfo* preset = nullptr;
                    for (const GfBdatUniqueMotion::PresetInfo* info : m_presets) {
                        pick -= info->m_weight;
                        if (pick <= 0) {
                            preset = info;
                            break;
                        }
                    }
                    if (preset != nullptr) {
                        for (int i = 0; i < 6; i++) {
                            const GfBdatUniqueMotion::PresetInfo::Entry& entry = preset->m_entries[i];
                            if (entry.m_charaId != 0) {
                                if (Member* member = findMember(entry.m_charaId)) {
                                    member->m_state = 3;
                                    member->m_motion = entry.m_motion;
                                    member->m_wait = entry.m_wait;
                                }
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < 9; i++) {
            Member& member = m_members[i];
            if (member.m_state == 2) {
                const GfBdatUniqueMotion::CharaInfo* chara = GfBdatUniqueMotion::getCharaInfo(member.m_charaId);
                if (chara != nullptr && static_cast<unsigned int>(ml::mtRand(1, 100)) <= chara->m_rate) {
                    unsigned int total = 0;
                    for (int k = 0; k < 3; k++) {
                        total += chara->m_weights[k];
                    }
                    int pick = ml::mtRand(1, total > 1 ? total : 1);
                    unsigned short motion = 0;
                    for (int k = 0; k < 3; k++) {
                        pick -= chara->m_weights[k];
                        if (pick <= 0) {
                            motion = k;
                            break;
                        }
                    }
                    member.m_state = 3;
                    member.m_motion = motion;
                    member.m_wait = chara->m_waitMin + (chara->m_waitMax - chara->m_waitMin) * ml::mtRandf1();
                }
                if (member.m_state == 2) {
                    member.m_state = 1;
                }
            }
        }
        m_timer = 0.0f;
    }
}

void GfGamePlayerUniqueScheduler::onReload() {
    if (GfGamePlayerUniqueScheduler* scheduler = get()) {
        scheduler->rebuildPreset();
    }
}

inline void GfGamePlayerUniqueScheduler::rebuildPreset() {
    m_presets.clear();
    GfBdatUniqueMotion::PresetKey key(
        m_members[0].m_charaId, m_members[1].m_charaId, m_members[2].m_charaId,
        m_members[3].m_charaId, m_members[4].m_charaId, m_members[5].m_charaId);
    std::sort(key.m_ids, key.m_ids + 6);
    GfBdatUniqueMotion::queryPreset(&m_presets, key);
}

GfGamePlayerUniqueScheduler::GfGamePlayerUniqueScheduler() : m_timer(0.0f) {}

GfGamePlayerUniqueScheduler::~GfGamePlayerUniqueScheduler() {}

inline void GfGamePlayerUniqueScheduler::setMember(Member& member, GF_OBJ_HANDLE* handle) {
    member.m_handle = handle;
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        member.m_charaId = 0;
        member.m_state = 0;
    } else {
        member.m_charaId = GfObjUtil::getObjSetup(handle)->m_bdatId;
        member.m_state = 1;
    }
}

void GfGamePlayerUniqueScheduler::gevPartyMemberOK(bool ok) {
    if (ok) {
        if (GfGameManager::fn_71002A9E68()) {
            // three drivers for each of the first three (getHandleDriver's second argument 0 to 2)
            for (unsigned int i = 0; i < 3; i++) {
                for (unsigned int j = 0; j < 3; j++) {
                    setMember(m_members[i * 3 + j], GfGameParty::getHandleDriver(i, j));
                }
            }
        } else {
            // the first three drivers and their blades
            for (unsigned int i = 0; i < 3; i++) {
                setMember(m_members[i * 2], GfGameParty::getHandleDriver(i, 0));
                setMember(m_members[i * 2 + 1], GfGameParty::getHandleBlade(i, -1));
            }
        }
        rebuildPreset();
    }
}

void GfGamePlayerUniqueScheduler::gevBattleStart() {
    m_timer = 0.0f;
    for (int i = 0; i < 9; i++) {
        m_members[i].m_state = 1;
    }
}

void GfGamePlayerUniqueScheduler::gevChangeBlade(GF_OBJ_HANDLE*, int, int) {
    gevPartyMemberOK(true);
}

}  // namespace gf
