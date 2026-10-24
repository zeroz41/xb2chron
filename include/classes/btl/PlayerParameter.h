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
    virtual void Initialize(gf::GF_OBJ_HANDLE*);  // slot 1
    virtual void InitializeArtsPalette(int);  // slot 2
    virtual void vf3();  // slot 3
    virtual void vf4();  // slot 4
    virtual void BattleEnd();  // slot 5
    virtual void vf6();  // slot 6
    virtual void vf7();  // slot 7
    virtual void Update(fw::UpdateInfo const&, bool);  // slot 8
    virtual void vf10();  // slot 10
    virtual void GetBladeIndex() const;  // slot 12
    virtual unsigned int GetWeaponID(int) const;  // slot 13
    virtual void GetEquipAccessory() const;  // slot 14
    virtual void GetIdeaLevel(int) const;  // slot 15
    virtual void vf16();  // slot 16
    virtual void GetArtsPaletteNum() const;  // slot 17
    virtual void ResetRecast();  // slot 18
    virtual void WritebackRecast(btl::GROUP_DATA*);  // slot 19
    virtual void InitializeEnhance() const;  // slot 21
    virtual void vf23();  // slot 23
    virtual void vf43();  // slot 43
    virtual void vf44();  // slot 44
    virtual void vf45();  // slot 45
    virtual void vf46();  // slot 46
    virtual void vf47();  // slot 47
    virtual void vf48();  // slot 48
    virtual void GetUseWeaponRate(int) const;  // slot 49
    virtual void vf50();  // slot 50
    virtual void vf51();  // slot 51
    virtual void vf52();  // slot 52
    virtual void vf53();  // slot 53
    virtual void vf54();  // slot 54
    virtual void vf63();  // slot 63
    virtual void vf64();  // slot 64
    virtual bool fn_7100085314(int) const;  // slot 65 (placeholder name: see CharacterParameter)
    virtual void vf75();  // slot 75
    virtual void InitializeAttackParam();  // slot 79
    virtual void CalcDamageArmorEx(unsigned int);  // slot 80
    virtual ~PlayerParameter();  // slot 81
};
}  // namespace btl

#endif
