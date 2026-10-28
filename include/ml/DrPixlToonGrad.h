#ifndef ML_DRPIXLTOONGRAD_H
#define ML_DRPIXLTOONGRAD_H

namespace grlib { class CGLibTextureBuffer; }

namespace ml {
// DrPixlPostMan::m_toonGrad. Only what DrPixlPostMan calls is declared.
class DrPixlToonGrad {
public:
    grlib::CGLibTextureBuffer* getGradTex() const;
    grlib::CGLibTextureBuffer* getDarkGradTex() const;
    void render();
};
}  // namespace ml

#endif
