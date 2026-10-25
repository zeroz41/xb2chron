#ifndef CLASSES_BTL_DATAMANAGER_H
#define CLASSES_BTL_DATAMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class CharacterParameter; }
namespace btl { class DataManager; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace btl {
// an art's data as DataManager::GetArtsData fills it (layout not recovered yet)
struct ARTS_DATA {
    enum DATA_TYPE : int;
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

    unsigned char pad_8[0x15D0B];
    // Utility::GetElementalEffectID returns it (the name is not the original's)
    unsigned char m_elementalEffectID;
};
}  // namespace btl

#endif
