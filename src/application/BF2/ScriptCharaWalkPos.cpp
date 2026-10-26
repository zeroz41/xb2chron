// Script VM plugin evt_chara (its table, entries and Regist function). The entries are static and nothing names
// them: they keep placeholder fn_ names.
#include "classes/event/UIManager.h"
#include "vm/yvm2.h"
#include "btl/Utility.h"
#include "classes/ai/AiManager.h"
#include "classes/gf/GfGameParty.h"
#include "ml/MTRand.h"
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"
#include "classes/event/Manager.h"
#include "classes/event/FrameManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "classes/event/Param.h"
#include "classes/event/TodoManager.h"
#include "classes/event/BgmManager.h"
#include "classes/event/ScriptCamCut.h"
#include "classes/event/ScriptCamFollowPos.h"
#include "classes/event/ScriptCamFollowTar.h"
#include "classes/event/ScriptCamFov.h"
#include "classes/event/ScriptCamMotion.h"
#include "classes/event/ScriptCamMoveFov.h"
#include "classes/event/ScriptCamMovePos.h"
#include "classes/event/ScriptCamMoveRotZ.h"
#include "classes/event/ScriptCamMoveTar.h"
#include "classes/event/ScriptCamNearfar.h"
#include "classes/event/ScriptCamPos.h"
#include "classes/event/ScriptCamRotZ.h"
#include "classes/event/ScriptCamTar.h"
#include "classes/event/DataManager.h"
#include "classes/event/PosAxis.h"
#include "classes/event/SeamlessManager.h"
#include "classes/event/ScriptCharaAction.h"
#include "classes/event/ScriptCharaFacial.h"
#include "classes/event/ScriptCharaFade.h"
#include "classes/event/ScriptCharaHead.h"
#include "classes/event/ScriptCharaLinerPos.h"
#include "classes/event/ScriptCharaLinerRot.h"
#include "classes/event/ScriptCharaMotion.h"
#include "classes/event/ScriptCharaMotionABC.h"
#include "classes/event/ScriptCharaMount.h"
#include "classes/event/ScriptCharaSetIdle.h"
#include "classes/event/ScriptCharaTalk.h"
#include "classes/event/ScriptCharaTgt.h"
#include "classes/event/ScriptCharaTurnRot.h"
#include "classes/event/ScriptCharaWalkPos.h"
#include "classes/event/ScriptCharaWink.h"
#include "classes/event/ObjectManager.h"
#include "classes/event/ObjectChara.h"
#include "classes/event/CharaObj.h"
#include "gf/GfDataBlade.h"
#include "classes/event/ScriptUtil.h"
#include "classes/event/ObjectList.h"
#include "mm/Vec3.h"
#include "classes/event/SkipManager.h"
#include "classes/event/ScriptEffectAnim.h"
#include "classes/event/ScriptEffectCast.h"
#include "classes/event/ScriptEffectColor.h"
#include "classes/event/ScriptEffectKill.h"
#include "classes/event/ScriptEffectMount.h"
#include "classes/event/ScriptEffectMove.h"
#include "classes/event/ScriptEffectPlay.h"
#include "classes/event/ScriptEffectScale.h"
#include "classes/event/ScriptEffectTurn.h"
#include "classes/event/AttachActorBase.h"
#include "classes/event/EnvManager.h"

// The plugins' return-value setters. Inferred: the names are not the original's (the original may have spelled
// these out in every function).
static inline void vmRetIntSet(VMThread* pThread, int value) {
    VMData ret;
    ret.type = VMDATA_INT;
    ret.v.i = value;
    vmRetValSet(pThread, &ret);
}

static inline void vmRetFixedSet(VMThread* pThread, float value) {
    VMData ret;
    ret.type = VMDATA_FIXED;
    ret.v.f = value;
    vmRetValSet(pThread, &ret);
}

static inline void vmRetBoolSet(VMThread* pThread, bool value) {
    VMData ret;
    ret.type = value ? VMDATA_TRUE : VMDATA_FALSE;
    vmRetValSet(pThread, &ret);
}

// evt_chara.setPos
static int fn_710065B23C(VMThread* pThread) {
    int type = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int x = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int y = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int z = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    event::ObjectList* list = mm::mtl::Singleton<event::ObjectManager>::getPtr()->m_current;
    event::Object* obj = list != nullptr ? list->m_active : nullptr;
    if (event::ScriptUtil::getObjType(obj) == 2) {
        event::PosAxis axis(type, (float)x * 0.001f, (float)y * 0.001f, (float)z * 0.001f);
        static_cast<event::ObjectChara*>(obj)->setPosAxis(axis);
        static_cast<event::ObjectChara*>(obj)->m_chara->resetDynamics(0);
    }
    return 0;
}

// evt_chara.walkPos
static int fn_710065B3A4(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    int a5 = vmArgOmitChk(pThread, 5) ? 0 : vmArgIntGet(5, vmArgPtrGet(pThread, 5));
    bool a6 = vmArgOmitChk(pThread, 6) ? true : vmArgBoolGet(6, vmArgPtrGet(pThread, 6)) != 0;
    event::Param param;
    param.val(0).setS32(a1);
    param.val(1).setF32(a2 * 0.001f);
    param.val(2).setF32(a3 * 0.001f);
    param.val(3).setF32(a4 * 0.001f);
    param.val(4).setS32(a5);
    param.val(5).setBool(a6);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaWalkPos::exec, param);
    return 0;
}

// evt_chara.linerPos
static int fn_710065B630(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    int a5 = vmArgOmitChk(pThread, 5) ? 0 : vmArgBoolGet(5, vmArgPtrGet(pThread, 5));
    int a6 = vmArgOmitChk(pThread, 6) ? 0 : vmArgIntGet(6, vmArgPtrGet(pThread, 6));
    int a7 = vmArgOmitChk(pThread, 7) ? 1 : vmArgIntGet(7, vmArgPtrGet(pThread, 7));
    event::Param param;
    param.val(0).setS32(a1);
    param.val(1).setF32(a2 * 0.001f);
    param.val(2).setF32(a3 * 0.001f);
    param.val(3).setF32(a4 * 0.001f);
    param.val(4).setBool(a5 != 0);
    param.val(5).setS32(a6);
    param.val(6).setS32(a7);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaLinerPos::exec, param);
    return 0;
}

// evt_chara.setRot
static int fn_710065B90C(VMThread* pThread) {
    int type = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int x = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int y = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int z = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    event::ObjectList* list = mm::mtl::Singleton<event::ObjectManager>::getPtr()->m_current;
    event::Object* obj = list != nullptr ? list->m_active : nullptr;
    if (event::ScriptUtil::getObjType(obj) == 2) {
        event::RotAxis axis(type, (float)x * 0.001f * 0.017453292f, (float)y * 0.001f * 0.017453292f, (float)z * 0.001f * 0.017453292f);
        static_cast<event::ObjectChara*>(obj)->setRotAxis(axis);
        static_cast<event::ObjectChara*>(obj)->m_chara->resetDynamics(0);
    }
    return 0;
}

// evt_chara.turnRot
static int fn_710065BA88(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    int a5 = vmArgOmitChk(pThread, 5) ? 0 : vmArgIntGet(5, vmArgPtrGet(pThread, 5));
    float a6 = vmArgOmitChk(pThread, 6) ? 1.0f : vmArgIntGet(6, vmArgPtrGet(pThread, 6)) * 0.01f;
    event::Param param;
    param.val(0).setS32(a1);
    param.val(1).setF32(a2 * 0.001f * 0.017453292f);
    param.val(2).setF32(a3 * 0.001f * 0.017453292f);
    param.val(3).setF32(a4 * 0.001f * 0.017453292f);
    param.val(4).setS32(a5);
    param.val(5).setF32(a6);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaTurnRot::exec, param);
    return 0;
}

// evt_chara.linerRot
static int fn_710065BD38(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    int a5 = vmArgOmitChk(pThread, 5) ? 0 : vmArgIntGet(5, vmArgPtrGet(pThread, 5));
    int a6 = vmArgOmitChk(pThread, 6) ? 1 : vmArgIntGet(6, vmArgPtrGet(pThread, 6));
    event::Param param;
    param.val(0).setS32(a1);
    param.val(1).setF32(a2 * 0.001f * 0.017453292f);
    param.val(2).setF32(a3 * 0.001f * 0.017453292f);
    param.val(3).setF32(a4 * 0.001f * 0.017453292f);
    param.val(4).setS32(a5);
    param.val(5).setS32(a6);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaLinerRot::exec, param);
    return 0;
}

// evt_chara.setTar
static int fn_710065BFD4(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    int a5 = vmArgIntGet(5, vmArgPtrGet(pThread, 5));
    int a6 = vmArgOmitChk(pThread, 6) ? 0 : vmArgIntGet(6, vmArgPtrGet(pThread, 6));
    int a7 = vmArgOmitChk(pThread, 7) ? 0 : vmArgIntGet(7, vmArgPtrGet(pThread, 7));
    int a8 = vmArgOmitChk(pThread, 8) ? 0 : vmArgBoolGet(8, vmArgPtrGet(pThread, 8));
    float a9 = vmArgOmitChk(pThread, 9) ? -1.0f : (float)vmArgIntGet(9, vmArgPtrGet(pThread, 9));
    float a10 = vmArgOmitChk(pThread, 10) ? -1.0f : (float)vmArgIntGet(10, vmArgPtrGet(pThread, 10));
    event::Param param;
    param.val(0).setS32(a1);
    if (mm::mtl::Singleton<event::DataManager>::getPtr()->checkRadianTar(a1)) {
        param.val(1).setF32((float)a2 * 0.001f * 0.017453292f);
        param.val(2).setF32((float)a3 * 0.001f * 0.017453292f);
        param.val(3).setF32((float)a4 * 0.001f * 0.017453292f);
    } else {
        param.val(1).setF32((float)a2 * 0.001f);
        param.val(2).setF32((float)a3 * 0.001f);
        param.val(3).setF32((float)a4 * 0.001f);
    }
    param.val(4).setF32(a5);
    param.val(5).setS32(a6);
    param.val(6).setS32(a7);
    param.val(7).setF32(a8 ? a9 : -1.0f);
    param.val(8).setF32(a8 ? a10 : -1.0f);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaTgt::exec, param);
    return 0;
}

// evt_chara.setIdle
static int fn_710065C420(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    event::Param param;
    param.val(0).setS32(a1);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaSetIdle::exec, param);
    return 0;
}

// evt_chara.playAction
static int fn_710065C554(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgOmitChk(pThread, 3) ? 1 : vmArgBoolGet(3, vmArgPtrGet(pThread, 3));
    bool a4 = vmArgOmitChk(pThread, 4) ? true : vmArgBoolGet(4, vmArgPtrGet(pThread, 4)) != 0;
    event::Param param;
    param.val(0).setS32(a1);
    param.val(1).setF32(a2);
    param.val(2).setBool(a3 != 0);
    param.val(3).setBool(a4);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaAction::exec, param);
    return 0;
}

// evt_chara.playMotion
static int fn_710065C758(VMThread* pThread) {
    const char* a1 = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    float a4 = vmArgOmitChk(pThread, 4) ? 0.0f : vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    event::Param param;
    param.val(0).setStr(a1);
    param.val(1).setF32(a2);
    param.val(2).setF32(a3 * 0.01f);
    param.val(3).setF32(a4);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaMotion::exec, param);
    return 0;
}

// evt_chara.playMotionABC
static int fn_710065C954(VMThread* pThread) {
    const char* a1 = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    const char* a2 = vmArgStringGet(2, vmArgPtrGet(pThread, 2));
    const char* a3 = vmArgStringGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    int a5 = vmArgIntGet(5, vmArgPtrGet(pThread, 5));
    int a6 = vmArgIntGet(6, vmArgPtrGet(pThread, 6));
    int a7 = vmArgOmitChk(pThread, 7) ? 0 : vmArgBoolGet(7, vmArgPtrGet(pThread, 7));
    float a8 = vmArgOmitChk(pThread, 8) ? -1.0f : (float)vmArgIntGet(8, vmArgPtrGet(pThread, 8));
    float a9 = vmArgOmitChk(pThread, 9) ? -1.0f : (float)vmArgIntGet(9, vmArgPtrGet(pThread, 9));
    float a10 = vmArgOmitChk(pThread, 10) ? 0.0f : (float)vmArgIntGet(10, vmArgPtrGet(pThread, 10));
    event::Param param;
    param.val(0).setStr(a1);
    param.val(1).setStr(a2);
    param.val(2).setStr(a3);
    param.val(3).setF32(a4);
    param.val(4).setF32(a5);
    param.val(5).setF32(a6 * 0.01f);
    param.val(6).setF32(a7 ? a8 : -1.0f);
    param.val(7).setF32(a7 ? a9 : -1.0f);
    param.val(8).setF32(a10);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaMotionABC::exec, param);
    return 0;
}

// evt_chara.playHead
static int fn_710065CCCC(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgOmitChk(pThread, 3) ? 1 : vmArgBoolGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgOmitChk(pThread, 4) ? 1 : vmArgBoolGet(4, vmArgPtrGet(pThread, 4));
    int a5 = vmArgOmitChk(pThread, 5) ? 0 : vmArgBoolGet(5, vmArgPtrGet(pThread, 5));
    float a6 = vmArgOmitChk(pThread, 6) ? -1.0f : (float)vmArgIntGet(6, vmArgPtrGet(pThread, 6)) * 0.01f;
    float a7 = vmArgOmitChk(pThread, 7) ? -1.0f : (float)vmArgIntGet(7, vmArgPtrGet(pThread, 7)) * 0.01f;
    event::Param param;
    param.val(0).setS32(a1);
    param.val(1).setF32(a2);
    param.val(2).setBool(a3 != 0);
    param.val(3).setBool(a4 != 0);
    param.val(4).setF32(a5 ? a6 : -1.0f);
    param.val(5).setF32(a5 ? a7 : -1.0f);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaHead::exec, param);
    return 0;
}

// evt_chara.playFacial
static int fn_710065CFCC(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgOmitChk(pThread, 3) ? 0 : vmArgBoolGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgOmitChk(pThread, 4) ? 0 : vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    float a5 = vmArgOmitChk(pThread, 5) ? -1.0f : (float)vmArgIntGet(5, vmArgPtrGet(pThread, 5)) * 0.01f;
    int a6 = vmArgOmitChk(pThread, 6) ? 0 : vmArgBoolGet(6, vmArgPtrGet(pThread, 6));
    int a7 = vmArgOmitChk(pThread, 7) ? 0 : vmArgIntGet(7, vmArgPtrGet(pThread, 7));
    float a8 = vmArgOmitChk(pThread, 8) ? -1.0f : (float)vmArgIntGet(8, vmArgPtrGet(pThread, 8)) * 0.01f;
    int a9 = vmArgOmitChk(pThread, 9) ? 0 : vmArgBoolGet(9, vmArgPtrGet(pThread, 9));
    int a10 = vmArgOmitChk(pThread, 10) ? 0 : vmArgIntGet(10, vmArgPtrGet(pThread, 10));
    float a11 = vmArgOmitChk(pThread, 11) ? -1.0f : (float)vmArgIntGet(11, vmArgPtrGet(pThread, 11)) * 0.01f;
    int a12 = vmArgOmitChk(pThread, 12) ? 0 : vmArgBoolGet(12, vmArgPtrGet(pThread, 12));
    float a13 = vmArgOmitChk(pThread, 13) ? -1.0f : (float)vmArgIntGet(13, vmArgPtrGet(pThread, 13));
    float a14 = vmArgOmitChk(pThread, 14) ? -1.0f : (float)vmArgIntGet(14, vmArgPtrGet(pThread, 14));
    event::Param param;
    param.val(0).setS32(a1);
    param.val(1).setF32(a2);
    param.val(2).setS32(a3 ? a4 : -1);
    param.val(3).setF32(a3 ? a5 : -1.0f);
    param.val(4).setS32(a6 ? a7 : -1);
    param.val(5).setF32(a6 ? a8 : -1.0f);
    param.val(6).setS32(a9 ? a10 : -1);
    param.val(7).setF32(a9 ? a11 : -1.0f);
    param.val(8).setF32(a12 ? a13 : -1.0f);
    param.val(9).setF32(a12 ? a14 : -1.0f);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaFacial::exec, param);
    return 0;
}

// evt_chara.playTalk
static int fn_710065D4C4(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgOmitChk(pThread, 2) ? 0 : vmArgBoolGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgOmitChk(pThread, 3) ? 1 : vmArgBoolGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgOmitChk(pThread, 4) ? 1 : vmArgBoolGet(4, vmArgPtrGet(pThread, 4));
    float a5 = vmArgOmitChk(pThread, 5) ? -1.0f : (float)vmArgIntGet(5, vmArgPtrGet(pThread, 5)) * 0.01f;
    float a6 = vmArgOmitChk(pThread, 6) ? -1.0f : (float)vmArgIntGet(6, vmArgPtrGet(pThread, 6)) * 0.01f;
    int a7 = vmArgOmitChk(pThread, 7) ? 0 : vmArgBoolGet(7, vmArgPtrGet(pThread, 7));
    float a8 = vmArgOmitChk(pThread, 8) ? -1.0f : (float)vmArgIntGet(8, vmArgPtrGet(pThread, 8)) * 0.01f;
    float a9 = vmArgOmitChk(pThread, 9) ? -1.0f : (float)vmArgIntGet(9, vmArgPtrGet(pThread, 9)) * 0.01f;
    event::Param param;
    param.val(0).setF32(a1);
    param.val(1).setBool(a2 ? a3 != 0 : true);
    param.val(2).setBool(a2 ? a4 != 0 : true);
    param.val(3).setF32(a2 ? a5 : -1.0f);
    param.val(4).setF32(a2 ? a6 : -1.0f);
    param.val(5).setF32(a7 ? a8 : -1.0f);
    param.val(6).setF32(a7 ? a9 : -1.0f);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaTalk::exec, param);
    return 0;
}

// evt_chara.playWink
static int fn_710065D890(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgOmitChk(pThread, 3) ? 0 : vmArgBoolGet(3, vmArgPtrGet(pThread, 3));
    float a4 = vmArgOmitChk(pThread, 4) ? 0.0f : (float)vmArgIntGet(4, vmArgPtrGet(pThread, 4)) * 0.01f;
    float a5 = vmArgOmitChk(pThread, 5) ? 0.0f : (float)vmArgIntGet(5, vmArgPtrGet(pThread, 5)) * 0.01f;
    int a6 = vmArgOmitChk(pThread, 6) ? -1 : vmArgIntGet(6, vmArgPtrGet(pThread, 6));
    int a7 = vmArgOmitChk(pThread, 7) ? 1 : vmArgBoolGet(7, vmArgPtrGet(pThread, 7));
    bool a8 = vmArgOmitChk(pThread, 8) ? true : vmArgBoolGet(8, vmArgPtrGet(pThread, 8)) != 0;
    event::Param param;
    param.val(0).setS32(a1);
    param.val(1).setF32(a2);
    param.val(2).setBool(a3 != 0);
    param.val(3).setF32(a3 ? a4 : 0.0f);
    param.val(4).setF32(a3 ? a5 : 0.0f);
    param.val(5).setS32(a6);
    param.val(6).setBool(a7 != 0);
    param.val(7).setBool(a8);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaWink::exec, param);
    return 0;
}

// evt_chara.mount
static int fn_710065DBEC(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    const char* a2 = vmArgStringGet(2, vmArgPtrGet(pThread, 2));
    float a3 = vmArgOmitChk(pThread, 3) ? 0.0f : (float)vmArgIntGet(3, vmArgPtrGet(pThread, 3)) * 0.001f;
    float a4 = vmArgOmitChk(pThread, 4) ? 0.0f : (float)vmArgIntGet(4, vmArgPtrGet(pThread, 4)) * 0.001f;
    float a5 = vmArgOmitChk(pThread, 5) ? 0.0f : (float)vmArgIntGet(5, vmArgPtrGet(pThread, 5)) * 0.001f;
    float a6 = vmArgOmitChk(pThread, 6) ? 0.0f : (float)vmArgIntGet(6, vmArgPtrGet(pThread, 6)) * 0.001f * 0.017453292f;
    float a7 = vmArgOmitChk(pThread, 7) ? 0.0f : (float)vmArgIntGet(7, vmArgPtrGet(pThread, 7)) * 0.001f * 0.017453292f;
    float a8 = vmArgOmitChk(pThread, 8) ? 0.0f : (float)vmArgIntGet(8, vmArgPtrGet(pThread, 8)) * 0.001f * 0.017453292f;
    bool fast = mm::mtl::Singleton<event::SkipManager>::getPtr()->isSkipFast();
    if (a1 > 3 && !fast) {
        event::Param param;
        param.val(0).setS32(a1 - 4);
        param.val(1).setStr(a2);
        param.val(2).setF32(a3);
        param.val(3).setF32(a4);
        param.val(4).setF32(a5);
        param.val(5).setF32(a6);
        param.val(6).setF32(a7);
        param.val(7).setF32(a8);
        mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaMount::exec, param);
    }
    return 0;
}

// evt_chara.playFade
static int fn_710065DFE8(VMThread* pThread) {
    int a1 = vmArgBoolGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    event::Param param;
    param.val(0).setBool(a1 != 0);
    param.val(1).setF32(a2);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaFade::exec, param);
    return 0;
}

// evt_chara.playVolumeFade
static int fn_710065E154(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgOmitChk(pThread, 2) ? 1 : vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    float a3 = vmArgOmitChk(pThread, 3) ? 1.0f : vmArgFixedGet(3, vmArgPtrGet(pThread, 3));
    float a4 = vmArgOmitChk(pThread, 4) ? 1.0f : vmArgFixedGet(4, vmArgPtrGet(pThread, 4));
    float a5 = vmArgOmitChk(pThread, 5) ? 1.0f : vmArgFixedGet(5, vmArgPtrGet(pThread, 5));
    float a6 = vmArgOmitChk(pThread, 6) ? 0.0f : vmArgFixedGet(6, vmArgPtrGet(pThread, 6));
    float a7 = vmArgOmitChk(pThread, 7) ? 0.0f : vmArgFixedGet(7, vmArgPtrGet(pThread, 7));
    float a8 = vmArgOmitChk(pThread, 8) ? 0.0f : vmArgFixedGet(8, vmArgPtrGet(pThread, 8));
    float a9 = vmArgOmitChk(pThread, 9) ? 0.5f : vmArgFixedGet(9, vmArgPtrGet(pThread, 9));
    float a10 = vmArgOmitChk(pThread, 10) ? 1.0f : vmArgFixedGet(10, vmArgPtrGet(pThread, 10));
    int a11 = vmArgOmitChk(pThread, 11) ? -1 : vmArgIntGet(11, vmArgPtrGet(pThread, 11));
    float a12 = vmArgOmitChk(pThread, 12) ? 0.5f : vmArgFixedGet(12, vmArgPtrGet(pThread, 12));
    event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->searchByName(name);
    if (obj != nullptr && obj->m_type == 2) {
        static_cast<event::ObjectChara*>(obj)->m_chara->playVolumeFade(event::CharaEffectPlayer::VF_TYPE(1), a2, mm::Vec3(a3, a4, a5),
                                                                        mm::Vec3(a6, a7, a8), a9, a10, a11, a12);
    }
    return 0;
}

// evt_chara.playVolumeFadeAnim
static int fn_710065E49C(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    float time = vmArgOmitChk(pThread, 2) ? 0.5f : vmArgFixedGet(2, vmArgPtrGet(pThread, 2));
    float delay = vmArgOmitChk(pThread, 3) ? 0.0f : vmArgFixedGet(3, vmArgPtrGet(pThread, 3));
    event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->searchByName(name);
    if (obj != nullptr && obj->m_type == 2) {
        static_cast<event::ObjectChara*>(obj)->m_chara->playVolumeFadeAnim(event::CharaEffectPlayer::VF_TYPE(1), time, delay);
    }
    return 0;
}

// evt_chara.stopVolumeFade
static int fn_710065E5CC(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->searchByName(name);
    if (obj != nullptr && obj->m_type == 2) {
        static_cast<event::ObjectChara*>(obj)->m_chara->stopVolumeFade(event::CharaEffectPlayer::VF_TYPE(1));
    }
    return 0;
}

// evt_chara.playRimBloom
static int fn_710065E680(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    int type = vmArgOmitChk(pThread, 2) ? 1 : vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->searchByName(name);
    if (obj != nullptr && obj->m_type == 2) {
        static_cast<event::ObjectChara*>(obj)->m_chara->playRimBloom(type);
    }
    return 0;
}

// evt_chara.stopRimBloom
static int fn_710065E770(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->searchByName(name);
    if (obj != nullptr && obj->m_type == 2) {
        static_cast<event::ObjectChara*>(obj)->m_chara->stopRimBloom();
    }
    return 0;
}

// evt_chara.setPartsDisp
static int fn_710065E820(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    const char* part = vmArgStringGet(2, vmArgPtrGet(pThread, 2));
    int disp = vmArgBoolGet(3, vmArgPtrGet(pThread, 3));
    event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->searchByName(name);
    if (obj != nullptr && obj->m_type == 2) {
        static_cast<event::ObjectChara*>(obj)->m_chara->setExtDisp(part, disp != 0);
    }
    return 0;
}

// evt_chara.setExtParam
static int fn_710065E920(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    const char* part = vmArgStringGet(2, vmArgPtrGet(pThread, 2));
    float value = vmArgFixedGet(3, vmArgPtrGet(pThread, 3));
    event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->searchByName(name);
    if (obj != nullptr && obj->m_type == 2) {
        static_cast<event::ObjectChara*>(obj)->m_chara->setExtParam(part, value);
    }
    return 0;
}

// evt_chara.setWeaponDisp
static int fn_710065EA24(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    int disp = vmArgBoolGet(2, vmArgPtrGet(pThread, 2));
    event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->searchByName(name);
    if (obj != nullptr && obj->m_type == 2) {
        static_cast<event::ObjectChara*>(obj)->m_chara->setHideWeapon(event::WPNHIDEID(3), disp == 0, false);
        static_cast<event::ObjectChara*>(obj)->m_chara->setHideWeapon(event::WPNHIDEID(3), disp == 0, true);
    }
    return 0;
}

// evt_chara.setWeaponDispByBladeID
static int fn_710065EB28(VMThread* pThread) {
    int blade = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int disp = vmArgBoolGet(2, vmArgPtrGet(pThread, 2));
    int creator = gf::GfDataBlade::getCreator(blade);
    if (creator > 0) {
        event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->searchByID(3, creator);
        if (obj != nullptr && obj->m_type == 2) {
            static_cast<event::ObjectChara*>(obj)->m_chara->setHideWeapon(event::WPNHIDEID(3), disp == 0, false);
            static_cast<event::ObjectChara*>(obj)->m_chara->setHideWeapon(event::WPNHIDEID(3), disp == 0, true);
        }
    }
    return 0;
}

// evt_chara.setCharaDisp
static int fn_710065EC44(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    int disp = vmArgBoolGet(2, vmArgPtrGet(pThread, 2));
    event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->searchByName(name);
    if (obj != nullptr && obj->m_type == 2) {
        if (disp) {
            static_cast<event::ObjectChara*>(obj)->m_chara->playFade(false, 0.0f);
        } else {
            static_cast<event::ObjectChara*>(obj)->m_chara->playFade(true, 0.0f);
        }
    }
    return 0;
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B73128).
static VMPluginFunc s_evtcharaPlugin[] = {
    {"setPos", fn_710065B23C},
    {"walkPos", fn_710065B3A4},
    {"linerPos", fn_710065B630},
    {"setRot", fn_710065B90C},
    {"turnRot", fn_710065BA88},
    {"linerRot", fn_710065BD38},
    {"setTar", fn_710065BFD4},
    {"setIdle", fn_710065C420},
    {"playAction", fn_710065C554},
    {"playMotion", fn_710065C758},
    {"playMotionABC", fn_710065C954},
    {"playHead", fn_710065CCCC},
    {"playFacial", fn_710065CFCC},
    {"playTalk", fn_710065D4C4},
    {"playWink", fn_710065D890},
    {"mount", fn_710065DBEC},
    {"playFade", fn_710065DFE8},
    {"playVolumeFade", fn_710065E154},
    {"playVolumeFadeAnim", fn_710065E49C},
    {"stopVolumeFade", fn_710065E5CC},
    {"playRimBloom", fn_710065E680},
    {"stopRimBloom", fn_710065E770},
    {"setPartsDisp", fn_710065E820},
    {"setExtParam", fn_710065E920},
    {"setWeaponDisp", fn_710065EA24},
    {"setWeaponDispByBladeID", fn_710065EB28},
    {"setCharaDisp", fn_710065EC44},
    {nullptr, nullptr},
};

void pluginEvtCharaRegist() {
    vmPluginRegist("evt_chara", s_evtcharaPlugin);
}
