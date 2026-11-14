#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkTbox.h"
#include "classes/gf/GfComBehaviorGmk.h"
#include "classes/gf/GfMenuFieldSkill.h"
#include "classes/gf/SCOM_QUEST_GIMMICK.h"
#include "gf/GfDropitemEmitter.h"
#include "gf/GfQuestUtil.h"
#include "classes/gf/GfFieldTbox.h"
#include <string.h>
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfObj.h"
#include "fw/UpdateInfo.h"
#include "gf/GfObjAcc.h"
#include "plugin/Bdat.h"
#include "classes/gmk/GmkBattleChallengeReward.h"
#include "classes/gmk/GmkSalvageLocator.h"
#include "classes/gf/GfDataBdat.h"

namespace gf {

GfFieldTbox::~GfFieldTbox() {}

bool GfFieldTbox::isDropitemsEmitted() const {
    return m_emitter.m_isEmitted;
}

void GfFieldTbox::gevMapjump(GEV gev, const MapjumpCallbackInfo&) {
    if (gev == 1) {
        end();
    }
}

void GfFieldTbox::start(GF_OBJ_HANDLE* handle) {
    m_seqTime = 0.0f;
    m_emitter.dispose();
    m_isExcavation = false;
    m_seq = nullptr;
    m_rscId = -1;
    m_isUIEnd = false;
    m_isFsOK = false;
    m_handle = handle;
    gmk::AGmkBase* gmk = gmk::getBindedGmkInst(handle);
    if (gmk == nullptr) {
        return;
    }
    gmk::GmkType type = gmk->getGmkType();
    if (type == gmk::GmkTbox::TYPE) {
        gmk::GmkTbox* tbox = static_cast<gmk::GmkTbox*>(gmk);
        m_rscId = Bdat::getValCheckU16(tbox->getBindedBdatFp(), "RSC_ID", tbox->m_createInfo.m_bdatId);
        m_isExcavation = tbox->getBdatInfo()->m_dig && tbox->getProgress() == 0;
    } else if (type == gmk::GmkSalvageLocator::TYPE) {
        m_rscId = Bdat::getValCheckU16(GfDataBdat::getFP(0x77), "RSC_ID",
                                       static_cast<gmk::GmkSalvageLocator*>(gmk)->pad_e8);
    } else if (type == gmk::GmkBattleChallengeReward::TYPE) {
        m_rscId = static_cast<gmk::GmkBattleChallengeReward*>(gmk)->getBdatId_RSC_TboxList();
    }
    unsigned char* fp = GfDataBdat::getFP(0xac);
    Bdat::uVal time;
    time.ulong = Bdat::getValCheck(fp, "FS_starttime", m_rscId, 8);
    m_fsStartTime = time.real;
    time.ulong = Bdat::getValCheck(fp, "TBOX_open_starttime", m_rscId, 8);
    m_openStartTime = time.real;
    m_seq = &GfFieldTbox::seqWaitCheckFs;
}

void GfFieldTbox::seqWaitCheckFs(float dt) {
    m_seqTime += dt;
    if (m_seqTime < m_fsStartTime) {
        return;
    }
    m_seqTime = 0.0f;
    m_seq = &GfFieldTbox::seqCheckFs;
}

void GfFieldTbox::build(const GfSetupParam& param) {
#line 224
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfFieldTbox(param);
}

void GfFieldTbox::destroy() {
    GfFieldTbox* tbox = get();
    tbox->dispose();
    delete tbox;
}

void GfFieldTbox::update(const fw::UpdateInfo& info) {
    GfFieldTbox* tbox = get();
    if (tbox != nullptr && tbox->m_isCreate) {
        tbox->update(info.m_deltaTime);
    }
}

void GfFieldTbox::seqWaitUIEnd(float) {
    if (GfMenuFieldSkill::isRunning()) {
        return;
    }
    m_isUIEnd = true;
    if (gmk::AGmkBase* gmk = gmk::getBindedGmkInst(m_handle)) {
        gmk::GmkType type = gmk->getGmkType();
        unsigned int id = gmk->m_createInfo.m_bdatId;
        if (GfQuestUtil::getGimmickTaskEndCheck(type, id) == 2) {
            SCOM_QUEST_GIMMICK::createTresure(id, 0.0f);
        }
    }
    m_seq = m_isFsOK ? &GfFieldTbox::seqWaitOpenFieldTbox : nullptr;
    m_seqTime = 0.0f;
}

void GfFieldTbox::seqWaitDigEnd(float) {
    GfObjAcc acc(m_handle);
    GfObj* obj = acc.getObj();
    if (obj == nullptr) {
        end();
        return;
    }
    if (GfComAsm* comAsm = obj->getComponent<GfComAsm>(2)) {
        const char* state = comAsm->getStateName(AnimLayer(0));
        if (state != nullptr && strcmp(state, "S_open_00") != 0) {
            return;
        }
    }
    gmk::AGmkBase* gmk = gmk::getBindedGmkInst(m_handle);
    if (gmk == nullptr) {
        end();
        return;
    }
    static_cast<gmk::GmkTbox*>(gmk)->setTargetable(true);
    GfObjAcc boxAcc(m_handle);
    if (GfComBehaviorGmk* behavior = boxAcc.getObj()->getComponent<GfComBehaviorGmk>(6)) {
        behavior->createMenuObj();
    }
    m_seq = nullptr;
}

void GfFieldTbox::seqWaitDropBegin(float) {
    if (!m_emitter.m_isEmitted) {
        return;
    }
    if (gmk::AGmkBase* gmk = gmk::getBindedGmkInst(m_handle)) {
        gmk::GmkType type = gmk->getGmkType();
        unsigned int id = gmk->m_createInfo.m_bdatId;
        if (GfQuestUtil::getGimmickTaskEndCheck(type, id) == 1) {
            SCOM_QUEST_GIMMICK::createTresure(id, 0.0f);
        }
    }
    m_seq = nullptr;
}

}  // namespace gf
