#ifndef CLASSES_ML_DRMDOCTLDAMMY_H
#define CLASSES_ML_DRMDOCTLDAMMY_H

#include "classes/ml/DrMdlObj.h"

namespace ml {
// table 0x7100B7B978
class DrMdoCtlDammy : public ::ml::DrMdlObj {
public:
    DrMdoCtlDammy(const void* data, DrMan* drMan, int viewNum);
    virtual ~DrMdoCtlDammy();  // slot 0
    virtual void update();  // slot 2
    virtual void dispOffUpdate();  // slot 3
    virtual void resourceInit();  // slot 5

    unsigned char pad_190[0x20];  // sizeof 0x1B0 (DrMdlMan::createMdl news that much); not recovered
};
}  // namespace ml

#endif
