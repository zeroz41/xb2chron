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
static inline const char* getGmkKindName(const char** names, int type) {
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

GmkDmgPhantomList::~GmkDmgPhantomList() {}

GmkDmgEffectList::~GmkDmgEffectList() {}

GmkDmgSeList::~GmkDmgSeList() {}

GmkRoutedFootPrintPointList::~GmkRoutedFootPrintPointList() {}

GmkSalvageLocatorList::~GmkSalvageLocatorList() {}

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
    const char* name = Bdat::getValCheck(fp, "salvage", id, 7);
    if (name == nullptr || *name == '\0') {
        return;
    }
    m_gmkLists[GmkEnemy::TYPE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkEnemyList(0);
    typedef TGmkFormPc<GmkType(24), TGmkFormPcnpc<GmkType(25)> > FormPc;
    typedef TGmkFormPcnpc<GmkType(25)> FormPcnpc;
    m_gmkLists[FormPc::TYPE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false)
        TGmkFormPcList<FormPc, TGmkList<FormPc, FormPc::BdatInfo, 1129337414u, 3u, GmkFormPcGob> >;
    m_gmkLists[FormPcnpc::TYPE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false)
        TGmkFormPcnpcList<FormPcnpc, TGmkList<FormPcnpc, FormPcnpc::BdatInfo, 1347310150u, 2u, GmkFormPcnpcGob> >;
    m_gmkLists[GmkSalvageLocator::TYPE] = new (fw::FrameworkMemory::getMem(5), nullptr, 0, 4, false) GmkSalvageLocatorList;
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
            bdatName = Bdat::getMember(setFp, column.m_str) != nullptr ? Bdat::getValCheck(setFp, column.m_str, id, 7) : nullptr;
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

}  // namespace gmk
