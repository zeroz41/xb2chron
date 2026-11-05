#ifndef CLASSES_ML_DEVGRAPHNX_H
#define CLASSES_ML_DEVGRAPHNX_H

#include "classes/ml/DevGraph.h"
#include "ml/font/FontSys.h"

namespace ml { enum FONT_STYLE : int; }
namespace ml { class FileHandleTh; }
namespace ml { class FileReadResult; }
namespace nn { namespace fs { struct FileHandle; } }
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
    // named by the symbols: keeps the name of the font file initGL loads (a FixStr<64> file static of the unit)
    static void entrySasakiFont(const char* name);

    unsigned char pad_370[0x8];
    FontSys m_font;  // 0x378 (the destructor destroys it; the name is not the original's)
    void* m_fontData;  // 0x6D0 freed after m_font is destroyed by wkStandbyLogout (the name is not the original's)
};
// nn::fs's allocator hooks (0x71006AEF64 allocateFile, 0x71006AEFB0 deallocateFile)
namespace device_detail {
// the memory allocateFile takes from (DeviceNx::initializeSDK creates it: "sdkFileMem")
extern mtl::ALLOC_HANDLE hMemFile;
void* allocateFile(unsigned long size);
void deallocateFile(void* ptr, unsigned long size);
}  // namespace device_detail
// zlib's allocator hooks
class DevFileUtilNx {
public:
    // items * size bytes of the temporary memory; clears the first size bytes (the parameter names are not the
    // original's)
    static void* zlibAlloc(void* opaque, unsigned int items, unsigned int size);
    static void zlibFree(void* opaque, void* ptr);
    // named by the symbols: one read of a channel's file for a request (DevFileNxTh::thUpdate and
    // DevFileArchiveNx::thUpdate); whether it succeeded. The parameters' meanings are inferred
    static bool readFile(FileHandleTh*& handle, nn::fs::FileHandle& file, int, long offset, void* buffer,
                         unsigned int size, FileReadResult& result);
};
}  // namespace ml

#endif
