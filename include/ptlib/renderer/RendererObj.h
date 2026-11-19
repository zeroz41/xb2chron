#ifndef PTLIB_RENDERER_RENDEREROBJ_H
#define PTLIB_RENDERER_RENDEREROBJ_H

#include "grlib/CGLibRenderTarget.h"
#include "grlib/CGLibTexture.h"
#include "ptlib/renderer/ShaderManager.h"
#include "mm/Vec3.h"
#include "mm/Vec3NA.h"
#include <string.h>

namespace ptlib { class DrDrawWorkInfoEF; class FxParam; class StaticAllocObj; }
namespace ptlib { namespace emitter { class EmitterManager; class EmitterObj; class ParticleObj; } }
namespace effect { class IEffectCallBack; }
namespace mm { namespace mtl { template <typename T, unsigned long N> class FixedVector; } }

namespace ptlib { namespace renderer {

// the renderer's own render targets, made in the renderer's block by createAll (the field names are not the
// original's: they follow the sizes and formats createAll gives them)
class BackBuffer {
public:
    // inline in RenderManager::init, like reset
    BackBuffer() : m_pHalfColor(nullptr), m_pTiny(nullptr), m_pHalfDepth(nullptr), m_pTiny2(nullptr), m_isReleased(true) {}
    ~BackBuffer() { release(); }
    // no targets (RenderGrObj's constructor; the name is not the original's)
    void reset() {
        m_pHalfColor = nullptr;
        m_pTiny = nullptr;
        m_pHalfDepth = nullptr;
        m_pTiny2 = nullptr;
        m_isReleased = true;
    }
    // destroys the targets (inline in RenderGrObj::term and the destructor; the name is not the original's)
    void release() {
        if (m_pHalfColor != nullptr) {
            if (m_pHalfDepth != nullptr) {
                m_pHalfDepth->~CGLibRenderTarget();
            }
            if (m_pHalfColor != nullptr) {
                m_pHalfColor->~CGLibRenderTarget();
            }
            if (m_pTiny != nullptr) {
                m_pTiny->~CGLibRenderTarget();
            }
            if (m_pTiny2 != nullptr) {
                m_pTiny2->~CGLibRenderTarget();
            }
            m_pHalfColor = nullptr;
            m_pTiny = nullptr;
            m_pHalfDepth = nullptr;
            m_pTiny2 = nullptr;
            m_isReleased = true;
        }
    }
    void createAll(StaticAllocObj* pAlloc, float width, float height, float width2, float height2,
                   unsigned int offset);
    // gives the half-size targets half of width x height, their pixels from offset in the pool (createAll and
    // RenderGrObj::fxcore_setup_target_update inline it; the name is not the original's)
    void resizeHalf(float width, float height, unsigned int offset) {
        width *= 0.5f;
        height *= 0.5f;
        unsigned int size;
        unsigned int align;
        grlib::CGLibTexture::getDefPixelSize(size, align, width, height, 0, static_cast<GrlSurfaceFormat>(0x3F));
        unsigned int depthOffset = offset + (align - offset % align) % align;
        offset = size + depthOffset;
        m_pHalfDepth->setTextureInfo(width, height, static_cast<GrlSurfaceFormat>(0x3F), true, depthOffset);
        grlib::CGLibTexture::getDefPixelSize(size, align, width, height, 0, static_cast<GrlSurfaceFormat>(5));
        offset += (align - offset % align) % align;
        m_pHalfColor->setTextureInfo(width, height, static_cast<GrlSurfaceFormat>(5), true, offset);
    }

    grlib::CGLibRenderTarget* m_pHalfColor;  // 0x00: half the screen, format 5
    unsigned char pad_8[0x8];
    grlib::CGLibRenderTarget* m_pTiny;       // 0x10: 8x8, format 1
    grlib::CGLibRenderTarget* m_pHalfDepth;  // 0x18: half the screen, format 0x3F
    grlib::CGLibRenderTarget* m_pTiny2;      // 0x20: 8x8, format 0x26
    bool m_isReleased;                        // 0x28
};

// what a tail or strip is drawn with (the field names are not the original's; the size is not known yet)
class DrawTailWork {
public:
    unsigned char pad_0[0x8];
    int m_index;  // 0x8: draw_common_atr_strip scales the second particle's m_sizeRate by it
    unsigned char pad_c[0xC];
    // 0x18: the size the vertex takes: 0 the particle's, 1 none, 2 its x only, 3 (strips) the emitter's m_drawDist
    int m_sizeType;
    bool m_useSizeZ;  // 0x1C: the vertex takes the second particle's m_size.z instead of its m_size.y
};

// one weapon tail vertex (draw_common_atr_wpn_tail fills it; the field names are not the original's: they follow
// the particle fields copied into them)
class WpnTailShdVtxLayout {
public:
    mm::Vec3NA m_pos;           // 0x0
    unsigned int m_drawIndex;   // 0xC: the particle's m_drawIndex
    mm::Vec3NA m_rot;           // 0x10
    float m_drawParam;          // 0x1C
    float m_drawVec[4];         // 0x20
    mm::Vec3NA m_keyVec;        // 0x30
    float m_size2;              // 0x3C: 1 minus the second particle's size y or z
    mm::Vec3NA m_size;          // 0x40
    unsigned char pad_4c[0x4];
    unsigned int m_rgba;        // 0x50
    unsigned int m_rgba2;       // 0x54
    float m_drawSize[2];        // 0x58: by draw type: the size over the screen size, or the two work sizes
};

namespace sort {
// one emitter of RenderGrObj::prioritySort's draw list (the names are not the original's)
struct EmitterSort {
    bool m_sortFirst;            // the emitter's EmitterArg::m_sortType is 0
    unsigned char m_priority;    // m_drawLayer plus m_drawLayerOfs, clamped to 0..255
    float m_depth;               // the emitter's position in view space, z
    bool m_border;               // 0x8: prioritySort clears it
    emitter::EmitterObj* m_pEmitter;  // 0x10
};

// prioritySort's stable_sort order: priority, then the m_sortFirst ones, then depth
struct Compare {
    bool operator()(const EmitterSort& a, const EmitterSort& b) const {
        if (a.m_priority < b.m_priority) {
            return true;
        }
        if (a.m_priority == b.m_priority) {
            if (a.m_sortFirst > b.m_sortFirst) {
                return true;
            }
            if (a.m_sortFirst == b.m_sortFirst && a.m_depth < b.m_depth) {
                return true;
            }
        }
        return false;
    }
};
}  // namespace sort

// the renderer's graphics objects (particle_renderer_obj.cpp)
class RenderGrObj {
public:
    // inline in RenderManager::init, which builds it in place
    RenderGrObj() : pad_40(nullptr), pad_48(0), pad_50(0), pad_60(mm::Vec3::zero), pad_70(nullptr) {
        m_backBuffer.reset();
        pad_260 = 0;
        m_blendState = 0;
        for (int i = 0; i < 12; i++) {
            m_screenParam[i] = 0.0f;
        }
    }
    ~RenderGrObj();
    // RenderManager::init inlines it after setDrInfo (the name is not the original's)
    void init(StaticAllocObj* pAlloc) {
        // zero is read before the first store (the original loads it ahead of pad_40)
        const mm::Vec3 zero = mm::Vec3::zero;
        pad_40 = nullptr;
        pad_48 = 0;
        pad_50 = 0;
        pad_60 = zero;
        pad_70 = nullptr;
        m_pAlloc = pAlloc;
        m_shaderManager.init();
    }
    void term();
    BackBuffer* getBackBuffer();
    void fxcore_setup_target_update(int view);
    void draw(emitter::EmitterManager& manager, FxParam& param, int view, int pass);
    void myGX2SetBlendControl(int mode);
    void drawKizunaLine(int view);
    void drawSortAndNormal(emitter::EmitterManager& manager, int view, FxParam& param, int pass);
    void prioritySort(emitter::EmitterManager& manager, int view, FxParam& param,
                      mm::mtl::FixedVector<sort::EmitterSort, 4000>& list);
    void draw_capture();
    void draw_common_atr_wpn_tail(WpnTailShdVtxLayout* pVtx, mm::Vec3& pos, emitter::ParticleObj* pParticle,
                                  emitter::ParticleObj* pParticle2, float, unsigned int type, DrawTailWork* pWork);
    void draw_common_atr_normal(float* pOut, emitter::ParticleObj* pParticle, float, unsigned int type, float, float);
    void draw_common_atr_strip(float* pOut, emitter::ParticleObj* pParticle, emitter::ParticleObj* pParticle2, float,
                               unsigned int, DrawTailWork* pWork, mm::Vec3 vec0, mm::Vec3 vec1, float, float);
    void draw_common_uconst(float* pOut, emitter::EmitterObj* pEmitter);
    void draw_common_uparam(float* pOut, unsigned int* pFlags, emitter::EmitterObj* pEmitter);
    void setEffectRenderTarget(grlib::CGLibRenderTarget* pTarget, grlib::CGLibDepthBuffer* pDepth,
                               grlib::CGLibRenderTarget* pTarget1, grlib::CGLibRenderTarget* pTarget2);

    BackBuffer m_backBuffer;  // 0x0
    unsigned char pad_30[0x10];
    void* pad_40;              // 0x40: cleared by the constructor and init
    unsigned long pad_48;      // 0x48: cleared by the constructor and init
    unsigned long pad_50;      // 0x50: cleared by the constructor and init
    unsigned char pad_58[0x8];
    mm::Vec3 pad_60;           // 0x60: zero after the constructor and init
    void* pad_70;              // 0x70: cleared by the constructor and init
    unsigned char pad_78[0x8];
    // 0x80: three float4s of screen sizes draw fills: 1/size, 1, ratio; size, 1/size; size, 1/size (the name is not
    // the original's)
    float m_screenParam[12];
    ShaderManager m_shaderManager;  // 0xB0: the effect shaders (the name is not the original's)
    unsigned char pad_250[0x8];
    const DrDrawWorkInfoEF* m_pDrInfo;  // 0x258: RenderManager::setDrInfo writes it
    unsigned long pad_260;     // 0x260: cleared by the constructor
    StaticAllocObj* m_pAlloc;  // 0x268: the block createAll makes the targets in
    int m_blendState;          // 0x270: draw and draw_capture reset it (the name is not the original's)
    unsigned char pad_274[0xC];
};

// one state's frame block in a caster's bind data (SwtPackData::getAddr returns it by value in x8, and getFramePos
// keeps 0x30 bytes for it; the fields past 0x8 are not read here)
class SwtData {
public:
    SwtData(const unsigned int* pData) : m_pData(pData), pad_8(0) {}

    // u32 count, two u32s, then count entries: char name[0x20], u32 key count, key count * {short frame?, x, y, z}
    const unsigned int* m_pData;  // 0x0
    unsigned int pad_8;           // 0x8: cleared by the constructor
    unsigned char pad_c[0x24];
};

// a caster's bind data (effect::IEffectCallBack::getBindData): u32 state count, count * char[0x80] state names,
// then count u32 offsets of each state's SwtData block
class SwtPackData {
public:
    // m_size is stored before m_num is read (the original stores in that order)
    SwtPackData(const unsigned int* pData, unsigned int size) : m_pData(pData), m_size(size) { m_num = *pData; }

    // the key count of the entry named pArrayName[type * 2] (inline in getAddr; the static's symbol names it)
    static unsigned int calcFrameSize(const unsigned int* pData, short type) {
        static const char* pArrayName[] = {
            "locusPoint_armR_00",  "locusPoint_armR_01",  "locusPoint_armL_00",  "locusPoint_armL_01",
            "locusPoint_footR_01", "locusPoint_footR_00", "locusPoint_footL_01", "locusPoint_footL_00",
        };
        unsigned int num = pData[0];
        const unsigned int* p = pData + 3;
        for (unsigned int i = 0; i < num; i++) {
            if (strstr(reinterpret_cast<const char*>(p), pArrayName[type * 2]) != nullptr) {
                return p[8];
            }
            p = p + p[8] * 2 + 9;
        }
        return 0;
    }
    SwtData getAddr(float& frame, unsigned int index, short type);

    const unsigned int* m_pData;  // 0x0
    unsigned int m_num;           // 0x8
    unsigned int m_size;          // 0xC
};

bool calcFrame(const SwtData& data, float frame, mm::Vec3& pos0, mm::Vec3& pos1, short type);
bool getFramePos(mm::Vec3& pos0, mm::Vec3& pos1, float frame, effect::IEffectCallBack* pCallBack, short type);

}}  // namespace ptlib::renderer

#endif
