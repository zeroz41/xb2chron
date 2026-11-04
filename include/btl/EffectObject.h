#ifndef BTL_EFFECTOBJECT_H
#define BTL_EFFECTOBJECT_H

#include "mm/Vec3.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "btl/EffectMoveComponent.h"
#include "classes/btl/CharacterParameter.h"

namespace fw { class EffectPack; class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace btl {
// one battle effect (application/BF2/battle/EffectObject): an effect played at a point or an object followed, its
// hit data and its move. No table: a plain class. The field names are not the original's.
class EffectObject {
public:
    // EffectObject::m_kind: what SetObject set up (Initialize kills a played effect)
    enum KIND { KIND_NONE = 0, KIND_OBJECT = 1, KIND_EFFECT = 2 };
    // EffectObject::m_hitKind: which of the hit data's forms Set*HitData filled
    enum HIT_KIND { HIT_KIND_NONE = 0, HIT_KIND_ONE_SHOT = 1, HIT_KIND_INTERVAL = 2 };

    EffectObject();
    void Initialize(unsigned int id);
    void SetOneShotHitData(float rate, bool flag);
    void SetObject(gf::GF_OBJ_HANDLE* handle, mm::mtl::FixedVector<fw::EffectPack*, 8>& packs);
    void SetObject(mm::mtl::FixedVector<fw::EffectPack*, 8>& packs, const char* name, const mm::Vec3& pos,
                   const mm::Vec3* dir, const mm::Vec3* scale);
    // 2.0.0's symbols name it. What it does: copies the owner's (CharacterManager::GetCharacterConst(m_owner)) arts
    // slot data (BattleCharacter::GetArtsSlotData(slot, !flag, -1)) with SetArtsData; nothing without an owner.
    // EffectManager::CreateBullet calls it.
    void SetArtsData(int slot, int artsKind, bool flag, unsigned int artsParam);
    // 2.0.0's symbols name it. What it does: copies an arts slot's data into m_artsSlot and stores the byte into
    // m_artsKind, the word into m_artsParam. EffectManager::UpdateProc calls it.
    void SetArtsData(const ARTS_SLOT_DATA& slot, int artsKind, unsigned int artsParam);
    void SetBulletData(int bulletId, int param);
    void SetIntervalHitData(float interval, float rate, bool flag0, float count, float maxHit, bool flag1,
                            bool flag2, bool flag3);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits between
    // SetIntervalHitData and SetMoveParam in this unit. What it does: stores two bytes and a halfword into the
    // fields at 0x198. EffectManager::CreateCircleEffect calls it.
    void fn_710009BA78(unsigned char a, unsigned char b, unsigned short c);
    void SetMoveParam(const EffectMoveComponent::MOVE_PARAM& param);
    void SetEndEffect(const char* name);
    bool IsEnd() const;
    void Update(const fw::UpdateInfo& info);
    void CheckEnd();
    void EndProc();
    void UpdateHit(float a, float b);
    void ReturnLinkObj();
    void HitOneShotProc();
    void StartNextAttack();
    void StartAdditionalAttack();

    // Set*HitData's data (the field names are not the original's)
    struct ONE_SHOT_HIT {
        float m_rate;
        bool m_isActive;
        bool m_flag;
        bool m_isFirst;
        bool m_noAddAttack;  // set while the bullet's AddAtkNum is 0
    };
    struct INTERVAL_HIT {
        float m_rate;
        short m_interval;  // the interval times 100
        short m_maxHit;
        signed char m_count;
        unsigned char m_flag0 : 1;
        unsigned char m_flag1 : 1;
        unsigned char m_flag2 : 1;
        unsigned char m_flag3 : 1;
        unsigned char pad_e1_4 : 4;
        unsigned char m_hitFlags[0xB4];
    };

    mm::mtl::FixedVector<fw::EffectPack*, 8> m_effectPacks;
    gf::GF_OBJ_HANDLE* m_owner;  // CharacterManager::GetCharacterConst looks it up
    gf::GF_OBJ_HANDLE* pad_50;  // -1 after Initialize; meaning unknown
    gf::GF_OBJ_HANDLE* pad_58;  // -1 after Initialize; meaning unknown
    mm::mtl::FixStr<32> m_endEffect;  // SetEndEffect
    unsigned char pad_84[0xC];
    mm::Vec3 m_pos;      // SetObject: the followed object's position
    mm::Vec3 m_dir;      // unitZ after Initialize
    mm::Vec3 pad_b0;     // zero after Initialize; meaning unknown
    mm::Vec3 m_scale;    // unit after Initialize
    union {
        gf::GF_OBJ_HANDLE* m_object;  // KIND_OBJECT
        unsigned int m_effect;        // KIND_EFFECT: fw::EffectManager's handle
    };
    union {
        ONE_SHOT_HIT m_oneShotHit;
        INTERVAL_HIT m_intervalHit;
    };
    // fn_710009BA78 sets them; EffectManager::CreateCircleEffect calls it (the names are not the original's)
    unsigned char m_circleParamA;
    unsigned char m_circleParamB;
    unsigned short m_circleParamC;
    ARTS_SLOT_DATA m_artsSlot;
    unsigned char pad_1b4[0xC];
    EffectMoveComponent m_move;
    unsigned int m_id;  // Initialize's
    unsigned int m_artsParam;
    unsigned int pad_278;
    float m_remainTime;  // IsEnd: over at 0 or below once m_isTimed (the name is not the original's)
    short m_bulletId;
    short m_bulletParam;
    unsigned char m_artsKind;
    unsigned char m_fadeFrames;  // fw::EffectManager::fadeOutDead's, none for 0
    unsigned char m_kind;
    unsigned char m_hitKind;
    unsigned char m_addAtkNum;  // the bullet's AddAtkNum (BDAT 18)
    unsigned char m_isTimed : 1;
    unsigned char m_bit1 : 1;
    unsigned char m_bit2 : 1;
    unsigned char m_bit3 : 1;
    unsigned char pad_289_4 : 4;
};
}  // namespace btl

#endif
