#ifndef CLASSES_ML_PROCDESKTOP_H
#define CLASSES_ML_PROCDESKTOP_H

#include "classes/ml/WinProc.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace ml {
// table 0x7100B78600; base at 0x0 ml::WinProc (tl::TitleApp::execute calls WinProc::pssGetApplicationView on the
// desktop), base at 0x1F0 mm::mtl::PtrSingleton<ProcDesktop> (the constructor stores its table there and asserts
// get()==0 at singleton.h line 82; getView reads the desktop through its instance)
class ProcDesktop : public ::ml::WinProc, public mm::mtl::PtrSingleton<ProcDesktop> {
public:
    struct DESKTOP_ICON_DEF;
    // the desktop's own view (WinView.cpp)
    static WinView* getView();
    static void entryTable(DESKTOP_ICON_DEF* table, bool flag);
    static void autorun(const char* name);
    static void dispInfo(bool disp);
    static bool isDispInfo();
    static void setStartNotify(void (*initialize)(), void (*update)(), void (*finalize)());
    static void setBuildRevision(const char* revision);
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
};
}  // namespace ml

#endif
