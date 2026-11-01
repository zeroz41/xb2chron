#ifndef CLASSES_EVENT_UIMANAGER_H
#define CLASSES_EVENT_UIMANAGER_H

#include "classes/gf/GfMenuObjFade.h"
#include "classes/gf/GfMenuCallContext.h"
#include "mm/mtl/FixedVector.h"
#include "classes/event/AnmF32.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3D5C8; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::UIManager>
class UIManager : public IManager, public mm::mtl::Singleton<UIManager> {
public:
    // the opening telop's positions; the names are not the original's: they follow the script entries
    // (ScriptPlayText's evt_ui openOpeningTelopC/LB/RT/LH/RH pass 0..4)
    enum OPTELOP_TYPE : int {
        OPTELOP_C = 0,
        OPTELOP_LB = 1,
        OPTELOP_RT = 2,
        OPTELOP_LH = 3,
        OPTELOP_RH = 4,
    };

    // inline: D2/D0 and the thunks sit in CharaObj's tail; OnEventProc is the key function
    virtual ~UIManager() {}  // slot 0
    UIManager();  // 0x71001024A0, out of line; Singleton<UIManager>::getPtr inlines it
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void clear();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because the evt_ex plugin's
    // play (ScriptCamMotion) calls it on Singleton<UIManager>::getPtr(). What it does: takes the text, ether value,
    // exp/select/item lists and cancel text evt_ex's set* entries collected, checks MstxtManager's state and opens a
    // selection; returns false while the script must wait (play then calls vmWaitModeSet).
    bool fn_7100104130(const char* text, int ether, const mm::mtl::FixedVector<unsigned int, 16>& exp,
                       const mm::mtl::FixedVector<const char*, 16>& select,
                       const mm::mtl::FixedVector<unsigned int, 16>& item, const char* cancel);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because evt_ex's getResult calls
    // it on Singleton<UIManager>::getPtr(). What it does: returns the int at offset 0x48 (evt_ex.getResult's value).
    int fn_7100104AE8();
    // evt_pay.play: returns false while the script has to wait
    bool openPayoffUI(const char* text, const mm::mtl::FixedVector<unsigned int, 16>& money,
                      const mm::mtl::FixedVector<const char*, 16>& select, const char* cancel);
    // evt_pay.getResult's value (the int at 0x38)
    int getPayoffUI() const;
    void openBladeNameUI();
    bool openChapTelopUI(unsigned int id);
    void openAvanTitleUI(unsigned int id);
    void closeAvanTitleUI(int frame);
    void openZoneTelopUI(unsigned int id);
    void openOpeningTelopUI(OPTELOP_TYPE type, unsigned int id);
    // 0x71001052C4: 1.0.0's closeOpeningTelopUI (0x71000F27A0, called by 1.0.0's evt_ui closeOpeningTelop entries
    // with their type) grown from three to five types
    void closeOpeningTelopUI(OPTELOP_TYPE type);
    void startStaffrollUI(float speed, int type);
    void endStaffroll();
    bool openHomuraHikariUI();
    bool openMinigame();
    // returns false while the new game's wait goes on (the frame stays paused)
    bool startNewGameWait();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0 has no openHitonowa entry). A member
    // because ScriptPlayText's evt_ui openHitonowa calls it on Singleton<UIManager>. What it does: opens the
    // "Hitonowa" UI for the given ids (the script entry's 1st, 4th and 5th arguments, those above 0), with the
    // entry's 2nd argument and its 3rd as a bool; returns false while the script has to wait.
    bool fn_7100105B40(const mm::mtl::FixedVector<int, 3>& ids, int param, bool flag);
    void update();
    // 1.0.0's UIManager::logout (0x71000F02E8); 3.0.1 inlines it into OnEventProc
    void logout() {
        if (m_flags & 1) {
            gf::GfMenuObjFade::dispLoading(false, 0);
        }
        m_flags = 0;
    }

    // bit 14: startStaffrollUI opened the staff roll menu; the name is not the original's
    unsigned int m_openFlags;  // 0x10
    // bit 0: logout() hides the loading display; the name is not the original's
    unsigned int m_flags;  // 0x14
    // the constructor zeroes these (0x1c: 1); not known yet
    unsigned int pad_18;
    bool pad_1c;
    unsigned char pad_1d[0x20 - 0x1D];
    unsigned long pad_20;
    unsigned long pad_28;
    unsigned long pad_30;
    // evt_pay.getResult's value (getPayoffUI); the name is not the original's
    int m_payoffResult;  // 0x38
    unsigned char pad_3c[0x40 - 0x3C];
    unsigned long pad_40;  // the constructor zeroes it
    // evt_ex.getResult's value (fn_7100104AE8); the name is not the original's
    int m_exResult;  // 0x48
    unsigned char pad_4c[0x50 - 0x4C];
    unsigned long pad_50;  // the constructor zeroes it
    // the call context openBladeNameUI releases and creates for GfMenuObjBladeCreate::openCreatedBladeName; the
    // name is not the original's
    gf::GfMenuCallContext* m_bladeNameContext;  // 0x58
    unsigned long pad_60;  // the constructor zeroes it
    unsigned int pad_68;  // the constructor zeroes it
    unsigned char pad_6c[0x70 - 0x6C];
    // the call contexts openAvanTitleUI and openZoneTelopUI create; the names are not the original's
    gf::GfMenuCallContext* m_avanTitleContext;  // 0x70
    gf::GfMenuCallContext* m_zoneTelopContext;  // 0x78
    // two curves the constructor builds in place and the destructor tears down; the names are not the original's
    AnmF32 m_anm0;  // 0x80
    AnmF32 m_anm1;  // 0x190
    unsigned long pad_2a0;
    unsigned long pad_2a8;  // Singleton<UIManager>'s instance is 0x2B0 bytes
};
}  // namespace event

#endif
