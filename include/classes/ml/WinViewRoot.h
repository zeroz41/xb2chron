#ifndef CLASSES_ML_WINVIEWROOT_H
#define CLASSES_ML_WINVIEWROOT_H

#include "classes/ml/WorkObj.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace ml { class WinView; }

namespace ml {
// table 0x7100B78918; base at 0x1A8 mm::mtl::PtrSingleton<WinViewRoot> (the constructor stores its table there,
// asserts get()==0 at singleton.h line 82 and stores itself as its instance; the destructors clear it)
class WinViewRoot : public ::ml::WorkObj, public mm::mtl::PtrSingleton<WinViewRoot> {
public:
    // named name under parent (the parameter names are not the original's)
    WinViewRoot(const char* name, WorkObj* parent);
    // the root of the views, entered under parent
    static WinViewRoot* create(WorkObj* parent);
    // 1.0.0 only (3.0.1 dropped it): sets the flag WinViewRoot::renderView reads (the parameter name is not the original's)
    static void cutOff(bool off);
    // forgets proc as the current process (inline: WinProc::wkStandbyLogout; the name is not the original's)
    void invalidProc(const WorkObj* proc) {
        if (m_currentProc == proc || m_currentWork == proc) {
            m_currentWork = nullptr;
            m_currentProc = nullptr;
        }
    }
    // the view the work id wid names, if the root holds it (the parameter name is not the original's)
    static WinView* getView(unsigned int wid);
    // whether view is a child of parent, at any depth (the parameter names are not the original's)
    static bool isCurrentChild(const WinView* parent, const WinView* view);
    // forgets view as the current view (WinView::wkStandbyLogout calls it; the parameter name is not the original's)
    static void invalidCurrent(WinView* view);
    // renders every view under the root, then darkens the screen by the flow pause's rate; nothing while cut off
    // or with no desktop
    static void renderView();
    // the desktop's view, or the first of its child views that is full screen or covers the root, logged in and not
    // stopped
    static WinView* getFullScreenView();
    virtual ~WinViewRoot();  // slot 0
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
    // 0x1B0 the work ids of the views made current, 128 entries (setCurrent adds the view's WorkObj id; the name is
    // not the original's)
    reslist<unsigned int> m_currentList;
    WinView* m_current;       // 0x1F0 setCurrent stores the view, invalidCurrent clears it (the name is not the original's)
    WorkObj* m_currentWork;   // 0x1F8 setCurrent: the work its id names (the name is not the original's)
    WorkObj* m_currentProc;   // 0x200 setCurrent: the process under the desktop that holds it (the name is not the original's)
    unsigned int m_prevWid;   // 0x208 setCurrent: the work id of the view current before; -1 for none (the name is not the original's)
    unsigned char pad_20c[0x4];
};
}  // namespace ml

#endif
