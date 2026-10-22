#include "gf/FileStaticVec3.h"
#include "ai/Event.h"
#include "mm/mtl/RTTI.h"
#include "ai/Fsm.h"
#include "classes/ai/TaskNode.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/pc/BlackBoardField.h"
#include "classes/gf/pc/GfPropertyField.h"
#include "classes/gf/pc/StateFieldWallAiAdsorption.h"
#include "classes/gf/pc/StateFieldWallAiPrepare.h"
#include "classes/gf/pc/StateFieldWallAiWait.h"
#include "classes/gf/pc/TaskFieldWallEscape.h"
#include "classes/gf/pc/TaskFieldWallFall.h"
#include "classes/gf/pc/TaskFieldWallFollow.h"
#include "classes/gf/pc/TaskFieldWallJumpWait.h"
#include "classes/gf/pc/TaskFieldWallPrepare.h"
#include "classes/fw/ComponentObject.h"
#include "fw/Transform.h"
#include "fw/UpdateInfo.h"
#include "gf/MsgPcFieldWallJump.h"
#include "gf/pc/AgentUtilField.h"

namespace gf { namespace pc {

void TaskFieldWallPrepare::onEvent(ai::BlackBoard& bb, const ai::Event& event) {
    BlackBoardField* pBB = mm::mtl::rttiCast<BlackBoardField>(&bb);
#line 23
    MM_ASSERT(pBB);
    switch (event.m_type) {
    case 1:
        onChangeActivate(*pBB, static_cast<const ai::ActivateEvent&>(event));
        break;
    case 2:
        onCreate(*pBB, static_cast<const ai::CreateEvent&>(event));
        break;
    case 4:
        onDestroy(*pBB, static_cast<const ai::DestroyEvent&>(event));
        break;
    }
}

inline void TaskFieldWallPrepare::onChangeActivate(BlackBoardField& bb, const ai::ActivateEvent& event) {
    if (!event.m_active) {
        m_context.m_blackBoard = &bb;
        m_fsm->setState(0);
        m_context.m_blackBoard = nullptr;
    }
}

void TaskFieldWallPrepare::onCreate(BlackBoardField& bb, const ai::CreateEvent& event) {
#line 83
    m_fsm.reset(new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ai::Fsm(getAllocator(ALLOCATOR(0))));
    m_fsm->beginSetup(&m_context, 3);
    m_fsm->registerState<StateFieldWallAiWait>(0);
    m_fsm->registerState<StateFieldWallAiPrepare>(1);
    m_fsm->registerState<StateFieldWallAiAdsorption>(2);
    m_fsm->endSetup();
    m_context.m_blackBoard = &bb;
    m_fsm->setState(0);
    m_context.m_blackBoard = nullptr;
}

void TaskFieldWallPrepare::onDestroy(BlackBoardField& bb, const ai::DestroyEvent& event) {
    m_context.m_blackBoard = &bb;
    if (m_fsm) {
        m_fsm->cleanup();
    }
    m_context.m_blackBoard = nullptr;
    m_fsm.reset();
}

inline bool TaskFieldWallPrepare::testCondition(const BlackBoardField& bb) {
    bool notice = (bb.m_flags & 0x10) != 0;
    return !(bb.m_property->m_field.m_statusFlags & 0x10) && notice;
}

inline void TaskFieldWallPrepare::update(BlackBoardField& bb) {
    m_context.m_blackBoard = &bb;
    m_fsm->update(bb.m_updateInfo);
    m_context.m_blackBoard = nullptr;
}

bool TaskFieldWallFollow::testCondition(const BlackBoardField& bb) {
    return (bb.m_property->m_field.m_statusFlags & 0x20) != 0;
}

void TaskFieldWallFollow::update(BlackBoardField& bb) {
    GfComPropertyPc* property = bb.m_property;
    fw::Transform transform;
    if (AgentUtilField::getWallFollowTransform(bb, &transform)) {
        mm::Vec2 input = AgentUtilField::calcFollowWallInput(transform.position, *property);
        if (AgentUtilField::isEnableWallMove(*property, input)) {
            property->m_inputDir.x = input.x;
            property->m_inputDir.y = input.y;
            return;
        }
    }
    if (AgentUtilField::isWallEndMove(bb)) {
        AgentUtilField::setFollowWallEndInput(bb.m_wallEndPos, *property);
    } else {
        AgentUtilField::setIdleInput(*property);
    }
}

void TaskFieldWallFall::onEvent(ai::BlackBoard& bb, const ai::Event& event) {
    BlackBoardField* pBB = mm::mtl::rttiCast<BlackBoardField>(&bb);
#line 165
    MM_ASSERT(pBB);
    switch (event.m_type) {
    case 1:
        if (!event.m_active) {
            m_time = 0.0f;
        }
        break;
    case 2:
        m_time = 0.0f;
        break;
    }
}

inline bool TaskFieldWallFall::testCondition(const BlackBoardField& bb) {
    return (bb.m_flags & 0x20) && (bb.m_property->m_field.m_statusFlags & 0x10);
}

inline void TaskFieldWallFall::update(BlackBoardField& bb) {
    m_time += bb.m_updateInfo->m_deltaTime;
    GfComPropertyPc* property = bb.m_property;
    const WallAiParam* param = AgentUtilField::getAIParamAdapter(*property, PARAM_ID_FIELD_AI(5)).get<WallAiParam>();
    if (m_time >= param->fallDelay) {
        property->m_inputFlags.m_actions |= 8;
    }
}

bool TaskFieldWallEscape::testCondition(const BlackBoardField& bb) {
    GfComPropertyPc* property = bb.m_property;
    const WallAiParam* param = AgentUtilField::getAIParamAdapter(*property, PARAM_ID_FIELD_AI(5)).get<WallAiParam>();
    if (!(property->m_field.m_statusFlags & 0x10)) {
        return false;
    }
    return AgentUtilField::calcParentPlayerPush(*property, property->m_pos, param->escapeRange, &m_push);
}

void TaskFieldWallEscape::update(BlackBoardField& bb) {
    GfComPropertyPc* property = bb.m_property;
    property->m_inputDir.y = property->m_stickFrontDir.dot(m_push) >= 0.0f ? 1.0f : -1.0f;
    property->m_inputDir.x = property->m_stickSideDir.dot(m_push) >= 0.0f ? 1.0f : -1.0f;
}

bool TaskFieldWallJumpWait::testCondition(const BlackBoardField& bb) {
    return (bb.m_flags & 0x100) != 0;
}

void TaskFieldWallJumpWait::update(BlackBoardField& bb) {
    GfComPropertyPc* property = bb.m_property;
    const GfPropertyField::WallJumpInfo* info = property->m_field.getWallJumpInfo();
    if (!AgentUtilField::existNearChimbPlayer(*property, info->m_pos) && !AgentUtilField::isWallJumpAnyPlayer()) {
        MsgPcFieldWallJump msg;
        GfObj* obj = static_cast<GfObj*>(property->m_owner);
        obj->sendMessage(obj, msg);
        if (msg.m_accepted) {
            bb.m_flags &= ~0x100;
        }
    }
}

// the wall AI states' slots: inline (their tables have no key function; TaskFieldWallPrepare's registrations make
// the states, so their tables and slots are emitted here), handing the owner and the update to the state's own
// functions in the wall states' unit
inline const char* StateFieldWallAiWait::getName() const {
    return "StateFieldWallAiWait";
}
inline void StateFieldWallAiWait::onEnter(void* owner, ai::State* prev) {}
inline void StateFieldWallAiWait::onLeave(void* owner, ai::State* next) {}
inline void StateFieldWallAiWait::onStep(void* owner, const void* arg) {
    update(static_cast<WallAiContextField*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWallAiPrepare::getName() const {
    return "StateFieldWallAiPrepare";
}
inline void StateFieldWallAiPrepare::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<WallAiContextField*>(owner), prev);
}
inline void StateFieldWallAiPrepare::onLeave(void* owner, ai::State* next) {}
inline void StateFieldWallAiPrepare::onStep(void* owner, const void* arg) {
    update(static_cast<WallAiContextField*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWallAiAdsorption::getName() const {
    return "StateFieldWallAiAdsorption";
}
inline void StateFieldWallAiAdsorption::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<WallAiContextField*>(owner), prev);
}
inline void StateFieldWallAiAdsorption::onLeave(void* owner, ai::State* next) {
    leave(static_cast<WallAiContextField*>(owner), next);
}
inline void StateFieldWallAiAdsorption::onStep(void* owner, const void* arg) {
    update(static_cast<WallAiContextField*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

mm::mtl::RTTI TaskFieldWallPrepare::m_rtti("TaskFieldWallPrepare", &ai::TaskNode::m_rtti, nullptr);
mm::mtl::RTTI TaskFieldWallFollow::m_rtti("TaskFieldWallFollow", &ai::TaskNode::m_rtti, nullptr);
mm::mtl::RTTI TaskFieldWallFall::m_rtti("TaskFieldWallFall", &ai::TaskNode::m_rtti, nullptr);
mm::mtl::RTTI TaskFieldWallEscape::m_rtti("TaskFieldWallEscape", &ai::TaskNode::m_rtti, nullptr);
mm::mtl::RTTI TaskFieldWallJumpWait::m_rtti("TaskFieldWallJumpWait", &ai::TaskNode::m_rtti, nullptr);

}}  // namespace gf::pc
