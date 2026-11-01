#ifndef ML_DRPIXLSHADOWCACHEMAN_H
#define ML_DRPIXLSHADOWCACHEMAN_H

#include "grlib/CGLibRenderTarget.h"
#include "classes/ml/DrCalcClipWorkPlane.h"

namespace mm { class Vec3; }
namespace grlib { class CGLibDblUniformBlock; }

namespace ml {
class DrPixlMan;

// one cached shadow map: SHCACHE_WORK_TBL's constructor builds them 0x9D0 apart (depth target at 0, clip plane at
// 0x900). Only what DrPixlMan.cpp's recovered functions use is recovered (the field names are not the original's).
class DrPixlShadowCacheObj {
public:
    bool clipTest(mm::Vec3 const& pos, float radius);

    grlib::CGLibDepthTarget m_depth;  // 0x0
    unsigned char pad_800[0xE8];
    unsigned long m_cacheBit;  // 0x8E8: this cache's bit in a seam's done mask (the name is not the original's)
    unsigned char pad_8F0[0x2];
    short m_cacheIdx;  // 0x8F2: index of this cache's buffer in a seam's buffer list (the name is not the original's)
    unsigned char pad_8F4[0xC];
    DrCalcClipWorkPlane m_clip;  // 0x900
    unsigned char pad_910[0xC0];
};

// DrPixlMan's shadow cache manager (DrPixlMan::m_shadowCacheMan). Only what DrPixlMan.cpp's recovered functions use
// is recovered (the field names are not the original's).
class DrPixlShadowCacheMan {
public:
    // 0x6140 bytes; the manager's constructor builds four from 0x10
    struct SHCACHE_WORK_TBL {
        SHCACHE_WORK_TBL();
        ~SHCACHE_WORK_TBL();

        unsigned char pad_0[0x5940];
        grlib::CGLibDepthTarget m_dirDepth;  // 0x5940: DrPixlMan::setShadowDirRenderTarget selects it
    };

    void addShadowCacheUpdate(bool);
    void delShadowCacheUpdate();
    void callSelectShadowCacheUpdate(unsigned long mask);
    void shadowCacheRender();
    void fastRender();
    void shadowmapRender(int index);
    void debugShadowCacheRender();
    void createCacheBuff();
    void resetColorBuff();
    void buffUpdate();

    // 0x0: 0x40 set by DrPixlMan::pixelEndMode, 0x80 by addShadowCacheUpdate, 0x180 by delShadowCacheUpdate,
    // 0x400 by DrPixlMan::callShadowCacheVariance
    unsigned int m_flags;
    DrPixlMan* m_pixlMan;  // 0x8: the constructor's argument
    SHCACHE_WORK_TBL m_workTbl[4];  // 0x10
    grlib::CGLibDblUniformBlock* m_uniforms;  // 0x18510: one per DrPixlMan::setupShadowUnifrom index
    unsigned char pad_18518[0x294];
    int m_updateCount;  // 0x187AC: addShadowCacheUpdate counts up, delShadowCacheUpdate down to 0
    unsigned long m_selectUpdate;  // 0x187B0: callSelectShadowCacheUpdate clears the bits it is given
};
}  // namespace ml

#endif
