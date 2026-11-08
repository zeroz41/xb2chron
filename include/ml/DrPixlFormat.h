#ifndef ML_DRPIXLFORMAT_H
#define ML_DRPIXLFORMAT_H

#include "grlib/GrlTypes.h"

namespace ml {
// the surface formats of the pixel manager's render targets; DrPixlMan.cpp defines them from DrAPCache's TEXTYPE
// constants (in its static initializer, in this order)
class DrPixlFormat {
public:
    static GrlSurfaceFormat s_MrtFormat[19];
    static GrlSurfaceFormat s_SeparateCol;
    static GrlSurfaceFormat s_ResponsiveAAMask;
    static GrlSurfaceFormat s_BackFaceDepth;
    static GrlSurfaceFormat s_LgtLinkGIBFadeList;
    static GrlSurfaceFormat s_LgtLinkGIBIndexMask;
    static GrlSurfaceFormat s_DirShadowFormat;
    static GrlSurfaceFormat s_QuaterNormalFormat;
    static GrlSurfaceFormat s_DepthBufferFormat;
    static GrlSurfaceFormat s_BloomFormat;
    static GrlSurfaceFormat s_VolumeFormat;
    static GrlSurfaceFormat s_TMAAFormat;
    static GrlSurfaceFormat s_DofCalcFormat;
    static GrlSurfaceFormat s_DofLastFormat;
    static GrlSurfaceFormat s_DofCalcSampFormat;
    static GrlSurfaceFormat s_DofAutoFormat;
    static GrlSurfaceFormat s_SimilarityFormat;
    static GrlSurfaceFormat s_BlurVelFormat;
    static GrlSurfaceFormat s_BlurOutFormat;
    static GrlSurfaceFormat s_BlurMaskFormat;
    static GrlSurfaceFormat s_SsrFormat;
    static GrlSurfaceFormat s_ToneMapFormat;
    static GrlSurfaceFormat s_SSAOOutFormat;
    static GrlSurfaceFormat s_SSAOWorkFormat;
    static GrlSurfaceFormat s_SSAOHistory;
    static GrlSurfaceFormat s_SSAOMaskFormat;
    static GrlSurfaceFormat s_ShwRayFormat;
    static GrlSurfaceFormat s_ShwRaytraceFormat;
};
}  // namespace ml

#endif
