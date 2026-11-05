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
namespace gf { class GfMenuCallContext; }

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
            unsigned short id;  // 0: unused
            signed char attr;   // negative: unused
            unsigned char pad_7;

            // a set id and a non-negative attribute (the name is not the original's; an inline member: its two
            // loads become one 32-bit load, as in GetIraChainAttackSlotByBdatID)
            bool IsValid() const { return id != 0 && attr >= 0; }
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
    // whether the chain attack of group slot (m_groupSlot when negative) must end
    bool IsExitChainAttack(int slot) const;
    static void PreUpdate(const fw::UpdateInfo& info);
    // inline in 3.0.1 (1.0.0 has it out of line): drops m_flags.narrationPlayed
    void PreUpdateProc(const fw::UpdateInfo& info) {
        m_flags.narrationPlayed = false;
    }
    static void Update(const fw::UpdateInfo& info);
    void UpdateProc(const fw::UpdateInfo& info);
    // 2.0.0's symbols name it. What it does: true when the start direction step (byte 0x1978,
    // ChainAttackStartDirectionProc's switch) is past 1.
    bool IsStartDirectionAfterFadeOut() const;
    unsigned char GetSpAttackLevel(int index) const;
    float GetSpAttackRecast(int index, int attr) const;
    // the slot (0-2) of driver index's special attack entry with this id, -1 for none
    int GetIraChainAttackSlotByBdatID(int index, unsigned int bdatId) const;
    // the slot of the Ira blade n of driver index's group (a table by GetIraGroupDriverID), -1 for none
    int GetIraChainAttackSlot(int index, int n) const;
    void ModifyPosition();
    void ModifyPositionForward(gf::GF_OBJ_HANDLE* driver);
    void ModifyPositionBackward(gf::GF_OBJ_HANDLE* driver, gf::GF_OBJ_HANDLE* other);
    // the order (0-8) of attribute attr in m_orderAttrs, -1 for none
    int GetAttrOrder(int attr) const;
    void Start(gf::GF_OBJ_HANDLE* handle);
    int GetOrderAttr(int index) const;
    // the rate's float bits stepped up by one, as GetDamageRate's
    float GetBonusRate(gf::GF_OBJ_HANDLE* handle) const;
    void TurnButtonChllengeResultProc(TURN_BTN_RESULT_TYPE type);
    bool IsProc(bool) const;
    bool IsResult() const;
    float GetDamageRate() const;
    // 2.0.0's symbols name it. What it does: while the chain attack proc state (0x1A00) is 1-50, adds its float to
    // m_addedValue.
    void AddCriticalBonus(float value);
    // 2.0.0's symbols name it. What it does: m_addedValue while a chain attack proc state (0x1A00) is set, else 0.
    float GetCriticalBonus() const;
    void AddTotalDamage(unsigned int damage);
    void AddOverKillDamage(unsigned int damage);
    int GetGroupIndex() const;
    // 2.0.0's symbols give it a bool, which it does not read (2.0.0's callers pass true)
    bool IsStartWait(bool) const;
    bool IsSelectAction() const;
    // 2.0.0's symbols name it. A member because it reads this unit's
    // ChainAttackManager (BattleCharacter::AI_Move passes the singleton). What it does: true when the proc state
    // (0x1A00) is 12 or 13.
    bool IsIraChange() const;
    bool IsStopTime() const;

    // ElementalComboManager::CreateBreakEffect compares it with its character's handle (meaning unknown)
    gf::GF_OBJ_HANDLE* pad_8;
    unsigned char pad_10[0x10];
    gf::GfMenuCallContext* m_menuContext;  // AddOverKillDamage opens the overkill menu with it (the name is not the original's)
    unsigned char pad_28[0x8];
    ::mm::mtl::FixedVector<DROP_ITEM_DATA, 32> m_dropItems;  // AddDropData's (the name is not the original's)
    unsigned char pad_1838[0x108];
    float pad_1940;  // GetBonusRate gives no rate after the result states while it is 0.2 or more (meaning unknown)
    float m_addedValue;  // AddCriticalBonus adds to it (the name is not the original's)
    unsigned int m_totalDamage;  // AddTotalDamage (the name is not the original's)
    // AddOverKillDamage: the target's max HP as the overkill starts, then the damage added during it; GetBonusRate
    // rates their ratio (the names are not the original's)
    unsigned int m_overkillMaxHp;
    unsigned int m_overkillDamage;
    unsigned char pad_1954[0x4];
    unsigned int m_slowId;  // AddOverKillDamage's BattleGlobal::RegisterSlow id (the name is not the original's)
    unsigned char pad_195C[0x4];
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
    unsigned char m_groupCount;  // ModifyPosition's count of m_groups (the name is not the original's)
    unsigned char m_orderAttrs[9];  // GetOrderAttr (the name is not the original's)
    unsigned char pad_1A11[0x2];
    unsigned char pad_1A13;  // Start clears 0x1A13-0x1A15
    unsigned char pad_1A14;
    unsigned char pad_1A15;
    struct {
        unsigned short pad_bit0 : 1;
        unsigned short pad_bit1 : 1;
        unsigned short pad_bit2 : 1;
        unsigned short pad_bit3 : 1;
        unsigned short narrationPlayed : 1;  // UpdateProc sets it as it plays narration voice 3, PreUpdateProc drops it (the name is not the original's)
        unsigned short pad_bit5 : 5;
        unsigned short overkill : 1;  // AddOverKillDamage sets it as it starts the overkill (the name is not the original's)
        unsigned short pad_bit11 : 5;
    } m_flags;
    unsigned char pad_1A18[0x8];
};
}  // namespace btl

#endif
