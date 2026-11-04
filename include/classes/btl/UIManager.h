#ifndef CLASSES_BTL_UIMANAGER_H
#define CLASSES_BTL_UIMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedVector.h"
#include "classes/gf/GfMenuCallContext.h"

namespace btl { class BattleCharacter; class UIManager; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; class GfMenuCallContext; }
namespace mm { class Vec3; }

namespace btl {
// table 0x7100B3BE28
class UIManager : public ::mm::mtl::PtrSingleton< ::btl::UIManager> {
public:
    // an input the battle UI is told about (GfGameTarget's selectRight sends 5, selectLeft 4; the names of the values
    // are not known)
    enum INPUT_TYPE {};
    // a tutorial RegisterTutorial queues (the field names are not the original's)
    struct TutorialInfo {
        unsigned int m_id : 8;     // the tutorial
        unsigned int m_time : 21;  // RegisterTutorial's time, in 1/0x40000 units
        unsigned int m_force : 1;  // RegisterTutorial's bool
        bool pad_bit30 : 1;
        bool pad_bit31 : 1;  // set for tutorial 0x6C
    };

    // 3.0.1 has no out-of-line copy (1.0.0's 0x710008D8B0): Create builds it in place
    UIManager()
        : m_kakuseiRate(0.0f), m_kakusei(false), m_kakuseiOther(false),
          m_rescueObj(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), m_rescueOpen(false),
          pad_30(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), pad_38(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)),
          pad_40(0), pad_41(0), pad_e0(0.0f), m_elementComboSerial(1), pad_e8(0), pad_ec(0.0f), pad_f0(3) {
        pad_bit8 = false;
        pad_bit9 = false;
        pad_bit10 = false;
        pad_bit11 = false;
        pad_bit12 = false;
        pad_bit13 = false;
        pad_bit14 = false;
        pad_bit15 = false;
        pad_bit16 = false;
        pad_bit17 = false;
        pad_bit18 = false;
        pad_bit19 = false;
        pad_bit20 = false;
    }
    virtual ~UIManager();  // slot 0
    static void Create();
    static void Destroy();
    void NotifyMapChange();
    // 2.0.0's symbols name it. What it does: pad_38 = its argument; nothing in the module calls it directly.
    void NotifyRecordUpdate(gf::GF_OBJ_HANDLE* obj);
    static void PreUpdate(const fw::UpdateInfo& info);
    static void Update(const fw::UpdateInfo& info);
    void UpdateProc(const fw::UpdateInfo& info);
    void UpdateMenuData(const fw::UpdateInfo& info);
    void UpdateRescueUI();
    // 2.0.0's symbols name it. UpdateProc calls it with this after UpdateRescueUI.
    void UpdatePartyGauge();
    // 2.0.0's symbols name it. UpdateProc calls it with this; it updates pad_40/pad_41.
    void UpdateBattleTime();
    // 2.0.0's symbols name it. UpdateProc tail-calls it with this and its UpdateInfo; it shows the tutorials
    // RegisterTutorial queued in m_tutorials.
    void UpdateTutorial(const fw::UpdateInfo& info);
    bool RegisterTutorial(unsigned int id, float time, bool force);
    unsigned int StartElementalComboDirectionUI(int combo);
    void ExitElementalComboDirectionUI(unsigned int id);
    void SetKakuseiData(bool kakusei, bool other, float rate);
    void RegisterRescueUI(gf::GF_OBJ_HANDLE* obj);
    void DispChainUI(gf::GF_OBJ_HANDLE* obj);
    void DispBuffUI(const mm::Vec3& pos, int type, bool flag);
    void DispSystemMessageUI(const BattleCharacter* chara, int type, bool flag);
    void DispElementalEffectUI(gf::GF_OBJ_HANDLE* obj, int type);
    void DispUniteComboUI(const mm::Vec3& pos, int param0, int param1);
    void DispUniteComboUI(int param0, int param1, unsigned short value0, unsigned short value1,
                          unsigned short value2, unsigned char sub0, unsigned char sub1, unsigned char sub2);
    void NotifyInput(INPUT_TYPE type, int arg);

    // the elemental combo direction (the names are not the original's): StartElementalComboDirectionUI opens it,
    // ExitElementalComboDirectionUI cancels it, UpdateProc releases the context once it ends
    struct ElementComboDirection {
        ElementComboDirection() : m_context(nullptr), m_id(0), m_type(0), m_exit(false) {}
        // drops the context's reference and forgets the direction
        void clear() {
            if (m_context != nullptr) {
                m_context->release();
                m_context = nullptr;
            }
            m_context = nullptr;
            m_id = 0;
            m_type = 0;
            m_exit = false;
        }
        gf::GfMenuCallContext* m_context;
        unsigned int m_id;
        unsigned char m_type;
        bool m_exit;
    };
    ElementComboDirection m_elementCombo;
    // SetKakuseiData's values (the names are not the original's)
    float m_kakuseiRate;
    bool m_kakusei;
    bool m_kakuseiOther;
    // RegisterRescueUI's object, -1 when none; UpdateRescueUI opens the action window over it
    // (the names are not the original's)
    gf::GF_OBJ_HANDLE* m_rescueObj;
    bool m_rescueOpen;
    gf::GF_OBJ_HANDLE* pad_30;
    gf::GF_OBJ_HANDLE* pad_38;  // NotifyRecordUpdate sets it
    unsigned char pad_40;
    unsigned char pad_41;
    mm::mtl::FixedVector<TutorialInfo, 36> m_tutorials;  // RegisterTutorial queues (the name is not the original's)
    float pad_e0;
    unsigned int m_elementComboSerial;  // StartElementalComboDirectionUI's ids, from 1 (the name is not the original's)
    unsigned int pad_e8;
    float pad_ec;
    unsigned char pad_f0;  // Create sets it to 3
    // flags from 0xF1, one 16-bit storage unit
    bool pad_bit8 : 1;
    bool pad_bit9 : 1;
    bool pad_bit10 : 1;
    bool pad_bit11 : 1;  // NotifyInput(3) sets it
    bool pad_bit12 : 1;  // NotifyInput(4) sets it
    bool pad_bit13 : 1;  // NotifyInput(5) sets it
    bool pad_bit14 : 1;  // NotifyInput(6) sets it
    // GfGameTarget's changeMode, selectRight/selectLeft and startNearTarget test it (the name is not the original's)
    bool pad_bit15 : 1;
    bool pad_bit16 : 1;
    bool pad_bit17 : 1;  // RegisterTutorial sets it for a forced tutorial
    bool pad_bit18 : 1;  // RegisterTutorial sets it
    bool pad_bit19 : 1;  // NotifyMapChange clears it
    bool pad_bit20 : 1;
};
}  // namespace btl

#endif
