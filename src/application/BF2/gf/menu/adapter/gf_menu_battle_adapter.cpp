#include "classes/btl/DataManager.h"
#include "classes/gf/GfMenuBattleAdapter.h"
#include "btl/Utility.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/DataParamAcc.h"
#include "ui/uiDateTime.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfGameParty.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfDataDriverArts.h"
#include "classes/gf/GfMenuBattleAdapter/ReferenceIndexConverter.h"
#include "classes/gf/GfMenuManager.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/UIStr.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"

namespace gf {

// Display callback and plugin settings for each adapter type, in create's index order.
static GfMenuBattleAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuBattleAdapter::update_ArtsSlotRecast, {0, 0, 100}},
    {&GfMenuBattleAdapter::update_ArtsSlotIcon, {1, 0, 0}},
    {&GfMenuBattleAdapter::update_ArtsSlotIconElem, {8, 0, 0}},
    {&GfMenuBattleAdapter::update_ArtsSlotIconType, {1, 0, 0}},
    {&GfMenuBattleAdapter::update_ArtsSlotIconEnhance, {1, 0, 0}},
    {&GfMenuBattleAdapter::update_ArtsSlotIconReaction, {1, 0, 0}},
    {&GfMenuBattleAdapter::update_ArtsSlotIconRange, {1, 0, 0}},
    {&GfMenuBattleAdapter::update_ArtsSlotName, {2, 0, 0}},
    {&GfMenuBattleAdapter::update_ArtsSlotInfo, {2, 0, 0}},
    {&GfMenuBattleAdapter::update_ArtsFightComboIcon, {1, 0, 0}},
    {&GfMenuBattleAdapter::update_ArtsSlotEnable, {3, 0, 0}},
    {&GfMenuBattleAdapter::update_ChainCount, {0, 0, 99}},
    {&GfMenuBattleAdapter::update_PartyGauge, {0, 0, 100}},
    {&GfMenuBattleAdapter::update_PartyGaugeAll, {0, 0, 100}},
    {&GfMenuBattleAdapter::update_ChainAttackRecast, {0, 0, 100}},
    {&GfMenuBattleAdapter::update_ChainAttackCount, {0, 0, 99}},
    {&GfMenuBattleAdapter::update_ChainAttackDamageRatio, {0, 0, 9999}},
    {&GfMenuBattleAdapter::fn_71003331F8, {0, 0, 9999}},
    {&GfMenuBattleAdapter::update_ChainAttackExpBonus, {0, 0, 999}},
    {&GfMenuBattleAdapter::update_ChainAttackTotalDamage, {0, 0, 9999999}},
    {&GfMenuBattleAdapter::update_ChainAttackBurstCount, {0, 0, 99}},
    {&GfMenuBattleAdapter::update_AwakeningRestTime, {0, 0, 100}},
    {&GfMenuBattleAdapter::update_ElemComboEffTime, {0, 0, 100}},
    {&GfMenuBattleAdapter::update_ArtsRange, {3, 0, 0}},
    {&GfMenuBattleAdapter::update_ReverseIconCol, {8, 0, 0}},
    {&GfMenuBattleAdapter::fn_71003333D0, {7, 4, 0}},
    {&GfMenuBattleAdapter::fn_7100333434, {0, 0, 99999}},
    {&GfMenuBattleAdapter::fn_7100333474, {0, 0, 99999}},
    {&GfMenuBattleAdapter::fn_71003334B4, {0, 0, 99999}},
    {&GfMenuBattleAdapter::fn_71003334F4, {0, 0, 100}},
    {&GfMenuBattleAdapter::fn_710033355C, {0, 0, 100}},
    {&GfMenuBattleAdapter::fn_71003335AC, {0, 0, 100}},
    {&GfMenuBattleAdapter::fn_7100333630, {0, 0, 4}},
    {&GfMenuBattleAdapter::fn_7100333674, {3, 0, 0}},
    {&GfMenuBattleAdapter::fn_71003336A0, {0, 0, 100}},
    {&GfMenuBattleAdapter::fn_7100333700, {0, 0, 5}},
    {&GfMenuBattleAdapter::fn_7100333750, {0, 0, 5}},
    {&GfMenuBattleAdapter::fn_71003337A0, {1, 0, 0}},
    {&GfMenuBattleAdapter::fn_710033383C, {0, 0, 100}},
    {&GfMenuBattleAdapter::fn_71003338A0, {2, 0, 0}},
    {&GfMenuBattleAdapter::fn_7100333934, {1, 0, 0}},
    {&GfMenuBattleAdapter::fn_71003339D0, {0, 0, 999}},
    {&GfMenuBattleAdapter::fn_7100333A00, {0, 0, 100}},
    {&GfMenuBattleAdapter::fn_7100333A40, {0, 0, 999}},
};

GfMenuBattleAdapter::~GfMenuBattleAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuBattleAdapter* GfMenuBattleAdapter::create(unsigned int handle, unsigned int type) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object == nullptr) {
        return nullptr;
    }
    const TypeSetup& setup = s_typeSetups[type];
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup.plugin);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 155
    GfMenuBattleAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuBattleAdapter(plugin);
    adapter->m_update.set(adapter, setup.func);
    plugin->release();
    return adapter;
}

bool GfMenuBattleAdapter::update_ArtsSlotRecast() {
    const GfMenuReference::ArtsPaletteInfo* info = GfMenuReference::getArtsPaletteInfo(m_index);
    setNumber(info->m_recast * 100.0f);
    return info->m_recast > 0.0f;
}

bool GfMenuBattleAdapter::update_ArtsSlotIcon() {
    unsigned short arts = GfMenuReference::getArtsPaletteInfo(m_index)->m_artsId;
    if (arts != 0) {
        unsigned short icon = GfMenuBdat::getIconIDFromArtsID(arts);
        setNumber(GfMenuBdat::getIconImageIndex(icon));
    }
    return arts != 0;
}

bool GfMenuBattleAdapter::update_ArtsSlotIconElem() {
    unsigned short arts = GfMenuReference::getArtsPaletteInfo(m_index)->m_artsId;
    if (arts != 0) {
        mm::mtl::FixStr<32> color;
        color.format("elemental%02d", GfMenuReference::getArtsPaletteElementType(m_index));
        setMulColor(color.m_str);
    }
    return arts != 0;
}

bool GfMenuBattleAdapter::update_ArtsSlotIconType() {
    unsigned short arts = GfMenuReference::getArtsPaletteInfo(m_index)->m_artsId;
    if (arts != 0) {
        setNumber(GfMenuReference::getArtsPaletteIconInfo(m_index)->m_type);
    }
    return arts != 0;
}

bool GfMenuBattleAdapter::update_ArtsSlotIconEnhance() {
    unsigned short arts = GfMenuReference::getArtsPaletteInfo(m_index)->m_artsId;
    if (arts != 0) {
        setNumber(GfMenuReference::getArtsPaletteIconInfo(m_index)->m_enhance);
    }
    return arts != 0;
}

bool GfMenuBattleAdapter::update_ArtsSlotIconReaction() {
    unsigned short arts = GfMenuReference::getArtsPaletteInfo(m_index)->m_artsId;
    if (arts != 0) {
        setNumber(GfMenuReference::getArtsPaletteIconInfo(m_index)->m_reaction);
    }
    return arts != 0;
}

bool GfMenuBattleAdapter::update_ArtsSlotIconRange() {
    unsigned short arts = GfMenuReference::getArtsPaletteInfo(m_index)->m_artsId;
    if (arts != 0) {
        setNumber(GfMenuReference::getArtsPaletteIconInfo(m_index)->m_range);
    }
    return arts != 0;
}

bool GfMenuBattleAdapter::update_ArtsSlotName() {
    const GfMenuReference::ArtsPaletteInfo* info = GfMenuReference::getArtsPaletteInfo(m_index);
    unsigned short arts = info->m_artsId;
    if (arts != 0) {
        ui::UIStr text(GfDataDriverArts::getNameFP(), GfDataDriverArts::getNameID(info->m_artsId));
        setText(text);
    }
    return arts != 0;
}

bool GfMenuBattleAdapter::update_ArtsSlotInfo() {
    const GfMenuReference::ArtsPaletteInfo* info = GfMenuReference::getArtsPaletteInfo(m_index);
    unsigned short arts = info->m_artsId;
    if (arts != 0) {
        ui::UIStr text(GfDataDriverArts::getCaptionFP(), GfDataDriverArts::getCaptionID(info->m_artsId));
        setText(text);
    }
    return arts != 0;
}

bool GfMenuBattleAdapter::update_ArtsFightComboIcon() {
    const GfMenuReference::ArtsPaletteInfo* info = GfMenuReference::getArtsPaletteInfo(m_index);
    btl::ARTS_DATA data;
    unsigned short arts = info->m_artsId;
    if (arts == 0) {
        return false;
    }
    btl::Utility::GetArtsData(static_cast<btl::ARTS_DATA::DATA_TYPE>(0), arts, data);
    if (data.m_fightCombo == 0) {
        return false;
    }
    setNumber(data.m_fightCombo - 1);
    return true;
}

bool GfMenuBattleAdapter::update_ChainCount() {
    setNumber(GfMenuReference::getChainNum());
    return true;
}

bool GfMenuBattleAdapter::update_PartyGauge() {
    int gauge = GfGameParty::getPartyGauge() - m_index * 100;
    setNumber(gauge < 0 ? 0 : (gauge > 100 ? 100 : gauge));
    return true;
}

bool GfMenuBattleAdapter::update_PartyGaugeAll() {
    unsigned short gauge = GfGameParty::getPartyGauge();
    if (gauge != 0) {
        setNumber(gauge / 300.0f * 100.0f);
        return true;
    }
    setNumber(0);
    return false;
}

bool GfMenuBattleAdapter::update_ChainAttackRecast() {
    setNumber(GfMenuReference::getChainAttackActionRecast() * 100.0f);
    return true;
}

bool GfMenuBattleAdapter::update_ChainAttackCount() {
    setNumber(GfMenuReference::getChainAttackActionCount());
    return true;
}

bool GfMenuBattleAdapter::update_ChainAttackDamageRatio() {
    setNumber(GfMenuReference::getChainAttackDamageRatio() * 100.0f);
    return true;
}

bool GfMenuBattleAdapter::fn_71003331F8() {
    setNumber(GfMenuReference::fn_7100367380());
    return true;
}

bool GfMenuBattleAdapter::update_ChainAttackExpBonus() {
    setNumber(GfMenuReference::getChainAttackExpRatio() * 100.0f);
    return true;
}

bool GfMenuBattleAdapter::update_ChainAttackTotalDamage() {
    setNumber(GfMenuReference::getChainAttackTotalDamage());
    return true;
}

bool GfMenuBattleAdapter::update_ChainAttackBurstCount() {
    setNumber(GfMenuReference::getChainAttackBurstCount());
    return true;
}

bool GfMenuBattleAdapter::update_AwakeningRestTime() {
    setNumber(GfMenuReference::getAwakeningRestTimeRatio() * 100.0f);
    return true;
}

bool GfMenuBattleAdapter::update_ElemComboEffTime() {
    if (GfMenuReference::getElementComboParty(m_index) == 0) {
        return false;
    }
    setNumber(GfMenuReference::getElementComboPartyTimeLeft(m_index) * 100.0f);
    return true;
}

bool GfMenuBattleAdapter::update_ArtsRange() {
    return GfMenuReference::isWeaponJustRange();
}

bool GfMenuBattleAdapter::update_ReverseIconCol() {
    if (m_index == 0 && GfMenuObjUtil::fn_710048FD30(3)) {
        return false;
    }
    if (!GfMenuReference::isReversePaletteBtnState(m_index, 0)) {
        return false;
    }
    if (GfMenuReference::isReversePaletteBtnState(m_index, 1)) {
        setColor("white");
    } else {
        setColor("gray");
    }
    return true;
}

bool GfMenuBattleAdapter::fn_7100333434() {
    if (!GfGameManager::fn_71002AC580()) {
        return false;
    }
    setNumber(GfGameManager::fn_71002AC5D8()->m_value2C);
    return true;
}

bool GfMenuBattleAdapter::fn_7100333474() {
    if (!GfGameManager::fn_71002AC580()) {
        return false;
    }
    setNumber(GfGameManager::fn_71002AC5D8()->m_value28);
    return true;
}

bool GfMenuBattleAdapter::fn_71003334B4() {
    if (!GfGameManager::fn_71002AC580()) {
        return false;
    }
    setNumber(GfGameManager::fn_71002AC5D8()->m_value1C);
    return true;
}

bool GfMenuBattleAdapter::fn_71003334F4() {
    if (!GfGameManager::fn_71002AC580()) {
        return false;
    }
    unsigned int index = m_index;
    GfGameManager::fn_71002AC5D8();
    if (index < 3) {
        const GfGameManager::BattleChallengeRecord* record = GfGameManager::fn_71002AC5D8();
        setNumber(record->m_ratios[m_index] * 100.0f);
        return true;
    }
    return false;
}

bool GfMenuBattleAdapter::fn_710033355C() {
    if (!GfMenuObjUtil::fn_710048FD30(1)) {
        return false;
    }
    setNumber(GfMenuReference::fn_710036742C() * 100.0f);
    return true;
}

bool GfMenuBattleAdapter::fn_71003335AC() {
    if (!GfMenuObjUtil::fn_710048FD30(3)) {
        return false;
    }
    int number;
    int current = GfMenuReference::fn_710036805C();
    if (m_index == current) {
        number = GfMenuReference::fn_7100367FDC() * 100.0f;
    } else if (m_index > current) {
        number = 0;
    } else {
        number = getNumberMax();
    }
    setNumber(number);
    return number > 0;
}

bool GfMenuBattleAdapter::fn_7100333630() {
    if (!GfMenuObjUtil::fn_710048FD30(3)) {
        return false;
    }
    setNumber(GfMenuReference::fn_710036805C());
    return true;
}

bool GfMenuBattleAdapter::fn_7100333674() {
    if (!GfMenuObjUtil::fn_710048FD30(3)) {
        return false;
    }
    return GfMenuReference::fn_7100368418(3);
}

bool GfMenuBattleAdapter::fn_71003336A0() {
    if (!GfMenuObjUtil::fn_710048FD30(3)) {
        return false;
    }
    setNumber(GfMenuReference::fn_71003686A0(0)->m_ratio * 100.0f);
    return GfMenuReference::fn_7100368418(4);
}

bool GfMenuBattleAdapter::fn_7100333700() {
    if (!GfMenuObjUtil::fn_710048FD30(3)) {
        return false;
    }
    setNumber(GfMenuReference::fn_71003686A0(1)->m_count);
    return GfMenuReference::fn_7100368418(4);
}

bool GfMenuBattleAdapter::fn_7100333750() {
    if (!GfMenuObjUtil::fn_710048FD30(3)) {
        return false;
    }
    setNumber(GfMenuReference::fn_71003686A0(0)->m_count);
    return GfMenuReference::fn_7100368418(4);
}

bool GfMenuBattleAdapter::fn_71003337A0() {
    if (!GfMenuObjUtil::fn_710048FD30(3)) {
        return false;
    }
    unsigned int id = GfMenuReference::fn_71003687B0(m_index)->m_gimmickId;
    if (id == 0) {
        return false;
    }
    DataParamAcc acc(3, id, static_cast<GimmickType>(0));
    if (!acc.isValid()) {
        return false;
    }
    int face = GfMenuObjUtil::getFaceIconID(acc);
    if (face == 0) {
        return false;
    }
    setNumber(GfMenuBdat::getIconImageIndex(face));
    return true;
}

bool GfMenuBattleAdapter::fn_710033383C() {
    if (!GfMenuObjUtil::fn_710048FD30(3)) {
        return false;
    }
    const GfMenuReference::LayerGimmick* gimmick = GfMenuReference::fn_71003687B0(m_index);
    setNumber(gimmick->m_ratio * 100.0f);
    return gimmick->m_ratio > 0.0f;
}

bool GfMenuBattleAdapter::fn_71003338A0() {
    if (!GfMenuObjUtil::fn_710048FD30(3)) {
        return false;
    }
    DataParamAcc acc(3, GfMenuReference::fn_71003687B0(m_index)->m_gimmickId, static_cast<GimmickType>(0));
    if (!acc.isValid()) {
        return false;
    }
    setText(GfMenuObjUtil::getName(acc));
    return true;
}

bool GfMenuBattleAdapter::fn_7100333934() {
    if (!GfMenuObjUtil::fn_710048FD30(3)) {
        return false;
    }
    DataParamAcc acc(3, GfMenuReference::fn_71003687B0(m_index)->m_gimmickId, static_cast<GimmickType>(0));
    if (!acc.isValid()) {
        return false;
    }
    setNumber(GfMenuBdat::getIconImageIndex(static_cast<unsigned short>(acc.getAttribute(-1, false) + 158)));
    return true;
}

bool GfMenuBattleAdapter::fn_71003339D0() {
    setNumber(GfMenuReference::fn_7100368B40()->m_number);
    return true;
}

bool GfMenuBattleAdapter::fn_7100333A00() {
    setNumber(GfMenuReference::fn_7100368B40()->m_ratio * 100.0f);
    return true;
}

bool GfMenuBattleAdapter::fn_7100333A40() {
    const GfMenuReference::LayerResult* result = GfMenuReference::fn_7100368B40();
    setNumber(static_cast<unsigned int>(m_index) < 3 ? result->m_numbers[m_index] : 0);
    return true;
}

void GfMenuBattleAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        int index = 0;
        m_converter->getIndex(index);
        if (m_index != index) {
            m_index = index;
            setChange();
        }
    }
    if (m_update.isValid() && (m_flags & 3) != 0 &&
        (GfMenuManager::isBattleState(0) || GfMenuManager::isBattleState(1))) {
        if (m_index < 0) {
            setDisp(false);
        } else {
            setDisp(m_update());
        }
        m_flags &= ~1;
    }
}

}  // namespace gf
