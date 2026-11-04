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
    {&GfMenuBattleAdapter::update_ChainAttackOverkillBonus, {0, 0, 9999}},
    {&GfMenuBattleAdapter::update_ChainAttackExpBonus, {0, 0, 999}},
    {&GfMenuBattleAdapter::update_ChainAttackTotalDamage, {0, 0, 9999999}},
    {&GfMenuBattleAdapter::update_ChainAttackBurstCount, {0, 0, 99}},
    {&GfMenuBattleAdapter::update_AwakeningRestTime, {0, 0, 100}},
    {&GfMenuBattleAdapter::update_ElemComboEffTime, {0, 0, 100}},
    {&GfMenuBattleAdapter::update_ArtsRange, {3, 0, 0}},
    {&GfMenuBattleAdapter::update_ReverseIconCol, {8, 0, 0}},
    {&GfMenuBattleAdapter::update_BattleTime, {7, 4, 0}},
    {&GfMenuBattleAdapter::update_BtlChEther, {0, 0, 99999}},
    {&GfMenuBattleAdapter::update_BtlChScore, {0, 0, 99999}},
    {&GfMenuBattleAdapter::update_BtlChScoreNeed, {0, 0, 99999}},
    {&GfMenuBattleAdapter::update_BtlChBoxRate, {0, 0, 100}},
    {&GfMenuBattleAdapter::update_VisionTimeRatio, {0, 0, 100}},
    {&GfMenuBattleAdapter::update_IraSpecialRecast, {0, 0, 100}},
    {&GfMenuBattleAdapter::update_IraSpecialLv, {0, 0, 4}},
    {&GfMenuBattleAdapter::update_IraTalentArtsEnable, {3, 0, 0}},
    {&GfMenuBattleAdapter::update_IraSirenGaugeEN, {0, 0, 100}},
    {&GfMenuBattleAdapter::update_IraSirenLvPT, {0, 0, 5}},
    {&GfMenuBattleAdapter::update_IraSirenLvEN, {0, 0, 5}},
    {&GfMenuBattleAdapter::update_IraChainDrFace, {1, 0, 0}},
    {&GfMenuBattleAdapter::update_IraChainRecast, {0, 0, 100}},
    {&GfMenuBattleAdapter::update_IraChainDrName, {2, 0, 0}},
    {&GfMenuBattleAdapter::update_IraChainDrElem, {1, 0, 0}},
    {&GfMenuBattleAdapter::update_OCGGearCount, {0, 0, 999}},
    {&GfMenuBattleAdapter::update_OCGTimeRatio, {0, 0, 100}},
    {&GfMenuBattleAdapter::update_OCGBonus, {0, 0, 999}},
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

bool GfMenuBattleAdapter::update_ChainAttackOverkillBonus() {
    setNumber(GfMenuReference::getChainAttackOverkillBonus());
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
    if (m_index == 0 && GfMenuObjUtil::isValidExpansion(3)) {
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

bool GfMenuBattleAdapter::update_BtlChEther() {
    if (!GfGameManager::isBattleArenaActive()) {
        return false;
    }
    setNumber(GfGameManager::getBattleArenaMenuInfo()->m_value2C);
    return true;
}

bool GfMenuBattleAdapter::update_BtlChScore() {
    if (!GfGameManager::isBattleArenaActive()) {
        return false;
    }
    setNumber(GfGameManager::getBattleArenaMenuInfo()->m_value28);
    return true;
}

bool GfMenuBattleAdapter::update_BtlChScoreNeed() {
    if (!GfGameManager::isBattleArenaActive()) {
        return false;
    }
    setNumber(GfGameManager::getBattleArenaMenuInfo()->m_value1C);
    return true;
}

bool GfMenuBattleAdapter::update_BtlChBoxRate() {
    if (!GfGameManager::isBattleArenaActive()) {
        return false;
    }
    unsigned int index = m_index;
    GfGameManager::getBattleArenaMenuInfo();
    if (index < 3) {
        const GfGameManager::BattleChallengeRecord* record = GfGameManager::getBattleArenaMenuInfo();
        setNumber(record->m_ratios[m_index] * 100.0f);
        return true;
    }
    return false;
}

bool GfMenuBattleAdapter::update_VisionTimeRatio() {
    if (!GfMenuObjUtil::isValidExpansion(1)) {
        return false;
    }
    setNumber(GfMenuReference::getVisionTimeRatio() * 100.0f);
    return true;
}

bool GfMenuBattleAdapter::update_IraSpecialRecast() {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return false;
    }
    int number;
    int current = GfMenuReference::getIraSpecialArtsLv();
    if (m_index == current) {
        number = GfMenuReference::getIraSpecialArtsRecast() * 100.0f;
    } else if (m_index > current) {
        number = 0;
    } else {
        number = getNumberMax();
    }
    setNumber(number);
    return number > 0;
}

bool GfMenuBattleAdapter::update_IraSpecialLv() {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return false;
    }
    setNumber(GfMenuReference::getIraSpecialArtsLv());
    return true;
}

bool GfMenuBattleAdapter::update_IraTalentArtsEnable() {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return false;
    }
    return GfMenuReference::isIraFlag(3);
}

bool GfMenuBattleAdapter::update_IraSirenGaugeEN() {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return false;
    }
    setNumber(GfMenuReference::getIraSirenInfo(0)->m_ratio * 100.0f);
    return GfMenuReference::isIraFlag(4);
}

bool GfMenuBattleAdapter::update_IraSirenLvPT() {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return false;
    }
    setNumber(GfMenuReference::getIraSirenInfo(1)->m_count);
    return GfMenuReference::isIraFlag(4);
}

bool GfMenuBattleAdapter::update_IraSirenLvEN() {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return false;
    }
    setNumber(GfMenuReference::getIraSirenInfo(0)->m_count);
    return GfMenuReference::isIraFlag(4);
}

bool GfMenuBattleAdapter::update_IraChainDrFace() {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return false;
    }
    unsigned int id = GfMenuReference::getIraChainInfo(m_index)->m_gimmickId;
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

bool GfMenuBattleAdapter::update_IraChainRecast() {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return false;
    }
    const GfMenuReference::LayerGimmick* gimmick = GfMenuReference::getIraChainInfo(m_index);
    setNumber(gimmick->m_ratio * 100.0f);
    return gimmick->m_ratio > 0.0f;
}

bool GfMenuBattleAdapter::update_IraChainDrName() {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return false;
    }
    DataParamAcc acc(3, GfMenuReference::getIraChainInfo(m_index)->m_gimmickId, static_cast<GimmickType>(0));
    if (!acc.isValid()) {
        return false;
    }
    setText(GfMenuObjUtil::getName(acc));
    return true;
}

bool GfMenuBattleAdapter::update_IraChainDrElem() {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return false;
    }
    DataParamAcc acc(3, GfMenuReference::getIraChainInfo(m_index)->m_gimmickId, static_cast<GimmickType>(0));
    if (!acc.isValid()) {
        return false;
    }
    setNumber(GfMenuBdat::getIconImageIndex(static_cast<unsigned short>(acc.getAttribute(-1, false) + 158)));
    return true;
}

bool GfMenuBattleAdapter::update_OCGGearCount() {
    setNumber(GfMenuReference::getOCGInfo()->m_number);
    return true;
}

bool GfMenuBattleAdapter::update_OCGTimeRatio() {
    setNumber(GfMenuReference::getOCGInfo()->m_ratio * 100.0f);
    return true;
}

bool GfMenuBattleAdapter::update_OCGBonus() {
    const GfMenuReference::LayerResult* result = GfMenuReference::getOCGInfo();
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
