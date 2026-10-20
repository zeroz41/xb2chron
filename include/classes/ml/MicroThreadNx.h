#ifndef CLASSES_ML_MICROTHREADNX_H
#define CLASSES_ML_MICROTHREADNX_H

#include "classes/ml/MicroThread.h"

namespace nn { namespace os { class FiberType; }}

namespace ml {
// table 0x7100B78438
class MicroThreadNx : public ::ml::MicroThread {
public:
    virtual ~MicroThreadNx();  // slot 0
    virtual void destroyThread(ml::MicroThread::MTHREAD*);  // slot 2
    virtual void switchThreadMain(ml::MicroThread::MTHREAD*);  // slot 3
    virtual void switchThread(ml::MicroThread::MTHREAD*, ml::MicroThread::MTHREAD*);  // slot 4
    virtual void setupThread(ml::MicroThread::MTHREAD*, nn::os::FiberType* (*)(void*));  // slot 5
};
}  // namespace ml

#endif
