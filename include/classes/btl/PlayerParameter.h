#ifndef CLASSES_BTL_PLAYERPARAMETER_H
#define CLASSES_BTL_PLAYERPARAMETER_H

#include "classes/btl/CharacterParameter.h"

namespace btl { class GROUP_DATA; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace btl {
// table 0x7100B3B588
class PlayerParameter : public ::btl::CharacterParameter {
public:
    PlayerParameter();
    virtual void Initialize(gf::GF_OBJ_HANDLE*);  // slot 1
    virtual void InitializeArtsPalette(int);  // slot 2
    virtual void CheckChangeArtsPalette();  // slot 3
    virtual void BattleStart(int);  // slot 4
    virtual void BattleEnd();  // slot 5
    virtual void BattleEndInitialize();  // slot 6
    virtual void PreUpdate(fw::UpdateInfo const&);  // slot 7
    virtual void Update(fw::UpdateInfo const&, bool);  // slot 8
    virtual void UpdateBuddy();  // slot 10
    virtual int GetBladeIndex() const;  // slot 12
    virtual unsigned int GetWeaponID(int) const;  // slot 13
    virtual int GetEquipAccessory() const;  // slot 14
    virtual int GetIdeaLevel(int) const;  // slot 15
    virtual const ARTS_PALETTE_DATA* GetArtsPaletteDataConst(int) const;  // slot 16
    virtual int GetArtsPaletteNum() const;  // slot 17
    virtual void ResetRecast();  // slot 18
    virtual void WritebackRecast(btl::GROUP_DATA*);  // slot 19
    virtual bool InitializeEnhance() const;  // slot 21
    virtual bool IsPlayerParameter() const;  // slot 23
    virtual void StartMindEye();  // slot 43
    virtual void EndMindEye(bool);  // slot 44 (placeholder name: see CharacterParameter)
    virtual float GetMindEyeArtsSpeedRate() const;  // slot 45 (placeholder names: see CharacterParameter)
    virtual float GetMindEyeMoveSpeedRate() const;  // slot 46
    virtual float GetMindEyeAttackRate() const;  // slot 47
    virtual float GetMindEyeHateRate() const;  // slot 48
    virtual float GetMindEyeRestRate() const;  // slot 49
    virtual bool IsMindEye() const;  // slot 50
    virtual void ResetHanaBusterRebootTimer();  // slot 51 (placeholder name: see CharacterParameter)
    virtual void SetHanaBusterRebootTimer();  // slot 52
    virtual int IsHanaBusterReboot() const;  // slot 53
    virtual int GetIraDummyBladeID() const;  // slot 54
    virtual int GetBladeChangeType() const;  // slot 63
    virtual bool IsDriver(bool) const;  // slot 64
    virtual bool IsBlade(bool) const;  // slot 65 (placeholder name: see CharacterParameter)
    virtual bool IsApplyMapRev() const;  // slot 75 (placeholder name: see CharacterParameter)
    virtual void InitializeAttackParam();  // slot 79
    virtual unsigned int CalcDamageArmorEx(unsigned int);  // slot 80
    virtual ~PlayerParameter();  // slot 81

    unsigned char pad_624[0x4];
    // the palettes (array new; GetArtsPaletteDataConst indexes it, the destructor deletes it; the name is not the
    // original's)
    ARTS_PALETTE_DATA* m_artsPaletteData;
    // the armor CalcDamageArmorEx takes damage off (-1 after construction, Initialize and BattleEndInitialize;
    // BattleStart and CalcDamageArmorEx set it up from the pouch buff when negative); meaning unknown
    int pad_630;
    // a timer: slot 43 starts it at BtlSystemBalanceAccess's 0x10C, PreUpdate counts it down, slot 44 ends it,
    // GetMindEyeRestRate answers its share of the start value
    float pad_634;
    // a timer: slot 52 starts it, PreUpdate counts it down, slot 53 holds when it ran out; slot 51 clears it
    float pad_638;
    int pad_63c;  // BattleEnd clears it; slot 54 returns it when set; meaning unknown
    unsigned char m_artsPaletteNum;  // GetArtsPaletteNum (the name is not the original's)
    unsigned char m_bladeChangeType;  // GetBladeChangeType (the name is not the original's)
    unsigned char pad_642;  // whether the 0x634 timer runs (slots 43, 44; read as a byte); meaning unknown
    bool pad_643;  // returned by slot 75 (IsApplyMapRev); true after construction; meaning unknown
};
}  // namespace btl

#endif
