#include "classes/gf/GfMenuObjAnnounce.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfMenuTypes.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"
#include "classes/ui/UIObjectAcc.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"

namespace gf {

namespace {
// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009BD50C). The alpha each of the five
// LAY_schedule@%02d rows fades to.
const float s_scheduleAlpha[5] = {0.125f, 0.25f, 1.0f, 0.25f, 0.125f};
}  // namespace

GfMenuObjAnnounce::GfMenuObjAnnounce(unsigned int handle)
    : GfMenuObject(handle), pad_24(0), pad_28(0), m_imageIndex(0), m_seq(this), m_mainSeq(this), m_selectList(nullptr),
      m_cursor(nullptr), m_idList(nullptr), pad_308(0), pad_30C(false), pad_310(0) {
    m_idList = GfMenuIDList::create();
}

GfMenuObjAnnounce::~GfMenuObjAnnounce() {
    if (m_idList != nullptr) {
        m_idList->release();
        m_idList = nullptr;
    }
    if (m_cursor != nullptr) {
        m_cursor->release();
        m_cursor = nullptr;
    }
    if (m_selectList != nullptr) {
        m_selectList->release();
        m_selectList = nullptr;
    }
}

void GfMenuObjAnnounce::setCloseToDlcGift() {
    GfMenuTypes::Param param;
    param.m_menuId = 1;
    GfMenuFullScreen::registLayerParam(0x47, param);
}

void GfMenuObjAnnounce::finalize() {
    GfMenuObjOperationInfo::setDisp(true);
    GfMenuObject::finalize();
}

void GfMenuObjAnnounce::update() {
    m_seq.update();
    m_mainSeq.update();
    GfMenuObject::update();
}

bool GfMenuObjAnnounce::seqCloseImage2() {
    ui::UIObjectAcc img(m_handle, "LAY_contents_img");
    float alpha;
    img.getAlpha(alpha);
    if (alpha > 0.0f) {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_time = 0.25f;
        GfMenuObjUtil::startCtrl(img.m_handle, param, nullptr);
    }
    return true;
}

bool GfMenuObjAnnounce::seqCloseImage() {
    ui::UIObjectAcc img(m_handle, "LAY_contents_img");
    float alpha;
    img.getAlpha(alpha);
    if (alpha > 0.0f) {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_time = 0.25f;
        GfMenuObjUtil::startCtrl(img.m_handle, param, nullptr);
        m_seq.addJob(&GfMenuObjAnnounce::seqWaitImage);
    } else {
        ui::UIObjectAcc image(img.m_handle, "IMG_contents_img");
        image.setImageIndex(m_imageIndex);
        m_seq.addJob(&GfMenuObjAnnounce::seqOpenImage);
    }
    return true;
}

void GfMenuObjAnnounce::PageListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        GfMenuObject::disableInput(1);
        break;
    case 3:
        if (event.m_param0 == 1 && !m_owner->pad_30C) {
            if (GfMenuObjUtil::isValidExpansion(3)) {
                GfMenuObjMainMenu2::setSystemKeyEnable(true);
            } else {
                GfMenuObject::enableInput(acc.m_handle);
            }
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        }
        break;
    case 0x102:
        if (GfMenuObjUtil::isValidExpansion(3)) {
            GfMenuObjMainMenu2::setSystemKeyEnable(true);
        } else {
            GfMenuObject::enableInput(acc.m_handle);
        }
        GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        break;
    case 8:
        if (event.m_param1 == 2) {
            GfMenuObject::disableInput(acc.m_handle);
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
            GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_top"), 0, 0.0f);
            GfMenuObjUtil::playSECommonCancel();
        }
        break;
    case 0x21: {
        unsigned int page = m_owner->pad_24;
        unsigned char* fp = GfDataBdat::getFP(0x10B);
        if (GfMenuObjUtil::isValidExpansion(3)) {
            fp = GfDataBdat::getFP(0x10C);
            m_owner->m_imageIndex = 1;
            m_owner->m_seq.clear();
            m_owner->m_seq.addJob(&GfMenuObjAnnounce::seqCloseImage);
        }
        unsigned char* text = GfDataBdat::getFP(0x13B);
        unsigned short title = Bdat::getVal(fp, "title", page + 1);
        unsigned short summary = Bdat::getVal(fp, "summary", page + 1);
        ui::UIObjectAcc(acc.m_handle, "TXT_page_index").setText(ui::UIStr(text, title));
        ui::UIObjectAcc(acc.m_handle, "TXT_page_summary").setText(ui::UIStr(text, summary));
        GfMenuObjUtil::setCommonFadeIn(acc.m_handle, 1, 1);
        ui::UIObjectAcc(acc.m_handle, "IMG_page_base").startAnimationFromIndex(page + 1, false);
        m_owner->pad_310 = acc.m_handle;
        break;
    }
    case 0x22:
        GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 2, 1);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjAnnounce::ScheduleListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        GfMenuObject::disableInput(1);
        break;
    case 3: {
        int type = event.m_param0;
        if (type == 1) {
            if (!m_owner->pad_30C) {
                GfMenuObject::enableInput(acc.m_handle);
                GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
            }
            m_owner->refreshSchedule(false);
            GfMenuObject::resetInputSelection(acc.m_handle);
            GfMenuObject::setupInputSelection(acc.m_handle, 0, m_owner->m_idList->getSize());
        } else if (type == 2) {
            acc.setDisp(false);
        } else if (type == 3) {
            m_owner->pad_308 = 0;
            m_owner->refreshSchedule(false);
        }
        break;
    }
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        if (index != -1) {
            if (prev == -1) {
                m_owner->m_idList->setIndex(index);
            } else if (m_owner->pad_308 == 0) {
                int ctrl;
                if (index > prev) {
                    ctrl = m_owner->ctrlScheduleUp();
                } else {
                    ctrl = m_owner->ctrlScheduleDown();
                }
                if (ctrl != -1) {
                    m_owner->closeScheduleBody();
                    GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
                }
                m_owner->m_idList->setIndex(index);
            } else {
                m_owner->pad_308 = 0;
                m_owner->stopScheduleMove();
                m_owner->m_idList->setIndex(index);
                m_owner->refreshSchedule(false);
            }
        }
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSECommonCursor();
        }
        break;
    }
    case 8:
        if (event.m_param1 == 2) {
            GfMenuObject::disableInput(acc.m_handle);
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
            GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_top"), 1, 0.0f);
            GfMenuObjUtil::playSECommonCancel();
        }
        break;
    case 0x21:
        m_owner->m_idList->setIndex(0);
        m_owner->refreshSchedule(true);
        acc.setDisp(true);
        GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_schedule_base"), 1, 0);
        GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_schedule_arrow"), 1, 0);
        {
            int ctrl = GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_schedule_contents"), 1, 1);
            GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        }
        m_owner->pad_310 = acc.m_handle;
        break;
    case 0x22:
        GfMenuObjUtil::setCommonFadeOut(acc.searchChild("LAY_schedule_base"), 2, 0);
        GfMenuObjUtil::setCommonFadeOut(acc.searchChild("LAY_schedule_arrow"), 2, 0);
        {
            int ctrl = GfMenuObjUtil::setCommonFadeOut(acc.searchChild("LAY_schedule_contents"), 2, 1);
            GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        }
        break;
    case 0x102:
        GfMenuObject::enableInput(acc.m_handle);
        GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjAnnounce::closeScheduleBody() {
    ui::UIObjectAcc schedule(m_handle, "LAY_schedule");
    unsigned char* fp = GfDataBdat::getFP(0x10D);
    unsigned int index = m_idList->getIndex(false);
    unsigned int rows = m_idList->getPageRowSize();
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < m_idList->getPageRowSize(); i++) {
        unsigned int id = i + (index - rows / 2);
        if (id < static_cast<unsigned int>(m_idList->getSize())) {
            bool available = static_cast<unsigned char>(Bdat::getVal(fp, "available", m_idList->getContents(id).m_id)) == 1;
            name.format("TXT_schedule_summary@%02d", i + 1);
            ui::UIObjectAcc summary(schedule.m_handle, name.m_str);
            name.format("IMG_schedule_base@%02d", i + 1);
            ui::UIObjectAcc base(schedule.m_handle, name.m_str);
            int ctrl = GfMenuObjUtil::getCtrlID(summary.m_handle);
            if (ctrl != -1) {
                GfMenuObjUtil::stopCtrl(ctrl);
            }
            summary.setDisp(false);
            base.startAnimation(available ? "index_green" : "index_orange", false);
        }
    }
}

void GfMenuObjAnnounce::stopScheduleMove() {
    ui::UIObjectAcc schedule(m_handle, "LAY_schedule");
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < m_idList->getPageRowSize(); i++) {
        name.format("LAY_schedule@%02d", i + 1);
        ui::UIObjectAcc row(schedule.m_handle, name.m_str);
        int ctrl = GfMenuObjUtil::getCtrlID(row.m_handle);
        if (ctrl != -1) {
            GfMenuObjUtil::stopCtrl(ctrl);
        }
    }
}

void GfMenuObjAnnounce::AlertListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        GfMenuObject::disableInput(1);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableInput(acc.m_handle);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        }
        break;
    case 8:
        if (event.m_param1 == 1) {
            GfMenuObject::disableInput(acc.m_handle);
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            GfMenuObject::sendCloseEvent(acc.m_handle, 0, 0.0f);
            m_owner->pad_30C = false;
            m_owner->pad_24 = 0;
            ui::EventData ev;
            ev.m_type = 0x102;
            GfMenuObject::sendEvent(acc.getParentHandle(), ev, 0.0f);
            GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_top"), 0, 0.0f);
            GfMenuObjUtil::playSECommonDecide();
        }
        break;
    case 0x21:
        m_owner->pad_30C = true;
        GfMenuObjUtil::setCommonFadeIn(acc.m_handle, 1, 0);
        break;
    case 0x22:
        GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 2, 0);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjAnnounce::seqOpenImage() {
    ui::UIObjectAcc img(m_handle, "LAY_contents_img");
    bool ready;
    if (img.isStreaming()) {
        img.setAlpha(0.0f);
        ready = false;
    } else {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 1;
        param.m_time = 0.25f;
        GfMenuObjUtil::startCtrl(img.m_handle, param, nullptr);
        ready = true;
    }
    return ready;
}

bool GfMenuObjAnnounce::seqWaitImage() {
    ui::UIObjectAcc img(m_handle, "LAY_contents_img");
    int ctrl = GfMenuObjUtil::getCtrlID(img.m_handle);
    if (ctrl != -1 && GfMenuObjUtil::isBusyCtrl(ctrl)) {
        return false;
    }
    {
        ui::UIObjectAcc image(img.m_handle, "IMG_contents_img");
        image.setImageIndex(m_imageIndex);
    }
    m_seq.addJob(&GfMenuObjAnnounce::seqOpenImage);
    return true;
}

}  // namespace gf
