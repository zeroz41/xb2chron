#include "classes/gmk/GmkAreaWeather.h"
#include "classes/gmk/GmkBattleLock.h"
#include "classes/gmk/GmkBlade.h"
#include "classes/gmk/GmkClimbing.h"
#include "classes/gmk/GmkDmgGimmick.h"
#include "classes/gmk/GmkDoor.h"
#include "classes/gmk/GmkEffectLocator.h"
#include "classes/gmk/GmkElevatorLocator.h"
#include "classes/gmk/GmkEvent.h"
#include "classes/gmk/GmkFieldLock.h"
#include "classes/gmk/GmkFieldVolume.h"
#include "classes/gmk/GmkGrave.h"
#include "classes/gmk/GmkKizunaTalk.h"
#include "classes/gmk/GmkLandmark.h"
#include "classes/gmk/GmkMapJump.h"
#include "classes/gmk/GmkMapObj.h"
#include "classes/gmk/GmkNpc.h"
#include "classes/gmk/GmkPrecious.h"
#include "classes/gmk/GmkRoutedFootPrint.h"
#include "classes/gmk/GmkRoutedMapObj.h"
#include "classes/gmk/GmkRoutedMob.h"
#include "classes/gmk/GmkRoutedNpc.h"
#include "classes/gmk/GmkSe.h"
#include "classes/gmk/GmkSeLine.h"
#include "classes/gmk/GmkSeLinePoint.h"
#include "classes/gmk/GmkSquadLeader.h"
#include "classes/gmk/GmkSquadMember.h"
#include "classes/gmk/GmkTargetPoint.h"
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
#include "classes/gmk/TUnk_B6EE88.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gmk/IGmkList.h"
#include "classes/gmk/GmkGobEventListener.h"
#include "classes/gmk/GmkSalvageLocator.h"
#include "classes/gmk/TGmkList.h"
#include "classes/gmk/GmkNpcManager.h"
#include "classes/gmk/GmkSet.h"
#include "classes/gmk/GmkSetOfSalvageChildren.h"
#include "classes/gmk/GmkManager.h"
#include "classes/gmk/TGmkFormPc.h"
#include "classes/gmk/TGmkFormPcnpc.h"
#include "classes/gmk/TGmkFormPcList.h"
#include "classes/gmk/TGmkFormPcnpcList.h"
#include "classes/gmk/GmkEnemyList.h"
#include "classes/fw/FrameworkMemory.h"
#include "mtl/MemManager.h"
#include "plugin/Bdat.h"
#include "classes/gmk/IGmkList.h"
#include "classes/gmk/GmkAccManager.h"
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
#include "classes/gmk/GmkMapGimmick.h"
#include "classes/gmk/GmkRoute.h"
#include "classes/gmk/GmkRoutePoint.h"
#include "classes/gmk/GmkTbox.h"
#include "classes/gmk/GmkTrigger.h"
#include "classes/gmk/GmkWarp.h"

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

void GmkAntiBladeArea::debugDraw() const {}

GmkRoutePointList::~GmkRoutePointList() {}

GmkRoutedEnemyPointList::~GmkRoutedEnemyPointList() {}

GmkMobList::~GmkMobList() {}

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

const char* GmkManager::getSheetnameByType(int id, GmkType type) const {
    mm::mtl::FixStr<256> column;
    column.format("%s_bdat", getGmkKindName(s_gmkKindNames, type));
    unsigned char* setFp = m_gmkSetBdatFp;
    return Bdat::getMember(setFp, column.m_str) != nullptr ? reinterpret_cast<const char*>(Bdat::getValCheck(setFp, column.m_str, id, 7)) : nullptr;
}

int GmkManager::getMapBdatId(int id) const {
    unsigned char* fp = m_gmkSetBdatFp;
    int count = Bdat::getIdCount(fp);
    int top = Bdat::getIdTop(fp);
    if (id < top || id >= top + count) {
        return -1;
    }
    return static_cast<unsigned short>(Bdat::getValCheck(fp, "mapId", id, 2));
}

GmkCollectionList::~GmkCollectionList() {
    dispose();
}

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


void GmkSetOfSalvageChildren::createGmkLists(int id) {
    for (int i = 0; i < GMK_LIST_NUM; ++i) {
        if (m_gmkLists[i] != nullptr) {
            delete m_gmkLists[i];
            m_gmkLists[i] = nullptr;
        }
    }
    unsigned char* fp = GmkManager::sys()->m_gmkSetBdatFp;
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
            unsigned char* setFp = manager->m_gmkSetBdatFp;
            bdatName = Bdat::getMember(setFp, column.m_str) != nullptr ? reinterpret_cast<const char*>(Bdat::getValCheck(setFp, column.m_str, id, 7)) : nullptr;
        }
        IGmkList::CreateInfo info;
        info.m_allocHandle = m_allocHandle;
        info.m_param = this;
        info.m_path = "gmk/";
        info.m_path += name;
        info.m_path += ".lvb";
        if (bdatName != nullptr) {
            info.m_bdatName = bdatName;
        }
        info.m_pos = m_pos;
        info.m_rotY = m_rotY;
        list->create(info);
    }
    m_npcManager.dispose();
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
        unsigned char* fp = manager->m_gmkSetBdatFp;
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
            unsigned char* setFp = manager->m_gmkSetBdatFp;
            bdatName = Bdat::getMember(setFp, column.m_str) != nullptr ? reinterpret_cast<const char*>(Bdat::getValCheck(setFp, column.m_str, id, 7)) : nullptr;
        }
        IGmkList::CreateInfo info;
        info.m_allocHandle = m_allocHandle;
        info.m_param = this;
        info.m_path = "gmk/";
        info.m_path += name;
        info.m_path += ".lvb";
        if (bdatName != nullptr) {
            info.m_bdatName = bdatName;
        }
        info.m_pos = m_pos;
        info.m_rotY = m_rotY;
        list->create(info);
    }
}

}  // namespace gmk
