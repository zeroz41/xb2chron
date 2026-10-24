#ifndef ML_SCNOBJACCRESSUBMESH_H
#define ML_SCNOBJACCRESSUBMESH_H

namespace ml { class ScnObjModel; }
namespace ml { class DrResMdoMeshObj; }
namespace ml {
class ScnObjAccResSubMesh {
public:
    explicit ScnObjAccResSubMesh(ScnObjModel* model);
    int getExtMax() const;
    int getExtIdx(const char* name) const;
    const char* getExtName(int index) const;
    void setExtAlpha(int index, float alpha);

    // field names are not the original's
    const void* m_subMesh;  // the resource's sub-mesh data
    DrResMdoMeshObj* m_mesh;
};
}  // namespace ml

#endif
