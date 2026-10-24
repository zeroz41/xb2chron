#include "classes/gf/GfQuestTarget.h"
#include "classes/gf/GfFieldGimmick.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkAcc.h"
#include "classes/gmk/GmkManager.h"
#include "classes/gmk/GmkTbox.h"
#include "classes/gmk/GmkPrecious.h"
#include "classes/gmk/GmkEvent.h"
#include "classes/gmk/GmkLandmark.h"
#include "classes/gf/AFieldLocator.h"
#include "classes/gf/LocatorTbox.h"
#include "classes/gf/LocatorPreciousPreorder.h"
#include "classes/gf/LocatorEventPreorder.h"
#include "classes/gf/LocatorReach.h"
#include "classes/gf/LocatorPrecious.h"

namespace gf {

void LocatorTbox::update() {
    if (m_tboxId == 0) {
        return;
    }
    m_posNum = 0;
    if (!m_acc.m_info.isValid()) {
        gmk::GmkAcc::CreateInfo info;
        const gmk::AGmkBase* gmk = gmk::GmkManager::sys()->findFirstGmkInstByBdatId(gmk::GmkTbox::TYPE, m_tboxId);
        if (gmk != nullptr) {
            info.validate(*gmk);
            if (info.isValid()) {
                m_acc.create(info);
            }
        }
    }
    if (m_acc.isValid()) {
        const gmk::GmkTbox* tbox = static_cast<const gmk::GmkTbox*>(m_acc.m_gmk);
        if (!tbox->getBdatInfo()->isPopCondMatchedExceptDist()) {
            return;
        }
        if (tbox->getProgress() == 1) {
            return;
        }
        m_pos = *m_acc.m_gmk->m_pos;
    }
    m_posNum = 1;
}
void LocatorPreciousPreorder::update() {
    if (m_preciousId == 0) {
        return;
    }
    m_posNum = 0;
    if (!m_acc.m_info.isValid()) {
        gmk::GmkAcc::CreateInfo info;
        const gmk::AGmkBase* gmk =
            gmk::GmkManager::sys()->findFirstGmkInstByBdatId(gmk::GmkPrecious::TYPE, m_preciousId);
        if (gmk != nullptr) {
            info.validate(*gmk);
            if (info.isValid()) {
                m_acc.create(info);
            }
        }
    }
    if (m_acc.isValid()) {
        const gmk::GmkPrecious* precious = static_cast<const gmk::GmkPrecious*>(m_acc.m_gmk);
        if (precious->isObtained()) {
            return;
        }
        if (!precious->getBdatInfo()->isPopCondMatched()) {
            return;
        }
        m_pos = *m_acc.m_gmk->m_pos;
    }
    m_posNum = 1;
}
void LocatorEventPreorder::update() {
    if (m_eventId == 0) {
        return;
    }
    m_posNum = 0;
    if (!m_acc.m_info.isValid()) {
        gmk::GmkAcc::CreateInfo info;
        const gmk::AGmkBase* gmk = gmk::GmkManager::sys()->findFirstGmkInstByBdatId(gmk::GmkEvent::TYPE, m_eventId);
        if (gmk != nullptr) {
            info.validate(*gmk);
            if (info.isValid()) {
                m_acc.create(info);
            }
        }
    }
    if (m_acc.isValid()) {
        const gmk::GmkEvent* event = static_cast<const gmk::GmkEvent*>(m_acc.m_gmk);
        if (!event->m_isCondMatched) {
            return;
        }
        m_pos = *m_acc.m_gmk->m_pos;
    }
    m_posNum = 1;
}
void LocatorPrecious::onTraverse(const gmk::AGmkBase& gmk) {
    if (!gmk.isValid()) {
        return;
    }
    const gmk::GmkPrecious& precious = static_cast<const gmk::GmkPrecious&>(gmk);
    if (precious.getBdatInfo()->m_itmId != m_preciousId) {
        return;
    }
    if (precious.isObtained()) {
        return;
    }
    gmk::GmkAcc::CreateInfo info;
    info.validate(gmk);
    m_accs.push_back(gmk::GmkAcc(info));
    m_posList.push_back(*gmk.m_pos);
}
LocatorTbox::LocatorTbox(QuestID questId, unsigned short tboxId) : m_tboxId(0), m_posNum(0) {
    if (!questId.empty() && tboxId != 0) {
        create(questId, tboxId);
    }
}

}  // namespace gf
