#ifndef ML_DRPIXLSHADOWCACHEMAN_H
#define ML_DRPIXLSHADOWCACHEMAN_H

#include "grlib/CGLibRenderTarget.h"
#include "grlib/CGLibUniformArray.h"
#include "classes/ml/DrCalcClipWorkPlane.h"
#include "classes/ml/DrCalcClipWorkShadowPlane.h"
#include "mm/Vec3.h"

namespace mm { class Vec3; }

namespace ml {
class DrPixlMan;

// one cached shadow map: SHCACHE_WORK_TBL's constructor builds them 0x9D0 apart (depth target at 0, clip plane at
// 0x900). Only what DrPixlMan.cpp's recovered functions use is recovered (the field names are not the original's).
class DrPixlShadowCacheObj {
public:
    // inlined into SHCACHE_WORK_TBL's destructor: releases the depth target before the members are destroyed
    ~DrPixlShadowCacheObj() { m_depth.release(); }
    bool clipTest(mm::Vec3 const& pos, float radius);

    grlib::CGLibDepthTarget m_depth;  // 0x0
    unsigned char pad_800[0x8];
    // 0x808: DrMdoCtlPos::shadowCacheRender renders with m_mdlFlags 0x80 while bit 4 is set and does not mark the
    // cache done while bit 3 is set (the name is not the original's)
    unsigned char m_flags;
    unsigned char pad_809[0xDF];
    unsigned long m_cacheBit;  // 0x8E8: this cache's bit in a seam's done mask (the name is not the original's)
    // 0x8F0: index of DrPixlShadowCacheMan::SHADOW_CHECK_RANGE_TBL (the name is not the original's)
    short m_level;
    short m_cacheIdx;  // 0x8F2: index of this cache's buffer in a seam's buffer list (the name is not the original's)
    unsigned char pad_8F4[0xC];
    DrCalcClipWorkPlane m_clip;  // 0x900
};

// DrPixlMan's shadow cache manager (DrPixlMan::m_shadowCacheMan). Only what DrPixlMan.cpp's recovered functions use
// is recovered (the field names are not the original's).
class DrPixlShadowCacheMan {
public:
    // 0x6140 bytes; the manager's constructor builds four from 0x10
    struct SHCACHE_WORK_TBL {
        SHCACHE_WORK_TBL();
        ~SHCACHE_WORK_TBL();

        DrPixlShadowCacheObj m_cacheObj[9];  // 0x0: debugShadowCacheRender draws the first m_cacheNum
        // 0x5850: the manager's constructor sets these per table (20/120/1000/256, 0x400 for three tables and 0x100
        // for the fourth, ...); resetColorBuff sizes m_dirDepth m_size x m_size (the names are not the original's)
        float m_range;
        int m_size;     // 0x5854
        float m_near;   // 0x5858
        float m_far;    // 0x585C
        float m_ofs;    // 0x5860
        unsigned char pad_5864[0xDC];
        grlib::CGLibDepthTarget m_dirDepth;  // 0x5940: DrPixlMan::setShadowDirRenderTarget selects it
    };

    DrPixlShadowCacheMan(DrPixlMan* pixlMan);

    void addShadowCacheUpdate(bool);
    void delShadowCacheUpdate();
    void callSelectShadowCacheUpdate(unsigned long mask);
    ~DrPixlShadowCacheMan();
    void shadowCacheRender();
    void fastRender();
    void shadowmapRender(int index);
    void debugShadowCacheRender();
    void createCacheBuff();
    void resetColorBuff();
    void buffUpdate();
    // by DrPixlShadowCacheObj::m_level: 0, 2, 15, 5 (DrMdoCtlPos::shadowCacheRender keeps it as its range)
    static const float SHADOW_CHECK_RANGE_TBL[4];

    // DrResMdoPosInstAnm::update tests the 0x800/0x1000/0x2000 bits it returns
    unsigned int clipDirShadowChk(const mm::Vec3& pos, float radius, bool skipView);

    // 0x0: 0x40 set by DrPixlMan::pixelEndMode, 0x80 by addShadowCacheUpdate, 0x180 by delShadowCacheUpdate,
    // 0x400 by DrPixlMan::callShadowCacheVariance
    unsigned int m_flags;
    DrPixlMan* m_pixlMan;  // 0x8: the constructor's argument
    SHCACHE_WORK_TBL m_workTbl[4];  // 0x10
    // 0x18510: one block per DrPixlMan::setupShadowUnifrom index
    grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock> m_uniforms;
    unsigned char pad_18538[0x8];
    // 0x18540: the constructor builds four 0x90 apart; clipDirShadowChk tests the first three, giving
    // 0x800 << i (the name is not the original's)
    DrCalcClipWorkShadowPlane m_dirClip[4];
    float m_dirRange[3];  // 0x18780: the constructor sets 10000 (the name is not the original's)
    unsigned char pad_1878C[0x4];
    // 0x18790: clipDirShadowChk's clipLineTest direction; the constructor normalizes (1, -2, 1) (the name is not the
    // original's)
    mm::Vec3 m_lightDir;
    // 0x187A0: debugShadowCacheRender lays the caches out m_cacheCols to a row (3) and draws m_cacheNum (9) of each
    // table's m_cacheObj (the names are not the original's)
    int m_cacheCols;
    int m_cacheNum;     // 0x187A4
    int m_renderIdx;    // 0x187A8: shadowmapRender's argument (the name is not the original's)
    int m_updateCount;  // 0x187AC: addShadowCacheUpdate counts up, delShadowCacheUpdate down to 0
    unsigned long m_selectUpdate;  // 0x187B0: callSelectShadowCacheUpdate clears the bits it is given
    unsigned long pad_187B8;       // 0x187B8: zeroed by the constructor
    unsigned short pad_187C0;      // 0x187C0: zeroed by the constructor
};
}  // namespace ml

#endif
