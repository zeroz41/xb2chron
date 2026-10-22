#ifndef CLASSES_ML_WINVIEW_H
#define CLASSES_ML_WINVIEW_H

#include "classes/ml/WorkObj.h"

namespace ml { class IWorkEvent; }
namespace ml { class WorkObj; }
namespace mm { template <typename> class Rect; }

namespace ml {
// a base of ml::WinView no evidence names yet
class TUnk_B788F8 {
public:
    virtual ~TUnk_B788F8();
};
// table 0x7100B78828; base at 0x1A8 unknown (TUnk_B788F8)
class WinView : public ::ml::WorkObj, public TUnk_B788F8 {
public:
    enum RENDER_INFO : int;
    virtual ~WinView();  // slot 0
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
    virtual void evtFocusOn();  // slot 17
    virtual void evtFocusOff();  // slot 18
    virtual void detachRenderWork(ml::WorkObj const*);  // slot 19
    virtual void detachWorkEvent(ml::IWorkEvent const*);  // slot 20
    virtual void destroyCtrlMemory();  // slot 21
    virtual void applyRect();  // slot 22
    virtual void getViewOfs(mm::Rect<int>&, bool);  // slot 23
};
}  // namespace ml

#endif
