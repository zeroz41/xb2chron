#ifndef CLASSES_ML_DEBDRAW_H
#define CLASSES_ML_DEBDRAW_H

#include "classes/ml/DevGraphCB.h"
#include "mm/Col4.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"
#include "classes/ml/fixed_size_alloc.h"
#include "classes/ml/reslist.h"

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
    // a primitive's 16 bytes in the pool (the layout is unknown)
    struct PRM_DATA {
        unsigned char pad_00[0x10];
    };
    DebDraw();
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
    // the debug draw (the argument is unused)
    static DebDraw* getOnly(unsigned int);
    // the cache's work id; -1 with no debug draw
    static int getCacheDrawWID();
    static void setCurrentPrio(int prio);
    static void flushPrio(int prio, const mm::Mat44& view, const mm::Mat44& proj);

    // the debug draw of a work id (the cache's DebDraw)
    static DebDraw* get(unsigned int wid);

    void setPerspective(const mm::Mat44& view, const mm::Mat44& proj);
    void setMatrix(const mm::Mat44& mtx);
    void setTex(grlib::CGLibTextureBuffer* tex);
    void setCol(const mm::Col4& col);
    // named by the symbols: the same with the colour's parts (the parameter names are not the original's)
    void setCol(float r, float g, float b, float a);
    // named by the symbols: an rgb colour and its alpha (the cache gets the colour opaque; the parameter names are
    // not the original's)
    void setCol(const mm::Col3& col, float a);
    void setDoubleSide(bool doubleSide);
    void setZComp(bool on);
    void setZWrite(bool on);
    void renderRect(const mm::Rect<int>& rect);
    void renderRectFill(const mm::Rect<int>& rect);
    // named by the symbols: the same with the rectangle's parts (the parameter names are not the original's)
    void renderRect(int x, int y, int w, int h);
    void renderRectFill(int x, int y, int w, int h);
    void renderCube(const mm::Vec3& min, const mm::Vec3& max);
    void renderCircle(const mm::Mat44& mtx, float radius, int div);
    void renderAxis(float length);
    void renderArrow(const mm::Vec3& start, const mm::Vec3& end);
    void renderCubeArrow(const mm::Vec3& start, const mm::Vec3& end);
    void renderRealSphere(float radius, int div);
    void renderConeFill(float radius, float height, unsigned int div);
    void renderCone(float radius, float height, unsigned int div);
    void renderCylinder(float radius, float height, unsigned int div);
    void renderCapsule(float radius, float height, unsigned int div);
    void renderSquare(float width, float height);
    void setLineWidth(unsigned int width);
    void setAlphaBlend(bool blend);
    void clrTex();
    void renderLine(const mm::Vec3& start, const mm::Vec3& end);
    void renderLine(const mm::Pnt<int>& start, const mm::Pnt<int>& end);
    void fontColor(const mm::Col4& col);
    void font(int x, int y, const char* text);

    unsigned int m_flags;                 // 0x08 (the name is not the original's)
    mm::Col4 m_col;                       // 0x0C white from the constructor (the name is not the original's)
    float pad_01c;                        // 0x1C 1.0f from the constructor
    int pad_020;                          // 0x20 -1 from the constructor
    int pad_024;
    int pad_028;
    mm::Vec3 m_pos;                       // 0x30 zero from the constructor (the name is not the original's)
    unsigned char pad_040[0x80];
    mm::Mat44 m_mtx;                      // 0xC0 identity from the constructor (the name is not the original's)
    unsigned char pad_100[0x40];
    int pad_140;
    unsigned int m_lineWidth;             // 0x144 setLineWidth's (the name is not the original's)
    int pad_148;
    float pad_14c;                        // 0x14C DebDrawCmd's 2D adds take z from it
    int pad_150;
    bool m_zComp;                         // 0x154 true from the constructor, setZComp's (the name is not the original's)
    bool m_zWrite;                        // 0x155 true from the constructor, setZWrite's (the name is not the original's)
    bool pad_156;                         // DebDrawCmd::fastSetup clears it
    mm::Vec3 pad_160;                     // zero from the constructor
    int pad_170;                          // -1 from the constructor
    void* pad_178;
    grlib::CGLibTextureBuffer* m_tex;     // 0x180 setTex's (the name is not the original's)
    fixed_size_alloc<PRM_DATA> m_prmAlloc;  // 0x188 (the name is not the original's)
    reslist<PRM_DATA*> m_prmList;         // 0x1B8 (the name is not the original's)
    long pad_1f8;                         // -1 from the constructor
    int pad_200;
    void* pad_208;
    CacheDraw* m_cache;                   // 0x210 (the name is not the original's)
    bool m_cacheOnRender;                 // 0x218 isNotRender's (the name is not the original's)
};
}  // namespace ml

#endif
