#ifndef BTL_SIREN_BATTLE_MANAGER_H
#define BTL_SIREN_BATTLE_MANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusivePtr.h"

// The class of application/BF2/battle/siren_battle_manager.cpp. Nothing names it: the symbols leave its table
// (0x7100B3BD68) and its singleton (0x7100B939D0) unnamed and 1.0.0 has no such file, so it is SirenBattleManager and its
// functions keep placeholder names (new in 3.0.1, nothing in 1.0.0's place names them).

namespace fw { class Camera; class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace btl { class BattleCharacter; }

namespace btl {

// table 0x7100B3BD68 (slot 0 its destructor, which releases m_camera); 0x1D0 bytes (Create allocates so many)
class SirenBattleManager : public ::mm::mtl::PtrSingleton< ::btl::SirenBattleManager> {
public:
    // 2.0.0's symbols name it. What it does: allocates the unit's SirenBattleManager (the new cites "battle/siren_battle_manager.cpp"), whose PtrSingleton
    // constructor asserts get()==0, then loads its BDAT rows (Initialize). btl::BattleManager::Initialize calls it
    // last, after UIManager::Create.
    static void Create();
    // 2.0.0's symbols name it. What it does:
    // resets that object (Finalize) and deletes it; btl::BattleManager::Finalize calls it first, before
    // UIManager::Destroy (the reverse of the create order).
    static void Destroy();
    // One row of BDAT table 0x3C, as Initialize reads it; fields named after the columns (the struct's name is not
    // the original's). Level 0 of each array is not in the table: damage 0, gauge 1, down 250, shots 0.
    struct Param {
        float m_damage[5];     // "DamageLV%d" / 100
        float m_gauge[5];      // "GaugeLV%d" / 100
        float m_gaugeBonus;    // "GaugeBonus" / 100
        unsigned short m_arrangeID;  // "ArrangeID": the BattleCharacter's BDAT id (SetSirenObject)
        unsigned short m_gun;        // "Gun"
        unsigned short m_lance;      // "Lance"
        unsigned char m_down[5];     // "DownLV%d"
        unsigned char m_shotNum[5];  // "ShotNumLV%d"
        unsigned char m_shotFrame;   // "ShotFrame" (GetShootBulletIntrevalSec returns it in seconds)
        unsigned char pad_3d[0x3];
    };
    // One per side, indexed like m_params (by !flag); the name is not the original's.
    struct Side {
        gf::GF_OBJ_HANDLE* m_handle;  // the BattleCharacter's handle; (GF_OBJ_HANDLE*)-1 while none
        float m_gauge;                // AddSirenSpGaugeRate adds to it, never below 0
        unsigned char pad_c;          // 1 after a reset; NotifyInputSpAttack passes it to TalkManager::NotifyTrigger
        bool pad_d;                   // GetShootBulletNum returns it
        bool pad_e;                   // while set AddSirenSpGaugeRate also sets the party gauge
        unsigned char pad_f;
        signed char pad_10;           // the BattleCharacter's byte at 0xEEF; 90 after a reset
        unsigned char m_level;        // indexes m_params' level arrays
        unsigned char pad_12_0 : 1;   // while set the side's damage/gauge rates are 0
        unsigned char pad_12_1 : 1;   // while set the gauge rate is multiplied by m_gaugeBonus
        unsigned char pad_12_2 : 6;
        unsigned char pad_13[0x5];

        void reset() {
            m_handle = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
            m_gauge = 0.0f;
            pad_c = 1;
            pad_d = false;
            pad_10 = 90;
            m_level = 0;
            pad_12_0 = 0;
            pad_12_1 = 0;
        }
    };

    SirenBattleManager() : pad_c0(0), pad_c4(-1.0f), pad_d0(0), pad_1c8(0xFF), pad_1c9(0xFF), pad_1ca(0), pad_1cb(0), pad_1cc(0) {
        m_sides[0].reset();
        m_sides[1].reset();
    }
    virtual ~SirenBattleManager();  // slot 0

    // 2.0.0's symbols name them. What they do: Initialize: fills m_params from BDAT table 0x3C (one row each) and the
    // situation tables (camera names, W/B positions) from table 0x3D's "situation", "camera", "Wpos", "Bpos"
    void Initialize();
    // Finalize: pops m_camera from CameraManager's first layer, resets both sides and the state, shows the menus
    //   again (GfMenuManager::setDispAll(true)); BattleManager::gevMapjump runs it through NotifyMapChange
    void Finalize();
    void NotifyMapChange();
    // NotifyDownEnd: clears the side's pad_12_0
    void NotifyDownEnd(bool flag);
    // PreUpdate / Update: BattleManager::update calls them with its UpdateInfo, the first beside the
    //   other managers' PreUpdate (it does nothing), the second beside their Update (singleton's UpdateProc)
    static void PreUpdate(const fw::UpdateInfo& info);
    static void Update(const fw::UpdateInfo& info);
    void UpdateProc(const fw::UpdateInfo& info);
    // GetSituationCameraName: the camera name of a situation
    const char* GetSituationCameraName(int situation) const;
    // GetShootBulletNum: the side's pad_d
    bool GetShootBulletNum(bool flag) const;
    // GetShootBulletIntrevalSec: the side's ShotFrame in seconds (frames / 30)
    float GetShootBulletIntrevalSec(bool flag) const;
    // SetSirenObject: while pad_1cb is clear, takes the character whose BDAT id is a side's ArrangeID as that side;
    //   pad_d0 = 1 once both sides have one
    void SetSirenObject(const BattleCharacter* character);
    // IsRegisterSiren: a side has a character
    bool IsRegisterSiren() const;
    // SetGimmickCamera: pops the current camera, then holds the given one
    void SetGimmickCamera(::mm::mtl::IntrusivePtr<fw::Camera> camera);
    // IsCameraProc: pad_1cb set and (a camera held, pad_d0 in 12..18, or TalkManager's IsTalkSirenSp)
    bool IsCameraProc() const;
    // IsEnableOperate: true without pad_1cb, else pad_d0 is 11 or above 18 and nothing of IsCameraProc holds
    bool IsEnableOperate() const;
    // GetDamageBonus / GetGaugeRate: the side's damage / gauge rate at its level (gauge times GaugeBonus with
    //   pad_12_1; 0 with pad_12_0)
    float GetDamageBonus(bool flag) const;
    float GetGaugeRate(bool flag) const;
    // AddSirenSpGaugeRate: unless IsCameraProc holds or pad_12_0 is set, adds (int)(value * gauge rate) + 1 to the side's
    //   gauge (DataManager::SetPartyGauge(gauge * 300) with pad_e), kept at 0 or above
    void AddSirenSpGaugeRate(float value, bool flag);

    Param m_params[2];
    Side m_sides[2];
    ::mm::mtl::IntrusivePtr<fw::Camera> m_camera;  // the camera SetGimmickCamera holds
    int pad_c0;
    float pad_c4;
    unsigned char pad_c8[0x8];
    int pad_d0;  // state: 1 once both sides have characters; 11..18 later
    unsigned char pad_d4[0x4];
    const char* m_cameraNames[20];  // by situation ("camera")
    struct {
        unsigned short m_wpos;  // "Wpos"
        unsigned short m_bpos;  // "Bpos"
    } m_positions[20];  // by situation
    unsigned char pad_1c8;
    unsigned char pad_1c9;  // GfGameParty::getHandleDriver's first argument (IsEnableSpAttack)
    unsigned char pad_1ca;
    unsigned char pad_1cb;  // set while a siren battle runs (most functions test it)
    unsigned char pad_1cc;
    unsigned char pad_1cd[0x3];
};
}  // namespace btl

#endif
