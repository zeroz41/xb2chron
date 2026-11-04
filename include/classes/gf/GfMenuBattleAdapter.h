#ifndef CLASSES_GF_GFMENUBATTLEADAPTER_H
#define CLASSES_GF_GFMENUBATTLEADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "mm/mtl/Delegate.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }

namespace gf {
// table 0x7100B5A0A0; the battle display (arts palette, chain attack, party gauge)
class GfMenuBattleAdapter : public ::gf::GfMenuAdapter {
public:
    class ReferenceIndexConverter;
    // a display callback and the plugin create makes for it (the table at 0x7100B5A0C8, in create's type order)
    struct TypeSetup {
        bool (GfMenuBattleAdapter::*func)();
        GfMenuAdapter::PluginSetup plugin;
    };
    GfMenuBattleAdapter(ui::UIObjectPlugin* plugin)
        : GfMenuAdapter(plugin, true, true), m_index(0), m_update(), m_converter(nullptr) {}
    virtual ~GfMenuBattleAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    // a plugin of that type (an entry of its 0x20-byte table) on the handle, and an adapter for it (null without one)
    static GfMenuBattleAdapter* create(unsigned int handle, unsigned int type);
    bool update_ArtsSlotRecast();
    bool update_ArtsSlotIcon();
    bool update_ArtsSlotIconElem();
    bool update_ArtsSlotIconType();
    bool update_ArtsSlotIconEnhance();
    bool update_ArtsSlotIconReaction();
    bool update_ArtsSlotIconRange();
    bool update_ArtsSlotName();
    bool update_ArtsSlotInfo();
    bool update_ArtsFightComboIcon();
    bool update_ArtsSlotEnable();
    bool update_ChainCount();
    bool update_PartyGauge();
    bool update_PartyGaugeAll();
    bool update_ChainAttackRecast();
    bool update_ChainAttackCount();
    bool update_ChainAttackDamageRatio();
    // 2.0.0's symbols name it. What it does: sets the number to GfMenuReference::getChainAttackOverkillBonus()'s and
    // returns true.
    bool update_ChainAttackOverkillBonus();
    bool update_ChainAttackExpBonus();
    bool update_ChainAttackTotalDamage();
    bool update_ChainAttackBurstCount();
    bool update_AwakeningRestTime();
    bool update_ElemComboEffTime();
    bool update_ArtsRange();
    bool update_ReverseIconCol();
    // 2.0.0's symbols name them. What they do: update_BattleTime: a time plugin (seconds 4):
    // GfMenuReference::getBattleTime()'s seconds as minutes (max 99) and seconds;
    // update_BtlChEther/update_BtlChScore/update_BtlChScoreNeed: when isBattleArenaActive(), the int at 0x2C / int at
    // 0x28 / short at 0x1C of getBattleArenaMenuInfo()'s record (numbers 0..99999); update_BtlChBoxRate: when
    // isBattleArenaActive() and m_index < 3, the float at 0xAD0 + m_index*4 of that record, in percent;
    // update_VisionTimeRatio: on menu layer 1 (GfMenuObjUtil::isValidExpansion(1)),
    // GfMenuReference::getVisionTimeRatio() in percent;
    // update_IraSpecialRecast/update_IraSpecialLv/update_IraTalentArtsEnable/update_IraSirenGaugeEN/update_IraSirenLvPT/update_IraSirenLvEN:
    // on menu layer 3, values of GfMenuReference::getIraSpecialArtsLv/getIraSpecialArtsRecast/getIraSirenInfo and its
    // flags at 0x4CFA0 (bits 3, 4);
    // update_IraChainDrFace/update_IraChainRecast/update_IraChainDrName/update_IraChainDrElem: on menu layer 3, the
    // face icon, a float in percent, the name and the attribute icon of the gimmick
    // GfMenuReference::getIraChainInfo(m_index) names; update_OCGGearCount/update_OCGTimeRatio/update_OCGBonus: the int
    // at 0, the float at 4 (percent) and the int at 8 + m_index*4 (m_index < 3) of GfMenuReference::getOCGInfo()'s
    // record.
    bool update_BattleTime();
    bool update_BtlChEther();
    bool update_BtlChScore();
    bool update_BtlChScoreNeed();
    bool update_BtlChBoxRate();
    bool update_VisionTimeRatio();
    bool update_IraSpecialRecast();
    bool update_IraSpecialLv();
    bool update_IraTalentArtsEnable();
    bool update_IraSirenGaugeEN();
    bool update_IraSirenLvPT();
    bool update_IraSirenLvEN();
    bool update_IraChainDrFace();
    bool update_IraChainRecast();
    bool update_IraChainDrName();
    bool update_IraChainDrElem();
    bool update_OCGGearCount();
    bool update_OCGTimeRatio();
    bool update_OCGBonus();

    // which one of its kind it shows: create clears it, callers set it (GfMenuObjSpecialGauge's gauge levels),
    // the callbacks read it, update takes the converter's (the name is not the original's)
    int m_index;
    unsigned char pad_34[0x4];
    mm::mtl::Delegate<bool()> m_update;  // create's: the table entry's callback (the name is not the original's)
    // where update takes m_index from; the destructor deletes it (the name is not the original's)
    ReferenceIndexConverter* m_converter;
};
}  // namespace gf

#endif
