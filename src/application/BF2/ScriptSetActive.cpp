// Script VM plugins evt_env and evt_ex (their tables, entries and Regist functions). The entries are static and nothing names
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

// evt_env.setClock
static int fn_710066100C(VMThread* pThread) {
    const char* clock = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::EnvManager>::getPtr()->setClock(clock);
    return 0;
}

// evt_env.setClockStop
static int fn_71006610A4(VMThread* pThread) {
    bool stop = vmArgBoolGet(1, vmArgPtrGet(pThread, 1)) != 0;
    mm::mtl::Singleton<event::EnvManager>::getPtr()->setClockStop(stop);
    return 0;
}

// evt_env.setWeather
static int fn_7100661140(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    float frame = vmArgOmitChk(pThread, 2) ? 0.0f : vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    mm::mtl::Singleton<event::EnvManager>::getPtr()->setMapWeatherID(gf::WEATHERID(id), frame);
    return 0;
}

// evt_env.setWeatherType
static int fn_710066121C(VMThread* pThread) {
    int type = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::EnvManager>::getPtr()->setWeatherType(gf::WEATYPE(type));
    return 0;
}

// evt_env.setColorFilter
static int fn_71006612B4(VMThread* pThread) {
    bool enable = vmArgBoolGet(1, vmArgPtrGet(pThread, 1)) != 0;
    int no = vmArgOmitChk(pThread, 2) ? 0 : vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int frame = vmArgOmitChk(pThread, 3) ? 0 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    float rate = vmArgOmitChk(pThread, 4) ? 0.0f : vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    mm::mtl::Singleton<event::EnvManager>::getPtr()->setColorFilter(event::EnvManager::COLORFILTER_TYPE(enable ? 1 : 2), no, frame, rate);
    return 0;
}

// evt_env.setMotBlur
static int fn_7100661410(VMThread* pThread) {
    bool enable = vmArgBoolGet(1, vmArgPtrGet(pThread, 1)) != 0;
    mm::mtl::Singleton<event::EnvManager>::getPtr()->setMotBlur(enable);
    return 0;
}

// evt_env.setToneMap
static int fn_71006614AC(VMThread* pThread) {
    bool enable = vmArgBoolGet(1, vmArgPtrGet(pThread, 1)) != 0;
    float value = vmArgOmitChk(pThread, 2) ? 0.23f : vmArgFixedGet(2, vmArgPtrGet(pThread, 2));
    mm::mtl::Singleton<event::EnvManager>::getPtr()->setToneMap(enable, value);
    return 0;
}

// evt_env.resetScene
static int fn_7100661590(VMThread* pThread) {
    mm::mtl::Singleton<event::EnvManager>::getPtr()->resetScene();
    return 0;
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B73368).
static VMPluginFunc s_evtenvPlugin[] = {
    {"setClock", fn_710066100C},
    {"setClockStop", fn_71006610A4},
    {"setWeather", fn_7100661140},
    {"setWeatherType", fn_710066121C},
    {"setColorFilter", fn_71006612B4},
    {"setMotBlur", fn_7100661410},
    {"setToneMap", fn_71006614AC},
    {"resetScene", fn_7100661590},
    {nullptr, nullptr},
};

void pluginEvtEnvRegist() {
    vmPluginRegist("evt_env", s_evtenvPlugin);
}


// evt_ex: a selection the script builds (begin, the set* entries) and then shows (play, getResult). Proposed names,
// not the original's: the symbols leave the file statics unnamed (lbl_7100EC1790, one merged block).
static mm::mtl::FixedVector<unsigned int, 16> s_exExp;
static mm::mtl::FixedVector<const char*, 16> s_exSelect;
static mm::mtl::FixedVector<unsigned int, 16> s_exItem;
static int s_exEther;
static const char* s_exText;
static const char* s_exCancel;

// evt_ex.begin
static int fn_7100661640(VMThread* pThread) {
    s_exText = nullptr;
    s_exEther = 0;
    s_exExp.clear();
    s_exSelect.clear();
    s_exItem.clear();
    s_exCancel = nullptr;
    return 0;
}

// evt_ex.setText
static int fn_7100661680(VMThread* pThread) {
    s_exText = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    return 0;
}

// evt_ex.setEther
static int fn_71006616B4(VMThread* pThread) {
    s_exEther = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    return 0;
}

// evt_ex.setExp
static int fn_71006616E4(VMThread* pThread) {
    unsigned int exp = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    s_exExp.push_back(exp);
    return 0;
}

// evt_ex.setSelect
static int fn_7100661764(VMThread* pThread) {
    const char* select = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    s_exSelect.push_back(select);
    return 0;
}

// evt_ex.setItem
static int fn_71006617E4(VMThread* pThread) {
    unsigned int item = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    s_exItem.push_back(item);
    return 0;
}

// evt_ex.setCancel
static int fn_7100661864(VMThread* pThread) {
    s_exCancel = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    return 0;
}

// evt_ex.play
static int fn_7100661898(VMThread* pThread) {
    if (!mm::mtl::Singleton<event::UIManager>::getPtr()->fn_7100104130(s_exText, s_exEther, s_exExp, s_exSelect,
                                                                         s_exItem, s_exCancel)) {
        vmWaitModeSet(pThread);
    }
    return 0;
}

// evt_ex.getResult
static int fn_7100661940(VMThread* pThread) {
    vmRetIntSet(pThread, mm::mtl::Singleton<event::UIManager>::getPtr()->fn_7100104AE8());
    return 1;
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B733F8).
static VMPluginFunc s_evtexPlugin[] = {
    {"begin", fn_7100661640},
    {"setText", fn_7100661680},
    {"setEther", fn_71006616B4},
    {"setExp", fn_71006616E4},
    {"setSelect", fn_7100661764},
    {"setItem", fn_71006617E4},
    {"setCancel", fn_7100661864},
    {"play", fn_7100661898},
    {"getResult", fn_7100661940},
    {nullptr, nullptr},
};

// 2.0.0's symbols name it. pluginRegist calls it.
void pluginEvtExRegist() {
    vmPluginRegist("evt_ex", s_evtexPlugin);
}
