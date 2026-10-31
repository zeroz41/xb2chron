#ifndef CLASSES_ML_MICROTHREADNX_H
#define CLASSES_ML_MICROTHREADNX_H

#include "classes/ml/MicroThread.h"
#include "nn/os.h"

namespace ml {
// table 0x7100B78438
class MicroThreadNx : public ::ml::MicroThread {
public:
    // one of the fibers micro threads run on, 0x70 bytes (the names are not the original's)
    class FIBER {
    public:
        FIBER() : m_stack(nullptr), m_useNum(0), m_unk68(nullptr) {}
        nn::os::FiberType m_fiber;  // 0x0
        void* m_stack;              // 0x58: 0x10000 bytes from WorkCpu's stack memory
        int m_useNum;               // 0x60: threads set up on it (0: free)
        void* m_unk68;              // 0x68: null from construction, read nowhere in this unit
    };

    MicroThreadNx();
    virtual ~MicroThreadNx();  // slot 0
    virtual void destroyThread(ml::MicroThread::MTHREAD*);  // slot 2
    virtual void switchThreadMain(ml::MicroThread::MTHREAD*);  // slot 3
    virtual void switchThread(ml::MicroThread::MTHREAD*, ml::MicroThread::MTHREAD*);  // slot 4
    virtual void setupThread(ml::MicroThread::MTHREAD*, nn::os::FiberType* (*)(void*));  // slot 5

    FIBER m_fibers[16];  // 0x2C8
};
}  // namespace ml

#endif
