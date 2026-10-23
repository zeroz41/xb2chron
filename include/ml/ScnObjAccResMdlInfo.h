#ifndef ML_SCNOBJACCRESMDLINFO_H
#define ML_SCNOBJACCRESMDLINFO_H

namespace ml { class ScnObjModel; }

namespace ml {
// access to a model's resource information (fw::ModelObject::isRender asks it whether the GPU draws the model)
class ScnObjAccResMdlInfo {
public:
    ScnObjAccResMdlInfo(ScnObjModel* model);
    int isGpuRender() const;  // nonzero when the GPU draws it (isRender tests it so)
    void* m_drMdl;  // the constructor's model's draw object (1.0.0's setDrMdl; the type is not in the symbols)
};
}  // namespace ml

#endif
