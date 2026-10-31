#include "classes/gf/GfMenuObjEvTheater.h"
#include "classes/gf/GfMenuObjEvTheater/HeaderListener.h"
#include "classes/gf/GfMenuObjEvTheater/TUnk_B62178.h"
#include "classes/gf/GfMenuMsgList.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"
#include "ui/EventData.h"

namespace gf {

// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009C10C4). fn_7100401298's timezone images.
// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009C10B8). fn_7100404720's "cap_id" rows.
static const int s_capRows[3] = {1, 2, 9};
static const unsigned int s_timezoneImages[3] = {0, 2, 3};
// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009C10D0). fn_7100401598's element icons.
static const int s_elementIcons[7] = {0x9F, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA6};

bool GfMenuObjEvTheater::attach(GfMenuCallContext* context) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x19));
    if (acc.m_object != nullptr) {
        GfMenuObject::startCallContext(context, 0x19, acc.m_handle);
        return true;
    }
    return false;
}

void GfMenuObjEvTheater::fadeout(GfMenuCallContext* context) {
    if (GfMenuObjUtil::checkCCNext(context, 0x19)) {
        ui::EventData event;
        event.m_type = 0x101;
        GfMenuObject::sendEvent(context->m_handle, event, 0.0f);
    }
}

void GfMenuObjEvTheater::fadein(GfMenuCallContext* context) {
    if (GfMenuObjUtil::checkCCNext(context, 0x19)) {
        ui::EventData event;
        event.m_type = 0x102;
        GfMenuObject::sendEvent(context->m_handle, event, 0.0f);
    }
}

void GfMenuObjEvTheater::fn_71003FEE10(bool flag) {}

void GfMenuObjEvTheater::finalize() {
    GfMenuManager::fn_710035A718(false);
    GfMenuObject::finalize();
}

void GfMenuObjEvTheater::update() {
    m_seq.update();
    GfMenuObject::update();
}

bool GfMenuObjEvTheater::fn_7100401298(unsigned int value) {
    if (m_timezoneLocked) {
        return false;
    }
    ui::UIObjectAcc acc(m_handle, "IMG_select_set_ev_timezone");
    if (m_timezone != 0) {
        acc.setImageIndex(s_timezoneImages[m_timezone - 1]);
    } else {
        acc.setImageIndex(s_timezoneImages[value]);
        m_timezoneFromList = false;
    }
    return true;
}

bool GfMenuObjEvTheater::fn_7100401538(unsigned int value) {
    ui::UIObjectAcc acc(m_handle, "IMG_select_set_ev_face");
    acc.setImageIndex(GfMenuBdat::getIconImageIndex(value != 0 ? 0xD0 : 0xCF));
    return true;
}

bool GfMenuObjEvTheater::fn_7100401598(unsigned int value) {
    ui::UIObjectAcc acc(m_handle, "IMG_select_set_bl_elem");
    acc.setImageIndex(GfMenuBdat::getIconImageIndex(s_elementIcons[value]));
    return true;
}

bool GfMenuObjEvTheater::fn_71004015F8(unsigned int value) {
    ui::UIObjectAcc acc(m_handle, "IMG_select_set_bl_face");
    unsigned int icon = m_faceIcon;
    if (icon == 0x10E) {
        unsigned int next = value + 1;
        icon += next > 3 ? 0 : next;
    } else {
        icon += value;
    }
    acc.setImageIndex(GfMenuBdat::getIconImageIndex(icon));
    return true;
}

bool GfMenuObjEvTheater::fn_710040166C(unsigned int value) {
    m_number->m_value = value;
    return true;
}

void GfMenuObjEvTheater::HeaderListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        m_shown = 0;
        break;
    case 0x21:
        if (m_shown == 0) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_r";
            param.m_setDefault = true;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, "LAY_header_body");
            {
                ui::UIObjectAcc base(acc.m_handle, "IMG_header_base");
                base.startAnimation("fade_in", false);
                base.setDisp(true);
            }
            unsigned int count = acc.countChild("TXT_header_title@%02d", 1);
            mm::mtl::FixStr<32> name;
            for (unsigned int i = 0; i < count; i++) {
                name.format("TXT_header_title@%02d", i + 1);
                acc.setDispChild(i + 1 == m_owner->m_title, name.m_str);
            }
            acc.setDispChild(false, "LAY_header_item");
            acc.setDispChild(false, "LAY_header_input");
            m_shown = 1;
        }
        break;
    case 0x22:
        if (m_shown == 1) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_out_r";
            param.m_startFlags = 10;
            param.m_eventId = 2;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, "LAY_header_body");
            {
                ui::UIObjectAcc base(acc.m_handle, "IMG_header_base");
                base.startAnimation("fade_out", false);
            }
            m_shown = 0;
        }
        break;
    case 0x103: {
        ui::UIObjectAcc text(acc.m_handle, "TXT_header_item");
        ui::UIStr str;
        m_owner->m_msgList->getMsg(-1, str, false);
        text.setText(str);
        acc.setDispChild(true, "LAY_header_item");
        acc.setDispChild(false, "LAY_header_input");
        unsigned int count = acc.countChild("TXT_header_input@%02d", 1);
        mm::mtl::FixStr<32> name;
        for (unsigned int i = 0; i < count; i++) {
            name.format("TXT_header_input@%02d", i + 1);
            acc.setDispChild(i + 1 == m_owner->m_title, name.m_str);
        }
        break;
    }
    case 0x104:
        acc.setDispChild(false, "LAY_header_item");
        acc.setDispChild(false, "LAY_header_input");
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjEvTheater::fn_7100404720(unsigned int index) {
    ui::UIObjectAcc acc(m_capHandle);
    if (acc.m_object != nullptr) {
        unsigned char* messages = GfDataBdat::getFP(0x136);
        ui::UIStr text(messages, static_cast<unsigned short>(
                                     Bdat::getVal(m_capBdat, "cap_id", s_capRows[index])));
        acc.setText(text);
    }
}

void GfMenuObjEvTheater::TUnk_B62178::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        GfMenuObject::disableInput(acc.m_handle);
        break;
    case 0x21:
        acc.setDisp(true);
        GfMenuObject::enableInput(acc.m_handle);
        GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        GfMenuObjUtil::setCommonFadeIn(acc.m_handle, 0, 0);
        break;
    case 0x22:
        acc.setDisp(false);
        GfMenuObject::disableInput(acc.m_handle);
        GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 0, 0);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjEvTheater::fn_71004051EC() {
    ui::UIObjectAcc image(m_handle, "IMG_preview");
    m_previewTime += GfMenuManager::getUpdateDT();
    if (m_previewTime < 5.0f && image.isStreaming()) {
        return false;
    }
    ui::UIObjectAcc preview(m_handle, "LAY_preview");
    GfMenuObjUtil::setCommonFadeIn(preview.m_handle, 1, 0);
    m_previewTime = 0.0f;
    return true;
}

bool GfMenuObjEvTheater::fn_7100405294() {
    ui::UIObjectAcc acc(m_handle, "LAY_preview");
    ui::EventData event;
    event.m_type = 0x105;
    GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    return true;
}

}  // namespace gf
