#ifndef CLASSES_ML_WINVIEW_H
#define CLASSES_ML_WINVIEW_H

#include "classes/ml/FontLayer.h"
#include "classes/ml/WorkObj.h"
#include "mm/Col4.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "ml/CriticalSection.h"
#include "classes/ml/MsgParam.h"
#include "classes/ml/reslist.h"
#include "classes/ml/threadval.h"

namespace ml { class IWorkEvent; }
namespace ml { class WorkObj; }

namespace ml {
// a view's split frame, kept in each bank of WinView's RENDER_INFO at 0x28 (WinView::applyRect calls apply on the
// calculation bank's; the constructor clears 0x0 and 0x8 and sets 0x14 and 0x18 to -1). Its size is not proven:
// it is taken up to the colours at RENDER_INFO 0x50.
class WinSplitFrame {
public:
    void apply();
    unsigned char pad_0[0x14];
    // 0x14 the work ids of the split's two views; -1 for none (WinView::isSplit: both name views held by the views'
    // root; the name is not the original's)
    unsigned int m_viewWid[2];
    unsigned char pad_1c[0xC];
};

// table 0x7100B78828; base FontLayer at 0x1A8 (the font commands' flushes print through getView(false) + 0x1A8 as
// FontLayer::font's this)
class WinView : public ::ml::WorkObj, public ::ml::FontLayer {
public:
    static WinView* getView(bool sub);
    // registers a work-event listener with the view (GfAssetManager::initialize registers itself, false)
    void attachWorkEvent(IWorkEvent* event, bool flag);
    // what each bank of m_renderInfo holds (the field names are not the original's)
    struct RENDER_INFO {
        mm::Pnt<int> m_size;      // 0x00 the constructor sets the root's width and height
        unsigned char pad_8[0x10];
        // 0x18 the view's offsets: getClientSize takes [0] and [2] from the width, [1] and [3] from the height;
        // applyRect stores getViewOfs's w, x, h, y into [0], [1], [2], [3]
        int m_viewOfs[4];
        WinSplitFrame m_splitFrame;  // 0x28 applyRect applies it
        unsigned char pad_50[0x30];
        int m_focusState;  // 0x80 the constructor and evtFocusOff set 8
        unsigned char pad_84[0x2C];
    };
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

    // the client size: the root's while m_fullScreen is set, else the size less the view's offsets, from the
    // calculation bank when cpu is set, else the render bank (the parameter name is not the original's)
    mm::Pnt<int> getClientSize(bool cpu) const;
    mm::Rect<int> getClientAbsRect(bool cpu) const;
    mm::Rect<int> getClientScissorRect(bool cpu) const;
    // the client's corner from getClientAbsRect and the size from getClientScissorRect, clipped to the root
    mm::Rect<int> getClientScissorAbsRect(bool cpu) const;
    void updateMsg();
    // whether both of the split frame's views exist, from the calculation bank when cpu is set
    bool isSplit(bool cpu) const;
    void applyPrio();

    threadval<RENDER_INFO> m_renderInfo;  // 0x1B8 (the name is not the original's)
    reslist<unsigned int> m_renderWorks;  // 0x338 wkTail sends event 0 only once it is empty (the name is not the original's)
    reslist<IWorkEvent*> m_workEvents;    // 0x378 (the name is not the original's)
    bool m_fullScreen : 1;  // 0x3B8 getClientSize returns the root's size while it is set (the name is not the original's)
    unsigned char pad_3b9[0x7];
    MsgParam<10> m_msg;  // 0x3C0 (the name is not the original's)
    unsigned char pad_4c8[0x4C];
    // 0x514 the constructor copies setInitialBackCol's colour into it; tl::TitleApplet::initialize sets it black
    // (the name is not the original's)
    mm::Col4 m_backCol;
    unsigned char pad_524[0x1C];
    CriticalSection m_cs;      // 0x540 getViewOfs holds it (the name is not the original's)
    CriticalSection m_cs2;     // 0x568 (the name is not the original's)
};
}  // namespace ml

#endif
