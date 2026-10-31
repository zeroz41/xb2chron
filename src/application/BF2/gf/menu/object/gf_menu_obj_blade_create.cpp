#include "gf/FileStaticVec3.h"
#include "classes/gf/GfMenuObjBladeCreate.h"
#include "classes/gf/GfMenuModelView.h"
#include "gf/GfReqCommand.h"
#include "classes/gf/GfMenuBladeCreateCamera.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "classes/gf/GfMenuFullScreen.h"
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
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuObjCmnStatus.h"
#include "classes/gf/GfMenuReference.h"
#include "gf/GfDataBlade.h"
#include "mm/Vec2.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfSound.h"
#include "classes/ui/UIObjectAcc.h"
#include "ui/EventData.h"

namespace gf {

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
    return !m_modelView->isLoading();
}

bool GfMenuObjBladeCreate::seqEnd() {
    enableFSInput(m_page);
    return true;
}

void GfMenuObjBladeCreate::update() {
    m_seq.update();
    if (m_modelView != nullptr) {
        m_modelView->update();
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
            GfMenuItemList* list = m_owner->m_boosterList;
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

bool GfMenuObjBladeCreate::seqCreateStartSE() {
    if (m_se[1] != 0) {
        GfMenuObjUtil::stopSE(m_se[1], 0.0f);
        m_se[1] = 0;
    }
    m_se[2] = GfMenuObjUtil::playSE("se_fld_allmap_715");
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

mm::mtl::RTTI GfMenuBladeCreateCamera::m_rtti("GfMenuBladeCreateCamera", &::fw::Camera::m_rtti, nullptr);

}  // namespace gf
