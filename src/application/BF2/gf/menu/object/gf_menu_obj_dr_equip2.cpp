#include "classes/gf/GfMenuObjDrEquip2.h"
#include "classes/gf/GfMenuObjDrEquip2/EquipItemListener.h"
#include "classes/gf/GfMenuObjDrEquip2/ItemListListener.h"
#include "classes/gf/GfMenuObjDrEquip2/MainListener.h"
#include "classes/gf/GfMenuObjDrEquip2/SlotListener.h"
#include "classes/gf/GfMenuObjDrEquip2.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuReference.h"
#include "gf/GfEquipUtil.h"
#include "gf/GfItemUtil.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuReferenceItem.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjDrEquip2::GfMenuObjDrEquip2(unsigned int handle)
    : GfMenuObject(handle), m_driver(0), pad_28(false), m_items(nullptr), m_object(nullptr), m_items2(nullptr),
      m_selectList(nullptr), m_object2(nullptr), m_refItem(), m_context2(nullptr), m_drivers(nullptr),
      m_context(nullptr), pad_7C(0), pad_84(0) {
    m_context = GfMenuCallContext::create();
}

GfMenuObjDrEquip2::~GfMenuObjDrEquip2() {
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_items2 != nullptr) {
        m_items2->release();
        m_items2 = nullptr;
    }
    if (m_selectList != nullptr) {
        m_selectList->release();
        m_selectList = nullptr;
    }
    if (m_object2 != nullptr) {
        m_object2->release();
        m_object2 = nullptr;
    }
    m_refItem = nullptr;
    if (m_context2 != nullptr) {
        m_context2->release();
        m_context2 = nullptr;
    }
    if (m_drivers != nullptr) {
        m_drivers->release();
        m_drivers = nullptr;
    }
    if (m_items != nullptr) {
        m_items->release();
        m_items = nullptr;
    }
    if (m_object != nullptr) {
        m_object->release();
        m_object = nullptr;
    }
}

void GfMenuObjDrEquip2::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int handle = acc.searchChild("LAY_main");
    {
#line 154
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    GfMenuObject::attachExternalCall(99, handle);
    handle = acc.searchChild("LAY_equip_slot");
    {
#line 160
        SlotListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SlotListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    handle = acc.searchChild("LAY_item_list");
    {
#line 164
        ItemListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ItemListListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    handle = acc.searchChild("LAY_equip");
    {
#line 168
        EquipItemListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) EquipItemListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    m_driver = 0;
    ui::UISelectObjList::CreateParam selectParam;
    selectParam.m_allocator = getAllocator(ALLOCATOR(0));
    m_selectList = ui::UISelectObjList::create(selectParam);
    m_items2 = GfMenuItemList::create();
    m_items = GfMenuItemList::create();
    ui::UIListInfoBase::SetupParam itemParam;
    itemParam.m_pageRowSize = 3;
    m_items->setup(getAllocator(ALLOCATOR(0)), itemParam);
    m_refItem = GfMenuReferenceItem::create();
    m_drivers = GfMenuDriverList::create();
    GfMenuDriverList::PartySetup setup;
    setup.m_skipUnused = false;
    setup.m_convertDriver = false;
    setup.m_selectFlag = false;
    setup.m_type = 2;
    m_drivers->setupFromParty(setup);
    m_context2 = GfMenuCallContext::create();
    GfMenuObject::disableInput(acc.searchChild("LAY_equip_slot"));
    GfMenuObject::disableInput(acc.searchChild("LAY_item_list"));
    GfMenuObject::initialize();
}

void GfMenuObjDrEquip2::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjDrEquip2::update() {
    GfMenuObject::update();
}

void GfMenuObjDrEquip2::fn_71003F1CD8() {
    bool enable = GfGameManager::isClearGame() &&
                  !GfEquipUtil::fn_71002FC38C(GfMenuReference::getReferenceDriverID(m_driver)) &&
                  GfItemUtil::getItemBoxCount(0x636A) != 0;
    ui::UIObjectAcc acc(m_handle, "LAY_equip_slot");
    GfMenuObjOperationInfo::setActionEnable(acc.m_handle, 10, enable);
}

void GfMenuObjDrEquip2::EquipItemListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc ownerAcc(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    if (event.m_type == 1) {
        setupEquipItem(acc, m_owner->m_items);
    } else {
        ui::UIObjectListener::reciveEvent(event, handle);
    }
}

}  // namespace gf
