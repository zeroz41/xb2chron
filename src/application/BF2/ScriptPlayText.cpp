// Script VM plugins of this unit (their tables, entries and Regist functions). The entries are static and nothing
// names them: they keep placeholder fn_ names.
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


// The object the last evt_setup command created (cleared again at once). Proposed name, not the original's: the
// symbols leave it unnamed (lbl_7100EC1A98).
static event::Object* s_createdObj;

// evt_setup.talk
static int fn_710066332C(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    if (s_createdObj == nullptr) {
        s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createGfObjTalk(name);
    }
    s_createdObj = nullptr;
    return 0;
}

// evt_setup.walk
static int fn_71006633E0(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgOmitChk(pThread, 3) ? 0 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    if (s_createdObj == nullptr) {
        s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createGfObjPcByWalkID(name, id, option);
    }
    s_createdObj = nullptr;
    return 0;
}

// evt_setup.pc
static int fn_71006634F8(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgOmitChk(pThread, 3) ? 0 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    unsigned int option2 = vmArgOmitChk(pThread, 4) ? 0 : vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    if (s_createdObj == nullptr) {
        s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createGfObj(name, static_cast<event::CHARA_TYPE>(1), id, option, option2);
    }
    s_createdObj = nullptr;
    return 0;
}

// evt_setup.blade
static int fn_710066364C(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgOmitChk(pThread, 3) ? 0 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    if (s_createdObj == nullptr) {
        s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createGfObj(name, static_cast<event::CHARA_TYPE>(2), id, option, 0);
    }
    s_createdObj = nullptr;
    return 0;
}

// evt_setup.npc
static int fn_710066376C(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgOmitChk(pThread, 3) ? 0 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    if (s_createdObj == nullptr) {
        s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createGfObj(name, static_cast<event::CHARA_TYPE>(3), id, option, 0);
    }
    s_createdObj = nullptr;
    return 0;
}

// evt_setup.en
static int fn_710066388C(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgOmitChk(pThread, 3) ? 0 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    if (s_createdObj == nullptr) {
        s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createGfObj(name, static_cast<event::CHARA_TYPE>(5), id, option, 0);
    }
    s_createdObj = nullptr;
    return 0;
}

// evt_setup.model
static int fn_71006639AC(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    const char* model = vmArgStringGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgOmitChk(pThread, 3) ? 0 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    if (s_createdObj == nullptr) {
        s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createModel(name, model, 0, option);
    }
    s_createdObj = nullptr;
    return 0;
}

// evt_setup.pcByWalk
static int fn_7100663AC8(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgOmitChk(pThread, 3) ? 0 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    if (s_createdObj == nullptr) {
        s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createGfObjPcByWalkID(name, id, option);
    }
    s_createdObj = nullptr;
    return 0;
}

// evt_setup.pcByBlade
static int fn_7100663BE0(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgOmitChk(pThread, 3) ? 0 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    if (s_createdObj == nullptr) {
        s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createGfObjPcByBladeID(name, id, option);
    }
    s_createdObj = nullptr;
    return 0;
}

// evt_setup.bladeByWalk
static int fn_7100663CF8(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgOmitChk(pThread, 3) ? 0 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    if (s_createdObj == nullptr) {
        s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createGfObjBlByWalkID(name, id, option);
    }
    s_createdObj = nullptr;
    return 0;
}

// evt_setup.bladeByPc
static int fn_7100663E10(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgOmitChk(pThread, 3) ? 0 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    if (s_createdObj == nullptr) {
        s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createGfObjBladeByPcID(name, id, option);
    }
    s_createdObj = nullptr;
    return 0;
}

// evt_setup.pcPartyIn
static int fn_7100663F28(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgOmitChk(pThread, 3) ? 0 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    unsigned int option2 = vmArgOmitChk(pThread, 4) ? 0 : vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    if (s_createdObj == nullptr) {
        s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createGfObjPartyIn(name, static_cast<event::CHARA_TYPE>(1), id, option, option2);
    }
    s_createdObj = nullptr;
    return 0;
}

// evt_setup.bladePartyIn
static int fn_710066407C(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgOmitChk(pThread, 3) ? 0 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    if (s_createdObj == nullptr) {
        s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createGfObjPartyIn(name, static_cast<event::CHARA_TYPE>(2), id, option, 0);
    }
    s_createdObj = nullptr;
    return 0;
}

// evt_setup.npcPartyIn
static int fn_710066419C(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgOmitChk(pThread, 3) ? 0 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    if (s_createdObj == nullptr) {
        s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createGfObjPartyIn(name, static_cast<event::CHARA_TYPE>(3), id, option, 0);
    }
    s_createdObj = nullptr;
    return 0;
}

// evt_setup.pcsev
static int fn_71006642BC(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgOmitChk(pThread, 3) ? 0 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    if (s_createdObj == nullptr) {
        s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createGfObj(name, static_cast<event::CHARA_TYPE>(1), id, option, 0);
    }
    s_createdObj = nullptr;
    return 0;
}

// evt_setup.blsev
static int fn_71006643DC(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgOmitChk(pThread, 3) ? 0 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    if (s_createdObj == nullptr) {
        s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createGfObj(name, static_cast<event::CHARA_TYPE>(2), id, option, 0);
    }
    s_createdObj = nullptr;
    return 0;
}

// evt_setup.npsev
static int fn_71006644FC(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgOmitChk(pThread, 3) ? 0 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    if (s_createdObj == nullptr) {
        s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createGfObj(name, static_cast<event::CHARA_TYPE>(3), id, option, 0);
    }
    s_createdObj = nullptr;
    return 0;
}

// evt_setup.ensev
static int fn_710066461C(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgOmitChk(pThread, 3) ? 0 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    if (s_createdObj == nullptr) {
        s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createGfObj(name, static_cast<event::CHARA_TYPE>(5), id, option, 0);
    }
    s_createdObj = nullptr;
    return 0;
}

// evt_setup.cs
static int fn_710066473C(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    const char* model = vmArgStringGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgOmitChk(pThread, 3) ? 0 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    unsigned int option2 = vmArgOmitChk(pThread, 4) ? 0 : vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    if (model[0] != '\0') {
        if (s_createdObj == nullptr) {
            s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createModel(name, model, option2, option);
        }
        s_createdObj = nullptr;
    }
    return 0;
}

// evt_setup.evpa
static int fn_7100664894(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::FixStr<64> path("event/evpa/jp/");
    path += mm::mtl::Singleton<event::Extend>::getPtr()->filename(name);
    mm::mtl::Singleton<event::ResManager>::getPtr()->loadPack(path.m_str);
    return 0;
}

// evt_setup.motion
static int fn_7100664A1C(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::CharaManager>::getPtr()->loadResource(name);
    return 0;
}

// evt_setup.mdlstm
static int fn_7100664AB4(VMThread* pThread) {
    int frame = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    const char* name = vmArgStringGet(2, vmArgPtrGet(pThread, 2));
    unsigned int id = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    mm::mtl::Singleton<event::CharaManager>::getPtr()->loadMdlstream(static_cast<float>(frame), name, id);
    return 0;
}

// evt_setup.pcstm
static int fn_7100664B98(VMThread* pThread) {
    int frame = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    mm::mtl::Singleton<event::CharaManager>::getPtr()->loadMdlstream(static_cast<float>(frame), static_cast<event::CHARA_TYPE>(1), id, option);
    return 0;
}

// evt_setup.blstm
static int fn_7100664C80(VMThread* pThread) {
    int frame = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    mm::mtl::Singleton<event::CharaManager>::getPtr()->loadMdlstream(static_cast<float>(frame), static_cast<event::CHARA_TYPE>(2), id, option);
    return 0;
}

// evt_setup.npstm
static int fn_7100664D68(VMThread* pThread) {
    int frame = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    mm::mtl::Singleton<event::CharaManager>::getPtr()->loadMdlstream(static_cast<float>(frame), static_cast<event::CHARA_TYPE>(3), id, option);
    return 0;
}

// evt_setup.enstm
static int fn_7100664E50(VMThread* pThread) {
    int frame = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    unsigned int option = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    mm::mtl::Singleton<event::CharaManager>::getPtr()->loadMdlstream(static_cast<float>(frame), static_cast<event::CHARA_TYPE>(5), id, option);
    return 0;
}

// evt_setup.cammotion
static int fn_7100664F38(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::CamManager>::getPtr()->loadResource(name);
    return 0;
}

// evt_setup.camera
static int fn_7100664FD0(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    if (s_createdObj == nullptr) {
        s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createCamera(name, id);
    }
    s_createdObj = nullptr;
    return 0;
}

// evt_setup.effmotion
static int fn_71006650A8(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::EffectManager>::getPtr()->loadResource(name);
    return 0;
}

// evt_setup.effect
static int fn_7100665140(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    if (s_createdObj == nullptr) {
        s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createEffect(name);
    }
    s_createdObj = nullptr;
    return 0;
}

// evt_setup.lgtmotion
static int fn_71006651F4(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::LightManager>::getPtr()->loadResource(name);
    return 0;
}

// evt_setup.light
static int fn_710066528C(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    if (s_createdObj == nullptr) {
        s_createdObj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->createLight(name, id);
    }
    s_createdObj = nullptr;
    return 0;
}

// evt_setup.se
static int fn_7100665364(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::SeManager>::getPtr()->load(name);
    return 0;
}

// evt_setup.focal
static int fn_71006653FC(VMThread* pThread) {
    int focal = vmArgBoolGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::CamManager>::getPtr()->setFocal(focal != 0);
    return 0;
}

// evt_setup.offsetSrc
static int fn_7100665498(VMThread* pThread) {
    int x = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int y = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int z = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int angle = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    bool flag = vmArgOmitChk(pThread, 5) ? false : vmArgBoolGet(5, vmArgPtrGet(pThread, 5)) != 0;
    // millimetres to metres, thousandths of a degree to radians
    mm::mtl::Singleton<event::DataManager>::getPtr()->setOffsetSrc(mm::Vec3(x * 0.001f, y * 0.001f, z * 0.001f),
                                                          angle * 0.001f * 0.017453292f, flag);
    return 0;
}

// evt_setup.offsetDes
static int fn_710066561C(VMThread* pThread) {
    int x = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int y = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int z = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int angle = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    bool flag = vmArgOmitChk(pThread, 5) ? false : vmArgBoolGet(5, vmArgPtrGet(pThread, 5)) != 0;
    // millimetres to metres, thousandths of a degree to radians
    mm::mtl::Singleton<event::DataManager>::getPtr()->setOffsetDes(mm::Vec3(x * 0.001f, y * 0.001f, z * 0.001f),
                                                          angle * 0.001f * 0.017453292f, flag);
    return 0;
}

// evt_setup.keyframe
static int fn_71006657A0(VMThread* pThread) {
    int frame = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::FrameManager>::getPtr()->addKeyFrame(static_cast<float>(frame), false);
    return 0;
}

// evt_setup.camframe
static int fn_710066583C(VMThread* pThread) {
    int frame = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::FrameManager>::getPtr()->addKeyFrame(static_cast<float>(frame), true);
    return 0;
}

// evt_setup.setSeamlessReadPos
static int fn_71006658D8(VMThread* pThread) {
    int x = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int y = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int z = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    event::PosAxis pos(2, x * 0.001f, y * 0.001f, z * 0.001f);
    mm::mtl::Singleton<event::SeamlessManager>::getPtr()->addFirstSeamPoint(
        mm::mtl::PtrSingleton<event::Manager>::sys()->m_sceneName.m_str, pos);
    return 0;
}

// evt_setup.setSeamlessReadAxis
static int fn_71006659F4(VMThread* pThread) {
    unsigned int type = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int x = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int y = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int z = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    event::PosAxis pos(type, x * 0.001f, y * 0.001f, z * 0.001f);
    mm::mtl::Singleton<event::SeamlessManager>::getPtr()->addFirstSeamPoint(
        mm::mtl::PtrSingleton<event::Manager>::sys()->m_sceneName.m_str, pos);
    return 0;
}

// The evt_setup plugin's table. Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B73698).
static VMPluginFunc s_evtsetupPlugin[] = {
    {"talk", fn_710066332C},
    {"walk", fn_71006633E0},
    {"pc", fn_71006634F8},
    {"blade", fn_710066364C},
    {"npc", fn_710066376C},
    {"en", fn_710066388C},
    {"model", fn_71006639AC},
    {"pcByWalk", fn_7100663AC8},
    {"pcByBlade", fn_7100663BE0},
    {"bladeByWalk", fn_7100663CF8},
    {"bladeByPc", fn_7100663E10},
    {"pcPartyIn", fn_7100663F28},
    {"bladePartyIn", fn_710066407C},
    {"npcPartyIn", fn_710066419C},
    {"pcsev", fn_71006642BC},
    {"blsev", fn_71006643DC},
    {"npsev", fn_71006644FC},
    {"ensev", fn_710066461C},
    {"cs", fn_710066473C},
    {"evpa", fn_7100664894},
    {"motion", fn_7100664A1C},
    {"mdlstm", fn_7100664AB4},
    {"pcstm", fn_7100664B98},
    {"blstm", fn_7100664C80},
    {"npstm", fn_7100664D68},
    {"enstm", fn_7100664E50},
    {"cammotion", fn_7100664F38},
    {"camera", fn_7100664FD0},
    {"effmotion", fn_71006650A8},
    {"effect", fn_7100665140},
    {"lgtmotion", fn_71006651F4},
    {"light", fn_710066528C},
    {"se", fn_7100665364},
    {"focal", fn_71006653FC},
    {"offsetSrc", fn_7100665498},
    {"offsetDes", fn_710066561C},
    {"keyframe", fn_71006657A0},
    {"camframe", fn_710066583C},
    {"setSeamlessReadPos", fn_71006658D8},
    {"setSeamlessReadAxis", fn_71006659F4},
    {nullptr, nullptr},
};

void pluginEvtSetupRegist() {
    vmPluginRegist("evt_setup", s_evtsetupPlugin);
}

// evt_status.judge
static int fn_7100665B40(VMThread* pThread) {
    int type = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int param1 = vmArgOmitChk(pThread, 2) ? 0 : vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int param2 = vmArgOmitChk(pThread, 3) ? 0 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int param3 = vmArgOmitChk(pThread, 4) ? 0 : vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    int param4 = vmArgOmitChk(pThread, 5) ? 0 : vmArgIntGet(5, vmArgPtrGet(pThread, 5));
    bool result;
    if (!mm::mtl::Singleton<event::StatusManager>::getPtr()->judge(static_cast<EVT_judge>(type), param1, param2, param3,
                                                                   param4, result)) {
        vmWaitModeSet(pThread);
    }
    vmRetBoolSet(pThread, result);
    return 1;
}

// evt_status.change
static int fn_7100665D10(VMThread* pThread) {
    int type = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int param1 = vmArgOmitChk(pThread, 2) ? 0 : vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int param2 = vmArgOmitChk(pThread, 3) ? 0 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int param3 = vmArgOmitChk(pThread, 4) ? 0 : vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    int param4 = vmArgOmitChk(pThread, 5) ? 0 : vmArgIntGet(5, vmArgPtrGet(pThread, 5));
    const char* name = vmArgOmitChk(pThread, 6) ? "" : vmArgStringGet(6, vmArgPtrGet(pThread, 6));
    bool done = mm::mtl::Singleton<event::StatusManager>::getPtr()->change(static_cast<EVT_change>(type), param1, param2,
                                                                           param3, param4, name);
    gf::GfQuestManager::requestOrderQuestForce();
    if (!done) {
        vmWaitModeSet(pThread);
    }
    return 0;
}

// evt_status.getLeader
static int fn_7100665EF8(VMThread* pThread) {
    unsigned int id = mm::mtl::Singleton<event::ObjectPartyList>::getPtr()->getLeaderDriverId();
    if (gf::GfGameManager::isGameTypeIra()) {
        // drivers 17-25 are the script's 1-9; the rest count as 1
        static const unsigned int table[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        if (id < 26) {
            id = table[id];
        }
        if (id < 1 || id > 9) {
            id = 1;
        }
    } else {
        static const unsigned int table[] = {0, 1, 2, 3, 4, 0, 5};
        if (id < 7) {
            id = table[id];
        }
        if (id < 1 || id > 5) {
            id = 1;
        }
    }
    vmRetIntSet(pThread, id);
    return 1;
}

// evt_status.getPartner
static int fn_7100665FD8(VMThread* pThread) {
    unsigned int bladeId = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    unsigned int id = mm::mtl::Singleton<event::StatusManager>::getPtr()->getDriverByBladeId(bladeId);
    if (gf::GfGameManager::isGameTypeIra()) {
        id = 1;
    } else {
        static const unsigned int table[] = {0, 1, 2, 3, 0, 0, 4};
        if (id < 7) {
            id = table[id];
        }
        if (id < 1 || id > 4) {
            id = 1;
        }
    }
    vmRetIntSet(pThread, id);
    return 1;
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B73928).
static VMPluginFunc s_evtstatusPlugin[] = {
    {"judge", fn_7100665B40},
    {"change", fn_7100665D10},
    {"getLeader", fn_7100665EF8},
    {"getPartner", fn_7100665FD8},
    {nullptr, nullptr},
};

void pluginEvtStatusRegist() {
    vmPluginRegist("evt_status", s_evtstatusPlugin);
}


// evt_text.seamVoice
static int fn_71006660E8(VMThread* pThread) {
    int frame = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    const char* name = vmArgStringGet(2, vmArgPtrGet(pThread, 2));
    const char* voice = vmArgOmitChk(pThread, 3) ? "" : vmArgStringGet(3, vmArgPtrGet(pThread, 3));
    if (mm::mtl::PtrSingleton<event::Manager>::sys()->checkLanguageMode()) {
        if (*voice != '\0') {
            mm::mtl::Singleton<event::VoiceManager>::getPtr()->preload(frame, voice);
        } else if (*name != '\0') {
            mm::mtl::Singleton<event::VoiceManager>::getPtr()->preloadAuto(frame, name);
        }
    }
    return 0;
}

// evt_text.play
static int fn_7100666274(VMThread* pThread) {
    // slotN: the value for the command Param's slot N (what each means is not known; the names are not the original's)
    const char* text = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    int slot1 = vmArgOmitChk(pThread, 2) ? -1 : vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    float slot2 = vmArgOmitChk(pThread, 3) ? 30.0f : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    float slot3 = vmArgOmitChk(pThread, 4) ? 0.0f : vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    float slot4 = vmArgOmitChk(pThread, 5) ? 0.0f : vmArgIntGet(5, vmArgPtrGet(pThread, 5));
    int slot5 = vmArgOmitChk(pThread, 6) ? 0 : vmArgIntGet(6, vmArgPtrGet(pThread, 6));
    if (mm::mtl::PtrSingleton<event::Manager>::sys()->checkLanguageMode()) {
        event::Param param;
        param.val(0).setStr(text);
        param.val(1).setS32(slot1);
        param.val(2).setF32(slot2);
        param.val(3).setF32(slot3);
        param.val(4).setF32(slot4);
        param.val(5).setS32(slot5);
        mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptPlayText::exec, param);
    }
    return 0;
}

// The evt_text plugin's table. Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B73978).
static VMPluginFunc s_evttextPlugin[] = {
    {"seamVoice", fn_71006660E8},
    {"play", fn_7100666274},
    {nullptr, nullptr},
};

void pluginEvtTextRegist() {
    vmPluginRegist("evt_text", s_evttextPlugin);
}
