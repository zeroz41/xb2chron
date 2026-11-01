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
class WinView;
class WinSplitFrame {
public:
    void apply();
    // the first and the second view's part of the view (getScissorRect1: from the corner to the split; 2: past the
    // split and the frame's width)
    mm::Rect<int> getScissorRect1() const;
    mm::Rect<int> getScissorRect2() const;
    WinView* m_view;     // 0x00 the view split (the name is not the original's)
    bool m_vertical;     // 0x08 set: split at m_pos.y, else at m_pos.x (the name is not the original's)
    mm::Pnt<int> m_pos;  // 0x0C where the split lies (the name is not the original's)
    // 0x14 the work ids of the split's two views; -1 for none (WinView::isSplit: both name views held by the views'
    // root; the name is not the original's)
    unsigned int m_viewWid[2];
    unsigned char pad_1c[0x4];
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
        // 0x08 the size WinSplitFrame splits (apply from the calculation bank, getScissorRect1/2 from the render bank)
        mm::Pnt<int> m_viewSize;
        unsigned char pad_10[0x8];
        // 0x18 the view's offsets: getClientSize takes [0] and [2] from the width, [1] and [3] from the height;
        // applyRect stores getViewOfs's w, x, h, y into [0], [1], [2], [3]
        int m_viewOfs[4];
        WinSplitFrame m_splitFrame;  // 0x28 applyRect applies it
        unsigned char pad_48[0x38];
        int m_focusState;  // 0x80 the constructor and evtFocusOff set 8
        unsigned char pad_84[0x24];
        // 0xA8 the frame's width between split views (WinSplitFrame::apply and getScissorRect2 skip it; the name is
        // not the original's)
        unsigned short m_frameWidth;
        unsigned char pad_aa[0x6];
    };
    static void setInitialBackCol(const mm::Col4& col);
    void updateViewPort(const mm::Rect<int>& rect);
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
    void renderView();

    threadval<RENDER_INFO> m_renderInfo;  // 0x1B8 (the name is not the original's)
    reslist<unsigned int> m_renderWorks;  // 0x338 wkTail sends event 0 only once it is empty (the name is not the original's)
    reslist<IWorkEvent*> m_workEvents;    // 0x378 (the name is not the original's)
    // 0x3B8 one word of flags (setFullScreen reads and sets bit 0 as a word; ProcDesktop::wkStandbyLogin sets 0x100)
    unsigned int m_fullScreen : 1;  // getClientSize returns the root's size while it is set (the name is not the original's)
    unsigned int : 6;
    // bit 7: wkStandbyLogout detaches the render works and logs out even while some remain (the name is not the
    // original's)
    unsigned int m_forceLogout : 1;
    unsigned int : 24;
    unsigned char pad_3bc[0x4];
    MsgParam<10> m_msg;  // 0x3C0 (the name is not the original's)
    unsigned char pad_4c8[0x4C];
    // 0x514 the constructor copies setInitialBackCol's colour into it; tl::TitleApplet::initialize sets it black
    // (the name is not the original's)
    mm::Col4 m_backCol;
    unsigned char pad_524[0x18];
    // 0x53C WinSplitFrame::apply copies the calculation bank into the render bank after updateViewPort while it is
    // set (the name is not the original's)
    bool m_copyRender;
    unsigned char pad_53d[0x3];
    CriticalSection m_cs;      // 0x540 getViewOfs holds it (the name is not the original's)
    CriticalSection m_cs2;     // 0x568 (the name is not the original's)
};
}  // namespace ml

#endif
