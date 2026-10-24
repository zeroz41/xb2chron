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

namespace gf {

void GfMenuManager::build(const GfSetupParam& param) {
#line 514
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuManager(param);
}

void GfMenuManager::destroy() {
    GfMenuManager* self = get();
    self->finalize();
    delete self;
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

void GfMenuManager::fn_7100359CD8(unsigned short id, unsigned short arg) {
    GfMenuManager* mgr = get();
    if (mgr == nullptr || !mgr->m_initialized || mgr->m_callContext == nullptr) {
        return;
    }
    mgr->m_callContext->reset();
    GfMenuObjCommonText::fn_71003E1F60(mgr->m_callContext, id, arg);
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
    applyGammaCorrectValue(option.m_gamma / 255.0f);
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
    if (param.m_questId.m_id == 0 && param.m_questId.m_achieveId == 0) {
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
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuLocation::refreshLocator(3);
    }
}

void GfMenuManager::qevChangeCurrentQuest(const QuestChangeParam&) {
    GfMenuLocation::refreshLocator(0);
    GfMenuLocation::refreshLocator(1);
    GfMenuLocation::refreshLocator(3);
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

}  // namespace gf
