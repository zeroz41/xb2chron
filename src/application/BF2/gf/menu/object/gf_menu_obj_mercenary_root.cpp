#include "classes/gf/GfMenuObjMercenaryRoot.h"
#include "classes/gf/GfMenuObjMercenaryRoot/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuSoundManager.h"
#include "classes/gf/GfSound.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfDataMercenaries.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixedVector.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjMercenaryRoot::GfMenuObjMercenaryRoot(unsigned int handle)
    : GfMenuObject(handle), m_bgImage(-1), m_seq(this), m_bgm(0) {}

GfMenuObjMercenaryRoot::~GfMenuObjMercenaryRoot() {}

void GfMenuObjMercenaryRoot::openBg(int image) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x4D));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_param0 = image;
        event.m_param1 = 0;
        event.m_type = 0x21;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjMercenaryRoot::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    GfMenuObject::attachExternalCall(0x4D, acc.m_handle);
#line 88
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    // the original stores the count after the listener's own fields, not with its base
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObjMainMenu2::setCloseKeyEnable(false);
    GfMenuObject::initialize();
}

void GfMenuObjMercenaryRoot::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjMercenaryRoot::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjMercenaryRoot::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        bool reward = false;
        for (unsigned int i = 0; i < GfDataMercenaries::getTeamNum(); i++) {
            GfDataMercenaries::Team* team = GfDataMercenaries::getTeamByIndex(i);
            if (team != nullptr && GfDataMercenaries::isTeamStateReward(team->m_teamId)) {
                reward = true;
                break;
            }
        }
        if (reward) {
            GfMenuObject::changeFSSubLayer(acc.m_handle, 2, 0x37, true);
        } else {
            GfMenuObject::changeFSSubLayer(acc.m_handle, 2, 0x34, true);
        }
        acc.setDispChild(false, "IMG_bg");
        acc.setDispChild(false, "IMG_bg_front");
        if (GfSound::get() != nullptr) {
            GfMenuSoundManager::fadeOutFieldBgm(0.5f);
            m_owner->m_bgm = GfMenuObjUtil::playBGM(22, false, fw::SoundCategory(17));
        } else {
            m_owner->m_bgm = 0;
        }
        break;
    }
    case 2:
        if (GfSound::get() != nullptr) {
            GfMenuSoundManager::fadeFieldBgm(1.0f, 0.5f);
            GfMenuObjUtil::stopBGM(m_owner->m_bgm, 1.0f);
            m_owner->m_bgm = 0;
        }
        acc.setTerm();
        break;
    case 3:
        if (event.m_param0 == 1) {
            ui::UIObjectAcc bg(acc.m_handle, "IMG_bg");
            bg.setImageIndex(m_owner->m_bgImage);
            m_owner->m_seq.addJob(&GfMenuObjMercenaryRoot::seqWaitBGStream);
        }
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 0x21: {
        int image = event.m_param0;
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 1;
        param.m_time = 0.25f;
        param.m_eventId = 1;
        if (m_owner->m_bgImage == -1) {
            ui::UIObjectAcc bg(acc.m_handle, "IMG_bg");
            bg.setImageIndex(image);
            GfMenuObjUtil::startCtrl(acc.m_handle, param, "IMG_bg");
        } else {
            ui::UIObjectAcc front(acc.m_handle, "IMG_bg_front");
            front.setImageIndex(image);
            int ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, "IMG_bg_front");
            GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        }
        m_owner->m_bgImage = image;
        m_owner->m_seq.clear();
        break;
    }
    case 0x22: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_time = 0.25f;
        param.m_eventId = 2;
        int ctrl = GfMenuObjUtil::startCtrl(acc.m_handle, param, "IMG_bg");
        GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        acc.setDispChild(false, "IMG_bg_front");
        break;
    }
    }
}

bool GfMenuObjMercenaryRoot::seqWaitBGStream() {
    ui::UIObjectAcc bg(m_handle, "IMG_bg");
    if (bg.isStreaming()) {
        return false;
    }
    ui::UIObjectAcc front(m_handle, "IMG_bg_front");
    front.setDisp(false);
    return true;
}

}  // namespace gf
