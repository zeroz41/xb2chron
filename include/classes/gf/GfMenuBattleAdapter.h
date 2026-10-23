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
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0 goes from
    // update_ChainAttackDamageRatio to update_ChainAttackExpBonus). A member because it is entry 17 of this class's
    // TypeSetup table (a number plugin 0..9999). What it does: sets the number to GfMenuReference::fn_7100367380()'s
    // and returns true.
    bool fn_71003331F8();
    bool update_ChainAttackExpBonus();
    bool update_ChainAttackTotalDamage();
    bool update_ChainAttackBurstCount();
    bool update_AwakeningRestTime();
    bool update_ElemComboEffTime();
    bool update_ArtsRange();
    bool update_ReverseIconCol();
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them (1.0.0's file ends its callbacks with
    // update_ReverseIconCol). Members because they are entries 25..43 of this class's TypeSetup table, read
    // m_index and call setNumber/setText/setTime on this. What they do:
    // fn_71003333D0: a time plugin (seconds 4): GfMenuReference::fn_71003673C8()'s seconds as minutes (max 99)
    //   and seconds;
    // fn_7100333434/fn_7100333474/fn_71003334B4: when fn_71002AC580(), the int at 0x2C / int at 0x28 / short at
    //   0x1C of fn_71002AC5D8()'s record (numbers 0..99999);
    // fn_71003334F4: when fn_71002AC580() and m_index < 3, the float at 0xAD0 + m_index*4 of that record, in percent;
    // fn_710033355C: on menu layer 1 (GfMenuObjUtil::fn_710048FD30(1)), GfMenuReference::fn_710036742C() in percent;
    // fn_71003335AC/fn_7100333630/fn_7100333674/fn_71003336A0/fn_7100333700/fn_7100333750: on menu layer 3, values
    //   of GfMenuReference::fn_710036805C/fn_7100367FDC/fn_71003686A0 and its flags at 0x4CFA0 (bits 3, 4);
    // fn_71003337A0/fn_710033383C/fn_71003338A0/fn_7100333934: on menu layer 3, the face icon, a float in percent,
    //   the name and the attribute icon of the gimmick GfMenuReference::fn_71003687B0(m_index) names;
    // fn_71003339D0/fn_7100333A00/fn_7100333A40: the int at 0, the float at 4 (percent) and the int at
    //   8 + m_index*4 (m_index < 3) of GfMenuReference::fn_7100368B40()'s record.
    bool fn_71003333D0();
    bool fn_7100333434();
    bool fn_7100333474();
    bool fn_71003334B4();
    bool fn_71003334F4();
    bool fn_710033355C();
    bool fn_71003335AC();
    bool fn_7100333630();
    bool fn_7100333674();
    bool fn_71003336A0();
    bool fn_7100333700();
    bool fn_7100333750();
    bool fn_71003337A0();
    bool fn_710033383C();
    bool fn_71003338A0();
    bool fn_7100333934();
    bool fn_71003339D0();
    bool fn_7100333A00();
    bool fn_7100333A40();

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
