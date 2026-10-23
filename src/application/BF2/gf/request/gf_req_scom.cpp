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
#include "classes/gf/GfAllocator.h"

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
    request->m_value3 = -1;
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


}  // namespace gf
