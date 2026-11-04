#include "ui/EventData.h"
#include "ui/UIUtil.h"
#include "fw/PadData.h"
#include "gf/GfMenuSequence.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjTutorial.h"
#include "classes/gf/GfMenuObjHelpHud.h"
#include "classes/gf/GfMenuObjHelpHud/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"

namespace gf {

GfMenuObjHelpHud::GfMenuObjHelpHud(unsigned int handle)
    : GfMenuObject(handle), m_page(0), m_seq(this), m_jobStarted(false) {}

GfMenuObjHelpHud::~GfMenuObjHelpHud() {}

// sends the help HUD (external call 0x84) event 0x101 (its listener enables input and shows LAY_help), unless
// add-on menu layer 3 is usable
void GfMenuObjHelpHud::enable() {
    if (GfMenuObjUtil::isValidExpansion(3)) {
        return;
    }
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x84));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x101;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

// sends it event 0x102 (its listener disables input and drops the page shown)
void GfMenuObjHelpHud::disable() {
    if (GfMenuObjUtil::isValidExpansion(3)) {
        return;
    }
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x84));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x102;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjHelpHud::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
#line 117
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    // the original stores the count after the listener's own fields, not with its base
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObject::attachExternalCall(0x84, acc.m_handle);
    GfMenuObject::initialize();
}

void GfMenuObjHelpHud::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjHelpHud::update() {
    if (m_page != 0) {
        if (GfMenuManager::isOpenFullScreen()) {
            ui::UIObjectAcc image(m_handle, "IMG_help");
            image.setImageIndex(0);
            m_page = 0;
            m_seq.clear();
        } else if (GfMenuObjTutorial::isWaiting()) {
            m_page = 0;
            m_seq.clear();
            m_seq.addJob(&GfMenuObjHelpHud::seqPageFadeOut);
            m_seq.addJob(&GfMenuObjHelpHud::seqPageLoad);
        }
    }
    m_seq.update();
    GfMenuObject::update();
}

bool GfMenuObjHelpHud::seqPageFadeOut() {
    ui::UIObjectAcc image(m_handle, "IMG_help");
    if (!m_jobStarted) {
        ctrlFadeOut(image.m_handle);
        m_jobStarted = true;
        return false;
    }
    int ctrl = GfMenuObjUtil::getCtrlID(image.m_handle);
    if (ctrl != -1 && GfMenuObjUtil::isBusyCtrl(ctrl)) {
        return false;
    }
    m_jobStarted = false;
    return true;
}

bool GfMenuObjHelpHud::seqPageLoad() {
    ui::UIObjectAcc image(m_handle, "IMG_help");
    if (!m_jobStarted) {
        if (m_page == 0) {
            image.setImageIndex(0);
            image.setDisp(false);
            return true;
        }
        image.setImageIndex(m_page);
        m_jobStarted = true;
    }
    if (image.isStreaming()) {
        return false;
    }
    m_seq.addJob(&GfMenuObjHelpHud::seqPageFadeIn);
    m_jobStarted = false;
    return true;
}

void GfMenuObjHelpHud::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::disableInput(acc.m_handle);
        break;
    case 8: {
        if (!m_owner->m_seq.m_jobs.empty()) {
            GfMenuObjUtil::playSECommon(2);
            return;
        }
        int button = event.m_param1;
        unsigned int page = m_owner->m_page;
        if (!GfMenuManager::isFieldHudInputEnable() || (ui::UIUtil::getPadData()->m_btn & 0x10) != 0) {
            return;
        }
        if (button == 9) {
            if (m_owner->m_page == 0) {
                m_owner->m_page = 1;
            } else if (m_owner->m_page < 1 || m_owner->m_page > 2) {
                m_owner->m_page = 1;
            } else {
                m_owner->m_page++;
                if (m_owner->m_page > 2) {
                    m_owner->m_page = 0;
                }
            }
        } else if (button == 10) {
            if (m_owner->m_page == 0) {
                m_owner->m_page = 3;
            } else if (m_owner->m_page < 3 || m_owner->m_page > 4) {
                m_owner->m_page = 3;
            } else {
                m_owner->m_page++;
                if (m_owner->m_page > 4) {
                    m_owner->m_page = 0;
                }
            }
        } else if (button == 11) {
            if (m_owner->m_page == 0) {
                m_owner->m_page = 5;
            } else if (m_owner->m_page < 5 || m_owner->m_page > 5) {
                m_owner->m_page = 5;
            } else {
                m_owner->m_page++;
                if (m_owner->m_page > 5) {
                    m_owner->m_page = 0;
                }
            }
        }
        if (page != m_owner->m_page) {
            m_owner->m_jobStarted = false;
            m_owner->m_seq.addJob(&GfMenuObjHelpHud::seqPageFadeOut);
            m_owner->m_seq.addJob(&GfMenuObjHelpHud::seqPageLoad);
        }
        return;
    }
    case 0x101:
        GfMenuObject::enableInput(acc.m_handle);
        acc.setDispChild(true, "LAY_help");
        acc.setDispChild(false, "IMG_help");
        break;
    case 0x102:
        GfMenuObject::disableInput(acc.m_handle);
        if (m_owner->m_page != 0) {
            m_owner->m_page = 0;
            m_owner->m_seq.clear();
            m_owner->m_seq.addJob(&GfMenuObjHelpHud::seqPageFadeOut);
            m_owner->m_seq.addJob(&GfMenuObjHelpHud::seqPageLoad);
        }
        break;
    }
    UIObjectListener::reciveEvent(event, handle);
}

bool GfMenuObjHelpHud::seqPageFadeIn() {
    ui::UIObjectAcc image(m_handle, "IMG_help");
    if (!m_jobStarted) {
        ctrlFadeIn(image.m_handle);
        m_jobStarted = true;
        return false;
    }
    int ctrl = GfMenuObjUtil::getCtrlID(image.m_handle);
    if (ctrl != -1 && GfMenuObjUtil::isBusyCtrl(ctrl)) {
        return false;
    }
    m_jobStarted = false;
    return true;
}

}  // namespace gf
