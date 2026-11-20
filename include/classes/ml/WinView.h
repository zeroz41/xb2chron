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
    // no view and no split views (WinView's constructor builds both banks' frames)
    WinSplitFrame() : m_view(nullptr), m_vertical(false) {
        m_viewWid[0] = 0xFFFFFFFF;
        m_viewWid[1] = 0xFFFFFFFF;
    }
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

// the frame drawn around a view, kept in each bank of WinView's RENDER_INFO at 0x48 (WinViewFrame::renderTitle reads
// its view's render bank and the frame width at 0x60 = RENDER_INFO 0xA8)
class WinViewFrame {
public:
    // grey frame colours, focus state 8 and a frame 4 pixels wide (1.0.0 has it out of line in this file)
    WinViewFrame();
    // names the view framed (1.0.0's name; the WinView constructor passes itself)
    void setInfo(WinView* view);
    void render(WinView* view) const;
    // the client's offset inside the frame: none while the view has no frame or is full screen, else the frame width
    // across and the width (plus twice it and the 22-pixel title bar while the view has one) down (inline: written
    // out in getFrameAbsPos, getClientAbsRect and setFullScreen; the name is not the original's)
    inline mm::Pnt<int> getClientOfs() const;
    WinView* m_view;  // 0x00 the view framed (the name is not the original's)
    // 0x08 (RENDER_INFO 0x50) the frame's colour: 1.0.0's getColorTransparency returns it with its alpha times the
    // view's m_backAlpha; WinView's constructor sets ProcDesktop's default frame colour (the name is not the
    // original's)
    mm::Col4 m_color;
    mm::Col4 pad_18;  // 0x18 the constructor sets (0.8, 0.8, 0.8, 1)
    // 0x28 (RENDER_INFO 0x70) the title bar's colour: WinView's constructor sets the default title bar colour (the
    // name is not the original's)
    mm::Col4 m_titleBarColor;
    int m_focusState;  // 0x38 (RENDER_INFO 0x80) the constructor and evtFocusOff set 8
    unsigned char pad_3c[0x14];
    unsigned char pad_50[0x8];
    mm::Pnt<int> m_pos;  // 0x58 (RENDER_INFO 0xA0) the frame's corner in its parent view (the name is not the original's)
    // 0x60 (RENDER_INFO 0xA8) the frame's width (WinSplitFrame::apply and getScissorRect2 skip it between split views;
    // the name is not the original's)
    short m_frameWidth;
    unsigned char pad_62[0x6];
};

// table 0x7100B78828; base FontLayer at 0x1A8 (the font commands' flushes print through getView(false) + 0x1A8 as
// FontLayer::font's this)
class WinView : public ::ml::WorkObj, public ::ml::FontLayer {
public:
    // named name under parent (WinProc::pssCreateView makes it; the parameter names are not the original's)
    WinView(const char* name, WorkObj* parent);
    static WinView* getView(bool sub);
    // renders the work in the view (WinProc::pssCreateView attaches its process; returns true)
    bool attachRenderWork(const WorkObj* work);
    // registers a work-event listener with the view (GfAssetManager::initialize registers itself, false)
    bool attachWorkEvent(IWorkEvent* event, bool flag);
    // fills the client area with the back colour (its alpha times m_backAlpha) on the render bank, unless skip is set
    // (the parameter name is not the original's)
    void initializeClientScreen(bool skip);
    // what each bank of m_renderInfo holds (the field names are not the original's)
    struct RENDER_INFO {
        // both sizes the root's, no offsets (WinView.cpp)
        RENDER_INFO();
        mm::Pnt<int> m_size;      // 0x00 the constructor sets the root's width and height
        // 0x08 the size WinSplitFrame splits (apply from the calculation bank, getScissorRect1/2 from the render bank)
        mm::Pnt<int> m_viewSize;
        unsigned char pad_10[0x8];
        // 0x18 the view's offsets: getClientSize takes [0] and [2] from the width, [1] and [3] from the height;
        // applyRect stores getViewOfs's w, x, h, y into [0], [1], [2], [3]
        int m_viewOfs[4];
        WinSplitFrame m_splitFrame;  // 0x28 applyRect applies it
        WinViewFrame m_frame;  // 0x48 the frame renderView draws (WinViewFrame::render's this)
    };
    static void setInitialBackCol(const mm::Col4& col);
    void updateViewPort(const mm::Rect<int>& rect);
    virtual ~WinView();  // slot 0
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
    virtual bool evtFocusOn();  // slot 17 (returns true)
    virtual bool evtFocusOff();  // slot 18 (returns true)
    // removes the work from the view's render works and from both views of its split (returns true)
    virtual bool detachRenderWork(ml::WorkObj const* work);  // slot 19
    // removes the listener from the view and from both views of its split (returns true)
    virtual bool detachWorkEvent(ml::IWorkEvent const* event);  // slot 20
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
    void setFullScreen();
    // names the view: its title and its work name (FrameworkLauncher's build thread names it after the process)
    void setTitle(const char* title);
    // the frame's corner from the root: its own frame position plus each parent view's frame position and client
    // offset, from the calculation bank when cpu is set
    mm::Pnt<int> getFrameAbsPos(bool cpu) const;
    // clips rect (absolute) to the view's client area and to each parent view's up to the root
    void normalizeAbsRect(mm::Rect<int>& rect, bool cpu) const;

    threadval<RENDER_INFO> m_renderInfo;  // 0x1B8 (the name is not the original's)
    reslist<unsigned int> m_renderWorks;  // 0x338 wkTail sends event 0 only once it is empty (the name is not the original's)
    reslist<IWorkEvent*> m_workEvents;    // 0x378 (the name is not the original's)
    // 0x3B8 one word of flags (setFullScreen reads and sets bit 0 as a word; ProcDesktop::wkStandbyLogin sets 0x100;
    // the constructor clears the word)
    union {
    unsigned int m_viewFlags;  // the name is not the original's
    struct {
    unsigned int m_fullScreen : 1;  // getClientSize returns the root's size while it is set (the name is not the original's)
    // bit 1: drops the frame like m_fullScreen (WinViewFrame::getClientOfs; the name is not the original's)
    unsigned int m_frameOff : 1;
    // bit 2: WinViewRoot::getFullScreenView takes a view that covers the root as full screen only while it is clear
    // (the name is not the original's)
    unsigned int m_noFullScreen : 1;
    // bit 3: wkStandbyLogin queues no message 7 while it or bit 9 is set (the name is not the original's)
    unsigned int m_noLoginMsg : 1;
    unsigned int : 3;
    // bit 7: wkStandbyLogout detaches the render works and logs out even while some remain (the name is not the
    // original's)
    unsigned int m_forceLogout : 1;
    unsigned int : 1;
    // bit 9: as bit 3 (the name is not the original's)
    unsigned int m_noLoginMsg2 : 1;
    unsigned int : 22;
    };
    };
    // 0x3BC the frame's style, a word of its own (the constructor clears it; the names are not the original's)
    union {
    unsigned int m_frameStyle;
    struct {
    unsigned int m_framed : 1;    // bit 0: the view has a frame (WinViewFrame::getClientOfs)
    unsigned int m_titleBar : 1;  // bit 1: the frame has a title bar (WinViewFrame::getClientOfs)
    unsigned int : 30;
    };
    };
    MsgParam<10> m_msg;  // 0x3C0 (the name is not the original's)
    // 0x4C8 the m_msg index pushed last (attachWorkEvent sets the argument of that message; as WorkObj's m_lastEvent;
    // the name is not the original's)
    unsigned int m_lastMsg;
    unsigned char pad_4cc[0x4];
    // 0x4D0 setTitle assigns it with WorkObj's m_name (the name is not the original's)
    mm::mtl::FixStr<64> m_title;
    // 0x514 the constructor copies setInitialBackCol's colour into it; tl::TitleApplet::initialize sets it black
    // (the name is not the original's)
    mm::Col4 m_backCol;
    // 0x524 initializeClientScreen multiplies the back colour's alpha by it (the name is not the original's)
    float m_backAlpha;
    // 0x528 WinViewRoot::invalidCurrent makes the current view the listed one with the lowest value, up to the one
    // current before (the name is not the original's)
    int m_currentPrio;
    // 0x52C the frame's corner and the view's size setFullScreen keeps while the view is full screen and restores
    // after it (the name is not the original's)
    mm::Rect<int> m_windowRect;
    // 0x53C WinSplitFrame::apply copies the calculation bank into the render bank after updateViewPort while it is
    // set (the name is not the original's)
    bool m_copyRender;
    unsigned char pad_53d[0x3];
    CriticalSection m_cs;      // 0x540 getViewOfs holds it (the name is not the original's)
    CriticalSection m_cs2;     // 0x568 (the name is not the original's)
};
inline mm::Pnt<int> WinViewFrame::getClientOfs() const {
    if (!m_view->m_framed || m_view->m_fullScreen || m_view->m_frameOff) {
        return mm::Pnt<int>(0, 0);
    }
    int width = m_frameWidth;
    int height = width;
    if (m_view->m_titleBar) {
        height = width * 2 + 22;
    }
    return mm::Pnt<int>(width, height);
}
}  // namespace ml

#endif
