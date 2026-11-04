#include "classes/gf/GfMenuItemAdapter.h"
#include "gf/GfItemUtil.h"
#include "gf/GfDataItem.h"
#include "gf/GfDataHana.h"
#include "gf/GfMenuItemUtil.h"
#include "classes/gf/GfMenuItemAdapter/IConverter.h"
#include "classes/gf/GfMenuItemAdapter/ListConverter.h"
#include "classes/gf/GfMenuItemAdapter/ReferenceItemConverter.h"
#include "classes/gf/GfMenuItemAdapter/PouchReferenceDriverConverter.h"
#include "classes/gf/GfMenuItemAdapter/ReferenceDriverEquipConverter.h"
#include "classes/gf/GfMenuItemAdapter/ReferenceBladeEquipConverter.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/GfPouchUtil.h"
#include "gf/SDataPouch.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfDataDriver.h"
#include "gf/GfEquipUtil.h"
#include "gf/GfMenuBdat.h"
#include "classes/gf/GfDataBdat.h"
#include "ui/uiDateTime.h"
#include "classes/gf/GfBdatItem.h"
#include "classes/gf/GfMenuReference.h"
#include "ui/UIStr.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"

namespace gf {

// Display callback and plugin settings for each adapter type, in create's index order.
static GfMenuItemAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuItemAdapter::update_Name, {2, 0, 0}},
    {&GfMenuItemAdapter::update_Icon, {1, 0, 0}},
    {&GfMenuItemAdapter::update_IconAll, {1, 0, 0}},
    {&GfMenuItemAdapter::update_Count, {0, 0, 999}},
    {&GfMenuItemAdapter::update_CountMax, {0, 0, 999}},
    {&GfMenuItemAdapter::update_Price, {0, 0, 999999999}},
    {&GfMenuItemAdapter::update_SellPrice, {0, 0, 999999999}},
    {&GfMenuItemAdapter::update_RareIcon, {1, 0, 0}},
    {&GfMenuItemAdapter::update_EquipableColor, {8, 0, 0}},
    {&GfMenuItemAdapter::update_Caption, {2, 0, 0}},
    {&GfMenuItemAdapter::update_CategoryIcon, {1, 0, 0}},
    {&GfMenuItemAdapter::update_GetAreaText, {2, 0, 0}},
    {&GfMenuItemAdapter::update_SubCategoryText, {2, 0, 0}},
    {&GfMenuItemAdapter::update_EffectTime, {7, 3, 0}},
    {&GfMenuItemAdapter::update_EffectText, {2, 0, 0}},
    {&GfMenuItemAdapter::update_useEnergy, {0, 0, 9999}},
    {&GfMenuItemAdapter::update_needEther, {0, 0, 999999999}},
    {&GfMenuItemAdapter::update_dustEther, {0, 0, 999999999}},
    {&GfMenuItemAdapter::update_PArmor, {0, 0, 100}},
    {&GfMenuItemAdapter::update_EArmor, {0, 0, 100}},
    {&GfMenuItemAdapter::update_revise, {0, 0, 100}},
    {&GfMenuItemAdapter::update_dispRevise, {3, 0, 0}},
    {&GfMenuItemAdapter::update_roleText, {2, 0, 0}},
    {&GfMenuItemAdapter::update_canStack, {3, 0, 0}},
    {&GfMenuItemAdapter::update_IconElem, {1, 0, 0}},
};

GfMenuItemAdapter::~GfMenuItemAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuItemAdapter* GfMenuItemAdapter::create(unsigned int handle, unsigned int type, const MenuItemInfo& item,
                                             bool changed) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object == nullptr) {
        return nullptr;
    }
    const TypeSetup& setup = s_typeSetups[type];
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup.plugin);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 657
    GfMenuItemAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuItemAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_item = item;
    plugin->release();
    return adapter;
}

bool GfMenuItemAdapter::update_Name(const MenuItemInfo& item) {
    if (m_item.m_id == 0 || m_item.m_type == 0) {
        return false;
    }
    ui::UIStr name;
    GfMenuItemUtil::getItemName(item.m_type, item.m_id, name);
    if (name.isValid()) {
        setText(name);
        return true;
    }
    return false;
}

bool GfMenuItemAdapter::update_Count(const MenuItemInfo& item) {
    if (m_item.m_id == 0 || m_item.m_type == 0) {
        setNumber(0);
    } else {
        setNumber(static_cast<short>(item.m_count));
    }
    return true;
}

bool GfMenuItemAdapter::update_CountMax(const MenuItemInfo& item) {
    if (m_item.m_id == 0 || m_item.m_type == 0) {
        setNumber(0);
    } else {
        setNumber(GfItemUtil::getEnableStock(item.m_id));
        if (GfMenuObjUtil::isValidExpansion(3) && item.m_id == 0x62D9) {
            setNumber(3);
        }
    }
    return true;
}

bool GfMenuItemAdapter::update_Price(const MenuItemInfo& item) {
    if (m_item.m_id == 0 || m_item.m_type == 0) {
        setNumber(0);
    } else {
        ItemPrice price;
        GfItemUtil::getPrice(price, item.m_id, GfMenuReference::getReferenceShopID());
        setNumber(price.m_price);
    }
    return true;
}

bool GfMenuItemAdapter::update_SellPrice(const MenuItemInfo& item) {
    if (m_item.m_id == 0 || m_item.m_type == 0) {
        setNumber(0);
        return false;
    }
    switch (item.m_type) {
    case 6:
    case 14:
    case 15:
        return false;
    }
    ItemPrice price;
    GfItemUtil::getPrice(price, item.m_id, GfMenuReference::getReferenceShopID());
    setNumber(price.m_sellPrice);
    return true;
}

bool GfMenuItemAdapter::update_RareIcon(const MenuItemInfo& item) {
    if (m_item.m_id == 0 || m_item.m_type == 0) {
        return false;
    }
    switch (item.m_type) {
    case 6:
    case 14:
    case 15:
        return false;
    }
    setNumber(GfDataItem::getRarity(item.m_id));
    return true;
}

bool GfMenuItemAdapter::update_EquipableColor(const MenuItemInfo& item) {
    if (m_item.m_id == 0 || m_item.m_type == 0) {
        return false;
    }
    switch (m_item.m_type) {
    case 2:
        if (GfMenuItemUtil::canEquipAcc(item.m_id, 0, 0) != 0) {
            setMulColor("unuse");
        } else {
            setMulColor("white");
        }
        break;
    case 3:
        setMulColor("white");
        break;
    }
    return true;
}

bool GfMenuItemAdapter::update_CategoryIcon(const MenuItemInfo& item) {
    if (m_item.m_id != 0 && m_item.m_type != 0 && item.m_type == 3 && item.m_id != 0) {
        setNumber(1);
        return true;
    }
    return false;
}

bool GfMenuItemAdapter::update_SubCategoryText(const MenuItemInfo& item) {
    if (m_item.m_id != 0 && m_item.m_type != 0 && item.m_type == 10) {
        ItemProperty property;
        GfItemUtil::getProperty(property, item.m_id, 0);
        if (property.m_favoriteKey >= 12) {
            unsigned int row = property.m_favoriteKey - 11;
            ui::UIStr text(GfDataBdat::getFP(0x12F), row);
            setText(text);
            return true;
        }
    }
    return false;

}

bool GfMenuItemAdapter::update_EffectTime(const MenuItemInfo& item) {
    if (m_item.m_id == 0 || m_item.m_type == 0 || item.m_type != 10) {
        return false;
    }
    ItemProperty property;
    GfItemUtil::getProperty(property, item.m_id, 0);
    ui::uiDateTime time = {};
    time.hour = property.m_favoriteTime / 60;
    time.minute = property.m_favoriteTime % 60;
    setTime(time);
    return true;
}

bool GfMenuItemAdapter::update_useEnergy(const MenuItemInfo& item) {
    if (m_item.m_id != 0 && m_item.m_type != 0 && item.m_type - 16 <= 4) {
        setNumber(GfDataHana::getPartsPower(item.m_id));
        return true;
    }
    return false;
}

bool GfMenuItemAdapter::update_needEther(const MenuItemInfo& item) {
    if (m_item.m_id != 0 && m_item.m_type != 0 && item.m_type - 16 <= 4) {
        ItemProperty property;
        GfItemUtil::getProperty(property, item.m_id, 0);
        setNumber(property.m_needEther);
        return true;
    }
    return false;
}

bool GfMenuItemAdapter::update_dustEther(const MenuItemInfo& item) {
    if (m_item.m_id != 0 && m_item.m_type != 0 && item.m_type - 16 <= 4) {
        ItemProperty property;
        GfItemUtil::getProperty(property, item.m_id, 0);
        setNumber(property.m_dustEther);
        return true;
    }
    return false;
}

bool GfMenuItemAdapter::update_PArmor(const MenuItemInfo& item) {
    if (m_item.m_id == 0 || m_item.m_type == 0 || item.m_type != 16) {
        return false;
    }
    ItemProperty property;
    GfItemUtil::getProperty(property, item.m_id, 0);
    setNumber(property.m_pArmor);
    return true;
}

bool GfMenuItemAdapter::update_EArmor(const MenuItemInfo& item) {
    if (m_item.m_id == 0 || m_item.m_type == 0 || item.m_type != 16) {
        return false;
    }
    ItemProperty property;
    GfItemUtil::getProperty(property, item.m_id, 0);
    setNumber(property.m_eArmor);
    return true;
}



bool GfMenuItemAdapter::update_roleText(const MenuItemInfo& item) {
    if (m_item.m_id == 0 || m_item.m_type == 0 || item.m_type != 16) {
        return false;
    }
    ItemProperty property;
    GfItemUtil::getProperty(property, item.m_id, 0);
    unsigned char role = property.m_role;
    if (role == 0) {
        return false;
    }
    ui::UIStr text(GfDataBdat::getFP(0x115), role);
    setText(text);
    return true;
}

bool GfMenuItemAdapter::update_canStack(const MenuItemInfo& item) {
    return GfMenuItemUtil::canCountStack(item.m_type);
}

bool GfMenuItemAdapter::update_IconElem(const MenuItemInfo& item) {
    if (GfMenuObjUtil::isValidExpansion(3) && item.m_type == 2) {
        unsigned short icon = GfBdatItem::get()->getPcEquipAddAtr(item.m_id) + 0x9E;
        setNumber(GfMenuBdat::getIconImageIndex(icon));
        return true;
    }
    return false;
}

GfMenuItemAdapter* GfMenuItemAdapter::createFromCoverter(unsigned int handle, unsigned int type, IConverter* converter,
                                                         bool changed) {
    if (handle == 0) {
        return nullptr;
    }
    MenuItemInfo item;
    converter->getItemInfo(item);
    GfMenuItemAdapter* adapter = create(handle, type, item, changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

GfMenuItemAdapter* GfMenuItemAdapter::createFromList(unsigned int handle, unsigned int kind, GfMenuItemList* list,
                                                     int index, bool changed) {
    if (handle == 0) {
        return nullptr;
    }
#line 692
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListConverter(list, index);
    return createFromCoverter(handle, kind, converter, changed);
}

GfMenuItemAdapter* GfMenuItemAdapter::createFromReference(unsigned int handle, unsigned int type,
                                                          mm::mtl::IntrusivePtr<IGfMenuReferenceItem> reference,
                                                          bool changed) {
    if (handle == 0) {
        return nullptr;
    }
#line 703
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReferenceItemConverter(reference);
    return createFromCoverter(handle, type, converter, changed);
}

GfMenuItemAdapter* GfMenuItemAdapter::createFromPouchReferenceDriver(unsigned int handle, unsigned int type,
                                                                     unsigned int pouch, unsigned int reference,
                                                                     bool changed) {
    if (handle == 0) {
        return nullptr;
    }
#line 747
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) PouchReferenceDriverConverter(pouch, reference);
    return createFromCoverter(handle, type, converter, changed);
}

GfMenuItemAdapter* GfMenuItemAdapter::createFromReferenceDriverEquip(unsigned int handle, unsigned int type,
                                                                     unsigned int reference, unsigned int slot,
                                                                     bool changed) {
    if (handle == 0) {
        return nullptr;
    }
#line 803
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReferenceDriverEquipConverter(reference, slot);
    return createFromCoverter(handle, type, converter, changed);
}

GfMenuItemAdapter* GfMenuItemAdapter::createFromReferenceBladeEquip(unsigned int handle, unsigned int type,
                                                                    unsigned int reference, unsigned int slot,
                                                                    bool changed) {
    if (handle == 0) {
        return nullptr;
    }
#line 825
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReferenceBladeEquipConverter(reference, slot);
    return createFromCoverter(handle, type, converter, changed);
}

void GfMenuItemAdapter::changeItem(const MenuItemInfo& item) {
    if (m_item.m_type != item.m_type || m_item.m_id != item.m_id || m_item.m_count != item.m_count) {
        m_item = item;
        setChange();
    }
}

void GfMenuItemAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        MenuItemInfo item;
        m_converter->getItemInfo(item);
        changeItem(item);
    }
    if (m_update.isValid() && (m_flags & 3) != 0) {
        setDisp(m_update(m_item));
        m_flags &= ~1;
    }
}

GfMenuItemAdapter::ListConverter::~ListConverter() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

void GfMenuItemAdapter::ListConverter::getItemInfo(MenuItemInfo& item) {
    GfMenuItemList* list;
    unsigned int index;
    if (m_index == -1) {
        list = m_list;
        index = list->getIndex(false);
    } else {
        if (m_index >= m_list->getSize()) {
            item.m_type = 0;
            item.m_id = 0;
            return;
        }
        list = m_list;
        index = list->getPageIndex(m_index);
    }
    item = list->getContents(index);
}

GfMenuItemAdapter::ListConverter* GfMenuItemAdapter::ListConverter::fromList() {
    return this;
}

GfMenuItemAdapter::PouchConverter* GfMenuItemAdapter::IConverter::fromPouch() {
    return nullptr;
}

GfMenuItemAdapter::MissionConverter* GfMenuItemAdapter::IConverter::fromMission() {
    return nullptr;
}

GfMenuItemAdapter::ListConverter* GfMenuItemAdapter::IConverter::fromList() {
    return nullptr;
}

GfMenuItemAdapter::ReferenceItemConverter::~ReferenceItemConverter() {
    m_reference = nullptr;
}

void GfMenuItemAdapter::ReferenceItemConverter::getItemInfo(MenuItemInfo& item) {
    m_reference->getItem(item);
}

GfMenuItemAdapter::PouchReferenceDriverConverter::~PouchReferenceDriverConverter() {}

void GfMenuItemAdapter::PouchReferenceDriverConverter::getItemInfo(MenuItemInfo& item) {
    unsigned int slot = m_pouch;
    const SDataPouch& pouch = GfPouchUtil::getPouch(GfMenuReference::getReferenceDriverID(m_reference), slot);
    item.m_type = 10;
    item.m_id = pouch.itemId;
    item.m_count = 1;
}

GfMenuItemAdapter::IConverter::~IConverter() {}

GfMenuItemAdapter::ReferenceDriverEquipConverter::~ReferenceDriverEquipConverter() {}

void GfMenuItemAdapter::ReferenceDriverEquipConverter::getItemInfo(MenuItemInfo& item) {
    DataParamAcc acc(3, GfMenuReference::getReferenceDriverID(m_reference), GimmickType(0));
    if (!acc.isValid()) {
        return;
    }
    item.m_type = 2;
    if (m_slot <= 2) {
        if (GfMenuObjUtil::isValidExpansion(3)) {
            if (GfDataDriver::isIraFront(acc.isValid() && acc.getObjType() == 3 ? acc.getBdatId() : 0)) {
                if (m_slot == 0) {
                    item.m_id = GfEquipUtil::getEquipIraWpnAcce(acc.isValid() && acc.getObjType() == 3 ? acc.getBdatId() : 0);
                } else {
                    item.m_id = acc.getEquipAcce(m_slot - 1, false);
                }
            }
        } else {
            item.m_id = acc.getEquipAcce(m_slot, false);
        }
    }
    item.m_count = 1;
}

GfMenuItemAdapter::ReferenceBladeEquipConverter::~ReferenceBladeEquipConverter() {}

void GfMenuItemAdapter::ReferenceBladeEquipConverter::getItemInfo(MenuItemInfo& item) {
    unsigned int blade = GfMenuReference::getReferenceBladeID(m_reference);
    DataParamAcc acc(4, blade, GimmickType(0));
    if (!acc.isValid()) {
        return;
    }
    if (m_slot <= 2) {
        item.m_id = GfEquipUtil::getEquipBladeOrb(blade, m_slot);
        item.m_type = 3;
    }
    item.m_count = 1;
}

}  // namespace gf
