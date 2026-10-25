#ifndef CLASSES_EVENT_UIMANAGER_H
#define CLASSES_EVENT_UIMANAGER_H

#include "classes/gf/GfMenuObjFade.h"
#include "mm/mtl/FixedVector.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::UIManager no evidence names yet
class TUnk_B3D5C8 {
public:
    virtual ~TUnk_B3D5C8();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::UIManager no evidence names yet
class TUnk_B3D5F0 {
public:
    virtual ~TUnk_B3D5F0();
};
// table 0x7100B3D5C8; base at 0x0 unknown (TUnk_B3D5C8), base at 0x8 unknown (TUnk_B3D5F0)
class UIManager : public TUnk_B3D5C8, public TUnk_B3D5F0 {
public:
    virtual ~UIManager();  // slot 0
    UIManager();  // out of line (Singleton<UIManager>::getPtr calls it)
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
    void update();
    // 1.0.0's UIManager::logout (0x71000F02E8); 3.0.1 inlines it into OnEventProc
    void logout() {
        if (m_flags & 1) {
            gf::GfMenuObjFade::dispLoading(false, 0);
        }
        m_flags = 0;
    }

    unsigned char pad_10[0x4];
    // bit 0: logout() hides the loading display; the name is not the original's
    unsigned int m_flags;  // 0x14
};
}  // namespace event

#endif
