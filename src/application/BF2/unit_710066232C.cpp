// Script VM plugins evt_rand, evt_se and evt_sel (their tables, entries and Regist functions). The entries
// are static and nothing names them: they keep placeholder fn_ names.
#include "vm/yvm2.h"
#include "classes/mm/mtl/Singleton.h"
#include "classes/event/DofManager.h"
#include "classes/event/ShakeManager.h"
#include "classes/event/FadeManager.h"
#include "classes/event/RandManager.h"
#include "classes/event/SeManager.h"
#include "classes/event/SelectManager.h"
#include "classes/event/ObjectManager.h"
#include "classes/event/ObjectChara.h"
#include "mm/Col4.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include <string.h>

// The plugins' return-value setter. Inferred: the name is not the original's (the original may have spelled it out
// in every function).
static inline void vmRetIntSet(VMThread* pThread, int value) {
    VMData ret;
    ret.type = VMDATA_INT;
    ret.v.i = value;
    vmRetValSet(pThread, &ret);
}

// evt_rand.play
static int fn_7100662B40(VMThread* pThread) {
    int no = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    if (!mm::mtl::Singleton<event::RandManager>::getPtr()->play(no)) {
        vmWaitModeSet(pThread);
    }
    return 0;
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B735D8).
static VMPluginFunc s_evtrandPlugin[] = {
    {"play", fn_7100662B40},
    {nullptr, nullptr},
};

void pluginEvtRandRegist() {
    vmPluginRegist("evt_rand", s_evtrandPlugin);
}

// evt_se.play
static int fn_7100662C04(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    const char* name = vmArgStringGet(2, vmArgPtrGet(pThread, 2));
    float p0 = vmArgOmitChk(pThread, 3) ? 0.0f : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    float p1 = vmArgOmitChk(pThread, 4) ? 0.0f : vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    float p2 = vmArgOmitChk(pThread, 5) ? 0.0f : vmArgIntGet(5, vmArgPtrGet(pThread, 5));
    float volume = vmArgOmitChk(pThread, 6) ? 1.0f : vmArgIntGet(6, vmArgPtrGet(pThread, 6)) * 0.01f;
    mm::mtl::Singleton<event::SeManager>::getPtr()->play(id, name, p0, p1, p2, volume);
    return 0;
}

// evt_se.changeVolume
static int fn_7100662DBC(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int volume = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int frame = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    mm::mtl::Singleton<event::SeManager>::getPtr()->changeVolume(id, volume * 0.01f, frame);
    return 0;
}

// evt_se.pan
static int fn_7100662EAC(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int pan = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    float frame = vmArgOmitChk(pThread, 3) ? 0.0f : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int type = vmArgOmitChk(pThread, 4) ? 1 : vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    mm::mtl::Singleton<event::SeManager>::getPtr()->pan(id, pan * 0.01f, frame, (event::CV_TYPE)type);
    return 0;
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B735F8).
static VMPluginFunc s_evtsePlugin[] = {
    {"play", fn_7100662C04},
    {"changeVolume", fn_7100662DBC},
    {"pan", fn_7100662EAC},
    {nullptr, nullptr},
};

void pluginEvtSeRegist() {
    vmPluginRegist("evt_se", s_evtsePlugin);
}

// evt_sel: a selection the script builds (begin, setText, setItem) and then shows (play, getResult). Proposed names,
// not the original's: the symbols leave the file statics unnamed (lbl_7100EC1A00, one merged block).
static mm::mtl::FixedVector<const char*, 16> s_selItem;
static int s_selType;
static const char* s_selText;

// evt_sel.begin
static int fn_7100663008(VMThread* pThread) {
    s_selType = vmArgOmitChk(pThread, 1) ? 0 : vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    s_selText = nullptr;
    s_selItem.clear();
    return 0;
}

// evt_sel.setText
static int fn_7100663070(VMThread* pThread) {
    s_selText = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    return 0;
}

// evt_sel.setItem
static int fn_71006630A4(VMThread* pThread) {
    const char* item = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    s_selItem.push_back(item);
    return 0;
}

// evt_sel.play
static int fn_7100663124(VMThread* pThread) {
    event::ObjectChara* obj =
        static_cast<event::ObjectChara*>(mm::mtl::Singleton<event::ObjectManager>::getPtr()->getActive(2));
    event::CharaObj* chara = obj != nullptr ? obj->m_chara : nullptr;
    if (!mm::mtl::Singleton<event::SelectManager>::getPtr()->play((event::SELECT_TYPE)s_selType, s_selText,
                                                                   s_selItem, chara)) {
        vmWaitModeSet(pThread);
    }
    return 0;
}

// evt_sel.getResult
static int fn_7100663254(VMThread* pThread) {
    vmRetIntSet(pThread, mm::mtl::Singleton<event::SelectManager>::getPtr()->getResult());
    return 1;
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B73638).
static VMPluginFunc s_evtselPlugin[] = {
    {"begin", fn_7100663008},
    {"setText", fn_7100663070},
    {"setItem", fn_71006630A4},
    {"play", fn_7100663124},
    {"getResult", fn_7100663254},
    {nullptr, nullptr},
};

void pluginEvtSelRegist() {
    vmPluginRegist("evt_sel", s_evtselPlugin);
}
