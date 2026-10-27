#ifndef CLASSES_ML_DEBDRAW_H
#define CLASSES_ML_DEBDRAW_H

#include "classes/ml/DevGraphCB.h"

namespace mm { class Col3; }
namespace mm { class Col4; }
namespace mm { class Mat44; }
namespace mm { class Vec3; }
namespace mm { template <typename> class Pnt; }
namespace mm { template <typename> class Rect; }

namespace grlib { class CGLibTextureBuffer; }

namespace ml { class CacheDraw; }

namespace ml {
// table 0x7100B761D0
class DebDraw : public ::ml::DevGraphCB {
public:
    // swaps the draw buffers once a frame rendered (DevGraph::renderSync calls it after renderSyncSys)
    static void swap();
    enum PRM_DATA : int;
    virtual ~DebDraw();  // slot 0
    virtual void fastSetup() = 0;  // slot 7
    virtual void restoreShader() = 0;  // slot 8
    virtual void begin(unsigned int, unsigned int) = 0;  // slot 9
    virtual void end() = 0;  // slot 10
    virtual void add(mm::Vec3 const&, mm::Vec3 const&) = 0;  // slot 11
    virtual void add(mm::Pnt<int> const&, mm::Pnt<int> const&) = 0;  // slot 12
    virtual void add(int, int, int, int) = 0;  // slot 13
    virtual void add(mm::Vec3 const&) = 0;  // slot 14
    virtual void add(mm::Pnt<int> const&) = 0;  // slot 15
    virtual void add(float, float, float) = 0;  // slot 16
    virtual void add(int, int, int) = 0;  // slot 17
    virtual void add(int, int) = 0;  // slot 18
    virtual void add(mm::Vec3 const&, mm::Col4 const&) = 0;  // slot 19
    virtual void add(mm::Vec3 const&, mm::Col3 const&) = 0;  // slot 20
    virtual void add(int, int, mm::Col4 const&) = 0;  // slot 21
    virtual void add(int, int, mm::Col3 const&) = 0;  // slot 22
    virtual void add(mm::Vec3 const&, mm::Vec3 const&, mm::Col4 const&) = 0;  // slot 23
    virtual void add(mm::Rect<int> const&) = 0;  // slot 24
    virtual void add(mm::Vec3 const&, mm::Vec3 const&, mm::Vec3 const&) = 0;  // slot 25
    virtual void setPerspective(float, float, float, mm::Mat44 const&, mm::Vec3 const*);  // slot 26
    virtual void setOrtho();  // slot 27
    virtual void clear();  // slot 28

    // 1.0.0 has it out of line; 3.0.1 inlines every use (defined inline in ml/CacheDraw.cpp): whether commands go to the cache (a debug draw exists and
    // the caller is not the render thread, or the cache is used there too)
    static bool isNotRender();
    // the command cache the framework's debug drawing (fw::debug) records into
    static CacheDraw* getCacheDraw();

    void setLineWidth(unsigned int width);
    void setAlphaBlend(bool blend);
    void clrTex();
    void renderLine(const mm::Vec3& start, const mm::Vec3& end);
    void renderLine(const mm::Pnt<int>& start, const mm::Pnt<int>& end);
    void fontColor(const mm::Col4& col);
    void font(int x, int y, const char* text);

    unsigned int m_flags;                 // 0x08 (the name is not the original's)
    unsigned char pad_00c[0x138];
    unsigned int m_lineWidth;             // 0x144 setLineWidth's (the name is not the original's)
    unsigned char pad_148[0x38];
    grlib::CGLibTextureBuffer* m_tex;     // 0x180 setTex's (the name is not the original's)
    unsigned char pad_188[0x88];
    CacheDraw* m_cache;                   // 0x210 (the name is not the original's)
    bool m_cacheOnRender;                 // 0x218 isNotRender's (the name is not the original's)
};
}  // namespace ml

#endif
