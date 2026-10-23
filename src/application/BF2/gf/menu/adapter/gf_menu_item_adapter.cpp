#include "classes/gf/GfMenuItemAdapter.h"
#include "gf/GfItemUtil.h"
#include "gf/GfDataItem.h"
#include "gf/GfDataHana.h"
#include "gf/GfMenuItemUtil.h"
#include "classes/gf/GfMenuItemAdapter/IConverter.h"
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
    {&GfMenuItemAdapter::fn_710034220C, {0, 0, 999}},
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
    {&GfMenuItemAdapter::fn_7100342FA8, {1, 0, 0}},
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

bool GfMenuItemAdapter::update_Count(const MenuItemInfo& item) {
    if (m_item.m_id == 0 || m_item.m_type == 0) {
        setNumber(0);
    } else {
        setNumber(static_cast<short>(item.m_count));
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

}  // namespace gf
