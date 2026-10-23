#ifndef CLASSES_ML_PROCDESKTOP_H
#define CLASSES_ML_PROCDESKTOP_H

#include "classes/ml/WinProc.h"

namespace ml {
// a base of ml::ProcDesktop no evidence names yet
class TUnk_B78698 {
public:
    virtual ~TUnk_B78698();
};
// table 0x7100B78600; base at 0x0 ml::WinProc (tl::TitleApp::execute calls WinProc::pssGetApplicationView on the desktop), base at 0x1F0 unknown (TUnk_B78698)
class ProcDesktop : public ::ml::WinProc, public TUnk_B78698 {
public:
    // the desktop's own view (WinView.cpp)
    static WinView* getView();
    virtual ~ProcDesktop();  // slot 0
    virtual void OnPauseTrigger(bool, char const*);  // slot 5
    virtual void wkStandby();  // slot 8
    virtual void wkRender();  // slot 10
    virtual void wkRenderAfter();  // slot 11
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
};
}  // namespace ml

#endif
