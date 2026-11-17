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
#include "classes/gf/GfMenuReferenceAdapter.h"
#include "classes/ui/UIManager.h"
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
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfGameMercenaries.h"
#include "classes/gf/GfMenuMercenariesAdapter.h"
#include "classes/gf/GfMenuMissionAdapter.h"
#include "classes/gf/GfMenuZoneAdapter.h"
#include "gf/GfDataMercenaries.h"
#include "classes/gf/GfBdatCond.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataDriver.h"
#include "mm/mtl/FixStr.h"
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

void GfMenuObjCommonText::MerListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        GfMenuAdapterManager::beginCategory(3);
        GfMenuZoneAdapter::createFromReference(acc.searchChild("IMG_dialog_mer_info_flag"), 2, m_owner->m_merNumber2, false);
        GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_dialog_mer_info_bl_face"), 3, 4, false);
        GfMenuMercenariesAdapter::createFromReferenceBlade(acc.searchChild("TXT_dialog_mer_info_unit_name"), 0, 4, false);
        GfMenuMissionAdapter::createFromReference(acc.searchChild("TXT_dialog_mer_info_mis_name"), 0, m_owner->m_merNumber1, false);
        GfMenuMissionAdapter::createFromReference(acc.searchChild("TXT_dialog_mer_info_time"), 5, m_owner->m_merNumber1, true);
        GfMenuObjUtil::createSyncPlugin(acc.searchChild("TXT_dialog_mer_info_time_inf"), acc.searchChild("TXT_dialog_mer_info_time"), 0x40);
        GfMenuAdapterManager::endCategory();
        {
            GfMenuObjUtil::FitOption option;
            option.m_addHalfSize = true;
            option.m_keepScaleX = true;
            GfMenuObjUtil::createFitPlugin(acc.searchChild("IMG_dialog_mer_win"), acc.searchChild("LAY_dialog_mer_main"), 0, 0, option);
        }
        {
            ui::UISelectObjList::CreateParam param;
            param.m_allocator = getAllocator(ALLOCATOR(0));
            m_owner->m_merSelect = ui::UISelectObjList::create(param);
        }
        {
            ui::UICtrlCursorSelect::CursorSetting setting;
            setting.setType(0);
            setting.m_dockType = 0;
            setting.m_outer = false;
            m_owner->m_merCursor = ui::UICtrlCursorSelect::create(acc.searchChild("LAY_dialog_mer_cursor"), setting, m_owner->m_merSelect);
        }
        GfMenuObjUtil::createSyncPlugin(acc.searchChild("LAY_dialog_mer_cursor_base"), acc.searchChild("LAY_dialog_mer_cursor"), 2);
        acc.setDisp(false);
        acc.setSuspend(true);
        m_shown = 0;
        break;
    }
    case 3:
        if (event.m_param0 == 0) {
            break;
        }
        if (event.m_param0 == 1) {
            GfMenuObject::enableInput(acc.m_handle);
        } else if (m_shown == 0) {
            GfGameMercenaries::stopMissionTime(false);
            acc.setSuspend(true);
        }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 6: {
        int index = event.m_param0;
        if (index != -1) {
            int prev = event.m_param1;
            m_owner->m_merSelect->setIndex(index);
            if (prev != -1 && index != prev) {
                GfMenuObjUtil::playSECommonCursor();
            }
        }
        break;
    }
    case 8: {
        int input = event.m_param1;
        if (input == 1) {
            int selected = event.m_param0;
            GfMenuObject::addResultCallContext(acc.getParentHandle(), selected != 0, 0);
            GfMenuObjCommonText::close();
        } else if (input == 2) {
            GfMenuObject::addResultCallContext(acc.getParentHandle(), 1, 0);
            GfMenuObjCommonText::close();
        }
        GfMenuObjUtil::playSECommonFromInput(input);
        break;
    }
    case 0x22:
        GfMenuObjUtil::setCommonFadeOut(acc.m_handle, 2, 0);
        m_owner->m_merCursor->setDisp(false);
        GfMenuObject::disableInput(acc.m_handle);
        m_shown = 0;
        break;
    case 0x21: {
        unsigned int blade = event.m_param0;
        unsigned short text = event.m_paramShort[2];
        unsigned short kind = event.m_paramShort[3];
        short index = event.m_paramShort[4];
        GfMenuObject::setText(acc.searchChild("TXT_dialog_mer_main_text"), text);
        GfGameMercenaries::stopMissionTime(true);
        if (blade == 0) {
            GfMenuObject::termCallContext(acc.getParentHandle());
        } else {
            unsigned int team = GfDataMercenaries::getTeamID(blade);
            unsigned int leader = GfDataMercenaries::getTeamLeader(team);
            unsigned int mission = GfDataMercenaries::getTeamMission(team);
            unsigned int zone = GfDataMercenaries::getMissionZoneID(mission);
            if (team == 0 || mission == 0 || zone == 0) {
                GfMenuObject::termCallContext(acc.getParentHandle());
            } else {
                m_owner->m_merNumber1->setValue(mission);
                m_owner->m_merNumber2->setValue(zone);
                GfMenuReference::setReferenceBladeID(4, leader);
                bool reward = GfDataMercenaries::isTeamStateReward(team);
                m_owner->m_merSelect->clear();
                if (kind == 0) {
                    acc.setDispChild(true, "LAY_dialog_mer_ok_only");
                    acc.setDispChild(false, "LAY_dialog_mer_select");
                    m_owner->m_merSelect->addObject(acc.searchChild("TXT_dialog_mer_ok_only"));
                    m_owner->m_merSelect->setIndex(0);
                } else {
                    acc.setDispChild(false, "LAY_dialog_mer_ok_only");
                    acc.setDispChild(true, "LAY_dialog_mer_select");
                    m_owner->m_merSelect->addObject(acc.searchChild("TXT_dialog_mer_ok"));
                    m_owner->m_merSelect->addObject(acc.searchChild("TXT_dialog_mer_cancel"));
                    m_owner->m_merSelect->setIndex(index);
                }
                if (reward) {
                    GfMenuObjUtil::setColMulandAdd(acc.searchChild("TXT_dialog_mer_info_unit_name"), "txt_disable");
                    ui::UIObjectAcc(acc.searchChild("TXT_dialog_mer_info_unit_name")).setAlpha(0.5f);
                    GfMenuObjUtil::setColMulandAdd(acc.searchChild("TXT_dialog_mer_info_mis_name"), "txt_disable");
                    ui::UIObjectAcc(acc.searchChild("TXT_dialog_mer_info_mis_name")).setAlpha(0.5f);
                    GfMenuObjUtil::setColMulandAdd(acc.searchChild("TXT_dialog_mer_info_time"), "txt_disable");
                    GfMenuObjUtil::setChildAddColor(acc.m_handle, "IMG_dialog_mer_info_base", "black");
                    ui::UIObjectAcc timeInf(acc.m_handle, "TXT_dialog_mer_info_time_inf");
                    timeInf.setAlpha(0.0f);
                } else {
                    GfMenuObjUtil::setColDefault(acc.searchChild("TXT_dialog_mer_info_unit_name"));
                    ui::UIObjectAcc(acc.searchChild("TXT_dialog_mer_info_unit_name")).setAlpha(1.0f);
                    GfMenuObjUtil::setColDefault(acc.searchChild("TXT_dialog_mer_info_mis_name"));
                    ui::UIObjectAcc(acc.searchChild("TXT_dialog_mer_info_mis_name")).setAlpha(1.0f);
                    GfMenuObjUtil::setColDefault(acc.searchChild("TXT_dialog_mer_info_time"));
                    GfMenuObjUtil::setColDefault(acc.searchChild("IMG_dialog_mer_info_base"));
                    ui::UIObjectAcc timeInf(acc.m_handle, "TXT_dialog_mer_info_time_inf");
                    timeInf.setAlpha(1.0f);
                }
                acc.setDispChild(reward, "TXT_dialog_mer_come_back");
                m_owner->m_merCursor->setDisp(true);
                GfMenuObject::resetInputSelection(acc.m_handle);
                GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_merSelect);
            }
        }
        sendEvent(acc.m_handle, 0x101, 0, 1);
        m_shown = 1;
        break;
    }
    case 0x101: {
        mm::Rect<short> rect;
        acc.getLayoutRect("dialog_top", rect);
        acc.setPosCenter(mm::Pnt<short>(rect.x + rect.w / 2, rect.y + rect.h / 2));
        GfMenuObjUtil::setCommonFadeIn(acc.m_handle, 1, 0);
        break;
    }
    }
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

void GfMenuObjCommonText::NumSelectListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc main(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuAdapterManager::beginCategory(3);
        GfMenuReferenceAdapter::create(acc.searchChild("TXT_num_select_value"), m_owner->m_numSelectNumber1, true);
        GfMenuReferenceAdapter::create(acc.searchChild("TXT_num_select_total_price"), m_owner->m_numSelectNumber2, true);
        GfMenuAdapterManager::endCategory();
        GfMenuObject::disableInput(acc.m_handle);
        acc.setDisp(false);
        acc.setSuspend(true);
        m_shown = 0;
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableInput(acc.m_handle);
        } else if (event.m_param0 == 2) {
            if (m_shown == 0) {
                acc.setSuspend(true);
            }
        }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 6: {
        int value = event.m_param0;
        int prev = event.m_param1;
        m_owner->m_numSelectNumber1->setValue(value);
        m_owner->m_numSelectNumber2->setValue(m_owner->m_numSelectStep * value);
        if (prev != -1 && value != prev) {
            GfMenuObjUtil::playSE(0x19);
        }
        break;
    }
    case 8:
        if (event.m_param1 == 1) {
            if (m_owner->m_numSelectNumber1->m_value == 0) {
                break;
            }
            GfMenuObject::addResultCallContext(main.searchChild("LAY_main"), 0, m_owner->m_numSelectNumber1->m_value);
            sendEvent(main.searchChild("LAY_main"), 0x22, 0, 0);
        } else if (event.m_param1 == 2) {
            GfMenuObject::addResultCallContext(main.searchChild("LAY_main"), 1, 0);
            sendEvent(main.searchChild("LAY_main"), 0x22, 0, 0);
        }
        GfMenuObjUtil::playSECommonFromInput(event.m_param1);
        break;
    case 0x21: {
        unsigned short kind = event.m_paramShort[0];
        ui::UIObjectAcc first(acc.searchChild("TXT_num_select_index@01"));
        first.setDisp(kind == 0);
        ui::UIObjectAcc second(acc.searchChild("TXT_num_select_index@02"));
        second.setDisp(kind != 0);
        m_owner->m_numSelectNumber1->setValue(0);
        m_owner->m_numSelectNumber1->setMin(event.m_paramShort[1]);
        m_owner->m_numSelectNumber1->setMax(event.m_paramShort[2]);
        m_owner->m_numSelectNumber2->setValue(0);
        m_owner->m_numSelectNumber2->setMin(0);
        m_owner->m_numSelectNumber2->setMax(999999999);
        m_owner->m_numSelectStep = event.m_param2;
        GfMenuObject::resetInputSelection(handle);
        GfMenuObject::setupInputSelection(handle, 0, event.m_paramShort[2] + 1);
        GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeIn(handle, 1, 0));
        m_shown = 1;
        break;
    }
    case 0x22:
        GfMenuObject::disableInput(acc.m_handle);
        GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeOut(handle, 2, 0));
        m_shown = 0;
        break;
    }
}

void GfMenuObjCommonText::KizunaListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc main(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        GfMenuAdapterManager::beginCategory(3);
        {
            mm::mtl::FixStr<32> name;
            unsigned int count = acc.countChild("LAY_dialog_kizuna_bl@%02d", 1);
            {
                ui::UIListInfoBase::SetupParam param;
                param.m_pageRowSize = count;
                m_owner->m_bladeList->setup(getAllocator(ALLOCATOR(0)), param);
            }
            for (unsigned int i = 0; i < count; i++) {
                name.format("IMG_dialog_kizuna_bl_face@%02d", i + 1);
                GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.m_str), 3, m_owner->m_bladeList, i, false);
            }
            count = acc.countChild("LAY_dialog_kizuna_dr@%02d", 1);
            {
                ui::UIListInfoBase::SetupParam param;
                param.m_pageRowSize = count;
                m_owner->m_driverList->setup(getAllocator(ALLOCATOR(0)), param);
            }
            for (unsigned int i = 0; i < count; i++) {
                name.format("IMG_dialog_kizuna_dr_face@%02d", i + 1);
                GfMenuCharDataAdapter::createFromDriverList(acc.searchChild(name.m_str), 3, m_owner->m_driverList, i, false);
            }
        }
        GfMenuAdapterManager::endCategory();
        {
            ui::UISelectObjList::CreateParam param;
            param.m_allocator = getAllocator(ALLOCATOR(0));
            m_owner->m_kizunaSelect = ui::UISelectObjList::create(param);
        }
        GfMenuObjUtil::FitOption option;
        option.m_addHalfSize = true;
        option.m_keepScaleX = true;
        GfMenuObjUtil::createFitPlugin(acc.searchChild("IMG_kizuna_kizuna_win"), acc.searchChild("LAY_dialog_kizuna_main"), 0, 0,
                                       option);
        acc.setSuspend(true);
        m_shown = 0;
        break;
    }
    case 3:
        if (event.m_param0 == 0) {
            return;
        }
        if (event.m_param0 == 1) {
            GfMenuObject::enableInput(acc.m_handle);
        } else if (m_shown == 0) {
            acc.setSuspend(true);
        }
        break;
    case 8: {
        int input = event.m_param1;
        GfMenuObject::addResultCallContext(main.searchChild("LAY_main"), 0, 0);
        GfMenuObject::disableInput(handle);
        GfMenuObjCommonText::close();
        GfMenuObjUtil::playSECommonFromInput(input);
        break;
    }
    case 0x21: {
        unsigned int condition = event.m_param0;
        unsigned short title = event.m_param1;
        mm::mtl::FixStr<32> name;
        GfMenuObject::setText(acc.searchChild("TXT_dialog_kizuna_title"), title);
        m_owner->m_driverList->clear();
        m_owner->m_bladeList->clear();
        m_owner->m_kizunaSelect->clear();
        GfBdatCond* cond = mm::mtl::PtrSingleton<GfBdatCond>::get();
        for (unsigned int i = 0; i < 8; i++) {
            if (cond->getConditionListConditionType(condition, i) != 6) {
                continue;
            }
            unsigned int party = cond->getConditionListCondition(condition, i);
            if (party == 0) {
                continue;
            }
            if (cond->getConditionPTCategory(party) == 0) {
                for (unsigned int slot = 0; slot < 3; slot++) {
                    unsigned int pc = cond->getConditionPTPCID(party, slot);
                    if (pc == 0) {
                        continue;
                    }
                    if (GfDataDriver::isDriver(pc)) {
                        MenuDriverInfo info;
                        info.m_driver = pc;
                        m_owner->m_driverList->addContents(info);
                        name.format("LAY_dialog_kizuna_dr@%02d", m_owner->m_driverList->getSize());
                    } else if (GfDataBlade::isBladeID(pc)) {
                        MenuBladeInfo info;
                        info.m_blade = pc;
                        m_owner->m_bladeList->addContents(info);
                        name.format("LAY_dialog_kizuna_bl@%02d", m_owner->m_bladeList->getSize());
                    } else {
                        continue;
                    }
                    m_owner->m_kizunaSelect->addObject(acc.searchChild(name.m_str));
                    acc.setDispChild(true, name.m_str);
                }
            } else if (cond->getConditionPTCategory(party) == 6) {
                unsigned int blade = cond->getConditionPTPCID(party, 0);
                if (blade != 0) {
                    MenuDriverInfo info;
                    info.m_driver = GfDataBlade::getCreator(blade);
                    if (info.m_driver != 0) {
                        m_owner->m_driverList->addContents(info);
                        name.format("LAY_dialog_kizuna_dr@%02d", m_owner->m_driverList->getSize());
                        m_owner->m_kizunaSelect->addObject(acc.searchChild(name.m_str));
                        acc.setDispChild(true, name.m_str);
                    }
                }
            }
        }
        for (unsigned int n = m_owner->m_driverList->getSize(); n < m_owner->m_driverList->getPageRowSize();) {
            n++;
            name.format("LAY_dialog_kizuna_dr@%02d", n);
            acc.setDispChild(false, name.m_str);
        }
        for (unsigned int n = m_owner->m_bladeList->getSize(); n < m_owner->m_bladeList->getPageRowSize();) {
            n++;
            name.format("LAY_dialog_kizuna_bl@%02d", n);
            acc.setDispChild(false, name.m_str);
        }
        {
            mm::Rect<short> rect;
            mm::Rect<short> next;
            acc.getLayoutRect("kizuna_blade", rect);
            acc.getLayoutRect("kizuna_blade_next", next);
            GfMenuObjUtil::placeObjectH(m_owner->m_kizunaSelect, mm::Pnt<short>(rect.x + rect.w / 2, rect.y + rect.h / 2),
                                        next.x - rect.x);
        }
        {
            mm::Pnt<short> pos;
            ui::UIObjectAcc ok(acc.m_handle, "LAY_dialog_kizuna_ok_only");
            ok.getPosCenter(pos);
            ui::UIObjectAcc cursor(acc.m_handle, "LAY_dialog_kizuna_cursor");
            cursor.setPosCenter(pos);
        }
        GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeIn(handle, 1, 0));
        m_shown = 1;
        break;
    }
    case 0x22:
        GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeOut(handle, 2, 0));
        m_shown = 0;
        break;
    }
    UIObjectListener::reciveEvent(event, handle);
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

// the cursor targets of the dialog's three kinds (DialogListener's m_state). Proposed names, not the original's:
// the symbols leave them unnamed (lbl_7100B61650, lbl_7100B61658, lbl_7100B61668)
static const char* s_dialogOkOnlyTargets[] = {"LAY_dialog_ok_only_text"};
static const char* s_dialogSelectTargets[] = {"LAY_dialog_ok_text", "LAY_dialog_cancel_text"};
static const char* s_dialogSelectLongTargets[] = {"LAY_dialog_ok_text_long@01", "LAY_dialog_ok_text_long@02",
                                                  "LAY_dialog_cancel_text_long"};

void GfMenuObjCommonText::DialogListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc main(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        m_state = 0;
        GfMenuObjCommonText::setupDialog(handle);
        GfMenuObjUtil::CursorParam param;
        param.m_parent = acc.getParentHandle();
        param.m_cursor = acc.searchChild("LAY_dialog_cursor");
        param.m_type = 0;
        param.m_setting.m_dockType = 0;
        param.m_setting.m_outer = false;
        param.m_names = s_dialogSelectTargets;
        param.m_nameCount = 2;
        m_owner->m_dialogCursor = GfMenuObjUtil::createCursor(param);
        acc.setDisp(false);
        GfMenuObject::disableInput(handle);
        acc.setSuspend(true);
        m_shown = 0;
        return;
    }
    case 3:
        if (event.m_param0 == 0) {
            return;
        }
        if (event.m_param0 == 1) {
            GfMenuObject::enableInput(handle);
        } else if (event.m_param0 == 2) {
            if (m_shown == 0) {
                acc.setSuspend(true);
            }
        }
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        m_owner->m_dialogCursor->inputChange(index);
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSECommonCursor();
        }
        return;
    }
    case 8:
        if (event.m_param1 == 1) {
            unsigned int index = event.m_param0;
            if (m_state == 2) {
                bool cancel = !(index == 0 || index == 1);
                GfMenuObject::addResultCallContext(main.searchChild("LAY_main"), cancel, 0);
                if (!cancel) {
                    bool second = index != 0;
                    GfMenuObject::addResultCallContext(main.searchChild("LAY_main"), second, 1);
                }
            } else {
                bool yes = index != 0;
                GfMenuObject::addResultCallContext(main.searchChild("LAY_main"), yes, 0);
            }
            GfMenuObjCommonText::close();
        } else if (event.m_param1 == 2) {
            if (m_state == 1 || m_state == 2) {
                GfMenuObject::addResultCallContext(main.searchChild("LAY_main"), 1, 0);
                m_owner->m_dialogCursor->open(1);
                GfMenuObjCommonText::close();
            }
        }
        GfMenuObjUtil::playSECommonFromInput(event.m_param1);
        return;
    case 0x101: {
        int bottom = event.m_param0;
        GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeIn(handle, 1, 0));
        acc.setDisp(true);
        mm::Rect<short> rect;
        acc.getLayoutRect(bottom == 0 ? "dialog_top" : "dialog_bottom", rect);
        acc.setPosCenter(mm::Pnt<short>(rect.x + rect.w / 2, rect.y + rect.h / 2));
        ui::UIObjectAcc titleAcc(acc.m_handle, "TXT_dialog_title");
        mm::Pnt<short> pos;
        titleAcc.getPosCenter(pos);
        pos.x = rect.w / 2;
        titleAcc.setPosCenter(pos);
        break;
    }
    case 0x21: {
        unsigned short title = event.m_paramShort[0];
        unsigned short text = event.m_paramShort[1];
        unsigned short ok = event.m_paramShort[2];
        unsigned short cancel = event.m_paramShort[3];
        unsigned short kind = event.m_paramShort[4];
        unsigned short selected = event.m_paramShort[5];
        unsigned short bottom = event.m_paramShort[6];
        m_state = kind;
        GfMenuObjUtil::setChildDisp(handle, "LAY_dialog_ok_only", kind == 0);
        GfMenuObjUtil::setChildDisp(handle, "LAY_dialog_select", kind == 1);
        GfMenuObjUtil::setChildDisp(handle, "LAY_dialog_select_long", kind == 2);
        GfMenuObjUtil::setChildDisp(handle, "IMG_dialog_cursor_r", kind != 2);
        GfMenuObjUtil::setChildDisp(handle, "IMG_dialog_cursor_r_long", kind == 2);
        {
            ui::UIObjectAcc cursor(handle, "LAY_dialog_cursor");
            cursor.updateLayoutSize();
        }
        int count = 0;
        switch (kind) {
        case 0:
            GfMenuObjUtil::changeCursorTarget(m_owner->m_dialogCursor, main.m_handle, s_dialogOkOnlyTargets, 1);
            count = 1;
            break;
        case 1:
            GfMenuObjUtil::changeCursorTarget(m_owner->m_dialogCursor, main.m_handle, s_dialogSelectTargets, 2);
            count = 2;
            break;
        case 2:
            GfMenuObjUtil::changeCursorTarget(m_owner->m_dialogCursor, main.m_handle, s_dialogSelectLongTargets, 3);
            count = 3;
            break;
        }
        unsigned int index = kind == 0 ? 2 : selected;
        m_owner->m_dialogCursor->open(index);
        if (m_state == 2) {
            GfMenuObjUtil::setChildDisp(handle, "LAY_dialog_title", false);
            if (title != 0xFFFF) {
                GfMenuObjUtil::setChildText(handle, "TXT_dialog_ok_long@02", title);
            }
        } else {
            GfMenuObjUtil::setChildDisp(handle, "LAY_dialog_title", title != 0xFFFF);
            if (title != 0xFFFF) {
                GfMenuObjUtil::setChildText(handle, "TXT_dialog_title", title);
            }
        }
        if (text != 0xFFFF) {
            GfMenuObjUtil::setChildText(handle, "TXT_dialog_text", text);
        }
        switch (kind) {
        case 0:
            if (ok != 0xFFFF) {
                GfMenuObjUtil::setChildText(handle, "TXT_dialog_ok_only", ok);
            }
            break;
        case 1:
            if (ok != 0xFFFF) {
                GfMenuObjUtil::setChildText(handle, "TXT_dialog_ok", ok);
            }
            if (cancel != 0xFFFF) {
                GfMenuObjUtil::setChildText(handle, "TXT_dialog_select_cancel", cancel);
            }
            break;
        case 2:
            if (ok != 0xFFFF) {
                GfMenuObjUtil::setChildText(handle, "TXT_dialog_ok_long@01", ok);
            }
            if (cancel != 0xFFFF) {
                GfMenuObjUtil::setChildText(handle, "TXT_dialog_select_cancel_long", cancel);
            }
            break;
        }
        GfMenuObjUtil::setChildDisp(handle, "LAY_dialog", true);
        GfMenuObjUtil::setChildDisp(handle, "IMG_dialog_win@01", true);
        GfMenuObjUtil::setChildDisp(handle, "IMG_dialog_win@02", false);
        GfMenuObject::resetInputSelection(handle);
        GfMenuObject::setupInputSelection(handle, index, count);
        GfMenuObject::disableInput(handle);
        mm::Rect<short> rect;
        acc.getLayoutRect(bottom == 0 ? "dialog_top" : "dialog_bottom", rect);
        acc.setPosCenter(mm::Pnt<short>(rect.x + rect.w / 2, rect.y + rect.h / 2));
        acc.setDisp(false);
        ui::UIObjectAcc titleAcc(acc.m_handle, "TXT_dialog_title");
        mm::Pnt<short> pos;
        titleAcc.getPosCenter(pos);
        pos.x = rect.w / 2;
        titleAcc.setPosCenter(pos);
        sendEvent(handle, 0x101, bottom, 1);
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
