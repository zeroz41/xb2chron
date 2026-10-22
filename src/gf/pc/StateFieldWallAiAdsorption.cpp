#include "classes/ai/State.h"
#include "classes/gf/pc/BlackBoardField.h"
#include "gf/pc/StateUtilField.h"
#include "classes/gf/pc/StateFieldWallAiWait.h"
#include "classes/gf/pc/StateFieldWallAiPrepare.h"
#include "classes/gf/pc/StateFieldWallAiAdsorption.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/navi/NvmshAcObj.h"
#include "gf/pc/AgentUtilField.h"

namespace gf { namespace pc {

void StateFieldWallAiWait::update(WallAiContextField* context, const fw::UpdateInfo& info) {
    BlackBoardField* blackBoard = context->m_blackBoard;
    GfComPropertyPc* property = blackBoard->m_property;
    mm::Vec3 pos = StateUtilField::calcWallPreparePosition(*property, blackBoard->m_wallPos, blackBoard->m_wallPlane);
    if (StateUtilField::isEnableWallAdsorptionStart(*property, blackBoard->m_wallPos, pos)) {
        requestState(2);
    } else if (StateUtilField::isEnableWallPrepare(*property)) {
        requestState(1);
    } else {
        AgentUtilField::setIdleInput(*property);
    }
}

void StateFieldWallAiPrepare::enter(WallAiContextField* context, ai::State* prev) {
    BlackBoardField* blackBoard = context->m_blackBoard;
    GfComPropertyPc* property = blackBoard->m_property;
    navi::NvmshAcObj* nvmshAcObj = blackBoard->m_nvmshAcObj;
    nvmshAcObj->setBeginPos(property->m_pos);
    mm::Vec3 pos = StateUtilField::calcWallPreparePosition(*property, blackBoard->m_wallPos, blackBoard->m_wallPlane);
    nvmshAcObj->setEndPos(pos);
}

void StateFieldWallAiPrepare::update(WallAiContextField* context, const fw::UpdateInfo& info) {
    BlackBoardField* blackBoard = context->m_blackBoard;
    GfComPropertyPc* property = blackBoard->m_property;
    mm::Vec3 pos = StateUtilField::calcWallPreparePosition(*property, blackBoard->m_wallPos, blackBoard->m_wallPlane);
    if (StateUtilField::isEnableWallAdsorptionStart(*property, blackBoard->m_wallPos, pos)) {
        requestState(2);
        return;
    }
    if (StateUtilField::isWallPreparePosition(*property, pos)) {
        AgentUtilField::setIdleInput(*property);
    } else {
        mm::Vec3 diff = pos - property->m_pos;
        navi::NvmshAcObj* nvmshAcObj = blackBoard->m_nvmshAcObj;
        float distance = mm::Vec3(diff.x, 0.0f, diff.z).length();
        AgentUtilField::setFollowInput(distance, nvmshAcObj, *property);
    }
    enter(context, nullptr);
}

void StateFieldWallAiAdsorption::enter(WallAiContextField* context, ai::State* prev) {
    BlackBoardField* blackBoard = context->m_blackBoard;
    navi::NvmshAcObj* nvmshAcObj = blackBoard->m_nvmshAcObj;
    const mm::Vec3& pos = blackBoard->m_property->m_pos;
    nvmshAcObj->setBeginPos(pos);
    nvmshAcObj->setEndPos(blackBoard->m_wallPos);
    context->m_blackBoard->m_property->m_field.m_statusFlags |= 8;
}

void StateFieldWallAiAdsorption::leave(WallAiContextField* context, ai::State* next) {
    context->m_blackBoard->m_property->m_field.m_statusFlags &= ~8;
}

void StateFieldWallAiAdsorption::update(WallAiContextField* context, const fw::UpdateInfo& info) {
    BlackBoardField* blackBoard = context->m_blackBoard;
    GfComPropertyPc* property = blackBoard->m_property;
    navi::NvmshAcObj* nvmshAcObj = blackBoard->m_nvmshAcObj;
    mm::Vec3 diff = blackBoard->m_wallPos - property->m_pos;
    float distance = mm::Vec3(diff.x, 0.0f, diff.z).length();
    AgentUtilField::setFollowInput(distance, nvmshAcObj, *property);
    blackBoard = context->m_blackBoard;
    nvmshAcObj = blackBoard->m_nvmshAcObj;
    const mm::Vec3& pos = blackBoard->m_property->m_pos;
    nvmshAcObj->setBeginPos(pos);
    nvmshAcObj->setEndPos(blackBoard->m_wallPos);
}

}}  // namespace gf::pc
