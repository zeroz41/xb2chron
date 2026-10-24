#ifndef ML_SCNOBJACCRESMDLINFO_H
#define ML_SCNOBJACCRESMDLINFO_H

#include "mm/Col3.h"

namespace ml { class ScnObjModel; }
namespace ml { class DrMdlObj; }

namespace ml {
// the arguments of DrMdoCtlNom::createAfterImage, in order (field names are not the original's)
struct DrMdlAfterImageParams {
    float m_params0[3];
    mm::Col3 m_color0;
    float m_params1[3];
    mm::Col3 m_color1;
    float m_params2[3];
};
}  // namespace ml

namespace ml {
// access to a model's resource information (fw::ModelObject::isRender asks it whether the GPU draws the model)
class ScnObjAccResMdlInfo {
public:
    ScnObjAccResMdlInfo(ScnObjModel* model);
    int isGpuRender() const;  // nonzero when the GPU draws it (isRender tests it so)
    void setAlwaysMiddleTexStm(bool on);
    void setGpuClip(bool on);
    void setAlwaysTexStm(bool on);
    void setDblBuffAlpha(bool on);
    void setSpAlphaMode(bool on);
    void setCamCheckMode(bool on);
    bool isCamCheckResl() const;
    void createAfterImage(const DrMdlAfterImageParams& params);
    void releaseAfterImage();

    DrMdlObj* m_drMdl;  // the constructor's model's draw object
};
}  // namespace ml

#endif
