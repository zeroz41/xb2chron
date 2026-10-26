// Script VM plugins evt_lgt and evt_obj (their tables, entries and Regist functions). The entries are static and nothing names
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
