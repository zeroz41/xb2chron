#ifndef CLASSES_BTL_BLADEARTSMANAGER_H
#define CLASSES_BTL_BLADEARTSMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class BladeArtsManager; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace btl {
// table 0x7100B3A880
class BladeArtsManager : public ::mm::mtl::PtrSingleton< ::btl::BladeArtsManager> {
public:
    enum PROGRESS_ID {};

    // one blade art in progress (RegisterBladeArts fills it, BladeArtsProc runs it); the field names are not the
    // original's
    struct PROC_DATA {
        PROC_DATA() { clear(); }
        void clear() {
            m_driver = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
            m_blade = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
            m_target = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
            m_arts = -1;
            m_step = 0;
            m_challengeId = 0;
            m_isForced = false;
        }

        gf::GF_OBJ_HANDLE* m_driver;  // RegisterBladeArts' first handle
        gf::GF_OBJ_HANDLE* m_blade;   // its second (BattleCharacter::IsActBladeArts asks this one)
        gf::GF_OBJ_HANDLE* m_target;  // its third (GetTargetHandle returns it)
        int m_arts;                   // BattleCharacter::IsActBladeArts' answer (SetAction's int)
        int m_step;                   // BladeArtsProc's state: 0-4 running, 5 ending, 7 done
        unsigned int m_challengeId;   // ButtonChallenge::Start's id (StartButtonChallenge), cancelled at the end
        bool m_isForced;              // RegisterBladeArts' last bool: no battle checks; SetAction gets -1.0f
    };

    BladeArtsManager();
    virtual ~BladeArtsManager();  // slot 0
    static void Create();
    static void Destroy();
    void NotifyMapChange();
    // 1.0.0's name (its symbol at the same place in the file; 3.0.1's BattleManager::update calls it before
    // CharacterManager's update, as 1.0.0's does)
    static void PreUpdateProc(const fw::UpdateInfo& info);
    static void Update(const fw::UpdateInfo& info);
    bool BladeArtsProc(PROC_DATA& data);
    bool RegisterBladeArts(gf::GF_OBJ_HANDLE* driver, gf::GF_OBJ_HANDLE* blade, gf::GF_OBJ_HANDLE* target, int arts,
                           bool, bool forced);
    void FinishBladeArts(gf::GF_OBJ_HANDLE* handle);
    bool NotifyProgress(gf::GF_OBJ_HANDLE* handle, PROGRESS_ID id);
    void StartButtonChallenge(gf::GF_OBJ_HANDLE* handle);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0 has no function between
    // StartButtonChallenge and GetTargetHandle). A member because its address is in blade_arts_manager's unit, its
    // walk is GetTargetHandle's and BattleCharacter::AttackTimingProc calls it on the singleton. What it does:
    // returns the ButtonChallenge id (m_challengeId) of the entry whose driver or blade is the handle, 0 for none.
    unsigned int fn_71000161A8(gf::GF_OBJ_HANDLE* handle) const;
    gf::GF_OBJ_HANDLE* GetTargetHandle(gf::GF_OBJ_HANDLE* handle) const;
    bool IsRegister(gf::GF_OBJ_HANDLE* handle) const;
    bool IsBladeStart(gf::GF_OBJ_HANDLE* handle) const;
    bool IsBladeAttack(gf::GF_OBJ_HANDLE* handle) const;

    // the entry whose driver or blade is the handle (the lookup GetTargetHandle, IsRegister, IsBladeStart and
    // IsBladeAttack share; the name is not the original's)
    PROC_DATA* find(gf::GF_OBJ_HANDLE* handle) {
        for (int i = 0; i < m_procNum; i++) {
            if (m_procs[i].m_driver == handle || m_procs[i].m_blade == handle) {
                return &m_procs[i];
            }
        }
        return nullptr;
    }
    const PROC_DATA* find(gf::GF_OBJ_HANDLE* handle) const {
        for (int i = 0; i < m_procNum; i++) {
            if (m_procs[i].m_driver == handle || m_procs[i].m_blade == handle) {
                return &m_procs[i];
            }
        }
        return nullptr;
    }

    PROC_DATA m_procs[10];
    int m_procNum;
};
}  // namespace btl

#endif
