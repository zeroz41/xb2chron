#ifndef CLASSES_ML_DEVTOUCHNX_H
#define CLASSES_ML_DEVTOUCHNX_H

#include "classes/ml/DevTouch.h"
#include "ml/WorkUtil.h"
#include "mm/mtl/UniquePtr.h"

namespace ml {
// table 0x7100B768A8
class DevTouchNx : public ::ml::DevTouch {
public:
    // the SDK side: the touch screen's last states (0x290 bytes: update copies them in whole)
    struct Impl {
        // reads the touch screen's states and reports the touches' downs, moves and ups to dev
        void update(DevTouchNx* dev);
        unsigned char pad_0[0x290];
    };

    // inline: the original keeps its copies in the weak tail (updateDevice is the key function)
    // inline: WorkUtil::createWork<DevTouchNx> builds it (the original has no out-of-line copy)
    DevTouchNx(const char* name, WorkObj* parent)
        : DevTouch(name, parent), m_impl(new (WorkUtil::getWorkMem(), nullptr, 0, 8, false) Impl) {}
    virtual ~DevTouchNx() {}  // slot 0
    virtual void updateDevice();  // slot 20
    virtual bool createDevice();  // slot 21
    virtual void releaseDevice();  // slot 22

    mm::mtl::UniquePtr<Impl> m_impl;  // 0x7D0
};
}  // namespace ml

#endif
