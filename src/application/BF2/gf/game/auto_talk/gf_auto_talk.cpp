// gf_auto_talk.cpp (the assertions cite it): the auto talks of a map's gimmick sets
#include "classes/gmk/GmkAcc.h"
#include "classes/gmk/GmkSet.h"
#include "classes/gf/GfMenuObjBalloon.h"
#include "classes/gf/GfFieldGimmick.h"
#include "classes/gf/GfAutoTalk.h"
#include "classes/gf/GfAutoTalkList.h"
#include "classes/gf/GfAutoTalkManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/gmk/GmkManager.h"
#include "classes/gmk/GmkMob.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfObjSetupMob.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/GfObjInfo.h"
#include "gf/GfMenuBdat.h"
#include "mm/mtl/RTTI.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComBehaviorMob.h"
#include "gf/GfObjAcc.h"
#include "fw/UpdateInfo.h"
#include "plugin/Bdat.h"

#define GF_AUTO_TALK_PATH "D:/Monolithsoft/BF2/prog/application/BF2/gf/game/auto_talk/gf_auto_talk.cpp"

namespace gf {

void GfAutoTalk::disposeMenuObj() {
    if (m_context != nullptr) {
        GfMenuObjBalloon::close(m_context, true);
        if (m_context != nullptr) {
            m_context->release();
            m_context = nullptr;
        }
    }
}

void GfAutoTalk::BdatInfo::create(const CBdatWrapper& bdat, int id) {
    dispose();
    m_mobId = Bdat::getValCheckU16(bdat.m_fp, "MOBID", id);
    m_range = Bdat::getValCheckU16(bdat.m_fp, "Range", id);
    m_condition = Bdat::getValCheckU16(bdat.m_fp, "Condition", id);
    m_text = Bdat::getValCheckU16(bdat.m_fp, "Text", id);
    m_ontime = Bdat::getValCheckU16(bdat.m_fp, "Ontime", id);
    m_beforeId = Bdat::getValCheckU16(bdat.m_fp, "BeforeID", id);
    if (m_beforeId != 0) {
        int count = Bdat::getIdCount(bdat.m_fp);
        unsigned short before = m_beforeId;
        unsigned short next;
        int i = 0;
        do {
            next = Bdat::getValCheckU16(bdat.m_fp, "BeforeID", before);
            if (next == 0) {
                break;
            }
            before = next;
            ++i;
        } while (count > i);
        m_range = Bdat::getValCheckU16(bdat.m_fp, "Range", before);
        m_condition = Bdat::getValCheckU16(bdat.m_fp, "Condition", before);
    }
}

void GfAutoTalk::create(const CreateInfo& info) {
    dispose();
    m_info = info;
    m_bdatInfo.create(CBdatWrapper(info.m_fp), info.m_id);
    const BdatInfo& bdat = m_bdatInfo;
    if (bdat.m_mobId == 0) {
        dispose();
    } else {
        float range = bdat.m_range;
        m_dist.m_horizontalSq = range * range;
        m_dist.m_verticalSq = range * range;
        gmk::GmkAcc::CreateInfoByBdatId accInfo;
        accInfo.m_type = gmk::GmkType(0x12);
        accInfo.m_bdatId = bdat.m_mobId;
        m_gmkAcc.create(accInfo);
    }
}

void GfAutoTalk::update(float dt) {
    if (!isValid()) {
        return;
    }
    if (m_context != nullptr && (m_context->isTerm() || !GfGameManager::isAutoTalkOK())) {
        disposeMenuObj();
    }
    if (m_disp && m_dispTime > 0.0f) {
        m_dispTime -= dt;
        if (m_dispTime <= 0.0f) {
            disposeMenuObj();
        }
    }
    if (static_cast<gmk::GmkMob*>(m_gmkAcc.m_gmk)->getGobInstNum() == 0) {
        return;
    }
    bool disp = canDispText();
    if (m_disp != disp) {
        m_disp = disp;
        if (disp) {
            m_dispTime = m_bdatInfo.m_ontime;
            createMenuObj();
        } else {
            m_dispTime = 0.0f;
            disposeMenuObj();
        }
    }
}

bool GfAutoTalk::canDispText() const {
    if (!GfGameManager::isAutoTalkOK()) {
        return false;
    }
    if (m_bdatInfo.m_condition != 0 && !GfGameCond::isGameCond(m_bdatInfo.m_condition)) {
        return false;
    }
    if (!m_gmkAcc.isValid()) {
        return false;
    }
    if (m_bdatInfo.m_beforeId != 0) {
        const GfAutoTalk* before =
            GfAutoTalkManager::get()->findGfAutoTalkByBdatId(m_info.m_fp, m_bdatInfo.m_beforeId);
        if (before != nullptr && !before->isDispEnd()) {
            return false;
        }
    }
    if (!m_dist.isMatch(*m_gmkAcc.m_gmk->m_pos)) {
        return false;
    }
    gmk::GmkMob* mob = static_cast<gmk::GmkMob*>(m_gmkAcc.m_gmk);
    if (mob->getGobInstNum() == 0) {
        return false;
    }
    GfObjAcc acc(mob->getGobInst(0));
    if (acc.m_obj == nullptr) {
        return false;
    }
    if (!acc.isDisp(OBJDISP(0))) {
        return false;
    }
    if (acc.isMultiBindWaiting()) {
        return false;
    }
    GfObj* obj = acc.getObj();
    if (obj == nullptr) {
        return false;
    }
    if (GfGameManager::isGameTypeIra()) {
        GfComBehaviorMob* behavior = obj->getComponent<GfComBehaviorMob>(6);
        if (behavior != nullptr && !behavior->pad_53d9) {
            return false;
        }
    }
    return true;
}

void GfAutoTalk::createMenuObj() {
    disposeMenuObj();
    m_context = GfMenuCallContext::create();
    GfMenuObjBalloon::OpenParam param;
    param.m_bdat = m_info.m_fpMs;
    param.m_msgId = m_bdatInfo.m_text;
    param.m_object = static_cast<gmk::GmkMob*>(m_gmkAcc.m_gmk)->getGobInst(0);
    int id = mm::mtl::rttiCast<GfObjSetupMob>(GfObjManager::getObjInfo(param.m_object)->m_setup)->m_bdatId;
    if (id > 0) {
        GfMenuBdat::getMenuOffset(Bdat::getValCheckU16(GfDataBdat::getFP(0xaa), "OffsetID", id), param.m_offset);
    } else {
        param.m_offset.m_bone = nullptr;
        param.m_offset.m_offset = mm::Vec3::zero;
    }
    GfMenuObjBalloon::openAutoTalk(m_context, param);
}

void GfAutoTalkList::create(const CreateInfo& info) {
    dispose();
    m_info = info;
    unsigned char* fp = info.m_fp;
    int count = Bdat::getIdCount(fp);
    m_talks.setAllocator(fw::FrameworkMemory::getAllocator(5));
    m_talks.reserve(count);
    m_talks.resize(count);
    int top = Bdat::getIdTop(fp);
    for (int i = 0; i < count; ++i) {
        GfAutoTalk::CreateInfo talkInfo;
        talkInfo.m_fp = info.m_fp;
        talkInfo.m_fpMs = info.m_fpMs;
        talkInfo.m_id = top + i;
        m_talks[i].create(talkInfo);
    }
}

void GfAutoTalkList::dispose() {
    unsigned long count = m_talks.size();
    for (unsigned long i = 0; i < count; ++i) {
        m_talks[i].dispose();
    }
    m_talks.clear();
    m_info = CreateInfo();
}

void GfAutoTalkManager::build(const GfSetupParam& param) {
#line 483 GF_AUTO_TALK_PATH
    GfAutoTalkManager* self = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfAutoTalkManager(param);
    self->create();
}

void GfAutoTalkManager::create() {
    dispose();
    m_seq = &GfAutoTalkManager::seqInit;
}

void GfAutoTalkManager::destroy() {
    if (get() != nullptr) {
        delete get();
    }
}

void GfAutoTalkManager::update(const fw::UpdateInfo& info) {
    if (GfAutoTalkManager* self = get()) {
        self->update(info.m_deltaTime);
    }
}

void GfAutoTalkManager::seqInit(float dt) {
    if (GfFieldGimmick::isGmkSetReady()) {
        const mm::mtl::Vector<gmk::GmkSet*>& sets = gmk::GmkManager::get()->m_gmkSets;
        unsigned long count = sets.size();
        for (unsigned long i = 0; i < count; ++i) {
            createAutoTalkList(sets[i]->m_createInfo.m_bdatId);
        }
        m_seq = &GfAutoTalkManager::seqUpdate;
    }
}

bool GfAutoTalkManager::createAutoTalkList(int id) {
    disposeAutoTalkList(id);
    GfAutoTalkList::CreateInfo info;
    info.m_id = id;
    unsigned char* fp = gmk::GmkManager::get()->m_bdatFp;
    const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(fp, "autoTalk", id, 7));
    if (name == nullptr || *name == '\0') {
        return false;
    }
    info.m_fp = Bdat::getFP(name);
    if (info.m_fp == nullptr) {
        return false;
    }
    name = reinterpret_cast<const char*>(Bdat::getValCheck(fp, "autoTalk_ms", id, 7));
    if (name == nullptr || *name == '\0') {
        return false;
    }
    info.m_fpMs = Bdat::getFP(name);
    if (info.m_fpMs == nullptr) {
        return false;
    }
    if (info.m_id <= 0) {
        return false;
    }
#line 597 GF_AUTO_TALK_PATH
    GfAutoTalkList* list = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfAutoTalkList(&info);
    m_lists.push_back(list);
    return true;
}

void GfAutoTalkManager::seqUpdate(float dt) {
    for (mm::mtl::IntrusiveList<GfAutoTalkList>::iterator it = m_lists.begin(); it != m_lists.end(); ++it) {
        it->update(dt);
    }
}

GfAutoTalk::~GfAutoTalk() {
    dispose();
}

GfAutoTalkList::~GfAutoTalkList() {
    dispose();
}

}  // namespace gf
