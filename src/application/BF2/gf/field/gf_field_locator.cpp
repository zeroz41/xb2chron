#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkAcc.h"
#include "classes/gmk/GmkManager.h"
#include "classes/gmk/GmkTbox.h"
#include "classes/gmk/GmkPrecious.h"
#include "classes/gf/AFieldLocator.h"
#include "classes/gf/LocatorTbox.h"
#include "classes/gf/LocatorPreciousPreorder.h"

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

}  // namespace gf
