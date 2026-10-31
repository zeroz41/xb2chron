#ifndef ML_DRSHDLGTMAN_H
#define ML_DRSHDLGTMAN_H

#include "ml/DrResFetch.h"

namespace mm { class Vec3; class Quat; class Col3; }

namespace grlib { template <typename T0> class CGLibShdListBase; }

namespace ml {
class DrMan;
class DrShdLgtHybrid;
class DrShdLgtGlobalIBL;
class DrShdLgtClustered;
class DrShdLgtObj;
class DrLightObjPnt;
class DrLightObjSpt;
class FileResTh;

// The light shader manager: the shaders of "/monolib/shader/shd_lgt.wishp" and the three light renderers its
// constructor creates. The field names are not the original's.
class DrShdLgtMan {
public:
    // the program kinds of the global IBL shader getGlobalIBLShader indexes (no enumerator has a name yet)
    enum GIBL_SHADER_TYPE {};
    // the shape renderDebug draws: renderDebugPnt passes 0 (no enumerator has a name yet)
    enum RENDER_DEBUG_TYPE {};

    DrShdLgtMan(DrMan* drMan);
    ~DrShdLgtMan();
    void releaseLightShader();
    void reloadShader(int);
    void renderBegin();
    void stockBegin();
    void stockEnd();
    DrShdLgtObj* getGlobalIBLShader(GIBL_SHADER_TYPE type);
    DrShdLgtHybrid* getHybridLight();
    void setupLgtBuff();
    void setupGlobalIBLShader(DrShdLgtObj* shader);
    void renderDebugPnt(DrLightObjPnt* light);
    void renderDebugSpt(DrLightObjSpt* light);
    void renderDebug(RENDER_DEBUG_TYPE type, const mm::Vec3& pos, const mm::Quat& rot, const mm::Vec3& scale,
                     const mm::Col3& color);

    DrMan* m_pDrMan;  // 0x0
    FileResTh* m_pRes;  // 0x8, the shader package's file
    grlib::CGLibShdListBase<DrShdLgtObj>* m_pShdList;  // 0x10
    // the package's extension entries: shaders of m_pShdList (getGlobalIBLShader indexes the second one's programs)
    DrShdLgtObj* m_pExtShader[3];  // 0x18
    DrResFetch m_fetch;  // 0x30, the light vertex parameters
    // renderBegin resets them
    unsigned short m_renderFlag;  // 0x40
    unsigned short m_renderIdx[2];  // 0x42
    unsigned char pad_46[0x2];
    int m_lgtBuffReq;  // 0x48, setupLgtBuff sets the light buffer up while it is not 0, then clears it
    unsigned char pad_4c[0x4];
    DrShdLgtHybrid* m_pHybrid;  // 0x50
    DrShdLgtGlobalIBL* m_pGlobalIBL;  // 0x58
    DrShdLgtClustered* m_pClustered;  // 0x60
};
}  // namespace ml

#endif
