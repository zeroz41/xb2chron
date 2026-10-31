#ifndef CLASSES_GF_GFGAMEMANAGER_H
#define CLASSES_GF_GFGAMEMANAGER_H

#include "classes/gf/IGfEvent.h"
#include "classes/gf/IQuestEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GfSetupParam; }
namespace mm { class Vec3; }
namespace fw { class UpdateInfo; }
namespace gf { enum GF_STATE : int; }
namespace gf { enum ActivateType : int; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfGameManager; }
namespace mm { namespace mtl { template <typename, unsigned long> class FixedArray; }}
namespace gf { struct OwnerBonus; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { class QuestCompleteChildParam; }
namespace gf { class QuestCompleteParam; }
namespace gf { class QuestOrderParam; }
namespace gf { enum GEV : int; }
namespace gf { enum GF_STATE : int; }
namespace gf { enum RELOAD_BDAT : int; }
namespace gf { enum GfPlayerDead : int; }

namespace gf {
// table 0x7100B54938; IGfEvent at 0x8 (1.0.0's table names the overrides), IQuestEvent at 0x10
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function (the symbols spell it in gf's
// namespace) in gf_game_manager's unit. What it does: the int at 0x104 of PtrSingleton<TUnk_B535D0>'s instance (its
// record's m_value2C), 0 when there is none.
unsigned int fn_71002AC5B8();

class GfGameManager : public ::mm::mtl::PtrSingleton< ::gf::GfGameManager>, public ::gf::IGfEvent, public ::gf::IQuestEvent {
public:
    GfGameManager() : m_initialized(false), m_leaveGameForDebug(false) {}
    static void setStartGame();
    static bool isEnableRoomForHikariLv4();
    static void setStopMainMenuOpenForGimmick(bool stop);
    static bool isValidCollisionVelocity();
    // whether a map jump may start (neither the state nor the reserved one is 8 or 9)
    static bool isMapjumpOK();
    // GfGameScene has player stop flag 1, 3, 4 or 5 set (false without a GfGameScene)
    static bool isGmkTutorialSequenceOK();
    // not in battle, not in theater mode, and the control is free
    static bool isAutoTalkOK();
    // a GfPlayComQuestCompleteUI is alive
    static bool isQuestCompleteUI();
    static bool isEnableBattouWithHoodHomura(bool flag);
    // the leader may not draw its weapon (a blade reset plays, the first blade rebuilds, or isEnableBattouWithHoodHomura(true))
    static bool isDisableBattou();
    // whether the fade of that layer runs (or SCOM type 27 is queued); -1 asks layers 0, 1 and 2
    static bool isFading(unsigned int layer);
    // the pad's characters: the controlled mover first
    static void collectPadCharList(mm::mtl::FixedArray<gf::GF_OBJ_HANDLE*, 2>* list);
    static void setValidCollisionVelocity(bool valid);
    // SCOM_ACCESS_TARGET and SCOM_TARGET_UI pass their request's object
    static void setAccessTarget(gf::GF_OBJ_HANDLE* handle);
    static void setTargetUI(gf::GF_OBJ_HANDLE* handle);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code is in gf_game_manager's unit
    // and GfManager::fn_710032A958 calls it on GfGameManager's instance. What it does: when PtrSingleton<gf::GfGameScene>'s
    // instance exists, calls fn_71002CC060 on it (the update info passed on unused); the info is TitleApplet's per-frame one
    void fn_71002AC9C0(const fw::UpdateInfo& info);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its code is in
    // gf_game_manager's unit among GfGameManager's functions and takes no instance. What it does: copies the Vec3 into
    // the static Vec3 getControlMoverPosition falls back on (guard 0x7100D6CC00, first set to mm::Vec3::zero); TitleStatePlayEvent::gevPlayEvent
    // passes gf::GfInfo::m_camPos (GEV 0xE) and mm::Vec3::zero (GEV 0xD).
    static void fn_71002AB894(const mm::Vec3& pos);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its code is in
    // gf_game_manager's unit among GfGameManager's functions and takes no instance. What it does: when the instance
    // the pointer at 0x7100B94428 holds exists, tail-calls fn_7100291DB4 on it (that one reads local game flag type 1
    // index 0xDC0D); false otherwise. 23 callers (GfGameUtil::incEnemySuppress skips counting while it holds,
    // GfFieldWeather::updateWeather, GfGameScene::setEnemyDead, GfMenuBattleAdapter).
    static bool fn_71002AC580();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its code is in
    // gf_game_manager's unit among GfGameManager's functions and takes no instance. What it does: tail-calls
    // fn_71002EC634, the byte 0x6F into the option data (tl::TitleMain's getOptionBuffer in advertize/theater mode,
    // else GfDataManager::getDataOption()). Callers: btl::BattleGlobal::PreUpdateProc, gf::fn_71002ED6B8 (picks a
    // record column 0/1/2/4 with it), SCOM_ENBOOK_BOSS_TIME::exec.
    static unsigned int fn_71002AC57C();
    // The record fn_71002AC5D8 returns and fn_71002AC60C fills (the name and its fields' names are not the
    // original's): one battle challenge's data (gf_game_arena's fn_7100290130 clears it the way the constructor
    // does, then fills it from GfBdatBtl's row). GfMenuBattleAdapter's callbacks read its short at 0x1C, ints at
    // 0x28/0x2C and floats at 0xAD0; gf_menu_obj_btl_time reads m_kind; gf_menu_btlch_adapter's callbacks (TUnk_B5A648)
    // read most of the rest. 0xAF0 bytes: the 0xAF0-byte frames of those callbacks hold one.
    struct BattleChallengeRecord {
        // the elements of the two lists are not known (gf_game_arena fills them): room of 0xA0 and 0x9E8 bytes
        struct Entry38 {
            unsigned char pad_00[0x8];
        };
        struct EntryE0 {
            unsigned char pad_00[0x9E8];
        };
        // 12 bytes the arena copies from GfDataGame's table (row * 0x40 + type * 12 at 0x11A8CC)
        struct Rule {
            Rule() : m_value0(0), m_value4(0), m_value8(0), m_flag8(0) {}
            // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members: TUnk_B52C38's
            // fn_710028C9CC calls them on its Rule at +0xB0 with the arena's record (code in unit_710028EBB0). What
            // they do: fn_71002903AC keeps a larger value in m_value8, sets the record's m_value2C to the value and
            // its m_ratios from GfBdatBtl's fn_71001EA2E8 thresholds 0..2; fn_71002904DC keeps a larger value in
            // m_value4 and sets the record's m_value28; fn_71002904F4 keeps a smaller one in m_value0 (0 counts as
            // none) and sets the record's m_value30.
            void fn_71002903AC(BattleChallengeRecord* record, unsigned int value);
            void fn_71002904DC(BattleChallengeRecord* record, unsigned int value);
            void fn_71002904F4(BattleChallengeRecord* record, unsigned int value);
            unsigned int m_value0;
            unsigned int m_value4;
            unsigned int m_value8 : 17;  // also stored at 0x2C
            unsigned int m_flag8 : 7;
        };
        BattleChallengeRecord() {
            clear();
            m_ratios[0] = 0.0f;
            m_ratios[1] = 0.0f;
            m_ratios[2] = 0.0f;
            m_rule = Rule();
            m_valueAE8 = 1;
            m_flagAEC = false;
        }
        // what the constructor and gf_game_arena's fn_7100290130 zero first
        void clear() {
            m_id = 0;
            m_value4 = 0;
            m_kind = 0;
            m_value8 = 0;
            m_valueA = 0;
            m_valueC = 0;
            m_valueE = 0;
            m_value10 = 0;
            m_flag12 = false;
            m_text14.m_message = 0;
            m_flag1A = false;
            m_value1C = 0;
            m_values1E[0] = 0;
            m_values1E[1] = 0;
            m_values1E[2] = 0;
            m_value24 = 0;
            m_value28 = 0;
            m_value2C = 0;
            m_value30 = 0;
        }
        unsigned int m_id;
        unsigned short m_value4;  // seconds
        unsigned short m_kind;  // gf_menu_obj_btl_time's fn_71003B4CC0 opens LAY_score with 0 for 1, with 1 for 3
        unsigned short m_value8;
        unsigned short m_valueA;
        unsigned short m_valueC;
        unsigned short m_valueE;
        unsigned short m_value10;  // with m_flag12: 0x10..0x1B hold three {message, flag} pairs
        bool m_flag12;
        unsigned char pad_13[0x1];
        // a message of GfDataBdat 0x1A1 and its flag (the names are not the original's)
        struct Text {
            unsigned short m_message;
            unsigned char m_flag;
        };
        Text m_text14;  // the constructor sets only the message
        Text getText14() const { return m_text14; }
        unsigned short m_value18;  // not set by the constructor
        bool m_flag1A;
        unsigned char pad_1B[0x1];
        unsigned short m_value1C;
        unsigned short m_values1E[3];
        unsigned int m_value24;
        unsigned int m_value28;
        unsigned int m_value2C;
        unsigned int m_value30;  // seconds
        unsigned char pad_34[0x4];
        // the challenge id and mode the lists are built for (gf_game_arena's fn_7100291E40 builds one on the stack,
        // TUnk_B52C38 keeps one at +0x20; the names are not the original's)
        struct Key {
            unsigned int m_id;
            unsigned int m_mode;
            bool m_flag8;  // fn_7100291E40 clears it
            // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (code in unit_710028EBB0's range).
            // A member: fn_71002908DC and TUnk_28D7B8::fn_710028E5BC call it on a key with a blade ID. What it does:
            // reads GfBdatBtl's rows for m_id against the blade's weapon rank and weapon type.
            unsigned int fn_7100290AE4(unsigned int blade) const;
        };
        // the two lists gf_game_arena's fn_7100291E40 fills (both helpers take this object; the name is not the
        // original's)
        struct Lists {
            // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them (code in unit_710028EBB0's
            // range). Members: fn_7100291E40 calls both on the record's lists with its key. What they do:
            // fn_71002907A0 clears m_list38 and fills it from GfBdatBtl's rows for the key's id, fn_71002908DC
            // the same for m_listE0.
            void fn_71002907A0(const Key& key);
            void fn_71002908DC(const Key& key);
            mm::mtl::FixedVector<Entry38, 20> m_list38;
            mm::mtl::FixedVector<EntryE0, 1> m_listE0;
        };
        // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (code in unit_710028EBB0's range). A
        // member: fn_7100291E40 calls it on the record with the challenge id. What it does: clears the record and
        // fills its header from GfBdatBtl's row for the id.
        void fn_7100290130(unsigned int id);
        Lists m_lists;
        float m_ratios[3];
        Rule m_rule;
        Rule getRule() const { return m_rule; }
        int m_valueAE8;
        bool m_flagAEC;
    };
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its code is in
    // gf_game_manager's unit among GfGameManager's functions and takes no instance. What it does: when the instance
    // the pointer at 0x7100B94428 holds exists, has gf_game_arena's fn_7100291E40 fill the record for the id and
    // mode it is given and returns true; false otherwise. gf_menu_btlch_adapter's callbacks pass the mode
    // GfMenuReference::fn_7100369304 answers.
    static bool fn_71002AC60C(BattleChallengeRecord* record, unsigned int id, unsigned int mode);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its code is in
    // gf_game_manager's unit among GfGameManager's functions and takes no instance. What it does: returns the address
    // 0xD8 bytes into the instance the pointer at 0x7100B94428 holds (the one fn_71002AC580 asks); 12 callers
    // (GfMenuBattleAdapter, the battle challenge manager, gf_menu_obj_btl_time, gf_menu_btlch_adapter).
    static BattleChallengeRecord* fn_71002AC5D8();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code is in gf_game_manager's unit
    // among GfGameManager's functions. What it does: when PtrSingleton<TUnk_B54858> exists, passes it and its bool to
    // TUnk_B54858::fn_71002A7430 (as GfGameManager::setupGame does); GfManager::fn_710032A1FC calls it
    static void fn_71002AC558(bool flag);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code is in gf_game_manager's unit
    // among GfGameManager's functions and takes no instance. What it does: tail-calls fn_710024DD88, which returns bits
    // 16-19 of the u32 at 0x101D08 of GfDataManager::getDataGame(). Callers: fn_71002CBBD0 and gf_menu_obj_hitonowa's
    // GfMenuObjHitonowa::fn_710041D544 (keeps it in a file static), initialize and fn_71004256F8.
    static unsigned int fn_71002AC8E0();
    static void build(const GfSetupParam& param);
    void initialize(const GfSetupParam& param);
    static void destroy();
    static void setState(GF_STATE state, bool flag);
    static void leaveGameForDebug();
    // whether the player is paused (StateFieldPrepareBigJump waits while it is)
    static bool isPlayerPause();
    static void destroyBattleEnemy();
    static bool isField();
    static bool isInnerState(GF_STATE state);
    static void enterBattle(bool flag);
    static bool isStopBattleSequence();
    void update(const fw::UpdateInfo& info);
    void postUpdate(const fw::UpdateInfo& info);
    void finalize();
    static float getFieldSpeed(const fw::UpdateInfo& info);
    void updateParam(const fw::UpdateInfo& info);
    virtual ~GfGameManager();  // slot 0
    static bool isGameObjEmpty();
    static bool isBladeChange();
    static bool isFullScreenMenu();
    static void setMapID(unsigned int, unsigned int);
    static bool isMapjump();
    static bool isMapjumpWithSaveData();
    static bool isAdvertize();
    static bool isPlayerDeadSequence();
    static bool isDisableAutoRun();
    static bool isRexAwakening();
    static bool isGmkTutorialMoverOK();
    static void setGmkTutorialMoverOK(bool ok);
    static GfPlayerDead getDeadType();
    static bool isForceBossBattleBgm();
    static bool isForceEventBgm();
    static bool isDisableJumpForRide();
    static void setHomuriWeaponExtraMesh(bool, float);
    static bool isPlayEnemyVoice();
    static bool isPartyMemberPlayVoice();
    static bool isEventWait();
    static bool isFieldLockMsgOK();
    static unsigned int getMapZoneID();
    static bool isPartyCreateForMapjump();
    static bool isInMetJIJI();
    static bool isEnableGimmickPhantomDamage();
    static bool isEnableGetFieldPrecious();
    static bool isEnableCreateBattleLock();
    static bool isPartyMover(gf::GF_OBJ_HANDLE* handle);
    static bool isNight();
    static bool isEnableHoodHomuraScenes();
    static bool isAssetNumberInvalid();
    static bool isEnableOpenMainMenuSequence();
    static bool isEnableOpenMainMenu();
    static gf::GF_OBJ_HANDLE* getPartyLeader();
    static gf::GF_OBJ_HANDLE* getControlMover();  // the object the player controls
    static gf::GF_OBJ_HANDLE* getPartyLeaderDriver();
    // whether an event is playing; with sequential, a sequential play's inner event state counts too
    static bool isEvent(bool sequential);
    // whether the player is in a talk (a forced one, or the game state's talk flag)
    static bool isTalking();
    static int getMapID();
    // the map a jump goes to (GfGameEnv's int at 0x10; GfFieldZoneScript::execScript names its script from it)
    static unsigned int getMapJumpID();
    static int getScenarioId();  // the chapter GfMenuGameAdapter::update_Chapter shows
    static bool isPlaySequenceClear();
    static bool isPlayerCameraPause();
    // the owner bonuses the party's precious items add up to (GfGameScene's)
    static const gf::OwnerBonus& getOwnerBonus();
    // whether the PC may access objects on the field now
    static bool isEnableFieldAccess();
    static bool isRoom();
    static bool isFadeout();
    static bool isStartGame();
    // SCOM_POPUP::exec holds popup kind 7 back while this is true
    static bool isBusyBladeCreateEvent();
    static bool isLeaveGameForDebug();
    static bool isControlFree();
    // an event plays: GfGameScene::isPlayEvent() when there is a GfGameScene (the symbols still spell it
    // fn_71002AA244; 1.0.0's isPlayEvent at 0x71003196DC has the same code, and SCOM_FIELD_VOICE's stop test calls it
    // in both)
    static bool isPlayEvent();
    static bool isScenarioGame();
    static bool isGmkTutorialOK();
    static bool isPlayEventOK();
    // the leader may show the landmark UI: control free and its target state 0/2/3/5 with no fade-out, state 1 the
    // target's m_gmkTutorialOK
    static bool isLandmarkUiOK();
    static bool isEnemyChangeBattleOK();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its code is in
    // gf_game_manager's unit among GfGameManager's functions and takes no instance. What it does: with
    // PtrSingleton<TUnk_B54858>'s instance in mode 1, whether GfDataBlade::fn_7100231884 (local flag 1, width 16) is
    // in [11115, 11130); otherwise whether it is at least 10034 and its value / 64 is below 157. Callers:
    // GfGameScene::checkFieldBladeChange / checkFieldBladeChangeForRide, GfPlayFactory::createPlayerDead, fn_71002B6A80.
    static bool fn_71002AAA0C();
    static bool isTalkOK();
    static bool isEnablePlayerDeadSequence();
    static void setGmkTutorialSequenceOK(bool ok);
    static bool isBattle();
    // GfGameUtil::isCondBladeModel asks it for a blade id before the blade's model condition
    static bool isChangeNormalHomuraForce(unsigned int blade);
    // whether the field target may be a battle target (GfGameTarget asks it each update)
    static bool isEnableFieldBattleTarget();
    // the game's state (GfGameState::getState's: this only forwards to it; GfGameSalvage::startSalvage starts only in
    // state 11)
    static GF_STATE getState();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in this
    // file among GfGameManager's functions (every named function of the unit is GfGameManager's or IQuestEvent's
    // inline virtuals). What it does: whether the game runs in the mode the title screen switches on: true when
    // gf_game_env.cpp's 3.0.1 singleton (TUnk_B54858: 0x10 bytes, created by fn_71002A752C from
    // initialize) exists and its int at 0x8 is 1. Only fn_71002AC558(flag & 1)
    // writes that int; it is reached from title_main.cpp's fn_7100156288 through fn_710014FDB8 and gf_manager.cpp's
    // fn_710032A1FC, which hands the same flag to fw::Framework (byte 0x459), fw::EffectManager (0x2FD8),
    // fw::SoundManager (0x44C8), the render DrSys parameters and GfDataGame (bit 0 of 0xFD6D0). GfMenuManager's
    // constructor tests it right after registering menu layer 3 for "menu_ira" (see GfMenuObjUtil::fn_710048FD30).
    // "Ira" in those paths suggests the Torna expansion's mode; that is inferred, not a name. 269 callers.
    static bool isClearGame();  // the game has been cleared once (the story's end reached)
    static bool fn_71002A9E68();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // gf_game_manager's unit, between GfGameManager's own functions. What it does: tail-calls fn_7100232754 and
    // returns its bool. Callers: GfMenuManager's layer-72 opener (fn_710035DBAC), GfMenuCharDataAdapter,
    // GfMenuObjCommonText::fn_71003E1F60.
    static bool fn_71002AC64C();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // gf_game_manager's unit among GfGameManager's functions. What it does: when fn_71002EDA8C answers true and
    // PtrSingleton<GfGameScene> exists, sets the scene's byte at 0x8B8 to 1. Callers: fn_71003BE1BC and the sys
    // plugin's autoSave (no arguments).
    static void fn_71002AC6A8();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // gf_game_manager's unit among GfGameManager's functions. What it does: false when gf_game_env.cpp's 3.0.1
    // singleton (TUnk_B54858) does not exist, else tail-calls fn_71002A75DC(singleton, 0x30101) (an add-on
    // content check). GfMenuObjUtil::fn_710048FD30 answers its add-on menu layer 1 with it; GfMenuManager's
    // constructor and GfGameScene::setEnemyDead call it too.
    static bool fn_71002AC598();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's
    // GfGamePlayerUniqueScheduler::update calls isBattle() where 3.0.1 calls this). A static of GfGameManager because
    // gf_game_manager.cpp's functions fill its unit. What it does: true while an event of type 2 or more plays
    // (GfGameEvent::getPlayEventId through GfDataEvent::getEventType), while the fade is not clear
    // (GfGameManager::isFadeClear), or while GfGameScene's battle bit (0x148 bit 1, GfGameScene::isBattle) is set;
    // false when there is no GfGameScene. Its only caller is GfGamePlayerUniqueScheduler::update, which skips the
    // scheduler while it is true.
    static bool fn_71002AC70C();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its code is in gf_game_manager's unit among
    // GfGameManager's functions and takes no instance. What it does: tail-calls gf::fn_71002EE904(value) (GfWeapon's
    // unit: the option data's SSoundUiOption at +0x4C gets value through fn_7100254FDC).
    static void fn_71002AC578(unsigned int value);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its code is in gf_game_manager's unit among
    // GfGameManager's functions and takes no instance. What it does: the int at 0x100 of PtrSingleton<TUnk_B535D0>'s
    // instance (its record's m_value28), 0 when there is none.
    static unsigned int fn_71002AC5EC();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its code is in gf_game_manager's unit among
    // GfGameManager's functions and takes no instance. What it does: sets the byte at 0x8C0 of PtrSingleton<GfGameScene>'s
    // instance when there is one.
    static void fn_71002AC6F0();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its code is in gf_game_manager's unit among
    // GfGameManager's functions and takes no instance. What it does: GfGameScene::fn_71002C4BFC() when there is a
    // GfGameScene, else false.
    static bool fn_71002AC764();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its code is in gf_game_manager's unit among
    // GfGameManager's functions and takes no instance. What it does: when TUnk_B54858's instance exists with mode 1,
    // whether any of the party's drivers 0..2 (GfGameParty::getHandleDriver(party, n)) is in battle; else whether
    // driver 0 or the party's blade (getHandleBlade(party, -1)) is in battle, false without a driver.
    static bool fn_71002AC77C(unsigned int party);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its code is in gf_game_manager's unit among
    // GfGameManager's functions and takes no instance. What it does: false unless TUnk_B54858's instance exists, its
    // mode is not 1 and fn_71002A75DC(0x30101) holds; then gf::fn_71002EE9A4() (option byte 0x84 is 0).
    static bool fn_71002AC89C();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its code is in gf_game_manager's unit among
    // GfGameManager's functions and takes no instance. What it does: whether id is 0 or one of 30255..30258.
    static bool fn_71002AC8E4(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its code is in gf_game_manager's unit among
    // GfGameManager's functions and takes no instance. What it does: the byte at 0x21B of PtrSingleton<tl::TitleMain>'s
    // instance is set (false without one).
    static bool fn_71002AC908();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its code is in gf_game_manager's unit among
    // GfGameManager's functions and takes no instance. What it does: whether the arena (TUnk_B535D0) is in state 5 and
    // btl::TUnk_B3A9C8's instance exists and either its fn_7100026A48 holds or its fn_7100026814 holds with
    // btl::Utility::AI_GetEnemyNum() == 0.
    static bool fn_71002AC930();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its code is in gf_game_manager's unit among
    // GfGameManager's functions and takes no instance. What it does: tail-call gf::fn_71002EE9EC / fn_71002EEA34 /
    // fn_71002EEA7C (GfWeapon's unit: the option data's bytes 0x7F / 0x80 / 0x81 are set).
    static bool fn_71002AC99C();
    static bool fn_71002AC9A0();
    static bool fn_71002AC9A4();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its code is in gf_game_manager's unit among
    // GfGameManager's functions and takes no instance. What it does: true while GfPlayComQuestCompleteUI::s_active
    // is above 0 or PtrSingleton<GfPlayComOpenNpcEntry>'s instance exists; else GfGameScene::fn_71002C4B38() when
    // there is a GfGameScene, false otherwise. Caller: GfGameScene::isBattleStop.
    static bool fn_71002AC340();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its code is in gf_game_manager's unit among
    // GfGameManager's functions and takes no instance. What it does: whether the int at 0x630 of PtrSingleton<GfGameScene>'s
    // instance is above 0 (false without one). Caller: btl::BattleCharacter::IsProcAI.
    static bool fn_71002AC384();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its code is in gf_game_manager's unit among
    // GfGameManager's functions and takes no instance. What it does: the handle of
    // PtrSingleton<GfGamePlayerFormation>'s first player (m_players[0].m_handle) when there is a formation and it is
    // not -1, else getPartyLeader() unless it is -1, else GfGameParty::fn_71002BC6F8(). Callers: gmk's
    // getPlayerPos / isPlayerExist / getInterestPos and many gimmick updates.
    static GF_OBJ_HANDLE* fn_71002AA074();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its code is in gf_game_manager's unit among
    // GfGameManager's functions and takes no instance. What it does: while there is a
    // GfGameScene and it plays an event, whether the object is not displayed (GfObjAcc::isDisp(0) false); false
    // otherwise. Caller: GfComBehaviorPc::update.
    static bool fn_71002AA25C(GF_OBJ_HANDLE* handle);
    static void clear();
    // takes fn_71002A9E68()'s answer in 3.0.1 (every caller passes it; the symbols still spell 1.0.0's setupGame())
    static void setupGame(bool flag);
    virtual void fn_710000FA68(unsigned int, bool, unsigned int);  // slot 2 (its code forwards the 32-bit value and the bool to GfGameScene, not the third; placeholder name: see IGfEvent)
    virtual void fn_710000FA60(unsigned int, unsigned int);  // slot 3 (forwards the first 32-bit value to GfGameScene; placeholder name: see IGfEvent)
    virtual void fn_710000FA64(unsigned int, unsigned int);  // slot 4 (forwards the first 32-bit value to GfGameScene; placeholder name: see IGfEvent)
    virtual void fn_710000FA20();  // slot 5 (forwards to GfGameScene; placeholder name: see IGfEvent)
    virtual void gevExecBuy(unsigned int, unsigned int, unsigned int);  // slot 6
    virtual void gevChangeParty();  // slot 7
    virtual void gevGetArts(unsigned int, unsigned int, bool);  // slot 8
    virtual void gevDriverLevel(unsigned int, unsigned int, unsigned int);  // slot 9
    virtual void gevSelectHikari(bool);  // slot 10
    virtual void gevBattleStart();  // slot 11
    virtual void gevBattleEnd();  // slot 12
    virtual void gevPause(unsigned int, unsigned int);  // slot 13
    virtual void gevChangeBlade(gf::GF_OBJ_HANDLE*, int, int);  // slot 14
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 15
    virtual void gevGameObjEnter(gf::GF_OBJ_HANDLE*);  // slot 16
    virtual void gevGameObjLeave(gf::GF_OBJ_HANDLE*);  // slot 17
    virtual void gevDriverActivate(unsigned int, gf::ActivateType, gf::ActivateType);  // slot 18
    virtual void gevBladeActivate(unsigned int, gf::ActivateType, gf::ActivateType);  // slot 19
    virtual void gevBladeUnselect(unsigned int, bool);  // slot 20
    virtual void gevBladeEnable(unsigned int);  // slot 21
    virtual void gevPlayEvent(gf::GEV, unsigned int);  // slot 22
    virtual void gevPartyMemberOK(bool);  // slot 23
    virtual void gevPartyIDMemberOK(bool, unsigned int);  // slot 24
    virtual void gevItemAdd(unsigned int, int);  // slot 25
    virtual void gevLayerPause(unsigned int, bool);  // slot 26
    virtual void gevReloadBdat(gf::RELOAD_BDAT, unsigned int);  // slot 27
    virtual void gevSalvageStateChange(unsigned int);  // slot 28
    virtual void gevChangeScenarioFlag(unsigned int, unsigned int);  // slot 29
    virtual void fn_710000FAB8(unsigned int id);  // slot 30 (forwards the id to TUnk_B54858::fn_71002A7734; placeholder name: see IGfEvent)
    virtual void gevChangeWeather(unsigned int, unsigned int);  // slot 31
    virtual void gevChangeTimeRange(unsigned int);  // slot 32
    virtual void gevGameState(gf::GF_STATE, gf::GF_STATE);  // slot 33
    virtual void gevControllFree(bool);  // slot 34
    virtual void gevMercenariesMissionFlag(unsigned int, unsigned int, unsigned int);  // slot 35
    virtual void fn_710000FA1C();  // slot 36 (forwards to GfGameScene; placeholder name: see IGfEvent)
    virtual void fn_710000FA18();  // slot 37 (forwards to GfGameScene; placeholder name: see IGfEvent)
    virtual void qevOrderQuest(gf::QuestOrderParam const&);  // slot 38
    virtual void qevCompleteQuest(gf::QuestCompleteParam const&);  // slot 39
    virtual void qevCompleteChildQuest(gf::QuestCompleteChildParam const&);  // slot 40

    // set at the end of initialize, cleared by finalize (the name is not the original's)
    bool m_initialized;
    // set by leaveGameForDebug, read by isLeaveGameForDebug (the name is not the original's)
    bool m_leaveGameForDebug;
    unsigned char pad_1A[0x6];
    static bool isFadeClear();
    static bool isExistBossEnemy();
    static bool isExistBossEnemyWithHp();
    static bool isPlayerFinishBattleState();
    static bool isWaitGimmickPopForMapjump();
    static bool isBattleStop();
    static const mm::Vec3& getControlMoverPosition();
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Statics of GfGameManager: their
    // addresses lie in gf_game_manager's unit among GfGameManager's functions and they use no instance.
    // What they do: fn_71002AC310 and fn_71002AC328 (the same code) answer whether GfPlayComQuestCompleteUI::s_start
    // is above 0; btl::BattleGlobal::PreUpdateProc calls both.
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static of GfGameManager (address among its
    // functions in gf_game_manager's unit). What it does: stores the flag into s_disablePlayerCameraPause.
    static void fn_71002AB4F8(bool flag);
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100D6CBE8). While it is set,
    // isPlayerCameraPause answers false; clear() resets it and fn_71002AB4F8 sets it (reached through the GOT, so
    // a class static rather than a file static)
    static bool s_disablePlayerCameraPause;
    // 1.0.0's isExecTutorial tail-called GfMenuObjTutorial::isWaiting from btl::BattleGlobal::PreUpdateProc;
    // 3.0.1's PreUpdateProc calls this one at the same place (the symbols still spell it fn_71002AA6CC)
    static bool isExecTutorial();
    static bool fn_71002AC310();
    static bool fn_71002AC328();
    // fn_71002AC650 / fn_71002AC670: whether GfItemUtil::getItemBoxCount of item 25472 / 25541 is not 0;
    // GfMenuBladeList::setupFromTeam, fn_710028DAB4 and fn_71002E2F4C call both.
    static bool fn_71002AC650();
    static bool fn_71002AC670();
    // fn_71002AC6D8: GfGameScene::isPlayEvent() when there is a GfGameScene (the same code as isPlayEvent);
    // gf::pc::StateUtil::playVibration calls it.
    static bool fn_71002AC6D8();
};
}  // namespace gf

#endif
