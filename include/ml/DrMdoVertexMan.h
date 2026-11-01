#ifndef ML_DRMDOVERTEXMAN_H
#define ML_DRMDOVERTEXMAN_H

#include "ml/DrMdoResList.h"
#include "ml/DrResMdoVertex.h"

namespace grlib { class CGLibVtxInstans; }

namespace ml {
// DrMdlMan's vertex manager (its constructor makes it first). Only what DrGpuCheckRender reads is recovered.
class DrMdoVertexMan {
public:
    DrMdoVertexMan();
    ~DrMdoVertexMan();
    void update();
    // the vertex resource of the stream: a listed one gains a reference, else a new one is linked at the end
    DrResMdoVertex* createVertexObj(DrCalcStmListObj* stm);
    // drops a reference to vertex; the last one unlinks and deletes it
    void releaseVertexObj(DrResMdoVertex* vertex);
    void begin();
    void end();

    static int s_nInstansBuffSize;

    DrMdoResList<DrResMdoVertex> m_vertexList;  // 0x0: update updates each (the name is not the original's)
    grlib::CGLibVtxInstans* m_instans;  // 0x10, the instance ring DrGpuCheckRender takes its part of (the name is not the original's)
};
}  // namespace ml

#endif
