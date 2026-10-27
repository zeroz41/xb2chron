#include "classes/gf/GfFieldCollect.h"
#include "classes/gf/SCOM_QUEST_GIMMICK.h"
#include "classes/gmk/GmkCollection.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfFieldCollect.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkCollection.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfComBehaviorGmk.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuFieldSkill.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/SCOM_ACHIEV_INC.h"
#include "classes/gf/SCOM_QUEST_GIMMICK.h"
#include "classes/gf/DataParamAcc.h"
#include "fw/UpdateInfo.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDropitemEmitter.h"
#include "gf/GfItemUtil.h"
#include "gf/GfObjAcc.h"
#include "gf/GfQuestUtil.h"
#include "ml/MTRand.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"

namespace gf {

void GfFieldCollect::seqEnd(float) {}

GfFieldCollect::~GfFieldCollect() {}

void GfFieldCollect::gevMapjump(GEV gev, const MapjumpCallbackInfo&) {
    if (gev == 1) {
        end();
    }
}

void GfFieldCollect::start(GF_OBJ_HANDLE* handle) {
    m_emitters.clear();
    m_isUIEnd = false;
    m_seq = &GfFieldCollect::seqWaitDo;
    m_handle = handle;
    m_seqTime = 0.0f;
    unsigned int time =
        Bdat::getValCheck(GfDataBdat::getFP(0x7B), 0, GfGameManager::fn_71002A9E68() ? 0x53 : 4, 8);
    m_doStartTime = *reinterpret_cast<float*>(&time);
}

void GfFieldCollect::createDropitemEmitter(const GfDropitemEmitter::CreateInfo& info) {
    m_emitters.push_back(GfDropitemEmitter(nullptr));
    m_emitters.back().create(info);
}

void GfFieldCollect::build(const GfSetupParam& param) {
#line 188
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfFieldCollect(param);
}

void GfFieldCollect::destroy() {
    GfFieldCollect* collect = get();
    collect->dispose();
    delete collect;
}

void GfFieldCollect::seqWaitUIEnd(float) {
    if (GfMenuFieldSkill::isRunning()) {
        return;
    }
    m_isUIEnd = true;
    SCOM_ACHIEV_INC::addTotalCount(0x41, 1);
    SCOM_ACHIEV_INC::create(0x41, 1, 0);
    SCOM_ACHIEV_INC::create(0x42, 1, 0);
    if (GfGameManager::fn_71002A9E68()) {
        if (gmk::AGmkBase* gmk = gmk::getBindedGmkInst(m_handle)) {
            gmk::GmkType type = gmk->getGmkType();
            unsigned int id = gmk->m_createInfo.m_bdatId;
            if (GfQuestUtil::getGimmickTaskEndCheck(type, id) == 2) {
                SCOM_QUEST_GIMMICK::fn_710055F594(id, 0.0f);
            }
        }
    }
    m_seqTime = 0.0f;
    if (m_isPreciousOnly) {
        m_seq = &GfFieldCollect::fn_71002681C4;
    } else {
        m_seq = &GfFieldCollect::seqDo;
    }
}

}  // namespace gf
