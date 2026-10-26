// Script VM plugin evt_eff (its table, entries and Regist function). The entries are static and nothing names
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

// evt_eff.play
static int fn_710065F768(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    float a3 = vmArgOmitChk(pThread, 3) ? 0.0f : (float)vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    float a4 = vmArgOmitChk(pThread, 4) ? 1.0f : (float)vmArgIntGet(4, vmArgPtrGet(pThread, 4)) * 0.01f;
    int cast = vmArgOmitChk(pThread, 5) ? -1 : vmArgIntGet(5, vmArgPtrGet(pThread, 5));
    int mount = vmArgOmitChk(pThread, 6) ? -1 : vmArgIntGet(6, vmArgPtrGet(pThread, 6));
    int a7 = vmArgOmitChk(pThread, 7) ? 0 : vmArgIntGet(7, vmArgPtrGet(pThread, 7));
    const char* a8 = vmArgOmitChk(pThread, 8) ? "" : vmArgStringGet(8, vmArgPtrGet(pThread, 8));
    float a9 = vmArgOmitChk(pThread, 9) ? 0.0f : (float)vmArgIntGet(9, vmArgPtrGet(pThread, 9)) * 0.001f;
    float a10 = vmArgOmitChk(pThread, 10) ? 0.0f : (float)vmArgIntGet(10, vmArgPtrGet(pThread, 10)) * 0.001f;
    float a11 = vmArgOmitChk(pThread, 11) ? 0.0f : (float)vmArgIntGet(11, vmArgPtrGet(pThread, 11)) * 0.001f;
    int a12 = vmArgOmitChk(pThread, 12) ? 0 : vmArgIntGet(12, vmArgPtrGet(pThread, 12));
    int a13 = vmArgOmitChk(pThread, 13) ? 0 : vmArgIntGet(13, vmArgPtrGet(pThread, 13));
    if (mm::mtl::Singleton<event::SkipManager>::getPtr()->isSkipFast()) {
        return 0;
    }
    event::Param param;
    param.val(0).setStr(name);
    param.val(1).setF32(a2);
    param.val(2).setF32(a4);
    param.val(3).setF32(a3);
    param.val(4).setS32(a12);
    param.val(5).setS32(a13);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptEffectPlay::exec, param);
    if (cast >= 0) {
        event::ObjectChara* chara = mm::mtl::Singleton<event::ObjectManager>::getPtr()->getChara(cast);
        param.val(0).setUserdata(chara);
        mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptEffectCast::exec, param);
    } else if (mount >= 0) {
        event::ObjectChara* chara = mm::mtl::Singleton<event::ObjectManager>::getPtr()->getChara(mount);
        bool bone = chara->m_chara->m_attach->hasBone(a8);
        param.val(0).setUserdata(chara);
        param.val(1).setS32(a7);
        param.val(2).setStr(a8);
        param.val(3).setF32(a9);
        param.val(4).setF32(a10);
        param.val(5).setF32(a11);
        param.val(6).setBool(bone);
        mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptEffectMount::exec, param);
    }
    return 0;
}

// evt_eff.kill
static int fn_710065FE84(VMThread* pThread) {
    event::Param param;
    param.val(0).setBool(1);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptEffectKill::exec, param);
    return 0;
}

// evt_eff.playAnm
static int fn_710065FFA0(VMThread* pThread) {
    const char* a1 = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    event::Param param;
    param.val(0).setStr(a1);
    param.val(1).setF32(a2);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptEffectAnim::exec, param);
    return 0;
}

// evt_eff.moveTo
static int fn_7100660108(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    int a5 = vmArgOmitChk(pThread, 5) ? 0 : vmArgIntGet(5, vmArgPtrGet(pThread, 5));
    int a6 = vmArgOmitChk(pThread, 6) ? 1 : vmArgIntGet(6, vmArgPtrGet(pThread, 6));
    event::Param param;
    param.val(0).setS32(a1);
    param.val(1).setF32(a2 * 0.001f);
    param.val(2).setF32(a3 * 0.001f);
    param.val(3).setF32(a4 * 0.001f);
    param.val(4).setS32(a5);
    param.val(5).setS32(a6);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptEffectMove::exec, param);
    return 0;
}

// evt_eff.turnTo
static int fn_7100660390(VMThread* pThread) {
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
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptEffectTurn::exec, param);
    return 0;
}

// evt_eff.scale
static int fn_710066062C(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    event::Param param;
    param.val(0).setF32(a1 * 0.01f);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptEffectScale::exec, param);
    return 0;
}

// evt_eff.colorTo
static int fn_710066076C(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    int a5 = vmArgOmitChk(pThread, 5) ? 0 : vmArgIntGet(5, vmArgPtrGet(pThread, 5));
    int a6 = vmArgOmitChk(pThread, 6) ? 1 : vmArgIntGet(6, vmArgPtrGet(pThread, 6));
    event::Param param;
    param.val(0).setF32(a1 * 0.01f);
    param.val(1).setF32(a2 * 0.01f);
    param.val(2).setF32(a3 * 0.01f);
    param.val(3).setF32(a4 * 0.01f);
    param.val(4).setS32(a5);
    param.val(5).setS32(a6);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptEffectColor::exec, param);
    return 0;
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B732E8).
static VMPluginFunc s_evteffPlugin[] = {
    {"play", fn_710065F768},
    {"kill", fn_710065FE84},
    {"playAnm", fn_710065FFA0},
    {"moveTo", fn_7100660108},
    {"turnTo", fn_7100660390},
    {"scale", fn_710066062C},
    {"colorTo", fn_710066076C},
    {nullptr, nullptr},
};

void pluginEvtEffRegist() {
    vmPluginRegist("evt_eff", s_evteffPlugin);
}
