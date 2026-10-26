// Script VM plugin evt_pay (its table, entries and Regist function). The entries are static and nothing names
// them: they keep placeholder fn_ names.
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
