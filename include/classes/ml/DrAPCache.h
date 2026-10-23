#ifndef CLASSES_ML_DRAPCACHE_H
#define CLASSES_ML_DRAPCACHE_H

namespace grlib { class CGLibSampler; class CGLibTextureBuffer; }

namespace ml {
// table 0x7100B7E928
class DrAPCache {
public:
    virtual ~DrAPCache() {}  // slot 0

    void endZRender();
    void endThicknessRenderFirst();
    void endThicknessRenderSecond();
    void endMdlZRender();
    void endGBuffRender();
    void setRefractionRender();
    void endRefractionRender();
    void setTexture(const grlib::CGLibTextureBuffer& texture, const grlib::CGLibSampler& sampler, unsigned int location);
};
}  // namespace ml

#endif
