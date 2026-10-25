#ifndef CLASSES_BTL_BATTLECHARACTER_H
#define CLASSES_BTL_BATTLECHARACTER_H

#include "mm/Vec3.h"

namespace btl { class CharacterParameter; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class MsgObjectNotifyAsmCallback; }

namespace btl {
// table 0x7100B3AA08
class BattleCharacter {
public:
    enum ANIM_ID : int;
    virtual ~BattleCharacter();  // slot 0
    // 1.0.0's names, from its table (same slots); StateBattleActionBase::BeforeUpdate forwards to the first
    virtual void BeforeUpdate(fw::UpdateInfo const&);  // slot 2
    virtual void Update();  // slot 3
    virtual void AfterUpdate();  // slot 4
    virtual void SetAnimationCallback(btl::BattleCharacter::ANIM_ID, int, int, char const*);  // slot 5
    virtual void OnLandCallback(bool, bool);  // slot 6
    virtual void LandingCallback();  // slot 7
    virtual void BoundCallback();  // slot 8

    // a hit that skips the attack's own calculation (ButtonChallenge's result damages the challenge's target with
    // one; the field names are not the original's)
    struct DIRECT_DAMAGE_DATA {
        BattleCharacter* m_attacker;
        int m_type;              // ButtonChallenge gives 0x12-0x15 by the result
        unsigned int m_damage;
        int pad_10;
        bool pad_14;
    };
    CharacterParameter* GetCharacterParameter(bool);
    CharacterParameter* GetCharacterParameterConst(bool) const;
    // what the enemy's battle states hand an animation annotation to (1.0.0's name)
    void AsmCallback(const gf::MsgObjectNotifyAsmCallback& msg);
    void NotifyChangeAttr(gf::GF_OBJ_HANDLE* handle, unsigned int attr, unsigned int prevAttr);
    bool IsDead(unsigned int) const;
    bool IsControlCharacter() const;
    void SetWeaponType(int type);
    void NotifyDirectDamage(const DIRECT_DAMAGE_DATA& data);
    void AddBladeArtsRecast(int, float);
    void FluctuateKizuna(int, float);
    void AddPartyGauge(float);
    bool IsAngry() const;
    bool IsBlade() const;
    bool IsBattle() const;
    gf::GF_OBJ_HANDLE* GetRescueTarget() const;
    // the id the AI scripts know the character by: its index for a player character, 100 more for an enemy (the
    // Utility::AI_ getters compute it so; the name is not the original's)
    int GetAiChrID() const {
        int id = m_index + 100;
        if (m_isPlayer) {
            id = m_index;
        }
        return id;
    }
    bool SetAngry(bool, float);
    int GetKizunaStage(float*) const;
    bool StartBackHome();
    bool MoveStop(bool);
    void AddKizuna(float);
    void SetScout(bool);
    void SetSuperArmorTime(float);
    bool IsInAttackRange(int, float*) const;
    bool IsEnableTurnAI() const;
    void TurnTarget(bool, bool, bool);
    // Placeholder name: 1.0.0's ButtonChallenge::ResultProc calls IsBlade() const in its place, with no argument.
    // A member: called on CharacterManager::GetCharacterConst's character. What it does: ButtonChallenge asks it
    // with true; when it holds, the challenge's character is a blade and its driver (the parameter's handle) acts.
    bool fn_7100028D0C(bool);
    // Placeholder name: 1.0.0's ResultProc calls GetWeaponAttack(bool, bool) const in its place, with one argument
    // fewer. A member: as fn_7100028D0C. What it does: gives the attack ButtonChallenge adds to the stat for its
    // damage; ButtonChallenge passes its param's flag, false, false.
    float fn_710006760C(bool, bool, bool);
    // Placeholder name: 1.0.0's ResultProc calls GetFriendEnhanceRate(int, bool) const in its place, with one
    // argument fewer. A member: as fn_7100028D0C. What it does: ButtonChallenge passes 0xB9, 0, 0 and adds a positive
    // result to the party gauge.
    float fn_710005F0D8(int, int, int);
    // Placeholder name: 1.0.0's ResultProc calls AchieveCondition(int, unsigned int) const in its place, with the
    // same arguments (0xC, 0): the rename's evidence. A member: as fn_7100028D0C.
    void fn_7100041D00(int, unsigned int);

    unsigned char pad_8[0x8];
    // where the character stands: EnemyParameter::AngryInfection measures from it (the name is not the original's)
    mm::Vec3 m_pos;
    unsigned char pad_20[0xF8];
    // the character's object: Utility::AI_GetCharacterHandle returns it (the name is not the original's)
    gf::GF_OBJ_HANDLE* m_handle;
    // the object the character targets, (GF_OBJ_HANDLE*)-1 for none: Utility::AI_GetTargetCharacterID reads it
    // (the name is not the original's)
    gf::GF_OBJ_HANDLE* m_targetHandle;
    unsigned char pad_128[0xDC8];
    // the character's index on its side (GetAiChrID; the name is not the original's)
    signed char m_index;
    unsigned char pad_EF1[0xB];
    unsigned int pad_EFC : 31;
    // a player-side character (GetAiChrID; the name is not the original's)
    unsigned int m_isPlayer : 1;
    unsigned int pad_F00 : 23;
    // Utility::AI_IsFly returns it (the name is not the original's)
    unsigned int m_isFly : 1;
    unsigned int pad_F00_24 : 8;
    unsigned char pad_F04[0x2A4];
    // Utility::AI_GetStamp returns it while the character lives (the name is not the original's)
    int m_stamp;
};
}  // namespace btl

#endif
