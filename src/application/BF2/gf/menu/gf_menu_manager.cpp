#include "classes/ui/UIPadRead.h"
#include "classes/gf/GfMenuMnagerPadRead.h"
#include "classes/gf/GfGamePad.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjPartyGauge.h"
#include "gf/gf_data_aoc.h"
#include "classes/gf/GfMenuObjDamageValue.h"
#include "classes/gf/GfMenuObjDamageBuff.h"
#include "classes/gf/GfMenuObjExpGet.h"
#include "classes/gf/GfMenuObjHanaPartsMake.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuObjCampMenu.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "mm/mtl/Bitflag.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuObjEnemyStatus.h"
#include "classes/gf/GfMenuObjPartyStatus.h"
#include "classes/gf/GfMenuObjPartyGauge.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuObjQuestLog.h"
#include "classes/gf/GfGameScene.h"
#include "gf/QuestTaskParam.h"
#include "classes/tl/TitleMain.h"
#include "gf/QuestCompleteChildParam.h"
#include "gf/SDataOption.h"
#include "classes/gf/GfMenuObjActionWindow.h"
#include "classes/gf/GfMenuObjComboRoute.h"
#include "gf/GfObjAcc.h"
#include "gf/GfMenuFlag.h"
#include "classes/gf/GfMenuLocation.h"
#include "classes/gf/GfMenuObjSaveLoad2.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/ui/UIManager.h"
#include "classes/gf/GfMenuObjOption.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuFade.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuLocation.h"
#include "classes/gf/GfMenuObjSaveLoad2.h"
#include "classes/gf/GfMenuObjTutorial.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuObjChapterTelop.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuObjMainRoot.h"
#include "classes/gf/GfMenuObjOption.h"
#include "classes/gf/GfMenuObjZoneTelop.h"
#include "classes/ui/UIManager.h"
#include "classes/gf/GfAllocator.h"
#include "gf/GfSetupParam.h"
#include "layer/LayerAccManager.h"
#include "ml/ScnRenderDrSysParmAcc.h"
#include "gf/GfMenuObjDummyTutorial.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuObjCampMenu.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjDamageValue.h"
#include "classes/gf/GfMenuObjDamageBuff.h"
#include "classes/gf/GfMenuObjExpGet.h"
#include "classes/gf/GfMenuObjHanaPartsMake.h"
#include "classes/gf/GfMenuObjEnvironmentInfo.h"
#include "classes/gf/GfMenuObjDropItem.h"
#include "gf/GfDataItem.h"
#include "classes/gf/GfMenuMnagerPadRead.h"
#include "classes/gf/GfGamePad.h"
#include "gf/gf_data_aoc.h"
#include "gf/GfDataBlade.h"
#include "gf/SDataOption.h"
#include "fw/LangUtil.h"
#include "nn/oe.h"
#include "classes/ml/DevFileTh.h"
#include "classes/gf/GfGameEnv.h"
#include "ui/UIUtil.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/GfFieldGimmick.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/GfObjProperty.h"
#include "classes/gf/GfObjPropertyEnemy.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameFlag.h"
#include "gf/GfPlayFactory.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfMenuObjCharChange.h"
#include "classes/gf/GfMenuObjChainAttack.h"
#include "classes/gf/GfMenuObjTargetInfo.h"
#include "classes/ui/UIInputManager.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuCallManager.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuFade.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuHUD.h"
#include "classes/gf/GfMenuStatus.h"
#include "classes/gf/GfMenuEquip.h"
#include "classes/gf/GfMenuMain.h"
#include "classes/gf/GfMenuShop.h"
#include "classes/gf/GfMenuPrecious.h"
#include "classes/gf/GfMenuKizunaring.h"
#include "classes/gf/GfMenuQuest.h"
#include "classes/gf/GfMenuMinimap.h"
#include "classes/gf/GfMenuScriptManager.h"
#include "classes/gf/GfMenuFieldSkill.h"
#include "classes/gf/GfMenuManyObjects.h"
#include "classes/gf/GfMenuOrderMgr.h"
#include "classes/gf/GfMenuLocation.h"
#include "classes/gf/GfMenuMapInfo.h"
#include "classes/gf/GfMenuSoundManager.h"
#include "classes/gf/GfMenuObjBtlchTutorial.h"
#include "classes/gf/GfMenuObjTips.h"

namespace gf {

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EA6F48). getGameVersionString reads the
// application's display version into it.
static nn::oe::DisplayVersion s_displayVersion;

GfMenuManager::GfMenuManager(const GfSetupParam& param)
    : m_objs(), m_initialized(false), m_locked(false), pad_4092(0), m_list(), pad_40B0(0), m_targetObjHandle((GF_OBJ_HANDLE*)-1),
      m_accessObjHandle((GF_OBJ_HANDLE*)-1), m_targetChanged(false), m_accessChanged(false), m_battleStateEnable(false),
      m_curCameraType(0), m_callContext(nullptr), m_commonWindowResult(0), m_battleState(), pad_40E0(), m_dispHud(),
      pad_40E8(0), pad_40F0(0), m_updateDT(0.0f), m_comboRouteOpen(), m_openBtlModelView(false), m_openNameSelect(false),
      m_openOpeningTelop(false), m_hideAll(false), m_enableQuestOpen(false), m_evTheaterFlag(false), m_layer101Open(false),
      m_layer72Open(false), m_layer300Open(false), m_region(0), m_optionFlag(false), m_regionJP(false),
      m_baseGameFlag(false), pad_4113(1), m_bladeBookFlag(), pad_4118(0), pad_4120(), m_latestCommonWinID(0),
      m_mapjumpAtlasInfo(), m_titleValue(0), m_titleCount(0), m_npcMeetIds(), pad_43B0(0) {
    bool jp = ml::DevFileTh::checkValidFileBlock("bdat/jp.bin");
    m_region = !jp;
    if (!jp && ml::DevFileTh::checkValidFileBlock("stream/voice/jp/01/01010101.nop")) {
        m_optionFlag = true;
    }
    if (ml::DevFileTh::checkValidFileBlock("menu_ira/font/bf2.wisty")) {
        ui::UIUtil::changeRootFolder("menu_ira");
        ui::UIUtil::registEnableExpType(3);
        if (GfGameManager::isGameTypeIra()) {
            ui::UIUtil::setResourceReplaceID(1);
            pad_4113 = 0;
        }
        m_regionJP = true;
    }
    if (m_regionJP) {
        m_optionFlag = true;
    }
    if (GfGameManager::isInstalledBattleArenaContents()) {
        ui::UIUtil::registEnableExpType(1);
    }
    if (GfGameAoc::get()->fn_71002A75DC(0x101)) {
        ui::UIUtil::registEnableExpType(3);
        if (GfGameManager::isGameTypeIra()) {
            ui::UIUtil::setResourceReplaceID(1);
        }
    }
    if (GfGameAoc::get()->fn_71002A75DC(0x20301)) {
        m_baseGameFlag = true;
    }
    m_bladeBookFlag.reset();
    if (!GfMenuObjUtil::isValidExpansion(3) && ml::DevFileTh::checkValidFileBlock("menu/image/fim_bl_142.wilay")) {
        m_bladeBookFlag.set(0, true);
    }
    initialize(param);
}

void GfMenuManager::build(const GfSetupParam& param) {
#line 514
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuManager(param);
}

GfMenuManager::~GfMenuManager() {}

void GfMenuManager::destroy() {
    GfMenuManager* self = get();
    self->finalize();
    delete self;
}

bool GfMenuManager::isInitialized() {
    GfMenuManager* mgr = get();
    return mgr != nullptr && mgr->m_initialized && !mgr->pad_40B0 &&
           GfMenuReference::isInitialized() &&
           GfMenuCallManager::isInitialized() &&
           GfMenuAdapterManager::isInitialized() &&
           GfMenuFade::isInitialized() &&
           GfMenuFullScreen::isInitialized() &&
           GfMenuHUD::isInitialized() &&
           GfMenuStatus::isInitialized() &&
           GfMenuEquip::isInitialized() &&
           GfMenuMain::isInitialized() &&
           GfMenuShop::isInitialized() &&
           GfMenuPrecious::isInitialized() &&
           GfMenuKizunaring::isInitialized() &&
           GfMenuQuest::isInitialized() &&
           GfMenuMinimap::isInitialized() &&
           GfMenuScriptManager::isInitialized() &&
           GfMenuFieldSkill::isInitialized() &&
           GfMenuManyObjects::isInitialized() &&
           GfMenuOrderMgr::isInitialized() &&
           GfMenuLocation::isInitialized() &&
           GfMenuMapInfo::isInitialized() &&
           GfMenuSoundManager::isInitialized();
}

bool GfMenuManager::isRegionJP() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr) {
        return false;
    }
    return mgr->m_regionJP;
}

void GfMenuManager::initOptionData(SDataOption& option) {
    GfMenuObjOption::initOptionData(option);
}

void GfMenuManager::applyGammaCorrectValue(float value) {
    float gamma = value + value + 1.2f;
    layer::LayerAccManager layerAcc;
    layerAcc.setGamma(gamma);
    ml::ScnRenderDrSysParmAcc scnAcc;
    scnAcc.setGamma(gamma);
}

bool GfMenuManager::isFading(unsigned int layer) {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized) {
        return false;
    }
    return GfMenuFade::isFading(layer);
}

bool GfMenuManager::isFading() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized) {
        return false;
    }
    for (unsigned int layer = 0; layer < 3; ++layer) {
        if (isFading(layer)) {
            return true;
        }
    }
    return false;
}

void GfMenuManager::getFadeColor(unsigned int layer, mm::Col4& color) {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized || mgr->m_locked) {
        return;
    }
    GfMenuFade::getFadeColor(layer, color);
}

float GfMenuManager::getUpdateDT() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized) {
        return 0.0f;
    }
    return mgr->m_updateDT;
}

GF_OBJ_HANDLE* GfMenuManager::getTargetObjHandle() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    if (!mgr->m_initialized) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    return mgr->m_targetObjHandle;
}

GF_OBJ_HANDLE* GfMenuManager::getAccessObjHandle() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    if (!mgr->m_initialized) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    return mgr->m_accessObjHandle;
}

unsigned int GfMenuManager::getCurCameraType() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr) {
        return 0;
    }
    if (!mgr->m_initialized) {
        return 0;
    }
    return mgr->m_curCameraType;
}

void GfMenuManager::openCommonWindow(unsigned short id) {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized || mgr->m_callContext == nullptr) {
        return;
    }
    mgr->m_callContext->reset();
    GfMenuObjCommonText::open(mgr->m_callContext, id, 0);
    mgr->m_latestCommonWinID = id;
}

void GfMenuManager::openCommonWindowWithNamed(unsigned short id, unsigned int arg) {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized || mgr->m_callContext == nullptr) {
        return;
    }
    mgr->m_callContext->reset();
    GfMenuObjCommonText::openWithNamed(mgr->m_callContext, id, arg);
    mgr->m_latestCommonWinID = id;
}

void GfMenuManager::openCommonWindow(const MenuCommonWindowParam& param) {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized || mgr->m_callContext == nullptr) {
        return;
    }
    mgr->m_callContext->reset();
    GfMenuObjCommonText::open(mgr->m_callContext, param);
}

void GfMenuManager::closeCommonWindow() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized || mgr->m_callContext == nullptr) {
        return;
    }
    GfMenuObjCommonText::close();
}

bool GfMenuManager::isOpenCommonWindow() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized) {
        return false;
    }
    if (mgr->m_callContext == nullptr || mgr->m_callContext->getState() == 0) {
        return false;
    }
    if (!mgr->m_callContext->isActive()) {
        return false;
    }
    return mgr->m_callContext->m_objectId == 100;
}

int GfMenuManager::getCommonWindowResult() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr) {
        return 0;
    }
    if (!mgr->m_initialized) {
        return 0;
    }
    return mgr->m_commonWindowResult;
}

unsigned int GfMenuManager::getLatestCommonWinID() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr) {
        return 0;
    }
    if (!mgr->m_initialized) {
        return 0;
    }
    return mgr->m_latestCommonWinID;
}

void GfMenuManager::openPreciousWindow(unsigned short id) {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized || mgr->m_callContext == nullptr) {
        return;
    }
    mgr->m_callContext->reset();
    GfMenuObjCommonText::openItem(mgr->m_callContext, 11, id);
}

bool GfMenuManager::isOpenPreciousWindow() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized) {
        return false;
    }
    if (mgr->m_callContext == nullptr || mgr->m_callContext->getState() == 0) {
        return false;
    }
    if (!mgr->m_callContext->isActive()) {
        return false;
    }
    return mgr->m_callContext->m_objectId == 100;
}

void GfMenuManager::openChapterTelop(unsigned char chapter) {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized) {
        return;
    }
    if (chapter < 1 || chapter > 10 || mgr->m_callContext == nullptr) {
        return;
    }
    mgr->m_callContext->reset();
    GfMenuObjChapterTelop::openBeginTelop(mgr->m_callContext, chapter);
}

void GfMenuManager::openChapterEndTelop(unsigned char chapter) {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized) {
        return;
    }
    if (chapter < 1 || chapter > 10 || mgr->m_callContext == nullptr) {
        return;
    }
    mgr->m_callContext->reset();
    GfMenuObjChapterTelop::openEndTelop(mgr->m_callContext, chapter);
}

bool GfMenuManager::isOpenChapterTelop() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized) {
        return false;
    }
    if (mgr->m_callContext == nullptr || mgr->m_callContext->getState() == 0) {
        return false;
    }
    if (!mgr->m_callContext->isActive()) {
        return false;
    }
    return mgr->m_callContext->m_objectId == 68;
}

void GfMenuManager::openZoneTelop(unsigned short zone) {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized) {
        return;
    }
    if (mgr->m_callContext == nullptr || zone == 0) {
        return;
    }
    mgr->m_callContext->reset();
    GfMenuObjZoneTelop::open(mgr->m_callContext, zone);
}

bool GfMenuManager::isOpenZoneTelop() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized) {
        return false;
    }
    if (mgr->m_callContext == nullptr || mgr->m_callContext->getState() == 0) {
        return false;
    }
    if (!mgr->m_callContext->isActive()) {
        return false;
    }
    return mgr->m_callContext->m_objectId == 69;
}

void GfMenuManager::openDummyTutorial(unsigned char tutorial) {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized || mgr->m_callContext == nullptr) {
        return;
    }
    mgr->m_callContext->reset();
    GfMenuObjDummyTutorial::OpenParam param;
    param.m_id = tutorial;
    GfMenuObjDummyTutorial::open(mgr->m_callContext, param);
}

bool GfMenuManager::isOpenDummyTutorial() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized) {
        return false;
    }
    if (mgr->m_callContext == nullptr || mgr->m_callContext->getState() == 0) {
        return false;
    }
    if (!mgr->m_callContext->isActive()) {
        return false;
    }
    return mgr->m_callContext->m_objectId == 121;
}

void GfMenuManager::setEnableQuestOpen(bool enable) {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized) {
        return;
    }
    mgr->m_enableQuestOpen = enable;
}

bool GfMenuManager::isEnableQuestOpen() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr) {
        return false;
    }
    if (!mgr->m_initialized) {
        return false;
    }
    return mgr->m_enableQuestOpen;
}

unsigned int GfMenuManager::getRegion() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr) {
        return 0;
    }
    return mgr->m_region;
}

bool GfMenuManager::isRegionUS() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr) {
        return false;
    }
    return mgr->m_region == 1;
}

void GfMenuManager::gevCameraControl(unsigned int type) {
    m_curCameraType = type;
}

bool GfMenuManager::isOpenFullScreen() {
    return GfMenuFullScreen::isOpen();
}

void GfMenuManager::openFullScreen(unsigned int screen, bool flag0, bool flag1) {
    GfMenuFullScreen::open(screen, flag0, flag1);
}

void GfMenuManager::openMenu(unsigned int menu) {
    GfMenuObjMainRoot::OpenParam param;
    param.m_menuId = menu;
    GfMenuObjMainRoot::registOpenParam(param);
    GfMenuFullScreen::open(2, true, true);
}

void GfMenuManager::openBtlModelView() {
    if (get() == nullptr) {
        return;
    }
    ui::UIManager::get()->createLayer(10);
}

void GfMenuManager::closeBtlModelView() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_openBtlModelView) {
        return;
    }
    ui::UIManager::get()->terminateLayer(10, true);
}

bool GfMenuManager::isOpenBtlModelView() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr) {
        return false;
    }
    return mgr->m_openBtlModelView;
}

void GfMenuManager::openNameSelect() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr) {
        return;
    }
    ui::UIManager::get()->createLayer(12);
    mgr->m_openNameSelect = true;
}

bool GfMenuManager::isOpenNameSelect() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr) {
        return false;
    }
    return mgr->m_openNameSelect;
}

void GfMenuManager::openOpeningTelop() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr) {
        return;
    }
    ui::UIManager::get()->createLayer(13);
    mgr->m_openOpeningTelop = true;
}

void GfMenuManager::closeOpeningTelop() {
    if (get() == nullptr) {
        return;
    }
    ui::UIManager::get()->terminateLayer(13, true);
}

void GfMenuManager::openStaffroll() {
    if (get() == nullptr) {
        return;
    }
    ui::UIManager::get()->createLayer(14);
}

void GfMenuManager::closeStaffroll() {
    if (get() == nullptr) {
        return;
    }
    ui::UIManager::get()->terminateLayer(14, true);
}

void GfMenuManager::acceptAccess(GF_OBJ_HANDLE*) {
    GfMenuObjUtil::playSE(0x1B);
}

void GfMenuManager::closeFullScreen(bool flag0, bool flag1) {
    GfMenuFullScreen::close(flag0, flag1);
}

bool GfMenuManager::isSwitchingFullScreen() {
    return GfMenuFullScreen::isSwitching();
}

bool GfMenuManager::isFieldHudInputEnable() {
    return !GfMenuObjTutorial::isWaiting();
}

void GfMenuManager::setDispAll(bool disp) {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || mgr->m_locked) {
        return;
    }
    mgr->m_hideAll = !disp;
}

void GfMenuManager::applyOptionData(const SDataOption& option) {
    applyGammaCorrectValue(option.m_soundUi.m_gamma / 255.0f);
}

void GfMenuManager::setBattleState(unsigned int state, bool on) {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized || !mgr->m_battleStateEnable) {
        return;
    }
    mgr->m_battleState.set(state, on);
}

bool GfMenuManager::isBattleState(unsigned int state) {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized) {
        return false;
    }
    return mgr->m_battleState.test(state);
}

bool GfMenuManager::isClearCheck() {
    tl::TitleMain* title = tl::TitleMain::get();
    if (title == nullptr) {
        return false;
    }
    return title->m_isClear;
}

void GfMenuManager::gevAccessTarget(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.m_obj == nullptr) {
        GfMenuObjActionWindow::close();
        if (m_accessObjHandle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            m_accessChanged = true;
        }
        m_accessObjHandle = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    } else {
        GfMenuObjActionWindow::OpenParam param;
        param.m_obj = handle;
        param.m_button = 4;
        GfMenuObjActionWindow::open(param);
        if (m_accessObjHandle != handle) {
            m_accessChanged = true;
        }
        m_accessObjHandle = handle;
    }
}

void GfMenuManager::gevChangeTarget(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.m_obj == nullptr || acc.getType() != 5) {
        GfMenuReference::setPartyStatusLock(0, false);
        GfMenuObjPartyStatus::close(false);
        GfMenuObjEnemyStatus::close();
    } else {
        GfMenuObjEnemyStatus::OpenParam param;
        param.m_obj = handle;
        GfMenuObjEnemyStatus::open(param);
        GfMenuReference::setPartyStatusLock(0, true);
        GfMenuObjPartyStatus::open(true);
    }
    if (m_targetObjHandle != handle) {
        m_targetChanged = true;
    }
    m_targetObjHandle = handle;
}

void GfMenuManager::gevBattleStart() {
    GfMenuObjEnemyStatus::disp(true);
    GfMenuObjComboRoute::disp(true);
    GfMenuObjPartyGauge::disp(true);
    setBattleState(0, true);
}




void GfMenuManager::qevCompleteChildQuest(const QuestCompleteChildParam& param) {
    if (param.m_questId == QuestID()) {
        return;
    }
    GfMenuLocation::refreshLocator(0);
    GfMenuLocation::refreshLocator(1);
    GfMenuLocation::refreshLocator(3);
}

void GfMenuManager::qevOrderQuest(const QuestOrderParam&) {
    GfMenuLocation::refreshLocator(0);
    GfMenuLocation::refreshLocator(1);
    GfMenuLocation::refreshLocator(3);
}

void GfMenuManager::qevCompleteQuest(const gf::QuestCompleteParam&) {}

void GfMenuManager::qevLoadTaskState(unsigned int count) {
    if (count == 0) {
        return;
    }
    GfMenuLocation::refreshLocator(0);
    GfMenuLocation::refreshLocator(1);
    GfMenuLocation::refreshLocator(3);
}

void GfMenuManager::qevChangeQuestState(const QuestStateParam&) {
    GfMenuLocation::refreshLocator(0);
    GfMenuLocation::refreshLocator(1);
    if (GfMenuObjUtil::isValidExpansion(3)) {
        GfMenuLocation::refreshLocator(3);
    }
}

void GfMenuManager::qevChangeCurrentQuest(const QuestChangeParam&) {
    GfMenuLocation::refreshLocator(0);
    GfMenuLocation::refreshLocator(1);
    GfMenuLocation::refreshLocator(3);
}

const fw::PadData& GfMenuMnagerPadRead::uiGetControlPad() const {
    return *GfGamePad::getPadPlayer();
}

void GfMenuManager::beginUpdate(const fw::UpdateInfo& info) {
    GfMenuAdapterManager::postUpdateAfter(info);
}

void GfMenuManager::openSave() {
    GfMenuObjMainRoot::OpenParam param;
    GfMenuObjSaveLoad2::OpenParam saveParam;
    saveParam.m_mode = 1;
    GfMenuObjSaveLoad2::registOpenParam(saveParam);
    param.m_menuId = 0x35;
    GfMenuObjMainRoot::registOpenParam(param);
    GfMenuFullScreen::open(2, true, true);
}

bool GfMenuManager::isEnableVoiceChange() {
    GfMenuManager* mgr = GfMenuManager::get();
    if (mgr == nullptr) {
        return false;
    }
    return mgr->m_optionFlag;
}

void GfMenuManager::resetLatestCommonWinID() {
    GfMenuManager* mgr = GfMenuManager::get();
    if (mgr == nullptr || !mgr->m_initialized) {
        return;
    }
    mgr->m_latestCommonWinID = 0;
}

int GfMenuManager::getTutotialStartID() {
    GfMenuManager* mgr = GfMenuManager::get();
    if (mgr == nullptr) {
        return 0;
    }
    return mgr->m_titleValue;
}

bool GfMenuManager::isOpenBtlchTutorial() {
    GfMenuManager* mgr = GfMenuManager::get();
    if (mgr == nullptr) {
        return false;
    }
    return mgr->m_titleCount != 0;
}


bool GfMenuManager::hasGift() {
    return true;
}

bool GfMenuManager::startTutorial(unsigned int id) {
    unsigned char* fp = GfDataBdat::getFP(0xFF);
    if (fp == nullptr) {
        return false;
    }
    if (GfMenuObjUtil::isValidExpansion(3)) {
        if (unsigned char* fpLayer = GfDataBdat::getFP(0x100)) {
            Bdat::getIdTop(fpLayer);
            fp = fpLayer;
        }
    }
    int index = id - Bdat::getIdTop(fp);
    if (index < 0) {
        return false;
    }
    int flag = index + 0xC710;
    if (GfGameFlag::getLocal(1, flag) == 1) {
        return false;
    }
    GfMenuManager* mgr = get();
    if (mgr == nullptr) {
        return false;
    }
    mgr->m_titleValue = Bdat::getMember(fp, "start_id") != nullptr ? static_cast<unsigned char>(Bdat::getVal(fp, "start_id", id)) : 0;
    GfPlayFactory::createStartTutorial(id, nullptr);
    GfGameFlag::setLocal(1, flag, 1);
    return true;
}

bool GfMenuManager::startBtlchTutorial(unsigned int menuId) {
    GfMenuManager* mgr = get();
    if (mgr == nullptr) {
        return false;
    }
    if (GfMenuObjUtil::isValidExpansion(3)) {
        if (mgr->m_titleCount == 0) {
            ui::UIManager::get()->createLayer(302);
            GfMenuObjTips::registStartTutorialID(menuId);
        } else {
            GfMenuObjTips::start(menuId);
        }
    } else {
        if (mgr->m_titleCount == 0) {
            ui::UIManager::get()->createLayer(103);
            loadBchUI();
            GfMenuObjBtlchTutorial::registStartTutorialID(menuId);
        } else {
            GfMenuObjBtlchTutorial::start(menuId);
        }
    }
    mgr->m_titleCount = menuId;
    return true;
}

void GfMenuManager::loadBchUI() {
    if (get() != nullptr && GfMenuObjUtil::isValidExpansion(1)) {
        ui::UIManager::get()->createLayer(102);
    }
}

int GfMenuManager::getGiftNumber() {
    return GfDataAoc::fn_71002229C0(4);
}

bool GfMenuManager::canPlayerControl() {
    GfMenuManager* mgr = GfMenuManager::get();
    if (mgr == nullptr) {
        return false;
    }
    return mgr->m_battleStateEnable;
}

bool GfMenuManager::isEnableMinimap() {
    return GfMenuFlag::get1(31) == 0;
}

void GfMenuManager::setTheaterNonTelop(bool flag) {
    GfMenuManager* mgr = GfMenuManager::get();
    if (mgr == nullptr) {
        return;
    }
    mgr->m_evTheaterFlag = flag;
}

void GfMenuManager::initOptionDataForIra(SDataOption& option) {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return;
    }
    GfMenuManager* mgr = GfMenuManager::get();
    if (mgr == nullptr || !mgr->m_optionFlag) {
        return;
    }
    if (fw::LangUtil::getLangType() == 0 || fw::LangUtil::getLangType() == 6 || fw::LangUtil::getLangType() == 11) {
        option.m_soundUi.m_byte1E = 1;
    } else {
        option.m_soundUi.m_byte1E = 0;
    }
}

bool GfMenuManager::openBtlchTutorialList() {
    GfMenuManager* mgr = GfMenuManager::get();
    if (mgr == nullptr || !GfMenuObjUtil::isValidExpansion(1)) {
        return false;
    }
    ui::UIManager::get()->createLayer(103);
    loadBchUI();
    mgr->m_titleCount = 1;
    return true;
}

bool GfMenuManager::isResExist(unsigned int index) {
    GfMenuManager* mgr = GfMenuManager::get();
    return index == 0 && mgr != nullptr && mgr->m_bladeBookFlag.test(0);
}

const char* GfMenuManager::getGameVersionString() {
    GfMenuManager* mgr = GfMenuManager::get();
    if ((mgr == nullptr || !mgr->m_regionJP) && GfGameManager::isGameTypeIra()) {
        return "2.0.1";
    }
    nn::oe::GetDisplayVersion(&s_displayVersion);
    return s_displayVersion.value;
}

bool GfMenuManager::isTheaterNonTelop() {
    GfMenuManager* mgr = GfMenuManager::get();
    if (mgr == nullptr) {
        return false;
    }
    return mgr->m_evTheaterFlag;
}

void GfMenuManager::requestNpcEntry(unsigned int id) {
    GfMenuManager* mgr = GfMenuManager::get();
    if (mgr == nullptr || !GfMenuObjUtil::isValidExpansion(3)) {
        return;
    }
    if (mgr->m_npcMeetIds.size() == mgr->m_npcMeetIds.capacity()) {
        return;
    }
    if (GfDataBlade::fn_710024DAB0(id) == 0 || !GfDataBlade::fn_710024DE6C(id)) {
        return;
    }
    mgr->m_npcMeetIds.push_back(id);
}

void GfMenuManager::updateLocatorAtlasCinfo(const GfGmkLocatorAtlas::CreateInfo& info) {
    GfMenuManager* mgr = GfMenuManager::get();
    if (mgr == nullptr || !GfGameManager::isMapjump()) {
        return;
    }
    mgr->m_mapjumpAtlasInfo = info;
}

void GfMenuManager::checkElementCombo() {
    GF_OBJ_HANDLE* handle = getTargetObjHandle();
    if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        GfObjAcc acc(handle);
        if (acc.getType() != 5) {
            return;
        }
        GfObjProperty* prop = GfObjUtil::getProperty(handle);
        if (prop == nullptr) {
            return;
        }
        GfObjPropertyEnemy* enemy = prop->getEnemy();
        if (enemy == nullptr) {
            return;
        }
        bool combo = enemy->m_elementComboId != 0;
        if (m_comboRouteOpen != combo) {
            if (combo) {
                GfMenuObjComboRoute::open();
            } else {
                GfMenuObjComboRoute::close();
            }
            m_comboRouteOpen = combo;
        }
    } else if (GfMenuObjUtil::isValidExpansion(1) && GfGameManager::isBattleArenaActive() && m_comboRouteOpen &&
               !isBattleState(0)) {
        GfMenuObjComboRoute::close();
        m_comboRouteOpen = false;
    }
}

bool GfMenuManager::hasNpcEntry() {
    GfMenuManager* mgr = GfMenuManager::get();
    if (mgr == nullptr) {
        return false;
    }
    GfMenuObjUtil::isValidExpansion(3);
    return !mgr->m_npcMeetIds.empty();
}

bool GfMenuManager::isHideAll() {
    GfMenuManager* mgr = GfMenuManager::get();
    if (mgr == nullptr || mgr->m_locked) {
        return false;
    }
    return mgr->m_hideAll;
}

bool GfMenuManager::isDispHud(int hud) {
    GfMenuManager* mgr = GfMenuManager::get();
    if (mgr == nullptr || mgr->m_locked) {
        return false;
    }
    return mgr->m_dispHud.test(hud);
}

void GfMenuManager::qevChangeTaskState(const QuestTaskParam& param) {
    if (param.m_questId == QuestID()) {
        return;
    }
    GfMenuLocation::refreshLocator(0);
    GfMenuLocation::refreshLocator(1);
    if (param.m_state == TASK_STATE(1)) {
        GfMenuObjQuestLog::completeTask(param);
        return;
    }
    GfGameScene* scene = GfGameScene::get();
    if (scene == nullptr) {
        return;
    }
    if (param.m_questId == scene->getQuestIdForTaskLog()) {
        GfMenuObjQuestLog::updateTask();
    }
}

void GfMenuManager::unloadBchUI() {
    if (get() != nullptr && GfMenuObjUtil::isValidExpansion(1)) {
        ui::UIManager::get()->terminateLayer(102, true);
        GfMenuObjPartyGauge::enableOpen();
    }
}

void GfMenuManager::gevMapjump(gf::GEV gev, const gf::MapjumpCallbackInfo&) {
    GfMenuObjComboRoute::close();
    GfMenuObjPartyGauge::close();
    if (static_cast<int>(gev) == 2) {
        GfGmkLocatorAtlas& atlas = GfFieldGimmick::get()->m_locatorAtlas;
        if (atlas.m_info.m_mapId >= 1) {
            m_mapjumpAtlasInfo = atlas.m_info;
            atlas.dispose();
        }
    } else if (static_cast<int>(gev) == 6) {
        if (m_mapjumpAtlasInfo.m_mapId >= 1) {
            GfFieldGimmick::get()->m_locatorAtlas.create(m_mapjumpAtlasInfo);
            m_mapjumpAtlasInfo = GfGmkLocatorAtlas::CreateInfo();
        }
    }
}

void GfMenuManager::gevBattleEnd() {
    m_battleState.reset();
    GfMenuReference::setChainNum(0);
    GfMenuObjComboRoute::close();
    GfMenuObjPartyGauge::close();
    if (GfMenuObjUtil::isValidExpansion(3)) {
        GfMenuReference::resetIraCharRecast();
    }
}

void GfMenuManager::gevPlayEvent(gf::GEV gev, unsigned int) {
    if (GfMenuFullScreen::isOpen()) {
        return;
    }
    switch (static_cast<int>(gev)) {
    case 10:
        GfMenuObjComboRoute::close();
        GfMenuObjPartyStatus::close(true);
        m_dispHud.set(1, false);
        m_dispHud.set(2, false);
        break;
    case 12:
        m_battleState.reset();
        m_battleStateEnable = false;
        GfMenuObjPartyGauge::close();
        GfMenuObjPartyStatus::close(true);
        GfMenuObjComboRoute::close();
        GfMenuObjChainAttack::closeResult();
        break;
    case 13:
        if (ui::UIInputManager* input = ui::UIInputManager::get()) {
            input->enable();
        }
        break;
    case 14:
        GfMenuObjDamageValue::closeAll();
        GfMenuObjDamageBuff::closeAll();
        GfMenuObjDropItem::closeAll();
        GfMenuObjExpGet::closeAll();
        GfMenuObjPartyGauge::close();
        GfMenuObjChainAttack::closeResult();
        GfMenuObjComboRoute::close();
        GfMenuObjPartyStatus::close(true);
        GfMenuObjTargetInfo::disp(false);
        break;
    }
}

void GfMenuManager::openBtlchOrder() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !GfMenuObjUtil::isValidExpansion(1)) {
        return;
    }
    ui::UIManager::get()->createLayer(101);
    mgr->m_layer101Open = true;
}

bool GfMenuManager::isEnableExpBlade3() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || GfGameManager::isGameTypeIra()) {
        return false;
    }
    return mgr->m_baseGameFlag;
}

void GfMenuManager::update(const fw::UpdateInfo&) {
    if (get() == nullptr) {
        return;
    }
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EA6F70, its guard); nothing reads it
    // (1.0.0's update is only this static).
    static mm::mtl::FixStr<16> s_work;
    if (GfMenuObjUtil::isValidExpansion(1) && GfGameManager::isBattleArenaActive()) {
        GfMenuAdapterManager::addActiveCategory(4);
    } else {
        GfMenuAdapterManager::delActiveCategory(4);
    }
}

bool GfMenuManager::isOpenBtlchOrder() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr) {
        return false;
    }
    return mgr->m_layer101Open;
}

void GfMenuManager::openNamedList() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !GfGameManager::isEnableNamedRecord()) {
        return;
    }
    ui::UIManager::get()->createLayer(72);
    mgr->m_layer72Open = true;
}

bool GfMenuManager::isOpenNamedList() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr) {
        return false;
    }
    return mgr->m_layer72Open;
}

void GfMenuManager::openCampMenu() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !GfMenuObjUtil::isValidExpansion(3)) {
        return;
    }
    if (mgr->m_layer300Open) {
        GfMenuObjCampMenu::returnFromEvent();
        return;
    }
    ui::UIManager::get()->createLayer(300);
    mgr->m_layer300Open = true;
}

bool GfMenuManager::isOpenCampMenu() {
    GfMenuManager* mgr = get();
    if (mgr == nullptr) {
        return false;
    }
    return mgr->m_layer300Open;
}

bool GfMenuManager::isCampSelectTalk() {
    return GfMenuObjCampMenu::getSelectResult() == 1;
}

void GfMenuManager::setMainmenuOpenMap() {
    GfMenuObjMainMenu2::OpenParam param;
    param.m_page = 1;
    GfMenuObjMainMenu2::registOpenParam(param);
}

void GfMenuManager::setMainmenuOpenSystem() {
    GfMenuObjMainMenu2::OpenParam param;
    param.m_page = GfMenuObjUtil::isValidExpansion(3) ? 5 : 6;
    GfMenuObjMainMenu2::registOpenParam(param);
}

void GfMenuManager::setMainmenuOpenPtForm() {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return;
    }
    GfMenuObjMainMenu2::OpenParam param;
    param.m_page = 0;
    GfMenuObjMainMenu2::registOpenParam(param);
}

void GfMenuManager::setMainmenuOpenHitonowa() {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return;
    }
    GfMenuObjMainMenu2::OpenParam param;
    param.m_page = 3;
    GfMenuObjMainMenu2::registOpenParam(param);
}

void GfMenuManager::gevSalvageStateChange(unsigned int state) {
    switch (state) {
    case 3:
        m_dispHud.set(1, false);
        m_dispHud.set(2, false);
        break;
    case 4:
        GfMenuObjEnvironmentInfo::close();
        break;
    case 6:
        GfMenuObjDamageValue::closeAll();
        GfMenuObjDamageBuff::closeAll();
        GfMenuObjDropItem::closeAll();
        GfMenuObjExpGet::closeAll();
        break;
    case 20:
        m_dispHud.set(1, true);
        m_dispHud.set(2, true);
        break;
    }
}

void GfMenuManager::gevItemAdd(unsigned int item, int num) {
    if (num > 0) {
        unsigned int type = GfDataItem::getItemType(item);
        if (type >= 1 && type <= 20) {
            GfMenuFlag::set1(type + 0x3A, 1);
        }
    } else {
        GfMenuObjHanaPartsMake::updateItemList();
    }
}

void GfMenuManager::gevChangeParty() {
    if (!GfMenuObjUtil::isValidExpansion(3) || m_battleState.test(0) || m_battleState.test(1)) {
        return;
    }
    unsigned int changed = 0;
    GfMenuReference::IraCharInfo owner = {0, {0xFF, 0.0f}};
    if (unsigned int driver = GfGameParty::getDriverBdatId(0, 0)) {
        owner.m_driver = driver;
        owner.m_gauge.m_type = 0;
    }
    if (GfMenuReference::setIraCharInfo(0, owner)) {
        changed |= 1;
    }
    // reset field by field (an assigned record would go through Bitflag's operator=, which the original does not call)
    owner.m_driver = 0;
    owner.m_gauge.m_type = 0xFF;
    owner.m_gauge.m_rate = 0.0f;
    owner.m_gauge.m_flags.reset();
    if (unsigned int driver = GfGameParty::getDriverBdatId(0, 1)) {
        owner.m_driver = driver;
        owner.m_gauge.m_type = 1;
    }
    changed |= GfMenuReference::setIraCharInfo(1, owner) ? 2 : 0;
    owner.m_driver = 0;
    owner.m_gauge.m_type = 0xFF;
    owner.m_gauge.m_rate = 0.0f;
    owner.m_gauge.m_flags.reset();
    if (unsigned int driver = GfGameParty::getDriverBdatId(0, 2)) {
        owner.m_driver = driver;
        owner.m_gauge.m_type = 2;
    }
    bool changed2 = GfMenuReference::setIraCharInfo(2, owner);
    if (changed == 3) {
        GfMenuObjCharChange::changeFormation();
    }
    if (changed2) {
        GfMenuObjCharChange::changeBlade();
    }
}

}  // namespace gf
