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

void GfMenuObjSort::refreshItem(unsigned int, unsigned int) {
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
