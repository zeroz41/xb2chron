#ifndef CLASSES_ML_DRMDOCTLMPF_H
#define CLASSES_ML_DRMDOCTLMPF_H

#include "classes/ml/DrMdlObj.h"

namespace ml {
// table 0x7100B7B7B0
class DrMdoCtlMpf : public ::ml::DrMdlObj {
public:
    DrMdoCtlMpf(const void* data, const char* name, DrMan* drMan, int viewNum);  // DrMdlMan::createMdl news it
    virtual ~DrMdoCtlMpf();  // slot 0
    virtual void update();  // slot 2
    virtual void resourceInit();  // slot 5
    void releaseMpf();
    void defMpfrender();
    void defMpfZPreRender();
    void callZPrepassRender();
    void callRenderMpf();

    unsigned char pad_190[0x70];  // sizeof 0x200 (DrMdlMan::createMdl news that much); not recovered
};
}  // namespace ml

#endif
