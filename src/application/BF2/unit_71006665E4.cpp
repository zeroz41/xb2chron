// Script VM plugins of this unit (their tables, entries and Regist functions). The entries are static and nothing
// names them: they keep placeholder fn_ names. Not written yet: pt.setDriverEnable (declared only).
// The thread class's methods (0x710066AC34-0x710066AD8C) are this file's (ocThreadRegist's class table points at
// them), though the split hands their addresses to ui_animation_manager.cpp.
#include "vm/yvm2.h"
#include "classes/mm/mtl/Singleton.h"
#include "classes/event/CamManager.h"
#include "classes/event/CharaManager.h"
#include "classes/event/DataManager.h"
#include "classes/event/DebugManager.h"
#include "classes/event/EffectManager.h"
#include "classes/event/Extend.h"
#include "classes/event/FrameManager.h"
#include "classes/event/HideManager.h"
#include "classes/event/LightManager.h"
#include "classes/event/Manager.h"
#include "classes/event/MovieManager.h"
#include "classes/event/ObjectManager.h"
#include "classes/event/ObjectPartyList.h"
#include "classes/event/Param.h"
#include "classes/event/PosAxis.h"
#include "classes/event/ResManager.h"
#include "classes/event/ScriptPlayText.h"
#include "classes/event/SeManager.h"
#include "classes/event/SeamlessManager.h"
#include "classes/event/SkipManager.h"
#include "classes/event/StatusManager.h"
#include "classes/event/TodoManager.h"
#include "classes/event/UIManager.h"
#include "classes/event/VoiceManager.h"
#include "classes/event/VolumeManager.h"
#include "classes/gf/GfBdatChrDr.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfFieldGmkTutorial.h"
#include "classes/gf/GfFieldTime.h"
#include "classes/gf/GfFieldWeather.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfGameEvent.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameMercenaries.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfManager.h"
#include "classes/gf/GfMenuFade.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjBladeCreate.h"
#include "classes/gf/GfMenuObjEnvironmentInfo.h"
#include "classes/gf/GfMenuObjMinimap2.h"
#include "classes/gf/GfMenuObjPartyForm3.h"
#include "classes/gf/GfMenuObjPopup.h"
#include "classes/gf/GfMenuObjQuestLog.h"
#include "classes/gf/GfMenuObjTutorial.h"
#include "classes/gf/GfQuestManager.h"
#include "classes/gf/GfSequentialPlay.h"
#include "classes/gf/GfWeapon.h"
#include "classes/gf/SCOM_ADD_MONEY.h"
#include "classes/gf/SCOM_CURRENT_BLADE.h"
#include "classes/gf/SCOM_PARTY_ADD.h"
#include "classes/gf/SCOM_SET_FLAG.h"
#include "classes/gf/SCOM_SOLO_REX.h"
#include "classes/gf/ScriptCamera.h"
#include "classes/gf/ShipRollPlugin.h"
#include "classes/gmk/GmkElevator.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataHana.h"
#include "gf/GfDataMercenaries.h"
#include "gf/GfGameUtil.h"
#include "gf/GfItemUtil.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfPlayFactory.h"
#include "gf/GfReqCommand.h"
#include "gf/ParamReturnTitle.h"
#include "gf/gf_menu_obj_camp_menu.h"
#include "gf/gf_menu_obj_tips.h"
#include "mm/Col4.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"

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



// evt_movie.preload
static int fn_7100666634(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    if (!mm::mtl::Singleton<event::DebugManager>::getPtr()->isMovieDebug()) {
        mm::mtl::Singleton<event::MovieManager>::getPtr()->preload(name, false);
    }
    return 0;
}

// evt_movie.preloadObj
static int fn_7100666734(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    if (!mm::mtl::Singleton<event::DebugManager>::getPtr()->isMovieDebug()) {
        mm::mtl::Singleton<event::MovieManager>::getPtr()->preload(name, true);
    }
    return 0;
}

// evt_movie.play
static int fn_7100666834(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    if (!mm::mtl::Singleton<event::MovieManager>::getPtr()->isScriptFlag() &&
        !mm::mtl::Singleton<event::MovieManager>::getPtr()->isLoadedAuto(name, false) &&
        !mm::mtl::Singleton<event::SkipManager>::getPtr()->isSkip()) {
        mm::mtl::Singleton<event::FrameManager>::getPtr()->pause(static_cast<event::FrameManager::PAUSE_TYPE>(11), true);
        mm::mtl::Singleton<event::MovieManager>::getPtr()->captureScreen(true);
        mm::mtl::Singleton<event::MovieManager>::getPtr()->setScriptFlag(true);
        vmWaitModeSet(pThread);
        return 0;
    }
    mm::mtl::Singleton<event::MovieManager>::getPtr()->preload(name, false);
    if (!mm::mtl::Singleton<event::MovieManager>::getPtr()->isLoading()) {
        mm::mtl::Singleton<event::MovieManager>::getPtr()->play(name, false, true);
        mm::mtl::Singleton<event::FrameManager>::getPtr()->pause(static_cast<event::FrameManager::PAUSE_TYPE>(11), false);
        mm::mtl::Singleton<event::MovieManager>::getPtr()->captureScreen(false);
        mm::mtl::Singleton<event::MovieManager>::getPtr()->setScriptFlag(false);
        return 0;
    }
    mm::mtl::Singleton<event::FrameManager>::getPtr()->pause(static_cast<event::FrameManager::PAUSE_TYPE>(11), true);
    mm::mtl::Singleton<event::MovieManager>::getPtr()->captureScreen(true);
    vmWaitModeSet(pThread);
    return 0;
}

// evt_movie.playObj
static int fn_7100666DD4(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    if (!mm::mtl::Singleton<event::MovieManager>::getPtr()->isScriptFlag() &&
        !mm::mtl::Singleton<event::SkipManager>::getPtr()->isSkip() &&
        !mm::mtl::Singleton<event::MovieManager>::getPtr()->isLoadedAuto(name, false)) {
        mm::mtl::Singleton<event::FrameManager>::getPtr()->pause(static_cast<event::FrameManager::PAUSE_TYPE>(11), true);
        mm::mtl::Singleton<event::MovieManager>::getPtr()->captureScreen(true);
        mm::mtl::Singleton<event::MovieManager>::getPtr()->setScriptFlag(true);
        vmWaitModeSet(pThread);
        return 0;
    }
    mm::mtl::Singleton<event::MovieManager>::getPtr()->preload(name, true);
    if (!mm::mtl::Singleton<event::MovieManager>::getPtr()->isLoading()) {
        mm::mtl::Singleton<event::MovieManager>::getPtr()->play(name, true, true);
        mm::mtl::Singleton<event::FrameManager>::getPtr()->pause(static_cast<event::FrameManager::PAUSE_TYPE>(11), false);
        mm::mtl::Singleton<event::MovieManager>::getPtr()->captureScreen(false);
        mm::mtl::Singleton<event::MovieManager>::getPtr()->setScriptFlag(false);
        return 0;
    }
    mm::mtl::Singleton<event::FrameManager>::getPtr()->pause(static_cast<event::FrameManager::PAUSE_TYPE>(11), true);
    mm::mtl::Singleton<event::MovieManager>::getPtr()->captureScreen(true);
    vmWaitModeSet(pThread);
    return 0;
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B739A8).
static VMPluginFunc s_evtmoviePlugin[] = {
    {"preload", fn_7100666634},
    {"preloadObj", fn_7100666734},
    {"play", fn_7100666834},
    {"playObj", fn_7100666DD4},
    {nullptr, nullptr},
};

void pluginEvtMovRegist() {
    vmPluginRegist("evt_movie", s_evtmoviePlugin);
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

// The evt_map plugin's table. Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B739F8).
static VMPluginFunc s_evtmapPlugin[] = {
    {"setDisp", fn_7100667374},
    {nullptr, nullptr},
};

void pluginEvtMapRegist() {
    vmPluginRegist("evt_map", s_evtmapPlugin);
}

// evt_ui.openChapTelop
static int fn_7100667534(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    if (!mm::mtl::Singleton<event::UIManager>::getPtr()->openChapTelopUI(id)) {
        vmWaitModeSet(pThread);
    }
    return 0;
}

// evt_ui.openAvanTitle
static int fn_71006675E4(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::UIManager>::getPtr()->openAvanTitleUI(id);
    return 0;
}

// evt_ui.closeAvanTitle
static int fn_710066767C(VMThread* pThread) {
    mm::mtl::Singleton<event::UIManager>::getPtr()->closeAvanTitleUI(10);
    return 0;
}

// evt_ui.openZoneTelop
static int fn_71006676FC(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::UIManager>::getPtr()->openZoneTelopUI(id);
    return 0;
}

// evt_ui.openOpeningTelopC
static int fn_7100667794(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::UIManager>::getPtr()->openOpeningTelopUI(event::UIManager::OPTELOP_C, id);
    return 0;
}

// evt_ui.openOpeningTelopLB
static int fn_7100667830(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::UIManager>::getPtr()->openOpeningTelopUI(event::UIManager::OPTELOP_LB, id);
    return 0;
}

// evt_ui.openOpeningTelopRT
static int fn_71006678CC(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::UIManager>::getPtr()->openOpeningTelopUI(event::UIManager::OPTELOP_RT, id);
    return 0;
}

// evt_ui.openOpeningTelopLH
static int fn_7100667968(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::UIManager>::getPtr()->openOpeningTelopUI(event::UIManager::OPTELOP_LH, id);
    return 0;
}

// evt_ui.openOpeningTelopRH
static int fn_7100667A04(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::UIManager>::getPtr()->openOpeningTelopUI(event::UIManager::OPTELOP_RH, id);
    return 0;
}

// evt_ui.closeOpeningTelopC
static int fn_7100667AA0(VMThread* pThread) {
    mm::mtl::Singleton<event::UIManager>::getPtr()->closeOpeningTelopUI(event::UIManager::OPTELOP_C);
    return 0;
}

// evt_ui.closeOpeningTelopLB
static int fn_7100667B20(VMThread* pThread) {
    mm::mtl::Singleton<event::UIManager>::getPtr()->closeOpeningTelopUI(event::UIManager::OPTELOP_LB);
    return 0;
}

// evt_ui.closeOpeningTelopRT
static int fn_7100667BA0(VMThread* pThread) {
    mm::mtl::Singleton<event::UIManager>::getPtr()->closeOpeningTelopUI(event::UIManager::OPTELOP_RT);
    return 0;
}

// evt_ui.closeOpeningTelopLH
static int fn_7100667C20(VMThread* pThread) {
    mm::mtl::Singleton<event::UIManager>::getPtr()->closeOpeningTelopUI(event::UIManager::OPTELOP_LH);
    return 0;
}

// evt_ui.closeOpeningTelopRH
static int fn_7100667CA0(VMThread* pThread) {
    mm::mtl::Singleton<event::UIManager>::getPtr()->closeOpeningTelopUI(event::UIManager::OPTELOP_RH);
    return 0;
}

// evt_ui.startStaffroll
static int fn_7100667D20(VMThread* pThread) {
    float speed = vmArgFixedGet(1, vmArgPtrGet(pThread, 1));
    int type = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    mm::mtl::Singleton<event::UIManager>::getPtr()->startStaffrollUI(speed, type);
    return 0;
}

// evt_ui.endStaffroll
static int fn_7100667DE4(VMThread* pThread) {
    mm::mtl::Singleton<event::UIManager>::getPtr()->endStaffroll();
    return 0;
}

// evt_ui.openHomuraHikari
static int fn_7100667E60(VMThread* pThread) {
    if (!gf::GfManager::isExecModeThater()) {
        if (!mm::mtl::Singleton<event::UIManager>::getPtr()->openHomuraHikariUI()) {
            vmWaitModeSet(pThread);
        }
    }
    return 0;
}

// evt_ui.openMiniGame
static int fn_7100667EF4(VMThread* pThread) {
    if (!mm::mtl::Singleton<event::UIManager>::getPtr()->openMinigame()) {
        vmWaitModeSet(pThread);
    }
    return 0;
}

// evt_ui.openHitonowa
static int fn_7100667F80(VMThread* pThread) {
    int id0 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int param = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int flag = vmArgBoolGet(3, vmArgPtrGet(pThread, 3));
    int id1 = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    int id2 = vmArgIntGet(5, vmArgPtrGet(pThread, 5));
    mm::mtl::FixedVector<int, 3> ids;
    if (id0 > 0) {
        ids.push_back(id0);
    }
    if (id1 > 0) {
        ids.push_back(id1);
    }
    if (id2 > 0) {
        ids.push_back(id2);
    }
    if (!mm::mtl::Singleton<event::UIManager>::getPtr()->fn_7100105B40(ids, param, flag != 0)) {
        vmWaitModeSet(pThread);
    }
    return 0;
}

// The evt_ui plugin's table. Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B73A18).
static VMPluginFunc s_evtuiPlugin[] = {
    {"openChapTelop", fn_7100667534},
    {"openAvanTitle", fn_71006675E4},
    {"closeAvanTitle", fn_710066767C},
    {"openZoneTelop", fn_71006676FC},
    {"openOpeningTelopC", fn_7100667794},
    {"openOpeningTelopLB", fn_7100667830},
    {"openOpeningTelopRT", fn_71006678CC},
    {"openOpeningTelopLH", fn_7100667968},
    {"openOpeningTelopRH", fn_7100667A04},
    {"closeOpeningTelopC", fn_7100667AA0},
    {"closeOpeningTelopLB", fn_7100667B20},
    {"closeOpeningTelopRT", fn_7100667BA0},
    {"closeOpeningTelopLH", fn_7100667C20},
    {"closeOpeningTelopRH", fn_7100667CA0},
    {"startStaffroll", fn_7100667D20},
    {"endStaffroll", fn_7100667DE4},
    {"openHomuraHikari", fn_7100667E60},
    {"openMiniGame", fn_7100667EF4},
    {"openHitonowa", fn_7100667F80},
    {nullptr, nullptr},
};

void pluginEvtUiRegist() {
    vmPluginRegist("evt_ui", s_evtuiPlugin);
}

// evt_voice.play
static int fn_710066814C(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::VoiceManager>::getPtr()->playOneshot(name, 1.0f);
    return 0;
}

// The evt_voice plugin's table. Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B73B58).
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

// The evt_vol plugin's table. Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B73B78).
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

// fld.getScenario
static int fn_7100668C20(VMThread* pThread) {
    vmRetIntSet(pThread, gf::GfDataBlade::fn_7100231884());
    return 1;
}

// fld.setScenario
static int fn_7100668C68(VMThread* pThread) {
    int value = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    gf::SCOM_SET_FLAG::create(16, 1, value);
    return 0;
}

// fld.getTime
static int fn_7100668CA0(VMThread* pThread) {
    int hour = 0;
    if (mm::mtl::PtrSingleton<gf::GfFieldTime>::sys() != nullptr) {
        hour = mm::mtl::PtrSingleton<gf::GfFieldTime>::sys()->getHour();
    }
    vmRetIntSet(pThread, hour);
    return 1;
}

// fld.setTime
static int fn_7100668CF4(VMThread* pThread) {
    int hour = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int min = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    if (mm::mtl::PtrSingleton<gf::GfFieldTime>::sys() != nullptr) {
        mm::mtl::PtrSingleton<gf::GfFieldTime>::sys()->setTime(hour, min);
    }
    return 0;
}

// fld.stopTime
static int fn_7100668D60(VMThread* pThread) {
    int stop = vmArgOmitChk(pThread, 1) ? 0 : vmArgBoolGet(1, vmArgPtrGet(pThread, 1));
    if (mm::mtl::PtrSingleton<gf::GfFieldTime>::sys() != nullptr) {
        mm::mtl::PtrSingleton<gf::GfFieldTime>::sys()->setFieldScriptTimeStop(stop != 0);
    }
    return 0;
}

// fld.setWeather
static int fn_7100668DCC(VMThread* pThread) {
    int type = vmArgOmitChk(pThread, 1) ? 0 : vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    bool flag = vmArgOmitChk(pThread, 2) ? false : vmArgBoolGet(2, vmArgPtrGet(pThread, 2)) != 0;
    gf::GfFieldWeather::setWeather(static_cast<gf::WEATYPE>(type), flag);
    return 0;
}

// fld.setFlag1
static int fn_7100668E5C(VMThread* pThread) {
    int index = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int value = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    gf::SCOM_SET_FLAG::create(1, index, value);
    return 0;
}

// fld.getFlag1
static int fn_7100668EBC(VMThread* pThread) {
    int index = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    vmRetIntSet(pThread, gf::GfGameFlag::getLocal(1, index));
    return 1;
}

// fld.setFlag2
static int fn_7100668F1C(VMThread* pThread) {
    int index = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int value = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    gf::SCOM_SET_FLAG::create(2, index, value);
    return 0;
}

// fld.getFlag2
static int fn_7100668F7C(VMThread* pThread) {
    int index = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    vmRetIntSet(pThread, gf::GfGameFlag::getLocal(2, index));
    return 1;
}

// fld.setFlag4
static int fn_7100668FDC(VMThread* pThread) {
    int index = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int value = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    gf::SCOM_SET_FLAG::create(4, index, value);
    return 0;
}

// fld.getFlag4
static int fn_710066903C(VMThread* pThread) {
    int index = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    vmRetIntSet(pThread, gf::GfGameFlag::getLocal(4, index));
    return 1;
}

// fld.setFlag8
static int fn_710066909C(VMThread* pThread) {
    int index = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int value = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    gf::SCOM_SET_FLAG::create(8, index, value);
    return 0;
}

// fld.getFlag8
static int fn_71006690FC(VMThread* pThread) {
    int index = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    vmRetIntSet(pThread, gf::GfGameFlag::getLocal(8, index));
    return 1;
}

// fld.setFlag16
static int fn_710066915C(VMThread* pThread) {
    int index = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int value = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    gf::SCOM_SET_FLAG::create(16, index, value);
    return 0;
}

// fld.getFlag16
static int fn_71006691BC(VMThread* pThread) {
    int index = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    vmRetIntSet(pThread, gf::GfGameFlag::getLocal(16, index));
    return 1;
}

// fld.startScript
static int fn_710066921C(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    gf::GfReqCommand::reqStartScript(0, name, true);
    return 0;
}

// fld.addMoney
static int fn_7100669254(VMThread* pThread) {
    int money = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    gf::SCOM_ADD_MONEY::create(money);
    return 0;
}

// fld.addItem
static int fn_7100669280(VMThread* pThread) {
    // the first argument is read and not used
    vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int item = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int count = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    gf::GfItemUtil::addItemBox(item, count);
    return 0;
}

// fld.isGameCond
static int fn_71006692F4(VMThread* pThread) {
    int cond = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    vmRetBoolSet(pThread, gf::GfGameCond::isGameCond(cond));
    return 1;
}

// fld.setCamShip
static int fn_7100669350(VMThread* pThread) {
    int roll = vmArgBoolGet(1, vmArgPtrGet(pThread, 1));
    int pitch = vmArgBoolGet(2, vmArgPtrGet(pThread, 2));
    gf::ShipRollPlugin::setEnable(roll == 1, pitch == 1);
    return 0;
}

// fld.startCam
static int fn_71006693B8(VMThread* pThread) {
    float x = vmArgFixedGet(1, vmArgPtrGet(pThread, 1));
    float y = vmArgFixedGet(2, vmArgPtrGet(pThread, 2));
    float z = vmArgFixedGet(3, vmArgPtrGet(pThread, 3));
    float rotX = vmArgFixedGet(4, vmArgPtrGet(pThread, 4));
    float rotY = vmArgFixedGet(5, vmArgPtrGet(pThread, 5));
    int frames = vmArgIntGet(6, vmArgPtrGet(pThread, 6));
    mm::mtl::Singleton<gf::ScriptCamera>::getPtr()->start(mm::Vec3(x, y, z), mm::Vec3(rotX, rotY, 0.0f),
                                                       static_cast<float>(frames));
    return 0;
}

// fld.endCam
static int fn_710066951C(VMThread* pThread) {
    int frames = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<gf::ScriptCamera>::getPtr()->end(static_cast<float>(frames));
    return 0;
}

// fld.moveCam
static int fn_71006695B4(VMThread* pThread) {
    float x = vmArgFixedGet(1, vmArgPtrGet(pThread, 1));
    float y = vmArgFixedGet(2, vmArgPtrGet(pThread, 2));
    float z = vmArgFixedGet(3, vmArgPtrGet(pThread, 3));
    float rotX = vmArgFixedGet(4, vmArgPtrGet(pThread, 4));
    float rotY = vmArgFixedGet(5, vmArgPtrGet(pThread, 5));
    int frames = vmArgIntGet(6, vmArgPtrGet(pThread, 6));
    mm::mtl::Singleton<gf::ScriptCamera>::getPtr()->move(mm::Vec3(x, y, z), mm::Vec3(rotX, rotY, 0.0f),
                                                       static_cast<float>(frames));
    return 0;
}

// fld.setNpcMeet
static int fn_7100669718(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    bool before = gf::GfDataBlade::fn_710024DE6C(id);
    gf::GfDataBlade::fn_710024DDDC(id, true);
    if (before != gf::GfDataBlade::fn_710024DE6C(id)) {
        gf::GfMenuManager::fn_710035A764(id);
    }
    return 0;
}

// The fld plugin's table. Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B73C68).
static VMPluginFunc s_fldPlugin[] = {
    {"getScenario", fn_7100668C20},
    {"setScenario", fn_7100668C68},
    {"getTime", fn_7100668CA0},
    {"setTime", fn_7100668CF4},
    {"stopTime", fn_7100668D60},
    {"setWeather", fn_7100668DCC},
    {"setFlag1", fn_7100668E5C},
    {"getFlag1", fn_7100668EBC},
    {"setFlag2", fn_7100668F1C},
    {"getFlag2", fn_7100668F7C},
    {"setFlag4", fn_7100668FDC},
    {"getFlag4", fn_710066903C},
    {"setFlag8", fn_710066909C},
    {"getFlag8", fn_71006690FC},
    {"setFlag16", fn_710066915C},
    {"getFlag16", fn_71006691BC},
    {"startScript", fn_710066921C},
    {"addMoney", fn_7100669254},
    {"addItem", fn_7100669280},
    {"isGameCond", fn_71006692F4},
    {"setCamShip", fn_7100669350},
    {"startCam", fn_71006693B8},
    {"endCam", fn_710066951C},
    {"moveCam", fn_71006695B4},
    {"setNpcMeet", fn_7100669718},
    {nullptr, nullptr},
};

void pluginFldRegist() {
    vmPluginRegist("fld", s_fldPlugin);
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

// The gmk plugin's table. Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B73E08).
static VMPluginFunc s_gmkPlugin[] = {
    {"getStartId", fn_710066978C},
    {"openPortal", fn_71006697CC},
    {nullptr, nullptr},
};

void pluginGmkRegist() {
    vmPluginRegist("gmk", s_gmkPlugin);
}

// pt.setBladeEnable
static int fn_7100669814(VMThread* pThread) {
    unsigned int blade = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    unsigned int driver = 0;
    if (!vmArgOmitChk(pThread, 2)) {
        driver = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    }
    if (driver == 11) {
        driver = 1;
    }
    int slot = -1;
    if (!gf::GfGameManager::isClearGame() && gf::GfDataBlade::isRegularBlade(blade)) {
        bool regular = gf::GfDataBlade::isRegularBlade(gf::GfDataDriver::getBlade(driver, 0));
        if (blade == 1003) {
            slot = 4;
        } else {
            slot = regular ? -1 : 0;
        }
    }
    unsigned int creator = gf::GfDataBlade::getCreator(blade);
    if ((gf::GfDataBlade::isRareBlade(blade) && !gf::GfDataBlade::isDummyBlade(blade) && creator != 0 &&
         gf::GfDataDriver::isActivateUnuse(creator) && !gf::GfDataBlade::isEnableEngageRex(blade) &&
         !(blade == 1042 && creator == 8 && gf::GfDataBlade::fn_7100231884() == 1021)) ||
        (gf::GfDataHana::isValid(blade) &&
         (gf::GfDataBlade::fn_71002383C8(1005) || gf::GfDataBlade::fn_71002383C8(1006) ||
          gf::GfDataBlade::fn_71002383C8(1007)))) {
        gf::SCOM_PARTY_ADD::removeBlade(blade, true, true);
    } else {
        gf::SCOM_PARTY_ADD::addBlade(blade, driver, slot);
    }
    return 0;
}

// pt.setBladeDisable
static int fn_7100669984(VMThread* pThread) {
    unsigned int blade = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    // an omitted second argument counts as true
    if (vmArgOmitChk(pThread, 2) || vmArgBoolGet(2, vmArgPtrGet(pThread, 2))) {
        gf::SCOM_PARTY_ADD::removeBlade(blade, true, true);
    } else {
        gf::SCOM_PARTY_ADD::removeBlade(blade, false, true);
    }
    return 0;
}

// pt.setDriverEnable: not identical yet (wip/pt_full.cpp; the original hoists `mov w0, w19` above `cbz w20`)
static int fn_7100669A08(VMThread* pThread);

// pt.setDriverDisable
static int fn_7100669BA4(VMThread* pThread) {
    unsigned int driver = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    // an omitted second argument counts as true
    if (vmArgOmitChk(pThread, 2) || vmArgBoolGet(2, vmArgPtrGet(pThread, 2))) {
        gf::SCOM_PARTY_ADD::removeDriver(driver, true);
    } else {
        gf::SCOM_PARTY_ADD::removeDriver(driver, false);
    }
    return 0;
}

// pt.setDriverAway
static int fn_7100669C20(VMThread* pThread) {
    unsigned int driver = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    bool mask = vmArgBoolGet(2, vmArgPtrGet(pThread, 2));
    gf::GfDataDriver::setScenarioMask(driver, mask);
    return 0;
}

// pt.startBattle
static int fn_7100669C80(VMThread* pThread) {
    bool flag = true;
    if (!vmArgOmitChk(pThread, 1)) {
        flag = vmArgBoolGet(1, vmArgPtrGet(pThread, 1));
    }
    gf::GfPlayFactory::createBattleStart(flag);
    return 0;
}

// pt.setBladeCreator
static int fn_7100669CD8(VMThread* pThread) {
    unsigned int blade = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    unsigned int creator = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    gf::GfDataBlade::setCreator(blade, creator);
    return 0;
}

// pt.setCurrentBlade
static int fn_7100669D34(VMThread* pThread) {
    unsigned int blade = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    // Pyra and Mythra (1001, 1002) stay as they are once the game is cleared
    if (gf::GfGameManager::isClearGame() && blade >= 1001 && blade <= 1003 &&
        (gf::GfDataBlade::fn_71002383C8(1001) || gf::GfDataBlade::fn_71002383C8(1002))) {
        return 0;
    }
    gf::SCOM_CURRENT_BLADE::create(blade);
    return 0;
}

// pt.setHomuraHikari
static int fn_7100669D9C(VMThread* pThread) {
    bool homura = vmArgBoolGet(1, vmArgPtrGet(pThread, 1));
    gf::GfGameUtil::changeHikariCurrent(!homura);
    return 0;
}

// pt.setMaxGauge
static int fn_7100669DD0(VMThread* pThread) {
    gf::GfGameUtil::setMaxPartyGauge();
    return 0;
}

// pt.setSoloRex
static int fn_7100669DE8(VMThread* pThread) {
    bool solo = vmArgBoolGet(1, vmArgPtrGet(pThread, 1));
    gf::SCOM_SOLO_REX::create(solo);
    return 0;
}

// pt.setPartyChange10010
static int fn_7100669E1C(VMThread* pThread) {
    gf::GfGameUtil::setPartyChange10010();
    return 0;
}

// pt.setPartyChange10020
static int fn_7100669E34(VMThread* pThread) {
    gf::GfGameUtil::setPartyChange10020();
    return 0;
}

// pt.changeKubira
static int fn_7100669E4C(VMThread* pThread) {
    gf::GfGameUtil::fn_71002EBC90();
    return 0;
}

// pt.setBladeLeader
static int fn_7100669E64(VMThread* pThread) {
    unsigned int blade = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    if (gf::GfDataBlade::isActivateUnuse(blade)) {
        unsigned int driver = gf::GfGameParty::getDriverBdatId(0, 0);
        gf::GfDataBlade::setCreator(blade, driver);
        gf::GfDataBlade::setEnableEngageRex(blade, false);
        gf::SCOM_PARTY_ADD::addBlade(blade, driver, -1);
    }
    return 0;
}

// pt.setIraParty
static int fn_7100669ED8(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    gf::SCOM_PARTY_ADD::fn_7100562048(id);
    return 0;
}

static VMPluginFunc s_ptPlugin[] = {
    {"setBladeEnable", fn_7100669814},
    {"setBladeDisable", fn_7100669984},
    {"setDriverEnable", fn_7100669A08},
    {"setDriverDisable", fn_7100669BA4},
    {"setDriverAway", fn_7100669C20},
    {"startBattle", fn_7100669C80},
    {"setBladeCreator", fn_7100669CD8},
    {"setCurrentBlade", fn_7100669D34},
    {"setHomuraHikari", fn_7100669D9C},
    {"setMaxGauge", fn_7100669DD0},
    {"setSoloRex", fn_7100669DE8},
    {"setPartyChange10010", fn_7100669E1C},
    {"setPartyChange10020", fn_7100669E34},
    {"changeKubira", fn_7100669E4C},
    {"setBladeLeader", fn_7100669E64},
    {"setIraParty", fn_7100669ED8},
    {nullptr, nullptr},
};

void pluginPartyRegist() {
    vmPluginRegist("pt", s_ptPlugin);
}

// sys.getStartId
static int fn_7100669F18(VMThread* pThread) {
    vmRetIntSet(pThread, gf::GfGameEvent::getAfterEventStartID());
    return 1;
}

// sys.playEvent
static int fn_7100669F5C(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    if (!gf::GfManager::isExecModeThater()) {
        gf::GfPlayFactory::createOneEvent(id);
    }
    return 0;
}

// sys.reserveEvent
static int fn_7100669FA0(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    if (!gf::GfManager::isExecModeThater()) {
        gf::GfPlayFactory::createReserveEvent(name);
    }
    return 0;
}

// sys.returnTitle
static int fn_7100669FE4(VMThread* pThread) {
    gf::ParamReturnTitle param = {};
    param.m_gameClear = true;
    gf::GfPlayFactory::createReturnTitle(param);
    return 0;
}

// sys.fadeClear
static int fn_710066A014(VMThread* pThread) {
    int time = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    gf::GfMenuFade::setFade(0, time, mm::Col4::zero);
    gf::GfMenuFade::setFade(1, time, mm::Col4::zero);
    gf::GfMenuFade::setFade(2, time, mm::Col4::zero);
    return 0;
}

// sys.getGameType
static int fn_710066A080(VMThread* pThread) {
    vmRetIntSet(pThread, gf::GfGameManager::fn_71002A9E68());
    return 1;
}

// sys.getBootType
static int fn_710066A0C8(VMThread* pThread) {
    vmRetIntSet(pThread, gf::fn_71002EEBE4());
    return 1;
}

// sys.autoSave
static int fn_710066A10C(VMThread* pThread) {
    gf::GfGameManager::fn_71002AC6A8();
    return 0;
}

// sys.fadeIn
static int fn_710066A124(VMThread* pThread) {
    int time = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    gf::GfMenuFade::setFade(1, time, mm::Col4::black);
    return 0;
}

// sys.playTutorial
static int fn_710066A160(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    if (!gf::GfManager::isExecModeThater()) {
        gf::GfPlayFactory::fn_7100321924(name, id);
    }
    return 0;
}

// The sys plugin's table. Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B73F48).
static VMPluginFunc s_sysPlugin[] = {
    {"getStartId", fn_7100669F18},
    {"playEvent", fn_7100669F5C},
    {"reserveEvent", fn_7100669FA0},
    {"returnTitle", fn_7100669FE4},
    {"fadeClear", fn_710066A014},
    {"getGameType", fn_710066A080},
    {"getBootType", fn_710066A0C8},
    {"autoSave", fn_710066A10C},
    {"fadeIn", fn_710066A124},
    {"playTutorial", fn_710066A160},
    {nullptr, nullptr},
};

void pluginSysRegist() {
    vmPluginRegist("sys", s_sysPlugin);
}

// ui.dispCommonUI
static int fn_710066A1DC(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    vmRetIntSet(pThread, gf::GfPlayFactory::createCommonMessage(id));
    return 1;
}

// ui.isDispCommonUI
static int fn_710066A234(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    vmRetBoolSet(pThread, gf::GfPlayFactory::isDispCommonMessage(id));
    return 1;
}

// ui.getDispCommonUI
static int fn_710066A290(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    vmRetIntSet(pThread, gf::GfPlayFactory::getDispCommonMessage(id));
    return 1;
}

// ui.openChapterSave
static int fn_710066A2E8(VMThread* pThread) {
    int id = vmArgOmitChk(pThread, 1) ? 0 : vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    gf::GfPlayFactory::createOpenChapterSave(id);
    return 0;
}

// ui.isCloseChapterSave
static int fn_710066A338(VMThread* pThread) {
    vmRetBoolSet(pThread, !gf::GfPlayFactory::isDispChapterSave());
    return 1;
}

// ui.openChapter
static int fn_710066A380(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    gf::GfPlayFactory::createOpenChapterUI(id);
    return 0;
}

// ui.openChapterEnd
static int fn_710066A3AC(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    gf::GfPlayFactory::createOpenChapterEndUI(id);
    return 0;
}

// ui.openZone
static int fn_710066A3D8(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    gf::GfPlayFactory::createOpenZoneUI(id);
    return 0;
}

// ui.settingPartyFormBeforeBattle
static int fn_710066A404(VMThread* pThread) {
    gf::GfMenuObjPartyForm3::OpenParam param;
    param.m_value = 1;
    gf::GfMenuObjPartyForm3::registOpenParam(param);
    return 0;
}

// ui.openPartyForm
static int fn_710066A430(VMThread* pThread) {
    gf::GfPlayFactory::createOpenMenu(0x24, nullptr);
    return 0;
}

// ui.isOpenPartyForm
static int fn_710066A450(VMThread* pThread) {
    gf::GfSequentialPlay* play = mm::mtl::PtrSingleton<gf::GfSequentialPlay>::sys();
    vmRetBoolSet(pThread, play != nullptr && play->fn_7100323420(0x24, 0));
    return 1;
}

// ui.openBladeCreate
static int fn_710066A4B8(VMThread* pThread) {
    gf::GfMenuObjBladeCreate::OpenParam param;
    param.m_value = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    gf::GfMenuObjBladeCreate::registOpenParam(param);
    gf::GfPlayFactory::createOpenMenu(0xB, nullptr);
    return 0;
}

// ui.openOrbMenu
static int fn_710066A500(VMThread* pThread) {
    return 0;
}

// ui.openTutorial
static int fn_710066A508(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    if (!gf::GfManager::isExecModeThater()) {
        if (vmWkIdxGet(pThread) == 0) {
            gf::GfPlayFactory::createOpenDummyTutorial(id);
            vmWkIdxSet(pThread, 1);
        } else if (!gf::GfMenuManager::isOpenDummyTutorial()) {
            return 0;
        }
        vmWaitModeSet(pThread);
    }
    return 0;
}

// ui.waitCloseFullScreen
static int fn_710066A57C(VMThread* pThread) {
    if (gf::GfMenuObjUtil::fn_710048FD30(3)) {
        gf::GfSequentialPlay* play = mm::mtl::PtrSingleton<gf::GfSequentialPlay>::sys();
        if (play != nullptr && play->fn_7100323420(0x24, 0)) {
            vmWaitModeSet(pThread);
        }
    }
    if (gf::GfMenuManager::isOpenFullScreen()) {
        vmWaitModeSet(pThread);
    }
    return 0;
}

// ui.enableEnvironmentInfo
static int fn_710066A5E0(VMThread* pThread) {
    gf::GfMenuObjEnvironmentInfo::enable();
    return 0;
}

// ui.disableEnvironmentInfo
static int fn_710066A5F8(VMThread* pThread) {
    gf::GfMenuObjEnvironmentInfo::disable();
    return 0;
}

// ui.openMiniGame
static int fn_710066A610(VMThread* pThread) {
    gf::GfPlayFactory::createMiniGame();
    return 0;
}

// ui.openTutorialText
static int fn_710066A628(VMThread* pThread) {
    int index = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int text = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    if (!gf::GfManager::isExecModeThater()) {
        if (vmWkIdxGet(pThread) == 0) {
            gf::GfMenuObjTutorial::TextParam param;
            param.m_text = text;
            gf::GfMenuObjTutorial::openText(index, param);
            vmWkIdxSet(pThread, 1);
        } else if (!gf::GfMenuObjTutorial::isWaiting()) {
            return 0;
        }
        vmWaitModeSet(pThread);
    }
    return 0;
}

// ui.closeTutorialText
static int fn_710066A6C8(VMThread* pThread) {
    int index = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    if (!gf::GfManager::isExecModeThater()) {
        gf::GfMenuObjTutorial::closeText(index);
    }
    return 0;
}

// ui.nextTutorialText
static int fn_710066A70C(VMThread* pThread) {
    int index = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int text = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    if (!gf::GfManager::isExecModeThater()) {
        if (vmWkIdxGet(pThread) == 0) {
            gf::GfMenuObjTutorial::TextParam param;
            param.m_text = text;
            gf::GfMenuObjTutorial::openText(index, param);
            vmWkIdxSet(pThread, 1);
        } else if (!gf::GfMenuObjTutorial::isWaiting()) {
            return 0;
        }
        vmWaitModeSet(pThread);
    }
    return 0;
}

// ui.openTutorialArrow
static int fn_710066A7AC(VMThread* pThread) {
    int index = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int b = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int c = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    if (!gf::GfManager::isExecModeThater()) {
        gf::GfMenuObjTutorial::FocusParam param;
        param.m_value[2] = a;
        param.m_value[0] = b;
        param.m_value[1] = c;
        gf::GfMenuObjTutorial::openFocus(index, param);
    }
    return 0;
}

// ui.closeTutorialArrow
static int fn_710066A868(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    gf::GfMenuObjTutorial::closeFocus(id);
    return 0;
}

// ui.openTutorialIcon
static int fn_710066A894(VMThread* pThread) {
    int index = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int b = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    if (!gf::GfManager::isExecModeThater()) {
        gf::GfMenuObjTutorial::IconParam param;
        param.m_value[0] = a;
        param.m_value[1] = b;
        gf::GfMenuObjTutorial::openIcon(index, param);
    }
    return 0;
}

// ui.closeTutorialIcon
static int fn_710066A928(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    gf::GfMenuObjTutorial::closeIcon(id);
    return 0;
}

// ui.closeTutorial
static int fn_710066A954(VMThread* pThread) {
    gf::GfMenuObjTutorial::closeAll();
    return 0;
}

// ui.openPopup
static int fn_710066A96C(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    gf::GfMenuObjPopup::OpenParam param = {10, {static_cast<unsigned int>(id), 0, 0}};
    gf::GfMenuObjPopup::open(param);
    return 0;
}

// ui.startTutorial
static int fn_710066A9B0(VMThread* pThread) {
    if (!gf::GfManager::isExecModeThater()) {
        if (vmWkIdxGet(pThread) == 0) {
            gf::GfMenuObjTutorial::start();
            vmWkIdxSet(pThread, 1);
            vmWaitModeSet(pThread);
        } else if (gf::GfMenuObjTutorial::isWaiting()) {
            vmWaitModeSet(pThread);
        }
    }
    if (gf::GfGameScene* scene = mm::mtl::PtrSingleton<gf::GfGameScene>::sys()) {
        scene->fn_71002C4BE4();
    }
    return 0;
}

// ui.enableMinimap
static int fn_710066AA1C(VMThread* pThread) {
    gf::GfMenuObjMinimap2::enable();
    return 0;
}

// ui.disableMinimap
static int fn_710066AA34(VMThread* pThread) {
    gf::GfMenuObjMinimap2::disable();
    return 0;
}

// ui.lockQuestLogOpen
static int fn_710066AA4C(VMThread* pThread) {
    gf::GfMenuObjQuestLog::lockLogOpen();
    return 0;
}

// ui.unlockQuestLogOpen
static int fn_710066AA64(VMThread* pThread) {
    gf::GfMenuObjQuestLog::unlockLogOpen();
    return 0;
}

// ui.getTutorialStartID
static int fn_710066AA7C(VMThread* pThread) {
    vmRetIntSet(pThread, gf::GfMenuManager::fn_710035A364());
    return 1;
}

// ui.unlockTips
static int fn_710066AAC0(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    gf::fn_7100487A90(id);
    return 0;
}

// ui.setCampTalkNew
static int fn_710066AAEC(VMThread* pThread) {
    gf::fn_71003BBCDC();
    return 0;
}

// The ui plugin's table. Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B73FF8).
static VMPluginFunc s_uiPlugin[] = {
    {"dispCommonUI", fn_710066A1DC},
    {"isDispCommonUI", fn_710066A234},
    {"getDispCommonUI", fn_710066A290},
    {"openChapterSave", fn_710066A2E8},
    {"isCloseChapterSave", fn_710066A338},
    {"openChapter", fn_710066A380},
    {"openChapterEnd", fn_710066A3AC},
    {"openZone", fn_710066A3D8},
    {"settingPartyFormBeforeBattle", fn_710066A404},
    {"openPartyForm", fn_710066A430},
    {"isOpenPartyForm", fn_710066A450},
    {"openBladeCreate", fn_710066A4B8},
    {"openOrbMenu", fn_710066A500},
    {"openTutorial", fn_710066A508},
    {"waitCloseFullScreen", fn_710066A57C},
    {"enableEnvironmentInfo", fn_710066A5E0},
    {"disableEnvironmentInfo", fn_710066A5F8},
    {"openMiniGame", fn_710066A610},
    {"openTutorialText", fn_710066A628},
    {"closeTutorialText", fn_710066A6C8},
    {"nextTutorialText", fn_710066A70C},
    {"openTutorialArrow", fn_710066A7AC},
    {"closeTutorialArrow", fn_710066A868},
    {"openTutorialIcon", fn_710066A894},
    {"closeTutorialIcon", fn_710066A928},
    {"closeTutorial", fn_710066A954},
    {"openPopup", fn_710066A96C},
    {"startTutorial", fn_710066A9B0},
    {"enableMinimap", fn_710066AA1C},
    {"disableMinimap", fn_710066AA34},
    {"lockQuestLogOpen", fn_710066AA4C},
    {"unlockQuestLogOpen", fn_710066AA64},
    {"getTutorialStartID", fn_710066AA7C},
    {"unlockTips", fn_710066AAC0},
    {"setCampTalkNew", fn_710066AAEC},
    {nullptr, nullptr},
};

void pluginUiRegist() {
    vmPluginRegist("ui", s_uiPlugin);
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

// The wait plugin's table. Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B74238).
static VMPluginFunc s_waitPlugin[] = {
    {"frame", fn_710066AB18},
    {nullptr, nullptr},
};

void pluginWaitRegist() {
    vmPluginRegist("wait", s_waitPlugin);
}

// The thread script class: a script makes a thread of one of its functions (thread(func)) and starts, ends, joins,
// sleeps and wakes it by the thread's id, which is the object's value. The methods are the table's strings.

// thread(func): a thread of the script function func
static int fn_710066ABB0(VMThread* th, void* unused, unsigned long ocId) {
    VMData ret;
    int func = vmArgFunctionGet(1, vmArgPtrGet(th, 1));
    int id;
    if (!vmThreadGetOC(th, func, &id)) {
        vmOCExceptionThrow(th);
        return 0;
    }
    ret.type = VMDATA_OC;
    ret.hi = ocId;
    ret.v.obj = reinterpret_cast<void*>(static_cast<unsigned long>(static_cast<unsigned int>(id)));
    vmRetValSet(th, &ret);
    return 1;
}

// thread.start
static int fn_710066AC34(VMThread* th, int id) {
    vmThreadStart(th, id);
    return 0;
}

// thread.end
static int fn_710066AC4C(VMThread* th, int id) {
    vmThreadEnd(id);
    return 0;
}

// thread.isAlive
static int fn_710066AC68(VMThread* th, int id) {
    vmRetBoolSet(th, vmThreadIsAlive(id));
    return 1;
}

// thread.join: waits while the thread runs
static int fn_710066ACB4(VMThread* th, int id) {
    if (vmThreadIsAlive(id)) {
        vmWaitModeSet(th);
    }
    return 0;
}

// thread.sleep
static int fn_710066ACE8(VMThread* th, int id) {
    vmThreadSleep(id);
    return 0;
}

// thread.wakeup
static int fn_710066AD04(VMThread* th, int id) {
    vmThreadWakeup(id);
    return 0;
}

// The thread class's methods. Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B74278).
static VMOCMethod s_threadMethods[] = {
    {"start", reinterpret_cast<void*>(&fn_710066AC34), 0},
    {"end", reinterpret_cast<void*>(&fn_710066AC4C), 0},
    {"isAlive", reinterpret_cast<void*>(&fn_710066AC68), 0},
    {"join", reinterpret_cast<void*>(&fn_710066ACB4), 0},
    {"sleep", reinterpret_cast<void*>(&fn_710066ACE8), 0},
    {"wakeup", reinterpret_cast<void*>(&fn_710066AD04), 0},
    {nullptr, nullptr, 0},
};

// The thread script class. Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B74258).
static VMOC s_threadOC = {"thread", reinterpret_cast<void*>(&fn_710066ABB0), nullptr, s_threadMethods};

void ocThreadRegist() {
    vmOCRegist(&s_threadOC);
}
