#ifndef CLASSES_BTL_BUTTONCHALLENGE_H
#define CLASSES_BTL_BUTTONCHALLENGE_H

#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuObjButtonChallenge2.h"

namespace fw { class UpdateInfo; }

namespace btl {
// table 0x7100B3A940; BattleGlobal holds one and updates it (BattleGlobal::UpdateProc)
class ButtonChallenge {
public:
    // what a challenge asks for: Start copies it into m_param (the field names are not the original's)
    struct BUTTON_CHALLENGE_PARAM {
        BUTTON_CHALLENGE_PARAM() : m_menuType(0), m_menuId(0), m_kind(4), m_flag(0), m_stat(0), m_target(0),
                                   m_character(0x5A), m_priority(0) {}
        unsigned int m_menuType : 14;  // 0xF9 opens GfMenuObjButtonChallenge2's sequence, any other its single one
        unsigned int m_menuId : 14;    // what GfMenuObjButtonChallenge2::open gets
        unsigned int m_kind : 4;       // whose result it is: 0 an attack, 1 a chain attack turn, 2 an enemy's, 3
                                       // BattleGlobal's; 4 none (IsProc)
        unsigned int : 0;
        unsigned int m_flag : 16;       // fn_710001C990 passes it (as a bool) to BattleCharacter::fn_710006760C
        unsigned int m_stat : 16;       // fn_710001C990's damage base: 1 the strength, 2 the ether power
        int m_target;                  // the character fn_710001C990 damages
        unsigned char m_character;     // the character that challenges (CharacterManager::GetCharacterConst(int))
        unsigned char m_priority;      // a challenge in progress gives way only to an equal or higher one (Start)
    };

    ButtonChallenge();
    virtual ~ButtonChallenge();  // slot 0

    int Start(const BUTTON_CHALLENGE_PARAM& param);
    void Cancel(unsigned int id);
    void ProgressSeparately();
    bool IsProc() const;
    void Update(const fw::UpdateInfo& info);
    bool IsEnemyChallengeSuccess();

    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's OpenButtonChallenge(int, int) at 0x71000171F4 does its
    // create/reset and open part, with other arguments; 1.0.0's Start inlines it). A
    // member because Start passes its this. What it does: opens GfMenuObjButtonChallenge2 (its sequence for menu
    // type 0xF9) on a new or reset m_context, unless BattleGlobal::fn_710000A724 holds (and, for a kind other
    // than 0, BattleGlobal::fn_71000068F8 too): then it drops m_context and marks the challenge skipped.
    void fn_710001C6A8(const BUTTON_CHALLENGE_PARAM& param);
    // Placeholder name: 1.0.0's ResultProc(int) sits at the same call sites (Start, Update,
    // BattleCharacter::AttackTimingProc) with the same body, but 3.0.1 added the bool, so the arguments differ. A
    // member: its callers pass their this. What it does: plays the result's pad vibration, applies the result by the
    // challenge's kind (damage, the chain attack turn, the enemy's success, BattleGlobal's), plays the narration voice
    // when the bool is set, and marks the challenge done.
    void fn_710001C990(int result, bool narrate);
    // 1.0.0's CancelProc() (0x7100017850): 3.0.1 inlines it everywhere (Start, Cancel). Closes the menu (only an open
    // one, in 3.0.1), keeps its context for the close and clears the challenge.
    void CancelProc() {
        gf::GfMenuCallContext* context = m_context;
        if (context != nullptr) {
            if (m_prevContext != nullptr) {
                m_prevContext->release();
                m_prevContext = nullptr;
            }
            m_context = nullptr;
            m_prevContext = context;
            if (m_isOpen) {
                gf::GfMenuObjButtonChallenge2::close(context);
            }
        }
        m_param = BUTTON_CHALLENGE_PARAM();
        m_id = 0;
        m_isOpen = false;
        m_isDone = true;
        m_isSkipped = false;
        m_enemySuccess = false;
    }
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's BattleCharacter::AttackTimingProc
    // and ChainAttackManager::UpdateProc do this inline). A member: its callers pass a ButtonChallenge. What it
    // does: for a skipped challenge with this id not yet done, gives fn_710001C990(2, false), drops m_context,
    // clears the challenge, deletes its slow and lifts BattleGlobal's pause 4.
    void fn_710001D2F0(unsigned int id);

    gf::GfMenuCallContext* m_context;      // GfMenuObjButtonChallenge2's while it is open
    gf::GfMenuCallContext* m_prevContext;  // the one being closed (Cancel, Start)
    BUTTON_CHALLENGE_PARAM m_param;        // Start's
    int m_nextId;                          // the id the next Start returns (never -1's successor 0)
    int m_id;                              // the challenge in progress, 0 for none
    unsigned int m_slowId;                 // BattleGlobal::DeleteSlow's
    unsigned char m_successCount;          // fn_710001C990 counts its results of 3, picks the narration by it
    bool m_isOpen;                         // GfMenuObjButtonChallenge2 is open (fn_710001C6A8)
    bool m_isDone;                         // fn_710001C990 ran for the challenge
    bool m_isSkipped;                      // fn_710001C6A8 did not open the menu
    bool m_enemySuccess;                   // fn_710001C990's for kind 2, IsEnemyChallengeSuccess takes it
};
}  // namespace btl

#endif
