#ifndef CLASSES_ML_DEVFILEWRITERNX_H
#define CLASSES_ML_DEVFILEWRITERNX_H

#include "classes/ml/DevFileWriterTh.h"

namespace ml {
// table 0x7100B77348
class DevFileWriterNx : public ::ml::DevFileWriterTh {
public:
    virtual bool asyncUpdate();  // slot 2
};
}  // namespace ml

#endif
