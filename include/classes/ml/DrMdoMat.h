#ifndef CLASSES_ML_DRMDOMAT_H
#define CLASSES_ML_DRMDOMAT_H

#include "classes/ml/DrMdlBase.h"

namespace ml { class MdsMatInfoHeader; }

namespace ml {
// table 0x7100B7BD30
class DrMdoMat : public ::ml::DrMdlBase {
public:
    virtual ~DrMdoMat();  // slot 0
    virtual void matCall_MatxView(ml::MdsMatInfoHeader const*, int, int);  // slot 17
};
}  // namespace ml

#endif
