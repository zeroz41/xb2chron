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
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuObjNamedDialog.h"
#include "classes/ui/UIInputManager.h"
#include "ui/UIUtil.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UISelectObjList.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectSyncPlugin.h"
#include "gf/GfDataItem.h"
#include "gf/GfMenuItemUtil.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "plugin/Bdat.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"

namespace gf {

GfMenuObjCommonText::GfMenuObjCommonText(unsigned int handle)
    : GfMenuObject(handle), m_dialogCursor(nullptr), m_merSelect(nullptr), m_merCursor(nullptr), m_merNumber1(),
      m_merNumber2(), m_bladeList(nullptr), m_driverList(nullptr), m_kizunaSelect(nullptr), m_drChangeListInfo(nullptr),
      m_drChangeCursor(nullptr), m_numSelectNumber1(), m_numSelectNumber2(), m_numSelectStep(0) {
    m_merNumber1 = GfMenuReferenceNumber::create();
    m_merNumber1->m_value = 0;
    m_merNumber2 = GfMenuReferenceNumber::create();
    m_merNumber2->m_value = 0;
    m_bladeList = GfMenuBladeList::create();
    m_driverList = GfMenuDriverList::create();
    s_pItemList = GfMenuItemList::create();
    s_pSubMenuIDList = GfMenuIDList::create();
    ui::UIListInfoBase::SetupParam param;
    param.m_pageRowSize = 4;
    s_pSubMenuIDList->setup(getAllocator(ALLOCATOR(0)), param);
    s_pChangeDrList = GfMenuDriverList::create();
    m_numSelectNumber1 = GfMenuReferenceNumber::create();
    m_numSelectNumber1->m_value = 0;
    m_numSelectNumber2 = GfMenuReferenceNumber::create();
    m_numSelectNumber2->m_value = 0;
}

GfMenuObjCommonText::~GfMenuObjCommonText() {
    m_merNumber1 = nullptr;
    m_merNumber2 = nullptr;
    if (m_drChangeCursor != nullptr) {
        m_drChangeCursor->release();
        m_drChangeCursor = nullptr;
    }
    if (m_drChangeListInfo != nullptr) {
        m_drChangeListInfo->release();
        m_drChangeListInfo = nullptr;
    }
    if (s_pChangeDrList != nullptr) {
        s_pChangeDrList->release();
        s_pChangeDrList = nullptr;
    }
    if (s_pSubMenuIDList != nullptr) {
        s_pSubMenuIDList->release();
        s_pSubMenuIDList = nullptr;
    }
    if (s_pItemList != nullptr) {
        s_pItemList->release();
        s_pItemList = nullptr;
    }
    if (m_merSelect != nullptr) {
        m_merSelect->release();
        m_merSelect = nullptr;
    }
    if (m_merCursor != nullptr) {
        m_merCursor->release();
        m_merCursor = nullptr;
    }
    if (m_kizunaSelect != nullptr) {
        m_kizunaSelect->release();
        m_kizunaSelect = nullptr;
    }
    if (m_bladeList != nullptr) {
        m_bladeList->release();
        m_bladeList = nullptr;
    }
    if (m_driverList != nullptr) {
        m_driverList->release();
        m_driverList = nullptr;
    }
    if (m_dialogCursor != nullptr) {
        m_dialogCursor->release();
        m_dialogCursor = nullptr;
    }
    m_numSelectNumber1 = nullptr;
    m_numSelectNumber2 = nullptr;
}

void GfMenuObjCommonText::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjCommonText::update() {
    GfMenuObject::update();
}

void GfMenuObjCommonText::setupDialog(unsigned int handle) {
    GfMenuObjUtil::FitOption option;
    option.m_addHalfSize = true;
    option.m_keepScaleX = true;
    unsigned int text = ui::UIUtil::searchChild(handle, "LAY_dialog_text");
    GfMenuObjUtil::createFitPlugin(ui::UIUtil::searchChild(handle, "IMG_dialog_win@01"), text, 0, 0, option);
    GfMenuObjUtil::createFitPlugin(ui::UIUtil::searchChild(handle, "IMG_dialog_win@02"), text, 0, 0, option);
    unsigned int cursor = ui::UIUtil::searchChild(handle, "LAY_dialog_cursor");
    ui::UIObjectSyncPlugin* plugin;
    {
        ui::UIObjectAcc acc(cursor);
        plugin = ui::UIObjectSyncPlugin::create(acc.searchSibiling("LAY_dialog_cursor_base"));
    }
    plugin->setTargetObject(cursor);
    plugin->setTargetFlag(0x3E);
    if (plugin != nullptr) {
        plugin->release();
    }
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
// 2.0.0's symbols name it
bool GfMenuObjCommonText::s_OpenNamedDialog;

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

void GfMenuObjCommonText::openSubMenu(GfMenuCallContext* context, const GfMenuIDList* ids, const SubMenuOption& param) {
    unsigned int handle = GfMenuObject::getAttachedObject(100);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        bool term = ui::UIObjectAcc(handle).isTerm();
        if (context != nullptr && !term) {
            s_pSubMenuIDList->clear();
            for (unsigned int i = 0; i < ids->getSize(); i++) {
                s_pSubMenuIDList->addContents(ids->getContents(i));
            }
            s_pSubMenuIDList->setIndex(param.m_index);
            ui::EventData event;
            event.m_type = 0x21;
            event.m_param0 = 0;
            event.m_paramShort[2] = param.pad_0;
            event.m_paramShort[3] = param.pad_4;
            event.m_paramShort[4] = param.pad_6;
            event.m_paramShort[7] = 5;
            GfMenuObject::sendEvent(handle, event, 0.0f);
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

void GfMenuObjCommonText::ErrorListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc main(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setSuspend(true);
        m_shown = 0;
        break;
    case 3:
        if (event.m_param0 == 0) {
            return;
        }
        if (event.m_param0 == 2 && m_shown == 0) {
            acc.setSuspend(true);
        }
        break;
    case 8:
        GfMenuObject::addResultCallContext(main.searchChild("LAY_main"), 0, 0);
        GfMenuObjCommonText::close();
        break;
    case 0x21: {
        unsigned short text = event.m_paramShort[1];
        unsigned short bottom = event.m_paramShort[6];
        if (text != 0xFFFF) {
            GfMenuObjUtil::setChildText(handle, "TXT_error", text);
        }
        GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeIn(handle, 1, 0));
        GfMenuObject::enableInput(handle);
        mm::Rect<short> rect;
        acc.getLayoutRect(bottom == 0 ? "error_dialog_top" : "error_dialog_bottom", rect);
        acc.setPosCenter(mm::Pnt<short>(rect.x + rect.w / 2, rect.y + rect.h / 2));
        m_shown = 1;
        break;
    }
    case 0x22:
        GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeOut(handle, 2, 0));
        GfMenuObject::disableInput(handle);
        m_shown = 0;
        break;
    }
    UIObjectListener::reciveEvent(event, handle);
}

void GfMenuObjCommonText::OwnerChangeListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        acc.setSuspend(true);
        GfMenuObject::disableInput(acc.m_handle);
        m_shown = 0;
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 8: {
        int input = event.m_param1;
        if (input == 1 || input == 2) {
            GfMenuObjCommonText::close();
        }
        GfMenuObjUtil::playSECommonFromInput(input);
        break;
    }
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableInput(acc.m_handle);
        } else if (event.m_param0 == 2) {
            acc.setDisp(false);
            acc.setAlpha(1.0f);
            if (m_shown == 0) {
                acc.setSuspend(true);
            }
        }
        break;
    case 0x21: {
        unsigned short kind = event.m_paramShort[0];
        {
            GfMenuObjUtil::CtrlParam param;
            param.m_time = 0.25f;
            param.m_eventId = 1;
            param.m_methods = 1;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        }
        acc.setDispChild(kind == 0, "TXT_owner_change_caption");
        acc.setDispChild(kind == 1, "TXT_owner_change_caption_rex");
        acc.setDispChild(kind == 2, "TXT_owner_change_caption_rex2");
        {
            ui::UIObjectAcc ok(acc.searchChild("LAY_owner_ch_ok_only"));
            GfMenuObjUtil::setDockPos(acc.searchChild("IMG_owner_ch_cursor_l"), ok.m_handle, 1, true);
            GfMenuObjUtil::addPos(acc.searchChild("IMG_owner_ch_cursor_l"), -10, 0);
            GfMenuObjUtil::setDockPos(acc.searchChild("IMG_owner_ch_cursor_r"), ok.m_handle, 2, true);
            GfMenuObjUtil::addPos(acc.searchChild("IMG_owner_ch_cursor_r"), 10, 0);
        }
        m_shown = 1;
        break;
    }
    case 0x22: {
        GfMenuObject::disableInput(acc.m_handle);
        GfMenuObjUtil::CtrlParam param;
        param.m_time = 0.25f;
        param.m_eventId = 2;
        param.m_methods = 2;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        m_shown = 0;
        break;
    }
    }
}

void GfMenuObjCommonText::GetItemListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        acc.setSuspend(true);
        GfMenuObject::disableInput(acc.m_handle);
        m_shown = 0;
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 8: {
        int input = event.m_param1;
        if (input == 1 || input == 2) {
            GfMenuObjCommonText::close();
        }
        GfMenuObjUtil::playSECommonFromInput(input);
        break;
    }
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableInput(acc.m_handle);
        } else if (event.m_param0 == 2) {
            acc.setDisp(false);
            acc.setAlpha(1.0f);
            if (m_shown == 0) {
                acc.setSuspend(true);
            }
        }
        break;
    case 0x21: {
        {
            GfMenuObjUtil::CtrlParam param;
            param.m_time = 0.25f;
            param.m_methods = 1;
            param.m_delay = 1.0f / 30.0f;
            param.m_eventId = 1;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        }
        acc.setAlpha(0.0f);
        {
            ui::UIObjectAcc ok(acc.searchChild("LAY_get_item_ok_only"));
            GfMenuObjUtil::setDockPos(acc.searchChild("IMG_get_item_cursor_l"), ok.m_handle, 1, true);
            GfMenuObjUtil::addPos(acc.searchChild("IMG_get_item_cursor_l"), -10, 0);
            GfMenuObjUtil::setDockPos(acc.searchChild("IMG_get_item_cursor_r"), ok.m_handle, 2, true);
            GfMenuObjUtil::addPos(acc.searchChild("IMG_get_item_cursor_r"), 10, 0);
        }
        mm::Rect<short> rect;
        mm::Rect<short> next;
        acc.getLayoutRect("item_3", rect);
        acc.getLayoutRect("item_4", next);
        GfMenuObjUtil::placeObjectV(acc.m_handle, "LAY_get_item@%02d", s_pItemList->getSize(),
                                    mm::Pnt<short>(rect.x + rect.w / 2, rect.y + rect.h / 2), next.y - rect.y);
        m_shown = 1;
        break;
    }
    case 0x22: {
        GfMenuObject::disableInput(acc.m_handle);
        GfMenuObjUtil::CtrlParam param;
        param.m_time = 0.25f;
        param.m_eventId = 2;
        param.m_methods = 2;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        m_shown = 0;
        break;
    }
    }
}

void GfMenuObjCommonText::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    if (event.m_type == 1) {
        m_kind = 0xFF;
    } else if (event.m_type == 0x21) {
        GfMenuAdapterManager::addActiveCategory(3);
        m_kind = event.m_paramShort[7];
        // the layout of the dialog kind
        unsigned int child;
        switch (m_kind) {
        case 0:
            child = acc.searchChild("LAY_dialog");
            break;
        case 1:
            child = acc.searchChild("LAY_error");
            break;
        case 2:
            child = acc.searchChild("LAY_dialog_mer");
            break;
        case 3:
            child = acc.searchChild("LAY_dialog_kizuna");
            break;
        case 4:
            child = acc.searchChild("LAY_get_item");
            break;
        case 5:
            child = acc.searchChild("LAY_select");
            break;
        case 6:
            child = acc.searchChild("LAY_dr_change");
            break;
        case 7:
            child = acc.searchChild("LAY_owner_change");
            break;
        case 8:
            child = acc.searchChild("LAY_num_select");
            break;
        default:
            GfMenuObject::termCallContext(acc.m_handle);
            return;
        }
        if (child == 0) {
            return;
        }
        if (m_kind == 5) {
            GfMenuObject::sendEvent(child, event, 1.0f / 15.0f);
        } else {
            GfMenuObject::sendEvent(child, event, 0.0f);
        }
        ui::UIObjectAcc(child).setSuspend(false);
        ui::UIInputManager* input = ui::UIInputManager::get();
        m_savedLayer = input->m_minimumLayerHandle;
        input->m_minimumLayerHandle = ui::UIUtil::getGroupPriority(4);
        GfMenuObjUtil::playSE(9);
    } else if (event.m_type == 0x22) {
        // the layout of the dialog kind
        unsigned int child;
        switch (m_kind) {
        case 0:
            child = acc.searchChild("LAY_dialog");
            break;
        case 1:
            child = acc.searchChild("LAY_error");
            break;
        case 2:
            child = acc.searchChild("LAY_dialog_mer");
            break;
        case 3:
            child = acc.searchChild("LAY_dialog_kizuna");
            break;
        case 4:
            child = acc.searchChild("LAY_get_item");
            break;
        case 5:
            child = acc.searchChild("LAY_select");
            break;
        case 6:
            child = acc.searchChild("LAY_dr_change");
            break;
        case 7:
            child = acc.searchChild("LAY_owner_change");
            break;
        case 8:
            child = acc.searchChild("LAY_num_select");
            break;
        default:
            return;
        }
        if (child == 0) {
            return;
        }
        GfMenuObject::sendEvent(child, event, 0.0f);
        ui::UIInputManager* input = ui::UIInputManager::get();
        input->m_minimumLayerHandle = m_savedLayer;
        GfMenuObject::termCallContext(handle);
        m_kind = 0xFF;
        GfMenuAdapterManager::delActiveCategory(3);
        if (GfMenuObjCommonText::s_OpenNamedDialog) {
            GfMenuObjNamedDialog::close();
            GfMenuObjCommonText::s_OpenNamedDialog = false;
        }
    }
    UIObjectListener::reciveEvent(event, handle);
}

void GfMenuObjCommonText::DrChangeListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::disableInput(acc.m_handle);
        acc.setDisp(false);
        acc.setSuspend(true);
        m_shown = 0;
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        s_pChangeDrList->setIndex(index);
        m_owner->m_drChangeListInfo->setIndex(index);
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSECommonCursor();
        }
        break;
    }
    case 0x22: {
        GfMenuObjUtil::CtrlParam param;
        param.m_time = 0.25f;
        param.m_eventId = 2;
        param.m_methods = 2;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        GfMenuObject::disableInput(acc.m_handle);
        m_shown = 0;
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableInput(acc.m_handle);
            m_owner->m_drChangeCursor->setDisp(true);
        } else if (event.m_param0 == 2) {
            if (m_shown == 0) {
                acc.setSuspend(true);
            }
        }
        break;
    case 8: {
        int input = event.m_param1;
        if (input == 1) {
            unsigned int result = event.m_param0;
            GfMenuObject::addResultCallContext(acc.getParentHandle(), result, 0);
            GfMenuObjUtil::playSE(10);
        } else if (input == 2) {
            GfMenuObjUtil::playSECommonCancel();
        } else {
            break;
        }
        GfMenuObjCommonText::close();
        m_owner->m_drChangeCursor->setDisp(true);
        break;
    }
    case 0x21: {
        acc.setAlpha(1.0f);
        mm::Rect<short> rect;
        {
            GfMenuObjUtil::CtrlParam param;
            param.m_time = 0.25f;
            param.m_eventId = 1;
            param.m_methods = 1;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        }
        mm::Rect<short> next;
        acc.getLayoutRect("dr_select", rect);
        acc.getLayoutRect("dr_select_next", next);
        GfMenuObjUtil::placeObjectH(acc.m_handle, "LAY_dr_change@%02d", s_pChangeDrList->getSize(),
                                    mm::Pnt<short>(rect.x + rect.w / 2, rect.y + rect.h / 2), next.x - rect.x);
        m_owner->m_drChangeCursor->setDisp(false);
        GfMenuObject::resetInputSelection(acc.m_handle);
        GfMenuObject::setupInputSelectionFromList(acc.m_handle, *s_pChangeDrList);
        m_shown = 1;
        break;
    }
    }
}

void GfMenuObjCommonText::openWithNamed(GfMenuCallContext* context, unsigned int text, unsigned int row) {
    open(context, text, 0);
    if (GfGameManager::isEnableNamedRecord()) {
        GfMenuObjNamedDialog::open(row);
        s_OpenNamedDialog = true;
    }
}

}  // namespace gf
