#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfMenuWeaponAdapter.h"
#include "classes/gf/GfMenuWeaponAdapter/IConverter.h"
#include "classes/gf/GfMenuWeaponAdapter/ReferenceBladeConverter.h"
#include "classes/gf/GfMenuWeaponAdapter/ReferenceChipConverter.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfBdatItem.h"
#include "classes/gf/GfBdatRsc.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "gf/GfDataWeapon.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuObjUtil.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"

namespace gf {

// per type: the update_* update shows and the plugin create makes (text, number from 1 to 999 or to 100, image
// index)
static GfMenuWeaponAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuWeaponAdapter::update_Name, {2, 0, 0}},
    {&GfMenuWeaponAdapter::update_Atk, {0, 1, 999}},
    {&GfMenuWeaponAdapter::update_Guard, {0, 0, 100}},
    {&GfMenuWeaponAdapter::update_Critical, {0, 0, 100}},
    {&GfMenuWeaponAdapter::update_Balance, {0, 1, 999}},
    {&GfMenuWeaponAdapter::update_TypeName, {2, 0, 0}},
    {&GfMenuWeaponAdapter::update_Caption, {2, 0, 0}},
    {&GfMenuWeaponAdapter::update_Image, {1, 0, 0}},
};

GfMenuWeaponAdapter::~GfMenuWeaponAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuWeaponAdapter* GfMenuWeaponAdapter::create(unsigned int handle, unsigned int type, unsigned int weaponId,
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
#line 191
    GfMenuWeaponAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuWeaponAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_weaponId = weaponId;
    plugin->release();
    return adapter;
}

bool GfMenuWeaponAdapter::update_Name(unsigned int weaponId) {
    unsigned char* bdat;
    unsigned int id;
    GfDataWeapon::getName(bdat, id, weaponId);
    ui::UIStr text(bdat, id);
    setText(text);
    return true;
}

bool GfMenuWeaponAdapter::update_Atk(unsigned int weaponId) {
    setNumber(GfDataWeapon::getDamage(weaponId));
    return true;
}

bool GfMenuWeaponAdapter::update_Guard(unsigned int weaponId) {
    setNumber(GfDataWeapon::getGuardRatio(weaponId));
    return true;
}

bool GfMenuWeaponAdapter::update_Critical(unsigned int weaponId) {
    setNumber(GfDataWeapon::getCriticalRatio(weaponId));
    return true;
}

bool GfMenuWeaponAdapter::update_Balance(unsigned int weaponId) {
    setNumber(GfDataWeapon::getStability(weaponId));
    return true;
}

bool GfMenuWeaponAdapter::update_TypeName(unsigned int weaponId) {
    unsigned char* bdat;
    unsigned int id;
    if (!GfDataWeapon::getWeaponTypeNameByItem(bdat, id, weaponId) || !GfMenuBdat::isValidBdatID(bdat, id)) {
        return false;
    }
    ui::UIStr text(bdat, id);
    setText(text);
    return true;
}

bool GfMenuWeaponAdapter::update_Caption(unsigned int weaponId) {
    unsigned int enhance = GfDataWeapon::getEnhance(weaponId);
    if (enhance == 0) {
        return false;
    }
    unsigned char* message = GfDataBdat::getFP(0x19B);
    unsigned char* bdat = GfDataBdat::getFP(0x2C);
    if (!GfMenuBdat::isValidBdatID(bdat, enhance)) {
        return false;
    }
    unsigned int caption = (unsigned char)Bdat::getVal(bdat, "Caption", enhance);
    // with add-on menu layer 3 usable, the table's Caption2 (when it has one and it is not 0) replaces Caption
    if (GfMenuObjUtil::fn_710048FD30(3) && Bdat::getMember(bdat, "Caption2") != nullptr) {
        unsigned short caption2 = (unsigned short)Bdat::getVal(bdat, "Caption2", enhance);
        if (caption2 != 0) {
            caption = caption2;
        }
    }
    if (!GfMenuBdat::isValidBdatID(message, caption)) {
        return false;
    }
    ui::UIStr text(message, caption);
    text.m_ownerId = enhance;
    setText(text);
    return true;
}

bool GfMenuWeaponAdapter::update_Image(unsigned int weaponId) {
    unsigned short rsc = GfBdatItem::get()->getPcWpnRscR(weaponId);
    if (rsc == 0) {
        return false;
    }
    int image = GfBdatRsc::get()->getRSC_PcWpnMenuImageID(rsc);
    if (image == 0) {
        return false;
    }
    setNumber(image);
    return true;
}

GfMenuWeaponAdapter* GfMenuWeaponAdapter::createFromCoverter(unsigned int handle, unsigned int type,
                                                             IConverter* converter, bool changed) {
    GfMenuWeaponAdapter* adapter = create(handle, type, converter->getWeaponID(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

GfMenuWeaponAdapter* GfMenuWeaponAdapter::createFromReferenceBlade(unsigned int handle, unsigned int type,
                                                                   unsigned int reference, bool changed) {
#line 216
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReferenceBladeConverter(reference);
    return createFromCoverter(handle, type, converter, changed);
}

GfMenuWeaponAdapter* GfMenuWeaponAdapter::createFromReferenceChip(unsigned int handle, unsigned int type,
                                                                  const ReferenceChip& chip, bool changed) {
#line 234
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReferenceChipConverter(chip);
    return createFromCoverter(handle, type, converter, changed);
}

void GfMenuWeaponAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        unsigned int weaponId = m_converter->getWeaponID();
        if (m_weaponId != weaponId) {
            m_weaponId = weaponId;
            setChange();
        }
    }
    if (m_update.isValid() && (m_flags & 3) != 0) {
        if (m_weaponId != 0) {
            setDisp(m_update(m_weaponId));
        } else {
            setDisp(false);
        }
        m_flags &= ~1;
    }
}

GfMenuWeaponAdapter::ReferenceChipConverter::~ReferenceChipConverter() {}

unsigned int GfMenuWeaponAdapter::ReferenceChipConverter::getWeaponID() {
    DataParamAcc acc(4, GfMenuReference::getReferenceBladeID(m_chip.m_reference), GimmickType(0));
    unsigned int weapon = 0;
    if (acc.isValid()) {
        if (m_chip.m_chip && m_chip.m_chip->m_value != 0) {
            weapon = GfDataWeapon::getNewWeapon(acc.getEquipWeapon(-1, false), m_chip.m_chip->m_value);
        } else {
            weapon = 0;
        }
    }
    return weapon;
}

}  // namespace gf
