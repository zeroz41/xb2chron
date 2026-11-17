#include "classes/gf/GfMenuObjBlEquip.h"
#include "classes/gf/GfMenuObjBlEquip/ItemSelectListener.h"
#include "classes/gf/GfMenuObjBlEquip/MainListener.h"
#include "classes/gf/GfMenuObjBlEquip/SlotListener.h"
#include "classes/gf/GfMenuObjBlEquip.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuItemAdapter.h"
#include "classes/gf/GfMenuReference.h"
#include "gf/GfEquipUtil.h"
#include "mm/mtl/FixStr.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "classes/gf/GfMenuObjCharSelect.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjCmnStatus.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "ui/EventData.h"
#include "classes/gf/GfMenuObjSort.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/ui/UIObjectScrollBarPlugin.h"
#include "gf/GfMenuItemUtil.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/GfItemUtil.h"

namespace gf {

GfMenuObjBlEquip::GfMenuObjBlEquip(unsigned int handle)
    : GfMenuObject(handle), m_items(nullptr), m_cursor(nullptr), m_items2(nullptr), m_selectList(nullptr),
      m_context2(nullptr), m_context(nullptr), pad_60(0) {
    m_context = GfMenuCallContext::create();
}

GfMenuObjBlEquip::~GfMenuObjBlEquip() {
    if (m_cursor != nullptr) {
        m_cursor->release();
        m_cursor = nullptr;
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_items != nullptr) {
        m_items->release();
        m_items = nullptr;
    }
    if (m_items2 != nullptr) {
        m_items2->release();
        m_items2 = nullptr;
    }
    if (m_selectList != nullptr) {
        m_selectList->release();
        m_selectList = nullptr;
    }
    if (m_context2 != nullptr) {
        m_context2->release();
        m_context2 = nullptr;
    }
}

void GfMenuObjBlEquip::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int handle = acc.searchChild("LAY_main");
    {
#line 129
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    GfMenuObject::attachExternalCall(105, handle);
    handle = acc.searchChild("LAY_eqpac_slot");
    {
#line 134
        SlotListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SlotListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    handle = acc.searchChild("LAY_stockac_list");
    {
#line 138
        ItemSelectListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ItemSelectListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    ui::UISelectObjList::CreateParam selectParam;
    selectParam.m_allocator = getAllocator(ALLOCATOR(0));
    m_selectList = ui::UISelectObjList::create(selectParam);
    m_items = GfMenuItemList::create();
    ui::UIListInfoBase::SetupParam itemParam;
    itemParam.m_pageRowSize = 3;
    m_items->setup(getAllocator(ALLOCATOR(0)), itemParam);
    m_items2 = GfMenuItemList::create();
    m_context2 = GfMenuCallContext::create();
    GfMenuObject::disableInput(acc.searchChild("LAY_eqpac_slot"));
    GfMenuObject::disableInput(acc.searchChild("LAY_stockac_list"));
    GfMenuObject::initialize();
}

void GfMenuObjBlEquip::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjBlEquip::update() {
    GfMenuObject::update();
}

void GfMenuObjBlEquip::MainListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(true);
        setFadeIn(handle);
        break;
    case 3:
        if (event.m_param0 == 2) {
            acc.setDisp(false);
            acc.setTerm();
            GfMenuObjCharSelect::returnSubMenu();
            GfMenuObject::returnFSSubLayer(m_owner);
        } else if (event.m_param0 == 1) {
            sendEvent(acc.searchChild("LAY_eqpac_slot"), 0x101, 0);
        }
        break;
    case 0x21:
        acc.setDisp(true);
        break;
    case 0x22:
        setFadeOut(handle);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjBlEquip::SlotListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc owner(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        setupSlot(acc, m_owner->m_items);
        refreshSlot(acc);
        GfMenuObjMainMenu2::setSubIndexText(10);
        GfMenuObjUtil::CursorParam param;
        param.m_parent = ui::UIObjectAcc(handle).getParentHandle();
        param.m_cursor = acc.searchChild("IMG_slot_cursor");
        param.m_setting.m_waitAnim = "loop";
        param.m_type = 0;
        param.m_setting.m_dockType = 0;
        param.m_pickup = "IMG_asc_icon@%02d";
        m_owner->m_cursor = GfMenuObjUtil::createCursor(param);
        m_owner->m_cursor->open(0);
        m_owner->m_cursor->setDisp(false);
        GfMenuObject::setupInputSelection(handle, 0, m_owner->m_items->getSize());
        sendEvent(owner.searchChild("LAY_stockac_list"), 0x102, 0);
        GfMenuReference::setBladeVirtualEquipOrbSlot(0);
        break;
    }
    case 6: {
        int index = event.m_param0;
        if (index >= 0) {
            int prev = event.m_param1;
            m_owner->m_items->setIndex(index);
            unsigned int slot = m_owner->m_items->getIndex(true);
            if (m_owner->m_cursor->inputChange(slot)) {
                mm::mtl::FixStr<32> name;
                if (prev >= 0) {
                    name.format("IMG_slot_select@%02d", prev + 1);
                    ui::UIObjectAcc select(acc.searchChild(name.m_str));
                    select.stopAnimation();
                    select.setDisp(false);
                }
                name.format("IMG_slot_select@%02d", index + 1);
                ui::UIObjectAcc select(acc.searchChild(name.m_str));
                select.setDisp(true);
                select.startAnimation("loop", false);
                GfMenuReference::setBladeVirtualEquipOrbSlot(slot);
                GfMenuItemList* items = m_owner->m_items;
                GfMenuObjOperationInfo::setActionEnable(handle, 9, items->getContents(items->getIndex(false)).m_id != 0);
                refreshItemList(owner, m_owner->m_items2, m_owner->m_selectList, slot);
                if (prev != -1 && index != prev) {
                    GfMenuObjUtil::playSECommonCursor();
                }
            }
        }
        break;
    }
    case 8:
        switch (event.m_param1) {
        case 1: {
            unsigned int max = GfEquipUtil::getEquipOrbMax(GfMenuReference::getReferenceBladeID(0));
            if (m_owner->m_items->getIndex(true) < max && m_owner->m_items2->getSize() != 0) {
                sendEvent(handle, 0x102, 0);
                sendEvent(owner.searchChild("LAY_stockac_list"), 0x101, 0);
                GfMenuObjMainMenu2::closeCharChange();
                GfMenuObjUtil::playSECommonDecide();
            } else {
                GfMenuObjUtil::playSECommon(2);
            }
            break;
        }
        case 2:
            GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
            sendEvent(owner.searchChild("LAY_main"), 0x22, 0);
            GfMenuObject::disableInput(handle);
            GfMenuReference::setBladeVirtualEquipOrbSlot(0);
            GfMenuObjMainMenu2::disableCharChange();
            GfMenuObjUtil::playSECommonCancel();
            break;
        case 9: {
            unsigned int blade = GfMenuReference::getReferenceBladeID(0);
            unsigned int slot = m_owner->m_items->getIndex(true);
            if (GfEquipUtil::getEquipBladeOrb(blade, slot) != 0) {
                m_owner->pad_50 = 4;
                removeItem(owner, m_owner->m_items, m_owner->m_items2, m_owner->m_selectList, blade, slot,
                           m_owner->m_context2);
                GfMenuObjOperationInfo::setActionEnable(handle, 9, false);
                GfMenuObjUtil::playSE(0x11);
            }
            break;
        }
        case 0x12:
            GfMenuObjOperationInfo::changeText(handle, 0x12, !GfMenuObjCmnStatus::swapBlStatus());
            break;
        }
        break;
    case 0x101:
        GfMenuObjOperationInfo::setGuideText(0x1D, 0);
        GfMenuObjOperationInfo::add(handle, 0, 0, 0);
        GfMenuObjOperationInfo::changeText(handle, 0x12, !GfMenuObjCmnStatus::isOpenBlStatus());
        GfMenuObject::enableInput(handle);
        GfMenuReference::setBladeVirtualEquipOrb(0);
        if (GfMenuObjMainMenu2::isOpenCharMenu()) {
            GfMenuObjMainMenu2::openCharChange(acc.m_handle, 2, false);
        }
        break;
    case 0x102:
        GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
        GfMenuObject::disableInput(handle);
        break;
    case 0x140: {
        GfMenuReference::setReferenceBladeID(0, event.m_param0);
        {
            mm::mtl::FixStr<32> name;
            name.format("IMG_slot_select@%02d", m_owner->m_items->getIndex(true) + 1);
            ui::UIObjectAcc select(acc.searchChild(name.m_str));
            select.stopAnimation();
            select.setDisp(false);
        }
        updateEquipItemList(m_owner->m_items);
        unsigned int slot = m_owner->m_items->getIndex(true);
        refreshItemList(owner, m_owner->m_items2, m_owner->m_selectList, slot);
        refreshSlot(acc);
        GfMenuObject::resetInputSelection(handle);
        GfMenuObject::setupInputSelection(handle, 0, m_owner->m_items->getSize());
        GfMenuObjCharSelect::execCharPosScale(1);
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjBlEquip::setupSlot(ui::UIObjectAcc& acc, GfMenuItemList* items) {
    mm::mtl::FixStr<32> name;
    updateEquipItemList(items);
    GfMenuReference::getReferenceBladeID(0);
    GfMenuAdapterManager::beginAddAfter();
    for (int i = 0; i < 3; i++) {
        name.format("IMG_asc_icon@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 10, items, i, false);
    }
    GfMenuItemAdapter::createFromList(acc.searchChild("TXT_eqasc_name"), 0, items, -1, false);
    GfMenuItemAdapter::createFromList(acc.searchChild("TXT_eqpasc_iftxt"), 9, items, -1, false);
    GfMenuItemAdapter::createFromList(acc.searchChild("IMG_eqp_raicon"), 7, items, -1, false);
    GfMenuAdapterManager::endAddAfter();
    for (int i = 0; i < 3; i++) {
        name.format("IMG_slot_select@%02d", i + 1);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, false);
        name.format("IMG_slot_hold@%02d", i + 1);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, false);
    }
}

void GfMenuObjBlEquip::refreshSlot(ui::UIObjectAcc& acc) {
    unsigned int blade = GfMenuReference::getReferenceBladeID(0);
    unsigned int max = GfEquipUtil::getEquipOrbMax(blade);
    ui::UIObjectAcc noSlot(acc.searchChild("TXT_no_slot"));
    mm::mtl::FixStr<32> name;
    if (max == 0) {
        for (int i = 0; i < 3; i++) {
            name.format("LAY_slot@%02d", i + 1);
            ui::UIObjectAcc slot(acc.searchChild(name.m_str));
            slot.setDisp(false);
        }
        noSlot.setDisp(true);
    } else {
        ui::UISelectObjList* select;
        {
            ui::UISelectObjList::CreateParam param;
            param.m_allocator = getAllocator(ALLOCATOR(0));
            select = ui::UISelectObjList::create(param);
        }
        for (unsigned int i = 0; i < 3; i++) {
            name.format("LAY_slot@%02d", i + 1);
            ui::UIObjectAcc slot(acc.searchChild(name.m_str));
            if (i < max) {
                slot.setDisp(true);
                unsigned int handle = slot.m_handle;
                select->addContents(handle);
            } else {
                slot.setDisp(false);
            }
        }
        mm::Rect<short> rect2;
        acc.getLayoutRect("slot_2", rect2);
        mm::Rect<short> rect1;
        acc.getLayoutRect("slot_1", rect1);
        unsigned int width = rect2.x - 1 - rect1.x;
        mm::Pnt<short> center(rect2.x + rect2.w / 2, rect2.y + rect2.h / 2);
        GfMenuObjUtil::placeObjectH(select, center, width);
        if (select != nullptr) {
            select->release();
        }
        noSlot.setDisp(false);
    }
}

void GfMenuObjBlEquip::refreshItemList(ui::UIObjectAcc& acc, GfMenuItemList* items, ui::UISelectObjList* select,
                                       unsigned int slot) {
    unsigned int blade = GfMenuReference::getReferenceBladeID(0);
    for (unsigned int i = 0; i < select->getSize();) {
        MenuItemInfo& item = items->getContents(items->getPageIndex(i));
        mm::mtl::FixStr<32> name;
        unsigned int equipped = GfMenuItemUtil::searchEquipOrb(item.m_id, item.m_entry, nullptr);
        bool isUsed = equipped != 0;
        i++;
        name.format("TXT_list_use@%02d", i);
        ui::UIObjectAcc use(acc.searchChild(name.m_str));
        use.setDisp(isUsed);
        if (equipped != 0) {
            DataParamAcc param(4, equipped, GimmickType(0));
            use.setText(GfMenuObjUtil::getName(param));
            GfMenuObjUtil::setColMulandAdd(use.m_handle, equipped == blade ? "txt_normal" : "txt_disable");
        }
        unsigned int type = item.m_type;
        name.format("LAY_list_use@%02d", i);
        ui::UIObjectAcc(acc.searchChild(name.m_str)).setDisp(type == 3);
        name.format("LAY_list_num@%02d", i);
        ui::UIObjectAcc(acc.searchChild(name.m_str)).setDisp(type != 3);
        name.format("TXT_aslist_name@%02d", i);
        ui::UIObjectAcc text(acc.searchChild(name.m_str));
        switch (GfMenuItemUtil::canEquipOrb(item.m_id, item.m_entry, blade, slot)) {
        case 1:
        case 3:
        case 4:
        case 5:
            GfMenuObjUtil::setColMulandAdd(text.m_handle, "txt_disable");
            break;
        default:
            text.loadDefColor();
            break;
        }
    }
}

void GfMenuObjBlEquip::ItemSelectListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc owner(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        setupItemList(acc, m_owner->m_items2, m_owner->m_selectList);
        ui::UIObjectScrollBarPlugin* plugin = ui::UIObjectScrollBarPlugin::create(
            acc.searchChild("IMG_scroll_point"), 0, m_owner->m_items2, "IMG_scroll_line");
        if (plugin != nullptr) {
            plugin->release();
        }
        sendEvent(handle, 0x102, 0);
        unsigned int slot = m_owner->m_items->getIndex(true);
        refreshItemList(owner, m_owner->m_items2, m_owner->m_selectList, slot);
        unsigned short sortId = GfMenuObjSort::getSortID(0xF, 0);
        GfMenuObjSort::setSortLabelText(sortId, owner.searchChild("TXT_item_sort_label"));
        m_owner->pad_60 = 0;
        sortOrb(m_owner->m_items2, sortId);
        break;
    }
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        unsigned int prevRow = m_owner->m_items2->getIndex(true);
        m_owner->m_items2->setIndex(index);
        unsigned int row = m_owner->m_items2->getIndex(true);
        m_owner->m_selectList->setIndex(row);
        bool hasPrev = prev != -1;
        mm::mtl::FixStr<32> name;
        if (hasPrev) {
            name.format("IMG_listcursor@%02d", prevRow + 1);
            acc.setDispChild(false, name.m_str);
        }
        name.format("IMG_listcursor@%02d", row + 1);
        acc.setDispChild(true, name.m_str);
        unsigned int slot = m_owner->m_items->getIndex(true);
        refreshItemList(acc, m_owner->m_items2, m_owner->m_selectList, slot);
        GfMenuItemList* items = m_owner->m_items2;
        GfMenuReference::setBladeVirtualEquipOrb(items->getContents(items->getIndex(false)).m_id);
        if (index != prev && hasPrev) {
            GfMenuObjUtil::playSECommonCursor();
        }
        break;
    }
    case 8:
        switch (event.m_param1) {
        case 1: {
            unsigned int blade = GfMenuReference::getReferenceBladeID(0);
            GfMenuItemList* items = m_owner->m_items2;
            MenuItemInfo& info = items->getContents(items->getIndex(false));
            if (info.m_count != 0) {
                if (info.m_type == 9) {
                    m_owner->pad_50 = 0;
                    m_owner->m_context2->reset();
                    GfMenuObjCommonText::openError(m_owner->m_context2, 0x19, 0);
                    GfMenuObjUtil::playSECommon(2);
                } else {
                    unsigned int slot = m_owner->m_items->getIndex(true);
                    int result = GfMenuItemUtil::canEquipOrb(info.m_id, info.m_entry, blade, slot);
                    switch (result) {
                    case 0: {
                        m_owner->pad_50 = 3;
                        removeItem(acc, m_owner->m_items, m_owner->m_items2, m_owner->m_selectList, blade, slot,
                                   m_owner->m_context2);
                        GfEquipUtil::equipBladeOrb(blade, info.m_id, m_owner->m_items->getIndex(true), info.m_entry);
                        MenuItemInfo equip;
                        equip.m_type = info.m_type;
                        equip.m_id = info.m_id;
                        equip.m_count = 1;
                        equip.m_sortIndex = info.m_sortIndex;
                        equip.m_entry = info.m_entry;
                        GfMenuItemList* slots = m_owner->m_items;
                        unsigned int at = slots->getIndex(false);
                        if (at < slots->m_list.size()) {
                            slots->m_list[at] = equip;
                        }
                        refreshItemList(acc, m_owner->m_items2, m_owner->m_selectList, slot);
                        sendEvent(handle, 0x102, 0);
                        sendEvent(owner.searchChild("LAY_eqpac_slot"), 0x101, 0);
                        GfMenuObjOperationInfo::setActionEnable(owner.searchChild("LAY_eqpac_slot"), 9, true);
                        GfMenuObjUtil::playSE(0x11);
                        break;
                    }
                    case 5:
                        m_owner->m_context2->reset();
                        GfMenuObjCommonText::open(m_owner->m_context2, 0x124, 0);
                        GfMenuObject::setCallContextEventHandler(m_owner->m_context2, handle);
                        m_owner->pad_50 = 0;
                        break;
                    case 2:
                        m_owner->m_context2->reset();
                        GfMenuObjCommonText::open(m_owner->m_context2, 0xAB, 0);
                        GfMenuObject::setCallContextEventHandler(m_owner->m_context2, handle);
                        m_owner->pad_50 = 5;
                        break;
                    default: {
                        unsigned int error = GfMenuItemUtil::getEquipErrorCmnWindowID(result);
                        if (error != 0) {
                            m_owner->pad_50 = 0;
                            m_owner->m_context2->reset();
                            GfMenuObjCommonText::openError(m_owner->m_context2, error, 0);
                        }
                        break;
                    }
                    }
                    GfMenuObject::setCallContextEventHandler(m_owner->m_context2, acc.m_handle);
                }
            }
            break;
        }
        case 2:
            sendEvent(handle, 0x102, 0);
            sendEvent(owner.searchChild("LAY_eqpac_slot"), 0x101, 0);
            GfMenuObjUtil::playSECommonCancel();
            break;
        case 0x11:
            GfMenuObjSort::open(acc.m_handle, owner.searchChild("TXT_item_sort_label"), 0xF, m_owner->pad_60);
            GfMenuObject::disableInput(handle);
            GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
            break;
        case 0x12:
            GfMenuObjOperationInfo::changeText(handle, 0x12, !GfMenuObjCmnStatus::swapBlStatus());
            break;
        }
        break;
    case 0x41: {
        unsigned int blade = GfMenuReference::getReferenceBladeID(0);
        GfMenuItemList* items = m_owner->m_items2;
        MenuItemInfo& info = items->getContents(items->getIndex(false));
        unsigned int id = event.m_param0;
        if (event.m_param2 == 0 && m_owner->m_context2->m_id == id && m_owner->pad_50 == 5) {
            unsigned int otherSlot = 0;
            unsigned int other = GfMenuItemUtil::searchEquipOrb(info.m_id, info.m_entry, &otherSlot);
            if (other != 0) {
                removeItem(acc, nullptr, m_owner->m_items2, m_owner->m_selectList, other, otherSlot,
                           m_owner->m_context2);
                unsigned int slot = m_owner->m_items->getIndex(true);
                removeItem(acc, m_owner->m_items, m_owner->m_items2, m_owner->m_selectList, blade, slot,
                           m_owner->m_context2);
                GfEquipUtil::equipBladeOrb(blade, info.m_id, slot, info.m_entry);
                MenuItemInfo equip;
                equip.m_type = info.m_type;
                equip.m_id = info.m_id;
                equip.m_count = 1;
                equip.m_sortIndex = info.m_sortIndex;
                equip.m_entry = info.m_entry;
                GfMenuItemList* slots = m_owner->m_items;
                unsigned int at = slots->getIndex(false);
                if (at < slots->m_list.size()) {
                    slots->m_list[at] = equip;
                }
                refreshItemList(acc, m_owner->m_items2, m_owner->m_selectList, slot);
            }
        }
        break;
    }
    case 0x101: {
        GfMenuObjOperationInfo::setGuideText(0x13, 0);
        GfMenuObjOperationInfo::add(handle, 0, 0, 0);
        GfMenuObjOperationInfo::changeText(handle, 0x12, !GfMenuObjCmnStatus::isOpenBlStatus());
        mm::mtl::FixStr<32> name;
        for (unsigned int i = 0; i < m_owner->m_selectList->getSize(); i++) {
            name.format("IMG_listcursor@%02d", i + 1);
            acc.setDispChild(i == m_owner->m_items2->getIndex(true), name.m_str);
        }
        name.format("IMG_slot_hold@%02d", m_owner->m_items->getIndex(true) + 1);
        {
            ui::UIObjectAcc hold(owner.searchChild(name.m_str));
            hold.setDisp(true);
            hold.startAnimation("loop", false);
        }
        GfMenuObject::setupInputSelectionFromList(handle, *m_owner->m_items2);
        GfMenuObject::enableInput(handle);
        break;
    }
    case 0x102: {
        GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
        mm::mtl::FixStr<32> name;
        for (unsigned int i = 0; i < m_owner->m_selectList->getSize(); i++) {
            name.format("IMG_listcursor@%02d", i + 1);
            acc.setDispChild(false, name.m_str);
        }
        name.format("IMG_slot_hold@%02d", m_owner->m_items->getIndex(true) + 1);
        {
            ui::UIObjectAcc hold(owner.searchChild(name.m_str));
            hold.stopAnimation();
            hold.setDisp(false);
        }
        GfMenuObject::disableInput(handle);
        break;
    }
    case 0x148:
        GfMenuObject::enableInput(handle);
        GfMenuObjOperationInfo::add(handle, 0, 0, 0);
        if (GfMenuObjUtil::isValidExpansion(3)) {
            GfMenuObjOperationInfo::changeText(handle, 0x12, !GfMenuObjCmnStatus::isOpenBlStatus());
        }
        if (m_owner->pad_60 != event.m_param0) {
            unsigned short sortId = GfMenuObjSort::getSortID(0xF, event.m_param0);
            sortOrb(m_owner->m_items2, sortId);
            m_owner->pad_60 = event.m_param0;
            unsigned int slot = m_owner->m_items->getIndex(true);
            refreshItemList(acc, m_owner->m_items2, m_owner->m_selectList, slot);
        }
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjBlEquip::setupItemList(ui::UIObjectAcc& acc, GfMenuItemList* items, ui::UISelectObjList* select) {
    select->pickupObject(acc.m_handle, "LAY_stcklist@%02d", 1);
    unsigned int count = select->getSize();
    if (items == nullptr || count == 0) {
        return;
    }
    GfMenuItemList::ItemBoxSetup setup;
    setup.m_type = 3;
    setup.pad_28 = 0;
    setup.m_setup.m_pageRowSize = select->getSize();
    setup.m_setup.m_pageScroll = true;
    items->setupFromBox(setup);
    if (items->getSize() == 0) {
        ui::UIListInfoBase::SetupParam param = setup.m_setup;
        items->setup(getAllocator(ALLOCATOR(0)), param);
    }
    mm::mtl::FixedVector<GfItem, 1024> orbs;
    GfItemUtil::getInfo(orbs, static_cast<ItemType::Type>(9), false);
    for (GfItem* it = orbs.begin(); it != orbs.end(); ++it) {
        MenuItemInfo info;
        info.m_type = 9;
        info.m_id = it->m_item;
        info.m_entry = it->m_handle;
        info.m_count = it->m_count;
        items->addContents(info);
    }
    GfMenuAdapterManager::beginAddAfter();
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < select->getSize(); i++) {
        name.format("IMG_aslist_icon@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 2, items, i, false);
        name.format("TXT_aslist_name@%02d", i + 1);
        GfMenuItemAdapter* adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0, items, i, false);
        if (adapter != nullptr) {
            name.format("LAY_stcklist@%02d", i + 1);
            adapter->m_rowHandle = acc.searchChild(name.m_str);
        }
        name.format("IMG_list_rea@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 7, items, i, false);
        name.format("TXT_list_num@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 3, items, i, false);
        name.format("TXT_list_max@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 4, items, i, false);
    }
    GfMenuAdapterManager::endAddAfter();
    GfMenuItemAdapter::createFromList(acc.searchChild("TXT_stockasc_info"), 9, items, -1, false);
    GfMenuItemAdapter::createFromList(acc.searchChild("TXT_stac_prisenum"), 5, items, -1, false);
    ui::UIObjectAcc icon(acc.searchChild("IMG_stock_icon"));
    icon.setImageIndex(1);
}

// rebuilds the list as its type 3 items, then its type 9 items, each part sorted by the order (setupItemList lists
// the box's type 3 items, then adds the type 9 ones)
void GfMenuObjBlEquip::sortOrb(GfMenuItemList* items, unsigned short order) {
    GfMenuItemList* type3List = GfMenuItemList::create();
    GfMenuItemList* type9List = GfMenuItemList::create();
    ui::UIListInfoBase::SetupParam param;
    type3List->setup(getAllocator(ALLOCATOR(0)), param);
    type9List->setup(getAllocator(ALLOCATOR(0)), param);
    for (unsigned int i = 0; i < items->getSize(); i++) {
        MenuItemInfo& info = items->getContents(i);
        if (info.m_type == 3) {
            type3List->addContents(info);
        }
    }
    type3List->sort(order, false);
    for (unsigned int i = 0; i < items->getSize(); i++) {
        MenuItemInfo& info = items->getContents(i);
        if (info.m_type == 9) {
            type9List->addContents(info);
        }
    }
    type9List->sort(order, false);
    unsigned int count = 0;
    while (count < type3List->getSize()) {
        MenuItemInfo& info = type3List->getContents(count);
        unsigned int index = count++;
        if (index < items->m_list.size()) {
            items->m_list[index] = info;
        }
    }
    for (unsigned int i = 0; i < type9List->getSize(); i++) {
        unsigned int index = count + i;
        MenuItemInfo& info = type9List->getContents(i);
        if (index < items->m_list.size()) {
            items->m_list[index] = info;
        }
    }
    if (type3List != nullptr) {
        type3List->release();
    }
    if (type9List != nullptr) {
        type9List->release();
    }
}

}  // namespace gf
