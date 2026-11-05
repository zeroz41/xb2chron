#include "classes/gf/GfGameArena.h"
#include "classes/gf/GfArenaBattle.h"
#include "classes/gf/GfArenaParty.h"
#include "classes/gf/GfReqSmallCom.h"
#include "classes/gf/StateArenaWait.h"
#include "classes/gf/StateArenaField.h"
#include "classes/gf/StateArenaReturnBattle.h"
#include "classes/gf/StateArenaEvent.h"
#include "classes/gf/StateArenaResultBattle.h"
#include "classes/gf/GfArenaReward.h"
#include "classes/gf/GfMenuObjSalvage.h"
#include "math.h"
#include "classes/gf/StateArenaSetup.h"
#include "classes/gf/StateArenaLeave.h"
#include "classes/gf/StateArenaStartBattle.h"
#include "classes/gf/StateArenaExecBattle.h"
#include "classes/gf/GfBdatBtl.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfMenuManager.h"
#include "gf/GfDataMap.h"
#include "gf/GfDataBlade.h"
#include "gf/MapjumpCallbackInfo.h"
#include "btl/Utility.h"
#include "gf/GfArenaUtil.h"
#include "classes/gf/SCOM_POPUP.h"
#include "classes/gf/GfBdatCond.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfGameParty.h"
#include "gf/GfDataDriver.h"
#include "gf/GfItemUtil.h"

namespace gf {

void StateArenaWait::gevMapjump(gf::GEV gev, gf::MapjumpCallbackInfo const& info) {
    switch (static_cast<int>(gev)) {
    case 1:
        if (GfGameArena* arena = mm::mtl::PtrSingleton<GfGameArena>::sys()) {
            if (!arena->isActiveArena() && GfDataMap::getMapID(info.m_mapJumpId) == 0x3A) {
                MsgGameBtlArena msg(0xB);
                static_cast<fw::MessageObject*>(arena)->recieveMessage(arena, msg);
            }
        }
        break;
    case 6:
        if (GfGameArena* arena = mm::mtl::PtrSingleton<GfGameArena>::sys()) {
            if (arena->isActiveArena()) {
                m_arenaFlagSeen = true;
            }
        }
        break;
    }
}

void StateArenaSetup::enter(GfGameArena* arena, ai::State*) {
    arena->createMapSound();
}

void StateArenaSetup::leave(GfGameArena*, ai::State*) {}

void StateArenaSetup::update(GfGameArena*, fw::UpdateInfo const&) {
    requestState(3);
}

void StateArenaLeave::enter(GfGameArena* arena, ai::State*) {
    arena->m_partySetup->removeFieldBlade();
    arena->destroyMapSound();
}

void StateArenaLeave::leave(GfGameArena*, ai::State*) {}

void StateArenaLeave::update(GfGameArena*, fw::UpdateInfo const&) {
    requestState(9);
}

void StateArenaField::gevMapjump(gf::GEV gev, gf::MapjumpCallbackInfo const& info) {
    if (gev == 1) {
        if (GfGameArena* arena = mm::mtl::PtrSingleton<GfGameArena>::sys()) {
            if (arena->isActiveArena() && GfDataMap::getMapID(info.m_mapJumpId) != 0x3A) {
                MsgGameBtlArena msg(0xA);
                static_cast<fw::MessageObject*>(arena)->recieveMessage(arena, msg);
            }
        }
    }
}

void StateArenaStartBattle::enter(GfGameArena*, ai::State*) {}

void StateArenaStartBattle::leave(GfGameArena*, ai::State*) {}

void StateArenaStartBattle::update(GfGameArena* arena, fw::UpdateInfo const&) {
    if (arena->m_partySetup->setupParty(arena->m_msgObj->m_key)) {
        GfMenuManager::loadBchUI();
        arena->m_msgObj->mapjumpForBattleStart();
        requestState(5);
    } else {
        requestState(3);
    }
}

void StateArenaExecBattle::enter(GfGameArena*, ai::State*) {
    btl::Utility::StartChallengeBattleCallback();
}

void StateArenaExecBattle::leave(GfGameArena*, ai::State*) {}

void StateArenaExecBattle::update(GfGameArena* arena, fw::UpdateInfo const& info) {
    arena->m_msgObj->execBattleSequence(info);
    requestState(7);
}

void StateArenaReturnBattle::gevMapjump(gf::GEV gev, gf::MapjumpCallbackInfo const&) {
    if (gev == 4) {
        if (GfGameArena* arena = mm::mtl::PtrSingleton<GfGameArena>::sys()) {
            arena->m_msgObj->mapjumpForReturnFieldForObjCleanup();
        }
    }
}

void StateArenaResultBattle::enter(GfGameArena* arena, ai::State*) {
    arena->m_helper->listUpTBox();
    m_step = &StateArenaResultBattle::updateStart;
    m_context = GfMenuCallContext::create();
}

void StateArenaResultBattle::updateStart(GfGameArena* arena, fw::UpdateInfo const&) {
    if (arena->m_msgObj->m_result == 2 || arena->m_helper->getTresureBoxNum(arena->m_msgObj->m_score)) {
        m_step = &StateArenaResultBattle::updateCamera;
    } else {
        m_step = &StateArenaResultBattle::updateFadeWait;
    }
}

void StateArenaResultBattle::leave(GfGameArena*, ai::State*) {
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
}

void StateArenaResultBattle::update(GfGameArena* arena, fw::UpdateInfo const& info) {
    if (m_step) {
        (this->*m_step)(arena, info);
    }
}

void StateArenaResultBattle::updateCamera(GfGameArena* arena, fw::UpdateInfo const&) {
    mm::Mat44 mtx;
    if (arena->m_helper->getActionOrigin(mtx)) {
        mm::Vec3 pos(mtx.m[3][0], mtx.m[3][1], mtx.m[3][2]);
        float rotY = atan2f(mtx.m[2][0], mtx.m[2][2]);
        arena->m_helper->createCameraCut01(pos, rotY);
    }
    arena->m_helper->playCameraCut01();
    m_timer = 0.5f;
    m_step = &StateArenaResultBattle::updateCameraWait;
}

void StateArenaResultBattle::updateFadeWait(GfGameArena* arena, fw::UpdateInfo const&) {
    if (!GfGameManager::isFading(static_cast<unsigned int>(-1))) {
            bool clear = arena->m_msgObj->m_result == 2 || arena->m_helper->getTresureBoxNum(arena->m_msgObj->m_score);
        if (clear) {
            arena->m_helper->playReturnVoice(arena->m_msgObj->m_result == 2);
            m_step = &StateArenaResultBattle::updateResult;
        } else {
            arena->m_helper->playReturnVoice(false);
            m_step = &StateArenaResultBattle::updateFinish;
        }
    }
}

void StateArenaResultBattle::updateResult(GfGameArena*, fw::UpdateInfo const&) {
    m_context->reset();
    GfMenuObjSalvage::openBtlchRecord(m_context);
    m_step = &StateArenaResultBattle::updateResultWait;
}

void StateArenaResultBattle::updateFinish(GfGameArena* arena, fw::UpdateInfo const&) {
    arena->m_helper->destroyCameraCut01();
    requestState(3);
    m_step = nullptr;
}

void StateArenaResultBattle::updateResultWait(GfGameArena*, fw::UpdateInfo const&) {
    if (m_context->isTerm()) {
        m_step = &StateArenaResultBattle::updateTBox;
    }
}

void StateArenaResultBattle::updateTBox(GfGameArena* arena, fw::UpdateInfo const&) {
    if (arena->m_helper->getTresureBoxNum(arena->m_msgObj->m_score)) {
        arena->m_helper->createTresureBox(arena->m_msgObj->m_score);
    } else {
        arena->m_helper->createMoney(arena->m_msgObj->m_score);
    }
    m_timer = 0.5f;
    m_step = &StateArenaResultBattle::updateTBoxWait;
}

void StateArenaResultBattle::updateCameraWait(GfGameArena*, fw::UpdateInfo const& info) {
    m_timer -= info.m_frameTime;
    if (m_timer < 0.0f) {
        m_step = &StateArenaResultBattle::updateFadeWait;
    }
}

void StateArenaResultBattle::updateTBoxWait(GfGameArena*, fw::UpdateInfo const& info) {
    m_timer -= info.m_deltaTime;
    if (m_timer < 0.0f) {
        m_step = &StateArenaResultBattle::updateUI;
    }
}

void StateArenaResultBattle::updateUI(GfGameArena* arena, fw::UpdateInfo const&) {
    m_context->reset();
    GfMenuObjSalvage::ResultParam param;
    param.m_unk2 = 1;
    GfMenuObjSalvage::openResult(m_context, param);
    arena->m_helper->playVoice(arena->m_msgObj->m_score);
    m_step = &StateArenaResultBattle::updateUIWait;
}

void StateArenaResultBattle::updateUIWait(GfGameArena* arena, fw::UpdateInfo const&) {
    if (m_context->isTerm()) {
        arena->m_helper->destroyCameraCut01();
        m_timer = 0.0f;
        m_step = &StateArenaResultBattle::updateReturnCamera;
    }
}

void StateArenaResultBattle::updateReturnCamera(GfGameArena* arena, fw::UpdateInfo const& info) {
    m_timer += info.m_deltaTime;
    if (m_timer > 1.0f) {
            arena->m_helper->dropClearReward(arena->m_msgObj->m_score);
        m_step = &StateArenaResultBattle::updateFinish;
    }
}

void StateArenaEvent::gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&) {}

void StateArenaEvent::gevPlayEvent(gf::GEV gev, unsigned int) {
    switch (static_cast<int>(gev)) {
    case 0xC: m_playState = 1; break;
    case 0xD: m_playState = 3; break;
    case 0xE: m_playState = 2; break;
    default: break;
    }
}

void GfArenaUtil::setupMenuInfoForChBtl(ArenaMenuInfo& info, unsigned int id) {
    GfBdatBtl* btl = mm::mtl::PtrSingleton<GfBdatBtl>::sys();
    bool hasItem = btl->getBTL_ChBtlNeedItem(id) == 0 || GfItemUtil::getItemBoxCount(btl->getBTL_ChBtlNeedItem(id)) != 0;
    info.clear();
    info.m_lists.m_list38.clear();
    info.m_lists.m_listE0.clear();
    info.m_ratios[0] = 0.0f;
    info.m_ratios[1] = 0.0f;
    info.m_ratios[2] = 0.0f;
    info.m_rule = ChBtlInfo::ChBtlDiff();
    info.m_valueAE8 = 1;
    info.m_flagAEC = false;
    info.m_id = id;
    info.m_valueE = btl->getBTL_ChBtlName(id);
    info.m_value8 = btl->getBTL_ChBtlMaxLevel(id);
    info.m_kind = btl->getBTL_ChBtlType(id);
    info.m_valueC = btl->getBTL_ChBtlDifficult(id);
    info.m_valueA = btl->getBTL_ChBtlJoinNumber(id);
    info.m_value4 = btl->getBTL_ChBtlTimeLimit(id);
    info.m_value10 = btl->getBTL_ChBtlCaption(id);
    info.m_flag12 = btl->getBTL_ChBtlCondition(id) == 0 ? hasItem
                                                       : hasItem && GfGameCond::isGameCond(btl->getBTL_ChBtlCondition(id));
    info.m_text14.m_message = btl->getBTL_ChBtlConditionCap(id);
    info.m_text14.m_flag = btl->getBTL_ChBtlCondition2(id) == 0
                               ? hasItem
                               : hasItem && GfGameCond::isGameCond(btl->getBTL_ChBtlCondition2(id));
    info.m_value18 = btl->getBTL_ChBtlConditionCap2(id);
    info.m_flag1A = btl->isBTL_ChBtlFlagHide(id);
    info.m_flag1B = btl->getBTL_ChBtlHideCondition(id) != 0 && GfGameCond::isGameCond(btl->getBTL_ChBtlHideCondition(id));
    info.m_value1C = btl->getBTL_ChBtlNeedDefeat(id);
    info.m_values1E[0] = btl->getBTL_ChBtlDriver(id, 0);
    info.m_values1E[1] = btl->getBTL_ChBtlDriver(id, 1);
    info.m_values1E[2] = btl->getBTL_ChBtlDriver(id, 2);
    info.m_valueAE8 = mm::mtl::PtrSingleton<GfGameArena>::sys()->getSaveInfo()->m_rows[id].m_flag3C;
}

void GfArenaUtil::setupMenuInfoForScore(ChBtlInfo::ChBtlDiff& diff, ArenaMenuInfo& info, unsigned int value) {
    if (diff.m_value4 < value) {
        diff.m_value4 = value;
    }
    info.m_value28 = value;
}

void GfArenaUtil::setupMenuInfoForClearTime(ChBtlInfo::ChBtlDiff& diff, ArenaMenuInfo& info, unsigned int value) {
    if (diff.m_value0 == 0 || value < diff.m_value0) {
        diff.m_value0 = value;
    }
    info.m_value30 = value;
}

void GfArenaUtil::setupSaveData(SaveChBtl& save, const mm::mtl::FixedVector<unsigned short, 128>& ids) {
    GfBdatBtl* btl = mm::mtl::PtrSingleton<GfBdatBtl>::sys();
    for (const unsigned short& id : ids) {
        ChBtlInfo& info = save.m_rows[id];
        if (!info.m_isChecked) {
            info.m_isChecked = true;
            info.m_flag3C = !btl->isBTL_ChBtlFlagHide(id);
        }
    }
}

void GfArenaUtil::applyChallengeStatus(SaveChBtl& save, const mm::mtl::FixedVector<unsigned short, 128>& ids) {
    GfBdatBtl* btl = mm::mtl::PtrSingleton<GfBdatBtl>::sys();
    for (const unsigned short& id : ids) {
        ChBtlInfo& info = save.m_rows[id];
        if (!info.m_flag3C) {
            if (GfGameCond::isGameCond(btl->getBTL_ChBtlCondition(id))) {
                info.m_flag3C = true;
                info.m_flag3E = true;
                SCOM_POPUP::createChBtlNewChallenge(id);
            }
        } else if (!info.m_flag3E) {
            if (GfGameCond::isGameCond(btl->getBTL_ChBtlCondition(id))) {
                info.m_flag3E = true;
            }
        }
    }
}

void GfArenaUtil::setupBattleMapWeather(unsigned int id) {
    GfBdatBtl* btl = mm::mtl::PtrSingleton<GfBdatBtl>::sys();
    if (unsigned int map = btl->getBTL_ChBtlMapJump(id)) {
        unsigned int mapId = GfDataMap::getMapID(map);
        unsigned int weather = btl->getBTL_ChBtlWeather(id);
        WeatherParam* env = GfDataMap::getWeatherParam(mapId);
        if (env->m_mapId == mapId) {
            env->m_id = static_cast<WEATHERID>(weather < 4 ? weather + 1 : 5);
            env->m_time = 0.0f;
            env->m_timeMax = 100.0f;
        }
    }
}

void GfArenaUtil::setupChBtlList(mm::mtl::FixedVector<unsigned short, 128>& ids) {
    ids.clear();
    GfBdatBtl* btl = mm::mtl::PtrSingleton<GfBdatBtl>::sys();
    unsigned short start = btl->getBTL_ChBtlStart();
    unsigned short end = btl->getBTL_ChBtlEnd();
    for (unsigned short id = start; id < end; ++id) {
        ids.push_back(id);
    }
}

void GfArenaUtil::setChallengeOK(SaveChBtl& save, unsigned int id) {
    save.m_rows[id].m_flag3C = 2;
}

unsigned int GfArenaUtil::getWeaponDamage(const ArenaBattleStart& start, unsigned int blade) {
    DataParamAcc acc(4, blade, static_cast<GimmickType>(0));
    GfBdatBtl* btl = mm::mtl::PtrSingleton<GfBdatBtl>::sys();
    unsigned int maxRank = btl->getBTL_ChBtlMaxWpnRank(start.m_id);
    if (maxRank != 0 && GfDataBlade::getBladeWeaponRank(blade) > maxRank) {
        if (unsigned int table = btl->getBTL_ChBtlWpnRevTable(start.m_id)) {
            return btl->getBTL_ChBtlWpnRevWpnDmg(table, acc.getWeaponType(-1, false));
        }
    }
    return acc.getWeaponDamage(false);
}

void GfArenaUtil::createPopupForKillEnemy(unsigned int value) {
    GfBdatBtl* btl = mm::mtl::PtrSingleton<GfBdatBtl>::sys();
    GfBdatCond* cond = mm::mtl::PtrSingleton<GfBdatCond>::sys();
    unsigned short start = btl->getBTL_ChBtlStart();
    unsigned short end = btl->getBTL_ChBtlEnd();
    for (unsigned short id = start; id < end; ++id) {
        unsigned int condition = btl->getBTL_ChBtlCondition(id);
        if (condition != 0 && cond->getConditionListConditionType(condition, 0) == 0xD) {
            if (cond->getConditionNamedNamed(cond->getConditionListCondition(condition, 0)) == value) {
                ChBtlInfo& info = mm::mtl::PtrSingleton<GfGameArena>::sys()->getSaveInfo()->m_rows[id];
                if (!info.m_flag3E) {
                    SCOM_POPUP::createChBtlNewChallenge(id);
                    info.m_flag3E = true;
                }
                return;
            }
        }
    }
}

unsigned int GfArenaUtil::getPlayEvent(unsigned int id) {
    if (id == 0) {
        return 0;
    }
    return mm::mtl::PtrSingleton<GfBdatBtl>::sys()->getBTL_ChBtlEvent(id);
}

bool GfArenaUtil::isPlayEvent(const mm::mtl::FixedArray<ChBtlInfo, 48>& infos, unsigned int id) {
    if (id == 0) {
        return false;
    }
    return infos[id].m_rules[0].m_flag8 & 1;
}

}  // namespace gf
