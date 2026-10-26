#include "classes/gf/GfMenuFullScreen.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfPartySelect.h"
#include "classes/gf/GfMenuObjCharSelect.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuObjBladeRelease.h"
#include "classes/gf/GfMenuObjBladeRelease/MainListener.h"
#include "classes/gf/GfMenuObjBladeRelease/ListListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "mm/Vec2.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjBladeRelease::GfMenuObjBladeRelease(unsigned int handle)
    : GfMenuObject(handle), pad_28(nullptr), m_bladeList(nullptr), m_list(nullptr), m_cursor(nullptr),
      m_context(nullptr), m_subContext(nullptr), m_seq(this), m_seqStep(false), m_subSeq(this), m_itemList(nullptr),
      pad_458(false), m_idList(nullptr), pad_468(false), pad_46C(-1), m_driverList(nullptr), m_hasRex(false),
      m_sortType(0), pad_4C8(0), m_voice(nullptr), m_voicePlayed(false) {
    m_itemList = GfMenuItemList::create();
    m_idList = GfMenuIDList::create();
    m_driverList = GfMenuDriverList::create();
    m_context = GfMenuCallContext::create();
    m_subContext = GfMenuCallContext::create();
}

GfMenuObjBladeRelease::~GfMenuObjBladeRelease() {
    if (m_driverList != nullptr) {
        m_driverList->release();
        m_driverList = nullptr;
    }
    if (m_idList != nullptr) {
        m_idList->release();
        m_idList = nullptr;
    }
    if (m_itemList != nullptr) {
        m_itemList->release();
        m_itemList = nullptr;
    }
    if (m_subContext != nullptr) {
        m_subContext->release();
        m_subContext = nullptr;
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_cursor != nullptr) {
        m_cursor->release();
        m_cursor = nullptr;
    }
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
    if (m_bladeList != nullptr) {
        m_bladeList->release();
        m_bladeList = nullptr;
    }
    if (pad_28 != nullptr) {
        pad_28->release();
        pad_28 = nullptr;
    }
}

void GfMenuObjBladeRelease::finalize() {
    if (m_voice != nullptr) {
        GfGameVoice::playStop(m_voice);
        m_voice = nullptr;
    }
    GfMenuObject::finalize();
}

void GfMenuObjBladeRelease::update() {
    m_seq.update();
    m_subSeq.update();
    GfMenuObject::update();
}

void GfMenuObjBladeRelease::MainListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    if (event.m_type == 1) {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
    } else if (event.m_type == 2) {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_out = 1;
        param.m_preset = 6;
        param.m_startFlag1 = true;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
    } else if (event.m_type == 0x101) {
        if (GfMenuReference::getReferenceBladeID(0) != 0) {
            m_owner->m_subSeq.clear();
            m_owner->m_subSeq.addJob(&GfMenuObjBladeRelease::seqOpenImage);
        }
    } else {
        ui::UIObjectListener::reciveEvent(event, handle);
    }
}

bool GfMenuObjBladeRelease::seqOpenImage() {
    ui::UIObjectAcc image(m_handle, "IMG_bl_img");
    if (image.isStreaming()) {
        image.setAlpha(0.0f);
        return false;
    }
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    unsigned int blade = GfMenuReference::getReferenceBladeID(0);
    acc.setLayout(image.m_handle, "bl_img01");
    GfMenuObjUtil::ImageParam imageParam;
    if (GfMenuObjUtil::getImageParam(1, blade, imageParam, 1)) {
        mm::Vec2 scale;
        image.getScale(scale);
        scale.x = imageParam.m_scale * scale.x;
        scale.y = imageParam.m_scale * scale.y;
        image.setScale(scale);
        GfMenuObjUtil::addPos(image.m_handle, imageParam.m_x, imageParam.m_y);
    }
    image.setAlpha(1.0f);
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "cmn_fade_motion_lr";
    param.m_motion = "fade_in_r";
    param.m_startFlags = 8;
    param.m_setDefault = true;
    GfMenuObjUtil::startCtrl(image.m_handle, param, nullptr);
    image.setAlpha(0.0f);
    return true;
}

bool GfMenuObjBladeRelease::seqConfirmBoosterGet() {
    if (m_itemList->getSize() != 0) {
        if (!m_seqStep) {
            m_context->reset();
            GfMenuObjCommonText::openGetItem(m_context, m_itemList);
            m_seqStep = true;
            return false;
        }
        if (!m_context->isTerm()) {
            return false;
        }
        m_seqStep = false;
    }
    return true;
}

bool GfMenuObjBladeRelease::seqResumeRelease() {
    ui::UIObjectAcc list(m_handle, "LAY_list_bl");
    GfMenuObject::sendOpenEvent(list.m_handle, 0, 0.0f);
    GfMenuObjMainMenu2::setCloseKeyEnable(true);
    ui::UIObjectAcc image(m_handle, "LAY_bl_img");
    image.setDisp(true);
    image.setAlpha(1.0f);
    return true;
}

bool GfMenuObjBladeRelease::seqSubMenuEnd() {
    ui::UIObjectAcc list(m_handle, "LAY_list_bl");
    GfMenuObject::sendOpenEvent(list.m_handle, 1, 0.0f);
    GfMenuObjMainMenu2::setCloseKeyEnable(true);
    m_seqStep = false;
    return true;
}

bool GfMenuObjBladeRelease::seqSubMenuOpenCustomize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    GfMenuObjUtil::setCommonFadeOut(acc.searchChild("LAY_list_bl"), 0, 0);
    GfMenuObjUtil::setCommonFadeOut(acc.searchChild("LAY_index"), 0, 0);
    const MenuBladeInfo& info = m_bladeList->getContents(m_bladeList->getIndex(false));
    GfMenuObjCharSelect::openBladeCustomize(acc.m_handle, info.m_blade, GfMenuFullScreen::getLayerGroup(m_fsLayer) + 1);
    m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuWaitLoadCustomize);
    return true;
}

bool GfMenuObjBladeRelease::seqSubMenuErrorOvdOnly() {
    if (!m_seqStep) {
        GfMenuManager::openCommonWindow(0xDD);
        m_seqStep = true;
        return false;
    }
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuOpen);
    m_seqStep = false;
    return true;
}

bool GfMenuObjBladeRelease::seqSubMenuErrorOvdLastOne() {
    if (!m_seqStep) {
        GfMenuManager::openCommonWindow(0xDE);
        m_seqStep = true;
        return false;
    }
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    m_seq.addJob(&GfMenuObjBladeRelease::seqSubMenuOpen);
    m_seqStep = false;
    return true;
}

}  // namespace gf
