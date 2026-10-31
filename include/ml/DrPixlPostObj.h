#ifndef ML_DRPIXLPOSTOBJ_H
#define ML_DRPIXLPOSTOBJ_H

namespace ml { class DrMan; class DrPixlMan; class DrPixlPostMan; class DrPixlRenderTarget; }

namespace ml {
// the post-process objects' base: the constructor keeps its three managers (the field names are not the original's)
class DrPixlPostObj {
public:
    DrPixlPostObj(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan);
    // rounds both sizes up to even (an odd value gains one)
    static void calc1PixlOfs(float& width, float& height);
    static float gaussianDistribution(float x, float y, float rho);
    void setScaleShader(DrPixlRenderTarget* target);
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
