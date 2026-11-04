#ifndef BTL_FORMATION_CHANGE_MANAGER_H
#define BTL_FORMATION_CHANGE_MANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/Vec3.h"

// The class of application/BF2/battle/formation_change_manager.cpp. Nothing names it: the symbols leave its table
// (0x7100B3BC20) and its singleton (0x7100B942E8) unnamed and 1.0.0 has no such file, so it is FormationChangeManager and its
// functions keep placeholder names (new in 3.0.1, nothing in 1.0.0's place names them).

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace btl {
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function: its unit's class has no name.
// What it does: allocates the unit's FormationChangeManager (the new cites "battle/formation_change_manager.cpp"), whose
// PtrSingleton constructor asserts get()==0, then resets it (NotifyMapChange). btl::BattleManager::Initialize calls it
// after BladeChangeManager::Create.
void fn_710009D7B8();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function: as fn_710009D7B8. What it does:
// deletes that object; btl::BattleManager::Finalize calls it between SpAttackManager::Destroy and BladeChangeManager::Destroy (the reverse of the create order).
void fn_710009D90C();

// table 0x7100B3BC20 (slot 0 its destructor, which only clears the singleton); 0x2A0 bytes (fn_710009D7B8 allocates
// so many)
class FormationChangeManager : public ::mm::mtl::PtrSingleton< ::btl::FormationChangeManager> {
public:
    // One queued request (the struct's and the fields' names are not the original's): type 1 (RegisterFormationChange) fades
    // a pair of characters, run by fn_710009DCAC; type 2 (RegisterBladeChange) changes one character's group driver, run
    // by fn_710009E008. 0x40 bytes (the Vec3 aligns it to 16).
    struct Request {
        Request() { clear(); }
        void clear() {
            m_handle[0] = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
            m_handle[1] = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
            m_pos = ::mm::Vec3::zero;
            m_type = 0;
            m_doneFlags = 0;
            m_flag32 = 0;
            m_end = 0;
            m_serial = 0;
            m_step = 0;
            m_groupIndex = 0;
            m_flag29 = 0;
            m_flag2a = 0;
            pad_2b = 0;
            m_time = 0.0f;
        }

        ::mm::Vec3 m_pos;               // the first character's position when queued
        gf::GF_OBJ_HANDLE* m_handle[2];  // the characters (type 2 uses the first only)
        unsigned int m_serial;          // FormationChangeManager::m_serial when queued
        int m_step;                     // the run's step, 0-4
        unsigned char m_groupIndex;     // the first character's GetGroupIndex
        bool m_flag29;                  // type 2: the character's IsForward when queued
        bool m_flag2a;                  // type 2: RegisterBladeChange's flag
        unsigned char pad_2b;
        float m_time;                   // time in the step (the update's delta added up)
        unsigned char m_type;           // 1 or 2; 0 unused
        unsigned char m_doneFlags;      // type 1, step 3: bit 0 the first, bit 1 the second character done
        bool m_flag32;                  // set by SetEnableCancel, tested by fn_710009ED18
        bool m_end;                     // set by ForceExit or when a character left; ends the run
    };

    FormationChangeManager();
    virtual ~FormationChangeManager();  // slot 0

    // 2.0.0's symbols name them. What they do: NotifyMapChange: m_serial = 1 and every request cleared
    // (BattleManager::gevMapjump; fn_710009D7B8)
    void NotifyMapChange();
    // PreUpdate / Update: BattleManager::update calls them with its UpdateInfo, the first beside the
    //   other managers' PreUpdate (it does nothing), the second beside their Update (singleton's UpdateProc)
    static void PreUpdate(const fw::UpdateInfo& info);
    static void Update(const fw::UpdateInfo& info);
    // UpdateProc: runs each request by type (fn_710009DCAC / fn_710009E008, given the UpdateInfo's delta) and
    //   removes it (the last moves into its place) when the run ends or the type is unknown
    void UpdateProc(const fw::UpdateInfo& info);
    // fn_710009DCAC / fn_710009E008: one step of a type 1 / type 2 request; true when it ended
    bool fn_710009DCAC(float delta, Request& request);
    bool fn_710009E008(float delta, Request& request);
    // RegisterFormationChange: queues a type 1 request for two battling characters that are not in one already (at most 10)
    bool RegisterFormationChange(gf::GF_OBJ_HANDLE* first, gf::GF_OBJ_HANDLE* second);
    // RegisterBladeChange: queues a type 2 request for a battling character that is not in one already (at most 10)
    bool RegisterBladeChange(gf::GF_OBJ_HANDLE* handle, bool flag);
    // ForceExit / SetEnableCancel: sets m_end / m_flag32 of the request the character is in
    void ForceExit(gf::GF_OBJ_HANDLE* handle);
    // fn_710009EB1C: the request the character is in, else nullptr
    Request* fn_710009EB1C(gf::GF_OBJ_HANDLE* handle);
    // IsRegister: whether the character is in a request
    bool IsRegister(gf::GF_OBJ_HANDLE* handle) const;
    // IsRegisterGroup: whether a request's m_groupIndex is group
    bool IsRegisterGroup(int group) const;
    // IsRegisterBladeChange / IsRegisterFormationChange: whether the character is in a type 2 / type 1 request
    bool IsRegisterBladeChange(gf::GF_OBJ_HANDLE* handle) const;
    bool IsRegisterFormationChange(gf::GF_OBJ_HANDLE* handle) const;
    void SetEnableCancel(gf::GF_OBJ_HANDLE* handle);
    // fn_710009ED18: for the character's request, true when m_flag32 is set, else the character's flag bit at
    //   0x11B3 when IsForward and IsControlCharacterGroup hold; true when it is in none
    bool fn_710009ED18(gf::GF_OBJ_HANDLE* handle);

    Request m_requests[10];
    int m_count;            // requests in use
    unsigned int m_serial;  // counts the requests queued, from 1 (the name is not the original's)
};
}  // namespace btl

#endif
