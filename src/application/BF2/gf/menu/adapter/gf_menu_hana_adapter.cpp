#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuHanaAdapter.h"
#include "classes/gf/GfMenuHanaAdapter/IConverter.h"
#include "classes/gf/GfMenuHanaAdapter/ReferenceIndexConverter.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "gf/GfDataHana.h"
#include "gf/GfGameUtilHana.h"
#include "gf/GfItemUtil.h"
#include "gf/GfMenuItemUtil.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"

namespace gf {

// per type: the update_* update shows and the plugin create makes (number up to 999999999, 9999 or 20, text, image
// index, colour)
static GfMenuHanaAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuHanaAdapter::update_ether, {0, 0, 999999999}},
    {&GfMenuHanaAdapter::update_equipPower, {0, 0, 9999}},
    {&GfMenuHanaAdapter::update_maxPower, {0, 0, 9999}},
    {&GfMenuHanaAdapter::update_roleText, {2, 0, 0}},
    {&GfMenuHanaAdapter::update_atrText, {2, 0, 0}},
    {&GfMenuHanaAdapter::update_atrIcon, {1, 0, 0}},
    {&GfMenuHanaAdapter::update_bustupIcon, {1, 0, 0}},
    {&GfMenuHanaAdapter::update_equipIcon, {1, 0, 0}},
    {&GfMenuHanaAdapter::update_rankPower, {0, 0, 20}},
    {&GfMenuHanaAdapter::update_maxRankPower, {0, 0, 20}},
    {&GfMenuHanaAdapter::update_partsExpandIcon, {1, 0, 0}},
    {&GfMenuHanaAdapter::update_equipColor, {8, 0, 0}},
};

// the sort table id of each part slot's parts, and of the parts each slot makes; the names are not the original's
static const struct {
    unsigned int m_partsId;
    unsigned int m_sortTableId;
} s_sortTableIds[] = {
    {1, 0x12}, {2, 0x13}, {3, 0x14}, {4, 0x14}, {5, 0x14}, {6, 0x15}, {7, 0x15},
    {8, 0x15}, {9, 0x16}, {10, 0x16}, {11, 0x16}, {12, 0x15}, {13, 0x15}, {14, 0x15},
}, s_makeSortTableIds[] = {
    {1, 0x17}, {2, 0x18}, {3, 0x19}, {6, 0x1A}, {9, 0x1B},
};

GfMenuHanaAdapter::~GfMenuHanaAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuHanaAdapter* GfMenuHanaAdapter::create(unsigned int handle, unsigned int type, unsigned int hanaId,
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
#line 120
    GfMenuHanaAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuHanaAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_hanaId = hanaId;
    plugin->release();
    return adapter;
}

bool GfMenuHanaAdapter::update_ether() {
    setNumber(GfDataHana::getEther());
    return true;
}

bool GfMenuHanaAdapter::update_equipPower() {
    setNumber(GfDataHana::getEquipPower(m_hanaId));
    setNumberMax(GfDataHana::getPowerCapacity(m_hanaId));
    return true;
}

bool GfMenuHanaAdapter::update_maxPower() {
    setNumber(GfDataHana::getPowerCapacity(m_hanaId));
    return true;
}

bool GfMenuHanaAdapter::update_roleText() {
    unsigned int role = GfDataHana::getRole(m_hanaId);
    if (role == 0) {
        return false;
    }
    ui::UIStr text(GfDataBdat::getFP(0x115), role);
    setText(text);
    return true;
}

bool GfMenuHanaAdapter::update_atrText() {
    int attribute = GfDataHana::getAttribute(m_hanaId);
    ui::UIStr text(GfDataBdat::getFP(0x114), attribute + 1);
    setText(text);
    return true;
}

bool GfMenuHanaAdapter::update_atrIcon() {
    setNumber(GfDataHana::getAttribute(m_hanaId));
    return true;
}

bool GfMenuHanaAdapter::update_bustupIcon() {
    if (m_hanaId - 1005 < 3) {
        setNumber(m_hanaId - 1004);
        return true;
    }
    return false;
}

bool GfMenuHanaAdapter::update_equipIcon() {
    if (m_partsId == 0) {
        return false;
    }
    setNumber((unsigned short)Bdat::getVal(GfDataBdat::getFP(0x17C), "icon", m_partsId));
    return true;
}

bool GfMenuHanaAdapter::update_rankPower() {
    setNumber(GfGameUtilHana::getPowerRank(m_hanaId));
    return true;
}

bool GfMenuHanaAdapter::update_maxRankPower() {
    setNumber(20);
    return true;
}

// update_partsExpandIcon: not identical yet (it inlines isOpenCircuit: the original
// branches to set 0/1 where ours selects)

bool GfMenuHanaAdapter::update_equipColor() {
    if (m_partsId == 0) {
        return false;
    }
    if (getEquipParts(m_hanaId, m_partsId) != 0 || m_partsId == 15) {
        setMulColor("hana_parts_icon");
    } else {
        setMulColor("hana_parts_icon_disable");
    }
    return true;
}

GfMenuHanaAdapter* GfMenuHanaAdapter::createFromCoverter(unsigned int handle, unsigned int type,
                                                         IConverter* converter, bool changed) {
    GfMenuHanaAdapter* adapter = create(handle, type, converter->getHanaId(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

GfMenuHanaAdapter* GfMenuHanaAdapter::createFromReferenceIndex(unsigned int handle, unsigned int type,
                                                               unsigned int index, bool changed) {
    if (handle == 0) {
        return nullptr;
    }
#line 138
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReferenceIndexConverter(index);
    return createFromCoverter(handle, type, converter, changed);
}

void GfMenuHanaAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        unsigned int hanaId = m_converter->getHanaId();
        if (m_hanaId != hanaId) {
            m_hanaId = hanaId;
            setChange();
        }
    }
    if (m_update.isValid() && (m_flags & 3) != 0) {
        setDisp(m_update());
        m_flags &= ~1;
    }
}

// isOpenCircuit: not identical yet (flow identical; the original branches on the
// result where ours uses cset)

unsigned int GfMenuHanaAdapter::getEquipParts(unsigned int hana, unsigned int partsId) {
    EquipHana equip;
    GfGameUtilHana::getEquip(equip, hana);
    switch (partsId) {
    case 1:
        return equip.m_roleParts;
    case 2:
        return equip.m_attributeParts;
    case 3:
    case 4:
    case 5:
        return equip.m_nArtsParts[partsId - 3].m_item;
    case 6:
    case 7:
    case 8:
        return equip.m_condenserParts[partsId - 6];
    case 9:
    case 10:
    case 11:
        return equip.m_artsParts[partsId - 9].m_item;
    case 12:
    case 13:
    case 14:
        return (&equip.m_condenserParts[3])[partsId - 12];
    }
    return 0;
}

bool GfMenuHanaAdapter::isEquipParts(unsigned int hana, unsigned int partsId, unsigned int item, RESULT_HANA& result) {
    switch (partsId) {
    case 1:
        result = GfGameUtilHana::isEnableEquipRoleParts(hana, item);
        break;
    case 2:
        result = GfGameUtilHana::isEnableEquipAttributeParts(hana, item);
        break;
    case 3:
    case 4:
    case 5:
        result = GfGameUtilHana::isEnableEquipNArtsParts(hana, item, partsId - 3);
        break;
    case 6:
    case 7:
    case 8:
        result = GfGameUtilHana::isEnableEquipCondenserParts(hana, item, partsId - 6);
        break;
    case 9:
    case 10:
    case 11:
        result = GfGameUtilHana::isEnableEquipArtsParts(hana, item, partsId - 9);
        break;
    case 12:
    case 13:
    case 14:
        result = GfGameUtilHana::isEnableEquipExtendCondenserParts(hana, item, partsId - 12);
        break;
    default:
        return false;
    }
    int count = GfItemUtil::getItemBoxCount(item);
    if (count == 0) {
        result = RESULT_HANA(8);
    }
    if (GfMenuItemUtil::fn_71003547CC(item, hana)) {
        // the condenser slots: another one with a part bound to Hana gives 14
        static const unsigned int slots[] = {6, 7, 8, 12, 13, 14};
        for (unsigned int i = 0; i < sizeof(slots) / sizeof(slots[0]); i++) {
            if (slots[i] != partsId) {
                unsigned int parts = getEquipParts(hana, slots[i]);
                if (parts != 0 && GfMenuItemUtil::fn_71003547CC(parts, hana)) {
                    result = RESULT_HANA(14);
                }
            }
        }
    }
    return result == 0 && count != 0;
}

// isMakeParts: not identical yet (the default case's false is materialized in
// its own block in the original)

bool GfMenuHanaAdapter::isCrystalParts(unsigned int partsId, unsigned int item, RESULT_HANA& result) {
    result = RESULT_HANA(0);
    return true;
}

// getHanaCount: not identical yet (the original tests the vectors' sizes before
// pointer loops)

unsigned int GfMenuHanaAdapter::getSortTableId(unsigned int partsId) {
    for (unsigned int i = 0; i < sizeof(s_sortTableIds) / sizeof(s_sortTableIds[0]); i++) {
        if (s_sortTableIds[i].m_partsId == partsId) {
            return s_sortTableIds[i].m_sortTableId;
        }
    }
    return 0;
}

unsigned int GfMenuHanaAdapter::getMakeSortTableId(unsigned int partsId) {
    for (unsigned int i = 0; i < sizeof(s_makeSortTableIds) / sizeof(s_makeSortTableIds[0]); i++) {
        if (s_makeSortTableIds[i].m_partsId == partsId) {
            return s_makeSortTableIds[i].m_sortTableId;
        }
    }
    return 0;
}

}  // namespace gf
