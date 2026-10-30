#ifndef CLASSES_ML_DEVGRAPHNX_H
#define CLASSES_ML_DEVGRAPHNX_H

#include "classes/ml/DevGraph.h"
#include "ml/font/FontSys.h"

namespace ml { enum FONT_STYLE : int; }
namespace mm { class Col4; }
namespace mm { class Mat44; }
namespace mm { template <typename> class Rect; }

namespace ml {
// table 0x7100B764C0
class DevGraphNx : public ::ml::DevGraph {
public:
    // inline: its copies sit with the class's weak slots (wkUpdate is the key function)
    virtual ~DevGraphNx() {}  // slot 0
    virtual void wkUpdate();  // slot 9
    virtual void wkRender();  // slot 10
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
    virtual void grSetViewportSys(mm::Rect<int> const&, int);  // slot 18
    virtual void grSetScissorSys(mm::Rect<int> const&);  // slot 19
    virtual void getPersSys(mm::Mat44&, float, float, float);  // slot 21
    virtual void getOrthoSys(mm::Mat44&);  // slot 22
    virtual int getRootWidthSys();  // slot 23
    virtual int getRootHeightSys();  // slot 24
    virtual float getScreenScaleWSys() { return 1.0f; }  // slot 25
    virtual float getVSyncSecSys() const { return 1.0f / 60.0f; }  // slot 26
    virtual void renderBeginSys();  // slot 27
    virtual void renderEndSys();  // slot 28
    virtual void renderSyncSys();  // slot 29
    virtual void resetSizeSys(short, short);  // slot 30
    virtual void fontDrawSys(short, short, float, float, char const*, mm::Col4 const*, bool);  // slot 31
    virtual unsigned int fontGetWidthSys(char const*, ml::FONT_STYLE, float);  // slot 32
    virtual unsigned int fontGetHeightSys(ml::FONT_STYLE, float);  // slot 33
    virtual float getCostSys() const;  // slot 34

    // the render thread's callbacks (their returns: nonzero when done)
    static unsigned int thInitialize(void*, void*);
    static unsigned int thDestroy(void*, void*);
    // named by the symbols: the render thread's frame swap
    static int thSync(void*, void*);
    static bool initGL();

    unsigned char pad_350[0x28];
    FontSys m_font;  // 0x378 (the destructor destroys it; the name is not the original's)
    void* m_fontData;  // 0x6D0 freed after m_font is destroyed by wkStandbyLogout (the name is not the original's)
};
// nn::fs's allocator hooks (0x71006AEF64 allocateFile, 0x71006AEFB0 deallocateFile)
namespace device_detail {
void deallocateFile(void* ptr, unsigned long size);
}  // namespace device_detail
// zlib's allocator hooks
class DevFileUtilNx {
public:
    static void zlibFree(void* opaque, void* ptr);
};
}  // namespace ml

#endif
