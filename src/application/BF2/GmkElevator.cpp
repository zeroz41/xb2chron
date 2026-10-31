#include "classes/gmk/GmkBdat.h"
#include "classes/gmk/GmkPhantomManager.h"
#include "classes/gmk/GmkLandmarkManager.h"
#include "classes/gmk/GmkBgmCondInfoManager.h"
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
#include "gf/GfItemUtil.h"
#include "classes/gmk/GmkTutorial.h"
#include "classes/gmk/TUnk_B6D590.h"
#include "classes/gmk/TUnk_B6D5F8.h"
#include "classes/gmk/TUnk_B6D660.h"
#include "classes/gmk/TUnk_B6D6C8.h"
#include "classes/gmk/GmkNpcList.h"
#include "classes/gmk/GmkRoutedEnemyList.h"
#include "classes/gmk/GmkRoutedNpcList.h"
#include "classes/gmk/GmkSalvageList.h"
#include "classes/gmk/TUnk_B6E340.h"
#include "classes/gmk/TUnk_B6ED38.h"
#include "classes/gmk/GmkBdat.h"
#include "classes/gmk/GmkLandmarkManager.h"
#include "classes/gmk/GmkSquadManager.h"
#include "classes/gmk/TUnk_B6EE88.h"
#include "classes/gf/GfGameManager.h"
#include "fw/NaviUtil.h"
#include "classes/gf/GfFieldTime.h"
#include "classes/gf/GfFieldWeather.h"
#include "classes/gf/GfGameFlag.h"
#include "gf/GfDataBlade.h"
#include "gf/GfQuestInfo.h"
#include "gf/GfObjAcc.h"
#include "classes/gf/GfComBehaviorNpc.h"
#include "gf/GfObjUtil.h"
#include "classes/gmk/GmkEnemy.h"
#include "classes/gmk/GmkRoutedEnemy.h"
#include "classes/gmk/GmkSalvage.h"
#include "classes/gmk/GameFlagCond.h"
#include "classes/gf/GfManager.h"
#include "arc/CArcData.h"
#include "classes/fw/CommonResource.h"
#include "classes/fw/SoundResSourceManager.h"
#include "classes/gf/GfAllocator.h"
#include "gf/GfSoundSource.h"
#include "classes/gf/GfObjManager.h"
#include "gf/GfStaticRes.h"
#include "gf/GfUtil.h"
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
#include "mm/Mat44.h"
#include "classes/gmk/Lvlb.h"
#include "classes/gf/GfFieldLod.h"
#include "classes/gf/GfFieldGimmick.h"
#include "classes/gf/MenuCommonWindowParam.h"
#include "gf/GfPlayFactory.h"
#include "classes/gf/SCOM_DESTROY_GAME_OBJ.h"
#include "classes/gf/SCOM_QUEST_GIMMICK.h"
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

bool GmkManager::isValid() const {
    return m_bdat.pad_120 != 0 && fw::BdatManager::isEnableBdat(m_bdat.m_createInfo.m_param) && m_bdatFp != nullptr;
}

void GmkManager::seqWaitValidateResDefBdatFp(float) {
    if (m_bdat.pad_120 != 0 && fw::BdatManager::isEnableBdat(m_bdat.m_createInfo.m_param)) {
        m_bdatFp = Bdat::getFP(m_createInfo.m_tableName.m_str);
        m_seq = &GmkManager::seqUpdate;
    }
}

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
    if (m_bdat.pad_120 != 0 && fw::BdatManager::isEnableBdat(m_bdat.m_createInfo.m_param)) {
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

void GmkRoutedEnemyList::update(float dt) {
    m_triggerList.update(dt);
    TGmkList::update(dt);
}

void GmkRoutedEnemyList::debugUpdateMmf() {
    TGmkList::debugUpdateMmf();
    m_triggerList.debugUpdateMmf();
}

void GmkRoutedEnemyList::debugDraw() const {
    TGmkList::debugDraw();
    m_triggerList.debugDraw();
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
    return m_bdat.pad_120 != 0 && fw::BdatManager::isEnableBdat(bdat.m_param);
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

int getCurrentMapBdatId() { return gf::GfGameManager::getMapID(); }

const IGmkList* GmkSet::getGmkList(GmkType type) const { return m_gmkLists[static_cast<unsigned int>(type)]; }

IGmkList* GmkSet::getGmkList(GmkType type) { return m_gmkLists[static_cast<unsigned int>(type)]; }

GmkNpcManager::~GmkNpcManager() { dispose(); }

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
    m_listParam = 0x20;
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
    m_gmkLists[60] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TUnk_B6ED38(3);
    m_gmkLists[61] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TUnk_B6EE88(1);
    m_gmkLists[62] = gf::GfGameManager::fn_71002A9E68() ? 
        new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TGmkList<TUnk_B6D660, TUnk_B6D660::BdatInfo, 1347240259u, 1u, TUnk_B6D660Gob>(1) : nullptr;
    m_gmkLists[63] = gf::GfGameManager::fn_71002A9E68() ? 
        new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) TUnk_B6E340(1) : nullptr;
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
gmk::GmkType GmkRoute::getGmkType() const { return TYPE; }
gmk::GmkType GmkRoutedEnemy::getGmkType() const { return TYPE; }
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

// the accesses it still holds lose their gimmick
GmkAccManager::~GmkAccManager() {
    for (::mm::mtl::IntrusiveList<GmkAcc>::iterator it = m_list1.begin(); it != m_list1.end(); ++it) {
        it->m_gmk = nullptr;
    }
    for (::mm::mtl::IntrusiveList<GmkAcc>::iterator it = m_list0.begin(); it != m_list0.end(); ++it) {
        it->m_gmk = nullptr;
    }
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

bool GmkCamera::isLoaded() const { return m_camera.get()->isLoaded(); }

bool GmkCamera::isEnd() const {
    if (m_camera.get() == nullptr) {
        return true;
    }
    return m_camera.get()->isPlayEnd();
}

void GmkCamera::update(float dt) {
    if (m_name.length() > 0 && m_seq) {
        (this->*m_seq)(dt);
    }
}

void GmkCamera::play() { m_seq = &GmkCamera::seqWaitToPlay; }

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

void GmkRouteNavi::dispose() {
    pad_ac = 0;
    pad_a4 = false;
    pad_a0 = 0;
    pad_80 = false;
    m_info = CreateInfo();
}

unsigned int GmkRoute::getRoutePointNum() const { return getData()->m_pointEnd - getData()->m_pointBegin; }
bool GmkRoute::isClosed() const { return getData()->m_flags & 1; }

void GmkRoute::debugDraw() const {
    AGmkBase::debugDraw();
    if (isValid()) {
        debugDrawRoute(mm::Col4::yellow);
    }
}

// the route point list of each routed kind in the gimmick set that made its list (GmkSet::createGmkLists passes the
// set as the list's CreateInfo::m_param); kinds 5, 8 and 20 have no class in the headers yet
IGmkList* GmkRoutedEnemy::getBindedRoutePointList() const {
    return static_cast<const GmkSet*>(m_list->getCreateInfo().m_param)->m_gmkLists[GmkRoutedEnemyPoint::TYPE];
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
IGmkList* GmkRoute::getBindedRoutePointList() const {
    return static_cast<const GmkSet*>(m_list->getCreateInfo().m_param)->m_gmkLists[GmkRoutePoint::TYPE];
}

void GmkEvent::create(const CreateInfo& info) { AGmkBase::create(info); }
void GmkBattleLock::create(const CreateInfo& info) { AGmkBase::create(info); }
void GmkFieldLock::create(const CreateInfo& info) { AGmkBase::create(info); }

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

bool isPlayerExist() { return gf::GfGameManager::fn_71002AA074() != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1); }

bool isNaviMeshExist(const mm::Vec3& pos) {
    mm::Vec3 out;
    return fw::NaviUtil::testNaviColi(out, pos, 2.0f, 2.0f);
}

const char* debugGetGmkBdatRowName(const AGmkBase&) { return "(null)"; }
const char* debugGetGmkBdatSheetName(const AGmkBase&) { return "(null)"; }

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

int GmkTbox::getProgress() const { return gf::GfGameFlag::getLocal(2, m_createInfo.m_bdatId + 31765); }

void GmkTbox::debugDraw() const {
    AGmkBase::debugDraw();
    isValid();
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

void GmkSalvage::create(const CreateInfo& info) {
    AGmkBase::create(info);
    unsigned char* fp = gf::GfDataBdat::getFP(0x7B);
    unsigned int popDist = Bdat::getValCheck(fp, 0, 0x1E, 8);
    m_popDistSq = *reinterpret_cast<float*>(&popDist) * *reinterpret_cast<float*>(&popDist);
    unsigned int dist = Bdat::getValCheck(fp, 0, 0x3A, 8);
    pad_64 = *reinterpret_cast<float*>(&dist) * *reinterpret_cast<float*>(&dist);
    m_seq = &GmkSalvage::seqValidateGmkSalvageLocatorDetails;
}

void GmkSalvage::dispose() {
    disposeRaffle(false);
    m_seq = nullptr;
    m_enemyLocators.clear();
    pad_a8 = 0;
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

GmkSquadLeader* GmkSquad::getBindedGmkSquadLeader() const {
    if (m_acc.isValid()) {
        IGmkList* members = static_cast<GmkSquadLeader*>(m_acc.m_gmk)->getBindedSquadMemberList();
        if (members != nullptr && members->getInstNum() != 0 && pad_70 != 0) {
            return static_cast<GmkSquadLeader*>(m_acc.m_gmk);
        }
    }
    return nullptr;
}
GmkElevatorLocator::~GmkElevatorLocator() { dispose(); }
GmkTargetPoint::~GmkTargetPoint() { dispose(); }
GmkRoutedEnemyPoint::~GmkRoutedEnemyPoint() { dispose(); }

GmkElevator::~GmkElevator() { dispose(); }

// ---- GmkDmgGimmick
void GmkDmgGimmick::seqWaitToCreateChild(float) {
    m_seq = &GmkDmgGimmick::seqUpdatePopDepop;
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

// ---- TUnk_B6D590 (placeholder slot symbols: see its header)
void TUnk_B6D590::dispose() {
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

void TUnk_B6D590::update(float dt) {
    AGmkBase::update(dt);
    if (m_seq) {
        (this->*m_seq)(dt);
    }
}

TUnk_B6D590::~TUnk_B6D590() { dispose(); }

gmk::GmkType TUnk_B6D590::getGmkType() const { return TYPE; }

bool TUnk_B6D590::isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }

void TUnk_B6D590::onPlayerAccessed(gf::GF_OBJ_HANDLE*) {
    m_isAccessed = true;
}

// ---- TUnk_B6D5F8 (placeholder slot symbols: see its header)
void TUnk_B6D5F8::update(float dt) {
    if (isValid()) {
        AGmkBase::update(dt);
        if (m_seq) {
            (this->*m_seq)(dt);
        }
    }
}

TUnk_B6D5F8::~TUnk_B6D5F8() { dispose(); }

gmk::GmkType TUnk_B6D5F8::getGmkType() const { return TYPE; }

bool TUnk_B6D5F8::isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }

// ---- TUnk_B6D660, TUnk_B6D6C8 (placeholder slot symbols: see their headers)
void TUnk_B6D660::create(const CreateInfo& info) {
    AGmkBase::create(info);
    unsigned char* fp = gf::GfDataBdat::getFP(0x7B);
    unsigned int dist = Bdat::getValCheck(fp, 0, 0x58, 8);
    float popDist = *reinterpret_cast<float*>(&dist);
    m_popDistSq = popDist * popDist;
    unsigned int value = Bdat::getValCheck(fp, 0, 0x5B, 8);
    pad_58 = *reinterpret_cast<float*>(&value);
}

void TUnk_B6D660::dispose() {
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

void TUnk_B6D660::debugDraw() const { AGmkBase::debugDraw(); }

TUnk_B6D660::~TUnk_B6D660() { dispose(); }

gmk::GmkType TUnk_B6D660::getGmkType() const { return TYPE; }

void TUnk_B6D6C8::create(const CreateInfo& info) {
    AGmkBase::create(info);
    gf::GfDataBdat::getFP(0x7B);
    m_seq = &TUnk_B6D6C8::fn_71005B9BDC;
}

void TUnk_B6D6C8::fn_71005B9BDC(float) { m_seq = &TUnk_B6D6C8::fn_71005BA88C; }

void TUnk_B6D6C8::dispose() {
    if (m_effectHandle != 0) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->remove(m_effectHandle);
        m_effectHandle = 0;
    }
    fn_71005B9C38(false);
    AGmkBase::dispose();
}

void TUnk_B6D6C8::debugDraw() const { AGmkBase::debugDraw(); }

void TUnk_B6D6C8::fn_71005BA88C(float) {}

void TUnk_B6D6C8::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE* handle) {
    if (event == gf::IGfObjListener::OBJEVT(3) && handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        gf::GfObjAcc acc(handle);
        if (acc.m_obj != nullptr) {
            acc.setUserData(gf::GfObjUserData(0), 0);
        }
    }
    if (event == gf::IGfObjListener::OBJEVT(3)) {
        fn_71005B9C38(false);
    }
}

TUnk_B6D6C8::~TUnk_B6D6C8() { dispose(); }

gmk::GmkType TUnk_B6D6C8::getGmkType() const { return TYPE; }

// ---- TUnk_B6E340 (the list of kind 0x3F; placeholder slot symbols)
void TUnk_B6E340::create(const IGmkList::CreateInfo& info) {
    TGmkList::create(info);
#line 641 "D:/Monolithsoft/BF2/prog/application/BF2\\gmk/gmk_sealed_stone/gmk_sealed_stone_impl.h"
    m_effects = new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) EffectList();
    m_effects->fn_71005BAA98();
}

void TUnk_B6E340::dispose() {
    if (m_effects != nullptr) {
        m_effects->fn_71005BAC78();
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

void TUnk_B6E340::EffectList::fn_71005BAC78() {
    if (m_entries.size() != 0) {
        for (Entry& entry : m_entries) {
            mm::mtl::PtrSingleton<fw::EffectManager>::sys()->kill(entry.m_effectHandle);
        }
        m_entries.destroy();
    }
}

TUnk_B6E340::~TUnk_B6E340() { dispose(); }

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

void GmkAreaBgm::dispose() {
    for (int i = 0; i < 4; i++) {
        m_condInfos[i].dispose();
    }
    pad_160 = nullptr;
    m_phantom.dispose();
    AGmkBase::dispose();
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

void GmkSeLine::dispose() {
    if (m_seHandle != 0) {
        mm::mtl::PtrSingleton<fw::SoundManager>::sys()->stopSe(m_seHandle, 1.0f);
        m_seHandle = 0;
        TGmkActiveList<GmkSeLine>::removeGmk(this);
    }
    AGmkBase::dispose();
}

GmkSeLine::~GmkSeLine() { dispose(); }

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

void GmkMapObj::dispose() {
    disposeGobInst(false);
    AGmkBase::dispose();
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

void GmkFieldLock::dispose() {
    m_collision.dispose();
    AGmkBase::dispose();
}

GmkFieldLock::~GmkFieldLock() { dispose(); }

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

void GmkMob::dispose() {
    m_insts.dispose();
    AGmkBase::dispose();
}

GmkMob::~GmkMob() { dispose(); }

void GmkRoutedMob::dispose() {
    if (m_navis.size() != 0) {
        m_navis.destroy();
    }
    m_insts.dispose();
    GmkRoute::dispose();
}

GmkRoutedMob::~GmkRoutedMob() { dispose(); }

void GmkLandmark::dispose() {
    disposeGmkPhantom();
    AGmkBase::dispose();
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

GmkNpcList::~GmkNpcList() {
    dispose();
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

GmkLandmarkManager::~GmkLandmarkManager() {
    dispose();
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

bool ScenarioFlagCond::isMatch() const {
    unsigned short flag = gf::GfDataBlade::fn_7100231884();
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
    m_effectId = gf::GfGameManager::fn_71002A9E68() ? (unsigned short)Bdat::getValCheck(bdat.m_fp, "effectID", row, 2) : 0;
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
            m_eneDispRSq = (float)dispR * (float)dispR;
            m_eneDispHSq = (float)dispH * (float)dispH;
            unsigned char releaseR = Bdat::getValCheck(fp, "ene_release_r", mapId, 1);
            unsigned char releaseH = Bdat::getValCheck(fp, "ene_release_h", mapId, 1);
            float r = (float)(dispR + releaseR);
            float h = (float)(dispH + releaseH);
            m_eneReleaseRSq = r * r;
            m_eneReleaseHSq = h * h;
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
    if (gf::GfGameManager::fn_71002A9E68()) {
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

GmkEnemyInsts::~GmkEnemyInsts() { dispose(); }

void GmkEnemy::dispose() {
    m_insts.dispose();
    AGmkBase::dispose();
}

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

bool GmkCollection::fn_710059BFFC(unsigned short collectionId) const {
    return isValid() && getBdatInfo()->m_collectionTable == collectionId;
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

void GmkCollection::seqUpdateRepopCounter(float dt) {
    m_repopCounter -= dt;
    if (m_repopCounter > 0.0f) {
        return;
    }
    setTargetable(true);
}

void GmkCollection::onPlayerAccessed(gf::GF_OBJ_HANDLE*) { setTargetable(false); }

bool GmkPrecious::isObtained() const { return gf::GfGameFlag::getLocal(1, m_createInfo.m_bdatId + 47087) != 0; }

}  // namespace gmk
