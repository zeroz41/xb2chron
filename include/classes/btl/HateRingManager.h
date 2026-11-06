#ifndef CLASSES_BTL_HATERINGMANAGER_H
#define CLASSES_BTL_HATERINGMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/Vec3.h"

namespace btl { class HateRingManager; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace btl {
// table 0x7100B3BC60
class HateRingManager : public ::mm::mtl::PtrSingleton< ::btl::HateRingManager> {
public:
    // 1.0.0's name (RING_DATA::Reset(bool)): a hate ring, 0x30 bytes; 1.0.0's Reset zeroes the position, sets the
    // handle and target to -1 and destroys the two effects. The field names are not the original's.
    struct RING_DATA {
        // what Create's construction stores (3.0.1 inlines it)
        RING_DATA()
            : m_handle(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), m_target(-1), m_arrowTime(0.0f), m_ringEffect(0),
              m_arrowEffect(0) {
            m_pos = mm::Vec3::zero;
        }
        // 1.0.0's RING_DATA::Reset(bool); 3.0.1 inlines it in Destroy, UpdateProc and SetData, which show no use of
        // a bool, so it is left out here
        void Reset();  // defined inline in hate_ring_manager.cpp

        // where the arrow ends: UpdateArrow takes the target's ring position (raised) while it is zero
        mm::Vec3 m_pos;
        gf::GF_OBJ_HANDLE* m_handle;  // the object the ring is on
        int m_target;  // the party member it points at (1.0.0's GetTarget(int) returns it)
        // UpdateArrow's arrow animation time in 30ths of a second: grows to 15, then -1 (done); the name is not
        // the original's
        float m_arrowTime;
        unsigned int m_ringEffect;  // EffectManager::destroyHateRingVec's handle
        unsigned int m_arrowEffect;  // EffectManager::destroyHateArrow's handle
    };

    HateRingManager() {
        for (int i = 0; i < 3; i++) {
            m_ringEffects[i] = 0;
        }
        for (int i = 0; i < 3; i++) {
            m_hateEnemyNum[i] = 0;
        }
    }

    virtual ~HateRingManager();  // slot 0
    static void Create();
    static void Destroy();
    // 1.0.0's name: 3.0.1's BattleManager::update calls it between ChainAttackManager::PreUpdate and
    // EffectManager's, where 1.0.0's calls HateRingManager::PreUpdate. 2.0.0's symbols name it.
    static void PreUpdate(const fw::UpdateInfo& info);
    static void Update(const fw::UpdateInfo& info);
    void UpdateProc(const fw::UpdateInfo& info);
    void UpdateArrow(int index, RING_DATA& ring, float deltaTime);
    void UpdateRing(int index, mm::Vec3 pos, mm::Vec3 dir);
    void SetData(int index, gf::GF_OBJ_HANDLE* handle, int target);
    // 2.0.0's symbols name it. What it does: answers the byte at 0x112C + index (BattleCharacter's IsEnableArts and
    // AI_PickupHealPot call it).
    unsigned char GetHateEnemyNum(int index) const;
    // 2.0.0's symbols name it. What it does: packs the three bytes at 0x112C into one word, 10 bits apart
    // (UIManager::UpdateMenuData calls it).
    unsigned int GetHateEnemyNumAll() const;

    // 1.0.0's name: the driver handle of the party member the ring on `handle` targets (-1 when no ring is on it).
    // 3.0.1's symbol spells it GetTarget(GF_OBJ_HANDLE*): its body and its caller (BattleCharacter::UpdateTarget)
    // are 1.0.0's GetTargetHandle's, with getHandleDriver's party argument 0
    gf::GF_OBJ_HANDLE* GetTargetHandle(gf::GF_OBJ_HANDLE* handle) const;
    // 1.0.0's: the party member the ring on `handle` targets, -1 when no ring is on it (3.0.1 has no copy of it:
    // GetTargetHandle inlines it)
    int GetTarget(gf::GF_OBJ_HANDLE* handle) const {
        const RING_DATA* ring = m_rings;
        for (int i = 0; i < 90; i++, ring++) {
            if (ring->m_handle == handle) {
                return ring->m_target;
            }
        }
        return -1;
    }

    unsigned char pad_8[8];
    RING_DATA m_rings[90];
    // per party member: where its hate ring is (UpdateRing stores it) and the ring's EffectManager::createHateRing
    // handle; the names are not the original's
    mm::Vec3 m_partyPos[3];
    unsigned int m_ringEffects[3];
    // per party member: how many rings target it (UpdateProc counts them; GetHateEnemyNum reads them); the name
    // follows 2.0.0's GetHateEnemyNum
    unsigned char m_hateEnemyNum[3];
    unsigned char pad_112F;  // Create allocates 0x1130 bytes
};
}  // namespace btl

#endif
