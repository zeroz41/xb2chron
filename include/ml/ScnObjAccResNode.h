#ifndef ML_SCNOBJACCRESNODE_H
#define ML_SCNOBJACCRESNODE_H

namespace ml { class ScnObjModel; }
namespace ml { class DrMdlObj; }
namespace mm { class Mat44; }
#include "mm/Mat44.h"
namespace ml {
class ScnObjAccResNode {
public:
    ScnObjAccResNode();
    explicit ScnObjAccResNode(ScnObjModel* model);
    void setDrMdl(DrMdlObj* mdl);
    int getBoneMax() const;
    int getBoneIndex(const char* name) const;
    const char* getBoneName(int index) const;
    void setBoneMat(int index, const mm::Mat44& mat);
    const mm::Mat44& getBoneMat(int index) const;
    mm::Mat44* getBoneMatPtr(int index);

    DrMdlObj* m_drMdl;
};
}  // namespace ml

#endif
