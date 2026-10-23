// not proven yet: its table differs from the original's (word 6: _ZN3btl15BattleCharacter3vf3Ev where the original has _ZN3btl15BattleCharacter11AfterUpdateEv)
#ifndef CLASSES_BTL_BATTLECHARACTER_H
#define CLASSES_BTL_BATTLECHARACTER_H

namespace btl { class CharacterParameter; }

namespace btl {
// table 0x7100B3AA08
class BattleCharacter {
public:
    enum ANIM_ID : int;
    virtual ~BattleCharacter();  // slot 0
    virtual void vf1();  // slot 1
    virtual void vf2();  // slot 2
    virtual void vf3();  // slot 3
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
    CharacterParameter* GetCharacterParameterConst(bool) const;
    bool IsDead(unsigned int) const;
    bool IsControlCharacter() const;
    void SetWeaponType(int type);
    void NotifyDirectDamage(const DIRECT_DAMAGE_DATA& data);
    void AddBladeArtsRecast(int, float);
    void FluctuateKizuna(int, float);
    void AddPartyGauge(float);
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
};
}  // namespace btl

#endif
