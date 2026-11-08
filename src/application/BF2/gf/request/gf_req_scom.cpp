#include "classes/gf/GfReqSmallCom.h"
#include "classes/gf/SCOM.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfGameMercenaries.h"
#include "classes/gf/GfFieldManager.h"
#include "classes/gf/GfMapManager.h"
#include "gf/GfObjFactory.h"
#include "classes/gf/GfInitParamMapSeamless.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfManager.h"
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
#include "classes/gf/SCOM_SET_BLADE.h"
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
#include "classes/gf/SCOM_ENBOOK_BOSS_TIME.h"
#include "classes/gf/SCOM_BC_PARTICLE.h"
#include "classes/gf/SCOM_OBJ_ALPHA.h"
#include "classes/gf/SCOM_OBJ_VFADE.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfAppendHandles.h"
#include "classes/gf/GfPause.h"
#include "mm/Math.h"
#include "classes/gf/SCOM_DEAD_PARTICLE.h"
#include "classes/gf/SCOM_HOMURI_PARTS.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfWeapon.h"
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
#include "gf/MsgObjectHealHp.h"
#include "gf/MsgObjectMaxHp.h"
#include "classes/gf/GfGameEvent.h"
#include "gf/GfUtil.h"
#include "classes/gf/SCOM_SCRIPT.h"
#include "classes/gf/SCOM_BATTLE_ARENA.h"
#include "classes/gf/SCOM_ADD_ECUBE.h"
#include "classes/gf/SCOM_ADD_SCORE.h"
#include "classes/gf/SCOM_CLEAR_TIME.h"
#include "classes/gf/SCOM_DESTROY_PARTY_OBJ.h"
#include "gf/GfGameUnit.h"
#include "classes/gf/GfGameArena.h"
#include "gf/MsgGameBtlArena.h"
#include "classes/gf/GfScriptManager.h"
#include "ml/MTRand.h"
#include "classes/gf/SCOM_ADD_ITEM.h"
#include "gf/GfItemUtil.h"
#include "gf/GfQuestUtil.h"
#include "gf/QuestListAcc.h"
#include "classes/gf/GfFieldBgm.h"
#include "gf/GfDataField.h"
#include "gf/GfDataParty.h"
#include "gf/GfDataItem.h"
#include "classes/gf/GfBdatItem.h"
#include "mm/mtl/FixStr.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/GfGameUtilQuestArts.h"
#include "fw/LangUtil.h"
#include "classes/fw/BdatManager.h"
#include "ui/UIUtil.h"
#include "classes/ui/UIManager.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/IGfEvent.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/SCOM_RELOAD_TEXT.h"
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

bool SCOM_ADD_ECUBE::exec(fw::UpdateInfo const&) {
    GfGameUtil::addEtherCube(m_value);
    return true;
}

unsigned long SCOM_ADD_ECUBE::create(unsigned int value) {
    if (value == 0) {
        return -1;
    }
#line 147
    SCOM_ADD_ECUBE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ADD_ECUBE(value);
    return GfReqSmallCom::addRequest(request);
}

bool SCOM_ADD_SCORE::exec(fw::UpdateInfo const&) {
    GfGameUtil::addScore(m_value);
    return true;
}

unsigned long SCOM_ADD_SCORE::create(unsigned int value) {
    if (value == 0) {
        return -1;
    }
#line 164
    SCOM_ADD_SCORE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ADD_SCORE(value);
    return GfReqSmallCom::addRequest(request);
}

void SCOM_CLEAR_TIME::create(unsigned int value) {
    GfGameUtil::applyClearTimeForArena(value);
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

void SCOM_OBJ_WARP_POS::create(GF_OBJ_HANDLE* handle, const mm::Vec3& pos, const mm::Vec3& rot, bool arg) {
    fw::Transform transform;
    transform.position = pos;
    float x = rot.x;
    float y = rot.y;
    float z = rot.z;
    float sx = ::sinf(x * 0.5f);
    float cx = ::cosf(x * 0.5f);
    float sy = ::sinf(y * 0.5f);
    float cy = ::cosf(y * 0.5f);
    float sz = ::sinf(z * 0.5f);
    float cz = ::cosf(z * 0.5f);
    transform.rotation = mm::Quat(sx * cy * cz + cx * sy * sz, cx * sy * cz - sx * cy * sz,
                                  cx * cy * sz - sx * sy * cz, cx * cy * cz + sx * sy * sz);
#line 767
    SCOM_OBJ_WARP_POS* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_OBJ_WARP_POS(SCOM_TYPE(17));
    request->m_value = handle;
    request->m_value2 = transform;
    request->m_value3 = arg;
    GfReqSmallCom::addRequestParallel(request);
}

void SCOM_OBJ_WARP_POS::create(GF_OBJ_HANDLE* handle, const fw::Transform& transform, bool arg) {
#line 782
    SCOM_OBJ_WARP_POS* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_OBJ_WARP_POS(SCOM_TYPE(17));
    request->m_value = handle;
    request->m_value2 = transform;
    request->m_value3 = arg;
    GfReqSmallCom::addRequestParallel(request);
}

bool SCOM_DESTROY_GAME_OBJ::exec(fw::UpdateInfo const&) {
    GfGameObj::destroyGameObjWithAttribute(m_value, m_value2, m_value3);
    return true;
}

void SCOM_DESTROY_GAME_OBJ::create(GF_OBJ_HANDLE* handle, float time, unsigned int attribute) {
    GfObjAcc acc(handle);
    acc.setFlag(17, true);
    acc.setAttribute(acc.getAttribute() & ~4u);
#line 832
    SCOM_DESTROY_GAME_OBJ* request =
        new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_DESTROY_GAME_OBJ(SCOM_TYPE(0));
    request->m_value = handle;
    request->m_value2 = time;
    request->m_value3 = attribute;
    GfReqSmallCom::addRequestParallel(request);
}

bool SCOM_DESTROY_PARTY_OBJ::exec(fw::UpdateInfo const&) {
    if (!m_isDestroyed) {
        m_isDestroyed = true;
        GfGameUnit::destroyParty(m_party, &m_handles);
    }
    for (GF_OBJ_HANDLE** it = m_handles.begin(); it != m_handles.end(); ++it) {
        if (GfObjUtil::getObj(*it) != nullptr) {
            return false;
        }
    }
    GfEvent::callPartyChange();
    return true;
}

bool SCOM_LOADING::exec(fw::UpdateInfo const&) {
    if (!GfMenuFade::isInitialized()) {
        return false;
    }
    GfMenuFade::setLoading(m_value, m_value2);
    return true;
}

inline void GfEvent::callReloadBdat(RELOAD_BDAT type) {
    GfEvent* event = get();
    unsigned int count = GfDataBdat::getReloadCount();
    for (unsigned long i = 0; i < event->m_listeners.size(); ++i) {
        event->m_listeners[i]->gevReloadBdat(type, count);
    }
}

bool SCOM_RELOAD_TEXT::exec(fw::UpdateInfo const&) {
    GfEvent::callReloadBdat(RELOAD_BDAT(0));
    GfDataBdat::releaseBdatInfo();
    fw::BdatManager::reloadBdat(1);
    ui::UIUtil::initBdatFP();
    GfDataBdat::setupBdatInfo();
    GfDataUtil::refreshBdatParam();
    ui::UIManager::get()->reloadText();
    GfEvent::callReloadBdat(RELOAD_BDAT(1));
    return true;
}

unsigned long SCOM_RELOAD_TEXT::create(fw::LangType lang) {
    if (fw::LangUtil::getLangType() == lang) {
        return -1;
    }
    fw::LangUtil::setLangType(lang);
#line 1278
    SCOM_RELOAD_TEXT* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_RELOAD_TEXT(SCOM_TYPE(31));
    return GfReqSmallCom::addRequest(request);
}

bool SCOM_EXEC_MOUNT::exec(fw::UpdateInfo const&) {
    GfMountManager::execMount(m_value, GFATTACH(0), m_value2);
    return true;
}

unsigned long SCOM_EXEC_MOUNT::create(GF_OBJ_HANDLE* obj, OPTMNT mount) {
#line 1323
    SCOM_EXEC_MOUNT* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_EXEC_MOUNT(SCOM_TYPE(35));
    request->m_value = obj;
    request->m_value2 = mount;
    return GfReqSmallCom::addRequest(request);
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

unsigned long SCOM_BATTLE_BGM::create(unsigned int id) {
    GfFieldBgm::sys()->setRscBattleBgmID(id);
#line 4357
    SCOM_BATTLE_BGM* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_BATTLE_BGM(SCOM_TYPE(62));
    request->m_value = id;
    return GfReqSmallCom::addRequest(request);
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

void SCOM_HOMURI_PARTS::create(unsigned int party, bool toMax, float duration) {
#line 5826
    SCOM_HOMURI_PARTS* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_HOMURI_PARTS(SCOM_TYPE(76));
    request->m_party = party;
    request->m_toMax = toMax;
    request->m_time = 0.0f;
    request->m_duration = duration;
    GfReqSmallCom::addRequestParallel(request);
}

bool SCOM_DEAD_PARTICLE::exec(fw::UpdateInfo const& info) {
    GfObjAcc acc(m_obj);
    GfObj* obj = acc.getObj();
    if (!obj) {
        return true;
    }
    GfComAsm* com = obj->getComponent<GfComAsm>(2);
    if (m_step == 0) {
        if (com && !com->isEnd(AnimLayer(0)) && !com->isLoop(AnimLayer(0))) {
            return false;
        }
        m_step = 1;
        GfObjUtil::setDeadParticle(m_obj, true, m_particle, acc.getAlpha());
        GfObjUtil::setDeadParticle(GfMountManager::getHandle(m_obj, static_cast<GFATTACH>(0), static_cast<OPTMNT>(3)),
                                   true, m_particle, 1.0f);
        return false;
    } else if (m_step == 1) {
        if (m_time > 0.0f) {
            float time = m_time - info.m_deltaTime;
            if (time <= 0.0f) {
                time = 0.0f;
            }
            m_time = time;
            float ratio = m_time / m_totalTime;
            GF_OBJ_HANDLE* mount = GfMountManager::getHandle(m_obj, static_cast<GFATTACH>(0), static_cast<OPTMNT>(3));
            GfObjUtil::setDeadParticle(m_obj, ratio > 0.0f, m_particle, ratio);
            GfObjUtil::setDeadParticle(mount, ratio > 0.0f, m_particle, ratio);
        }
        DataParamAcc param(m_obj);
        if (param.getHp() != 0) {
            GF_OBJ_HANDLE* mount = GfMountManager::getHandle(m_obj, static_cast<GFATTACH>(0), static_cast<OPTMNT>(3));
            GfObjUtil::setDeadParticle(m_obj, false, m_particle, acc.getAlpha());
            GfObjUtil::setDeadParticle(mount, false, m_particle, acc.getAlpha());
            return true;
        }
        return false;
    }
    return true;
}

unsigned long SCOM_DEAD_PARTICLE::create(GF_OBJ_HANDLE* obj, unsigned int particle, float time) {
    if (time < 1e-6f) {
        return -1;
    }
#line 5899
    return GfReqSmallCom::addRequestParallel(new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_DEAD_PARTICLE(SCOM_TYPE(77), GfReqSmallCom::sys()->newHandle(), obj, particle, time));
}

bool SCOM_BC_PARTICLE::exec(fw::UpdateInfo const& info) {
    GfObjAcc acc(m_obj);
    if (acc.getObj()) {
        unsigned int particle = m_particle;
        if (m_step == 0) {
            m_step = 1;
            GfObjUtil::setDeadParticle(m_obj, true, particle, acc.getAlpha());
            return false;
        } else if (m_step == 1) {
            if (m_time > 0.0f) {
                if (!m_isStop) {
                    m_time -= info.m_deltaTime;
                }
                if (m_time <= 0.0f) {
                    m_time = 0.0f;
                }
                float ratio = m_time / m_totalTime;
                GfObjUtil::setDeadParticle(m_obj, ratio > 0.0f, particle, ratio);
                return m_time <= 0.0f;
            }
        }
    }
    return true;
}

inline SCOM_BC_PARTICLE::SCOM_BC_PARTICLE(GF_OBJ_HANDLE* obj, float time)
    : SCOM(SCOM_TYPE(77)), m_obj(obj), m_step(0), m_time(time), m_totalTime(time), m_isStop(false) {
    DataParamAcc acc(obj);
    m_particle = acc.getAttribute(-1, false);
    if (GfDataUtil::isEffectKagutsuchi(acc)) {
        m_particle = 0x11;
    }
}

unsigned long SCOM_BC_PARTICLE::create(GF_OBJ_HANDLE* obj, float time) {
    if (obj == reinterpret_cast<GF_OBJ_HANDLE*>(-1) || time < 1e-6f) {
        return -1;
    }
#line 5963
    SCOM_BC_PARTICLE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_BC_PARTICLE(obj, time);
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_BC_PARTICLE::createPortal(GF_OBJ_HANDLE* obj, float time) {
    if (obj == reinterpret_cast<GF_OBJ_HANDLE*>(-1) || time < 1e-6f) {
        return -1;
    }
#line 5971
    SCOM_BC_PARTICLE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_BC_PARTICLE(obj, time);
    request->m_particle = 10;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_BC_PARTICLE::createPortalEvt(GF_OBJ_HANDLE* obj, float time) {
    if (obj == reinterpret_cast<GF_OBJ_HANDLE*>(-1) || time < 1e-6f) {
        return -1;
    }
#line 5982
    SCOM_BC_PARTICLE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_BC_PARTICLE(obj, time);
    request->m_particle = 10;
    request->m_isStop = true;
    return GfReqSmallCom::addRequestParallel(request);
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

bool SCOM_MAXIMUM_HEAL::exec(fw::UpdateInfo const&) {
    if (GfObj* obj = GfObjUtil::getObj(m_value)) {
        DataParamAcc acc(m_value);
        fw::MessageObject* object = obj;
        {
            MsgObjectMaxHp msg(acc.getHpMax(false));
            object->recieveMessage(object, msg);
        }
        {
            MsgObjectHealHp msg(0, 1);
            msg.m_flags = MsgObjectHealHp::Flags();
            object->recieveMessage(object, msg);
        }
    }
    return true;
}

unsigned long SCOM_MAXIMUM_HEAL::create(GF_OBJ_HANDLE* a0) {
#line 217
    SCOM_MAXIMUM_HEAL* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_MAXIMUM_HEAL(SCOM_TYPE(8));
    request->m_value = a0;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long GfReqSmallCom::addRequestParallel(SCOM* request) {
    GfReqSmallCom* self = sys();
    if (!self->m_isSubParallel) {
        self->m_parallelList.push_back(request);
    } else {
        self->m_subParallelList.push_back(request);
    }
    return request->m_handle;
}

unsigned long SCOM_ADD_EXP::createBattleExp(unsigned int a0, unsigned int a1) {
    if (!a0) {
        return -1;
    }
#line 264
    SCOM_ADD_EXP* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ADD_EXP(SCOM_TYPE(4));
    request->m_value = a0;
    request->m_value2 = a1;
    request->m_value3 = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    request->m_value4 = 0;
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

bool SCOM_ADD_TRUST::exec(fw::UpdateInfo const&) {
    if (GfGameManager::isGameTypeIra()) {
        if (m_value2 == 0) {
            mm::mtl::FixedVector<unsigned short, 32> drivers;
            GfDataDriver::getListIra(drivers);
            for (const unsigned short& driver : drivers) {
                if (GfDataDriver::isIraFront(driver) || GfDataDriver::isActivateUnuse(driver)) {
                    continue;
                }
                GfGameUtil::addTrustPointIra(driver, m_value);
            }
        } else if (GfDataDriver::isDriver(m_value2)) {
            GfGameUtil::addTrustPointIra(m_value2, m_value);
        }
    } else {
        if (m_value2 == 0) {
            mm::mtl::FixedVector<unsigned short, 422> blades;
            GfDataBlade::getListPartyAll(blades);
            for (unsigned short* it = blades.begin(); it != blades.end(); ++it) {
                GfGameUtil::addTrustPoint(*it, m_value);
            }
        } else {
            GfGameUtil::addTrustPoint(m_value2, m_value);
        }
    }
    return true;
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

bool SCOM_ADD_ITEM::exec(fw::UpdateInfo const&) {
    if (m_count < 0) {
        int room = GfItemUtil::getEnableStock(m_item) - GfItemUtil::getItemBoxCount(m_item);
        int count = m_count < room ? m_count : room;
        int rest = m_count > room ? m_count - room : 0;
        if (GfItemUtil::isEnableAddItemBox(m_item, count) && GfItemUtil::addItemBox(m_item, count)) {
            if (m_showPrecious && count > 0 && GfItemUtil::isPrecious(m_item)) {
                GfPlayFactory::createMenuPrecious(m_item, true);
            }
        }
        if (rest > 0) {
            ItemPrice price;
            GfItemUtil::getPrice(price, m_item, 0);
            GfGameUtil::addMoney(price.m_sellPrice * rest);
        }
    } else {
        ItemPrice price;
        GfItemUtil::getPrice(price, m_item, 0);
        for (int i = 0; i < m_count; i++) {
            if (GfItemUtil::isEnableAddItemBox(m_item, 1)) {
                if (GfItemUtil::addItemBox(m_item, 1) && m_showPrecious && GfItemUtil::isPrecious(m_item)) {
                    GfPlayFactory::createMenuPrecious(m_item, true);
                }
            } else {
                GfGameUtil::addMoney(price.m_sellPrice);
            }
        }
    }
    return true;
}

unsigned long SCOM_ADD_ITEM::create(unsigned int a0, int a1) {
    if (!a0 || !a1) {
        return -1;
    }
#line 739
    SCOM_ADD_ITEM* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ADD_ITEM(SCOM_TYPE(13));
    request->m_item = a0;
    request->m_count = a1;
    request->m_showPrecious = false;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_ADD_ITEM::createForBattle(unsigned int a0, int a1) {
    if (!a0 || !a1) {
        return -1;
    }
#line 746
    SCOM_ADD_ITEM* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ADD_ITEM(SCOM_TYPE(13));
    request->m_item = a0;
    request->m_count = a1;
    request->m_showPrecious = true;
    return GfReqSmallCom::addRequest(request);
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

bool SCOM_CREATE_MAP_OBJ::exec(fw::UpdateInfo const&) {
    if (GfMapManager::getMapJumpID() == m_value) {
        if (m_value2 != 0) {
            GfInitParamMapSeamless param;
            param.m_objId = m_value2;
            param.pad_90 = true;
            GfObjFactory::createMap(param);
        }
    } else {
        GfInitParamMapSeamless param;
        param.m_objId = m_value;
        GfObjFactory::createMap(param);
    }
    return true;
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

bool SCOM_OBJ_ALPHA::exec(fw::UpdateInfo const& info) {
    if (!m_isPauseStop || !GfPause::isPause(0x80)) {
        GfObjAcc acc(m_obj);
        if (acc.m_obj) {
            float start = m_startAlpha;
            if (start < 0.0f) {
                start = acc.getAlphaNormal();
                m_startAlpha = start;
            }
            if (m_time > 1e-6f && mm::fabs(m_alpha - start) >= 1e-6f) {
                m_elapsed += info.m_deltaTime;
                if (m_elapsed > m_time) {
                    m_elapsed = m_time;
                }
                float ratio = m_elapsed / m_time;
                acc.setAlphaNormal(m_alpha * ratio + start * (1.0f - ratio));
                if (m_elapsed < m_time) {
                    return false;
                }
            } else {
                acc.setAlphaNormal(m_alpha);
            }
        }
        return true;
    }
    return false;
}

unsigned long SCOM_OBJ_ALPHA::create(GF_OBJ_HANDLE* handle, float time, float alpha) {
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return -1;
    }
#line 1434
    return GfReqSmallCom::addRequestParallel(new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_OBJ_ALPHA(GfReqSmallCom::sys()->newHandle(), handle, time, alpha));
}

unsigned long SCOM_OBJ_ALPHA::createEventPause(GF_OBJ_HANDLE* handle, float time, float alpha) {
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return -1;
    }
#line 1442
    SCOM_OBJ_ALPHA* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_OBJ_ALPHA(GfReqSmallCom::sys()->newHandle(), handle, time, alpha);
    request->m_isPauseStop = true;
    return GfReqSmallCom::addRequestParallel(request);
}

void SCOM_OBJ_ALPHA::createWeapon(GF_OBJ_HANDLE* handle, float time, float alpha) {
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    GfAppendHandles* weapons = GfMountManager::getAppendHandles(handle, static_cast<GFATTACH>(0));
    if (!weapons) {
        return;
    }
    for (int i = 0; i < 10; i++) {
        GF_OBJ_HANDLE* weapon = weapons->getObjHandles()[i];
        if (weapon != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
#line 1460
            GfReqSmallCom::addRequestParallel(new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_OBJ_ALPHA(GfReqSmallCom::sys()->newHandle(), weapon, time, alpha));
        }
    }
}

SCOM_OBJ_VFADE::SCOM_OBJ_VFADE(GF_SCOM_HANDLE* handle, GF_OBJ_HANDLE* obj, float time, float ratio, VFPARTS parts,
                               VFACC acc, VFEFF effect, bool useKeyFrame, bool isOtherPartsOff)
    : SCOM(SCOM_TYPE(67), reinterpret_cast<unsigned long>(handle)), m_obj(obj), m_time(time), m_elapsed(0.0f),
      m_ratio(ratio), m_startRatio(-1.0f), m_parts(parts), m_acc(acc), m_effect(effect), m_keys(),
      m_isOtherPartsOff(isOtherPartsOff), pad_71(false) {
    if (useKeyFrame) {
        GfVolumeFade::setupKeyFrame(m_keys, effect);
        m_time = m_keys.size() < 2 ? 0.0f : m_keys.at(m_keys.size() - 1)->m_time;
    }
    DataParamAcc param(obj);
    if (GfDataUtil::isEffectKagutsuchi(param)) {
        m_effect = VFEFF(16);
    } else if (param.getObjType() == 10) {
        unsigned int party = GfGameParty::getPartyId(obj);
        DataParamAcc blade(GfGameParty::getHandleBlade(party, -1));
        DataParamAcc driver(GfGameParty::getHandleDriver(party, static_cast<PTPOS>(0)));
        if (GfDataUtil::isEffectKagutsuchi(blade) || GfDataUtil::isEffectKagutsuchi(driver)) {
            m_effect = VFEFF(16);
        }
    }
}

void SCOM_OBJ_VFADE::applyPartsRatio(GfVolumeFade* fade, float ratio) {
    fade->setFadeRatio(m_acc, m_parts, ratio);
    if (GfGameManager::isGameTypeIra()) {
        return;
    }
    if (!m_isOtherPartsOff) {
        return;
    }
    if (m_parts == VFPARTS(-1)) {
        return;
    }
    for (int i = 0; i < 6; i++) {
        if (i != m_parts) {
            fade->setFadeRatio(m_acc, VFPARTS(i), 0.0f);
        }
    }
}

bool SCOM_OBJ_VFADE::updateFade(const fw::UpdateInfo& info) {
    if (GfObjUtil::isValid(m_obj)) {
        if (!GfObjUtil::isUpdate(m_obj)) {
            return false;
        }
        if (GfVolumeFade* fade = GfObjUtil::getVolumeFade(m_obj)) {
            GfObjUtil::setVolumeFadeUserFlag(m_obj, true);
            m_elapsed += info.m_deltaTime;
            if (m_elapsed > m_time) {
                m_elapsed = m_time;
            }
            fade->setEffectType(m_effect);
            if (m_keys.size() != 0) {
                float ratio;
                bool done = getRatioBySec(ratio, m_keys, m_elapsed);
                applyPartsRatio(fade, ratio);
                return done;
            }
            float start = m_startRatio;
            if (start < 0.0f) {
                start = fade->getFadeRatio(m_acc, m_parts);
                m_startRatio = start;
            }
            if (m_time > 1e-6f && mm::fabs(m_ratio - start) >= 1e-6f) {
                float r = m_elapsed / m_time;
                applyPartsRatio(fade, m_ratio * r + start * (1.0f - r));
                if (m_elapsed < m_time) {
                    return false;
                }
            } else {
                applyPartsRatio(fade, m_ratio);
            }
        }
    }
    return true;
}

bool SCOM_OBJ_VFADE::exec(fw::UpdateInfo const& info) {
    if (!updateFade(info)) {
        return false;
    }
    GF_OBJ_HANDLE* obj = m_obj;
    if (obj != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
#line 1483
        SCOM_OBJ_VFADE_OFF* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_OBJ_VFADE_OFF(SCOM_TYPE(67));
        request->m_value = obj;
        GfReqSmallCom::addRequestParallel(request);
    }
    return true;
}

// the name is not the original's (inlined everywhere): the effect types a fade takes: 2..8 and 16 as they are, 1
// becomes 16 for an object GfDataUtil::isEffectKagutsuchi accepts; false for any other
static inline bool checkVFadeEffect(GF_OBJ_HANDLE* obj, unsigned int& effect) {
    switch (effect) {
    case 1: {
        DataParamAcc param(obj);
        effect = GfDataUtil::isEffectKagutsuchi(param) ? 16 : 1;
        break;
    }
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 16:
        break;
    default:
        return false;
    }
    return true;
}

inline unsigned long SCOM_OBJ_VFADE::create(GF_OBJ_HANDLE* obj, float time, float ratio, VFPARTS parts, VFACC acc,
                                            VFEFF effect) {
#line 1691
    SCOM_OBJ_VFADE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_OBJ_VFADE(
        reinterpret_cast<GF_SCOM_HANDLE*>(GfReqSmallCom::sys()->newHandle()), obj, time, ratio, parts, acc, effect, false, false);
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_OBJ_VFADE::createParts(GF_OBJ_HANDLE* obj, float time, float ratio, VFPARTS parts, VFACC acc) {
    DataParamAcc param(obj);
    unsigned int type = param.getAttribute(-1, false);
    if (!checkVFadeEffect(obj, type)) {
        return -1;
    }
    return create(obj, time, ratio, parts, acc, VFEFF(type));
}

unsigned long SCOM_OBJ_VFADE::createPartsWithSingle(GF_OBJ_HANDLE* obj, float time, float ratio, VFPARTS parts,
                                                    VFACC acc) {
    DataParamAcc param(obj);
    unsigned int type = param.getAttribute(-1, false);
    if (!checkVFadeEffect(obj, type)) {
        return -1;
    }
#line 1746
    SCOM_OBJ_VFADE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_OBJ_VFADE(
        reinterpret_cast<GF_SCOM_HANDLE*>(GfReqSmallCom::sys()->newHandle()), obj, time, ratio, parts, acc, VFEFF(type), false, true);
    return GfReqSmallCom::addRequestParallel(request);
}

float SCOM_OBJ_VFADE::createDead(GF_OBJ_HANDLE* obj, unsigned int effect) {
    float time = 0.0f;
    if (!checkVFadeEffect(obj, effect)) {
        return time;
    }
    if (GfObjUtil::getVolumeFade(obj) != nullptr) {
#line 1711
        SCOM_OBJ_VFADE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_OBJ_VFADE(
            reinterpret_cast<GF_SCOM_HANDLE*>(GfReqSmallCom::sys()->newHandle()), obj, 1.0f, 1.0f, VFPARTS(-1), VFACC(0), VFEFF(effect), true, false);
        GfReqSmallCom::addRequestParallel(request);
        if (request != nullptr) {
            request->pad_71 = true;
            time = request->getKeyFrameSec();
        }
    }
    return time;
}

unsigned long SCOM_OBJ_VFADE::createBattle(GF_OBJ_HANDLE* obj, float ratio, unsigned int effect) {
    if (obj == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return -1;
    }
    if (!checkVFadeEffect(obj, effect)) {
        return -1;
    }
    return create(obj, 0.0f, ratio, VFPARTS(-1), VFACC(4), VFEFF(effect));
}

void SCOM_OBJ_VFADE::fn_710055E1A4(GF_OBJ_HANDLE* obj, float ratio, unsigned int effect) {
    if (obj == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    if (!checkVFadeEffect(obj, effect)) {
        return;
    }
#line 1792
    SCOM_OBJ_VFADE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_OBJ_VFADE(
        reinterpret_cast<GF_SCOM_HANDLE*>(GfReqSmallCom::sys()->newHandle()), obj, 0.0f, ratio, VFPARTS(-1), VFACC(4), VFEFF(effect), false, false);
    if (request != nullptr) {
        fw::UpdateInfo info;
        info.m_speed = 1.0f;
        info.m_frameTime = GfInfo::m_fSecPerFrame;
        info.m_deltaTime = GfInfo::m_fSecPerFrame;
        request->updateFade(info);
        delete request;
    }
}

unsigned long SCOM_OBJ_VFADE::createBattleParts(GF_OBJ_HANDLE* obj, float time, float ratio, unsigned int,
                                                VFPARTS parts) {
    if (obj == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return -1;
    }
    GfObjAcc acc(obj);
    switch (acc.getType()) {
    case 4:
        if (acc.getBladeId() == 1105) {
            return createParts(obj, time, ratio, parts, VFACC(4));
        }
        parts = VFPARTS(0);
        break;
    case 5:
        if (acc.isEnemyBlade()) {
            return createParts(obj, time, ratio, parts, VFACC(4));
        }
        break;
    }
    return createPartsWithSingle(obj, time, ratio, parts, VFACC(4));
}

unsigned long SCOM_QUEST_REACH::createDiscoverLandmark(unsigned int a0) {
#line 1944
    SCOM_QUEST_REACH* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_QUEST_REACH(SCOM_TYPE(42));
    request->m_value = 1;
    request->m_value2 = a0;
    GfReqSmallCom::addRequestParallel(request);
    return createArriveLandmark(a0);
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

unsigned long SCOM_QUEST_GIMMICK::createEnemyWave(unsigned int id, float time) {
    if (time > 0.0f) {
        GfPlayFactory::createGimmickTaskComplete(gmk::GmkType(58), id, time);
        return -1;
    }
#line 2133
    SCOM_QUEST_GIMMICK* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(SCOM_TYPE(43));
    request->m_value = gmk::GmkType(58);
    request->m_value2 = id;
    request->m_value3 = time;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_QUEST_GIMMICK::createCamp(unsigned int id, float time) {
    if (time > 0.0f) {
        GfPlayFactory::createGimmickTaskComplete(gmk::GmkType(62), id, time);
        return -1;
    }
#line 2152
    SCOM_QUEST_GIMMICK* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(SCOM_TYPE(43));
    request->m_value = gmk::GmkType(62);
    request->m_value2 = id;
    request->m_value3 = time;
    return GfReqSmallCom::addRequest(request);
}

unsigned long SCOM_QUEST_GIMMICK::createCollection(unsigned int id, float time) {
    if (time > 0.0f) {
        GfPlayFactory::createGimmickTaskComplete(gmk::GmkType(28), id, time);
        return -1;
    }
#line 2171
    SCOM_QUEST_GIMMICK* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_QUEST_GIMMICK(SCOM_TYPE(43));
    request->m_value = gmk::GmkType(28);
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

bool SCOM_ENBOOK_BOSS_TIME::exec(fw::UpdateInfo const&) {
    GfGameUtil::setClearNamedTime(m_enemy, m_time, static_cast<GFDIFF>(GfGameManager::getBtlDifficult()));
    return true;
}

unsigned long SCOM_ENBOOK_BOSS_TIME::create(GF_OBJ_HANDLE* handle, unsigned int time) {
    DataParamAcc acc(handle);
#line 5480
    return GfReqSmallCom::addRequestParallel(new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ENBOOK_BOSS_TIME(SCOM_TYPE(71), GfReqSmallCom::sys()->newHandle(), acc.isValid() ? acc.getBdatId() : 0, time));
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

unsigned long SCOM_POPUP::createQuest(QuestID id) {
    if (GfGameManager::isStartGame()) {
        return -1;
    }
    if (!QuestListAcc::get()->getListVisible(id)) {
        return -1;
    }
#line 5607
    SCOM_POPUP* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_POPUP(SCOM_TYPE(75));
    // a zeroed local copied in: the original stores the two unused values as one 8-byte zero
    GfMenuObjPopup::OpenParam param = {};
    param.m_type = 9;
    param.m_value[0] = id.m_id;
    request->m_param = param;
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

void SCOM_POPUP::cancelMercenaryReturn(unsigned int mapId, unsigned int teamId) {
    GfMenuObjPopup::OpenParam param;
    param.m_type = 8;
    param.m_value[0] = mapId;
    param.m_value[1] = teamId;
    param.m_value[2] = GfDataMercenaries::getTeamLeader(teamId);
    GfMenuObjPopup::remove(param);
}

unsigned long SCOM_POPUP::createMercenaryAdd(unsigned int a0) {
    if (a0 == 0 || GfGameManager::isStartGame() || !GfGameCond::isGameCond(2097)) {
        return -1;
    }
    GfMenuObjPopup::OpenParam param = {};
    param.m_type = 7;
    param.m_value[0] = GfDataMercenaries::getMissionMapID(a0);
#line 5649
    SCOM_POPUP* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_POPUP(SCOM_TYPE(75));
    request->m_param = param;
    request->m_wait = 20;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_POPUP::createAchievement(unsigned int blade, unsigned int line, unsigned int level) {
    if (GfGameManager::isStartGame()) {
        return -1;
    }
    if (!GfGameManager::isGameTypeIra() && !GfMenuObjUtil::getMenuCondition(15)) {
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

unsigned long SCOM_POPUP::createChBtlNewChallenge(unsigned int) {
    if (GfGameManager::isStartGame() || !GfGameManager::isInstalledBattleArenaContents() || GfItemUtil::getItemBoxCount(25443) == 0 ||
        GfGameFlag::getLocal(1, 35337) == 0) {
        return -1;
    }
#line 5765
    SCOM_POPUP* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_POPUP(SCOM_TYPE(75));
    request->m_param.m_type = 10;
    request->m_param.m_value[0] = 47;
    request->m_param.m_value[1] = 0;
    request->m_param.m_value[2] = 0;
    request->m_wait = 20;
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_POPUP::createCraft(unsigned int driver, unsigned int a1, unsigned int a2) {
    if (GfGameManager::isStartGame() || GfDataDriver::isActivateUnuse(driver)) {
        return -1;
    }
#line 5782
    SCOM_POPUP* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_POPUP(SCOM_TYPE(75));
    request->m_param.m_type = 11;
    request->m_param.m_value[0] = driver;
    request->m_param.m_value[1] = a1;
    request->m_param.m_value[2] = a2;
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

unsigned long SCOM_ACHIEV_INC::createBladeArts(GF_OBJ_HANDLE* handle, unsigned int arts) {
    DataParamAcc acc(handle);
    if (!acc.isValid()) {
        return -1;
    }
    unsigned int slot = 0;
    for (; slot < 3; slot++) {
        if (acc.getBladeArts(slot, false) == arts) {
            break;
        }
    }
    if (slot >= 3) {
        return -1;
    }
    unsigned int blade = acc.isValid() && acc.getObjType() == 3 ? acc.getBdatId() : 0;
    GfGameUtilQuestArts::calcQuestArtsCount(blade, slot);
    unsigned int type = slot + 0x5D;
#line 3448
    SCOM_ACHIEV_INC* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        SCOM_ACHIEV_INC(GfReqSmallCom::sys()->newHandle(), 0x62, 1, acc.getBlade(-1, false));
    GfReqSmallCom::addRequestParallel(request);
#line 3451
    request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        SCOM_ACHIEV_INC(GfReqSmallCom::sys()->newHandle(), type, 1, acc.getBlade(-1, false));
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_ACHIEV_INC::createBladeArtsSp(GF_OBJ_HANDLE* handle, unsigned int arts) {
    if (arts == 0) {
        return -1;
    }
    DataParamAcc acc(handle);
    if (!acc.isValid() || (acc.getBladeArtsEx(false) != arts && acc.getBladeArtsEx2(false) != arts)) {
        return -1;
    }
#line 3469
    SCOM_ACHIEV_INC* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ACHIEV_INC(GfReqSmallCom::sys()->newHandle(), 0x62, 1, acc.getBlade(-1, false));
    GfReqSmallCom::addRequestParallel(request);
#line 3472
    request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ACHIEV_INC(GfReqSmallCom::sys()->newHandle(), 0x60, 1, acc.getBlade(-1, false));
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_ACHIEV_INC::createBladeNArts(GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
    if (!acc.isValid()) {
        return -1;
    }
#line 3484
    SCOM_ACHIEV_INC* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ACHIEV_INC(GfReqSmallCom::sys()->newHandle(), 0x61, 1, acc.getBlade(-1, false));
    return GfReqSmallCom::addRequestParallel(request);
}

void SCOM_ACHIEV_INC::createElementalCombo(GF_OBJ_HANDLE* handle) {
    fn_7100564360(handle, 0x7D, 1);
}

void SCOM_ACHIEV_INC::fn_7100564360(GF_OBJ_HANDLE* handle, unsigned int type, unsigned int value) {
    addTotalCount(type - 1, value);
    create(type - 1, value, 0);
    mm::mtl::FixedVector<unsigned short, 422> blades;
    fn_7100563BB4(blades, handle, true);
    if (!blades.empty()) {
        unsigned short* it = blades.begin();
        unsigned short* end = blades.end();
        do {
            create(type, value, *it);
        } while (++it != end);
    }
}

void SCOM_ACHIEV_INC::createElementalComboFinish(GF_OBJ_HANDLE* handle) {
    fn_7100564360(handle, 0x7F, 1);
}

void SCOM_ACHIEV_INC::createFightCombo(GF_OBJ_HANDLE* handle) {
    fn_71005645F0(handle, 0x79);
}

void SCOM_ACHIEV_INC::createFightComboFinish(GF_OBJ_HANDLE* handle) {
    fn_71005645F0(handle, 0x7B);
}

void SCOM_ACHIEV_INC::createChainAttack(GF_OBJ_HANDLE* handle) {
    if (!GfGameManager::isGameTypeIra()) {
        fn_7100564360(handle, 0x81, 1);
        return;
    }
    GfObjAcc acc(handle);
    if (GfDataDriver::isIraFront(acc.getDriverId())) {
        return;
    }
    unsigned int blade = GfDataDriver::getIraBlade(acc.getDriverId(), -1);
    addTotalCount(0x80, 1);
    create(0x80, 1, 0);
    create(0x81, 1, blade);
}

void SCOM_ACHIEV_INC::createButtonChallenge() {
    fn_7100564360(GfGameManager::getPartyLeaderDriver(), 0x83, 1);
}

void SCOM_ACHIEV_INC::createHelp(GF_OBJ_HANDLE* handle) {
    fn_7100564360(handle, 0x85, 1);
}

void SCOM_ACHIEV_INC::createPotGet() {
    fn_7100564360(GfGameManager::getPartyLeaderDriver(), 0x87, 1);
}

void SCOM_ACHIEV_INC::createAvoid(GF_OBJ_HANDLE* handle) {
    fn_7100564360(handle, 0x89, 1);
}

void SCOM_ACHIEV_INC::createGuard(GF_OBJ_HANDLE* handle) {
    fn_7100564360(handle, 0x8B, 1);
}

void SCOM_ACHIEV_INC::createBladeChange(GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
    unsigned int blade = acc.isValid() ? acc.getBdatId() : 0;
    addTotalCount(0x8C, 1);
    create(0x8C, 1, 0);
    create(0x8D, 1, blade);
}

void SCOM_ACHIEV_INC::createRecover(GF_OBJ_HANDLE* handle, unsigned int value) {
    fn_7100564360(handle, 0x95, value);
}

void SCOM_ACHIEV_INC::createBackAttack(GF_OBJ_HANDLE* handle) {
    mm::mtl::FixedVector<unsigned short, 422> blades;
    fn_7100563BB4(blades, handle, true);
    if (!blades.empty()) {
        unsigned short* it = blades.begin();
        unsigned short* end = blades.end();
        do {
            create(0x96, 1, *it);
        } while (++it != end);
    }
}

void SCOM_ACHIEV_INC::createDamageMax(GF_OBJ_HANDLE* handle, unsigned int value) {
    addTotalCount(0x92, value);
    create(0x92, value, 0);
    mm::mtl::FixedVector<unsigned short, 422> blades;
    DataParamAcc acc(handle);
    unsigned int objType = acc.getObjType();
    if (objType == 4) {
        blades.push_back(acc.isValid() ? acc.getBdatId() : 0);
    } else if (objType == 3) {
        fn_7100563BB4(blades, handle, true);
    }
    if (!blades.empty()) {
        unsigned short* it = blades.begin();
        unsigned short* end = blades.end();
        do {
            create(0x93, value, *it);
        } while (++it != end);
    }
}

void SCOM_ACHIEV_INC::createDamageAdd(GF_OBJ_HANDLE* handle, unsigned int value) {
    addTotalCount(0x8E, value);
    create(0x8E, value, 0);
    mm::mtl::FixedVector<unsigned short, 422> blades;
    DataParamAcc acc(handle);
    unsigned int objType = acc.getObjType();
    if (objType == 4) {
        blades.push_back(acc.isValid() ? acc.getBdatId() : 0);
    } else if (objType == 3) {
        fn_7100563BB4(blades, handle, true);
    }
    if (!blades.empty()) {
        unsigned short* it = blades.begin();
        unsigned short* end = blades.end();
        do {
            create(0x8F, value, *it);
        } while (++it != end);
    }
}

void SCOM_ACHIEV_INC::createDamageGet(GF_OBJ_HANDLE* handle, unsigned int value) {
    addTotalCount(0x90, value);
    create(0x90, value, 0);
    mm::mtl::FixedVector<unsigned short, 422> blades;
    fn_7100563BB4(blades, handle, true);
    if (!blades.empty()) {
        unsigned short* it = blades.begin();
        unsigned short* end = blades.end();
        do {
            create(0x91, value, *it);
        } while (++it != end);
    }
}

void SCOM_ACHIEV_INC::createCriticalHit(GF_OBJ_HANDLE* handle) {
    addTotalCount(0x72, 1);
    create(0x72, 1, 0);
    mm::mtl::FixedVector<unsigned short, 422> blades;
    fn_7100563BB4(blades, handle, true);
    if (!blades.empty()) {
        unsigned short* it = blades.begin();
        unsigned short* end = blades.end();
        do {
            create(0x73, 1, *it);
        } while (++it != end);
    }
}

void SCOM_ACHIEV_INC::createCriticalGet(GF_OBJ_HANDLE* handle) {
    addTotalCount(0x74, 1);
    create(0x74, 1, 0);
    mm::mtl::FixedVector<unsigned short, 422> blades;
    fn_7100563BB4(blades, handle, true);
    if (!blades.empty()) {
        unsigned short* it = blades.begin();
        unsigned short* end = blades.end();
        do {
            create(0x75, 1, *it);
        } while (++it != end);
    }
}

void SCOM_ACHIEV_INC::createKizuna(GF_OBJ_HANDLE* handle) {
    addTotalCount(0x76, 1);
    create(0x76, 1, 0);
    mm::mtl::FixedVector<unsigned short, 422> blades;
    fn_7100563BB4(blades, handle, true);
    if (!blades.empty()) {
        unsigned short* it = blades.begin();
        unsigned short* end = blades.end();
        do {
            create(0x77, 1, *it);
        } while (++it != end);
    }
}

void SCOM_ACHIEV_INC::createBladeCreate() {
    addTotalCount(49, 1);
    create(49, 1, 0);
    mm::mtl::FixedVector<unsigned short, 422> blades;
    GfDataBlade::getListPartyAll(blades);
    if (GfAchievManager* manager = GfAchievManager::sys()) {
        manager->incAchievWithBlade(50, 1, blades);
    }
}

void SCOM_ACHIEV_INC::createCrystal() {
    mm::mtl::FixedVector<unsigned short, 422> blades;
    GfDataBlade::getListPartyAll(blades);
    if (GfAchievManager* manager = GfAchievManager::sys()) {
        manager->incAchievWithBlade(0x43, 1, blades);
    }
}

void SCOM_ACHIEV_INC::createOverKill() {
    mm::mtl::FixedVector<unsigned short, 422> blades;
    GfDataBlade::getListParty(blades);
    if (GfAchievManager* manager = GfAchievManager::sys()) {
        manager->incAchievWithBlade(0x9B, 1, blades);
    }
}

void SCOM_ACHIEV_INC::createCbCube(unsigned int value) {
    if (!GfGameManager::isInstalledBattleArenaContents()) {
        return;
    }
    GfDataAchievement::addTotalCount(0x9D, value);
    mm::mtl::FixedVector<unsigned short, 422> blades;
    GfDataBlade::getListParty(blades);
    if (GfAchievManager* manager = GfAchievManager::sys()) {
        manager->checkAchievWithBlade(0x9C, value, blades);
    }
}

void SCOM_ACHIEV_INC::createKizunaTalk() {
    unsigned int count = 0;
    for (int i = 1; i <= 100; ++i) {
        if (GfGameFlag::getLocal(2, i) == 2) {
            ++count;
        }
    }
    count += GfGameFlag::getLocal(0x20, 0x141);
    GfDataAchievement::setTotalCount(75, 0);
    GfDataAchievement::addTotalCount(75, count);
}

void SCOM_ACHIEV_INC::createTiger(unsigned int type) {
    mm::mtl::FixedVector<unsigned short, 422> blades;
    GfDataBlade::getListParty(blades);
    if (GfAchievManager* manager = GfAchievManager::sys()) {
        manager->incAchievWithBlade(type, 1, blades);
    }
}

void SCOM_ACHIEV_INC::createDriverCombo2(GF_OBJ_HANDLE* handle) {
    if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) && handle != GfGameManager::getPartyLeaderDriver()) {
        return;
    }
    if (!GfQuestInfo::isQuestOrder(0x8ED)) {
        return;
    }
    unsigned int count = GfGameFlag::getLocal(8, 0x87C);
    if (count < 0xFF) {
        GfGameFlag::setLocal(8, 0x87C, count + 1);
    }
}

void SCOM_ACHIEV_INC::createDriverCombo4(GF_OBJ_HANDLE* handle) {
    if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) && handle != GfGameManager::getPartyLeaderDriver()) {
        return;
    }
    if (!GfQuestInfo::isQuestOrder(0x8F0)) {
        return;
    }
    unsigned int count = GfGameFlag::getLocal(8, 0x87D);
    if (count < 0xFF) {
        GfGameFlag::setLocal(8, 0x87D, count + 1);
    }
}

void SCOM_ACHIEV_INC::createBladeCombo2(GF_OBJ_HANDLE*) {
    if (!GfQuestInfo::isQuestOrder(0x8F3)) {
        return;
    }
    unsigned int count = GfGameFlag::getLocal(8, 0x87E);
    if (count < 0xFF) {
        GfGameFlag::setLocal(8, 0x87E, count + 1);
    }
}

void SCOM_ACHIEV_INC::createBladeCombo3(GF_OBJ_HANDLE*) {
    if (!GfQuestInfo::isQuestOrder(0x8F6)) {
        return;
    }
    unsigned int count = GfGameFlag::getLocal(8, 0x87F);
    if (count < 0xFF) {
        GfGameFlag::setLocal(8, 0x87F, count + 1);
    }
}

void SCOM_ACHIEV_INC::createFusionCombo(GF_OBJ_HANDLE*) {
    if (!GfQuestInfo::isQuestOrder(0x8F9)) {
        return;
    }
    unsigned int count = GfGameFlag::getLocal(8, 0x880);
    if (count < 0xFF) {
        GfGameFlag::setLocal(8, 0x880, count + 1);
    }
}

// counts the field skill use (m_value) for m_value2's blade, or for every blade the party's drivers engage
bool SCOM_FIELD_SKILL::exec(const fw::UpdateInfo&) {
    if (m_value2 == 0) {
        if (!GfGameManager::isControlFree()) {
            return false;
        }
        for (unsigned int i = 0; i < 3; i++) {
            DataParamAcc driver(3, GfGameParty::getDriverBdatId(i, static_cast<PTPOS>(0)), GimmickType(0));
            if (driver.isValid()) {
                unsigned int driverId = 0;
                if (driver.isValid() && driver.getObjType() == 3) {
                    driverId = driver.getBdatId();
                }
                int num = GfDataDriver::getMaxSetBladeNum(driverId);
                for (int slot = 0; slot < num; slot++) {
                    unsigned int blade = driver.getBlade(slot, false);
                    if (blade != 0) {
                        GfQuestUtil::incFieldSkillTask(blade, m_value);
                    }
                }
            }
        }
    } else {
        GfQuestUtil::incFieldSkillTask(m_value2, m_value);
    }
    return true;
}

// 1.0.0 has it out of line; 3.0.1 has no copy (exec inlines it)
inline bool SCOM_FIELD_VOICE::isStopVoice() const {
    return (m_stopOnEvent && GfGameManager::isPlayEvent()) || m_flagD3;
}

bool SCOM_FIELD_VOICE::getIraMember(mm::mtl::FixedVector<GF_OBJ_HANDLE*, 9>& handles) {
    for (unsigned int i = 0; i < 3; i++) {
        for (unsigned int j = 0; j < 3; j++) {
            GF_OBJ_HANDLE* handle = GfGameParty::getHandleDriver(i, static_cast<PTPOS>(j));
            if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                handles.push_back(handle);
            }
        }
    }
    return !handles.empty();
}

// plays the first queued voice once its wait ran out and the player has control, waits for it, then takes it off;
// done when none is left
bool SCOM_FIELD_VOICE::exec(const fw::UpdateInfo& info) {
    if (m_flagD0) {
        if (!GfGameManager::isControlFree()) {
            return false;
        }
        m_flagD0 = false;
        m_flagD1 = true;
    }
    if (m_flagD1) {
        if (!GfGameManager::isControlFree()) {
            return true;
        }
    }
    Voice& voice = m_voices.first();
    if (voice.m_state == 0) {
        voice.m_wait -= info.m_deltaTime;
        if (voice.m_wait > 0.0f) {
            return false;
        }
        if (isStopVoice()) {
            voice.m_voice = 0;
        } else {
            voice.m_voice = GfFieldVoice::playVoice(voice.m_obj, voice.m_field, voice.m_prio);
            if (voice.m_voice != 0) {
                voice.m_state = CV_RESULT(2);
                return false;
            }
        }
        voice.m_state = CV_RESULT(3);
    } else if (voice.m_state == 2) {
        if (isStopVoice() && voice.m_voice != 0) {
            GfGameVoice::playStop(voice.m_voice);
            voice.m_voice = 0;
        }
        voice.m_state = GfGameVoice::getResult(voice.m_voice);
        if (voice.m_state == 2) {
            return false;
        }
    }
    if (voice.m_state >= 3) {
        m_voices.pop();
        if (m_voices.empty()) {
            return true;
        }
    }
    return false;
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

// the queued or running request with that handle, or nullptr (the name is not the original's)
static SCOM* findRequest(unsigned long handle) {
    GfReqSmallCom* com = GfReqSmallCom::sys();
    if (com == nullptr) {
        return nullptr;
    }
    for (GfReqSmallCom::RequestList::iterator it = com->m_list.begin(); it != com->m_list.end(); ++it) {
        if ((*it)->m_handle == handle) {
            return *it;
        }
    }
    for (GfReqSmallCom::RequestList::iterator it = com->m_parallelList.begin(); it != com->m_parallelList.end(); ++it) {
        if ((*it)->m_handle == handle) {
            return *it;
        }
    }
    return nullptr;
}

void SCOM_FIELD_VOICE::playStop(GF_SCOM_HANDLE* handle) {
    if (SCOM_FIELD_VOICE* request = static_cast<SCOM_FIELD_VOICE*>(findRequest(reinterpret_cast<unsigned long>(handle)))) {
        request->m_flagD3 = true;
    }
}

GAME_VOICE_HANDLE* SCOM_FIELD_VOICE::createJump(const ParamObj& obj) {
    if (GfGameManager::getControlMover() != obj.m_handle || !GfGameManager::isControlFree()) {
        return 0;
    }
    SCOM_ACHIEV_INC::addTotalCount(2, 1);
    SCOM_ACHIEV_INC::create(2, 1, 0);
    if (ml::mtRandf1() < 0.4f) {
        return 0;
    }
    return create(obj, CV_FIELD(0), CV_PRIO(1));
}

unsigned long SCOM_FIELD_VOICE::createLandmark() {
    if (GfGameManager::isBattle()) {
        return -1;
    }
    if (GfGameScene::sys() != nullptr && GfGameScene::sys()->m_value634 < 60) {
        return -1;
    }
    int party = fn_71005680B0();
    if (party == -1) {
        return -1;
    }
    bool torna = GfGameManager::isGameTypeIra();
    GF_OBJ_HANDLE* driver = GfGameParty::getHandleDriver(party, static_cast<PTPOS>(0));
    GF_OBJ_HANDLE* partner;
    if (torna) {
        partner = GfGameParty::getHandleDriver(party, static_cast<PTPOS>(1));
    } else {
        partner = GfGameParty::getHandleBlade(party, -1);
    }
    unsigned int hp;
    {
        DataParamAcc acc(driver);
        hp = acc.getHp();
    }
    if (hp == 0) {
        return -1;
    }
#line 4611
    SCOM_FIELD_VOICE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(true);
    if (request == 0) {
        return -1;
    }
    request->add(ParamObj(driver), CV_FIELD(5), CV_PRIO(1));
    request->add(ParamObj(partner), CV_FIELD(5), CV_PRIO(3));
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_FIELD_VOICE::createUnexplored() {
    if (GfGameManager::isBattle()) {
        return -1;
    }
    if (GfGameScene::sys() != nullptr && GfGameScene::sys()->m_value634 < 60) {
        return -1;
    }
    int party = fn_71005680B0();
    if (party == -1) {
        return -1;
    }
    bool torna = GfGameManager::isGameTypeIra();
    GF_OBJ_HANDLE* driver = GfGameParty::getHandleDriver(party, static_cast<PTPOS>(0));
    GF_OBJ_HANDLE* partner;
    if (torna) {
        partner = GfGameParty::getHandleDriver(party, static_cast<PTPOS>(1));
    } else {
        partner = GfGameParty::getHandleBlade(party, -1);
    }
    unsigned int hp;
    {
        DataParamAcc acc(driver);
        hp = acc.getHp();
    }
    if (hp == 0 || !GfGameObj::isValidGameObj(driver, true, nullptr)) {
        return -1;
    }
#line 4649
    SCOM_FIELD_VOICE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(true);
    if (request == 0) {
        return -1;
    }
    request->add(ParamObj(driver), CV_FIELD(6), CV_PRIO(1));
    request->add(ParamObj(partner), CV_FIELD(6), CV_PRIO(3));
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_FIELD_VOICE::createLevelupForCamp(const ParamObj& obj) {
    unsigned long handle = createLevelup(obj);
    if (SCOM_FIELD_VOICE* request = static_cast<SCOM_FIELD_VOICE*>(findRequest(handle))) {
        request->m_stopOnEvent = false;
    }
    return handle;
}

unsigned long SCOM_FIELD_VOICE::createExitInn() {
    int party = fn_71005680B0();
    if (party == -1) {
        return -1;
    }
    bool torna = GfGameManager::isGameTypeIra();
    GF_OBJ_HANDLE* driver = GfGameParty::getHandleDriver(party, static_cast<PTPOS>(0));
    GF_OBJ_HANDLE* partner;
    if (torna) {
        partner = GfGameParty::getHandleDriver(party, static_cast<PTPOS>(1));
    } else {
        partner = GfGameParty::getHandleBlade(party, -1);
    }
    unsigned int hp;
    {
        DataParamAcc acc(driver);
        hp = acc.getHp();
    }
    if (hp == 0 || !GfGameObj::isValidGameObj(partner, true, nullptr)) {
        return -1;
    }
#line 4715
    SCOM_FIELD_VOICE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE();
    if (request == 0) {
        return -1;
    }
    request->add(ParamObj(partner), CV_FIELD(9), CV_PRIO(1));
    request->add(ParamObj(driver), CV_FIELD(9), CV_PRIO(1));
    request->m_flagD0 = true;
    return GfReqSmallCom::addRequestParallel(request);
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

unsigned int SCOM_FIELD_VOICE::fn_7100567A44() {
    mm::mtl::FixedVector<unsigned short, 32> drivers;
    for (unsigned int i = 0; i < 5; i++) {
        unsigned int driver = GfDataParty::getDriver(i, static_cast<PTPOS>(0));
        if (driver != 0) {
            drivers.push_back(driver);
        }
    }
    if (drivers.size() == 0) {
        return 0;
    }
    return drivers[ml::mtRand(drivers.size())];
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

unsigned long SCOM_FIELD_VOICE::createSkipTravel(bool start) {
    CV_FIELD field = start ? CV_FIELD(19) : CV_FIELD(20);
    int party = fn_71005680B0();
    if (party != -1) {
        bool torna = GfGameManager::isGameTypeIra();
        GF_OBJ_HANDLE* driver = GfGameParty::getHandleDriver(party, static_cast<PTPOS>(0));
        GF_OBJ_HANDLE* partner =
            torna ? GfGameParty::getHandleDriver(party, static_cast<PTPOS>(1)) : GfGameParty::getHandleBlade(party, -1);
#line 4858
        SCOM_FIELD_VOICE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(true);
        if (request != 0) {
            request->add(ParamObj(driver), field, CV_PRIO(1));
            request->add(ParamObj(partner), field, CV_PRIO(1));
            GfReqSmallCom::addRequestParallel(request);
        }
    }
    return -1;
}

unsigned long SCOM_FIELD_VOICE::createRestart(CV_FIELD field) {
    int party = fn_71005680B0();
    if (party == -1) {
        return -1;
    }
    bool torna = GfGameManager::isGameTypeIra();
    GF_OBJ_HANDLE* driver = GfGameParty::getHandleDriver(party, static_cast<PTPOS>(0));
    GF_OBJ_HANDLE* partner;
    if (torna) {
        partner = GfGameParty::getHandleDriver(party, static_cast<PTPOS>(1));
    } else {
        partner = GfGameParty::getHandleBlade(party, -1);
    }
    unsigned int hp;
    {
        DataParamAcc acc(driver);
        hp = acc.getHp();
    }
    if (hp == 0 || !GfGameObj::isValidGameObj(driver, true, nullptr)) {
        return -1;
    }
#line 4886
    SCOM_FIELD_VOICE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(true);
    if (request == 0) {
        return -1;
    }
    request->add(ParamObj(driver), field, CV_PRIO(1), 0.5f);
    request->add(ParamObj(partner), field, CV_PRIO(1), 0.5f);
    return GfReqSmallCom::addRequestParallel(request);
}

int SCOM_FIELD_VOICE::fn_71005680B0() {
    mm::mtl::FixedVector<unsigned short, 32> parties;
    for (unsigned int i = 0; i < 3; i++) {
        bool valid;
        if (GfGameManager::isGameTypeIra()) {
            valid = GfGameParty::getDriverBdatId(i, static_cast<PTPOS>(0)) != 0 &&
                    GfGameParty::getDriverBdatId(i, static_cast<PTPOS>(1)) != 0;
        } else {
            valid = GfGameObj::isValidGameObj(GfGameParty::getHandleDriver(i, static_cast<PTPOS>(0)), true, nullptr) &&
                    GfGameObj::isValidGameObj(GfGameParty::getHandleBlade(i, -1), true, nullptr);
        }
        if (valid) {
            parties.push_back(i);
        }
    }
    if (parties.size() == 0) {
        return -1;
    }
    return parties[ml::mtRand(parties.size())];
}

unsigned long SCOM_FIELD_VOICE::createAchievementAll(unsigned int id) {
    unsigned int driver = GfDataBlade::getSetDriver(id);
    if (driver == 0) {
        driver = GfDataBlade::getCreator(id);
    }
#line 4931
    SCOM_FIELD_VOICE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE();
    if (request == 0) {
        return -1;
    }
    request->add(ParamObj(4, id), CV_FIELD(27), CV_PRIO(1));
    if (driver != 0) {
        request->add(ParamObj(3, driver), CV_FIELD(27), CV_PRIO(1));
    }
    return GfReqSmallCom::addRequestParallel(request);
}

GAME_VOICE_HANDLE* SCOM_FIELD_VOICE::createEngage(unsigned int id) {
    return GfFieldVoice::playVoice(ParamObj(4, id), CV_FIELD(36), 0, 0, CV_PRIO(1));
}

unsigned long SCOM_FIELD_VOICE::createTime(CV_FIELD field) {
    if (GfGameManager::isBattle()) {
        return -1;
    }
    int party = fn_71005680B0();
    if (party == -1) {
        return -1;
    }
    bool torna = GfGameManager::isGameTypeIra();
    GF_OBJ_HANDLE* driver = GfGameParty::getHandleDriver(party, static_cast<PTPOS>(0));
    GF_OBJ_HANDLE* partner;
    if (torna) {
        partner = GfGameParty::getHandleDriver(party, static_cast<PTPOS>(1));
    } else {
        partner = GfGameParty::getHandleBlade(party, -1);
    }
    unsigned int hp;
    {
        DataParamAcc acc(driver);
        hp = acc.getHp();
    }
    if (hp == 0 || !GfGameObj::isValidGameObj(driver, true, nullptr)) {
        return -1;
    }
#line 5142
    SCOM_FIELD_VOICE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_FIELD_VOICE(true);
    if (request == 0) {
        return -1;
    }
    request->add(ParamObj(driver), field, CV_PRIO(1));
    request->add(ParamObj(partner), field, CV_PRIO(1));
    return GfReqSmallCom::addRequestParallel(request);
}

GAME_VOICE_HANDLE* SCOM_FIELD_VOICE::createFieldSkillStart(unsigned int blade, unsigned int skill) {
    const char* name = GfDataBlade::getFieldSkillVoice(blade, skill);
    if (name == nullptr) {
        return nullptr;
    }
    return GfGameVoice::playVoice(ParamObj(4, blade), name, CV_PRIO(1), false);
}

GAME_VOICE_HANDLE* SCOM_FIELD_VOICE::createFieldSkillClear(unsigned int skill) {
    if (GfGameManager::isGameTypeIra()) {
        VoiceList names;
        names.push_back("750101");
        names.push_back("750102");
        names.push_back("750103");
        return createInPartyForIra(names);
    }
    QuestListAcc* quests = QuestListAcc::get();
    DataParamAcc leader(GfGameManager::getPartyLeaderDriver());
    unsigned int category = quests->getFLD_FieldSkillSettingSuccessVoiceCategory(skill);
    const char* name = GfDataField::getFieldSkillVoice(
        leader.isValid() && leader.getObjType() == 3 ? leader.getBdatId() : 0, category);
    if (name == nullptr) {
        return nullptr;
    }
    return GfGameVoice::playVoice(GfGameManager::getPartyLeaderDriver(), name, CV_PRIO(1));
}

GAME_VOICE_HANDLE* SCOM_FIELD_VOICE::createFieldSkillMiss(unsigned int skill) {
    if (GfGameManager::isGameTypeIra()) {
        VoiceList names;
        names.push_back("760101");
        names.push_back("760102");
        return createInPartyForIra(names);
    }
    QuestListAcc* quests = QuestListAcc::get();
    DataParamAcc leader(GfGameManager::getPartyLeaderDriver());
    unsigned int category = quests->getFLD_FieldSkillSettingMissVoiceCategory(skill);
    const char* name = GfDataField::getFieldSkillVoice(
        leader.isValid() && leader.getObjType() == 3 ? leader.getBdatId() : 0, category);
    if (name == nullptr) {
        return nullptr;
    }
    return GfGameVoice::playVoice(GfGameManager::getPartyLeaderDriver(), name, CV_PRIO(1));
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B6AB50). The blade names (bdat ids
// 0x11..0x19) a voice name is appended to. The original reaches it directly (file-local) yet keeps FixStr's
// "pszName != 0" check on the entry it reads, so the compiler did not fold it to its initial values: `used`
// reproduces that (as the GlobalMerge statics elsewhere).
__attribute__((used)) static const char* s_bladeVoiceIds[9] = {"701", "702", "703", "704", "705", "706", "707", "708", "709"};

// the blade id of a blade object, 0 for anything else (the original computes it at each use)
static inline unsigned int getBladeBdatId(const DataParamAcc& acc) {
    return acc.isValid() && acc.getObjType() == 3 ? acc.getBdatId() : 0;
}

GAME_VOICE_HANDLE* SCOM_FIELD_VOICE::createInPartyForIra(const VoiceList& names) {
    if (!GfGameManager::isGameTypeIra()) {
        return nullptr;
    }
    mm::mtl::FixedVector<GF_OBJ_HANDLE*, 9> handles;
    if (!getIraMember(handles)) {
        return nullptr;
    }
    DataParamAcc blade(handles[ml::mtRand(handles.size())]);
    if (getBladeBdatId(blade) < 0x11 || getBladeBdatId(blade) > 0x19) {
        return nullptr;
    }
    mm::mtl::FixStr<32> name(s_bladeVoiceIds[getBladeBdatId(blade) - 0x11]);
    name += names[ml::mtRand(names.size())];
    return GfGameVoice::playVoiceParty(blade.m_handle, name.m_str, CV_PRIO(3));
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B6AAC0)
static const char* const s_driverKizunaVoices[6][3] = {
    {"01200201", "01420601", "01980201"}, {"02490101", "02750101", "02410602"},
    {"06470101", "06470104", "06910103"}, {"03980201", "03490202", "03870101"},
    {"04490101", "04980201", "04320102"}, {"05490101", "05980201", "05980101"},
};

GAME_VOICE_HANDLE* SCOM_FIELD_VOICE::createDriverKizuna(unsigned int id) {
    if (id - 1 > 5) {
        return nullptr;
    }
    return GfGameVoice::playVoice(3, id, s_driverKizunaVoices[id - 1][ml::mtRand(3)], CV_PRIO(3));
}

void SCOM_FIELD_VOICE::createQuestOrderIra() {
    VoiceList names;
    names.push_back("670101");
    names.push_back("670102");
    createInPartyForIra(names);
}

void SCOM_FIELD_VOICE::createQuestCompleteIra() {
    VoiceList names;
    names.push_back("670103");
    names.push_back("670104");
    createInPartyForIra(names);
}

void SCOM_FIELD_VOICE::createHitonowaGet() {
    SCOM_FIELD_VOICE::VoiceList names;
    names.push_back("670105");
    names.push_back("670106");
    SCOM_FIELD_VOICE::createInPartyForIra(names);
}

GAME_VOICE_HANDLE* SCOM_FIELD_VOICE::createDriverForIra(unsigned int blade, const VoiceList& names) {
    if (!GfGameManager::isGameTypeIra() || blade - 0x11 > 8) {
        return nullptr;
    }
    mm::mtl::FixStr<32> name(s_bladeVoiceIds[blade - 0x11]);
    name += names[ml::mtRand(names.size())];
    return GfGameVoice::playVoiceParty(3, blade, name.m_str, CV_PRIO(3));
}

GAME_VOICE_HANDLE* SCOM_FIELD_VOICE::createCraftSelect(unsigned int blade) {
    SCOM_FIELD_VOICE::VoiceList names;
    names.push_back("680101");
    names.push_back("680102");
    return createDriverForIra(blade, names);
}

GAME_VOICE_HANDLE* SCOM_FIELD_VOICE::createPouchAutoAdd(unsigned int item, unsigned int blade) {
    if (GfDataItem::getItemType(item) == 10) {
        unsigned int category = GfBdatItem::sys()->getFavoriteCategory(item);
        SCOM_FIELD_VOICE::VoiceList names;
        if (GfDataItem::isFavoriteCategoryFood(category)) {
            names.push_back("690101");
        } else {
            names.push_back("690102");
        }
        return createDriverForIra(blade, names);
    }
    return nullptr;
}

GAME_VOICE_HANDLE* SCOM_FIELD_VOICE::createPouchAutoAddFailed(unsigned int item, unsigned int blade) {
    if (GfDataItem::getItemType(item) == 10) {
        unsigned int category = GfBdatItem::sys()->getFavoriteCategory(item);
        SCOM_FIELD_VOICE::VoiceList names;
        if (GfDataItem::isFavoriteCategoryFood(category)) {
            names.push_back("690103");
        } else {
            names.push_back("690104");
        }
        return createDriverForIra(blade, names);
    }
    return nullptr;
}

void SCOM_FIELD_VOICE::createArtsSetIra(unsigned int blade) {
    SCOM_FIELD_VOICE::VoiceList names;
    names.push_back("700101");
    names.push_back("700102");
    names.push_back("700103");
    createDriverForIra(blade, names);
}

void SCOM_FIELD_VOICE::createSkillGetIra(unsigned int blade) {
    SCOM_FIELD_VOICE::VoiceList names;
    names.push_back("710101");
    names.push_back("710102");
    names.push_back("710103");
    createDriverForIra(blade, names);
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
    GfGameUtil::addSpForObject(driver, m_value);
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

unsigned long SCOM_ADD_WP::createForBdatid(int driver, int a1, unsigned int a2) {
    if (!a1) {
        return -1;
    }
#line 382
    SCOM_ADD_WP* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_ADD_WP(SCOM_TYPE(7));
    request->m_driver = driver;
    request->m_value = a1;
    request->m_value2 = a2;
    request->m_mode = 3;
    return GfReqSmallCom::addRequestParallel(request);
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

void SCOM_ACHIEV_INC::createKillEnemy(GF_OBJ_HANDLE* handle) {
    addTotalCount(0x63, 1);
    create(0x63, 1, 0);
    mm::mtl::FixedVector<unsigned short, 422> blades;
    fn_7100563BB4(blades, handle, true);
    if (!blades.empty()) {
        unsigned short* it = blades.begin();
        unsigned short* end = blades.end();
        do {
            create(0x64, 1, *it);
        } while (++it != end);
    }
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

unsigned long SCOM_CURRENT_BLADE::create(unsigned int blade) {
    SCOM_PARTY_ADD::setCurrentBlade(blade);
#line 6017
    SCOM_CURRENT_BLADE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_CURRENT_BLADE(SCOM_TYPE(78));
    request->m_value = blade;
    return GfReqSmallCom::addRequest(request);
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
        if (GfDataBlade::isDummyBlade(blade) || GfDataBlade::isActivateMercenaryTeam(blade)) {
            continue;
        }
        if (GfDataBlade::getSetDriver(blade) == 0 || GfDataBlade::isReleasedRareBlade(blade)) {
            continue;
        }
        GfDataBlade::setUnselect(blade, m_value);
    }
    return true;
}

bool SCOM_BATTLE_ARENA::exec(fw::UpdateInfo const&) {
    if (GfGameArena* arena = mm::mtl::PtrSingleton<GfGameArena>::sys()) {
        unsigned int value = m_param;
        MsgGameBtlArena msg(m_type);
        msg.m_start.m_id = value;
        static_cast<fw::MessageObject*>(arena)->recieveMessage(arena, msg);
    }
    return true;
}

unsigned long SCOM_BATTLE_ARENA::createWin() {
#line 6217
    SCOM_BATTLE_ARENA* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_BATTLE_ARENA(0x4);
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_BATTLE_ARENA::createLose() {
#line 6225
    SCOM_BATTLE_ARENA* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_BATTLE_ARENA(0x3);
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_BATTLE_ARENA::createRetry() {
#line 6233
    SCOM_BATTLE_ARENA* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_BATTLE_ARENA(0x6);
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_BATTLE_ARENA::createGiveUp() {
#line 6241
    SCOM_BATTLE_ARENA* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_BATTLE_ARENA(0x5);
    return GfReqSmallCom::addRequestParallel(request);
}

unsigned long SCOM_BATTLE_ARENA::createLoseStart() {
#line 6249
    SCOM_BATTLE_ARENA* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_BATTLE_ARENA(0x14);
    return GfReqSmallCom::addRequestParallel(request);
}

void SCOM_BATTLE_ARENA::createPlayJingle(unsigned int id, float a, float b) {
    if (GfGameArena* arena = mm::mtl::PtrSingleton<GfGameArena>::sys()) {
        MsgGameBtlArena msg(0x12);
        msg.pad_34 = a;
        msg.pad_38 = b;
        msg.pad_3C = id;
        static_cast<fw::MessageObject*>(arena)->recieveMessage(arena, msg);
    }
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B6AD58)
static const char* const s_scoreVoices[4][4] = {
    {"650490101", "650490101", "650490102", "650490102"},
    {"650490109", "650490110", "650490103", "650490104"},
    {"650490109", "650490110", "650490105", "650490106"},
    {"650490109", "650490110", "650490107", "650490108"},
};

void SCOM_BATTLE_ARENA::createAfterVoice(unsigned int row) {
    unsigned int index = ml::mtRand(4);
    GfGameVoice::playVoice(6, 0xDC3, s_scoreVoices[row][index], CV_PRIO(3));
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

unsigned long SCOM_FADE::createEvent(unsigned int slot, unsigned int frames, const mm::Col4& color) {
    if (frames == 0 && color.a == 0.0f && GfGameEvent::getPlayEventId() == 10657) {
        return -1;
    }
    return create(slot, frames, color);
}

mm::mtl::FixedQueue<SCOM_PARTY_ADD::Info, 16> SCOM_PARTY_ADD::s_info;
// 2.0.0's symbols name it
unsigned int SCOM_PARTY_ADD::s_iraParty;

void SCOM_PARTY_ADD::addBlade(unsigned int blade, unsigned int driver, int param) {
    if (blade == 0) {
        return;
    }
    if (GfGameManager::isClearGame() && (blade - 1001 < 3 || GfDataBlade::isActivateMercenaryTeam(blade))) {
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
    SCOM_PARTY_ADD* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        SCOM_PARTY_ADD(reinterpret_cast<GF_SCOM_HANDLE*>(GfReqSmallCom::sys()->newHandle()));
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

void SCOM_PARTY_ADD::removeBlade(unsigned int blade, bool flag, bool checkClear) {
    if (blade == 0) {
        return;
    }
    if (GfGameManager::isClearGame() && checkClear && (blade - 1001 < 3 || GfDataBlade::isActivateMercenaryTeam(blade))) {
        return;
    }
    Info info = {GfDataBlade::getActBlade2CommonBlade(blade), 0, -1, flag, false, false, true, 2};
    s_info.push_front(info);
    create();
}

void SCOM_PARTY_ADD::addDriver(unsigned int driver, unsigned int param) {
    Info info = {0, driver, static_cast<int>(param), true, false, false, driver != 4, 3};
    s_info.push_back(info);
    if (driver == 2) {
        removeBlade(1011, false);
    }
    create();
}

void SCOM_PARTY_ADD::setToraBladeFollow() {
    for (mm::mtl::FixedQueue<Info, 16>::iterator it = s_info.begin(); it != s_info.end(); ++it) {
        if ((*it).m_kind == 3 && (*it).m_driver == 4) {
            (*it).m_isEnable = true;
            return;
        }
    }
}

void SCOM_PARTY_ADD::setIraParty(unsigned int party) {
    if (GfManager::isExecModeScenarioGame() && GfGameManager::isClearGame()) {
        return;
    }
    s_iraParty = party;
    create();
}

unsigned long SCOM_SET_BLADE::create(const RQ_SETUP_BLADE& info) {
    if (info.m_driver == 0) {
        return -1;
    }
    RQ_SETUP_BLADE setup = info;
    if (GfGameManager::isClearGame()) {
        bool pyra = setup.m_blades[0] == 1001 || setup.m_blades[1] == 1001 || setup.m_blades[2] == 1001 ||
                    setup.m_blades[3] == 1001 || setup.m_blades[4] == 1001;
        setup.m_blades[3] = pyra ? 1002 : 0;
        setup.m_blades[4] = pyra ? 1003 : 0;
    }
#line 3114
    SCOM_SET_BLADE* request = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SCOM_SET_BLADE(SCOM_TYPE(81), setup);
    return GfReqSmallCom::addRequest(request);
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

GfReqSmallCom::GfReqSmallCom() {
    m_handleCount = 0;
    m_isSubParallel = false;
    SCOM_PARTY_ADD::s_info.clear();
    SCOM_PARTY_ADD::s_iraParty = 0;
}

GfReqSmallCom::~GfReqSmallCom() {}

bool GfReqSmallCom::isValid(GF_SCOM_HANDLE* handle) {
    if (handle == reinterpret_cast<GF_SCOM_HANDLE*>(-1)) {
        return false;
    }
    for (RequestList::iterator it = m_list.begin(); it != m_list.end(); ++it) {
        if (reinterpret_cast<GF_SCOM_HANDLE*>((*it)->m_handle) == handle) {
            return true;
        }
    }
    for (RequestList::iterator it = m_parallelList.begin(); it != m_parallelList.end(); ++it) {
        if (reinterpret_cast<GF_SCOM_HANDLE*>((*it)->m_handle) == handle) {
            return true;
        }
    }
    return false;
}

bool GfReqSmallCom::isExistCommand(SCOM_TYPE type) {
    RequestList& list = sys()->m_list;
    for (RequestList::iterator it = list.begin(); it != list.end(); ++it) {
        if ((*it)->m_type == type) {
            return true;
        }
    }
    return false;
}

void GfReqSmallCom::update(const fw::UpdateInfo& info) {
    m_isSubParallel = true;
    RequestList::iterator it = m_list.begin();
    for (it = m_list.begin(); it != m_list.end(); ++it) {
        if ((*it)->m_state == 0) {
            goto found;
        }
    }
    for (it = m_list.begin(); it != m_list.end(); ++it) {
        if ((*it)->m_state == 1) {
            goto found;
        }
    }
    for (it = m_list.begin(); it != m_list.end(); ++it) {
        if ((*it)->m_state == 2) {
            goto found;
        }
    }
    goto parallel;
found:
    {
        SCOM*& request = *it;
        if (request->exec(info)) {
            if (request) {
                delete request;
                request = 0;
            }
            m_list.erase(it);
        }
    }
parallel:
    updateParallel(info);
    for (RequestList::iterator sub = m_subParallelList.begin(); sub != m_subParallelList.end(); ++sub) {
        m_parallelList.push_back(*sub);
    }
    m_subParallelList.clear();
    m_isSubParallel = false;
}

bool GfReqSmallCom::updateParallel(const fw::UpdateInfo& info) {
    RequestList::iterator it = m_parallelList.begin();
    while (it != m_parallelList.end()) {
        SCOM* request = *it;
        bool wait = false;
        if (request->getObjHandle() != static_cast<unsigned long>(-1)) {
            for (RequestList::iterator other = m_parallelList.begin(); other != m_parallelList.end(); ++other) {
                SCOM* before = *other;
                if (before == request) {
                    break;
                }
                if (before->m_type == request->m_type && before->getObjHandle() == request->getObjHandle()) {
                    wait = true;
                    break;
                }
            }
        }
        if (!wait) {
            SCOM*& done = *it;
            if (done->exec(info)) {
                if (done) {
                    delete done;
                    done = 0;
                }
                it = m_parallelList.erase(it);
                continue;
            }
        }
        ++it;
    }
    return true;
}
}  // namespace gf

template mm::mtl::PtrSingleton<gf::SCOM_PARTY_ADD>::~PtrSingleton();

namespace gf {

}  // namespace gf
