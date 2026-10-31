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

bool GfMenuObjBladeCreate::seqResultStart() {
    pad_1120 = false;
    m_seq.addJob(&GfMenuObjBladeCreate::seqResultConfirm);
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
