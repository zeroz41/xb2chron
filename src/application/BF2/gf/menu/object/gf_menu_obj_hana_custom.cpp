#include "classes/gf/GfMenuObjHanaCustom.h"
#include "classes/gf/GfMenuObjHanaCustom/MainListener.h"
#include "classes/gf/GfMenuObjHanaCustom/PartsListListener.h"
#include "classes/gf/GfMenuObjHanaCustom/ItemListListener.h"
#include "classes/gf/GfMenuObjHanaCustom/PlanListener.h"
#include "classes/gf/GfMenuObjHanaCustom/EquipListListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuReferenceItem.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "ui/EventData.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjCharSelect.h"
#include "gf/GfDataHana.h"
#include "classes/gf/GfMenuItemAdapter.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/GfMenuReference.h"

namespace gf {

GfMenuObjHanaCustom::GfMenuObjHanaCustom(unsigned int handle)
    : GfMenuObject(handle), m_planList(nullptr), m_equipList(nullptr), m_select(nullptr), m_unsetRef0(nullptr),
      m_partsTop(0), pad_84(0), m_itemList(nullptr), m_itemSelect(nullptr), m_unsetRef1(nullptr), m_context(nullptr), m_seq(this),
      m_refItem(nullptr), m_partsMode(0), pad_34C(0), m_step(0), m_refNumber() {
    m_partsLists.assign(nullptr);
}

GfMenuObjHanaCustom::~GfMenuObjHanaCustom() {
    if (m_planList != nullptr) {
        m_planList->release();
        m_planList = nullptr;
    }
    if (m_equipList != nullptr) {
        m_equipList->release();
        m_equipList = nullptr;
    }
    if (m_select != nullptr) {
        m_select->release();
        m_select = nullptr;
    }
    if (m_unsetRef0 != nullptr) {
        m_unsetRef0->release();
        m_unsetRef0 = nullptr;
    }
    if (m_itemList != nullptr) {
        m_itemList->release();
        m_itemList = nullptr;
    }
    if (m_itemSelect != nullptr) {
        m_itemSelect->release();
        m_itemSelect = nullptr;
    }
    if (m_unsetRef1 != nullptr) {
        m_unsetRef1->release();
        m_unsetRef1 = nullptr;
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    m_refItem = nullptr;
    m_refNumber = nullptr;
    for (int i = 0; i < 7; i++) {
        if (m_partsLists[i] != nullptr) {
            m_partsLists[i]->release();
            m_partsLists[i] = nullptr;
        }
    }
}

void GfMenuObjHanaCustom::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int handle = acc.searchChild("LAY_main");
    {
#line 175
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    GfMenuObject::attachExternalCall(0x72, handle);
    handle = acc.searchChild("LAY_parts_window");
    {
#line 181
        PartsListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) PartsListListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    handle = acc.searchChild("LAY_sub_window");
    {
#line 185
        ItemListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ItemListListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    handle = acc.searchChild("LAY_hana_main");
    {
#line 189
        PlanListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) PlanListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    handle = acc.searchChild("LAY_equip_list");
    {
#line 193
        EquipListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) EquipListListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    m_itemList = GfMenuItemList::create();
    ui::UISelectObjList::CreateParam create;
    create.m_allocator = getAllocator(ALLOCATOR(0));
    m_itemSelect = ui::UISelectObjList::create(create);
    m_planList = GfMenuIDList::create();
    ui::UIListInfoBase::SetupParam setup;
    setup.m_pageRowSize = 12;
    setup.m_pageScroll = true;
    m_planList->setup(getAllocator(ALLOCATOR(0)), setup);
    m_equipList = GfMenuIDList::create();
    m_equipList->setup(getAllocator(ALLOCATOR(0)), setup);
    create.m_allocator = getAllocator(ALLOCATOR(0));
    m_select = ui::UISelectObjList::create(create);
    m_context = GfMenuCallContext::create();
#line 57 "D:/Monolithsoft/BF2/prog/application/BF2/gf/menu/object/../adapter/../gf_menu_reference_item.h"
    m_refItem = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuReferenceItem;
    m_refItem->m_item = MenuItemInfo();
    for (int i = 0; i < 7; i++) {
        m_partsLists[i] = GfMenuIDList::create();
        ui::UIListInfoBase::SetupParam partsSetup;
        partsSetup.m_pageRowSize = 3;
        partsSetup.m_pageScroll = true;
        m_partsLists[i]->setup(getAllocator(ALLOCATOR(0)), partsSetup);
    }
    m_refNumber = GfMenuReferenceNumber::create();
    m_refNumber->m_value = 0;
    GfMenuObject::disableInput(acc.searchChild("LAY_parts_window"));
    GfMenuObject::disableInput(acc.searchChild("LAY_sub_window"));
    GfMenuObject::initialize();
}

void GfMenuObjHanaCustom::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjHanaCustom::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjHanaCustom::MainListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        setupMain(acc);
        GfMenuObjOperationInfo::setGuideText(0x18, 0);
        GfMenuObjMainMenu2::setSubIndexText(0x19);
        GfMenuObjMainMenu2::closeCharChange();
        setFadeIn(handle, 0);
        break;
    case 3:
        if (event.m_param0 == 2) {
            acc.setDisp(false);
            acc.setTerm();
            GfMenuObjCharSelect::returnSubMenu();
            GfMenuObject::returnFSSubLayer(m_owner);
        }
        break;
    case 0x21:
        acc.setDisp(true);
        break;
    case 0x22:
        setFadeOut(handle, 0);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjHanaCustom::removeParts(unsigned int hana, unsigned int slot) {
    switch (slot) {
    case 3:
    case 4:
    case 5:
        GfGameUtilHana::execEquipNArtsParts(hana, 0, GfItemHandle(), slot - 3);
        break;
    case 6:
    case 7:
    case 8:
        GfGameUtilHana::execEquipCondenserParts(hana, 0, GfItemHandle(), slot - 6);
        break;
    case 9:
    case 10:
    case 11:
        GfGameUtilHana::execEquipArtsParts(hana, 0, GfItemHandle(), slot - 9);
        break;
    case 12:
    case 13:
    case 14:
        GfGameUtilHana::execEquipExtendCondenserParts(hana, 0, GfItemHandle(), slot - 12);
        break;
    }
}

void GfMenuObjHanaCustom::equipParts(unsigned int hana, unsigned int slot, unsigned int item, GfItemHandle handle) {
    switch (slot) {
    case 1:
        GfGameUtilHana::execEquipRoleParts(hana, item, handle);
        break;
    case 2:
        GfGameUtilHana::execEquipAttributeParts(hana, item, handle);
        break;
    case 3:
    case 4:
    case 5:
        GfGameUtilHana::execEquipNArtsParts(hana, item, handle, slot - 3);
        break;
    case 6:
    case 7:
    case 8:
        GfGameUtilHana::execEquipCondenserParts(hana, item, handle, slot - 6);
        break;
    case 9:
    case 10:
    case 11:
        GfGameUtilHana::execEquipArtsParts(hana, item, handle, slot - 9);
        break;
    case 12:
    case 13:
    case 14:
        GfGameUtilHana::execEquipExtendCondenserParts(hana, item, handle, slot - 12);
        break;
    }
}

bool GfMenuObjHanaCustom::seqLineAnime() {
    ui::UIObjectAcc acc(m_handle);
    ui::UIObjectAcc main(acc.searchChild("LAY_main"));
    unsigned int line = m_planList->getContents(m_planList->getIndex(false)).m_id + m_partsTop;
    mm::mtl::FixStr<32> name;
    name.format("IMG_hnptline@%02d", line > 15 ? line - 7 : line);
    ui::UIObjectAcc img(main.searchChild(name.m_str));
    bool done = false;
    if (m_lineStep == 0) {
        img.startAnimation("act_start", false);
        m_lineStep = 1;
    } else if (!img.isPlayingAnimation()) {
        sendEvent(main.searchChild("LAY_parts_window"), 0x101, 0);
        m_lineStep = 0;
        done = true;
    }
    return done;
}

void GfMenuObjHanaCustom::setupItemList(ui::UIObjectAcc& acc, GfMenuItemList* list, ui::UISelectObjList* select) {
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < static_cast<unsigned int>(select->getSize()); i++) {
        name.format("TXT_sbpartsname@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0, list, i, false);
        name.format("IMG_sbpartsicon@%02d", i + 1);
        GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 2, list, i, false);
    }
}

void GfMenuObjHanaCustom::PlanListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc ownerAcc(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        unsigned int hana = GfMenuReference::getReferenceBladeID(0);
        setupPlan(acc, m_owner->m_planList);
        setupItemInfo(ownerAcc, m_owner->m_itemList);
        setupItemInfo2(ownerAcc, m_owner->m_refNumber, hana);
        break;
    }
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjHanaCustom::setupPlan(ui::UIObjectAcc& acc, GfMenuIDList* list) {
    GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_hn_enu_num"), 1, 0, true);
    GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_hn_enu_max"), 2, 0, true);
    GfMenuHanaAdapter* gauge = GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("IMG_hn_gauge"), 1, 0, true);
    if (gauge != nullptr) {
        gauge->setNumberInterpolateMode(0.2f);
    }
    ui::UIObjectAcc gaugeAcc(acc.searchChild("IMG_hn_gauge"));
    gaugeAcc.setExtType(4);
    GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_hn_ench_num"), 8, 0, true);
    GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_hn_ench_max"), 9, 0, false);
    GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_hn_rol"), 3, 0, true);
    GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("IMG_hn_elml"), 5, 0, true);
    GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("IMG_hana"), 6, 0, false);
}

void GfMenuObjHanaCustom::EquipListListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc ownerAcc(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        break;
    case 0x21:
        refreshEquipList(acc, GfMenuReference::getReferenceBladeID(0));
        setFadeIn(handle, 2);
        break;
    case 0x22:
        setFadeOut(handle, 2);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

}  // namespace gf
