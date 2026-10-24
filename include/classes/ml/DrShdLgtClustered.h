#ifndef CLASSES_ML_DRSHDLGTCLUSTERED_H
#define CLASSES_ML_DRSHDLGTCLUSTERED_H

#include "classes/ml/DrShdLgtDynamic.h"
#include "grlib/CGLibDblUniformBlock.h"

namespace ml { class DrLightMan; }
namespace ml { class DrLightObjPnt; }
namespace ml { class DrLightObjSpt; }
namespace ml { class DrShdLgtMan; }

namespace ml {
// table 0x7100B7E450
class DrShdLgtClustered : public ::ml::DrShdLgtDynamic {
public:
    virtual ~DrShdLgtClustered();  // slot 0
    virtual void stockBegin();  // slot 2
    virtual void stockEnd();  // slot 3
    virtual void update();  // slot 4
    virtual void addViewInfo(int);  // slot 6
    virtual void delViewInfo(int);  // slot 7
    virtual void stockPntList(ml::DrLightObjPnt*);  // slot 8
    virtual void stockSptList(ml::DrLightObjSpt*);  // slot 9
    virtual void render(ml::DrShdLgtMan*, ml::DrLightMan*);  // slot 10
    virtual void debugRender();  // slot 11

    void setPntLightUniformBlock(unsigned int idx, unsigned int location);
    void setSptLightUniformBlock(unsigned int idx, unsigned int location);
    void setPointerListUniformBlock(unsigned int idx, unsigned int location);
    void setLightListUniformBlock(unsigned int idx, unsigned int location);
    void setParamUniformBlock(unsigned int idx, unsigned int location);
    void setPntLightStorageBuffer(unsigned int idx, unsigned int location);
    void setSptLightStorageBuffer(unsigned int idx, unsigned int location);
    void setPointerListStorageBuffer(unsigned int idx, unsigned int location);
    void setLightListStorageBuffer(unsigned int idx, unsigned int location);
    void setParamStorageBuffer(unsigned int idx, unsigned int location);

    // one view's light buffers (0x190 bytes; the set*UniformBlock/StorageBuffer members index it by view);
    // field names from those setters
    struct ViewWork {
        grlib::CGLibDblUniformBlock pntLight;     // 0x0
        grlib::CGLibDblUniformBlock sptLight;     // 0x38
        grlib::CGLibDblUniformBlock pointerList;  // 0x70
        grlib::CGLibDblUniformBlock lightList;    // 0xA8
        unsigned char pad_e0[0x38];
        grlib::CGLibDblUniformBlock param;        // 0x118
        unsigned char pad_150[0x40];
    };

    unsigned char pad_8[0x18];
    ViewWork m_viewWork[1];  // 0x20; the view count is not proven
};
}  // namespace ml

#endif
