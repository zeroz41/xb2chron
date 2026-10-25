// Script VM plugins btl_ai, deb, evt and evt_env (their tables, entries and Regist functions). The entries are static
// and nothing names them: they keep placeholder fn_ names. The other plugins of this unit (evt_bgm, evt_cam,
// evt_chara, evt_eff, evt_ex) are separate translation units (SPLITS.md) and are not written yet.
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
        value = (unsigned char)(unsigned long)Bdat::getValCheck(bdat, "ComboStage", id, 1);
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
        value = (unsigned char)(unsigned long)Bdat::getValCheck(bdat, "Atr", id, 1);
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

