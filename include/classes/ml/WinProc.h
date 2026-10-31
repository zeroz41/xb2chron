#ifndef CLASSES_ML_WINPROC_H
#define CLASSES_ML_WINPROC_H

#include "classes/ml/WorkObj.h"

namespace ml { class WinView; }

namespace ml {
// table 0x7100B786D8
class WinProc : public ::ml::WorkObj {
public:
    // named name under parent, with room for childCapacity children (the parameter names are not the original's)
    WinProc(const char* name, WorkObj* parent, short childCapacity);
    virtual ~WinProc();  // slot 0
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
    // the view an application process draws into, if any (WinView.cpp)
    WinView* pssGetApplicationView();
    // the work its view id names, else the views' root (the return type is not in the symbol)
    WorkObj* pssGetParentView();
    // detaches the process's views (wkStandbyLogout calls it first)
    // (returns true in w0)
    bool pssDetachView();
    // detaches the view whose work id is wid (WinView::wkStandbyLogout calls it on each process it renders): false
    // when the list does not hold it (the parameter name is not the original's)
    bool pssDetachView(unsigned int wid);
    // 0x1A8 room for 16 work ids (the constructor creates it; the name is not the original's)
    reslist<unsigned int> m_viewList;
    unsigned int m_viewWid;  // 0x1E8 tl::TitleApp::execute stores its view's work id (WorkObj 0x50) here (the name is not the original's)
    // 0x1EC the constructor sets 2; WinViewRoot::setCurrent keeps the current process while its value is 0 and the
    // new one's is not (the name is not the original's)
    int m_focusMode;
};
}  // namespace ml

#endif
