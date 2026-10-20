#ifndef CLASSES_ML_MICROTHREAD_H
#define CLASSES_ML_MICROTHREAD_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ml { class MicroThread; }
namespace nn { namespace os { class FiberType; }}

namespace ml {
// table 0x7100B78478
class MicroThread : public ::mm::mtl::PtrSingleton< ::ml::MicroThread> {
public:
    class MTHREAD;
    virtual ~MicroThread();  // slot 0
    virtual void destroyThread(ml::MicroThread::MTHREAD*) = 0;  // slot 2
    virtual void switchThreadMain(ml::MicroThread::MTHREAD*) = 0;  // slot 3
    virtual void switchThread(ml::MicroThread::MTHREAD*, ml::MicroThread::MTHREAD*) = 0;  // slot 4
    virtual void setupThread(ml::MicroThread::MTHREAD*, nn::os::FiberType* (*)(void*)) = 0;  // slot 5
};
}  // namespace ml

#endif
