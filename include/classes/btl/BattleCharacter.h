#ifndef CLASSES_BTL_BATTLECHARACTER_H
#define CLASSES_BTL_BATTLECHARACTER_H

#include "btl/ActionCommand.h"
#include "mm/Vec3.h"

namespace btl { class CharacterParameter; }
namespace btl { struct ARTS_SLOT_DATA; struct ARTS_DATA; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfObj; }
namespace gf { class GfComProperty; }
namespace gf { class GfComEffectCaster; }
namespace gf { class MsgObjectNotifyAsmCallback; }
namespace gf { class MsgObjectNotifyDead; }

namespace btl {
// table 0x7100B3AA08
class BattleCharacter {
public:
    enum ANIM_ID : int;
    BattleCharacter();
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
    // where the character stands to the target, 0-3 (Utility::AI_GetTargetDirection answers it plus 1); the bool
    // it sets makes the answer void
    unsigned char CheckAttackPosition(gf::GF_OBJ_HANDLE* target, bool, bool* out) const;
    // what the enemy's battle states hand an animation annotation to (1.0.0's name)
    void AsmCallback(const gf::MsgObjectNotifyAsmCallback& msg);
    void NotifyChangeAttr(gf::GF_OBJ_HANDLE* handle, unsigned int attr, unsigned int prevAttr);
    bool IsDead(unsigned int) const;
    bool IsControlCharacter() const;
    bool IsControlCharacterGroup() const;
    void SetWeaponType(int type);
    void NotifyDirectDamage(const DIRECT_DAMAGE_DATA& data);
    void AddBladeArtsRecast(int, float);
    void FluctuateKizuna(int, float);
    void AddPartyGauge(float);
    bool IsAngry() const;
    bool IsBlade() const;
    bool IsBattle() const;
    // the arts slot a blade art would use (BladeArtsManager::RegisterBladeArts registers none below 0)
    int IsActBladeArts(int, bool) const;
    // CharacterManager::Register gives the character its handle and its slot index
    void Initialize(gf::GF_OBJ_HANDLE* handle, int index);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: CharacterManager::fn_710007C1E0
    // calls it on every enemy slot in use. What it does: while BattleGlobal's flags allow and the character lives,
    // looks m_bdatID up in BDAT table 0x100 (GfDataBdat::getFP) and updates the character from it.
    void fn_710002B868();
    gf::GF_OBJ_HANDLE* GetRescueTarget() const;
    // the id the AI scripts know the character by: its index for a player character, 100 more for an enemy (the
    // Utility::AI_ getters compute it so; the name is not the original's)
    int GetAiChrID() const {
        return m_isPlayer ? m_index : m_index + 100;
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
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: PlayerParameter's slot 44
    // (fn_7100088F4C) calls it on CharacterManager::GetCharacterConst's character for its m_charaIndex. What it
    // does: with true, unless CheckResistReaction(2, nullptr, true) resists, blows the character back (strength from
    // BDAT table 0x3A's "PowLv%d_%s" row), sets its action 0x10 and notifies TalkManager trigger 0x31; then fades out
    // (or, with BattleGlobal's flag bit 0, removes) the effect whose id it keeps at 0x15C and clears the id.
    void fn_71000424D8(bool);
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

    // the index into m_aActionFuncList (its Action/ActionCommand/ActionCommandEnd triples); the enumerator names
    // follow 1.0.0's function names in that table, they are not the original's. 7 and 10 are 3.0.1's new actions.
    enum ACTION_ID : unsigned char {
        ACTION_IDLE = 0,
        ACTION_PUT_OUT_WEAPON = 1,
        ACTION_PUT_AWAY_WEAPON = 2,
        ACTION_RUN = 3,
        ACTION_KIZUNA_MAX = 4,
        ACTION_ATTACK = 5,
        ACTION_ARTS = 6,
        ACTION_BLADE_ARTS = 8,
        ACTION_BLADE_CHANGE = 9,
        ACTION_SP_ATTACK = 11,
    };
    enum BLADE_TIMER_MODE : int;
    enum ALPHA_PROC_ID : int;
    enum ANIM_SPDATA_TYPE : int;
    enum DROP_ITEM_TYPE : int;
    enum RIMBLOOM_ID : int;

    void SetAction(ACTION_ID id, bool, bool, int param, float value);
    void DropItem(DROP_ITEM_TYPE type, bool);
    void SetRimBloom(RIMBLOOM_ID id, bool on);
    const gf::GfComProperty* GetComPropertyConst() const;
    gf::GfComEffectCaster* GetEffectCaster();
    bool IsOnSlide() const;
    gf::GF_OBJ_HANDLE* GetBuddyTargetObjectHandle() const;
    const char* GetNowAnimationStateName() const;
    float GetAnimationFrame() const;
    void FluctuatePartyGauge(int value);

    gf::GfObj* GetObject() const;
    void NotifyHateElse();
    void SetBladeSupportCondition(int condition);
    bool IsEnableBattleFace() const;
    int GetWeaponType(bool asmType) const;
    void StartBladeTimer(BLADE_TIMER_MODE mode);
    void EndBladeTimer(BLADE_TIMER_MODE mode);
    const ARTS_SLOT_DATA* GetArtsSlotData(int slot, bool, int palette) const;
    void NotifyAngryEnd();
    void ActionRun();
    bool IsBladeArtsEnd() const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: EnemyParameter's fn_7100088B6C
    // calls it on CharacterManager::GetCharacterConst's character. What it does: as NotifyAngryEnd for the effect at
    // 0x154 (m_subEffect): removed at once while BattleGlobal::m_removeEffect is set, else faded out over 5.
    void fn_7100042460();
    bool IsMove() const;
    bool IsScout() const;
    void GetMoveDataPerSec(mm::Vec3& move) const;
    unsigned int GetIKData(float& value0, float& value1) const;
    int GetAlphaSetID(ALPHA_PROC_ID id);
    unsigned long GetAnimSpecialProcData(ANIM_SPDATA_TYPE type) const;
    void ResetAlphaRate(int id);
    void RegisterAlphaAnimation(ALPHA_PROC_ID id, float, float, bool);
    ActionCommand* GetFreeCommand();
    int GetGroupIndex() const;
    bool CheckRandFriendEnhanceRate(int id) const;
    bool IsRescue() const;

    void ActionCommandIdle(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void ActionCommandEndIdle();
    void ActionCommandPutOutWeapon(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void ActionCommandEndPutOutWeapon();
    void ActionCommandPutAwayWeapon(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void ActionCommandEndPutAwayWeapon();
    void ActionCommandRun(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void ActionCommandEndRun();
    void ActionCommandKizunaMax(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void ActionCommandEndKizunaMax();
    void ActionCommandAttack(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void ActionCommandEndAttack();
    void ActionCommandArts(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void ActionCommandEndArts();
    void ActionCommandBladeArts(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void ActionCommandEndBladeArts();
    void ActionCommandBladeChange(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void ActionCommandEndBladeChange();
    void ActionCommandSpAttack(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void ActionCommandEndSpAttack();
    void ActionCommandSupport(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void ActionCommandEndSupport();
    void ActionCommandBladeGuard(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void ActionCommandEndBladeGuard();
    void ActionCommandRepelled(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void ActionCommandEndRepelled();
    void ActionCommandDown(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void ActionCommandEndDown();
    void ActionCommandKnockBack(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void ActionCommandEndKnockBack();
    void ActionCommandBreak(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void ActionCommandEndBreak();
    void ActionCommandDead(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void ActionCommandEndDead();
    void ActionCommandRescue(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void ActionCommandEndRescue();

    // Placeholder names (all below): new in 3.0.1, nothing in 1.0.0's place names them.
    // Members: second and third slots of the six m_aActionFuncList triples 3.0.1 added (member-pointer table of
    // (Action<X>, ActionCommand<X>, ActionCommandEnd<X>)); what they do: nothing (bare ret).
    void fn_7100048D28(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void fn_7100048D2C();
    void fn_710004BFD8(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void fn_710004BFDC();
    void fn_7100051E78(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void fn_7100051E7C();
    void fn_7100052154(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void fn_7100052158();
    void fn_7100052364(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void fn_7100052368();
    void fn_7100052CD8(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type);
    void fn_7100052CDC();
    // Members: they read or write this object's fields only (this in x0), inside this unit.
    // What they do: m_state == 1.
    bool fn_710002F118() const;
    // !m_isBattle || m_isBattleIgnore (run bit 73: 0xF07 bit 1).
    bool fn_710002F368() const;
    // m_isPlayer && !m_isBattle.
    bool fn_7100041728() const;
    void NotifyDead(const gf::MsgObjectNotifyDead& msg);
    // m_actionID == 4 / m_actionID == 9.
    bool fn_7100059D0C() const;
    bool fn_7100059D1C() const;
    // m_actionParam = param, then m_actionID = 5 / 0xF.
    void fn_7100059D2C(int param);
    void fn_7100059D68(int param);
    // m_actionParam = flag ? param : -param, then m_actionID = 7.
    void fn_7100059D3C(bool flag, int param);
    // m_actionParam = param, m_actionValue = value, then m_actionID = 10.
    void fn_7100059D54(int param, float value);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: Utility's AI_StartAction*/
    // AI_StartMove* ask it of the character a handle names. What it does: the parameter's m_isNotBlade (false
    // without a parameter).
    bool fn_710002F1F8() const;
    // Placeholder name: as fn_710002F1F8; caller Utility::AI_CheckState. What it does: the parameter's slot 42
    // (false without a parameter).
    bool fn_7100041CA4() const;
    // Placeholder name: as fn_710002F1F8; callers Utility::AI_AddBladeArtsRecast and ten others. What it does:
    // the parameter's slot 64 with the flag (false without a parameter).
    bool fn_71000290BC(bool);
    // Placeholder names: new in 3.0.1. Members: they call fn_710002FC0C. What they do: for a blade (IsBlade),
    // fn_710002FC0C(13) / fn_710002FC0C(14).
    void fn_7100042E30();
    void fn_7100042E90();
    // Talk trigger: when the BattleGlobal flag (+0x83CA bit 3) allows, and the id bit (1 << id) is set in the
    // word at 0xECC and clear in 0xED0, notifies TalkManager::NotifyTrigger with trigger 0x29/0x2A/0x2B by which
    // byte of 0xED4/0xED6/0xED8 equals id, and on success sets the bit in 0xED0. Returns whether it notified.
    // Callers: NotifyDirectDamage, AfterUpdate, NotifyLostHateTarget, DeadProc, AttackProc, DropHeadPot, others.
    bool fn_710002FC0C(int id);
    // fn_710002FC0C(7).
    bool fn_710004232C();
    // DropItem((DROP_ITEM_TYPE)(type + 5), false).
    void fn_710006C39C(int type);
    // Blade arts recast: called by fn_710003D114 (and so by Utility::AI_AddBladeArtsRecast) with a slot code
    // (~slot, ~16 for a negative slot), two flags and a float; 0x3B0 bytes, not written yet.
    void fn_710005F554(int slot, bool, bool, float value);
    // fn_710005F554(~(slot < 0 ? 16 : slot), flag0, flag1, value). Caller: Utility::AI_AddBladeArtsRecast.
    void fn_710003D114(bool flag0, int slot, bool flag1, float value);
    bool CheckAttackAction(ACTION_ID id, bool flag) const;
    int GetDriverType() const;
    int GetArtsSlotIndex(int artsID) const;
    float GetArtsAttackDistance(const ARTS_DATA& arts) const;
    void TurnDirection(const mm::Vec3& dir, bool, bool);

    unsigned char pad_8[0x8];
    // where the character stands: EnemyParameter::AngryInfection measures from it (the name is not the original's)
    mm::Vec3 m_pos;
    unsigned char pad_20[0x90];
    // the movement of this frame: GetMoveDataPerSec scales it by 30 (the name is not the original's)
    mm::Vec3 m_moveData;
    unsigned char pad_C0[0x58];
    // the character's object: Utility::AI_GetCharacterHandle returns it (the name is not the original's)
    gf::GF_OBJ_HANDLE* m_handle;
    // the object the character targets, (GF_OBJ_HANDLE*)-1 for none: Utility::AI_GetTargetCharacterID reads it
    // (the name is not the original's)
    gf::GF_OBJ_HANDLE* m_targetHandle;
    // the other object TurnTarget turns to when asked, (GF_OBJ_HANDLE*)-1 for none: then it turns to m_targetHandle
    // (the name is not the original's)
    gf::GF_OBJ_HANDLE* m_subTargetHandle;
    unsigned char pad_130[0x20];
    // the angry aura's effect, NotifyAngryEnd ends it (the name is not the original's)
    unsigned int m_angryEffect;
    // the effect fn_7100042460 ends the same way (the name is not the original's)
    unsigned int m_subEffect;
    unsigned char pad_158[0x28];
    // GetCharacterParameter's cache of DataManager's parameter for m_chrID (the name is not the original's)
    mutable CharacterParameter* m_param;
    unsigned char pad_188[0xB60];
    // Utility::AI_GetBdatID returns it (the name is not the original's)
    int m_bdatID;
    unsigned char pad_CEC[0x4];
    // the blade timer StartBladeTimer sets for its mode and EndBladeTimer clears (the name is not the original's)
    float m_bladeTimer;
    unsigned char pad_CF4[0xE4];
    // what GetIKData hands out while m_ikType is set (the names are not the original's)
    float m_ikValue0;
    float m_ikValue1;
    unsigned int m_ikType : 7;
    unsigned int pad_DE0_7 : 25;
    unsigned char pad_DE4[0x3];
    // GetAnimSpecialProcData gives m_animSpEnd - m_animSpStart while it is 2 (the names are not the original's)
    unsigned char m_animSpType : 3;
    unsigned char pad_DE7_3 : 5;
    unsigned int m_animSpStart;
    unsigned int m_animSpEnd;
    unsigned char pad_DF0[0xBC];
    // one alpha rate per alpha set; ResetAlphaRate sets them to -1 (the name is not the original's)
    float m_alphaRate[3];
    unsigned char pad_EB8[0x22];
    // the id DataManager::GetCharacterParameterConst looks the parameter up by, < 0 for none (the name is not the
    // original's)
    short m_chrID;
    unsigned char pad_EDC[0xC];
    // GetDriverType answers it (a blade answers its driver's; the name is not the original's)
    unsigned int m_driverType : 3;
    unsigned int pad_EE8_3 : 6;
    // the BLADE_TIMER_MODE m_bladeTimer runs for (the name is not the original's)
    unsigned int m_bladeTimerMode : 3;
    unsigned int pad_EE8_12 : 20;
    // SetRimBloom's: bit 0 for RIMBLOOM_ID 0, one of bits 1-8 for the ids 1-8 (the name is not the original's)
    unsigned short m_rimBloomFlags;
    unsigned char pad_EEE;
    // the index TalkManager's PlayVoice and GetPlayVoiceID take for the character (Utility::AI_PlayVoice; the name
    // is not the original's)
    signed char m_voiceIndex;
    // the character's index on its side (GetAiChrID; the name is not the original's)
    signed char m_index;
    // GetWeaponType returns it (the name is not the original's)
    signed char m_weaponType;
    unsigned char pad_EF2[0x2];
    // flags formation_change_manager's requests set while they run (the names are not the original's)
    unsigned char pad_EF4_0 : 1;
    unsigned char pad_EF4_1 : 1;  // a type 2 request's character (fn_710009E008)
    unsigned char pad_EF4_2 : 2;
    unsigned char pad_EF4_4 : 1;  // a type 1 request's characters (fn_710009DCAC)
    unsigned char pad_EF4_5 : 3;
    unsigned char pad_EF5[0x9];
    // one 16-byte bitfield run (StartBackHome loads and stores 0xEFE and 0xF06 as two 8-byte halves)
    unsigned int pad_EFE : 8;
    // IsControlCharacter's cached answer and whether it is cached (the names are not the original's)
    mutable unsigned int m_isControlChara : 1;
    mutable unsigned int m_isControlCharaCached : 1;
    unsigned int pad_EFF_2 : 3;
    // unknown: TurnTarget clears it once the target's position is known (the name is not the original's)
    unsigned int m_flagEFF_5 : 1;
    unsigned int pad_EFF_6 : 1;
    // a player-side character (GetAiChrID, IsEnableBattleFace; the name is not the original's)
    unsigned int m_isPlayer : 1;
    // IsBattle returns it (the name is not the original's)
    unsigned int m_isBattle : 1;
    unsigned int pad_F00_1 : 9;
    // ActionRun sets it when it draws the weapon of a character the player does not control and that does not fly
    // (the name is not the original's)
    unsigned int m_isAutoRun : 1;
    unsigned int pad_F01_3 : 1;
    // the name is not the original's: ActionCommandEndRun stays in the run action while it is set (run bit 28)
    unsigned int m_isRunHold : 1;
    unsigned int pad_F01_5 : 4;
    // StartBackHome sets it (the name is not the original's)
    unsigned int m_reqBackHome : 1;
    unsigned int pad_F00_18 : 5;
    // Utility::AI_IsFly returns it (the name is not the original's)
    unsigned int m_isFly : 1;
    unsigned int pad_F00_24 : 8;
    unsigned int pad_F04 : 25;
    // the name is not the original's: fn_710002F368 treats the character as out of battle while it is set
    unsigned int m_isBattleIgnore : 1;
    unsigned int pad_F07_2 : 6;
    unsigned int pad_F08 : 32;
    unsigned int pad_F0C : 16;
    unsigned char pad_F0E[0x12];
    // the commands GetFreeCommand hands out, m_commandNum of them in use (the names are not the original's)
    ActionCommand m_commands[10];
    int m_commandNum;
    // 1 or 4 lets the AI turn (IsEnableTurnAI); 4 is a move (IsMove) (the name is not the original's)
    unsigned char m_state;
    unsigned char pad_FED;
    // the ACTION_ID being run (ActionCommandBladeArts; the name is not the original's)
    unsigned short m_actionID;
    // the name is not the original's: ActionRun resets it, SetAction sets it, ActionCommandEndRun tests it for 0
    int m_actionStep;
    unsigned char pad_FF4[0x8];
    // what the action runs for: the party index of the character to rescue while m_state is 0x14 (GetRescueTarget;
    // the name is not the original's)
    int m_actionParam;
    unsigned char pad_1000[0xC];
    // the name is not the original's: SetAction's float argument
    float m_actionValue;
    unsigned char pad_1010[0x60];
    unsigned int pad_1070 : 16;
    // Utility::AI_GetReactionID returns it (the name is not the original's)
    unsigned int m_reactionID : 5;
    // IsBladeArtsEnd holds while it is not 1 (the name is not the original's)
    unsigned int m_bladeArtsState : 3;
    // a 3-byte run: IsBladeArtsEnd loads the byte at 0x1072 shifted, the byte at 0x1073 is a counter of its own
    unsigned char pad_1073;
    unsigned char pad_1074[0x1C];
    // SetSuperArmorTime keeps the longer time (the name is not the original's)
    float m_superArmorTime;
    unsigned char pad_1094[0x13];
    // Utility::AI_GetAutoAttackState answers it plus 1, kept in 0-3 (the name is not the original's)
    signed char m_autoAttackStep;
    unsigned char pad_10A8[0x6];
    // the character index of the one attacking from behind (Utility::AI_GetBackAttackerCharacterID; the name is not
    // the original's)
    short m_backAttacker;
    unsigned char pad_10B0[0x9];
    // Utility::AI_GetAutoAttackState answers m_autoAttackStep only while it is set (the name is not the original's)
    unsigned char m_isAutoAttack : 1;
    unsigned char pad_10B9_1 : 7;
    unsigned char pad_10BA[0x66];
    // one 8-byte bitfield run (GetRescueTarget loads it whole): the moving kind's own state, 0x14 while it rescues
    // m_moveRescueTarget (IsRescue, GetRescueTarget, MoveStop; the names are not the original's). An unsigned char
    // bitfield: IsRescue and MoveStop compare it as a 32-bit value, GetRescueTarget as the 64-bit run.
    unsigned char m_moveState : 8;
    unsigned int pad_1120_8 : 24;
    int m_moveRescueTarget : 32;
    unsigned char pad_1128[0xC];
    // SetScout adds 10 to it when scouting starts (the name is not the original's)
    float m_scoutTime;
    // 1 for a moving kind of character: IsMove holds, IsScout/SetScout act (the name is not the original's)
    int m_moveKind;
    unsigned char pad_113C[0x4];
    unsigned int pad_1140 : 1;
    // MoveStop's requests: bit 1 for MoveStop(false), bit 2 for MoveStop(true) (the names are not the original's)
    unsigned int m_moveStopReq : 1;
    unsigned int m_moveStopReqArg : 1;
    unsigned int pad_1140_3 : 1;
    // IsScout returns it (the name is not the original's)
    unsigned int m_isScout : 1;
    unsigned int pad_1140_5 : 27;
    unsigned char pad_1144[0x64];
    // Utility::AI_GetStamp returns it while the character lives (the name is not the original's)
    int m_stamp;
    // CharacterManager's slots are 0x11D0 apart with their in-use flag at 0x11C0, after the character
    unsigned char pad_11AC[0x6];
    // one bitfield run of 3 bytes (fn_710009ED18 reads it with a halfword load at 0x11B2, as a 3-byte unit loads)
    unsigned char pad_11B2 : 8;
    unsigned char pad_11B3_0 : 1;
    unsigned char pad_11B3_1 : 1;  // formation_change_manager's fn_710009ED18 returns it
    unsigned char pad_11B3_2 : 6;
    unsigned char pad_11B4 : 8;
    unsigned char pad_11B5[0xB];
};
}  // namespace btl

#endif
