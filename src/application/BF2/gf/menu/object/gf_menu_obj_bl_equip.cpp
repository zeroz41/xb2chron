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
#include "ui/EventData.h"

namespace gf {

GfMenuObjBlEquip::GfMenuObjBlEquip(unsigned int handle)
    : GfMenuObject(handle), m_items(nullptr), m_object(nullptr), m_items2(nullptr), m_selectList(nullptr),
      m_context2(nullptr), m_context(nullptr), pad_60(0) {
    m_context = GfMenuCallContext::create();
}

GfMenuObjBlEquip::~GfMenuObjBlEquip() {
    if (m_object != nullptr) {
        m_object->release();
        m_object = nullptr;
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

}  // namespace gf
