#ifndef CLASSES_EVENT_SELECTMANAGER_H
#define CLASSES_EVENT_SELECTMANAGER_H

#include "mm/mtl/FixedVector.h"

namespace event { enum MSG_TYPE : int; class CharaObj; }

#include "classes/event/SelectWindow.h"

namespace event {
// what kind of selection evt_sel.play shows (its begin entry's parameter); 1.0.0's mangled names spell the type
// event::SELECT_TYPE, its values are not known
enum SELECT_TYPE {};
}  // namespace event

namespace event {
// a base of event::SelectManager no evidence names yet
class TUnk_B3D748 {
public:
    virtual ~TUnk_B3D748() {}
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::SelectManager no evidence names yet
class TUnk_B3D770 {
public:
    virtual ~TUnk_B3D770() {}
};
// table 0x7100B3D748; base at 0x0 unknown (TUnk_B3D748), base at 0x8 unknown (TUnk_B3D770)
class SelectManager : public TUnk_B3D748, public TUnk_B3D770 {
public:
    // out of line: Singleton<SelectManager>::getPtr registers it with __cxa_atexit (see DofManager.h)
    virtual ~SelectManager();  // slot 0
    SelectManager();  // out of line (Singleton<SelectManager>::getPtr calls it)
    // evt_sel.play: returns false while the script has to wait
    bool play(SELECT_TYPE type, const char* text, mm::mtl::FixedVector<const char*, 16>& items, CharaObj* chara);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    int getResult() const;
    // 1.0.0's SelectManager::clear (0x71000F5EC0) and update (0x71000F5F48); 3.0.1 inlines them into OnEventProc
    void clear() {
        m_window.clear();
        pad_38 = 0;
        m_result = 0;
        pad_10 = 0;
    }
    void update() {
        if (pad_10 & 1) {
            m_window.update();
        }
    }

private:
    long pad_10;  // bit 0: a window is open (1.0.0 update and isActive test it)
    SelectWindow m_window;  // 0x18 (the name is not the original's)
    unsigned int pad_38;
    // what getResult returns; the name is not the original's
    int m_result;  // 0x3c
    unsigned char pad_40[0x8];
};
}  // namespace event

#endif
