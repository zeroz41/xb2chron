#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuShopAdapter.h"
#include "classes/gf/GfMenuShopAdapter/IConverter.h"
#include "classes/gf/GfMenuShopAdapter/ReferenceConverter.h"
#include "classes/gf/GfMenuShopAdapter/ReferenceNumberConverter.h"
#include "gf/GfItemUtil.h"
#include "gf/GfMenuItemUtil.h"
#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "gf/GfMenuBdat.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"

namespace gf {

// per type: the update_* update shows and the plugin create makes (text, image index, disp)
static GfMenuShopAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuShopAdapter::update_Name, {2, 0, 0}},
    {&GfMenuShopAdapter::update_CategoryName, {2, 0, 0}},
    {&GfMenuShopAdapter::update_Icon, {1, 0, 0}},
    {&GfMenuShopAdapter::update_CategoryIcon, {1, 0, 0}},
    {&GfMenuShopAdapter::update_Owner, {3, 0, 0}},
};

GfMenuShopAdapter::~GfMenuShopAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuShopAdapter* GfMenuShopAdapter::create(unsigned int handle, unsigned int type, unsigned int shopId,
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
#line 123
    GfMenuShopAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuShopAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_shopId = shopId;
    plugin->release();
    return adapter;
}

bool GfMenuShopAdapter::update_Name(unsigned int shopId) {
    unsigned char* shop = GfDataBdat::getFP(0xED);
    if (shop == nullptr) {
        return false;
    }
    unsigned short name = (unsigned short)Bdat::getVal(shop, "Name", shopId);
    if (name == 0) {
        return false;
    }
    ui::UIStr text(GfDataBdat::getFP(0x1BE), name);
    setText(text);
    return true;
}

bool GfMenuShopAdapter::update_CategoryName(unsigned int shopId) {
    unsigned char* shop = GfDataBdat::getFP(0xED);
    if (shop == nullptr) {
        return false;
    }
    unsigned short icon = (unsigned short)Bdat::getVal(shop, "ShopIcon", shopId);
    if (icon == 0) {
        return false;
    }
    unsigned char* category = GfDataBdat::getFP(0xF3);
    if (category == nullptr) {
        return false;
    }
    int top = Bdat::getIdTop(category);
    int i = 0;
    unsigned short name = 0;
    for (; i < Bdat::getIdCount(category); i++) {
        if ((unsigned short)Bdat::getVal(category, "icon_id", top + i) == icon) {
            name = (unsigned short)Bdat::getVal(category, "name", top + i);
        }
    }
    if (name == 0) {
        return false;
    }
    ui::UIStr text(GfDataBdat::getFP(0x11C), name);
    setText(text);
    return true;
}

bool GfMenuShopAdapter::update_Icon(unsigned int shopId) {
    unsigned char* shop = GfDataBdat::getFP(0xED);
    if (shop == nullptr) {
        return false;
    }
    unsigned short shopType = (unsigned short)Bdat::getVal(shop, "ShopType", shopId);
    if (shopType == 1 || shopType == 2) {
        return false;
    }
    unsigned short icon = (unsigned short)Bdat::getVal(shop, "ShopIcon", shopId);
    if (icon == 0) {
        return false;
    }
    ItemType::Type itemType;
    unsigned int itemId;
    if (!GfMenuItemUtil::convShopIcon(icon, itemType, itemId)) {
        return false;
    }
    unsigned int number;
    if (!GfMenuItemUtil::getIconNumber(itemType, itemId, number, false)) {
        return false;
    }
    setNumber(number);
    return true;
}

bool GfMenuShopAdapter::update_CategoryIcon(unsigned int shopId) {
    unsigned char* shop = GfDataBdat::getFP(0xED);
    if (shop == nullptr) {
        return false;
    }
    unsigned short icon = (unsigned short)Bdat::getVal(shop, "ShopIcon", shopId);
    unsigned short shopType = (unsigned short)Bdat::getVal(shop, "ShopType", shopId);
    // the image index per ShopType (0 shows only the 0x1A4 icon's, 3 nothing; the name is not the original's)
    static const int s_numbers[] = {0, 2, 3, 1};
    if (shopType >= sizeof(s_numbers) / sizeof(s_numbers[0])) {
        return false;
    }
    int number = s_numbers[shopType];
    if (number == 0) {
        if (icon != 0x1A4) {
            return false;
        }
        number = 5;
    } else if (shopType == 3) {
        return false;
    } else if (shopType == 1) {
        unsigned char* quest = GfDataBdat::getFP(0xF0);
        if (quest == nullptr) {
            return false;
        }
        unsigned short tableId = (unsigned short)Bdat::getVal(shop, "TableID", shopId);
        if (tableId == 0) {
            return false;
        }
        if ((unsigned short)Bdat::getVal(quest, "LinkQuestTask", tableId) != 0) {
            number = 4;
        } else {
            unsigned short shopIcon = (unsigned short)Bdat::getVal(shop, "ShopIcon", shopId);
            if (shopIcon == 0x1AA) {
                number = 6;
            } else if (shopIcon == 0x1AB) {
                number = 7;
            } else if (shopIcon == 0x1A4) {
                number = 5;
            }
        }
    }
    setNumber(number);
    return true;
}

bool GfMenuShopAdapter::update_Owner(unsigned int shopId) {
    unsigned char* shop = GfDataBdat::getFP(0xED);
    if (shop == nullptr) {
        return false;
    }
    unsigned char* table = GfDataBdat::getFP(0xEE);
    if (table == nullptr) {
        return false;
    }
    if ((unsigned short)Bdat::getVal(shop, "ShopType", shopId) != 0) {
        return false;
    }
    unsigned short tableId = (unsigned short)Bdat::getVal(shop, "TableID", shopId);
    if (tableId == 0) {
        return false;
    }
    unsigned short item = (unsigned short)Bdat::getVal(table, "PrivilegeItem", tableId);
    if (item == 0) {
        return false;
    }
    return GfItemUtil::getItemBoxCount(item) != 0;
}

GfMenuShopAdapter* GfMenuShopAdapter::createFromCoverter(unsigned int handle, unsigned int type,
                                                         IConverter* converter, bool changed) {
    GfMenuShopAdapter* adapter = create(handle, type, converter->getShopID(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

GfMenuShopAdapter* GfMenuShopAdapter::createFromReference(unsigned int handle, unsigned int type, bool changed) {
    if (handle == 0) {
        return nullptr;
    }
#line 139
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReferenceConverter();
    return createFromCoverter(handle, type, converter, changed);
}

GfMenuShopAdapter* GfMenuShopAdapter::createFromReference(unsigned int handle, unsigned int type,
                                                          mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference,
                                                          bool changed) {
    if (handle == 0) {
        return nullptr;
    }
#line 148
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReferenceNumberConverter(reference);
    return createFromCoverter(handle, type, converter, changed);
}

void GfMenuShopAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        unsigned int shopId = m_converter->getShopID();
        if (m_shopId != shopId) {
            m_shopId = shopId;
            setChange();
        }
    }
    if (m_update.isValid() && (m_flags & 3) != 0) {
        unsigned char* shop;
        if (m_shopId != 0 && (shop = GfDataBdat::getFP(0xED)) != nullptr && GfMenuBdat::isValidBdatID(shop, m_shopId)) {
            setDisp(m_update(m_shopId));
        } else {
            setDisp(false);
        }
        m_flags &= ~1;
    }
}

}  // namespace gf
