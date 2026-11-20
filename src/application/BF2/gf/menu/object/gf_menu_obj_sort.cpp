#include "classes/gf/GfMenuObjSort.h"
#include "classes/gf/GfMenuObjSort/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfDataFieldSkill.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"

namespace gf {

// the count of BDAT 0x16D's sort_type<N> members, which initialize counts. Proposed name, not the original's: the
// symbols leave it unnamed (lbl_7100EAB92C); the original reaches it without the GOT, so it is a file static
static unsigned int s_sortTypeCount;

GfMenuObjSort::GfMenuObjSort(unsigned int handle)
    : GfMenuObject(handle), m_resultHandle(0), m_callerHandle(0), m_menu(0), m_idList(nullptr) {
    m_idList = GfMenuIDList::create();
}

GfMenuObjSort::~GfMenuObjSort() {
    if (m_idList != nullptr) {
        m_idList->release();
        m_idList = nullptr;
    }
}

void GfMenuObjSort::initialize() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    GfMenuObject::attachExternalCall(0x83, main.m_handle);
#line 55
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(main.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
    {
        ui::UIObjectAcc list(main.m_handle, "LAY_list");
        ui::UIObjectAcc text(main.m_handle, "TXT_cur_name");
        GfMenuObjUtil::createDockPlugin(list.m_handle, text.m_handle, 3, mm::Pnt<short>(0, 16), 0);
    }
    GfMenuObjUtil::createVScrollBarPlugin(main.searchChild("IMG_list_scroll_bar"), m_idList, "IMG_list_scroll_base",
                                          true);
    GfMenuObjUtil::createSyncPlugin(main.searchChild("LAY_list_scroll_bar"), main.searchChild("IMG_list_scroll_base"),
                                    0x20);
    {
        ui::UIObjectAcc list(main.m_handle, "LAY_list");
        ui::UIObjectAcc base(main.m_handle, "IMG_base");
        GfMenuObjUtil::createFitPlugin(base.m_handle, list.m_handle, 16, 16, GfMenuObjUtil::FitOption());
    }
    unsigned char* bdat = GfDataBdat::getFP(0x16D);
    if (bdat != nullptr) {
        mm::mtl::FixStr<32> name;
        s_sortTypeCount = 0;
        name.format("sort_type%d", 1);
        while (Bdat::getMember(bdat, name.m_str) != nullptr) {
            s_sortTypeCount++;
            name.format("sort_type%d", s_sortTypeCount + 1);
        }
    }
    ui::UIListInfoBase::SetupParam param;
    param.m_pageRowSize = main.countChild("LAY_list_item@%02d", 1);
    param.m_pageScroll = true;
    m_idList->setup(getAllocator(ALLOCATOR(0)), param);
    GfMenuObject::initialize();
}

void GfMenuObjSort::finalize() {
    GfMenuObject::finalize();
}

// 1.0.0 has it out of line; 3.0.1 only inlines it
inline void GfMenuObjSort::close() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x83));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x22;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjSort::update() {
    if (m_resultHandle != 0) {
        ui::UIObjectAcc acc(m_resultHandle);
        if (acc.m_object == nullptr || acc.isTerm()) {
            close();
        }
    }
    GfMenuObject::update();
}

void GfMenuObjSort::refreshItem() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < m_idList->getPageRowSize(); i++) {
        unsigned int id = m_idList->getContents(m_idList->getPageIndex(i)).m_id;
        bool disp = id != 0;
        name.format("LAY_list_item@%02d", i + 1);
        ui::UIObjectAcc item(main.m_handle, name.m_str);
        item.setDisp(disp);
        if (id != 0) {
            unsigned int selected = m_idList->getIndex(true);
            name.format("TXT_list_name@%02d", i + 1);
            setSortLabelText(id, main.searchChild(name.m_str));
            ui::UIObjectAcc(main.m_handle, name.m_str).setAlpha(i == selected ? 0.0f : 1.0f);
            name.format("TXT_list_select@%02d", i + 1);
            setSortLabelText(id, main.searchChild(name.m_str));
            ui::UIObjectAcc(main.m_handle, name.m_str).setAlpha(i == selected ? 1.0f : 0.0f);
        }
    }
}

void GfMenuObjSort::setSortLabelText(unsigned short sortId, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    ui::UIStr text;
    unsigned char* bdat;
    unsigned int id;
    if (sortId >= 100) {
        if (GfDataFieldSkill::getName(bdat, id, static_cast<unsigned short>(sortId - 100))) {
            text.setupMstxt(bdat, id);
        }
    } else {
        if (!GfMenuBdat::isValidBdatID(GfDataBdat::getFP(0x14E), sortId)) {
            return;
        }
        unsigned short msg = GfMenuObjUtil::getMsgIDFromList(0x14E, sortId);
        text.setupMstxt(GfDataBdat::getFP(0x11E), msg);
    }
    acc.setText(text);
}

// the enhance<N> column of BDAT 0x16E a sort type lists (the name is not the original's)
static inline int getEnhanceColumn(unsigned int type) {
    int column = 0;
    if (type == 0xE) {
        column = 1;
    }
    if (type == 0xF) {
        column = 2;
    }
    if (type == 0x10) {
        column = 3;
    }
    if (type == 0x11) {
        column = 4;
    }
    return column;
}

void GfMenuObjSort::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    case 6: {
        int index = event.m_param0;
        if (index != -1) {
            int previous = event.m_param1;
            m_owner->m_idList->setIndex(index);
            m_owner->refreshItem();
            if (previous != -1 && index != previous) {
                GfMenuObjUtil::playSECommonCursor();
            }
        }
        break;
    }
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::enableInput(acc.m_handle);
        }
        break;
    case 8: {
        int index = event.m_param0;
        int input = event.m_param1;
        ui::UIObjectAcc caller(m_owner->m_callerHandle);
        switch (input) {
        case 1:
            if (m_openIndex != index) {
                GfMenuIDList* list = m_owner->m_idList;
                setSortLabelText(list->getContents(list->getIndex(false)).m_id, caller.m_handle);
            }
            GfMenuObjUtil::playSECommonDecide();
            break;
        case 2:
            index = m_openIndex;
            GfMenuObjUtil::playSECommonCancel();
            break;
        default:
            return;
        }
        ui::EventData result;
        result.m_type = 0x148;
        result.m_param0 = index;
        result.m_param1 = input == 1;
        GfMenuObject::sendEvent(m_owner->m_resultHandle, result, 0.0f);
        {
            ui::UIObjectAcc cursor(acc.m_handle, "LAY_cur");
            cursor.setAlpha(0.0f);
            caller.setDisp(true);
        }
        close();
        break;
    }
    case 0x22: {
        {
            ui::UIObjectAcc base(acc.m_handle, "IMG_base");
            int ctrl = GfMenuObjUtil::getCtrlID(base.m_handle);
            if (ctrl != 0) {
                GfMenuObjUtil::stopCtrl(ctrl);
            }
        }
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_time = 0.2f;
        param.m_eventId = 2;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        GfMenuObject::disableInput(acc.m_handle);
        m_owner->m_resultHandle = 0;
        m_owner->m_callerHandle = 0;
        m_owner->m_menu = 0;
        GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
        break;
    }
    case 0x21: {
        unsigned int resultHandle = event.m_param0;
        unsigned int callerHandle = event.m_param1;
        unsigned short menu = event.m_paramShort[4];
        unsigned short index = event.m_paramShort[5];
        ui::UIObjectAcc caller(callerHandle);
        m_owner->m_idList->clear();
        {
            unsigned char* bdat = GfDataBdat::getFP(0x16D);
            mm::mtl::FixStr<32> name;
            for (unsigned int i = 0; i < s_sortTypeCount; i++) {
                name.format("sort_type%d", i + 1);
                if (Bdat::getMember(bdat, name.m_str) == nullptr) {
                    continue;
                }
                unsigned short type = Bdat::getVal(bdat, name.m_str, menu);
                if (type == 0) {
                    continue;
                }
                int listed = 0;
                int enhance = getEnhanceColumn(type);
                if (enhance != 0) {
                    unsigned char* table = GfDataBdat::getFP(0x16E);
                    name.format("enhance%d", enhance);
                    if (Bdat::getMember(table, name.m_str) != nullptr) {
                        for (int j = 0; j < Bdat::getIdCount(table); j++) {
                            unsigned short value = Bdat::getVal(table, name.m_str, Bdat::getIdTop(table) + j);
                            if (value != 0) {
                                m_owner->m_idList->addContents(MenuID{value + 0x20u, 0});
                            }
                        }
                    }
                    listed = 1;
                }
                if (type == 0x15) {
                    unsigned char* table = GfDataBdat::getFP(0x16F);
                    name.format("buff%d", 1);
                    if (Bdat::getMember(table, name.m_str) != nullptr) {
                        for (int j = 0; j < Bdat::getIdCount(table); j++) {
                            unsigned short value = Bdat::getVal(table, name.m_str, Bdat::getIdTop(table) + j);
                            if (value != 0) {
                                m_owner->m_idList->addContents(MenuID{value + 0x50u, 0});
                            }
                        }
                    }
                    listed = 1;
                }
                if (type == 0x14) {
                    unsigned char* table = GfDataBdat::getFP(0x170);
                    name.format("role%d", 1);
                    if (Bdat::getMember(table, name.m_str) != nullptr) {
                        for (int j = 0; j < Bdat::getIdCount(table); j++) {
                            unsigned short value = Bdat::getVal(table, name.m_str, Bdat::getIdTop(table) + j);
                            if (value != 0) {
                                m_owner->m_idList->addContents(MenuID{value + 0x40u, 0});
                            }
                        }
                    }
                    listed = 1;
                }
                if (type == 0x18) {
                    unsigned char* table = GfDataBdat::getFP(0x171);
                    name.format("fs%d", 1);
                    if (Bdat::getMember(table, name.m_str) != nullptr) {
                        for (int j = 0; j < Bdat::getIdCount(table); j++) {
                            unsigned short value = Bdat::getVal(table, name.m_str, Bdat::getIdTop(table) + j);
                            if (value != 0) {
                                m_owner->m_idList->addContents(MenuID{value + 100u, 0});
                            }
                        }
                    }
                    listed = 1;
                }
                if (!listed) {
                    m_owner->m_idList->addContents(MenuID{type, 0});
                }
            }
        }
        {
            ui::UIObjectAcc current(acc.m_handle, "TXT_cur_name");
            ui::UIStr text;
            caller.getText(text);
            current.setText(text);
        }
        {
            ui::UIObjectAcc current(acc.m_handle, "TXT_cur_name");
            mm::Rect<short> rect;
            caller.getRect(rect, 3);
            current.setPosCenter(mm::Pnt<short>(rect.x + rect.w / 2, rect.y + rect.h / 2));
        }
        {
            ui::UIObjectAcc cursor(acc.m_handle, "LAY_cur");
            cursor.setAlpha(1.0f);
        }
        if (index >= static_cast<unsigned int>(m_owner->m_idList->getSize())) {
            index = m_owner->m_idList->getSize() - 1;
        }
        m_owner->m_idList->setIndex(index);
        caller.setDisp(false);
        int ctrl = GfMenuObjUtil::getCtrlID(acc.m_handle);
        if (ctrl != -1) {
            GfMenuObjUtil::stopCtrl(ctrl);
        }
        acc.setDisp(true);
        acc.setAlpha(1.0f);
        ui::UIObjectAcc list(acc.m_handle, "LAY_list");
        ui::UIObjectAcc base(acc.m_handle, "IMG_base");
        list.setAlpha(1.0f);
        base.setAlpha(1.0f);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 1;
        param.m_time = 0.2f;
        param.m_eventId = 1;
        GfMenuObjUtil::startCtrl(list.m_handle, param, nullptr);
        ctrl = GfMenuObjUtil::startCtrl(base.m_handle, param, nullptr);
        if (ctrl == -1) {
            GfMenuObject::enableInput(acc.m_handle);
        } else {
            GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        }
        m_owner->m_resultHandle = resultHandle;
        m_owner->m_callerHandle = callerHandle;
        m_owner->m_menu = menu;
        GfMenuObject::resetInputSelection(acc.m_handle);
        GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_idList);
        m_owner->refreshItem();
        GfMenuObjOperationInfo::add(handle, 0, 0, 0);
        GfMenuObjUtil::playSECommonSort();
        m_openIndex = m_owner->m_idList->getIndex(false);
        break;
    }
    }
}

void GfMenuObjSort::open(unsigned int handle, unsigned int caller, unsigned short menu, unsigned short index) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x83));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x21;
        event.m_param0 = handle;
        event.m_param1 = caller;
        event.m_paramShort[4] = menu;
        event.m_paramShort[5] = index;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

unsigned short GfMenuObjSort::getSortID(unsigned short menu, unsigned short index) {
    unsigned char* bdat = GfDataBdat::getFP(0x16D);
    unsigned int count = 0;
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < s_sortTypeCount; i++) {
        name.format("sort_type%d", i + 1);
        if (Bdat::getMember(bdat, name.m_str) == nullptr) {
            return 0;
        }
        unsigned short type = Bdat::getVal(bdat, name.m_str, menu);
        if (type == 0) {
            continue;
        }
        bool listed = false;
        int enhance = getEnhanceColumn(type);
        if (enhance != 0) {
            unsigned char* table = GfDataBdat::getFP(0x16E);
            mm::mtl::FixStr<32> column;
            column.format("enhance%d", enhance);
            if (Bdat::getMember(table, column.m_str) != nullptr) {
                for (int j = 0; j < Bdat::getIdCount(table); j++) {
                    unsigned short value = Bdat::getVal(table, column.m_str, Bdat::getIdTop(table) + j);
                    if (value != 0) {
                        if (count == index) {
                            return value + 0x20;
                        }
                        count++;
                    }
                }
            }
        }
        if (type == 0x15) {
            unsigned char* table = GfDataBdat::getFP(0x16F);
            name.format("buff%d", 1);
            if (Bdat::getMember(table, name.m_str) != nullptr) {
                for (int j = 0; j < Bdat::getIdCount(table); j++) {
                    unsigned short value = Bdat::getVal(table, name.m_str, Bdat::getIdTop(table) + j);
                    if (value != 0) {
                        if (count == index) {
                            return value + 0x50;
                        }
                        count++;
                    }
                }
            }
            listed = true;
        }
        if (type == 0x14) {
            unsigned char* table = GfDataBdat::getFP(0x170);
            name.format("role%d", 1);
            if (Bdat::getMember(table, name.m_str) != nullptr) {
                for (int j = 0; j < Bdat::getIdCount(table); j++) {
                    unsigned short value = Bdat::getVal(table, name.m_str, Bdat::getIdTop(table) + j);
                    if (value != 0) {
                        if (count == index) {
                            return value + 0x40;
                        }
                        count++;
                    }
                }
            }
            listed = true;
        }
        if (type == 0x18) {
            unsigned char* table = GfDataBdat::getFP(0x171);
            name.format("fs%d", 1);
            if (Bdat::getMember(table, name.m_str) != nullptr) {
                for (int j = 0; j < Bdat::getIdCount(table); j++) {
                    unsigned short value = Bdat::getVal(table, name.m_str, Bdat::getIdTop(table) + j);
                    if (value != 0) {
                        if (count == index) {
                            return value + 100;
                        }
                        count++;
                    }
                }
            }
            listed = true;
        }
        if (!listed && count++ == index) {
            return type;
        }
    }
    return 0;
}

}  // namespace gf
