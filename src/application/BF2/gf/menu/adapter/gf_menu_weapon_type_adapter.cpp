#include "gf/GfDataDriverArts.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfDataWeapon.h"
#include "classes/gf/GfMenuWeaponTypeAdapter.h"
#include "classes/gf/GfMenuWeaponTypeAdapter/IConverter.h"
#include "classes/gf/GfMenuWeaponTypeAdapter/ReferenceDriverConverter.h"
#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfMenuWeaponTypeAdapter.h"
#include "classes/gf/GfMenuWeaponTypeAdapter/IConverter.h"
#include "classes/gf/GfMenuWeaponTypeAdapter/ReferenceDriverConverter.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "gf/GfDataDriverArts.h"
#include "gf/GfDataWeapon.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixedArray.h"
#include "ui/UIStr.h"

namespace gf {

// per type: the update_* update shows and the plugin create makes (text, image index, number, disp)
static GfMenuWeaponTypeAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuWeaponTypeAdapter::update_WpnTypeName, {2, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_WpnTypeIcon, {1, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_WpnTypeWP, {0, 0, 9999999}},
    {&GfMenuWeaponTypeAdapter::update_ArtsName, {2, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsIconType, {1, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsIconEnhance, {1, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsIconReact, {1, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsIconRange, {1, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsTextType, {2, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsTextReact, {2, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsTextRange, {2, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsNumDamage, {0, 0, 999}},
    {&GfMenuWeaponTypeAdapter::update_ArtsNumRecast, {0, 0, 999}},
    {&GfMenuWeaponTypeAdapter::update_ArtsLevel, {0, 0, 99}},
    {&GfMenuWeaponTypeAdapter::update_ArtsIconLevel, {1, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsDescription, {2, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsWp, {0, 0, 99999}},
    {&GfMenuWeaponTypeAdapter::update_ArtsDriverLevel, {0, 1, 99}},
    {&GfMenuWeaponTypeAdapter::update_ArtsLevel0Disp, {3, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsLevelMaxDisp, {3, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsEnhanceDescription, {2, 0, 0}},
    {&GfMenuWeaponTypeAdapter::update_ArtsReleseLv, {0, 0, 99}},
};

GfMenuWeaponTypeAdapter::~GfMenuWeaponTypeAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuWeaponTypeAdapter* GfMenuWeaponTypeAdapter::create(unsigned int handle, unsigned int type, unsigned int driverId,
                                                         unsigned int wpnType, unsigned int artsIndex, bool changed) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object == nullptr) {
        return nullptr;
    }
    const TypeSetup& setup = s_typeSetups[type];
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup.plugin);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 203
    GfMenuWeaponTypeAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuWeaponTypeAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_driverId = driverId;
    adapter->m_wpnType = wpnType;
    adapter->m_artsIndex = artsIndex;
    plugin->release();
    return adapter;
}

inline bool GfMenuWeaponTypeAdapter::getDriverArts(DriverArts& arts) {
    mm::mtl::FixedArray<unsigned int, 4> list;
    if (GfMenuObjUtil::getEnableArts(list, m_driverId, m_wpnType, 0, false)) {
        if (m_artsIndex < 4) {
            arts.m_arts = list[m_artsIndex];
            arts.m_level = GfDataDriverArts::getArtsLevel(m_driverId, arts.m_arts);
            return true;
        }
    }
    return false;
}

bool GfMenuWeaponTypeAdapter::update_WpnTypeName() {
    unsigned char* bdat;
    unsigned int id;
    if (!GfDataWeapon::getWeaponTypeName(bdat, id, m_wpnType)) {
        return false;
    }
    ui::UIStr text(bdat, id);
    setText(text);
    return true;
}

bool GfMenuWeaponTypeAdapter::update_WpnTypeIcon() {
    if (m_wpnType == 0) {
        return false;
    }
    setNumber(m_wpnType - 1);
    return true;
}

bool GfMenuWeaponTypeAdapter::update_WpnTypeWP() {
    setNumber(GfDataDriverArts::getWp(m_driverId, m_wpnType, 0));
    return true;
}

bool GfMenuWeaponTypeAdapter::update_ArtsName() {
    mm::mtl::FixedArray<unsigned int, 4> list;
    if (!GfMenuObjUtil::getEnableArts(list, m_driverId, m_wpnType, 0, false)) {
        return false;
    }
    unsigned int arts = list[m_artsIndex];
    unsigned char* bdat = GfDataDriverArts::getNameFP();
    unsigned int id = GfDataDriverArts::getNameID(arts);
    if (id == 0) {
        return false;
    }
    ui::UIStr text(bdat, id);
    setText(text);
    return true;
}

bool GfMenuWeaponTypeAdapter::update_ArtsIconType() {
    mm::mtl::FixedArray<unsigned int, 4> list;
    if (!GfMenuObjUtil::getEnableArts(list, m_driverId, m_wpnType, 0, false)) {
        return false;
    }
    unsigned int arts = list[m_artsIndex];
    unsigned int level = GfDataDriverArts::getArtsLevel(m_driverId, arts);
    if (arts != 0 && level != 0) {
        GfMenuObjUtil::ArtsIconInfo info = {};
        if (GfMenuObjUtil::getArtsIconInfo(arts, level, info)) {
            setNumber(info.m_type);
            return true;
        }
    }
    return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsIconEnhance() {
    mm::mtl::FixedArray<unsigned int, 4> list;
    if (!GfMenuObjUtil::getEnableArts(list, m_driverId, m_wpnType, 0, false)) {
        return false;
    }
    unsigned int arts = list[m_artsIndex];
    unsigned int level = GfDataDriverArts::getArtsLevel(m_driverId, arts);
    if (arts != 0 && level != 0) {
        GfMenuObjUtil::ArtsIconInfo info = {};
        if (GfMenuObjUtil::getArtsIconInfo(arts, level, info)) {
            setNumber(info.m_enhance);
            return true;
        }
    }
    return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsIconReact() {
    mm::mtl::FixedArray<unsigned int, 4> list;
    if (!GfMenuObjUtil::getEnableArts(list, m_driverId, m_wpnType, 0, false)) {
        return false;
    }
    unsigned int arts = list[m_artsIndex];
    unsigned int level = GfDataDriverArts::getArtsLevel(m_driverId, arts);
    if (arts != 0 && level != 0) {
        GfMenuObjUtil::ArtsIconInfo info = {};
        if (GfMenuObjUtil::getArtsIconInfo(arts, level, info)) {
            setNumber(info.m_react);
            return true;
        }
    }
    return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsIconRange() {
    mm::mtl::FixedArray<unsigned int, 4> list;
    if (!GfMenuObjUtil::getEnableArts(list, m_driverId, m_wpnType, 0, false)) {
        return false;
    }
    unsigned int arts = list[m_artsIndex];
    unsigned int level = GfDataDriverArts::getArtsLevel(m_driverId, arts);
    if (arts != 0 && level != 0) {
        GfMenuObjUtil::ArtsIconInfo info = {};
        if (GfMenuObjUtil::getArtsIconInfo(arts, level, info)) {
            setNumber(info.m_range);
            return true;
        }
    }
    return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsTextType() {
    DriverArts arts;
    GfMenuObjUtil::ArtsIconInfo info = {};
    if (getDriverArts(arts) && GfMenuObjUtil::getArtsIconInfo(arts.m_arts, arts.m_level, info) &&
        info.m_type != 0) {
        unsigned short id = GfMenuObjUtil::getMsgIDFromList(0x14F, info.m_type);
        if (id != 0) {
            ui::UIStr text(GfDataBdat::getFP(0x121), id);
            setText(text);
            return true;
        }
    }
    return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsTextReact() {
    DriverArts arts;
    GfMenuObjUtil::ArtsIconInfo info = {};
    if (getDriverArts(arts) && GfMenuObjUtil::getArtsIconInfo(arts.m_arts, arts.m_level, info) &&
        (unsigned int)info.m_react >= 3) {
        unsigned short id = GfMenuObjUtil::getMsgIDFromList(0x13F, info.m_react - 2);
        if (id != 0) {
            ui::UIStr text(GfDataBdat::getFP(0x120), id);
            setText(text);
            return true;
        }
    }
    return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsTextRange() {
    DriverArts arts;
    GfMenuObjUtil::ArtsIconInfo info = {};
    if (getDriverArts(arts) && GfMenuObjUtil::getArtsIconInfo(arts.m_arts, arts.m_level, info)) {
        unsigned short id = GfMenuObjUtil::getMsgIDFromList(0x151, info.m_range + 1);
        if (id != 0) {
            ui::UIStr text(GfDataBdat::getFP(0x122), id);
            setText(text);
            return true;
        }
    }
    return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsNumDamage() {
    DriverArts arts;
    if (getDriverArts(arts)) {
        setNumber(GfDataDriverArts::getDamageMul(arts.m_arts, arts.m_level));
        return true;
    }
    return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsNumRecast() {
    DriverArts arts;
    if (getDriverArts(arts)) {
        setNumber(GfDataDriverArts::getRecast(arts.m_arts, arts.m_level));
        return true;
    }
    return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsLevel() {
    mm::mtl::FixedArray<unsigned int, 4> list;
    if (!GfMenuObjUtil::getEnableArts(list, m_driverId, m_wpnType, 0, false)) {
        return false;
    }
    unsigned int arts = list[m_artsIndex];
    setNumber(GfDataDriverArts::getArtsLevel(m_driverId, arts));
    return true;
}

bool GfMenuWeaponTypeAdapter::update_ArtsIconLevel() {
    mm::mtl::FixedArray<unsigned int, 4> list;
    if (!GfMenuObjUtil::getEnableArts(list, m_driverId, m_wpnType, 0, false)) {
        return false;
    }
    unsigned int arts = list[m_artsIndex];
    setNumber(GfDataDriverArts::getArtsLevel(m_driverId, arts) - 1);
    return true;
}

bool GfMenuWeaponTypeAdapter::update_ArtsDescription() {
    mm::mtl::FixedArray<unsigned int, 4> list;
    if (!GfMenuObjUtil::getEnableArts(list, m_driverId, m_wpnType, 0, false)) {
        return false;
    }
    unsigned int arts = list[m_artsIndex];
    ui::UIStr text(GfDataDriverArts::getCaptionFP(), GfDataDriverArts::getCaptionID(arts));
    setText(text);
    return true;
}

bool GfMenuWeaponTypeAdapter::update_ArtsWp() {
    mm::mtl::FixedArray<unsigned int, 4> list;
    if (!GfMenuObjUtil::getEnableArts(list, m_driverId, m_wpnType, 0, false)) {
        return false;
    }
    unsigned int arts = list[m_artsIndex];
    setNumber(GfDataDriverArts::getNeedLevelupWp(m_driverId, arts));
    return true;
}

bool GfMenuWeaponTypeAdapter::update_ArtsDriverLevel() {
    mm::mtl::FixedArray<unsigned int, 4> list;
    if (!GfMenuObjUtil::getEnableArts(list, m_driverId, m_wpnType, 0, false)) {
        return false;
    }
    unsigned int arts = list[m_artsIndex];
    unsigned int level = GfDataDriverArts::getArtsLevel(m_driverId, arts);
    if (level < GfDataDriverArts::getLevelMax(arts)) {
        unsigned int cap = GfDataDriverArts::getLevelCap(arts, level + 1);
        if (cap >= 1 && cap <= 99) {
            setNumber(cap);
            return true;
        }
    }
    return false;
}

bool GfMenuWeaponTypeAdapter::update_ArtsLevel0Disp() {
    mm::mtl::FixedArray<unsigned int, 4> list;
    if (GfMenuObjUtil::getEnableArts(list, m_driverId, m_wpnType, 0, false)) {
        unsigned int arts = list[m_artsIndex];
        if (GfDataDriverArts::getArtsLevel(m_driverId, arts) != 0) {
            return m_param == 0;
        }
    }
    return m_param != 0;
}

bool GfMenuWeaponTypeAdapter::update_ArtsLevelMaxDisp() {
    mm::mtl::FixedArray<unsigned int, 4> list;
    if (GfMenuObjUtil::getEnableArts(list, m_driverId, m_wpnType, 0, false)) {
        unsigned int arts = list[m_artsIndex];
        if (GfDataDriverArts::getArtsLevel(m_driverId, arts) < GfDataDriverArts::getLevelMax(arts)) {
            return m_param == 0;
        }
    }
    return m_param != 0;
}

bool GfMenuWeaponTypeAdapter::update_ArtsEnhanceDescription() {
    mm::mtl::FixedArray<unsigned int, 4> list;
    if (!GfMenuObjUtil::getEnableArts(list, m_driverId, m_wpnType, 0, false)) {
        return false;
    }
    unsigned int arts = list[m_artsIndex];
    GfDataDriverArts::getEnhance(arts, GfDataDriverArts::getArtsLevel(m_driverId, arts));
    ui::UIStr text(GfDataDriverArts::getCaptionFP(), GfDataDriverArts::getCaptionID(arts));
    setText(text);
    return true;
}

bool GfMenuWeaponTypeAdapter::update_ArtsReleseLv() {
    mm::mtl::FixedArray<unsigned int, 4> list;
    if (!GfMenuObjUtil::getEnableArts(list, m_driverId, m_wpnType, 0, false)) {
        return false;
    }
    setNumber(GfDataDriverArts::getLevelCap(list[m_artsIndex], m_param));
    return true;
}

GfMenuWeaponTypeAdapter* GfMenuWeaponTypeAdapter::createFromCoverter(unsigned int handle, unsigned int type,
                                                                     IConverter* converter, bool changed) {
    unsigned int driverId = converter->getDriverId();
    unsigned int wpnType = converter->getWpnType();
    unsigned int artsIndex = converter->getArtsIndex();
    GfMenuWeaponTypeAdapter* adapter = create(handle, type, driverId, wpnType, artsIndex, changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

GfMenuWeaponTypeAdapter* GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(
    unsigned int handle, unsigned int type, unsigned short driver, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> wpnType,
    unsigned short artsIndex, bool changed) {
#line 234
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        ReferenceDriverConverter(driver, wpnType, artsIndex);
    return createFromCoverter(handle, type, converter, changed);
}

void GfMenuWeaponTypeAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        unsigned int driverId = m_converter->getDriverId();
        if (m_driverId != driverId) {
            m_driverId = driverId;
            setChange();
        }
        unsigned int wpnType = m_converter->getWpnType();
        if (m_wpnType != wpnType) {
            m_wpnType = wpnType;
            setChange();
        }
        unsigned int artsIndex = m_converter->getArtsIndex();
        if (m_artsIndex != artsIndex) {
            m_artsIndex = artsIndex;
            setChange();
        }
    }
    if (m_update.isValid() && (m_flags & 3) != 0) {
        if (m_driverId != 0) {
            setDisp(m_update());
        } else {
            setDisp(false);
        }
        m_flags &= ~1;
    }
}

}  // namespace gf
