#ifndef CLASSES_BTL_BATTLEGLOBAL_H
#define CLASSES_BTL_BATTLEGLOBAL_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/btl/ButtonChallenge.h"
#include "classes/fw/Camera.h"

namespace btl { class BattleGlobal; }
namespace gf { class GfComEffectCaster; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; }
namespace btl { class ShakeCameraManager; struct ARTS_DATA; class BattleCharacter; }

namespace btl {
// The tutorial condition BattleGlobal::Tutorial takes (the type's name is the symbol's; its values are not named).
enum BTL_TUTORIAL_COND {};

// table 0x7100B3A3E0
class BattleGlobal : public ::mm::mtl::PtrSingleton< ::btl::BattleGlobal> {
public:
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
    void Tutorial(BTL_TUTORIAL_COND cond, int, void*);
    // reads the anti-blade area's revision row (Bdat 0x35) into m_mapRev when the area changes
    void UpdateMapRev();
    // whether a battle can run: not while GfGameManager stops battles
    bool IsEnableBattle() const;
    void SetElementalComboImmortal(gf::GF_OBJ_HANDLE* handle);
    void DeleteUniteComboDirection();
    void SetPause(int kind, bool pause);
    void DeleteSlow(unsigned int id);
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
    // parameter's slot 65 (fn_7100085314(true)) holds; raises m_linkJoinLevel to its level (+15 when named)
    void NotifyLinkJoinBattle(gf::GF_OBJ_HANDLE* handle);
    // counts one more chain (up to 0xFFFFFFF); when asked, plays narration voice 5 + level once the count reaches the
    // level's threshold (25, 50, 100) and goes up a level
    void AddChainCount(bool narrate);
    int GetElementalComboStage(int) const;
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
    // the result is an int switched on (0 and 1): 3.0.1 compares it with 1, then with 0
    void fn_710000BAE0(int id, int result);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's ai::AiData::isValid makes no call
    // there). A member: ai::AiData::isValid passes PtrSingleton<BattleGlobal>::sys(). What it does: returns bit 1 of
    // the byte at 0x83D0; while it is clear, isValid refuses the party's leader driver (GfGameParty::isLeaderDriver).
    bool fn_710000A6CC();

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
        unsigned char pad_0[0x4];
        float deleteDelay;  // DeleteDelayElementalComboSlow sets it
        int pad_8;  // DeleteDelayElementalComboSlow clears it
        unsigned int id;  // IsSlowProc looks it up
        unsigned char dynamicsChara;  // SetSlowDynamicsSpeed's character
        unsigned char pad_11;
        unsigned short dynamicsSpeed;  // SetSlowDynamicsSpeed's speed, in percent
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
    void RequestJingle(JINGLE_TYPE type);  // 1.0.0's RequestJingle(JINGLE_TYPE) (3.0.1's symbols spell fn_710000C3AC)
    bool IsJinglePlaying() const;
    void PlayErrorSE();  // 1.0.0's PlayErrorSE (3.0.1's symbols spell fn_710000C3C8)
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members: they read this BattleGlobal's
    // fields (callers pass PtrSingleton<BattleGlobal>::sys()). What they do:
    // Initialize: clears pad_8374[0-8], then keeps in pad_8374[driver - 17] the last row of BDAT table 1 whose
    // "IrType" is 3 for each "Driver" 17-25
    void fn_7100004C10();
    unsigned short fn_71000053C4(int id) const;  // pad_8374[id - 17]; PlayerParameter::InitializeArtsPalette
    const ELEMENTAL_COMBO_FLOW_DATA& fn_71000053F8(int id) const;  // the flow entry, no range check
    // the elements (bit element) of the final steps (stage above 2) reachable from step id through the children
    // pad_0[1-8] whose bit is in mask (BattleCharacter::AI_BladeChange), masked by it
    unsigned int fn_710000540C(int id, unsigned int mask) const;
    bool fn_7100007554() const;  // pad_5d54 != 0 (13 callers: BattleCharacter input/AI, CheckBattle, ...)
    void fn_710000903C();  // clears pad_83b2, sets pad_83b4 to 0xFF (BattleManager::CheckBattle)
    // takes id (a row of BDAT table 0xB1) into pad_83b2 when none is held (pad_83b4 0xFF) or its "Priority" is
    // above the held one's (kept in pad_83b4); whether it took it
    bool fn_7100009618(unsigned int id);
    bool fn_710000A7FC(int index) const;  // tests flag index of pad_83b8
    void fn_710000AC7C(int index);  // clears flag index of pad_83b8
    void fn_710000ACA4(int index);  // sets flag index of pad_83bc
    bool fn_710000C440(int index);  // sets flag index of pad_83bf; false when it was set already
    bool fn_710000C610() const;  // pad_5d60 <= 0
    bool fn_710000C624(gf::GF_OBJ_HANDLE* handle) const;  // pad_5d54 != 0 and pad_5d48 is handle
    bool fn_710000C648() const;  // pad_5d54 in 3-7
    bool fn_710000CEF4() const;  // pad_bit18
    bool fn_710000CF04() const;  // pad_bit21
    void fn_710000DE04(bool side, int add);  // adds to pad_83c0[!side], kept in 0-255 (CharacterParameter::SetBuff)
    bool fn_710000DE34(bool side);
    void fn_710000A6DC();
    // the next ones read pad_5d9c (and do nothing, or answer false) while m_challengeAnySuccess is set
    bool fn_710000DA48() const;  // pad_5d9c != 0
    void fn_710000DA8C();  // raises pad_5d9c from 1-2 to 3
    bool fn_710000DAD8() const;  // pad_5d9c > 2
    void fn_710000DD4C(int index, unsigned int add);  // adds to pad_5d78[index] (0-2) while pad_5d9c != 0
    bool fn_710000DDB0(bool check) const;  // pad_bit22, or check and pad_5dc0 >= 0
    bool fn_710000D468(bool check) const;  // pad_bit16, or check and pad_5db8 >= 0
    bool fn_710000D4BC(bool check) const;  // pad_bit20, or check and pad_5dbc >= 0
    // takes the party leader into m_leaderHandle and m_controlHandle; during a chain attack m_controlHandle becomes
    // the driver of the chain's group (ChainAttackManager::GetGroupIndex)
    void fn_71000063EC();  // flips pad_bit50 while pad_bit49 is set
    void fn_710000C660(ARTS_DATA& data) const;  // DataManager's arts data for pad_5d68 (GfEnemyBattleProperty::Update)
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
        bool endCriticalRecastEnhance : 1;  // IsEndCriticalRecastEnhance
        bool pad_bit8 : 1;
        bool pad_bit9 : 1;
        bool pad_bit10 : 1;
        bool pad_bit11 : 1;
        bool criticalRecastEnhanceEnd : 1;  // SetCriticalRecastEnhanceEnd
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
    // 1.0.0's AddDamageRate/MulDamageRate: the same code in the same place after SetDamageRate (3.0.1's symbols
    // spell fn_710000BE60/fn_710000BEE8)
    void AddDamageRate(unsigned int id, float rate, bool markChanged);
    void MulDamageRate(unsigned int id, float rate, bool markChanged);
    float GetDamageRate(unsigned int id, bool* changed) const;
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them (1.0.0's attack accessors run
    // SetEndDropHealPot2 ... GetDamageRate without them). Members: they sit among BattleGlobal's attack accessors and
    // look the record up in this BattleGlobal's records. What they do:
    void fn_710000B338(unsigned int id);  // sets the flag IsEndCriticalRecastEnhance reads
    void fn_710000B4D0(unsigned int id);  // sets flag bit 11
    bool fn_710000B52C(unsigned int id) const;  // flag bit 11 (false when there is no record)
    bool fn_710000B5F4(unsigned int id) const;  // the flag SetCriticalRecastEnhanceEnd sets
    void fn_710000B664(unsigned int id, bool on);  // stores flag bit 10
    bool fn_710000B6C0(unsigned int id) const;  // flag bit 10
    bool fn_710000B8CC(unsigned int id) const;  // whether a chain attack was running when the record was made
    void fn_710000BA08(unsigned int id, bool on);  // clears flag bit 8, stores flag bit 9
    int fn_710000BA74(unsigned int id) const;  // 1 when flag bit 8 is set, else 2 when bit 9 is, else 0
    // 3.0.1's symbols spell these SetDamageRate(unsigned int, float, bool) and Utility::AchieveCondition (1.0.0's
    // positions); their code takes this BattleGlobal, an id and an int (no float) and reads the record's byte at 0x12
    void fn_710000BD64(unsigned int id, int index);  // clears pad_bit18 (index 0) or pad_bit19 (index 1)
    bool fn_710000BDD4(unsigned int id, int index) const;  // pad_bit18 (0) or pad_bit19 (1); true otherwise

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

    // the party's leader driver, as fn_71000063EC last read it (the name is not the original's)
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
    unsigned char pad_778[0x8];
    // an enemy that joined through a link (NotifyLinkJoinBattle; the names are not the original's)
    struct LinkJoinEnemy {
        gf::GF_OBJ_HANDLE* handle;
        float time;  // 30 when it joins
    };
    // the enemies that joined through a link, nearest first asked by GetLinkJoinEnemyHandle (the name is not the
    // original's)
    ::mm::mtl::FixedVector<LinkJoinEnemy, 8> m_linkJoinEnemy;
    // two fixed vectors the destructor clears (element types unknown: only their byte sizes, 8 and 0x90, are known)
    ::mm::mtl::FixedVector<unsigned int, 2> pad_808;
    ::mm::mtl::FixedVector<unsigned int, 36> pad_818;
    unsigned char pad_8b0[0x8];
    // the slow-motion requests (the name is not the original's)
    ::mm::mtl::FixedVector<SLOW_PROC_DATA, 20> m_slowProc;
    float pad_a50;  // Utility::fn_710000FB7C holds while it is <= 0
    unsigned char pad_a54[0x48];
    // PlayerParameter::BattleStart copies it into CharacterParameter's pad_20; meaning unknown
    int pad_a9c;
    unsigned char pad_aa0[0x8];
    unsigned int m_nextAttackId;  // CreateAttackData's next id, never 0 (the name is not the original's)
    unsigned char pad_aac[0x4];
    // the attack records (the name is not the original's); full, AddAttackDamage drops the oldest
    mutable ::mm::mtl::FixedVector<AttackDamageData, 1000> m_attackData;
    // the elemental combo flow, by combo id (the name is not the original's)
    ELEMENTAL_COMBO_FLOW_DATA m_elementalComboFlow[66];
    // by stage 1-2 and index, what ELEMENTAL_COMBO_FLOW_DATA::fn_71000054F4 returns for an empty step
    unsigned char pad_5bf0[2][9];
    unsigned char pad_5c02;  // ELEMENTAL_COMBO_FLOW_DATA::fn_71000054F4 reads pad_5bf0 while it is 2
    unsigned char pad_5c03[0x49];
    // EnemyParameter::ApplyStatusEnhance scales every enhanced value by it (the name is not the original's)
    float m_statusEnhanceRate;
    // the challenge battle unit's fn_7100026D08 returns it; meaning unknown
    float pad_5c50;
    unsigned char pad_5c54[0x24];
    // the playing jingle's sound handle, -1 when none plays (IsJinglePlaying; the name is not the original's)
    long m_jingleHandle;
    unsigned char pad_5c80[0x18];
    // per party character, the anti-blade area's revisions: Bdat 0x35's "KizunaCap", "ArtSp", "nba" flag and
    // "PC%02dAtk"/"PC%02dDef" columns (UpdateMapRev; the names are not the original's)
    struct MapRev {
        unsigned short kizunaCap : 11;
        unsigned short artSp : 4;
        unsigned short nbaClear : 1;  // set when the row's "nba" flag is clear
        unsigned char atk;
        unsigned char def;
        // the constructor's values for every entry (and fn_710000CE5C's guarded static default)
        MapRev() : kizunaCap(1000), artSp(4), nbaClear(true), atk(100), def(100) {}
    };
    // Placeholder name: GROUP_BLADE_DATA::Initialize passes the party character (1-12) and whether the area's
    // revision applies; m_mapRev's entry for it (nullptr out of range), or a default entry when it does not apply
    const MapRev* fn_710000CE5C(int chara, bool apply) const;
    // Placeholder name: DataManager::UpdateProc passes a character and its driver; fn_710000CE5C's entry for the
    // character's m_bdatID, applied unless the driver's parameter slot 75 says otherwise, when it is a player
    // (m_isPlayer) that fn_71000290BC(true) accepts and m_challengeAnySuccess is clear; else nullptr
    const MapRev* fn_710000CD60(BattleCharacter* chara, BattleCharacter* driver) const;
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
    unsigned char pad_5d10[0x8];
    // the unite combo direction's camera (DeleteUniteComboDirection pops it; the name is not the original's)
    ::mm::mtl::IntrusivePtr<fw::Camera> m_uniteComboCamera;
    unsigned char pad_5d20[0x1F];
    unsigned char pad_5d3f;  // see pad_5d08
    unsigned char pad_5d40[0x8];
    // fn_710000C624 compares its handle with it while pad_5d54 is non-zero
    gf::GF_OBJ_HANDLE* pad_5d48;
    unsigned char pad_5d50[0x4];
    // non-zero while something runs that many BattleCharacter input/AI functions ask about (fn_7100007554);
    // fn_710000C648 tests it for 3-7
    int pad_5d54;
    unsigned int pad_5d58;  // an attack record id (fn_710000BAE0 flags that record)
    unsigned char pad_5d5c[0x4];
    float pad_5d60;  // fn_710000C610 tests it for <= 0
    int pad_5d64;  // fn_710000BAE0 acts only for this challenge id
    // an arts reference: data type in bits 0-2, arts id above (fn_710000C660 asks DataManager::GetArtsData for it)
    unsigned short pad_5d68;
    unsigned char pad_5d6a[0x4];
    unsigned char pad_5d6e;  // fn_710000BAE0 sends a menu event once while it is set, then clears it
    unsigned char pad_5d6f[0x9];
    unsigned int pad_5d78[3];  // fn_710000DD4C adds to an entry, up to 99999999
    unsigned char pad_5d84[0x18];
    int pad_5d9c;  // fn_710000DA48/DA8C/DAD8/DD4C read it while m_challengeAnySuccess is clear
    unsigned char pad_5da0[0x18];
    float pad_5db8;  // fn_710000D468 tests it for >= 0
    float pad_5dbc;  // fn_710000D4BC tests it for >= 0
    float pad_5dc0;  // fn_710000DDB0 tests it for >= 0
    unsigned char pad_5dc4[0x14];
    float pad_5dd8;  // Utility::fn_7100010DA4 stores it
    unsigned char pad_5ddc[0x16];
    // Utility::AI_EnemyKillNum returns it (the name is not the original's)
    unsigned short m_enemyKillNum;
    // each normal attack's arts id by [character][weapon][combo step]; row 0 is the default (GetNormalAttackArtsID;
    // the name is not the original's; the meaning of the indices is inferred from 1.0.0's InitializeNormalAttackArtsID)
    unsigned short m_normalAttackArtsID[32][50][3];
    unsigned short pad_8374[31];  // fn_71000053C4 reads entry id - 17
    unsigned short pad_83b2;  // the id fn_7100009618 took; fn_710000903C clears it
    unsigned char pad_83b4;  // its priority; fn_710000903C sets it to 0xFF (none)
    unsigned char m_jingleRequest;  // RequestJingle (the name is not the original's)
    // pause flags by kind, 8 to a byte; IsPause(-1) asks for any (the name is not the original's)
    unsigned char m_pause[2];
    unsigned char pad_83b8[4];  // flags by index, 8 to a byte (fn_710000A7FC tests, fn_710000AC7C clears)
    unsigned char pad_83bc[3];  // flags by index, 8 to a byte (fn_710000ACA4 sets)
    unsigned char pad_83bf[1];  // flags by index, 8 to a byte (fn_710000C440 tests and sets)
    unsigned char pad_83c0[2];  // two counters by side (fn_710000DE04 adds, fn_710000DE34 counts down)
    unsigned char pad_83c2[0x6];
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
    // the rest of the unit: fn_710000A724 reads bits 35, 49 and 50, fn_71000068F8 bits 49 and 50
    unsigned char : 2;
    // CharacterManager::PreUpdateProc sets it once an enemy in battle belongs to a quest with an active task
    // (gf::GfQuestUtil::getCurrentEnemyWithEvent; meaning unknown)
    bool pad_bit6 : 1;
    bool pad_bit7 : 1;  // Utility::fn_71000100F0 sets it
    unsigned char : 4;
    bool pad_bit12 : 1;  // DeleteElementalComboCamera clears it
    unsigned char : 3;
    bool pad_bit16 : 1;  // fn_710000D468 holds while it is set
    bool pad_bit17 : 1;  // EnemyParameter::MulHate changes no hate while it is set
    bool pad_bit18 : 1;  // fn_710000CEF4 returns it
    unsigned char : 1;
    bool pad_bit20 : 1;  // fn_710000D4BC holds while it is set
    bool pad_bit21 : 1;  // fn_710000CF04 returns it
    bool pad_bit22 : 1;  // fn_710000DDB0 holds while it is set
    // set when the controlled character is told of its death of kind 3 or 4 (pc::StateBattleBase::
    // procMsgObjectNotifyDead; the name is not the original's)
    bool m_controlCharacterDead : 1;
    // while set, IsGameOver holds without asking GfGameManager (the name is not the original's)
    bool m_gameOver : 1;
    unsigned char : 4;
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
    bool pad_bit35 : 1;  // fn_710000A724 holds while it is set
    unsigned char : 4;
    // GfGameTarget's selectRight/selectLeft change no target while it is clear (the name is not the original's)
    bool pad_bit40 : 1;
    // NotifyShiftTimeOver sets it while UIManager's pad_bit15 is set; fn_710000A764 clears it with pad_bit40
    bool pad_bit41 : 1;
    unsigned char : 5;
    // set once PlayErrorSE played its sound, which it then does not play again (the name is not the original's)
    bool m_errorSePlayed : 1;
    bool pad_bit48 : 1;
    bool pad_bit49 : 1;  // fn_710000A6CC returns it; fn_71000068F8 asks for it with pad_bit50
    bool pad_bit50 : 1;
    unsigned char : 3;
    bool pad_bit54 : 1;  // GROUP_DATA::ProgressCoolTime advances the group's own cool time while it is set
    bool pad_bit55 : 1;  // Utility::fn_71000151EC returns it
};
}  // namespace btl

#endif
