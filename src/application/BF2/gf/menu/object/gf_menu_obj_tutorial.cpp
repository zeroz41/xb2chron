#include "classes/gf/GfMenuObjTutorial.h"
#include "classes/gf/GfMenuObjTutorial/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"
#include "mm/mtl/Delegate.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixStr.h"
#include "mm/Pnt.h"

namespace gf {

// the tutorial's call context: the constructor creates it, the destructor releases it (the name is not the
// original's; the symbol is unnamed)
static GfMenuCallContext* s_context;

GfMenuObjTutorial::GfMenuObjTutorial(unsigned int handle) : GfMenuObject(handle), m_seq(this), m_termWait(0) {
    s_context = GfMenuCallContext::create();
    s_context->reset();
}

GfMenuObjTutorial::~GfMenuObjTutorial() {
    if (s_context != nullptr) {
        s_context->release();
        s_context = nullptr;
    }
}

void GfMenuObjTutorial::openText(unsigned int index, const TextParam& param) {
    if (GfMenuObjUtil::checkCCStart(s_context)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x7A));
        if (acc.m_object != nullptr) {
            unsigned short text = GfMenuObject::registString(ui::UIStr(GfDataBdat::getFP(0x12A), param.m_text));
            ui::EventData event;
            event.m_type = 0x101;
            event.m_paramShort[0] = index;
            event.m_paramShort[1] = 1;
            event.m_paramShort[2] = text;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
            GfMenuObject::startCallContext(s_context, 0x7A, acc.m_handle);
        }
    }
}

void GfMenuObjTutorial::closeText(unsigned int index) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x7A));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x101;
        event.m_paramShort[0] = index;
        event.m_paramShort[1] = 0;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

bool GfMenuObjTutorial::isWaiting() {
    return s_context != nullptr && s_context->isActive();
}

void GfMenuObjTutorial::openFocus(unsigned int index, const FocusParam& param) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x7A));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x102;
        event.m_paramShort[0] = index;
        event.m_paramShort[1] = 1;
        event.m_paramShort[2] = param.m_value[2];
        event.m_paramShort[3] = param.m_value[0];
        event.m_paramShort[4] = param.m_value[1];
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjTutorial::closeFocus(unsigned int index) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x7A));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x102;
        event.m_paramShort[0] = index;
        event.m_paramShort[1] = 0;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjTutorial::openIcon(unsigned int index, const IconParam& param) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x7A));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x103;
        event.m_paramShort[0] = index;
        event.m_paramShort[1] = 1;
        event.m_paramShort[3] = param.m_value[0];
        event.m_paramShort[4] = param.m_value[1];
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjTutorial::closeIcon(unsigned int index) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x7A));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x103;
        event.m_paramShort[0] = index;
        event.m_paramShort[1] = 0;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjTutorial::start() {
    if (GfMenuObjUtil::checkCCStart(s_context)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x7A));
        if (acc.m_object != nullptr) {
            ui::EventData event;
            event.m_type = 0x104;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
            GfMenuObject::startCallContext(s_context, 0x7A, acc.m_handle);
        }
    }
}

void GfMenuObjTutorial::closeAll() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x7A));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x22;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjTutorial::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    if (acc.m_object != nullptr) {
        GfMenuObject::attachExternalCall(0x7A, acc.m_handle);
#line 239
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        // the original stores the count after the listener's own fields, not with its base
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuObject::initialize();
    }
}

void GfMenuObjTutorial::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjTutorial::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjTutorial::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 0x101: {
        // a text: its index, whether it opens, the string
        unsigned short index = event.m_paramShort[0];
        unsigned short open = event.m_paramShort[1];
        mm::mtl::FixStr<32> name;
        name.format("LAY_info@%02d", index + 1);
        ui::UIObjectAcc lay(acc.m_handle, name.m_str);
        if (lay.m_object != nullptr) {
            if (open == 1) {
                lay.setDisp(true);
                name.format("TXT_info@%02d", index + 1);
                {
                    unsigned int parent = lay.m_handle;
                    unsigned short text = event.m_paramShort[2];
                    ui::UIObjectAcc txt(parent, name.m_str);
                    if (txt.m_object != nullptr) {
                        GfMenuObject::setText(txt.m_handle, text);
                    }
                }
                GfMenuObject::enableInput(acc.m_handle);
                GfMenuObject::registTimer(acc.m_handle, 0, 0.5f, true);
                acc.setDispChild(true, "IMG_info_arrow@01");
                acc.setDispChild(true, "IMG_info_arrow@02");
            } else {
                lay.setDisp(false);
                GfMenuObject::disableInput(acc.m_handle);
                GfMenuObject::releaseTimer(acc.m_handle);
                acc.setDispChild(false, "IMG_info_arrow@01");
                acc.setDispChild(false, "IMG_info_arrow@02");
            }
        }
        break;
    }
    case 0x102: {
        // a focus: its index, whether it opens, the side it points from, the point
        unsigned short index = event.m_paramShort[0];
        unsigned short open = event.m_paramShort[1];
        mm::mtl::FixStr<32> name;
        name.format("LAY_focus@%02d", index + 1);
        ui::UIObjectAcc lay(acc.m_handle, name.m_str);
        if (lay.m_object != nullptr) {
            if (open == 1) {
                unsigned short side = event.m_paramShort[2];
                lay.setDisp(true);
                short width;
                short height;
                lay.getSize(true, width, height);
                mm::Pnt<short> pos;
                pos.x = event.m_paramShort[3];
                pos.y = event.m_paramShort[4];
                float rot = 0.0f;
                switch (side) {
                case 0:
                    pos.y += height / 2;
                    break;
                case 1:
                    pos.y -= height / 2;
                    rot = 3.14159274f;
                    break;
                case 2:
                    pos.x += width / 2;
                    rot = 1.57079637f;
                    break;
                case 3:
                    pos.x -= width / 2;
                    rot = 4.71238899f;
                    break;
                }
                lay.setRot(rot);
                lay.setPosCenter(pos);
                name.format("IMG_focus_icon@%02d", index + 1);
                ui::UIObjectAcc(acc.m_handle, name.m_str).startAnimation("loop", false);
            } else {
                lay.setDisp(false);
                name.format("IMG_focus_icon@%02d", index + 1);
                ui::UIObjectAcc(acc.m_handle, name.m_str).stopAnimation();
            }
        }
        break;
    }
    case 0x103: {
        // an icon: its index, whether it opens, the point
        unsigned short index = event.m_paramShort[0];
        unsigned short open = event.m_paramShort[1];
        mm::mtl::FixStr<32> name;
        name.format("LAY_icon@%02d", index + 1);
        ui::UIObjectAcc lay(acc.m_handle, name.m_str);
        if (lay.m_object != nullptr) {
            if (open == 1) {
                lay.setDisp(true);
                mm::Pnt<short> pos;
                pos.x = event.m_paramShort[3];
                pos.y = event.m_paramShort[4];
                lay.setPosCenter(pos);
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x80000;
                param.m_curve = 1;
                param.m_scale = 1.2f;
                param.m_reserve = true;
                param.m_setDefault = true;
                param.m_time = 0.5f;
                GfMenuObjUtil::startCtrl(lay.m_handle, param, nullptr);
            } else {
                int slot = GfMenuObjUtil::getCtrlID(lay.m_handle);
                if (slot != -1) {
                    GfMenuObjUtil::stopCtrl(slot);
                }
                lay.setDisp(false);
            }
        }
        break;
    }
    case 0x104:
        m_owner->m_telopStarted = false;
        m_owner->m_seq.clear();
        m_owner->m_seq.addJob(&GfMenuObjTutorial::seqTelopStart);
        m_owner->m_seq.addWait(30);
        m_owner->m_seq.addJob(&GfMenuObjTutorial::seqTelopEnd);
        m_owner->m_seq.addJob(&GfMenuObjTutorial::seqEnd);
        break;
    case 0x105:
        break;
    case 1:
        GfMenuObject::disableInput(acc.m_handle);
        acc.setDisp(true);
        break;
    case 8:
        if (event.m_param1 == 1) {
            GfMenuObject::termCallContext(acc.m_handle);
            GfMenuObject::disableInput(acc.m_handle);
            GfMenuObject::releaseTimer(acc.m_handle);
            acc.setDispChild(false, "IMG_info_arrow@01");
            acc.setDispChild(false, "IMG_info_arrow@02");
        }
        break;
    case 0xB: {
        bool disp = (event.m_param1 & 1) == 0;
        acc.setDispChild(disp, "IMG_info_arrow@01");
        acc.setDispChild(disp, "IMG_info_arrow@02");
        break;
    }
    case 0x22:
        closeText(0);
        closeText(1);
        closeFocus(0);
        closeFocus(1);
        closeFocus(2);
        closeFocus(3);
        closeIcon(0);
        closeIcon(1);
        closeIcon(2);
        closeIcon(3);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjTutorial::seqTelopStart() {
    ui::UIObjectAcc img(m_handle, "IMG_start");
    if (!m_telopStarted) {
        ui::UIObjectAcc lay(m_handle, "LAY_start");
        lay.setDisp(true);
        img.startAnimation("start", false);
        {
            ui::UIObjectAcc text(m_handle, "TXT_start");
            text.setDisp(true);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_l";
            param.m_setDefault = true;
            param.m_startFlags = 8;
            GfMenuObjUtil::startCtrl(text.m_handle, param, nullptr);
        }
        m_telopStarted = true;
        m_termWait = 5;
        GfMenuObjUtil::playJingle(0xB);
        return false;
    }
    if (m_termWait != 0 && --m_termWait == 0) {
        ui::UIObjectAcc main(m_handle, "LAY_main");
        GfMenuObject::termCallContext(main.m_handle);
    }
    if (img.isPlayingAnimation()) {
        return false;
    }
    m_telopStarted = false;
    return true;
}

bool GfMenuObjTutorial::seqTelopEnd() {
    ui::UIObjectAcc img(m_handle, "IMG_start");
    if (!m_telopStarted) {
        img.startAnimation("end", false);
        {
            ui::UIObjectAcc text(m_handle, "TXT_start");
            text.setDisp(true);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_out_l";
            param.m_setDefault = true;
            param.m_startFlags = 10;
            GfMenuObjUtil::startCtrl(text.m_handle, param, nullptr);
        }
        m_telopStarted = true;
        return false;
    }
    if (img.isPlayingAnimation()) {
        return false;
    }
    ui::UIObjectAcc lay(m_handle, "LAY_start");
    lay.setDisp(false);
    m_telopStarted = false;
    return true;
}

bool GfMenuObjTutorial::seqEnd() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    ui::EventData event;
    event.m_type = 0x105;
    GfMenuObject::sendEvent(main.m_handle, event, 0.0f);
    return true;
}
}  // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjTutorial>(const mm::mtl::Delegate<bool()>*);

template bool gf::GfMenuSequence<gf::GfMenuObjTutorial, 8>::wait();

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjTutorial, 8>>(const mm::mtl::Delegate<bool()>*);

namespace gf {

}  // namespace gf
