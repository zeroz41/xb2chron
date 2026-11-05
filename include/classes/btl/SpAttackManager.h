#ifndef CLASSES_BTL_SPATTACKMANAGER_H
#define CLASSES_BTL_SPATTACKMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusivePtr.h"

namespace btl { class SpAttackManager; }
namespace fw { class Camera; class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; class GfArtsMovie; class GfTrinityAttack; }

namespace btl {
// table 0x7100B3BDA8
class SpAttackManager : public ::mm::mtl::PtrSingleton< ::btl::SpAttackManager> {
public:
    // PROGRESS_ID: NotifyProgress handles 0, 2 and 3 (no enumerator names are known)
    enum PROGRESS_ID {};

    // one running special attack (0x60 bytes); field names are inferred from the code (not the original's)
    struct PROC_DATA {
        PROC_DATA() : m_artsMovie(nullptr), m_trinityAttack(nullptr) { Reset(); }
        // 1.0.0's PROC_DATA::Reset (0x7100086230); inline in 3.0.1 (defined in sp_attack_manager.cpp)
        void Reset();
        bool IsMember(gf::GF_OBJ_HANDLE* handle) const;

        gf::GfArtsMovie* m_artsMovie;
        // set for a three-character attack: IsMember then also accepts the third character
        gf::GfTrinityAttack* m_trinityAttack;
        // RegisterSpAttack's three handles, in its argument order (the names are not the original's)
        gf::GF_OBJ_HANDLE* m_attacker;
        gf::GF_OBJ_HANDLE* m_partner;
        gf::GF_OBJ_HANDLE* m_target;
        unsigned long pad_28;
        unsigned long pad_30;
        unsigned long pad_38;
        // the step NotifyProgress moves the attack to (4, 5 or 7; the name is not the original's)
        int m_state;
        int pad_44;
        unsigned short pad_48;
        // the arts SlowProc reads the slow-motion row of (GetArtsData type 3; meaning unknown)
        unsigned short pad_4A;
        // a slow BattleGlobal::DeleteSlow ends when the attack stops (the name is not the original's)
        unsigned int m_slowId;
        // SlowProc's step through the slow-motion row (1-based columns are this + 1; 0xFF when done; the name is not
        // the original's)
        unsigned char m_slowStep;
        // two bytes reset as one (0xFF, 0): a 2-byte member assigned whole (the names are not the original's)
        struct Pair51 {
            Pair51() : pad_0(-1), pad_1(0) {}
            // MovieProc compares it signed with BattleCharacter::pad_CD4, then pad_1 - 6 with the animation frame
            signed char pad_0;
            unsigned char pad_1;
        } m_pair51;
        // the attack's phase: IsMovie is true while it is 3 or 4 (the name is not the original's)
        unsigned char m_phase;
        // eight bytes reset as one: a 4-aligned member assigned whole (the names are not the original's)
        struct Info54 {
            Info54() : pad_0(0), pad_4(0), m_slot(0), pad_7(0) {}
            unsigned int pad_0;
            unsigned short pad_4;
            // GetSpAttackSlot returns it (the name is not the original's)
            unsigned char m_slot;
            unsigned char pad_7;
        } m_info54;
        unsigned char pad_5C_0 : 1;
        // SlowProc runs only while it is set (meaning unknown)
        unsigned char pad_5C_1 : 1;
        // FinishUpdateAttackData clears it (the name is not the original's)
        unsigned char m_isUpdateAttackData : 1;
        // IsLastAttackDriver returns it (the name is not the original's)
        unsigned char m_isLastAttackDriver : 1;
        // NotifyProgress(0) sets one per side: the pair, then the third character (names not the original's)
        unsigned char m_progressPair : 1;
        unsigned char m_progressThird : 1;
        // IsDispThirdChr returns it for the first three-character attack (the name is not the original's)
        unsigned char m_isDispThirdChr : 1;
        unsigned char pad_5C_7 : 1;
        // (0x5D..0x5F is tail padding: UpdateProc's copy of a PROC_DATA moves 0x5D bytes)
    };

    SpAttackManager();
    virtual ~SpAttackManager();  // slot 0
    static void Create();
    static void Destroy();
    void NotifyMapChange();
    void DeleteCamera(bool interpolate);
    // 3.0.1 leaves it unnamed (fn_71000A76B0); 1.0.0's BattleManager::update calls this name (0x7100086900, a bare
    // ret) at the same place, between BladeChangeManager::PreUpdate and the next manager's (renames.tsv)
    static void PreUpdate(const fw::UpdateInfo& info);
    static void Update(const fw::UpdateInfo& info);
    void UpdateProc(const fw::UpdateInfo& info);
    // MirrorCopyProc and SeparatelyProc return true when the attack is over (UpdateProc then resets it)
    bool MirrorCopyProc(PROC_DATA& data);
    bool SeparatelyProc(PROC_DATA& data);
    void VoiceProc(PROC_DATA& data, bool flag);
    void SlowProc(PROC_DATA& data, bool flag);
    // true once the movie step is over (its caller goes on only then)
    bool MovieProc(PROC_DATA& data);
    bool RegisterSpAttack(gf::GF_OBJ_HANDLE* attacker, gf::GF_OBJ_HANDLE* partner, gf::GF_OBJ_HANDLE* target,
                          bool flag0, bool flag1);
    bool IsRegister(gf::GF_OBJ_HANDLE* handle) const;
    void NotifyProgress(gf::GF_OBJ_HANDLE* handle, PROGRESS_ID id);
    void FinishUpdateAttackData(gf::GF_OBJ_HANDLE* handle);
    unsigned char GetSpAttackSlot(gf::GF_OBJ_HANDLE* handle) const;
    gf::GF_OBJ_HANDLE* GetTargetHandle(gf::GF_OBJ_HANDLE* handle) const;
    bool IsLastAttackDriver(gf::GF_OBJ_HANDLE* handle) const;
    bool IsDispThirdChr() const;
    bool IsMovie() const;

    ::mm::mtl::IntrusivePtr<fw::Camera> m_camera;
    // the characters whose BattleCharacter flag DeleteCamera clears (the names are not the original's)
    gf::GF_OBJ_HANDLE* m_cameraCharas[3];
    PROC_DATA m_procs[5];
    // above zero while a special attack runs: Utility::AI_IsProcSpAttack tests it (the name is not the original's)
    int m_procCount;
    // seconds the camera has waited to start (UpdateProc adds the frame time while the camera has not started and
    // deletes it at 1; DeleteCamera clears it; the name is not the original's)
    float m_cameraWait;
    // DeleteCamera's pop time in 30ths of a second (the name is not the original's)
    unsigned char m_cameraFrames;
    unsigned char pad_211[0x7];
};

}  // namespace btl

#endif
