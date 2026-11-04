#ifndef CLASSES_BTL_EFFECTMANAGER_H
#define CLASSES_BTL_EFFECTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedList.h"
#include "mm/mtl/FixedVector.h"
#include "btl/EffectObject.h"
#include "classes/btl/CharacterParameter.h"

namespace btl { class EffectManager; struct ARTS_DATA; }
namespace fw { class EffectPack; class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace btl {
// table 0x7100B3BB38; the battle's effects (application/BF2/battle/effect/effect_manager_battle): up to 90
// EffectObjects played at once and up to 30 effects registered to be created later (RegisterCreateEffect)
class EffectManager : public ::mm::mtl::PtrSingleton< ::btl::EffectManager> {
public:
    // CreateEffect's argument: an effect created with a kind other than 0 ends the playing effects of its kind
    enum EXCLUSION_TYPE { EXCLUSION_TYPE_NONE = 0 };

    // a playing effect: its id (EffectObject::m_id) and the index of its slot in m_effects
    struct PROC_DATA {
        unsigned int m_id;
        int m_index;
    };
    // a registered effect: the index of its slot in m_registers
    struct REGISTER_PROC_DATA {
        unsigned char m_index;
    };

    // one of the 90 effect slots (the names are not the original's)
    struct EFFECT_DATA {
        EFFECT_DATA() : m_used(false) {}

        EffectObject m_obj;
        unsigned char m_exclusionType;  // CreateEffect's EXCLUSION_TYPE
        bool m_used;
    };
    // one of the 30 registered effects: what UpdateProc creates when its time comes (the names are not the
    // original's)
    struct REGISTER_DATA {
        REGISTER_DATA() : m_used(false) {}

        mm::mtl::FixedVector<fw::EffectPack*, 8> m_effectPacks;
        gf::GF_OBJ_HANDLE* m_owner;  // copied to the created EffectObject's m_owner
        gf::GF_OBJ_HANDLE* pad_50;   // copied to the created EffectObject's pad_50
        gf::GF_OBJ_HANDLE* pad_58;   // copied to the created EffectObject's pad_58
        mm::mtl::FixStr<32> m_name;  // the effect's name
        unsigned char pad_84[0xC];
        mm::Vec3 m_pos;
        mm::Vec3 m_scale;
        ARTS_SLOT_DATA m_artsSlot;
        float m_interval;           // the time between two creations
        float m_timer;              // the time left to the next creation
        unsigned int m_artsParam;   // EffectObject::SetArtsData's
        unsigned char m_artsKind;   // EffectObject::SetArtsData's
        unsigned char m_count;      // how many times it is created
        unsigned char m_created;    // how many times it was
        unsigned char m_num;        // EffectObjects created each time
        unsigned char pad_d8;
        bool m_used;
    };

    EffectManager();
    virtual ~EffectManager();  // slot 0

    // Create: 1.0.0's name (fn_710009733C in 3.0.1): 1.0.0's BattleManager::Initialize calls it after
    // HateRingManager::Create, as 3.0.1's does
    static void Create();
    static void Destroy();
    void Initialize();
    void Finalize();
    void DeleteAllEffect();
    void NotifyMapChange();
    // PreUpdate: 1.0.0's name (fn_7100097638 in 3.0.1), next to Update; 1.0.0's BattleManager::update calls it
    // before the managers' Update, as 3.0.1's does. PreUpdateProc is empty, as in 1.0.0.
    static void PreUpdate(const fw::UpdateInfo& info);
    void PreUpdateProc(const fw::UpdateInfo& info) {}
    static void Update(const fw::UpdateInfo& info);
    void UpdateProc(const fw::UpdateInfo& info);
    unsigned int CreateEffect(EXCLUSION_TYPE type);
    EffectObject* GetEffect(unsigned int id);
    int GetFreeDataIndex() const;
    void CreateBullet(int, const ARTS_DATA&, int, unsigned int, int, gf::GF_OBJ_HANDLE*, gf::GF_OBJ_HANDLE*,
                      const mm::Vec3&, const mm::Vec3&, bool, bool);
    void RegisterCreateEffect(mm::mtl::FixedVector<fw::EffectPack*, 8>& packs, const char* name,
                              const mm::Vec3& pos, const mm::Vec3& scale, float, int, int, gf::GF_OBJ_HANDLE*,
                              gf::GF_OBJ_HANDLE*, gf::GF_OBJ_HANDLE*, const ARTS_SLOT_DATA&, int, unsigned int);
    void CreateCircleEffect(int, gf::GF_OBJ_HANDLE*, gf::GF_OBJ_HANDLE*);
    // 2.0.0's symbols name it (1.0.0's function in this place was IsExistChrHitEffect)
    bool IsExistChrCircle(gf::GF_OBJ_HANDLE* handle) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits in this unit
    // between IsExistChrCircle and the destructor and works on m_rates. What it does: adds the value to
    // m_rates[index], clamped to 0..0xFFFF, and sets m_ratesDirty so UpdateProc clears them all next frame.
    // EffectObject::ReturnLinkObj calls it.
    void AddCircleDamageBonus(int index, int value);
    // 2.0.0's symbols name it. What it does: m_rates[index] / 100 (times 0.01f). BattleCharacter::GetDamageEnhanceRate
    // calls it.
    float GetCircleDamageBonusRate(int index) const;

    EFFECT_DATA m_effects[90];
    mm::mtl::FixedList<PROC_DATA, 90> m_procList;
    REGISTER_DATA m_registers[30];
    mm::mtl::FixedList<REGISTER_PROC_DATA, 30> m_registerList;
    int m_nextId;  // the next effect's id: 1 first, skips -1 (the name is not the original's)
    // AddCircleDamageBonus's values by index, cleared each frame they changed (the names are not the original's)
    unsigned short m_rates[90];
    bool m_ratesDirty;
};
}  // namespace btl

#endif
