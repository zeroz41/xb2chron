// Script VM plugins of this unit (their tables, entries and Regist functions). The entries are static and nothing
// names them: they keep placeholder fn_ names. Plugins not written yet: see the coordinator's notes.
#include "vm/yvm2.h"
#include "classes/mm/mtl/Singleton.h"
#include "classes/event/HideManager.h"
#include "classes/event/VoiceManager.h"
#include "classes/event/VolumeManager.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfFieldGmkTutorial.h"
#include "classes/gmk/GmkElevator.h"

// The plugins' return-value setters. Inferred: the names are not the original's (the original may have spelled
// these out in every function).
static inline void vmRetIntSet(VMThread* pThread, int value) {
    VMData ret;
    ret.type = VMDATA_INT;
    ret.v.i = value;
    vmRetValSet(pThread, &ret);
}

static inline void vmRetBoolSet(VMThread* pThread, bool value) {
    VMData ret;
    ret.type = value ? VMDATA_TRUE : VMDATA_FALSE;
    vmRetValSet(pThread, &ret);
}

// evt_map.setDisp
static int fn_7100667374(VMThread* pThread) {
    int disp = vmArgBoolGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::HideManager>::getPtr()->hideGroup(false);
    int group = mm::mtl::Singleton<event::HideManager>::getPtr()->getGroup();
    if (disp) {
        group &= ~0x100;
    } else {
        group |= 0x100;
    }
    mm::mtl::Singleton<event::HideManager>::getPtr()->defineGroup(event::HideManager::GRP_TYPE(group));
    mm::mtl::Singleton<event::HideManager>::getPtr()->hideGroup(true);
    return 0;
}

static VMPluginFunc s_evtmapPlugin[] = {
    {"setDisp", fn_7100667374},
    {nullptr, nullptr},
};

void pluginEvtMapRegist() {
    vmPluginRegist("evt_map", s_evtmapPlugin);
}

// evt_voice.play
static int fn_710066814C(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::VoiceManager>::getPtr()->playOneshot(name, 1.0f);
    return 0;
}

static VMPluginFunc s_evtvoicePlugin[] = {
    {"play", fn_710066814C},
    {nullptr, nullptr},
};

void pluginEvtVoiceRegist() {
    vmPluginRegist("evt_voice", s_evtvoicePlugin);
}

// evt_vol.changeBgmCategory
static int fn_71006681FC(VMThread* pThread) {
    int volume = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int frame = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    mm::mtl::Singleton<event::VolumeManager>::getPtr()->changeCategoryVolume(event::VolumeManager::CATE(0),
                                                                             volume * 0.01f, frame);
    return 0;
}

// evt_vol.changeFldCategory
static int fn_71006682D0(VMThread* pThread) {
    int volume = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int frame = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    mm::mtl::Singleton<event::VolumeManager>::getPtr()->changeCategoryVolume(event::VolumeManager::CATE(3),
                                                                             volume * 0.01f, frame);
    return 0;
}

// evt_vol.changeGmkCategory
static int fn_71006683A4(VMThread* pThread) {
    int volume = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int frame = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    mm::mtl::Singleton<event::VolumeManager>::getPtr()->changeCategoryVolume(event::VolumeManager::CATE(4),
                                                                             volume * 0.01f, frame);
    return 0;
}

// evt_vol.changeEnvCategory
static int fn_7100668478(VMThread* pThread) {
    int volume = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int frame = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    mm::mtl::Singleton<event::VolumeManager>::getPtr()->changeCategoryVolume(event::VolumeManager::CATE(5),
                                                                             volume * 0.01f, frame);
    return 0;
}

// evt_vol.changeWeaCategory
static int fn_710066854C(VMThread* pThread) {
    int volume = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int frame = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    mm::mtl::Singleton<event::VolumeManager>::getPtr()->changeCategoryVolume(event::VolumeManager::CATE(6),
                                                                             volume * 0.01f, frame);
    return 0;
}

// evt_vol.changeEvtSeCategory
static int fn_7100668620(VMThread* pThread) {
    int volume = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int frame = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    mm::mtl::Singleton<event::VolumeManager>::getPtr()->changeCategoryVolume(event::VolumeManager::CATE(9),
                                                                             volume * 0.01f, frame);
    return 0;
}

// evt_vol.changeEvtCsCategory
static int fn_71006686F4(VMThread* pThread) {
    int volume = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int frame = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    mm::mtl::Singleton<event::VolumeManager>::getPtr()->changeCategoryVolume(event::VolumeManager::CATE(7),
                                                                             volume * 0.01f, frame);
    return 0;
}

// evt_vol.resetBgmCategory
static int fn_71006687C8(VMThread* pThread) {
    int frame = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::VolumeManager>::getPtr()->resetCategoryVolume(event::VolumeManager::CATE(0), frame);
    return 0;
}

// evt_vol.resetFldCategory
static int fn_7100668864(VMThread* pThread) {
    int frame = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::VolumeManager>::getPtr()->resetCategoryVolume(event::VolumeManager::CATE(3), frame);
    return 0;
}

// evt_vol.resetGmkCategory
static int fn_7100668900(VMThread* pThread) {
    int frame = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::VolumeManager>::getPtr()->resetCategoryVolume(event::VolumeManager::CATE(4), frame);
    return 0;
}

// evt_vol.resetEnvCategory
static int fn_710066899C(VMThread* pThread) {
    int frame = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::VolumeManager>::getPtr()->resetCategoryVolume(event::VolumeManager::CATE(5), frame);
    return 0;
}

// evt_vol.resetWeaCategory
static int fn_7100668A38(VMThread* pThread) {
    int frame = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::VolumeManager>::getPtr()->resetCategoryVolume(event::VolumeManager::CATE(6), frame);
    return 0;
}

// evt_vol.resetEvtSeCategory
static int fn_7100668AD4(VMThread* pThread) {
    int frame = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::VolumeManager>::getPtr()->resetCategoryVolume(event::VolumeManager::CATE(9), frame);
    return 0;
}

// evt_vol.resetEvtCsCategory
static int fn_7100668B70(VMThread* pThread) {
    int frame = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::VolumeManager>::getPtr()->resetCategoryVolume(event::VolumeManager::CATE(7), frame);
    return 0;
}

static VMPluginFunc s_evtvolPlugin[] = {
    {"changeBgmCategory", fn_71006681FC},
    {"changeFldCategory", fn_71006682D0},
    {"changeGmkCategory", fn_71006683A4},
    {"changeEnvCategory", fn_7100668478},
    {"changeWeaCategory", fn_710066854C},
    {"changeEvtSeCategory", fn_7100668620},
    {"changeEvtCsCategory", fn_71006686F4},
    {"resetBgmCategory", fn_71006687C8},
    {"resetFldCategory", fn_7100668864},
    {"resetGmkCategory", fn_7100668900},
    {"resetEnvCategory", fn_710066899C},
    {"resetWeaCategory", fn_7100668A38},
    {"resetEvtSeCategory", fn_7100668AD4},
    {"resetEvtCsCategory", fn_7100668B70},
    {nullptr, nullptr},
};

void pluginEvtVolRegist() {
    vmPluginRegist("evt_vol", s_evtvolPlugin);
}

// gmk.getStartId
static int fn_710066978C(VMThread* pThread) {
    vmRetIntSet(pThread, mm::mtl::PtrSingleton<gf::GfFieldGmkTutorial>::sys()->m_arg);
    return 1;
}

// gmk.openPortal
static int fn_71006697CC(VMThread* pThread) {
    gf::GfEvent::fn_7100328774();
    if (!gmk::GmkElevator::fn_71005B928C()) {
        vmWaitModeSet(pThread);
    }
    return 0;
}

static VMPluginFunc s_gmkPlugin[] = {
    {"getStartId", fn_710066978C},
    {"openPortal", fn_71006697CC},
    {nullptr, nullptr},
};

void pluginGmkRegist() {
    vmPluginRegist("gmk", s_gmkPlugin);
}

// wait.frame
static int fn_710066AB18(VMThread* pThread) {
    int frame = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int idx = vmWkIdxGet(pThread);
    // the frames left, in the VM's 20.12 fixed point
    int* pRest = reinterpret_cast<int*>(vmWkGet(pThread, 0));
    if (idx == 0) {
        *pRest = frame << 12;
        vmWkIdxSet(pThread, 1);
    } else {
        int rest = *pRest;
        *pRest = rest - 0x1000;
        if (rest <= 0x1000) {
            return 0;
        }
    }
    vmWaitModeSet(pThread);
    return 0;
}

static VMPluginFunc s_waitPlugin[] = {
    {"frame", fn_710066AB18},
    {nullptr, nullptr},
};

void pluginWaitRegist() {
    vmPluginRegist("wait", s_waitPlugin);
}
