#include "classes/gf/GfReqSmallCom.h"
#include "classes/gf/SCOM.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfGameMercenaries.h"
#include "classes/gf/GfFieldManager.h"
#include "classes/gf/GfMapManager.h"
#include "classes/gf/GfGameManager.h"
#include "gf/GfQuestTask.h"
#include "classes/gf/GfGameCamera.h"
#include "classes/gf/SCOM_ADD_MONEY.h"
#include "classes/gf/SCOM_ADD_COIN.h"
#include "classes/gf/SCOM_MAXIMUM_HEAL.h"
#include "classes/gf/SCOM_ADD_EXP.h"
#include "classes/gf/SCOM_ADD_SP.h"
#include "classes/gf/SCOM_ADD_IDEA.h"
#include "classes/gf/SCOM_LEVELUP_DEVELOP.h"
#include "classes/gf/SCOM_ADD_MERCENARIES_POINT.h"
#include "classes/gf/SCOM_SET_MERCENARIES_LEVEL.h"
#include "classes/gf/SCOM_ADD_TRUST.h"
#include "classes/gf/SCOM_DESTROY_FIELD_OBJ.h"
#include "classes/gf/SCOM_DESTROY_MAP_OBJ.h"
#include "classes/gf/SCOM_CREATE_MAP_OBJ.h"
#include "classes/gf/SCOM_LOADING.h"
#include "classes/gf/SCOM_DESTROY_GMK_SET.h"
#include "classes/gf/SCOM_CREATE_GMK_SET.h"
#include "classes/gf/SCOM_QUEST_REACH.h"
#include "classes/gf/SCOM_ITEM_USE.h"
#include "classes/gf/SCOM_ACCESS_TARGET.h"
#include "classes/gf/SCOM_TARGET_UI.h"
#include "classes/gf/SCOM_SET_FLAG.h"
#include "classes/gf/SCOM_SET_CAMTYPE.h"
#include "classes/gf/SCOM_EXEC_CURRENT_BLADE.h"
#include "classes/gf/SCOM_NIA_BLADE.h"
#include "classes/gf/SCOM_ACHIEV_INC.h"
#include "classes/gf/SCOM_FIELD_SKILL.h"
#include "classes/gf/SCOM_ZONE.h"
#include "classes/gf/SCOM_SOLO_REX.h"
#include "classes/gf/GfMenuFade.h"
#include "classes/gf/GfMountManager.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/GfGameObj.h"
#include "gf/GfDataEnBook.h"
#include "classes/gf/GfQuestManager.h"
#include "gf/GfPlayFactory.h"
#include "classes/gf/SCOM_POPUP.h"
#include "gf/GfDataMercenaries.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfBdatBtl.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/SCOM_ADD_DEVELOP.h"
#include "classes/gf/SCOM_OBJ_WARP_POS.h"
#include "classes/gf/SCOM_DESTROY_GAME_OBJ.h"
#include "classes/gf/SCOM_EXEC_MOUNT.h"
#include "classes/gf/SCOM_OBJ_VFADE_OFF.h"
#include "classes/gf/SCOM_QUEST_GIMMICK.h"
#include "classes/gf/SCOM_BATTLE_BGM.h"
#include "classes/gf/SCOM_ENBOOK_IN_BATTLE.h"
#include "classes/gf/SCOM_ENBOOK_DEFEAT_ENEMY.h"
#include "classes/gf/SCOM_ENBOOK_DEAD_PLAYER.h"
#include "classes/gf/SCOM_REFRESH_COMPASS.h"
#include "classes/gf/SCOM_BATTLE_TASK_RESET.h"
#include "gf/ParamObj.h"
#include "gf/GfFieldVoice.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfAchievManager.h"
#include "gf/GfDataAchievement.h"
#include "classes/gf/GfGameVoice.h"
#include "fw/UpdateInfo.h"
#include "classes/gf/SCOM_ADD_ETHER.h"
#include "gf/GfDataMap.h"
#include "gf/GfObjAcc.h"
#include "classes/gf/SCOM_ADD_WP.h"
#include "classes/gf/SCOM_MISSION_COMPLETE.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/SCOM_CHAR_DEAD.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfAllocator.h"

#include "classes/gf/GfFieldGimmick.h"
#include "classes/gf/GfAutoTalkManager.h"
#include "classes/gf/SCOM_CURRENT_BLADE.h"
#include "classes/gf/SCOM_SALVAGE_VOICE.h"
#include "classes/gf/SCOM_RANDOM_INN.h"
#include "gf/GfSalvageVoice.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataMap.h"
#include "gf/GfDataUtil.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/SCOM_FADE.h"
#include "gf/FileStaticVec3.h"
#include "classes/gf/SCOM_PARTY_ADD.h"
#include "classes/gf/SCOM_PARTY_LEADER.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfGameEvent.h"
#include "gf/GfUtil.h"
#include "classes/gf/SCOM_SCRIPT.h"
#include "classes/gf/GfScriptManager.h"
namespace gf {
bool SCOM_ADD_MONEY::exec(fw::UpdateInfo const&) {
    GfGameUtil::addMoney(m_money);
    return true;
}

bool SCOM_ADD_COIN::exec(fw::UpdateInfo const&) {
    GfGameUtil::addCoin(m_coin);
    return true;
}

bool SCOM_LEVELUP_DEVELOP::exec(fw::UpdateInfo const&) {
    if (!GfGameManager::isControlFree()) {
        return false;
    }
    GfGameUtil::execDevelopLevelUp();
    return true;
}

bool SCOM_ADD_MERCENARIES_POINT::exec(fw::UpdateInfo const&) {
    GfGameMercenaries::addPoint(m_point);
    return true;
}

bool SCOM_SET_MERCENARIES_LEVEL::exec(fw::UpdateInfo const&) {
    GfGameMercenaries::setLevel(m_level);
    return true;
}

bool SCOM_DESTROY_FIELD_OBJ::exec(fw::UpdateInfo const&) {
    GfFieldManager::destroyObj();
    return true;
}

bool SCOM_DESTROY_MAP_OBJ::exec(fw::UpdateInfo const&) {
    GfMapManager::destroyObj();
    return true;
}

bool SCOM_ITEM_USE::exec(fw::UpdateInfo const&) {
    GfQuestTask::completeItemUseTask(m_item, m_count);
    return true;
}

bool SCOM_ACCESS_TARGET::exec(fw::UpdateInfo const&) {
    GfGameManager::setAccessTarget(m_target);
    return true;
}

bool SCOM_TARGET_UI::exec(fw::UpdateInfo const&) {
    GfGameManager::setTargetUI(m_target);
    return true;
}

bool SCOM_SET_CAMTYPE::exec(fw::UpdateInfo const&) {
    GfGameCamera::setCameraControlType(m_cameraType);
    return true;
}


bool SCOM_ADD_DEVELOP::exec(fw::UpdateInfo const&) {
    GfGameUtil::addDevelopPoint(m_value2, m_value);
    return true;
}

bool SCOM_OBJ_WARP_POS::exec(fw::UpdateInfo const&) {
    GfObjUtil::setWarpTransform(m_value, m_value2, m_value3);
    return true;
}

bool SCOM_DESTROY_GAME_OBJ::exec(fw::UpdateInfo const&) {
    GfGameObj::destroyGameObjWithAttribute(m_value, m_value2, m_value3);
    return true;
}

bool SCOM_LOADING::exec(fw::UpdateInfo const&) {
    if (!GfMenuFade::isInitialized()) {
        return false;
    }
    GfMenuFade::setLoading(m_value, m_value2);
    return true;
}

bool SCOM_EXEC_MOUNT::exec(fw::UpdateInfo const&) {
    GfMountManager::execMount(m_value, GFATTACH(0), m_value2);
    return true;
}

bool SCOM_OBJ_VFADE_OFF::exec(fw::UpdateInfo const&) {
    GfObjUtil::setVolumeFadeUserFlag(m_value, false);
    return true;
}

bool SCOM_QUEST_GIMMICK::exec(fw::UpdateInfo const&) {
    GfQuestTask::completeGimmickTask(m_value, m_value2);
    return true;
}

bool SCOM_BATTLE_BGM::exec(fw::UpdateInfo const&) {
    return true;
}

bool SCOM_ENBOOK_IN_BATTLE::exec(fw::UpdateInfo const&) {
    GfDataEnBook::setAttackFlag(m_value);
    return true;
}

bool SCOM_ENBOOK_DEFEAT_ENEMY::exec(fw::UpdateInfo const&) {
    GfDataEnBook::incDefeatNum(m_value);
    return true;
}

bool SCOM_ENBOOK_DEAD_PLAYER::exec(fw::UpdateInfo const&) {
    GfDataEnBook::incDeadNum(m_value);
    return true;
}

bool SCOM_REFRESH_COMPASS::exec(fw::UpdateInfo const&) {
    if (--m_wait > 0) {
        return false;
    }
    GfQuestManager::requestRefreshQuestTaskState();
    return true;
}

bool SCOM_BATTLE_TASK_RESET::exec(fw::UpdateInfo const&) {
    if (--m_wait > 0) {
        return false;
    }
    GfQuestManager::resetBattleTaskForBattleEnd();
    return true;
}

unsigned long SCOM_ADD_MONEY::create(int a0) {
    if (!a0) {
        return -1;
    }
#line 131
    SCOM_ADD_MONEY* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ADD_MONEY(SCOM_TYPE(1));
    request->m_money = a0;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_ADD_COIN::create(int a0) {
    if (!a0) {
        return -1;
    }
#line 187
    SCOM_ADD_COIN* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ADD_COIN(SCOM_TYPE(2));
    request->m_coin = a0;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_MAXIMUM_HEAL::create(GF_OBJ_HANDLE* a0) {
#line 217
    SCOM_MAXIMUM_HEAL* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_MAXIMUM_HEAL(SCOM_TYPE(8));
    request->m_value = a0;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_ADD_EXP::createInnExp(unsigned int a0) {
    if (!a0) {
        return -1;
    }
#line 269
    SCOM_ADD_EXP* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ADD_EXP(SCOM_TYPE(4));
    request->m_value = a0;
    request->m_value2 = 0;
    request->m_value3 = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    request->m_value4 = 1;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_ADD_SP::create(GF_OBJ_HANDLE* a0, int a1) {
    if (!a1) {
        return -1;
    }
#line 403
    SCOM_ADD_SP* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ADD_SP(SCOM_TYPE(8));
    request->m_value = a1;
    request->m_value2 = 0;
    request->m_value3 = a0;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_ADD_SP::create(unsigned int a0, int a1) {
    if (!a1) {
        return -1;
    }
#line 408
    SCOM_ADD_SP* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ADD_SP(SCOM_TYPE(8));
    request->m_value = a1;
    request->m_value2 = a0;
    request->m_value3 = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_ADD_IDEA::create(GF_OBJ_HANDLE* a0, unsigned int a1, int a2) {
    if (!a2) {
        return -1;
    }
#line 430
    SCOM_ADD_IDEA* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ADD_IDEA(SCOM_TYPE(9));
    request->m_value = a2;
    request->m_value2 = 0;
    request->m_value3 = a1;
    request->m_value4 = a0;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_ADD_IDEA::create(unsigned int a0, unsigned int a1, int a2) {
    if (!a2) {
        return -1;
    }
#line 435
    SCOM_ADD_IDEA* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ADD_IDEA(SCOM_TYPE(9));
    request->m_value = a2;
    request->m_value2 = a0;
    request->m_value3 = a1;
    request->m_value4 = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_LEVELUP_DEVELOP::create() {
#line 486
    SCOM_LEVELUP_DEVELOP* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_LEVELUP_DEVELOP(SCOM_TYPE(12));
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_ADD_MERCENARIES_POINT::create(unsigned int a0) {
    if (!a0) {
        return -1;
    }
#line 501
    SCOM_ADD_MERCENARIES_POINT* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ADD_MERCENARIES_POINT(SCOM_TYPE(59));
    request->m_point = a0;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_SET_MERCENARIES_LEVEL::create(unsigned int a0) {
#line 515
    SCOM_SET_MERCENARIES_LEVEL* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_SET_MERCENARIES_LEVEL(SCOM_TYPE(60));
    request->m_level = a0;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_ADD_TRUST::create(unsigned int a0, unsigned int a1) {
    if (!a1) {
        return -1;
    }
#line 614
    SCOM_ADD_TRUST* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ADD_TRUST(SCOM_TYPE(64));
    request->m_value = a1;
    request->m_value2 = a0;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_DESTROY_FIELD_OBJ::create() {
#line 1039
    SCOM_DESTROY_FIELD_OBJ* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_DESTROY_FIELD_OBJ(SCOM_TYPE(24));
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_DESTROY_MAP_OBJ::create() {
#line 1055
    SCOM_DESTROY_MAP_OBJ* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_DESTROY_MAP_OBJ(SCOM_TYPE(25));
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_CREATE_MAP_OBJ::create(unsigned int a0, unsigned int a1) {
#line 1080
    SCOM_CREATE_MAP_OBJ* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_CREATE_MAP_OBJ(SCOM_TYPE(26));
    request->m_value = a0;
    request->m_value2 = a1;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_LOADING::create(unsigned int a0, bool a1) {
#line 1149
    SCOM_LOADING* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_LOADING(SCOM_TYPE(28));
    request->m_value = a0;
    request->m_value2 = a1;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_DESTROY_GMK_SET::create(unsigned int a0) {
#line 1368
    SCOM_DESTROY_GMK_SET* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_DESTROY_GMK_SET(SCOM_TYPE(38));
    request->m_value = a0;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_CREATE_GMK_SET::create(unsigned int a0) {
#line 1384
    SCOM_CREATE_GMK_SET* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_CREATE_GMK_SET(SCOM_TYPE(39));
    request->m_value = a0;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_QUEST_REACH::createArriveLandmark(unsigned int a0) {
#line 1951
    SCOM_QUEST_REACH* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_QUEST_REACH(SCOM_TYPE(42));
    request->m_value = 2;
    request->m_value2 = a0;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_QUEST_REACH::createArrivePlace(unsigned int a0) {
#line 1957
    SCOM_QUEST_REACH* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_QUEST_REACH(SCOM_TYPE(42));
    request->m_value = 3;
    request->m_value2 = a0;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_ITEM_USE::create(unsigned int a0, unsigned int a1) {
#line 1972
    SCOM_ITEM_USE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ITEM_USE(SCOM_TYPE(68));
    request->m_item = a0;
    request->m_count = a1;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_ACCESS_TARGET::create(GF_OBJ_HANDLE* a0) {
#line 2202
    SCOM_ACCESS_TARGET* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ACCESS_TARGET(SCOM_TYPE(46));
    request->m_target = a0;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_TARGET_UI::create(GF_OBJ_HANDLE* a0) {
#line 2219
    SCOM_TARGET_UI* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_TARGET_UI(SCOM_TYPE(47));
    request->m_target = a0;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_SET_FLAG::create(unsigned int a0, unsigned int a1, unsigned int a2) {
#line 2259
    SCOM_SET_FLAG* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_SET_FLAG(SCOM_TYPE(48));
    request->m_value = a0;
    request->m_value2 = a1;
    request->m_value3 = a2;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_SET_CAMTYPE::create(int a0) {
#line 2273
    SCOM_SET_CAMTYPE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_SET_CAMTYPE(SCOM_TYPE(49));
    request->m_cameraType = a0;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_EXEC_CURRENT_BLADE::create(unsigned int a0) {
#line 6375
    SCOM_EXEC_CURRENT_BLADE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_EXEC_CURRENT_BLADE(SCOM_TYPE(78));
    request->m_value = a0;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_NIA_BLADE::create(bool a0) {
#line 3291
    SCOM_NIA_BLADE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_NIA_BLADE(SCOM_TYPE(82));
    request->m_value = a0;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_FIELD_SKILL::create(unsigned int a0) {
    if (!a0) {
        return -1;
    }
#line 4208
    SCOM_FIELD_SKILL* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_FIELD_SKILL(SCOM_TYPE(55));
    request->m_value = a0;
    request->m_value2 = 0;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_FIELD_SKILL::createWithBlade(unsigned int a0, unsigned int a1) {
    if (!a0) {
        return -1;
    }
#line 4215
    SCOM_FIELD_SKILL* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_FIELD_SKILL(SCOM_TYPE(55));
    request->m_value = a0;
    request->m_value2 = a1;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_ZONE::create(unsigned int a0) {
#line 5449
    SCOM_ZONE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ZONE(SCOM_TYPE(66));
    request->m_value = a0;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_SOLO_REX::create(bool a0) {
#line 6191
    SCOM_SOLO_REX* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_SOLO_REX(SCOM_TYPE(78));
    request->m_value = a0;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_REFRESH_COMPASS::create() {
    if (get()) {
        return -1;
    }
#line 6121
    SCOM_REFRESH_COMPASS* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_REFRESH_COMPASS(SCOM_TYPE(78));
    request->m_wait = 3;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_BATTLE_TASK_RESET::create() {
    if (get()) {
        return -1;
    }
#line 6145
    SCOM_BATTLE_TASK_RESET* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_BATTLE_TASK_RESET(SCOM_TYPE(78));
    request->m_wait = 3;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_QUEST_GIMMICK::createDoor(unsigned int id, float time) {
    if (time > 0.0f) {
        GfPlayFactory::createGimmickTaskComplete(gmk::GmkType(41), id, time);
        return -1;
    }
#line 2001
    SCOM_QUEST_GIMMICK* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(SCOM_TYPE(43));
    request->m_value = gmk::GmkType(41);
    request->m_value2 = id;
    request->m_value3 = time;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_QUEST_GIMMICK::createElevator(unsigned int id, float time) {
    if (time > 0.0f) {
        GfPlayFactory::createGimmickTaskComplete(gmk::GmkType(42), id, time);
        return -1;
    }
#line 2020
    SCOM_QUEST_GIMMICK* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(SCOM_TYPE(43));
    request->m_value = gmk::GmkType(42);
    request->m_value2 = id;
    request->m_value3 = time;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_QUEST_GIMMICK::createJump(unsigned int id, float time) {
    if (time > 0.0f) {
        GfPlayFactory::createGimmickTaskComplete(gmk::GmkType(37), id, time);
        return -1;
    }
#line 2039
    SCOM_QUEST_GIMMICK* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(SCOM_TYPE(43));
    request->m_value = gmk::GmkType(37);
    request->m_value2 = id;
    request->m_value3 = time;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_QUEST_GIMMICK::createMapGimmick(unsigned int id, float time) {
    if (time > 0.0f) {
        GfPlayFactory::createGimmickTaskComplete(gmk::GmkType(33), id, time);
        return -1;
    }
#line 2058
    SCOM_QUEST_GIMMICK* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(SCOM_TYPE(43));
    request->m_value = gmk::GmkType(33);
    request->m_value2 = id;
    request->m_value3 = time;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_QUEST_GIMMICK::createWarp(unsigned int id, float time) {
    if (time > 0.0f) {
        GfPlayFactory::createGimmickTaskComplete(gmk::GmkType(38), id, time);
        return -1;
    }
#line 2076
    SCOM_QUEST_GIMMICK* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(SCOM_TYPE(43));
    request->m_value = gmk::GmkType(38);
    request->m_value2 = id;
    request->m_value3 = time;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_QUEST_GIMMICK::createSalvage(unsigned int id, float time) {
    if (time > 0.0f) {
        GfPlayFactory::createGimmickTaskComplete(gmk::GmkType(31), id, time);
        return -1;
    }
#line 2095
    SCOM_QUEST_GIMMICK* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(SCOM_TYPE(43));
    request->m_value = gmk::GmkType(31);
    request->m_value2 = id;
    request->m_value3 = time;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_QUEST_GIMMICK::createTresure(unsigned int id, float time) {
    if (time > 0.0f) {
        GfPlayFactory::createGimmickTaskComplete(gmk::GmkType(9), id, time);
        return -1;
    }
#line 2114
    SCOM_QUEST_GIMMICK* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(SCOM_TYPE(43));
    request->m_value = gmk::GmkType(9);
    request->m_value2 = id;
    request->m_value3 = time;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_ENBOOK_IN_BATTLE::create(GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
#line 5464
    return GfReqSmallCom::addRequestParallel(new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ENBOOK_IN_BATTLE(SCOM_TYPE(69), GfReqSmallCom::sys()->newHandle(), acc.isValid() ? acc.getBdatId() : 0));
}

unsigned long SCOM_ENBOOK_DEFEAT_ENEMY::create(GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
#line 5495
    return GfReqSmallCom::addRequestParallel(new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ENBOOK_DEFEAT_ENEMY(SCOM_TYPE(72), GfReqSmallCom::sys()->newHandle(), acc.isValid() ? acc.getBdatId() : 0));
}

unsigned long SCOM_ENBOOK_DEAD_PLAYER::create(GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
#line 5510
    return GfReqSmallCom::addRequestParallel(new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ENBOOK_DEAD_PLAYER(SCOM_TYPE(73), GfReqSmallCom::sys()->newHandle(), acc.isValid() ? acc.getBdatId() : 0));
}

bool SCOM_POPUP::exec(fw::UpdateInfo const&) {
    if (--m_wait > 0) {
        return false;
    }
    if (m_param.m_type == 7 && GfGameManager::isBusyBladeCreateEvent()) {
        return false;
    }
    GfMenuObjPopup::open(m_param);
    return true;
}

unsigned long SCOM_POPUP::createAffinity(unsigned int a0, unsigned int a1, unsigned int a2) {
    if (GfGameManager::isStartGame()) {
        return -1;
    }
#line 5674
    SCOM_POPUP* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_POPUP(SCOM_TYPE(75));
    request->m_param.m_type = 5;
    request->m_param.m_value[0] = a0;
    request->m_param.m_value[1] = a1;
    request->m_param.m_value[2] = a2;
    request->m_wait = 20;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_POPUP::createIdea(unsigned int a0, unsigned int a1, unsigned int a2) {
    if (GfGameManager::isStartGame()) {
        return -1;
    }
#line 5705
    SCOM_POPUP* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_POPUP(SCOM_TYPE(75));
    request->m_param.m_type = 3;
    request->m_param.m_value[0] = a0;
    request->m_param.m_value[1] = a1;
    request->m_param.m_value[2] = a2;
    request->m_wait = 20;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_POPUP::createPouch(unsigned int a0, unsigned int a1, unsigned int a2) {
    if (GfGameManager::isStartGame() || a0 == 0) {
        return -1;
    }
#line 5719
    SCOM_POPUP* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_POPUP(SCOM_TYPE(75));
    request->m_param.m_type = 2;
    request->m_param.m_value[0] = a0;
    request->m_param.m_value[1] = a1;
    request->m_param.m_value[2] = a2;
    request->m_wait = 20;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_POPUP::createDevelop(unsigned int a0, unsigned int a1) {
    if (GfGameManager::isStartGame()) {
        return -1;
    }
#line 5661
    SCOM_POPUP* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_POPUP(SCOM_TYPE(75));
    request->m_param.m_type = 6;
    request->m_param.m_value[0] = a0;
    request->m_param.m_value[1] = a1;
    request->m_param.m_value[2] = 0;
    request->m_wait = 20;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_POPUP::createCrystalOK(unsigned int a0) {
    if (GfGameManager::isStartGame()) {
        return -1;
    }
#line 5745
    SCOM_POPUP* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_POPUP(SCOM_TYPE(75));
    request->m_param.m_type = 10;
    request->m_param.m_value[0] = a0;
    request->m_param.m_value[1] = 0;
    request->m_param.m_value[2] = 0;
    request->m_wait = 20;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_POPUP::createMercenaryReturn(unsigned int a0, unsigned int a1) {
    if (GfGameManager::isStartGame()) {
        return -1;
    }
    unsigned int leader = GfDataMercenaries::getTeamLeader(a1);
#line 5620
    SCOM_POPUP* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_POPUP(SCOM_TYPE(75));
    request->m_param.m_type = 8;
    request->m_param.m_value[0] = a0;
    request->m_param.m_value[1] = a1;
    request->m_param.m_value[2] = leader;
    request->m_wait = 20;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_POPUP::createAchievement(unsigned int blade, unsigned int line, unsigned int level) {
    if (GfGameManager::isStartGame()) {
        return -1;
    }
    if (!GfGameManager::fn_71002A9E68() && !GfMenuObjUtil::getMenuCondition(15)) {
        return -1;
    }
    if (GfGameUtil::setupSaveAchievementPopup(blade, line, level)) {
        return -1;
    }
#line 5692
    SCOM_POPUP* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_POPUP(SCOM_TYPE(75));
    request->m_param.m_type = 4;
    request->m_param.m_value[0] = blade;
    request->m_param.m_value[1] = line;
    request->m_param.m_value[2] = level;
    request->m_wait = 20;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_POPUP::createArts(unsigned int a0, unsigned int a1) {
    if (GfGameManager::isStartGame()) {
        return -1;
    }
    unsigned int type = GfBdatBtl::get()->getArtsDrWpnType(a1);
#line 5732
    SCOM_POPUP* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_POPUP(SCOM_TYPE(75));
    request->m_param.m_type = 1;
    request->m_param.m_value[0] = a0;
    request->m_param.m_value[1] = type;
    request->m_param.m_value[2] = a1;
    request->m_wait = 20;
    return GfReqSmallCom::addRequestParallel(request);
}


unsigned int SCOM_ACHIEV_INC::s_countSalvageShop;

bool SCOM_ACHIEV_INC::exec(fw::UpdateInfo const&) {
    GfAchievManager* manager = GfAchievManager::sys();
    if (manager == 0) {
        return true;
    }
    if (GfDataAchievement::isWaitControllFreeStats(m_value)) {
        if (!GfGameManager::isControlFree()) {
            return false;
        }
        if (m_value == 0x22) {
            if (s_countSalvageShop != 0) {
                s_countSalvageShop = 0;
                manager->incAchiev(0x22, 1);
            }
            return true;
        }
    }
    if (!m_blades.empty()) {
        manager->incAchievWithBlade(m_value, m_value2, m_blades);
    } else {
        manager->incAchiev(m_value, m_value2);
    }
    return true;
}

unsigned long SCOM_ACHIEV_INC::create(unsigned int type, int value, unsigned int blade) {
#line 3345
    SCOM_ACHIEV_INC* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ACHIEV_INC(type, value);
    if (blade != 0) {
        request->m_blades.push_back(blade);
    }
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_ACHIEV_INC::createParty(unsigned int type, int value) {
#line 3351
    SCOM_ACHIEV_INC* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ACHIEV_INC(type, value);
    GfDataBlade::getListPartyAll(request->m_blades);
    return GfReqSmallCom::addRequestParallel(request);
}

void SCOM_ACHIEV_INC::addTotalCount(unsigned int type, unsigned int value) {
    GfDataAchievement::addTotalCount(type, value);
}

void SCOM_ACHIEV_INC::createCrystal() {
    mm::mtl::FixedVector<unsigned short, 422> blades;
    GfDataBlade::getListPartyAll(blades);
    if (GfAchievManager* manager = GfAchievManager::sys()) {
        manager->incAchievWithBlade(0x43, 1, blades);
    }
}

GAME_VOICE_HANDLE* SCOM_FIELD_VOICE::create(CV_FIELD field, CV_PRIO prio) {
    ParamObj obj(GfGameManager::getControlMover());
    return GfFieldVoice::playVoice(obj, field, prio);
}

GAME_VOICE_HANDLE* SCOM_FIELD_VOICE::create(const ParamObj& obj, CV_FIELD field, CV_PRIO prio) {
    ParamObj target = obj;
    if (obj.m_handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1) && obj.m_id == 0) {
        target = ParamObj(GfGameManager::getControlMover());
    }
    return GfFieldVoice::playVoice(target, field, prio);
}

GAME_VOICE_HANDLE* SCOM_FIELD_VOICE::createHighLanding(const ParamObj& obj) {
    if (GfGameManager::getControlMover() != obj.m_handle) {
        return 0;
    }
    return create(obj, CV_FIELD(2), CV_PRIO(1));
}

GAME_VOICE_HANDLE* SCOM_FIELD_VOICE::createFallDead(const ParamObj& obj) {
    if (GfGameManager::isEvent(false)) {
        return 0;
    }
    return create(obj, CV_FIELD(1), CV_PRIO(4));
}

GAME_VOICE_HANDLE* SCOM_FIELD_VOICE::createMercenariesIn(unsigned int id) {
    return create(ParamObj(4, id), CV_FIELD(13), CV_PRIO(1));
}

GAME_VOICE_HANDLE* SCOM_FIELD_VOICE::createMercenariesLeader(unsigned int id) {
    return create(ParamObj(4, id), CV_FIELD(14), CV_PRIO(1));
}

unsigned long SCOM_FIELD_VOICE::createMercenariesStart(unsigned int id) {
    unsigned int blade = fn_7100567A44();
#line 4793
    SCOM_FIELD_VOICE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE();
    if (request == 0) {
        return -1;
    }
    request->add(ParamObj(4, id), CV_FIELD(15), CV_PRIO(1));
    if (blade != 0) {
        request->add(ParamObj(3, blade), CV_FIELD(15), CV_PRIO(1));
    }
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_FIELD_VOICE::createMercenariesEnd(unsigned int id) {
    unsigned int blade = fn_7100567A44();
#line 4810
    SCOM_FIELD_VOICE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE();
    if (request == 0) {
        return -1;
    }
    request->add(ParamObj(4, id), CV_FIELD(16), CV_PRIO(1));
    if (blade != 0) {
        request->add(ParamObj(3, blade), CV_FIELD(16), CV_PRIO(1));
    }
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_FIELD_VOICE::createMercenariesResult(unsigned int id) {
    unsigned int blade = fn_7100567A44();
#line 4827
    SCOM_FIELD_VOICE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE();
    if (request == 0) {
        return -1;
    }
    request->add(ParamObj(4, id), CV_FIELD(17), CV_PRIO(1));
    if (blade != 0) {
        request->add(ParamObj(3, blade), CV_FIELD(17), CV_PRIO(1));
    }
    return GfReqSmallCom::addRequestParallel(request);
}

GAME_VOICE_HANDLE* SCOM_FIELD_VOICE::createReleaseBlade(unsigned int id) {
    return create(ParamObj(4, id), CV_FIELD(18), CV_PRIO(1));
}

GAME_VOICE_HANDLE* SCOM_FIELD_VOICE::createAchievement(unsigned int id, unsigned int level) {
    ParamObj obj(4, id);
    if (level == 9) {
        return GfFieldVoice::playVoice(obj, CV_FIELD(26), 0, 0, CV_PRIO(1));
    }
    return GfFieldVoice::playVoice(obj, CV_FIELD(25), level / 3, level % 3, CV_PRIO(1));
}

GAME_VOICE_HANDLE* SCOM_FIELD_VOICE::createEngage(unsigned int id) {
    return GfFieldVoice::playVoice(ParamObj(4, id), CV_FIELD(36), 0, 0, CV_PRIO(1));
}

unsigned long SCOM_ADD_ETHER::create(int a0) {
    GfGameUtil::addEther(a0);
    return -1;
}

unsigned long SCOM_ADD_DEVELOP::create(unsigned int a0, unsigned int a1) {
    if (!a0 || !a1) {
        return -1;
    }
#line 464
    SCOM_ADD_DEVELOP* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ADD_DEVELOP(SCOM_TYPE(11));
    request->m_value = a1;
    request->m_value2 = a0;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_ADD_DEVELOP::createGmk(unsigned int a0, unsigned int a1) {
    return create(GfDataMap::getFieldZoneId(a0), a1);
}

bool SCOM_ADD_EXP::exec(fw::UpdateInfo const&) {
    unsigned int driver = m_value2;
    if (driver == 0) {
        if (m_value3 == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            driver = 0;
        } else {
            GfObjAcc acc(m_value3);
            driver = acc.getDriverId();
        }
    }
    if (m_value4) {
        GfGameUtil::addExpInn(m_value);
    } else {
        GfGameUtil::addExpBattle(driver, m_value);
    }
    return true;
}

bool SCOM_ADD_SP::exec(fw::UpdateInfo const&) {
    unsigned int driver = m_value2;
    if (driver == 0) {
        if (m_value3 == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            driver = 0;
        } else {
            GfObjAcc acc(m_value3);
            driver = acc.getDriverId();
        }
    }
    GfGameUtil::addSP(driver, m_value);
    return true;
}

bool SCOM_ADD_IDEA::exec(fw::UpdateInfo const&) {
    unsigned int driver = m_value2;
    if (driver == 0) {
        if (m_value4 == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            driver = 0;
        } else {
            GfObjAcc acc(m_value4);
            driver = acc.getDriverId();
        }
    }
    GfGameUtil::addIdeaPoint(driver, m_value3, m_value);
    return true;
}

bool SCOM_ADD_WP::exec(fw::UpdateInfo const&) {
    unsigned int driver;
    if (m_mode == 3) {
        driver = m_driver;
    } else {
        GfObjAcc acc(m_handle);
        driver = acc.getType() == 3 ? acc.getDriverId() : 0;
        if (m_mode == 0) {
            GfGameUtil::addWp(driver, m_value2, m_value);
            return true;
        } else if (m_mode == 2) {
            GfGameUtil::addWpForReserve(m_value);
            return true;
        } else if (m_mode != 1) {
            return true;
        }
    }
    GfGameUtil::addWpForObject(driver, m_value2, m_value);
    return true;
}

bool SCOM_MISSION_COMPLETE::exec(fw::UpdateInfo const&) {
    int flag = GfGameMercenaries::getMissionFlag(m_mission);
    if (flag == 2) {
        unsigned int team = GfDataMercenaries::getTeamIDByMissionID(m_mission);
        GfGameMercenaries::setMissionCompleteForce(m_mission);
        GfGameMercenaries::execMissionRewardAchievementBonusForBlade(m_mission);
        GfGameMercenaries::execMissionAchievementForBlade(m_mission);
        GfGameMercenaries::clearTeamMember(team);
        return false;
    } else if (flag == 3) {
        GfGameMercenaries::execMissionReward(m_mission);
    }
    return true;
}

unsigned long SCOM_MISSION_COMPLETE::create(unsigned int a0) {
    unsigned int flag = GfGameMercenaries::getMissionFlag(a0);
    if (flag != 2 && flag != 3) {
        return -1;
    }
#line 560
    SCOM_MISSION_COMPLETE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_MISSION_COMPLETE(SCOM_TYPE(80));
    request->m_mission = a0;
    return GfReqSmallCom::addRequest(request);
}

bool SCOM_SET_FLAG::exec(fw::UpdateInfo const&) {
    switch (m_value) {
    case 1:
        GfGameFlag::setLocal(1, m_value2, m_value3);
        break;
    case 2:
        GfGameFlag::setLocal(2, m_value2, m_value3);
        break;
    case 4:
        GfGameFlag::setLocal(4, m_value2, m_value3);
        break;
    case 8:
        GfGameFlag::setLocal(8, m_value2, m_value3);
        break;
    case 0x10:
        GfGameFlag::setLocal(0x10, m_value2, m_value3);
        break;
    case 0x20:
        GfGameFlag::setLocal(0x20, m_value2, m_value3);
        break;
    }
    return true;
}

bool SCOM_CHAR_DEAD::exec(fw::UpdateInfo const&) {
    GfObjAcc acc(m_handle);
    GfObjAcc killer(m_msg.m_killer);
    if (m_handle != m_msg.m_killer) {
        GfGameParty::getPartyId(m_handle);
    }
    if (acc.getType() == 5) {
        if (!GfGameManager::isPlayerDeadSequence()) {
            GfQuestTask::incSuppressEnemy(acc.getEnArrangeId());
            GfGameUtil::incEnemySuppress(acc.getEnArrangeId());
        }
        if (GfGameScene::sys()) {
            GfGameScene::sys()->setEnemyDead(m_handle);
        }
    }
    return true;
}

bool SCOM_DESTROY_GMK_SET::exec(fw::UpdateInfo const&) {
    GfFieldGimmick::disposeGmkSet(m_value);
    return true;
}

bool SCOM_CREATE_GMK_SET::exec(fw::UpdateInfo const&) {
    GfFieldGimmick::createGmkSet(m_value);
    GfAutoTalkManager::sys()->create();
    return true;
}

bool SCOM_ZONE::exec(fw::UpdateInfo const&) {
    if (!GfGameManager::isControlFree()) {
        return false;
    }
    unsigned int mapId = GfGameManager::getMapID();
    if (mapId == m_value && !GfDataMap::isMapCompleteFlag(mapId)) {
        GfDataMap::setMapCompleteFlag(m_value);
    }
    return true;
}

bool SCOM_CURRENT_BLADE::exec(fw::UpdateInfo const&) {
    unsigned int setId = GfDataBlade::getDriverSetID(m_value);
    unsigned int driver = GfDataBlade::getSetDriver(m_value);
    if (setId <= 4 && driver != 0) {
        GfDataDriver::setEquipBlade(driver, true, setId);
    }
    if (m_value == 1001) {
        GfDataBlade::setHikariCurrent(false);
    } else if (m_value == 1002) {
        GfDataBlade::setHikariCurrent(true);
    }
    return true;
}

GAME_VOICE_HANDLE* SCOM_SALVAGE_VOICE::create(GF_OBJ_HANDLE* handle, CV_SALVAGE voice) {
    return GfSalvageVoice::playVoice(handle, voice);
}

GAME_VOICE_HANDLE* SCOM_SALVAGE_VOICE::createResult(GF_OBJ_HANDLE* handle, CV_SALVAGE_RESULT voice) {
    return GfSalvageVoice::playResultVoice(handle, voice);
}

bool SCOM_SALVAGE_VOICE::isPlayEnd(GAME_VOICE_HANDLE* voice) {
    return GfGameVoice::getResult(voice) != CV_RESULT(2);
}

void SCOM_RANDOM_INN::setRandom() {
    GfDataUtil::setRandomInn();
}

bool GfReqSmallCom::isExistCommand() {
    if (!sys()->m_list.empty()) {
        return true;
    }
    return !sys()->m_parallelList.empty();
}

bool GfReqSmallCom::isExistCommandWithoutParallel() {
    return !sys()->m_list.empty();
}

bool SCOM_SOLO_REX::exec(fw::UpdateInfo const&) {
    for (unsigned int i = 0; i < 422; ++i) {
        unsigned int blade = GfDataBlade::getBladeID(i);
        if (blade == 0) {
            continue;
        }
        int creator = GfDataBlade::getCreator(blade);
        if (creator == 0 || creator == 1) {
            continue;
        }
        if (GfDataBlade::isDummyBlade(blade) || GfDataBlade::fn_71002383C8(blade)) {
            continue;
        }
        if (GfDataBlade::getSetDriver(blade) == 0 || GfDataBlade::isReleasedRareBlade(blade)) {
            continue;
        }
        GfDataBlade::setUnselect(blade, m_value);
    }
    return true;
}

SCOM_FADE::Fade SCOM_FADE::s_fades[3];
unsigned long SCOM_FADE::s_hCreatedReq = -1;

bool SCOM_FADE::exec(fw::UpdateInfo const&) {
    if (!GfMenuFade::isInitialized()) {
        return false;
    }
    for (int i = 0; i < 3; ++i) {
        if (s_fades[i].m_slot != static_cast<unsigned int>(-1)) {
            GfMenuFade::setFade(s_fades[i].m_slot, s_fades[i].m_frames, s_fades[i].m_color);
            s_fades[i].m_slot = -1;
        }
    }
    s_hCreatedReq = -1;
    return true;
}

unsigned long SCOM_FADE::create(unsigned int slot, unsigned int frames, const mm::Col4& color) {
    s_fades[slot].m_slot = slot;
    s_fades[slot].m_frames = frames;
    s_fades[slot].m_color = color;
    if (s_hCreatedReq == static_cast<unsigned long>(-1)) {
#line 1114
        SCOM_FADE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_FADE(SCOM_TYPE(27));
        s_hCreatedReq = GfReqSmallCom::addRequest(request);
    }
    return s_hCreatedReq;
}

mm::mtl::FixedQueue<SCOM_PARTY_ADD::Info, 16> SCOM_PARTY_ADD::s_info;

void SCOM_PARTY_ADD::addBlade(unsigned int blade, unsigned int driver, int param) {
    if (blade == 0) {
        return;
    }
    if (GfGameManager::isClearGame() && (blade - 1001 < 3 || GfDataBlade::fn_71002383C8(blade))) {
        return;
    }
    Info info = {GfDataBlade::getActBlade2CommonBlade(blade), driver, param, true, false, false, true, 1};
    s_info.push_back(info);
    create();
}

unsigned long SCOM_PARTY_ADD::create() {
    if (sys() != nullptr) {
        return -1;
    }
#line 2992
    SCOM_PARTY_ADD* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_PARTY_ADD();
    return GfReqSmallCom::addRequest(request);
}

void SCOM_PARTY_ADD::removeBlade(unsigned int driver, int slot, bool flag) {
    DataParamAcc acc(3, driver, GimmickType(0));
    if (acc.isValid()) {
        removeBlade(acc.getBlade(slot, false), flag, true);
    }
}

void SCOM_PARTY_ADD::removeDriver(unsigned int driver, bool flag) {
    Info info = {0, driver, -1, flag, false, false, true, 4};
    s_info.push_back(info);
    create();
}

bool SCOM_QUEST_REACH::exec(const fw::UpdateInfo&) {
    if (m_value != 3 || !GfGameManager::isInnerState(GF_STATE(20)) ||
        (GfGameEvent::get() != nullptr && GfGameEvent::get()->m_eventPhase >= 2)) {
        GfQuestTask::completeReachTask(m_value, m_value2);
        return true;
    }
    return false;
}

bool SCOM_SCRIPT::exec(const fw::UpdateInfo&) {
    if (m_name.length() == 0) {
        GfScriptManager::destroyScript(m_id);
        return true;
    }
    if (m_step == 0) {
        GfScriptManager::loadScript(m_id, m_name.m_str);
        m_step = 1;
    }
    if (m_step == 1) {
        if (GfScriptManager::isScriptLoadError(m_id)) {
            return true;
        }
        if (!GfScriptManager::isScriptWaitStart(m_id)) {
            return false;
        }
        GfScriptManager::startScript(m_id);
        if (!m_flag) {
            return true;
        }
        m_step = 2;
    }
    if (m_step == 2) {
        if (GfScriptManager::isScriptActive(m_id)) {
            return false;
        }
    }
    return true;
}

GF_SCOM_HANDLE* SCOM_SCRIPT::create(unsigned int id, const char* name, bool flag) {
    mm::mtl::FixStr<32> script;
    if (name != nullptr) {
        script = util::getNoPathExtName(name).m_str;
    }
#line 1205
    SCOM_SCRIPT* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_SCRIPT(SCOM_TYPE(29), id, script, flag);
    return reinterpret_cast<GF_SCOM_HANDLE*>(GfReqSmallCom::addRequestParallel(request));
}

mm::Vec3 SCOM_PARTY_LEADER::s_pos = mm::Vec3::zero;

}  // namespace gf
