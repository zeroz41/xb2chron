#include "classes/gf/GfMenuObjEventSubtitle.h"
#include "classes/gf/GfMenuObjEventSubtitle/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataManager.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObject.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UITagParser.h"
#include "fw/LangUtil.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/SDataOption.h"
#include "layer/LayerAccFontObj.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"
#include "ui/UIUtil.h"

namespace gf {

GfMenuObjEventSubtitle::GfMenuObjEventSubtitle(unsigned int handle) : GfMenuObject(handle) {}

GfMenuObjEventSubtitle::~GfMenuObjEventSubtitle() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjEventSubtitle::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
#line 71
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    // the original stores the count after the listener's own fields, not with its base
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObject::attachExternalCall(1, acc.m_handle);
    if (fw::LangUtil::getLangType() == 0 || fw::LangUtil::getLangType() == 7) {
        ui::UIObjectAcc text(acc.searchChild("TXT_str_v"));
        if (text.m_object != nullptr) {
            layer::LayerAccFontObj font(ui::UIUtil::getObject(text.m_handle)->m_layer);
            font.setDispSetting(layer::LayerFontSetting(2));
            GfMenuObjUtil::addPos(text.m_handle, 92, 0);
        }
    }
    ui::UIObjectAcc(m_handle).setTerm();
    GfMenuObject::initialize();
}

void GfMenuObjEventSubtitle::finalize() {
    GfMenuObject::detachExternalCall(1);
    GfMenuObject::finalize();
}

void GfMenuObjEventSubtitle::update() {
    GfMenuObject::update();
}

void GfMenuObjEventSubtitle::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        break;
    case 2:
        acc.setTerm();
        break;
    case 0x45: {
        ui::UIObjectAcc text(acc.m_handle, "TXT_str00");
        ui::UIObjectAcc vertical(acc.m_handle, "TXT_str_v");
        text.setDisp(false);
        text.setText(ui::UIStr(" ", false));
        vertical.setDisp(false);
        vertical.setText(ui::UIStr(" ", false));
        break;
    }
    case 0x100: {
        int line = event.m_param1;
        const ui::UIStr& str = GfMenuObject::getString(event.m_param0);
        if (ui::UITagParser::get()->parseTag(str.c_str(), "ML:undisp")) {
            GfMenuObject::releaseString(event.m_param0);
            ui::EventData hide;
            hide.m_type = 0x101;
            GfMenuObject::sendEvent(acc.m_handle, hide, 0.0f);
            break;
        }
        bool isVertical = ui::UITagParser::get()->parseTag(str.c_str(), "ML:Vertical");
        unsigned int child;
        if (line == 0) {
            if (isVertical) {
                child = acc.searchChild("TXT_str_v");
            } else {
                if (!GfDataManager::getDataOption()->m_soundUi.m_eventSubtitle) {
                    GfMenuObject::releaseString(event.m_param0);
                    break;
                }
                child = acc.searchChild("TXT_str00");
            }
        } else if (line == 1) {
            child = acc.searchChild("TXT_str01");
        } else if (line == 2) {
            child = acc.searchChild("TXT_str02");
        } else {
            child = 0;
        }
        ui::UIObjectAcc text(child);
        if (text.m_object != nullptr) {
            if (isVertical) {
                text.setSlopeRot(-12.0f);
            }
            text.setDisp(true);
            GfMenuObject::setText(text.m_handle, event.m_param0);
        }
        break;
    }
    case 0x101: {
        ui::UIObjectAcc text0(acc.m_handle, "TXT_str00");
        ui::UIObjectAcc vertical(acc.m_handle, "TXT_str_v");
        ui::UIObjectAcc text1(acc.m_handle, "TXT_str01");
        ui::UIObjectAcc text2(acc.m_handle, "TXT_str02");
        text0.setDisp(false);
        vertical.setDisp(false);
        text1.setDisp(false);
        text2.setDisp(false);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjEventSubtitle::dispText(unsigned char* bdat, unsigned int id, unsigned int line) {
    unsigned int handle = GfMenuObject::getAttachedObject(1);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            unsigned short str = GfMenuObject::registString(ui::UIStr(bdat, id));
            ui::EventData event;
            event.m_type = 0x100;
            event.m_param0 = str;
            event.m_param1 = line;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjEventSubtitle::hideText() {
    unsigned int handle = GfMenuObject::getAttachedObject(1);
    ui::EventData event;
    event.m_type = 0x101;
    ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
}

void GfMenuObjEventSubtitle::endText() {
    unsigned int handle = GfMenuObject::getAttachedObject(1);
    ui::EventData event;
    event.m_type = 0x45;
    ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
}

}  // namespace gf
