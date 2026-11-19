#ifndef CLASSES_BTL_BATTLEGLOBAL_H
#define CLASSES_BTL_BATTLEGLOBAL_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/btl/ButtonChallenge.h"
#include "classes/fw/Camera.h"
#include "gf/SoundHandle.h"

namespace btl { class BattleGlobal; }
namespace gf { class GfComEffectCaster; class GF_SE_CATEGORY_HANDLE; class GfMenuCallContext; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; }
namespace btl { class ShakeCameraManager; struct ARTS_DATA; class BattleCharacter; }

namespace btl {
// The tutorial condition BattleGlobal::Tutorial takes (the type's name is the symbol's; its values are not named).
enum BTL_TUTORIAL_COND {};
// the battle difficulty (SetupDifficultyData: 0, 2, 3 pick balance rates, 4 repeats); enumerators not known
enum BTL_DIFFICULTY {};

// table 0x7100B3A3E0
class BattleGlobal : public ::mm::mtl::PtrSingleton< ::btl::BattleGlobal> {
public:
    // 2.0.0's symbols name these parameter types; their values are not named
    enum FUTURE_VIEW_BTN_RESULT_TYPE {};  // FutureViewButtonChllengeResultProc's result (0, 1)
    enum ATTACK_ONCE_SE_TYPE {};  // EndAttackSE / IsPlayAttackSE (0, 1)
    // AddOCGTime's kind: an index into its 13 Bdat 0x36 columns AddTimeBC1-3, AddTimeDC1-4, AddTimeFC2-7
    enum OCG_TIME_TYPE {};
    enum SE_ONCE_ID {};  // CheckOnceSE's flag index
    BattleGlobal();
    virtual ~BattleGlobal();  // slot 0
    void Initialize();
    static void Create();
    static void Destroy();
    static void PreUpdate(const fw::UpdateInfo& info);
    static void Update(const fw::UpdateInfo& info);
    static void PostUpdate(const fw::UpdateInfo& info);
    void PreUpdateProc(const fw::UpdateInfo& info);
    void UpdateProc(const fw::UpdateInfo& info);
    void PostUpdateProc(const fw::UpdateInfo& info);
    // the original's symbol names it; BattleManager::gevMapjump calls it on a map change (GEV 2)
    void NotifyMapChange();
    void BattleEndInitialize(bool);  // NotifyMapChange passes true
    void Tutorial(BTL_TUTORIAL_COND cond, int, void*);
    // clears the end conditions and the battle flags, which (unless the game is over) it first copies into local
    // game flags 0xC710 and up
    void ResetTutorialByBattleEnd();
    // reads the anti-blade area's revision row (Bdat 0x35) into m_mapRev when the area changes
    void UpdateMapRev();
    // whether a battle can run: not while GfGameManager stops battles
    bool IsEnableBattle() const;
    void SetElementalComboImmortal(gf::GF_OBJ_HANDLE* handle);
    void DeleteUniteComboDirection();
    // starts the unite combo direction registered for pad_5d30's character (Bdat 0x44 row pad_5d3d): its camera
    // ("Camera" 1/2, pushed while "Waitf") and its slow motion ("Slow", "Slowf"); once (pad_5d3f)
    void StartUniteComboDirection();
    // the unite combo direction's frame: waits pad_5d2c (6 s) to start it, then shows its UI and voice at the row's
    // "UIStartf"/"UIEndf"/"Voicef" frames (pad_5d3e bits) and deletes it once the camera has played and pad_5d28 ran
    // out (or, without camera, once its slow motion ended)
    void UpdateUniteComboDirection(const fw::UpdateInfo& info);
    // sets the difficulty's rates (pad_5c04-pad_5c58) unless pad_bit1 is set or nothing changed (difficulty 4 again:
    // every 37th call)
    void SetupDifficultyData(BTL_DIFFICULTY difficulty);
    void SetPause(int kind, bool pause);
    void DeleteSlow(unsigned int id);
    // deletes every slow-motion request's effect on its character (on a copy of the requests)
    void DeleteSlowAll();
    // makes the special effect of the type (0: "cmn_020_007") after deleting the one there was
    void CreateSpecialEffect(int type);
    // the symbols name it through InputLeverGachaButton's LEVER_GACHA_DATA::BUTTON; its members are not known
    struct LEVER_GACHA_DATA {
        // InputLeverGachaButton's button (0-3; compared unsigned, as an enum of non-negative enumerators, whose names
        // are not known)
        enum BUTTON : unsigned int {};
    };
    // a lever gacha button press: whether it counted (each button counts again once its time ran out)
    bool InputLeverGachaButton(LEVER_GACHA_DATA::BUTTON button);
    // a lever gacha stick angle (radians): whether it counted
    bool InputLeverGachaStick(float angle);
    // starts a future view on the handle's character for time, unless one runs or its cool time does not end
    void RegisterFutureView(gf::GF_OBJ_HANDLE* handle, float time, unsigned int id, int type, int arts, int value);
    void DeleteSpecialEffect(int type);
    // deletes the elemental combo's slow-motion request and sets its slowed effects back to speed 1
    void DeleteElementalComboSlow();
    void DeleteElementalComboCamera();
    // DeleteElementalComboCamera, then handle and camera become the elemental combo's (the camera is not pushed)
    void RegisterElementalComboCamera(::mm::mtl::IntrusivePtr<fw::Camera> camera, gf::GF_OBJ_HANDLE* handle);
    // a slow-motion request; its id (0 when none was taken)
    unsigned int RegisterSlow(float, float, float);
    // replaces the elemental combo's slow-motion request and slows its registered effects to 100
    void RegisterElementalComboSlow();
    // the effect (with its caster; none: EffectManager's) of that side to slow with the elemental combo, slowed now
    // when the request runs
    void RegisterElementalComboInvalidSlowEffect(int side, unsigned int effect, gf::GfComEffectCaster* caster);
    // runs the character's dynamics (GfComDynamics, component 8) at speed percent while the slow-motion request lasts
    void SetSlowDynamicsSpeed(unsigned int id, int chara, unsigned int speed);
    bool IsGameOver() const;
    // whether the battle is paused for kind (GfGameTarget's selectRight/selectLeft pass -1: any)
    bool IsPause(int kind) const;
    // the enemy linked to join at the position, (GF_OBJ_HANDLE*)-1 for none (Utility::AI_GetLinkCharacterID)
    gf::GF_OBJ_HANDLE* GetLinkJoinEnemyHandle(const mm::Vec3& pos);
    // records an enemy that joined the battle through a link (CharacterManager's character for the handle), unless its
    // parameter's slot 65 (IsBlade(true)) holds; raises m_linkJoinLevel to its level (+15 when named)
    void NotifyLinkJoinBattle(gf::GF_OBJ_HANDLE* handle);
    // counts one more chain (up to 0xFFFFFFF); when asked, plays narration voice 5 + level once the count reaches the
    // level's threshold (25, 50, 100) and goes up a level
    void AddChainCount(bool narrate);
    int GetElementalComboStage(int) const;
    // GfGameTarget::updateImpl calls it once its near-target hold outlasts its parameter's time
    void NotifyShiftTimeOver();
    // 2.0.0's symbols name it. What it does: clears flag bits 40 and 41 (bits 0 and 1 of the byte at 0x83CF).
    void NotifyShiftNone();
    // 2.0.0's symbols name it. A member: ButtonChallenge passes
    // PtrSingleton<BattleGlobal>::sys(). What it does: tests flag bits at 0x83CE (bits 17 and 18 both set, or bit 3).
    // ButtonChallenge::OpenButtonChallenge skips opening its menu when it holds.
    bool IsButtonChallengeAutoSuccess() const;
    // 2.0.0's symbols name it. A member: as IsButtonChallengeAutoSuccess. What it does:
    // tests bits 1 and 2 of the byte at 0x83D0 both set; ButtonChallenge::OpenButtonChallenge asks it for kinds other than 0.
    bool IsPlayerAutoOperate() const;
    // 2.0.0's symbols name it. A member: as
    // IsButtonChallengeAutoSuccess. What it does: ButtonChallenge::ResultProc passes it the challenge id and whether the result was
    // -1 (failed), for challenges of kind 3.
    // the result is an int switched on (0 and 1): 3.0.1 compares it with 1, then with 0
    void FutureViewButtonChllengeResultProc(unsigned int id, FUTURE_VIEW_BTN_RESULT_TYPE result);
    // 2.0.0's symbols name it. A member: ai::AiData::isValid passes PtrSingleton<BattleGlobal>::sys(). What it does: returns bit 1 of
    // the byte at 0x83D0; while it is clear, isValid refuses the party's leader driver (GfGameParty::isLeaderDriver).
    bool IsValidAutoMode() const;

    // One step of an elemental combo (1.0.0's name: GetElementalComboEffectFlagByFlow takes one); the field names
    // are not the original's
    struct ELEMENTAL_COMBO_FLOW_DATA {
        unsigned char pad_0[9];
        unsigned char prevId;  // the step before this one (GetFirstStageElementalComboData walks back to stage 1)
        unsigned char pad_a;
        unsigned char stage : 3;  // GetElementalComboStage
        // the element whose value the step bursts (ElementalComboManager::Burst; the name is not the original's)
        unsigned char element : 4;
        unsigned char pad_bit7 : 1;
        // the step after this one by index (an empty step: BattleGlobal's pad_5bf0 for stage 1-2 while
        // m_challengeAnySuccess is set and pad_5c02 is 2, unless the bool is set)
        unsigned char GetNextID(int index, bool) const;
    };

    // one slow-motion request (1.0.0's name: SLOW_PROC_DATA::Finalize); the field names are not the original's
    // a random camera shake (1.0.0's name); the field names are not the original's: ShakeCameraRandom copies them
    // into a ShakeCameraElementRandom
    struct SHAKE_CAMERA_RANDOM_PARAM {
        int type;
        float amplitude;
        float interval;  // at least 1/30
        bool useFrameTime;
        float fadeInTime;
        float duration;
        float fadeOutTime;
        bool vertical;
    };
    void ShakeCameraRandom(const SHAKE_CAMERA_RANDOM_PARAM& param);
    // a camera shake along an axis (1.0.0's name); the field names are not the original's: ShakeCameraAxis copies them
    // into a ShakeCameraElementAxis (axisType 0) or a ShakeCameraElementCameraAxis (1-6)
    struct SHAKE_CAMERA_AXIS_PARAM {
        int type;
        float amplitude;
        float interval;  // at least 1/30
        bool useFrameTime;
        mm::Vec3 axis;  // axisType 0's
        int axisType;  // 0 the axis above; 1-6 the camera's x, -x, y, -y, -z, z
        int stepCount;
        int repeat;
        bool flag;
    };
    void ShakeCameraAxis(const SHAKE_CAMERA_AXIS_PARAM& param);

    struct SLOW_PROC_DATA {
        float pad_0;  // RegisterSlow's first argument (RegisterElementalComboSlow passes 0.01)
        float deleteDelay;  // DeleteDelayElementalComboSlow sets it; RegisterSlow's second argument
        float pad_8;  // DeleteDelayElementalComboSlow clears it; RegisterSlow stores minus its third argument (or 0)
        unsigned int id;  // IsSlowProc looks it up
        unsigned char dynamicsChara;  // SetSlowDynamicsSpeed's character
        unsigned char pad_11;
        unsigned short dynamicsSpeed;  // SetSlowDynamicsSpeed's speed, in percent
        // 1.0.0's name; sets the character's dynamics back to speed 1 (no copy of its own in 3.0.1: inline)
        void Finalize();
    };
    // the request with this id, or none (inline: no copy of its own in either version)
    SLOW_PROC_DATA* GetSlowProcData(unsigned int id) {
        if (id != 0) {
            for (SLOW_PROC_DATA& data : m_slowProc) {
                if (data.id == id) {
                    return &data;
                }
            }
        }
        return nullptr;
    }
    void DeleteDelayElementalComboSlow(float delay);
    // 1.0.0's GetSlowProcDataConst (no copy of its own in 3.0.1: inline)
    const SLOW_PROC_DATA* GetSlowProcDataConst(unsigned int id) const {
        if (id != 0) {
            for (const SLOW_PROC_DATA* it = m_slowProc.begin(); it != m_slowProc.end(); ++it) {
                if (it->id == id) {
                    return it;
                }
            }
        }
        return nullptr;
    }
    bool IsSlowProc(unsigned int id) const;

    const ELEMENTAL_COMBO_FLOW_DATA& GetElementalComboFlowData(int id) const;  // entry 0 for an id out of range
    int GetFirstStageElementalComboData(int id) const;
    int GetNormalAttackArtsID(int chara, int weapon, int step) const;
    enum JINGLE_TYPE {};  // 1.0.0's name (RequestJingle, PlayJingle); its values are not recovered
    // the "tag" string of row id (1 to 223) of BDAT table 0x3B when its "delivered" column is set, else null; cached
    // in m_seTags (1.0.0's name; BattleCharacter's PlaySE/PlaySystemSE/SetAction call it)
    const char* GetSeTag(int id) const;
    void RequestJingle(JINGLE_TYPE type);  // 1.0.0's and 2.0.0's RequestJingle(JINGLE_TYPE)
    bool IsJinglePlaying() const;
    void PlayJingle(JINGLE_TYPE type);
    void StopJingle(bool clear);
    void FinalizeJingle();
    // notifies TalkManager's trigger with the voice of a random party character of BDAT id 0x452 (0x452 or 0x453
    // for kinds 1-2)
    void SpeakFutureViewVoice(int trigger, int kind);
    void PlayErrorSE();  // 1.0.0's and 2.0.0's PlayErrorSE
    // 2.0.0's symbols name InitializeIraTalentArtsID, GetElementalComboFlowDataFast.
    // They read this BattleGlobal's fields (callers pass PtrSingleton<BattleGlobal>::sys()). What they do: Initialize:
    // clears pad_8374[0-8], then keeps in pad_8374[driver - 17] the last row of BDAT table 1 whose "IrType" is 3 for
    // each "Driver" 17-25
    void InitializeNormalAttackArtsID();
    void InitializeIraTalentArtsID();
    unsigned short GetIraTalentArtsID(unsigned int id) const;  // pad_8374[id - 17]; PlayerParameter::InitializeArtsPalette
    const ELEMENTAL_COMBO_FLOW_DATA& GetElementalComboFlowDataFast(int id) const;  // the flow entry, no range check
    // the elements (bit element) of the final steps (stage above 2) reachable from step id through the children
    // pad_0[1-8] whose bit is in mask (BattleCharacter::AI_BladeChange), masked by it
    unsigned int GetElementalComboEffectFlag(int id, unsigned int mask) const;
    bool IsFutureView() const;  // pad_5d54 != 0 (13 callers: BattleCharacter input/AI, CheckBattle, ...)
    void ResetBGM();  // clears pad_83b2, sets pad_83b4 to 0xFF (BattleManager::CheckBattle)
    // takes id (a row of BDAT table 0xB1) into pad_83b2 when none is held (pad_83b4 0xFF) or its "Priority" is
    // above the held one's (kept in pad_83b4); whether it took it
    bool SetBGM(unsigned int id);
    bool IsEndTutorialCondition(BTL_TUTORIAL_COND index) const;  // tests flag index of pad_83b8
    void ClearEndTutorialConditionFlag(BTL_TUTORIAL_COND index);  // clears flag index of pad_83b8
    void SetTutorialBattleFlag(int index);  // sets flag index of pad_83bc
    bool CheckOnceSE(SE_ONCE_ID index) const;  // sets flag index of pad_83bf; false when it was set already
    bool IsEndFutureViewCoolTime() const;  // pad_5d60 <= 0
    bool IsFutureViewEnemy(gf::GF_OBJ_HANDLE* handle) const;  // pad_5d54 != 0 and pad_5d48 is handle
    bool IsFutureViewFilter() const;  // pad_5d54 in 3-7
    bool IsKakuseiFinished() const;  // pad_bit18
    bool IsMindEyeFinished() const;  // pad_bit21
    void AddPartyPerfectAvoidNum(bool side, int add);  // adds to pad_83c0[!side], kept in 0-255 (CharacterParameter::SetBuff)
    bool UsePartyPerfectAvoid(bool side) const;
    void SwitchPlayerAutoOperate();
    // the next ones read pad_5d9c (and do nothing, or answer false) while m_challengeAnySuccess is set
    bool IsOCG() const;  // pad_5d9c != 0
    void ResultOCG();  // raises pad_5d9c from 1-2 to 3
    // closes the OCG menu, restores the battle BGM (or the challenge battle's) and resets the OCG state
    void EndOCG();
    bool IsOCGResult() const;  // pad_5d9c > 2
    void AddOCGDamage(int index, unsigned int add);  // adds to pad_5d78[index] (0-2) while pad_5d9c != 0
    bool IsOCGOrder(bool check) const;  // pad_bit22, or check and pad_5dc0 >= 0
    void StartOCG(float time, int index);
    // the bonuses for pad_5da0's count from Bdat 0x36 (DmgNum*, RecastNum*, ResistNum*)
    void SetupOCGBonus();
    void ContinueOCG();
    void AddOCGCount(const ARTS_DATA* arts);
    void AddOCGTime(OCG_TIME_TYPE type);
    bool IsKakuseiOrder(bool check) const;  // pad_bit16, or check and pad_5db8 >= 0
    bool IsMindEyeOrder(bool check) const;  // pad_bit20, or check and pad_5dbc >= 0
    // takes the party leader into m_leaderHandle and m_controlHandle; during a chain attack m_controlHandle becomes
    // the driver of the chain's group (ChainAttackManager::GetGroupIndex)
    void SetupLeaderAndControlCharacterHandle();  // flips pad_bit50 while pad_bit49 is set
    void GetFutureViewArtsData(ARTS_DATA& data) const;  // DataManager's arts data for pad_5d68 (GfEnemyBattleProperty::Update)
    // the camera shake's adjustment, when there is a shake manager
    void ApplyBattleCameraAdjustment(mm::Vec3& pos, mm::Vec3& target);  // counts pad_83c0[!side] down; false when it was 0

    // One attack's record, found by its id (CreateAttackData hands the ids out). The type and field names are not the
    // original's (1.0.0's GetAttackDamageDataNum/GetAttackDamageDataConst read the records). Its bit-fields from 0x8 on
    // are separate storage runs: 64 bits at 0x8, 16 at 0x10, 8 at 0x12.
    struct AttackDamageData {
        unsigned int id;
        int damage;  // AddAttackDamage adds to it, GetAttackDamage returns it
        unsigned int damageRate : 27;  // 16.16 fixed point (GetDamageRate), 1.0 when created
        unsigned int attr : 5;  // SetAttackAttr/GetAttackAttr; 9 when created, read as none (-1)
        unsigned int hitCount : 7;  // AddAttackDamage counts each further hit
        unsigned int : 19;
        unsigned int pad_bit58 : 6;  // 1 when created
        unsigned int : 0;  // the flags below are a storage unit of their own (32-bit loads, no 64-bit one)
        bool justDistanceAttack : 1;  // SetJustDistanceAttack/IsJustDistanceAttack
        bool resistantBreakDamageEnd : 1;  // SetResistantBreakDamageEnd; IsEnableResistantBreakDamage while clear
        bool chainAttack : 1;  // ChainAttackManager::IsProc(true) when created
        bool permitArts : 1;  // SetPermitArts/IsPermitArts
        bool noShootBullet : 1;  // SetShootBullet stores the negation; IsShootBullet while clear
        bool damageRateChanged : 1;  // AddDamageRate/MulDamageRate set it when asked; GetDamageRate reports it
        bool endDropHealPot2 : 1;  // SetEndDropHealPot2/IsEndDropHealPot2
        bool endCriticalRecastEnhance : 1;  // SetCriticalRecastEnhanceEnd/IsEndCriticalRecastEnhance
        bool pad_bit8 : 1;
        bool pad_bit9 : 1;
        bool pad_bit10 : 1;
        bool pad_bit11 : 1;
        bool angryArtsAttack : 1;  // SetAngryArtsAttack/IsAngryArtsAttack
        bool updated : 1;  // set by every lookup
        unsigned int : 2;
        unsigned char : 0;  // 16-bit flags, then a byte of flags of its own (16- and 8-bit stores)
        bool enableAddElementalBall : 1;  // SetEnableAddElementalBall/IsEnableAddElementalBall, set when created
        bool validAttackRange : 1;  // SetValidAttackRange/IsValidAttackRange, set when created
        bool pad_bit18 : 1;
        bool pad_bit19 : 1;
        unsigned char pad_bit20 : 4;
        unsigned char charaIndex;  // CharacterManager's index of the attacker (SearchCharacter)
    };

    // a new attack record for the attacker's handle; its id
    unsigned int CreateAttackData(gf::GF_OBJ_HANDLE* handle);
    // adds damage to the record (unless create, or the handle is not -1 and not its attacker's), else makes a
    // record; the record's damage
    int AddAttackDamage(gf::GF_OBJ_HANDLE* handle, unsigned int id, unsigned int damage, bool create);
    void UpdateAttackData(unsigned int id);
    int GetAttackDamage(unsigned int id) const;
    // the handle of the record's attacker (charaIndex), -1 when there is no record
    gf::GF_OBJ_HANDLE* GetAttackMainTargetHandle(unsigned int id) const;
    void SetAttackAttr(unsigned int id, int attr);
    int GetAttackAttr(unsigned int id) const;
    void SetEndDropHealPot2(unsigned int id);
    bool IsEndDropHealPot2(unsigned int id) const;
    bool IsEndCriticalRecastEnhance(unsigned int id) const;
    void SetJustDistanceAttack(unsigned int id);
    bool IsJustDistanceAttack(unsigned int id) const;
    void SetCriticalRecastEnhanceEnd(unsigned int id);
    void SetEnableAddElementalBall(unsigned int id, bool enable);
    bool IsEnableAddElementalBall(unsigned int id) const;
    void SetResistantBreakDamageEnd(unsigned int id);
    bool IsEnableResistantBreakDamage(unsigned int id) const;
    void SetPermitArts(unsigned int id);
    bool IsPermitArts(unsigned int id) const;
    void SetShootBullet(unsigned int id, bool shoot);
    bool IsShootBullet(unsigned int id) const;
    void SetValidAttackRange(unsigned int id, bool valid);
    bool IsValidAttackRange(unsigned int id) const;
    // 1.0.0's and 2.0.0's AddDamageRate/MulDamageRate: the same code in the same place after SetDamageRate
    void AddDamageRate(unsigned int id, float rate, bool markChanged);
    void MulDamageRate(unsigned int id, float rate, bool markChanged);
    float GetDamageRate(unsigned int id, bool* changed) const;
    // 2.0.0's symbols name SetAngryArtsAttack, SetTalentMinochiAttack, IsTalentMinochiAttack, IsAngryArtsAttack,
    // SetAchieveBackAttack, IsAchieveBackAttack, IsChainAttackDamage, SetFutureViewCalc, GetFutureViewResult. They sit
    // among BattleGlobal's attack accessors and look the record up in this BattleGlobal's records. What they do:
    void SetAngryArtsAttack(unsigned int id);  // sets the flag IsAngryArtsAttack reads
    void SetTalentMinochiAttack(unsigned int id);  // sets flag bit 11
    bool IsTalentMinochiAttack(unsigned int id) const;  // flag bit 11 (false when there is no record)
    bool IsAngryArtsAttack(unsigned int id) const;  // the flag SetAngryArtsAttack sets
    void SetAchieveBackAttack(unsigned int id, bool on);  // stores flag bit 10
    bool IsAchieveBackAttack(unsigned int id) const;  // flag bit 10
    bool IsChainAttackDamage(unsigned int id) const;  // whether a chain attack was running when the record was made
    void SetFutureViewCalc(unsigned int id, bool on);  // clears flag bit 8, stores flag bit 9
    int GetFutureViewResult(unsigned int id) const;  // 1 when flag bit 8 is set, else 2 when bit 9 is, else 0
    // 3.0.1's symbols spell these SetDamageRate(unsigned int, float, bool) and Utility::AchieveCondition (1.0.0's
    // positions); their code takes this BattleGlobal, an id and an int (no float) and reads the record's byte at 0x12
    void EndAttackSE(unsigned int id, ATTACK_ONCE_SE_TYPE index);  // clears pad_bit18 (index 0) or pad_bit19 (index 1)
    bool IsPlayAttackSE(unsigned int id, ATTACK_ONCE_SE_TYPE index) const;  // pad_bit18 (0) or pad_bit19 (1); true otherwise

    // every attack accessor's lookup (inline: no copy of its own in either version)
    AttackDamageData* findAttackData(unsigned int id) const {
        if (id != 0) {
            for (AttackDamageData* it = m_attackData.begin(); it != m_attackData.end(); ++it) {
                if (it->id == id) {
                    it->updated = true;
                    return it;
                }
            }
        }
        return nullptr;
    }

    // the party's leader driver, as SetupLeaderAndControlCharacterHandle last read it (the name is not the original's)
    gf::GF_OBJ_HANDLE* m_leaderHandle;
    // the character the player controls: BattleCharacter::IsControlCharacter compares its handle with it (the name is
    // not the original's)
    gf::GF_OBJ_HANDLE* m_controlHandle;
    // the target BattleCharacter::SetAttackTarget gives the controlled character (the name is not the original's)
    gf::GF_OBJ_HANDLE* m_controlTargetHandle;
    unsigned char pad_20[0x10];
    // GetSeTag's cache of BDAT 0x3B's "tag" strings, by row id (the name is not the original's)
    mutable const char* m_seTags[0xE0];
    ShakeCameraManager* m_shakeCamera;  // ApplyBattleCameraAdjustment (the name is not the original's)
    // the button challenge in progress (the destructor destroys it in place; the name is not the original's)
    ButtonChallenge m_buttonChallenge;
    // the debuff mask: bit n - 1 for buff n (CharacterParameter::CheckDebuff walks it with IsBuff; meaning
    // otherwise unknown)
    unsigned long pad_778;
    // an enemy that joined through a link (NotifyLinkJoinBattle; the names are not the original's)
    struct LinkJoinEnemy {
        gf::GF_OBJ_HANDLE* handle;
        float time;  // 30 when it joins
    };
    // the enemies that joined through a link, nearest first asked by GetLinkJoinEnemyHandle (the name is not the
    // original's)
    ::mm::mtl::FixedVector<LinkJoinEnemy, 8> m_linkJoinEnemy;
    // the special effects CreateSpecialEffect made, by type (DeleteSpecialEffect; the type and names are not the
    // original's)
    struct SpecialEffect {
        unsigned int handle;  // the EffectManager handle
        int type;  // CreateSpecialEffect's type (-1 once deleted)
    };
    ::mm::mtl::FixedVector<SpecialEffect, 1> m_specialEffect;
    // a fixed vector the destructor clears (element type unknown: only its byte size, 0x90, is known)
    ::mm::mtl::FixedVector<unsigned int, 36> pad_818;
    unsigned int pad_8b0;  // NotifyMapChange clears it (meaning unknown)
    unsigned char pad_8b4[0x4];
    // the slow-motion requests (the name is not the original's)
    ::mm::mtl::FixedVector<SLOW_PROC_DATA, 20> m_slowProc;
    float pad_a50;  // Utility::IsPause holds while it is <= 0
    unsigned char pad_a54[0x4];
    unsigned int m_nextSlowId;  // RegisterSlow's next id, never 0 (the name is not the original's)
    unsigned char pad_a5c[0x40];
    // PlayerParameter::BattleStart copies it into CharacterParameter's pad_20; meaning unknown
    int pad_a9c;
    unsigned char pad_aa0[0x4];
    // BattleManager::Update stores its game-over timer (pad_10) divided by 15 there each frame (meaning unknown)
    float pad_aa4;
    unsigned int m_nextAttackId;  // CreateAttackData's next id, never 0 (the name is not the original's)
    unsigned char pad_aac[0x4];
    // the attack records (the name is not the original's); full, AddAttackDamage drops the oldest
    mutable ::mm::mtl::FixedVector<AttackDamageData, 1000> m_attackData;
    // the elemental combo flow, by combo id (the name is not the original's)
    ELEMENTAL_COMBO_FLOW_DATA m_elementalComboFlow[66];
    // by stage 1-2 and index, what ELEMENTAL_COMBO_FLOW_DATA::GetNextID returns for an empty step
    unsigned char pad_5bf0[2][9];
    unsigned char pad_5c02;  // ELEMENTAL_COMBO_FLOW_DATA::GetNextID reads pad_5bf0 while it is 2
    unsigned char pad_5c03[0x1];
    // EnemyParameter::SetResistantAttr adds (it - 1) * 0.08 to a nonzero elemental awake chance unless pad_5c58 is
    // set (meaning unknown)
    // SetupDifficultyData sets the next ones from GfGameManager::getBtlDifParam(1-12), percentages as rates
    float pad_5c04;  // param 1
    float pad_5c08;  // param 2
    float pad_5c0c;  // param 3
    float pad_5c10;  // param 4
    float pad_5c14;  // 1 / param 5 (0 when that is not above 1e-6)
    float pad_5c18;  // 1 / param 11 (likewise)
    // DataManager::AddPartyGauge multiplies every gain by it (the name is not the original's); param 6
    float m_partyGaugeRate;
    float pad_5c20;  // param 7
    float pad_5c24;  // param 8
    float pad_5c28;  // param 9
    float pad_5c2c;  // param 10, as is
    // SetupDifficultyData derives the next ones from pad_5c04 (constants when it is below 1)
    float pad_5c30;
    // EnemyParameter::AddEnhanceBallHateCallback: the least hate it adds, the rate of the hate gap to the hate
    // target it adds, and the recast it adds to random palette slots (meanings inferred, not the original's names)
    float pad_5c34;
    float pad_5c38;
    float pad_5c3c;
    float pad_5c40;
    float pad_5c44;
    float pad_5c48;
    // EnemyParameter::ApplyStatusEnhanceAndDifficulty scales every enhanced value by it (the name is not the
    // original's)
    float m_statusEnhanceRate;
    // the challenge battle unit's GetDropEtherCubeRate returns it; meaning unknown
    float pad_5c50;
    unsigned char pad_5c54;  // SetupDifficultyData's difficulty
    unsigned char pad_5c55;  // SetupDifficultyData's count of repeated calls for difficulty 4
    bool pad_5c56;  // getBtlDifParam(12) above 1
    bool pad_5c57;  // pad_5c04 below 1
    bool pad_5c58;  // EnemyParameter::SetResistantAttr skips its pad_5c04 term while it is set (meaning unknown)
    unsigned char pad_5c59[0x3];
    // the lever gacha's input state (the fields of LEVER_GACHA_DATA, declared above; field names are not the original's)
    // per button, the time before it counts again (InputLeverGachaButton)
    float m_leverGachaButtonTime[4];
    // InputLeverGachaStick's stick angles, in 1/10000 radians: the last one that counted (0xFFFF: none) and the latest
    unsigned short m_leverGachaStickAngle;
    unsigned short m_leverGachaStickLastAngle;
    unsigned char pad_5c70;
    unsigned char m_leverGachaCount;  // counts every input that counted (InputLeverGachaButton/Stick)
    bool m_leverGachaInput;  // set by every input that counted
    unsigned char pad_5c73[0x5];
    // the jingle's sound category handle, -1 when none (PlayJingle creates it, FinalizeJingle releases it;
    // IsJinglePlaying; the name is not the original's)
    gf::GF_SE_CATEGORY_HANDLE* m_jingleHandle;
    // the playing jingle (StopJingle stops it; the name is not the original's)
    gf::SoundHandle m_jingleSound;
    JINGLE_TYPE m_jingleType;  // PlayJingle's type (the name is not the original's)
    int m_jingleState;  // PlayJingle sets 1 (the name is not the original's)
    int pad_5c90;  // StopJingle(true) and FinalizeJingle clear it
    unsigned char pad_5c94[0x4];
    // per party character, the anti-blade area's revisions: Bdat 0x35's "KizunaCap", "ArtSp", "nba" flag and
    // "PC%02dAtk"/"PC%02dDef" columns (UpdateMapRev; the names are not the original's)
    struct MapRev {
        unsigned short kizunaCap : 11;
        unsigned short artSp : 4;
        unsigned short nbaClear : 1;  // set when the row's "nba" flag is clear
        unsigned char atk;
        unsigned char def;
        // the constructor's values for every entry (and GetMapDriverRevDataByBdatID's guarded static default)
        MapRev() : kizunaCap(1000), artSp(4), nbaClear(true), atk(100), def(100) {}
    };
    // 2.0.0's symbols name it. GROUP_BLADE_DATA::Initialize passes the party character (1-12) and whether the area's
    // revision applies; m_mapRev's entry for it (nullptr out of range), or a default entry when it does not apply
    const MapRev* GetMapDriverRevDataByBdatID(int chara, bool apply) const;
    // 2.0.0's symbols name it. DataManager::UpdateProc passes a character and its driver; GetMapDriverRevDataByBdatID's entry for the
    // character's m_bdatID, applied unless the driver's parameter slot 75 says otherwise, when it is a player
    // (m_isPlayer) that IsDriver(true) accepts and m_challengeAnySuccess is clear; else nullptr
    const MapRev* GetMapDriverRevData(const BattleCharacter* chara, const BattleCharacter* driver) const;
    MapRev m_mapRev[12];
    int m_mapRevAreaId;  // the anti-blade area id m_mapRev was read for (the name is not the original's)
    // the chain count and the narration level it reached (AddChainCount; the names are not the original's)
    struct ChainCount {
        unsigned int count : 28;
        unsigned int level : 4;
    };
    ChainCount m_chainCount;
    // the elemental combo's work at 0x5CD0: one object of its own (RegisterElementalComboInvalidSlowEffect addresses
    // its slowed casters and effects from its start). The type and field names are not the original's.
    struct ElementalComboWork {
        gf::GF_OBJ_HANDLE* pad_0;  // DeleteElementalComboCamera sets it to -1 (no handle)
        gf::GF_OBJ_HANDLE* m_immortal;  // SetElementalComboImmortal
        // the elemental combo's camera (RegisterElementalComboCamera)
        ::mm::mtl::IntrusivePtr<fw::Camera> m_camera;
        // the effects slowed with the elemental combo, with their casters (none: EffectManager's);
        // DeleteElementalComboSlow sets them back to speed 1
        gf::GfComEffectCaster* m_slowCaster[2];
        unsigned int m_slowEffect[2];
        // the elemental combo's slow-motion request (DeleteDelayElementalComboSlow)
        unsigned int m_slowId;
    };  // 0x38 bytes (4 of tail padding)
    ElementalComboWork m_elementalCombo;
    // ElementalComboManager deletes the unite combo direction when its character is this one, while pad_5d3f is
    // clear (meaning unknown)
    gf::GF_OBJ_HANDLE* pad_5d08;
    // DeleteUniteComboDirection clears the BattleCharacter pad_EF5_0 of its character (meaning unknown)
    gf::GF_OBJ_HANDLE* pad_5d10;
    // the unite combo direction's camera (DeleteUniteComboDirection pops it; the name is not the original's)
    ::mm::mtl::IntrusivePtr<fw::Camera> m_uniteComboCamera;
    // the next ones are what DeleteUniteComboDirection resets (meanings unknown)
    unsigned int pad_5d20;  // a slow-motion request id (DeleteUniteComboDirection deletes it)
    float pad_5d24;  // UpdateUniteComboDirection's frame count (30 per second) since the start
    float pad_5d28;  // StartUniteComboDirection: the camera's "Waitf" frames in seconds
    float pad_5d2c;  // UpdateUniteComboDirection's time before the start (6 s)
    // RegisterUniteComboDirection stores the next four (u16 stores); pad_5d30 is a character index (-1 when reset)
    short pad_5d30;
    unsigned short pad_5d32;
    unsigned short pad_5d34;
    unsigned short pad_5d36;
    // UpdateUniteComboDirection hands the next three to UIManager::DispUniteComboUI
    unsigned short pad_5d38_0 : 5;
    unsigned short pad_5d38_5 : 5;
    unsigned short pad_5d38_10 : 5;
    unsigned short pad_5d38_15 : 1;
    unsigned char pad_5d3a;  // DispUniteComboUI's first two arguments
    unsigned char pad_5d3b;
    unsigned char pad_5d3c;  // SomebodyPraise follows the direction from 3 up
    unsigned char pad_5d3d;  // StartUniteComboDirection's Bdat 0x44 row
    unsigned char pad_5d3e;  // UpdateUniteComboDirection's done steps (bits 0-2)
    unsigned char pad_5d3f;  // see pad_5d08; StartUniteComboDirection sets it once started
    // a vision menu's context, released by hand as m_ocgContext is (NotifyMapChange; the name is not the original's)
    gf::GfMenuCallContext* m_visionContext;
    // IsFutureViewEnemy compares its handle with it while pad_5d54 is non-zero
    gf::GF_OBJ_HANDLE* pad_5d48;
    unsigned char pad_5d50[0x4];
    // non-zero while something runs that many BattleCharacter input/AI functions ask about (IsFutureView);
    // IsFutureViewFilter tests it for 3-7
    int pad_5d54;
    unsigned int pad_5d58;  // an attack record id (FutureViewButtonChllengeResultProc flags that record)
    unsigned char pad_5d5c[0x4];
    float pad_5d60;  // IsEndFutureViewCoolTime tests it for <= 0
    int pad_5d64;  // FutureViewButtonChllengeResultProc acts only for this challenge id
    // an arts reference: data type in bits 0-2, arts id above (GetFutureViewArtsData asks DataManager::GetArtsData for it)
    unsigned short pad_5d68;
    unsigned char pad_5d6a;  // RegisterFutureView's last argument
    // RegisterFutureView: the m_voiceIndex of the characters (in the handle's list) of Bdat id 0x452 and 0x453
    signed char pad_5d6b;
    signed char pad_5d6c;
    unsigned char pad_5d6d;
    unsigned char pad_5d6e;  // FutureViewButtonChllengeResultProc sends a menu event once while it is set, then clears it
    unsigned char pad_5d6f[0x1];
    // the OCG result menu's context (UpdateOCG creates it, EndOCG releases it; the name is not the original's)
    gf::GfMenuCallContext* m_ocgContext;
    // the next ones are what EndOCG resets
    unsigned int pad_5d78[3];  // AddOCGDamage adds to an entry, up to 99999999
    float pad_5d84;  // the time StartOCG sets; AddOCGTime adds to it, up to 99
    float pad_5d88;  // the time AddOCGTime added so far, up to Bdat 0x36's AddTimeMax
    float pad_5d8c;  // SetupOCGBonus's rates (DmgNum*, RecastNum*, ResistNum*)
    float pad_5d90;
    float pad_5d94;
    unsigned int pad_5d98;
    int pad_5d9c;  // IsOCG/DA8C/DAD8/DD4C read it while m_challengeAnySuccess is clear
    unsigned short pad_5da0;  // AddOCGCount's count, up to 999
    unsigned short pad_5da2;  // SetupOCGBonus's levels (DmgNum*, RecastNum*, ResistNum*)
    unsigned short pad_5da4;
    unsigned short pad_5da6;
    unsigned char pad_5da8;  // a character index (UpdateOCG); 90 (none) when reset
    unsigned char pad_5da9;
    unsigned char pad_5daa;  // 1 when reset
    unsigned char pad_5dab[0xD];
    float pad_5db8;  // IsKakuseiOrder tests it for >= 0
    float pad_5dbc;  // IsMindEyeOrder tests it for >= 0
    float pad_5dc0;  // IsOCGOrder tests it for >= 0
    unsigned char pad_5dc4[0x14];
    float pad_5dd8;  // Utility::SetBattleEndEnemyCall stores it
    unsigned char pad_5ddc[0x16];
    // Utility::AI_EnemyKillNum returns it (the name is not the original's)
    unsigned short m_enemyKillNum;
    // each normal attack's arts id by [character][weapon][combo step]; row 0 is the default (GetNormalAttackArtsID;
    // the name is not the original's; the meaning of the indices is inferred from 1.0.0's InitializeNormalAttackArtsID)
    unsigned short m_normalAttackArtsID[32][50][3];
    unsigned short pad_8374[31];  // GetIraTalentArtsID reads entry id - 17
    unsigned short pad_83b2;  // the id SetBGM took; ResetBGM clears it
    unsigned char pad_83b4;  // its priority; ResetBGM sets it to 0xFF (none)
    unsigned char m_jingleRequest;  // RequestJingle (the name is not the original's)
    // pause flags by kind, 8 to a byte; IsPause(-1) asks for any (the name is not the original's)
    unsigned char m_pause[2];
    unsigned char pad_83b8[4];  // flags by index, 8 to a byte (IsEndTutorialCondition tests, ClearEndTutorialConditionFlag clears)
    unsigned char pad_83bc[3];  // flags by index, 8 to a byte (SetTutorialBattleFlag sets)
    mutable unsigned char pad_83bf[1];  // (mutable: 2.0.0's symbols make CheckOnceSE const) flags by index, 8 to a byte (CheckOnceSE tests and sets)
    mutable unsigned char pad_83c0[2];  // (mutable: 2.0.0's symbols make UsePartyPerfectAvoid const) two counters by side (AddPartyPerfectAvoidNum adds, UsePartyPerfectAvoid counts down)
    unsigned char pad_83c2;
    // BattleCharacter::IsDisableActionByTacticsCall needs bit 1 set (with m_challengeAnySuccess; meanings unknown)
    unsigned char pad_83c3_0 : 1;
    unsigned char pad_83c3_1 : 1;
    unsigned char pad_83c3_2 : 6;
    unsigned char pad_83c4[0x2];
    // the blade change type BattleCharacter::CheckForceExit hands to BladeChangeManager::StartBladeChange (3 while
    // pad_bit36 is set; meaning unknown)
    signed char pad_83c6;
    unsigned char pad_83c7;
    // the highest level of an enemy that joined through a link, +15 for a named one (NotifyLinkJoinBattle; the name
    // is not the original's)
    unsigned char m_linkJoinLevel;
    // CharacterManager::UpdateProc stores 3 less m_enhanceCount there, kept in 0-3 (meaning unknown)
    unsigned char pad_83c9;
    // flags (the names are not the original's): one storage unit of 7 bytes, as their reads load it
    // while set, BattleCharacter::NotifyAngryEnd removes the angry effect at once instead of fading it out (the name
    // is not the original's)
    bool m_removeEffect : 1;
    bool pad_bit1 : 1;
    bool pad_bit2 : 1;
    bool m_challengeAnySuccess : 1;  // ButtonChallenge's results 1-3 (not only 3) achieve its condition 0xC
    // the rest of the unit: IsButtonChallengeAutoSuccess reads bits 35, 49 and 50, IsPlayerAutoOperate bits 49 and 50
    unsigned char : 1;
    bool pad_bit5 : 1;  // while set, ChainAttackManager::AddOverKillDamage starts no overkill on a target CharacterParameter::pad_5de protects
    // CharacterManager::PreUpdateProc sets it once an enemy in battle belongs to a quest with an active task
    // (gf::GfQuestUtil::getCurrentEnemyWithEvent; meaning unknown)
    bool pad_bit6 : 1;
    bool pad_bit7 : 1;  // Utility::NotifyNeedPutAwayWeapon sets it
    // pc::StateBattle sets it for the leader: Enter and Update (manual camera) to whether it has a target, Update
    // clears it without the manual camera, Leave clears it (meaning unknown)
    bool pad_bit8 : 1;
    unsigned char : 1;
    bool pad_bit10 : 1;  // ChainAttackManager::Start sets it
    unsigned char : 1;
    bool pad_bit12 : 1;  // DeleteElementalComboCamera clears it
    bool pad_bit13 : 1;  // NotifyMapChange sets it (meaning unknown)
    unsigned char : 1;
    bool pad_bit15 : 1;  // NotifyMapChange clears it (meaning unknown)
    bool pad_bit16 : 1;  // IsKakuseiOrder holds while it is set
    bool pad_bit17 : 1;  // EnemyParameter::MulHate changes no hate while it is set
    bool pad_bit18 : 1;  // IsKakuseiFinished returns it
    unsigned char : 1;
    bool pad_bit20 : 1;  // IsMindEyeOrder holds while it is set
    bool pad_bit21 : 1;  // IsMindEyeFinished returns it
    bool pad_bit22 : 1;  // IsOCGOrder holds while it is set
    // set when the controlled character is told of its death of kind 3 or 4 (pc::StateBattleBase::
    // procMsgObjectNotifyDead; the name is not the original's)
    bool m_controlCharacterDead : 1;
    // while set, IsGameOver holds without asking GfGameManager (the name is not the original's)
    bool m_gameOver : 1;
    // BattleCharacter::CreateDeadEffect creates no dead effect while it or m_removeEffect is set (meaning unknown)
    bool pad_bit25 : 1;
    // while set, CharacterParameter::IsSuspendFightComboTimer holds for the character m_controlTargetHandle names
    // (meaning unknown)
    bool pad_bit26 : 1;
    bool pad_bit27 : 1;  // EnemyParameter::BattleStart sets it for a boss (IsBoss); meaning unknown
    bool pad_bit28 : 1;  // EnemyParameter::BattleStart sets it for a named enemy (IsNamed); meaning unknown
    // CharacterManager::PostUpdateProc sets it to whether an enemy answers BattleCharacter::IsScout (meaning
    // unknown)
    bool pad_bit29 : 1;
    // while set, an enemy's GfEnemyBattleProperty::GetReturnHomeDistance and GetReturnHomeCharacterDistance give
    // BtlSystemBalanceAccess's m_returnHomeDistance instead of its own
    bool pad_bit30 : 1;
    unsigned char : 1;
    // BattleCharacter::SetExitBattle sets it when the controlled character exits with its second argument set (the
    // name is not the original's)
    bool m_controlExitBattle : 1;
    // Utility::AI_IsKillChild returns it (the name is not the original's)
    bool m_killChild : 1;
    unsigned char : 1;
    bool pad_bit35 : 1;  // IsButtonChallengeAutoSuccess holds while it is set
    bool pad_bit36 : 1;  // while set, BattleCharacter::CheckForceExit starts its blade change with type 3 (meaning unknown)
    unsigned char : 1;
    // EnemyParameter::BattleStart sets it for an enemy whose ChrEnArrange row has the Hikari flag; meaning unknown
    bool pad_bit38 : 1;
    // EnemyParameter::BattleStart sets it for an enemy with m_isInvalidWarp; meaning unknown
    bool pad_bit39 : 1;
    // GfGameTarget's selectRight/selectLeft change no target while it is clear (the name is not the original's)
    bool pad_bit40 : 1;
    // NotifyShiftTimeOver sets it while UIManager's pad_bit15 is set; NotifyShiftNone clears it with pad_bit40
    bool pad_bit41 : 1;
    // while set, Utility::IsSatisfyCondition holds for its conditions 0-2, 5-7, 10, 11, 14, 15 and 19 (1, 2, 16-19 with
    // m_challengeAnySuccess) without asking FLD_ConditionList (meaning unknown)
    bool pad_bit42 : 1;
    bool pad_bit43 : 1;  // while set, UIManager::UpdateTutorial shows no queued tutorial (meaning unknown)
    // BattleManager::update stops the battle's time (a zero time step) while pad_bit43 or one of these is set
    bool pad_bit44 : 1;
    bool pad_bit45 : 1;
    // EnemyParameter::BattleStart sets it for an enemy whose ChrEnArrange row has the PGMax flag, unless pad_bit1 is
    // set (then it fills party gauge group 10003 instead); meaning unknown
    bool pad_bit46 : 1;
    // set once PlayErrorSE played its sound, which it then does not play again (the name is not the original's)
    bool m_errorSePlayed : 1;
    bool pad_bit48 : 1;
    bool pad_bit49 : 1;  // IsValidAutoMode returns it; IsPlayerAutoOperate asks for it with pad_bit50
    bool pad_bit50 : 1;
    // while set, DataManager::SetPartyGauge does not raise the party gauge (meaning unknown)
    bool pad_bit51 : 1;
    bool pad_bit52 : 1;  // ResetTutorialByBattleEnd sets it (meaning unknown)
    bool pad_bit53 : 1;  // ResetTutorialByBattleEnd clears it (meaning unknown)
    bool pad_bit54 : 1;  // GROUP_DATA::ProgressCoolTime advances the group's own cool time while it is set
    bool pad_bit55 : 1;  // Utility::AI_IsUseSirenSp returns it
};
}  // namespace btl

#endif
