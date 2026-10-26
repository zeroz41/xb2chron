#ifndef BTL_SIREN_BATTLE_MANAGER_H
#define BTL_SIREN_BATTLE_MANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusivePtr.h"

// The class of application/BF2/battle/siren_battle_manager.cpp. Nothing names it: the symbols leave its table
// (0x7100B3BD68) and its singleton (0x7100B939D0) unnamed and 1.0.0 has no such file, so it is TUnk_B3BD68 and its
// functions keep placeholder names (new in 3.0.1, nothing in 1.0.0's place names them).

namespace fw { class Camera; class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace btl { class BattleCharacter; }

namespace btl {
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function: its unit's class has no name.
// What it does: allocates the unit's TUnk_B3BD68 (the new cites "battle/siren_battle_manager.cpp"), whose PtrSingleton
// constructor asserts get()==0, then loads its BDAT rows (fn_71000A53C4). btl::BattleManager::Initialize calls it
// last, after UIManager::Create.
void fn_71000A52CC();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function: as fn_71000A52CC. What it does:
// resets that object (fn_71000A5764) and deletes it; btl::BattleManager::Finalize calls it first, before
// UIManager::Destroy (the reverse of the create order).
void fn_71000A571C();

// table 0x7100B3BD68 (slot 0 its destructor, which releases m_camera); 0x1D0 bytes (fn_71000A52CC allocates so many)
class TUnk_B3BD68 : public ::mm::mtl::PtrSingleton< ::btl::TUnk_B3BD68> {
public:
    // One row of BDAT table 0x3C, as fn_71000A53C4 reads it; fields named after the columns (the struct's name is not
    // the original's). Level 0 of each array is not in the table: damage 0, gauge 1, down 250, shots 0.
    struct Param {
        float m_damage[5];     // "DamageLV%d" / 100
        float m_gauge[5];      // "GaugeLV%d" / 100
        float m_gaugeBonus;    // "GaugeBonus" / 100
        unsigned short m_arrangeID;  // "ArrangeID": the BattleCharacter's BDAT id (fn_71000A6C68)
        unsigned short m_gun;        // "Gun"
        unsigned short m_lance;      // "Lance"
        unsigned char m_down[5];     // "DownLV%d"
        unsigned char m_shotNum[5];  // "ShotNumLV%d"
        unsigned char m_shotFrame;   // "ShotFrame" (fn_71000A6C44 returns it in seconds)
        unsigned char pad_3d[0x3];
    };
    // One per side, indexed like m_params (by !flag); the name is not the original's.
    struct Side {
        gf::GF_OBJ_HANDLE* m_handle;  // the BattleCharacter's handle; (GF_OBJ_HANDLE*)-1 while none
        float m_gauge;                // fn_71000A6FD0 adds to it, never below 0
        unsigned char pad_c;          // 1 after a reset; fn_71000A5870 passes it to TalkManager::NotifyTrigger
        bool pad_d;                   // fn_71000A6C2C returns it
        bool pad_e;                   // while set fn_71000A6FD0 also sets the party gauge
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

    TUnk_B3BD68() : pad_c0(0), pad_c4(-1.0f), pad_d0(0), pad_1c8(0xFF), pad_1c9(0xFF), pad_1ca(0), pad_1cb(0), pad_1cc(0) {
        m_sides[0].reset();
        m_sides[1].reset();
    }
    virtual ~TUnk_B3BD68();  // slot 0

    // Placeholder names (members: they read this object's fields; their callers pass the singleton). What they do:
    // fn_71000A53C4: fills m_params from BDAT table 0x3C (one row each) and the situation tables (camera names,
    //   W/B positions) from table 0x3D's "situation", "camera", "Wpos", "Bpos"
    void fn_71000A53C4();
    // fn_71000A5764: pops m_camera from CameraManager's first layer, resets both sides and the state, shows the menus
    //   again (GfMenuManager::setDispAll(true)); BattleManager::gevMapjump runs it through fn_71000A586C
    void fn_71000A5764();
    void fn_71000A586C();
    // fn_71000A5B20: clears the side's pad_12_0
    void fn_71000A5B20(bool flag);
    // fn_71000A6050 / fn_71000A6054: BattleManager::update calls them with its UpdateInfo, the first beside the
    //   other managers' PreUpdate (it does nothing), the second beside their Update (singleton's fn_71000A606C)
    static void fn_71000A6050(const fw::UpdateInfo& info);
    static void fn_71000A6054(const fw::UpdateInfo& info);
    void fn_71000A606C(const fw::UpdateInfo& info);
    // fn_71000A6C20: the camera name of a situation
    const char* fn_71000A6C20(int situation) const;
    // fn_71000A6C2C: the side's pad_d
    bool fn_71000A6C2C(bool flag) const;
    // fn_71000A6C44: the side's ShotFrame in seconds (frames / 30)
    float fn_71000A6C44(bool flag) const;
    // fn_71000A6C68: while pad_1cb is clear, takes the character whose BDAT id is a side's ArrangeID as that side;
    //   pad_d0 = 1 once both sides have one
    void fn_71000A6C68(BattleCharacter* character);
    // fn_71000A6CCC: a side has a character
    bool fn_71000A6CCC() const;
    // fn_71000A6CF0: pops the current camera, then holds the given one
    void fn_71000A6CF0(::mm::mtl::IntrusivePtr<fw::Camera>& camera);
    // fn_71000A6DFC: pad_1cb set and (a camera held, pad_d0 in 12..18, or TalkManager's fn_71000AA39C)
    bool fn_71000A6DFC() const;
    // fn_71000A6E5C: true without pad_1cb, else pad_d0 is 11 or above 18 and nothing of fn_71000A6DFC holds
    bool fn_71000A6E5C() const;
    // fn_71000A6EBC / fn_71000A6F34: the side's damage / gauge rate at its level (gauge times GaugeBonus with
    //   pad_12_1; 0 with pad_12_0)
    float fn_71000A6EBC(bool flag) const;
    float fn_71000A6F34(bool flag) const;
    // fn_71000A6FD0: unless fn_71000A6DFC holds or pad_12_0 is set, adds (int)(value * gauge rate) + 1 to the side's
    //   gauge (DataManager::SetPartyGauge(gauge * 300) with pad_e), kept at 0 or above
    void fn_71000A6FD0(float value, bool flag);

    Param m_params[2];
    Side m_sides[2];
    ::mm::mtl::IntrusivePtr<fw::Camera> m_camera;  // the camera fn_71000A6CF0 holds
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
    unsigned char pad_1c9;  // GfGameParty::getHandleDriver's first argument (fn_71000A59E0)
    unsigned char pad_1ca;
    unsigned char pad_1cb;  // set while a siren battle runs (most functions test it)
    unsigned char pad_1cc;
    unsigned char pad_1cd[0x3];
};
}  // namespace btl

#endif
