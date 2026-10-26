#ifndef CLASSES_BTL_BLADECHANGEMANAGER_H
#define CLASSES_BTL_BLADECHANGEMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "fw/UpdateInfo.h"

namespace btl { class BladeChangeManager; class BattleCharacter; }
namespace gf { class GF_OBJ_HANDLE; }

namespace btl {
// table 0x7100B3A8C0
class BladeChangeManager : public ::mm::mtl::PtrSingleton< ::btl::BladeChangeManager> {
public:
    // one blade change in progress (StartBladeChange fills it, BladeChangeProc/HomuraChangeProc/ForceHikariProc run
    // it); the field names are not the original's
    struct PROC_DATA {
        PROC_DATA() { clear(); }
        void clear() {
            m_driver = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
            m_blade = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
            m_effect = 0;
            m_enhance = 0;
            m_newBlade = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
            m_changeBladeIndex = -1;
            m_baseBladeBdatId = 0;
            m_wait = 0;
            m_serial = 0;
            m_timer = 0.0f;
            m_type = 0;
            m_kind = 0;
            m_isWithChain = true;
            m_flag3f = false;
            m_isDriverDone = false;
            m_isNewBladeDone = false;
            m_isFinished = false;
            m_isNotHomura = true;
        }

        gf::GF_OBJ_HANDLE* m_driver;    // StartBladeChange's first handle
        gf::GF_OBJ_HANDLE* m_blade;     // its second
        gf::GF_OBJ_HANDLE* m_newBlade;  // the third handle IsRegister asks (-1 until set)
        unsigned int m_effect;          // an effect handle UpdateProc keeps at the blade's position (0 for none)
        int m_enhance;                  // BattleCharacter::SatisfyEnhanceCondition(0x167) at the start
        int m_changeBladeIndex;         // StartBladeChange's first int (GetChangeBladeIndex)
        int m_baseBladeBdatId;          // the blade character's bdat id at the start (GetBaseBladeBdatID)
        int m_wait;                     // IsReceiveLater compares it with a limit chosen by m_kind
        int m_serial;                   // the manager's m_serial when started
        float m_timer;                  // the Proc functions' timer
        unsigned char m_type;           // StartBladeChange's second int (GetBladeChangeType); 3-5 are Homura's
        signed char m_kind;             // 0, 1 or 2 from m_type
        bool m_isWithChain;             // StartBladeChange's bool (and no chain attack running)
        bool m_flag3f;
        bool m_isDriverDone;            // the driver no longer counts as registered
        bool m_isNewBladeDone;          // m_newBlade no longer counts as registered
        bool m_isFinished;              // FinishBladeChange sets it
        bool m_isNotHomura;             // m_type is not 3-5
    };

    BladeChangeManager();
    virtual ~BladeChangeManager();  // slot 0
    static void Create();
    static void Destroy();
    // 1.0.0's name: 3.0.1's BattleManager::gevMapjump calls it where 1.0.0's calls BladeChangeManager::NotifyMapChange
    // (the same code). Its symbol still spells fn_71000166CC.
    void NotifyMapChange();
    // 1.0.0's name: 3.0.1's BattleManager::update calls it between BladeArtsManager::PreUpdateProc and TUnk_B3BC20's,
    // where 1.0.0's calls BladeChangeManager::PreUpdate. Its symbol still spells fn_710001671C.
    static void PreUpdate(const fw::UpdateInfo& info);
    static void Update(const fw::UpdateInfo& info);
    void UpdateProc(const fw::UpdateInfo& info);
    bool BladeChangeProc(PROC_DATA& data, float delta);
    bool HomuraChangeProc(PROC_DATA& data, float delta);
    bool ForceHikariProc(PROC_DATA& data, float delta);
    void AppearBuff(int, BattleCharacter*, BattleCharacter*);
    bool StartBladeChange(gf::GF_OBJ_HANDLE* driver, gf::GF_OBJ_HANDLE* blade, int index, int type, bool withChain);
    void FinishBladeChange(gf::GF_OBJ_HANDLE* handle);
    int GetChangeBladeIndex(gf::GF_OBJ_HANDLE* handle) const;
    int GetBaseBladeBdatID(gf::GF_OBJ_HANDLE* handle) const;
    int GetBladeChangeType(gf::GF_OBJ_HANDLE* handle) const;
    bool IsRegister(gf::GF_OBJ_HANDLE* handle) const;
    bool IsReceiveLater(gf::GF_OBJ_HANDLE* handle) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // blade_change_manager's unit, its walk is IsRegister's and Utility::IsEnableEventStart,
    // ChainAttackManager::ChainAttackStartDirectionProc and BattleCharacter::CheckForceExit call it on the singleton.
    // What it does: true when an entry whose driver or blade is the handle (any entry for a handle of -1) has
    // m_isNotHomura clear, i.e. a Homura change (type 3-5) of that character is running.
    bool fn_710001903C(gf::GF_OBJ_HANDLE* handle) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // blade_change_manager's unit and its walk is IsProcHomuriEnd's. What it does: true when an entry has type 1,
    // change blade index 4 and m_isNewBladeDone clear.
    bool fn_71000190E0() const;
    bool IsProcHomuriEnd() const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's StateField::onDead has no such call).
    // A member because its address is in blade_change_manager's unit and StateField::onDead calls it on
    // PtrSingleton<BladeChangeManager>::sys(). What it does: finds the entry IsRegister would (driver with
    // m_isDriverDone clear, blade, or m_newBlade with m_isNewBladeDone clear); for that entry it returns true when
    // CharacterManager::GetCharacterConst(handle) is none, else the negation of fn_7100028D0C(character, false); true
    // when no entry holds it. StateField::onDead handles a death only when true.
    bool fn_7100019180(gf::GF_OBJ_HANDLE* handle);

    PROC_DATA m_procs[10];
    int m_procNum;
    int m_serial;  // StartBladeChange's counter for PROC_DATA::m_serial (1 after NotifyMapChange, skips 0 on wrap)
};
}  // namespace btl

#endif
