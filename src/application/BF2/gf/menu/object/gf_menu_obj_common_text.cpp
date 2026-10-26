#include "classes/ui/UIListInfo.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuObjCommonText/DialogListener.h"
#include "classes/gf/GfMenuObjCommonText/DrChangeListener.h"
#include "classes/gf/GfMenuObjCommonText/ErrorListener.h"
#include "classes/gf/GfMenuObjCommonText/GetItemListener.h"
#include "classes/gf/GfMenuObjCommonText/KizunaListener.h"
#include "classes/gf/GfMenuObjCommonText/MainListener.h"
#include "classes/gf/GfMenuObjCommonText/MerListener.h"
#include "classes/gf/GfMenuObjCommonText/NumSelectListener.h"
#include "classes/gf/GfMenuObjCommonText/OwnerChangeListener.h"
#include "classes/gf/GfMenuObjCommonText/SelectListener.h"
#include "classes/gf/MenuCommonWindowParam.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfDataItem.h"
#include "gf/GfMenuItemUtil.h"
#include "plugin/Bdat.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"

namespace gf {

void GfMenuObjCommonText::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjCommonText::update() {
    GfMenuObject::update();
}

void GfMenuObjCommonText::close() {
    unsigned int handle = GfMenuObject::getAttachedObject(100);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x22;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjCommonText::open(GfMenuCallContext* context, const MenuCommonWindowParam& param) {
    unsigned int handle = GfMenuObject::getAttachedObject(100);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            GfMenuObject::startCallContext(context, 100, handle);
            unsigned short title = param.m_titleBdat != nullptr ? GfMenuObject::registString(ui::UIStr(param.m_titleBdat, param.m_titleId)) : 0xFFFF;
            unsigned short text = param.m_bdat != nullptr ? GfMenuObject::registString(ui::UIStr(param.m_bdat, param.m_msgId)) : 0xFFFF;
            unsigned short ok = param.m_okBdat != nullptr ? GfMenuObject::registString(ui::UIStr(param.m_okBdat, param.m_okId)) : 0xFFFF;
            unsigned short cancel = param.m_cancelBdat != nullptr ? GfMenuObject::registString(ui::UIStr(param.m_cancelBdat, param.m_cancelId)) : 0xFFFF;
            ui::EventData event;
            event.m_type = 0x21;
            event.m_paramShort[0] = title;
            event.m_paramShort[1] = text;
            event.m_paramShort[2] = ok;
            event.m_paramShort[3] = cancel;
            event.m_paramShort[4] = param.m_type;
            event.m_paramShort[5] = param.m_type != 0 ? param.m_select : 1;
            event.m_paramShort[6] = param.pad_44;
            event.m_paramShort[7] = param.pad_48;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjCommonText::open(GfMenuCallContext* context, unsigned int text, unsigned int value) {
    unsigned char* fp = GfDataBdat::getFP(0xF6);
    if (fp == nullptr) {
        return;
    }
    unsigned char* msg = GfDataBdat::getFP(0x111);
    if (msg == nullptr) {
        return;
    }
    MenuCommonWindowParam param;
    unsigned int title = static_cast<unsigned short>(Bdat::getVal(fp, "title", text));
    if (title != 0) {
        param.m_titleBdat = msg;
        param.m_titleId = title;
    }
    unsigned int body = static_cast<unsigned short>(Bdat::getVal(fp, "text", text));
    if (body != 0) {
        param.m_bdat = msg;
        param.m_msgId = body;
    }
    unsigned int ok = static_cast<unsigned short>(Bdat::getVal(fp, "select_ok_txt", text));
    if (ok != 0) {
        param.m_okBdat = msg;
        param.m_okId = ok;
    }
    unsigned int cancel = static_cast<unsigned short>(Bdat::getVal(fp, "select_cancel_txt", text));
    if (cancel != 0) {
        param.m_cancelBdat = msg;
        param.m_cancelId = cancel;
    }
    param.m_type = static_cast<unsigned char>(Bdat::getVal(fp, "type", text));
    param.m_select = static_cast<unsigned char>(Bdat::getVal(fp, "select", text));
    param.pad_44 = value;
    param.pad_48 = 0;
    open(context, param);
}

void GfMenuObjCommonText::openItem(GfMenuCallContext* context, unsigned int kind, unsigned int item) {
    unsigned char* fp = GfDataBdat::getFP(0xF6);
    if (fp == nullptr) {
        return;
    }
    unsigned char* msg = GfDataBdat::getFP(0x111);
    if (msg == nullptr) {
        return;
    }
    MenuCommonWindowParam param;
    param.m_titleBdat = msg;
    param.m_titleId = static_cast<unsigned short>(Bdat::getVal(fp, "title", kind));
    {
        unsigned char type = GfDataItem::getItemType(item);
        ui::UIStr name;
        GfMenuItemUtil::getItemName(type, item, name);
        param.m_bdat = name.getMsgFP();
        param.m_msgId = name.getMsgID();
    }
    param.m_type = static_cast<unsigned char>(Bdat::getVal(fp, "type", kind));
    param.m_select = static_cast<unsigned char>(Bdat::getVal(fp, "select", kind));
    param.pad_48 = 0;
    open(context, param);
}

void GfMenuObjCommonText::openError(GfMenuCallContext* context, unsigned int error, unsigned int value) {
    unsigned char* fp = GfDataBdat::getFP(0x149);
    if (fp == nullptr) {
        return;
    }
    unsigned char* msg = GfDataBdat::getFP(0x11F);
    if (msg == nullptr) {
        return;
    }
    MenuCommonWindowParam param;
    unsigned int name = static_cast<unsigned short>(Bdat::getVal(fp, "name", error));
    if (name != 0) {
        param.m_bdat = msg;
        param.m_msgId = name;
    }
    param.pad_44 = value;
    param.pad_48 = 1;
    open(context, param);
}

void GfMenuObjCommonText::openMissionStop(GfMenuCallContext* context, unsigned int text, unsigned int value) {
    unsigned int handle = GfMenuObject::getAttachedObject(100);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        bool term = ui::UIObjectAcc(handle).isTerm();
        if (context != nullptr && !term) {
            unsigned char* fp = GfDataBdat::getFP(0xF6);
            if (fp == nullptr) {
                return;
            }
            unsigned int id = static_cast<unsigned short>(Bdat::getVal(fp, "text", text));
            if (id != 0) {
                unsigned short str = GfMenuObject::registString(ui::UIStr(GfDataBdat::getFP(0x111), id));
                ui::EventData event;
                event.m_type = 0x21;
                event.m_param0 = value;
                event.m_paramShort[2] = str;
                event.m_paramShort[3] = static_cast<unsigned char>(Bdat::getVal(fp, "type", text));
                event.m_paramShort[4] = static_cast<unsigned char>(Bdat::getVal(fp, "select", text));
                event.m_paramShort[7] = 2;
                GfMenuObject::sendEvent(handle, event, 0.0f);
                GfMenuObject::startCallContext(context, 100, handle);
            } else {
                context->abort();
            }
        }
    }
}

void GfMenuObjCommonText::openKizunaDialog(GfMenuCallContext* context, const OpenKizunaParam& param) {
    unsigned int handle = GfMenuObject::getAttachedObject(100);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        bool term = ui::UIObjectAcc(handle).isTerm();
        if (context != nullptr && !term) {
            if (GfDataBdat::getFP(0xF6) != nullptr) {
                unsigned short str = GfMenuObject::registString(ui::UIStr(param.m_bdat, param.m_id));
                ui::EventData event;
                event.m_type = 0x21;
                event.m_param0 = param.m_value;
                event.m_paramShort[2] = str;
                event.m_paramShort[7] = 3;
                GfMenuObject::sendEvent(handle, event, 0.0f);
                GfMenuObject::startCallContext(context, 100, handle);
            }
        }
    }
}

GfMenuItemList* GfMenuObjCommonText::s_pItemList;
GfMenuIDList* GfMenuObjCommonText::s_pSubMenuIDList;
GfMenuDriverList* GfMenuObjCommonText::s_pChangeDrList;

void GfMenuObjCommonText::openGetItem(GfMenuCallContext* context, const GfMenuItemList* items) {
    unsigned int handle = GfMenuObject::getAttachedObject(100);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        bool term = ui::UIObjectAcc(handle).isTerm();
        if (context != nullptr && !term) {
            s_pItemList->clear();
            for (unsigned int i = 0; i < items->getSize(); i++) {
                s_pItemList->addContents(items->getContents(i));
            }
            ui::EventData event;
            event.m_type = 0x21;
            event.m_paramShort[7] = 4;
            GfMenuObject::sendEvent(handle, event, 1.0f / 30.0f);
            GfMenuObject::startCallContext(context, 100, handle);
        }
    }
}

void GfMenuObjCommonText::openSelectItem(GfMenuCallContext* context, const GfMenuItemList* items, unsigned int value) {
    unsigned int handle = GfMenuObject::getAttachedObject(100);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        bool term = ui::UIObjectAcc(handle).isTerm();
        if (context != nullptr && !term) {
            s_pItemList->clear();
            for (unsigned int i = 0; i < items->getSize(); i++) {
                s_pItemList->addContents(items->getContents(i));
            }
            ui::EventData event;
            event.m_type = 0x21;
            event.m_param0 = value;
            event.m_paramShort[2] = 1;
            event.m_paramShort[3] = 1;
            event.m_paramShort[4] = 0;
            event.m_paramShort[7] = 5;
            GfMenuObject::sendEvent(handle, event, 0.0f);
            GfMenuObject::startCallContext(context, 100, handle);
        }
    }
}

void GfMenuObjCommonText::openDrChange(GfMenuCallContext* context, unsigned int driver, const GfMenuDriverList* drivers) {
    unsigned int handle = GfMenuObject::getAttachedObject(100);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        bool term = ui::UIObjectAcc(handle).isTerm();
        if (context != nullptr && !term) {
            s_pChangeDrList->clear();
            for (unsigned int i = 0; i < drivers->getSize(); i++) {
                s_pChangeDrList->addContents(drivers->getContents(i));
            }
            s_pChangeDrList->setIndex(0);
            GfMenuReference::setReferenceDriverID(4, driver);
            ui::EventData event;
            event.m_type = 0x21;
            event.m_paramShort[7] = 6;
            GfMenuObject::sendEvent(handle, event, 0.0f);
            GfMenuObject::startCallContext(context, 100, handle);
        }
    }
}

void GfMenuObjCommonText::openOwnerChange(GfMenuCallContext* context, unsigned int driver, unsigned int owner) {
    unsigned int handle = GfMenuObject::getAttachedObject(100);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        bool term = ui::UIObjectAcc(handle).isTerm();
        if (context != nullptr && !term) {
            GfMenuReference::setReferenceDriverID(4, driver);
            GfMenuReference::setReferenceDriverID(5, owner);
            ui::EventData event;
            event.m_type = 0x21;
            event.m_paramShort[0] = 0;
            event.m_paramShort[7] = 7;
            GfMenuObject::sendEvent(handle, event, 0.0f);
            GfMenuObject::startCallContext(context, 100, handle);
        }
    }
}

void GfMenuObjCommonText::openNumSelect(GfMenuCallContext* context, const OpenNumSelectParam& param) {
    unsigned int handle = GfMenuObject::getAttachedObject(100);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        bool term = ui::UIObjectAcc(handle).isTerm();
        if (context != nullptr && !term) {
            ui::EventData event;
            event.m_type = 0x21;
            event.m_paramShort[0] = param.pad_0;
            event.m_paramShort[1] = param.pad_4;
            event.m_paramShort[2] = param.pad_8;
            event.m_param2 = param.pad_C;
            event.m_paramShort[7] = 8;
            GfMenuObject::sendEvent(handle, event, 0.0f);
            GfMenuObject::startCallContext(context, 100, handle);
        }
    }
}

}  // namespace gf
