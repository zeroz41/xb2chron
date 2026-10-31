#ifndef CLASSES_ML_PROCDESKTOP_H
#define CLASSES_ML_PROCDESKTOP_H

#include "classes/ml/WinProc.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mtl/MemManager.h"

namespace ml { class DesktopIcon; }

namespace ml {
// table 0x7100B78600; base at 0x0 ml::WinProc (tl::TitleApp::execute calls WinProc::pssGetApplicationView on the
// desktop), base at 0x1F0 mm::mtl::PtrSingleton<ProcDesktop> (the constructor stores its table there and asserts
// get()==0 at singleton.h line 82; getView reads the desktop through its instance)
class ProcDesktop : public ::ml::WinProc, public mm::mtl::PtrSingleton<ProcDesktop> {
public:
    struct DESKTOP_ICON_DEF;
    // the desktop's icons, in a buffer of room from a handle (the constructor allocates room for 64; wkStandbyLogin
    // appends what DesktopIcon::create returns; the destructor inlines release). No symbol names the type: the
    // type's and its members' names are not the original's.
    struct IconArray {
        IconArray() : m_items(nullptr), m_count(0), m_capacity(0) {}
        ~IconArray() { release(); }
        void clear() { m_count = 0; }
        void release() {
            clear();
            if (m_mem.m_handle != 0 && m_items != nullptr) {
                mtl::MemManager::deallocate(m_items, 0, false);
                m_items = nullptr;
            }
            m_items = nullptr;
            m_capacity = 0;
            m_mem.m_handle = 0;
        }
        DesktopIcon** m_items;    // 0x00
        unsigned int m_count;     // 0x08
        unsigned int m_capacity;  // 0x0C
        mtl::ALLOC_HANDLE m_mem;  // 0x10
    };
    // named name under parent (WinProcRoot::wkStandbyLogin makes it; the parameter names are not the original's)
    ProcDesktop(const char* name, WorkObj* parent);
    // the desktop's own view (WinView.cpp)
    static WinView* getView();
    static void entryTable(DESKTOP_ICON_DEF* table, bool flag);
    static void autorun(const char* name);
    static void dispInfo(bool disp);
    static bool isDispInfo();
    static void setStartNotify(void (*initialize)(), void (*update)(), void (*finalize)());
    static void setBuildRevision(const char* revision);
    // runs the icon whose name _dsk::s_selectAppName holds (apps::LauncherApp's destructor calls it once a closing
    // FrameworkLauncher handed it an applet)
    static void executeSelectApp();
    virtual ~ProcDesktop();  // slot 0
    virtual void OnPauseTrigger(bool, char const*);  // slot 5
    virtual void wkStandby();  // slot 8
    virtual void wkRender();  // slot 10
    virtual void wkRenderAfter();  // slot 11
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
    unsigned char pad_1F8[0x10];
    WinView* m_view;  // 0x208 getView returns it; the constructor clears it (the name is not the original's)
    IconArray m_icons;  // 0x210 (the name is not the original's)
    // (the object is 0x278 bytes: WinProcRoot::wkStandbyLogin allocates it so)
    unsigned char pad_228[0x34];
    // 0x25C the frame speed OnPauseTrigger last handed DevGraph::setFrameSpd (0 while paused); a trigger moves the
    // trigger's own value here and clears it (the name is not the original's)
    float m_frameSpd;
    float m_lastFrameSpd;  // 0x260 OnPauseTrigger stores the value it moves (the name is not the original's)
    unsigned char pad_264[0x14];
};
}  // namespace ml

#endif
