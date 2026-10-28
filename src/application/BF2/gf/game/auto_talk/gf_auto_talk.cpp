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
            createAutoTalkList(sets[i]->m_bdatId);
        }
        m_seq = &GfAutoTalkManager::seqUpdate;
    }
}

bool GfAutoTalkManager::createAutoTalkList(int id) {
    disposeAutoTalkList(id);
    GfAutoTalkList::CreateInfo info;
    info.m_id = id;
    unsigned char* fp = gmk::GmkManager::get()->m_bdat.m_bdatFp;
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
