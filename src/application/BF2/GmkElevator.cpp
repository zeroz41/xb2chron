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

}  // namespace gmk
