#ifndef CLASSES_ML_DRMDOCTLCLDMDL_H
#define CLASSES_ML_DRMDOCTLCLDMDL_H

#include "classes/ml/DrMdlObj.h"

namespace cloud { class CloudMdlDataObj; }

namespace ml {
// table 0x7100B7B718
class DrMdoCtlCldMdl : public ::ml::DrMdlObj {
public:
    DrMdoCtlCldMdl(const void* data, DrMan* drMan, int viewNum);
    virtual ~DrMdoCtlCldMdl();  // slot 0
    virtual void update();  // slot 2
    virtual void dispOffUpdate();  // slot 3
    virtual void resourceInit();  // slot 5

    unsigned char pad_188[0x20];
    // 0x1A8: the cloud model data resourceInit creates from m_pCldData (the names are not the original's)
    cloud::CloudMdlDataObj* m_pCldMdlData;
    const void* m_pCldData;  // 0x1B0
};
}  // namespace ml

#endif
