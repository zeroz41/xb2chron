#ifndef CLASSES_BTL_BATTLEGLOBAL_H
#define CLASSES_BTL_BATTLEGLOBAL_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class BattleGlobal; }
namespace fw { class UpdateInfo; }

namespace btl {
// table 0x7100B3A3E0
class BattleGlobal : public ::mm::mtl::PtrSingleton< ::btl::BattleGlobal> {
public:
    virtual ~BattleGlobal();  // slot 0
    static void Create();
    static void Destroy();
    static void PostUpdate(const fw::UpdateInfo& info);
    void SetPause(int kind, bool pause);
    void DeleteSlow(unsigned int id);
    bool IsGameOver() const;
    // whether the battle is paused for kind (GfGameTarget's selectRight/selectLeft pass -1: any)
    bool IsPause(int kind) const;
    // GfGameTarget::updateImpl calls it once its near-target hold outlasts its parameter's time
    void NotifyShiftTimeOver();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's GfGameTarget::judgeNearTarget makes
    // no call there). A member: GfGameTarget::judgeNearTarget passes PtrSingleton<BattleGlobal>::sys(). What it does:
    // clears flag bits 40 and 41 (bits 0 and 1 of the byte at 0x83CF).
    void fn_710000A764();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: ButtonChallenge passes
    // PtrSingleton<BattleGlobal>::sys(). What it does: tests flag bits at 0x83CE (bits 17 and 18 both set, or bit 3).
    // ButtonChallenge::fn_710001C6A8 skips opening its menu when it holds.
    bool fn_710000A724();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: as fn_710000A724. What it does:
    // tests bits 1 and 2 of the byte at 0x83D0 both set; ButtonChallenge::fn_710001C6A8 asks it for kinds other than 0.
    bool fn_71000068F8();
    // Placeholder name: nothing in 1.0.0's ButtonChallenge::ResultProc names it (no call there). A member: as
    // fn_710000A724. What it does: ButtonChallenge::ResultProc passes it the challenge id and whether the result was
    // -1 (failed), for challenges of kind 3.
    void fn_710000BAE0(int id, bool failed);

    unsigned char pad_8[0x5C44];
    // EnemyParameter::ApplyStatusEnhance scales every enhanced value by it (the name is not the original's)
    float m_statusEnhanceRate;
    unsigned char pad_5c50[0x277A];
    // flags (the names are not the original's): one storage unit of 7 bytes, as their reads load it
    bool pad_bit0 : 1;
    bool pad_bit1 : 1;
    bool pad_bit2 : 1;
    bool m_challengeAnySuccess : 1;  // ButtonChallenge's results 1-3 (not only 3) achieve its condition 0xC
    // the rest of the unit: fn_710000A724 reads bits 35, 49 and 50, fn_71000068F8 bits 49 and 50
    unsigned char : 4;
    unsigned char : 8;
    unsigned char : 1;
    bool pad_bit17 : 1;  // EnemyParameter::MulHate changes no hate while it is set
    unsigned char : 6;
    unsigned char : 8;
    unsigned char : 8;
    // GfGameTarget's selectRight/selectLeft change no target while it is clear (the name is not the original's)
    bool pad_bit40 : 1;
    unsigned char : 7;
    unsigned char : 3;
};
}  // namespace btl

#endif
