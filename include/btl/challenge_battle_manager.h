#ifndef BTL_CHALLENGE_BATTLE_MANAGER_H
#define BTL_CHALLENGE_BATTLE_MANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/mm/mtl/ReferenceObject.h"

// The class of application/BF2/battle/challenge_battle_manager.cpp. Nothing names it: the symbols leave its table
// (0x7100B3A9C8) and its singleton (0x7100B939B0) unnamed and 1.0.0 has no such file, so it is TUnk_B3A9C8 and its
// functions keep placeholder names (new in 3.0.1, nothing in 1.0.0's place names them).

namespace btl { class BattleCharacter; }

namespace btl {
// Placeholder name. A free function: btl::BattleManager::Initialize calls it after DataManager's create. What it
// does: allocates the unit's TUnk_B3A9C8 (the new cites "battle/challenge_battle_manager.cpp"), whose PtrSingleton
// constructor asserts get()==0.
void fn_71000254E4();
// Placeholder name. A free function: as fn_71000254E4. What it does: deletes that object; btl::BattleManager::Finalize
// calls it between BladeArtsManager::Destroy and DataManager's (the reverse of the create order).
void fn_7100025588();

// table 0x7100B3A9C8 (slot 0 its destructor, which only clears the singleton); 0x30 bytes (fn_71000254E4 allocates
// so many)
class TUnk_B3A9C8 : public ::mm::mtl::PtrSingleton< ::btl::TUnk_B3A9C8> {
public:
    TUnk_B3A9C8()
        : pad_8(nullptr), pad_10(0.0f), pad_14(0.0f), pad_18(0.0f), pad_1c(0.0f), pad_20(0), pad_22(0), pad_24(0),
          pad_26(0), pad_27(0), pad_28(0), pad_29(4), pad_2a(0), pad_2b(0), pad_2c(0), pad_2d(0) {}
    virtual ~TUnk_B3A9C8() {}  // slot 0

    // Placeholder names (members: they read this object's fields; their callers pass the singleton). What they do:
    // fn_710002567C: pad_26 != 0 (25 callers: BattleGlobal::PreUpdateProc, BattleManager::CheckBattle,
    //   Utility::IsEnableEventStart, ...)
    bool fn_710002567C() const;
    // fn_710002575C: TalkManager::PlayNarrationVoice(0x30, 0, 0), then pad_1c = 2.75
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because x0 is this class's
    // singleton (Utility's fn_710000FB3C/FB4C/FB5C pass TUnk_B3A9C8::sys()) and they read and reset its fields.
    // What they do: release pad_8 and reset pad_10..pad_2d (GfMenuReference::fn_71003673A8(0), DataManager's
    // SetPartyGauge(0, false), gf::TUnk_B60928::fn_71003B48B8); fn_71000255A8 only while pad_26 is 0 and then
    // loads pad_20/pad_22 from lbl_7100EB7DBC and sets pad_26; fn_710002568C only while pad_26 is set, clears it
    // and sets bit 15 of a halfword in each of DataManager's 18 entries; fn_710002579C only while pad_26 is set.
    void fn_71000255A8();
    void fn_710002568C();
    void fn_710002579C();
    void fn_710002575C();
    // fn_7100026A48 / fn_7100026A58: pad_26 above 149 / above 199
    bool fn_7100026A48() const;
    bool fn_7100026A58() const;
    // fn_7100026C18: pad_24 = value while pad_26 is set (EnemyParameter's SetupBGM passes its BGM id)
    void fn_7100026C18(unsigned short value);
    // fn_7100026C28: while pad_26 is set, fn_7100026CBC(BDAT 78's "Score" of id, false), then character's
    //   fn_710006C39C(id) when one is given (BattleCharacter::DeadProc, CharacterParameter::SetElementalComboID)
    void fn_7100026C28(int id, BattleCharacter* character);
    // fn_7100026CBC: while pad_26 is set, gf::fn_7100558D28(score) for a score, unless pad_29 is 2 or 3 and not
    //   always (BattleCharacter::DeadProc)
    void fn_7100026CBC(int score, bool always);
    // fn_7100026CF0: gf::fn_7100558BAC(value) for a value while pad_26 is set
    void fn_7100026CF0(int value);
    // fn_7100026D20: while pad_26 is 160, BtlSystemBalanceAccess's pad_120 less pad_18 (0 when not above 0, -1
    //   otherwise) and in *flag whether it is at most 5, or not above 0, or below 30% of pad_120
    float fn_7100026D20(bool* flag) const;
    // fn_7100026DAC: pad_26 is 201 and GfGameManager::isFadeout()
    bool fn_7100026DAC() const;
    // fn_7100026DDC: pad_26 in 100..149
    bool fn_7100026DDC() const;
    // fn_7100026DF0: false without pad_26; with pad_29 3 whether CharacterManager has no battle enemy, else
    //   fn_7100026DDC()
    bool fn_7100026DF0() const;
    // fn_7100026E4C: pad_26 in 157..161
    bool fn_7100026E4C() const;
    // fn_7100026E64 / fn_7100026E84 / fn_7100026EB0: true without pad_26; else pad_2b != 0 / pad_26 in 50..149 /
    //   pad_29 == 3
    bool fn_7100026E64() const;
    bool fn_7100026E84() const;
    bool fn_7100026EB0() const;

    ::mm::mtl::ReferenceObject* pad_8;  // released (and cleared) by fn_71000255A8/fn_710002568C/fn_710002579C
    float pad_10;
    float pad_14;
    float pad_18;
    float pad_1c;
    unsigned short pad_20;
    unsigned short pad_22;
    unsigned short pad_24;
    unsigned char pad_26;  // 0 while no challenge battle runs; most functions test it
    unsigned char pad_27;
    unsigned char pad_28;
    unsigned char pad_29;
    unsigned char pad_2a;
    unsigned char pad_2b;
    unsigned char pad_2c;
    unsigned char pad_2d;
};

// Placeholder name. A free function: it reads no TUnk_B3A9C8. What it does: BattleGlobal's pad_5c50
// (BattleCharacter::DropItem).
float fn_7100026D08();
}  // namespace btl

#endif
