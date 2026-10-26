#ifndef CLASSES_BTL_DATAMANAGER_H
#define CLASSES_BTL_DATAMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class CharacterParameter; }
namespace btl { class DataManager; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace btl {
// an art's data as DataManager::GetArtsData fills it (layout not recovered yet)
// DataManager::GetArtsData fills it; only what BattleCharacter reads is recovered (two runs of unsigned int
// bitfields at 0x8 and 0x18: clang reads each as one 64-bit unit)
struct ARTS_DATA {
    enum DATA_TYPE : int;
    unsigned char pad_0[0x8];
    unsigned int pad_8_0 : 5;
    // unknown: GetArtsAttackDistance adds enhance 195's value for 12 (the name is not the original's)
    unsigned int m_category : 6;
    unsigned int pad_8_11 : 21;
    unsigned int pad_C : 32;
    unsigned char pad_10[0x8];
    unsigned int pad_18 : 32;
    // the distance GetArtsAttackDistance starts from (the name is not the original's)
    unsigned int m_distance : 12;
    unsigned int pad_1C_12 : 20;
};

// table 0x7100B3BAF8
class DataManager : public ::mm::mtl::PtrSingleton< ::btl::DataManager> {
public:
    virtual ~DataManager();  // slot 0
    void SetPartyGauge(int value, bool flag);  // GfGameUtil::setMaxPartyGauge passes (300, false)
    // Create: 1.0.0's name (fn_710009028C in 3.0.1): 1.0.0's BattleManager::Initialize calls it fourth, as 3.0.1's does
    static void Create();
    static void Destroy();
    static void PostUpdate(const fw::UpdateInfo& info);
    void ReleaseEnemyGroup(gf::GF_OBJ_HANDLE* handle);
    void GetArtsData(ARTS_DATA::DATA_TYPE type, int id, ARTS_DATA& data) const;
    bool IsSpecialEffects(int effect) const;
    // BattleCharacter::GetCharacterParameter passes the character's id
    CharacterParameter* GetCharacterParameterConst(int id) const;
    void FluctuatePartyGauge(int value, int groupIndex);
    // BattleCharacter::AddPartyGauge passes its value, its group index and true
    void AddPartyGauge(float value, int groupIndex, bool);

    unsigned char pad_8[0x15D0B];
    // Utility::GetElementalEffectID returns it (the name is not the original's)
    unsigned char m_elementalEffectID;
};
}  // namespace btl

#endif
