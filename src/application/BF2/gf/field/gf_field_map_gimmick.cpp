#include "classes/gf/IFieldSeq.h"
#include "classes/gf/AFieldSeq.h"
#include "classes/gf/GfFieldGrave.h"
#include "classes/gf/GfFieldGmkTutorial.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gmk/GmkGrave.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfComBehaviorGmk.h"
#include "classes/gf/GfMenuFieldSkill.h"
#include "classes/gf/GfObj.h"
#include "classes/fw/ScriptManager.h"
#include "classes/fw/ScriptInfo.h"
#include "classes/gmk/AGmkBase.h"
#include "gf/GfObjAcc.h"

namespace gf {

AFieldSeq::AFieldSeq(const GfSetupParam&)
    : m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_seq(nullptr), m_isEnd(false), m_isFsSucceeded(false) {}

void AFieldSeq::gevMapjump(GEV ev, const MapjumpCallbackInfo&) {
    if (ev == GEV(1)) {
        dispose();
    }
}

void AFieldSeq::create(GF_OBJ_HANDLE* handle) {
    dispose();
    m_handle = handle;
    m_seq = &AFieldSeq::seqCheckFs;
}

void AFieldSeq::dispose() {
    m_isEnd = false;
    m_isFsSucceeded = false;
    m_handle = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    m_seq = nullptr;
}

void AFieldSeq::update(float dt) {
    if (m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) && m_seq) {
        (this->*m_seq)(dt);
    }
}

void AFieldSeq::seqWaitUIEnd(float) {
    if (GfMenuFieldSkill::isRunning()) {
        return;
    }
    if (m_isFsSucceeded) {
        GfObjAcc acc(m_handle);
        if (acc.m_obj != nullptr) {
            if (GfComBehaviorGmk* behavior = acc.getObj()->getComponent<GfComBehaviorGmk>(6)) {
                behavior->disposeMenuObj();
            }
        }
        onFsSucceeded();
    } else {
        onFsFailed();
    }
    m_seq = nullptr;
    m_isEnd = true;
}

bool AFieldSeq::isEnd() const {
    return m_isEnd;
}

GfFieldGrave::GfFieldGrave(const GfSetupParam&) : m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_seq(nullptr) {}

void GfFieldGrave::gevMapjump(GEV ev, const MapjumpCallbackInfo&) {
    if (ev == GEV(1)) {
        dispose();
    }
}

void GfFieldGrave::create(GF_OBJ_HANDLE* handle) {
    dispose();
    m_handle = handle;
    gmk::AGmkBase* gmk = gmk::getBindedGmkInst(handle);
    GfMenuManager::fn_7100359CD8(
        51, gmk != nullptr ? static_cast<const gmk::GmkGrave::BdatInfo*>(gmk->m_bdatInfo)->m_windowArg : 0);
    m_seq = &GfFieldGrave::seqWaitToSelect;
}

void GfFieldGrave::seqWaitToSelect(float) {
    if (GfMenuManager::isOpenCommonWindow()) {
        return;
    }
    unsigned short result = GfMenuManager::getCommonWindowResult();
    if (result == 0) {
        if (gmk::AGmkBase* gmk = gmk::getBindedGmkInst(m_handle)) {
            static_cast<gmk::GmkGrave*>(gmk)->reqPopEnemy();
        } else {
            dispose();
        }
    }
    m_seq = nullptr;
    m_isEnd = true;
}

void GfFieldGrave::dispose() {
    if (GfMenuManager::isOpenCommonWindow()) {
        GfMenuManager::closeCommonWindow();
    }
    m_isEnd = false;
    m_handle = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    m_seq = nullptr;
}

void GfFieldGrave::update(float dt) {
    if (m_seq) {
        (this->*m_seq)(dt);
    }
}

void GfFieldGmkTutorial::build(const GfSetupParam&) {
#line 1437
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfFieldGmkTutorial();
}

void GfFieldGmkTutorial::destroy() {
    GfFieldGmkTutorial* tutorial = get();
    tutorial->dispose();
    delete tutorial;
}

void GfFieldGmkTutorial::dispose() {
    m_arg = 0;
    m_name.clear();
}

void GfFieldGmkTutorial::create(const char* name, unsigned int arg) {
    dispose();
    m_name = name;
    m_arg = arg;
    fw::ScriptManager::get()->loadScript(m_scriptId, name, ml::FILE_PRIO(7));
    fw::ScriptManager::get()->getScript(m_scriptId).start();
}

bool GfFieldGmkTutorial::isEnd() const {
    if (m_waitMover) {
        return true;
    }
    const fw::ScriptManager* manager = fw::ScriptManager::get();
    return manager->getScript(m_scriptId).isFinish();
}

void GfFieldGmkTutorial::gevMapjump(GEV ev, const MapjumpCallbackInfo&) {
    if (ev == GEV(1)) {
        dispose();
    }
}

bool AFieldSeq::cancel() {
    dispose();
    return true;
}

void AFieldSeq::onFsFailed() {}

}  // namespace gf
