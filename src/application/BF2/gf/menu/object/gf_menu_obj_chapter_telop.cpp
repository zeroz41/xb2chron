#include "classes/ui/UIObjectAcc.h"
#include "classes/gf/GfMenuObjChapterTelop.h"
#include "classes/gf/GfMenuObjChapterTelop/ListListener.h"
#include "ui/EventData.h"
#include "gf/GfMenuSequence.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuObjChapterTelop.h"
#include "classes/gf/GfMenuObjChapterTelop/ListListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObject.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UITagParser.h"
#include "fw/LangUtil.h"
#include "layer/LayerAccFontObj.h"
#include "mm/Rect.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"
#include "ui/UIUtil.h"

namespace gf {

GfMenuObjChapterTelop::GfMenuObjChapterTelop(unsigned int handle) : GfMenuObject(handle), m_seq(this) {}

GfMenuObjChapterTelop::~GfMenuObjChapterTelop() {}

void GfMenuObjChapterTelop::initialize() {
    ui::UIObjectAcc acc(m_handle);
    ui::UIObjectAcc main(acc.m_handle, "LAY_main");
    if (main.m_object != nullptr) {
#line 92
        ListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListListener(this);
        // the original stores the count after the listener's own fields, not with its base
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(main.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuObject::attachExternalCall(0x44, main.m_handle);
        GfMenuObject::hookAnimationEvent(main.m_handle, main.searchChild("IMG_begin_track"), 0);
        GfMenuObject::hookAnimationEvent(main.m_handle, main.searchChild("IMG_begin_title"), 0);
        GfMenuObject::hookAnimationEvent(main.m_handle, main.searchChild("IMG_end_telop"), 0);
    }
    GfMenuObject::initialize();
}

void GfMenuObjChapterTelop::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjChapterTelop::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjChapterTelop::ListListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_chapter = 0;
        m_phase = 0;
        break;
    case 2:
        GfMenuObject::termCallContext(handle);
        acc.setTerm();
        break;
    case 3:
        if (m_phase == 0) {
            acc.setDisp(false);
            GfMenuObject::termCallContext(handle);
        }
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 0x21: {
        int chapter = event.m_param0;
        int type = event.m_param1;
        acc.setDisp(true);
        m_chapter = chapter;
        ui::UIObjectAcc(acc.m_handle, "LAY_begin_telop").setDisp(type == 0);
        ui::UIObjectAcc(acc.m_handle, "LAY_end_telop").setDisp(type == 1);
        ui::UIObjectAcc(acc.m_handle, "LAY_avan_title").setDisp(type == 2);
        if (type == 0) {
            ui::UIObjectAcc(acc.m_handle, "IMG_begin_track").setImageIndex(event.m_param0);
            ui::UIObjectAcc(acc.m_handle, "IMG_begin_title").setImageIndex(event.m_param0);
            m_owner->m_seq.addJob(&GfMenuObjChapterTelop::seqWaitStreamBegin);
            m_phase = 0;
        } else if (type == 1) {
            unsigned char* bdat = GfDataBdat::getFP(0x152);
            if (bdat == nullptr) {
                return;
            }
            bool vertical;
            {
                ui::UIObjectAcc index(acc.m_handle, "TXT_end_index");
                if (index.m_object == nullptr) {
                    return;
                }
                unsigned short id = (unsigned short)(unsigned long)Bdat::getVal(bdat, "index", chapter);
                if (id == 0) {
                    return;
                }
                ui::UIStr str(GfDataBdat::getFP(0x123), id);
                vertical = ui::UITagParser::get()->parseTag(str.c_str(), "ML:Vertical");
                if (vertical) {
                    layer::LayerAccFontObj font(ui::UIUtil::getObject(index.m_handle)->m_layer);
                    font.setDispSetting(layer::LayerFontSetting(2));
                }
                if (fw::LangUtil::getLangType() != 0 && fw::LangUtil::getLangType() != 6 &&
                    fw::LangUtil::getLangType() != 11 && fw::LangUtil::getLangType() != 7) {
                    index.setTextAlignH(1);
                }
                index.setSlopeRot(-12.0f);
                index.setText(str);
            }
            {
                ui::UIObjectAcc title(acc.m_handle, "TXT_end_title");
                if (title.m_object == nullptr) {
                    return;
                }
                unsigned short id = (unsigned short)(unsigned long)Bdat::getVal(bdat, "title", chapter);
                if (id == 0) {
                    return;
                }
                if (vertical) {
                    layer::LayerAccFontObj font(ui::UIUtil::getObject(title.m_handle)->m_layer);
                    font.setDispSetting(layer::LayerFontSetting(2));
                }
                title.setSlopeRot(-12.0f);
                title.setText(ui::UIStr(GfDataBdat::getFP(0x123), id));
            }
            if (fw::LangUtil::getLangType() == 0 || fw::LangUtil::getLangType() == 6 ||
                fw::LangUtil::getLangType() == 11 || fw::LangUtil::getLangType() == 7) {
                ui::UIObjectAcc index(acc.m_handle, "TXT_end_index");
                if (index.m_object == nullptr) {
                    return;
                }
                ui::UIObjectAcc title(acc.m_handle, "TXT_end_title");
                if (title.m_object == nullptr) {
                    return;
                }
                GfMenuObjUtil::setDockPos(title.m_handle, index.m_handle, 4, true);
                GfMenuObjUtil::addPos(title.m_handle, 0, 16);
                mm::Rect<short> indexRect;
                mm::Rect<short> titleRect;
                index.getRect(indexRect, 2);
                title.getRect(titleRect, 2);
                // centres the two texts' height (and the 16 between them) on 360
                short y = -indexRect.y - (indexRect.h + titleRect.h + 16) / 2 + 360;
                GfMenuObjUtil::addPos(index.m_handle, 0, y);
                GfMenuObjUtil::addPos(title.m_handle, 0, y);
            }
            m_owner->m_seq.clear();
            m_owner->m_seq.addWait(225);
            m_owner->m_seq.addJob(&GfMenuObjChapterTelop::seqOutChapterEnd);
        } else if (type == 2) {
            unsigned char* bdat = GfDataBdat::getFP(0x152);
            if (bdat == nullptr) {
                return;
            }
            ui::UIObjectAcc index(acc.m_handle, "TXT_avan_title_index");
            if (index.m_object != nullptr) {
                ui::UIObjectAcc name(acc.m_handle, "TXT_avan_title_name");
                if (name.m_object != nullptr) {
                    if (chapter == 10) {
                        chapter = 11;
                    }
                    unsigned short id = (unsigned short)(unsigned long)Bdat::getVal(bdat, "index", chapter);
                    if (id != 0) {
                        {
                            ui::UIStr str(GfDataBdat::getFP(0x123), id);
                            index.setSlopeRot(-12.0f);
                            index.setText(str);
                        }
                        id = (unsigned short)(unsigned long)Bdat::getVal(bdat, "title", chapter);
                        if (id != 0) {
                            name.setText(ui::UIStr(GfDataBdat::getFP(0x123), id));
                            name.setSlopeRot(-12.0f);
                            GfMenuObjUtil::setDockPos(name.m_handle, index.m_handle, 2, true);
                            GfMenuObjUtil::addPos(name.m_handle, 32, 0);
                        }
                    }
                }
            }
        }
        break;
    }
    case 0xC:
        switch (m_phase) {
        case 0:
            acc.setDisp(false);
            GfMenuObject::termCallContext(handle);
            break;
        case 1: {
            ui::UIObjectAcc telop(acc.m_handle, "IMG_end_telop");
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 2;
            param.m_time = 1.0f;
            param.m_startFlags = 10;
            int ctrl = GfMenuObjUtil::startCtrl(telop.m_handle, param, nullptr);
            GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
            m_phase = 0;
            break;
        }
        }
        break;
    case 0x22:
        if (event.m_param0Short == 0) {
            acc.setDisp(false);
        } else {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 2;
            param.m_time = event.m_param0Short * (1.0f / 30.0f);
            param.m_startFlags = 10;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        }
        GfMenuObject::termCallContext(handle);
        break;
    }
}

bool GfMenuObjChapterTelop::seqWaitStreamBegin() {
    ui::UIObjectAcc track(m_handle, "IMG_begin_track");
    ui::UIObjectAcc title(m_handle, "IMG_begin_title");
    if (track.isStreamImage() && track.isStreaming()) {
        return false;
    }
    if (title.isStreamImage() && title.isStreaming()) {
        return false;
    }
    track.setDisp(true);
    track.startAnimation("start", false);
    title.setDisp(true);
    title.startAnimation("start", false);
    return true;
}

bool GfMenuObjChapterTelop::seqOutChapterEnd() {
    ui::UIObjectAcc telop(m_handle, "LAY_end_telop");
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 2;
    param.m_time = 1.0f;
    param.m_startFlags = 10;
    GfMenuObjUtil::startCtrl(m_handle, param, "LAY_end_telop");
    m_seq.addJob(&GfMenuObjChapterTelop::seqWaitChapterEnd);
    return true;
}

void GfMenuObjChapterTelop::openBeginTelop(GfMenuCallContext* context, int chapter) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x44);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            GfMenuObject::startCallContext(context, 0x44, handle);
            ui::EventData event;
            event.m_type = 0x21;
            event.m_param0 = chapter - 1U < 10 ? chapter : 1;
            event.m_param1 = 0;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjChapterTelop::openEndTelop(GfMenuCallContext* context, int chapter) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x44);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            GfMenuObject::startCallContext(context, 0x44, handle);
            if (GfMenuObjUtil::fn_710048FD30(3)) {
                int index = chapter > 10 ? 12 : chapter;
                ui::EventData event;
                event.m_type = 0x21;
                event.m_param0 = index;
                event.m_param1 = 1;
                GfMenuObject::sendEvent(handle, event, 0.0f);
            } else {
                ui::EventData event;
                event.m_type = 0x21;
                event.m_param0 = chapter - 1U < 10 ? chapter : 1;
                event.m_param1 = 1;
                GfMenuObject::sendEvent(handle, event, 0.0f);
            }
        }
    }
}

void GfMenuObjChapterTelop::openAvanTitle(GfMenuCallContext* context, int chapter) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x44);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            GfMenuObject::startCallContext(context, 0x44, handle);
            ui::EventData event;
            event.m_type = 0x21;
            event.m_param0 = chapter - 1U < 10 ? chapter : 1;
            event.m_param1 = 2;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjChapterTelop::close(unsigned short frames) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x44);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x22;
            event.m_param0Short = frames;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

bool GfMenuObjChapterTelop::seqWaitChapterEnd() {
    ui::UIObjectAcc telop(m_handle, "LAY_end_telop");
    if (GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(telop.m_handle))) {
        return false;
    }
    GfMenuObject::termCallContext(ui::UIObjectAcc(m_handle, "LAY_main").m_handle);
    return true;
}

}  // namespace gf
