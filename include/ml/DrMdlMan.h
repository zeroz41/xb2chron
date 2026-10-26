#ifndef ML_DRMDLMAN_H
#define ML_DRMDLMAN_H

namespace ml {
class DrMan;
class DrMdoVertexMan;
class DrGpuCheckBase;
class DrGpuCheckRender;
class DrMdlObj;
class DrMdoGrpObj;
class DrStmReadCheck;

// DrMan's model manager (DrMan::m_mdlMan). Only what this file's users read is recovered; the field names are
// not the original's.
class DrMdlMan {
public:
    DrMdlMan(DrMan* man);
    DrMdlObj* createMdl(const void* resource, const char* name, int arg);
    DrMdoGrpObj* createInstantGrp(int arg, unsigned int viewNum);
    DrGpuCheckBase* createGpuCheckObj(int type);
    DrStmReadCheck* createStmLoadObj(const char* name);
    // news a DrGpuCheckObj (bool true) and appends it to the type's list
    DrGpuCheckBase* createEffGpuCheckObj(int type);

    unsigned char pad_0[0x8];
    DrMdoVertexMan* m_vertexMan;  // 0x8, the constructor's first DrMdoVertexMan
    unsigned char pad_10[0x38];
    DrGpuCheckRender* m_gpuCheckRender;  // 0x48, the constructor's DrGpuCheckRender
};
}  // namespace ml

#endif
