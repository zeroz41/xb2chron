// not proven yet: its table differs from the original's (word 6: _ZN3btl15BattleCharacter3vf3Ev where the original has _ZN3btl15BattleCharacter11AfterUpdateEv)
#ifndef CLASSES_BTL_BATTLECHARACTER_H
#define CLASSES_BTL_BATTLECHARACTER_H

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
};
}  // namespace btl

#endif
