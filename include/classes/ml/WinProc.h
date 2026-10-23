#ifndef CLASSES_ML_WINPROC_H
#define CLASSES_ML_WINPROC_H

#include "classes/ml/WorkObj.h"

namespace ml { class WinView; }

namespace ml {
// table 0x7100B786D8
class WinProc : public ::ml::WorkObj {
public:
    virtual ~WinProc();  // slot 0
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
    // the view an application process draws into, if any (WinView.cpp)
    WinView* pssGetApplicationView();
    unsigned char pad_1A8[0x40];
    unsigned int m_viewWid;  // 0x1E8 tl::TitleApp::execute stores its view's work id (WorkObj 0x50) here (the name is not the original's)
    unsigned char pad_1EC[0x4];
};
}  // namespace ml

#endif
