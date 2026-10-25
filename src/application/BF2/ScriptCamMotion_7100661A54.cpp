// Script VM plugins evt_lgt, evt_obj and evt_pay (their tables, entries and Regist functions). The entries are
// static and nothing names them: they keep placeholder fn_ names.
#include "vm/yvm2.h"
#include "classes/mm/mtl/Singleton.h"
#include "classes/event/Manager.h"
#include "classes/event/ObjectManager.h"
#include "classes/event/ObjectList.h"
#include "classes/event/ObjectLight.h"
#include "classes/event/PosAxis.h"
#include "classes/event/RotAxis.h"
#include "classes/event/Param.h"
#include "classes/event/TodoManager.h"
#include "classes/event/ScriptSetActive.h"
#include "classes/event/UIManager.h"
#include "mm/mtl/FixedVector.h"

// The plugins' return-value setter. Inferred: the name is not the original's (the original may have spelled it out
// in every function).
static inline void vmRetIntSet(VMThread* pThread, int value) {
    VMData ret;
    ret.type = VMDATA_INT;
    ret.v.i = value;
    vmRetValSet(pThread, &ret);
}

// evt_pay: a payoff the script builds (begin, the set* entries) and then shows (play, getResult). Proposed names,
// not the original's: the symbols leave the file statics unnamed (lbl_7100EC18C0, one merged block).
static mm::mtl::FixedVector<unsigned int, 16> s_payMoney;
static mm::mtl::FixedVector<const char*, 16> s_paySelect;
static const char* s_payText;
static const char* s_payCancel;

// evt_lgt.playMotion
static int fn_7100661A68(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    int frame = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->m_current->m_active;
    if (obj->m_type == 5) {
        static_cast<event::ObjectLight*>(obj)->play(name, frame);
    }
    return 0;
}

// evt_lgt.setPos
static int fn_7100661B40(VMThread* pThread) {
    int type = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int x = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int y = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int z = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->m_current->m_active;
    if (obj->m_type == 5) {
        event::PosAxis axis(type, (float)x * 0.001f, (float)y * 0.001f, (float)z * 0.001f);
        static_cast<event::ObjectLight*>(obj)->setPosAxis(axis);
    }
    return 0;
}

// evt_lgt.setRot
static int fn_7100661C8C(VMThread* pThread) {
    int type = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int x = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int y = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int z = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->m_current->m_active;
    if (obj->m_type == 5) {
        event::RotAxis axis(type, (float)x * 0.001f * 0.017453292f, (float)y * 0.001f * 0.017453292f,
                            (float)z * 0.001f * 0.017453292f);
        static_cast<event::ObjectLight*>(obj)->setRotAxis(axis);
    }
    return 0;
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B73498).
static VMPluginFunc s_evtlgtPlugin[] = {
    {"playMotion", fn_7100661A68},
    {"setPos", fn_7100661B40},
    {"setRot", fn_7100661C8C},
    {nullptr, nullptr},
};

void pluginEvtLgtRegist() {
    vmPluginRegist("evt_lgt", s_evtlgtPlugin);
}

// evt_obj.select
static int fn_7100661E00(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    if (mm::mtl::PtrSingleton<event::Manager>::sys()->checkLanguageMode()) {
        event::Param param;
        param.val(0).setStr(name);
        mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptSetActive::exec, param);
    }
    return 0;
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B734D8).
static VMPluginFunc s_evtobjPlugin[] = {
    {"select", fn_7100661E00},
    {nullptr, nullptr},
};

void pluginEvtObjRegist() {
    vmPluginRegist("evt_obj", s_evtobjPlugin);
}

// evt_pay.begin
static int fn_7100662004(VMThread* pThread) {
    s_payText = nullptr;
    s_payMoney.clear();
    s_paySelect.clear();
    s_payCancel = nullptr;
    return 0;
}

// evt_pay.setText
static int fn_7100662034(VMThread* pThread) {
    s_payText = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    return 0;
}

// evt_pay.setMoney
static int fn_7100662064(VMThread* pThread) {
    unsigned int money = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    s_payMoney.push_back(money);
    return 0;
}

// evt_pay.setSelect
static int fn_71006620E4(VMThread* pThread) {
    const char* select = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    s_paySelect.push_back(select);
    return 0;
}

// evt_pay.setCancel
static int fn_7100662164(VMThread* pThread) {
    s_payCancel = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    return 0;
}

// evt_pay.play
static int fn_7100662198(VMThread* pThread) {
    if (!mm::mtl::Singleton<event::UIManager>::getPtr()->openPayoffUI(s_payText, s_payMoney, s_paySelect,
                                                                       s_payCancel)) {
        vmWaitModeSet(pThread);
    }
    return 0;
}

// evt_pay.getResult
static int fn_7100662238(VMThread* pThread) {
    vmRetIntSet(pThread, mm::mtl::Singleton<event::UIManager>::getPtr()->getPayoffUI());
    return 1;
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B734F8).
static VMPluginFunc s_evtpayPlugin[] = {
    {"begin", fn_7100662004},
    {"setText", fn_7100662034},
    {"setMoney", fn_7100662064},
    {"setSelect", fn_71006620E4},
    {"setCancel", fn_7100662164},
    {"play", fn_7100662198},
    {"getResult", fn_7100662238},
    {nullptr, nullptr},
};

void pluginEvtPayRegist() {
    vmPluginRegist("evt_pay", s_evtpayPlugin);
}
