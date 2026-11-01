#ifndef ML_DRPIXLPOSTOBJ_H
#define ML_DRPIXLPOSTOBJ_H

namespace grlib { class CGLibUniformEtcUtility; }
namespace ml { class DrMan; class DrPixlMan; class DrPixlPostMan; class DrPixlRenderTarget; class DrShdDataObj; }

namespace ml {
// the post-process objects' base: the constructor keeps its three managers (the field names are not the original's)
class DrPixlPostObj {
public:
    DrPixlPostObj(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan);
    // rounds both sizes up to even (an odd value gains one)
    static void calc1PixlOfs(float& width, float& height);
    static float gaussianDistribution(float x, float y, float rho);
    void setScaleShader(DrPixlRenderTarget* target);
    // binds target's texture at location (linear sampling with filter) and a unit uv scale at ofs
    void setUVScale_UB(grlib::CGLibUniformEtcUtility& uniform, DrShdDataObj* shader, const DrPixlRenderTarget* target,
                       bool filter, unsigned int location, unsigned int ofs);
    // four floats per tap from -radius to radius: the offset, 0 (or swapped) and the normalised weight times scale
    static void getSampleOffsets_GaussBlur_Horizontally(float width, float height, int radius, float* offsets,
                                                        float scale, float rho);
    static void getSampleOffsets_GaussBlur_Verticaly(float width, float height, int radius, float* offsets,
                                                     float scale, float rho);

    DrMan* m_drMan;  // 0x0
    DrPixlMan* m_pixlMan;  // 0x8
    DrPixlPostMan* m_postMan;  // 0x10
};
}  // namespace ml

#endif
