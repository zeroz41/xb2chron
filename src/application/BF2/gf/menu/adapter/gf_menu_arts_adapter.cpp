#include "classes/gf/GfMenuArtsAdapter.h"
#include "classes/gf/GfMenuArtsList.h"
#include "classes/gf/GfMenuArtsAdapter/IConverter.h"
#include "classes/gf/GfMenuArtsAdapter/ListConverter.h"
#include "classes/gf/GfMenuArtsAdapter/ListReferenceDriverConverter.h"
#include "classes/gf/GfMenuArtsAdapter/ListReferenceDriverConverterReferenceIndex.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfBdatBtl.h"
#include "gf/GfDataDriverArts.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "gf/GfMenuEnhanceAdapter.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"

namespace gf {

// per type: the update_* update shows and the plugin create makes (text, image index, number up to 9999999, number
// from 1 to 5, number up to 99, number up to 999, disp)
static GfMenuArtsAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuArtsAdapter::update_ArtsName, {2, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsDescription, {2, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsIconType, {1, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsIconEnhance, {1, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsIconReact, {1, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsIconRange, {1, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsWp, {0, 0, 9999999}},
    {&GfMenuArtsAdapter::update_ArtsIconLevel, {1, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsNumLevel, {0, 1, 5}},
    {&GfMenuArtsAdapter::update_ArtsReleseLv, {0, 0, 99}},
    {&GfMenuArtsAdapter::update_ArtsTextType, {2, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsTextRange, {2, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsTextReact, {2, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsNumDamage, {0, 0, 999}},
    {&GfMenuArtsAdapter::update_ArtsNumRecast, {0, 0, 999}},
    {&GfMenuArtsAdapter::update_ArtsEnhanceDescription, {2, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsIconReleseLv, {1, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsNumDamageNextLv, {0, 0, 999}},
    {&GfMenuArtsAdapter::update_ArtsNumRecastNextLv, {0, 0, 999}},
    {&GfMenuArtsAdapter::update_ArtsEnhanceDescriptionNextLv, {2, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsDispLvMax, {3, 0, 0}},
    {&GfMenuArtsAdapter::update_ArtsTextIndex, {2, 0, 0}},
    {&GfMenuArtsAdapter::update_IraArtsTalentCaption, {2, 0, 0}},
    {&GfMenuArtsAdapter::update_IraArtsTalentCond, {2, 0, 0}},
};

inline GfMenuArtsAdapter* GfMenuArtsAdapter::createFromCoverter(unsigned int handle, unsigned int type,
                                                                IConverter* converter, bool changed) {
    MenuArtsInfo info = {};
    converter->getArtsInfo(info);
    unsigned int driverId = converter->getDriverId();
    GfMenuArtsAdapter* adapter = create(handle, type, info.m_artsId, driverId, info.m_level, changed);
    if (adapter == nullptr) {
        return nullptr;
    }
    adapter->m_converter = converter;
    return adapter;
}

GfMenuArtsAdapter* GfMenuArtsAdapter::createFromList(unsigned int handle, unsigned int type, GfMenuArtsList* list,
                                                     int index, unsigned int driverId, bool changed) {
#line 288
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListConverter(list, index, driverId);
    return createFromCoverter(handle, type, converter, changed);
}

GfMenuArtsAdapter* GfMenuArtsAdapter::createFromListReferenceDriver(unsigned int handle, unsigned int type,
                                                                    GfMenuArtsList* list, int index,
                                                                    unsigned int reference, bool changed) {
#line 297
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        ListReferenceDriverConverter(list, index, reference);
    return createFromCoverter(handle, type, converter, changed);
}

GfMenuArtsAdapter* GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(
    unsigned int handle, unsigned int type, GfMenuArtsList* list, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> index,
    unsigned int reference, bool changed) {
#line 306
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        ListReferenceDriverConverterReferenceIndex(list, index, reference);
    return createFromCoverter(handle, type, converter, changed);
}

GfMenuArtsAdapter::~GfMenuArtsAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuArtsAdapter* GfMenuArtsAdapter::create(unsigned int handle, unsigned int type, unsigned int artsId,
                                             unsigned int driverId, unsigned int level, bool changed) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object == nullptr) {
        return nullptr;
    }
    const TypeSetup& setup = s_typeSetups[type];
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup.plugin);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 376
    GfMenuArtsAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuArtsAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_artsId = artsId;
    adapter->m_driverId = driverId;
    adapter->m_level = level;
    plugin->release();
    return adapter;
}

bool GfMenuArtsAdapter::update_ArtsName() {
    unsigned char* bdat = GfDataDriverArts::getNameFP();
    unsigned int id = GfDataDriverArts::getNameID(m_artsId);
    if (id == 0) {
        return false;
    }
    ui::UIStr text(bdat, id);
    setText(text);
    return true;
}

bool GfMenuArtsAdapter::update_ArtsDescription() {
    unsigned char* bdat = GfDataDriverArts::getCaptionFP();
    unsigned int id = GfDataDriverArts::getCaptionID(m_artsId);
    if (id == 0) {
        return false;
    }
    ui::UIStr text(bdat, id);
    setText(text);
    return true;
}

bool GfMenuArtsAdapter::update_ArtsIconType() {
    if (m_driverId == 0 || m_artsId == 0) {
        return false;
    }
    if (m_level != 0) {
        GfMenuObjUtil::ArtsIconInfo info = {};
        if (GfMenuObjUtil::getArtsIconInfo(m_artsId, m_level, info)) {
            setNumber(info.m_type);
            return true;
        }
    }
    return false;
}

bool GfMenuArtsAdapter::update_ArtsIconEnhance() {
    if (m_driverId == 0 || m_artsId == 0) {
        return false;
    }
    if (m_level != 0) {
        GfMenuObjUtil::ArtsIconInfo info = {};
        if (GfMenuObjUtil::getArtsIconInfo(m_artsId, m_level, info)) {
            setNumber(info.m_enhance);
            return true;
        }
    }
    return false;
}

bool GfMenuArtsAdapter::update_ArtsIconReact() {
    if (m_driverId == 0 || m_artsId == 0) {
        return false;
    }
    if (m_level != 0) {
        GfMenuObjUtil::ArtsIconInfo info = {};
        if (GfMenuObjUtil::getArtsIconInfo(m_artsId, m_level, info)) {
            setNumber(info.m_react);
            return true;
        }
    }
    return false;
}

bool GfMenuArtsAdapter::update_ArtsIconRange() {
    if (m_driverId == 0 || m_artsId == 0) {
        return false;
    }
    if (m_level != 0) {
        GfMenuObjUtil::ArtsIconInfo info = {};
        if (GfMenuObjUtil::getArtsIconInfo(m_artsId, m_level, info)) {
            setNumber(info.m_range);
            return true;
        }
    }
    return false;
}

bool GfMenuArtsAdapter::update_ArtsWp() {
    if (m_driverId == 0 || m_artsId == 0) {
        return false;
    }
    if (m_level >= GfDataDriverArts::getLevelMax(m_artsId)) {
        return false;
    }
    setNumber(GfDataDriverArts::getNeedLevelupWp(m_driverId, m_artsId));
    return true;
}

bool GfMenuArtsAdapter::update_ArtsIconLevel() {
    if (m_driverId == 0 || m_artsId == 0 || m_level == 0) {
        return false;
    }
    setNumber(m_level - 1);
    return true;
}

bool GfMenuArtsAdapter::update_ArtsNumLevel() {
    if (m_driverId == 0 || m_artsId == 0) {
        return false;
    }
    setNumber(m_level);
    return true;
}

bool GfMenuArtsAdapter::update_ArtsReleseLv() {
    if (m_driverId == 0 || m_artsId == 0) {
        return false;
    }
    setNumber(GfDataDriverArts::getLevelCap(m_artsId, m_releaseIndex));
    return true;
}

bool GfMenuArtsAdapter::update_ArtsTextType() {
    if (m_driverId == 0 || m_artsId == 0 || m_level == 0) {
        return false;
    }
    int artsType = GfDataDriverArts::getArtsType(m_artsId);
    unsigned short index = 3;
    switch (artsType) {
    case 1:
        index = 1;
        break;
    case 2:
        index = 4;
        break;
    case 3:
        index = 2;
        break;
    case 11:
        break;
    default:
        if (GfMenuObjUtil::isValidExpansion(3) && artsType == 4) {
            index = 5;
            break;
        }
        return false;
    }
    unsigned short id = GfMenuObjUtil::getMsgIDFromList(0x14F, index);
    if (id == 0) {
        return false;
    }
    ui::UIStr text(GfDataBdat::getFP(0x121), id);
    setText(text);
    return true;
}

bool GfMenuArtsAdapter::update_ArtsTextRange() {
    if (m_driverId == 0 || m_artsId == 0 || m_level == 0) {
        return false;
    }
    GfMenuObjUtil::ArtsIconInfo info = {};
    if (!GfMenuObjUtil::getArtsIconInfo(m_artsId, m_level, info)) {
        return false;
    }
    unsigned short id = GfMenuObjUtil::getMsgIDFromList(0x151, info.m_range + 1);
    if (id == 0) {
        return false;
    }
    ui::UIStr text(GfDataBdat::getFP(0x122), id);
    setText(text);
    return true;
}

bool GfMenuArtsAdapter::update_ArtsTextReact() {
    if (m_driverId == 0 || m_artsId == 0 || m_level == 0) {
        return false;
    }
    GfMenuObjUtil::ArtsIconInfo info = {};
    if (!GfMenuObjUtil::getArtsIconInfo(m_artsId, m_level, info)) {
        return false;
    }
    unsigned int id;
    if (info.m_react != 0) {
        id = GfMenuObjUtil::getMsgIDFromList(0x140, info.m_react);
        if (id == 0) {
            return false;
        }
    } else {
        id = GfMenuObjUtil::getMsgIDFromList(0x140, 7);
        if (id == 0) {
            return false;
        }
    }
    ui::UIStr text(GfDataBdat::getFP(0x120), id);
    setText(text);
    return true;
}

bool GfMenuArtsAdapter::update_ArtsNumDamage() {
    if (m_driverId == 0 || m_artsId == 0) {
        return false;
    }
    unsigned int level = m_level;
    if (level == 0) {
        return false;
    }
    int artsType = GfDataDriverArts::getArtsType(m_artsId);
    if (GfMenuObjUtil::isValidExpansion(3) && artsType == 4) {
        return false;
    }
    unsigned int damage = GfDataDriverArts::getDamageMul(m_artsId, level);
    if (artsType == 11) {
        setNumber(damage / 30);
    } else {
        setNumber(damage);
    }
    return true;
}

bool GfMenuArtsAdapter::update_ArtsNumRecast() {
    if (m_driverId == 0 || m_artsId == 0 ||
        (GfMenuObjUtil::isValidExpansion(3) && GfBdatBtl::get()->getArtsDrIrType(m_artsId) == 2) || m_level == 0) {
        return false;
    }
    setNumber(GfDataDriverArts::getRecast(m_artsId, m_level));
    return true;
}

bool GfMenuArtsAdapter::update_ArtsEnhanceDescription() {
    if (m_driverId == 0 || m_artsId == 0 || m_level == 0) {
        return false;
    }
    unsigned int enhance = GfDataDriverArts::getEnhance(m_artsId, m_level);
    if (enhance == 0) {
        unsigned int id = (unsigned short)Bdat::getVal(GfDataBdat::getFP(0x15A), "name", 4);
        ui::UIStr text(GfDataBdat::getFP(0xF5), id);
        setText(text);
    } else {
        ui::UIStr text;
        GfMenuEnhanceAdapter::getEnhanceCaption(enhance, text);
        setText(text);
    }
    return true;
}

bool GfMenuArtsAdapter::update_ArtsIconReleseLv() {
    if (m_driverId == 0 || m_artsId == 0) {
        return false;
    }
    unsigned int cap = GfDataDriverArts::getLevelCap(m_artsId, m_releaseIndex);
    DataParamAcc acc(3, m_driverId, GimmickType(0));
    bool result = false;
    if (acc.isValid()) {
        setNumber(cap <= acc.getLevel(false));
        result = true;
    }
    return result;
}

bool GfMenuArtsAdapter::update_ArtsNumDamageNextLv() {
    if (m_driverId == 0 || m_artsId == 0) {
        return false;
    }
    unsigned int level = m_level + 1;
    if (level > GfDataDriverArts::getLevelMax(m_artsId)) {
        return false;
    }
    int artsType = GfDataDriverArts::getArtsType(m_artsId);
    if (GfMenuObjUtil::isValidExpansion(3) && artsType == 4) {
        return false;
    }
    unsigned int damage = GfDataDriverArts::getDamageMul(m_artsId, level);
    if (artsType == 11) {
        setNumber(damage / 30);
    } else {
        setNumber(damage);
    }
    return true;
}

bool GfMenuArtsAdapter::update_ArtsNumRecastNextLv() {
    if (m_driverId == 0 || m_artsId == 0 ||
        (GfMenuObjUtil::isValidExpansion(3) && GfBdatBtl::get()->getArtsDrIrType(m_artsId) == 2)) {
        return false;
    }
    unsigned int level = m_level + 1;
    if (level > GfDataDriverArts::getLevelMax(m_artsId)) {
        return false;
    }
    setNumber(GfDataDriverArts::getRecast(m_artsId, level));
    return true;
}

bool GfMenuArtsAdapter::update_ArtsEnhanceDescriptionNextLv() {
    if (m_driverId == 0 || m_artsId == 0) {
        return false;
    }
    unsigned int level = m_level + 1;
    if (level > GfDataDriverArts::getLevelMax(m_artsId)) {
        return false;
    }
    unsigned int enhance = GfDataDriverArts::getEnhance(m_artsId, level);
    if (enhance == 0) {
        unsigned int id = (unsigned short)Bdat::getVal(GfDataBdat::getFP(0x15A), "name", 4);
        ui::UIStr text(GfDataBdat::getFP(0xF5), id);
        setText(text);
    } else {
        ui::UIStr text;
        GfMenuEnhanceAdapter::getEnhanceCaption(enhance, text);
        setText(text);
    }
    return true;
}

// update_ArtsDispLvMax: not written yet (2 words apart: the original's artsId == 0 test branches to the shared
// "return false" block, ours past it); see wip

bool GfMenuArtsAdapter::update_ArtsTextIndex() {
    if (m_driverId == 0 || m_artsId == 0 || m_level == 0) {
        return false;
    }
    int artsType = GfDataDriverArts::getArtsType(m_artsId);
    unsigned short index;
    if (artsType == 11) {
        index = 2;
    } else if (artsType == 3) {
        index = 3;
    } else if (artsType == 1 || artsType == 2) {
        index = 1;
    } else {
        return false;
    }
    unsigned short id = GfMenuObjUtil::getMsgIDFromList(0x150, index);
    if (id == 0) {
        return false;
    }
    ui::UIStr text(GfDataBdat::getFP(0xF5), id);
    setText(text);
    return true;
}

bool GfMenuArtsAdapter::update_IraArtsTalentCaption() {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return false;
    }
    unsigned short id = GfDataDriverArts::getTalentCaptionID(m_artsId);
    if (id == 0) {
        return false;
    }
    ui::UIStr text(GfDataBdat::getFP(0x191), id);
    setText(text);
    return true;
}

bool GfMenuArtsAdapter::update_IraArtsTalentCond() {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return false;
    }
    unsigned short id = GfDataDriverArts::getCondTalentCaptionID(m_artsId);
    if (id == 0) {
        return false;
    }
    ui::UIStr text(GfDataBdat::getFP(0x191), id);
    setText(text);
    return true;
}

void GfMenuArtsAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        MenuArtsInfo arts = {};
        m_converter->getArtsInfo(arts);
        if (m_artsId != arts.m_artsId) {
            m_artsId = arts.m_artsId;
            setChange();
        }
        if (m_driverId != m_converter->getDriverId()) {
            m_driverId = m_converter->getDriverId();
            setChange();
        }
        if (m_level != arts.m_level) {
            m_level = arts.m_level;
            setChange();
        }
    }
    if (m_update.isValid() && (m_flags & 3) != 0) {
        if (m_artsId != 0) {
            setDisp(m_update());
        } else {
            setDisp(false);
        }
        m_flags &= ~1;
    }
}

GfMenuArtsAdapter::ListConverter::~ListConverter() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

void GfMenuArtsAdapter::ListConverter::getArtsInfo(MenuArtsInfo& info) {
    GfMenuArtsList* list;
    unsigned int index;
    if (m_index == -1) {
        list = m_list;
        index = list->getIndex(false);
    } else {
        if (m_index >= m_list->getSize()) {
            info = MenuArtsInfo();
            return;
        }
        list = m_list;
        index = list->getPageIndex(m_index);
    }
    info = list->getContents(index);
}

unsigned int GfMenuArtsAdapter::ListConverter::getDriverId() {
    return m_driverId;
}

GfMenuArtsAdapter::ListReferenceDriverConverter::~ListReferenceDriverConverter() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

void GfMenuArtsAdapter::ListReferenceDriverConverter::getArtsInfo(MenuArtsInfo& info) {
    GfMenuArtsList* list;
    unsigned int index;
    if (m_index == -1) {
        list = m_list;
        index = list->getIndex(false);
    } else {
        if (m_index >= m_list->getSize()) {
            info = MenuArtsInfo();
            return;
        }
        list = m_list;
        index = list->getPageIndex(m_index);
    }
    info = list->getContents(index);
}

unsigned int GfMenuArtsAdapter::ListReferenceDriverConverter::getDriverId() {
    return GfMenuReference::getReferenceDriverID(m_reference);
}

GfMenuArtsAdapter::ListReferenceDriverConverterReferenceIndex::~ListReferenceDriverConverterReferenceIndex() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
    m_index = nullptr;
}

void GfMenuArtsAdapter::ListReferenceDriverConverterReferenceIndex::getArtsInfo(MenuArtsInfo& info) {
    if (m_index->m_value == -1) {
        GfMenuArtsList* list = m_list;
        info = list->getContents(list->getIndex(false));
    } else {
        if (m_index->m_value >= m_list->getSize()) {
            info.m_artsId = 0;
            return;
        }
        GfMenuArtsList* list = m_list;
        info = list->getContents(list->getPageIndex(m_index->m_value));
    }
}

unsigned int GfMenuArtsAdapter::ListReferenceDriverConverterReferenceIndex::getDriverId() {
    return GfMenuReference::getReferenceDriverID(m_reference);
}

}  // namespace gf
