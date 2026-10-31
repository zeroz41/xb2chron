#ifndef CLASSES_BTL_HATERINGMANAGER_H
#define CLASSES_BTL_HATERINGMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class HateRingManager; }
namespace fw { class UpdateInfo; }

namespace btl {
// table 0x7100B3BC60
class HateRingManager : public ::mm::mtl::PtrSingleton< ::btl::HateRingManager> {
public:
    virtual ~HateRingManager();  // slot 0
    static void Create();
    static void Destroy();
    // 1.0.0's name: 3.0.1's BattleManager::update calls it between ChainAttackManager::PreUpdate and
    // EffectManager's, where 1.0.0's calls HateRingManager::PreUpdate. Its symbol still spells fn_71000A14E0.
    static void PreUpdate(const fw::UpdateInfo& info);
    static void Update(const fw::UpdateInfo& info);
    void UpdateProc(const fw::UpdateInfo& info);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // bytes at 0x112C from `this`. What it does: answers the byte at 0x112C + index (BattleCharacter's
    // IsEnableArts and AI_PickupHealPot call it).
    unsigned char fn_71000A1DB8(int index) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // bytes at 0x112C from `this`. What it does: packs the three bytes at 0x112C into one word, 10 bits apart
    // (UIManager::UpdateMenuData calls it).
    unsigned int fn_71000A1DC8() const;

    unsigned char pad_8[0x1124];
    // read by fn_71000A1DB8 and fn_71000A1DC8; meaning unknown
    unsigned char pad_112C[3];
    unsigned char pad_112F;  // Create allocates 0x1130 bytes
};
}  // namespace btl

#endif
