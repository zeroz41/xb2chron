#ifndef BTL_CHALLENGE_BATTLE_MANAGER_H
#define BTL_CHALLENGE_BATTLE_MANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/mm/mtl/ReferenceObject.h"

// The class of application/BF2/battle/challenge_battle_manager.cpp (table 0x7100B3A9C8,
// singleton 0x7100B939B0; not in 1.0.0). 2.0.0's symbols name ChallengeBattleManager and its functions.

namespace btl { class BattleCharacter; }
namespace fw { class UpdateInfo; }
namespace gf { class GfMenuCallContext; }

namespace btl {

// table 0x7100B3A9C8 (slot 0 its destructor, which only clears the singleton); 0x30 bytes (Create allocates
// so many)
class ChallengeBattleManager : public ::mm::mtl::PtrSingleton< ::btl::ChallengeBattleManager> {
public:
    ChallengeBattleManager()
        : pad_8(nullptr), pad_10(0.0f), pad_14(0.0f), pad_18(0.0f), pad_1c(0.0f), pad_20(0), pad_22(0), pad_24(0),
          pad_26(0), pad_27(0), pad_28(0), pad_29(4), pad_2a(0), pad_2b(0), pad_2c(0), pad_2d(0) {}
    virtual ~ChallengeBattleManager() {}  // slot 0
    // 2.0.0's symbols name it. btl::BattleManager::Initialize calls it after DataManager's create. What it
    // does: allocates the unit's ChallengeBattleManager (the new cites "battle/challenge_battle_manager.cpp"), whose PtrSingleton
    // constructor asserts get()==0.
    static void Create();
    // 2.0.0's symbols name it. What it does: deletes that object; btl::BattleManager::Finalize
    // calls it between BladeArtsManager::Destroy and DataManager's (the reverse of the create order).
    static void Destroy();
    // 2.0.0's symbols name it. btl::BattleManager::update calls it with its update info between
    // CharacterManager::Update and BladeArtsManager::Update (the managers' static Update(const fw::UpdateInfo&) slot).
    // What it does: the singleton's UpdateProc(info).
    static void Update(const fw::UpdateInfo& info);
    // the original's symbol names it; btl::BattleManager::update calls it between CharacterManager::PreUpdate and
    // BladeArtsManager::PreUpdate
    static void PreUpdate(const fw::UpdateInfo& info);
    // 2.0.0's symbols name it (a const member that reads no ChallengeBattleManager). What it does: BattleGlobal's pad_5c50
    // (BattleCharacter::DropItem).
    float GetDropEtherCubeRate() const;

    // 2.0.0's symbols name them. What they do: IsProc: pad_26 != 0 (25 callers: BattleGlobal::PreUpdateProc,
    // BattleManager::CheckBattle, Utility::IsEnableEventStart, ...)
    bool IsProc() const;
    // NotifyStartTelop: TalkManager::PlayNarrationVoice(0x30, 0, 0), then pad_1c = 2.75
    // 2.0.0's symbols name them. What they do: release pad_8 and reset pad_10..pad_2d
    // (GfMenuReference::setBattleTime(0), DataManager's SetPartyGauge(0, false), gf::GfMenuObjBtlTime::reset); Start
    // only while pad_26 is 0 and then loads pad_20/pad_22 from lbl_7100EB7DBC and sets pad_26; End only while pad_26 is
    // set, clears it and sets bit 15 of a halfword in each of DataManager's 18 entries; Retry only while pad_26 is set.
    void Start();
    void End();
    void Retry();
    void NotifyStartTelop();
    // IsResult / IsExit: pad_26 above 149 / above 199
    bool IsResult() const;
    bool IsExit() const;
    // 2.0.0's symbols name it. What it does: returns the byte at 0x8 of the .bss object 0x7100EB7DBC (this unused).
    bool IsWaveFinished() const;
    // SetBGMID: pad_24 = value while pad_26 is set (EnemyParameter's SetupBGM passes its BGM id)
    void SetBGMID(unsigned int value);
    // AddScoreByID: while pad_26 is set, AddScore(BDAT 78's "Score" of id, false), then character's
    //   DropEtherCubeByScoreID(id) when one is given (BattleCharacter::DeadProc, CharacterParameter::SetElementalComboID)
    void AddScoreByID(int id, BattleCharacter* character);
    // AddScore: while pad_26 is set, gf::SCOM_ADD_SCORE::create(score) for a score, unless pad_29 is 2 or 3 and not
    //   always (BattleCharacter::DeadProc)
    void AddScore(int score, bool always);
    // AddEtherCube: gf::SCOM_ADD_ECUBE::create(value) for a value while pad_26 is set
    void AddEtherCube(int value);
    // GetWinWalkRestTime: while pad_26 is 160, BtlSystemBalanceAccess's pad_120 less pad_18 (0 when not above 0, -1
    //   otherwise) and in flag whether it is at most 5, or not above 0, or below 30% of pad_120
    float GetWinWalkRestTime(bool& flag) const;
    // IsRetryProc: pad_26 is 201 and GfGameManager::isFadeout()
    bool IsRetryProc() const;
    // IsWaveInterval: pad_26 in 100..149
    bool IsWaveInterval() const;
    // IsEnableAutoHeal: false without pad_26; with pad_29 3 whether CharacterManager has no battle enemy, else
    //   IsWaveInterval()
    bool IsEnableAutoHeal() const;
    // IsWin: pad_26 in 157..161
    bool IsWin() const;
    // IsEnableOperate / IsEnableEnemyBattle / IsEnableReturnHome: true without pad_26; else pad_2b != 0 / pad_26 in 50..149 /
    //   pad_29 == 3
    bool IsEnableOperate() const;
    bool IsEnableEnemyBattle() const;
    bool IsEnableReturnHome() const;
    // 2.0.0's symbols name it. What it does: whether getBattleArenaMenuInfo()'s m_value4 (seconds) less pad_10 is at
    // most 300.
    bool IsChallengeTimeWarning() const;
    // 2.0.0's symbols name it. What it does: the per-frame update: pad_26's state machine (1..3 start, 51 and
    // 101..104 the waves, 151..156 the loss and its retry window, 157..161 the win, 201/202 the exit), then the
    // gimmick's suspend, pad_2b, the time pad_10 and the state's time pad_14/pad_18, the start telop's narration
    // (pad_1c), RetireProc and the BGM id pad_24.
    void UpdateProc(const fw::UpdateInfo& info);
    // 2.0.0's symbols name it. What it does: true once pad_2c is set; otherwise, while no pause, camera direction or
    // chain attack runs, sets pad_2c on game over, or pad_2c and pad_2d once pad_10 reaches the challenge's seconds.
    bool CheckChallengeFailure() const;
    // 2.0.0's symbols name it. What it does: drops ether cubes (gf::GfFobjDropitem::emitDropitems) around the
    // controlled character while the arena menu info's float at 0xAD4 is above 0.
    void DropLoseEtherCube();
    // 2.0.0's symbols name it. What it does: pad_27's retire step: 0 asks (common window 290, pause 7) when the pad's
    // button allows it, 1 waits for the window's answer (pad_28 = 2 or 3, pad_26 = 153).
    void RetireProc(const fw::UpdateInfo& info);

    // the context UpdateProc opens GfMenuObjBtlchTelop's menu with (states 151 and 158); released (and cleared) by
    // Start/End/Retry and by UpdateProc once it terminates
    ::gf::GfMenuCallContext* pad_8;
    float pad_10;
    float pad_14;
    float pad_18;
    float pad_1c;
    unsigned short pad_20;
    unsigned short pad_22;
    unsigned short pad_24;
    unsigned char pad_26;  // 0 while no challenge battle runs; most functions test it
    unsigned char pad_27;
    unsigned char pad_28;
    unsigned char pad_29;
    unsigned char pad_2a;
    unsigned char pad_2b;
    mutable unsigned char pad_2c;  // CheckChallengeFailure (const) sets it
    mutable unsigned char pad_2d;  // CheckChallengeFailure (const) sets it
};

}  // namespace btl

#endif
