#ifndef CLASSES_BTL_CHAINATTACKMANAGER_H
#define CLASSES_BTL_CHAINATTACKMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/fw/Camera.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/MMStdBase.h"

namespace btl { class ChainAttackManager; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace btl {
// table 0x7100B3A960; Create allocates 0x1A20 bytes
class ChainAttackManager : public ::mm::mtl::PtrSingleton< ::btl::ChainAttackManager> {
public:
    enum TURN_BTN_RESULT_TYPE : int;

    // one item the chain attack drops (AddDropData/AddDropHealpotData fill them, DropAllItem drops them); 0xC0
    // bytes, the copy constructor out of line in this unit
    struct DROP_ITEM_DATA {
        DROP_ITEM_DATA(const DROP_ITEM_DATA& other);

        gf::GF_OBJ_HANDLE* handle;  // UpdateProc reads its transform (the name is not the original's)
        unsigned char pad_8[0xB8];
    };

    // one driver's special attack state (stride 0x1C; GetSpAttackLevel reads level)
    struct SP_ATTACK_DATA {
        // three entries (the struct name and its fields are not the original's): GetSpAttackRecast returns the
        // recast of the one with a set id and the attribute asked for
        struct ENTRY {
            float recast;
            unsigned int id : 16;  // 0: unused
            int attr : 8;          // negative: unused
        };
        ENTRY entries[3];
        unsigned char level;  // GetSpAttackLevel
        unsigned char pad_19[0x3];
    };

    ChainAttackManager();
    virtual ~ChainAttackManager();  // slot 0
    static void Create();
    static void Destroy();
    void Reset(int);
    static void PreUpdate(const fw::UpdateInfo& info);
    // inline in 3.0.1 (1.0.0 has it out of line): drops m_flags.narrationPlayed
    void PreUpdateProc(const fw::UpdateInfo& info) {
        m_flags.narrationPlayed = false;
    }
    static void Update(const fw::UpdateInfo& info);
    void UpdateProc(const fw::UpdateInfo& info);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this unit's
    // ChainAttackManager (BladeChangeManager::BladeChangeProc passes the singleton). What it does: true when the
    // start direction step (byte 0x1978, ChainAttackStartDirectionProc's switch) is past 1.
    bool fn_7100023F58() const;
    unsigned char GetSpAttackLevel(int index) const;
    float GetSpAttackRecast(int index, int attr) const;
    int GetOrderAttr(int index) const;
    void TurnButtonChllengeResultProc(TURN_BTN_RESULT_TYPE type);
    bool IsProc(bool) const;
    bool IsResult() const;
    float GetDamageRate() const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it updates this
    // unit's ChainAttackManager (BattleCharacter::SatisfyEnhanceCondition passes the singleton). What it does:
    // while the chain attack proc state (0x1A00) is 1-50, adds its float to m_addedValue.
    void fn_71000247D0(float value);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this unit's
    // ChainAttackManager (BattleCharacter::GetCriticalRate passes the singleton). What it does: m_addedValue
    // while a chain attack proc state (0x1A00) is set, else 0.
    float fn_71000247F4() const;
    void AddTotalDamage(unsigned int damage);
    int GetGroupIndex() const;
    bool IsStartWait() const;
    bool IsSelectAction() const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this unit's
    // ChainAttackManager (BattleCharacter::AI_Move passes the singleton). What it does: true when the proc state
    // (0x1A00) is 12 or 13.
    bool fn_7100024A0C() const;
    bool IsStopTime() const;

    // ElementalComboManager::CreateBreakEffect compares it with its character's handle (meaning unknown)
    gf::GF_OBJ_HANDLE* pad_8;
    unsigned char pad_10[0x20];
    ::mm::mtl::FixedVector<DROP_ITEM_DATA, 32> m_dropItems;  // AddDropData's (the name is not the original's)
    unsigned char pad_1838[0x10C];
    float m_addedValue;  // fn_71000247D0 adds to it (the name is not the original's)
    unsigned int m_totalDamage;  // AddTotalDamage (the name is not the original's)
    unsigned char pad_194C[0x14];
    ::mm::mtl::IntrusivePtr<fw::Camera> m_startCamera;  // ChainAttackStartDirectionProc pops it (the name is not the original's)
    unsigned char pad_1968[0x10];
    unsigned char m_startStep;  // ChainAttackStartDirectionProc's step (the name is not the original's)
    unsigned char pad_1979[0xF];
    ::mm::mtl::IntrusivePtr<fw::Camera> m_camera;  // UpdateProc pops it (the name is not the original's)
    unsigned char pad_1990[0x14];
    SP_ATTACK_DATA m_spAttacks[3];  // GetSpAttackLevel (the name is not the original's)
    unsigned char pad_19F8[0x4];
    unsigned short m_damageRate;  // GetDamageRate (the name is not the original's)
    unsigned char pad_19FE[0x2];
    unsigned char m_procState;  // IsProc/IsResult/IsStartWait read it (the name is not the original's)
    unsigned char pad_1A01[0x2];
    unsigned char m_groupSlot;  // GetGroupIndex's index into m_groups (the name is not the original's)
    unsigned char m_groups[3];  // GetGroupIndex (the name is not the original's)
    unsigned char pad_1A07;
    unsigned char m_orderAttrs[9];  // GetOrderAttr (the name is not the original's)
    unsigned char pad_1A11[0x5];
    struct {
        unsigned short pad_bit0 : 1;
        unsigned short pad_bit1 : 1;
        unsigned short pad_bit2 : 1;
        unsigned short pad_bit3 : 1;
        unsigned short narrationPlayed : 1;  // UpdateProc sets it as it plays narration voice 3, PreUpdateProc drops it (the name is not the original's)
        unsigned short pad_bit5 : 11;
    } m_flags;
    unsigned char pad_1A18[0x8];
};
}  // namespace btl

#endif
