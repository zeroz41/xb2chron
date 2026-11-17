#include "gf/FileStaticVec3.h"
#include "classes/gf/GfMenuObjBladeCreate.h"
#include "classes/gf/GfMenuModelView.h"
#include "gf/GfReqCommand.h"
#include "classes/gf/GfMenuBladeCreateCamera.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuObjBladeSet2.h"
#include "classes/gf/SCOM_PARTY_ADD.h"
#include "gf/GfPlayFactory.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjBladeName.h"
#include "classes/gf/GfMenuObjFade.h"
#include "classes/gf/GfMenuSoundManager.h"
#include "classes/gf/GfReqManager.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuTypes.h"
#include "ml/ScnRenderDrSysParmAcc.h"
#include "classes/gf/GfMenuObjBladeCreate/MainListener.h"
#include "classes/gf/GfMenuObjBladeCreate/IdeagramListener.h"
#include "classes/gf/GfMenuObjBladeCreate/ResultListener.h"
#include "classes/gf/GfMenuObjBladeCreate/BoosterNumListener.h"
#include "classes/gf/GfMenuObjBladeCreate/ConfirmListener.h"
#include "classes/gf/GfMenuObjBladeCreate/DriverSelectListener.h"
#include "classes/gf/GfMenuObjBladeCreate/CrystalSelectListener.h"
#include "classes/gf/GfMenuObjBladeCreate/BoosterSelectListener.h"
#include "classes/ui/UISelectObjList.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuObjCmnStatus.h"
#include "classes/gf/GfMenuReference.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfBladeManager.h"
#include "gf/GfItemUtil.h"
#include "mm/Vec2.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfSound.h"
#include "classes/ui/UIObjectAcc.h"
#include "ui/EventData.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfMenuFade.h"
#include "classes/gf/GfSequentialPlay.h"
#include "mm/Col4.h"
#include "mm/mtl/FixStr.h"
#include <string.h>
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"
#include "gf/GfObjAcc.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/ui/UIManager.h"
#include "mm/mtl/Vector.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/Delegate.h"

namespace gf {

namespace {
// the pages' UI objects, by page (lbl_7100B5FF58; getPageObject's). Proposed name, not the original's
const char* s_pageNames[6] = {
    "LAY_dr_select", "LAY_core_select", "LAY_bst_select", "LAY_confirm", "LAY_create", "LAY_result",
};
// the booster page's effects, by booster (its item id less the boosters' first): the cursor's and the decision's
// (lbl_7100B5FF88). Proposed name, not the original's
const char* s_boosterEffects[4][2] = {
    {"bc_00_000", "bc_10_000"},
    {"bc_01_000", "bc_11_000"},
    {"bc_02_000", "bc_12_000"},
    {"bc_03_000", "bc_13_000"},
};
// the sounds BoosterSelectListener plays on a decision, by booster (lbl_7100B5FFC8). Proposed name, not the original's
const char* s_boosterSEs[4] = {"se_fld_allmap_707", "se_fld_allmap_708", "se_fld_allmap_709", "se_fld_allmap_710"};
// what changePage adds to pad_11A0 for the camera it pushes, by page (lbl_71009BDE6C). Proposed name, not the
// original's
const unsigned int s_pageCameras[6] = {0, 1, 2, 3, 4, 4};
}  // namespace

GfMenuObjBladeCreate::GfMenuObjBladeCreate(unsigned int handle)
    : GfMenuObject(handle), m_seq(this), m_eventSignal(nullptr), pad_1120(false), pad_1140(4), pad_1144(0),
      pad_1170(0), m_boosterNumbers(), pad_1180(0), m_number(), m_camera(nullptr), pad_1198(-1), pad_11A0(0),
      pad_11A8(nullptr), m_saveReq(0), pad_11B4(false), pad_11B8(0), m_bgm(0), m_se() {
    m_number = GfMenuReferenceNumber::create();
#line 170
    m_camera = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuBladeCreateCamera();
    m_se[0] = 0;
    m_se[1] = 0;
    m_se[2] = 0;
}

GfMenuObjBladeCreate::~GfMenuObjBladeCreate() {
    m_camera = nullptr;
    m_number = nullptr;
    if (pad_1160 != nullptr) {
        pad_1160->release();
        pad_1160 = nullptr;
    }
    if (pad_1168 != nullptr) {
        pad_1168->release();
        pad_1168 = nullptr;
    }
    if (pad_1150 != nullptr) {
        pad_1150->release();
        pad_1150 = nullptr;
    }
    if (pad_1158 != nullptr) {
        pad_1158->release();
        pad_1158 = nullptr;
    }
    if (pad_11A8 != nullptr) {
        pad_11A8->release();
        pad_11A8 = nullptr;
    }
}

inline unsigned int GfMenuObjBladeCreate::getPageObject(unsigned int handle, unsigned int page, bool sibling) {
    unsigned int object = 0;
    if (handle != 0 && page < 6) {
        ui::UIObjectAcc acc(handle);
        object = sibling ? acc.searchSibiling(s_pageNames[page]) : acc.searchChild(s_pageNames[page]);
    }
    return object;
}

void GfMenuObjBladeCreate::changePage(unsigned int handle, PageContext* context, unsigned int page, bool sibling,
                                      bool popCamera) {
    ui::UIObjectAcc prev(getPageObject(handle, context->m_page, sibling));
    ui::UIObjectAcc next(getPageObject(handle, page, sibling));
    ui::EventData event(0);
    if (next.m_object != nullptr) {
        event.m_type = 0x22;
        ui::UIManager::get()->requestObjectEvent(prev.m_handle, event, 0.0f);
        if (next.m_object != nullptr) {
            event.m_type = 0x21;
            ui::UIManager::get()->requestObjectEvent(next.m_handle, event, 0.0f);
        }
        context->m_prevPage = context->m_page;
        context->m_page = page;
        GfMenuObject::disableFSInput();
        if (popCamera) {
            context->m_modelView->popCamera(0.5f);
        }
        if (page == 0) {
            context->m_modelView->resetCamera(pad_1198, 0.0f);
        } else {
            context->m_modelView->pushCamera(s_pageCameras[page] + pad_11A0, 0.5f);
        }
    }
}

void GfMenuObjBladeCreate::updateIdea(bool keep) {
    int levels[4] = {0, 0, 0, 0};
    GfMenuReference::resetDriverAddIdeaLv();
    if (m_pageContext.m_page > 1 && m_number->m_value > 0) {
        GfMenuItemList* list = m_pageContext.m_boosterList;
        unsigned int id = list->getContents(list->getIndex(false)).m_id;
        int index = id - Bdat::getIdTop(GfDataBdat::getFP(0xA2));
        int number = m_number->m_value;
        levels[index] = number;
        if (keep) {
            int booster = m_pageContext.m_boosterList->getIndex(false);
            m_boosterNumbers[booster] = number;
        }
    }
    for (unsigned int i = 0; i < 4; i++) {
        GfMenuReference::setDriverAddIdeaLv(i, levels[i]);
    }
}

void GfMenuObjBladeCreate::setGuideText(unsigned int id) {
    ui::UIObjectAcc acc(m_handle, "TXT_guide");
    unsigned int name = Bdat::getVal(GfDataBdat::getFP(0x146), "name", id) & 0xFFFF;
    {
        ui::UIStr str(GfDataBdat::getFP(0x118), name);
        acc.setText(str);
    }
    acc.setDisp(true);
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "cmn_fade_motion_lr";
    param.m_motion = "fade_in_l";
    param.m_startFlags = 8;
    param.m_setDefault = true;
    param.m_time = 0.2f;
    GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
}

bool GfMenuObjBladeCreate::seqStart() {
    ml::ScnRenderDrSysParmAcc acc;
    if (acc.isSeamMapRead()) {
        return false;
    }
    pad_1120 = false;
    GfMenuSoundManager::fadeOutFieldBgm(0.5f);
    return true;
}

bool GfMenuObjBladeCreate::seqWaitLoading() {
    return !m_pageContext.m_modelView->isLoading();
}

bool GfMenuObjBladeCreate::seqSetupDriverObj() {
    {
        ui::UIObjectAcc acc(m_handle, "LAY_main");
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 1;
        param.m_time = 0.25f;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
    }
    changePage(m_handle, &m_pageContext, 0, false, false);
    m_pageContext.m_modelView->playEffect(8, "bc_30_000", mm::Vec3(0.0f, 0.0f, 0.0f),
                                          reinterpret_cast<GF_OBJ_HANDLE*>(-1));
    m_se[0] = GfMenuObjUtil::playSE("se_fld_allmap_701");
    return true;
}

void GfMenuObjBladeCreate::finalize() {
    if (m_pageContext.m_modelView != nullptr) {
        delete m_pageContext.m_modelView;
        m_pageContext.m_modelView = nullptr;
    }
    if (m_pageContext.m_driverList != nullptr) {
        m_pageContext.m_driverList->release();
        m_pageContext.m_driverList = nullptr;
    }
    if (m_pageContext.m_boosterList != nullptr) {
        m_pageContext.m_boosterList->release();
        m_pageContext.m_boosterList = nullptr;
    }
    if (m_pageContext.pad_48 != nullptr) {
        m_pageContext.pad_48->release();
        m_pageContext.pad_48 = nullptr;
    }
    if (m_pageContext.pad_30 != nullptr) {
        m_pageContext.pad_30->release();
        m_pageContext.pad_30 = nullptr;
    }
    if (m_pageContext.m_callContext != nullptr) {
        m_pageContext.m_callContext->release();
        m_pageContext.m_callContext = nullptr;
    }
    GfMenuObject::finalize();
}

bool GfMenuObjBladeCreate::seqEnd() {
    enableFSInput(m_pageContext.m_page);
    return true;
}

void GfMenuObjBladeCreate::update() {
    m_seq.update();
    if (m_pageContext.m_modelView != nullptr) {
        m_pageContext.m_modelView->update();
    }
    GfMenuObject::update();
}

void GfMenuObjBladeCreate::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObjOperationInfo::setGuideDisp(false);
        acc.setDisp(false);
        break;
    case 2: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_startFlags = 1;
        param.m_time = 0.5f;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        GfMenuObjOperationInfo::setGuideDisp(true);
        GfMenuObjMainMenu2::dispCloseButton();
        if (GfSound::get() != nullptr) {
            if (GfGameManager::isClearGame() && m_owner->pad_11B4) {
                GfMenuSoundManager::fadeInFieldBgm(0.5f);
            } else {
                GfMenuSoundManager::fadeFieldBgm(1.0f, 0.5f);
            }
            GfMenuObjUtil::stopBGM(m_owner->m_bgm, 1.0f);
            m_owner->m_bgm = 0;
            GfMenuObjBladeCreate* owner = m_owner;
            for (int i = 0; i < 3; i++) {
                if (owner->m_se[i] != 0) {
                    GfMenuObjUtil::stopSE(owner->m_se[i], 0.0f);
                }
            }
        }
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjBladeCreate::DriverSelectListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableFSInput(0);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
            if (m_owner->pad_11B4) {
                GfMenuObject::setInputActionEnable(acc.m_handle, 2, false);
            }
            GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_context->m_driverList);
        }
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        unsigned char dir = static_cast<unsigned char>(event.m_param2);
        m_context->m_driverList->setIndex(index);
        GfMenuDriverList* list = m_context->m_driverList;
        GfMenuReference::setReferenceDriverID(0, list->getContents(list->getIndex(false)).m_driver);
        if (index == -1 || prev == -1) {
            break;
        }
        list = m_context->m_driverList;
        unsigned int driver = list->getContents(list->getIndex(false)).m_driver;
        // the drivers in the carousel's order (a 16-byte constant; initialize and seqCreateDriverObj read the same)
        const unsigned int drivers[4] = {1, 2, 6, 3};
        unsigned int i = 0;
        while (drivers[i] != driver) {
            i++;
        }
        m_owner->pad_11A0 = i * 5;
        if (index == prev) {
            break;
        }
        m_owner->m_camera->setRotY(m_owner->pad_119C * index, dir, 0.25f);
        GfMenuObjUtil::playSECommonTab();
        break;
    }
    case 8:
        if (event.m_param1 == 1) {
            m_owner->nextPage(acc.m_handle, m_context, true);
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            {
                GfMenuDriverList* list = m_context->m_driverList;
                GfMenuModelView* view = m_context->m_modelView;
                view->sendObjectCommand(view->findGfObj(3, list->getContents(list->getIndex(false)).m_driver),
                                        "C_reachout_00");
            }
            GfMenuDriverList* list = m_context->m_driverList;
            switch (list->getContents(list->getIndex(false)).m_driver) {
            case 1:
                GfMenuObjUtil::playSE("se_fld_allmap_702");
                break;
            case 2:
                GfMenuObjUtil::playSE("se_fld_allmap_703");
                break;
            case 3:
                GfMenuObjUtil::playSE("se_fld_allmap_705");
                break;
            case 6:
                GfMenuObjUtil::playSE("se_fld_allmap_704");
                break;
            }
            GfMenuItemList::ItemBoxSetup setup;
            setup.m_type = 0xB;
            setup.m_setup.m_pageRowSize = m_owner->pad_1150->getSize();
            setup.m_setup.m_pageScroll = true;
            if (m_owner->pad_11B8 == 0) {
                m_context->pad_48->setupFromBox(setup);
                m_context->pad_48->setIndex(0);
            } else {
                MenuItemInfo item;
                item.m_type = 0xB;
                item.m_id = m_owner->pad_11B8;
                item.m_count = 1;
                m_context->pad_48->setup(getAllocator(ALLOCATOR(0)), setup.m_setup);
                m_context->pad_48->addItem(item, false);
            }
        } else if (event.m_param1 == 2) {
            if (m_owner->pad_11B4) {
                break;
            }
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            GfMenuObject::returnFSSubLayer(m_owner);
        }
        GfMenuObjUtil::playSECommonFromInput(event.m_param1);
        break;
    case 0x21: {
        GfMenuDriverList* list = m_context->m_driverList;
        GfMenuReference::setReferenceDriverID(0, list->getContents(list->getIndex(false)).m_driver);
        GfMenuReference::setReferenceBladeID(0, 0);
        m_owner->setGuideText(0x27);
        m_owner->dispGuideText(true);
        fadeIn(acc.m_handle);
        if (!m_owner->pad_11B4) {
            GfMenuObjMainMenu2::setCloseKeyEnable(true);
        }
        list = m_context->m_driverList;
        GfMenuModelView* view = m_context->m_modelView;
        view->sendObjectCommand(view->findGfObj(3, list->getContents(list->getIndex(false)).m_driver), "C_idle");
        if (m_owner->m_bgm == 0) {
            m_owner->m_bgm = GfMenuObjUtil::playBGM(0x14, false, fw::SoundCategory(0x11));
        }
        m_owner->m_pageContext.m_confirmed = false;
        break;
    }
    case 0x22:
        fadeOut(acc.m_handle);
        break;
    }
}

void GfMenuObjBladeCreate::CrystalSelectListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableFSInput(1);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        }
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        m_context->pad_48->setIndex(index);
        m_owner->pad_1150->setIndex(m_context->pad_48->getIndex(true));
        m_owner->refreshCrystalList();
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSECommonCursor();
        }
        break;
    }
    case 8:
        if (event.m_param1 == 1) {
            if (event.m_param0 == -1) {
                GfMenuObjUtil::playSECommon(2);
                break;
            }
            GfMenuItemList* list = m_context->pad_48;
            unsigned int crystal = list->getContents(list->getIndex(false)).m_id;
            GfMenuDriverList* drivers = m_owner->m_pageContext.m_driverList;
            unsigned int driver = drivers->getContents(drivers->getIndex(false)).m_driver;
            if (!GfItemUtil::isValidCrystal(crystal) || (crystal == 0xAFCD && driver != 6)) {
                drivers = m_owner->m_pageContext.m_driverList;
                driver = drivers->getContents(drivers->getIndex(false)).m_driver;
                if (crystal == 0xAFCD && driver != 6) {
                    GfMenuManager::openCommonWindow(0xD4);
                } else if (!GfItemUtil::isValidCrystal(crystal)) {
                    GfMenuManager::openCommonWindow(0xA9);
                } else {
                    GfMenuObjUtil::playSECommon(2);
                }
            } else {
                m_context->m_skipPage2 = false;
                if (GfBladeManager::isBindRareBladeCrystal(crystal) || m_owner->pad_11B8 == 0xAFD2) {
                    m_context->m_skipPage2 = true;
                } else if (GfDataBlade::getEnableCountForCreateBlade(crystal) == 0) {
                    GfMenuObjUtil::playSECommon(2);
                    GfMenuManager::openCommonWindow(0xBE);
                    break;
                }
                GfMenuItemList::ItemBoxSetup setup;
                setup.m_type = 0xC;
                setup.m_setup.m_pageRowSize = m_owner->pad_1160->getSize();
                m_context->m_boosterList->setupFromBox(setup);
                m_context->m_boosterList->setIndex(0);
                m_context->m_boosterList->sort(3, true);
                if (m_context->m_boosterList->getSize() == 0) {
                    m_context->m_skipPage2 = true;
                }
                m_owner->nextPage(acc.m_handle, m_context, true);
                GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            }
        } else if (event.m_param1 == 2) {
            {
                GfMenuModelView* view = m_context->m_modelView;
                view->delGfObj(0xF, view->getMapObjID(1));
            }
            {
                GfMenuModelView* view = m_context->m_modelView;
                view->delGfObj(0xF, view->getMapObjID(2));
            }
            if (m_owner->m_se[1] != 0) {
                GfMenuObjUtil::stopSE(m_owner->m_se[1], 0.0f);
                m_owner->m_se[1] = 0;
            }
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            m_owner->returnPage(acc.m_handle, m_context, true);
        }
        GfMenuObjUtil::playSECommonFromInput(event.m_param1);
        break;
    case 0x21:
        if (m_context->pad_48->getSize() == 0) {
            GfMenuObject::setupInputSelection(acc.m_handle, -1, 0);
            acc.setDispChild(false, "IMG_core_select_cursor");
        } else {
            acc.setDispChild(true, "IMG_core_select_cursor");
            if (m_context->m_prevPage == 0) {
                GfMenuObject::resetInputSelection(acc.m_handle);
            }
            GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_context->pad_48);
            m_owner->refreshCrystalList();
            GfMenuModelView* view = m_context->m_modelView;
            if (!view->checkGfObj(0xF, view->getMapObjID(1))) {
                m_context->m_modelView->addMapObjObject(1);
                m_context->m_modelView->addMapObjObject(2);
                m_owner->m_seq.clear();
                m_owner->m_seq.addJob(&GfMenuObjBladeCreate::seqWaitLoading);
                m_owner->m_seq.addJob(&GfMenuObjBladeCreate::seqSetupCrystal);
            }
        }
        fadeIn(acc.m_handle);
        m_owner->setGuideText(0x28);
        break;
    case 0x22:
        fadeOut(acc.m_handle);
        break;
    }
}

bool GfMenuObjBladeCreate::seqSetupCrystal() {
    GfMenuDriverList* list = m_pageContext.m_driverList;
    unsigned int driver = list->getContents(list->getIndex(false)).m_driver;
    {
        GfMenuModelView* view = m_pageContext.m_modelView;
        GF_OBJ_HANDLE* driverObj = view->findGfObj(3, driver);
        view->attachObject(view->findGfObj(0xF, view->getMapObjID(1)), driverObj, "EX_wp_R");
    }
    {
        GfMenuModelView* view = m_pageContext.m_modelView;
        GF_OBJ_HANDLE* driverObj = view->findGfObj(3, driver);
        view->attachObject(view->findGfObj(0xF, view->getMapObjID(2)), driverObj, "EX_wp_R");
    }
    mm::Vec3 scale;
    scale.x = scale.y = scale.z = 0.7f;
    {
        GfMenuModelView* view = m_pageContext.m_modelView;
        GfMenuModelView::setObjectScale(view->findGfObj(0xF, view->getMapObjID(1)), scale);
    }
    {
        GfMenuModelView* view = m_pageContext.m_modelView;
        GfMenuModelView::setObjectScale(view->findGfObj(0xF, view->getMapObjID(2)), scale);
    }
    {
        GfMenuModelView* view = m_pageContext.m_modelView;
        GfMenuModelView::setObjectDisp(view->findGfObj(0xF, view->getMapObjID(2)), false);
    }
    m_se[1] = GfMenuObjUtil::playSE("se_fld_allmap_706");
    refreshCrystalList();
    return true;
}


inline void GfMenuObjBladeCreate::dispGuideText(bool disp) {
    ui::UIObjectAcc guide(m_handle, "LAY_guide");
    guide.setDisp(disp);
}

inline void GfMenuObjBladeCreate::returnPage(unsigned int handle, PageContext* context, bool) {
    unsigned int page = 0;
    switch (context->m_page) {
    case 1:
        break;
    case 2:
        page = 1;
        break;
    case 3:
        page = context->m_skipPage2 ? 1 : 2;
        break;
    case 4:
        page = 3;
        break;
    default:
        return;
    }
    changePage(handle, context, page, true, true);
}

void GfMenuObjBladeCreate::BoosterSelectListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableFSInput(2);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        }
        break;
    case 6: {
        int index = event.m_param0;
        if (index != -1) {
            int prev = event.m_param1;
            m_owner->pad_1160->setIndex(index);
            if (index < m_context->m_boosterList->getSize()) {
                m_context->m_boosterList->setIndex(index);
                m_context->m_boosterList->getRowOffset();  // the original reads it and drops it
                GfMenuItemList* list = m_context->m_boosterList;
                int booster = list->getContents(list->getIndex(false)).m_id - Bdat::getIdTop(GfDataBdat::getFP(0xA2));
                if (booster >= 0 && booster < 4) {
                    if (prev != -1) {
                        m_context->m_modelView->removeEffect(prev + 9);
                    }
                    GfMenuModelView* view = m_context->m_modelView;
                    view->playEffect(index + 9, s_boosterEffects[booster][0], mm::Vec3(0.0f, 0.0f, 0.0f),
                                     view->findGfObj(0xF, view->getMapObjID(1)));
                }
            } else {
                m_context->m_modelView->removeEffect(prev + 9);
            }
            if (prev != -1 && index != prev) {
                GfMenuObjUtil::playSECommonCursor();
            }
        }
        break;
    }
    case 8: {
        int index = event.m_param0;
        if (event.m_param1 == 1) {
            if (index != -1) {
                if (index < m_context->m_boosterList->getSize()) {
                    GfMenuObject::sendOpenEvent(acc.searchChild("LAY_bst_select_dialog"), 0, 0.0f);
                } else {
                    // no booster: the skip item creates without one
                    ui::EventData send;
                    send.m_type = 0x101;
                    GfMenuObject::sendEvent(acc.m_handle, send, 0.0f);
                }
                GfMenuObject::disableFSInput();
                GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            }
        } else if (event.m_param1 == 2) {
            if (index < m_context->m_boosterList->getSize()) {
                m_context->m_modelView->stopEffect(index + 9);
            }
            GfMenuObject::sendCloseEvent(acc.searchSibiling("LAY_dr_idea"), 0, 0.0f);
            m_owner->returnPage(acc.m_handle, m_context, true);
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        }
        GfMenuObjUtil::playSECommonFromInput(event.m_param1);
        break;
    }
    case 0x21:
        if (m_context->m_boosterList->getSize() == 0) {
            GfMenuObject::setupInputSelection(acc.m_handle, -1, 0);
        } else if (m_context->m_prevPage == 1) {
            GfMenuObject::resetInputSelection(acc.m_handle);
            GfMenuObject::setupInputSelection(acc.m_handle, 0, m_context->m_boosterList->getSize() + 1);
            ui::UIObjectAcc skip(acc.m_handle, "LAY_bst_sel_item_skip");
            mm::mtl::FixStr<32> item;
            item.format("item_%d", m_context->m_boosterList->getSize() + 1);
            acc.setLayout(skip.m_handle, item.m_str);
        }
        m_owner->m_boosterNumbers[0] = 0;
        m_owner->m_boosterNumbers[1] = 0;
        m_owner->m_boosterNumbers[2] = 0;
        m_owner->pad_1180 = 0;
        m_owner->pad_1170 = 0;
        fadeIn(acc.m_handle);
        m_owner->setGuideText(0x29);
        GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_dr_idea"), 0, 0.0f);
        m_owner->m_number->m_value = 0;
        m_owner->updateIdea(false);
        break;
    case 0x22:
        fadeOut(acc.m_handle);
        break;
    case 0x101:
        GfMenuObject::sendCloseEvent(acc.searchSibiling("LAY_dr_idea"), 0, 0.0f);
        m_owner->nextPage(acc.m_handle, m_context, true);
        break;
    case 0x102: {
        int cursor = m_owner->pad_1160->getIndex(false);
        m_context->m_modelView->stopEffect(cursor + 9);
        GfMenuObjUtil::playVibration(static_cast<fw::VibrationID>(0xB), 1.0f);
        ui::EventData send;
        send.m_type = 0x101;
        GfMenuObject::sendEvent(acc.m_handle, send, 0.44f);
        break;
    }
    case 0x103:
        if (event.m_param0 == 1) {
            m_owner->pad_1160->getIndex(false);  // the original reads it and drops it
            GfMenuItemList* list = m_context->m_boosterList;
            int booster = list->getContents(list->getIndex(false)).m_id - Bdat::getIdTop(GfDataBdat::getFP(0xA2));
            GfMenuModelView* view = m_context->m_modelView;
            view->playEffect(0xD, s_boosterEffects[booster][1], mm::Vec3(0.0f, 0.0f, 0.0f),
                             view->findGfObj(0xF, view->getMapObjID(1)));
            GfMenuObjUtil::playSE(s_boosterSEs[booster]);
            ui::EventData send;
            send.m_type = 0x102;
            GfMenuObject::sendEvent(acc.m_handle, send, 0.56f);
        } else {
            GfMenuObject::enableFSInput(2);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
            m_owner->setGuideText(0x29);
        }
        break;
    }
}

void GfMenuObjBladeCreate::ConfirmListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        break;
    case 0x21:
        m_context->m_confirmed = false;
        m_context->m_callContext->reset();
        if (m_owner->pad_11B4) {
            GfMenuObjCommonText::open(m_context->m_callContext, 0x114, 0);
        } else {
            GfMenuObjCommonText::open(m_context->m_callContext, 0x113, 0);
        }
        GfMenuObject::setCallContextEventHandler(m_context->m_callContext, acc.m_handle);
        GfMenuObjOperationInfo::setDisp(false);
        m_owner->dispGuideText(false);
        if (!m_owner->pad_11B4) {
            GfMenuObjMainMenu2::setCloseKeyEnable(false);
        }
        break;
    case 0x22:
        break;
    case 0x41: {
        int id = event.m_param0;
        if (m_context->m_callContext->m_id == id) {
            // the text's answer: m_param3 1 with m_param2 1 for a yes, m_param3 0 on a decision (m_param2 0: next)
            unsigned long answer = event.m_param23;
            int choice = static_cast<int>(answer);
            switch (static_cast<int>(answer >> 32)) {
            case 0:
                if ((answer & 0xFFFFFFFF) == 0) {
                    ui::EventData send;
                    send.m_type = 0x22;
                    GfMenuObject::sendEvent(acc.searchSibiling("LAY_dr_idea"), send, 0.0f);
                    m_owner->nextPage(acc.m_handle, m_context, true);
                } else {
                    GfMenuObjOperationInfo::setDisp(true);
                    m_owner->dispGuideText(true);
                    m_owner->returnPage(acc.m_handle, m_context, true);
                    if (!m_owner->pad_11B4) {
                        GfMenuObjMainMenu2::setCloseKeyEnable(true);
                    }
                }
                break;
            case 1:
                if (choice == 1) {
                    m_context->m_confirmed = true;
                }
                break;
            }
        }
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjBladeCreate::seqSave() {
    m_saveReq = GfReqCommand::reqSave(static_cast<SAVESLOT>(22));
    GfMenuObjFade::dispSaving(true, 0);
    return true;
}

bool GfMenuObjBladeCreate::seqSaveWait() {
    if (GfReqManager::isValid(m_saveReq)) {
        return false;
    }
    GfMenuObjFade::dispSaving(false, 0);
    m_saveReq = -1;
    return true;
}

bool GfMenuObjBladeCreate::seqCreateStart() {
    GfMenuDriverList* list = m_pageContext.m_driverList;
    GfMenuModelView* view = m_pageContext.m_modelView;
    GF_OBJ_HANDLE* driverObj = view->findGfObj(3, list->getContents(list->getIndex(false)).m_driver);
    {
        GfMenuModelView* view = m_pageContext.m_modelView;
        mm::Vec3 pos(0.0f, 0.0f, 0.0f);
        view->playEffect(6, "bc_20_030", pos, view->findGfObj(0xF, view->getMapObjID(1)));
    }
    m_pageContext.m_modelView->playEffectFromCAS(0, "bc_20_000", driverObj);
    m_seq.addJob(&GfMenuObjBladeCreate::seqCreateSetup);
    list = m_pageContext.m_driverList;
    unsigned int driver = list->getContents(list->getIndex(false)).m_driver;
    for (unsigned int i = 0; i < m_pageContext.m_driverList->getSize(); i++) {
        if (driver != m_pageContext.m_driverList->getContents(i).m_driver) {
            GfObjAcc acc(m_pageContext.m_modelView->findGfObj(3, m_pageContext.m_driverList->getContents(i).m_driver));
            acc.setDisp(static_cast<OBJDISP>(1), false);
        }
    }
    const char* motion = nullptr;
    switch (driver) {
    case 1:
        motion = "mnu_blade_create_rex_01";
        break;
    case 2:
        motion = "mnu_blade_create_nia_01";
        break;
    case 3:
        motion = "mnu_blade_create_sieg_01";
        break;
    case 6:
        motion = "mnu_blade_create_melef_01";
        break;
    }
    if (motion == nullptr) {
        return true;
    }
    fw::Transform& transform =
        GfMenuModelView::getObjectTransform(m_pageContext.m_modelView->findGfObj(3, driver));
    const mm::Quat& q = transform.rotation;
    float x2 = q.x + q.x;
    float y2 = q.y + q.y;
    float z2 = q.z + q.z;
    float xx = q.x * x2;
    float xy = q.x * y2;
    float xz = q.x * z2;
    float yy = q.y * y2;
    float yz = q.y * z2;
    float zz = q.z * z2;
    float wx = q.w * x2;
    float wy = q.w * y2;
    float wz = q.w * z2;
    float m00 = 1.0f - (yy + zz);
    float m01 = xy + wz;
    float m02 = xz - wy;
    float m11 = 1.0f - (xx + zz);
    float m20 = xz + wy;
    float m21 = yz - wx;
    float m22 = 1.0f - (xx + yy);
    mm::Vec3 r;
    r.x = mm::asin(-m21);
    if (r.x < 1.57079637f) {
        if (r.x > -1.57079637f) {
            r.z = ::atan2f(m01, m11);
            r.y = ::atan2f(m20, m22);
        } else {
            r.z = -::atan2f(m02, m00);
            r.y = 0.0f;
        }
    } else {
        r.z = ::atan2f(m02, m00);
        r.y = 0.0f;
    }
    m_pageContext.m_modelView->playCameraMotion(motion, transform.position, r.y);
    return true;
}

bool GfMenuObjBladeCreate::seqCreateSkip() {
    if (GfMenuManager::isFading()) {
        return false;
    }
    GfMenuModelView* view = m_pageContext.m_modelView;
    GfMenuDriverList* list = m_pageContext.m_driverList;
    unsigned int driver = list->getContents(list->getIndex(false)).m_driver;
    view->sendObjectCommand(view->findGfObj(3, driver), "C_idle");
    for (unsigned int i = 0; i < m_pageContext.m_driverList->getSize(); i++) {
        unsigned int other = m_pageContext.m_driverList->getContents(i).m_driver;
        GfObjAcc acc(m_pageContext.m_modelView->findGfObj(3, other));
        acc.setDisp(static_cast<OBJDISP>(1), false);
    }
    {
        GfMenuModelView* view = m_pageContext.m_modelView;
        view->delGfObj(0xF, view->getMapObjID(1));
    }
    {
        GfMenuModelView* view = m_pageContext.m_modelView;
        view->delGfObj(0xF, view->getMapObjID(2));
    }
    if (m_se[1] != 0) {
        GfMenuObjUtil::stopSE(m_se[1], 0.0f);
        m_se[1] = 0;
    }
    GfMenuFade::setFade(2, 30, mm::Col4(0.0f, 0.0f, 0.0f, 0.0f));
    pad_1128.clear();
    m_seq.addJob(&GfMenuObjBladeCreate::seqCreateSkipToReslt);
    return true;
}

void GfMenuObjBladeCreate::ResultListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableFSInput(5);
            GfMenuObjOperationInfo::open(acc.m_handle, 0, 0, 0);
            GfMenuObjOperationInfo::setGuideDisp(false);
            m_owner->m_bgm = GfMenuObjUtil::playBGM(0x14, false, static_cast<fw::SoundCategory>(0x11));
        }
        break;
    case 8:
        if (event.m_param1 == 1) {
            m_owner->m_seq.addJob(&GfMenuObjBladeCreate::seqResultStart);
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            GfMenuObject::disableFSInput();
        }
        break;
    case 0x21: {
        fadeIn(acc.m_handle);
        GfMenuObjCmnStatus::openBlStatus(2, -1);
        {
            ui::UIObjectAcc image(acc.m_handle, "IMG_result_bl_img");
            unsigned int blade = GfMenuReference::getReferenceBladeID(0);
            acc.setLayout(image.m_handle, "blade");
            GfMenuObjUtil::ImageParam imageParam;
            if (GfMenuObjUtil::getImageParam(1, blade, imageParam, 1)) {
                mm::Vec2 scale;
                image.getScale(scale);
                scale.x *= imageParam.m_scale;
                scale.y *= imageParam.m_scale;
                image.setScale(scale);
                GfMenuObjUtil::addPos(image.m_handle, imageParam.m_x, imageParam.m_y);
            }
            GfMenuObjUtil::CtrlParam fade;
            fade.m_eventId = 1;
            fade.m_methods = 0x10000000;
            fade.m_motionLib = "cmn_fade_motion_lr";
            fade.m_motion = "fade_in_r";
            fade.m_startFlags = 8;
            GfMenuObjUtil::startCtrl(image.m_handle, fade, nullptr);
        }
        GfMenuObjUtil::playJingle(GfDataBlade::isCommonBlade(GfMenuReference::getReferenceBladeID(0)) ? 0xD : 0xC);
        break;
    }
    case 0x22: {
        GfMenuObjCmnStatus::closeBlStatus();
        fadeOut(acc.m_handle);
        break;
    }
    }
}

bool GfMenuObjBladeCreate::seqResultStart() {
    pad_1120 = false;
    m_seq.addJob(&GfMenuObjBladeCreate::seqResultConfirm);
    return true;
}

void GfMenuObjBladeCreate::IdeagramListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    if (event.m_type == 1) {
        acc.setDisp(false);
        m_shown = 0;
    } else if (event.m_type == 0x21) {
        if (m_shown == 0) {
            fadeIn(acc.m_handle);
            m_shown = 1;
        }
    } else if (event.m_type == 0x22) {
        if (m_shown == 1) {
            fadeOut(acc.m_handle);
            m_shown = 0;
        }
    } else {
        ui::UIObjectListener::reciveEvent(event, handle);
    }
}

void GfMenuObjBladeCreate::BoosterNumListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_shown = 0;
        m_decided = 1;
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableFSInput(6);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        } else if (event.m_param0 == 2) {
            ui::EventData send;
            send.m_type = 0x103;
            send.m_param0 = m_decided;
            GfMenuObject::sendEvent(acc.getParentHandle(), send, 0.0f);
        }
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        if (index != -1) {
            m_owner->m_number->setValue(index + 1);
            m_owner->updateIdea(false);
        }
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSE(0x19);
        }
        break;
    }
    case 8:
        if (event.m_param1 == 1) {
            m_owner->updateIdea(true);
            m_decided = 1;
            GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
        } else if (event.m_param1 == 2) {
            GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
            m_owner->m_number->m_value = 0;
            m_owner->updateIdea(false);
        }
        GfMenuObjUtil::playSECommonFromInput(event.m_param1);
        break;
    case 0x21:
        if (m_shown == 0) {
            fadeIn(acc.m_handle);
            m_shown = 1;
            m_decided = 0;
            GfMenuItemList* list = m_owner->m_pageContext.m_boosterList;
            // the count is read signed (ldrsh) and capped unsigned
            short have = list->getContents(list->getIndex(false)).m_count;
            unsigned int count = have;
            if (count > 5) {
                count = 5;
            }
            m_owner->m_number->m_min = 1;
            m_owner->m_number->m_max = count;
            m_owner->m_number->m_value = 1;
            GfMenuObject::resetInputSelection(acc.m_handle);
            GfMenuObject::setupInputSelection(acc.m_handle, 0, count);
        }
        m_owner->setGuideText(0x39);
        break;
    case 0x22:
        if (m_shown == 1) {
            GfMenuObject::disableFSInput();
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            fadeOut(acc.m_handle);
            m_shown = 0;
        }
        break;
    }
}

bool GfMenuObjBladeCreate::seqCreateSetup() {
    m_seq.addJob(&GfMenuObjBladeCreate::seqCreateStartDriver);
    m_seq.addWait(120);
    m_seq.addJob(&GfMenuObjBladeCreate::seqCreateStartSE);
    m_seq.addJob(&GfMenuObjBladeCreate::seqCreateWaitDriver);
    m_seq.addJob(&GfMenuObjBladeCreate::seqCreateWaitFade);
    m_seq.addJob(&GfMenuObjBladeCreate::seqCreateBuildBlade);
    pad_1148 = 0;
    return true;
}

bool GfMenuObjBladeCreate::seqCreateSkipToReslt() {
    if (GfMenuManager::isFading()) {
        return false;
    }
    nextPage(m_handle, &m_pageContext, false);
    return true;
}

bool GfMenuObjBladeCreate::seqCreateStartDriver() {
    GfMenuDriverList* list = m_pageContext.m_driverList;
    GfMenuModelView* view = m_pageContext.m_modelView;
    unsigned int driver = list->getContents(list->getIndex(false)).m_driver;
    view->sendObjectCommand(view->findGfObj(3, driver), "C_hold_00");
    GfMenuObjUtil::playSE("se_fld_allmap_711");
    return true;
}

bool GfMenuObjBladeCreate::seqCreateStartSE() {
    if (m_se[1] != 0) {
        GfMenuObjUtil::stopSE(m_se[1], 0.0f);
        m_se[1] = 0;
    }
    m_se[2] = GfMenuObjUtil::playSE("se_fld_allmap_715");
    return true;
}

bool GfMenuObjBladeCreate::seqCreateWaitDriver() {
    GfMenuDriverList* list = m_pageContext.m_driverList;
    unsigned int driver = list->getContents(list->getIndex(false)).m_driver;
    GfMenuModelView* view = m_pageContext.m_modelView;
    if (strcmp(view->getObjectAnimationState(view->findGfObj(3, driver)), "S_hold_01") != 0) {
        return false;
    }
    GfMenuFade::setFade(2, 30, mm::Col4(0.0f, 0.0f, 0.0f, 0.0f));
    return true;
}

bool GfMenuObjBladeCreate::seqCreateWaitFade() {
    return !GfMenuManager::isFading();
}

bool GfMenuObjBladeCreate::seqCreatePlayJingle() {
    GfMenuObjUtil::stopBGM(m_bgm, 1.0f);
    m_bgm = 0;
    return true;
}

bool GfMenuObjBladeCreate::seqCreatePlayBgmAfter() {
    return true;
}

bool GfMenuObjBladeCreate::seqCreateCtrlBlade() {
    unsigned int blade = *pad_1128.begin();
    switch (pad_1144) {
    case 0: {
        GfMenuModelView* view = m_pageContext.m_modelView;
        view->setObjectVanishRatio(view->findGfObj(4, blade), 1.0f);
        view = m_pageContext.m_modelView;
        view->setObjectVanishParam(view->findGfObj(4, blade), 9);
        GfMenuModelView::CtrlParam param(m_pageContext.m_modelView->findGfObj(4, blade), 0.3f, false);
        param.setAddPosY(0.2f);
        if (pad_1128.size() == 1) {
            param.setMoveVanish(0.5f);
        } else {
            param.setMoveVanish(0.7f);
        }
        m_pageContext.m_modelView->startObjectCtrl(param);
        GfMenuModelView* driverView = m_pageContext.m_modelView;
        GfMenuDriverList* list = m_pageContext.m_driverList;
        GF_OBJ_HANDLE* driver = driverView->findGfObj(3, list->getContents(list->getIndex(false)).m_driver);
        if (pad_1148 == 0) {
            m_pageContext.m_modelView->playEffectFromCAS(1, "bc_20_010", driver);
            pad_1148++;
        } else if (pad_1128.size() > 1) {
            m_pageContext.m_modelView->playEffectFromCAS(pad_1148 + 1, "bc_20_010", driver);
            pad_1148++;
        } else {
            GF_OBJ_HANDLE* obj = m_pageContext.m_modelView->findGfObj(4, blade);
            m_pageContext.m_modelView->playEffectFromCAS(5, "bc_20_020", driver);
            m_pageContext.m_modelView->playEffectFromCAS(7, "bc_20_040", obj);
        }
        GfMenuObjUtil::playVibration(static_cast<fw::VibrationID>(16), 1.0f);
        GfMenuObjUtil::playSE("se_fld_allmap_712");
        pad_114C = 15;
        break;
    }
    case 1: {
        GfMenuModelView::CtrlParam param(m_pageContext.m_modelView->findGfObj(4, blade), 0.4f, false);
        param.setAddPosY(0.2f);
        m_pageContext.m_modelView->startObjectCtrl(param);
        break;
    }
    case 2: {
        GfMenuModelView::CtrlParam param(m_pageContext.m_modelView->findGfObj(4, blade), 0.3f, false);
        if (pad_1128.size() == 1) {
            param.setAddPosY(-0.5f);
            param.setMoveSclX(0.001f);
            param.setMoveSclZ(0.001f);
        } else {
            param.setAddPosY(0.2f);
            param.setMoveVanish(1.0f);
            GfMenuObjUtil::playSE("se_fld_allmap_713");
        }
        m_pageContext.m_modelView->startObjectCtrl(param);
        break;
    }
    }
    m_seq.addJob(&GfMenuObjBladeCreate::seqCreateWaitBlade);
    return true;
}

bool GfMenuObjBladeCreate::seqCreateWaitBlade() {
    unsigned int blade = *pad_1128.begin();
    GfMenuModelView* view = m_pageContext.m_modelView;
    if (view->isObjectCtrlBusy(view->findGfObj(4, blade))) {
        return false;
    }
    if (pad_1144 < 2) {
        pad_1144++;
        m_seq.addJob(&GfMenuObjBladeCreate::seqCreateCtrlBlade);
    } else {
        m_pageContext.m_modelView->delGfObj(4, blade);
        pad_1128.erase(pad_1128.begin());
        if (!pad_1128.empty()) {
            pad_1144 = 0;
            m_seq.addJob(&GfMenuObjBladeCreate::seqCreateBuildBlade);
        } else {
            GfMenuFade::setFade(2, 60, mm::Col4::white);
            GfMenuObjUtil::playSE("se_fld_allmap_714");
            m_seq.addJob(&GfMenuObjBladeCreate::seqCreateWaitFade);
            m_seq.addJob(&GfMenuObjBladeCreate::seqCreatePlayJingle);
            m_seq.addWait(30);
            m_seq.addJob(&GfMenuObjBladeCreate::seqCreatePlayBgmAfter);
            m_seq.addJob(&GfMenuObjBladeCreate::seqCreateStartEvent);
            pad_1128.clear();
        }
    }
    return true;
}

bool GfMenuObjBladeCreate::seqCreateStartEvent() {
    for (unsigned int i = 0; i < m_pageContext.m_driverList->getSize(); i++) {
        unsigned int driver = m_pageContext.m_driverList->getContents(i).m_driver;
        GfObjAcc acc(m_pageContext.m_modelView->findGfObj(3, driver));
        acc.setDisp(static_cast<OBJDISP>(1), false);
    }
    unsigned int event = GfDataBlade::getCreateEvent(m_pageContext.m_blade);
#line 3049
    m_eventSignal = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfSequentialPlaySignal();
    GfPlayFactory::createBlEvent(event, 1, m_pageContext.m_blade, m_eventSignal);
    m_seq.addJob(&GfMenuObjBladeCreate::seqCreateWaitEvent);
    {
        GfMenuModelView* view = m_pageContext.m_modelView;
        view->delGfObj(0xF, view->getMapObjID(1));
    }
    {
        GfMenuModelView* view = m_pageContext.m_modelView;
        view->delGfObj(0xF, view->getMapObjID(2));
    }
    m_pageContext.m_modelView->stopEffect(6);
    m_pageContext.m_modelView->stopEffect(7);
    m_pageContext.m_modelView->stopEffect(0);
    m_pageContext.m_modelView->stopEffect(pad_1148 + 1);
    if (m_se[2] != 0) {
        GfMenuObjUtil::stopSE(m_se[2], 0.0f);
        m_se[2] = 0;
    }
    return true;
}

bool GfMenuObjBladeCreate::seqCreateWaitEvent() {
    if (m_eventSignal->m_active) {
        return false;
    }
    if (m_eventSignal != nullptr) {
        delete m_eventSignal;
        m_eventSignal = nullptr;
    }
    GfMenuObjBladeName::close();
    nextPage(m_handle, &m_pageContext, false);
    return true;
}

bool GfMenuObjBladeCreate::seqResultConfirm() {
    if (!pad_1120) {
        if (pad_11B4 && pad_11BC) {
            GfMenuDriverList* list = m_pageContext.m_driverList;
            unsigned int driver = list->getContents(list->getIndex(false)).m_driver;
            SCOM_PARTY_ADD::addBlade(m_pageContext.m_blade, driver, 1);
            if (!pad_11B4) {
                GfMenuObjMainMenu2::setCloseKeyEnable(true);
            }
            GfMenuObjOperationInfo::close();
            returnFSSubLayer(this);
            return true;
        }
        GfMenuManager::openCommonWindow(7);
        pad_1120 = true;
    }
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    unsigned short result = GfMenuManager::getCommonWindowResult();
    if (result != 0) {
        if (!pad_11B4) {
            m_seq.addJob(&GfMenuObjBladeCreate::seqResultEnd);
        } else {
            GfMenuObjMainMenu2::setCloseKeyEnable(true);
            GfMenuObjOperationInfo::close();
            returnFSSubLayer(this);
        }
        pad_1120 = false;
        return true;
    }
    if (!pad_11B4 || pad_11B8 == 0) {
        GfMenuObjBladeSet2::setCloseToReturn();
    } else {
        GfMenuObjBladeSet2::setCloseToFSClose();
    }
    if (pad_11B4) {
        GfMenuObjMainMenu2::setCloseKeyEnable(true);
    }
    changeFSSubLayer(m_handle, GfMenuFullScreen::getLayerGroup(m_fsLayer), getMenuLayerID(0x1E), true);
    return true;
}

bool GfMenuObjBladeCreate::seqResultEnd() {
    unsigned int blade = m_pageContext.m_blade;
    m_pageContext.m_modelView->delGfObj(4, blade);
    m_pageContext.m_modelView->stopCameraMotion();
    if (m_pageContext.m_confirmed) {
        m_pageContext.m_modelView->popCamera(0.5f);
    }
    nextPage(m_handle, &m_pageContext, false);
    for (unsigned int i = 0; i < m_pageContext.m_driverList->getSize(); i++) {
        unsigned int driver = m_pageContext.m_driverList->getContents(i).m_driver;
        GfObjAcc acc(m_pageContext.m_modelView->findGfObj(3, driver));
        acc.setDisp(static_cast<OBJDISP>(1), true);
    }
    return true;
}

void GfMenuObjBladeCreate::registOpenParam(const OpenParam& param) {
    GfMenuTypes::Param layer;
    layer.m_menuId = param.m_value;
    GfMenuFullScreen::registLayerParam(0x14, layer);
}

void GfMenuObjBladeCreate::openCreatedBladeName(GfMenuCallContext* context) {
    GfMenuObjBladeName::open(context);
}

GfMenuBladeCreateCamera::~GfMenuBladeCreateCamera() {}

const char* GfMenuBladeCreateCamera::getName() const {
    return "GfMenuBladeCreateCamera";
}
}  // namespace gf

// instantiated for gf::GfMenuObjBladeCreate::initialize, gf::GfMenuObjMainMenu2::openChrChangeSub, gf::GfMenuObjPartyForm3::DriverSelectListener::reciveEvent (not written yet)
template mm::mtl::Vector<gf::MenuDriverInfo>::iterator mm::mtl::Vector<gf::MenuDriverInfo>::erase(gf::MenuDriverInfo*);

template bool gf::GfMenuSequence<gf::GfMenuObjBladeCreate, 20>::wait();

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjBladeCreate, 20>>(const mm::mtl::Delegate<bool()>*);

namespace gf {

mm::mtl::RTTI GfMenuBladeCreateCamera::m_rtti("GfMenuBladeCreateCamera", &::fw::Camera::m_rtti, nullptr);

}  // namespace gf
