// Script VM plugins btl_ai, deb, evt, evt_bgm, evt_cam, evt_chara, evt_eff, evt_env and evt_ex (their tables, entries
// and Regist functions). The entries are static and nothing names them: they keep placeholder fn_ names.
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

// btl_ai.aiSize
static int fn_71006576E0(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    vmRetIntSet(pThread, ai::AiManager::getPtr()->getNumFromId(id));
    return 1;
}

// btl_ai.getTargetPlayerId
static int fn_71006577E0(VMThread* pThread) {
    vmRetIntSet(pThread, btl::Utility::AI_GetTargetedCharacterID(btl::Utility::GetLeader()));
    return 1;
}

// btl_ai.getBattleEnemyNum
static int fn_7100657828(VMThread* pThread) {
    vmRetIntSet(pThread, btl::Utility::AI_GetEnemyNum());
    return 1;
}

// btl_ai.getBattlePcNum
static int fn_710065786C(VMThread* pThread) {
    vmRetIntSet(pThread, btl::Utility::AI_GetPlayerNum());
    return 1;
}

// btl_ai.getTargetPlayerNum
static int fn_71006578B0(VMThread* pThread) {
    vmRetIntSet(pThread, btl::Utility::AI_GetAimCharacterNum(btl::Utility::GetLeader()));
    return 1;
}

// btl_ai.getIdByStamp
static int fn_71006578F8(VMThread* pThread) {
    vmRetIntSet(pThread, btl::Utility::AI_GetStampCharacterID(vmArgIntGet(1, vmArgPtrGet(pThread, 1))));
    return 1;
}

// btl_ai.getHpRateById
static int fn_7100657950(VMThread* pThread) {
    vmRetFixedSet(pThread, btl::Utility::AI_GetHpPercent(btl::Utility::AI_GetCharacterHandle(vmArgIntGet(1, vmArgPtrGet(pThread, 1)))));
    return 1;
}

// btl_ai.getLevelById
static int fn_71006579AC(VMThread* pThread) {
    vmRetIntSet(pThread, btl::Utility::AI_GetLevel(btl::Utility::AI_GetCharacterHandle(vmArgIntGet(1, vmArgPtrGet(pThread, 1)))));
    return 1;
}

// btl_ai.getElemById
static int fn_7100657A08(VMThread* pThread) {
    vmRetIntSet(pThread, btl::Utility::AI_GetAttribute(btl::Utility::AI_GetCharacterHandle(vmArgIntGet(1, vmArgPtrGet(pThread, 1)))));
    return 1;
}

// btl_ai.getVoiceCode
static int fn_7100657A64(VMThread* pThread) {
    vmRetIntSet(pThread, btl::Utility::AI_GetVoiceCode(btl::Utility::AI_GetCharacterHandle(vmArgIntGet(1, vmArgPtrGet(pThread, 1)))));
    return 1;
}

// btl_ai.getUsingArtsEnemyNum
static int fn_7100657AC0(VMThread* pThread) {
    vmRetIntSet(pThread, btl::Utility::AI_GetArtsEnemyNum());
    return 1;
}

// btl_ai.getUsingArtsPcNum
static int fn_7100657B04(VMThread* pThread) {
    vmRetIntSet(pThread, btl::Utility::AI_GetArtsPlayerNum());
    return 1;
}

// btl_ai.getElemComboStage
static int fn_7100657B48(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    unsigned char* bdat = gf::GfDataBdat::getFP(0x23);
    int top = Bdat::getIdTop(bdat);
    int count = Bdat::getIdCount(bdat);
    int value = -1;
    if (top <= id && id < top + count) {
        value = (unsigned char)Bdat::getValCheck(bdat, "ComboStage", id, 1);
    }
    vmRetIntSet(pThread, value);
    return 1;
}

// btl_ai.getElemComboAtr
static int fn_7100657BF8(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    unsigned char* bdat = gf::GfDataBdat::getFP(0x23);
    int top = Bdat::getIdTop(bdat);
    int count = Bdat::getIdCount(bdat);
    int value = -1;
    if (top <= id && id < top + count) {
        value = (unsigned char)Bdat::getValCheck(bdat, "Atr", id, 1);
    }
    vmRetIntSet(pThread, value);
    return 1;
}

// btl_ai.getElementalEffect
static int fn_7100657CA8(VMThread* pThread) {
    vmRetIntSet(pThread, btl::Utility::GetElementalEffectID());
    return 1;
}

// btl_ai.getKillEnemyNum
static int fn_7100657CEC(VMThread* pThread) {
    vmRetIntSet(pThread, btl::Utility::AI_EnemyKillNum());
    return 1;
}

// btl_ai.getPartyGaugeNum
static int fn_7100657D30(VMThread* pThread) {
    vmRetFixedSet(pThread, btl::Utility::fn_71000152D0());
    return 1;
}

// btl_ai.getEnemySirenGaugeRatio
static int fn_7100657D74(VMThread* pThread) {
    vmRetFixedSet(pThread, btl::Utility::fn_710001530C());
    return 1;
}

// btl_ai.addEnemySirenGaugeRatio
static int fn_7100657DB8(VMThread* pThread) {
    btl::Utility::fn_7100015320(vmArgFixedGet(1, vmArgPtrGet(pThread, 1)));
    vmRetFixedSet(pThread, btl::Utility::fn_710001530C());
    return 1;
}

// btl_ai.getWhiteSirenLevel
static int fn_7100657E14(VMThread* pThread) {
    vmRetIntSet(pThread, btl::Utility::fn_7100015334(1));
    return 1;
}

// btl_ai.getBlackSirenLevel
static int fn_7100657E5C(VMThread* pThread) {
    vmRetIntSet(pThread, btl::Utility::fn_7100015334(0));
    return 1;
}

// btl_ai.getChallengeID
static int fn_7100657EA4(VMThread* pThread) {
    vmRetIntSet(pThread, btl::Utility::fn_710001535C());
    return 1;
}

// btl_ai.isDeadById
static int fn_7100657EE8(VMThread* pThread) {
    vmRetBoolSet(pThread, btl::Utility::AI_CheckState(btl::Utility::AI_GetCharacterHandle(vmArgIntGet(1, vmArgPtrGet(pThread, 1))), btl::Utility::CHECK_STATE(3), 0));
    return 1;
}

// btl_ai.isAngryById
static int fn_7100657F50(VMThread* pThread) {
    vmRetBoolSet(pThread, btl::Utility::AI_IsAngry(btl::Utility::AI_GetCharacterHandle(vmArgIntGet(1, vmArgPtrGet(pThread, 1)))));
    return 1;
}

// btl_ai.isValidId
static int fn_7100657FB0(VMThread* pThread) {
    vmRetBoolSet(pThread, btl::Utility::AI_IsValidID(vmArgIntGet(1, vmArgPtrGet(pThread, 1))));
    return 1;
}

// btl_ai.isBuff
static int fn_710065800C(VMThread* pThread) {
    int id = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int buff = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    vmRetBoolSet(pThread, btl::Utility::AI_IsBuff(btl::Utility::AI_GetCharacterHandle(id), buff));
    return 1;
}

// btl_ai.isBladeArtsMax
static int fn_710065809C(VMThread* pThread) {
    vmRetBoolSet(pThread, btl::Utility::AI_IsProcSpAttack());
    return 1;
}

// btl_ai.isPartyDriverID
static int fn_71006580E4(VMThread* pThread) {
    vmRetBoolSet(pThread, btl::Utility::AI_IsPartyMember(vmArgIntGet(1, vmArgPtrGet(pThread, 1))));
    return 1;
}

// btl_ai.isBenkeiWeather
static int fn_7100658140(VMThread* pThread) {
    vmRetBoolSet(pThread, btl::Utility::AI_IsBenkeiWeather());
    return 1;
}

// btl_ai.isKillChild
static int fn_7100658188(VMThread* pThread) {
    vmRetBoolSet(pThread, btl::Utility::AI_IsKillChild());
    return 1;
}

// btl_ai.isUseSirenSp
static int fn_71006581D0(VMThread* pThread) {
    vmRetBoolSet(pThread, btl::Utility::fn_71000151EC());
    return 1;
}

// btl_ai.isPause
static int fn_7100658218(VMThread* pThread) {
    vmRetBoolSet(pThread, btl::Utility::fn_710000FB7C());
    return 1;
}

// btl_ai.buttonChallange
static int fn_7100658260(VMThread* pThread) {
    vmRetBoolSet(pThread, btl::Utility::AI_RegisterButtonChallenge(vmArgIntGet(1, vmArgPtrGet(pThread, 1)), false));
    return 1;
}

// btl_ai.getButtonChallangeResult
static int fn_71006582C0(VMThread* pThread) {
    int id = vmArgOmitChk(pThread, 1) ? 0 : vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    (void)id;
    vmRetIntSet(pThread, btl::Utility::AI_GetButtonChallengeResult());
    return 1;
}

// btl_ai.canButtonChallange
static int fn_7100658328(VMThread* pThread) {
    vmRetBoolSet(pThread, btl::Utility::AI_IsEnableButtonChallenge());
    return 1;
}

// btl_ai.rand
static int fn_7100658370(VMThread* pThread) {
    int rate = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    vmRetBoolSet(pThread, rate >= ml::mtRand(100));
    return 1;
}

// btl_ai.rand2
static int fn_71006583DC(VMThread* pThread) {
    int max = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    vmRetIntSet(pThread, (int)ml::mtRand() % max);
    return 1;
}

// btl_ai.setSpAttackRecast
static int fn_7100658440(VMThread* pThread) {
    int driver = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int level = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    bool flag = vmArgOmitChk(pThread, 3) ? false : vmArgBoolGet(3, vmArgPtrGet(pThread, 3)) != 0;
    btl::Utility::AI_SetBladeArtsRecastByLevel(gf::GfGameParty::getHandleDriver(driver, 0), level, flag);
    return 0;
}

// btl_ai.setResistantAttr
static int fn_71006584EC(VMThread* pThread) {
    btl::Utility::AI_SetResistantAttr(vmArgIntGet(1, vmArgPtrGet(pThread, 1)));
    return 0;
}

// btl_ai.setKizunaStage
static int fn_7100658518(VMThread* pThread) {
    int stage = vmArgOmitChk(pThread, 1) ? 6 : vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    bool flag = vmArgOmitChk(pThread, 2) ? false : vmArgBoolGet(2, vmArgPtrGet(pThread, 2)) != 0;
    btl::Utility::fn_7100010DBC(stage, flag);
    return 0;
}

// btl_ai.fullCoolTime
static int fn_71006585A8(VMThread* pThread) {
    btl::Utility::fn_7100010D84();
    return 0;
}

// btl_ai.setBattleEndEnemyCall
static int fn_71006585C0(VMThread* pThread) {
    btl::Utility::fn_7100010DA4(vmArgIntGet(1, vmArgPtrGet(pThread, 1)));
    return 0;
}

VMPluginFunc btl_ai[] = {
    {"aiSize", fn_71006576E0},
    {"getTargetPlayerId", fn_71006577E0},
    {"getBattleEnemyNum", fn_7100657828},
    {"getBattlePcNum", fn_710065786C},
    {"getTargetPlayerNum", fn_71006578B0},
    {"getIdByStamp", fn_71006578F8},
    {"getHpRateById", fn_7100657950},
    {"getLevelById", fn_71006579AC},
    {"getElemById", fn_7100657A08},
    {"getVoiceCode", fn_7100657A64},
    {"getUsingArtsEnemyNum", fn_7100657AC0},
    {"getUsingArtsPcNum", fn_7100657B04},
    {"getElemComboStage", fn_7100657B48},
    {"getElemComboAtr", fn_7100657BF8},
    {"getElementalEffect", fn_7100657CA8},
    {"getKillEnemyNum", fn_7100657CEC},
    {"getPartyGaugeNum", fn_7100657D30},
    {"getEnemySirenGaugeRatio", fn_7100657D74},
    {"addEnemySirenGaugeRatio", fn_7100657DB8},
    {"getWhiteSirenLevel", fn_7100657E14},
    {"getBlackSirenLevel", fn_7100657E5C},
    {"getChallengeID", fn_7100657EA4},
    {"isDeadById", fn_7100657EE8},
    {"isAngryById", fn_7100657F50},
    {"isValidId", fn_7100657FB0},
    {"isBuff", fn_710065800C},
    {"isBladeArtsMax", fn_710065809C},
    {"isPartyDriverID", fn_71006580E4},
    {"isBenkeiWeather", fn_7100658140},
    {"isKillChild", fn_7100658188},
    {"isUseSirenSp", fn_71006581D0},
    {"isPause", fn_7100658218},
    {"buttonChallange", fn_7100658260},
    {"getButtonChallangeResult", fn_71006582C0},
    {"canButtonChallange", fn_7100658328},
    {"rand", fn_7100658370},
    {"rand2", fn_71006583DC},
    {"setSpAttackRecast", fn_7100658440},
    {"setResistantAttr", fn_71006584EC},
    {"setKizunaStage", fn_7100658518},
    {"fullCoolTime", fn_71006585A8},
    {"setBattleEndEnemyCall", fn_71006585C0},
    {nullptr, nullptr},
};

void pluginBtlAiRegist() {
    vmPluginRegist("btl_ai", btl_ai);
}

// deb.put
static int fn_7100658618(VMThread* pThread) {
    return 0;
}

// deb.dummy
static int fn_7100658620(VMThread* pThread) {
    float value = vmArgFixedGet(1, vmArgPtrGet(pThread, 1));
    int sign, integer, frac;
    splitFixed(value, &sign, &integer, &frac);
    return 0;
}

static VMPluginFunc s_debPlugin[] = {
    {"put", fn_7100658618},
    {"dummy", fn_7100658620},
    {nullptr, nullptr},
};

void pluginDebRegist() {
    vmPluginRegist("deb", s_debPlugin);
}

// evt.init
static int fn_7100658674(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    if (!mm::mtl::PtrSingleton<event::Manager>::sys()->init(name)) {
        vmWaitModeSet(pThread);
    }
    return 0;
}

// evt.setupScene
static int fn_71006586C8(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    if (!mm::mtl::PtrSingleton<event::Manager>::sys()->setupScene(name)) {
        vmWaitModeSet(pThread);
    }
    return 0;
}

// evt.setupSceneEnd
static int fn_710065871C(VMThread* pThread) {
    if (!mm::mtl::PtrSingleton<event::Manager>::sys()->setupSceneEnd()) {
        vmWaitModeSet(pThread);
    }
    return 0;
}

// evt.startScene
static int fn_7100658758(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    int no = vmArgOmitChk(pThread, 2) ? 1 : vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    if (!mm::mtl::PtrSingleton<event::Manager>::sys()->startScene(name, no)) {
        vmWaitModeSet(pThread);
    }
    return 0;
}

// evt.startPage
static int fn_71006587EC(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    float frame = vmArgOmitChk(pThread, 2) ? 0.0f : vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int no = vmArgOmitChk(pThread, 3) ? 1 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    if (!mm::mtl::PtrSingleton<event::Manager>::sys()->startPage(name, no, frame)) {
        vmWaitModeSet(pThread);
    }
    return 0;
}

// evt.endScene
static int fn_71006588B8(VMThread* pThread) {
    if (!mm::mtl::PtrSingleton<event::Manager>::sys()->endScene()) {
        vmWaitModeSet(pThread);
    }
    return 0;
}

// evt.end
static int fn_71006588F4(VMThread* pThread) {
    if (!mm::mtl::PtrSingleton<event::Manager>::sys()->end()) {
        vmWaitModeSet(pThread);
    }
    return 0;
}

// evt.wait
static int fn_7100658930(VMThread* pThread) {
    int frame = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    mm::mtl::Singleton<event::FrameManager>::getPtr()->setSkipAbleFrame(frame);
    if (mm::mtl::Singleton<event::FrameManager>::getPtr()->getFrame() < frame) {
        if (mm::mtl::Singleton<event::FrameManager>::getPtr()->getFrame() < mm::mtl::Singleton<event::FrameManager>::getPtr()->getMaxFrame()) {
            vmWaitModeSet(pThread);
        }
    }
    return 0;
}

// evt.print
static int fn_7100658B04(VMThread* pThread) {
    vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    return 0;
}

// evt.beginJP
static int fn_7100658B2C(VMThread* pThread) {
    mm::mtl::PtrSingleton<event::Manager>::sys()->setLanguageMode(true, event::Manager::LANGUAGE_MODE_JP);
    return 0;
}

// evt.endJP
static int fn_7100658B58(VMThread* pThread) {
    mm::mtl::PtrSingleton<event::Manager>::sys()->setLanguageMode(false, event::Manager::LANGUAGE_MODE_NONE);
    return 0;
}

// evt.beginUS
static int fn_7100658B84(VMThread* pThread) {
    mm::mtl::PtrSingleton<event::Manager>::sys()->setLanguageMode(true, event::Manager::LANGUAGE_MODE_US);
    return 0;
}

// evt.endUS
static int fn_7100658BB0(VMThread* pThread) {
    mm::mtl::PtrSingleton<event::Manager>::sys()->setLanguageMode(false, event::Manager::LANGUAGE_MODE_NONE);
    return 0;
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B72F18).
static VMPluginFunc s_evtPlugin[] = {
    {"init", fn_7100658674},
    {"setupScene", fn_71006586C8},
    {"setupSceneEnd", fn_710065871C},
    {"startScene", fn_7100658758},
    {"startPage", fn_71006587EC},
    {"endScene", fn_71006588B8},
    {"end", fn_71006588F4},
    {"wait", fn_7100658930},
    {"print", fn_7100658B04},
    {"beginJP", fn_7100658B2C},
    {"endJP", fn_7100658B58},
    {"beginUS", fn_7100658B84},
    {"endUS", fn_7100658BB0},
    {nullptr, nullptr},
};

void pluginEvtRegist() {
    vmPluginRegist("evt", s_evtPlugin);
}

// evt_bgm.play
static int fn_7100658BF0(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    float a3 = vmArgOmitChk(pThread, 3) ? 1.0f : (float)vmArgIntGet(3, vmArgPtrGet(pThread, 3)) * 0.01f;
    float a4 = vmArgOmitChk(pThread, 4) ? 0.0f : (float)vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    float a5 = vmArgOmitChk(pThread, 5) ? 0.0f : (float)vmArgIntGet(5, vmArgPtrGet(pThread, 5));
    float a6 = vmArgOmitChk(pThread, 6) ? 0.0f : (float)vmArgIntGet(6, vmArgPtrGet(pThread, 6));
    float a7 = vmArgOmitChk(pThread, 7) ? 0.0f : (float)vmArgIntGet(7, vmArgPtrGet(pThread, 7));
    float a8 = vmArgOmitChk(pThread, 8) ? 0.0f : (float)vmArgIntGet(8, vmArgPtrGet(pThread, 8));
    int a9 = vmArgOmitChk(pThread, 9) ? 0 : vmArgBoolGet(9, vmArgPtrGet(pThread, 9));
    float a10 = vmArgOmitChk(pThread, 10) ? 0.0f : (float)vmArgIntGet(10, vmArgPtrGet(pThread, 10));
    mm::mtl::Singleton<event::BgmManager>::getPtr()->play(name, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    return 0;
}

// evt_bgm.changeVolume
static int fn_7100658EA4(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    mm::mtl::Singleton<event::BgmManager>::getPtr()->changeVolume(a1 * 0.01f, a2);
    return 0;
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B72FF8).
static VMPluginFunc s_evtbgmPlugin[] = {
    {"play", fn_7100658BF0},
    {"changeVolume", fn_7100658EA4},
    {nullptr, nullptr},
};

void pluginEvtBgmRegist() {
    vmPluginRegist("evt_bgm", s_evtbgmPlugin);
}

// evt_cam.playMotion
static int fn_7100658F88(VMThread* pThread) {
    const char* a1 = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    float a2 = vmArgOmitChk(pThread, 2) ? 0.0f : vmArgIntGet(2, vmArgPtrGet(pThread, 2)) * 0.001f;
    float a3 = vmArgOmitChk(pThread, 3) ? 0.0f : vmArgIntGet(3, vmArgPtrGet(pThread, 3)) * 0.001f;
    float a4 = vmArgOmitChk(pThread, 4) ? 0.0f : vmArgIntGet(4, vmArgPtrGet(pThread, 4)) * 0.001f;
    event::Param param;
    param.val(0).setStr(a1);
    param.val(1).setF32(a2);
    param.val(2).setF32(a3);
    param.val(3).setF32(a4);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCamMotion::exec, param);
    return 0;
}

// evt_cam.setPos
static int fn_71006591C0(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    event::Param param;
    param.val(0).setS32(a1);
    param.val(1).setF32(a2 * 0.001f);
    param.val(2).setF32(a3 * 0.001f);
    param.val(3).setF32(a4 * 0.001f);
    param.val(4).setS32(1);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCamPos::exec, param);
    return 0;
}

// evt_cam.movePos
static int fn_71006593C0(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    int a5 = vmArgIntGet(5, vmArgPtrGet(pThread, 5));
    int a6 = vmArgOmitChk(pThread, 6) ? 1 : vmArgIntGet(6, vmArgPtrGet(pThread, 6));
    event::Param param;
    param.val(0).setS32(a1);
    param.val(1).setF32(a2 * 0.001f);
    param.val(2).setF32(a3 * 0.001f);
    param.val(3).setF32(a4 * 0.001f);
    param.val(4).setF32(a5);
    param.val(5).setS32(a6);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCamMovePos::exec, param);
    return 0;
}

// evt_cam.setTar
static int fn_710065962C(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    event::Param param;
    param.val(0).setS32(a1);
    if (mm::mtl::Singleton<event::DataManager>::getPtr()->checkRadianTar(a1)) {
        param.val(1).setF32((float)a2 * 0.001f * 0.017453292f);
        param.val(2).setF32((float)a3 * 0.001f * 0.017453292f);
        param.val(3).setF32((float)a4 * 0.001f * 0.017453292f);
    } else {
        param.val(1).setF32((float)a2 * 0.001f);
        param.val(2).setF32((float)a3 * 0.001f);
        param.val(3).setF32((float)a4 * 0.001f);
    }
    param.val(4).setS32(1);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCamTar::exec, param);
    return 0;
}

// evt_cam.moveTar
static int fn_71006598E0(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    int a5 = vmArgIntGet(5, vmArgPtrGet(pThread, 5));
    int a6 = vmArgOmitChk(pThread, 6) ? 1 : vmArgIntGet(6, vmArgPtrGet(pThread, 6));
    event::Param param;
    param.val(0).setS32(a1);
    if (mm::mtl::Singleton<event::DataManager>::getPtr()->checkRadianTar(a1)) {
        param.val(1).setF32((float)a2 * 0.001f * 0.017453292f);
        param.val(2).setF32((float)a3 * 0.001f * 0.017453292f);
        param.val(3).setF32((float)a4 * 0.001f * 0.017453292f);
    } else {
        param.val(1).setF32((float)a2 * 0.001f);
        param.val(2).setF32((float)a3 * 0.001f);
        param.val(3).setF32((float)a4 * 0.001f);
    }
    param.val(4).setF32(a5);
    param.val(5).setS32(a6);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCamMoveTar::exec, param);
    return 0;
}

// evt_cam.setFov
static int fn_7100659C00(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    event::Param param;
    param.val(0).setF32(a1 * 0.001f);
    param.val(1).setS32(1);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCamFov::exec, param);
    return 0;
}

// evt_cam.moveFov
static int fn_7100659D54(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgOmitChk(pThread, 3) ? 1 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    event::Param param;
    param.val(0).setF32(a1 * 0.001f);
    param.val(1).setF32(a2);
    param.val(2).setS32(a3);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCamMoveFov::exec, param);
    return 0;
}

// evt_cam.setRotZ
static int fn_7100659F14(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    event::Param param;
    param.val(0).setF32(a1 * 0.001f);
    param.val(1).setS32(1);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCamRotZ::exec, param);
    return 0;
}

// evt_cam.moveRotZ
static int fn_710065A068(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgOmitChk(pThread, 3) ? 1 : vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    event::Param param;
    param.val(0).setF32(a1 * 0.001f);
    param.val(1).setF32(a2);
    param.val(2).setS32(a3);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCamMoveRotZ::exec, param);
    return 0;
}

// evt_cam.setNearfar
static int fn_710065A228(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    event::Param param;
    param.val(0).setS32(a1);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCamNearfar::exec, param);
    return 0;
}

// evt_cam.setCut
static int fn_710065A35C(VMThread* pThread) {
    const char* a1 = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    event::Param param;
    param.val(0).setStr(a1);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCamCut::exec, param);
    return 0;
}

// evt_cam.followPos
static int fn_710065A490(VMThread* pThread) {
    int a1 = vmArgBoolGet(1, vmArgPtrGet(pThread, 1));
    event::Param param;
    param.val(0).setBool(a1 != 0);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCamFollowPos::exec, param);
    return 0;
}

// evt_cam.followTar
static int fn_710065A5C8(VMThread* pThread) {
    int a1 = vmArgBoolGet(1, vmArgPtrGet(pThread, 1));
    event::Param param;
    param.val(0).setBool(a1 != 0);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCamFollowTar::exec, param);
    return 0;
}

// evt_cam.setSeamlessReadPos
static int fn_710065A700(VMThread* pThread) {
    int frame = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int x = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int y = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int z = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    event::PosAxis pos(2, x * 0.001f, y * 0.001f, z * 0.001f);
    mm::mtl::Singleton<event::SeamlessManager>::getPtr()->addSeamPoint(frame, pos);
    return 0;
}

// evt_cam.setSeamlessReadAxis
static int fn_710065A82C(VMThread* pThread) {
    int frame = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    unsigned int type = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int x = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int y = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    int z = vmArgIntGet(5, vmArgPtrGet(pThread, 5));
    event::PosAxis pos(type, x * 0.001f, y * 0.001f, z * 0.001f);
    mm::mtl::Singleton<event::SeamlessManager>::getPtr()->addSeamPoint(frame, pos);
    return 0;
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B73028).
static VMPluginFunc s_evtcamPlugin[] = {
    {"playMotion", fn_7100658F88},
    {"setPos", fn_71006591C0},
    {"movePos", fn_71006593C0},
    {"setTar", fn_710065962C},
    {"moveTar", fn_71006598E0},
    {"setFov", fn_7100659C00},
    {"moveFov", fn_7100659D54},
    {"setRotZ", fn_7100659F14},
    {"moveRotZ", fn_710065A068},
    {"setNearfar", fn_710065A228},
    {"setCut", fn_710065A35C},
    {"followPos", fn_710065A490},
    {"followTar", fn_710065A5C8},
    {"setSeamlessReadPos", fn_710065A700},
    {"setSeamlessReadAxis", fn_710065A82C},
    {nullptr, nullptr},
};

void pluginEvtCamRegist() {
    vmPluginRegist("evt_cam", s_evtcamPlugin);
}

// evt_chara.setPos
static int fn_710065B23C(VMThread* pThread) {
    int type = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int x = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int y = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int z = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    event::ObjectList* list = mm::mtl::Singleton<event::ObjectManager>::getPtr()->m_current;
    event::Object* obj = list != nullptr ? list->m_active : nullptr;
    if (event::ScriptUtil::getObjType(obj) == 2) {
        event::PosAxis axis(type, (float)x * 0.001f, (float)y * 0.001f, (float)z * 0.001f);
        static_cast<event::ObjectChara*>(obj)->setPosAxis(axis);
        static_cast<event::ObjectChara*>(obj)->m_chara->resetDynamics(0);
    }
    return 0;
}

// evt_chara.walkPos
static int fn_710065B3A4(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    int a5 = vmArgOmitChk(pThread, 5) ? 0 : vmArgIntGet(5, vmArgPtrGet(pThread, 5));
    bool a6 = vmArgOmitChk(pThread, 6) ? true : vmArgBoolGet(6, vmArgPtrGet(pThread, 6)) != 0;
    event::Param param;
    param.val(0).setS32(a1);
    param.val(1).setF32(a2 * 0.001f);
    param.val(2).setF32(a3 * 0.001f);
    param.val(3).setF32(a4 * 0.001f);
    param.val(4).setS32(a5);
    param.val(5).setBool(a6);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaWalkPos::exec, param);
    return 0;
}

// evt_chara.linerPos
static int fn_710065B630(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    int a5 = vmArgOmitChk(pThread, 5) ? 0 : vmArgBoolGet(5, vmArgPtrGet(pThread, 5));
    int a6 = vmArgOmitChk(pThread, 6) ? 0 : vmArgIntGet(6, vmArgPtrGet(pThread, 6));
    int a7 = vmArgOmitChk(pThread, 7) ? 1 : vmArgIntGet(7, vmArgPtrGet(pThread, 7));
    event::Param param;
    param.val(0).setS32(a1);
    param.val(1).setF32(a2 * 0.001f);
    param.val(2).setF32(a3 * 0.001f);
    param.val(3).setF32(a4 * 0.001f);
    param.val(4).setBool(a5 != 0);
    param.val(5).setS32(a6);
    param.val(6).setS32(a7);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaLinerPos::exec, param);
    return 0;
}

// evt_chara.setRot
static int fn_710065B90C(VMThread* pThread) {
    int type = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int x = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int y = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int z = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    event::ObjectList* list = mm::mtl::Singleton<event::ObjectManager>::getPtr()->m_current;
    event::Object* obj = list != nullptr ? list->m_active : nullptr;
    if (event::ScriptUtil::getObjType(obj) == 2) {
        event::RotAxis axis(type, (float)x * 0.001f * 0.017453292f, (float)y * 0.001f * 0.017453292f, (float)z * 0.001f * 0.017453292f);
        static_cast<event::ObjectChara*>(obj)->setRotAxis(axis);
        static_cast<event::ObjectChara*>(obj)->m_chara->resetDynamics(0);
    }
    return 0;
}

// evt_chara.turnRot
static int fn_710065BA88(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    int a5 = vmArgOmitChk(pThread, 5) ? 0 : vmArgIntGet(5, vmArgPtrGet(pThread, 5));
    float a6 = vmArgOmitChk(pThread, 6) ? 1.0f : vmArgIntGet(6, vmArgPtrGet(pThread, 6)) * 0.01f;
    event::Param param;
    param.val(0).setS32(a1);
    param.val(1).setF32(a2 * 0.001f * 0.017453292f);
    param.val(2).setF32(a3 * 0.001f * 0.017453292f);
    param.val(3).setF32(a4 * 0.001f * 0.017453292f);
    param.val(4).setS32(a5);
    param.val(5).setF32(a6);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaTurnRot::exec, param);
    return 0;
}

// evt_chara.linerRot
static int fn_710065BD38(VMThread* pThread) {
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
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaLinerRot::exec, param);
    return 0;
}

// evt_chara.setTar
static int fn_710065BFD4(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    int a5 = vmArgIntGet(5, vmArgPtrGet(pThread, 5));
    int a6 = vmArgOmitChk(pThread, 6) ? 0 : vmArgIntGet(6, vmArgPtrGet(pThread, 6));
    int a7 = vmArgOmitChk(pThread, 7) ? 0 : vmArgIntGet(7, vmArgPtrGet(pThread, 7));
    int a8 = vmArgOmitChk(pThread, 8) ? 0 : vmArgBoolGet(8, vmArgPtrGet(pThread, 8));
    float a9 = vmArgOmitChk(pThread, 9) ? -1.0f : (float)vmArgIntGet(9, vmArgPtrGet(pThread, 9));
    float a10 = vmArgOmitChk(pThread, 10) ? -1.0f : (float)vmArgIntGet(10, vmArgPtrGet(pThread, 10));
    event::Param param;
    param.val(0).setS32(a1);
    if (mm::mtl::Singleton<event::DataManager>::getPtr()->checkRadianTar(a1)) {
        param.val(1).setF32((float)a2 * 0.001f * 0.017453292f);
        param.val(2).setF32((float)a3 * 0.001f * 0.017453292f);
        param.val(3).setF32((float)a4 * 0.001f * 0.017453292f);
    } else {
        param.val(1).setF32((float)a2 * 0.001f);
        param.val(2).setF32((float)a3 * 0.001f);
        param.val(3).setF32((float)a4 * 0.001f);
    }
    param.val(4).setF32(a5);
    param.val(5).setS32(a6);
    param.val(6).setS32(a7);
    param.val(7).setF32(a8 ? a9 : -1.0f);
    param.val(8).setF32(a8 ? a10 : -1.0f);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaTgt::exec, param);
    return 0;
}

// evt_chara.setIdle
static int fn_710065C420(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    event::Param param;
    param.val(0).setS32(a1);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaSetIdle::exec, param);
    return 0;
}

// evt_chara.playAction
static int fn_710065C554(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgOmitChk(pThread, 3) ? 1 : vmArgBoolGet(3, vmArgPtrGet(pThread, 3));
    bool a4 = vmArgOmitChk(pThread, 4) ? true : vmArgBoolGet(4, vmArgPtrGet(pThread, 4)) != 0;
    event::Param param;
    param.val(0).setS32(a1);
    param.val(1).setF32(a2);
    param.val(2).setBool(a3 != 0);
    param.val(3).setBool(a4);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaAction::exec, param);
    return 0;
}

// evt_chara.playMotion
static int fn_710065C758(VMThread* pThread) {
    const char* a1 = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgIntGet(3, vmArgPtrGet(pThread, 3));
    float a4 = vmArgOmitChk(pThread, 4) ? 0.0f : vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    event::Param param;
    param.val(0).setStr(a1);
    param.val(1).setF32(a2);
    param.val(2).setF32(a3 * 0.01f);
    param.val(3).setF32(a4);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaMotion::exec, param);
    return 0;
}

// evt_chara.playMotionABC
static int fn_710065C954(VMThread* pThread) {
    const char* a1 = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    const char* a2 = vmArgStringGet(2, vmArgPtrGet(pThread, 2));
    const char* a3 = vmArgStringGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    int a5 = vmArgIntGet(5, vmArgPtrGet(pThread, 5));
    int a6 = vmArgIntGet(6, vmArgPtrGet(pThread, 6));
    int a7 = vmArgOmitChk(pThread, 7) ? 0 : vmArgBoolGet(7, vmArgPtrGet(pThread, 7));
    float a8 = vmArgOmitChk(pThread, 8) ? -1.0f : (float)vmArgIntGet(8, vmArgPtrGet(pThread, 8));
    float a9 = vmArgOmitChk(pThread, 9) ? -1.0f : (float)vmArgIntGet(9, vmArgPtrGet(pThread, 9));
    float a10 = vmArgOmitChk(pThread, 10) ? 0.0f : (float)vmArgIntGet(10, vmArgPtrGet(pThread, 10));
    event::Param param;
    param.val(0).setStr(a1);
    param.val(1).setStr(a2);
    param.val(2).setStr(a3);
    param.val(3).setF32(a4);
    param.val(4).setF32(a5);
    param.val(5).setF32(a6 * 0.01f);
    param.val(6).setF32(a7 ? a8 : -1.0f);
    param.val(7).setF32(a7 ? a9 : -1.0f);
    param.val(8).setF32(a10);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaMotionABC::exec, param);
    return 0;
}

// evt_chara.playHead
static int fn_710065CCCC(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgOmitChk(pThread, 3) ? 1 : vmArgBoolGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgOmitChk(pThread, 4) ? 1 : vmArgBoolGet(4, vmArgPtrGet(pThread, 4));
    int a5 = vmArgOmitChk(pThread, 5) ? 0 : vmArgBoolGet(5, vmArgPtrGet(pThread, 5));
    float a6 = vmArgOmitChk(pThread, 6) ? -1.0f : (float)vmArgIntGet(6, vmArgPtrGet(pThread, 6)) * 0.01f;
    float a7 = vmArgOmitChk(pThread, 7) ? -1.0f : (float)vmArgIntGet(7, vmArgPtrGet(pThread, 7)) * 0.01f;
    event::Param param;
    param.val(0).setS32(a1);
    param.val(1).setF32(a2);
    param.val(2).setBool(a3 != 0);
    param.val(3).setBool(a4 != 0);
    param.val(4).setF32(a5 ? a6 : -1.0f);
    param.val(5).setF32(a5 ? a7 : -1.0f);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaHead::exec, param);
    return 0;
}

// evt_chara.playFacial
static int fn_710065CFCC(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgOmitChk(pThread, 3) ? 0 : vmArgBoolGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgOmitChk(pThread, 4) ? 0 : vmArgIntGet(4, vmArgPtrGet(pThread, 4));
    float a5 = vmArgOmitChk(pThread, 5) ? -1.0f : (float)vmArgIntGet(5, vmArgPtrGet(pThread, 5)) * 0.01f;
    int a6 = vmArgOmitChk(pThread, 6) ? 0 : vmArgBoolGet(6, vmArgPtrGet(pThread, 6));
    int a7 = vmArgOmitChk(pThread, 7) ? 0 : vmArgIntGet(7, vmArgPtrGet(pThread, 7));
    float a8 = vmArgOmitChk(pThread, 8) ? -1.0f : (float)vmArgIntGet(8, vmArgPtrGet(pThread, 8)) * 0.01f;
    int a9 = vmArgOmitChk(pThread, 9) ? 0 : vmArgBoolGet(9, vmArgPtrGet(pThread, 9));
    int a10 = vmArgOmitChk(pThread, 10) ? 0 : vmArgIntGet(10, vmArgPtrGet(pThread, 10));
    float a11 = vmArgOmitChk(pThread, 11) ? -1.0f : (float)vmArgIntGet(11, vmArgPtrGet(pThread, 11)) * 0.01f;
    int a12 = vmArgOmitChk(pThread, 12) ? 0 : vmArgBoolGet(12, vmArgPtrGet(pThread, 12));
    float a13 = vmArgOmitChk(pThread, 13) ? -1.0f : (float)vmArgIntGet(13, vmArgPtrGet(pThread, 13));
    float a14 = vmArgOmitChk(pThread, 14) ? -1.0f : (float)vmArgIntGet(14, vmArgPtrGet(pThread, 14));
    event::Param param;
    param.val(0).setS32(a1);
    param.val(1).setF32(a2);
    param.val(2).setS32(a3 ? a4 : -1);
    param.val(3).setF32(a3 ? a5 : -1.0f);
    param.val(4).setS32(a6 ? a7 : -1);
    param.val(5).setF32(a6 ? a8 : -1.0f);
    param.val(6).setS32(a9 ? a10 : -1);
    param.val(7).setF32(a9 ? a11 : -1.0f);
    param.val(8).setF32(a12 ? a13 : -1.0f);
    param.val(9).setF32(a12 ? a14 : -1.0f);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaFacial::exec, param);
    return 0;
}

// evt_chara.playTalk
static int fn_710065D4C4(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgOmitChk(pThread, 2) ? 0 : vmArgBoolGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgOmitChk(pThread, 3) ? 1 : vmArgBoolGet(3, vmArgPtrGet(pThread, 3));
    int a4 = vmArgOmitChk(pThread, 4) ? 1 : vmArgBoolGet(4, vmArgPtrGet(pThread, 4));
    float a5 = vmArgOmitChk(pThread, 5) ? -1.0f : (float)vmArgIntGet(5, vmArgPtrGet(pThread, 5)) * 0.01f;
    float a6 = vmArgOmitChk(pThread, 6) ? -1.0f : (float)vmArgIntGet(6, vmArgPtrGet(pThread, 6)) * 0.01f;
    int a7 = vmArgOmitChk(pThread, 7) ? 0 : vmArgBoolGet(7, vmArgPtrGet(pThread, 7));
    float a8 = vmArgOmitChk(pThread, 8) ? -1.0f : (float)vmArgIntGet(8, vmArgPtrGet(pThread, 8)) * 0.01f;
    float a9 = vmArgOmitChk(pThread, 9) ? -1.0f : (float)vmArgIntGet(9, vmArgPtrGet(pThread, 9)) * 0.01f;
    event::Param param;
    param.val(0).setF32(a1);
    param.val(1).setBool(a2 ? a3 != 0 : true);
    param.val(2).setBool(a2 ? a4 != 0 : true);
    param.val(3).setF32(a2 ? a5 : -1.0f);
    param.val(4).setF32(a2 ? a6 : -1.0f);
    param.val(5).setF32(a7 ? a8 : -1.0f);
    param.val(6).setF32(a7 ? a9 : -1.0f);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaTalk::exec, param);
    return 0;
}

// evt_chara.playWink
static int fn_710065D890(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    int a3 = vmArgOmitChk(pThread, 3) ? 0 : vmArgBoolGet(3, vmArgPtrGet(pThread, 3));
    float a4 = vmArgOmitChk(pThread, 4) ? 0.0f : (float)vmArgIntGet(4, vmArgPtrGet(pThread, 4)) * 0.01f;
    float a5 = vmArgOmitChk(pThread, 5) ? 0.0f : (float)vmArgIntGet(5, vmArgPtrGet(pThread, 5)) * 0.01f;
    int a6 = vmArgOmitChk(pThread, 6) ? -1 : vmArgIntGet(6, vmArgPtrGet(pThread, 6));
    int a7 = vmArgOmitChk(pThread, 7) ? 1 : vmArgBoolGet(7, vmArgPtrGet(pThread, 7));
    bool a8 = vmArgOmitChk(pThread, 8) ? true : vmArgBoolGet(8, vmArgPtrGet(pThread, 8)) != 0;
    event::Param param;
    param.val(0).setS32(a1);
    param.val(1).setF32(a2);
    param.val(2).setBool(a3 != 0);
    param.val(3).setF32(a3 ? a4 : 0.0f);
    param.val(4).setF32(a3 ? a5 : 0.0f);
    param.val(5).setS32(a6);
    param.val(6).setBool(a7 != 0);
    param.val(7).setBool(a8);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaWink::exec, param);
    return 0;
}

// evt_chara.mount
static int fn_710065DBEC(VMThread* pThread) {
    int a1 = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    const char* a2 = vmArgStringGet(2, vmArgPtrGet(pThread, 2));
    float a3 = vmArgOmitChk(pThread, 3) ? 0.0f : (float)vmArgIntGet(3, vmArgPtrGet(pThread, 3)) * 0.001f;
    float a4 = vmArgOmitChk(pThread, 4) ? 0.0f : (float)vmArgIntGet(4, vmArgPtrGet(pThread, 4)) * 0.001f;
    float a5 = vmArgOmitChk(pThread, 5) ? 0.0f : (float)vmArgIntGet(5, vmArgPtrGet(pThread, 5)) * 0.001f;
    float a6 = vmArgOmitChk(pThread, 6) ? 0.0f : (float)vmArgIntGet(6, vmArgPtrGet(pThread, 6)) * 0.001f * 0.017453292f;
    float a7 = vmArgOmitChk(pThread, 7) ? 0.0f : (float)vmArgIntGet(7, vmArgPtrGet(pThread, 7)) * 0.001f * 0.017453292f;
    float a8 = vmArgOmitChk(pThread, 8) ? 0.0f : (float)vmArgIntGet(8, vmArgPtrGet(pThread, 8)) * 0.001f * 0.017453292f;
    bool fast = mm::mtl::Singleton<event::SkipManager>::getPtr()->isSkipFast();
    if (a1 > 3 && !fast) {
        event::Param param;
        param.val(0).setS32(a1 - 4);
        param.val(1).setStr(a2);
        param.val(2).setF32(a3);
        param.val(3).setF32(a4);
        param.val(4).setF32(a5);
        param.val(5).setF32(a6);
        param.val(6).setF32(a7);
        param.val(7).setF32(a8);
        mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaMount::exec, param);
    }
    return 0;
}

// evt_chara.playFade
static int fn_710065DFE8(VMThread* pThread) {
    int a1 = vmArgBoolGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    event::Param param;
    param.val(0).setBool(a1 != 0);
    param.val(1).setF32(a2);
    mm::mtl::Singleton<event::TodoManager>::getPtr()->add(&event::ScriptCharaFade::exec, param);
    return 0;
}

// evt_chara.playVolumeFade
static int fn_710065E154(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    int a2 = vmArgOmitChk(pThread, 2) ? 1 : vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    float a3 = vmArgOmitChk(pThread, 3) ? 1.0f : vmArgFixedGet(3, vmArgPtrGet(pThread, 3));
    float a4 = vmArgOmitChk(pThread, 4) ? 1.0f : vmArgFixedGet(4, vmArgPtrGet(pThread, 4));
    float a5 = vmArgOmitChk(pThread, 5) ? 1.0f : vmArgFixedGet(5, vmArgPtrGet(pThread, 5));
    float a6 = vmArgOmitChk(pThread, 6) ? 0.0f : vmArgFixedGet(6, vmArgPtrGet(pThread, 6));
    float a7 = vmArgOmitChk(pThread, 7) ? 0.0f : vmArgFixedGet(7, vmArgPtrGet(pThread, 7));
    float a8 = vmArgOmitChk(pThread, 8) ? 0.0f : vmArgFixedGet(8, vmArgPtrGet(pThread, 8));
    float a9 = vmArgOmitChk(pThread, 9) ? 0.5f : vmArgFixedGet(9, vmArgPtrGet(pThread, 9));
    float a10 = vmArgOmitChk(pThread, 10) ? 1.0f : vmArgFixedGet(10, vmArgPtrGet(pThread, 10));
    int a11 = vmArgOmitChk(pThread, 11) ? -1 : vmArgIntGet(11, vmArgPtrGet(pThread, 11));
    float a12 = vmArgOmitChk(pThread, 12) ? 0.5f : vmArgFixedGet(12, vmArgPtrGet(pThread, 12));
    event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->searchByName(name);
    if (obj != nullptr && obj->m_type == 2) {
        static_cast<event::ObjectChara*>(obj)->m_chara->playVolumeFade(event::CharaEffectPlayer::VF_TYPE(1), a2, mm::Vec3(a3, a4, a5),
                                                                        mm::Vec3(a6, a7, a8), a9, a10, a11, a12);
    }
    return 0;
}

// evt_chara.playVolumeFadeAnim
static int fn_710065E49C(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    float time = vmArgOmitChk(pThread, 2) ? 0.5f : vmArgFixedGet(2, vmArgPtrGet(pThread, 2));
    float delay = vmArgOmitChk(pThread, 3) ? 0.0f : vmArgFixedGet(3, vmArgPtrGet(pThread, 3));
    event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->searchByName(name);
    if (obj != nullptr && obj->m_type == 2) {
        static_cast<event::ObjectChara*>(obj)->m_chara->playVolumeFadeAnim(event::CharaEffectPlayer::VF_TYPE(1), time, delay);
    }
    return 0;
}

// evt_chara.stopVolumeFade
static int fn_710065E5CC(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->searchByName(name);
    if (obj != nullptr && obj->m_type == 2) {
        static_cast<event::ObjectChara*>(obj)->m_chara->stopVolumeFade(event::CharaEffectPlayer::VF_TYPE(1));
    }
    return 0;
}

// evt_chara.playRimBloom
static int fn_710065E680(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    int type = vmArgOmitChk(pThread, 2) ? 1 : vmArgIntGet(2, vmArgPtrGet(pThread, 2));
    event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->searchByName(name);
    if (obj != nullptr && obj->m_type == 2) {
        static_cast<event::ObjectChara*>(obj)->m_chara->playRimBloom(type);
    }
    return 0;
}

// evt_chara.stopRimBloom
static int fn_710065E770(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->searchByName(name);
    if (obj != nullptr && obj->m_type == 2) {
        static_cast<event::ObjectChara*>(obj)->m_chara->stopRimBloom();
    }
    return 0;
}

// evt_chara.setPartsDisp
static int fn_710065E820(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    const char* part = vmArgStringGet(2, vmArgPtrGet(pThread, 2));
    int disp = vmArgBoolGet(3, vmArgPtrGet(pThread, 3));
    event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->searchByName(name);
    if (obj != nullptr && obj->m_type == 2) {
        static_cast<event::ObjectChara*>(obj)->m_chara->setExtDisp(part, disp != 0);
    }
    return 0;
}

// evt_chara.setExtParam
static int fn_710065E920(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    const char* part = vmArgStringGet(2, vmArgPtrGet(pThread, 2));
    float value = vmArgFixedGet(3, vmArgPtrGet(pThread, 3));
    event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->searchByName(name);
    if (obj != nullptr && obj->m_type == 2) {
        static_cast<event::ObjectChara*>(obj)->m_chara->setExtParam(part, value);
    }
    return 0;
}

// evt_chara.setWeaponDisp
static int fn_710065EA24(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    int disp = vmArgBoolGet(2, vmArgPtrGet(pThread, 2));
    event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->searchByName(name);
    if (obj != nullptr && obj->m_type == 2) {
        static_cast<event::ObjectChara*>(obj)->m_chara->setHideWeapon(event::WPNHIDEID(3), disp == 0, false);
        static_cast<event::ObjectChara*>(obj)->m_chara->setHideWeapon(event::WPNHIDEID(3), disp == 0, true);
    }
    return 0;
}

// evt_chara.setWeaponDispByBladeID
static int fn_710065EB28(VMThread* pThread) {
    int blade = vmArgIntGet(1, vmArgPtrGet(pThread, 1));
    int disp = vmArgBoolGet(2, vmArgPtrGet(pThread, 2));
    int creator = gf::GfDataBlade::getCreator(blade);
    if (creator > 0) {
        event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->searchByID(3, creator);
        if (obj != nullptr && obj->m_type == 2) {
            static_cast<event::ObjectChara*>(obj)->m_chara->setHideWeapon(event::WPNHIDEID(3), disp == 0, false);
            static_cast<event::ObjectChara*>(obj)->m_chara->setHideWeapon(event::WPNHIDEID(3), disp == 0, true);
        }
    }
    return 0;
}

// evt_chara.setCharaDisp
static int fn_710065EC44(VMThread* pThread) {
    const char* name = vmArgStringGet(1, vmArgPtrGet(pThread, 1));
    int disp = vmArgBoolGet(2, vmArgPtrGet(pThread, 2));
    event::Object* obj = mm::mtl::Singleton<event::ObjectManager>::getPtr()->searchByName(name);
    if (obj != nullptr && obj->m_type == 2) {
        if (disp) {
            static_cast<event::ObjectChara*>(obj)->m_chara->playFade(false, 0.0f);
        } else {
            static_cast<event::ObjectChara*>(obj)->m_chara->playFade(true, 0.0f);
        }
    }
    return 0;
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B73128).
static VMPluginFunc s_evtcharaPlugin[] = {
    {"setPos", fn_710065B23C},
    {"walkPos", fn_710065B3A4},
    {"linerPos", fn_710065B630},
    {"setRot", fn_710065B90C},
    {"turnRot", fn_710065BA88},
    {"linerRot", fn_710065BD38},
    {"setTar", fn_710065BFD4},
    {"setIdle", fn_710065C420},
    {"playAction", fn_710065C554},
    {"playMotion", fn_710065C758},
    {"playMotionABC", fn_710065C954},
    {"playHead", fn_710065CCCC},
    {"playFacial", fn_710065CFCC},
    {"playTalk", fn_710065D4C4},
    {"playWink", fn_710065D890},
    {"mount", fn_710065DBEC},
    {"playFade", fn_710065DFE8},
    {"playVolumeFade", fn_710065E154},
    {"playVolumeFadeAnim", fn_710065E49C},
    {"stopVolumeFade", fn_710065E5CC},
    {"playRimBloom", fn_710065E680},
    {"stopRimBloom", fn_710065E770},
    {"setPartsDisp", fn_710065E820},
    {"setExtParam", fn_710065E920},
    {"setWeaponDisp", fn_710065EA24},
    {"setWeaponDispByBladeID", fn_710065EB28},
    {"setCharaDisp", fn_710065EC44},
    {nullptr, nullptr},
};

void pluginEvtCharaRegist() {
    vmPluginRegist("evt_chara", s_evtcharaPlugin);
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

// Placeholder name: new in 3.0.1 (1.0.0 has no evt_ex plugin), and the symbols name no function here. pluginRegist
// calls it; the pattern of the other plugins would make it pluginEvtExRegist, which no evidence confirms.
void fn_710066162C() {
    vmPluginRegist("evt_ex", s_evtexPlugin);
}
