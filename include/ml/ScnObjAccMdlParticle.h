#ifndef ML_SCNOBJACCMDLPARTICLE_H
#define ML_SCNOBJACCMDLPARTICLE_H

namespace ml { class ScnObjModel; }
namespace ml { struct MdlVtxParticle; }
namespace ml { class DrResMdoVtxMeshObj; }
namespace ml {
class ScnObjAccMdlParticle {
public:
    explicit ScnObjAccMdlParticle(ScnObjModel* model);
    void setActive(bool active, unsigned int index);
    void setParams(const MdlVtxParticle& params);

    DrResMdoVtxMeshObj* m_vtxMesh;  // the model's (the name is not the original's)
};
}  // namespace ml

#endif
