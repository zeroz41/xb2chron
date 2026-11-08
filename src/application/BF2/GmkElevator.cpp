#include <algorithm>
#include "classes/gmk/GmkBdat.h"
#include "classes/gmk/GmkPhantomManager.h"
#include "classes/gmk/GmkLandmarkManager.h"
#include "classes/gmk/GmkBgmCondInfoManager.h"
#include "classes/gf/GfMenuObjLocationTelop.h"
#include "classes/gmk/GmkSquadManager.h"
#include "classes/gmk/TGmkActiveList.h"
#include "classes/gmk/GmkManager.h"
#include "classes/gmk/GmkInstDispTraverserByBdatId.h"
#include "classes/fw/SoundManager.h"
#include "classes/gf/GfFieldBgm.h"
#include "classes/gf/GfComCollider.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjSetupGimmick.h"
#include "classes/fw/EffectManager.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkGrave.h"
#include "classes/gmk/GmkBlade.h"
#include "classes/gmk/GmkKizunaTalk.h"
#include "classes/gmk/GmkTbox.h"
#include "classes/gmk/GmkAreaWeather.h"
#include "classes/gmk/GmkBattleLock.h"
#include "classes/gmk/GmkClimbing.h"
#include "classes/gmk/GmkDmgGimmick.h"
#include "classes/gmk/GmkDoor.h"
#include "classes/gmk/GmkEffectLocator.h"
#include "classes/gmk/GmkElevatorLocator.h"
#include "classes/gmk/GmkEvent.h"
#include "classes/gmk/GmkFieldLock.h"
#include "classes/gmk/GmkFieldVolume.h"
#include "classes/gmk/GmkLandmark.h"
#include "classes/gmk/GmkMapJump.h"
#include "classes/gmk/GmkMapObj.h"
#include "classes/gmk/GmkNpc.h"
#include "classes/gmk/GmkPrecious.h"
#include "classes/gmk/GmkRoutedFootPrint.h"
#include "classes/gmk/GmkRoutedMapObj.h"
#include "classes/gmk/GmkRoutedMob.h"
#include "classes/gmk/GmkRoutedNpc.h"
#include "classes/gmk/GmkRouteNavi.h"
#include "ml/MtRand.h"
#include "classes/gmk/GmkSe.h"
#include "classes/gmk/GmkSeLine.h"
#include "classes/gmk/GmkSeLinePoint.h"
#include "classes/gmk/GmkSquadLeader.h"
#include "classes/gmk/GmkSquadMember.h"
#include "classes/gmk/GmkSquad.h"
#include "classes/gmk/GmkTargetPoint.h"
#include "classes/gmk/GmkJump.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuObjFieldIcon.h"
#include "gf/GfDataEnemy.h"
#include "gf/GfItemUtil.h"
#include "classes/gmk/GmkTutorial.h"
#include "classes/gmk/GmkBattleChallengeReward.h"
#include "classes/gmk/GmkBattleChallengePortal.h"
#include "classes/gmk/GmkCamp.h"
#include "classes/gmk/GmkSealedStone.h"
#include "classes/gmk/GmkNpcList.h"
#include "classes/gmk/GmkRoutedEnemyList.h"
#include "classes/gmk/GmkRoutedNpcList.h"
#include "classes/gmk/GmkSalvageList.h"
#include "classes/gmk/GmkSealedStoneList.h"
#include "classes/gmk/GmkBattleChallengeRewardList.h"
#include "classes/gmk/GmkBdat.h"
#include "classes/gmk/GmkLandmarkManager.h"
#include "classes/gmk/GmkSquadManager.h"
#include "classes/gmk/GmkBattleChallengePortalList.h"
#include "classes/gf/GfGameManager.h"
#include "fw/NaviUtil.h"
#include "classes/gf/GfFieldTime.h"
#include "classes/gf/GfFieldWeather.h"
#include "classes/gf/GfGameFlag.h"
#include "gf/GfDataBlade.h"
#include "gf/GfQuestInfo.h"
#include "gf/GfObjAcc.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gmk/GmkPhantom.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfComBehaviorEnemy.h"
#include "classes/gf/GfComBehaviorNpc.h"
#include "classes/gf/GfComModel.h"
#include "gf/GfObjUtil.h"
#include "classes/gmk/GmkEnemy.h"
#include "classes/gmk/GmkRoutedEnemy.h"
#include "classes/gmk/GmkSalvage.h"
#include "classes/gmk/GmkMob/PopXformFinder.h"
#include "classes/gmk/GmkRoutedMob/PopXformFinder.h"
#include "fw/ColiCheck.h"
#include "classes/gmk/GameFlagCond.h"
#include "classes/gmk/PopPosSafeCond.h"
#include "classes/gf/GfManager.h"
#include "arc/CArcData.h"
#include "classes/fw/CommonResource.h"
#include "classes/fw/SoundResSourceManager.h"
#include "classes/gf/GfAllocator.h"
#include "gf/GfSoundSource.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfObjSetupNpc.h"
#include "gf/GfStaticRes.h"
#include "gf/GfUtil.h"
#include "ml/mlUTF.h"
#include "ml/PathUtil.h"
#include "classes/gmk/IGmkList.h"
#include "classes/gmk/GmkGobEventListener.h"
#include "classes/gmk/GmkSalvageLocator.h"
#include "classes/gmk/TGmkList.h"
#include "classes/gmk/GmkNpcManager.h"
#include "classes/gmk/GmkSet.h"
#include "classes/gmk/GmkSetOfSalvageChildren.h"
#include "classes/gmk/GmkManager.h"
#include "classes/gmk/GmkForm.h"
#include "classes/gmk/TGmkFormPc.h"
#include "classes/gmk/TGmkFormPcnpc.h"
#include "classes/gmk/TGmkFormPcList.h"
#include "classes/gmk/TGmkFormPcnpcList.h"
#include "classes/gmk/GmkEnemyList.h"
#include "classes/fw/FrameworkMemory.h"
#include "mtl/MemManager.h"
#include "plugin/Bdat.h"
#include "classes/gmk/IGmkList.h"
#include "classes/gmk/GmkAcc.h"
#include "classes/gmk/GmkAccManager.h"
#include "classes/gmk/GmkCamera.h"
#include "classes/gmk/GmkGobEventListener.h"
#include "classes/gmk/TGmkList.h"
#include "classes/gmk/GmkMob.h"
#include "classes/gmk/GmkRoutePoint.h"
#include "classes/gmk/GmkRoutedEnemyPoint.h"
#include "classes/gmk/GmkDmgPhantom.h"
#include "classes/gmk/GmkDmgEffect.h"
#include "classes/gmk/GmkDmgSe.h"
#include "classes/gmk/GmkRoutedFootPrintPoint.h"
#include "classes/gmk/GmkSalvageLocator.h"
#include "classes/gmk/GmkCollection.h"
#include "classes/gmk/GmkTutorial.h"
#include "classes/gmk/GmkMapGimmick.h"
#include "classes/gmk/GmkTrigger.h"
#include "classes/gmk/GmkMapGimmickList.h"
#include "classes/gmk/GmkRoutePointList.h"
#include "classes/gmk/GmkRoutedEnemyPointList.h"
#include "classes/gmk/GmkMobList.h"
#include "classes/gmk/GmkDmgPhantomList.h"
#include "classes/gmk/GmkDmgEffectList.h"
#include "classes/gmk/GmkDmgSeList.h"
#include "classes/gmk/GmkRoutedFootPrintPointList.h"
#include "classes/gmk/GmkSalvageLocatorList.h"
#include "classes/gmk/GmkCollectionList.h"
#include "classes/gf/GfComBehaviorGmk.h"
#include "classes/gmk/GmkTutorialList.h"
#include "classes/gmk/GmkMapGimmickList.h"
#include "classes/gmk/GmkAntiBladeArea.h"
#include "classes/gmk/GmkAreaBgm.h"
#include "classes/gmk/GmkEffect.h"
#include "classes/gmk/GmkElevator.h"
#include "classes/gmk/GmkJump.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/GfItemUtil.h"
#include "classes/gmk/GmkTutorial.h"
#include "classes/gmk/GmkMapGimmick.h"
#include "classes/gmk/GmkRoute.h"
#include "classes/gmk/GmkRoutePoint.h"
#include "classes/gmk/GmkTrigger.h"
#include "classes/gmk/GmkWarp.h"
#include "btl/Utility.h"
#include "mm/Mat44.h"
#include "classes/gmk/Lvlb.h"
#include "classes/gf/GfFieldLod.h"
#include "classes/gf/GfFieldGimmick.h"
#include "classes/gf/MenuCommonWindowParam.h"
#include "gf/GfPlayFactory.h"
#include "classes/fw/CameraManager.h"
#include "classes/gf/SCOM_DESTROY_GAME_OBJ.h"
#include "classes/gf/SCOM_QUEST_GIMMICK.h"
#include "classes/gf/SCOM_QUEST_REACH.h"
#include "classes/gf/GfFieldSound.h"
#include "gf/GfQuestUtil.h"
#include "ml/ScnObjAccSeamPos.h"
#include "ml/ScnObjAccPartsPos.h"
#include "classes/gf/GfFieldManager.h"
#include "classes/fw/BdatManager.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/SDataEnemy.h"
#include "classes/gmk/GmkDoorPhantomManager.h"
#include "classes/gmk/GmkDmgPhantomManager.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfGamePlayerFormation.h"
#include "classes/gf/GfBdatChrEnArrange.h"
#include "gf/GfObjFactory.h"
#include "classes/gf/GfComTransform.h"
#include "classes/ml/Scn.h"
#include "classes/ml/ScnObjCam.h"
#include "classes/gmk/DistCond.h"
#include "effect/SendParam.h"
#include "classes/gmk/GmkSquadNavi.h"
#include "fw/FwDebug.h"
#include "mm/mtl/Vector.h"
#include "gf/GfDataUtil.h"
#include "classes/gmk/GmkRoutedEnemy/PopXformFinder.h"
#include "classes/gmk/GmkEnemy/PopXformFinder.h"
#include "classes/gf/GfQuestTarget.h"
#include "classes/gf/GfMenuCallContext.h"
#include "gf/GfMenuBdat.h"
#include "gf/MenuOffset.h"
#include "classes/gf/SCOM_ADD_ITEM.h"
#include "classes/fw/ParamManager.h"
#include "classes/fw/ParamList.h"
#include "gf/ItemGetParam.h"

namespace gf {
// the resident sound sources' files, by index (getSoundSourceFileName reads it; bindGFSoundSource loads each)
extern const char* const SS_NAME_TABLE[3];
const char* const SS_NAME_TABLE[3] = {
    "/sound/tag/source/field.ssp",
    "/sound/tag/source/battle.ssp",
    "/sound/tag/source/event.ssp",
};

unsigned int getSoundSourceCount() { return 3; }

const char* getSoundSourceFileName(unsigned int index) { return SS_NAME_TABLE[index]; }

// pushes every sound source of the resident files into fw::SoundResSourceManager
void bindGFSoundSource() {
    if (fw::SoundResSourceManager::sys() == nullptr) {
        return;
    }
    fw::SoundResSourceManager::beginPush(getSoundSourceCount(), getAllocator(ALLOCATOR(0)));
    for (unsigned int i = 0; i < getSoundSourceCount(); i++) {
        fw::CommonResource* res = GfStaticRes::search(getSoundSourceFileName(i));
        if (res != nullptr) {
            arc::CArcData arc(res->getAssetData());
            unsigned int files = arc.getFiles();
            for (unsigned int j = 0; j < files; j++) {
                fw::SoundResSourceManager::pushResource(fw::SoundResSourceImporter::importBinary(arc.getFileAdr(j)));
            }
        }
    }
    fw::SoundResSourceManager::endPush();
}

void unrbindGFSoundSource() {
    if (fw::SoundResSourceManager::sys() != nullptr) {
        fw::SoundResSourceManager::clearAll();
    }
}

namespace util {
// a debug text in Shift-JIS: str (UTF-8) converted through UTF-16, each '%' replaced with "per " (the result is one
// of eight buffers used in turn)
const char* debugUTF8ToSJIS(const char* str) {
    // Proposed names, not the original's: the symbols leave them unnamed (lbl_7100EB6D18, lbl_7100EB6D1C)
    __attribute__((used)) static unsigned int s_bufferIndex;
    __attribute__((used)) static char s_buffers[8][0x200];
    if (str == nullptr) {
        str = "";
    }
    if (s_bufferIndex >= 8) {
        s_bufferIndex = 0;
    }
    unsigned short utf16[0x200];
    mlUTF8toUTF16(utf16, 0x200, str);
    if (!mlUTF16toSJIS(s_buffers[s_bufferIndex], 0x200, utf16)) {
        s_buffers[s_bufferIndex][0] = '\0';
    }
    mm::mtl::FixStr<256> text(s_buffers[s_bufferIndex]);
    while (text.m_nLen > 0) {
        int pos = text.find('%');
        if (pos == -1) {
            break;
        }
        if (text.m_nLen > pos) {
            int end = pos + 1 < text.m_nLen ? pos + 1 : text.m_nLen;
            strcpy(text.m_str + pos, text.m_str + end);
            text.m_nLen = strlen(text.m_str);
        }
        text.insert(pos, "per ", 4);
    }
    char* out = s_buffers[s_bufferIndex];
    memcpy(out, text.m_str, text.m_nLen);
    out[text.m_nLen] = '\0';
    ++s_bufferIndex;
    return out;
}

const char* getFilePtrFromPath(const char* path) { return ml::PathUtil::getFilePtrFromPath(path); }

mm::mtl::FixStr<64> getNoPathExtName(const char* path) { return ml::PathUtil::getNoPathExtName(path); }
}  // namespace util
}  // namespace gf

// the gimmick kinds' names, by GmkType: the gimmick-set table's column of each (GmkSet::createGmkLists reads
// "<name>" and "<name>_bdat"; GmkManager::getSheetnameByType returns them; the name is not the original's)
static const char* s_gmkKindNames[gmk::GmkSet::GMK_LIST_NUM] = {
    "enemy",
    "enemy",
    "enemy",
    "npc",
    "npc",
    "npc",
    "mapObj",
    "mapObj",
    "mapObj",
    "tbox",
    "event",
    "enemy",
    "fieldLock",
    "effect",
    "effect",
    "se",
    "se",
    "se",
    "mob",
    "mob",
    "mob",
    "landmark",
    nullptr,
    nullptr,
    "formPc",
    "formPc",
    "formPcEv",
    "formPcEv",
    "collection",
    "areaBgm",
    "areaWeather",
    "salvage",
    nullptr,
    "mapGimmick",
    "precious",
    "grave",
    "kizunaTalk",
    "jump",
    "warp",
    "squad",
    "squad",
    "door",
    "elevator",
    "elevator",
    "mapJump",
    "fieldVolume",
    "climbing",
    "blade",
    "dmgGimmick",
    "dmgGimmick",
    "dmgGimmick",
    "dmgGimmick",
    nullptr,
    "enemy",
    "footPrint",
    "footPrint",
    "antiBladeArea",
    "tutorial",
    "enemyWave",
    "battleChallenge",
    "mapObj",
    "npc",
    "campPop",
    "sealedStone",
};

// one kind's entry of the names table; its users pass the table in, which keeps it writable (.data, reached
// without the GOT) as the original's is (the name is not the original's)
static inline const char* getGmkKindName(const char** names, unsigned int type) {
    return names[type];
}

namespace gmk {

// ---- GmkEnemyWaveExtension's pop settings reader
void GmkEnemyWaveExtension::getWavePopInfo(const GmkEnemy* enemy, WavePopInfo& info) const {
    if (gf::GfGameManager::isInstalledBattleArenaContents() || gf::GfGameManager::isGameTypeIra()) {
        unsigned char* fp = enemy->m_list->getBindedBdatFp();
        int row = enemy->m_createInfo.m_bdatId;
        info.m_partyFlag = Bdat::getValCheck(fp, "party_flag", row, 1);
        info.m_popPriority = Bdat::getValCheck(fp, "Wpop_Priority", row, 1);
        info.m_popTimerCond = Bdat::getValCheck(fp, "Wpop_TimerCond", row, 2);
        info.m_popNumCond = Bdat::getValCheck(fp, "Wpop_PopNumCond", row, 1);
        info.m_battleLockName = static_cast<short>(Bdat::getValCheck(fp, "battlelockname", row, 2)) - 1;
    }
}

// the enemy wave gimmick (in the enemy's list's wave list) that binds enemy, none outside the battle arena and Ira
GmkEnemyWave* GmkEnemyWaveExtension::getBindedGmkEnemyWave(const GmkEnemy* enemy) const {
    if (gf::GfGameManager::isInstalledBattleArenaContents() || gf::GfGameManager::isGameTypeIra()) {
        IGmkList* list = enemy->m_list;
        bool enabled = gf::GfGameManager::isInstalledBattleArenaContents() || gf::GfGameManager::isGameTypeIra();
        if (list == nullptr || !enabled) {
            return nullptr;
        }
        if (list->getGmkType() == GmkEnemy::TYPE) {
            IGmkList* waves = &static_cast<GmkEnemyList*>(list)->m_waveExt.m_waveList;
            for (unsigned int i = 0; i < waves->getInstNum(); i++) {
                GmkEnemyWave* wave = static_cast<GmkEnemyWave*>(waves->getInst(i));
                if (wave != nullptr) {
                    unsigned int num = wave->getBindedEnemyNum();
                    for (unsigned int j = 0; j < num; j++) {
                        if (wave->getBindedEnemy(j) == enemy) {
                            return wave;
                        }
                    }
                }
            }
        }
    }
    return nullptr;
}

// on Ira, the progress of the wave binding the object's enemy is updated at the object's position
void GmkEnemyWaveExtension::createSealedEnergyEffect(gf::GF_OBJ_HANDLE* handle) const {
    bool ira = gf::GfGameManager::isGameTypeIra();
    if (handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) || !ira) {
        return;
    }
    AGmkBase* gmk = getBindedGmkInst(handle);
    if (gmk == nullptr || gmk->getGmkType() != GmkEnemy::TYPE) {
        return;
    }
    GmkEnemyWave* wave = getBindedGmkEnemyWave(static_cast<GmkEnemy*>(gmk));
    if (wave == nullptr) {
        return;
    }
    gf::GfObjAcc acc(handle);
    gf::GfObj* obj = acc.getObj();
    if (obj == nullptr) {
        return;
    }
    gf::GfComBehaviorEnemy* behavior = obj->getComponent<gf::GfComBehaviorEnemy>(6);
    if (behavior == nullptr) {
        return;
    }
    wave->updateProgress(behavior->getTransform().position);
}

void GmkEnemyWaveExtension::backHome(const GmkEnemy* enemy) {
    if (gf::GfGameManager::isInstalledBattleArenaContents() || gf::GfGameManager::isGameTypeIra()) {
        unsigned int num = enemy->getGobInstNum();
        for (unsigned int i = 0; i < num; i++) {
            btl::Utility::AI_StartActionEscape(enemy->getGobInst(i));
        }
    }
}

void GmkEnemyListWaveExtension::createPopEffect(const mm::Vec3& pos) const {
    if (m_popEffect == nullptr) {
        return;
    }
    unsigned int handle = mm::mtl::PtrSingleton<fw::EffectManager>::sys()->create(m_popEffect, true);
    if (handle == 0) {
        return;
    }
    mm::mtl::PtrSingleton<fw::EffectManager>::sys()->setCategory(handle, fw::EF_CATEGORY(2));
    effect::SendParam param;
    param.m_mtx.setTrans(pos);
    mm::mtl::PtrSingleton<fw::EffectManager>::sys()->setParam(handle, &param);
}

// ---- GmkEnemyWaveList (GmkEnemyList's list at 0x470; placeholder slot symbols: see its header)
GmkEnemyWaveList::~GmkEnemyWaveList() { dispose(); }

static inline const char* getSheetnameByKindName(const GmkManager* manager, int id, const char* kindName);

void GmkEnemyListWaveExtension::create(IGmkList::CreateInfo& info) {
    if (!(gf::GfGameManager::isInstalledBattleArenaContents() || gf::GfGameManager::isGameTypeIra())) {
        return;
    }
    IGmkList::CreateInfo waveInfo = info;
    const char* name = getSheetnameByKindName(GmkManager::sys(), static_cast<const GmkSet*>(info.m_param)->m_createInfo.m_bdatId,
                                              "enemyWave");
    if (name != nullptr) {
        waveInfo.m_bdatName = name;
        m_waveList.create(waveInfo);
    }
    if (gf::GfGameManager::isGameTypeIra()) {
        if (fw::EffectPack* pack = gf::GfFieldManager::getEffectPack()) {
            m_popEffect = mm::mtl::PtrSingleton<fw::EffectManager>::sys()->search("ma40a_01_130_dlc", pack);
        }
    }
}

void GmkEnemyWaveList::create(const IGmkList::CreateInfo& info) { TGmkList::create(info); }

void GmkEnemyWaveList::dispose() {
    m_subList.dispose();
    const GmkSet* set = static_cast<const GmkSet*>(getCreateInfo().m_param);
    if (set != nullptr && !set->m_createInfo.m_flag) {
        gf::GfGameManager::setStopMainMenuOpenForGimmick(false);
    }
    TGmkList::dispose();
}

void GmkEnemyWaveList::update(float dt) {
    TGmkList::update(dt);
    m_subList.update(dt);
}

bool GmkEnemyWaveList::updateImmediate() { return TGmkList::updateImmediate() && m_subList.updateImmediate(); }

void GmkEnemyWaveList::debugUpdateMmf() {
    TGmkList::debugUpdateMmf();
    m_subList.debugUpdateMmf();
}
}  // namespace gmk

// instantiated for gmk::GmkRoutedEnemy::createRouteNavis, gmk::GmkRoutedMob::createRouteNavis (not written yet)
template void mm::mtl::Vector<std::pair<gf::GF_OBJ_HANDLE*, gmk::GmkRouteNavi> >::expand(unsigned long, unsigned long);

namespace gmk {

void GmkEnemyWaveList::debugDraw() const {
    TGmkList::debugDraw();
    m_subList.debugDraw();
}

unsigned char GmkEnemyInsts::BdatInfo::fn_710058356C(CBdatWrapper bdat, int row) {
    unsigned char groups = Bdat::getFlagVal(bdat.m_fp, "flag", row, "pop_smn") != 0;
    if (Bdat::getMember(bdat.m_fp, "pop_smn2") != nullptr && Bdat::getFlagVal(bdat.m_fp, "flag", row, "pop_smn2") != 0) {
        groups |= 2;
    }
    if (Bdat::getMember(bdat.m_fp, "pop_smn3") != nullptr && Bdat::getFlagVal(bdat.m_fp, "flag", row, "pop_smn3") != 0) {
        groups |= 4;
    }
    if (Bdat::getMember(bdat.m_fp, "pop_smn4") != nullptr && Bdat::getFlagVal(bdat.m_fp, "flag", row, "pop_smn4") != 0) {
        groups |= 8;
    }
    return groups;
}

void GmkTbox::onPlayerAccessed(gf::GF_OBJ_HANDLE*) {}

void GmkEffect::debugUpdateMmf() {}

void GmkRoute::debugUpdateMmf() {}

void GmkRoutePoint::debugUpdateMmf() {}

void GmkAreaBgm::debugDraw() const {}

void GmkMapGimmick::onPlayerAccessed(gf::GF_OBJ_HANDLE*) {}

void GmkJump::debugUpdateMmf() {}

void GmkWarp::debugUpdateMmf() {}

void GmkElevator::onLeavePhantom(const gmk::IGmkPhantomEventListener::OnLeaveInfo&) {}

void GmkTrigger::debugDraw() const {}

void GmkTrigger::seqUpdate(float) { applyPopCondMatched(m_phantom.pad_83); }

void GmkTrigger::update(float dt) {
    AGmkBase::update(dt);
    if (m_seq) {
        (this->*m_seq)(dt);
    }
}

void GmkAntiBladeArea::debugDraw() const {}

GmkRoutePointList::~GmkRoutePointList() {}

GmkRoutedEnemyPointList::~GmkRoutedEnemyPointList() {}

GmkMobList::~GmkMobList() {}

void GmkMobList::onResetUpdateGmkIndex() {
    if (++m_resetCount >= 2) {
        m_resetCount = 0;
        gf::GfFieldGimmick* fieldGimmick = mm::mtl::PtrSingleton<gf::GfFieldGimmick>::sys();
        if (fieldGimmick != nullptr) {
            fieldGimmick->m_mobSlotMgr.m_failedPopDistSqs.clear();
            fieldGimmick->m_mobSlotMgr.m_popDistSqLimit = 1.0e12f;
        }
    }
}

gmk::AGmkBase* GmkDmgPhantomList::getInst(unsigned int index) const {
    return const_cast<GmkDmgPhantom*>(&m_gmks[index]);
}

gmk::AGmkBase* GmkDmgEffectList::getInst(unsigned int index) const {
    return const_cast<GmkDmgEffect*>(&m_gmks[index]);
}

gmk::AGmkBase* GmkDmgSeList::getInst(unsigned int index) const {
    return const_cast<GmkDmgSe*>(&m_gmks[index]);
}

gmk::AGmkBase* GmkSalvageLocatorList::getInst(unsigned int index) const {
    return const_cast<GmkSalvageLocator*>(&m_gmks[index]);
}

bool GmkManager::isGmkSetsReady() const {
    if (!isValid() || m_gmkSets.size() == 0) {
        return false;
    }
    for (GmkSet* const* it = m_gmkSets.begin(); it != m_gmkSets.end(); ++it) {
        if (!(*it)->isValid() || !(*it)->isGmkListsCreated()) {
            return false;
        }
    }
    return true;
}

bool GmkSet::isGmkListsCreated() const {
    // the step's constant first: clang folds the null-pointer case of the member pointer compare away
    if (&GmkSet::seqUpdate != m_seq) {
        return false;
    }
    for (unsigned int i = 0; i < GMK_LIST_NUM; ++i) {
        const IGmkList* list = m_gmkLists[i];
        if (list == nullptr) {
            continue;
        }
        const IGmkList::CreateInfo& info = list->getCreateInfo();
        if (info.m_allocHandle.m_handle == 0 || info.m_path.length() == 0) {
            continue;
        }
        if (!list->isValid()) {
            return false;
        }
    }
    return true;
}

bool GmkManager::updateImmediate() {
    if (!isValid() || &GmkManager::seqUpdate != m_seq) {
        update(0.0f);
        return false;
    }
    if (m_gmkSets.size() == 0) {
        return true;
    }
    for (GmkSet* const* it = m_gmkSets.begin(); it != m_gmkSets.end(); ++it) {
        if (!(*it)->updateImmediate()) {
            return false;
        }
    }
    return true;
}

void GmkManager::seqUpdate(float dt) {
    m_phantomManager.update(dt);
    for (mm::mtl::IntrusiveList<GmkSquad>::iterator it = m_squadManager.m_list.begin(); it != m_squadManager.m_list.end(); ++it) {
        GmkSquad& squad = *it;
        if (squad.m_seq) {
            (squad.*squad.m_seq)(dt);
        }
    }
    TGmkActiveList<GmkPrecious>::sys()->pad_20 = true;
    {
        TGmkActiveList<GmkPrecious>* list = TGmkActiveList<GmkPrecious>::sys();
        for (mm::mtl::IntrusiveList<GmkPrecious>::iterator it = list->m_list.begin(); it != list->m_list.end(); ++it) {
            (*it).updateInActiveList(dt);
        }
    }
    TGmkActiveList<GmkPrecious>::sys()->pad_20 = false;
    TGmkActiveList<GmkSe>::sys()->pad_20 = true;
    {
        TGmkActiveList<GmkSe>* list = TGmkActiveList<GmkSe>::sys();
        for (mm::mtl::IntrusiveList<GmkSe>::iterator it = list->m_list.begin(); it != list->m_list.end(); ++it) {
            (*it).updateInActiveList(dt);
        }
    }
    TGmkActiveList<GmkSe>::sys()->pad_20 = false;
    TGmkActiveList<GmkSeLine>::sys()->pad_20 = true;
    {
        TGmkActiveList<GmkSeLine>* list = TGmkActiveList<GmkSeLine>::sys();
        for (mm::mtl::IntrusiveList<GmkSeLine>::iterator it = list->m_list.begin(); it != list->m_list.end(); ++it) {
            (*it).updateInActiveList(dt);
        }
    }
    TGmkActiveList<GmkSeLine>::sys()->pad_20 = false;
    TGmkActiveList<GmkEvent>::sys()->pad_20 = true;
    {
        TGmkActiveList<GmkEvent>* list = TGmkActiveList<GmkEvent>::sys();
        for (mm::mtl::IntrusiveList<GmkEvent>::iterator it = list->m_list.begin(); it != list->m_list.end(); ++it) {
            (*it).updateInActiveList(dt);
        }
    }
    TGmkActiveList<GmkEvent>::sys()->pad_20 = false;
    TGmkActiveList<GmkTutorial>::sys()->pad_20 = true;
    {
        TGmkActiveList<GmkTutorial>* list = TGmkActiveList<GmkTutorial>::sys();
        for (mm::mtl::IntrusiveList<GmkTutorial>::iterator it = list->m_list.begin(); it != list->m_list.end(); ++it) {
            GmkTutorial& tutorial = *it;
            if (tutorial.m_phantom.pad_83 && gf::GfGameFlag::getLocal(1, tutorial.getGameFlagId()) == 0 &&
                gf::GfGameManager::isGmkTutorialOK()) {
                tutorial.beginTutorial();
            }
        }
    }
    TGmkActiveList<GmkTutorial>::sys()->pad_20 = false;
    size_t num = m_gmkSets.size();
    for (size_t i = 0; i < num; ++i) {
        if (GmkSet* set = m_gmkSets[i]) {
            set->update(dt);
        }
    }
}

void GmkManager::update(float dt) {
    if (m_bdat.m_seq) {
        (m_bdat.*m_bdat.m_seq)(dt);
    }
    if (m_seq) {
        (this->*m_seq)(dt);
    }
}

bool GmkManager::isValid() const {
    return m_bdat.m_assetData != 0 && fw::BdatManager::isEnableBdat(m_bdat.m_createInfo.m_param) && m_bdatFp != nullptr;
}

void GmkManager::create(const CreateInfo& info) {
    dispose();
    m_createInfo = info;
    GmkBdat::CreateInfo bdatInfo;
    bdatInfo.m_handle = info.m_handle;
    bdatInfo.m_path = m_createInfo.m_bdatPath.m_str;
    bdatInfo.m_param = 3;
    m_bdat.create(bdatInfo);
    m_gmkSets.setAllocator(fw::FrameworkMemory::getAllocator(5));
    m_gmkSets.reserve(static_cast<unsigned int>(info.m_param));
    m_seq = &GmkManager::seqWaitValidateResDefBdatFp;
}

void GmkManager::seqWaitValidateResDefBdatFp(float) {
    if (m_bdat.m_assetData != 0 && fw::BdatManager::isEnableBdat(m_bdat.m_createInfo.m_param)) {
        m_bdatFp = Bdat::getFP(m_createInfo.m_tableName.m_str);
        m_seq = &GmkManager::seqUpdate;
    }
}

void GmkManager::createGmkSet(mtl::ALLOC_HANDLE handle, int bdatId, const mm::Vec3& pos, float rot) {
    if (m_gmkSets.size() != 0) {
        for (GmkSet** it = m_gmkSets.begin(); it != m_gmkSets.end(); ++it) {
            if ((*it)->m_createInfo.m_bdatId == bdatId) {
                return;
            }
        }
    }
    GmkSet::CreateInfo info;
    info.m_allocHandle = handle;
    info.m_bdatId = bdatId;
    info.m_pos = pos;
    info.m_rotY = rot;
    GmkSet* set = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkSet(&info);
    m_gmkSets.push_back(set);
}

bool GmkBdat::create(const CreateInfo& info) {
    dispose();
    m_createInfo = info;
    m_resource = fw::CommonResource::request(info.m_handle, m_createInfo.m_path.m_str, 9, false);
    if (m_resource->m_RefCount != 1) {
        return false;
    }
    m_seq = &GmkBdat::seqWaitResourceLoaded;
    return true;
}

void GmkBdat::dispose() {
    m_seq = nullptr;
    if (m_createInfo.m_param >= 0) {
        fw::BdatManager::unregistBdat(m_createInfo.m_param);
        m_createInfo.m_param = -1;
    }
    if (m_resource != nullptr) {
        m_resource->release();
        m_resource = nullptr;
    }
    m_assetData = nullptr;
    m_createInfo = CreateInfo();
}

void GmkManager::disposeGmkSet(int bdatId) {
    if (m_gmkSets.size() == 0) {
        return;
    }
    for (GmkSet** it = m_gmkSets.begin(); it != m_gmkSets.end(); ++it) {
        if ((*it)->m_createInfo.m_bdatId == bdatId) {
            delete *it;
            m_gmkSets.erase(it);
            return;
        }
    }
}
}  // namespace gmk

// instantiated for gmk::GmkManager::disposeGmkSet
template mm::mtl::Vector<gmk::GmkSet*>::iterator mm::mtl::Vector<gmk::GmkSet*>::erase(gmk::GmkSet**);

namespace gmk {

const char* GmkManager::getSheetnameByType(int id, GmkType type) const {
    mm::mtl::FixStr<256> column;
    column.format("%s_bdat", getGmkKindName(s_gmkKindNames, type));
    unsigned char* setFp = m_bdatFp;
    return Bdat::getMember(setFp, column.m_str) != nullptr ? reinterpret_cast<const char*>(Bdat::getValCheck(setFp, column.m_str, id, 7)) : nullptr;
}

int GmkManager::getMapBdatId(int id) const {
    unsigned char* fp = m_bdatFp;
    int count = Bdat::getIdCount(fp);
    int top = Bdat::getIdTop(fp);
    if (id < top || id >= top + count) {
        return -1;
    }
    return static_cast<unsigned short>(Bdat::getValCheck(fp, "mapId", id, 2));
}

GmkSet* GmkManager::findGmkSet(int bdatId) const {
    for (GmkSet* const* it = m_gmkSets.begin(); it != m_gmkSets.end(); ++it) {
        if (*it != nullptr && (*it)->m_createInfo.m_bdatId == bdatId) {
            return *it;
        }
    }
    return nullptr;
}

int GmkManager::findFirstBdatId_RSC_GmkSetList(GmkType type, int bdatId) const {
    int id = findFirstBdatId_RSC_GmkSetList(gf::GfGameManager::getMapID());
    if (id > 0 && isBdatIdOfGmkInstExist(id, type, bdatId)) {
        return id;
    }
    unsigned char* fp = m_bdatFp;
    if (fp != nullptr) {
        int count = Bdat::getIdCount(fp);
        int top = Bdat::getIdTop(fp);
        for (int i = top; i < top + count; ++i) {
            if (isBdatIdOfGmkInstExist(i, type, bdatId)) {
                return i;
            }
        }
    }
    return -1;
}

int GmkManager::findFirstBdatId_RSC_GmkSetList(int mapId) const {
    if (m_bdat.m_assetData != 0 && fw::BdatManager::isEnableBdat(m_bdat.m_createInfo.m_param)) {
        unsigned char* fp = m_bdatFp;
        int count = Bdat::getIdCount(fp);
        int top = Bdat::getIdTop(fp);
        for (int id = top; id < top + count; ++id) {
            if (getMapBdatId(id) == mapId) {
                return id;
            }
        }
    }
    return -1;
}

bool GmkManager::isBdatIdOfGmkInstExist(int id, GmkType type, int bdatId) const {
    if (id > 0) {
        const char* sheet = getSheetnameByType(id, type);
        if (sheet != nullptr && sheet[0] != '\0') {
            unsigned char* fp = Bdat::isExistFP(sheet);
            if (fp != nullptr) {
                int count = Bdat::getIdCount(fp);
                int top = Bdat::getIdTop(fp);
                return bdatId >= top && bdatId < top + count;
            }
        }
    }
    return false;
}

bool GmkManager::isValidView() const {
    if (!isValid() || &GmkManager::seqUpdate != m_seq) {
        return false;
    }
    for (GmkSet* const* it = m_gmkSets.begin(); it != m_gmkSets.end(); ++it) {
        if (!(*it)->isValid() || !(*it)->isValidView()) {
            return false;
        }
    }
    return true;
}

bool GmkSet::isValidView() const {
    if (!isValid() || &GmkSet::seqUpdate != m_seq) {
        return false;
    }
    for (IGmkList* const* it = m_gmkLists; it != m_gmkLists + GMK_LIST_NUM; ++it) {
        IGmkList* list = *it;
        if (list == nullptr) {
            continue;
        }
        const IGmkList::CreateInfo& info = list->getCreateInfo();
        if (info.m_allocHandle.m_handle == 0 || info.m_path.length() == 0) {
            continue;
        }
        if (!list->isValid()) {
            return false;
        }
        list->getGmkType();  // the original calls it and drops the result
        unsigned int num = list->getInstNum();
        for (unsigned int i = 0; i < num; ++i) {
            AGmkBase* gmk = list->getInst(i);
            if (gmk != nullptr && gmk->isValid() && !isGmkInstValidView(*gmk)) {
                return false;
            }
        }
    }
    return true;
}

void GmkPhantomManager::update(float) {
    mm::mtl::FixedArray<fw::TColiCheckResult<256>, 3>& results = m_results;
    for (unsigned int i = 0; i < 3; ++i) {
        results[i].clear();
    }
    {
        gf::GfObjAcc acc(gf::GfGameManager::getControlMoverForGimmick());
        if (acc.isValidTransform()) {
            const fw::Transform& transform = acc.getWorldTransform();
            fw::ColiCheckConfig config;
            config.m_flags = 2;
            config.m_mask = 0x100000;
            config.m_mode = 0;
            fw::ColiCheck::testSpherePhantom(results[0], transform.position, 0.0f, config);
        }
    }
    {
        gf::GfObjAcc acc(gf::GfGameParty::getHandleDriver(1, gf::PTPOS(0)));
        if (acc.isValidTransform()) {
            const fw::Transform& transform = acc.getWorldTransform();
            fw::ColiCheckConfig config;
            config.m_flags = 2;
            config.m_mask = 0x100000;
            config.m_mode = 0;
            fw::ColiCheck::testSpherePhantom(results[1], transform.position, 0.0f, config);
        }
    }
    {
        gf::GfObjAcc acc(gf::GfGameParty::getHandleDriver(2, gf::PTPOS(0)));
        if (acc.isValidTransform()) {
            const fw::Transform& transform = acc.getWorldTransform();
            fw::ColiCheckConfig config;
            config.m_flags = 2;
            config.m_mask = 0x100000;
            config.m_mode = 0;
            fw::ColiCheck::testSpherePhantom(results[2], transform.position, 0.0f, config);
        }
    }
    for (mm::mtl::IntrusiveList<GmkPhantom>::iterator it = m_phantoms.begin(); it != m_phantoms.end(); ++it) {
        it->update(results);
    }
}

GmkRoutedEnemyList::GmkRoutedEnemyList(unsigned int updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame), m_triggerList(-1) {}

void GmkRoutedEnemyList::setUpdateGmkNumPerFrame(unsigned int num) {
    TGmkList::setUpdateGmkNumPerFrame(num);
    m_triggerList.setUpdateGmkNumPerFrame(num);
}

void GmkRoutedEnemyList::create(const IGmkList::CreateInfo& info) {
    if (m_bdatInfo.create()) {
        TGmkList::create(info);
    } else {
        dispose();
    }
}

void GmkRoutedEnemyList::dispose() {
    m_triggerList.dispose();
    TGmkList::dispose();
}

void GmkRoutedEnemyList::createGmk(void* data) {
    TGmkList::createGmk(data);
    IGmkList::CreateInfo info = getCreateInfo();
    if (info.m_allocHandle.m_handle != 0 && info.m_path.length() != 0) {
        info.m_bdatName.clear();
        m_triggerList.create(info);
    }
}

void GmkRoutedEnemyList::update(float dt) {
    m_triggerList.update(dt);
    TGmkList::update(dt);
}

bool GmkRoutedEnemyList::updateImmediate() {
    return TGmkList::updateImmediate() && m_triggerList.updateImmediate();
}

void GmkRoutedEnemyList::debugUpdateMmf() {
    TGmkList::debugUpdateMmf();
    m_triggerList.debugUpdateMmf();
}

void GmkRoutedEnemyList::debugDraw() const {
    TGmkList::debugDraw();
    m_triggerList.debugDraw();
}

GmkEnemyList::GmkEnemyList(unsigned int updateGmkNumPerFrame)
    : TGmkList(updateGmkNumPerFrame), m_triggerList(-1) {}

// the wave list is set through an IGmkList pointer to it (the original calls its slot)
void GmkEnemyList::setUpdateGmkNumPerFrame(unsigned int num) {
    TGmkList::setUpdateGmkNumPerFrame(num);
    m_triggerList.setUpdateGmkNumPerFrame(num);
    IGmkList* waveList = &m_waveExt.m_waveList;
    if (gf::GfGameManager::isInstalledBattleArenaContents() || gf::GfGameManager::isGameTypeIra()) {
        waveList->setUpdateGmkNumPerFrame(num);
    }
}

void GmkEnemyList::create(const IGmkList::CreateInfo& info) {
    if (m_bdatInfo.create()) {
        TGmkList::create(info);
    } else {
        dispose();
    }
}

void GmkEnemyList::dispose() {
    m_triggerList.dispose();
    if (gf::GfGameManager::isInstalledBattleArenaContents() || gf::GfGameManager::isGameTypeIra()) {
        m_waveExt.m_waveList.dispose();
        m_waveExt.m_popEffect = nullptr;
    }
    TGmkList::dispose();
}

void GmkEnemyList::createGmk(void* data) {
    TGmkList::createGmk(data);
    IGmkList::CreateInfo info = getCreateInfo();
    if (info.m_allocHandle.m_handle != 0 && info.m_path.length() != 0) {
        info.m_bdatName.clear();
        m_triggerList.create(info);
        m_waveExt.create(info);
    }
}

bool GmkEnemyList::updateImmediate() {
    return TGmkList::updateImmediate() && m_triggerList.updateImmediate() &&
           (gf::GfGameManager::isInstalledBattleArenaContents() || gf::GfGameManager::isGameTypeIra()) &&
           m_waveExt.m_waveList.updateImmediate();
}

void GmkEnemyList::debugUpdateMmf() {
    TGmkList::debugUpdateMmf();
    m_triggerList.debugUpdateMmf();
    if (gf::GfGameManager::isInstalledBattleArenaContents() || gf::GfGameManager::isGameTypeIra()) {
        m_waveExt.m_waveList.debugUpdateMmf();
    }
}

void GmkEnemyList::debugDraw() const {
    TGmkList::debugDraw();
    m_triggerList.debugDraw();
    if (gf::GfGameManager::isInstalledBattleArenaContents() || gf::GfGameManager::isGameTypeIra()) {
        m_waveExt.m_waveList.debugDraw();
    }
}

GmkEnemyList::~GmkEnemyList() {
    dispose();
}

GmkRoutedEnemyList::~GmkRoutedEnemyList() {
    dispose();
}

GmkCollectionList::~GmkCollectionList() {
    dispose();
}

void GmkCollectionList::create(const IGmkList::CreateInfo& info) {
    if (m_bdatInfo.create()) {
        TGmkList::create(info);
    } else {
        dispose();
    }
}

void GmkSalvageList::update(float dt) {
    TGmkList::update(dt);
    m_gmkSet.update(dt);
}

void GmkSalvageList::debugUpdateMmf() {
    TGmkList::debugUpdateMmf();
}

void GmkSalvageList::debugDraw() const {
    TGmkList::debugDraw();
}

GmkSalvageList::~GmkSalvageList() {}

GmkTutorialList::~GmkTutorialList() {
    dispose();
}

GmkMapGimmickList::~GmkMapGimmickList() {
    dispose();
}

void GmkMapGimmickList::setUpdateGmkNumPerFrame(unsigned int num) {
    TGmkList::setUpdateGmkNumPerFrame(num);
    m_triggerList.setUpdateGmkNumPerFrame(num);
}

void GmkMapGimmickList::dispose() {
    m_triggerList.dispose();
    TGmkList::dispose();
}

void GmkMapGimmickList::update(float dt) {
    m_triggerList.update(dt);
    TGmkList::update(dt);
}

bool GmkMapGimmickList::updateImmediate() {
    return TGmkList::updateImmediate() && m_triggerList.updateImmediate();
}

void GmkMapGimmickList::debugUpdateMmf() {
    TGmkList::debugUpdateMmf();
    m_triggerList.debugUpdateMmf();
}

void GmkMapGimmickList::debugDraw() const {
    TGmkList::debugDraw();
    m_triggerList.debugDraw();
}

AGmkBase* GmkMapGimmickList::getInst(unsigned int index) const {
    return const_cast<GmkMapGimmick*>(&m_gmks[index]);
}


GmkSetOfSalvageChildren::~GmkSetOfSalvageChildren() {}

void GmkSetOfSalvageChildren::createGmkLists(int id) {
    for (int i = 0; i < GMK_LIST_NUM; ++i) {
        if (m_gmkLists[i] != nullptr) {
            delete m_gmkLists[i];
            m_gmkLists[i] = nullptr;
        }
    }
    unsigned char* fp = GmkManager::sys()->m_bdatFp;
    if (Bdat::getMember(fp, "salvage") == nullptr) {
        return;
    }
    const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(fp, "salvage", id, 7));
    if (name == nullptr || *name == '\0') {
        return;
    }
    m_gmkLists[GmkEnemy::TYPE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkEnemyList(0);
    typedef TGmkFormPc<GmkType(24), TGmkFormPcnpc<GmkType(25)> > FormPc;
    typedef TGmkFormPcnpc<GmkType(25)> FormPcnpc;
    m_gmkLists[FormPc::TYPE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false)
        TGmkFormPcList<FormPc, TGmkList<FormPc, FormPc::BdatInfo, 1129337414u, 3u, GmkFormPcGob> >(0);
    m_gmkLists[FormPcnpc::TYPE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false)
        TGmkFormPcnpcList<FormPcnpc, TGmkList<FormPcnpc, FormPcnpc::BdatInfo, 1347310150u, 2u, GmkFormPcnpcGob> >(0);
    m_gmkLists[GmkSalvageLocator::TYPE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkSalvageLocatorList(0);
    for (int i = 0; i < GMK_LIST_NUM; ++i) {
        IGmkList* list = m_gmkLists[i];
        if (list == nullptr) {
            continue;
        }
        const char* bdatName;
        {
            GmkManager* manager = GmkManager::sys();
            mm::mtl::FixStr<256> column;
            column.format("%s_bdat", getGmkKindName(s_gmkKindNames, i));
            unsigned char* setFp = manager->m_bdatFp;
            bdatName = Bdat::getMember(setFp, column.m_str) != nullptr ? reinterpret_cast<const char*>(Bdat::getValCheck(setFp, column.m_str, id, 7)) : nullptr;
        }
        IGmkList::CreateInfo info;
        info.m_allocHandle = m_createInfo.m_allocHandle;
        info.m_param = this;
        info.m_path = "gmk/";
        info.m_path += name;
        info.m_path += ".lvb";
        if (bdatName != nullptr) {
            info.m_bdatName = bdatName;
        }
        info.m_pos = m_createInfo.m_pos;
        info.m_rotY = m_createInfo.m_rotY;
        list->create(info);
    }
    m_npcManager.dispose();
}

bool GmkSet::isValid() const {
    // read through a copy: the handle's own 4-byte load (the set's 16-aligned field is not widened with m_bdatId)
    mtl::ALLOC_HANDLE handle = m_createInfo.m_allocHandle;
    if (handle.m_handle == 0 || !(m_createInfo.m_bdatId > 0)) {
        return false;
    }
    // a set whose BDAT file was not asked for needs none
    const GmkBdat::CreateInfo& bdat = m_bdat.m_createInfo;
    if (bdat.m_handle.m_handle == 0 || !(bdat.m_path.length() > 0) || bdat.m_param < 0) {
        return true;
    }
    return m_bdat.m_assetData != 0 && fw::BdatManager::isEnableBdat(bdat.m_param);
}

void GmkSet::update(float dt) {
    if (!GmkManager::sys()->isValid()) {
        return;
    }
    if (m_bdat.m_seq) {
        (m_bdat.*m_bdat.m_seq)(dt);
    }
    m_npcManager.update(dt);
    if (m_seq) {
        (this->*m_seq)(dt);
    }
}

// defined after update (the original's address is lower): the original passes 0.0f to m_npcManager.update but leaves
// GmkNpcIdInfo::update's unused float unset, i.e. dead-argument elimination saw GmkNpcManager::update before
// GmkNpcIdInfo::update in the module; referencing GmkNpcIdInfo::update here before update's body is emitted reverses
// that order
bool GmkSet::updateImmediate() {
    if (!isValid() || &GmkSet::seqUpdate != m_seq) {
        update(0.0f);
        return false;
    }
    for (int i = 0; i < GMK_LIST_NUM; ++i) {
        if (m_gmkLists[i] != nullptr) {
            m_gmkLists[i]->updateImmediate();
        }
    }
    unsigned int size = m_npcManager.m_npcIdInfos.size();
    for (unsigned int i = 0; i < size; ++i) {
        GmkNpcIdInfo& info = m_npcManager.m_npcIdInfos[i];
        if (info.isValid()) {
            info.update(0.0f, m_npcManager.m_flag);
        }
    }
    return true;
}

int getCurrentMapBdatId() { return gf::GfGameManager::getMapID(); }

const IGmkList* GmkSet::getGmkList(GmkType type) const { return m_gmkLists[static_cast<unsigned int>(type)]; }

IGmkList* GmkSet::getGmkList(GmkType type) { return m_gmkLists[static_cast<unsigned int>(type)]; }

GmkNpcManager::~GmkNpcManager() { dispose(); }

void GmkNpcManager::update(float dt) {
    if (gf::GfGameManager::isFadeout()) {
        unsigned int size = m_npcIdInfos.size();
        for (unsigned int i = 0; i < size; ++i) {
            GmkNpcIdInfo& info = m_npcIdInfos[i];
            if (info.isValid()) {
                info.update(dt, m_flag);
            }
        }
        return;
    }
    unsigned int size = m_npcIdInfos.size();
    if (size <= m_updateIdx) {
        m_updateIdx = 0;
    }
    unsigned int num = m_updateNumPerFrame < size ? m_updateNumPerFrame : size;
    for (unsigned int n = 0; n < num; ++n, ++m_updateIdx) {
        if (size <= m_updateIdx) {
            m_updateIdx = 0;
            return;
        }
        GmkNpcIdInfo& info = m_npcIdInfos[m_updateIdx];
        if (info.isValid()) {
            info.update(dt, m_flag);
        }
    }
}


void GmkNpcIdInfo::dispose() {
    if (m_handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        m_gmk->unbindToGameObj(m_handle);
        gf::GfObjUtil::destroy(m_handle);
        m_handle = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        m_gmk = nullptr;
        for (mm::mtl::IntrusiveList<AGmkNpc>::iterator it = m_gmks->begin(); it != m_gmks->end(); ++it) {
            if (it->isPopCondMatched()) {
                setActiveGmkNpc(&*it);
                break;
            }
        }
    }
    setActiveGmkNpc(nullptr);
    if (m_gmks != nullptr) {
        delete m_gmks;
        m_gmks = nullptr;
    }
    m_npcId = 0;
    m_bdatFp = nullptr;
}

void GmkNpcIdInfo::update(float, bool flag) {
    if (!isValid() || !isInterestPosExist()) {
        return;
    }
    {
        gf::GfObjAcc acc(m_handle);
        if (gf::GfObj* obj = acc.getObj()) {
            switch (obj->m_type) {
            case 5:
                if (acc.isBattle()) {
                    return;
                }
                break;
            case 6:
                if (gf::GfComBehaviorNpc* behavior = obj->getComponent<gf::GfComBehaviorNpc>(6)) {
                    if (behavior->pad_100) {
                        return;
                    }
                }
                break;
            }
        }
    }
    for (mm::mtl::IntrusiveList<AGmkNpc>::iterator it = m_gmks->begin(); it != m_gmks->end(); ++it) {
        if (it->isPopCondMatched()) {
            setActiveGmkNpc(&*it);
            break;
        }
    }
    if (m_handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        if (flag && m_gmk != nullptr && m_gmk->isPopDistCondMatched()) {
            createGobInst();
        }
    } else if (m_gmk->isDepopCondMatched() || m_gmk->isDepopDistCondMatched()) {
        gf::GF_OBJ_HANDLE* handle = m_handle;
        if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            gf::GfObjAcc acc(handle);
            if (acc.getObj() != nullptr && !acc.isDestroy() && !acc.testFlag(0x11)) {
                gf::SCOM_DESTROY_GAME_OBJ::create(handle, 1.0f, 0);
            }
        }
    }
}

inline void GmkNpcIdInfo::disposeGobInst() {
    if (m_handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        m_gmk->unbindToGameObj(m_handle);
        gf::GfObjUtil::destroy(m_handle);
        m_handle = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        m_gmk = nullptr;
        for (mm::mtl::IntrusiveList<AGmkNpc>::iterator it = m_gmks->begin(); it != m_gmks->end(); ++it) {
            if (it->isPopCondMatched()) {
                setActiveGmkNpc(&*it);
                break;
            }
        }
    }
}

// an object's setup as T when the setup and the object are of the given type, null otherwise (as gf_obj_factory's;
// the name is not the original's: the original's code is inline in each caller)
template <class T>
static inline T* getSetupOf(gf::GFOBJ_INFO* info, int type) {
    if (info == nullptr || info->m_setup == nullptr) {
        return nullptr;
    }
    gf::GfObjSetup* setup = info->m_setup;
    gf::GfObj* obj = info->m_obj;
    if (setup->m_type == static_cast<int>(obj->m_type) && type == static_cast<int>(obj->m_type)) {
        return setup->getRTTI()->isKindOf(&T::m_rtti) ? static_cast<T*>(setup) : nullptr;
    }
    return nullptr;
}

void GmkNpcIdInfo::createGobInst() {
    disposeGobInst();
    m_handle = gf::GfObjFactory::createGmkNpc(CBdatWrapper(m_gmk->getBindedBdatFp()), m_gmk->getBindedBdatId());
    if (m_handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    m_gmk->bindToGameObj(m_handle);
    m_gmk->validateDisp();
    gf::GfObjSetupNpc* setup = getSetupOf<gf::GfObjSetupNpc>(gf::GfObjManager::getObjInfo(m_handle), 6);
    mm::Vec3 pos;
    mm::Vec3 rot;
    m_gmk->findPopPosRot(pos, rot);
    setup->m_initialPos = pos;
    setup->pad_30 = rot;
}

void GmkNpcIdInfo::removeGmkNpc(AGmkNpc* npc) {
    if (npc == nullptr) {
        return;
    }
    npc->m_npcIdInfo = nullptr;
    if (m_gmk == npc) {
        disposeGobInst();
        m_gmk = nullptr;
    }
    m_gmks->remove(npc);
}

void GmkNpcManager::create() {
    m_npcIdInfos.setAllocator(fw::FrameworkMemory::getAllocator(5));
    unsigned char* fpA8 = gf::GfDataBdat::getFP(0xa8);
    unsigned char* fp88 = gf::GfDataBdat::getFP(0x88);
    unsigned char* fp8a = gf::GfDataBdat::getFP(0x8a);
    unsigned int num = Bdat::getIdCount(fpA8) + Bdat::getIdCount(fp88) + Bdat::getIdCount(fp8a);
    m_npcIdInfos.reserve(num);
    m_npcIdInfos.resize(num);
    m_npcIdTop = Bdat::getIdTop(gf::GfDataBdat::getFP(0xa8));
}

const GmkNpcIdInfo* GmkNpcManager::getNpcIdInfoByNpcId(int npcId) const {
    return &m_npcIdInfos[getNpcIdInfoIdxFromNpcId(npcId)];
}

int GmkNpcManager::getNpcIdInfoIdxFromNpcId(int npcId) {
    unsigned char* fp88 = gf::GfDataBdat::getFP(0x88);
    unsigned char* fp8a = gf::GfDataBdat::getFP(0x8a);
    unsigned char* fpA8 = gf::GfDataBdat::getFP(0xa8);
    if (npcId >= Bdat::getIdTop(fp88) && npcId < Bdat::getIdTop(fp88) + Bdat::getIdCount(fp88)) {
        return npcId - Bdat::getIdTop(fp88);
    }
    if (npcId >= Bdat::getIdTop(fp8a) && npcId < Bdat::getIdTop(fp8a) + Bdat::getIdCount(fp8a)) {
        return Bdat::getIdCount(fp88) + npcId - Bdat::getIdTop(fp8a);
    }
    int count88 = Bdat::getIdCount(fp88);
    int count8a = Bdat::getIdCount(fp8a);
    int topA8 = Bdat::getIdTop(fpA8);
    return count88 + npcId + count8a - topA8;
}

void GmkNpcManager::dispose() {
    m_npcIdTop = 0;
    if (m_npcIdInfos.size() != 0) {
        for (GmkNpcIdInfo* it = m_npcIdInfos.begin(); it != m_npcIdInfos.end(); ++it) {
            it->dispose();
        }
    }
    m_npcIdInfos.destroy();
}

void GmkNpcManager::removeGmkNpc(AGmkNpc* npc) {
    if (npc == nullptr) {
        return;
    }
    unsigned char* fp = npc->getBindedBdatFp();
    int row = npc->getBindedBdatId();
    if (row < Bdat::getIdTop(fp)) {
        return;
    }
    unsigned short npcId = Bdat::getValCheck(fp, "NpcID", row, 2);
    m_npcIdInfos[getNpcIdInfoIdxFromNpcId(npcId)].removeGmkNpc(npc);
}

// the same steps as dispose, written here: the original's dispose keeps its default CreateInfo on the stack, this
// copy does not (so the destructor does not inline dispose)
GmkSet::~GmkSet() {
    m_seq = nullptr;
    for (int i = 0; i < GMK_LIST_NUM; ++i) {
        if (m_gmkLists[i] != nullptr) {
            delete m_gmkLists[i];
            m_gmkLists[i] = nullptr;
        }
    }
    m_bdat.dispose();
    m_createInfo = CreateInfo();
}

void GmkSet::seqWaitToValidate_GfGameManager_m_mapID(float) {
    if (gf::GfGameManager::getMapID() != 0) {
        m_seq = &GmkSet::seqCreateMapBdat;
    }
}

void GmkSet::createGmkLists(int id) {
    m_npcManager.m_updateNumPerFrame = 0x20;
    for (int i = 0; i < GMK_LIST_NUM; ++i) {
        if (m_gmkLists[i] != nullptr) {
            delete m_gmkLists[i];
            m_gmkLists[i] = nullptr;
        }
    }
    typedef TGmkFormPc<GmkType(24), TGmkFormPcnpc<GmkType(25)> > FormPc24;
    typedef TGmkFormPcnpc<GmkType(25)> FormPcnpc25;
    typedef TGmkFormPc<GmkType(26), TGmkFormPcnpc<GmkType(27)> > FormPc26;
    typedef TGmkFormPcnpc<GmkType(27)> FormPcnpc27;
    m_gmkLists[0] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkEnemyList(32);
    m_gmkLists[1] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutedEnemyList(8);
    m_gmkLists[2] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutedEnemyPointList(1);
    m_gmkLists[3] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkNpcList(0);
    m_gmkLists[4] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutedNpcList(0);
    m_gmkLists[5] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutePointList(1);
    m_gmkLists[6] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkMapObj, GmkMapObj::BdatInfo, 1330659661u, 3u, GmkMapObjGob>(8);
    m_gmkLists[7] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkRoutedMapObj, GmkMapObj::BdatInfo, 1330662738u, 7u, GmkRouteGob>(4);
    m_gmkLists[8] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutePointList(1);
    m_gmkLists[9] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkTbox, GmkTbox::BdatInfo, 1481589332u, 6u, GmkTboxGob>(8);
    m_gmkLists[10] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkEvent, GmkEvent::BdatInfo, 1414420037u, 4u, GmkEventGob>(8);
    m_gmkLists[11] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkBattleLock, GmkBattleLock::BdatInfo, 1129075778u, 3u, GmkBattleLockGob>(8);
    m_gmkLists[12] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkFieldLock, GmkFieldLock::BdatInfo, 1129071686u, 2u, GmkFieldLockGob>(8);
    m_gmkLists[13] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkEffect, GmkEffect::BdatInfo, 1413695045u, 8u, GmkEffectGobCustom>(8);
    m_gmkLists[14] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkEffectLocator, GmkEffectLocator::BdatInfo, 1129072197u, 1u, GmkEffectLocatorGob>(1);
    m_gmkLists[15] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkSe, GmkSe::BdatInfo, 1162104403u, 2u, GmkSeGob>(8);
    m_gmkLists[16] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkSeLine, GmkSe::BdatInfo, 1313621331u, 2u, GmkSeLineGobCustom>(4);
    m_gmkLists[17] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkSeLinePoint, GmkSeLinePoint::BdatInfo, 1414548563u, 1u, GmkSeLinePointGobCustom>(1);
    m_gmkLists[18] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkMobList(8);
    m_gmkLists[19] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkRoutedMob, GmkMob::BdatInfo, 1112493394u, 6u, GmkRouteGob>(4);
    m_gmkLists[20] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutePointList(1);
    m_gmkLists[21] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkLandmark, GmkLandmark::BdatInfo, 1263354956u, 2u, GmkLandmarkGob>(8);
    m_gmkLists[22] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkRoute, GmkRoute::BdatInfo, 1448236355u, 5u, GmkRouteGob>(1);
    m_gmkLists[23] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutePointList(1);
    m_gmkLists[24] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkFormPcList<FormPc24, TGmkList<FormPc24, FormPc24::BdatInfo, 1129337414u, 3u, GmkFormPcGob> >(1);
    m_gmkLists[25] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkFormPcnpcList<FormPcnpc25, TGmkList<FormPcnpc25, FormPcnpc25::BdatInfo, 1347310150u, 2u, GmkFormPcnpcGob> >(1);
    m_gmkLists[26] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkFormPcList<FormPc26, TGmkList<FormPc26, FormPc26::BdatInfo, 1129337414u, 3u, GmkFormPcGob> >(1);
    m_gmkLists[27] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkFormPcnpcList<FormPcnpc27, TGmkList<FormPcnpc27, FormPcnpc27::BdatInfo, 1347310150u, 2u, GmkFormPcnpcGob> >(1);
    m_gmkLists[28] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkCollectionList(1);
    m_gmkLists[29] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkAreaBgm, GmkAreaBgm::BdatInfo, 1380009794u, 2u, GmkAreaBgmGob>(1);
    m_gmkLists[30] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkAreaWeather, GmkAreaWeather::BdatInfo, 1381259073u, 2u, GmkAreaWeatherGob>(1);
    m_gmkLists[31] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkSalvageList(1);
    m_gmkLists[32] = nullptr;
    m_gmkLists[33] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkMapGimmickList(1);
    m_gmkLists[34] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkPrecious, GmkPrecious::BdatInfo, 1396920912u, 2u, GmkPreciousGob>(1);
    m_gmkLists[35] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkGrave, GmkGrave::BdatInfo, 1447121479u, 4u, GmkGraveGob>(1);
    m_gmkLists[36] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkKizunaTalk, GmkKizunaTalk::BdatInfo, 1414421067u, 1u, GmkKizunaTalkGob>(1);
    m_gmkLists[37] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkJump, GmkJump::BdatInfo, 1347245386u, 3u, GmkJumpGobCustom>(1);
    m_gmkLists[38] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkWarp, GmkWarp::BdatInfo, 1347567959u, 1u, GmkWarpGobCustom>(1);
    m_gmkLists[39] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkSquadLeader, GmkSquadLeader::BdatInfo, 1145852243u, 2u, GmkSquadLeaderGobCustom>(1);
    m_gmkLists[40] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkSquadMember, GmkSquadMember::BdatInfo, 1112363347u, 1u, GmkSquadMemberGobCustom>(1);
    m_gmkLists[41] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkDoor, GmkDoor::BdatInfo, 1380929348u, 2u, GmkDoorGob>(1);
    m_gmkLists[42] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkElevator, GmkElevator::BdatInfo, 1414941765u, 2u, GmkElevatorGobCustom>(1);
    m_gmkLists[43] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkElevatorLocator, GmkElevatorLocator::BdatInfo, 1129073733u, 2u, GmkElevatorLocatorGob>(1);
    m_gmkLists[44] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkMapJump, GmkMapJump::BdatInfo, 1347047501u, 2u, GmkMapJumpGob>(1);
    m_gmkLists[45] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkFieldVolume, GmkFieldVolume::BdatInfo, 1296848454u, 2u, GmkFieldVolumeGob>(1);
    m_gmkLists[46] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkClimbing, GmkClimbing::BdatInfo, 1112362051u, 2u, GmkClimbingGob>(1);
    m_gmkLists[47] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkBlade, GmkBlade::BdatInfo, 1145130050u, 4u, GmkBladeGob>(1);
    m_gmkLists[48] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkDmgGimmick, GmkDmgGimmick::BdatInfo, 1296518468u, 1u, GmkDmgGimmickGobCustom>(1);
    m_gmkLists[49] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkDmgPhantomList(1);
    m_gmkLists[50] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkDmgEffectList(1);
    m_gmkLists[51] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkDmgSeList(1);
    m_gmkLists[52] = nullptr;
    m_gmkLists[53] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkTargetPoint, GmkTargetPoint::BdatInfo, 1414547284u, 1u, GmkTargetPointGob>(1);
    m_gmkLists[54] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkRoutedFootPrint, GmkRoutedFootPrint::BdatInfo, 1414547026u, 2u, GmkRoutedFootPrintGobCustom>(1);
    m_gmkLists[55] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkRoutedFootPrintPointList(1);
    m_gmkLists[56] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkAntiBladeArea, GmkAntiBladeArea::BdatInfo, 1095516737u, 2u, GmkAntiBladeAreaGob>(1);
    m_gmkLists[57] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkTutorialList(1);
    m_gmkLists[58] = nullptr;
    m_gmkLists[59] = nullptr;
    m_gmkLists[60] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkBattleChallengeRewardList(3);
    m_gmkLists[61] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkBattleChallengePortalList(1);
    m_gmkLists[62] = gf::GfGameManager::isGameTypeIra() ? 
        new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<GmkCamp, GmkCamp::BdatInfo, 1347240259u, 4u, GmkCampGob>(1) : nullptr;
    m_gmkLists[63] = gf::GfGameManager::isGameTypeIra() ? 
        new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkSealedStoneList(1) : nullptr;
    for (int i = 0; i < GMK_LIST_NUM; ++i) {
        IGmkList* list = m_gmkLists[i];
        if (list == nullptr) {
            continue;
        }
        // the route and point lists of the routed kinds read their rows with their owners'
        if ((0x0010000100C00000ULL >> i) & 1) {
            continue;
        }
        const char* kindName = getGmkKindName(s_gmkKindNames, i);
        GmkManager* manager = GmkManager::sys();
        unsigned char* fp = manager->m_bdatFp;
        if (Bdat::getMember(fp, kindName) == nullptr) {
            continue;
        }
        const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(fp, kindName, id, 7));
        if (name == nullptr || *name == '\0') {
            continue;
        }
        const char* bdatName;
        {
            GmkManager* manager = GmkManager::sys();
            mm::mtl::FixStr<256> column;
            column.format("%s_bdat", kindName);
            unsigned char* setFp = manager->m_bdatFp;
            bdatName = Bdat::getMember(setFp, column.m_str) != nullptr ? reinterpret_cast<const char*>(Bdat::getValCheck(setFp, column.m_str, id, 7)) : nullptr;
        }
        IGmkList::CreateInfo info;
        info.m_allocHandle = m_createInfo.m_allocHandle;
        info.m_param = this;
        info.m_path = "gmk/";
        info.m_path += name;
        info.m_path += ".lvb";
        if (bdatName != nullptr) {
            info.m_bdatName = bdatName;
        }
        info.m_pos = m_createInfo.m_pos;
        info.m_rotY = m_createInfo.m_rotY;
        list->create(info);
    }
}

GmkMapGimmickList::GmkMapGimmickList(unsigned int updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame), m_triggerList(-1) {}

void GmkSet::seqCreateMapBdat(float) {
    createGmkLists(m_createInfo.m_bdatId);
    m_seq = &GmkSet::seqUpdate;
}

void GmkSet::seqUpdate(float dt) {
    for (int i = 0; i < GMK_LIST_NUM; ++i) {
        if (m_gmkLists[i] != nullptr) {
            m_gmkLists[i]->update(dt);
        }
    }
}

void setDispByGmkType(GmkType type, bool disp) {
    GmkInstDispTraverserByBdatId f(0, disp);
    GmkManager::get()->traverseGmkInst(type, f);
}

void setDispByGmkTypeAndBdatId(GmkType type, int bdatId, bool disp) {
    GmkInstDispTraverserByBdatId f(bdatId, disp);
    GmkManager::get()->traverseGmkInst(type, f);
}

void setDispByGmkTypeAndGmkIdx(int gmkSetId, GmkType type, unsigned int idx, bool disp) {
    GmkSet* set = GmkManager::get()->findGmkSet(gmkSetId);
    if (set == nullptr) {
        return;
    }
    IGmkList* list = set->getGmkList(type);
    if (list == nullptr || idx >= list->getInstNum()) {
        return;
    }
    if (AGmkBase* inst = list->getInst(idx)) {
        fn_71005D3C54(*inst, false, disp);
    }
}

unsigned char* AGmkBase::getBindedBdatFp() const { return m_list->getBindedBdatFp(); }

GmkGobEventListener::~GmkGobEventListener() { gf::GfObjManager::removeListener(this); }
void GmkGobEventListener::listenerGfObj(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle, unsigned int) {
    gf::GfObjAcc acc(handle);
    AGmkBase* gmk = static_cast<AGmkBase*>(acc.getUserData(gf::GfObjUserData(0)));
    if (gmk != nullptr) {
        gmk->onGobEvent(evt, handle);
    }
}

// ---- each kind's type (its TYPE constant)
gmk::GmkType GmkAreaBgm::getGmkType() const { return TYPE; }
gmk::GmkType GmkPrecious::getGmkType() const { return TYPE; }
gmk::GmkType GmkSe::getGmkType() const { return TYPE; }
gmk::GmkType GmkSeLine::getGmkType() const { return TYPE; }
gmk::GmkType GmkEvent::getGmkType() const { return TYPE; }
gmk::GmkType GmkTutorial::getGmkType() const { return gmk::GmkType(57); }
gmk::GmkType GmkTrigger::getGmkType() const { return gmk::GmkType(52); }
gmk::GmkType GmkEnemy::getGmkType() const { return TYPE; }

bool GmkEnemy::isValid() const { return AGmkBase::isValid() && m_insts.isValid(); }

gmk::GmkType GmkRoute::getGmkType() const { return TYPE; }
gmk::GmkType GmkRoutedEnemy::getGmkType() const { return TYPE; }

bool GmkRoutedEnemy::isValid() const { return GmkRoute::isValid() && m_insts.isValid(); }

gmk::GmkType GmkRoutePoint::getGmkType() const { return gmk::GmkType(23); }
gmk::GmkType GmkNpc::getGmkType() const { return TYPE; }
gmk::GmkType GmkRoutedNpc::getGmkType() const { return TYPE; }
gmk::GmkType GmkMapObj::getGmkType() const { return TYPE; }
gmk::GmkType GmkRoutedMapObj::getGmkType() const { return TYPE; }
gmk::GmkType GmkTbox::getGmkType() const { return TYPE; }
gmk::GmkType GmkBattleLock::getGmkType() const { return TYPE; }
gmk::GmkType GmkFieldLock::getGmkType() const { return TYPE; }
gmk::GmkType GmkEffect::getGmkType() const { return TYPE; }
gmk::GmkType GmkMob::getGmkType() const { return gmk::GmkType(18); }
gmk::GmkType GmkRoutedMob::getGmkType() const { return TYPE; }
gmk::GmkType GmkLandmark::getGmkType() const { return TYPE; }
gmk::GmkType GmkCollection::getGmkType() const { return gmk::GmkType(28); }
gmk::GmkType GmkAreaWeather::getGmkType() const { return TYPE; }
gmk::GmkType GmkSalvage::getGmkType() const { return gmk::GmkType(31); }
gmk::GmkType GmkSalvageLocator::getGmkType() const { return gmk::GmkType(32); }
gmk::GmkType GmkMapGimmick::getGmkType() const { return gmk::GmkType(33); }
gmk::GmkType GmkGrave::getGmkType() const { return TYPE; }
gmk::GmkType GmkKizunaTalk::getGmkType() const { return TYPE; }
gmk::GmkType GmkJump::getGmkType() const { return TYPE; }
gmk::GmkType GmkWarp::getGmkType() const { return TYPE; }
gmk::GmkType GmkDoor::getGmkType() const { return TYPE; }
gmk::GmkType GmkElevator::getGmkType() const { return TYPE; }
gmk::GmkType GmkMapJump::getGmkType() const { return TYPE; }
gmk::GmkType GmkFieldVolume::getGmkType() const { return TYPE; }
gmk::GmkType GmkClimbing::getGmkType() const { return TYPE; }
gmk::GmkType GmkBlade::getGmkType() const { return TYPE; }
gmk::GmkType GmkDmgGimmick::getGmkType() const { return TYPE; }
gmk::GmkType GmkDmgPhantom::getGmkType() const { return gmk::GmkType(49); }
gmk::GmkType GmkDmgEffect::getGmkType() const { return gmk::GmkType(50); }
gmk::GmkType GmkDmgSe::getGmkType() const { return gmk::GmkType(51); }
gmk::GmkType GmkRoutedFootPrint::getGmkType() const { return TYPE; }
gmk::GmkType GmkRoutedFootPrintPoint::getGmkType() const { return gmk::GmkType(55); }
gmk::GmkType GmkAntiBladeArea::getGmkType() const { return TYPE; }
gmk::GmkType GmkEffectLocator::getGmkType() const { return TYPE; }
gmk::GmkType GmkSeLinePoint::getGmkType() const { return TYPE; }
gmk::GmkType GmkSquadLeader::getGmkType() const { return TYPE; }
gmk::GmkType GmkSquadMember::getGmkType() const { return TYPE; }
gmk::GmkType GmkElevatorLocator::getGmkType() const { return TYPE; }
gmk::GmkType GmkTargetPoint::getGmkType() const { return TYPE; }
gmk::GmkType GmkRoutedEnemyPoint::getGmkType() const { return gmk::GmkType(2); }

// ---- AGmkBase: its destructor is the key function (the table and its inline slots come out here)
AGmkBase::~AGmkBase() {
    m_list = nullptr;
    m_pos = nullptr;
    m_info = nullptr;
}
}  // namespace gmk

// instantiated for gmk::GmkSquad::seqInit, mm::mtl::Vector<mm::Vec3>::push_back
template void mm::mtl::Vector<mm::Vec3>::expand(unsigned long, unsigned long);

// instantiated for anm::Control::Control (not written yet), gmk::GmkSquad::seqInit
template void mm::mtl::Vector<float>::expand(unsigned long, unsigned long);

namespace gmk {

// valid while its route point list holds points
bool GmkRoute::isValid() const {
    bool valid = false;
    if (AGmkBase::isValid()) {
        IGmkList* list = getBindedRoutePointList();
        if (list != nullptr && list->getInstNum() != 0) {
            valid = true;
        }
    }
    return valid;
}

bool AGmkBase::isValid() const {
    return m_list != nullptr && m_createInfo.m_data != nullptr && m_createInfo.m_bdatInfo != nullptr;
}

void AGmkBase::dispose() {
    m_createInfo.m_version = 0;
    m_createInfo.m_data = nullptr;
    m_createInfo.m_bdatInfo = nullptr;
}

// drops what it had and keeps a copy of what it is created with
void AGmkBase::create(const CreateInfo& info) {
    dispose();
    m_createInfo = info;
}

// the original calls debugUpdateMmf here (its table's slot 10)
void AGmkBase::update(float) {
    debugUpdateMmf();
}

// asks isValid and drops the answer (the drawing itself is not in this build)
void AGmkBase::debugDraw() const {
    isValid();
}

// on event 3 the object's user data is cleared
void AGmkBase::onGobEvent(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle) {
    if (evt == gf::IGfObjListener::OBJEVT(3) && handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(handle);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
    }
}

// m_pos points at the gimmick's Xform: its scale is the third vector
float AGmkBase::getYSnapRayLength() const {
    switch (m_info->m_shape) {
    case 1:
    case 3:
        return m_pos[2].y;
    case 2:
        return m_pos[2].x;
    case 4:
        return m_pos[2].x + m_pos[2].y;
    default:
        return 1.0f;
    }
}

// snaps a point of from (its y raised by half the ray length, from the gimmick's own y when useOwnY) onto the
// ground with the pop finders' line test
static inline bool getYSnapPosForPop(mm::Vec3& pos, const mm::Vec3& from, float length);

bool AGmkBase::getPositionAppliedYSnap(mm::Vec3& out, const mm::Vec3& from, bool useOwnY) const {
    float half = getYSnapRayLength() * 0.5f;
    mm::Vec3 start;
    start.x = from.x;
    start.y = half + (useOwnY ? m_pos : &from)->y;
    start.z = from.z;
    return getYSnapPosForPop(out, start, half + half);
}

// names the gimmick: its set's row, its kind and its index in its list
void GmkAcc::CreateInfo::validate(const AGmkBase& gmk) {
    IGmkList* list = gmk.m_list;
    m_bdatId = static_cast<const GmkSet*>(list->getCreateInfo().m_param)->m_createInfo.m_bdatId;
    m_type = gmk.getGmkType();
    unsigned int num = list->getInstNum();
    for (unsigned int i = 0; i < num; i++) {
        if (list->getInst(i) == &gmk) {
            pad_8 = i;
        }
    }
}

GmkAcc::GmkAcc() : m_gmk(nullptr) {}

GmkAcc::GmkAcc(const CreateInfo& info) : m_gmk(nullptr) { create(info); }

void GmkAcc::create(const CreateInfo& info) {
    dispose();
    m_info = info;
    if (info.pad_c != 0) {
        update();
    }
    GmkAccManager* manager = GmkAccManager::sys();
    if (isValid()) {
        manager->m_list1.push_back(this);
    } else {
        manager->m_list0.push_back(this);
    }
}

// the same, from a type and row
void GmkAcc::create(const CreateInfoByBdatId& info) {
    dispose();
    m_infoByBdatId = info;
    if (info.m_flag) {
        update();
    }
    GmkAccManager* manager = GmkAccManager::sys();
    if (isValid()) {
        manager->m_list1.push_back(this);
    } else {
        manager->m_list0.push_back(this);
    }
}

GmkAcc::GmkAcc(const GmkAcc& other) : m_gmk(nullptr) {
    if (other.m_info.isValid()) {
        create(other.m_info);
    } else if (other.m_infoByBdatId.isValid()) {
        create(other.m_infoByBdatId);
    }
}

void GmkAcc::dispose() {
    GmkAccManager* manager = GmkAccManager::sys();
    if (manager != nullptr) {
        manager->removeGmkAcc(this);
    }
    m_gmk = nullptr;
    m_infoByBdatId = CreateInfoByBdatId();
    m_info = CreateInfo();
}

bool GmkAcc::isValid() const {
    if (m_gmk != nullptr) {
        return m_gmk->isValid();
    }
    return false;
}

// finds the gimmick again: by its set's row, kind and index, else by its kind and BDAT row
void GmkAcc::update() {
    if (GmkAccManager::sys() == nullptr || isValid()) {
        return;
    }
    if (m_info.isValid()) {
        AGmkBase* gmk = nullptr;
        GmkType type = m_info.m_type;
        GmkManager* manager = GmkManager::sys();
        unsigned int idx = m_info.pad_8;
        GmkSet* set = manager->findGmkSet(m_info.m_bdatId);
        if (set != nullptr) {
            IGmkList* list = set->getGmkList(type);
            if (list != nullptr && list->getInstNum() > idx) {
                gmk = list->getInst(idx);
            }
        }
        m_gmk = gmk;
    } else if (m_infoByBdatId.isValid()) {
        m_gmk = GmkManager::sys()->findFirstGmkInstByBdatId(m_infoByBdatId.m_type, m_infoByBdatId.m_bdatId);
    }
}

// unlinks a named access from the list it is in (m_list1 while it reaches a valid gimmick)
void GmkAccManager::removeGmkAcc(GmkAcc* acc) {
    if (acc == nullptr) {
        return;
    }
    if (!acc->m_info.isValid() && !acc->m_infoByBdatId.isValid()) {
        return;
    }
    if (acc->isValid()) {
        m_list1.remove(acc);
    } else {
        m_list0.remove(acc);
    }
}

// the accesses it still holds lose their gimmick
GmkAccManager::~GmkAccManager() {
    for (::mm::mtl::IntrusiveList<GmkAcc>::iterator it = m_list1.begin(); it != m_list1.end(); ++it) {
        it->m_gmk = nullptr;
    }
    for (::mm::mtl::IntrusiveList<GmkAcc>::iterator it = m_list0.begin(); it != m_list0.end(); ++it) {
        it->m_gmk = nullptr;
    }
}

// the accesses that reach a valid gimmick again move to m_list1
void GmkAccManager::update() {
    for (::mm::mtl::IntrusiveList<GmkAcc>::iterator it = m_list0.begin(); it != m_list0.end(); ++it) {
        it->update();
        if (it->isValid()) {
            GmkAcc* acc = it.operator->();
            it = m_list0.erase(it);
            --it;
            m_list1.push_back(*acc);
        }
    }
}

// the accesses reaching a gimmick of that list lose it; the valid ones move to m_list0
void GmkAccManager::invalidateAccs(const IGmkList& list) {
    if (sys() == nullptr) {
        return;
    }
    for (::mm::mtl::IntrusiveList<GmkAcc>::iterator it = sys()->m_list0.begin(); it != sys()->m_list0.end(); ++it) {
        if (it->m_gmk != nullptr && it->m_gmk->m_list == &list) {
            it->m_gmk = nullptr;
        }
    }
    list.getGmkType();
    for (::mm::mtl::IntrusiveList<GmkAcc>::iterator it = sys()->m_list1.begin(); it != sys()->m_list1.end(); ++it) {
        if (it->m_gmk->m_list == &list) {
            it->m_gmk = nullptr;
            GmkAcc* acc = it.operator->();
            it = sys()->m_list1.erase(it);
            --it;
            sys()->m_list0.push_back(*acc);
        }
    }
}

void disposeGobInst(gf::GF_OBJ_HANDLE* handle, float time) {
    gf::GfObjAcc acc(handle);
    if (acc.getObj() != nullptr && !acc.isDestroy() && !acc.testFlag(17)) {
        gf::SCOM_DESTROY_GAME_OBJ::create(handle, time, 0);
    }
}

bool GmkCamera::CreateInfo::validateTransform(gf::GF_OBJ_HANDLE* handle) {
    gf::GfObjAcc acc(handle);
    if (!acc.isValidTransform()) {
        return false;
    }
    const fw::Transform& transform = acc.getWorldTransformNoSync();
    const mm::Quat& q = transform.rotation;
    float x2 = q.x + q.x;
    float y2 = q.y + q.y;
    float z2 = q.z + q.z;
    float xx = q.x * x2;
    float xz = q.x * z2;
    float yy = q.y * y2;
    float wy = q.w * y2;
    float m20 = xz + wy;
    float m22 = 1.0f - (xx + yy);
    float rotY = atan2f(m20, m22);
    m_hasTransform = true;
    m_pos = transform.position;
    m_rotY = rotY;
    return true;
}

bool GmkCamera::CreateInfo::validateTransform(unsigned short lodId) {
    mm::Mat44 mtx;
    if (!gf::GfFieldLod::sys()->findTransform(mtx, lodId)) {
        return false;
    }
    mm::Vec3 pos = mtx.getTrans();
    float rotY = atan2f(mtx.m[2][0], mtx.m[2][2]);
    m_hasTransform = true;
    m_pos = pos;
    m_rotY = rotY;
    return true;
}

GmkCamera::GmkCamera(const CreateInfo* info) : m_camera(nullptr), m_seq(nullptr) {
    if (info != nullptr) {
        create(*info);
    }
}

void GmkCamera::create(const CreateInfo& info) {
    dispose();
    m_info = info;
    if (info.m_hasTransform) {
        m_camera = gf::GimmickCamera::create(info.m_name.m_str, info.m_pos, info.m_rotY);
    } else {
        m_camera = gf::GimmickCamera::create(info.m_name.m_str);
    }
    static_cast<gf::GimmickCamera*>(m_camera.get())->setAuto(info.pad_105);
    m_seq = &GmkCamera::seqWaitToLoaded;
    gf::GfGameManager::setStopMainMenuOpenForGimmick(true);
}

bool GmkCamera::isLoaded() const { return static_cast<gf::GimmickCamera*>(m_camera.get())->isLoaded(); }

bool GmkCamera::isEnd() const {
    if (m_camera.get() == nullptr) {
        return true;
    }
    return static_cast<gf::GimmickCamera*>(m_camera.get())->isPlayEnd();
}

// once the camera is loaded: an auto camera is pushed (after GfPlayFactory::createGmkCamera when pad_106 is set);
// then waits for its end
void GmkCamera::seqWaitToLoaded(float) {
    if (!isLoaded()) {
        return;
    }
    if (m_info.pad_105) {
        if (m_info.pad_106 && !gf::GfPlayFactory::createGmkCamera(m_camera)) {
            return;
        }
        fw::CameraManager::sys()->m_layers[0].push(m_camera, 0.0f);
        switch (m_info.m_attr) {
        case 1:
            setDispOfParty(false, false);
            break;
        case 2:
            setDispOfParty(false, true);
            break;
        }
    }
    m_seq = &GmkCamera::seqWaitToEnd;
}

void GmkCamera::update(float dt) {
    if (m_info.m_name.length() > 0 && m_seq) {
        (this->*m_seq)(dt);
    }
}

void GmkCamera::play() { m_seq = &GmkCamera::seqWaitToPlay; }

// pushes the camera (after GfPlayFactory::createGmkCamera when pad_106 is set) and plays it, then waits for its end
void GmkCamera::seqWaitToPlay(float) {
    if (m_info.pad_106 && !gf::GfPlayFactory::createGmkCamera(m_camera)) {
        return;
    }
    fw::CameraManager::sys()->m_layers[0].push(m_camera, 0.0f);
    static_cast<gf::GimmickCamera*>(m_camera.get())->play();
    switch (m_info.m_attr) {
    case 1:
        setDispOfParty(false, false);
        break;
    case 2:
        setDispOfParty(false, true);
        break;
    }
    m_seq = &GmkCamera::seqWaitToEnd;
}

// once the camera has played: shows the party again (by m_attr), pops and releases the camera
void GmkCamera::seqWaitToEnd(float) {
    if (!static_cast<gf::GimmickCamera*>(m_camera.get())->isPlayEnd()) {
        return;
    }
    switch (m_info.m_attr) {
    case 1:
        setDispOfParty(true, false);
        break;
    case 2:
        setDispOfParty(true, true);
        break;
    }
    m_seq = nullptr;
    if (m_camera.get() != nullptr) {
        fw::CameraManager::sys()->m_layers[0].pop(m_camera, 0.0f);
        m_camera = nullptr;
    }
    gf::GfGameManager::setStopMainMenuOpenForGimmick(false);
}

// the entry's matrix: rotation then translation, scaled first unless noScale (AGmkBase::getMatrix calls it,
// TGmkList::createGmk inlines it)
mm::Mat44& Xform::toMatrix(mm::Mat44& mat, bool noScale) const {
    mm::Mat44 trans;
    trans.setTrans(m_pos);
    mm::Mat44 rot;
    rot.setRotXYZ(m_rot);
    if (noScale) {
        mat = rot * trans;
    } else {
        mm::Mat44 scale;
        scale.setScale(m_scale);
        mat = scale * rot * trans;
    }
    return mat;
}

// ---- kinds whose isValid/dispose/destructor are the base pattern
bool GmkTutorial::isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }
bool GmkTrigger::isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }
bool GmkRoutePoint::isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }
bool GmkBattleLock::isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }
bool GmkAreaWeather::isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }
bool GmkSalvageLocator::isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }
bool GmkFieldVolume::isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }
void GmkDmgPhantom::dispose() {
    m_phantom.dispose();
    AGmkBase::dispose();
}

GmkDmgPhantomManager::GmkDmgPhantomManager() : pad_38(false) {
    gf::GfObjManager::addListener(this, gf::IGfObjListener::OBJEVT(0));
    gf::GfEvent::addEventCallback(this);
    create();
}

void GmkDmgPhantomManager::create() {
    m_targets.destroy();
    m_targets.setAllocator(gf::getAllocator(gf::ALLOCATOR(0)));
    int capacity = gf::GfObjManager::getGfObjCapacity(5);
    m_targets.reserve(capacity > 0 ? static_cast<unsigned int>(capacity + 3) : 3u);
}

GmkDmgPhantomManager::~GmkDmgPhantomManager() {
    m_targets.destroy();
    gf::GfEvent::removeEventCallback(this);
    gf::GfObjManager::removeListener(this);
}

void GmkDmgPhantomManager::addTargetInfo(gf::GF_OBJ_HANDLE* handle) {
    for (const GmkDmgPhantomTargetInfo& info : m_targets) {
        if (info.m_gob == handle) {
            return;
        }
    }
    if (m_targets.size() != m_targets.capacity()) {
        m_targets.push_back(GmkDmgPhantomTargetInfo(handle));
    }
}

// whether an object of the given type is one the damage phantoms watch: the players standing alone, and enemies
// with the flag (inlined; the name is not the original's)
static bool isDmgPhantomTarget(gf::GF_OBJ_HANDLE* handle, unsigned int type) {
    gf::GfObjAcc acc(handle);
    if (type == 3 || type == 4) {
        unsigned int index = mm::mtl::PtrSingleton<gf::GfGamePlayerFormation>::sys()->findPlayer(handle);
        if (index == static_cast<unsigned int>(-1)) {
            return false;
        }
        return mm::mtl::PtrSingleton<gf::GfGamePlayerFormation>::sys()->m_players[index].m_standalone;
    }
    if (type != 5) {
        return false;
    }
    gf::DataParamAcc param(handle);
    const gf::SDataEnemy* enemy = param.getSDataEnemy();
    if (enemy == nullptr) {
        return false;
    }
    return enemy->m_fieldDamage;
}

void GmkDmgPhantomManager::listenerGfObj(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle, unsigned int type) {
    if (!isDmgPhantomTarget(handle, type)) {
        return;
    }
    switch (evt) {
    case gf::IGfObjListener::OBJEVT(2):
        addTargetInfo(handle);
        break;
    case gf::IGfObjListener::OBJEVT(3):
        if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            for (GmkDmgPhantomTargetInfo* it = m_targets.begin(); it != m_targets.end(); ++it) {
                if (it->m_gob == handle) {
                    m_targets.erase(it);
                    break;
                }
            }
        }
        break;
    }
}

void GmkDmgPhantomManager::gevPartyMover(gf::GF_OBJ_HANDLE* handle, bool mover) {
    int type = gf::GfObjUtil::getObjType(handle);
    if (type == 3 || type == 4) {
        if (mover) {
            if (gf::GfGameManager::isPartyMover(handle)) {
                addTargetInfo(handle);
            }
        } else if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            for (GmkDmgPhantomTargetInfo* it = m_targets.begin(); it != m_targets.end(); ++it) {
                if (it->m_gob == handle) {
                    m_targets.erase(it);
                    break;
                }
            }
        }
    }
}

GmkDmgPhantom::~GmkDmgPhantom() { dispose(); }

bool GmkDmgPhantom::isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }

GmkPhantomSimple::~GmkPhantomSimple() { dispose(); }
bool GmkDmgEffect::isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }
bool GmkDmgSe::isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }
bool GmkRoutedFootPrintPoint::isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }
bool GmkEffectLocator::isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }
bool GmkSeLinePoint::isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }
bool GmkSquadLeader::isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }
bool GmkSquadMember::isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }
bool GmkElevatorLocator::isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }
bool GmkTargetPoint::isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }
void GmkRoute::dispose() { AGmkBase::dispose(); }
void GmkRoutePoint::dispose() { AGmkBase::dispose(); }
void GmkSquadLeader::dispose() { AGmkBase::dispose(); }
void GmkSquadMember::dispose() { AGmkBase::dispose(); }

// the colour is filled member by member (the original stores r alone, then g and b as one pair, then a)
void GmkRoutePoint::debugDraw() const {
    AGmkBase::debugDraw();
    if (isValid()) {
        mm::Col4 col;
        const mm::Col3& cyan = mm::Col3::cyan;
        col.r = cyan.r;
        col.g = cyan.g;
        col.b = cyan.b;
        col.a = 0.8f;
        const Data* data = getData();
        fw::debug::drawLine(data->m_pos + data->pad_10, data->m_pos - data->pad_10, col);
    }
}
// kinds whose create is the base one
void GmkRoute::create(const CreateInfo& info) { AGmkBase::create(info); }

GmkRouteNavi::CreateInfo::CreateInfo(const GmkRoute* route)
    : m_bdatId(-1), m_type(GmkType(0x40)), m_routeIndx(0), m_offset(0.0f), pad_10(1.0f), pad_14(2.0f), pad_18(0x10),
      m_initResult(nullptr) {
    if (route != nullptr) {
        IGmkList* list = route->m_list;
        m_bdatId = static_cast<const GmkSet*>(list->getCreateInfo().m_param)->m_createInfo.m_bdatId;
        m_type = route->getGmkType();
        unsigned int num = list->getInstNum();
        for (unsigned int i = 0; i < num; i++) {
            if (list->getInst(i) == route) {
                m_routeIndx = i;
            }
        }
    }
}

bool GmkRouteNavi::CreateInfo::isValid() const {
    if (m_bdatId > 0) {
        switch (m_type) {
        case GmkType(1):
        case GmkType(4):
        case GmkType(7):
        case GmkType(19):
        case GmkType(22):
            return pad_18 != 0;
        default:
            break;
        }
    }
    return false;
}

GmkRouteNavi::GmkRouteNavi(const CreateInfo* info)
    : pad_68(1.0f), pad_6c(2.0f), m_seq(nullptr), pad_80(false), pad_90(0.0f, 0.0f, 0.0f), pad_a0(0), pad_a4(false),
      pad_a8(0), pad_ac(0) {
    if (info != nullptr) {
        create(*info);
    }
}

// a quadratic curve through the corner at the point: from the radius (the route's pad_8, at most half of each side)
// before it to the radius after it
bool GmkRouteNavi::getPosDirOnCurve(mm::Vec3& pos, mm::Vec3& dir, unsigned int indx, float t) const {
    const GmkRoute* route = getRoute();
    if (route == nullptr) {
        return false;
    }
    int step = pad_a4 ? -1 : 1;
    bool reverse = pad_a4;
    int prev = wrapPointIndx(indx - step, reverse);
    int next = wrapPointIndx(step + indx, reverse);
    const GmkRoutePoint* from = route->getRoutePoint(prev);
    const GmkRoutePoint* corner = route->getRoutePoint(indx);
    const GmkRoutePoint* to = route->getRoutePoint(next);
    if (from == nullptr || corner == nullptr || to == nullptr) {
        return false;
    }
    const GmkRoutePoint::Data* fromData = from->getData();
    const GmkRoutePoint::Data* cornerData = corner->getData();
    const GmkRoutePoint::Data* toData = to->getData();
    float offset = getPointOffset();
    mm::Vec3 a(offset * fromData->pad_10.x, offset * fromData->pad_10.y, offset * fromData->pad_10.z);
    a += fromData->m_pos;
    mm::Vec3 b(offset * cornerData->pad_10.x, offset * cornerData->pad_10.y, offset * cornerData->pad_10.z);
    b += cornerData->m_pos;
    mm::Vec3 c(offset * toData->pad_10.x, offset * toData->pad_10.y, offset * toData->pad_10.z);
    c += toData->m_pos;
    mm::Vec3 in = b - a;
    mm::Vec3 out = c - b;
    float inLen = in.length();
    float outLen = out.length();
    float radius = route->getData()->pad_8;
    float inRadius = radius < inLen * 0.5 ? radius : inLen * 0.5f;
    float outRadius = radius < outLen * 0.5 ? radius : outLen * 0.5f;
    mm::Vec3 begin = b - in * (inRadius / inLen);
    mm::Vec3 end = b + out * (outRadius / outLen);
    mm::Vec3 q0 = begin + (b - begin) * t;
    mm::Vec3 q1 = b + (end - b) * t;
    dir = q1 - q0;
    pos = q0 + dir * t;
    return true;
}

bool GmkRouteNavi::getPosDirOnLine(mm::Vec3& pos, mm::Vec3& dir, unsigned int indx, float t) const {
    const GmkRoute* route = getRoute();
    if (route == nullptr) {
        return false;
    }
    bool reverse = pad_a4;
    int prev = wrapPointIndx(indx - (pad_a4 ? -1 : 1), reverse);
    const GmkRoutePoint* from = route->getRoutePoint(prev);
    const GmkRoutePoint* to = route->getRoutePoint(indx);
    if (from == nullptr || to == nullptr) {
        return false;
    }
    const GmkRoutePoint::Data* fromData = from->getData();
    const GmkRoutePoint::Data* toData = to->getData();
    float offset = getPointOffset();
    mm::Vec3 a(offset * fromData->pad_10.x + fromData->m_pos.x, offset * fromData->pad_10.y + fromData->m_pos.y,
               offset * fromData->pad_10.z + fromData->m_pos.z);
    mm::Vec3 b(offset * toData->pad_10.x + toData->m_pos.x, offset * toData->pad_10.y + toData->m_pos.y,
               offset * toData->pad_10.z + toData->m_pos.z);
    dir = b - a;
    pos = a + dir * t;
    return true;
}

void GmkRouteNavi::update(const UpdateInfo& info) {
    if (isValid() && m_seq) {
        (this->*m_seq)(info);
    }
}

void GmkRouteNavi::updateNextPos() {
    UpdateInfo info;
    info.m_pos.x = pad_90.x;
    info.m_pos.y = pad_90.y;
    info.m_pos.z = pad_90.z;
    update(info);
}

bool GmkRouteNavi::isArrived(const mm::Vec3& pos, const mm::Vec3& target) const {
    mm::Vec3 d = pos - target;
    if (pad_6c < d.y) {
        return false;
    }
    float distSq = d.x * d.x + d.z * d.z;
    if (pad_68 * pad_68 < distSq) {
        return false;
    }
    return true;
}

void GmkRouteNavi::updateNextPointIndx() {
    if (pad_a4) {
        pad_a0 = wrapPointIndx(pad_a0 - 1, pad_a4);
    } else {
        pad_a0 = wrapPointIndx(pad_a0 + 1, pad_a4);
    }
}

void GmkRouteNavi::create(const CreateInfo& info) {
    dispose();
    m_info = info;
    pad_68 = info.pad_10;
    pad_6c = info.pad_14;
    pad_a0 = 1;
    pad_a8 = 0;
    {
        GmkAcc::CreateInfo accInfo;
        accInfo.m_bdatId = info.m_bdatId;
        accInfo.m_type = info.m_type;
        accInfo.pad_8 = info.m_routeIndx;
        m_acc.create(accInfo);
    }
    if (isValid()) {
        unsigned int flags = getRoute()->getData()->m_flags;
        if ((flags & 6) == 6) {
            pad_a4 = ml::mtRandf1() > 0.5f;
        } else if (flags & 2) {
            pad_a4 = false;
        } else if (flags & 4) {
            pad_a4 = true;
        }
    }
    if (info.m_initResult != nullptr) {
        initAtRandom(*info.m_initResult);
    } else {
        m_seq = &GmkRouteNavi::seqInit;
    }
}

void GmkRouteNavi::dispose() {
    pad_ac = 0;
    pad_a4 = false;
    pad_a0 = 0;
    pad_80 = false;
    m_info = CreateInfo();
}

unsigned int GmkRoute::getRoutePointNum() const { return getData()->m_pointEnd - getData()->m_pointBegin; }
bool GmkRoute::isClosed() const { return getData()->m_flags & 1; }

const GmkRoutePoint* GmkRoute::getRoutePoint(unsigned int index) const {
    const IGmkList* list = getBindedRoutePointList();
    if (list != nullptr) {
        unsigned int pointIdx = getData()->m_pointBegin + index;
        if (list->getInstNum() > pointIdx) {
            return static_cast<const GmkRoutePoint*>(list->getInst(pointIdx));
        }
    }
    return nullptr;
}

bool GmkRoute::getRoutePointPos(mm::Vec3& pos, unsigned int index) const {
    const GmkRoutePoint* point = getRoutePoint(index);
    if (point != nullptr && point->isValid()) {
        pos = point->getData()->m_pos;
        return true;
    }
    return false;
}

void GmkRoute::debugDraw() const {
    AGmkBase::debugDraw();
    if (isValid()) {
        debugDrawRoute(mm::Col4::yellow);
    }
}

// a squad member other than the leader keeps its place in the squad; any other object takes the first free
// navigator
bool GmkRoutedEnemy::PopXformFinder::onPopGob(gf::GF_OBJ_HANDLE* handle) const {
    {
        gf::GfObjAcc acc(handle);
        if (gf::GfObj* obj = acc.getObj()) {
            if (gf::GfComBehaviorEnemy* behavior = obj->getComponent<gf::GfComBehaviorEnemy>(6)) {
                const GmkSquadNavi& navi = behavior->m_field.m_squadNavi;
                if (navi.isInSquad() && navi.m_index != 0) {
                    return true;
                }
            }
        }
    }
    if (GmkRouteNavi* navi = m_gmk->findRouteNavi(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1))) {
        m_gmk->bindRouteNavi(handle, *navi);
        return true;
    }
    return false;
}

void GmkRoutedEnemy::bindRouteNavi(gf::GF_OBJ_HANDLE* handle, GmkRouteNavi& navi) {
    if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        for (std::pair<gf::GF_OBJ_HANDLE*, GmkRouteNavi>* it = m_navis.begin(); it != m_navis.end(); ++it) {
            if (it->first == handle) {
                it->first = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
                it->second.dispose();
                break;
            }
        }
    }
    for (std::pair<gf::GF_OBJ_HANDLE*, GmkRouteNavi>* it = m_navis.begin(); it != m_navis.end(); ++it) {
        if (&it->second == &navi) {
            it->first = handle;
            return;
        }
    }
}

// with no row only disposes; else creates the route and the insts from the row's distances (the list's defaults
// where the row has none)
void GmkRoutedEnemy::create(const AGmkBase::CreateInfo& info) {
    if (info.m_bdatInfo == nullptr) {
        dispose();
        return;
    }
    GmkRoute::create(info);
    GmkEnemyInsts::CreateInfo createInfo;
    const GmkEnemy::BdatInfo* bdat = static_cast<const GmkEnemy::BdatInfo*>(info.m_bdatInfo);
    const GmkRoutedEnemyList* list = static_cast<const GmkRoutedEnemyList*>(m_list);
    createInfo.m_gmk = this;
    createInfo.m_bdatFp = list->getBindedBdatFp();
    createInfo.m_bdatId = m_createInfo.m_bdatId;
    createInfo.m_popHeight = bdat->m_dispH != 0 ? bdat->m_dispH : list->m_bdatInfo.m_dispH;
    createInfo.m_depopHeight = createInfo.m_popHeight + list->m_bdatInfo.m_releaseH;
    createInfo.m_popRange = bdat->m_dispR != 0 ? bdat->m_dispR : list->m_bdatInfo.m_dispR;
    createInfo.m_depopRange = createInfo.m_popRange + list->m_bdatInfo.m_releaseR;
    createInfo.m_repopTime = list->m_bdatInfo.m_repopTime * 60.0f;
    m_insts.create(createInfo);
}

// the insts pop and depop by the route position nearest to the player
void GmkRoutedEnemy::update(float dt) {
    AGmkBase::update(dt);
    if (isValid() && isPlayerExist()) {
        mm::Vec3 pos;
        if (getNearestPos(pos, getPlayerPos())) {
            GmkEnemyInsts::UpdateInfo updateInfo;
            PopXformFinder finder(this);
            updateInfo.m_dt = dt;
            updateInfo.m_pos = &pos;
            updateInfo.m_finder = &finder;
            if (m_insts.isValid()) {
                m_insts.updatePopDepopCond(updateInfo);
                if (m_insts.m_seq) {
                    (m_insts.*m_insts.m_seq)(updateInfo);
                }
            }
        }
    }
}

void GmkRoutedEnemy::createRouteNavis(unsigned int num) {
    if (m_navis.size() != 0) {
        m_navis.destroy();
    }
    m_navis.setAllocator(gf::getAllocator(gf::ALLOCATOR(0)));
    m_navis.reserve(num);
    m_navis.resize(num);
    if (m_navis.size() != 0) {
        for (std::pair<gf::GF_OBJ_HANDLE*, GmkRouteNavi>* it = m_navis.begin(); it != m_navis.end(); ++it) {
            it->first = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        }
    }
}

// the route point list of each routed kind in the gimmick set that made its list (GmkSet::createGmkLists passes the
// set as the list's CreateInfo::m_param); kinds 5, 8 and 20 have no class in the headers yet
IGmkList* GmkRoutedEnemy::getBindedRoutePointList() const {
    return static_cast<const GmkSet*>(m_list->getCreateInfo().m_param)->m_gmkLists[GmkRoutedEnemyPoint::TYPE];
}

GmkRouteNavi* GmkRoutedEnemy::findRouteNavi(gf::GF_OBJ_HANDLE* handle) const {
    for (std::pair<gf::GF_OBJ_HANDLE*, GmkRouteNavi>* it = m_navis.begin(); it != m_navis.end(); ++it) {
        if (it->first == handle) {
            return &it->second;
        }
    }
    return nullptr;
}

void GmkRoutedEnemy::onEnemyDead(gf::GF_OBJ_HANDLE* handle) {
    if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        for (std::pair<gf::GF_OBJ_HANDLE*, GmkRouteNavi>* it = m_navis.begin(); it != m_navis.end(); ++it) {
            if (it->first == handle) {
                it->first = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
                it->second.dispose();
                break;
            }
        }
    }
    m_insts.onEnemyDead(handle);
}

void GmkRoutedEnemy::onGobEvent(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle) {
    AGmkBase::onGobEvent(evt, handle);
    if (evt == gf::IGfObjListener::OBJEVT(3)) {
        if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            for (std::pair<gf::GF_OBJ_HANDLE*, GmkRouteNavi>* it = m_navis.begin(); it != m_navis.end(); ++it) {
                if (it->first == handle) {
                    it->first = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
                    break;
                }
            }
        }
        m_insts.m_popInfo.removeGobInst(handle, false);
        if (m_insts.m_popInfo.getGobInstNum() == 0) {
            m_insts.pad_159 = 0;
        }
    }
}
gf::GF_OBJ_HANDLE* GmkNpc::getGobInst() const {
    if (m_npcIdInfo == nullptr) {
        return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    gf::GF_OBJ_HANDLE* handle = m_npcIdInfo->m_handle;
    const void* owner = nullptr;
    if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(handle);
        if (acc.m_obj != nullptr && !acc.isDestroy() && !acc.testFlag(0x11) && acc.getObj() != nullptr) {
            owner = acc.getUserData(gf::GfObjUserData(0));
        }
    }
    return this == owner ? handle : reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
}

bool GmkNpc::isPopCondMatchedExceptDist() const {
    if (m_npcIdInfo == nullptr || m_npcIdInfo->m_gmk != static_cast<const AGmkNpc*>(this)) {
        return false;
    }
    return isPopCondMatched();
}

// the NPC ids setDispSpecified keeps hidden unless asked to show them (the name is not the original's)
static inline bool isDispSpecifiedHiddenNpc(unsigned short npcId) {
    switch (npcId) {
    case 0xd20:
    case 0xd21:
    case 0xd22:
    case 0xd23:
    case 0xd75:
    case 0xdf1:
    case 0xe3b:
    case 0xe3c:
    case 0xe3d:
    case 0xe3e:
    case 0xe3f:
    case 0xe40:
    case 0xe41:
        return true;
    }
    return false;
}

void GmkNpc::setDispSpecified(bool disp) const {
    if (!isValid()) {
        return;
    }
    unsigned char* fp = getBindedBdatFp();
    pad_69 = disp || !isDispSpecifiedHiddenNpc(Bdat::getValCheck(fp, "NpcID", getBindedBdatId(), 2));
    validateDisp();
}

bool GmkNpc::isPopCondMatched() const {
    if (isValid()) {
        const BdatInfo* info = static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo);
        if (gf::GfGameManager::isBattle() && info->m_battleReaction == 0) {
            return false;
        }
        return info->isPopCommonCondMatched(*this);
    }
    return false;
}

bool GmkNpc::isDepopCondMatched() const {
    if (isValid()) {
        return !static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo)->isPopCommonCondMatched(*this);
    }
    return false;
}

// whether the interest position lies within the row's Visible_XZ / Visible_Y distances of pos (the name is not the original's)
template <class T>
static inline bool isInsideVisibleDist(const mm::Vec3& pos, const T* info) {
    if (!isInterestPosExist()) {
        return false;
    }
    const mm::Vec3& interest = getInterestPos();
    float dy = interest.y - pos.y;
    if (info->m_visibleYSq < dy * dy) {
        return false;
    }
    float dx = interest.x - pos.x;
    float dz = interest.z - pos.z;
    float xzSq = dx * dx + dz * dz;
    return !(info->m_visibleXZSq < xzSq);
}

// whether the interest position lies beyond the row's Invisible_XZ / Invisible_Y distances of pos (the name is not the original's)
template <class T>
static inline bool isOutsideInvisibleDist(const mm::Vec3& pos, const T* info) {
    if (!isInterestPosExist()) {
        return true;
    }
    const mm::Vec3& interest = getInterestPos();
    float dy = interest.y - pos.y;
    if (info->m_invisibleYSq < dy * dy) {
        return true;
    }
    float dx = interest.x - pos.x;
    float dz = interest.z - pos.z;
    float xzSq = dx * dx + dz * dz;
    return info->m_invisibleXZSq < xzSq;
}

bool GmkNpc::isPopDistCondMatched() const {
    if (isValid()) {
        const GmkNpc::BdatInfo* info = static_cast<const GmkNpc::BdatInfo*>(m_createInfo.m_bdatInfo);
        return isInsideVisibleDist(*m_pos, info);
    }
    return false;
}

bool GmkNpc::isDepopDistCondMatched() const {
    if (isValid()) {
        const GmkNpc::BdatInfo* info = static_cast<const GmkNpc::BdatInfo*>(m_createInfo.m_bdatInfo);
        return isOutsideInvisibleDist(*m_pos, info);
    }
    return false;
}

// m_pos points at the gimmick's Xform: its position, then its rotation
bool GmkNpc::findPopPosRot(mm::Vec3& pos, mm::Vec3& rot) const {
    pos = m_pos[0];
    rot = m_pos[1];
    return true;
}

void GmkNpc::bindToGameObj(gf::GF_OBJ_HANDLE* handle) const {
    {
        gf::GfObjAcc acc(handle);
        acc.setUserData(gf::GfObjUserData(0), reinterpret_cast<unsigned long>(this));
    }
    gf::GfObjAcc acc(handle);
    gf::GfObj* obj = acc.getObj();
    if (obj != nullptr && !acc.isDestroy() && !acc.testFlag(0x11)) {
        if (gf::GfComBehaviorNpc* behavior = obj->getComponent<gf::GfComBehaviorNpc>(6)) {
            behavior->validateBindedGmkInstInfo(true);
        }
    }
}

void GmkNpc::onGobEvent(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle) {
    AGmkBase::onGobEvent(evt, handle);
    if (evt == gf::IGfObjListener::OBJEVT(3)) {
        unbindToGameObj(handle);
        GmkNpcIdInfo* info = m_npcIdInfo;
        if (info->m_handle == handle) {
            info->disposeGobInst();
        }
    }
}

gf::GF_OBJ_HANDLE* GmkRoutedNpc::getGobInst() const {
    if (m_npcIdInfo == nullptr) {
        return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    gf::GF_OBJ_HANDLE* handle = m_npcIdInfo->m_handle;
    const void* owner = nullptr;
    if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(handle);
        if (acc.m_obj != nullptr && !acc.isDestroy() && !acc.testFlag(0x11) && acc.getObj() != nullptr) {
            owner = acc.getUserData(gf::GfObjUserData(0));
        }
    }
    return this == owner ? handle : reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
}

bool GmkRoutedNpc::isPopCondMatchedExceptDist() const {
    if (m_npcIdInfo == nullptr || m_npcIdInfo->m_gmk != static_cast<const AGmkNpc*>(this)) {
        return false;
    }
    return isPopCondMatched();
}

void GmkRoutedNpc::dispose() {
    if (m_navi != nullptr) {
        delete m_navi;
        m_navi = nullptr;
    }
    GmkRoute::dispose();
}

IGmkList* GmkRoutedNpc::getBindedRoutePointList() const {
    return static_cast<const GmkSet*>(m_list->getCreateInfo().m_param)->m_gmkLists[5];
}

bool GmkRoutedNpc::isPopCondMatched() const {
    if (isValid()) {
        return static_cast<const GmkNpc::BdatInfo*>(m_createInfo.m_bdatInfo)->isPopCommonCondMatched(*this);
    }
    return false;
}

bool GmkRoutedNpc::isDepopCondMatched() const {
    if (isValid()) {
        return !static_cast<const GmkNpc::BdatInfo*>(m_createInfo.m_bdatInfo)->isPopCommonCondMatched(*this);
    }
    return false;
}

bool GmkRoutedNpc::isPopDistCondMatched() const {
    if (isValid() && isPlayerExist()) {
        mm::Vec3 pos;
        if (getNearestPos(pos, getPlayerPos())) {
            const GmkNpc::BdatInfo* info = static_cast<const GmkNpc::BdatInfo*>(m_createInfo.m_bdatInfo);
            return isInsideVisibleDist(pos, info);
        }
    }
    return false;
}

bool GmkRoutedNpc::isDepopDistCondMatched() const {
    if (isValid() && isPlayerExist()) {
        mm::Vec3 pos;
        if (getNearestPos(pos, getPlayerPos())) {
            const GmkNpc::BdatInfo* info = static_cast<const GmkNpc::BdatInfo*>(m_createInfo.m_bdatInfo);
            return isOutsideInvisibleDist(pos, info);
        }
    }
    return false;
}

void GmkRoutedNpc::debugDraw() const {
    if (isValid()) {
        bool matched = static_cast<const GmkNpc::BdatInfo*>(m_createInfo.m_bdatInfo)->isPopCommonCondMatched(*this);
        if (isValid()) {
            if (matched) {
                debugDrawRoute(mm::Col4(mm::Col4::yellow));
            } else {
                debugDrawRoute(mm::Col4(mm::Col4::gray));
            }
        }
    }
}

void GmkRoutedNpc::bindToGameObj(gf::GF_OBJ_HANDLE* handle) const {
    {
        gf::GfObjAcc acc(handle);
        acc.setUserData(gf::GfObjUserData(0), reinterpret_cast<unsigned long>(this));
    }
    gf::GfObjAcc acc(handle);
    if (gf::GfObj* obj = acc.getObj()) {
        if (gf::GfComBehaviorNpc* behavior = obj->getComponent<gf::GfComBehaviorNpc>(6)) {
            behavior->validateBindedGmkInstInfo(true);
        }
    }
}

// keeps the game object's last world position and rotation, then clears its user data
void GmkRoutedNpc::unbindToGameObj(gf::GF_OBJ_HANDLE* handle) const {
    {
        gf::GfObjAcc acc(handle);
        if (acc.isValidTransform()) {
            fw::Transform transform = acc.getWorldTransformNoSync();
            pad_80 = transform.position;
            pad_90 = transform.rotation;
        }
    }
    if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(handle);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
    }
}

void GmkRoutedNpc::onGobEvent(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle) {
    AGmkBase::onGobEvent(evt, handle);
    if (evt == gf::IGfObjListener::OBJEVT(3)) {
        unbindToGameObj(handle);
        pad_78 = 1;
        GmkNpcIdInfo* info = m_npcIdInfo;
        if (info->m_handle == handle) {
            info->disposeGobInst();
        }
    }
}

void GmkRoutedNpc::validateDisp() const {
    gf::GF_OBJ_HANDLE* handle = getGobInst();
    if (handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    bool disp;
    if (pad_79) {
        // the original calls getGmkType here and drops its answer
        getGmkType();
        disp = true;
    } else {
        disp = false;
    }
    gf::GfObjAcc acc(handle);
    if (acc.m_obj != nullptr) {
        acc.setDisp(gf::OBJDISP(8), disp);
    }
}

void GmkRoutedNpcList::create(const IGmkList::CreateInfo& info) {
    TGmkList::create(info);
}
IGmkList* GmkRoutedMapObj::getBindedRoutePointList() const {
    return static_cast<const GmkSet*>(m_list->getCreateInfo().m_param)->m_gmkLists[8];
}
IGmkList* GmkRoutedMob::getBindedRoutePointList() const {
    return static_cast<const GmkSet*>(m_list->getCreateInfo().m_param)->m_gmkLists[20];
}

GmkRouteNavi* GmkRoutedMob::findRouteNavi(gf::GF_OBJ_HANDLE* handle) const {
    for (std::pair<gf::GF_OBJ_HANDLE*, GmkRouteNavi>* it = m_navis.begin(); it != m_navis.end(); ++it) {
        if (it->first == handle) {
            return &it->second;
        }
    }
    return nullptr;
}
IGmkList* GmkRoute::getBindedRoutePointList() const {
    return static_cast<const GmkSet*>(m_list->getCreateInfo().m_param)->m_gmkLists[GmkRoutePoint::TYPE];
}

void GmkEvent::create(const CreateInfo& info) { AGmkBase::create(info); }
void GmkBattleLock::create(const CreateInfo& info) { AGmkBase::create(info); }
void GmkFieldLock::create(const CreateInfo& info) { AGmkBase::create(info); }

void GmkCollection::create(const CreateInfo& info) {
    AGmkBase::create(info);
    if (!isValid()) {
        dispose();
        return;
    }
    setTargetable(gf::GfGameManager::isMapjumpWithSaveData() ? !isWaitRepop() : true);
    Bdat::uVal popDist;
    popDist.ulong = Bdat::getValCheck(gf::GfDataBdat::getFP(0x7B), 0, 1, 8);
    m_popDistSq = popDist.real * popDist.real;
}

void GmkCollection::dispose() {
    disposeIcon(false);
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    AGmkBase::dispose();
}

GmkCollection::~GmkCollection() { dispose(); }

void GmkCollection::update(float dt) {
    AGmkBase::update(dt);
    if (m_seq) {
        (this->*m_seq)(dt);
    }
}

// ---- kinds holding one effect or sound handle: the destructor is the key function (dispose inlined)
void GmkDmgEffect::dispose() {
    if (m_effectHandle != 0) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->remove(m_effectHandle);
        m_effectHandle = 0;
    }
    AGmkBase::dispose();
}

GmkDmgEffect::~GmkDmgEffect() { dispose(); }

void GmkDmgSe::dispose() {
    if (m_seHandle != 0) {
        mm::mtl::PtrSingleton<fw::SoundManager>::sys()->stopSe(m_seHandle, 0.0f);
        m_seHandle = 0;
    }
    AGmkBase::dispose();
}

GmkDmgSe::~GmkDmgSe() { dispose(); }

void GmkRoutedFootPrintPoint::dispose() {
    if (m_effectHandle != 0) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->dead(m_effectHandle);
        m_effectHandle = 0;
    }
    AGmkBase::dispose();
}

GmkRoutedFootPrintPoint::~GmkRoutedFootPrintPoint() { dispose(); }

GmkPrecious::~GmkPrecious() { dispose(); }

void GmkPrecious::create(const CreateInfo& info) {
    AGmkBase::create(info);
    Bdat::uVal popDist;
    popDist.ulong = Bdat::getValCheck(gf::GfDataBdat::getFP(0x7B), 0, 0x22, 8);
    m_popDistSq = popDist.real * popDist.real;
}

// ---- debug draws and updates of the base form
void GmkEvent::debugDraw() const { AGmkBase::debugDraw(); }
void GmkBattleLock::debugDraw() const { AGmkBase::debugDraw(); }
void GmkFieldLock::debugDraw() const { AGmkBase::debugDraw(); }
void GmkEffect::debugDraw() const { AGmkBase::debugDraw(); }
void GmkMob::debugDraw() const { AGmkBase::debugDraw(); }
void GmkMapJump::dispose() {
    m_phantom.dispose();
    AGmkBase::dispose();
}

void GmkMapJump::debugDraw() const { AGmkBase::debugDraw(); }
void GmkGrave::debugDraw() const {
    AGmkBase::debugDraw();
    isValid();
}
void GmkDmgEffect::update(float dt) { AGmkBase::update(dt); }

int IGmkList::debugGetDocId() const { return 0; }

bool isInterestPosExist() {
    GmkManager* manager = GmkManager::sys();
    if (manager != nullptr && manager->pad_198 != 1) {
        if (manager->pad_198 == 0) {
            return isPlayerExist();
        }
        return false;
    }
    ml::Scn* scn = ml::Scn::sys();
    if (scn == nullptr) {
        return false;
    }
    return scn->getCam(-1) != nullptr;
}

bool isPlayerExist() { return gf::GfGameManager::getControlMoverForGimmick() != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1); }

const mm::Vec3& getInterestPos() {
    GmkManager* manager = GmkManager::sys();
    if (manager != nullptr && manager->pad_198 != 1) {
        if (manager->pad_198 == 0) {
            return getPlayerPos();
        }
        return mm::Vec3::zero;
    }
    return ml::Scn::sys()->getCam(-1)->m_info.m_render->m_transform.m_posGbl;
}

const mm::Vec3& getPlayerPos() {
    if (gf::GfGameManager::isGameTypeIra()) {
        return gf::GfGameManager::getControlMoverPosition();
    }
    gf::GfObj* obj = gf::GfObjUtil::getObj(gf::GfGameManager::getControlMoverForGimmick());
    return obj->getComponent<gf::GfComTransform>(0)->getPosition();
}

// the icon row of a quest target icon type (BDAT 0x7B member 1, rows 15..19), -1 for the others
int getBdatIdOfQuestTargetIcon(unsigned int iconType) {
    unsigned char* fp = gf::GfDataBdat::getFP(0x7b);
    switch (iconType) {
    case 1:
        return (unsigned short)Bdat::getValCheck(fp, 1, 0xf, 2);
    case 2:
        return (unsigned short)Bdat::getValCheck(fp, 1, 0x10, 2);
    case 3:
        return (unsigned short)Bdat::getValCheck(fp, 1, 0x11, 2);
    case 4:
        return (unsigned short)Bdat::getValCheck(fp, 1, 0x12, 2);
    case 6:
        return (unsigned short)Bdat::getValCheck(fp, 1, 0x13, 2);
    default:
        return -1;
    }
}

AGmkBase* getBindedGmkInst(gf::GF_OBJ_HANDLE* handle) {
    if (handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return nullptr;
    }
    gf::GfObjAcc acc(handle);
    if (acc.m_obj == nullptr || acc.isDestroy() || acc.testFlag(0x11) || acc.getObj() == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<AGmkBase*>(acc.getUserData(gf::GfObjUserData(0)));
}

bool isNaviMeshExist(const mm::Vec3& pos) {
    mm::Vec3 out;
    return fw::NaviUtil::testNaviColi(out, pos, 2.0f, 2.0f);
}

const char* debugGetGmkBdatRowName(const AGmkBase&) { return "(null)"; }
const char* debugGetGmkBdatSheetName(const AGmkBase&) { return "(null)"; }

void applyLodFade(unsigned short lodId, bool flag) {
    if (const gf::GfFieldLod::BdatInfo* lodInfo = mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->findBdatInfo(lodId)) {
        if (lodInfo->m_fadeInTime > 0.0f) {
            mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->setFade(lodId, true, flag);
        } else if (lodInfo->m_fadeOutTime > 0.0f) {
            mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->setFade(lodId, false, flag);
        }
    }
}

// whether the gimmick's npc motion blinks: its bdat row's "Mot" (u16) names a FLD_NpcMobMotionId row whose
// "notEyeBlink" flag is clear; false without a bound table or motion
bool hasEyeBlink(const AGmkBase& gmk) {
    unsigned char* fp = gmk.getBindedBdatFp();
    if (fp == nullptr) {
        return false;
    }
    unsigned short mot = Bdat::getValCheckU16(fp, "Mot", gmk.m_createInfo.m_bdatId);
    if (mot == 0) {
        return false;
    }
    return Bdat::getFlagVal(Bdat::getFP("FLD_NpcMobMotionId"), "flag", mot, "notEyeBlink") == 0;
}

bool canPopSquadMember(gf::GF_OBJ_HANDLE* handle) {
    if (gf::GfGameUtil::isGameObjWait(handle)) {
        return false;
    }
    gf::GfObjAcc acc(handle);
    if (!acc.isValidTransform() || acc.isDestroy() || acc.testFlag(0x11)) {
        return false;
    }
    gf::GfObj* obj = acc.getObj();
    if (obj == nullptr) {
        return false;
    }
    const gf::GfComBehaviorEnemy* behavior = obj->getComponent<gf::GfComBehaviorEnemy>(6);
    if (behavior == nullptr) {
        return false;
    }
    return behavior->getStateId() != 13;
}

int GmkTbox::getProgress() const { return gf::GfGameFlag::getLocal(2, m_createInfo.m_bdatId + 31765); }

void GmkTbox::debugDraw() const {
    AGmkBase::debugDraw();
    isValid();
}

bool GmkMapObj::BdatInfo::isPopCondMatched(const mm::Vec3& pos) const {
    if (!isInsideVisibleDist(pos, this)) {
        return false;
    }
    if (m_condition != 0 && !gf::GfGameCond::isGameCond(m_condition)) {
        return false;
    }
    return true;
}

bool GmkMapObj::BdatInfo::isDepopCondMatched(const mm::Vec3& pos) const {
    if (isOutsideInvisibleDist(pos, this)) {
        return true;
    }
    if (m_condition != 0 && !gf::GfGameCond::isGameCond(m_condition)) {
        return true;
    }
    return false;
}

void GmkMapObj::reqDisposeGob(float wait, unsigned int arg) const {
    m_disposeWait = wait;
    m_disposeArg = arg;
}

void GmkRoutedFootPrint::dispose() {
    AGmkBase::dispose();
    pad_50 = nullptr;
    pad_58 = nullptr;
}

GmkRoutedFootPrint::~GmkRoutedFootPrint() { dispose(); }

void GmkRoutedFootPrint::debugDraw() const {
    AGmkBase::debugDraw();
    if (isValid()) {
        debugDrawRoute(mm::Col4::yellow);
    }
}

unsigned int GmkTutorial::getGameFlagId() const { return m_createInfo.m_bdatId + 54162; }

bool GmkLandmark::isFound() const { return gf::GfGameFlag::getLocal(1, m_createInfo.m_bdatId + 51161) != 0; }

void GmkJump::reqDeadIcon() {
    if (!pad_78) {
        pad_78 = 1;
        if (m_effectHandle != 0) {
            mm::mtl::PtrSingleton<fw::EffectManager>::sys()->dead(m_effectHandle);
            m_effectHandle = 0;
        }
    }
}

void GmkJump::reqRecreateIcon() {
    if (pad_78) {
        pad_78 = 0;
        if (m_effectHandle == 0) {
            createIcon();
        }
    }
}

const TGmkFormPc<GmkType(24), TGmkFormPcnpc<GmkType(25)> >* GmkSalvage::getGmkFormPc() const {
    typedef TGmkFormPc<GmkType(24), TGmkFormPcnpc<GmkType(25)> > FormPc;
    const Data* data = getData();
    unsigned int idx = data->m_formPcIdx;
    int num = data->pad_c - idx;
    if (num > 0) {
        const IGmkList* list = static_cast<const GmkSalvageList*>(m_list)->m_gmkSet.m_gmkLists[FormPc::TYPE];
        if (list->getInstNum() > idx) {
            return static_cast<const FormPc*>(list->getInst(idx));
        }
    }
    return nullptr;
}

void GmkSalvage::disposeRaffle(bool req) {
    if (!pad_d0) {
        return;
    }
    m_raffleResult.m_dropDrawn.reset();
    m_raffleResult.m_dropIds[0] = -1;
    m_raffleResult.m_dropIds[1] = -1;
    m_raffleResult.m_dropIds[2] = -1;
    m_raffleResult.m_tboxDrawn.reset();
    m_raffleResult.m_tboxIds[0] = -1;
    m_raffleResult.m_tboxIds[1] = -1;
    m_raffleResult.m_tboxIds[2] = -1;
    m_raffleResult.m_enemyDrawn.reset();
    m_raffleResult.m_enemyIds[0] = -1;
    m_raffleResult.m_enemyIds[1] = -1;
    m_raffleResult.m_enemyIds[2] = -1;
    for (int i = 0; i < 3; i++) {
        m_raffleResult.m_enemies[i].m_id = 0;
        m_raffleResult.m_enemies[i].pad_2 = 0;
    }
    pad_d0 = false;
    pad_d1 = false;
    const GmkSet& set = static_cast<const GmkSalvageList*>(m_list)->m_gmkSet;
    if (!set.isValid()) {
        return;
    }
    const IGmkList* locators = set.m_gmkLists[GmkSalvageLocator::TYPE];
    if (locators == nullptr || !locators->isValid()) {
        return;
    }
    const mm::mtl::FixedVector<GmkSalvageLocator*, 3>& tboxes = m_tboxLocators;
    for (unsigned int i = 0, n = tboxes.size(); i < n; i++) {
        GmkSalvageLocator* locator = tboxes[i];
        if (locator != nullptr) {
            locator->m_isAccessed = false;
            locator->disposeGobInst(req);
        }
    }
    const mm::mtl::FixedVector<GmkSalvageLocator*, 3>& drops = m_dropLocators;
    for (unsigned int i = 0, n = drops.size(); i < n; i++) {
        GmkSalvageLocator* locator = drops[i];
        if (locator != nullptr) {
            locator->pad_58 = 0;
            locator->m_dropitemEmitter.dispose();
        }
    }
    const mm::mtl::FixedVector<GmkSalvageLocator*, 3>& enemies = m_enemyLocators;
    for (unsigned int i = 0, n = enemies.size(); i < n; i++) {
        GmkSalvageLocator* locator = enemies[i];
        if (locator != nullptr) {
            locator->disposeGobInst(req);
        }
    }
}

void GmkSalvage::popByRaffleResult() {
    const mm::mtl::FixedVector<GmkSalvageLocator*, 3>& drops = m_dropLocators;
    for (unsigned int i = 0; i < 3; i++) {
        if (m_raffleResult.m_dropDrawn[i]) {
            GmkSalvageLocator* locator = drops[i];
            CreateInfo info = locator->m_createInfo;
            locator->create(info);
            locator->pad_e8 = m_raffleResult.m_dropIds[i];
            locator->m_popWait = 0.0f;
            locator->m_popTimer = 0.0f;
            locator->m_seq = &GmkSalvageLocator::seqWaitPop;
        }
    }
    const mm::mtl::FixedVector<GmkSalvageLocator*, 3>& tboxes = m_tboxLocators;
    for (unsigned int i = 0; i < 3; i++) {
        if (m_raffleResult.m_tboxDrawn[i]) {
            GmkSalvageLocator* locator = tboxes[i];
            CreateInfo info = locator->m_createInfo;
            locator->create(info);
            locator->pad_e8 = m_raffleResult.m_tboxIds[i];
            locator->m_popWait = 0.0f;
            locator->m_popTimer = 0.0f;
            locator->m_seq = &GmkSalvageLocator::seqWaitPop;
        }
    }
    const mm::mtl::FixedVector<GmkSalvageLocator*, 3>& enemies = m_enemyLocators;
    for (unsigned int i = 0; i < 3; i++) {
        if (m_raffleResult.m_enemyDrawn[i]) {
            GmkSalvageLocator* locator = enemies[i];
            CreateInfo info = locator->m_createInfo;
            locator->create(info);
            const RaffleResult::Enemy& enemy = m_raffleResult.m_enemies[i];
            int id = m_raffleResult.m_enemyIds[i];
            unsigned int enemyId = enemy.m_id;
            unsigned char enemyPad = enemy.pad_2;
            locator->pad_e8 = id;
            locator->pad_ec = enemyId;
            locator->pad_f0 = enemyPad;
            locator->m_popWait = 0.0f;
            locator->m_popTimer = 0.0f;
            locator->m_seq = &GmkSalvageLocator::seqWaitPop;
        }
    }
    pad_d1 = true;
}

void GmkSalvage::create(const CreateInfo& info) {
    AGmkBase::create(info);
    unsigned char* fp = gf::GfDataBdat::getFP(0x7B);
    unsigned int popDist = Bdat::getValCheck(fp, 0, 0x1E, 8);
    m_popDistSq = *reinterpret_cast<float*>(&popDist) * *reinterpret_cast<float*>(&popDist);
    unsigned int dist = Bdat::getValCheck(fp, 0, 0x3A, 8);
    pad_64 = *reinterpret_cast<float*>(&dist) * *reinterpret_cast<float*>(&dist);
    m_seq = &GmkSalvage::seqValidateGmkSalvageLocatorDetails;
}

// the salvage's index-th locator, none when the locator list has no such element (an inferred helper; the name is
// not the original's)
static inline GmkSalvageLocator* getSalvageLocator(const GmkSalvage* salvage, unsigned int index) {
    GmkSalvageLocatorList* locators = static_cast<GmkSalvageLocatorList*>(
        static_cast<const GmkSalvageList*>(salvage->m_list)->m_gmkSet.m_gmkLists[GmkSalvageLocator::TYPE]);
    if (locators == nullptr) {
        return nullptr;
    }
    unsigned int locatorIndex = salvage->getData()->m_locatorBegin + index;
    if (locators->getInstNum() <= locatorIndex) {
        return nullptr;
    }
    return &locators->m_gmks[locatorIndex];
}

void GmkSalvage::seqValidateGmkSalvageLocatorDetails(float) {
    const Data* data = getData();
    unsigned int num = data->m_locatorEnd - data->m_locatorBegin;
    if (num != 0) {
        if (getSalvageLocator(this, 0) == nullptr) {
            return;
        }
        for (unsigned int i = 0; i < num; i++) {
            GmkSalvageLocator* locator = getSalvageLocator(this, i);
            locator->m_salvage = this;
            switch (locator->m_createInfo.m_data[0]) {
            case 1:
                if (m_dropLocators.size() != m_dropLocators.capacity()) {
                    m_dropLocators.push_back(locator);
                }
                break;
            case 2:
                if (m_tboxLocators.size() != m_tboxLocators.capacity()) {
                    m_tboxLocators.push_back(locator);
                }
                break;
            case 3:
                if (m_eventLocator == nullptr) {
                    m_eventLocator = locator;
                }
                break;
            case 4:
                if (m_enemyLocators.size() != m_enemyLocators.capacity()) {
                    m_enemyLocators.push_back(locator);
                }
                break;
            }
        }
    }
    m_seq = &GmkSalvage::seqUpdatePopDepop;
}

void GmkSalvage::dispose() {
    disposeRaffle(false);
    m_seq = nullptr;
    m_enemyLocators.clear();
    m_eventLocator = nullptr;
    m_tboxLocators.clear();
    m_dropLocators.clear();
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    AGmkBase::dispose();
}

void GmkSalvage::update(float dt) {
    AGmkBase::update(dt);
    if (isValid()) {
        if (pad_129) {
            pad_129 = 0;
            const mm::mtl::FixedVector<GmkSalvageLocator*, 3>& tboxes = m_tboxLocators;
            for (unsigned int i = 0, n = tboxes.size(); i < n; i++) {
                GmkSalvageLocator* locator = tboxes[i];
                if (locator != nullptr) {
                    locator->m_isAccessed = false;
                    locator->disposeGobInst(true);
                }
            }
        }
        if (m_seq) {
            (this->*m_seq)(dt);
        }
    }
}

void GmkSalvage::onGobEvent(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle) {
    AGmkBase::onGobEvent(evt, handle);
    if (evt == gf::IGfObjListener::OBJEVT(3)) {
        // the salvage's object went away: if it was an enemy the raffle placed, its treasure boxes go too
        bool isEnemy = false;
        const mm::mtl::FixedVector<GmkSalvageLocator*, 3>& enemies = m_enemyLocators;
        for (unsigned int i = 0, n = enemies.size(); i < n; i++) {
            GmkSalvageLocator* locator = enemies[i];
            if (locator != nullptr && locator->isValid() && !locator->pad_f1) {
                isEnemy |= locator->m_gob == handle;
                if (locator->m_gob == handle) {
                    break;
                }
            }
        }
        if (isEnemy) {
            const mm::mtl::FixedVector<GmkSalvageLocator*, 3>& tboxes = m_tboxLocators;
            for (unsigned int i = 0, n = tboxes.size(); i < n; i++) {
                GmkSalvageLocator* locator = tboxes[i];
                if (locator != nullptr) {
                    locator->m_isAccessed = false;
                    locator->disposeGobInst(true);
                }
            }
        }
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
}

void GmkSalvage::onPlayerAccessed(gf::GF_OBJ_HANDLE*) { gf::GfGameFlag::setLocal(1, m_createInfo.m_bdatId + 11804, 1); }

void GmkSalvage::debugDraw() const {
    AGmkBase::debugDraw();
    isValid();
}
void GmkRoutedMapObj::create(const CreateInfo& info) { GmkRoute::create(info); }
void GmkLandmark::create(const CreateInfo& info) { AGmkBase::create(info); }
void GmkRoutePoint::create(const CreateInfo& info) { AGmkBase::create(info); }
void GmkFieldVolume::create(const CreateInfo& info) { AGmkBase::create(info); }
void GmkTutorial::create(const CreateInfo& info) { AGmkBase::create(info); }
void GmkSquadLeader::create(const CreateInfo& info) { AGmkBase::create(info); }

IGmkList* GmkSquadLeader::getBindedSquadMemberList() const {
    return static_cast<const GmkSet*>(m_list->getCreateInfo().m_param)->m_gmkLists[GmkSquadMember::TYPE];
}
void GmkSquadMember::create(const CreateInfo& info) { AGmkBase::create(info); }
GmkRoute::~GmkRoute() { dispose(); }
GmkRoutedNpc::~GmkRoutedNpc() { dispose(); }

bool GmkRoutedMapObj::canPopGobInst() const {
    if (m_gobInst == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) && isPlayerExist()) {
        const GmkMapObj::BdatInfo* info = static_cast<const GmkMapObj::BdatInfo*>(m_createInfo.m_bdatInfo);
        mm::Vec3 pos;
        if (getNearestPos(pos, getPlayerPos())) {
            return info->isPopCondMatched(pos);
        }
    }
    return false;
}

bool GmkRoutedMapObj::canDepopGobInst() const {
    if (m_gobInst != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) && isPlayerExist()) {
        const GmkMapObj::BdatInfo* info = static_cast<const GmkMapObj::BdatInfo*>(m_createInfo.m_bdatInfo);
        mm::Vec3 pos;
        if (getNearestPos(pos, getPlayerPos())) {
            return info->isDepopCondMatched(pos);
        }
    }
    return false;
}

void GmkRoutedMapObj::dispose() {
    if (m_gobInst != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gobInst);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gobInst);
        m_gobInst = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    GmkRoute::dispose();
}

void GmkRoutedMapObj::update(float dt) {
    AGmkBase::update(dt);
    if (!isValid() || !isInterestPosExist()) {
        return;
    }
    if (canPopGobInst()) {
        createGobInst();
    } else if (canDepopGobInst() && m_gobInst != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gobInst);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gobInst);
        m_gobInst = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
}

void GmkRoutedMapObj::createGobInst() {
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set != nullptr && set->m_createInfo.m_flag) {
        return;
    }
    if (m_gobInst != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gobInst);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gobInst);
        m_gobInst = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    CBdatWrapper bdat(m_list->getBindedBdatFp());
    m_gobInst = gf::GfObjFactory::createGmkMapObj(bdat, m_createInfo.m_bdatId);
    {
        gf::GfObjAcc acc(m_gobInst);
        acc.setUserData(gf::GfObjUserData(0), reinterpret_cast<unsigned long>(this));
    }
    gf::GF_OBJ_HANDLE* handle = m_gobInst;
    if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        bool disp;
        if (pad_58) {
            // the original calls getGmkType here and drops its answer
            getGmkType();
            disp = true;
        } else {
            disp = false;
        }
        gf::GfObjAcc acc(handle);
        if (acc.m_obj != nullptr) {
            acc.setDisp(gf::OBJDISP(8), disp);
        }
    }
    gf::GfObjSetupGimmick* setup = mm::mtl::rttiCast<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(m_gobInst)->m_setup);
    const mm::Vec3* xform = m_pos;
    setup->m_initialPos = xform[0];
    setup->pad_30 = xform[1];
}

void GmkRoutedMapObj::onGobEvent(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle) {
    AGmkBase::onGobEvent(evt, handle);
    if (evt == gf::IGfObjListener::OBJEVT(3)) {
        m_gobInst = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
}

GmkRoutedMapObj::~GmkRoutedMapObj() { dispose(); }
GmkRoutePoint::~GmkRoutePoint() { dispose(); }
GmkFieldVolume::~GmkFieldVolume() { dispose(); }
GmkSquadLeader::~GmkSquadLeader() { dispose(); }
GmkSquadMember::~GmkSquadMember() { dispose(); }
GmkSquad::~GmkSquad() { dispose(); }

void GmkSquad::seqUpdate(float) {
    if (isValid()) {
        updatePosRotY(false);
    } else {
        m_seq = &GmkSquad::seqInit;
    }
}

GmkSquadLeader* GmkSquad::getBindedGmkSquadLeader() const {
    if (m_acc.isValid()) {
        IGmkList* members = static_cast<GmkSquadLeader*>(m_acc.m_gmk)->getBindedSquadMemberList();
        if (members != nullptr && members->getInstNum() != 0 && pad_70 != 0) {
            return static_cast<GmkSquadLeader*>(m_acc.m_gmk);
        }
    }
    return nullptr;
}

bool GmkSquadNavi::getPosRotY(mm::Vec3& pos, float& rotY) const {
    if (isInSquad() && m_info.m_squad->isValid()) {
        m_info.m_squad->getPosRotY(pos, rotY, m_index);
        pos += pad_30;
        return true;
    }
    return false;
}

void GmkSquad::getPosRotY(mm::Vec3& pos, float& rotY, unsigned int index) const {
    pos = m_vec3s[index];
    rotY = m_floats[index];
}

void GmkSquadNavi::create(const CreateInfo& info) {
    dispose();
    m_info = info;
    m_info.m_squad->addGmkSquadNavi(this);
}

void GmkSquadNavi::dispose() {
    if (m_info.m_squad != nullptr && m_info.m_handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        m_info.m_squad->removeGmkSquadNavi(this);
        m_info = CreateInfo();
    }
}

void GmkSquad::removeGmkSquadNavi(GmkSquadNavi* navi) {
    if (navi != nullptr && navi->intoNode()) {
        m_bools[navi->m_index] = false;
        m_navis.remove(navi);
        navi->m_info = GmkSquadNavi::CreateInfo();
    }
}
GmkElevatorLocator::~GmkElevatorLocator() { dispose(); }
GmkTargetPoint::~GmkTargetPoint() { dispose(); }
GmkRoutedEnemyPoint::~GmkRoutedEnemyPoint() { dispose(); }

GmkElevator::~GmkElevator() { dispose(); }

// ---- GmkDmgGimmick
void GmkDmgGimmick::seqWaitToCreateChild(float) {
    m_seq = &GmkDmgGimmick::seqUpdatePopDepop;
}

void GmkDmgGimmick::create(const CreateInfo& info) {
    AGmkBase::create(info);
    if (!isValid()) {
        dispose();
        return;
    }
    fw::EffectPack* pack = gf::GfFieldManager::getEffectPack();
    if (pack != nullptr) {
        const char* name = static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo)->m_effectName;
        if (name != nullptr && *name != '\0') {
            pad_58 = mm::mtl::PtrSingleton<fw::EffectManager>::sys()->search(name, pack);
            if (pad_58 == nullptr) {
                // the original asks the list's CreateInfo here and does not use it (a message compiled out)
                m_list->getCreateInfo();
            }
        }
    }
    pad_60 = mm::mtl::PtrSingleton<gf::GfFieldSound>::sys()->getMapPack();
    m_seq = &GmkDmgGimmick::seqWaitToCreateChild;
}

void GmkDmgGimmick::dispose() {
    pad_58 = nullptr;
    AGmkBase::dispose();
    m_seq = nullptr;
}

void GmkDmgGimmick::update(float dt) {
    AGmkBase::update(dt);
    if (isValid() && m_seq) {
        (this->*m_seq)(dt);
    }
}

void GmkDmgGimmick::debugDraw() const {
    AGmkBase::debugDraw();
    isValid();
}

GmkDmgGimmick::~GmkDmgGimmick() { dispose(); }

GmkAntiBladeArea::~GmkAntiBladeArea() { dispose(); }

// its phantom (listened to by itself) is made unless the gimmick set says otherwise
void GmkAntiBladeArea::create(const CreateInfo& info) {
    AGmkBase::create(info);
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set == nullptr || !set->m_createInfo.m_flag) {
        m_phantom.create(*this, this, false);
    }
}

// the player entered it: it becomes the manager's first area and the active one
void GmkAntiBladeArea::onEnterPhantom(const IGmkPhantomEventListener::OnEnterInfo&) {
    GmkAntiBladeAreaManager::sys()->m_areas.push_front(this);
    GmkAntiBladeAreaManager::sys()->m_active = GmkAntiBladeAreaManager::sys()->m_areas.front();
}

inline void GmkAntiBladeAreaManager::removeArea(GmkAntiBladeArea* area) {
    if (area != nullptr && area->intoNode()) {
        if (sys() != nullptr) {
            sys()->m_areas.remove(area);
            if (sys()->m_areas.empty()) {
                sys()->m_active = nullptr;
            } else {
                sys()->m_active = sys()->m_areas.front();
            }
        }
    }
}

void GmkAntiBladeArea::onLeavePhantom(const IGmkPhantomEventListener::OnLeaveInfo&) {
    GmkAntiBladeAreaManager::removeArea(this);
}

void GmkAntiBladeAreaManager::dispose() {
    m_active = nullptr;
    m_areas.clear();
}

// ---- GmkSalvageLocator
GmkSalvageLocator::~GmkSalvageLocator() { dispose(); }

void GmkSalvageLocator::onPlayerAccessed(gf::GF_OBJ_HANDLE*) {
    m_isAccessed = true;
}

void GmkSalvageLocator::reqDisposeTboxGobInst(float wait) const {
    m_disposeWait = wait;
    pad_e4 = 0;
}

void GmkSalvageLocator::setTargetable(bool targetable) const {
    gf::GF_OBJ_HANDLE* gob = m_gob;
    if (gob == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    gf::GfObjAcc acc(gob);
    if (acc.m_obj != nullptr) {
        gf::GfObjSetupGimmick* setup = mm::mtl::rttiCast<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(gob)->m_setup);
        if (targetable) {
            setup->pad_6c |= 7;
        } else {
            setup->pad_6c &= ~7;
        }
    }
    if (gf::GfObj* obj = acc.getObj()) {
        if (targetable) {
            obj->pad_110 |= 7;
        } else {
            obj->pad_110 &= ~7;
        }
    }
}

void GmkSalvageLocator::seqWaitPop(float dt) {
    m_popTimer += dt;
    if (m_popTimer < m_popWait) {
        return;
    }
    m_seq = &GmkSalvageLocator::seqPop;
}

void GmkSalvageLocator::dispose() {
    pad_f0 = 0;
    pad_e8 = -1;
    pad_ec = 0;
    m_disposeWait = 0.0f;
    pad_e4 = 0;
    pad_58 = 0;
    m_dropitemEmitter.dispose();
    m_isAccessed = false;
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        syncDepopTboxes();
        if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            gf::GfObjAcc acc(m_gob);
            if (acc.m_obj != nullptr) {
                acc.setUserData(gf::GfObjUserData(0), 0);
            }
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    AGmkBase::dispose();
}

void GmkSalvageLocator::update(float dt) {
    AGmkBase::update(dt);
    if (m_seq) {
        (this->*m_seq)(dt);
    }
}

void GmkSalvageLocator::syncDepopTboxes() {
    if (m_createInfo.m_data[0] == 4 && !pad_f1 && !pad_f2 && m_salvage != nullptr) {
        m_salvage->pad_129 = 1;
    }
}

void GmkSalvageLocator::disposeGobInst(bool req) {
    if (m_gob == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    syncDepopTboxes();
    if (req) {
        gf::GF_OBJ_HANDLE* gob = m_gob;
        gf::GfObjAcc acc(gob);
        if (acc.getObj() != nullptr && !acc.isDestroy() && !acc.testFlag(17)) {
            gf::SCOM_DESTROY_GAME_OBJ::create(gob, 1.0f, 0);
        }
    } else {
        if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            gf::GfObjAcc acc(m_gob);
            if (acc.m_obj != nullptr) {
                acc.setUserData(gf::GfObjUserData(0), 0);
            }
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
}

void GmkSalvageLocator::onGobEvent(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle) {
    AGmkBase::onGobEvent(evt, handle);
    if (evt == gf::IGfObjListener::OBJEVT(3) && m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        syncDepopTboxes();
        if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            gf::GfObjAcc acc(m_gob);
            if (acc.m_obj != nullptr) {
                acc.setUserData(gf::GfObjUserData(0), 0);
            }
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
}

void GmkSalvageLocator::onEnemyDead(gf::GF_OBJ_HANDLE*) { pad_f1 = 1; }

void GmkSalvageLocator::onEnemyHomeToPlayerAccess(gf::GF_OBJ_HANDLE*) { pad_f2 = 1; }

// ---- GmkEnemyWave (GmkEnemyList's wave; placeholder slot symbols: see its header)
GmkEnemyWave::ProgressInfo GmkEnemyWave::sm_progressInfo;

unsigned int GmkEnemyWave::getBindedEnemyNum() const {
    const Data* data = getData();
    return data->m_enemyEnd - data->m_enemyBegin;
}

GmkEnemy* GmkEnemyWave::getBindedEnemy(unsigned int index) {
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    GmkEnemyList* enemies = static_cast<GmkEnemyList*>(set->m_gmkLists[GmkEnemy::TYPE]);
    if (enemies == nullptr) {
        return nullptr;
    }
    unsigned int enemyIndex = getData()->m_enemyBegin + index;
    if (enemies->getInstNum() <= enemyIndex) {
        return nullptr;
    }
    return &enemies->m_gmks[enemyIndex];
}

// whether a list of the gimmick set is still loading: it has a path to load but is not valid yet (an inferred helper;
// the name is not the original's)
static inline bool isGmkListLoading(const IGmkList* list) {
    if (list == nullptr) {
        return false;
    }
    const IGmkList::CreateInfo& info = list->getCreateInfo();
    return info.m_allocHandle.m_handle != 0 && info.m_path.length() != 0 && !list->isValid();
}

// takes its enemies (sorted by pop priority, then index), the access to the gimmick its first enemy's battle lock
// names, its phantom (on that gimmick when there is one) unless the gimmick set says otherwise, then runs its first
// step
void GmkEnemyWave::create(const CreateInfo& info) {
    AGmkBase::create(info);
    for (unsigned short i = 0; i < getBindedEnemyNum(); i++) {
        GmkEnemy* enemy = getBindedEnemy(i);
        if (enemy->isValid()) {
            if (gf::GfGameManager::isInstalledBattleArenaContents() || gf::GfGameManager::isGameTypeIra()) {
                enemy->m_insts.m_waveFlags |= 2;
            }
            if ((gf::GfGameManager::isInstalledBattleArenaContents() || gf::GfGameManager::isGameTypeIra()) &&
                (gf::GfGameManager::isInstalledBattleArenaContents() || gf::GfGameManager::isGameTypeIra())) {
                enemy->m_insts.m_waveFlags |= 1;
            }
            GmkEnemyWaveExtension::WavePopInfo popInfo;
            enemy->pad_1d0.getWavePopInfo(enemy, popInfo);
            m_entries.push_back(Entry(enemy, i, popInfo));
        }
    }
    std::sort(m_entries.begin(), m_entries.end(), [](const Entry& a, const Entry& b) {
        if (a.m_popInfo.m_popPriority != b.m_popInfo.m_popPriority) {
            return a.m_popInfo.m_popPriority < b.m_popInfo.m_popPriority;
        }
        return a.m_index < b.m_index;
    });
    Bdat::uVal dist;
    dist.ulong = Bdat::getValCheck(gf::GfDataBdat::getFP(0x7B), 0, 0x1E, 8);
    m_accessDistSq = dist.real * dist.real;
    if (m_entries.size() != 0) {
        short lockName = m_entries[0].m_popInfo.m_battleLockName;
        if (lockName >= 0) {
            GmkAcc::CreateInfo accInfo;
            accInfo.m_bdatId = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param)->m_createInfo.m_bdatId;
            accInfo.m_type = GmkType(0xb);
            accInfo.pad_8 = lockName;
            m_acc.create(accInfo);
            m_isAccCounted = false;
        }
    }
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set == nullptr || !set->m_createInfo.m_flag) {
        if (m_acc.isValid()) {
            m_phantom.create(*m_acc.m_gmk, nullptr, false);
        } else {
            m_phantom.create(*this, nullptr, false);
        }
    }
    m_seq = &GmkEnemyWave::seqWaitToValidLinkGmkList;
    seqWaitToValidLinkGmkList(0.0f);
}

// false while one of its enemies is not ready; a battle challenge's wave pops once started, the others by their row's
// conditions
bool GmkEnemyWave::isPopCondMatched() const {
    for (const Entry& entry : m_entries) {
        const GmkEnemy* enemy = entry.m_enemy;
        if (enemy == nullptr || !enemy->isValid() || !enemy->m_insts.isValid() || !enemy->m_insts.m_popInfo.pad_2) {
            return false;
        }
    }
    if (m_isChallenge) {
        return m_isStarted;
    }
    const BdatInfo* bdat = getBdatInfo();
    if (gf::GfGameManager::isGameTypeIra() && gf::GfGameManager::isPlayEvent()) {
        return false;
    }
    if (bdat->m_condition != 0 && !gf::GfGameCond::isGameCond(bdat->m_condition)) {
        return false;
    }
    if (bdat->m_popTime.m_time != 0 && !bdat->m_popTime.isMatch()) {
        return false;
    }
    if (bdat->m_questFlag.isSet() && !bdat->m_questFlag.isMatch()) {
        return false;
    }
    if (bdat->m_scenarioFlag.m_scenarioFlagMax != 0 && !bdat->m_scenarioFlag.isMatch()) {
        return false;
    }
    return true;
}

// the index-th sealed stone of the gimmick set's list (an inferred helper: the original reaches the element through a
// pointer, not a reference, and re-reads the index; the name is not the original's)
static inline GmkSealedStone* getSealedStone(GmkSealedStoneList* stones, unsigned int index) { return &stones->m_gmks[index]; }

// waits for the gimmick set's enemy lists, takes the sealed stone and the map gimmick its row names, then goes on to
// reset
void GmkEnemyWave::seqWaitToValidLinkGmkList(float dt) {
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (isGmkListLoading(set->m_gmkLists[GmkEnemy::TYPE]) || isGmkListLoading(set->m_gmkLists[GmkRoutedEnemy::TYPE])) {
        return;
    }
    applyPopCondMatchedEnemies(false);
    const BdatInfo* bdat = getBdatInfo();
    if (gf::GfGameManager::isGameTypeIra()) {
        const GmkSet* gmkSet = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
        if (bdat->m_sealedStoneIndex != 0 && m_sealedStone == nullptr) {
            GmkSealedStoneList* stones = static_cast<GmkSealedStoneList*>(gmkSet->m_gmkLists[63]);
            if (stones == nullptr || !stones->isValid()) {
                return;
            }
            unsigned int index = bdat->m_sealedStoneIndex - 1;
            if (stones->getInstNum() <= index) {
                return;
            }
            m_sealedStone = getSealedStone(stones, bdat->m_sealedStoneIndex - 1);
            if (m_sealedStone == nullptr || !m_sealedStone->isValid()) {
                return;
            }
        }
        if (bdat->m_mapGimmickId != 0 && !m_secondAcc.isValid()) {
            IGmkList* maps = gmkSet->m_gmkLists[GmkMapGimmick::TYPE];
            if (maps == nullptr || !maps->isValid()) {
                return;
            }
            GmkAcc::CreateInfoByBdatId accInfo;
            accInfo.m_type = GmkMapGimmick::TYPE;
            accInfo.m_bdatId = bdat->m_mapGimmickId;
            m_secondAcc.create(accInfo);
            if (!m_secondAcc.isValid()) {
                return;
            }
            GmkMapGimmick* gimmick = static_cast<GmkMapGimmick*>(m_secondAcc.m_gmk);
            gimmick->pad_a8 = true;
            gimmick->pad_a9 = false;
        }
    }
    reset();
}

// its step, phantom, access and game object released
void GmkEnemyWave::dispose() {
    m_seq = nullptr;
    m_phantom.dispose();
    m_acc.dispose();
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    AGmkBase::dispose();
}

// the wave is over: the quest is told (Ira), its map gimmick shown, its flag kept when the row says once only
void GmkEnemyWave::seqFinish(float) {
    if (gf::GfGameManager::isGameTypeIra()) {
        if (!m_isCleared) {
            int bdatId = m_createInfo.m_bdatId;
            gf::GfQuestUtil::getGimmickTaskEndCheck(TYPE, bdatId);
            gf::SCOM_QUEST_GIMMICK::createEnemyWave(bdatId, 0.0f);
            if (m_secondAcc.isValid()) {
                GmkMapGimmick* gimmick = static_cast<GmkMapGimmick*>(m_secondAcc.m_gmk);
                gimmick->pad_a8 = true;
                gimmick->pad_a9 = true;
            }
        }
        if (getBdatInfo()->m_onlyOnce) {
            gf::GfGameFlag::setLocal(1, m_createInfo.m_bdatId + 0xd796, 1);
        }
    }
    releaseAccCount();
    applyPopCondMatchedEnemies(false);
    m_isCleared = true;
    m_seq = nullptr;
    sm_progressInfo.m_restNum = -1;
    gf::GfGameManager::setStopMainMenuOpenForGimmick(false);
}

void GmkEnemyWave::seqWaitAccessing(float) {}

// once its conditions hold: its invincible enemies marked (Ira, once), then, with the player in its phantom, its
// enemies reset and the update step started
void GmkEnemyWave::seqWaitPlayerIntoPhantom(float) {
    if (!isPopCondMatched()) {
        return;
    }
    if (gf::GfGameManager::isGameTypeIra() && !m_isInvincibleMarked) {
        for (Entry& entry : m_entries) {
            GmkEnemy* enemy = entry.m_enemy;
            const GmkEnemyInsts::BdatInfo& bdat = enemy->m_insts.m_bdatInfo;
            if (bdat.m_mutekiCondition != 0 || bdat.m_mutekiQuestFlag.isSet()) {
                enemy->m_insts.pad_158 = 1;
                enemy->m_insts.pad_159 = 1;
            }
        }
        m_isInvincibleMarked = true;
    }
    if (m_phantom.m_coliObject == nullptr || m_phantom.pad_83) {
        for (Entry& entry : m_entries) {
            GmkEnemy* enemy = entry.m_enemy;
            enemy->m_insts.reqClearRepopCounter();
            if (gf::GfGameManager::isGameTypeIra()) {
                enemy->m_insts.m_waveFlags &= ~4;
            }
            entry.pad_e = 0;
            entry.pad_8 = 0;
        }
        m_seq = &GmkEnemyWave::seqUpdate;
        if (gf::GfGameManager::isGameTypeIra() && m_sealedStone != nullptr) {
            m_sealedStone->pad_6c = 1;
        }
        gf::GfGameManager::setStopMainMenuOpenForGimmick(true);
    }
}

// how many game objects its enemies hold
unsigned int GmkEnemyWave::getEnemyGobInstNum() const {
    unsigned int num = 0;
    for (const Entry* it = m_entries.begin(); it != m_entries.end(); ++it) {
        num += it->m_enemy->getGobInstNum();
    }
    return num;
}

void GmkEnemyWave::debugDraw() const {}

void GmkEnemyWave::onPlayerAccessed(gf::GF_OBJ_HANDLE*) {
    if (!isValid() || m_entries.size() == 0) {
        return;
    }
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    unsigned short condition = getBdatInfo()->m_opCondition;
    if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
        const BdatInfo* bdat = getBdatInfo();
        gf::MenuCommonWindowParam param;
        param.m_bdat = gf::GfDataBdat::getFP(0x1b1);
        param.m_msgId = bdat->m_missMsgId;
        gf::GfPlayFactory::createCommonMessage(param);
        return;
    }
    if (getData()->m_accessType != 1) {
        return;
    }
    for (Entry& entry : m_entries) {
        GmkEnemy* enemy = entry.m_enemy;
        enemy->m_insts.reqClearRepopCounter();
        if (gf::GfGameManager::isGameTypeIra()) {
            enemy->m_insts.m_waveFlags &= ~4;
        }
        entry.pad_e = 0;
        entry.pad_8 = 0;
    }
    m_seq = &GmkEnemyWave::seqUpdate;
    if (gf::GfGameManager::isGameTypeIra() && m_sealedStone != nullptr) {
        m_sealedStone->pad_6c = 1;
    }
    gf::GfGameManager::setStopMainMenuOpenForGimmick(true);
}

void GmkEnemyWave::seqAbort(float) {
    if (gf::GfGameManager::isGameTypeIra() && m_sealedStone != nullptr) {
        m_sealedStone->pad_6c = 0;
    }
    if (gf::GfGameManager::isGameTypeIra()) {
        for (Entry& entry : m_entries) {
            entry.m_enemy->pad_1d0.backHome(entry.m_enemy);
        }
    }
    applyPopCondMatchedEnemies(false);
    m_seq = &GmkEnemyWave::seqAbortWait;
}

// waits until its enemies (but the invincible ones) hold no game object, then resets
void GmkEnemyWave::seqAbortWait(float) {
    int num = 0;
    for (const Entry* it = m_entries.begin(); it != m_entries.end(); ++it) {
        const GmkEnemyInsts::BdatInfo& bdat = it->m_enemy->m_insts.m_bdatInfo;
        if (bdat.m_mutekiCondition == 0 && !bdat.m_mutekiQuestFlag.isSet()) {
            unsigned int gobNum = it->m_enemy->getGobInstNum();
            num += it->m_popInfo.m_partyFlag == 0 ? (gobNum != 0 ? 1 : 0) : gobNum;
        }
    }
    if (num != 0) {
        return;
    }
    reset();
    gf::GfGameManager::setStopMainMenuOpenForGimmick(false);
}

void GmkEnemyWave::BdatInfo::create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
    m_scenarioFlag = ScenarioFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMin", row, 2), (unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMax", row, 2));
    m_questFlag = QuestFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "QuestFlag", row, 2), (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMin", row, 1),
                                (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMax", row, 1));
    m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
    m_popTime.m_time = (unsigned int)Bdat::getValCheck(bdat.m_fp, "POP_TIME", row, 3);
    m_popWeather.m_weather = (unsigned char)Bdat::getValCheck(bdat.m_fp, "popWeather", row, 1);
    m_instanceMax = (unsigned char)Bdat::getValCheck(bdat.m_fp, "instanceMax", row, 1);
    m_mapGimmickId = (unsigned short)Bdat::getValCheck(bdat.m_fp, "gimmick", row, 2);
    m_onlyOnce = (unsigned char)Bdat::getValCheck(bdat.m_fp, "onlyOnce", row, 1);
    m_nameRadius = (unsigned short)Bdat::getValCheck(bdat.m_fp, "nameRadius", row, 2);
    m_waitTime = (unsigned short)Bdat::getValCheck(bdat.m_fp, "waitTime", row, 2);
    m_sealedStoneIndex = gf::GfGameManager::isGameTypeIra() ? (unsigned short)Bdat::getValCheck(bdat.m_fp, "sealedStonePopID", row, 2) : 0;
    if (gf::GfGameManager::isGameTypeIra()) {
        m_opCondition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "OP_Condition", row, 2);
        m_missMsgId = (unsigned short)Bdat::getValCheck(bdat.m_fp, "missMSG_ID", row, 2);
    }
}

// a gimmick set row's BDAT table name for a kind given by name, as GmkManager::getSheetnameByType reads it (the
// original inlines it with the literal kind name; the name is not the original's)
static inline const char* getSheetnameByKindName(const GmkManager* manager, int id, const char* kindName) {
    mm::mtl::FixStr<256> column;
    column.format("%s_bdat", kindName);
    unsigned char* setFp = manager->m_bdatFp;
    return Bdat::getMember(setFp, column.m_str) != nullptr ? reinterpret_cast<const char*>(Bdat::getValCheck(setFp, column.m_str, id, 7)) : nullptr;
}

GmkEnemyWaveList::GmkEnemyWaveList(unsigned int updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame), m_subList(-1) {}

// the second list's BDAT table is the gimmick set's "battleChallenge_bdat" column
void GmkEnemyWaveList::createGmk(void* data) {
    TGmkList::createGmk(data);
    IGmkList::CreateInfo info = getCreateInfo();
    if (info.m_allocHandle.m_handle != 0 && info.m_path.length() != 0) {
        info.m_bdatName.clear();
        IGmkList::CreateInfo subInfo = info;
        subInfo.m_bdatName = getSheetnameByKindName(GmkManager::sys(), static_cast<const GmkSet*>(info.m_param)->m_createInfo.m_bdatId,
                                                    "battleChallenge");
        m_subList.create(subInfo);
    }
}

// ---- GmkBattleChallenge (GmkEnemyList's battle challenge; placeholder slot symbols: see its header)
GmkBattleChallenge* GmkBattleChallenge::sm_activeInstance;
unsigned int GmkBattleChallenge::sm_targetGmkBdatId;
GmkBattleChallenge::State GmkBattleChallenge::sm_battleStatus;

inline GmkEnemyWave* GmkBattleChallenge::getWave(unsigned int index) const {
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    GmkEnemyList* enemies = static_cast<GmkEnemyList*>(set->m_gmkLists[GmkEnemy::TYPE]);
    if (enemies == nullptr) {
        return nullptr;
    }
    unsigned int waveIndex = index + getData()->m_waveBegin;
    if (enemies->m_waveExt.m_waveList.getInstNum() <= waveIndex) {
        return nullptr;
    }
    return &enemies->m_waveExt.m_waveList.m_gmks[waveIndex];
}

// its phantom is made unless the gimmick set says otherwise (on the access's target when there is one); its waves'
// phantoms are released
void GmkBattleChallenge::create(const CreateInfo& info) {
    AGmkBase::create(info);
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set == nullptr || !set->m_createInfo.m_flag) {
        AGmkBase* target = getBattleLock();
        if (target != nullptr) {
            m_phantom.create(*target, nullptr, false);
        } else {
            m_phantom.create(*this, nullptr, false);
        }
        m_isAccCounted = false;
    }
    for (unsigned int i = 0; i < getWaveNum(); i++) {
        GmkEnemyWave* wave = getWave(i);
        wave->m_isChallenge = true;
        wave->m_phantom.dispose();
    }
    m_seq = &GmkBattleChallenge::seqCheckCondition;
}

// starts the challenge once its row's conditions hold and the player is inside its phantom
void GmkBattleChallenge::seqCheckCondition(float) {
    // the original asks the list's CreateInfo here and does not use it
    m_list->getCreateInfo();
    const BdatInfo* info = static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo);
    if (info->m_condition != 0 && !gf::GfGameCond::isGameCond(info->m_condition)) {
        return;
    }
    if (info->m_questFlag.isSet() && !info->m_questFlag.isMatch()) {
        return;
    }
    if (info->m_scenarioFlag.m_scenarioFlagMax != 0 && !info->m_scenarioFlag.isMatch()) {
        return;
    }
    if (!m_phantom.pad_83) {
        return;
    }
    sm_activeInstance = this;
    if (!m_isAccCounted) {
        GmkBattleLock* lock = getBattleLock();
        if (lock != nullptr) {
            lock->pad_c4++;
            m_isAccCounted = true;
        }
    }
    m_result = 0;
    m_seq = &GmkBattleChallenge::seqWaveStart;
}

void GmkBattleChallenge::dispose() {
    m_seq = nullptr;
    m_phantom.dispose();
    if (sm_activeInstance == this) {
        terminate();
    }
    AGmkBase::dispose();
}

void GmkBattleChallenge::terminate() {
    sm_battleStatus.clear();
    sm_targetGmkBdatId = 0;
    sm_activeInstance = nullptr;
}

void GmkBattleChallenge::update(float dt) {
    AGmkBase::update(dt);
    if (!m_isPaused) {
        if (m_seq) {
            (this->*m_seq)(dt);
        }
    }
}

void GmkBattleChallenge::debugDraw() const {}

void GmkBattleChallenge::suspendAll(bool pause) {
    m_isPaused = pause;
    unsigned int num = getWaveNum();
    for (unsigned int i = 0; i < num; i++) {
        getWave(i)->m_isPaused = pause;
    }
}

void GmkBattleChallenge::seqWaveUpdate(float dt) {
    updateBattleStatus(false);
    unsigned int clearedNum = 0;
    for (unsigned int i = 0; i < getWaveNum(); i++) {
        if (getWave(i)->m_isCleared) {
            clearedNum = i + 1;
        }
    }
    float timer = m_timer - dt;
    m_timer = timer;
    if (timer <= 0.0f) {
        clearedNum = std::min<unsigned int>(m_waveCount + 1, getWaveNum());
    }
    if (m_waveCount < clearedNum) {
        m_result = timer <= 0.0f ? 1 : 2;
        m_waveCount = clearedNum;
        if (m_waveCount < getWaveNum()) {
            unsigned char* fp = gf::GfDataBdat::getFP(0x7B);
            Bdat::uVal wait;
            if (timer <= 0.0f) {
                wait.real = 0.0f;
            } else {
                wait.ulong = Bdat::getValCheck(fp, 0, 0x56, 8);
            }
            m_timer = wait.real;
            m_seq = &GmkBattleChallenge::seqWaitNextWave;
        } else {
            m_seq = &GmkBattleChallenge::seqFinish;
            seqFinish(dt);
        }
    }
}

void GmkBattleChallenge::seqFinish(float) {
    updateBattleStatus(true);
    m_seq = nullptr;
}

void GmkBattleChallenge::seqWaitNextWave(float dt) {
    m_timer -= dt;
    if (m_timer < 0.0f) {
        m_seq = &GmkBattleChallenge::seqWaveStart;
    }
}

void GmkBattleChallenge::debugChangeWave(unsigned int) {}

void GmkBattleChallenge::suspend(bool flag) {
    if (sm_activeInstance != nullptr) {
        sm_activeInstance->suspendAll(flag);
    }
}

// ---- GmkBattleChallengeReward (placeholder slot symbols: see its header)
unsigned int GmkBattleChallengeReward::getBdatId_RSC_TboxList() const {
    unsigned char* fp = gf::GfDataBdat::getFP(0x4D);
    mm::mtl::FixStr<32> column;
    column.format("TresureResource%d", m_index + 1);
    return Bdat::getValCheckU16(fp, column.m_str, m_bdatRow);
}

unsigned int GmkBattleChallengeReward::getBdatId_BTL_ChBtlRewardSet() const {
    unsigned char* fp = gf::GfDataBdat::getFP(0x4D);
    mm::mtl::FixStr<16> column;
    column.format("TresureSet%d", m_index + 1);
    return Bdat::getValCheckU16(fp, column.m_str, m_bdatRow);
}

void GmkBattleChallengeReward::setTargetable(bool targetable) const {
    gf::GF_OBJ_HANDLE* gob = m_gob;
    if (gob == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    gf::GfObjAcc acc(gob);
    if (acc.m_obj != nullptr) {
        gf::GfObjSetupGimmick* setup = mm::mtl::rttiCast<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(gob)->m_setup);
        if (targetable) {
            setup->pad_6c |= 7;
        } else {
            setup->pad_6c &= ~7;
        }
    }
    if (gf::GfObj* obj = acc.getObj()) {
        if (targetable) {
            obj->pad_110 |= 7;
        } else {
            obj->pad_110 &= ~7;
        }
    }
}

void GmkBattleChallengeReward::initWaitPopTime(float waitTime) {
    m_waitTime = waitTime;
    m_timer = 0.0f;
    m_seq = &GmkBattleChallengeReward::seqWaitPop;
}

void GmkBattleChallengeReward::seqWaitPop(float dt) {
    m_timer += dt;
    if (m_timer > m_waitTime) {
        if (m_gob == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            createTboxGobInst();
        }
        m_seq = &GmkBattleChallengeReward::seqWait;
    }
}

void GmkBattleChallengeReward::dispose() {
    m_isAccessed = false;
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    AGmkBase::dispose();
}

void GmkBattleChallengeReward::update(float dt) {
    AGmkBase::update(dt);
    if (m_seq) {
        (this->*m_seq)(dt);
    }
}

void GmkBattleChallengeReward::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE* handle) {
    if (event == gf::IGfObjListener::OBJEVT(3) && handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(handle);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
    }
    if (event == gf::IGfObjListener::OBJEVT(3) && m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
}

void GmkBattleChallengeReward::seqWait(float) {
    if (m_isAccessed) {
        m_timer = 0.0f;
        m_seq = &GmkBattleChallengeReward::seqDepopWait;
    }
}

void GmkBattleChallengeReward::seqDepopWait(float dt) {
    unsigned char* fp = gf::GfDataBdat::getFP(0x7B);
    unsigned int value = Bdat::getValCheck(fp, 0, 0x52, 8);
    float waitTime = *reinterpret_cast<float*>(&value);
    m_timer += dt;
    if (m_timer > waitTime) {
        gf::GF_OBJ_HANDLE* gob = m_gob;
        if (gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            gf::GfObjAcc acc(gob);
            if (acc.getObj() != nullptr && !acc.isDestroy() && !acc.testFlag(17)) {
                gf::SCOM_DESTROY_GAME_OBJ::create(gob, 1.0f, 0);
            }
        }
        m_seq = nullptr;
    }
}

GmkBattleChallengeReward::~GmkBattleChallengeReward() { dispose(); }

gmk::GmkType GmkBattleChallengeReward::getGmkType() const { return TYPE; }

bool GmkBattleChallengeReward::isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }

void GmkBattleChallengeReward::onPlayerAccessed(gf::GF_OBJ_HANDLE*) {
    m_isAccessed = true;
}

// ---- GmkBattleChallengePortal (placeholder slot symbols: see its header)
void GmkBattleChallengePortal::BdatInfo::create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
    m_scenarioFlag = ScenarioFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMin", row, 2),
                                      (unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMax", row, 2));
    m_questFlag = QuestFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "QuestFlag", row, 2),
                                (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMin", row, 1),
                                (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMax", row, 1));
    m_timeRange.m_time = (unsigned short)Bdat::getValCheck(bdat.m_fp, "TimeRange", row, 2);
    m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
    unsigned int visibleXZ = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Visible_XZ", row, 2);
    unsigned short visibleY = Bdat::getValCheck(bdat.m_fp, "Visible_Y", row, 2);
    m_visibleXZSq = (float)visibleXZ * (float)visibleXZ;
    m_visibleYSq = (float)visibleY * (float)visibleY;
    unsigned short invisibleXZ = Bdat::getValCheck(bdat.m_fp, "Invisible_XZ", row, 2);
    if (invisibleXZ <= visibleXZ) {
        invisibleXZ = visibleXZ + 1;
    }
    unsigned short invisibleY = Bdat::getValCheck(bdat.m_fp, "Invisible_Y", row, 2);
    if (invisibleY <= visibleY) {
        invisibleY = visibleY + 1;
    }
    m_invisibleXZSq = (float)invisibleXZ * (float)invisibleXZ;
    m_invisibleYSq = (float)invisibleY * (float)invisibleY;
}

bool GmkBattleChallengePortal::BdatInfo::isPopCommonCondMatched(const AGmkBase&) const {
    if (m_scenarioFlag.m_scenarioFlagMax != 0 && !m_scenarioFlag.isMatch()) {
        return false;
    }
    if (m_questFlag.isSet() && !m_questFlag.isMatch()) {
        return false;
    }
    if (m_timeRange.m_time != 0 && !m_timeRange.isMatch()) {
        return false;
    }
    if (m_condition != 0 && !gf::GfGameCond::isGameCond(m_condition)) {
        return false;
    }
    return true;
}

void GmkBattleChallengePortal::seqValidateResHandle(float) {
    fw::EffectPack* pack = gf::GfFieldManager::getEffectPack();
    if (pack == nullptr) {
        return;
    }
    m_portalEffect[0] = mm::mtl::PtrSingleton<fw::EffectManager>::sys()->search("ex_portal_01", pack);
    if (m_portalEffect[0] == nullptr) {
        return;
    }
    m_portalEffect[1] = mm::mtl::PtrSingleton<fw::EffectManager>::sys()->search("ex_portal_02", pack);
    if (m_portalEffect[1] == nullptr) {
        return;
    }
    m_seq = &GmkBattleChallengePortal::seqUpdate;
}

void GmkBattleChallengePortal::dispose() {
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->kill(m_effectHandle[0]);
        m_effectHandle[0] = 0;
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->kill(m_effectHandle[1]);
        m_effectHandle[1] = 0;
    }
    AGmkBase::dispose();
}

void GmkBattleChallengePortal::disposeGobInst(bool fade) {
    gf::GF_OBJ_HANDLE* gob = m_gob;
    if (gob == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    if (fade) {
        gf::GfObjAcc acc(gob);
        if (acc.getObj() != nullptr && !acc.isDestroy() && !acc.testFlag(0x11)) {
            gf::SCOM_DESTROY_GAME_OBJ::create(gob, 1.0f, 0);
        }
    } else {
        gf::GfObjAcc acc(gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    for (int i = 0; i < 2; i++) {
        if (fade) {
            mm::mtl::PtrSingleton<fw::EffectManager>::sys()->fadeOutDead(m_effectHandle[i]);
        } else {
            mm::mtl::PtrSingleton<fw::EffectManager>::sys()->kill(m_effectHandle[i]);
        }
        m_effectHandle[i] = 0;
    }
}

void GmkBattleChallengePortal::update(float dt) {
    if (isValid()) {
        AGmkBase::update(dt);
        if (m_seq) {
            (this->*m_seq)(dt);
        }
    }
}

bool GmkBattleChallengePortal::isPopCondMatchedExceptDist() const {
    if (isValid()) {
        return static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo)->isPopCommonCondMatched(*this);
    }
    return false;
}

void GmkBattleChallengePortal::createGobInst() {
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set != nullptr && set->m_createInfo.m_flag) {
        return;
    }
    disposeGobInst(false);
    CBdatWrapper bdat(m_list->getBindedBdatFp());
    m_gob = gf::GfObjFactory::createGmkNpc(bdat, m_createInfo.m_bdatId);
    if (m_gob == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    gf::GfObjAcc acc(m_gob);
    acc.setUserData(gf::GfObjUserData(0), reinterpret_cast<unsigned long>(this));
    gf::GfObjSetupNpc* setup = mm::mtl::rttiCast<gf::GfObjSetupNpc>(gf::GfObjManager::getObjInfo(m_gob)->m_setup);
    // m_pos points at the gimmick's Xform: its position, then its rotation (only the y angle is taken)
    const mm::Vec3* xform = m_pos;
    float rotY = xform[1].y;
    setup->m_initialPos.x = xform[0].x;
    setup->m_initialPos.y = xform[0].y;
    setup->m_initialPos.z = xform[0].z;
    setup->pad_30.x = 0.0f;
    setup->pad_30.y = rotY;
    setup->pad_30.z = 0.0f;
    createEffect(0);
}

bool GmkBattleChallengePortal::createEffect(unsigned int index) {
    unsigned int& handle = m_effectHandle[index];
    handle = mm::mtl::PtrSingleton<fw::EffectManager>::sys()->create(m_portalEffect[index], true);
    if (handle == 0) {
        return false;
    }
    mm::mtl::PtrSingleton<fw::EffectManager>::sys()->setCategory(handle, fw::EF_CATEGORY(1));
    effect::SendParam param;
    getMatrix(param.m_mtx, false);
    mm::mtl::PtrSingleton<fw::EffectManager>::sys()->setParam(handle, &param);
    return true;
}

bool GmkBattleChallengePortal::canPopGobInst() const {
    bool result = false;
    if (m_gob == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        const BdatInfo* info = static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo);
        if (info->isPopCommonCondMatched(*this) && isInsideVisibleDist(*m_pos, info) && !isOutsideInvisibleDist(*m_pos, info)) {
            result = true;
        }
    }
    return result;
}

bool GmkBattleChallengePortal::canDepopGobInst() const {
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        const BdatInfo* info = static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo);
        if (!info->isPopCommonCondMatched(*this) || isOutsideInvisibleDist(*m_pos, info)) {
            return true;
        }
    }
    return false;
}

void GmkBattleChallengePortal::seqUpdate(float) {
    if (canPopGobInst()) {
        createGobInst();
    } else if (canDepopGobInst()) {
        disposeGobInst(true);
    }
}

void GmkBattleChallengePortal::seqOpen(float) {
    createEffect(1);
    unsigned int mapId = gf::GfGameManager::getMapID();
    unsigned int se;
    switch (mapId) {
    default:
        se = 0;
        break;
    case 3:
        se = 0xD;
        break;
    case 9:
        se = 0x10;
        break;
    case 0x3A:
        se = 2;
        break;
    }
    if (fw::SoundManager* sound = mm::mtl::PtrSingleton<fw::SoundManager>::sys()) {
        if (gf::GfFieldSound* fieldSound = mm::mtl::PtrSingleton<gf::GfFieldSound>::sys()) {
            sound->playSe(se, fieldSound->getMapPack(), 1.0f, fw::SoundCategory(0));
            Bdat::uVal wait;
            wait.ulong = Bdat::getValCheck(gf::GfDataBdat::getFP(0x7B), 0, 0x55, 8);
            m_timer = wait.real;
            m_seq = &GmkBattleChallengePortal::seqWait;
        }
    }
}

void GmkBattleChallengePortal::seqFinish(float) {}

void GmkBattleChallengePortal::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE* handle) {
    if (event == gf::IGfObjListener::OBJEVT(3) && handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(handle);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
    }
    if (event == gf::IGfObjListener::OBJEVT(3) && m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->kill(m_effectHandle[0]);
        m_effectHandle[0] = 0;
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->kill(m_effectHandle[1]);
        m_effectHandle[1] = 0;
    }
}

void GmkBattleChallengePortal::seqWait(float dt) {
    m_timer -= dt;
    if (m_timer <= 0.0f) {
        m_seq = &GmkBattleChallengePortal::seqFinish;
    }
}

GmkBattleChallengePortal::~GmkBattleChallengePortal() { dispose(); }

gmk::GmkType GmkBattleChallengePortal::getGmkType() const { return TYPE; }

bool GmkBattleChallengePortal::isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }

// ---- GmkCamp, GmkSealedStone (placeholder slot symbols: see their headers)
bool GmkCamp::BdatInfo::isCondMatched() const {
    if (m_condition != 0 && !gf::GfGameCond::isGameCond(m_condition)) {
        return false;
    }
    return true;
}

void GmkCamp::create(const CreateInfo& info) {
    AGmkBase::create(info);
    unsigned char* fp = gf::GfDataBdat::getFP(0x7B);
    unsigned int dist = Bdat::getValCheck(fp, 0, 0x58, 8);
    float popDist = *reinterpret_cast<float*>(&dist);
    m_popDistSq = popDist * popDist;
    unsigned int value = Bdat::getValCheck(fp, 0, 0x5B, 8);
    pad_58 = *reinterpret_cast<float*>(&value);
}

void GmkCamp::dispose() {
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    AGmkBase::dispose();
}

void GmkCamp::debugDraw() const { AGmkBase::debugDraw(); }

bool GmkCamp::isFound() const { return gf::GfGameFlag::getLocal(1, m_createInfo.m_bdatId + 0xD869) != 0; }

GmkCamp::~GmkCamp() { dispose(); }

gmk::GmkType GmkCamp::getGmkType() const { return TYPE; }

void GmkSealedStone::BdatInfo::create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
    m_feedbackEffectName = reinterpret_cast<const char*>(Bdat::getValCheck(bdat.m_fp, "FeedbackEffectName", row, 7));
    m_finishEffectName = reinterpret_cast<const char*>(Bdat::getValCheck(bdat.m_fp, "FinishEffectName", row, 7));
    Bdat::uVal waitTime;
    waitTime.uint = (unsigned int)Bdat::getValCheck(bdat.m_fp, "FinishWaitTime", row, 8);
    m_finishWaitTime = waitTime.real;
    unsigned int visibleXZ = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Visible_XZ", row, 2);
    unsigned short visibleY = Bdat::getValCheck(bdat.m_fp, "Visible_Y", row, 2);
    m_visibleXZSq = (float)visibleXZ * (float)visibleXZ;
    m_visibleYSq = (float)visibleY * (float)visibleY;
    unsigned short invisibleXZ = Bdat::getValCheck(bdat.m_fp, "Invisible_XZ", row, 2);
    if (invisibleXZ <= visibleXZ) {
        invisibleXZ = visibleXZ + 1;
    }
    unsigned short invisibleY = Bdat::getValCheck(bdat.m_fp, "Invisible_Y", row, 2);
    if (invisibleY <= visibleY) {
        invisibleY = visibleY + 1;
    }
    m_invisibleXZSq = (float)invisibleXZ * (float)invisibleXZ;
    m_invisibleYSq = (float)invisibleY * (float)invisibleY;
    if (Bdat::getMember(bdat.m_fp, "Priority") != nullptr) {
        m_priority = (unsigned char)Bdat::getValCheck(bdat.m_fp, "Priority", row, 1);
    }
    Bdat::uVal scale;
    scale.uint = (unsigned int)Bdat::getValCheck(bdat.m_fp, "EffectScale", row, 8);
    m_effectScale = scale.real;
    Bdat::uVal x, y, z;
    x.uint = (unsigned int)Bdat::getValCheck(bdat.m_fp, "EffectOffsetX", row, 8);
    y.uint = (unsigned int)Bdat::getValCheck(bdat.m_fp, "EffectOffsetY", row, 8);
    z.uint = (unsigned int)Bdat::getValCheck(bdat.m_fp, "EffectOffsetZ", row, 8);
    m_effectOffset.x = x.real;
    m_effectOffset.y = y.real;
    m_effectOffset.z = z.real;
}

void GmkSealedStone::create(const CreateInfo& info) {
    AGmkBase::create(info);
    gf::GfDataBdat::getFP(0x7B);
    m_seq = &GmkSealedStone::seqValidateResHandle;
}

void GmkSealedStone::seqValidateResHandle(float) { m_seq = &GmkSealedStone::seqUpdate; }

void GmkSealedStone::dispose() {
    if (m_effectHandle != 0) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->remove(m_effectHandle);
        m_effectHandle = 0;
    }
    disposeGobInst(false);
    AGmkBase::dispose();
}

void GmkSealedStone::debugDraw() const { AGmkBase::debugDraw(); }

void GmkSealedStone::seqUpdate(float) {}

bool GmkSealedStone::canPopGobInst() const {
    if (m_gob == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        const BdatInfo* info = static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo);
        if (isInsideVisibleDist(*m_pos, info)) {
            return !(pad_68 >= 1.0f);
        }
    }
    return false;
}

void GmkSealedStone::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE* handle) {
    if (event == gf::IGfObjListener::OBJEVT(3) && handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(handle);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
    }
    if (event == gf::IGfObjListener::OBJEVT(3)) {
        disposeGobInst(false);
    }
}

GmkSealedStone::~GmkSealedStone() { dispose(); }

gmk::GmkType GmkSealedStone::getGmkType() const { return TYPE; }

// ---- GmkSealedStoneList (the list of kind 0x3F; placeholder slot symbols)
void GmkSealedStoneList::create(const IGmkList::CreateInfo& info) {
    TGmkList::create(info);
#line 641 "D:/Monolithsoft/BF2/prog/application/BF2\\gmk/gmk_sealed_stone/gmk_sealed_stone_impl.h"
    m_effects = new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) GmkSealedStoneEnergyEffectManager();
    m_effects->create();
}

void GmkSealedStoneList::dispose() {
    if (m_effects != nullptr) {
        m_effects->dispose();
        if (m_effects != nullptr) {
            delete m_effects;
            m_effects = nullptr;
        }
    }
    if (pad_2a8 != nullptr) {
        pad_2a8 = nullptr;
    }
    pad_2b8 = 0;
    pad_2a8 = nullptr;
    pad_2b0 = nullptr;
    TGmkList::dispose();
}

void GmkSealedStoneEnergyEffectManager::create() {
    dispose();
    if (fw::EffectPack* pack = gf::GfFieldManager::getEffectPack()) {
        m_effectRes = mm::mtl::PtrSingleton<fw::EffectManager>::sys()->search("ma40a_01_140_dlc", pack);
    }
    m_entries.setAllocator(gf::getAllocator(gf::ALLOCATOR(0)));
    m_entries.reserve(32, 16);
}

void GmkSealedStoneEnergyEffectManager::dispose() {
    if (m_entries.size() != 0) {
        for (EffectInfo& entry : m_entries) {
            mm::mtl::PtrSingleton<fw::EffectManager>::sys()->kill(entry.m_effectHandle);
        }
        m_entries.destroy();
    }
}

}  // namespace gmk
// out of line in the original (update and createEffect call them; neither is written yet)
template mm::mtl::Vector<gmk::GmkSealedStoneEnergyEffectManager::EffectInfo>::iterator
mm::mtl::Vector<gmk::GmkSealedStoneEnergyEffectManager::EffectInfo>::erase(gmk::GmkSealedStoneEnergyEffectManager::EffectInfo*);
template void mm::mtl::Vector<gmk::GmkSealedStoneEnergyEffectManager::EffectInfo>::push_back(
    const gmk::GmkSealedStoneEnergyEffectManager::EffectInfo&);
namespace gmk {

GmkSealedStoneList::~GmkSealedStoneList() { dispose(); }

// ---- kinds holding one game object
void GmkTbox::setTargetable(bool targetable) const {
    gf::GF_OBJ_HANDLE* gob = m_gob;
    if (gob == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    gf::GfObjAcc acc(gob);
    if (acc.m_obj != nullptr) {
        gf::GfObjSetupGimmick* setup = mm::mtl::rttiCast<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(gob)->m_setup);
        if (targetable) {
            setup->pad_6c |= 7;
        } else {
            setup->pad_6c &= ~7;
        }
    }
    if (gf::GfObj* obj = acc.getObj()) {
        if (targetable) {
            obj->pad_110 |= 7;
        } else {
            obj->pad_110 &= ~7;
        }
    }
}

void GmkTbox::create(const CreateInfo& info) {
    AGmkBase::create(info);
    if (gf::GfGameManager::isGameTypeIra() && getBdatInfo()->m_noponBarrel &&
        gf::GfGameFlag::getLocal(1, m_createInfo.m_bdatId + 54134) != 0) {
        gf::GfGameFlag::setLocal(2, m_createInfo.m_bdatId + 31765, 1);
    }
}

void GmkTbox::dispose() {
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    AGmkBase::dispose();
}

void GmkTbox::onGobEvent(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle) {
    AGmkBase::onGobEvent(evt, handle);
    if (evt == gf::IGfObjListener::OBJEVT(3) && m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
}

void GmkKizunaTalk::dispose() {
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    AGmkBase::dispose();
}

void GmkBlade::bindToGameObj(gf::GF_OBJ_HANDLE* handle) const {
    {
        gf::GfObjAcc acc(handle);
        acc.setUserData(gf::GfObjUserData(0), reinterpret_cast<unsigned long>(this));
    }
    gf::GfObjAcc acc(handle);
    if (gf::GfObj* obj = acc.getObj()) {
        if (gf::GfComBehaviorNpc* behavior = obj->getComponent<gf::GfComBehaviorNpc>(6)) {
            behavior->validateBindedGmkInstInfo(false);
        }
    }
}

void GmkBlade::dispose() {
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    AGmkBase::dispose();
}

void GmkGrave::dispose() {
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    AGmkBase::dispose();
}

void GmkGrave::onGobEvent(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle) {
    AGmkBase::onGobEvent(evt, handle);
    if (evt == gf::IGfObjListener::OBJEVT(3) && m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
}

GmkGrave::~GmkGrave() { dispose(); }

bool GmkGrave::reqPopEnemy() const {
    if (reqPopEnemy<GmkEnemy>()) {
        return true;
    }
    return reqPopEnemy<GmkRoutedEnemy>();
}

GmkTbox::~GmkTbox() { dispose(); }

GmkKizunaTalk::~GmkKizunaTalk() { dispose(); }

void GmkKizunaTalk::create(const CreateInfo& info) {
    AGmkBase::create(info);
    Bdat::uVal popDist;
    popDist.ulong = Bdat::getValCheck(gf::GfDataBdat::getFP(0x7B), 0, 0x1E, 8);
    m_popDistSq = popDist.real * popDist.real;
}

void GmkKizunaTalk::debugDraw() const {
    if (isValid()) {
        static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo)->isCondMatched();
    }
}

GmkBlade::~GmkBlade() { dispose(); }

// 1.0.0's out-of-line member; 3.0.1 inlines it (it reads m_current again through the singleton)
inline void GmkBgmCondInfoManager::applyFieldBgm() const {
    unsigned int bgmID = 0;
    if (m_current != nullptr) {
        bgmID = static_cast<const GmkAreaBgm::BdatInfo*>(sys()->m_current->m_owner->m_createInfo.m_bdatInfo)->m_bgmCondition;
    }
    mm::mtl::PtrSingleton<gf::GfFieldBgm>::sys()->setGimmickBgmID(bgmID);
}

inline void GmkBgmCondInfoManager::removeInfo(GmkBgmCondInfo* info) {
    if (info != nullptr && info->intoNode()) {
        if (sys() != nullptr) {
            sys()->m_list.remove(info);
            sys()->m_current = sys()->m_list.empty() ? nullptr : static_cast<GmkBgmCondInfo*>(sys()->m_list.m_root.m_next);
            sys()->applyFieldBgm();
        }
    }
}

inline void GmkBgmCondInfo::dispose() { GmkBgmCondInfoManager::removeInfo(this); }

// its address follows the template code's (0x71005D852C); kept next to its users
GmkBgmCondInfo::~GmkBgmCondInfo() { dispose(); }

void GmkAreaBgm::create(const CreateInfo& info) {
    AGmkBase::create(info);
    createBgmCondInfos();
}

void GmkAreaBgm::dispose() {
    for (int i = 0; i < 4; i++) {
        m_condInfos[i].dispose();
    }
    pad_160 = nullptr;
    m_phantom.dispose();
    AGmkBase::dispose();
}

void GmkAreaBgm::onLeavePhantom(const IGmkPhantomEventListener::OnLeaveInfo&) {
    for (int i = 0; i < 4; i++) {
        m_condInfos[i].dispose();
    }
}

void GmkSe::dispose() {
    if (m_seHandle != 0) {
        mm::mtl::PtrSingleton<fw::SoundManager>::sys()->stopSe(m_seHandle, 1.0f);
        m_seHandle = 0;
        TGmkActiveList<GmkSe>::removeGmk(this);
    }
    AGmkBase::dispose();
}

GmkSe::~GmkSe() { dispose(); }

void GmkSe::debugDraw() const {
    if (isValid() && m_popCondMatched) {
        mm::Mat44 mtx;
        mtx.setTrans(*m_pos);
        const Data* data = getData();
        fw::debug::drawCircleLine(mtx, data->pad_4, mm::Col4::blue);
        fw::debug::drawCircleLine(mtx, data->pad_0, mm::Col4::red);
    }
}

void GmkSeLine::dispose() {
    if (m_seHandle != 0) {
        mm::mtl::PtrSingleton<fw::SoundManager>::sys()->stopSe(m_seHandle, 1.0f);
        m_seHandle = 0;
        TGmkActiveList<GmkSeLine>::removeGmk(this);
    }
    AGmkBase::dispose();
}

GmkSeLine::~GmkSeLine() { dispose(); }

void GmkSeLine::update(float) {
    debugUpdateMmf();
    if (!isValid()) {
        return;
    }
    m_popCondMatched = getBdatInfo()->isPopCondMatched();
    if (m_seHandle == 0) {
        if (m_popCondMatched && isPlayerInsideAabb()) {
            createInst();
            return;
        }
        if (m_seHandle == 0) {
            return;
        }
    }
    if (m_popCondMatched && isPlayerInsideAabb()) {
        return;
    }
    if (m_seHandle != 0) {
        mm::mtl::PtrSingleton<fw::SoundManager>::sys()->stopSe(m_seHandle, 1.0f);
        m_seHandle = 0;
        TGmkActiveList<GmkSeLine>::removeGmk(this);
    }
}

bool GmkSeLine::isPlayerInsideAabb() const {
    if (!isPlayerExist()) {
        return false;
    }
    const mm::Vec3& pos = getPlayerPos();
    const Data* data = getData();
    return data->m_aabbMin[0] <= pos.x && pos.x < data->m_aabbMax[0] && data->m_aabbMin[1] <= pos.y &&
           pos.y < data->m_aabbMax[1] && data->m_aabbMin[2] <= pos.z && pos.z < data->m_aabbMax[2];
}

void GmkTrigger::create(const CreateInfo& info) {
    AGmkBase::create(info);
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set == nullptr || !set->m_createInfo.m_flag) {
        m_phantom.create(*this, nullptr, false);
    }
    applyPopCondMatched(false);
    m_seq = &GmkTrigger::seqWaitToValidLinkGmkList;
}

void GmkTrigger::dispose() {
    m_seq = nullptr;
    m_phantom.dispose();
    AGmkBase::dispose();
}

GmkTrigger::~GmkTrigger() { dispose(); }

void GmkEvent::disposeGmkPhantom() {
    TGmkActiveList<GmkEvent>::removeGmk(this);
    m_phantom.dispose();
}

void GmkTutorial::disposeGmkPhantom() {
    TGmkActiveList<GmkTutorial>::removeGmk(this);
    m_phantom.dispose();
}

void GmkEvent::updateInActiveList(float) {
    if (!m_phantom.pad_83) {
        return;
    }
    if (!getBdatInfo()->isCondMatched()) {
        return;
    }
    if (!gf::GfGameManager::isPlayEventOK() || gf::GfManager::isExecModeThater() || pad_f1) {
        return;
    }
    if (gf::GfPlayFactory::createOneEventForGimmick(getBdatInfo()->m_eventId)) {
        pad_f1 = true;
        pad_f2 = false;
        gf::SCOM_QUEST_REACH::createArrivePlace(m_createInfo.m_bdatId);
    }
}

void GmkEvent::dispose() {
    pad_f2 = false;
    pad_f1 = false;
    m_isCondMatched = false;
    disposeGmkPhantom();
    AGmkBase::dispose();
}

GmkEvent::~GmkEvent() { dispose(); }

void GmkTutorial::dispose() {
    pad_f0 = 0;
    disposeGmkPhantom();
    AGmkBase::dispose();
}

GmkTutorial::~GmkTutorial() { dispose(); }

void GmkMapObj::onGobEvent(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle) {
    AGmkBase::onGobEvent(evt, handle);
    if (evt == gf::IGfObjListener::OBJEVT(3)) {
        disposeGobInst(false);
    }
}

void GmkMapObj::dispose() {
    disposeGobInst(false);
    AGmkBase::dispose();
}

void GmkMapObj::disposeGobInst(bool req) {
    gf::GF_OBJ_HANDLE* gob = m_gobInst;
    if (gob == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    if (req && m_disposeWait > 0.0f) {
        float wait = m_disposeWait;
        unsigned int arg = m_disposeArg;
        gf::GfObjAcc acc(gob);
        if (acc.getObj() != nullptr && !acc.isDestroy() && !acc.testFlag(0x11)) {
            gf::SCOM_DESTROY_GAME_OBJ::create(gob, wait, arg);
        }
        m_disposeWait = 0.0f;
    } else {
        {
            gf::GfObjAcc acc(gob);
            if (acc.m_obj != nullptr) {
                acc.setUserData(gf::GfObjUserData(0), 0);
            }
        }
        gmk::disposeGobInst(m_gobInst, 0.0f);
        m_gobInst = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
}

void GmkMapObj::update(float dt) {
    AGmkBase::update(dt);
    if (!isValid() || !isInterestPosExist()) {
        return;
    }
    if (m_gobInst == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) &&
        static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo)->isPopCondMatched(*m_pos) && (!pad_51 || pad_52)) {
        createGobInst();
    } else if (m_gobInst != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) &&
               (static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo)->isDepopCondMatched(*m_pos) || (pad_51 && !pad_52))) {
        disposeGobInst(true);
    }
}

void GmkMapObj::createGobInst() {
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set != nullptr && set->m_createInfo.m_flag) {
        return;
    }
    disposeGobInst(false);
    CBdatWrapper bdat(m_list->getBindedBdatFp());
    m_gobInst = gf::GfObjFactory::createGmkMapObj(bdat, m_createInfo.m_bdatId);
    {
        gf::GfObjAcc acc(m_gobInst);
        acc.setUserData(gf::GfObjUserData(0), reinterpret_cast<unsigned long>(this));
    }
    gf::GF_OBJ_HANDLE* handle = m_gobInst;
    if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        bool disp;
        if (pad_50) {
            // the original calls getGmkType here and drops its answer
            getGmkType();
            disp = true;
        } else {
            disp = false;
        }
        gf::GfObjAcc acc(handle);
        if (acc.m_obj != nullptr) {
            acc.setDisp(gf::OBJDISP(8), disp);
        }
    }
    gf::GfObjSetupGimmick* setup = getSetupOf<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(m_gobInst), 8);
    const mm::Vec3* xform = m_pos;
    setup->m_initialPos = xform[0];
    setup->pad_30 = xform[1];
    setup->setInitialScale(m_pos[2].x);
}

GmkMapObj::~GmkMapObj() { dispose(); }

GmkCollision::~GmkCollision() { dispose(); }

void GmkBattleLock::dispose() {
    if (m_effectHandle != 0) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->remove(m_effectHandle);
        m_effectHandle = 0;
    }
    m_collision.dispose();
    AGmkBase::dispose();
}

GmkBattleLock::~GmkBattleLock() { dispose(); }

void GmkBattleLock::createEffect() {
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set != nullptr && set->m_createInfo.m_flag) {
        return;
    }
    if (m_effectHandle != 0) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->remove(m_effectHandle);
        m_effectHandle = 0;
    }
    const unsigned char* data = m_createInfo.m_data;
    switch (m_info->m_shape) {
    case 3:
        m_effectHandle = mm::mtl::PtrSingleton<fw::EffectManager>::sys()->create(
            data[0] ? "cmn_204_001" : "cmn_204_011", nullptr, true);
        break;
    case 4:
        m_effectHandle = mm::mtl::PtrSingleton<fw::EffectManager>::sys()->create(
            data[0] ? "cmn_204_000" : "cmn_204_010", nullptr, true);
        break;
    default:
        return;
    }
    if (m_effectHandle != 0) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->setCategory(m_effectHandle, fw::EF_CATEGORY(1));
        applyEffectParam();
    }
}

void GmkFieldLock::dispose() {
    m_collision.dispose();
    AGmkBase::dispose();
}

GmkFieldLock::~GmkFieldLock() { dispose(); }
void GmkEffect::getLocatorPosRotXYZ(mm::Vec3& pos, mm::Vec3& rot) const {
    pos = m_pos[0];
    rot = m_pos[1];
    const Data* data = getData();
    if (data->m_locatorId >= 0) {
        const IGmkList* list = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param)->m_gmkLists[GmkEffectLocator::TYPE];
        if (list != nullptr && list->isValid()) {
            const AGmkBase* locator = list->getInst(data->m_locatorId);
            pos = locator->m_pos[0];
            rot = locator->m_pos[1];
        }
    }
}

// the gimmick data's show conditions into its conditions (bytes 0x14..0x22)
void GmkEffect::create(const CreateInfo& info) {
    if (info.m_bdatInfo == nullptr) {
        return;
    }
    AGmkBase::create(info);
    const Data* data = getData();
    int time = data->m_time0;
    if (data->m_time1) {
        time |= 2;
    }
    if (data->m_time2) {
        time |= 4;
    }
    if (data->m_time3) {
        time |= 8;
    }
    if (data->m_time4) {
        time |= 0x10;
    }
    if (data->m_time5) {
        time |= 0x20;
    }
    m_popTime.m_time = time;
    unsigned char weather = 0;
    if (data->m_weather0) {
        weather |= 0x10;
    }
    if (data->m_weather1) {
        weather |= 1;
    }
    if (data->m_weather2) {
        weather |= 2;
    }
    if (data->m_weather3) {
        weather |= 4;
    }
    if (data->m_weather4) {
        weather |= 8;
    }
    m_popWeather.m_weather = weather;
    m_popInOutDoor = InOutDoorCond(data->m_inOutDoor0, data->m_inOutDoor1);
    if (data->m_cloud[0]) {
        if (!data->m_cloud[1]) {
            m_popCloud.m_cloudSea = 0;
        }
    } else if (data->m_cloud[1]) {
        m_popCloud.m_cloudSea = 1;
    }
    m_seq = &GmkEffect::seqValidateResHandle;
}

void GmkEffect::seqValidateResHandle(float) {
    fw::EffectPack* pack = gf::GfFieldManager::getEffectPack();
    if (pack == nullptr) {
        return;
    }
    const char* name = getData()->m_effectName;
    pad_a0 = mm::mtl::PtrSingleton<fw::EffectManager>::sys()->search(name, pack);
    if (pad_a0 == nullptr) {
        return;
    }
    pad_a8 = mm::mtl::PtrSingleton<fw::EffectManager>::sys()->containsCamAxis(pad_a0);
    m_seq = &GmkEffect::seqUpdate;
}

void GmkEffect::dispose() {
    m_flags.reset();
    if (m_effectHandle != 0) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->remove(m_effectHandle);
        m_effectHandle = 0;
    }
    AGmkBase::dispose();
    m_seq = nullptr;
    pad_a0 = nullptr;
}

void GmkEffect::update(float dt) {
    AGmkBase::update(dt);
    if (isValid()) {
        updatePopDepopCond();
        if (m_seq) {
            (this->*m_seq)(dt);
        }
    }
}

GmkEffect::~GmkEffect() { dispose(); }

// getYSnapPos with the pop finders' line test (all four build the same config inline; the name is not the
// original's)
static inline bool getYSnapPosForPop(mm::Vec3& pos, const mm::Vec3& from, float length) {
    fw::ColiCheckConfig config;
    config.m_mode = 2;
    config.m_flags = 9;
    config.m_mask = 0x80000020;
    return getYSnapPos(pos, from, length, config);
}

// the row's pop conditions (the flag, time and condition columns only for a row with no group); the gimmick is
// not read
void GmkMobInsts::BdatInfo::create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
    m_group = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Group", row, 2);
    m_squadId = (unsigned short)Bdat::getValCheck(bdat.m_fp, "squadId", row, 2);
    if (m_group == 0) {
        m_scenarioFlag = ScenarioFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMin", row, 2),
                                          (unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMax", row, 2));
        m_questFlag = QuestFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "QuestFlag", row, 2),
                                    (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMin", row, 1),
                                    (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMax", row, 1));
        m_timeRange.m_time = (unsigned short)Bdat::getValCheck(bdat.m_fp, "TimeRange", row, 2);
        m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
    }
    m_mot = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Mot", row, 2);
    m_collision = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Collision", row, 2);
    m_reactionRange = (unsigned short)Bdat::getValCheck(bdat.m_fp, "ReactionRange", row, 2);
    m_reactionPercent = (unsigned short)Bdat::getValCheck(bdat.m_fp, "ReactionPercent", row, 2);
    m_reactionMot = (unsigned short)Bdat::getValCheck(bdat.m_fp, "ReactionMot", row, 2);
    m_battleReaction = (unsigned short)Bdat::getValCheck(bdat.m_fp, "BattleReaction", row, 2);
    unsigned int visibleXZ = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Visible_XZ", row, 2);
    unsigned short visibleY = Bdat::getValCheck(bdat.m_fp, "Visible_Y", row, 2);
    m_visible.m_horizontalSq = (float)visibleXZ * (float)visibleXZ;
    m_visible.m_verticalSq = (float)visibleY * (float)visibleY;
    unsigned short invisibleXZ = Bdat::getValCheck(bdat.m_fp, "Invisible_XZ", row, 2);
    if (invisibleXZ <= visibleXZ) {
        invisibleXZ = visibleXZ + 1;
    }
    unsigned short invisibleY = Bdat::getValCheck(bdat.m_fp, "Invisible_Y", row, 2);
    if (invisibleY <= visibleY) {
        invisibleY = visibleY + 1;
    }
    m_invisible.m_horizontalSq = (float)invisibleXZ * (float)invisibleXZ;
    m_invisible.m_verticalSq = (float)invisibleY * (float)invisibleY;
}

// a squad with room places the objects; else the gimmick's position (m_popInfo.m_popNum 1) or a point in its
// shape; the rotation is the gimmick's; snapped on the ground when its data's first byte says so
bool GmkMob::PopXformFinder::findPosRot(mm::Vec3& pos, mm::Vec3& rot) const {
    GmkSquad* squad = m_gmk->m_insts.m_squad;
    unsigned int num;
    if (squad != nullptr && (num = m_gmk->getGobInstNum()) != 0 && num < squad->pad_70) {
        gf::GfObjAcc acc(m_gmk->getGobInst(0));
        if (!acc.isValidTransform()) {
            return false;
        }
        squad->getPosRotY(pos, rot.y, m_gmk->getGobInstNum());
        rot.z = 0.0f;
        rot.x = 0.0f;
    } else if (m_gmk->m_insts.m_popInfo.m_popNum == 1) {
        pos = *m_gmk->m_pos;
    } else {
        m_gmk->getPositionInShape(pos, false);
    }
    rot = m_gmk->m_pos[1];
    if (*m_gmk->m_createInfo.m_data != 0) {
        float half = m_gmk->getYSnapRayLength() * 0.5f;
        mm::Vec3 from;
        from.x = pos.x;
        from.y = pos.y + half;
        from.z = pos.z;
        if (!getYSnapPosForPop(pos, from, half + half)) {
            return false;
        }
    }
    return true;
}

inline void GmkMobInsts::create(AGmkBase* gmk, unsigned char* bdatFp, int bdatId) {
    dispose();
    m_gmk = gmk;
    m_bdatFp = bdatFp;
    m_bdatId = bdatId;
    m_bdatInfo.create(bdatFp, bdatId, *gmk);
#line 513 "D:/Monolithsoft/BF2/prog/application/BF2\\gmk/gmk_mob/gmk_mob_impl.h"
    m_gobInsts = new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) mm::mtl::Vector<gf::GF_OBJ_HANDLE*>();
    createSquad(m_bdatInfo.m_squadId);
    m_seq = &GmkMobInsts::seqUpdatePopDepop;
}

// with a row: the insts from the list's table and the row
void GmkMob::create(const AGmkBase::CreateInfo& info) {
    if (info.m_bdatInfo != nullptr) {
        AGmkBase::create(info);
        unsigned char* bdatFp = m_list->getBindedBdatFp();
        m_insts.create(this, bdatFp, info.m_bdatId);
    }
}

void GmkMob::dispose() {
    m_insts.dispose();
    AGmkBase::dispose();
}

GmkMob::~GmkMob() { dispose(); }

// the insts pop and depop around the gimmick's position
void GmkMob::update(float dt) {
    AGmkBase::update(dt);
    if (isValid()) {
        GmkMobInsts::UpdateInfo updateInfo;
        PopXformFinder finder(this);
        updateInfo.m_dt = dt;
        updateInfo.m_pos = m_pos;
        updateInfo.m_finder = &finder;
        if (m_insts.isValid()) {
            if (m_insts.m_seq) {
                (m_insts.*m_insts.m_seq)(updateInfo);
            }
        }
    }
}

// a destroyed object leaves the insts' objects
void GmkMob::onGobEvent(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle) {
    AGmkBase::onGobEvent(evt, handle);
    if (evt == gf::IGfObjListener::OBJEVT(3) && handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        m_insts.removeGobInst(handle);
    }
}

void GmkMobInsts::validateDisp(gf::GF_OBJ_HANDLE* handle) const {
    if (AGmkBase* gmk = getBindedGmkInst(handle)) {
        gmk->getGmkType();
        bool disp = pad_a0;
        gf::GfObjAcc acc(handle);
        if (acc.m_obj != nullptr) {
            acc.setDisp(gf::OBJDISP(8), disp);
        }
    }
}

// the squad released, the objects destroyed and their list freed; the sequence and flag bits 0..2 cleared
void GmkMobInsts::dispose() {
    m_seq = nullptr;
    m_flags &= ~7UL;
    if (m_squad != nullptr) {
        m_squad->release();
        m_squad = nullptr;
    }
    disposeGobInsts(false);
    if (m_gobInsts != nullptr) {
        delete m_gobInsts;
        m_gobInsts = nullptr;
    }
    m_gmk = nullptr;
    m_bdatFp = nullptr;
    m_bdatId = -1;
}

// a squad for the row's squadId (its gimmick set's row and the id less one)
void GmkMobInsts::createSquad(unsigned short squadId) {
    if (m_squad != nullptr) {
        m_squad->release();
        m_squad = nullptr;
    }
    if (squadId != 0) {
        GmkSquad::CreateInfo info;
        info.m_gmkSetId = static_cast<const GmkSet*>(m_gmk->m_list->getCreateInfo().m_param)->m_createInfo.m_bdatId;
        info.pad_4 = squadId - 1;
#line 716 "D:/Monolithsoft/BF2/prog/application/BF2\\gmk/gmk_mob/gmk_mob_impl.h"
        GmkSquad* squad = new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) GmkSquad;
        squad->create(info);
        m_squad = squad;
        squad->addRef();
    }
}

// while the interest position exists: the objects pop when the row's conditions hold within the visible range and
// fade out when the conditions fail or the position leaves the invisible range; one more pops while it is in range
void GmkMobInsts::seqUpdatePopDepop(const UpdateInfo& info) {
    if (!isInterestPosExist()) {
        return;
    }
    updatePopDepopCond(info);
    if (!hasGobInst() && (m_flags & 3) == 3) {
        createGobInsts();
        unsigned int capacity = m_gobInsts->capacity();
        info.m_finder->onCreateGobInsts(capacity);
    } else if (hasGobInst() && (m_flags & 5) != 5) {
        disposeGobInsts(true);
    }
    if (m_flags & 2) {
        m_popInfo.update(*this, *m_gobInsts, *info.m_finder);
    }
}

// fade: the live objects fade out and the sequence waits for them; else they are destroyed at once and the list is
// freed
void GmkMobInsts::disposeGobInsts(bool fade) {
    if (hasGobInst()) {
        unsigned long num = m_gobInsts->size();
        for (unsigned long i = 0; i < num; i++) {
            gf::GF_OBJ_HANDLE* handle = (*m_gobInsts)[i];
            if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
                gf::GfObjAcc acc(handle);
                if (fade) {
                    if (acc.getObj() != nullptr && !acc.isDestroy() && !acc.testFlag(0x11)) {
                        gf::SCOM_DESTROY_GAME_OBJ::create(handle, 1.0f, 0);
                    }
                } else {
                    if (acc.m_obj != nullptr) {
                        acc.setUserData(gf::GfObjUserData(0), 0);
                    }
                    gf::GfObjUtil::destroy(handle);
                }
            }
        }
        if (fade) {
            m_seq = &GmkMobInsts::seqWaitToFadeOutOfGobInst;
            return;
        }
        m_gobInsts->destroy();
        m_popInfo.m_popNum = 0;
        m_popInfo.m_mobIds.clear();
    }
}

// the pop row read again and the list made room for its count
void GmkMobInsts::createGobInsts() {
    disposeGobInsts(false);
    m_popInfo.create(m_bdatFp, m_bdatId);
    m_gobInsts->destroy();
    m_gobInsts->setAllocator(gf::getAllocator(gf::ALLOCATOR(0)));
    m_gobInsts->reserve(static_cast<unsigned int>(m_popInfo.m_popNum));
}

// back to popping once every object has faded out
void GmkMobInsts::seqWaitToFadeOutOfGobInst(const UpdateInfo& info) {
    if (getGobInstNum() == 0) {
        m_gobInsts->destroy();
        m_popInfo.m_popNum = 0;
        m_popInfo.m_mobIds.clear();
        m_seq = &GmkMobInsts::seqUpdatePopDepop;
    }
}

// within its visible distances of the interest position, and that within the mob slots' pop distance limit
bool GmkMobInsts::BdatInfo::isPopDistCondMatched(const mm::Vec3& pos) const {
    if (!m_visible.isMatch(pos)) {
        return false;
    }
    if (!isInterestPosExist()) {
        return false;
    }
    const mm::Vec3& interest = getInterestPos();
    float dx = interest.x - pos.x;
    float dy = interest.y - pos.y;
    float dz = interest.z - pos.z;
    float distSq = dx * dx + dy * dy + dz * dz;
    gf::GfFieldGimmick* fieldGimmick = mm::mtl::PtrSingleton<gf::GfFieldGimmick>::sys();
    float limit = fieldGimmick != nullptr ? fieldGimmick->m_mobSlotMgr.m_popDistSqLimit : 1.0e12f;
    return !(limit < distSq);
}

void GmkMobInsts::validateDisp() const {
    if (isValid()) {
        unsigned int num = getGobInstNum();
        for (unsigned int i = 0; i < num; i++) {
            validateDisp((*m_gobInsts)[i]);
        }
    }
}

void GmkRoutedMob::PopXformFinder::onPopGob(gf::GF_OBJ_HANDLE* handle) const {
    if (m_navi != nullptr) {
        m_gmk->bindRouteNavi(handle, *m_navi);
    }
}

void GmkRoutedMob::bindRouteNavi(gf::GF_OBJ_HANDLE* handle, GmkRouteNavi& navi) {
    if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        for (std::pair<gf::GF_OBJ_HANDLE*, GmkRouteNavi>* it = m_navis.begin(); it != m_navis.end(); ++it) {
            if (it->first == handle) {
                it->first = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
                it->second.dispose();
                break;
            }
        }
    }
    for (std::pair<gf::GF_OBJ_HANDLE*, GmkRouteNavi>* it = m_navis.begin(); it != m_navis.end(); ++it) {
        if (&it->second == &navi) {
            it->first = handle;
            return;
        }
    }
}

// with a row: the route, then the insts from the list's table and the row
void GmkRoutedMob::create(const AGmkBase::CreateInfo& info) {
    if (info.m_bdatInfo != nullptr) {
        GmkRoute::create(info);
        unsigned char* bdatFp = m_list->getBindedBdatFp();
        m_insts.create(this, bdatFp, info.m_bdatId);
    }
}

void GmkRoutedMob::dispose() {
    if (m_navis.size() != 0) {
        m_navis.destroy();
    }
    m_insts.dispose();
    GmkRoute::dispose();
}

GmkRoutedMob::~GmkRoutedMob() { dispose(); }

// the insts pop and depop by the route position nearest to the player
void GmkRoutedMob::update(float dt) {
    AGmkBase::update(dt);
    if (isValid() && isPlayerExist()) {
        mm::Vec3 pos;
        if (getNearestPos(pos, getPlayerPos())) {
            GmkMobInsts::UpdateInfo updateInfo;
            PopXformFinder finder(this);
            updateInfo.m_dt = dt;
            updateInfo.m_pos = &pos;
            updateInfo.m_finder = &finder;
            if (m_insts.isValid()) {
                if (m_insts.m_seq) {
                    (m_insts.*m_insts.m_seq)(updateInfo);
                }
            }
        }
    }
}

void GmkRoutedMob::debugDraw() const {
    if (isValid()) {
        bool popped = m_insts.m_flags & 1;
        if (isValid()) {
            if (popped) {
                debugDrawRoute(mm::Col4(mm::Col4::yellow));
            } else {
                debugDrawRoute(mm::Col4(mm::Col4::gray));
            }
        }
    }
}

void GmkRoutedMob::createRouteNavis(unsigned int num) {
    if (m_navis.size() != 0) {
        m_navis.destroy();
    }
    m_navis.setAllocator(gf::getAllocator(gf::ALLOCATOR(0)));
    m_navis.reserve(num);
    m_navis.resize(num);
    if (m_navis.size() != 0) {
        for (std::pair<gf::GF_OBJ_HANDLE*, GmkRouteNavi>* it = m_navis.begin(); it != m_navis.end(); ++it) {
            it->first = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        }
    }
}

// a destroyed object leaves its route navigator and the insts' objects
void GmkRoutedMob::onGobEvent(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle) {
    AGmkBase::onGobEvent(evt, handle);
    if (evt == gf::IGfObjListener::OBJEVT(3) && handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        for (std::pair<gf::GF_OBJ_HANDLE*, GmkRouteNavi>* it = m_navis.begin(); it != m_navis.end(); ++it) {
            if (it->first == handle) {
                it->first = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
                it->second.dispose();
                break;
            }
        }
        m_insts.removeGobInst(handle);
    }
}

void GmkLandmark::dispose() {
    disposeGmkPhantom();
    AGmkBase::dispose();
}

void GmkLandmark::disposeGmkPhantom() {
    m_phantom.dispose();
    if (!pad_f1) {
        return;
    }
    pad_f1 = false;
    gf::GfMenuObjLocationTelop::cancel();
    if (GmkLandmarkManager::sys() != nullptr) {
        GmkLandmarkManager::sys()->m_list.remove(this);
        if (GmkLandmarkManager::sys()->m_list.empty()) {
            GmkLandmarkManager::sys()->m_currentLandmark = nullptr;
        } else {
            GmkLandmarkManager::sys()->m_currentLandmark = GmkLandmarkManager::sys()->m_list.front();
        }
    }
}

void GmkLandmark::update(float) {
    debugUpdateMmf();
    if (!isValid()) {
        return;
    }
    bool matched = getBdatInfo()->isCondMatched();
    if (pad_f0 != matched) {
        if (matched) {
            const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
            if (set == nullptr || !set->m_createInfo.m_flag) {
                m_phantom.create(*this, this, false);
            }
        } else {
            disposeGmkPhantom();
        }
        pad_f0 = matched;
    }
    if (m_phantom.pad_83 && gf::GfGameManager::isLandmarkUiOK()) {
        beginEvent();
    }
}

GmkLandmark::~GmkLandmark() { dispose(); }

// destructors whose original D2 is AGmkBase's (the table's slot 0 holds AGmkBase::~AGmkBase: clang emits the empty
// body as an alias of the base's)
GmkEffectLocator::~GmkEffectLocator() {}
GmkSeLinePoint::~GmkSeLinePoint() {}

GmkNpc::~GmkNpc() { dispose(); }

unsigned char* GmkNpc::getBindedBdatFp() const { return m_list->getBindedBdatFp(); }

int GmkNpc::getBindedBdatId() const { return m_createInfo.m_bdatId; }

void GmkNpc::debugDraw() const {
    if (isValid()) {
        static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo)->isPopCommonCondMatched(*this);
    }
}

// clears the game object's user data (the object stays)
void GmkNpc::unbindToGameObj(gf::GF_OBJ_HANDLE* handle) const {
    if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(handle);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
    }
}


void GmkNpc::BdatInfo::create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
    m_group = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Group", row, 2);
    m_battleReaction = (unsigned short)Bdat::getValCheck(bdat.m_fp, "BattleReaction", row, 2);
    if (m_group == 0) {
        m_scenarioFlag = ScenarioFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMin", row, 2),
                                          (unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMax", row, 2));
        m_questFlag = QuestFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "QuestFlag", row, 2),
                                    (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMin", row, 1),
                                    (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMax", row, 1));
        m_timeRange.m_time = (unsigned short)Bdat::getValCheck(bdat.m_fp, "TimeRange", row, 2);
        m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
    }
    unsigned int visibleXZ = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Visible_XZ", row, 2);
    unsigned short visibleY = Bdat::getValCheck(bdat.m_fp, "Visible_Y", row, 2);
    m_visibleXZSq = (float)visibleXZ * (float)visibleXZ;
    m_visibleYSq = (float)visibleY * (float)visibleY;
    unsigned short invisibleXZ = Bdat::getValCheck(bdat.m_fp, "Invisible_XZ", row, 2);
    if (invisibleXZ <= visibleXZ) {
        invisibleXZ = visibleXZ + 1;
    }
    unsigned short invisibleY = Bdat::getValCheck(bdat.m_fp, "Invisible_Y", row, 2);
    if (invisibleY <= visibleY) {
        invisibleY = visibleY + 1;
    }
    m_invisibleXZSq = (float)invisibleXZ * (float)invisibleXZ;
    m_invisibleYSq = (float)invisibleY * (float)invisibleY;
}


unsigned char* GmkRoutedNpc::getBindedBdatFp() const { return m_list->getBindedBdatFp(); }

int GmkRoutedNpc::getBindedBdatId() const { return m_createInfo.m_bdatId; }

void GmkNpcList::createGmk(void* data) {
    TGmkList::createGmk(data);
    GmkSet* set = static_cast<GmkSet*>(getCreateInfo().m_param);
    unsigned int num = getInstNum();
    for (unsigned int i = 0; i < num; i++) {
        set->m_npcManager.addGmkNpc(&m_gmks[i]);
    }
}

void GmkNpcList::disposeGmk() {
    GmkSet* set = static_cast<GmkSet*>(getCreateInfo().m_param);
    if (set != nullptr) {
        unsigned int num = getInstNum();
        for (unsigned int i = 0; i < num; i++) {
            set->m_npcManager.removeGmkNpc(&m_gmks[i]);
        }
    }
    TGmkList::disposeGmk();
}

GmkNpcList::~GmkNpcList() {
    dispose();
}

void GmkRoutedNpcList::createGmk(void* data) {
    TGmkList::createGmk(data);
    GmkSet* set = static_cast<GmkSet*>(getCreateInfo().m_param);
    unsigned int num = getInstNum();
    for (unsigned int i = 0; i < num; i++) {
        set->m_npcManager.addGmkNpc(&m_gmks[i]);
    }
}

void GmkRoutedNpcList::disposeGmk() {
    GmkSet* set = static_cast<GmkSet*>(getCreateInfo().m_param);
    if (set != nullptr) {
        unsigned int num = getInstNum();
        for (unsigned int i = 0; i < num; i++) {
            set->m_npcManager.removeGmkNpc(&m_gmks[i]);
        }
    }
    TGmkList::disposeGmk();
}

GmkRoutedNpcList::~GmkRoutedNpcList() {
    dispose();
}

GmkManager::GmkManager() : m_bdatFp(nullptr), pad_198(0), m_seq(nullptr) {}

void GmkCollision::enter(const fw::IColiEventListener::EnterInfo& info) {
    fw::ColiUserData* userData = info.m_other->m_userData;
    if (userData != nullptr && userData->getRTTI()->isKindOf(&gf::GfComCollider::UserData::m_rtti)) {
        gf::GfComCollider* collider = static_cast<gf::GfComCollider::UserData*>(userData)->m_owner;
        if (static_cast<gf::GfObj*>(collider->m_owner)->m_handle == gf::GfGameManager::getPartyLeader()) {
            m_leaderEntered = true;
            m_leaderInside = true;
        }
    }
}

void GmkCollision::leave(const fw::IColiEventListener::LeaveInfo& info) {
    fw::ColiUserData* userData = info.m_other->m_userData;
    if (userData != nullptr && userData->getRTTI()->isKindOf(&gf::GfComCollider::UserData::m_rtti)) {
        gf::GfComCollider* collider = static_cast<gf::GfComCollider::UserData*>(userData)->m_owner;
        if (static_cast<gf::GfObj*>(collider->m_owner)->m_handle == gf::GfGameManager::getPartyLeader()) {
            m_leaderLeft = true;
            m_leaderInside = false;
        }
    }
}

GmkPhantom::~GmkPhantom() {
    if (GmkPhantomManager* manager = GmkPhantomManager::sys()) {
        manager->m_phantoms.remove(this);
    }
    dispose();
}

GmkManager::~GmkManager() {
    dispose();
}

GmkPhantomManager::~GmkPhantomManager() {}

GmkForm::GmkForm(const CreateInfo* info) : pad_0(0) {
    for (int i = 0; i < 6; i++) {
        pad_10[i] = mm::Vec3::zero;
        pad_70[i] = 0.0f;
    }
    if (info != nullptr) {
        create(*info);
    }
}

bool GmkForm::create(const CreateInfo& info) {
    const GmkSet* set = info.m_set;
    bool kind26 = info.pad_c;
    unsigned int index = info.m_index;
    if (kind26) {
        typedef TGmkFormPc<GmkType(26), TGmkFormPcnpc<GmkType(27)> > FormPc;
        const IGmkList* list = set->m_gmkLists[FormPc::TYPE];
        if (list == nullptr || list->getInstNum() <= index) {
            return false;
        }
        const AGmkBase* gmk = list->getInst(index);
        if (gmk == nullptr || !create<FormPc, TGmkFormPcnpc<GmkType(27)> >(*static_cast<const FormPc*>(gmk))) {
            return false;
        }
    } else {
        typedef TGmkFormPc<GmkType(24), TGmkFormPcnpc<GmkType(25)> > FormPc;
        const IGmkList* list = set->m_gmkLists[FormPc::TYPE];
        if (list == nullptr || list->getInstNum() <= index) {
            return false;
        }
        const AGmkBase* gmk = list->getInst(index);
        if (gmk == nullptr || !create<FormPc, TGmkFormPcnpc<GmkType(25)> >(*static_cast<const FormPc*>(gmk))) {
            return false;
        }
    }
    validatePosRotY();
    return true;
}

void GmkForm::getPosRotY(mm::Vec3& pos, float& rotY, unsigned int index) const {
    pos = pad_10[index];
    rotY = pad_70[index];
}

bool GmkForm::create(const mm::Vec3& pos, float rotY) {
    pad_0 = 1;
    pad_10[0] = pos;
    pad_70[0] = rotY;
    validatePosRotY();
    return true;
}

void GmkForm::dispose() { pad_0 = 0; }

GmkBdat::~GmkBdat() {
    dispose();
}

void GmkBdat::seqWaitResourceLoaded(float) {
    if (m_resource->valid()) {
        m_assetData = m_resource->getAssetData();
        if (m_assetData == nullptr || fw::BdatManager::isExistBdat(m_createInfo.m_param)) {
            dispose();
            return;
        }
        fw::BdatManager::loadBdatFromMemory(m_createInfo.m_param, m_assetData);
        m_seq = nullptr;
    }
}

GmkLandmarkManager::~GmkLandmarkManager() {
    dispose();
}

void GmkLandmark::onLeavePhantom(const IGmkPhantomEventListener::OnLeaveInfo&) {
    if (gf::GfGameManager::isGameTypeIra() && gf::GfGameManager::getControlMoverForGimmick() == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    if (!pad_f1) {
        return;
    }
    pad_f1 = false;
    gf::GfMenuObjLocationTelop::cancel();
    if (GmkLandmarkManager::sys() != nullptr) {
        GmkLandmarkManager::sys()->m_list.remove(this);
        if (GmkLandmarkManager::sys()->m_list.empty()) {
            GmkLandmarkManager::sys()->m_currentLandmark = nullptr;
        } else {
            GmkLandmarkManager::sys()->m_currentLandmark = GmkLandmarkManager::sys()->m_list.front();
        }
    }
}

void GmkLandmarkManager::addGmkLandmark(GmkLandmark* landmark) {
    unsigned char category = landmark->getBdatInfo()->m_category;
    GmkLandmarkManager* manager = sys();
    mm::mtl::IntrusiveList<GmkLandmark>::iterator it = manager->m_list.begin();
    for (; it != manager->m_list.end(); ++it) {
        if (it->getBdatInfo()->m_category >= category) {
            manager->m_list.insert_before(it, landmark);
            goto inserted;
        }
    }
    manager->m_list.push_back(landmark);
inserted:
    sys()->m_currentLandmark = sys()->m_list.front();
}

void GmkLandmarkManager::dispose() {
    m_currentLandmark = nullptr;
    m_list.clear();
}

GmkSquadManager::~GmkSquadManager() {
    clearGmkSquads();
}

// the list emptied by its own loop (written out here: the list's clear() inlined lays the size check out the other way)
GmkBgmCondInfoManager::~GmkBgmCondInfoManager() {
    m_current = nullptr;
    for (mm::mtl::IntrusiveList<GmkBgmCondInfo>::iterator it = m_list.begin(); it != m_list.end();) {
        it = m_list.erase(it);
    }
}

void GmkTbox::BdatInfo::create(unsigned char* fp, int row, const AGmkBase& gmk) {
    m_condition = (unsigned short)Bdat::getValCheck(fp, "Condition", row, 2);
    m_dig = Bdat::getFlagVal(fp, "flag", row, "Digflg") != 0;
    m_msgVisible = (unsigned char)Bdat::getValCheck(fp, "msgVisible", row, 1);
    m_msgdigVisible = (unsigned char)Bdat::getValCheck(fp, "msgdigVisible", row, 1);
    {
        unsigned short rscId = Bdat::getValCheck(fp, "RSC_ID", row, 2);
        unsigned char* rscFp = gf::GfDataBdat::getFP(0xAC);
        unsigned short visibleR = Bdat::getValCheck(rscFp, "visible_Radius", rscId, 2);
        m_visibleRadiusSq = (float)visibleR * (float)visibleR;
        unsigned short invisibleR = Bdat::getValCheck(rscFp, "invisible_Radius", rscId, 2);
        m_invisibleRadiusSq = (float)invisibleR * (float)invisibleR;
    }
    {
        unsigned short rscId = Bdat::getValCheck(fp, "RSC_ID", row, 2);
        m_category = Bdat::getFlagVal(gf::GfDataBdat::getFP(0xAC), "flag", rscId, "TBOX_category") != 0;
    }
    if (Bdat::getMember(fp, "DigPopflg") != nullptr) {
        m_digPop = Bdat::getFlagVal(fp, "flag", row, "DigPopflg") != 0;
    }
    if (Bdat::getMember(fp, "NoponBarrel") != nullptr) {
        m_noponBarrel = Bdat::getFlagVal(fp, "flag", row, "NoponBarrel") != 0;
    }
}

bool GmkTbox::BdatInfo::isPopCondMatchedExceptDist() const {
    if (m_condition != 0 && !gf::GfGameCond::isGameCond(m_condition)) {
        return false;
    }
    return true;
}

bool GmkTbox::BdatInfo::isPopCondMatched(const mm::Vec3& pos) const {
    if (!isPopCondMatchedExceptDist() || !DistCond::isMatch(m_visibleRadiusSq, pos)) {
        return false;
    }
    return true;
}

bool GmkTbox::BdatInfo::isDepopCondMatched(const mm::Vec3& pos) const {
    if (isPopCondMatchedExceptDist() && DistCond::isMatch(m_invisibleRadiusSq, pos)) {
        return false;
    }
    return true;
}

void GmkTbox::successToAccess() {
    unsigned int progress;
    if (getBdatInfo()->m_dig && getProgress() == 0) {
        progress = 2;
    } else {
        setTargetable(false);
        progress = 1;
    }
    gf::GfGameFlag::setLocal(2, m_createInfo.m_bdatId + 31765, progress);
    if (gf::GfGameManager::isGameTypeIra() && getBdatInfo()->m_noponBarrel) {
        gf::GfGameFlag::setLocal(1, m_createInfo.m_bdatId + 54134, 1);
    }
}

// gmk::disposeGobInst unless there is no object (the name is not the original's)
static inline void disposeGobInstIfAny(gf::GF_OBJ_HANDLE* gob, float time) {
    if (gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gmk::disposeGobInst(gob, time);
    }
}

void GmkTbox::update(float dt) {
    AGmkBase::update(dt);
    if (!isValid()) {
        return;
    }
    if (!(getBdatInfo()->m_visibleRadiusSq > 0.0f) || !(getBdatInfo()->m_invisibleRadiusSq > 0.0f)) {
        return;
    }
    if (isInterestPosExist()) {
        if (m_gob == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) && !(getBdatInfo()->m_category && getProgress() == 1) &&
            getBdatInfo()->isPopCondMatched(*m_pos)) {
            createGobInst();
        } else if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) && getBdatInfo()->isDepopCondMatched(*m_pos)) {
            disposeGobInstIfAny(m_gob, 1.0f);
        }
    }
    if (getBdatInfo()->m_category && getProgress() == 1 && m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        if (pad_58 < pad_54) {
            pad_58 += dt;
            if (pad_54 <= pad_58) {
                disposeGobInstIfAny(m_gob, 1.0f);
            }
        }
    }
}

void GmkAreaWeather::create(const CreateInfo& info) {
    AGmkBase::create(info);
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set == nullptr || !set->m_createInfo.m_flag) {
        m_phantom.create(*this, nullptr, false);
    }
}

void GmkAreaWeather::dispose() {
    m_phantom.dispose();
    AGmkBase::dispose();
}

GmkAreaWeather::~GmkAreaWeather() { dispose(); }

bool GmkLandmark::BdatInfo::isCondMatched() const {
    if (m_cndId != 0 && !gf::GfGameCond::isGameCond(m_cndId)) {
        return false;
    }
    return true;
}

bool GmkSalvage::BdatInfo::isCondMatched() const {
    if (m_condition != 0 && !gf::GfGameCond::isGameCond(m_condition)) {
        return false;
    }
    return true;
}

bool GmkKizunaTalk::BdatInfo::isCondMatched() const {
    if (m_conditionId != 0 && !gf::GfGameCond::isGameCond(m_conditionId)) {
        return false;
    }
    return true;
}

bool GmkJump::BdatInfo::isPopCondMatched() const {
    if (m_condition != 0 && !gf::GfGameCond::isGameCond(m_condition)) {
        return false;
    }
    return true;
}

// the squared ene_disp/ene_release distances of the current map's row of BDAT 0x5D and the icon's squared distance;
// no row for the map: disposed again
void GmkJump::create(const CreateInfo& info) {
    AGmkBase::create(info);
    unsigned char* fp = gf::GfDataBdat::getFP(0x5D);
    if (fp != nullptr) {
        int mapId = gf::GfGameManager::getMapID();
        if (mapId >= Bdat::getIdTop(fp) && Bdat::getIdTop(fp) + Bdat::getIdCount(fp) > mapId) {
            unsigned char dispR = Bdat::getValCheck(fp, "ene_disp_r", mapId, 1);
            unsigned char dispH = Bdat::getValCheck(fp, "ene_disp_h", mapId, 1);
            m_eneDisp.m_horizontalSq = (float)dispR * (float)dispR;
            m_eneDisp.m_verticalSq = (float)dispH * (float)dispH;
            unsigned char releaseR = Bdat::getValCheck(fp, "ene_release_r", mapId, 1);
            unsigned char releaseH = Bdat::getValCheck(fp, "ene_release_h", mapId, 1);
            float r = (float)(dispR + releaseR);
            float h = (float)(dispH + releaseH);
            m_eneRelease.m_horizontalSq = r * r;
            m_eneRelease.m_verticalSq = h * h;
            Bdat::uVal iconDist;
            iconDist.ulong = Bdat::getValCheck(gf::GfDataBdat::getFP(0x7B), 0, 1, 8);
            m_iconDistSq = iconDist.real * iconDist.real;
            return;
        }
    }
    dispose();
}

void GmkJump::dispose() {
    if (m_effectHandle != 0) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->remove(m_effectHandle);
        m_effectHandle = 0;
    }
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    AGmkBase::dispose();
}

// pops or fades out its game object by the distance conditions; shows the icon near the start position
void GmkJump::update(float dt) {
    AGmkBase::update(dt);
    if (!isValid()) {
        return;
    }
    pad_50 = getBdatInfo()->isPopCondMatched();
    if (!isInterestPosExist()) {
        return;
    }
    if (canPopGobInst()) {
        createGobInst();
    } else if (canDepopGobInst()) {
        gf::GF_OBJ_HANDLE* gob = m_gob;
        if (gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            gf::GfObjAcc acc(gob);
            if (acc.getObj() != nullptr && !acc.isDestroy() && !acc.testFlag(17)) {
                gf::SCOM_DESTROY_GAME_OBJ::create(gob, 1.0f, 0);
            }
        }
    }
    if (pad_78) {
        return;
    }
    if (pad_50 && DistCond::isMatch(m_iconDistSq, getData()->m_startPos)) {
        if (m_effectHandle == 0) {
            createIcon();
        }
    } else if (m_effectHandle != 0) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->fadeOutDead(m_effectHandle, 5);
        m_effectHandle = 0;
    }
}

bool GmkJump::canPopGobInst() const {
    bool result = false;
    if (m_gob == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) && pad_50) {
        if (m_eneDisp.isMatch(getData()->m_startPos)) {
            result = true;
        }
    }
    return result;
}

void GmkJump::createGobInst() {
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set != nullptr && set->m_createInfo.m_flag) {
        return;
    }
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    CBdatWrapper bdat(m_list->getBindedBdatFp());
    m_gob = gf::GfObjFactory::createGmkCollection(bdat, m_createInfo.m_bdatId);
    {
        gf::GfObjAcc acc(m_gob);
        acc.setUserData(gf::GfObjUserData(0), reinterpret_cast<unsigned long>(this));
    }
    {
        gf::GF_OBJ_HANDLE* gob = m_gob;
        gf::GfObjAcc acc(gob);
        if (acc.m_obj != nullptr) {
            gf::GfObjSetupGimmick* setup = mm::mtl::rttiCast<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(gob)->m_setup);
            setup->pad_6c |= 7;
        }
        if (gf::GfObj* obj = acc.getObj()) {
            obj->pad_110 |= 7;
        }
    }
    {
        gf::GF_OBJ_HANDLE* gob = m_gob;
        // the original calls getGmkType here and drops its answer
        getGmkType();
        gf::GfObjAcc acc(gob);
        if (acc.m_obj != nullptr) {
            acc.setDisp(gf::OBJDISP(8), true);
        }
    }
    gf::GfObjSetupGimmick* setup = mm::mtl::rttiCast<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(m_gob)->m_setup);
    const Data* data = getData();
    setup->m_initialPos.x = data->m_startPos.x;
    setup->m_initialPos.y = data->m_startPos.y;
    setup->m_initialPos.z = data->m_startPos.z;
}

bool GmkJump::canDepopGobInst() const {
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        if (!pad_50 || !m_eneRelease.isMatch(getData()->m_startPos)) {
            return true;
        }
    }
    return false;
}

// the icon effect: "cmn_100_103" for a jump of type 0, "cmn_100_106" (or the field pack's "ma40a_01_100_dlc" in
// the Ira game) for type 1
void GmkJump::createIcon() {
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set != nullptr && set->m_createInfo.m_flag) {
        return;
    }
    if (m_effectHandle != 0) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->remove(m_effectHandle);
        m_effectHandle = 0;
    }
    const char* name;
    fw::EffectPack* pack;
    if (getBdatInfo()->m_type == 1) {
        bool ira = gf::GfGameManager::isGameTypeIra();
        name = ira ? "ma40a_01_100_dlc" : "cmn_100_106";
        pack = ira ? gf::GfFieldManager::getEffectPack() : nullptr;
    } else {
        pack = nullptr;
        name = "cmn_100_103";
    }
    void* efb = mm::mtl::PtrSingleton<fw::EffectManager>::sys()->search(name, pack);
    if (efb == nullptr) {
        return;
    }
    m_effectHandle = mm::mtl::PtrSingleton<fw::EffectManager>::sys()->create(efb, true);
    if (m_effectHandle != 0) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->setCategory(m_effectHandle, fw::EF_CATEGORY(1));
        validateIconPos();
    }
}

// places the icon: type 1 on the ground under the start position (getYSnapPos from 3 above, 6 down), type 0 at
// the start position raised by BDAT 0x7B member 0x25 and turned by the data's rotation
void GmkJump::validateIconPos() {
    if (m_effectHandle == 0) {
        return;
    }
    effect::SendParam param;
    const Data* data = getData();
    mm::Vec3 pos;
    float rotY;
    if (getBdatInfo()->m_type == 1) {
        mm::Vec3 from = data->m_startPos;
        from.y += 3.0f;
        if (!getYSnapPosForPop(pos, from, 6.0f)) {
            pos = data->m_startPos;
        }
        rotY = 0.0f;
    } else {
        pos = data->m_startPos;
        Bdat::uVal height;
        height.ulong = Bdat::getValCheck(gf::GfDataBdat::getFP(0x7B), 0, 0x25, 8);
        pos.y += height.real;
        rotY = data->m_rotY;
    }
    // read before the rotation (the original loads the position before its sinf/cosf calls)
    mm::Vec3 trans = pos;
    param.m_mtx.setRotY(rotY);
    param.m_mtx.addTrans(trans);
    bool flag;
    if (pad_79) {
        // the original calls getGmkType here and drops its answer
        getGmkType();
        flag = true;
    } else {
        flag = false;
    }
    param.m_flagB = flag;
    mm::mtl::PtrSingleton<fw::EffectManager>::sys()->setParam(m_effectHandle, &param);
}

void GmkJump::onGobEvent(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle) {
    AGmkBase::onGobEvent(evt, handle);
    if (evt == gf::IGfObjListener::OBJEVT(3) && m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
}

void GmkJump::onFsSucceeded() const {
    if (gf::GfGameManager::isGameTypeIra() && getBdatInfo()->m_type == 1) {
        suceededBigJump();
    }
}

GmkJump::~GmkJump() { dispose(); }

void GmkLandmark::BdatInfo::create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
    m_nameId = (unsigned short)Bdat::getValCheck(bdat.m_fp, "MSGID", row, 2);
    m_category = (unsigned char)Bdat::getValCheck(bdat.m_fp, "category", row, 1);
    m_cndId = (unsigned short)Bdat::getValCheck(bdat.m_fp, "cndID", row, 2);
    m_noTelop = Bdat::getFlagVal(bdat.m_fp, "flag", row, "noTelop") != 0;
    if (m_nameId != 0) {
        m_name = Bdat::getMSText(gf::GfDataBdat::getFP(0x1B3), m_nameId);
    }
}

void GmkEvent::BdatInfo::create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
    m_scenarioFlag = ScenarioFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMin", row, 2),
                                      (unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMax", row, 2));
    m_questFlag = QuestFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "QuestFlag", row, 2),
                                (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMin", row, 1),
                                (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMax", row, 1));
    m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
    m_eventId = (unsigned short)Bdat::getValCheck(bdat.m_fp, "EventID", row, 2);
    m_iconBdatId = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Icon", row, 2);
}

void GmkFieldLock::BdatInfo::create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
    m_scenarioFlag = ScenarioFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMin", row, 2),
                                      (unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMax", row, 2));
    m_questFlag = QuestFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "QuestFlag", row, 2),
                                (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMin", row, 1),
                                (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMax", row, 1));
    m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
    m_rockType = (unsigned char)Bdat::getValCheck(bdat.m_fp, "rockTYPE", row, 1);
    m_txtId = (unsigned short)Bdat::getValCheck(bdat.m_fp, "txtID", row, 2);
}

void GmkPrecious::BdatInfo::create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
    m_itmId = 0;
    m_itmId = (unsigned short)Bdat::getValCheck(bdat.m_fp, "itmID", row, 2);
    gf::GfItemUtil::isPrecious(m_itmId);
    m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
    m_questId = (unsigned short)Bdat::getValCheck(bdat.m_fp, "QuestID", row, 2);
    m_scenarioFlag = ScenarioFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMin", row, 2),
                                      (unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMax", row, 2));
    m_questFlag = QuestFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "QuestFlag", row, 2),
                                (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMin", row, 1),
                                (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMax", row, 1));
    m_popTime.m_time = (unsigned int)Bdat::getValCheck(bdat.m_fp, "POP_TIME", row, 3);
    m_popWeather.m_weather = (unsigned char)Bdat::getValCheck(bdat.m_fp, "popWeather", row, 1);
}

void GmkTutorial::BdatInfo::create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
    ScenarioFlagCond scenarioFlag((unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMin", row, 2), 0xFFFF);
    if (scenarioFlag.m_scenarioFlagMin != 0) {
        m_scenarioFlag = scenarioFlag;
    }
    m_questFlag = QuestFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "QuestFlag", row, 2),
                                (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMin", row, 1),
                                (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMax", row, 1));
    m_sysMultiFlag = (unsigned char)Bdat::getValCheck(bdat.m_fp, "SysMultiFlag", row, 1);
}

void GmkElevator::BdatInfo::create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
    m_opCondition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "OP_Condition", row, 2);
    m_callnameRadius = (unsigned short)Bdat::getValCheck(bdat.m_fp, "callnameRadius", row, 2);
    m_liftnameRadius = (unsigned short)Bdat::getValCheck(bdat.m_fp, "liftnameRadius", row, 2);
    m_liftLod = (unsigned short)Bdat::getValCheck(bdat.m_fp, "LIFTLOD", row, 2);
    m_shtALod = (unsigned short)Bdat::getValCheck(bdat.m_fp, "shtALOD", row, 2);
    m_shtBLod = (unsigned short)Bdat::getValCheck(bdat.m_fp, "shtBLOD", row, 2);
    m_switchALod = (unsigned short)Bdat::getValCheck(bdat.m_fp, "switchALOD", row, 2);
    m_switchBLod = (unsigned short)Bdat::getValCheck(bdat.m_fp, "switchBLOD", row, 2);
    m_switchSe = (unsigned short)Bdat::getValCheck(bdat.m_fp, "switchSE", row, 2);
    m_shutterSe = (unsigned short)Bdat::getValCheck(bdat.m_fp, "shutterSE", row, 2);
    m_liftStartSe = (unsigned short)Bdat::getValCheck(bdat.m_fp, "LiftStartSE", row, 2);
    m_liftLoopSe = (unsigned short)Bdat::getValCheck(bdat.m_fp, "LiftLoopSE", row, 2);
    m_liftStopSe = (unsigned short)Bdat::getValCheck(bdat.m_fp, "LiftStopSE", row, 2);
    m_liftMinVolDist = (unsigned char)Bdat::getValCheck(bdat.m_fp, "LiftMinVolDist", row, 1);
    m_liftMaxVolDist = (unsigned char)Bdat::getValCheck(bdat.m_fp, "LiftMaxVolDist", row, 1);
    m_liftReverse = Bdat::getFlagVal(bdat.m_fp, "flag", row, "lift_reverse") != 0;
    Bdat::uVal liftspeed;
    liftspeed.uint = (unsigned int)Bdat::getValCheck(bdat.m_fp, "call_liftspeed", row, 8);
    m_callLiftspeed = liftspeed.real;
    m_missMsgId = (unsigned short)Bdat::getValCheck(bdat.m_fp, "missMSG_ID", row, 2);
    m_elevatorNextwait = (short)Bdat::getValCheck(bdat.m_fp, "elevator_nextwait", row, 5);
    m_liftAMapJumpId = (unsigned short)Bdat::getValCheck(bdat.m_fp, "liftAMapJumpId", row, 2);
    m_liftBMapJumpId = (unsigned short)Bdat::getValCheck(bdat.m_fp, "liftBMapJumpId", row, 2);
}

GmkElevator::GmkElevator()
    : pad_4b0(-1), m_seq(nullptr), m_accessed0(false), m_accessed2(false), m_accessed3(false), m_accessed1(false),
      m_nextWait(0.0f) {
    for (int i = 0; i < 4; i++) {
        m_gobs[i] = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
}

const AGmkBase* GmkElevator::getGmkBaseByItemType(ItemType type) const {
    const AGmkBase* gmk = nullptr;
    switch (type) {
    case 0:
        gmk = this;
        break;
    case 1: {
        const IGmkList* list = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param)->m_gmkLists[GmkElevatorLocator::TYPE];
        if (list->isValid()) {
            const Data* data = reinterpret_cast<const Data*>(m_createInfo.m_data);
            gmk = list->getInst(data->m_locatorId);
        }
        break;
    }
    case 2: {
        const IGmkList* list = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param)->m_gmkLists[GmkElevatorLocator::TYPE];
        if (list->isValid()) {
            const Data* data = reinterpret_cast<const Data*>(m_createInfo.m_data);
            gmk = list->getInst(data->m_locatorId + 1);
        }
        break;
    }
    case 3: {
        const IGmkList* list = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param)->m_gmkLists[GmkElevatorLocator::TYPE];
        if (list->isValid()) {
            const Data* data = reinterpret_cast<const Data*>(m_createInfo.m_data);
            gmk = list->getInst(data->m_locatorId + 2);
        }
        break;
    }
    }
    return gmk;
}

bool GmkElevator::getPosForCompass(mm::Vec3& pos) const {
    const BdatInfo* info = static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo);
    if (info->m_liftAMapJumpId != 0) {
        if (&GmkElevator::seqDownIdle == m_seq) {
            const AGmkBase* gmk = getGmkBaseByItemType(ItemType(2));
            if (gmk == nullptr) {
                return false;
            }
            pos = *gmk->m_pos;
        } else if (&GmkElevator::seqUpIdle == m_seq) {
            const AGmkBase* gmk = getGmkBaseByItemType(ItemType(3));
            if (gmk == nullptr) {
                return false;
            }
            pos = *gmk->m_pos;
        } else if (&GmkElevator::seqWaitToArriveDownFloor == m_seq) {
            pos = *getGmkBaseByItemType(ItemType(1))->m_pos;
        } else {
            return false;
        }
    } else if (info->m_liftBMapJumpId != 0) {
        if (&GmkElevator::seqUpIdle == m_seq) {
            pos = *getGmkBaseByItemType(ItemType(0))->m_pos;
        } else if (&GmkElevator::seqDownIdle == m_seq) {
            const AGmkBase* gmk = getGmkBaseByItemType(ItemType(1));
            if (gmk == nullptr) {
                return false;
            }
            pos = *gmk->m_pos;
        } else if (&GmkElevator::seqWaitToArriveUpFloor == m_seq) {
            pos = *getGmkBaseByItemType(ItemType(3))->m_pos;
        } else {
            return false;
        }
    } else if (info->m_liftReverse) {
        pos = *getGmkBaseByItemType(ItemType(3))->m_pos;
    } else {
        pos = *getGmkBaseByItemType(ItemType(1))->m_pos;
    }
    return true;
}

void GmkElevator::seqDownIdle(float) {
    if (!m_accessed2) {
        if (!m_accessed1 || !isValid() ||
            !gf::GfGameManager::isElevatorMoveOK(static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo)->m_liftLod)) {
            return;
        }
    }
    const BdatInfo* info = static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo);
    if (m_accessed2) {
        mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->setPlaySpeed(info->m_liftLod, info->m_callLiftspeed);
        m_accessed2 = false;
    }
    if (m_accessed1) {
        m_accessed1 = false;
    }
    setTargetableByItemType(ItemType(0), false);
    setTargetableByItemType(ItemType(1), false);
    setTargetableByItemType(ItemType(2), false);
    setTargetableByItemType(ItemType(3), false);
    if (info->m_shtALod == 0) {
        mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->setAnimReverse(info->m_liftLod, false, false);
        m_seq = &GmkElevator::seqWaitToArriveUpFloor;
        gf::GfFieldLod* lod = mm::mtl::PtrSingleton<gf::GfFieldLod>::get();
        mm::Mat44 mtx;
        if (lod != nullptr && lod->m_initialized &&
            lod->findTransform(mtx, static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo)->m_liftLod)) {
            mm::Vec3 pos = mtx.getTrans();
            createSe(SeType(2), pos);
            createSe(SeType(3), pos);
        }
    } else {
        mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->setAnimReverse(info->m_shtALod, true, false);
        gf::GfFieldLod* lod = mm::mtl::PtrSingleton<gf::GfFieldLod>::get();
        mm::Mat44 mtx;
        if (lod != nullptr && lod->m_initialized &&
            lod->findTransform(mtx, static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo)->m_shtALod)) {
            mm::Vec3 pos = mtx.getTrans();
            createSe(SeType(1), pos);
        }
        m_seq = &GmkElevator::seqWaitToCloseDownShutter;
    }
}

void GmkElevator::seqUpIdle(float) {
    if (!m_accessed0) {
        if (!m_accessed3 || !isValid() ||
            !gf::GfGameManager::isElevatorMoveOK(static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo)->m_liftLod)) {
            return;
        }
    }
    const BdatInfo* info = static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo);
    if (m_accessed0) {
        mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->setPlaySpeed(info->m_liftLod, info->m_callLiftspeed);
        m_accessed0 = false;
    }
    if (m_accessed3) {
        m_accessed3 = false;
    }
    setTargetableByItemType(ItemType(0), false);
    setTargetableByItemType(ItemType(1), false);
    setTargetableByItemType(ItemType(2), false);
    setTargetableByItemType(ItemType(3), false);
    if (info->m_shtBLod == 0) {
        mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->setAnimReverse(info->m_liftLod, true, false);
        m_seq = &GmkElevator::seqWaitToArriveDownFloor;
        gf::GfFieldLod* lod = mm::mtl::PtrSingleton<gf::GfFieldLod>::get();
        mm::Mat44 mtx;
        if (lod != nullptr && lod->m_initialized &&
            lod->findTransform(mtx, static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo)->m_liftLod)) {
            mm::Vec3 pos = mtx.getTrans();
            createSe(SeType(2), pos);
            createSe(SeType(3), pos);
        }
    } else {
        mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->setAnimReverse(info->m_shtBLod, true, false);
        gf::GfFieldLod* lod = mm::mtl::PtrSingleton<gf::GfFieldLod>::get();
        mm::Mat44 mtx;
        if (lod != nullptr && lod->m_initialized &&
            lod->findTransform(mtx, static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo)->m_shtBLod)) {
            mm::Vec3 pos = mtx.getTrans();
            createSe(SeType(1), pos);
        }
        m_seq = &GmkElevator::seqWaitToCloseUpShutter;
    }
}

void GmkElevator::seqWaitToArriveDownFloor(float) {
    gf::GfFieldLod* lod = mm::mtl::PtrSingleton<gf::GfFieldLod>::get();
    if (lod->m_coliAnim.m_info.m_model == nullptr || lod->m_coliAnim.m_info.m_lod == nullptr) {
        return;
    }
    const BdatInfo* info = static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo);
    if (!lod->isPlayAnimEnd(info->m_liftLod)) {
        return;
    }
    {
        gf::GfFieldLod* lod = mm::mtl::PtrSingleton<gf::GfFieldLod>::get();
        mm::Mat44 mtx;
        if (lod != nullptr && lod->m_initialized &&
            lod->findTransform(mtx, static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo)->m_liftLod)) {
            mm::Vec3 pos = mtx.getTrans();
            createSe(SeType(2), pos);
        }
    }
    m_ctrlVolSes[3].dispose();
    mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->setPlaySpeed(info->m_liftLod, 1.0f);
    if (info->m_shtALod != 0) {
        mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->setAnimReverse(info->m_shtALod, false, false);
        gf::GfFieldLod* lod = mm::mtl::PtrSingleton<gf::GfFieldLod>::get();
        mm::Mat44 mtx;
        if (lod != nullptr && lod->m_initialized &&
            lod->findTransform(mtx, static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo)->m_shtALod)) {
            mm::Vec3 pos = mtx.getTrans();
            createSe(SeType(1), pos);
        }
    }
    setTargetableByItemType(ItemType(0), false);
    setTargetableByItemType(ItemType(1), true);
    setTargetableByItemType(ItemType(2), true);
    setTargetableByItemType(ItemType(3), false);
    m_accessed0 = false;
    m_accessed2 = false;
    m_accessed3 = false;
    m_accessed1 = false;
    m_seq = &GmkElevator::seqDownIdle;
    if (info->m_liftBMapJumpId == 0) {
        unsigned int id = m_createInfo.m_bdatId;
        float wait = gf::GfQuestUtil::getGimmickTaskEndCheck(TYPE, id) == 1
                         ? static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo)->m_elevatorNextwait
                         : 0.0f;
        gf::SCOM_QUEST_GIMMICK::createElevator(id, wait);
    }
}

void GmkElevator::seqWaitToArriveUpFloor(float) {
    gf::GfFieldLod* lod = mm::mtl::PtrSingleton<gf::GfFieldLod>::get();
    if (lod->m_coliAnim.m_info.m_model == nullptr || lod->m_coliAnim.m_info.m_lod == nullptr) {
        return;
    }
    const BdatInfo* info = static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo);
    if (!lod->isPlayAnimEnd(info->m_liftLod)) {
        return;
    }
    {
        gf::GfFieldLod* lod = mm::mtl::PtrSingleton<gf::GfFieldLod>::get();
        mm::Mat44 mtx;
        if (lod != nullptr && lod->m_initialized &&
            lod->findTransform(mtx, static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo)->m_liftLod)) {
            mm::Vec3 pos = mtx.getTrans();
            createSe(SeType(2), pos);
        }
    }
    m_ctrlVolSes[3].dispose();
    mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->setPlaySpeed(info->m_liftLod, 1.0f);
    if (info->m_shtBLod != 0) {
        mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->setAnimReverse(info->m_shtBLod, false, false);
        gf::GfFieldLod* lod = mm::mtl::PtrSingleton<gf::GfFieldLod>::get();
        mm::Mat44 mtx;
        if (lod != nullptr && lod->m_initialized &&
            lod->findTransform(mtx, static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo)->m_shtBLod)) {
            mm::Vec3 pos = mtx.getTrans();
            createSe(SeType(1), pos);
        }
    }
    setTargetableByItemType(ItemType(0), true);
    setTargetableByItemType(ItemType(1), false);
    setTargetableByItemType(ItemType(2), false);
    setTargetableByItemType(ItemType(3), true);
    m_accessed0 = false;
    m_accessed2 = false;
    m_accessed3 = false;
    m_accessed1 = false;
    m_seq = &GmkElevator::seqUpIdle;
    if (info->m_liftBMapJumpId == 0) {
        unsigned int id = m_createInfo.m_bdatId;
        float wait = gf::GfQuestUtil::getGimmickTaskEndCheck(TYPE, id) == 1
                         ? static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo)->m_elevatorNextwait
                         : 0.0f;
        gf::SCOM_QUEST_GIMMICK::createElevator(id, wait);
    }
}

// ---- GmkElevator
bool GmkElevator::isCallSwitch(gf::GF_OBJ_HANDLE* gob) const {
    int index = getGobIndex(gob);
    return index == 0 || index == 2;
}

bool GmkElevator::isLiftSwitch(gf::GF_OBJ_HANDLE* gob) const {
    int index = getGobIndex(gob);
    return index == 1 || index == 3;
}

void GmkElevator::dispose() {
    m_accessed0 = false;
    m_accessed2 = false;
    m_accessed3 = false;
    m_accessed1 = false;
    pad_4b0 = -1;
    m_seq = nullptr;
    clearGobInsts();
    for (int i = 0; i < 4; i++) {
        m_ctrlVolSes[i].dispose();
    }
    bool valid = isValid();
    gf::GfFieldLod* lod = mm::mtl::PtrSingleton<gf::GfFieldLod>::get();
    if (lod != nullptr && valid) {
        gf::GfFieldGimmick* gimmick = mm::mtl::PtrSingleton<gf::GfFieldGimmick>::get();
        if (gimmick == nullptr || !gimmick->m_unknownFlag1) {
            const BdatInfo* info = static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo);
            if (info->m_liftAMapJumpId != 0) {
                lod->setAnimReverse(info->m_liftLod, true, true);
            } else if (info->m_liftBMapJumpId != 0) {
                lod->setAnimReverse(info->m_liftLod, false, true);
            }
        }
    }
    AGmkBase::dispose();
}

void GmkElevator::clearGobInsts() {
    for (int i = 0; i < 4; i++) {
        if (m_gobs[i] != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            gf::GfObjAcc acc(m_gobs[i]);
            if (acc.m_obj != nullptr) {
                acc.setUserData(gf::GfObjUserData(0), 0);
            }
            gf::GfObjUtil::destroy(m_gobs[i]);
            m_gobs[i] = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        }
    }
}

void GmkElevator::update(float dt) {
    debugUpdateMmf();
    if (isValid() && m_seq) {
        (this->*m_seq)(dt);
    }
}

void GmkElevator::setTargetableByItemType(ItemType type, bool targetable) {
    if (m_gobs[type] == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set == nullptr || !set->m_createInfo.m_flag) {
        const BdatInfo* info = static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo);
        unsigned int switchId;
        if (info->m_opCondition == 0 || gf::GfGameCond::isGameCond(info->m_opCondition)) {
            switchId = targetable ? 1 : 2;
        } else {
            switchId = 2;
        }
        info = static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo);
        switch (type) {
        case 0:
            if (info->m_switchALod != 0) {
                mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->setLodSwitchId(info->m_switchALod, switchId);
            }
            break;
        case 2:
            if (info->m_switchBLod != 0) {
                mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->setLodSwitchId(info->m_switchBLod, switchId);
            }
            break;
        }
    }
    gf::GF_OBJ_HANDLE* gob = m_gobs[type];
    gf::GfObjAcc acc(gob);
    if (acc.m_obj != nullptr) {
        gf::GfObjSetupGimmick* setup = mm::mtl::rttiCast<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(gob)->m_setup);
        if (targetable) {
            setup->pad_6c |= 7;
        } else {
            setup->pad_6c &= ~7;
        }
    }
    if (gf::GfObj* obj = acc.getObj()) {
        if (targetable) {
            obj->pad_110 |= 7;
        } else {
            obj->pad_110 &= ~7;
        }
    }
}

void GmkElevator::seqWaitToCloseDownShutter(float) {
    gf::GfFieldLod* lod = mm::mtl::PtrSingleton<gf::GfFieldLod>::get();
    if (lod->m_coliAnim.m_info.m_model == nullptr || lod->m_coliAnim.m_info.m_lod == nullptr) {
        return;
    }
    const BdatInfo* info = static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo);
    if (!lod->isPlayAnimEnd(info->m_shtALod)) {
        return;
    }
    mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->setAnimReverse(info->m_liftLod, false, false);
    m_seq = &GmkElevator::seqWaitToArriveUpFloor;
    gf::GfFieldLod* lod2 = mm::mtl::PtrSingleton<gf::GfFieldLod>::get();
    mm::Mat44 mtx;
    if (lod2 != nullptr && lod2->m_initialized &&
        lod2->findTransform(mtx, static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo)->m_liftLod)) {
        mm::Vec3 pos = mtx.getTrans();
        createSe(SeType(2), pos);
        createSe(SeType(3), pos);
    }
}

void GmkElevator::seqWaitToCloseUpShutter(float) {
    gf::GfFieldLod* lod = mm::mtl::PtrSingleton<gf::GfFieldLod>::get();
    if (lod->m_coliAnim.m_info.m_model == nullptr || lod->m_coliAnim.m_info.m_lod == nullptr) {
        return;
    }
    const BdatInfo* info = static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo);
    if (!lod->isPlayAnimEnd(info->m_shtBLod)) {
        return;
    }
    mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->setAnimReverse(info->m_liftLod, true, false);
    m_seq = &GmkElevator::seqWaitToArriveDownFloor;
    gf::GfFieldLod* lod2 = mm::mtl::PtrSingleton<gf::GfFieldLod>::get();
    mm::Mat44 mtx;
    if (lod2 != nullptr && lod2->m_initialized &&
        lod2->findTransform(mtx, static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo)->m_liftLod)) {
        mm::Vec3 pos = mtx.getTrans();
        createSe(SeType(2), pos);
        createSe(SeType(3), pos);
    }
}

void GmkElevator::onGobEvent(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle) {
    AGmkBase::onGobEvent(evt, handle);
    if (evt == gf::IGfObjListener::OBJEVT(3)) {
        switch (getGobIndex(handle)) {
        case 0: m_gobs[0] = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1); break;
        case 1: m_gobs[1] = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1); break;
        case 2: m_gobs[2] = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1); break;
        case 3: m_gobs[3] = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1); break;
        }
    }
}

void GmkElevator::onPlayerAccessed(gf::GF_OBJ_HANDLE* gob) {
    const BdatInfo* info = static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo);
    if (info->m_opCondition != 0 && !gf::GfGameCond::isGameCond(info->m_opCondition)) {
        unsigned short msgId = info->m_missMsgId;
        gf::MenuCommonWindowParam param;
        param.m_bdat = gf::GfDataBdat::getFP(0x1b1);
        param.m_msgId = msgId;
        gf::GfPlayFactory::createCommonMessage(param);
        return;
    }
    ItemType type;
    if (m_gobs[0] == gob) {
        type = ItemType(0);
        m_accessed0 = true;
    } else if (m_gobs[1] == gob) {
        type = ItemType(1);
        m_accessed1 = true;
    } else if (m_gobs[2] == gob) {
        m_accessed2 = true;
        type = ItemType(2);
    } else if (m_gobs[3] == gob) {
        type = ItemType(3);
        m_accessed3 = true;
    } else {
        return;
    }
    if (const AGmkBase* gmk = getGmkBaseByItemType(type)) {
        createSe(SeType(0), *gmk->m_pos);
    }
}

bool ScenarioFlagCond::isMatch() const {
    unsigned short flag = gf::GfDataUtil::getScenarioFlag();
    if (m_scenarioFlagMin > flag) {
        return false;
    }
    return flag <= m_scenarioFlagMax;
}
bool QuestFlagCond::isMatch() const {
    unsigned char state = gf::GfQuestInfo::getState(m_questFlag);
    return (m_questFlagMin <= state) & (state <= m_questFlagMax);
}
bool TimeCond::isMatch() const {
    bool match = false;
    if (gf::GfFieldTime* time = mm::mtl::PtrSingleton<gf::GfFieldTime>::sys()) {
        match = (time->getTimeRangeBits() & m_time) != 0;
    }
    return match;
}
bool WeatherCond::isMatch() const {
    return (gf::GfFieldWeather::getCurrentMapWeatherBit(false) & m_weather) != 0;
}
bool GmkEvent::BdatInfo::isCondMatched() const {
    if (m_scenarioFlag.m_scenarioFlagMax != 0 && !m_scenarioFlag.isMatch()) {
        return false;
    }
    if (m_questFlag.m_questFlag != 0 && m_questFlag.m_questFlagMin <= m_questFlag.m_questFlagMax &&
        !m_questFlag.isMatch()) {
        return false;
    }
    if (m_condition != 0 && !gf::GfGameCond::isGameCond(m_condition)) {
        return false;
    }
    return true;
}
bool GmkTutorial::BdatInfo::isCondMatched() const {
    if (m_scenarioFlag.m_scenarioFlagMax != 0 && !m_scenarioFlag.isMatch()) {
        return false;
    }
    if (m_questFlag.m_questFlag != 0 && m_questFlag.m_questFlagMin <= m_questFlag.m_questFlagMax &&
        !m_questFlag.isMatch()) {
        return false;
    }
    if (m_sysMultiFlag != 0 && gf::GfGameFlag::getLocal(1, m_sysMultiFlag + 0x89FA) == 0) {
        return false;
    }
    return true;
}
bool GmkPrecious::BdatInfo::isPopCondMatched() const {
    if (m_scenarioFlag.m_scenarioFlagMax != 0 && !m_scenarioFlag.isMatch()) {
        return false;
    }
    if (m_questFlag.m_questFlag != 0 && m_questFlag.m_questFlagMin <= m_questFlag.m_questFlagMax &&
        !m_questFlag.isMatch()) {
        return false;
    }
    if (m_popTime.m_time != 0 && !m_popTime.isMatch()) {
        return false;
    }
    if (m_popWeather.m_weather != 0 && !m_popWeather.isMatch()) {
        return false;
    }
    if (m_condition != 0 && !gf::GfGameCond::isGameCond(m_condition)) {
        return false;
    }
    return true;
}

bool GmkDoor::BdatInfo::isPopCondMatched() const {
    if (m_condition != 0 && !gf::GfGameCond::isGameCond(m_condition)) {
        return false;
    }
    if (m_bootedGmk.isSet() && !m_bootedGmk.isMatch()) {
        return false;
    }
    return true;
}

void GmkDoor::BdatInfo::create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
    m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
    m_bootedGmk = BootedGmkCond(bdat, row, nullptr);
    m_bootedGmk2 = BootedGmkCond(bdat, row, "OP_");
    m_responseType = (unsigned char)Bdat::getValCheck(bdat.m_fp, "response_type", row, 1);
    m_responseChr = (unsigned char)Bdat::getValCheck(bdat.m_fp, "response_CHR", row, 1);
    m_nameRadius = (unsigned short)Bdat::getValCheck(bdat.m_fp, "nameRadius", row, 2);
    m_lodModel = (unsigned short)Bdat::getValCheck(bdat.m_fp, "LODmodel", row, 2);
    m_missMsgId = (unsigned short)Bdat::getValCheck(bdat.m_fp, "missMSG_ID", row, 2);
    m_openLodAnime = Bdat::getFlagVal(bdat.m_fp, "flag", row, "open_LODanime") != 0;
    m_openSeType = Bdat::getFlagVal(bdat.m_fp, "flag", row, "open_SE_type") != 0;
    m_openSe = (unsigned short)Bdat::getValCheck(bdat.m_fp, "open_SE", row, 2);
    m_openSeSize = (unsigned char)Bdat::getValCheck(bdat.m_fp, "open_SE_size", row, 1);
    m_openCamGimId = reinterpret_cast<const char*>(Bdat::getValCheck(bdat.m_fp, "open_camGim_ID", row, 7));
    m_openCamGimAtr = (unsigned char)Bdat::getValCheck(bdat.m_fp, "open_camGim_ATR", row, 1);
    m_closeLodAnime = Bdat::getFlagVal(bdat.m_fp, "flag", row, "close_LODanime") != 0;
    m_closeSeType = Bdat::getFlagVal(bdat.m_fp, "flag", row, "close_SE_type") != 0;
    m_closeSe = (unsigned short)Bdat::getValCheck(bdat.m_fp, "close_SE", row, 2);
    m_closeSeSize = (unsigned char)Bdat::getValCheck(bdat.m_fp, "close_SE_size", row, 1);
    m_closeCamGimId = reinterpret_cast<const char*>(Bdat::getValCheck(bdat.m_fp, "close_camGim_ID", row, 7));
    m_closeCamGimAtr = (unsigned char)Bdat::getValCheck(bdat.m_fp, "close_camGim_ATR", row, 1);
    Bdat::uVal nextwait;
    nextwait.ulong = Bdat::getValCheck(bdat.m_fp, "door_nextwait", row, 8);
    m_doorNextwait = nextwait.real;
    m_spCloseCamGimId = reinterpret_cast<const char*>(Bdat::getValCheck(bdat.m_fp, "sp_close_camGim_ID", row, 7));
    m_spCloseCamGimAtr = (unsigned char)Bdat::getValCheck(bdat.m_fp, "sp_close_camGim_ATR", row, 1);
    m_bootedGmk3 = BootedGmkCond(bdat, row, "SPOP_");
    m_gmkCamPos = Bdat::getFlagVal(bdat.m_fp, "flag", row, "gmkCamPos") != 0;
}

bool GmkDoor::BdatInfo::isLoadSaveData() const {
    gf::GfFieldGimmick* gimmick = mm::mtl::PtrSingleton<gf::GfFieldGimmick>::get();
    if (gimmick != nullptr && gimmick->m_unknownFlag1) {
        return true;
    }
    if (m_lodModel == 0) {
        return false;
    }
    switch (m_responseType) {
    case 2:
    case 4:
    case 5:
        return true;
    default:
        return false;
    }
}

bool GmkDoor::isSeLoop(bool mapPack, unsigned short se) const {
    gf::GfFieldSound* sound = mm::mtl::PtrSingleton<gf::GfFieldSound>::get();
    fw::SoundPack* pack = mapPack ? sound->getMapPack() : sound->getCommonPack();
    return fw::SoundManager::get()->isLoop(se, pack);
}

void GmkDoor::seqDoor_BeforeBoot(float) { pollBootGmk(); }

void GmkDoor::seqDoor_Shutdowned(float dt) { seqDoor_Booted(dt); }

void GmkDoor::seqDoor_SpBooted(float dt) {
    if (m_doorWait < getBdatInfo()->m_doorNextwait) {
        m_doorWait += dt;
    }
}

void GmkDoor::setLodSwitch(LodSwitch lodSwitch) {
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set == nullptr || !set->m_createInfo.m_flag) {
        unsigned int switchId;
        switch (lodSwitch) {
        case 0:
            switchId = 2;
            break;
        case 1:
            switchId = 2;
            break;
        case 2:
            switchId = 1;
            break;
        default:
            switchId = 0;
            break;
        }
        gf::GfFieldLod* lod = mm::mtl::PtrSingleton<gf::GfFieldLod>::get();
        if (lod->m_coliAnim.m_info.m_model == nullptr || lod->m_coliAnim.m_info.m_lod == nullptr) {
            return;
        }
        unsigned short lodId = lod->m_lodIds[getBdatInfo()->m_lodModel - lod->m_idTop];
        ml::ScnObjAccSeamPos seam(lod->m_coliAnim.m_info.m_model);
        int max = seam.getMax();
        for (int i = 0; i < max; i++) {
            ml::ScnObjAccPartsPos parts = seam.getObj(i);
            if (lodId == parts.getID()) {
                parts.setSwitchID(switchId);
            }
        }
    }
}

void GmkDoor::openDoor(bool anim) {
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set != nullptr && set->m_createInfo.m_flag) {
        return;
    }
    const BdatInfo* info = getBdatInfo();
    mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->setAnimReverse(info->m_lodModel, false, anim);
    gf::GF_OBJ_HANDLE* gob = m_gob;
    if (gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(gob);
        if (acc.m_obj != nullptr) {
            gf::GfObjSetupGimmick* setup = mm::mtl::rttiCast<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(gob)->m_setup);
            setup->pad_6c &= ~7;
        }
        if (gf::GfObj* obj = acc.getObj()) {
            obj->pad_110 &= ~7;
        }
    }
    if (info->m_openSe != 0) {
        if (anim && !isSeLoop(info->m_openSeType, info->m_openSe)) {
            return;
        }
        createSe(info->m_openSeType, info->m_openSe, info->m_openSeSize);
    }
    if (!anim) {
        unsigned int id = m_createInfo.m_bdatId;
        float time;
        if (gf::GfQuestUtil::getGimmickTaskEndCheck(TYPE, id) == 1) {
            const BdatInfo* bdat = getBdatInfo();
            time = mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->getAnimEndTime(bdat->m_lodModel) + bdat->m_doorNextwait;
        } else {
            time = 0.0f;
        }
        gf::SCOM_QUEST_GIMMICK::createDoor(id, time);
    }
}

void GmkDoor::closeDoor(bool anim) {
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set != nullptr && set->m_createInfo.m_flag) {
        return;
    }
    const BdatInfo* info = getBdatInfo();
    mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->setAnimReverse(info->m_lodModel, true, anim);
    gf::GF_OBJ_HANDLE* gob = m_gob;
    if (gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(gob);
        if (acc.m_obj != nullptr) {
            gf::GfObjSetupGimmick* setup = mm::mtl::rttiCast<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(gob)->m_setup);
            setup->pad_6c |= 7;
        }
        if (gf::GfObj* obj = acc.getObj()) {
            obj->pad_110 |= 7;
        }
    }
    if (info->m_closeSe != 0) {
        if (anim && !isSeLoop(info->m_closeSeType, info->m_closeSe)) {
            return;
        }
        createSe(info->m_closeSeType, info->m_closeSe, info->m_closeSeSize);
    }
}

void GmkDoor::bootGmk(bool anim, bool camera) {
    if (getProgress() == 1) {
        return;
    }
    const BdatInfo* info = getBdatInfo();
    if (info->m_openLodAnime) {
        closeDoor(anim);
    } else {
        openDoor(anim);
    }
    unsigned short lodModel = info->m_lodModel;
    if (const gf::GfFieldLod::BdatInfo* lodInfo = mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->findBdatInfo(lodModel)) {
        if (lodInfo->m_fadeInTime > 0.0f) {
            mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->setFade(lodModel, true, anim);
        } else if (lodInfo->m_fadeOutTime > 0.0f) {
            mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->setFade(lodModel, false, anim);
        }
    }
    createGmkCamera(info->m_openCamGimId, info->m_openCamGimAtr, camera);
    if (!info->m_bootedGmk3.isSet()) {
        m_doorWait = anim ? info->m_doorNextwait : 0.0f;
    }
    setProgress(Progress(1));
}

void GmkDoor::dispose() {
    disposeGmkPhantom();
    m_camera.dispose();
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    m_ctrlVolSe.dispose();
    AGmkBase::dispose();
}

void GmkDoor::disposeGmkPhantom() {
    m_phantomSimple.dispose();
    m_phantom.dispose();
}

void GmkDoor::update(float dt) {
    AGmkBase::update(dt);
    if (!isValid()) {
        return;
    }
    if (pad_2b1 != pad_2b0) {
        if (pad_2b1 && !pad_2b0) {
            switch (getBdatInfo()->m_responseType) {
            case 6:
            case 7:
                shutdownGmk(false, true);
                break;
            }
        }
        pad_2b1 = pad_2b0;
    }
    const BdatInfo* info = getBdatInfo();
    pad_2b0 = false;
    if (info->isPopCondMatched()) {
        if (m_gob == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) && info->isGfObjMustExist()) {
            createGfObjHandle();
        }
        if (m_phantom.m_coliObject == nullptr && m_phantomSimple.m_coliObject == nullptr && info->isPhantomMustExist()) {
            createGmkPhantom();
        }
    } else {
        disposeGfObjHandle();
        if (m_phantom.m_coliObject != nullptr || m_phantomSimple.m_coliObject != nullptr) {
            disposeGmkPhantom();
        }
    }
    m_camera.update(dt);
    if (m_seq) {
        (this->*m_seq)(dt);
    }
}

void GmkDoor::createGfObjHandle() {
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set != nullptr && set->m_createInfo.m_flag) {
        return;
    }
    disposeGfObjHandle();
    CBdatWrapper bdat(m_list->getBindedBdatFp());
    m_gob = gf::GfObjFactory::createGmkEvent(bdat, m_createInfo.m_bdatId);
    {
        gf::GfObjAcc acc(m_gob);
        acc.setUserData(gf::GfObjUserData(0), reinterpret_cast<unsigned long>(this));
    }
    gf::GfObjSetupGimmick* setup = mm::mtl::rttiCast<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(m_gob)->m_setup);
    const mm::Vec3* xform = m_pos;
    setup->m_initialPos.x = xform[0].x;
    setup->m_initialPos.y = xform[0].y;
    setup->m_initialPos.z = xform[0].z;
    setup->pad_30.x = xform[1].x;
    setup->pad_30.y = xform[1].y;
    setup->pad_30.z = xform[1].z;
    unsigned short lodModel = getBdatInfo()->m_lodModel;
    bool closed = mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->isAnimReverse(lodModel);
    gf::GF_OBJ_HANDLE* gob = m_gob;
    gf::GfObjAcc acc(gob);
    if (acc.m_obj != nullptr) {
        gf::GfObjSetupGimmick* gobSetup = mm::mtl::rttiCast<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(gob)->m_setup);
        if (closed) {
            gobSetup->pad_6c |= 7;
        } else {
            gobSetup->pad_6c &= ~7;
        }
    }
    if (gf::GfObj* obj = acc.getObj()) {
        if (closed) {
            obj->pad_110 |= 7;
        } else {
            obj->pad_110 &= ~7;
        }
    }
}

void GmkDoor::createGmkPhantom() {
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set != nullptr && set->m_createInfo.m_flag) {
        return;
    }
    switch (m_info->m_shape) {
    case 2:
    case 3:
    case 4:
        break;
    default:
        return;
    }
    if (getBdatInfo()->m_responseChr & 2) {
        GmkPhantomSimple::CreateInfo info;
        info.validateByAGmkBase(*this);
        m_phantomSimple.create(info);
        m_phantomSimple.m_coliObject->setUserData(this);
    } else {
        m_phantom.create(*this, this, true);
    }
}

bool GmkDoor::createGmkCamera(const char* name, unsigned char attr, bool play) {
    m_camera.dispose();
    GmkCamera::CreateInfo info;
    info.m_name = name;
    info.m_attr = attr;
    info.pad_106 = play;
    const BdatInfo* bdatInfo = getBdatInfo();
    if (bdatInfo->m_gmkCamPos) {
        info.validateTransform(bdatInfo->m_lodModel);
    }
    if (info.m_name.length() > 0) {
        m_camera.create(info);
        return true;
    }
    return false;
}

void GmkDoor::debugDraw() const {
    if (!isValid()) {
        return;
    }
    if (getBdatInfo()->m_responseType == 5) {
        const mm::Vec3* xform = m_pos;
        mm::Vec3 dir = mm::Vec3::unitZ;
        mm::Mat44 rot;
        rot.setRotXYZ(xform[1]);
        mm::Vec3 end = xform[0] + mm::Vec3(dir.x * rot.m[0][0] + dir.y * rot.m[1][0] + dir.z * rot.m[2][0] + rot.m[3][0],
                                           dir.x * rot.m[0][1] + dir.y * rot.m[1][1] + dir.z * rot.m[2][1] + rot.m[3][1],
                                           dir.x * rot.m[0][2] + dir.y * rot.m[1][2] + dir.z * rot.m[2][2] + rot.m[3][2]);
        const mm::Col3& col = mm::Col3::yellow;
        fw::debug::drawArrow(xform[0], end, mm::Col4(col.r, col.g, col.b, 1.0f));
    }
    mm::mtl::PtrSingleton<gf::GfFieldLod>::get()->isAnimReverse(getBdatInfo()->m_lodModel);
}

void GmkDoor::createSe(bool mapPack, unsigned short se, unsigned char size) {
    m_ctrlVolSe.dispose();
    gf::GfFieldSound* sound = mm::mtl::PtrSingleton<gf::GfFieldSound>::get();
    fw::SoundPack* pack = mapPack ? sound->getMapPack() : sound->getCommonPack();
    if (se == 0 || pack == nullptr) {
        return;
    }
    GmkCtrlVolSe::CreateInfo info;
    info.m_pack = pack;
    info.m_seId = se;
    info.m_minDist = size;
    info.m_maxDist = size;
    info.m_pos = *m_pos;
    m_ctrlVolSe.create(info);
}

void GmkDoor::onPlayerAccessed(gf::GF_OBJ_HANDLE*) {
    const BdatInfo* info = getBdatInfo();
    if (info->m_responseType == 5) {
        if (gf::GfGameManager::getControlMoverForGimmick() == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            return;
        }
        const mm::Vec3* player;
        if (gf::GfGameManager::isGameTypeIra()) {
            player = &gf::GfGameManager::getControlMoverPosition();
        } else {
            gf::GfObj* obj = gf::GfObjUtil::getObj(gf::GfGameManager::getControlMoverForGimmick());
            player = &obj->getComponent<gf::GfComTransform>(0)->getPosition();
        }
        mm::Vec3 diff;
        diff.x = player->x - m_pos[0].x;
        diff.y = player->y - m_pos[0].y;
        diff.z = player->z - m_pos[0].z;
        mm::Mat44 rot;
        rot.setRotXYZ(m_pos[1]);
        // in front of the door: opens it
        if (diff.x * rot.m[2][0] + diff.y * rot.m[2][1] + diff.z * rot.m[2][2] < 0.0f) {
            bootGmk(false, false);
            setLodSwitch(LodSwitch(2));
            return;
        }
    } else if (!info->m_bootedGmk2.isSet() || info->m_bootedGmk2.isMatch()) {
        bootGmk(false, false);
        return;
    }
    unsigned short msgId = info->m_missMsgId;
    gf::MenuCommonWindowParam param;
    param.m_bdat = gf::GfDataBdat::getFP(0x1b1);
    param.m_msgId = msgId;
    gf::GfPlayFactory::createCommonMessage(param);
}

void GmkDoor::onEnterPhantom(const IGmkPhantomEventListener::OnEnterInfo& info) {
    // only in seqDoor_BeforeBoot, seqDoor_Booted or seqDoor_Shutdowned
    if (&GmkDoor::seqDoor_BeforeBoot != m_seq && &GmkDoor::seqDoor_Booted != m_seq &&
        &GmkDoor::seqDoor_Shutdowned != m_seq) {
        return;
    }
    pollBootGmk();
}

void GmkDoor::onLeavePhantom(const IGmkPhantomEventListener::OnLeaveInfo& info) {
    const BdatInfo* bdatInfo = getBdatInfo();
    if (bdatInfo->m_responseType == 6 || bdatInfo->m_responseType == 7) {
        shutdownGmk(false, true);
    }
}

void GmkDoor::onGobEvent(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle) {
    AGmkBase::onGobEvent(evt, handle);
    if (evt == gf::IGfObjListener::OBJEVT(3)) {
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
}

GmkDoorPhantomManager::GmkDoorPhantomManager() {
    gf::GfObjManager::addListener(this, gf::IGfObjListener::OBJEVT(0));
    create();
}

void GmkDoorPhantomManager::create() {
    m_targets.destroy();
    m_targets.setAllocator(gf::getAllocator(gf::ALLOCATOR(0)));
    int capacity = gf::GfObjManager::getGfObjCapacity(5);
    m_targets.reserve(capacity > 0 ? static_cast<unsigned int>(capacity + 3) : 3u);
}

GmkDoorPhantomManager::~GmkDoorPhantomManager() {
    m_targets.destroy();
    gf::GfObjManager::removeListener(this);
}

// whether an object of the given type is one the door phantoms watch: objects of types 3 and 4, and enemies with
// the flag (inlined; the name is not the original's)
static bool isDoorPhantomTarget(gf::GF_OBJ_HANDLE* handle, unsigned int type) {
    gf::GfObjAcc acc(handle);
    switch (type) {
    case 3:
    case 4:
        return true;
    case 5: {
        gf::DataParamAcc param(handle);
        const gf::SDataEnemy* enemy = param.getSDataEnemy();
        if (enemy == nullptr) {
            return false;
        }
        return enemy->m_flags5bit2;
    }
    default:
        return false;
    }
}

void GmkDoorPhantomManager::listenerGfObj(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle, unsigned int type) {
    if (!isDoorPhantomTarget(handle, type)) {
        return;
    }
    switch (evt) {
    case gf::IGfObjListener::OBJEVT(2):
        if (m_targets.size() != m_targets.capacity()) {
            m_targets.push_back(GmkDoorPhantomTargetInfo(handle));
        }
        break;
    case gf::IGfObjListener::OBJEVT(3):
        if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            for (GmkDoorPhantomTargetInfo* it = m_targets.begin(); it != m_targets.end(); ++it) {
                if (it->m_gob == handle) {
                    m_targets.erase(it);
                    break;
                }
            }
        }
        break;
    }
}
void GmkMapGimmick::BdatInfo::create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
    m_popTime.m_time = (unsigned short)Bdat::getValCheck(bdat.m_fp, "popTime", row, 3);
    m_popWeather.m_weather = (unsigned char)Bdat::getValCheck(bdat.m_fp, "popWeather", row, 1);
    m_bootedGmk = BootedGmkCond(bdat, row, nullptr);
    m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
    m_nameRadius = (unsigned short)Bdat::getValCheck(bdat.m_fp, "nameRadius", row, 2);
    m_mapobjId = (unsigned short)Bdat::getValCheck(bdat.m_fp, "mapobjID", row, 2);
    m_effectId = gf::GfGameManager::isGameTypeIra() ? (unsigned short)Bdat::getValCheck(bdat.m_fp, "effectID", row, 2) : 0;
    m_msgRay = Bdat::getFlagVal(bdat.m_fp, "flag", row, "MSG_ray") != 0;
}

void GmkWarp::BdatInfo::create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
    m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
    m_bootedGmk = BootedGmkCond(bdat, row, nullptr);
    m_nameRadius = (unsigned short)Bdat::getValCheck(bdat.m_fp, "nameRadius", row, 2);
    unsigned char* fp = gf::GfDataBdat::getFP(0x5D);
    if (fp != nullptr) {
        int mapId = gf::GfGameManager::getMapID();
        if (mapId >= Bdat::getIdTop(fp) && Bdat::getIdTop(fp) + Bdat::getIdCount(fp) > mapId) {
            unsigned char dispR = Bdat::getValCheck(fp, "ene_disp_r", mapId, 1);
            unsigned char dispH = Bdat::getValCheck(fp, "ene_disp_h", mapId, 1);
            m_eneDisp.m_horizontalSq = (float)dispR * (float)dispR;
            m_eneDisp.m_verticalSq = (float)dispH * (float)dispH;
            unsigned char releaseR = Bdat::getValCheck(fp, "ene_release_r", mapId, 1);
            unsigned char releaseH = Bdat::getValCheck(fp, "ene_release_h", mapId, 1);
            float r = (float)(dispR + releaseR);
            float h = (float)(dispH + releaseH);
            m_eneRelease.m_horizontalSq = r * r;
            m_eneRelease.m_verticalSq = h * h;
        }
    }
}

bool GmkWarp::BdatInfo::isPopCondCommonMatched() const {
    if (m_condition != 0 && !gf::GfGameCond::isGameCond(m_condition)) {
        return false;
    }
    if (m_bootedGmk.isSet() && !m_bootedGmk.isMatch()) {
        return false;
    }
    return true;
}

bool GmkWarp::BdatInfo::isPopCondMatched(const mm::Vec3& pos) const {
    if (!isPopCondCommonMatched()) {
        return false;
    }
    if (!m_eneDisp.isMatch(pos)) {
        return false;
    }
    return true;
}

bool GmkWarp::BdatInfo::isDepopCondMatched(const mm::Vec3& pos) const {
    if (!isPopCondCommonMatched()) {
        return true;
    }
    if (!m_eneRelease.isMatch(pos)) {
        return true;
    }
    return false;
}

void GmkWarp::create(const CreateInfo& info) {
    AGmkBase::create(info);
    Bdat::uVal popDist;
    popDist.ulong = Bdat::getValCheck(gf::GfDataBdat::getFP(0x7B), 0, 1, 8);
    m_popDistSq = popDist.real * popDist.real;
}

void GmkWarp::dispose() {
    for (unsigned int i = 0; i < 2; i++) {
        if (m_iconEffects[i] != 0) {
            mm::mtl::PtrSingleton<fw::EffectManager>::sys()->remove(m_iconEffects[i]);
            m_iconEffects[i] = 0;
        }
    }
    clearGobInsts();
    AGmkBase::dispose();
}

void GmkWarp::onGobEvent(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle) {
    AGmkBase::onGobEvent(evt, handle);
    if (evt == gf::IGfObjListener::OBJEVT(3)) {
        gf::GF_OBJ_HANDLE** gob = nullptr;
        if (m_firstHandle == handle) {
            gob = &m_firstHandle;
        } else if (m_secondHandle == handle) {
            gob = &m_secondHandle;
        }
        if (gob != nullptr) {
            *gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        }
    }
}

void GmkSquad::create(const CreateInfo& info) {
    dispose();
    if (GmkManager::sys()->findGmkSet(info.m_gmkSetId) == nullptr) {
        return;
    }
    m_info = info;
    GmkAcc::CreateInfo accInfo;
    accInfo.m_bdatId = info.m_gmkSetId;
    accInfo.m_type = GmkSquadLeader::TYPE;
    accInfo.pad_8 = info.pad_4;
    m_acc.create(accInfo);
    m_seq = &GmkSquad::seqInit;
    mm::mtl::IntrusiveList<GmkSquad>& list = GmkSquadManager::sys()->m_list;
    if (list.end() == list.find(this)) {
        list.push_back(this);
    }
}

void GmkSquad::seqInit(float) {
    if (!m_acc.isValid()) {
        return;
    }
    GmkSquadLeader* leader = static_cast<GmkSquadLeader*>(m_acc.m_gmk);
    if (leader == nullptr) {
        return;
    }
    IGmkList* members = leader->getBindedSquadMemberList();
    if (members == nullptr || members->getInstNum() == 0) {
        return;
    }
    const GmkSquadLeader::Data* data = leader->getData();
    if (data->m_memberDefType == 1) {
        pad_70 = data->m_lastMember + 1 - data->m_firstMember;
    } else if (data->m_memberDefType == 2) {
        pad_70 = m_info.pad_8;
    }
    m_vec3s.destroy();
    m_vec3s.setAllocator(fw::FrameworkMemory::getAllocator(5));
    m_vec3s.reserve(pad_70);
    for (unsigned int i = 0; i < pad_70; ++i) {
        m_vec3s.push_back(mm::Vec3::zero);
    }
    m_floats.destroy();
    m_floats.setAllocator(fw::FrameworkMemory::getAllocator(5));
    m_floats.reserve(pad_70);
    for (unsigned int i = 0; i < pad_70; ++i) {
        m_floats.push_back(0.0f);
    }
    updatePosRotY(false);
    m_bools.destroy();
    m_bools.setAllocator(fw::FrameworkMemory::getAllocator(5));
    m_bools.reserve(pad_70);
    for (unsigned int i = 0; i < pad_70; ++i) {
        m_bools.push_back(false);
    }
    m_seq = &GmkSquad::seqUpdate;
}

}  // namespace gmk

// instantiated for mm::mtl::Vector<mm::Vec3>::resize (not written yet), gmk::GmkSquad::seqInit
template void mm::mtl::Vector<mm::Vec3>::push_back(mm::Vec3 const&);

namespace gmk {

void GmkWarp::clearGobInsts() {
    if (m_firstHandle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_firstHandle);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_firstHandle);
        m_firstHandle = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    if (m_secondHandle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_secondHandle);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_secondHandle);
        m_secondHandle = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
}

void GmkWarp::reqDeadIcon() {
    if (!m_iconDead) {
        m_iconDead = true;
        for (unsigned int i = 0; i < 2; i++) {
            if (m_iconEffects[i] != 0) {
                mm::mtl::PtrSingleton<fw::EffectManager>::sys()->dead(m_iconEffects[i]);
                m_iconEffects[i] = 0;
            }
        }
    }
}

void GmkWarp::reqRecreateIcon() {
    if (m_iconDead) {
        m_iconDead = false;
        for (unsigned int i = 0; i < 2; i++) {
            if (m_iconEffects[i] == 0) {
                createIcon(i);
            }
        }
    }
}

GmkWarp::~GmkWarp() { dispose(); }
GmkDoor::~GmkDoor() { dispose(); }
void GmkClimbing::BdatInfo::create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
    m_scenarioFlag = ScenarioFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMin", row, 2),
                                      (unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMax", row, 2));
    m_questFlag = QuestFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "QuestFlag", row, 2),
                                (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMin", row, 1),
                                (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMax", row, 1));
    m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
    m_bootedGmk = BootedGmkCond(bdat, row, "OP_");
    m_climiconRadius = (unsigned short)Bdat::getValCheck(bdat.m_fp, "climiconRadius", row, 2);
}

bool GmkClimbing::BdatInfo::isPopCondMatched() const {
    if (m_scenarioFlag.m_scenarioFlagMax != 0 && !m_scenarioFlag.isMatch()) {
        return false;
    }
    if (m_questFlag.m_questFlag != 0 && m_questFlag.m_questFlagMin <= m_questFlag.m_questFlagMax &&
        !m_questFlag.isMatch()) {
        return false;
    }
    if (m_condition != 0 && !gf::GfGameCond::isGameCond(m_condition)) {
        return false;
    }
    if (m_bootedGmk.isSet() && !m_bootedGmk.isMatch()) {
        return false;
    }
    return true;
}

void GmkClimbing::create(const CreateInfo& info) {
    m_iconPos = *m_pos;
    unsigned int height = Bdat::getValCheck(gf::GfDataBdat::getFP(0x7B), 0, 0x25, 8);
    m_iconPos.y += *reinterpret_cast<float*>(&height);
    AGmkBase::create(info);
}

void GmkClimbing::dispose() {
    if (m_iconContext != nullptr) {
        gf::GfMenuObjFieldIcon::close(m_iconContext);
        if (m_iconContext != nullptr) {
            m_iconContext->release();
            m_iconContext = nullptr;
        }
    }
    AGmkBase::dispose();
}

void GmkBlade::BdatInfo::create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
    m_kind = (unsigned char)Bdat::getValCheck(bdat.m_fp, "BladeSizeCheck", row, 1);
    m_scenarioFlag = ScenarioFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMin", row, 2),
                                      (unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMax", row, 2));
    m_timeRange.m_time = (unsigned short)Bdat::getValCheck(bdat.m_fp, "TimeRange", row, 2);
    m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
    m_battleReaction = (unsigned short)Bdat::getValCheck(bdat.m_fp, "BattleReaction", row, 2);
    unsigned int visibleXZ = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Visible_XZ", row, 2);
    unsigned short visibleY = Bdat::getValCheck(bdat.m_fp, "Visible_Y", row, 2);
    m_visibleXZSq = (float)visibleXZ * (float)visibleXZ;
    m_visibleYSq = (float)visibleY * (float)visibleY;
    unsigned short invisibleXZ = Bdat::getValCheck(bdat.m_fp, "Invisible_XZ", row, 2);
    if (invisibleXZ <= visibleXZ) {
        invisibleXZ = visibleXZ + 1;
    }
    unsigned short invisibleY = Bdat::getValCheck(bdat.m_fp, "Invisible_Y", row, 2);
    if (invisibleY <= visibleY) {
        invisibleY = visibleY + 1;
    }
    m_invisibleXZSq = (float)invisibleXZ * (float)invisibleXZ;
    m_invisibleYSq = (float)invisibleY * (float)invisibleY;
}

void GmkDmgGimmick::BdatInfo::create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
    m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
    m_bootedGmk = BootedGmkCond(bdat, row, "DEPOP_");
    m_depopCondition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "DEPOP_Condition", row, 2);
    Bdat::uVal interval;
    interval.ulong = Bdat::getValCheck(bdat.m_fp, "DMG_interval", row, 8);
    m_dmgInterval = interval.real;
    m_pcDmg = (unsigned char)Bdat::getValCheck(bdat.m_fp, "Pc_dmg", row, 1);
    m_enDmg = (unsigned char)Bdat::getValCheck(bdat.m_fp, "EN_dmg", row, 1);
    m_effectName = reinterpret_cast<const char*>(Bdat::getValCheck(bdat.m_fp, "effect_name", row, 7));
    m_seName = (unsigned char)Bdat::getValCheck(bdat.m_fp, "SE_name", row, 1);
    m_volumeMax = (unsigned char)Bdat::getValCheck(bdat.m_fp, "volumeMAX", row, 1);
    m_volumeMin = (unsigned char)Bdat::getValCheck(bdat.m_fp, "volumeMIN", row, 1);
    unsigned short dispR = Bdat::getValCheck(bdat.m_fp, "effect_disp_r", row, 2);
    m_effectDispRSq = (float)dispR * (float)dispR;
    unsigned char releaseR = Bdat::getValCheck(bdat.m_fp, "effect_release_r", row, 1);
    float r = (float)(dispR + releaseR);
    m_effectReleaseRSq = r * r;
}
bool GmkMapGimmick::BdatInfo::isPopCondMatched() const {
    if (m_popTime.m_time != 0 && !m_popTime.isMatch()) {
        return false;
    }
    if (m_popWeather.m_weather != 0 && !m_popWeather.isMatch()) {
        return false;
    }
    if (m_bootedGmk.isSet() && !m_bootedGmk.isMatch()) {
        return false;
    }
    if (m_condition != 0 && !gf::GfGameCond::isGameCond(m_condition)) {
        return false;
    }
    return true;
}

void GmkMapGimmick::setSolved() const { gf::GfGameFlag::setLocal(1, m_createInfo.m_bdatId + 43878, 1); }

bool GmkMapGimmick::isNotSolved() const {
    GameFlagCond cond(1, m_createInfo.m_bdatId + 43878);
    return cond.isMatch(0);
}

void GmkMapGimmick::create(const CreateInfo& info) {
    AGmkBase::create(info);
    if (isValid()) {
        float dist = getBdatInfo()->m_nameRadius + 10.0f;
        m_nameDistSq = dist * dist;
        m_seq = &GmkMapGimmick::seqInit;
    }
}

// links the map objects and the effect its row names (the GmkMapObj fields 0x51/0x52, the GmkEffect fields
// 0xb1/0xb2: set, and whether the gimmick is still unsolved), puts the LOD models in their state, then updates
void GmkMapGimmick::seqInit(float) {
    const BdatInfo* info = getBdatInfo();
    if (info->m_mapobjId != 0) {
        AGmkBase* gmk = GmkManager::sys()->findFirstGmkInstByBdatId(GmkMapObj::TYPE, info->m_mapobjId);
        if (gmk == nullptr) {
            gmk = GmkManager::sys()->findFirstGmkInstByBdatId(GmkRoutedMapObj::TYPE, info->m_mapobjId);
            if (gmk == nullptr) {
                return;
            }
        }
        // the original writes the GmkMapObj fields for a GmkRoutedMapObj too
        GmkMapObj* mapObj = static_cast<GmkMapObj*>(gmk);
        bool notSolved = isNotSolved();
        mapObj->pad_51 = 1;
        mapObj->pad_52 = notSolved;
    }
    if (gf::GfGameManager::isGameTypeIra() && info->m_effectId != 0) {
        GmkEffect* effect =
            static_cast<GmkEffect*>(GmkManager::sys()->findFirstGmkInstByBdatId(GmkEffect::TYPE, info->m_effectId));
        if (effect == nullptr) {
            return;
        }
        bool notSolved = isNotSolved();
        effect->pad_b1 = 1;
        effect->pad_b2 = notSolved;
    }
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set == nullptr || !set->m_createInfo.m_flag) {
        validateLodState();
    }
    m_seq = &GmkMapGimmick::seqUpdate;
}

void GmkMapGimmick::dispose() {
    m_seq = nullptr;
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    AGmkBase::dispose();
}

void GmkMapGimmick::update(float dt) {
    AGmkBase::update(dt);
    if (isValid() && m_seq) {
        (this->*m_seq)(dt);
    }
}

void GmkMapGimmick::debugDraw() const {
    if (isValid()) {
        isNotSolved();
    }
}

// true while it has a game object and the gimmick is solved, its row's conditions fail or the interest position
// is beyond the name distance
bool GmkMapGimmick::canDepopGobInst() const {
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        if (!isNotSolved() || !getBdatInfo()->isPopCondMatched()) {
            return true;
        }
        if (m_nameDistSq > 0.0f && !DistCond::isMatch(m_nameDistSq, *m_pos)) {
            return true;
        }
    }
    return false;
}

bool GmkMapGimmick::validateEffectWithoutLodControl(int lodId, bool flag) const {
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set != nullptr && set->m_createInfo.m_flag) {
        return false;
    }
    m_lodEffect.createAsset(lodId);
    if (!m_lodEffect.m_hasAsset) {
        return false;
    }
    if (m_lodEffect.getAsset(gf::LOD_STATE_ANIM) == nullptr) {
        return false;
    }
    if (flag) {
        void* asset = m_lodEffect.getAsset(gf::LOD_STATE_ANIM);
        if (!mm::mtl::PtrSingleton<fw::EffectManager>::sys()->isLoop(asset)) {
            return false;
        }
    }
    gf::GfFieldLod* fieldLod = gf::GfFieldLod::sys();
    ml::ScnObjModel* model = fieldLod->m_coliAnim.m_info.m_model;
    if (model != nullptr && fieldLod->m_coliAnim.m_info.m_lod != nullptr) {
        unsigned short id = fieldLod->m_lodIds[lodId - fieldLod->m_idTop];
        ml::ScnObjAccSeamPos seam(model);
        int max = seam.getMax();
        for (int i = 0; i < max; i++) {
            ml::ScnObjAccPartsPos parts = seam.getObj(i);
            if (id == parts.getID() && m_lodEffect.m_handle == 0) {
                m_lodEffect.createInst(gf::LOD_STATE_ANIM, parts, false);
            }
        }
    }
    return true;
}

void GmkMapGimmick::onGobEvent(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle) {
    AGmkBase::onGobEvent(evt, handle);
    if (evt == gf::IGfObjListener::OBJEVT(3)) {
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
}

GmkSalvage::~GmkSalvage() { dispose(); }

GmkMapGimmick::~GmkMapGimmick() { dispose(); }

GmkClimbing::~GmkClimbing() { dispose(); }

GmkMapJump::~GmkMapJump() { dispose(); }

void GmkMapObj::BdatInfo::create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
    m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
    unsigned int visibleXZ = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Visible_XZ", row, 2);
    unsigned short visibleY = Bdat::getValCheck(bdat.m_fp, "Visible_Y", row, 2);
    m_visibleXZSq = (float)visibleXZ * (float)visibleXZ;
    m_visibleYSq = (float)visibleY * (float)visibleY;
    unsigned short invisibleXZ = Bdat::getValCheck(bdat.m_fp, "Invisible_XZ", row, 2);
    if (invisibleXZ <= visibleXZ) {
        invisibleXZ = visibleXZ + 1;
    }
    unsigned short invisibleY = Bdat::getValCheck(bdat.m_fp, "Invisible_Y", row, 2);
    if (invisibleY <= visibleY) {
        invisibleY = visibleY + 1;
    }
    m_invisibleXZSq = (float)invisibleXZ * (float)invisibleXZ;
    m_invisibleYSq = (float)invisibleY * (float)invisibleY;
    if (Bdat::getMember(bdat.m_fp, "Priority") != nullptr) {
        m_priority = (unsigned char)Bdat::getValCheck(bdat.m_fp, "Priority", row, 1);
    }
}

void GmkSe::BdatInfo::create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
    m_seType = Bdat::getFlagVal(bdat.m_fp, "flag", row, "se_type") != 0;
    m_playOnce = Bdat::getFlagVal(bdat.m_fp, "flag", row, "play_once") != 0;
    m_seName = (unsigned short)Bdat::getValCheck(bdat.m_fp, "seName", row, 2);
    m_volumeMax = (unsigned char)Bdat::getValCheck(bdat.m_fp, "volumeMAX", row, 1);
    m_volumeMin = (unsigned char)Bdat::getValCheck(bdat.m_fp, "volumeMIN", row, 1);
    m_scenarioFlag = ScenarioFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMin", row, 2),
                                      (unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMax", row, 2));
    m_questFlag = QuestFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "QuestFlag", row, 2),
                                (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMin", row, 1),
                                (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMax", row, 1));
    m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
    m_popTime.m_time = (unsigned short)Bdat::getValCheck(bdat.m_fp, "SEpopTime", row, 2);
    m_weather.m_weather = (unsigned char)Bdat::getValCheck(bdat.m_fp, "wtrSEType", row, 1);
    m_bootedGmk = BootedGmkCond(bdat, row, nullptr);
    m_bootedGmkNot = BootedGmkCond(bdat, row, "OP_");
    m_inRoomVolume = (unsigned char)Bdat::getValCheck(bdat.m_fp, "InRoom_volume", row, 1);
}

void GmkCollection::BdatInfo::create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
    m_popTime.m_time = (unsigned int)Bdat::getValCheck(bdat.m_fp, "POP_TIME", row, 3);
    m_popWeather.m_weather = (unsigned char)Bdat::getValCheck(bdat.m_fp, "popWeather", row, 1);
    m_nameRadius = (unsigned short)Bdat::getValCheck(bdat.m_fp, "nameRadius", row, 2);
    m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
    Bdat::uVal popDist;
    popDist.ulong = Bdat::getValCheck(gf::GfDataBdat::getFP(0x7B), 0, 1, 8);
    m_popDistSq = popDist.real * popDist.real;
    if (gf::GfGameManager::isGameTypeIra()) {
        m_rarity = (unsigned char)Bdat::getValCheck(bdat.m_fp, "rarity", row, 1);
        m_collectionTable = Bdat::getValCheckU16(bdat.m_fp, "CollectionTable", row);
        if (m_collectionTable != 0) {
            unsigned char* fp = gf::GfDataBdat::getFP(0x1E0);
            if (Bdat::getValCheckU8(fp, "randitmPopMin", m_collectionTable) == 1 &&
                Bdat::getValCheckU8(fp, "randitmPopMax", m_collectionTable) == 1) {
                unsigned short itemId = Bdat::getValCheckU16(fp, "itm1ID", m_collectionTable);
                unsigned char per = Bdat::getValCheckU8(fp, "itm1Per", m_collectionTable);
                if (gf::GfItemUtil::isPrecious(itemId) && per == 100) {
                    m_itemId = itemId;
                }
            }
        }
    }
}

bool GmkSe::BdatInfo::isPopCondMatched() const {
    if (m_scenarioFlag.m_scenarioFlagMax != 0 && !m_scenarioFlag.isMatch()) {
        return false;
    }
    if (m_questFlag.m_questFlag != 0 && m_questFlag.m_questFlagMin <= m_questFlag.m_questFlagMax &&
        !m_questFlag.isMatch()) {
        return false;
    }
    if (m_condition != 0 && !gf::GfGameCond::isGameCond(m_condition)) {
        return false;
    }
    if (m_popTime.m_time != 0 && !m_popTime.isMatch()) {
        return false;
    }
    if (m_weather.m_weather != 0 && !m_weather.isMatch()) {
        return false;
    }
    if (m_bootedGmk.isSet() && !m_bootedGmk.isMatch()) {
        return false;
    }
    if (m_bootedGmkNot.isSet() && m_bootedGmkNot.isMatch()) {
        return false;
    }
    return true;
}

GmkCtrlVolSe::GmkCtrlVolSe() : m_seHandle(0), m_dist(0.0f), m_isPaused(false) {}

bool GmkCtrlVolSe::isPlayEnd() const {
    return !mm::mtl::PtrSingleton<fw::SoundManager>::sys()->isPlaying(m_seHandle);
}

void GmkCtrlVolSe::create(const CreateInfo& info) {
    dispose();
    m_info = info;
    m_curPos = info.m_pos;
    createInst();
}

bool DistHvCond::isMatch(const mm::Vec3& pos) const {
    if (!isInterestPosExist()) {
        return false;
    }
    const mm::Vec3& interest = getInterestPos();
    float dy = interest.y - pos.y;
    if (m_verticalSq < dy * dy) {
        return false;
    }
    float dx = interest.x - pos.x;
    float dz = interest.z - pos.z;
    float xzSq = dx * dx + dz * dz;
    return !(m_horizontalSq < xzSq);
}

bool DistCond::isMatch(float distSq, const mm::Vec3& pos) {
    GmkManager* manager = GmkManager::sys();
    if (manager != nullptr && manager->pad_198 != 1) {
        if (manager->pad_198 != 0) {
            return false;
        }
        if (!gf::GfGameManager::isGameTypeIra() && !isPlayerExist()) {
            return false;
        }
    } else {
        ml::Scn* scn = ml::Scn::sys();
        if (scn == nullptr || scn->getCam(-1) == nullptr) {
            return false;
        }
    }
    const mm::Vec3& interest = getInterestPos();
    float dx = interest.x - pos.x;
    float dy = interest.y - pos.y;
    float dz = interest.z - pos.z;
    return !(dx * dx + dy * dy + dz * dz > distSq);
}

ScenarioFlagCond::ScenarioFlagCond(const CBdatWrapper& bdat, int row, const char* prefix) {
    unsigned short min;
    unsigned short max;
    if (prefix == nullptr) {
        min = Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMin", row, 2);
        max = Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMax", row, 2);
    } else {
        mm::mtl::FixStr<32> column;
        column.format("%s%s", prefix, "ScenarioFlagMin");
        min = Bdat::getValCheck(bdat.m_fp, column.m_str, row, 2);
        column.format("%s%s", prefix, "ScenarioFlagMax");
        max = Bdat::getValCheck(bdat.m_fp, column.m_str, row, 2);
    }
    if (max >= min) {
        m_scenarioFlagMin = min;
        m_scenarioFlagMax = max;
    }
}

QuestFlagCond::QuestFlagCond(const CBdatWrapper& bdat, int row, const char* prefix) {
    unsigned short flag;
    unsigned char min;
    unsigned char max;
    if (prefix == nullptr) {
        flag = Bdat::getValCheck(bdat.m_fp, "QuestFlag", row, 2);
        min = Bdat::getValCheck(bdat.m_fp, "QuestFlagMin", row, 1);
        max = Bdat::getValCheck(bdat.m_fp, "QuestFlagMax", row, 1);
    } else {
        mm::mtl::FixStr<32> column;
        column.format("%s%s", prefix, "QuestFlag");
        flag = Bdat::getValCheck(bdat.m_fp, column.m_str, row, 2);
        column.format("%s%s", prefix, "QuestFlagMin");
        min = Bdat::getValCheck(bdat.m_fp, column.m_str, row, 1);
        column.format("%s%s", prefix, "QuestFlagMax");
        max = Bdat::getValCheck(bdat.m_fp, column.m_str, row, 1);
    }
    if (max >= min) {
        m_questFlag = flag;
        m_questFlagMin = min;
        m_questFlagMax = max;
    }
}

bool GameFlagCond::isMatch(unsigned int value) const {
    switch (m_flagType) {
    case 1:
        return gf::GfGameFlag::getLocal(0x1, m_flagIndex) == value;
    case 2:
        return gf::GfGameFlag::getLocal(0x2, m_flagIndex) == value;
    case 3:
        return gf::GfGameFlag::getLocal(0x4, m_flagIndex) == value;
    case 4:
        return gf::GfGameFlag::getLocal(0x8, m_flagIndex) == value;
    case 5:
        return gf::GfGameFlag::getLocal(0x10, m_flagIndex) == value;
    case 6:
        return gf::GfGameFlag::getLocal(0x20, m_flagIndex) == value;
    default:
        return false;
    }
}

PopPosSafeCond::PopPosSafeCond(const CreateInfo* info) : m_isValid(false) {
    if (info != nullptr) {
        // the original stores the defaults again before the copy
        m_info = CreateInfo();
        m_info = *info;
        m_isValid = true;
    }
}

BootedGmkCond::BootedGmkCond(unsigned char type, unsigned short id) : m_gimmickType(0), m_gimmickId(0) {
    set(type, id);
}

BootedGmkCond::BootedGmkCond(const CBdatWrapper& bdat, int row, const char* prefix) : m_gimmickType(0), m_gimmickId(0) {
    mm::mtl::FixStr<32> column;
    if (prefix == nullptr) {
        column = "gimmickType";
    } else {
        column.format("%sgimmickType", prefix);
    }
    unsigned char type = Bdat::getValCheck(bdat.m_fp, column.m_str, row, 1);
    if (prefix == nullptr) {
        column = "gimmickID";
    } else {
        column.format("%sgimmickID", prefix);
    }
    unsigned short id = Bdat::getValCheck(bdat.m_fp, column.m_str, row, 2);
    set(type, id);
}

bool BootedGmkCond::isMatch() const {
    GmkAcc::CreateInfoByBdatId info;
    switch (m_gimmickType) {
    case 1:
        info.m_type = GmkMapGimmick::TYPE;
        break;
    case 2:
        info.m_type = GmkDoor::TYPE;
        break;
    case 3:
        info.m_type = GmkType(0x2A);
        break;
    case 4:
        info.m_type = GmkType(0x26);
        break;
    case 5:
        info.m_type = GmkType(0x25);
        break;
    case 6:
        info.m_type = GmkType(0x30);
        break;
    default:
        return false;
    }
    info.m_bdatId = m_gimmickId;
    GmkAcc acc;
    acc.create(info);
    bool result = false;
    if (acc.isValid()) {
        switch (m_gimmickType) {
        case 1:
            result = !static_cast<const GmkMapGimmick*>(acc.m_gmk)->isNotSolved();
            break;
        case 2: {
            const GmkDoor* door = static_cast<const GmkDoor*>(acc.m_gmk);
            GmkDoor::Progress progress = door->getProgress();
            if (progress != 0 && !(door->m_doorWait < door->getBdatInfo()->m_doorNextwait)) {
                // the original tests the condition's fields off the row, not through isSet
                const BootedGmkCond& sp = door->getBdatInfo()->m_bootedGmk3;
                if (sp.m_gimmickType != 0 && sp.m_gimmickId != 0) {
                    result = progress == 3;
                } else {
                    result = progress == 1;
                }
            }
            break;
        }
        }
    }
    return result;
}

bool GmkEnemyInsts::BdatInfo::isPopCondMatched() const {
    if (m_smnGroups != 0) {
        return false;
    }
    if (isInvincibleCondMatched()) {
        return true;
    }
    if (m_scenarioFlag.m_scenarioFlagMax != 0 && !m_scenarioFlag.isMatch()) {
        return false;
    }
    if (m_questFlag.isSet() && !m_questFlag.isMatch()) {
        return false;
    }
    if (m_condition != 0 && !gf::GfGameCond::isGameCond(m_condition)) {
        return false;
    }
    if (!m_popTime.isMatch()) {
        return false;
    }
    if (m_popWeather.m_weather != 0 && !m_popWeather.isMatch()) {
        return false;
    }
    if (!m_popCloud.isMatch()) {
        return false;
    }
    return !gf::GfManager::isExecModeThater();
}

bool GmkEnemyInsts::BdatInfo::isInvincibleCondMatched() const {
    bool matched = false;
    if (m_mutekiCondition != 0) {
        if (!gf::GfGameCond::isGameCond(m_mutekiCondition)) {
            return false;
        }
        matched = true;
    }
    if (m_mutekiQuestFlag.isSet()) {
        if (!m_mutekiQuestFlag.isMatch()) {
            return false;
        }
        matched = true;
    }
    return matched;
}

bool GmkEnemyInsts::BdatInfo::isPopCondMatchedOfSmn() const {
    if (m_scenarioFlag.m_scenarioFlagMax != 0 && !m_scenarioFlag.isMatch()) {
        return false;
    }
    return true;
}

bool GmkEnemyInsts::PopInfo::hasEneID(unsigned short id, bool popped) const {
    for (unsigned int i = 0; i < 4; i++) {
        const PopEnemyInfo& info = m_enemyInfos[i];
        if (info.pad_10 == nullptr || info.pad_18 == nullptr) {
            continue;
        }
        if (popped && info.pad_3 < 100) {
            continue;
        }
        if (info.m_eneId == id) {
            return true;
        }
    }
    return false;
}

bool GmkEnemyInsts::PopInfo::hasTypeGenus(unsigned char genus, bool popped) const {
    for (unsigned int i = 0; i < 4; i++) {
        const PopEnemyInfo& info = m_enemyInfos[i];
        if (info.pad_10 == nullptr || info.pad_18 == nullptr) {
            continue;
        }
        if (popped && info.pad_3 < 100) {
            continue;
        }
        if (info.m_typeGenus == genus) {
            return true;
        }
    }
    return false;
}

unsigned int GmkEnemyInsts::PopInfo::getGobInstNum() const {
    unsigned int num = 0;
    for (unsigned int i = 0; i < 4; i++) {
        num += m_enemyInfos[i].getGobInstNum();
    }
    return num;
}

void GmkEnemyInsts::PopInfo::PopEnemyInfo::dispose() {
    if (pad_10 != nullptr) {
        delete pad_10;
        pad_10 = nullptr;
    }
    if (pad_18 != nullptr) {
        delete pad_18;
        pad_18 = nullptr;
    }
    pad_24 = 0;
}

void GmkEnemyInsts::PopInfo::removeDefeatedNamedEnemyInfo() {
    unsigned char* fp = gf::GfDataBdat::getFP(0x8b);
    for (unsigned int i = 0; i < 4; i++) {
        PopEnemyInfo& info = m_enemyInfos[i];
        if (info.pad_10 != nullptr && info.pad_18 != nullptr && Bdat::getFlagVal(fp, "Flag", info.m_eneId, "Named") != 0 &&
            gf::GfDataEnemy::getEnemySuppress(info.m_eneId) != 0) {
            info.dispose();
        }
    }
}

gf::GF_OBJ_HANDLE* GmkEnemyInsts::getGobInst(unsigned int index) const {
    for (unsigned int i = 0; i < 4; i++) {
        const PopInfo::PopEnemyInfo& info = m_popInfo.m_enemyInfos[i];
        unsigned int num = info.getGobInstNum();
        if (index < num) {
            unsigned char idx = index;
            if (idx < info.pad_18->size()) {
                return info.pad_18->at(idx);
            }
            return info.pad_10->at(idx - info.pad_18->size());
        }
        index -= num;
    }
    return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
}

bool GmkEnemyInsts::isQuestDead() const {
    for (unsigned int i = 0; i < 4; i++) {
        const PopInfo::PopEnemyInfo& info = m_popInfo.m_enemyInfos[i];
        if (info.pad_21 != info.pad_4) {
            return false;
        }
    }
    return true;
}

void GmkEnemyInsts::createSquad(unsigned short squadId, unsigned int num, float scale) {
    if (m_squad != nullptr) {
        m_squad->release();
        m_squad = nullptr;
    }
    if (squadId != 0) {
        GmkSquad::CreateInfo info;
        info.m_gmkSetId = static_cast<const GmkSet*>(m_gmk->m_list->getCreateInfo().m_param)->m_createInfo.m_bdatId;
        info.pad_4 = squadId - 1;
        info.pad_8 = num;
#line 1311 "D:/Monolithsoft/BF2/prog/application/BF2\\gmk/gmk_enemy/gmk_enemy_impl.h"
        GmkSquad* squad = new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) GmkSquad;
        squad->create(info);
        m_squad = squad;
        squad->addRef();
        m_squad->pad_2c = scale;
    }
}

void GmkEnemyInsts::validateDisp(gf::GF_OBJ_HANDLE* handle) const {
    if (AGmkBase* gmk = getBindedGmkInst(handle)) {
        gmk->getGmkType();
        bool disp = pad_140 != 0;
        gf::GfObjAcc acc(handle);
        if (acc.m_obj != nullptr) {
            acc.setDisp(gf::OBJDISP(8), disp);
        }
    }
}

void GmkEnemyInsts::validateDisp() const {
    unsigned int num = m_popInfo.getGobInstNum();
    for (unsigned int i = 0; i < num; i++) {
        validateDisp(getGobInst(i));
    }
}

bool GmkEnemyInsts::reqForcePopGobInst(const ForcePopEnemyInfo& info) const {
    if (m_popInfo.getGobInstNum() != 0) {
        return false;
    }
    if (m_bdatInfo.m_smnGroups != 0 && !(m_flags & 4)) {
        return false;
    }
    pad_141 = true;
    m_forcePopInfo = info;
    return true;
}

bool GmkEnemyInsts::reqClearRepopCounter() const {
    if (&GmkEnemyInsts::seqUpdateRepopCounter == m_seq) {
        m_clearRepopCounterReq = true;
        return true;
    }
    return false;
}

void GmkEnemyInsts::seqUpdateRepopCounter(const UpdateInfo& info) {
    const int id = pad_10;
    if (id == 40012 || id == 40013) {
        return;
    }
    if (m_clearRepopCounterReq) {
        m_clearRepopCounterReq = false;
        m_popWait = 0.0f;
    }
    if (!pad_141) {
        m_popWait -= info.m_dt;
        if (m_popWait > 0.0f) {
            return;
        }
    }
    m_popInfo.removeDefeatedNamedEnemyInfo();
    m_seq = &GmkEnemyInsts::seqUpdatePopDepop;
}

// the four slots' counts summed here (PopInfo::getGobInstNum's loop adds them in another order)
void GmkEnemyInsts::seqWaitToFadeOutOfGobInst(const UpdateInfo& info) {
    const PopInfo::PopEnemyInfo* infos = m_popInfo.m_enemyInfos;
    if (infos[0].getGobInstNum() + infos[1].getGobInstNum() + infos[2].getGobInstNum() + infos[3].getGobInstNum() == 0) {
        m_seq = &GmkEnemyInsts::seqUpdatePopDepop;
    }
}

bool GmkEnemyInsts::canDepopGobInst() const {
    if (!isValid()) {
        return false;
    }
    const PopInfo::PopEnemyInfo* infos = m_popInfo.m_enemyInfos;
    if (infos[0].getGobInstNum() + infos[1].getGobInstNum() + infos[2].getGobInstNum() + infos[3].getGobInstNum() == 0) {
        return false;
    }
    if (m_bdatInfo.m_smnGroups == 0) {
        if (!(m_flags & 1) && pad_180 == 0) {
            return true;
        }
    } else if (m_bdatInfo.m_scenarioFlag.m_scenarioFlagMax != 0 && !m_bdatInfo.m_scenarioFlag.isMatch()) {
        return true;
    }
    return !(m_flags & 4);
}

void GmkEnemyInsts::onEnemyDead(gf::GF_OBJ_HANDLE* handle) {
    if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(handle);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
    }
    m_popInfo.removeGobInst(handle, true);
    if (m_popInfo.getGobInstNum() == 0) {
        pad_159 = 0;
        if (m_bdatInfo.m_smnGroups == 0) {
            m_popWait = pad_24;
            m_seq = &GmkEnemyInsts::seqUpdateRepopCounter;
        }
    }
}

GmkEnemyInsts::~GmkEnemyInsts() { dispose(); }

void GmkEnemy::dispose() {
    m_insts.dispose();
    AGmkBase::dispose();
}
}  // namespace gmk

// instantiated for gmk::GmkManager::create, gmk::GmkManager::createGmkSet
template void mm::mtl::Vector<gmk::GmkSet*>::expand(unsigned long, unsigned long);

namespace gmk {

GmkEnemy::~GmkEnemy() { dispose(); }

void GmkRoutedEnemy::dispose() {
    if (m_navis.size() != 0) {
        m_navis.destroy();
    }
    m_insts.dispose();
    GmkRoute::dispose();
}

GmkRoutedEnemy::~GmkRoutedEnemy() { dispose(); }

void GmkEnemy::BdatInfo::create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
    m_targetPointName = static_cast<unsigned short>(Bdat::getValCheck(bdat.m_fp, "tagetpoint_name", row, 2));
    m_smnGroups = GmkEnemyInsts::BdatInfo::fn_710058356C(bdat, row);
    m_dispR = Bdat::getVarType(bdat.m_fp, "ene_disp_r") == 2
                  ? static_cast<unsigned short>(Bdat::getValCheck(bdat.m_fp, "ene_disp_r", row, 2))
                  : static_cast<unsigned char>(Bdat::getValCheck(bdat.m_fp, "ene_disp_r", row, 1));
    m_dispH = Bdat::getVarType(bdat.m_fp, "ene_disp_h") == 2
                  ? static_cast<unsigned short>(Bdat::getValCheck(bdat.m_fp, "ene_disp_h", row, 2))
                  : static_cast<unsigned char>(Bdat::getValCheck(bdat.m_fp, "ene_disp_h", row, 1));
}

// with no row only disposes; else keeps the CreateInfo and creates the insts from the row's distances (the list's
// defaults where the row has none)
void GmkEnemy::create(const AGmkBase::CreateInfo& info) {
    if (info.m_bdatInfo == nullptr) {
        dispose();
        return;
    }
    AGmkBase::create(info);
    GmkEnemyInsts::CreateInfo createInfo;
    const BdatInfo* bdat = static_cast<const BdatInfo*>(info.m_bdatInfo);
    const GmkEnemyList* list = static_cast<const GmkEnemyList*>(m_list);
    createInfo.m_gmk = this;
    createInfo.m_bdatFp = list->getBindedBdatFp();
    createInfo.m_bdatId = m_createInfo.m_bdatId;
    createInfo.m_popHeight = bdat->m_dispH != 0 ? bdat->m_dispH : list->m_bdatInfo.m_dispH;
    createInfo.m_depopHeight = createInfo.m_popHeight + list->m_bdatInfo.m_releaseH;
    createInfo.m_popRange = bdat->m_dispR != 0 ? bdat->m_dispR : list->m_bdatInfo.m_dispR;
    createInfo.m_depopRange = createInfo.m_popRange + list->m_bdatInfo.m_releaseR;
    createInfo.m_repopTime = list->m_bdatInfo.m_repopTime * 60.0f;
    m_insts.create(createInfo);
}

// the insts pop and depop by the gimmick's position
void GmkEnemy::update(float dt) {
    AGmkBase::update(dt);
    if (isValid()) {
        GmkEnemyInsts::UpdateInfo updateInfo;
        PopXformFinder finder(this);
        updateInfo.m_dt = dt;
        updateInfo.m_pos = m_pos;
        updateInfo.m_finder = &finder;
        if (m_insts.isValid()) {
            m_insts.updatePopDepopCond(updateInfo);
            if (m_insts.m_seq) {
                (m_insts.*m_insts.m_seq)(updateInfo);
            }
        }
    }
}

// a point at a random angle in [angleMin, angleMax) and a random share in [rateMin, rateMax) of the random walk
// radius around the gimmick's position (StateFieldAreaWalk::getGoalPosRandom; the parameter names are not the
// original's)
mm::Vec3& GmkEnemy::getPositionInRandomWalk(mm::Vec3& out, float angleMin, float angleMax, float rateMin,
                                            float rateMax) const {
    mm::Mat44 rot;
    rot.setRotY(ml::mtRandf1(angleMin, angleMax));
    mm::Vec3 in(0.0f, 0.0f, getData()->m_randomWalkRadius * ml::mtRandf1(rateMin, rateMax));
    out = mm::Vec3(in.x * rot.m[0][0] + in.y * rot.m[1][0] + in.z * rot.m[2][0],
                   in.x * rot.m[0][1] + in.y * rot.m[1][1] + in.z * rot.m[2][1],
                   in.x * rot.m[0][2] + in.y * rot.m[1][2] + in.z * rot.m[2][2]);
    out += *m_pos;
    return out;
}

bool GmkEnemy::isPointInsideRandomWalk(const mm::Vec3& pos) const {
    mm::Vec3 d = *m_pos - pos;
    return d.dot(d) <= getData()->m_randomWalkRadius * getData()->m_randomWalkRadius;
}

// on Ira the wave extension leaves a sealed energy effect where the object died
void GmkEnemy::onEnemyDead(gf::GF_OBJ_HANDLE* handle) {
    if (gf::GfGameManager::isGameTypeIra()) {
        pad_1d0.createSealedEnergyEffect(handle);
    }
    m_insts.onEnemyDead(handle);
}

void GmkEnemy::onGobEvent(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle) {
    AGmkBase::onGobEvent(evt, handle);
    bool ira = gf::GfGameManager::isGameTypeIra();
    if (evt == gf::IGfObjListener::OBJEVT(3) && ira) {
        m_insts.m_waveFlags |= 4;
    }
    if (evt == gf::IGfObjListener::OBJEVT(3)) {
        m_insts.m_popInfo.removeGobInst(handle, false);
        if (m_insts.m_popInfo.getGobInstNum() == 0) {
            m_insts.pad_159 = 0;
        }
    }
}

bool GmkBlade::BdatInfo::isPopCommonCondMatched() const {
    if (m_scenarioFlag.m_scenarioFlagMax != 0 && !m_scenarioFlag.isMatch()) {
        return false;
    }
    if (m_timeRange.m_time != 0 && !m_timeRange.isMatch()) {
        return false;
    }
    if (m_condition != 0 && !gf::GfGameCond::isGameCond(m_condition)) {
        return false;
    }
    if (gf::GfGameManager::isBattle() && m_battleReaction == 1) {
        return false;
    }
    return true;
}

bool GmkCollection::BdatInfo::isPopCondMatchedExceptDist() const {
    if (m_condition != 0 && !gf::GfGameCond::isGameCond(m_condition)) {
        return false;
    }
    if (m_popTime.m_time != 0 && !m_popTime.isMatch()) {
        return false;
    }
    if (m_popWeather.m_weather != 0 && !m_popWeather.isMatch()) {
        return false;
    }
    unsigned short itemId = m_itemId;
    if (itemId != 0) {
        unsigned int enableStock = gf::GfItemUtil::getEnableStock(itemId);
        if ((unsigned int)gf::GfItemUtil::getItemBoxCount(itemId) >= enableStock) {
            return false;
        }
    }
    return true;
}

bool GmkCollection::isFound() const {
    if (gf::GfGameManager::isGameTypeIra()) {
        unsigned int id = m_createInfo.m_bdatId;
        if (id >= 4401 && id - 4401 < 500) {
            return gf::GfGameFlag::getLocal(1, id + 51429) != 0;
        }
    }
    return true;
}

bool GmkCollection::isSameTableID(unsigned short collectionId) const {
    return isValid() && getBdatInfo()->m_collectionTable == collectionId;
}

unsigned int GmkCollection::getCategoryName_fld_gmkname() const {
    if (isValid()) {
        const BdatInfo* info = getBdatInfo();
        if (info->m_collectionTable != 0) {
            unsigned char* fp = gf::GfDataBdat::getFP(0x1e0);
            if (fp != nullptr) {
                return Bdat::getValCheck(fp, "categoryName", info->m_collectionTable, 2);
            }
        }
    }
    return 0;
}

bool GmkCollection::isWaitRepop() const { return gf::GfGameFlag::getLocal(1, m_createInfo.m_bdatId + 29020) != 0; }

void GmkCollection::disposeIcon(bool flag) {
    if (m_iconEffect != 0) {
        if (flag) {
            mm::mtl::PtrSingleton<fw::EffectManager>::sys()->fadeOutDead(m_iconEffect, 5);
        } else {
            mm::mtl::PtrSingleton<fw::EffectManager>::sys()->remove(m_iconEffect);
        }
        m_iconEffect = 0;
    }
}

void GmkCollection::createGfObjHandle() {
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set != nullptr && set->m_createInfo.m_flag) {
        return;
    }
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(m_gob);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    CBdatWrapper bdat(m_list->getBindedBdatFp());
    m_gob = gf::GfObjFactory::createGmkCollection(bdat, m_createInfo.m_bdatId);
    {
        gf::GfObjAcc acc(m_gob);
        acc.setUserData(gf::GfObjUserData(0), reinterpret_cast<unsigned long>(this));
    }
    bool disp;
    if (pad_6c) {
        // the original calls getGmkType here and drops its answer
        getGmkType();
        disp = true;
    } else {
        disp = false;
    }
    gf::GF_OBJ_HANDLE* handle = m_gob;
    if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(handle);
        if (acc.m_obj != nullptr) {
            acc.setDisp(gf::OBJDISP(8), disp);
        }
    }
    if (m_iconEffect != 0) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->setDisp(m_iconEffect, disp);
    }
    gf::GfObjSetupGimmick* setup = mm::mtl::rttiCast<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(m_gob)->m_setup);
    const mm::Vec3* xform = m_pos;
    setup->m_initialPos = xform[0];
    setup->pad_30 = xform[1];
    setTargetable(!isWaitRepop());
}

void GmkCollection::setTargetable(bool targetable) {
    gf::GfGameFlag::setLocal(1, m_createInfo.m_bdatId + 29020, !targetable);
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GF_OBJ_HANDLE* gob = m_gob;
        {
            gf::GfObjAcc acc(gob);
            if (acc.m_obj != nullptr) {
                gf::GfObjSetupGimmick* setup =
                    mm::mtl::rttiCast<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(gob)->m_setup);
                if (targetable) {
                    setup->pad_6c |= 7;
                } else {
                    setup->pad_6c &= ~7;
                }
            }
            if (gf::GfObj* obj = acc.getObj()) {
                if (targetable) {
                    obj->pad_110 |= 7;
                } else {
                    obj->pad_110 &= ~7;
                }
            }
        }
        gf::GfObjAcc acc(m_gob);
        if (gf::GfObj* obj = acc.getObj()) {
            if (gf::GfComBehaviorGmk* behavior = obj->getComponent<gf::GfComBehaviorGmk>(6)) {
                behavior->createMenuObj();
            }
        }
    }
    if (targetable) {
        m_repopCounter = 0.0f;
        m_seq = &GmkCollection::seqUpdatePopDepop;
    } else {
        if (m_repopCounter == 0.0f) {
            m_repopCounter = static_cast<const GmkCollectionList*>(m_list)->m_bdatInfo.m_repopTime * 60.0f;
        }
        m_seq = &GmkCollection::seqUpdateRepopCounter;
    }
}

// the icon effect: "cmn_200_000", in the Ira game one per rarity ("cmn_700_100".."cmn_700_102")
void GmkCollection::createIcon() {
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set != nullptr && set->m_createInfo.m_flag) {
        return;
    }
    if (m_iconEffect != 0) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->remove(m_iconEffect);
        m_iconEffect = 0;
    }
    const BdatInfo* info = getBdatInfo();
    const char* name = "cmn_200_000";
    if (gf::GfGameManager::isGameTypeIra()) {
        const char* names[] = {gf::GfGameManager::isGameTypeIra() ? "cmn_700_100" : "cmn_200_000", "cmn_700_101",
                               "cmn_700_102"};
        name = names[std::min<unsigned int>(info->m_rarity, 3)];
    }
    void* efb = mm::mtl::PtrSingleton<fw::EffectManager>::sys()->search(name, nullptr);
    if (efb == nullptr) {
        return;
    }
    m_iconEffect = mm::mtl::PtrSingleton<fw::EffectManager>::sys()->create(efb, true);
    if (m_iconEffect != 0) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->setCategory(m_iconEffect, fw::EF_CATEGORY(1));
        validateIconPos();
    }
}

void GmkCollection::seqUpdatePopDepop(float) {
    if (!isValid()) {
        return;
    }
    if (m_gob == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) && getBdatInfo()->isPopCondMatched(*this)) {
        createGfObjHandle();
        if (gf::GfGameManager::isGameTypeIra()) {
            unsigned int id = m_createInfo.m_bdatId;
            if (id >= 4401 && id - 4401 < 500) {
                gf::GfGameFlag::setLocal(1, id + 51429, 1);
            }
        }
    } else if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) && !getBdatInfo()->isPopCondMatched(*this)) {
        if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            gf::GfObjAcc acc(m_gob);
            if (acc.m_obj != nullptr) {
                acc.setUserData(gf::GfObjUserData(0), 0);
            }
            gf::GfObjUtil::destroy(m_gob);
            m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        }
        disposeIcon(true);
        return;
    }
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        const mm::Vec3* pos = m_pos;
        float distSq = m_popDistSq;
        if (DistCond::isMatch(distSq, *pos)) {
            if (m_iconEffect == 0) {
                createIcon();
            }
            return;
        }
    }
    disposeIcon(true);
}

void GmkCollection::seqUpdateRepopCounter(float dt) {
    m_repopCounter -= dt;
    if (m_repopCounter > 0.0f) {
        return;
    }
    setTargetable(true);
}

void GmkCollection::onPlayerAccessed(gf::GF_OBJ_HANDLE*) { setTargetable(false); }

void GmkPrecious::debugDraw() const {
    if (isValid()) {
        isPopCondMatched();
    }
}

// the item is not obtained, its row's conditions hold and the interest position lies within the pop distance
bool GmkPrecious::isPopCondMatched() const {
    const BdatInfo* info = getBdatInfo();
    if (isObtained()) {
        return false;
    }
    if (!info->isPopCondMatched()) {
        return false;
    }
    const mm::Vec3* pos = m_pos;
    float distSq = m_popDistSq;
    // isInterestPosExist with the player test that also accepts Ira's control mover
    GmkManager* manager = GmkManager::sys();
    if (manager != nullptr && manager->pad_198 != 1) {
        if (manager->pad_198 != 0) {
            return false;
        }
        if (!gf::GfGameManager::isGameTypeIra() &&
            gf::GfGameManager::getControlMoverForGimmick() == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            return false;
        }
    } else {
        ml::Scn* scn = ml::Scn::sys();
        if (scn == nullptr || scn->getCam(-1) == nullptr) {
            return false;
        }
    }
    const mm::Vec3& interest = getInterestPos();
    float dx = interest.x - pos->x;
    float dy = interest.y - pos->y;
    float dz = interest.z - pos->z;
    return !(dx * dx + dy * dy + dz * dz > distSq);
}

// the player takes the item when it stands within the item_get param's heights and radius of it
void GmkPrecious::updateInActiveList(float) {
    if (!isPlayerExist() || isObtained() || gf::GfGameManager::isBattle() ||
        !gf::GfGameManager::isEnableGetFieldPrecious()) {
        return;
    }
    const mm::Vec3& player = getPlayerPos();
    mm::Vec3 diff = *m_pos - player;
    // list 5's entry 5 read directly (no count check, unlike getAdapter)
    const gf::ItemGetParam* param =
        static_cast<const gf::ItemGetParam*>(fw::ParamManager::get()->m_paramLists[5]->m_entries[5].m_data);
    if (diff.y >= -param->lower && diff.y <= param->upper) {
        diff.y = 0.0f;
        if (diff.dot(diff) <= param->radius * param->radius) {
            gf::GfGameFlag::setLocal(1, m_createInfo.m_bdatId + 47087, 1);
            const BdatInfo* info = getBdatInfo();
            gf::SCOM_ADD_ITEM::create(info->m_itmId, 1);
            gf::GfPlayFactory::createMenuPrecious(info->m_itmId, true);
        }
    }
}

void GmkPrecious::dispose() {
    if (m_menuIcon != nullptr) {
        gf::GfMenuObjFieldIcon::close(m_menuIcon);
        if (m_menuIcon != nullptr) {
            m_menuIcon->release();
            m_menuIcon = nullptr;
        }
    }
    if (m_effectHandle != 0) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->remove(m_effectHandle);
        m_effectHandle = 0;
    }
    disposeGobInst(false);
    AGmkBase::dispose();
}

// leaves the active list; with fade, the game object fades out (destroy command), otherwise it is destroyed now
void GmkPrecious::disposeGobInst(bool fade) {
    if (m_gob == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    TGmkActiveList<GmkPrecious>::removeGmk(this);
    if (fade) {
        gf::GF_OBJ_HANDLE* gob = m_gob;
        gf::GfObjAcc acc(gob);
        if (acc.getObj() != nullptr && !acc.isDestroy() && !acc.testFlag(17)) {
            gf::SCOM_DESTROY_GAME_OBJ::create(gob, 1.0f, 0);
        }
    } else {
        if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            gf::GfObjAcc acc(m_gob);
            if (acc.m_obj != nullptr) {
                acc.setUserData(gf::GfObjUserData(0), 0);
            }
        }
        gf::GfObjUtil::destroy(m_gob);
        m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
}

// pops while the pop conditions hold, fades out when they stop holding or once the item is obtained
void GmkPrecious::update(float dt) {
    AGmkBase::update(dt);
    if (!isValid() || !gf::GfGameManager::isControlFree()) {
        return;
    }
    if (m_effectHandle == 0) {
        if (isPopCondMatched()) {
            createGobInst();
            createEffectIcon();
            validateXform();
        }
    } else if (!isPopCondMatched()) {
        disposeGobInst(true);
        if (m_effectHandle != 0) {
            mm::mtl::PtrSingleton<fw::EffectManager>::sys()->fadeOutDead(m_effectHandle, 5);
            m_effectHandle = 0;
        }
        if (m_menuIcon != nullptr) {
            gf::GfMenuObjFieldIcon::close(m_menuIcon);
            if (m_menuIcon != nullptr) {
                m_menuIcon->release();
                m_menuIcon = nullptr;
            }
        }
    }
    if (m_gob != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) && m_menuIcon == nullptr) {
        createMenuIcon();
    }
    updateMenuIcon();
    if (m_effectHandle != 0 && isObtained()) {
        disposeGobInst(true);
        if (m_effectHandle != 0) {
            mm::mtl::PtrSingleton<fw::EffectManager>::sys()->fadeOutDead(m_effectHandle, 5);
            m_effectHandle = 0;
        }
        if (m_menuIcon != nullptr) {
            gf::GfMenuObjFieldIcon::close(m_menuIcon);
            if (m_menuIcon != nullptr) {
                m_menuIcon->release();
                m_menuIcon = nullptr;
            }
        }
    }
}

// the icon effect over the item (cmn_700_110 in Ira, cmn_202_000 otherwise)
void GmkPrecious::createEffectIcon() {
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set != nullptr && set->m_createInfo.m_flag) {
        return;
    }
    if (m_effectHandle != 0) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->remove(m_effectHandle);
        m_effectHandle = 0;
    }
    const char* name = gf::GfGameManager::isGameTypeIra() ? "cmn_700_110" : "cmn_202_000";
    void* efb = mm::mtl::PtrSingleton<fw::EffectManager>::sys()->search(name, nullptr);
    if (efb == nullptr) {
        return;
    }
    m_effectHandle = mm::mtl::PtrSingleton<fw::EffectManager>::sys()->create(efb, true);
    if (m_effectHandle != 0) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->setCategory(m_effectHandle, fw::EF_CATEGORY(1));
    }
}

// the quest target icon over the item's object, when its quest gives one
void GmkPrecious::createMenuIcon() {
    const GmkSet* set = static_cast<const GmkSet*>(m_list->getCreateInfo().m_param);
    if (set != nullptr && set->m_createInfo.m_flag) {
        return;
    }
    if (m_menuIcon != nullptr) {
        gf::GfMenuObjFieldIcon::close(m_menuIcon);
        if (m_menuIcon != nullptr) {
            m_menuIcon->release();
            m_menuIcon = nullptr;
        }
    }
    gf::GF_OBJ_HANDLE* gob = m_gob;
    if (gob == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    unsigned short questId = getBdatInfo()->m_questId;
    int icon;
    {
        gf::GfObjAcc acc(gob);
        if (acc.m_obj == nullptr || acc.isDestroy() || acc.testFlag(17) || acc.getObj() == nullptr) {
            return;
        }
        icon = getBdatIdOfQuestTargetIcon(gf::GfQuestTarget::getIconType(gob, gf::QuestID(questId)));
    }
    if (icon < 0) {
        return;
    }
    m_menuIcon = gf::GfMenuCallContext::create();
    gf::GfMenuObjFieldIcon::OpenParam param;
    param.m_offset.m_offset = mm::Vec3(0.0f, 0.0f, 0.0f);
    param.m_offset.m_bone = nullptr;
    param.m_icon = icon;
    param.m_pos.x = m_pos->x;
    param.m_pos.y = m_pos->y;
    param.m_pos.z = m_pos->z;
    unsigned char* fp = gf::GfDataBdat::getFP(0x7b);
    gf::GfMenuBdat::getMenuOffset((unsigned short)Bdat::getValCheck(fp, 1, 0x2a, 2), param.m_offset);
    gf::GfMenuObjFieldIcon::open(m_menuIcon, param);
}

void GmkPrecious::updateMenuIcon() {
    if (m_gob == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) || m_menuIcon == nullptr) {
        return;
    }
    gf::GfObjAcc acc(m_gob);
    bool render = false;
    if (gf::GfObj* obj = acc.getObj()) {
        if (gf::GfComModel* model = obj->getComponent<gf::GfComModel>(1)) {
            render = model->isRender();
        }
    }
    gf::GfMenuObjFieldIcon::disp(m_menuIcon, render);
}

void GmkPrecious::onGobEvent(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle) {
    AGmkBase::onGobEvent(evt, handle);
    if (evt == gf::IGfObjListener::OBJEVT(3)) {
        disposeGobInst(false);
    }
}

bool GmkPrecious::isObtained() const { return gf::GfGameFlag::getLocal(1, m_createInfo.m_bdatId + 47087) != 0; }

}  // namespace gmk
