#include "classes/gf/GfMenuFieldSkill.h"
#include "classes/gf/GfMenuFieldSkill/StateIdle.h"
#include "classes/gf/GfMenuFieldSkill/StateStart.h"
#include "classes/gf/GfMenuFieldSkill/StateDispInfo.h"
#include "classes/gf/GfMenuFieldSkill/StateDispTotal.h"
#include "classes/gf/GfMenuFieldSkill/StateDispResult.h"
#include "classes/gf/GfMenuFieldSkill/StateWait.h"
#include "classes/gf/GfMenuFieldSkill/StateTotalNext.h"
#include "classes/gf/GfMenuFieldSkill/StateSkip.h"
#include "classes/gf/GfMenuFieldSkill/StateQuit.h"
#include "classes/gf/GfMenuObjFieldSkill.h"
#include "classes/gf/GfMenuReference.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuFieldSkill.h"
#include "classes/gf/GfMenuFieldSkill/StateIdle.h"
#include "classes/gf/GfMenuFieldSkill/StateStart.h"
#include "classes/gf/GfMenuFieldSkill/StateDispInfo.h"
#include "classes/gf/GfMenuFieldSkill/StateDispTotal.h"
#include "classes/gf/GfMenuFieldSkill/StateDispResult.h"
#include "classes/gf/GfMenuFieldSkill/StateWait.h"
#include "classes/gf/GfMenuFieldSkill/StateTotalNext.h"
#include "classes/gf/GfMenuFieldSkill/StateSkip.h"
#include "classes/gf/GfMenuFieldSkill/StateQuit.h"
#include "classes/gf/GfMenuObjFieldSkill.h"
#include "classes/gf/GfMenuReference.h"
#include "fw/UpdateInfo.h"
#include "gf/GfMenuObjUtil.h"

namespace gf {

namespace {
// drops a context the menu holds (the helper is not the original's: every holder releases its own the same way)
inline void releaseContext(GfMenuCallContext*& context) {
    if (context != nullptr) {
        context->release();
        context = nullptr;
    }
}
}  // namespace

GfMenuFieldSkill::~GfMenuFieldSkill() {
    releaseContext(m_context);
}

void GfMenuFieldSkill::build(const GfSetupParam& param) {
#line 70
    GfMenuFieldSkill* menu = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuFieldSkill();
    menu->m_fsm.beginSetup(menu, 9);
    menu->m_fsm.registerState<StateIdle>(0);
    menu->m_fsm.registerState<StateStart>(1);
    menu->m_fsm.registerState<StateDispInfo>(2);
    menu->m_fsm.registerState<StateDispTotal>(3);
    menu->m_fsm.registerState<StateDispResult>(6);
    menu->m_fsm.registerState<StateWait>(4);
    menu->m_fsm.registerState<StateTotalNext>(5);
    menu->m_fsm.registerState<StateSkip>(7);
    menu->m_fsm.registerState<StateQuit>(8);
    menu->m_fsm.endSetup();
    menu->m_fsm.setState(0);
}

void GfMenuFieldSkill::destroy() {
    GfMenuFieldSkill* menu = get();
    menu->m_fsm.cleanup();
    releaseContext(menu->m_resultContext);
    releaseContext(menu->m_totalContext);
    // the original never advances the iterator: it releases the first context until the vector is empty
    for (Info* info = menu->m_infos.begin(); info != menu->m_infos.end();) {
        releaseContext(info->m_context);
    }
    menu->m_infos.clear();
    delete menu;
}

bool GfMenuFieldSkill::isInitialized() {
    return true;
}

void GfMenuFieldSkill::postUpdate(const fw::UpdateInfo& info) {
    GfMenuFieldSkill* menu = get();
    if (menu == nullptr) {
        return;
    }
    if (menu->m_context != nullptr && menu->m_context->isActive()) {
        GfMenuCallContext::GfMenuResult result;
        if (menu->m_context->m_results.size() != 0) {
            menu->m_context->popResult(result);
            if (result.m_id == 2) {
                menu->m_skipped = true;
            }
        }
    }
    menu->m_fsm.update(&info);
}

bool GfMenuFieldSkill::start(const StartParam& param) {
    GfMenuFieldSkill* menu = get();
    if (menu == nullptr) {
        return false;
    }
    if (isRunning()) {
        return false;
    }
    if (param.m_type == 0 && param.m_skills.size() == 0) {
        return false;
    }
    menu->m_param = param;
    menu->m_skipped = false;
    menu->m_fsm.setState(1);
    GfMenuReference::setReferenceBladeID(5, 0);
    return true;
}

bool GfMenuFieldSkill::isRunning() {
    GfMenuFieldSkill* menu = get();
    if (menu != nullptr) {
        return menu->m_fsm.m_pState->m_stateID != 0;
    }
    return false;
}

// StateIdle: no menu
inline const char* GfMenuFieldSkill::StateIdle::getName() const {
    return "StateIdle";
}
inline void GfMenuFieldSkill::StateIdle::onEnter(void* owner, ai::State* prev) {}
inline void GfMenuFieldSkill::StateIdle::onLeave(void* owner, ai::State* next) {}
inline void GfMenuFieldSkill::StateIdle::onStep(void* owner, const void* arg) {}

// StateStart: attaches the skip input, then shows the skills one by one (type 0) or their total (type 1)
inline const char* GfMenuFieldSkill::StateStart::getName() const {
    return "StateStart";
}
inline void GfMenuFieldSkill::StateStart::onEnter(void* owner, ai::State* prev) {
    GfMenuFieldSkill* menu = static_cast<GfMenuFieldSkill*>(owner);
    menu->m_context->reset();
    GfMenuObjFieldSkill::attachSkip(menu->m_context);
    menu->m_levelIndex = 0;
}
inline void GfMenuFieldSkill::StateStart::onLeave(void* owner, ai::State* next) {}
inline void GfMenuFieldSkill::StateStart::onStep(void* owner, const void* arg) {
    GfMenuFieldSkill* menu = static_cast<GfMenuFieldSkill*>(owner);
    switch (menu->m_param.m_type) {
    case 0:
        requestState(2);
        break;
    case 1:
        requestState(3);
        break;
    }
}

inline const char* GfMenuFieldSkill::StateDispInfo::getName() const {
    return "StateDispInfo";
}
inline void GfMenuFieldSkill::StateDispInfo::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfMenuFieldSkill*>(owner), prev);
}
inline void GfMenuFieldSkill::StateDispInfo::onLeave(void* owner, ai::State* next) {}
inline void GfMenuFieldSkill::StateDispInfo::onStep(void* owner, const void* arg) {
    update(static_cast<GfMenuFieldSkill*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* GfMenuFieldSkill::StateDispTotal::getName() const {
    return "StateDispTotal";
}
inline void GfMenuFieldSkill::StateDispTotal::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfMenuFieldSkill*>(owner), prev);
}
inline void GfMenuFieldSkill::StateDispTotal::onLeave(void* owner, ai::State* next) {}
inline void GfMenuFieldSkill::StateDispTotal::onStep(void* owner, const void* arg) {
    update(static_cast<GfMenuFieldSkill*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}
void GfMenuFieldSkill::StateDispTotal::enter(GfMenuFieldSkill* menu, ai::State* prev) {
    menu->m_totalContext = GfMenuCallContext::create();
    GfMenuObjFieldSkill::OpenTotalParam param;
    if (menu->m_param.m_unk100 != 0 && menu->m_param.m_unk108 != 0) {
        param.m_unk0 = menu->m_param.m_unk100;
        param.m_unk8 = menu->m_param.m_unk108;
    }
    param.m_noSkills = menu->m_param.m_skills.size() == 0;
    for (const SkillLevel* level = menu->m_param.m_levels.begin(); level != menu->m_param.m_levels.end(); ++level) {
        param.m_levels.push_back(SkillLevel(level->m_skill, level->m_level));
    }
    GfMenuObjFieldSkill::openTotalInfo(menu->m_totalContext, param);
}
void GfMenuFieldSkill::StateDispTotal::update(GfMenuFieldSkill* menu, const fw::UpdateInfo& info) {
    if (menu->m_totalContext == nullptr) {
        requestState(2);
        return;
    }
    if (menu->m_totalContext->m_results.size() == 0) {
        return;
    }
    GfMenuCallContext::GfMenuResult result;
    menu->m_totalContext->popResult(result);
    if (result.m_id != 1) {
        return;
    }
    if (menu->m_param.m_skills.size() != 0) {
        GfMenuObjFieldSkill::setSkipInput(menu->m_context, true);
        requestState(2);
    } else {
        requestState(6);
    }
}

inline const char* GfMenuFieldSkill::StateDispResult::getName() const {
    return "StateDispResult";
}
inline void GfMenuFieldSkill::StateDispResult::onEnter(void* owner, ai::State* prev) {
    GfMenuFieldSkill* menu = static_cast<GfMenuFieldSkill*>(owner);
    menu->m_resultContext = GfMenuCallContext::create();
    GfMenuObjFieldSkill::OpenResultParam param;
    switch (menu->m_param.m_unk130) {
    case 0:
        param.m_unk0 = false;
        param.m_unk8 = menu->m_param.m_unk100;
        param.m_unk10 = menu->m_param.m_unk108;
        break;
    case 1:
        param.m_unk0 = true;
        break;
    }
    param.m_unk14 = menu->m_param.m_unk11C;
    GfMenuObjFieldSkill::openResult(menu->m_resultContext, param);
    m_closed = false;
    m_time = 0.0f;
}
inline void GfMenuFieldSkill::StateDispResult::onLeave(void* owner, ai::State* next) {
    GfMenuFieldSkill* menu = static_cast<GfMenuFieldSkill*>(owner);
    releaseContext(menu->m_totalContext);
    releaseContext(menu->m_resultContext);
}
inline void GfMenuFieldSkill::StateDispResult::onStep(void* owner, const void* arg) {
    update(static_cast<GfMenuFieldSkill*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}
inline void GfMenuFieldSkill::StateDispResult::update(GfMenuFieldSkill* menu, const fw::UpdateInfo& info) {
    if (!m_closed) {
        m_time = info.m_deltaTime + m_time;
        if (m_time > 2.0f) {
            GfMenuObjFieldSkill::closeResult(menu->m_resultContext);
            if (menu->m_totalContext != nullptr) {
                GfMenuObjFieldSkill::closeTotalInfo(menu->m_totalContext);
            }
            if (menu->m_param.m_unk130 == 1) {
                GfMenuObjFieldSkill::undoTotalSkillLevel(1);
                GfMenuObjFieldSkill::undoTotalSkillLevel(2);
            }
            m_closed = true;
        }
    } else if (menu->m_resultContext->isTerm()) {
        releaseContext(menu->m_resultContext);
        requestState(8);
    }
}

// StateWait: waits m_waitFrames frames (less when skipped), then changes to m_nextState
inline const char* GfMenuFieldSkill::StateWait::getName() const {
    return "StateWait";
}
inline void GfMenuFieldSkill::StateWait::onEnter(void* owner, ai::State* prev) {}
inline void GfMenuFieldSkill::StateWait::onLeave(void* owner, ai::State* next) {
    static_cast<GfMenuFieldSkill*>(owner)->m_waitFrames = 0;
}
inline void GfMenuFieldSkill::StateWait::onStep(void* owner, const void* arg) {
    GfMenuFieldSkill* menu = static_cast<GfMenuFieldSkill*>(owner);
    unsigned int frames = menu->m_waitFrames;
    unsigned int next = menu->m_nextState;
    if (frames != 0 && (menu->m_waitFrames = frames - 1) != 0 && !menu->m_skipped) {
        return;
    }
    if (menu->m_skipped && next != 5) {
        requestState(7);
    } else {
        requestState(next);
    }
}

// StateTotalNext: the next skill of the total, after a wait, or the result
inline const char* GfMenuFieldSkill::StateTotalNext::getName() const {
    return "StateTotalNext";
}
inline void GfMenuFieldSkill::StateTotalNext::onEnter(void* owner, ai::State* prev) {}
inline void GfMenuFieldSkill::StateTotalNext::onLeave(void* owner, ai::State* next) {}
inline void GfMenuFieldSkill::StateTotalNext::onStep(void* owner, const void* arg) {
    GfMenuFieldSkill* menu = static_cast<GfMenuFieldSkill*>(owner);
    if (menu->m_param.m_skills.size() == 0 || menu->m_levelIndex >= 2) {
        requestState(6);
    } else {
        menu->m_waitFrames = GfMenuObjUtil::getParamMenu()->m_totalWait * 30.0f;
        menu->m_nextState = 2;
        requestState(4);
    }
}

inline const char* GfMenuFieldSkill::StateSkip::getName() const {
    return "StateSkip";
}
inline void GfMenuFieldSkill::StateSkip::onEnter(void* owner, ai::State* prev) {
    m_step = 0;
}
inline void GfMenuFieldSkill::StateSkip::onLeave(void* owner, ai::State* next) {}
inline void GfMenuFieldSkill::StateSkip::onStep(void* owner, const void* arg) {
    update(static_cast<GfMenuFieldSkill*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}
// StateQuit: closes the menu, then goes idle once the close is done
inline const char* GfMenuFieldSkill::StateQuit::getName() const {
    return "StateQuit";
}
inline void GfMenuFieldSkill::StateQuit::onEnter(void* owner, ai::State* prev) {
    GfMenuFieldSkill* menu = static_cast<GfMenuFieldSkill*>(owner);
    menu->m_resultContext = GfMenuCallContext::create();
    GfMenuObjFieldSkill::close(menu->m_resultContext);
}
inline void GfMenuFieldSkill::StateQuit::onLeave(void* owner, ai::State* next) {
    releaseContext(static_cast<GfMenuFieldSkill*>(owner)->m_resultContext);
}
inline void GfMenuFieldSkill::StateQuit::onStep(void* owner, const void* arg) {
    GfMenuFieldSkill* menu = static_cast<GfMenuFieldSkill*>(owner);
    if (menu->m_resultContext == nullptr || menu->m_resultContext->isTerm()) {
        requestState(0);
    }
}

}  // namespace gf
