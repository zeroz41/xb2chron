#ifndef CLASSES_ML_DEVGRAPH_H
#define CLASSES_ML_DEVGRAPH_H

#include "classes/ml/DevBase.h"
#include "classes/ml/reslist.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/Col4.h"
#include "mm/Rect.h"

#include "mtl/AllocHandle.h"

namespace ml { enum RSTAT : int; }
namespace ml { enum FONT_STYLE : int; }
namespace mm { class Mat44; }
namespace ml { class DevGraphQue; }
namespace ml { class DevGraphCB; }

namespace ml {
namespace dg {
// getFrameSyncSec multiplies the frame time by it when it is not 0; setVSync keeps the previous value in s_nVSyncOld
extern int s_nVSync;
extern int s_nVSyncOld;
// isIgnore returns it; DevPad/DevFont log in without their device while it is set
extern bool s_bIgnore;
}  // namespace dg

// table 0x7100B75C48; its base at 0x1B0 is its singleton (the destructor stores PtrSingleton<ml::DevGraph>'s table
// there and clears its instance)
// what DevGraph::cb is told (WorkCpu::beginFrame passes 0; enumerators not recovered)
enum RCB : int;
class DevGraph : public ::ml::DevBase, public ::mm::mtl::PtrSingleton<DevGraph> {
public:
    virtual ~DevGraph();  // slot 0
    // the frame's scratch memory 0x338 points at: taken downward from m_top (the names are not the original's)
    struct WorkBuf {
        unsigned char pad_0[0x30];
        char* m_top;  // 0x30
    };
    // size bytes of the frame's scratch memory, 4-aligned downward (inline: DevFontLayer's queue and its commands;
    // the name is not the original's)
    void* allocWork(unsigned int size) {
        char* p = m_workBuf->m_top - size;
        if (reinterpret_cast<unsigned long>(p) & 3) {
            p -= reinterpret_cast<unsigned long>(p) & 3;
        }
        m_workBuf->m_top = p;
        return p;
    }
    static int getRootWidth();
    static int getRootHeight();
    // the frame time its object reports, 0 when there is none (inline: the symbols have no copy; getFrameSyncSec)
    static float getVSyncSec() {
        DevGraph* dev = get();
        if (dev != nullptr) {
            return dev->getVSyncSecSys();
        }
        return 0.0f;
    }
    static float getFrameSyncSec();
    static void setVSync(int vsync);
    static bool isIgnore();
    static int fontGetWidth(const char* text, FONT_STYLE style, float scale);
    static void grSetClearCol(const mm::Col4& col);
    // named by the symbols: the object's grInitContextSys, then its queue's flushViewport (WinView::renderView)
    static void grInitContext();
    static void* cmdOpenDisplayList(unsigned int size);
    static bool cmdCloseDisplayList();
    static void cmdExecDisplayList();
    static void cb(RCB rcb);
    static void pushRect(const mm::Rect<int>& a, const mm::Rect<int>& b, const mm::Rect<int>& c, bool flag);
    static void popRect();
    static void getPers(mm::Mat44& mtx, float fovy, float nearZ, float farZ);
    static mm::Rect<int>& getViewport();
    static float getScreenScaleW();
    // opens the frame: the display list, CGLibManager, the debug draw, then the device
    static void renderBegin();
    // named by the symbols: closes the frame: the outer renders, the device, CGLibManager, then the display list
    static void renderEnd();
    static void renderSync();
    // sets a render state (DevGraphNx::renderEndSys passes 1)
    static void setRenderState(RSTAT state);
    static float getCost();
    static void setFrameSpd(float spd);
    // a function drawn outside the scenes' rendering, and its removal (ErrViewer::standby hands it fnRender)
    static void addOuterRender(void (*render)());
    static void removeOuterRender(void (*render)());
    // the memory the graphics memory pools come from (gf::GfMemManager::initializeCore hands it the asset memory,
    // finalizeCore takes it back)
    static void setMemPoolMemHandle(mtl::ALLOC_HANDLE handle);
    static void setMemPoolBuffer(void* buffer, unsigned int size);
    static void releaseMemPoolMemHandle(mtl::ALLOC_HANDLE handle);
    static void releaseMemPoolBuffer(void* buffer);
    virtual void wkStandby();  // slot 8
    virtual void wkUpdate();  // slot 9
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
    virtual void cmdAddDisplayListFast(void*, unsigned int, unsigned int) {}  // slot 17
    virtual void grSetViewportSys(mm::Rect<int> const&, int) = 0;  // slot 18
    virtual void grSetScissorSys(mm::Rect<int> const&) = 0;  // slot 19
    virtual void grInitContextSys();  // slot 20
    virtual void getPersSys(mm::Mat44&, float, float, float) = 0;  // slot 21
    virtual void getOrthoSys(mm::Mat44&) = 0;  // slot 22
    virtual int getRootWidthSys() = 0;  // slot 23
    virtual int getRootHeightSys() = 0;  // slot 24
    virtual float getScreenScaleWSys() = 0;  // slot 25
    virtual float getVSyncSecSys() const = 0;  // slot 26
    virtual void renderBeginSys() = 0;  // slot 27
    virtual void renderEndSys() = 0;  // slot 28
    virtual void renderSyncSys() = 0;  // slot 29
    virtual void resetSizeSys(short, short) = 0;  // slot 30
    virtual void fontDrawSys(short, short, float, float, char const*, mm::Col4 const*, bool) = 0;  // slot 31
    // the widths and heights are unsigned (DevGraphNx converts its float with fcvtzu)
    virtual unsigned int fontGetWidthSys(char const*, ml::FONT_STYLE, float) = 0;  // slot 32
    virtual unsigned int fontGetHeightSys(ml::FONT_STYLE, float) = 0;  // slot 33
    virtual float getCostSys() const = 0;  // slot 34
    virtual void cmdExecDisplayListSys() {}  // slot 35
    virtual void cmdAddDisplayListSys(void*, unsigned int, unsigned int) {}  // slot 36
    virtual void cmdSetupDisplayListSys() {}  // slot 37
    virtual void cmdTermDisplayListSys() {}  // slot 38
    virtual void* cmdOpenDisplayListSys(unsigned int, bool, bool) { return nullptr; }  // slot 39
    virtual bool cmdCloseDisplayListSys(bool) { return false; }  // slot 40
    virtual void cmdAddCreatedListSys(void*, unsigned int) {}  // slot 41
    virtual void cmdSuspendDisplayListSys(bool, bool) {}  // slot 42
    virtual void* cmdGetCurrentAdrSys() { return nullptr; }  // slot 43
    virtual unsigned int cmdGetRemainSizeSys() const { return 0; }  // slot 44
    virtual void* cmdAllocSys(unsigned int, unsigned int) { return nullptr; }  // slot 45
    virtual void* cmdAlignSys(unsigned int) { return nullptr; }  // slot 46
    virtual void* cmdAddOfsSys(unsigned int) { return nullptr; }  // slot 47
    virtual bool cmdIsOpenDisplayListSys() const { return false; }  // slot 48

    // the frame callbacks (the destructor clears it; the name is not the original's)
    reslist<DevGraphCB*> m_cbList;  // 0x1B8
    unsigned char pad_1f8[0x10];
    mm::Rect<int> m_viewport;  // 0x208 getViewport returns it (the name is not the original's)
    unsigned char pad_218[0x18];
    int pad_230;          // 0x230 DebDraw::getScreenPos scales x by half of it (a screen width?)
    int pad_234;          // 0x234 DebDraw::getScreenPos scales y by half of it (a screen height?)
    unsigned char pad_238[0xDC];
    RSTAT m_renderState;  // 0x314 setRenderState stores it under its lock (the name is not the original's)
    // grSetClearCol copies the colour in and sets 0x328 to 1 (the names are not the original's)
    mm::Col4 m_clearCol;  // 0x318
    float m_clearDepth;   // 0x328
    unsigned char pad_32c[0x4];
    DevGraphQue* m_que;   // 0x330 pushRect/popRect forward to it (the name is not the original's)
    WorkBuf* m_workBuf;  // 0x338 (the name is not the original's)
    unsigned char pad_340[0x8];
    float m_frameSpd;     // 0x348 setFrameSpd (the name is not the original's)
    unsigned char pad_34c[0x4];
    // up to four render functions addOuterRender keeps in the first free entry and removeOuterRender clears
    // (ErrViewer's fnRender; the name is not the original's)
    void (*m_outerRender[4])();  // 0x350
};
}  // namespace ml

#endif
