// not proven yet: its table differs from the original's (word 6: _ZN2ml15DevFileWriterNx9getReaderEv where the original has _ZN2ml12DevFileJobTh9getReaderEv)
#ifndef CLASSES_ML_DEVFILEWRITERNX_H
#define CLASSES_ML_DEVFILEWRITERNX_H

#include "classes/ml/DevFileWriterTh.h"

namespace ml {
// table 0x7100B77348
class DevFileWriterNx : public ::ml::DevFileWriterTh {
public:
    virtual ~DevFileWriterNx();  // slot 0
    virtual void asyncUpdate();  // slot 2
    virtual void getReader();  // slot 4
};
}  // namespace ml

#endif
