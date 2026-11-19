#ifndef CLASSES_BTL_DATAMANAGER_H
#define CLASSES_BTL_DATAMANAGER_H

#include "btl/GroupData.h"
#include "classes/btl/PlayerParameter.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "ml/CriticalSection.h"
#include "mm/mtl/FixedVector.h"

namespace btl { class CharacterParameter; }
namespace btl { class DataManager; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfMenuCallContext; }

namespace btl {
// ENHANCE_EFFECT_DATA: in classes/btl/CharacterParameter.h (CharacterParameter holds them; included through
// PlayerParameter.h)

// an art's data as DataManager::GetArtsData fills it (layout not recovered yet)
// DataManager::GetArtsData fills it; only what BattleCharacter reads is recovered (two runs of unsigned int
// bitfields at 0x8 and 0x18: clang reads each as one 64-bit unit)
// 0xE8 bytes, 8-aligned: DataManager's arts caches hold them at a 0xE8 stride (UpdateCacheID, ClearCache) and
// GetArtsData's assignment copies 0xE8 bytes
struct ARTS_DATA {
    enum DATA_TYPE : int;
    // clears the bit fields (the first 0x20 bytes) only
    ARTS_DATA()
        : pad_0_0(0), pad_0_11(0), pad_0_22(0), m_kind(0), m_subKind(0), pad_0_32(0), m_hitWeightTotal(0),
          m_initialRecast(0), pad_8_0(0), m_category(0), m_hitCount(0), m_range(0), pad_8_19(0), pad_8_28(0),
          m_fightCombo(0), pad_C_3(0), m_hitRow(0), pad_10_12(0), pad_10_23(0), pad_10_28(0), pad_14(0), pad_18(0),
          m_distance(0), pad_1C_12(0), m_iconType(0) {}
    // the share of the hits' damage that hit takes (the hits' weights, divided by the two counts and the BDAT
    // table 0x12 row's "AddAtkNum" + 1)
    float GetHitWeightRate(int hit) const;
    // 2.0.0's symbols name it. What it does: 1 when m_kind is 3; else 2 when the enhance of m_enhance[index - 1]
    // (DataManager::GetEnhanceData) is effect 0x182; else 0 (BattleCharacter::ActionArts).
    int CheckHealArts(int index) const;
    unsigned long long pad_0_0 : 11;
    // BattleCharacter::StartAngryArts needs it non-zero (meaning unknown)
    unsigned long long pad_0_11 : 11;
    unsigned long long pad_0_22 : 2;
    unsigned long long m_kind : 5;  // CheckHealArts answers 1 for 3 (the name is not the original's)
    // with m_kind 3, GfMenuObjUtil::getArtsIconInfo gives range icon 3 for 3 (the name is not the original's)
    unsigned long long m_subKind : 3;
    unsigned long long pad_0_32 : 13;
    unsigned long long m_hitWeightTotal : 12;  // the hits' weights' total (GetHitWeightRate; the name is not the original's)
    unsigned long long m_initialRecast : 7;  // percent (ARTS_SLOT_DATA::ResetRecast; the name is not the original's)
    unsigned int pad_8_0 : 5;
    // unknown: GetArtsAttackDistance adds enhance 195's value for 12 (the name is not the original's)
    unsigned int m_category : 6;
    // how many of m_hits are used (GfMenuObjUtil::getArtsIconInfo looks for a reaction among them; the name is not
    // the original's)
    unsigned int m_hitCount : 5;
    // the range kind (GfMenuObjUtil::getArtsIconInfo turns it into a range icon; the name is not the original's)
    unsigned int m_range : 3;
    unsigned int pad_8_19 : 9;
    unsigned int pad_8_28 : 4;  // GetHitWeightRate divides by it from 2 on (meaning unknown)
    // the fight combo it starts, 0 for none (GfMenuBattleAdapter::update_ArtsFightComboIcon shows it less 1; the
    // name is not the original's)
    unsigned int m_fightCombo : 3;
    unsigned int pad_C_3 : 29;
    unsigned int m_hitRow : 12;  // the BDAT table 0x12 row GetHitWeightRate reads (the name is not the original's)
    unsigned int pad_10_12 : 11;
    unsigned int pad_10_23 : 5;  // GetHitWeightRate divides by it from 2 on (meaning unknown)
    unsigned int pad_10_28 : 4;
    unsigned int pad_14 : 32;
    unsigned int pad_18 : 32;
    // the distance GetArtsAttackDistance starts from (the name is not the original's)
    unsigned int m_distance : 12;
    unsigned int pad_1C_12 : 6;
    // the type icon less 4 (GfMenuObjUtil::getArtsIconInfo; the name is not the original's)
    unsigned int m_iconType : 14;
    // GfMenuBattleAdapter::update_ArtsFightComboIcon and GfMenuObjUtil::getArtsIconInfo construct one, clearing only
    // the first 0x20 bytes
    // ArtsGravityProc's window: from start stage/frame on it clears BattleCharacter's pad_F03_7, from end
    // stage/frame on it sets it; all zero for none (the struct's and the names are not the original's)
    struct GRAVITY {
        unsigned int m_startStage : 3;
        unsigned int m_startFrame : 13;
        unsigned int m_endStage : 3;
        unsigned int m_endFrame : 13;
    };
    GRAVITY m_gravity;
    unsigned char pad_24[0x4];
    // in DataManager's arts caches: how many other entries were used since this one (UpdateCacheID clears it on use
    // and ages the younger ones; the name is not the original's)
    unsigned char m_cacheAge;
    unsigned char pad_29[0x4];
    // BattleCharacter::StartAngryArts acts only while it is set (meaning unknown)
    unsigned int pad_2D_0 : 1;
    unsigned int pad_2D_1 : 6;
    // while set, DataManager::GetArtsData re-caches the entry when Utility::IsSatisfyCondition(0) differs from
    // pad_2D_8 (meaning unknown)
    bool pad_2D_7 : 1;
    bool pad_2D_8 : 1;
    unsigned int pad_2D_9 : 15;
    // one hit's share (GetHitWeightRate; the names are not the original's)
    struct HIT {
        unsigned char pad_0[0x2];
        unsigned char weight;
        // its reaction: 1-4 give reaction icons 3-6, 5-9 icon 1, 10-14 icon 2 (GfMenuObjUtil::getArtsIconInfo; the
        // name is not the original's)
        unsigned char reaction;
        unsigned char pad_4[0x2];
    };
    HIT m_hits[16];
    unsigned char pad_90[0x4];
    // an enhance of the arts (CheckHealArts reads entry index - 1; the count is not recovered, the names are not the
    // original's)
    struct ENHANCE {
        unsigned short id;
        unsigned char pad_2[0x4];
    };
    // (GfMenuObjUtil::getArtsIconInfo reads entries 0-4 by level)
    ENHANCE m_enhances[5];
    unsigned char pad_b2[0x36];
};

// an enemy group: RegisterEnemyGroup fills a free one with its two objects, ReleaseEnemyGroup marks each released
// and frees the group once both are; GetEnemyGroupIndex answers its index + 3 (the names are not the original's)
struct ENEMY_GROUP {
    gf::GF_OBJ_HANDLE* m_first;
    gf::GF_OBJ_HANDLE* m_second;
    bool m_firstReleased;
    bool m_secondReleased;
    unsigned char pad_12[0x6];
};

// a party group's item pouch buff: GetPouchBuffParam reads a parameter, IsPouchBuffTiming the flag at 0x3B (the
// names are not the original's)
struct POUCH_BUFF {
    float m_params[14];
    unsigned char pad_38[0x3];
    unsigned char m_isTiming;
};

// table 0x7100B3BAF8
class DataManager : public ::mm::mtl::PtrSingleton< ::btl::DataManager> {
public:
    DataManager();
    virtual ~DataManager();  // slot 0
    static void PreUpdate(const fw::UpdateInfo& info);
    static void Update(const fw::UpdateInfo& info);
    void UpdateProc(const fw::UpdateInfo& info);
    void InitializeComboRequestUI();
    int GetPartyGauge() const;
    float GetPouchBuffParam(int param, int groupIndex) const;
    bool IsPouchBuffTiming(int groupIndex) const;
    void SetSpecialEffects(int effect, bool enable);
    // ElementalComboManager::Update passes an entry of its element table and its character index
    void SetElementalEffect(int, int);
    static bool IsValidDeadEnhance(int enhance);
    // the enhance's effect (BDAT table 0x2C); false when it has none
    static bool GetEnhanceData(int enhance, ENHANCE_EFFECT_DATA& data, bool);
    // 2.0.0's symbols name it. What it does: when m_criticalSection is enabled calls the unnamed 0x71008B2B70 on it,
    // empties the four arts caches (the counts at 0x73D8, 0xCEB0, 0xF7A0, 0x112F8, as the destructor does) and resets
    // their entries' bitfields.
    void ClearCache();
    // the original's symbol names it; BattleManager::gevMapjump calls it on a map change (GEV 2)
    void NotifyMapChange();
    void SetPartyGauge(int value, bool flag);  // GfGameUtil::setMaxPartyGauge passes (300, false)
    // Create: 1.0.0's name (fn_710009028C in 3.0.1): 1.0.0's BattleManager::Initialize calls it fourth, as 3.0.1's does
    static void Create();
    static void Destroy();
    static void PostUpdate(const fw::UpdateInfo& info);
    int RegisterEnemyGroup(gf::GF_OBJ_HANDLE* first, gf::GF_OBJ_HANDLE* second);
    void ReleaseEnemyGroup(gf::GF_OBJ_HANDLE* handle);
    int GetEnemyGroupIndex(gf::GF_OBJ_HANDLE* handle) const;
    void GetArtsData(ARTS_DATA::DATA_TYPE type, int id, ARTS_DATA& data) const;
    bool IsSpecialEffects(int effect) const;
    // BattleCharacter::GetCharacterParameter passes the character's id
    CharacterParameter* GetCharacterParameterConst(int id) const;
    // CharacterParameter::SetAdditionalEnhance asks it for the driver's parameter when CharacterManager has no
    // character for the handle
    CharacterParameter* SearchCharacterParameterConst(gf::GF_OBJ_HANDLE* handle, bool) const;
    // values below 10000 are rows of BDAT table 0x37 ("Param"; row 5 shrinks by owner bonus 12), 10000-10003 fixed
    // amounts
    void FluctuatePartyGauge(int value, int groupIndex);
    // BattleCharacter::AddPartyGauge passes its value, its group index and true
    void AddPartyGauge(float value, int groupIndex, bool);
    // 2.0.0's symbols name it. What it does: KIZUNA_GAUGE_DATA:: SetKizunaStage(stage, 0.5, true) on
    // GROUP_DATA::GetBladeDataConst of every blade (0-4) of the three groups at +0x12E30, +0x12F50 and +0x13070, or,
    // with engagedOnly, only on each group's engaged blade (index -1).
    void SetKizunaStage(int stage, bool engagedOnly);
    // the symbols name it. What it does: an enemy (Misc::GetPartyID -1) gets a new EnemyParameter in the first free
    // m_enemyParameters slot (id 1000 + slot); a party character reuses its parameter (keeping its id) or the first
    // m_playerParameters entry without a handle (id = index); Initialize(handle) on it. The id, -1 when full
    int RegisterCharacterParameter(gf::GF_OBJ_HANDLE* handle);
    void UnregisterCharacterParameter(int id);
    void RegisterUpdateAttackParam(bool players, bool enemies);
    bool IsExistRequestPermit() const;
    void RequestPermit(int group, gf::GF_OBJ_HANDLE* handle);
    // counts each party group's pouch buff timer (m_params[12]) up while params 4 or 9 are set, in 30-unit steps
    void UpdatePouchBuff(float dt);

    // an arts cache's helper: ids holds the indices of the used entries of entries; ages every used entry younger
    // than data and makes data the youngest (UpdateCacheID's loop, the same for each cache; age is data's; the name is
    // not the original's)
    template <unsigned long N>
    static void UpdateAge(const ::mm::mtl::FixedVector<unsigned char, N>& ids, ARTS_DATA* entries, const ARTS_DATA* data,
                          unsigned char age) {
        for (unsigned char id : ids) {
            ARTS_DATA& entry = entries[id];
            if (&entry == data) {
                entry.m_cacheAge = 0;
            } else if (entry.m_cacheAge < age) {
                entry.m_cacheAge++;
            }
        }
    }

    // the symbols name it (the return type is inferred: GetArtsData passes it on to CacheArtsData; the cached entry
    // for type and id, else null)
    ARTS_DATA* GetCacheArtsDataConst(ARTS_DATA::DATA_TYPE type, int id) const;
    // the symbols name it (fills an entry for type and id, the given one or a free one, and returns it)
    ARTS_DATA* CacheArtsData(ARTS_DATA::DATA_TYPE type, int id, ARTS_DATA* data) const;
    // the symbols name it. What it does: makes data the youngest entry of the cache its type (pad_0_22) selects
    void UpdateCacheID(const ARTS_DATA* data) const;

    ml::CriticalSection m_criticalSection;  // the destructor destroys it (the name is not the original's)
    // GetCharacterParameterConst answers ids below 1000 from here (the name is not the original's)
    PlayerParameter m_playerParameters[18];
    // GetCharacterParameterConst answers ids from 1000 from here (the name is not the original's)
    CharacterParameter* m_enemyParameters[70];
    // the arts caches by type (pad_0_22): 1, 2, 3, and every other type; each the indices of its used entries, kept
    // sorted by the entries' ids (GetCacheArtsDataConst's binary search), and the entries. Separate members, not a
    // struct: GetCacheArtsDataConst addresses both from the DataManager. The indices are not mutable: the const
    // GetCacheArtsDataConst reads them through FixedVector's const operator[] (the names are not the original's)
    ::mm::mtl::FixedVector<unsigned char, 100> m_artsCacheIDs;
    mutable ARTS_DATA m_artsCache[100];
    ::mm::mtl::FixedVector<unsigned char, 45> m_artsCacheIDs1;
    mutable ARTS_DATA m_artsCache1[45];
    ::mm::mtl::FixedVector<unsigned char, 30> m_artsCacheIDs2;
    mutable ARTS_DATA m_artsCache2[30];
    ::mm::mtl::FixedVector<unsigned char, 30> m_artsCacheIDs3;
    mutable ARTS_DATA m_artsCache3[30];
    GROUP_DATA m_groups[38];  // BattleCharacter::GetGroupDataConst indexes it by group (the name is not the original's)
    ENEMY_GROUP m_enemyGroups[35];   // the name is not the original's
    POUCH_BUFF m_pouchBuffs[3];      // indexed by group (the name is not the original's)
    unsigned char pad_15CEC[0x4];
    int pad_15CF0;  // ClearCache clears it (meaning unknown)
    unsigned char pad_15CF4[0x4];
    // AddPartyGauge keeps the gain's fraction below one point here (the name is not the original's)
    float m_partyGaugeFraction;
    unsigned char pad_15CFC[0x4];
    // InitializeComboRequestUI creates it, Destroy releases it (the name is not the original's)
    gf::GfMenuCallContext* m_comboRequestContext;
    // ElementalComboManager::GetElementalComboID answers pad_15D11 for this character (meaning unknown)
    gf::GF_OBJ_HANDLE* pad_15D08;
    // the group BattleCharacter::ResetRequestPermit compares its own with (signed: 1.0.0's
    // DataManager::ResetRequestPermit sets it and the next byte to -1)
    signed char pad_15D10;
    unsigned char pad_15D11;  // see pad_15D08
    unsigned char pad_15D12;
    // Utility::GetElementalEffectID returns it (the name is not the original's)
    unsigned char m_elementalEffectID;
    unsigned char pad_15D14;
    bool m_specialEffects[5];  // SetSpecialEffects, IsSpecialEffects (the name is not the original's)
    unsigned char pad_15D1A;  // Utility::FullCoolTime sets it to 1
};
}  // namespace btl

#endif
