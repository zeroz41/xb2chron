// Script VM plugins of this unit (their tables, entries and Regist functions). The entries are static and nothing
// names them: they keep placeholder fn_ names. Plugins not written yet: evt_status, evt_text, evt_movie, evt_ui, pt, ui
// (and ScriptPlayText::exec, ocThreadRegist).
#include "vm/yvm2.h"
#include "classes/mm/mtl/Singleton.h"
#include "classes/event/CamManager.h"
#include "classes/event/CharaManager.h"
#include "classes/event/DataManager.h"
#include "classes/event/EffectManager.h"
#include "classes/event/Extend.h"
#include "classes/event/FrameManager.h"
#include "classes/event/HideManager.h"
#include "classes/event/LightManager.h"
#include "classes/event/Manager.h"
#include "classes/event/ObjectManager.h"
#include "classes/event/PosAxis.h"
#include "classes/event/ResManager.h"
#include "classes/event/SeManager.h"
#include "classes/event/SeamlessManager.h"
#include "classes/event/VoiceManager.h"
#include "classes/event/VolumeManager.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfFieldGmkTutorial.h"
#include "classes/gf/GfFieldTime.h"
#include "classes/gf/GfFieldWeather.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfGameEvent.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfManager.h"
#include "classes/gf/GfMenuFade.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfWeapon.h"
#include "classes/gf/SCOM_ADD_MONEY.h"
#include "classes/gf/SCOM_SET_FLAG.h"
#include "classes/gf/ScriptCamera.h"
#include "classes/gf/ShipRollPlugin.h"
#include "classes/gmk/GmkElevator.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/GfDataBlade.h"
#include "gf/GfItemUtil.h"
#include "gf/GfPlayFactory.h"
#include "gf/GfReqCommand.h"
#include "gf/ParamReturnTitle.h"
#include "mm/Col4.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixStr.h"

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

static VMPluginFunc s_gmkPlugin[] = {
    {"getStartId", fn_710066978C},
    {"openPortal", fn_71006697CC},
    {nullptr, nullptr},
};

void pluginGmkRegist() {
    vmPluginRegist("gmk", s_gmkPlugin);
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
