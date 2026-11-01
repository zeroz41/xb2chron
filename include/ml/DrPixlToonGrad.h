#ifndef ML_DRPIXLTOONGRAD_H
#define ML_DRPIXLTOONGRAD_H

namespace grlib { class CGLibTextureBuffer; }
namespace ml { class DrMan; class DrPixlRenderTarget; }

namespace ml {
// DrPixlPostMan::m_toonGrad: the toon gradient render targets, one pair per double buffer index. Field names are
// not the original's.
class DrPixlToonGrad {
public:
    DrPixlToonGrad(DrMan* drMan);
    ~DrPixlToonGrad();
    // references: DrPixlPostMan::getToonGradTex/getToonDarkGradTex make a framed call, not a tail call, which a
    // pointer return would allow (a dereferenceable return attribute blocks it)
    grlib::CGLibTextureBuffer& getGradTex() const;
    grlib::CGLibTextureBuffer& getDarkGradTex() const;
    void render();

    DrMan* m_drMan;                          // 0x00
    bool m_update;                           // 0x08: the constructor sets it
    DrPixlRenderTarget* m_gradTarget[2];     // 0x10: getGradTex returns [DrMan::s_nDblIdx]'s texture
    DrPixlRenderTarget* m_darkGradTarget[2]; // 0x20: getDarkGradTex returns [DrMan::s_nDblIdx]'s texture
};
}  // namespace ml

#endif
