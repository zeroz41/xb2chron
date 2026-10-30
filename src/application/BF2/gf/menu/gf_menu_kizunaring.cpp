#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuKizunaring.h"
#include "classes/gf/GfBdatItem.h"
#include "classes/gf/GfItemBox.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataItem.h"
#include "gf/GfDataUtil.h"
#include "gf/GfEquipUtil.h"
#include "gf/GfItemUtil.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuItemUtil.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfPartySelect.h"
#include "gf/GfRecipeOrbUtil.h"
#include "mm/mtl/FixedVector.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"

namespace gf {

void GfMenuItemUtil::getItemName(unsigned char type, unsigned int id, ui::UIStr& name) {
    unsigned char* data = GfMenuBdat::getItemDataFP(type, id);
    unsigned char* text = GfMenuBdat::getItemTextFP(type, id);
    if (data == nullptr || text == nullptr) {
        return;
    }
    if (Bdat::getMember(data, "Name") == nullptr || !GfMenuBdat::isValidBdatID(data, id)) {
        return;
    }
    unsigned short nameId = Bdat::getVal(data, "Name", id);
    if (nameId != 0 && GfMenuBdat::isValidBdatID(text, nameId)) {
        name.copy(ui::UIStr(text, nameId));
    }
}

int GfMenuItemUtil::getItemNum(unsigned char type, unsigned int id) {
    return GfItemUtil::getItemBoxCount(id);
}

bool GfMenuItemUtil::canCountStack(unsigned int id) {
    switch (id) {
    case 2:
    case 3:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
        return false;
    default:
        return true;
    }
}

bool GfMenuItemUtil::canBuyItem(unsigned int item, unsigned int shop) {
    ItemPrice price;
    GfItemUtil::getPrice(price, item, shop);
    if (GfDataUtil::getMoney() < price.m_price) {
        return false;
    }
    if (GfDataItem::getItemType(item) == 2) {
        unsigned int count = GfItemBox::sys()->fn_71002F9DD4(static_cast<ItemType::Type>(2));
        if (count >= GfItemUtil::getEnableStock(item)) {
            return false;
        }
    } else if (GfItemUtil::getEnableStock(item) == GfItemUtil::getItemBoxCount(item)) {
        return false;
    }
    return true;
}

bool GfMenuItemUtil::canSellItem(unsigned int item, unsigned int) {
    if (GfDataUtil::getMoney() >= 999999999) {
        return false;
    }
    return GfDataItem::isEnableSell(item);
}

bool GfMenuItemUtil::canSellItemType(unsigned int type) {
    switch (type) {
    case 1:
    case 2:
    case 3:
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
        return true;
    default:
        return false;
    }
}

int GfMenuItemUtil::canEquipAcc(unsigned int item, unsigned int driver, unsigned int slot) {
    if (driver == 0) {
        return 0;
    }
    if (GfEquipUtil::getEquipDriverAcce(driver, slot) == item) {
        return 1;
    }
    switch (GfEquipUtil::getEquipAcceResult(driver, slot, item)) {
    case 0:
        return 0;
    case 5:
        return 3;
    case 6:
        return 2;
    default:
        return 4;
    }
}

unsigned short GfMenuItemUtil::searchEquipAcc(unsigned int item, GfItemHandle handle, unsigned int* slot) {
    ::mm::mtl::FixedVector<unsigned short, 32> drivers;
    GfPartySelect::getDriverList(drivers, static_cast<GfPartySelect::LIST_TYPE>(6), 0);
    for (unsigned int i = 0; i < drivers.size(); i++) {
        unsigned short driver = *(drivers.begin() + i);
        if (driver == 0) {
            continue;
        }
        unsigned int slotCount = GfEquipUtil::fn_71002FC38C(driver) ? 3 : 2;
        for (unsigned int j = 0; j < slotCount; j++) {
            unsigned int acce = GfEquipUtil::getEquipDriverAcce(driver, j);
            if (acce != 0 && acce == item &&
                GfDataDriver::getEquipAcceHandle(driver, j).m_handle == handle.m_handle) {
                if (slot != nullptr) {
                    *slot = j;
                    if (GfMenuObjUtil::fn_710048FD30(3)) {
                        (*slot)++;
                    }
                }
                return driver;
            }
        }
    }
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        for (unsigned int i = 0; i < drivers.size(); i++) {
            unsigned short driver = *(drivers.begin() + i);
            if (driver == 0) {
                continue;
            }
            unsigned int acce = GfDataDriver::fn_7100247474(driver);
            if (acce != 0 && acce == item && GfDataDriver::fn_71002474B0(driver).m_handle == handle.m_handle) {
                if (slot != nullptr) {
                    *slot = 0;
                }
                return driver;
            }
        }
    }
    return 0;
}

bool GfMenuItemUtil::fn_71003547CC(unsigned int item, unsigned int blade) {
    bool result = false;
    unsigned int value;
    switch (GfDataItem::getItemType(item)) {
    case 3:
        value = GfBdatItem::sys()->fn_7100200FE4(item);
        if (value != 0 && value == blade) {
            result = true;
        }
        break;
    case 2:
        value = GfBdatItem::sys()->fn_7100203610(item);
        if (value != 0 && value == blade) {
            result = true;
        }
        break;
    case 20:
        value = GfBdatItem::sys()->fn_7100206788(item);
        if (value != 0 && value == blade) {
            result = true;
        }
        break;
    default:
        break;
    }
    return result;
}

int GfMenuItemUtil::canCreateOrb(unsigned int item) {
    unsigned int recipe = GfRecipeOrbUtil::getRecipeID(item);
    if (recipe == 0) {
        return 3;
    }
    if (!GfRecipeOrbUtil::isEnableRecipe(recipe)) {
        return 2;
    }
    unsigned long count;  // the orbs with the new one
    {
        ::mm::mtl::FixedVector<GfItem, 1024> items;
        GfItemUtil::getInfo(items, static_cast<ItemType::Type>(3), false);
        count = items.size() + 1;
    }
    return count > 500;
}

unsigned int GfMenuItemUtil::getEquipErrorCmnWindowID(unsigned int error) {
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_71009BCB94)
    static const unsigned int s_cmnWindowIds[] = {0, 22, 2, 1, 10, 0};
    if (error > 5) {
        return 0;
    }
    return s_cmnWindowIds[error];
}

bool GfMenuItemUtil::convShopIcon(unsigned int icon, ItemType::Type& type, unsigned int& id) {
    // Proposed names, not the original's: the symbols leave the table unnamed (lbl_71009BCBAC)
    struct ShopIcon {
        unsigned int m_icon;
        ItemType::Type m_type;
        unsigned int m_id;
    };
    static const ShopIcon s_shopIcons[] = {
        {428, static_cast<ItemType::Type>(5), 0},   {429, static_cast<ItemType::Type>(14), 0},
        {430, static_cast<ItemType::Type>(1), 0},   {432, static_cast<ItemType::Type>(3), 0},
        {434, static_cast<ItemType::Type>(10), 12}, {435, static_cast<ItemType::Type>(10), 13},
        {436, static_cast<ItemType::Type>(10), 14}, {437, static_cast<ItemType::Type>(10), 15},
        {438, static_cast<ItemType::Type>(10), 16}, {439, static_cast<ItemType::Type>(10), 17},
        {440, static_cast<ItemType::Type>(10), 18}, {441, static_cast<ItemType::Type>(10), 19},
        {442, static_cast<ItemType::Type>(10), 20}, {443, static_cast<ItemType::Type>(10), 21},
        {444, static_cast<ItemType::Type>(10), 22}, {445, static_cast<ItemType::Type>(10), 23},
        {446, static_cast<ItemType::Type>(2), 0},
    };
    for (unsigned int i = 0; i < sizeof(s_shopIcons) / sizeof(s_shopIcons[0]); i++) {
        if (s_shopIcons[i].m_icon == icon) {
            type = s_shopIcons[i].m_type;
            id = s_shopIcons[i].m_id;
            return true;
        }
    }
    return false;
}

GfMenuKizunaring::GfMenuKizunaring(const GfSetupParam& param) {
    initialize(param);
}

void GfMenuKizunaring::initialize(const GfSetupParam& param) {
    m_initialized = true;
}

GfMenuKizunaring::~GfMenuKizunaring() {}

void GfMenuKizunaring::build(const GfSetupParam& param) {
#line 41
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuKizunaring(param);
}

void GfMenuKizunaring::destroy() {
    GfMenuKizunaring* menu = get();
    menu->finalize();
    delete menu;
}

void GfMenuKizunaring::finalize() {
    m_initialized = false;
}

bool GfMenuKizunaring::isInitialized() {
    GfMenuKizunaring* menu = get();
    if (menu != nullptr) {
        return menu->m_initialized;
    }
    return false;
}

void GfMenuKizunaring::postUpdate(const fw::UpdateInfo& info) {}

}  // namespace gf
