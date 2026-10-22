#ifndef CLASSES_ML_MICROTHREAD_H
#define CLASSES_ML_MICROTHREAD_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ml { class MicroThread; }
namespace ml { class MLTHG; }
namespace ml { class MLTH; }
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
    MLTHG* createGroup();
    void releaseGroup(MLTHG* group);
    MLTH* createThread(MLTHG* group, nn::os::FiberType* (*func)(void*), void* arg);
    void sleep(unsigned int frames, bool wait);
    void update(MLTHG* group);
    void exit();
    unsigned char pad_8[0x2B8];
    MLTHG* m_currentGroup;  // the group running now (getCurrentThreadID reads its thread); the name is not the original's
};
}  // namespace ml

#endif
