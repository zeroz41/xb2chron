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
#include "mm/mtl/Delegate.h"
#include "gf/GfMenuItemUtil.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"

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

inline int GfMenuObjHanaCustom::searchIdList(GfMenuIDList* list, unsigned int id) {
    for (unsigned int i = 0; i < static_cast<unsigned int>(list->getSize()); i++) {
        if (list->getContents(i).m_id == id) {
            return i;
        }
    }
    return -1;
}

void GfMenuObjHanaCustom::updatePartsList(ui::UIObjectAcc& acc, GfMenuIDList* list, ui::UISelectObjList* select,
                                          mm::mtl::FixedArray<GfMenuIDList*, 7>& partsLists) {
    // the BDAT 0x17D column of each Hana form (1005-1007) (lbl_7100B627B0; the name is not the original's)
    static const char* const s_columns[] = {"JS_SET", "JK_SET", "JD_SET"};
    int hana = GfMenuReference::getReferenceBladeID(0);
    list->clear();
    if (hana < 1005 || hana > 1007) {
        return;
    }
    partsLists[0]->clear();
    partsLists[1]->clear();
    partsLists[2]->clear();
    partsLists[3]->clear();
    partsLists[4]->clear();
    partsLists[5]->clear();
    partsLists[6]->clear();
    unsigned char* fp = GfDataBdat::getFP(0x17D);
    int top = Bdat::getIdTop(fp);
    int count = Bdat::getIdCount(fp);
    const char* column = s_columns[hana - 1005];
    for (int i = 0; i != count; i++) {
        MenuID id = {};
        id.m_id = static_cast<unsigned short>(Bdat::getVal(fp, column, i + top));
        if (id.m_id == 0) {
            continue;
        }
        switch (id.m_id) {
        case 1:
        case 2:
        case 3:
        case 6:
        case 9:
        case 12:
        case 15:
            partsLists[static_cast<unsigned int>(list->getSize())]->addContents(id);
            list->addContents(id);
            break;
        case 4:
        case 5:
            partsLists[searchIdList(list, 3)]->addContents(id);
            break;
        case 7:
        case 8:
            partsLists[searchIdList(list, 6)]->addContents(id);
            break;
        case 10:
        case 11:
            partsLists[searchIdList(list, 9)]->addContents(id);
            break;
        case 13:
        case 14:
            partsLists[searchIdList(list, 12)]->addContents(id);
            break;
        }
    }
}

void GfMenuObjHanaCustom::refreshPartsList(ui::UIObjectAcc& acc, mm::mtl::FixedArray<GfMenuIDList*, 7>& partsLists) {
    unsigned char* fp = GfDataBdat::getFP(0x17D);
    int top = Bdat::getIdTop(fp);
    int count = Bdat::getIdCount(fp);
    mm::mtl::FixStr<32> name;
    for (int i = 0; i != count; i++) {
        unsigned short base = Bdat::getVal(fp, "BASE_SET", i + top);
        if (base == 0) {
            continue;
        }
        unsigned int size = 0;
        for (unsigned long j = 0; j < 7; j++) {
            if (partsLists[j]->getContents(0).m_id == base) {
                size = partsLists[j]->getSize();
                break;
            }
        }
        name.format("IMG_parts_base@%02d", i + 1);
        ui::UIObjectAcc img(acc.searchChild(name.m_str));
        mm::mtl::FixStr<32> anim;
        const EquipHana* equip = GfDataHana::getEquipParts(GfMenuReference::getReferenceBladeID(0));
        int equipped = 0;
        switch (base) {
        case 1:
        case 2:
        case 15:
            equipped = 1;
            break;
        case 3:
            equipped = (equip->m_nArtsParts[0].m_item != 0) + (equip->m_nArtsParts[1].m_item != 0) +
                       (equip->m_nArtsParts[2].m_item != 0);
            break;
        case 6: {
            const unsigned short* condenser = equip->m_condenserParts;
            equipped = (condenser[0] != 0) + (condenser[1] != 0) + (condenser[2] != 0);
            break;
        }
        case 9:
            equipped = (equip->m_artsParts[0].m_item != 0) + (equip->m_artsParts[1].m_item != 0) +
                       (equip->m_artsParts[2].m_item != 0);
            break;
        case 12: {
            const unsigned short* condenser = equip->m_extendCondenserParts;
            equipped = (condenser[0] != 0) + (condenser[1] != 0) + (condenser[2] != 0);
            break;
        }
        }
        if (equipped != 0) {
            anim.format("icon_%d_set", size);
        } else {
            anim.format("icon_%d", size);
        }
        img.startAnimation(anim.m_str, false);
    }
}

void GfMenuObjHanaCustom::getEquipItem(unsigned int hana, unsigned int slot, MenuItemInfo& item) {
    EquipHana equip;
    GfGameUtilHana::getEquip(equip, hana);
    switch (slot) {
    case 1:
        item.m_type = 0x10;
        item.m_id = equip.m_roleParts;
        break;
    case 2:
        item.m_type = 0x11;
        item.m_id = equip.m_attributeParts;
        break;
    case 3:
    case 4:
    case 5:
        item.m_type = 0x13;
        item.m_id = equip.m_nArtsParts[slot - 3].m_item;
        break;
    case 6:
    case 7:
    case 8:
        item.m_type = 0x14;
        item.m_id = equip.m_condenserParts[slot - 6];
        break;
    case 9:
    case 10:
    case 11:
        item.m_type = 0x12;
        item.m_id = equip.m_artsParts[slot - 9].m_item;
        break;
    case 12:
    case 13:
    case 14:
        item.m_type = 0x14;
        item.m_id = equip.m_extendCondenserParts[slot - 12];
        break;
    default:
        item.m_type = 0;
        item.m_id = 0;
        break;
    }
}

void GfMenuObjHanaCustom::refreshItemInfo(ui::UIObjectAcc& acc, GfMenuItemList* list, unsigned int type,
                                          unsigned int index) {
    mm::mtl::FixStr<32> name;
    switch (type) {
    case 0:
        name.format("LAY_ptinfo01@%02d", index);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, false);
        name.format("LAY_ptinfo02@%02d", index);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, false);
        name.format("LAY_ptinfo03@%02d", index);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, false);
        name.format("LAY_ptinfo04@%02d", index);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, false);
        break;
    case 1:
        name.format("LAY_ptinfo01@%02d", index);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, false);
        name.format("LAY_ptinfo02@%02d", index);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, false);
        name.format("LAY_ptinfo03@%02d", index);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, true);
        name.format("LAY_ptinfo04@%02d", index);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, false);
        break;
    case 2:
    case 3:
    case 4:
    case 5:
        name.format("LAY_ptinfo01@%02d", index);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, true);
        name.format("LAY_ptinfo02@%02d", index);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, true);
        name.format("LAY_ptinfo03@%02d", index);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, false);
        name.format("LAY_ptinfo04@%02d", index);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, false);
        break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        name.format("LAY_ptinfo01@%02d", index);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, false);
        name.format("LAY_ptinfo02@%02d", index);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, true);
        name.format("LAY_ptinfo03@%02d", index);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, false);
        name.format("LAY_ptinfo04@%02d", index);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, false);
        break;
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
        name.format("LAY_ptinfo01@%02d", index);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, false);
        name.format("LAY_ptinfo02@%02d", index);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, false);
        name.format("LAY_ptinfo03@%02d", index);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, false);
        name.format("LAY_ptinfo04@%02d", index);
        GfMenuObjUtil::setChildDisp(acc.m_handle, name.m_str, true);
        break;
    }
}
bool GfMenuObjHanaCustom::isExpandCircuit(unsigned int hana, unsigned int slot, RESULT_HANA& result) {
    switch (slot) {
    case 12:
    case 13:
    case 14:
    case 19:
    case 20:
    case 21: {
        unsigned int circuit = slot > 18 ? slot - 19 : slot - 12;
        result = GfGameUtilHana::isOpenCondenserCircuit(hana, circuit);
        if (result == static_cast<RESULT_HANA>(10)) {
            unsigned int need = GfGameUtilHana::getEtherForOpenCondenserCircuit(hana, circuit);
            if (need <= static_cast<unsigned int>(GfDataHana::getEther())) {
                return true;
            }
            result = static_cast<RESULT_HANA>(3);
        }
        break;
    }
    case 9:
    case 10:
    case 11:
    case 16:
    case 17:
    case 18: {
        unsigned int circuit = slot > 15 ? slot - 16 : slot - 9;
        result = GfGameUtilHana::isOpenArtsCircuit(hana, circuit);
        if (result == static_cast<RESULT_HANA>(10)) {
            unsigned int need = GfGameUtilHana::getEtherForOpenArtsCircuit(hana, circuit);
            if (need <= static_cast<unsigned int>(GfDataHana::getEther())) {
                return true;
            }
            result = static_cast<RESULT_HANA>(3);
        }
        break;
    }
    case 15: {
        unsigned int rank = GfGameUtilHana::getPowerRank(hana);
        if (rank < 20) {
            result = GfGameUtilHana::isExecPowerRankup(hana, rank + 1);
            if (result == 0) {
                return true;
            }
        } else {
            result = static_cast<RESULT_HANA>(6);
        }
        break;
    }
    }
    return false;
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

void GfMenuObjHanaCustom::refreshEquipList(ui::UIObjectAcc& acc, unsigned int hana) {
    for (unsigned int i = 1; i != 15; i++) {
        mm::mtl::FixStr<32> name;
        name.format("IMG_equip_list_icon@%02d", i);
        ui::UIObjectAcc icon(acc.searchChild(name.m_str));
        icon.setDisp(false);
        name.format("TXT_equip_list_cate_name@%02d", i);
        ui::UIObjectAcc category(acc.searchChild(name.m_str));
        category.setDisp(false);
        name.format("TXT_equip_list_name@%02d", i);
        ui::UIObjectAcc text(acc.searchChild(name.m_str));
        text.setDisp(false);
    }
    const EquipHana* equip = GfDataHana::getEquipParts(hana);
    unsigned int row = 0;
    if (refreshEquipListSub(acc, 1, equip->m_roleParts, row)) {
        row++;
    }
    if (refreshEquipListSub(acc, 2, equip->m_attributeParts, row)) {
        row++;
    }
    if (refreshEquipListSub(acc, 3, equip->m_nArtsParts[0].m_item, row)) {
        row++;
    }
    if (refreshEquipListSub(acc, 4, equip->m_nArtsParts[1].m_item, row)) {
        row++;
    }
    if (refreshEquipListSub(acc, 5, equip->m_nArtsParts[2].m_item, row)) {
        row++;
    }
    if (refreshEquipListSub(acc, 6, equip->m_condenserParts[0], row)) {
        row++;
    }
    if (refreshEquipListSub(acc, 7, equip->m_condenserParts[1], row)) {
        row++;
    }
    if (refreshEquipListSub(acc, 8, equip->m_condenserParts[2], row)) {
        row++;
    }
    if (refreshEquipListSub(acc, 9, equip->m_artsParts[0].m_item, row)) {
        row++;
    }
    if (refreshEquipListSub(acc, 10, equip->m_artsParts[1].m_item, row)) {
        row++;
    }
    if (refreshEquipListSub(acc, 11, equip->m_artsParts[2].m_item, row)) {
        row++;
    }
    if (refreshEquipListSub(acc, 12, equip->m_extendCondenserParts[0], row)) {
        row++;
    }
    if (refreshEquipListSub(acc, 13, equip->m_extendCondenserParts[1], row)) {
        row++;
    }
    refreshEquipListSub(acc, 14, equip->m_extendCondenserParts[2], row);
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

void GfMenuObjHanaCustom::refreshItemList(GfMenuItemList* list, ui::UISelectObjList* select, unsigned int partsId) {
    unsigned int hana = GfMenuReference::getReferenceBladeID(0);
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < static_cast<unsigned int>(select->getSize()); i++) {
        const MenuItemInfo& item = list->getContents(list->getPageIndex(i));
        ui::UIObjectAcc obj(select->getObject(i));
        name.format("TXT_sbpartsname@%02d", i + 1);
        ui::UIObjectAcc text(obj.searchChild(name.m_str));
        RESULT_HANA result;
        if (GfMenuHanaAdapter::isEquipParts(hana, partsId, item.m_id, result)) {
            GfMenuObjUtil::setColMulandAdd(text.m_handle, "txt_normal2");
        } else {
            GfMenuObjUtil::setColMulandAdd(text.m_handle, "txt_disable");
        }
        unsigned int blade = GfMenuItemUtil::searchEquipHanaParts(partsId, item.m_id, item.m_entry);
        bool used = blade != 0;
        mm::mtl::FixStr<32> useName;
        useName.format("TXT_sbpartsuse@%02d", i + 1);
        ui::UIObjectAcc use(obj.searchChild(useName.m_str));
        use.setDisp(used);
        if (blade != 0) {
            DataParamAcc param(4, blade, static_cast<GimmickType>(0));
            use.setText(GfMenuObjUtil::getName(param));
            GfMenuObjUtil::setColMulandAdd(use.m_handle, blade == hana ? "txt_normal" : "txt_disable");
        }
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

void GfMenuObjHanaCustom::setupItemInfo(ui::UIObjectAcc& acc, GfMenuItemList* list) {
    mm::mtl::FixStr<32> name;
    name.format("TXT_parts_ennum@%02d", 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0xF, list, -1, false);
    name.format("TXT_sparts_etxt@%02d", 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0x9, list, -1, false);
    name.format("TXT_ptpdf_num@%02d", 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0x12, list, -1, false);
    name.format("TXT_ptedf_num@%02d", 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0x13, list, -1, false);
    name.format("TXT_ptsp_num@%02d", 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0x14, list, -1, false);
    name.format("TXT_ptrl_name@%02d", 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0x16, list, -1, false);
    name.format("TXT_ptsp_id_hpmax@%02d", 1);
    GfMenuItemAdapter* adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0x15, list, -1, false);
    if (adapter != nullptr) {
        adapter->m_subIndex = 0;
    }
    name.format("TXT_ptsp_id_str@%02d", 1);
    adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0x15, list, -1, false);
    if (adapter != nullptr) {
        adapter->m_subIndex = 1;
    }
    name.format("TXT_ptsp_id_ether@%02d", 1);
    adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0x15, list, -1, false);
    if (adapter != nullptr) {
        adapter->m_subIndex = 2;
    }
    name.format("TXT_ptsp_id_dex@%02d", 1);
    adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0x15, list, -1, false);
    if (adapter != nullptr) {
        adapter->m_subIndex = 3;
    }
    name.format("TXT_ptsp_id_agi@%02d", 1);
    adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0x15, list, -1, false);
    if (adapter != nullptr) {
        adapter->m_subIndex = 4;
    }
    name.format("TXT_ptsp_id_luck@%02d", 1);
    adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.m_str), 0x15, list, -1, false);
    if (adapter != nullptr) {
        adapter->m_subIndex = 5;
    }
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
bool GfMenuObjHanaCustom::refreshEquipListSub(ui::UIObjectAcc& acc, unsigned int slot, unsigned int item,
                                              unsigned int index) {
    // each slot's ItemType::Type (lbl_71009C18DC; the name is not the original's)
    static const ItemType::Type s_types[] = {
        static_cast<ItemType::Type>(0x10), static_cast<ItemType::Type>(0x11), static_cast<ItemType::Type>(0x13),
        static_cast<ItemType::Type>(0x13), static_cast<ItemType::Type>(0x13), static_cast<ItemType::Type>(0x14),
        static_cast<ItemType::Type>(0x14), static_cast<ItemType::Type>(0x14), static_cast<ItemType::Type>(0x12),
        static_cast<ItemType::Type>(0x12), static_cast<ItemType::Type>(0x12), static_cast<ItemType::Type>(0x14),
        static_cast<ItemType::Type>(0x14), static_cast<ItemType::Type>(0x14),
    };
    mm::mtl::FixStr<32> name;
    unsigned char* msg = GfDataBdat::getFP(0xF5);
    unsigned char* fp = GfDataBdat::getFP(0x17C);
    name.format("IMG_equip_list_icon@%02d", index + 1);
    ui::UIObjectAcc icon(acc.searchChild(name.m_str));
    if (item != 0) {
        icon.setDisp(true);
        icon.setImageIndex(static_cast<unsigned short>(Bdat::getVal(fp, "icon", slot)));
    }
    name.format("TXT_equip_list_cate_name@%02d", index + 1);
    ui::UIObjectAcc category(acc.searchChild(name.m_str));
    unsigned short categoryName = Bdat::getVal(fp, "name", slot);
    if (item != 0 && categoryName != 0) {
        category.setDisp(true);
        category.setText(ui::UIStr(msg, categoryName));
    }
    name.format("TXT_equip_list_name@%02d", index + 1);
    ui::UIObjectAcc text(acc.searchChild(name.m_str));
    ui::UIStr itemName;
    GfMenuItemUtil::getItemName(s_types[slot - 1], item, itemName);
    if (item != 0 && itemName.isValid()) {
        text.setDisp(true);
        text.setText(itemName);
    }
    return item != 0;
}

}  // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjHanaCustom>(const mm::mtl::Delegate<bool()>*);

namespace gf {

}  // namespace gf
