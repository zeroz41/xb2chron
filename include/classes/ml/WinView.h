#ifndef CLASSES_ML_WINVIEW_H
#define CLASSES_ML_WINVIEW_H

#include "classes/ml/FontLayer.h"
#include "classes/ml/WorkObj.h"
#include "mm/Col4.h"

namespace ml { class IWorkEvent; }
namespace ml { class WorkObj; }
namespace mm { template <typename> class Rect; }

namespace ml {
// table 0x7100B78828; base FontLayer at 0x1A8 (the font commands' flushes print through getView(false) + 0x1A8 as
// FontLayer::font's this)
class WinView : public ::ml::WorkObj, public ::ml::FontLayer {
public:
    static WinView* getView(bool sub);
    enum RENDER_INFO : int;
    static void setInitialBackCol(const mm::Col4& col);
    virtual ~WinView();  // slot 0
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
    virtual bool evtFocusOn();  // slot 17 (returns true)
    virtual bool evtFocusOff();  // slot 18 (returns true)
    virtual void detachRenderWork(ml::WorkObj const*);  // slot 19
    virtual void detachWorkEvent(ml::IWorkEvent const*);  // slot 20
    virtual void destroyCtrlMemory();  // slot 21
    virtual void applyRect();  // slot 22
    virtual void getViewOfs(mm::Rect<int>&, bool);  // slot 23

    unsigned char pad_1B8[0x35C];
    // 0x514 the constructor copies setInitialBackCol's colour into it; tl::TitleApplet::initialize sets it black
    // (the name is not the original's)
    mm::Col4 m_backCol;
};
}  // namespace ml

#endif
