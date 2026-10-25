#ifndef ML_DRMDLMAN_H
#define ML_DRMDLMAN_H

namespace ml {
class DrMan;
class DrMdoVertexMan;
class DrGpuCheckBase;
class DrGpuCheckRender;

// DrMan's model manager (DrMan::m_mdlMan). Only what this file's users read is recovered; the field names are
// not the original's.
class DrMdlMan {
public:
    DrMdlMan(DrMan* man);
    // news a DrGpuCheckObj (bool true) and appends it to the type's list
    DrGpuCheckBase* createEffGpuCheckObj(int type);

    unsigned char pad_0[0x8];
    DrMdoVertexMan* m_vertexMan;  // 0x8, the constructor's first DrMdoVertexMan
    unsigned char pad_10[0x38];
    DrGpuCheckRender* m_gpuCheckRender;  // 0x48, the constructor's DrGpuCheckRender
};
}  // namespace ml

#endif
