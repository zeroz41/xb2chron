#ifndef ML_DRAPGXTYPE_H
#define ML_DRAPGXTYPE_H

#include "grlib/GrlTypes.h"

// the parameter names are not the original's
namespace ml {
// Static setters of the drawing state for the renderer's passes (they take no object: no function reads x0 as this).
class DrAPGxType {
public:
    static void endOccQuery();
    static void beginShadow();
    static void endShadow();
    static void beginColorOff();
    static void endColorOff();
    static void setupCullingOff();
    static void setupCullingFront();
    static void setupCullingBack();
    // the depth test and write switches and the compare function (the light debug renders pass 1, 1, 3)
    static void setupDepthContl(unsigned char, unsigned char, int);
    static void setupBlend(int blend);
    static void setupScreenQuads(bool blend);
    static void setupBloomAddMaterial(GrlBlendFunc src, GrlBlendFunc dst);
    static void beginOccQuery();
    static void shadowCacheSetup();
    static void setupAlphaChanel(bool alpha);
    static void setupStencilPrePassReset();
    static void setupStencilTest(unsigned char depthTest, unsigned char depthWrite, int depthCompare,
                                 unsigned char stencilTest, unsigned int ref, unsigned int mask, int stencilCompare,
                                 int fail, int depthFail, int pass);
    static void setupStencilTestWriteMask(unsigned char depthTest, unsigned char depthWrite, int depthCompare,
                                          unsigned char stencilTest, unsigned int ref, unsigned int mask,
                                          unsigned int writeMask, int stencilCompare, int fail, int depthFail,
                                          int pass);
    static void getMainScreenSize(int& width, int& height);
};
}  // namespace ml

#endif
